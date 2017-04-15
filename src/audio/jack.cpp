#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <cerrno>
#include <csignal>

#include <sndfile.hh>
#include <pthread.h>
#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <plog/Log.h>

#include "../globals.h"
#include "jack.h"
#include "../events.h"

namespace audio {

namespace jack {

const char *CLIENT_NAME = "tapedeck";

jack_client_t *client;

void shutdown(void *arg) {
  LOGI << "JACK shut down, exiting";
}

int process(jack_nframes_t nframes, void *arg) {
  if (!GLOB.doProcess) return 0;

  for (uint i = 0; i < GLOB.nOut; i++)
    GLOB.data.out[i] = (AudioSample *) jack_port_get_buffer(
      GLOB.ports.out[i], nframes);

  for (uint i = 0; i < GLOB.nIn; i++)
    GLOB.data.in[i] = (AudioSample *) jack_port_get_buffer(
      GLOB.ports.in[i], nframes);

  memset(GLOB.data.proc, 0, SAMPLE_SIZE * nframes);

  GLOB.events.preProcess(nframes); // Mic/Line input, Read only
  GLOB.events.process1(nframes);   // Synth
  GLOB.events.process2(nframes);   // Effects
  GLOB.events.postProcess(nframes);// Output, Read only

  return 0;
}

// Callback for samplerate change
int srateCallback(jack_nframes_t nframes, void *arg) {
  GLOB.samplerate = nframes;
  LOGI << "New sample rate: " << nframes;
  return 0;
}

// Callback for buffersize change
int bufsizeCallback(jack_nframes_t nframes, void *arg) {
  GLOB.buffersize = nframes;
  LOGI << "New buffer size: " << nframes;
  return 0;
}

void setupPorts() {

  // Register input ports
  for (uint i = 0; i < GLOB.nIn; i++) {
    //TODO: replace std::string here
    std::string name = "input";
    name += std::to_string(i + 1);

    GLOB.ports.in[i] = jack_port_register(
      GLOB.client,
      name.c_str(),
      JACK_DEFAULT_AUDIO_TYPE,
      JackPortIsInput,
      0);
    if (GLOB.ports.in[i] == NULL)
      LOGE << "Couldn't register port '" << name << "'";
  }

  // function to register outputs
  auto registerOutput = [&](const char *name) {
    return jack_port_register(
      GLOB.client,
      name,
      JACK_DEFAULT_AUDIO_TYPE,
      JackPortIsOutput,
      0);
  };
  // register output ports
  GLOB.ports.outL = registerOutput("outLeft");
  GLOB.ports.outR = registerOutput("outRight");

  // Find physical capture ports
  auto findPorts = [&](auto criteria, const char * type = "audio") {
    const char **ports = jack_get_ports(
      GLOB.client,
      NULL,
      type,
      criteria);
    if (ports == NULL) {
      LOGF << "No ports found matching " << std::to_string(criteria);
      jack_client_close(GLOB.client);
    }
    return ports;
  };

  // Helper function for connections
  auto connectPort = [&](const char *src_name, const char *dest_name) {
    if (jack_connect(GLOB.client, dest_name, src_name)) {
      LOGF << "Cannot connect port '" << src_name
      << "' to '" << dest_name << "'";
      LOGD << "src type: '" << jack_port_type(
        jack_port_by_name(client, src_name)) << "'";
      LOGD << "dest type: '" << jack_port_type(
        jack_port_by_name(client, dest_name)) << "'";
    }
  };

  const char **inputs  = findPorts(JackPortIsPhysical | JackPortIsOutput);
  const char **outputs = findPorts(JackPortIsPhysical | JackPortIsInput);

  uint ninputs = 0;
  while (inputs[ninputs] != NULL) ninputs++;
  uint noutputs = 0;
  while (outputs[noutputs] != NULL) noutputs++;

  for (uint i = 0; i < GLOB.nIn; i++) {
    connectPort(jack_port_name(GLOB.ports.in[i]), inputs[i % ninputs]);
  }
  for (uint i = 0; i < GLOB.nOut; i++) {
    connectPort(outputs[i % noutputs], jack_port_name(GLOB.ports.out[i]));
  }
}

void init() {

  client = jack_client_open(CLIENT_NAME, JackNullOption, &GLOB.jackStatus);

  GLOB.client = client;

  GLOB.events.preInit();

  if (!(GLOB.jackStatus & JackServerStarted)) {
    LOGF << "JACK server not running";
  }

  LOGI << "JACK server started";
  LOGD << "JACK client status: " << GLOB.jackStatus;

  GLOB.doProcess = 0;

  jack_set_process_callback(client, process, NULL);
  jack_set_sample_rate_callback(client, srateCallback, NULL);
  jack_set_buffer_size_callback(client, bufsizeCallback, NULL);

  GLOB.samplerate = jack_get_sample_rate(client);
  GLOB.buffersize = jack_get_buffer_size(client);

  if (jack_activate(client)) LOGF << "Cannot activate JACK client";

  setupPorts();

  for (uint i = 0; i < GLOB.nIn; i++)
    GLOB.data.in[i] = (AudioSample *)
      malloc(SAMPLE_SIZE * GLOB.buffersize);

  for (uint i = 0; i < GLOB.nOut; i++)
    GLOB.data.out[i] = (AudioSample *)
      malloc(SAMPLE_SIZE * GLOB.buffersize);

  GLOB.data.proc = (AudioSample *) malloc(SAMPLE_SIZE * GLOB.buffersize);

  GLOB.events.postInit();

  LOGI << "Completed initialization, enabling canProcess";

  GLOB.doProcess = 1;
}

void exit() {

  LOGI << "Exiting";

  GLOB.events.preExit();

  jack_client_close(client);

  GLOB.events.postExit();
}
}
}
