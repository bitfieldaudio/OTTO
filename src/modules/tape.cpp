#include "tape.h"
#include "../audio/jack.h"
#include "../globals.h"
#include <plog/Log.h>
#include <sndfile.hh>


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

      while (self->recording &&
        jack_ringbuffer_read_space(self->ringBuf) >= SAMPLE_SIZE) {

      //self->sndfile.readf((AudioSample*) framebuf, 1);
      memset(framebuf, 0, bytesPrFrame);

      uint pos = SAMPLE_SIZE * (self->recording - 1);
      jack_ringbuffer_read(self->ringBuf, framebuf + pos, SAMPLE_SIZE);

      if (self->sndfile.writef((AudioSample*) framebuf, 1) != 1) {
        LOGE << "Cannot write sndfile:";
        LOGE << self->sndfile.strError();
        goto done;
      }
    }

    pthread_cond_wait(&dataReady, &diskLock);
  }

done:
  pthread_mutex_unlock(&diskLock);
  free(framebuf) ;
  return 0;
}

void process(jack_nframes_t nframes, Module *arg) {
  auto *self = (TapeModule *) arg;

  if (self->recording) {
    if (jack_ringbuffer_write(self->ringBuf, (char *) GLOB.data.in[0],
      SAMPLE_SIZE * nframes) < SAMPLE_SIZE * nframes) {
      LOGE << "TapeModule overrun";
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

  if (self->monitor) {
    for (uint i = 0; i < GLOB.nOut; i++)
      memcpy(GLOB.data.out[i], GLOB.data.in[0], SAMPLE_SIZE * nframes);
  }
}

void exitThread(Module *arg) {
  auto *self = (TapeModule *) arg;
  self->recording = 0;
  sf_close(self->sndfile.rawHandle());
}

void initThread(Module *arg) {
  LOGD << "Registered TapeModule";
  auto *self = (TapeModule *) arg;
  size_t in_size = GLOB.nIn * sizeof(AudioSample*);

  self->ringBuf = jack_ringbuffer_create(
    GLOB.nIn * SAMPLE_SIZE * self->rbSize);

  /* Note from JACK sample capture_client.cpp:
   * When JACK is running realtime, jack_activate() will have
   * called mlockall() to lock our pages into memory.  But, we
   * still need to touch any newly allocated pages before
   * process() starts using them.  Otherwise, a page fault could
   * create a delay that would force JACK to shut us down.
   */
  memset(self->ringBuf->buf, 0, self->ringBuf->size);
  memset(GLOB.data.in, 0, in_size);

  int samplerate = GLOB.samplerate;
  int channels = self->nTracks;
  int format = SF_FORMAT_WAV | BITRATE;

  self->sndfile =
    SndfileHandle(GLOB.project->path, SFM_RDWR, format, channels, samplerate);

  if (self->sndfile.error()) {
    // Error
    LOGE << "Cannot open sndfile '" <<
      GLOB.project->path.c_str() << "' for output:";
    LOGE << self->sndfile.strError() << ")";

    jack_client_close(GLOB.client);
    exit(1);
  }

  pthread_create(&self->thread, NULL, diskRoutine, self);
}

void TapeModule::init() {
  GLOB.events.postInit.add(getInstance(), initThread);
  GLOB.events.preExit.add(getInstance(), exitThread);
  GLOB.events.postProcess.add(getInstance(), process);
}


