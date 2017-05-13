#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <cerrno>
#include <csignal>

#include <jack/jack.h>
#include <plog/Log.h>

#include "../globals.h"
#include "jack.h"
#include "../events.h"


void JackAudio::init() {
  client = jack_client_open(CLIENT_NAME.c_str(), JackNullOption, &jackStatus);

  if (!jackStatus & JackServerStarted) {
    LOGF << "Failed to start jack server";
    GLOB.running = false;
    return;
  }

  LOGI << "Jack server started";
  LOGD << "Jack client status: " << jackStatus;

  jack_set_process_callback(
    client,
    [](jack_nframes_t nframes, void *arg) {
      ((JackAudio*)arg)->process(nframes);
      return 0;
    }, this);

  jack_set_sample_rate_callback(
    client,
    [](jack_nframes_t nframes, void *arg) {
      ((JackAudio*)arg)->samplerateCallback(nframes);
      return 0;
    }, this);

  jack_set_buffer_size_callback(
    client,
    [](jack_nframes_t nframes, void *arg) {
      ((JackAudio*)arg)->buffersizeCallback(nframes);
      return 0;
    }, this);

  bufferSize = jack_get_buffer_size(client);

  if (jack_activate(client)) {
    LOGF << "Cannot activate JACK client";
    GLOB.running = false;
    return;
  }

  setupPorts();

  GLOB.audioData.outL  = (float *) malloc(bufferSize * sizeof(float));
  GLOB.audioData.outR  = (float *) malloc(bufferSize * sizeof(float));
  GLOB.audioData.input = (float *) malloc(bufferSize * sizeof(float));
  GLOB.audioData.proc  = (float *) malloc(bufferSize * sizeof(float));

  LOGI << "Initialized JackAudio. Beginning processing";

  processing = true;
}

void JackAudio::exit() {
  LOGI << "Closing Jack client";
  jack_client_close(client);
  GLOB.running = false;
}

void JackAudio::samplerateCallback(uint srate) {
  if (srate != GLOB.samplerate) {
    LOGF << "Jack changed the sample rate!";
    GLOB.running = false;
  }
}

void JackAudio::buffersizeCallback(uint buffsize) {
  //TODO
}

void JackAudio::setupPorts() {
  // Register an input port

  ports.input = jack_port_register(
    client, "input", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

  if (ports.input == NULL) {
    LOGF << "Couldn't register input port";
    GLOB.running = false;
    return;
  }

  ports.outL = jack_port_register(
    client, "outLeft", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  ports.outR = jack_port_register(
    client, "outRight", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

  auto inputs  = findPorts(JackPortIsPhysical | JackPortIsOutput);
  auto outputs = findPorts(JackPortIsPhysical | JackPortIsInput);

  if (inputs.empty()) {
    LOGF << "Couldn't find physical input port";
    GLOB.running = false;
    return;
  }
  if (outputs.empty()) {
    LOGF << "Couldn't find physical output ports";
    GLOB.running = false;
    return;
  }

  bool s;

  s = connectPorts(jack_port_name(ports.input), inputs[0]);
  if (!s) {GLOB.running = false; return;}

  s = connectPorts(outputs[0 % outputs.size()], jack_port_name(ports.outL));
  if (!s) {GLOB.running = false; return;}

  s = connectPorts(outputs[1 % outputs.size()], jack_port_name(ports.outR));
  if (!s) {GLOB.running = false; return;}

}

std::vector<std::string> JackAudio::findPorts(int criteria, PortType type) {
  const char **ports = jack_get_ports(
    client,
    NULL,
    (type == PortType::AUDIO) ? "audio" : "midi",
    criteria);
  std::vector<std::string> ret;
  for (int i = 0; ports[i] != 0; i++) {
    ret.push_back(ports[i]);
  }
  return ret;
};

// Helper function for connections
bool JackAudio::connectPorts(std::string src, std::string dest) {
  return not jack_connect(client, dest.c_str(), src.c_str());
}

void shutdown(void *arg) {
  LOGI << "JACK shut down, exiting";
}

void JackAudio::process(uint nframes) {
  if ( not (processing && GLOB.running)) return;
  GLOB.audioData.outL = (float *) jack_port_get_buffer(ports.outL, nframes);
  GLOB.audioData.outR = (float *) jack_port_get_buffer(ports.outR, nframes);
  GLOB.audioData.input = (float *) jack_port_get_buffer(ports.input, nframes);

  memset(GLOB.audioData.proc, 0, sizeof(float) * nframes);

  GLOB.synth.process(nframes);
  GLOB.effect1.process(nframes);
  GLOB.effect2.process(nframes);
  GLOB.effect3.process(nframes);
  GLOB.effect4.process(nframes);
  GLOB.tapedeck.process(nframes);
  GLOB.mixer.process(nframes);
}
