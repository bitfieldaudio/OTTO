#pragma once

#include <cstdlib>
#include <string>
#include <atomic>

#include <jack/jack.h>
#include <string>

#include "../events.h"

class JackAudio {
  struct {
    jack_port_t *outL;
    jack_port_t *outR;
    jack_port_t *input;
    jack_port_t *midiIn;
    jack_port_t *midiOut;
  } ports;

  jack_client_t *client;
  jack_status_t jackStatus;

  std::atomic_bool processing = {false};
private:

  enum class PortType {
    AUDIO,
    MIDI
  };

  void setupPorts();

  std::vector<std::string> findPorts(
    int criteria, PortType type = PortType::AUDIO);

  bool connectPorts(std::string src, std::string dest);

  // Callbacks
  void process(uint nframes);
  void shutdownCallback();
  void samplerateCallback(uint nframes);
  void buffersizeCallback(uint nframes);
public:

  uint bufferSize;
  typedef jack_default_audio_sample_t AudioSample;
  const size_t SAMPLE_SIZE = sizeof(AudioSample);
  const std::string CLIENT_NAME = "TOP-1";

  JackAudio() {}

  void init();
  void startProcess();
  void exit();

};
