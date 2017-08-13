#pragma once

#include "util/typedefs.hpp"

#include <string>
#include <atomic>
#include <string>

#include <jack/jack.h>

#include "core/events.h"

class JackAudio {
private:
  struct {
    jack_port_t *outL;
    jack_port_t *outR;
    jack_port_t *input;
    jack_port_t *midiIn;
    jack_port_t *midiOut;
  } ports;

  jack_client_t *client;
  jack_status_t jackStatus;

  std::atomic_bool isProcessing = {false};

  enum class PortType {
    Audio,
    Midi
  };

  void setupPorts();

  std::vector<std::string> findPorts(
    int criteria, PortType type = PortType::Audio);

  bool connectPorts(std::string src, std::string dest);

  // Callbacks
  void process(uint nframes);
  void shutdownCallback();
  void samplerateCallback(uint nframes);
  void buffersizeCallback(uint nframes);
public:

  uint bufferSize;
  using AudioSample = jack_default_audio_sample_t;
  const size_t SAMPLE_SIZE = sizeof(AudioSample);
  const std::string CLIENT_NAME = "TOP-1";

  JackAudio() {}

  void init();
  void startProcess();
  void exit();

};
