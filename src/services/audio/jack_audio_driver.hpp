#pragma once

#include <atomic>
#include <string>
#include <vector>

#include <jack/jack.h>
#include <jack/midiport.h>
#include "core/audio/midi.hpp"

namespace otto::audio {
  struct JackAudioDriver {
    static JackAudioDriver& get() noexcept;

    void init();
    void shutdown();

    std::atomic_int samplerate;

  private:
    JackAudioDriver() noexcept = default;
    ~JackAudioDriver() noexcept = default;

    using AudioSample = jack_default_audio_sample_t;
    static constexpr const size_t sampleSize = sizeof(AudioSample);
    static constexpr const char* const clientName = "OTTO";

    struct {
      jack_port_t *outL;
      jack_port_t *outR;
      jack_port_t *input;
      jack_port_t *midiIn;
      jack_port_t *midiOut;
    } ports;

    std::size_t bufferSize;

    jack_client_t* client;
    jack_status_t jackStatus;

    std::vector<midi::AnyMidiEvent> midi_buf;

    enum class PortType {
      Audio,
      Midi
    };

    void setupPorts();
    std::vector<std::string> findPorts(int criteria, PortType type = PortType::Audio);

    // Helper function for connections
    bool connectPorts(const std::string& src, const std::string& dest);
    void samplerateCallback(unsigned srate);
    void buffersizeCallback(unsigned buffsize);
    void gatherMidiInput(int nFrames);
    void process(int nframes);
  };
} // otto::audio
