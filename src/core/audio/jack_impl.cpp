#include <string>
#include <atomic>
#include <vector>

#include <jack/jack.h>
#include <jack/midiport.h>
#include <fmt/format.h>
#include <plog/Log.h>

#include "core/globals.hpp"
#include "util/event.hpp"
#include "util/timer.hpp"

#include "core/audio/processor.hpp"
#include "core/audio/main_audio.hpp"

namespace otto::audio {

  static void jackError(const char* s) {
    LOGE << "JACK: " << s;
  }

  static void jackLogInfo(const char* s) {
    LOGI << "JACK: " << s;
  }

  void shutdown(void* arg) {
    LOGI << "JACK shut down, exiting";
  }

  class MainAudio::Impl {
  public:

    using AudioSample = jack_default_audio_sample_t;
    const size_t sampleSize = sizeof(AudioSample);
    const std::string clientName = "OTTO";

    MainAudio& owner;

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

    Impl(MainAudio& owner)
      : owner (owner)
    {
      jack_set_error_function(jackError);
      jack_set_info_function(jackLogInfo);

      client = jack_client_open(clientName.c_str(), JackNullOption, &jackStatus);

      if ((!jackStatus) & JackServerStarted) {
        throw global::exception(global::ErrorCode::audio_error,
          "Failed to start jack server");
      }

      LOGI << "Jack server started";
      LOGD << "Jack client status: " << jackStatus;

      jack_set_process_callback(client,
        [](jack_nframes_t nframes, void* arg) {
          (static_cast<Impl*>(arg))->process(nframes);
          return 0;
        }, this);

      jack_set_sample_rate_callback(client,
        [](jack_nframes_t nframes, void* arg) {
          (static_cast<Impl*>(arg))->samplerateCallback(nframes);
          return 0;
        }, this);

      jack_set_buffer_size_callback(client,
        [](jack_nframes_t nframes, void* arg) {
          (static_cast<Impl*>(arg))->buffersizeCallback(nframes);
          return 0;
        }, this);

      jack_on_shutdown(client, shutdown, nullptr);

      bufferSize = jack_get_buffer_size(client);

      if (jack_activate(client)) {
        throw global::exception(global::ErrorCode::audio_error,
          "Cannot activate jack client");
      }

      setupPorts();

      LOGI << "Initialized JackAudio";
    }

    ~Impl()
    {
      LOGI << "Closing Jack client";
      jack_client_close(client);
      global::exit(global::ErrorCode::none);
    };

    void setupPorts()
    {
      // Audio ports
      ports.input = jack_port_register(
        client, "input", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

      if (ports.input == NULL) {
        throw global::exception(global::ErrorCode::audio_error,
          "Couldn't register input port");
      }

      ports.outL = jack_port_register(
        client, "outLeft", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
      ports.outR = jack_port_register(
        client, "outRight", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

      auto inputs  = findPorts(JackPortIsPhysical | JackPortIsOutput);
      auto outputs = findPorts(JackPortIsPhysical | JackPortIsInput);

      if (inputs.empty()) {
        throw global::exception(global::ErrorCode::audio_error,
          "Couldn't find physical input port");
      }
      if (outputs.empty()) {
        throw global::exception(global::ErrorCode::audio_error,
          "Couldn't find physical output ports");
      }

      bool s;

      s = connectPorts(jack_port_name(ports.input), inputs[0]);
      if (!s) {global::exit(global::ErrorCode::audio_error); return;}

      s = connectPorts(outputs[0 % outputs.size()], jack_port_name(ports.outL));
      if (!s) {global::exit(global::ErrorCode::audio_error); return;}

      s = connectPorts(outputs[1 % outputs.size()], jack_port_name(ports.outR));
      if (!s) {global::exit(global::ErrorCode::audio_error); return;}


      // Midi ports
      ports.midiIn = jack_port_register(
        client, "midiIn", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);

      if (ports.midiIn == NULL) {
        throw global::exception(global::ErrorCode::audio_error,
          "Couldn't register midi_in port");
      }

      ports.midiOut = jack_port_register(
        client, "midiOut", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

      auto midiIn  = findPorts(JackPortIsPhysical | JackPortIsOutput, PortType::Midi);
      auto midiOut = findPorts(JackPortIsPhysical | JackPortIsInput, PortType::Midi);

      if (midiIn.empty()) {
        LOGE << "Couldn't find physical midi input port";
        return;
      }
      if (midiOut.empty()) {
        LOGE << "Couldn't find physical midi output port";
        return;
      }

      s = connectPorts(jack_port_name(ports.midiIn), midiIn[0]);
      LOGE_IF(!s) << "Couldn't connect midi input";

      s = connectPorts(midiOut[0], jack_port_name(ports.midiOut));
      LOGE_IF(!s) << "Couldn't connect midi output";
    }

    std::vector<std::string> findPorts(int criteria, PortType type = PortType::Audio)
    {
      const char **ports = jack_get_ports(client, nullptr,
        (type == PortType::Audio) ? "audio" : "midi", criteria);
      std::vector<std::string> ret;
      if (ports == nullptr) return ret;
      for (int i = 0; ports[i] != nullptr; i++) {
        ret.emplace_back(ports[i]);
      }
      jack_free(ports);
      return ret;
    };

    // Helper function for connections
    bool connectPorts(const std::string& src, const std::string& dest)
    {
      return !jack_connect(client, dest.c_str(), src.c_str());
    }

    void samplerateCallback(unsigned srate)
    {
      LOGI << fmt::format("Jack changed the sample rate to {}", srate);
      global::audio.samplerate = srate;
      global::event::samplerate_change.runAll(srate);
    }

    void buffersizeCallback(unsigned buffsize)
    {
      LOGI << fmt::format("Jack changed the buffer size to {}", buffsize);
      bufferSize = buffsize;
      global::event::buffersize_change.runAll(buffsize);
    }

    void process(unsigned nframes)
    {
      if (!(owner.do_process && global::running())) return;

      static auto timer = util::timer::find_or_make("JackAudio::Process");
      util::timer::tick(timer);

      if (nframes > bufferSize) {
        LOGE << "Jack requested more frames than expected";
        return;
      }

      midi_buf.clear();

      // Get new midi events
      void *midiBuf = jack_port_get_buffer(ports.midiIn, nframes);
      int nevents = jack_midi_get_event_count(midiBuf);

      jack_midi_event_t event;
      for (int i = 0; i < nevents; i++) {
        using namespace midi;

        jack_midi_event_get(&event, midiBuf, i);
        midi::MidiEvent mEvent;

        mEvent.channel = event.buffer[0] & 0b00001111;
        mEvent.data = event.buffer + 1;
        mEvent.time = event.time;

        auto type = MidiEvent::Type(event.buffer[0] >> 4);
        switch (type) {
        case MidiEvent::Type::NoteOff:
          mEvent.type = MidiEvent::Type::NoteOff;
          midi_buf.emplace_back(NoteOffEvent(mEvent));
          break;
        case MidiEvent::Type::NoteOn:
          mEvent.type = MidiEvent::Type::NoteOn;
          midi_buf.emplace_back(NoteOnEvent(mEvent));
          break;
        case MidiEvent::Type::ControlChange:
          mEvent.type = MidiEvent::Type::ControlChange;
          midi_buf.emplace_back(ControlChangeEvent(mEvent));
          break;
        }
      }

      float* outLData = (float*) jack_port_get_buffer(ports.outL, nframes);
      float* outRData = (float*) jack_port_get_buffer(ports.outR, nframes);
      float* inData = (float*) jack_port_get_buffer(ports.input, nframes);

      auto out_data = owner.process({
          {reinterpret_cast<util::audio::AudioFrame<1>*>(inData), nframes},
          {midi_buf},
            nframes});

      LOGW_IF(out_data.nframes != nframes) << "Frames went missing!";

      // Separate channels
      for (int i = 0; i < nframes; i++)
      {
        outLData[i] = out_data.audio[i][0];
        outRData[i] = out_data.audio[i][1];
      }
    }

  };


  /*
   * MainAudio members
   */

  MainAudio::MainAudio() {}
  MainAudio::~MainAudio() {}

  void MainAudio::init() {
    impl = std::make_unique<Impl>(*this);
  }

  void MainAudio::exit() {
    impl.reset();
  }


} // otto::audio
