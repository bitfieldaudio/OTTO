#include "jack_audio_driver.hpp"

#include <string>
#include <vector>

#include <fmt/format.h>
#include <jack/jack.h>
#include <jack/midiport.h>

#include "core/globals.hpp"
#include "util/timer.hpp"

#include "services/engine_manager.hpp"
#include "services/audio_manager.hpp"
#include "core/audio/processor.hpp"
#include "services/logger.hpp"

namespace otto::audio {
  namespace {
    void jackError(const char* s)
    {
      LOG_F(ERROR, "JACK: {}", s);
    }

    void jackLogInfo(const char* s)
    {
      LOGI("JACK: {}", s);
    }

    void jackShutdown(void* arg)
    {
      LOGI("JACK shut down, exiting");
    }
  } // namespace

  JackAudioDriver& JackAudioDriver::get() noexcept
  {
    static JackAudioDriver instance {};
    return instance;
  }

  void JackAudioDriver::init()
  {
    jack_set_error_function(jackError);
    jack_set_info_function(jackLogInfo);

    client = jack_client_open(clientName, JackNullOption, &jackStatus);

    if ((!jackStatus) & JackServerStarted) {
      throw global::exception(global::ErrorCode::audio_error,
                              "Failed to start jack server");
    }

    LOG_F(INFO, "Jack server started");
    LOG_F(INFO, "Jack client status: {}", jackStatus);

    jack_set_process_callback(
      client,
      [](jack_nframes_t nframes, void* arg) {
        (static_cast<JackAudioDriver*>(arg))->process(nframes);
        return 0;
      },
      this);

    jack_set_sample_rate_callback(
      client,
      [](jack_nframes_t nframes, void* arg) {
        (static_cast<JackAudioDriver*>(arg))->samplerateCallback(nframes);
        return 0;
      },
      this);

    jack_set_buffer_size_callback(
      client,
      [](jack_nframes_t nframes, void* arg) {
        (static_cast<JackAudioDriver*>(arg))->buffersizeCallback(nframes);
        return 0;
      },
      this);

    jack_on_shutdown(client, jackShutdown, nullptr);

    bufferSize = jack_get_buffer_size(client);

    if (jack_activate(client)) {
      throw global::exception(global::ErrorCode::audio_error,
                              "Cannot activate jack client");
    }

    setupPorts();

    LOG_F(INFO, "Initialized JackAudio");
  }

  void JackAudioDriver::shutdown()
  {
    LOG_F(INFO, "Closing Jack client");
    jack_client_close(client);
  }

  void JackAudioDriver::setupPorts()
  {
    // Audio ports
    ports.input = jack_port_register(client, "input", JACK_DEFAULT_AUDIO_TYPE,
                                     JackPortIsInput, 0);

    if (ports.input == NULL) {
      throw global::exception(global::ErrorCode::audio_error,
                              "Couldn't register input port");
    }

    ports.outL = jack_port_register(client, "outLeft", JACK_DEFAULT_AUDIO_TYPE,
                                    JackPortIsOutput, 0);
    ports.outR = jack_port_register(client, "outRight", JACK_DEFAULT_AUDIO_TYPE,
                                    JackPortIsOutput, 0);

    auto inputs  = findPorts(JackPortIsPhysical | JackPortIsOutput);
    auto outputs = findPorts(JackPortIsPhysical | JackPortIsInput);

    if (outputs.empty()) {
      throw global::exception(global::ErrorCode::audio_error,
                              "Couldn't find physical output ports");
    }

    bool s;

    if (!inputs.empty()) {
      s = connectPorts(jack_port_name(ports.input), inputs[0]);
      if (!s) {
        global::exit(global::ErrorCode::audio_error);
        return;
      }
    }

    s = connectPorts(outputs[0 % outputs.size()], jack_port_name(ports.outL));
    if (!s) {
      global::exit(global::ErrorCode::audio_error);
      return;
    }

    s = connectPorts(outputs[1 % outputs.size()], jack_port_name(ports.outR));
    if (!s) {
      global::exit(global::ErrorCode::audio_error);
      return;
    }

    // Midi ports
    ports.midiIn = jack_port_register(client, "midiIn", JACK_DEFAULT_MIDI_TYPE,
                                      JackPortIsInput, 0);

    if (ports.midiIn == NULL) {
      throw global::exception(global::ErrorCode::audio_error,
                              "Couldn't register midi_in port");
    }

    ports.midiOut = jack_port_register(
      client, "midiOut", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

    auto midiIn =
      findPorts(JackPortIsPhysical | JackPortIsOutput, PortType::Midi);
    auto midiOut =
      findPorts(JackPortIsPhysical | JackPortIsInput, PortType::Midi);

    if (midiIn.empty()) {
      LOG_F(ERROR, "Couldn't find physical midi input port");
      return;
    }
    if (midiOut.empty()) {
      LOG_F(ERROR, "Couldn't find physical midi output port");
      return;
    }

    s = connectPorts(jack_port_name(ports.midiIn), midiIn[0]);
    LOG_IF_F(ERROR, !s, "Couldn't connect midi input");

    s = connectPorts(midiOut[0], jack_port_name(ports.midiOut));
    LOG_IF_F(ERROR, !s, "Couldn't connect midi output");
  }

  std::vector<std::string> JackAudioDriver::findPorts(int criteria,
                                                      PortType type)
  {
    const char** ports = jack_get_ports(
      client, nullptr, (type == PortType::Audio) ? "audio" : "midi", criteria);
    std::vector<std::string> ret;
    if (ports == nullptr) return ret;
    for (int i = 0; ports[i] != nullptr; i++) {
      ret.emplace_back(ports[i]);
    }
    jack_free(ports);
    return ret;
  }

  /// Helper function for connections
  bool JackAudioDriver::connectPorts(const std::string& src,
                                     const std::string& dest)
  {
    return !jack_connect(client, dest.c_str(), src.c_str());
  }

  void JackAudioDriver::samplerateCallback(unsigned srate)
  {
    LOG_F(INFO, "Jack changed the sample rate to {}", srate);
    samplerate = srate;
    audio::events::samplerate_change().fire(srate);
  }

  void JackAudioDriver::buffersizeCallback(unsigned buffsize)
  {
    LOG_F(INFO, "Jack changed the buffer size to {}", buffsize);
    bufferSize = buffsize;
    audio::events::buffersize_change().fire(buffsize);
  }

  void JackAudioDriver::gatherMidiInput(int nframes) {
    midi_buf.clear();

    // Get new midi events
    void* midiBuf = jack_port_get_buffer(ports.midiIn, nframes);
    int nevents   = jack_midi_get_event_count(midiBuf);

    jack_midi_event_t event;
    for (int i = 0; i < nevents; i++) {
      using namespace midi;

      jack_midi_event_get(&event, midiBuf, i);
      midi::MidiEvent mEvent;

      mEvent.channel = event.buffer[0] & 0b00001111;
      mEvent.data    = event.buffer + 1;
      mEvent.time    = event.time;

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
  }

  void JackAudioDriver::process(int nframes)
  {
    auto running = audio::running() && global::running();
    if (!running) {
      return;
    }

    TIME_SCOPE("JackAudio::Process");

    if ((size_t) nframes > bufferSize) {
      LOGE("Jack requested more frames than expected");
      return;
    }

    gatherMidiInput(nframes);

    float* outLData = (float*) jack_port_get_buffer(ports.outL, nframes);
    float* outRData = (float*) jack_port_get_buffer(ports.outR, nframes);
    float* inData   = (float*) jack_port_get_buffer(ports.input, nframes);

    auto out_data = engines::process(
      {{reinterpret_cast<util::audio::AudioFrame<1>*>(inData), nframes},
       {midi_buf},
       nframes});

    audio::process_audio_output(out_data);

    LOGW_IF(out_data.nframes != nframes, "Frames went missing!");

    // Separate channels
    for (int i = 0; i < nframes; i++) {
      outLData[i] = out_data.audio[i][0];
      outRData[i] = out_data.audio[i][1];
    }
  }
} // namespace otto::audio
