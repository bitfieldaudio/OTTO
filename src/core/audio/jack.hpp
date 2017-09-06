#pragma once

#include "util/typedefs.hpp"

#include <string>
#include <atomic>
#include <string>
#include <vector>

#include <jack/jack.h>

#include "core/audio/processor.hpp"

namespace top1::audio {

  class JackAudio {
    struct {
      jack_port_t *outL;
      jack_port_t *outR;
      jack_port_t *input;
      jack_port_t *midiIn;
      jack_port_t *midiOut;
    } ports;

    RTBuffer<float> procBuf;

    jack_client_t *client;
    jack_status_t jackStatus;

    std::atomic_bool isProcessing {false};

    enum class PortType {
      Audio,
      Midi
    };

    void setupPorts();

    std::vector<std::string> findPorts(int criteria,
      PortType type = PortType::Audio);

    bool connectPorts(std::string src, std::string dest);

    // Callbacks
    void process(uint nframes);
    void shutdownCallback();
    void samplerateCallback(uint nframes);
    void buffersizeCallback(uint nframes);
    public:

    uint bufferSize;
    using AudioSample = jack_default_audio_sample_t;
    const size_t sampleSize = sizeof(AudioSample);
    const std::string clientName = "TOP-1";

    JackAudio() {}

    void init();
    void startProcess();
    void exit();

  };

}
