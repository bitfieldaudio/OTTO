#pragma once

#include <cstdlib>
#include <string>

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <sndfile.h>
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
  const static uint nIn = 2;

  Project *project;
  jack_client_t *client;
  jack_status_t jackStatus;

  struct {
    union { // In theory this allows to ways to access the outputs.
      struct {
        jack_port_t *outL;
        jack_port_t *outR;
      };
      jack_port_t *out[nOut];
    };
    jack_port_t *in[nIn];
  } ports;

  jack_nframes_t samplerate;

  struct {
    union { // Theres probably a better way to do it though
      struct {
        AudioSample *outL;
        AudioSample *outR;
      };
      AudioSample *out[2];
    };
    AudioSample *in[nIn];
  } data;

  volatile bool doProcess;
  volatile int status;
};

struct {
  Dispatcher<ThreadInfo*> preInit;
  Dispatcher<ThreadInfo*> postInit;
  Dispatcher<ThreadInfo*> preExit;
  Dispatcher<ThreadInfo*> postExit;
  Dispatcher<jack_nframes_t, ThreadInfo*> preProcess; // IDK
  Dispatcher<jack_nframes_t, ThreadInfo*> process1;   // Synths
  Dispatcher<jack_nframes_t, ThreadInfo*> process2;   // Effects
  Dispatcher<jack_nframes_t, ThreadInfo*> postProcess;// Read only
} events;
}
}
