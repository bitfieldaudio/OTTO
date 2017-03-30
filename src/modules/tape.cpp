#include "tape.h"
#include "../audio/jack.h"
#include <plog/Log.h>

using namespace audio::jack;
using namespace audio;

const int BITRATE = SF_FORMAT_PCM_32;

pthread_mutex_t diskLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dataReady = PTHREAD_COND_INITIALIZER;
uint bytesPrFrame = TapeModule::nTracks * SAMPLE_SIZE;

// Run by the disk thread
void * diskRoutine(void *arg) {
  auto self = (TapeModule *) arg;

  char *framebuf = (char*) malloc(bytesPrFrame);

  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  pthread_mutex_lock(&diskLock);

  while(1) {

    while (jack_ringbuffer_read_space(self->ringBuf) >= bytesPrFrame) {
      jack_ringbuffer_read(self->ringBuf, framebuf, bytesPrFrame);

      if (sf_writef_float(self->sndFile, (AudioSample*) framebuf, 1) != 1) {
        // Error
        char errstr[256];
        sf_error_str (0, errstr, sizeof (errstr) - 1);

        LOGE << "Cannot write sndfile (" << errstr << ")";
        goto done;
      }
    }

    pthread_cond_wait(&dataReady, &diskLock);
  }

done:
  pthread_mutex_unlock(&diskLock);
  free(framebuf)

;
  return 0;
}

void process(jack_nframes_t nframes, jack::ThreadInfo *info, Module *arg) {
  auto *self = (TapeModule *) arg;

  for (uint i = 0; i < nframes; i++) {
    for (uint chn = 0; chn < self->nTracks; chn++) {
      if (jack_ringbuffer_write(self->ringBuf, (char *) info->data.in[chn],
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

void exitThread(jack::ThreadInfo *info, Module *arg) {
  auto *self = (TapeModule *) arg;
  pthread_join(self->thread, (void **) NULL);
  sf_close(self->sndFile);
}

void initThread(jack::ThreadInfo *info, Module *arg) {
  LOGD << "Registered TapeModule";
  auto *self = (TapeModule *) arg;
  size_t in_size = info->nIn * sizeof(AudioSample*);
  auto in = (AudioSample **) malloc(in_size);

  self->ringBuf = jack_ringbuffer_create(
    info->nIn * SAMPLE_SIZE * self->rbSize);

  /* Note from JACK sample capture_client.cpp:
   * When JACK is running realtime, jack_activate() will have
   * called mlockall() to lock our pages into memory.  But, we
   * still need to touch any newly allocated pages before
   * process() starts using them.  Otherwise, a page fault could
   * create a delay that would force JACK to shut us down.
   */
  memset(self->ringBuf->buf, 0, self->ringBuf->size);
  memset(in, 0, in_size);

  SF_INFO sfInfo;
  sfInfo.samplerate = info->samplerate;
  sfInfo.channels = self->nTracks;
  sfInfo.format = SF_FORMAT_WAV | BITRATE;

  if ((self->sndFile = sf_open(info->project->path.c_str(),
  SFM_RDWR, &sfInfo)) == NULL) {

    // Error
    char errstr[256];
    sf_error_str (0, errstr, sizeof (errstr) - 1);

    LOGE << "Cannot open sndfile '" <<
      info->project->path << "' for output (" << errstr << ")";

    jack_client_close(info->client);
    exit(1);
  }
  pthread_create(&self->thread, NULL, diskRoutine, self);
}

void TapeModule::init() {
  events.postInit.add(getInstance(), initThread);
  events.preExit.add(getInstance(), exitThread);
  events.postProcess.add(getInstance(), process);
}

