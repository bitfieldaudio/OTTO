#pragma once

#include <atomic>
#include <string>
#include <vector>

#include <jack/jack.h>
#include <jack/midiport.h>
#include "core/audio/midi.hpp"
#include "util/locked.hpp"

#include "util/locked.hpp"

namespace otto::service::audio {
  struct JackAudioDriver {
    static JackAudioDriver& get() noexcept;

    void init();
    void shutdown();

    std::atomic_int samplerate;

    void send_midi_event(core::midi::AnyMidiEvent) noexcept;

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

    util::atomic_swap<std::vector<core::midi::AnyMidiEvent>> midi_bufs;

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
    void new_port_callback(jack_port_id_t id);
    void gatherMidiInput(int nFrames);
    void process(int nframes);

    /// Jack cannot connect to a port from the notification thread, so we just add them here, and process them from the main one instead.
    std::vector<jack_port_id_t> new_ports;
  };

  using AudioDriver = JackAudioDriver;
} // otto::audio
