#include <string>
#include <atomic>
#include <vector>

#include <jack/jack.h>
#include <jack/midiport.h>
#include <fmt/format.h>

#include "core/globals.hpp"
#include "util/event.hpp"
#include "util/timer.hpp"

#include "core/audio/processor.hpp"

namespace otto::audio {
  struct JackAudioDriver {
    static JackAudioDriver& get();

    void init();
    void shutdown();

  private:
    JackAudioDriver() = default;
    ~JackAudioDriver() = default;

    using AudioSample = jack_default_audio_sample_t;
    const size_t sampleSize = sizeof(AudioSample);
    const std::string clientName = "OTTO";

    struct {
      jack_port_t *outL;
      jack_port_t *outR;
      jack_port_t *input;
      jack_port_t *midiIn;
      jack_port_t *midiOut;
    } ports;

    std::size_t bufferSize;

    jack_client_t *client;
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
    void process(int nframes);
  };
} // otto::audio
