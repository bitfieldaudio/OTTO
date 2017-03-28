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

#include "jack.h"
#include "../events.h"

namespace audio {
namespace disk {

}

namespace jack {

const char *CLIENT_NAME = "tapedeck";

jack_client_t *client;

void shutdown(void *arg) {
  LOGI << "JACK shut down, exiting";
  exit(1);
}

int process(jack_nframes_t nframes, void *arg) {
  auto *info = (ThreadInfo *) arg;

  if (!info->doProcess) return 0;

  for (uint i = 0; i < info->nOut; i++)
    info->data.out[i] = (AudioSample *) jack_port_get_buffer(
      info->ports.out[i], nframes);

  for (uint i = 0; i < info->nTracks; i++)
    info->data.in[i] = (AudioSample *) jack_port_get_buffer(
      info->ports.in[i], nframes);

  // Play silence for now
  for (auto data: info->data.out)
    memset(data, 0, SAMPLE_SIZE);

  events.jackProcess(nframes, info);

  return 0;
}

// Callback for samplerate change
int srateCallback(jack_nframes_t nframes, void *arg) {
  auto *info = (ThreadInfo *) arg;
  info->samplerate = nframes;
  LOGI << "New sample rate: " << nframes;
  return 0;
}

void setupPorts(ThreadInfo *info) {
  size_t in_size = info->nIn * sizeof(AudioSample*);
  auto in = (AudioSample **) malloc(in_size);

  info->ringBuf = jack_ringbuffer_create(
    info->nIn * SAMPLE_SIZE * info->rbSize);

  /* Note from JACK sample capture_client.cpp:
   * When JACK is running realtime, jack_activate() will have
   * called mlockall() to lock our pages into memory.  But, we
   * still need to touch any newly allocated pages before
   * process() starts using them.  Otherwise, a page fault could
   * create a delay that would force JACK to shut us down.
   */
  memset(info->ringBuf->buf, 0, info->ringBuf->size);
  memset(in, 0, in_size);

  // Register input ports
  for (uint i = 0; i < info->nIn; i++) {
    //TODO: replace std::string here
    std::string name = "input";
    name += std::to_string(i + 1);

    info->ports.in[i] = jack_port_register(
      info->client,
      name.c_str(),
      JACK_DEFAULT_AUDIO_TYPE,
      JackPortIsInput,
      0);
    if (info->ports.in[i] == NULL)
      LOGE << "Couldn't register port '" << name << "'";
  }

  // function to register outputs
  auto registerOutput = [&](const char *name) {
    return jack_port_register(
      info->client,
      name,
      JACK_DEFAULT_AUDIO_TYPE,
      JackPortIsOutput,
      0);
  };
  // register output ports
  info->ports.outL = registerOutput("outLeft");
  info->ports.outR = registerOutput("outRight");

  // Find physical capture ports
  auto findPorts = [&](auto criteria, const char * type = "audio") {
    const char **ports = jack_get_ports(
      info->client,
      NULL,
      type,
      criteria);
    if (ports == NULL) {
      LOGF << "No ports found matching " << std::to_string(criteria);
      jack_client_close(info->client);
      exit(1);
    }
    return ports;
  };

  // Helper function for connections
  auto connectPort = [&](const char *src_name, const char *dest_name) {
    if (jack_connect(info->client, dest_name, src_name)) {
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

  for (uint i = 0; i < info->nIn; i++) {
    connectPort(jack_port_name(info->ports.in[i]), inputs[i % ninputs]);
  }
  for (uint i = 0; i < info->nOut; i++) {
    connectPort(outputs[i % noutputs], jack_port_name(info->ports.out[i]));
  }

  LOGI << "Connected ports, enabling canProcess";

  info->doProcess = 1;
}

int init (int argc, char *argv[]) {
  ThreadInfo info;
  memset(&info, 0, sizeof(info));

  client = jack_client_open(CLIENT_NAME, JackNullOption, &info.jackStatus);
  info.client = client;

  events.preInit(&info);

  if (!(info.jackStatus & JackServerStarted)) {
    LOGF << "JACK server not running";
    exit(1);
  }

  LOGI << "JACK server started";
  LOGD << "JACK client status: " << info.jackStatus;

  info.doProcess = 0;

  jack_set_process_callback(client, process, &info);
  jack_set_sample_rate_callback(client, srateCallback, &info);

  if (jack_activate(client)) LOGF << "Cannot activate JACK client";
  jack_activate(client);

  setupPorts(&info);

  events.postInit(&info);

  while (1)
    sleep(10);

  events.preExit(&info);

  jack_client_close(client);

  events.postExit(&info);

  exit(0);
}
}
}
