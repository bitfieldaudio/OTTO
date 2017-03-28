#ifndef AUDIO_JACK_H
#define AUDIO_JACK_H

#include <cstdlib>
#include <string>

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <sndfile.hh>
#include <pthread.h>

#include "../events.h"

namespace audio {

typedef jack_default_audio_sample_t AudioSample;
const size_t SAMPLE_SIZE = sizeof(AudioSample);

namespace jack {
int init (int argc, char *argv[]);

struct Project {
  std::string name;
  std::string path;
};

struct ThreadInfo {
  // Number of ports
  const static uint nOut = 2;
  const static uint nIn = 4;
  const static uint nTracks = 4;

  Project *project;
  jack_client_t *client;
  jack_status_t jackStatus;

  struct Ports {
    union { // In theory this allows to ways to access the outputs.
      struct {
        jack_port_t *outL;
        jack_port_t *outR;
      };
      jack_port_t *out[nOut];
    };
    jack_port_t *in[nIn];
  } ports;

  jack_nframes_t rbSize = 16384;
  jack_ringbuffer_t *ringBuf;
  jack_nframes_t samplerate;

  SNDFILE *sndFile;

  struct Data {
    union { // Theres probably a better way to do it though
      struct {
        AudioSample *outL;
        AudioSample *outR;
      };
      AudioSample *out[2];
    };
    AudioSample *in[nTracks];
  } data;

  volatile bool doProcess;
  volatile int status;

  struct Disk {
    pthread_t *thread;
  } disk;
};

struct _Events {
  Dispatcher<ThreadInfo*> preInit;
  Dispatcher<ThreadInfo*> postInit;
  Dispatcher<ThreadInfo*> preExit;
  Dispatcher<ThreadInfo*> postExit;
  Dispatcher<jack_nframes_t, ThreadInfo*> jackProcess;
} events;
}
}

#endif
