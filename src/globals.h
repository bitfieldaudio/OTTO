#pragma once

#include <cstdlib>
#include <string>

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <sndfile.h>
#include <pthread.h>

#include "events.h"

namespace audio {
typedef jack_default_audio_sample_t AudioSample;
}

struct Project {
  std::string name = "Unnamed";
  std::string path = "unnamed.wav";
};

struct __Globals_t {
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
        audio::AudioSample *outL;
        audio::AudioSample *outR;
      };
      audio::AudioSample *out[2];
    };
    audio::AudioSample *in[nIn];
  } data;

  volatile bool doProcess;
  volatile int status;

  struct {
    Dispatcher<> preInit;
    Dispatcher<> postInit;
    Dispatcher<> preExit;
    Dispatcher<> postExit;
    Dispatcher<jack_nframes_t> preProcess; // IDK
    Dispatcher<jack_nframes_t> process1;   // Synths
    Dispatcher<jack_nframes_t> process2;   // Effects
    Dispatcher<jack_nframes_t> postProcess;// Read only
  } events;
};

extern __Globals_t GLOB;
