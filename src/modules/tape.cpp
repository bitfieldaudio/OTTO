#include "tape.h"
#include "../audio/jack.h"
#include "../globals.h"
#include <plog/Log.h>
#include <sndfile.hh>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace audio;
using namespace audio::jack;

const int BITRATE = SF_FORMAT_PCM_32;

void *TapeModule::diskRoutine(void *arg) {
  auto self = (TapeModule *) arg;

  char *framebuf = (char*) malloc(rbSize);

  while (1) {
    while (self->playing || self->recording) {
      if (self->playing) {
        auto space = jack_ringbuffer_write_space(self->playBuf);

        if (space >= SAMPLE_SIZE) {
          uint nframes = space / SAMPLE_SIZE;
          uint size = SAMPLE_SIZE * nframes * nTracks;
          // Clear the framebuffer
          memset(framebuf, 0, size);

          auto read = self->sndfile.readf((AudioSample*) framebuf, nframes);

          if (read < nframes) {
            LOGD << "Playing past end of file in " << read << " frames";
          }

          jack_ringbuffer_write(self->playBuf, framebuf, size);
        }
      }

      if (self->recording) {
        auto space = jack_ringbuffer_read_space(self->recBuf);

        if (space >= SAMPLE_SIZE) {
          uint nframes = space / SAMPLE_SIZE;
          uint size = SAMPLE_SIZE * nframes * nTracks;

          memset(framebuf, 0, size);

          jack_ringbuffer_read(self->recBuf, framebuf, size);

          if (self->sndfile.writef((AudioSample*) framebuf, nframes) != nframes) {
            LOGF << "Cannot write sndfile:";
            LOGF << self->sndfile.strError();
            goto done;
          }
        }
      }
      LOGE_IF(self->overruns) << "Overruns: " << self->overruns;
    }
  }

done:
  free(framebuf);
  return 0;
}

void TapeModule::process(jack_nframes_t nframes, Module *arg) {
  auto *self = (TapeModule *) arg;

  if (self->recording || self->playing) {
    uint bs = nTracks * SAMPLE_SIZE * nframes;
    if (self->playing) {
      if (jack_ringbuffer_read(self->playBuf, (char *) self->buffer, bs) < bs) {
        self->overruns++;
      };
    } else {
      memset(self->buffer, 0, bs);
    }
    for (uint f = 0; f < nframes; f++) {
      self->buffer[f * nTracks + self->recording - 1]
        = GLOB.data.proc[f];
    }
    if (self->recording) {
      if (jack_ringbuffer_write(self->recBuf, (char *) self->buffer, bs) < bs) {
        self->overruns++;
      }
    }
  }

  self->mixOut(nframes);
}

// Thanks: http://www.vttoth.com/CMS/index.php/technical-notes/68
static inline AudioSample mix(AudioSample A, AudioSample B) {
  return 2 * (A + B) - 2 * A * B - 1;
}

void TapeModule::mixOut(jack_nframes_t nframes) {
  if (playing) { // mix the tracks
    // TODO: Configurable and all that
    AudioSample mixed;
    for (uint f = 0; f < nframes; f++) {
      mixed = buffer[f * nTracks];
      for (uint t = 1; t < nTracks ; t++) {
        mixed = mix(mixed, buffer[f * nTracks + t]);
      }
      GLOB.data.outL[f] = GLOB.data.outR[f] = mixed;
    }
  } else { // Just monitor the proc
    memcpy(GLOB.data.outL, GLOB.data.proc, nframes * SAMPLE_SIZE);
    memcpy(GLOB.data.outR, GLOB.data.proc, nframes * SAMPLE_SIZE);
  }
}

void TapeModule::exitThread(Module *arg) {
  auto *self = (TapeModule *) arg;
  self->recording = 0;
  sf_close(self->sndfile.rawHandle());
}

void TapeModule::initThread(Module *arg) {
  LOGD << "Registered TapeModule";
  auto *self = (TapeModule *) arg;

  self->recBuf = jack_ringbuffer_create(
    self->rbSize);

  self->playBuf = jack_ringbuffer_create(
    self->rbSize);

  self->bufferSize = audio::SAMPLE_SIZE * GLOB.buffersize * nTracks;
  self->buffer = (audio::AudioSample *) malloc(self->bufferSize),
  /* Note from JACK sample capture_client.cpp:
   * When JACK is running realtime, jack_activate() will have
   * called mlockall() to lock our pages into memory.  But, we
   * still need to touch any newly allocated pages before
   * process() starts using them.  Otherwise, a page fault could
   * create a delay that would force JACK to shut us down.
   */
  memset(self->recBuf->buf, 0, self->recBuf->size);
  memset(self->playBuf->buf, 0, self->playBuf->size);
  memset(self->buffer, 0, self->bufferSize);

  int samplerate = GLOB.samplerate;
  int channels = self->nTracks;
  int format = SF_FORMAT_WAV | BITRATE;

  self->sndfile =
    SndfileHandle(GLOB.project->path, SFM_RDWR, format, channels, samplerate);

  if (self->sndfile.error()) {
    LOGE << "Cannot open sndfile '" <<
      GLOB.project->path.c_str() << "' for output:";
    LOGE << self->sndfile.strError() << ")";

    jack_client_close(GLOB.client);
    exit(1);
  }
  self->diskThread = std::thread(TapeModule::diskRoutine, self);
}

void TapeModule::init() {
  GLOB.events.postInit.add(getInstance(), initThread);
  GLOB.events.preExit.add(getInstance(), exitThread);
  GLOB.events.postProcess.add(getInstance(), process);
}


