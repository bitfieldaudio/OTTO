#include "tape.h";
#include "../audio/jack.h";
#include <plog/Log.h>

using namespace audio::jack;
using namespace audio;

const int BITRATE = SF_FORMAT_PCM_32;

pthread_mutex_t diskLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dataReady = PTHREAD_COND_INITIALIZER;
uint bytesPrFrame = ThreadInfo::nTracks * SAMPLE_SIZE;

// Run by the disk thread
void * diskRoutine(void *arg) {
  auto *info = (jack::ThreadInfo *) arg;

  char *framebuf = (char*) malloc(bytesPrFrame);

  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  pthread_mutex_lock(&diskLock);

  while(1) {

    while (jack_ringbuffer_read_space(info->ringBuf) >= bytesPrFrame) {
      jack_ringbuffer_read(info->ringBuf, framebuf, bytesPrFrame);

      if (sf_writef_float(info->sndFile, (AudioSample*) framebuf, 1) != 1) {
        // Error
        char errstr[256];
        sf_error_str (0, errstr, sizeof (errstr) - 1);

        LOGE << "Cannot write sndfile (" << errstr << ")";
        info->status = EIO;
        goto done;
      }
    }

    pthread_cond_wait(&dataReady, &diskLock);
  }

done:
  pthread_mutex_unlock(&diskLock);
  free(framebuf);
  return 0;
}

void process(jack_nframes_t nframes, jack::ThreadInfo *info) {
  for (uint i = 0; i < nframes; i++) {
    for (uint chn = 0; chn < info->nTracks; chn++) {
      if (jack_ringbuffer_write(info->ringBuf, (char *) info->data.in[chn],
      SAMPLE_SIZE)) {
        LOGE << "overrun";
      }
    }
  }

  /* Tell the disk thread there is work to do.  If it is already
   * running, the lock will not be available.  We can't wait
   * here in the process() thread, but we don't need to signal
   * in that case, because the disk thread will read all the
   * data queued before waiting again. */
  if (pthread_mutex_trylock (&diskLock) == 0) {
    pthread_cond_signal (&dataReady);
    pthread_mutex_unlock (&diskLock);
  }
}

void exitThread(jack::ThreadInfo *info) {
  pthread_join(*info->disk.thread, (void **) NULL);
  sf_close(info->sndFile);
}

void initThread(jack::ThreadInfo *info) {
  SF_INFO sfInfo;
  sfInfo.samplerate = info->samplerate;
  sfInfo.channels = info->nTracks;
  sfInfo.format = SF_FORMAT_WAV | BITRATE;

  if ((info->sndFile = sf_open(info->project->path.c_str(),
  SFM_RDWR, &sfInfo)) == NULL) {

    // Error
    char errstr[256];
    sf_error_str (0, errstr, sizeof (errstr) - 1);

    LOGE << "Cannot open sndfile '" <<
      info->project->path << "' for output (" << errstr << ")";

    jack_client_close(info->client);
    exit(1);
  }
  pthread_create(info->disk.thread, NULL, diskRoutine, info);
}

void TapeModule::init() {
  events.postInit.add(initThread);
  events.preExit.add(exitThread);
  events.jackProcess.add(process);
}
