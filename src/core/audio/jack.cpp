#include "jack.hpp"

#include <cstdlib>
#include <string>
#include <vector>

#include <jack/jack.h>
#include <jack/midiport.h>
#include <fmt/format.h>
#include <plog/Log.h>

#include "core/globals.hpp"
#include "util/event.hpp"
#include "util/timer.hpp"

namespace top1::audio {

  static void jackError(const char* s) {
    LOGE << "JACK: " << s;
  }

  static void jackLogInfo(const char* s) {
    LOGI << "JACK: " << s;
  }

  void JackAudio::init() {
    client = jack_client_open(clientName.c_str(), JackNullOption, &jackStatus);

    if ((!jackStatus) & JackServerStarted) {
      LOGF << "Failed to start jack server";
      Globals::exit();
      return;
    }

    LOGI << "Jack server started";
    LOGD << "Jack client status: " << jackStatus;

    jack_set_process_callback(client,
      [](jack_nframes_t nframes, void *arg) {
        ((JackAudio*)arg)->process(nframes);
        return 0;
      }, this);

    jack_set_sample_rate_callback(client,
      [](jack_nframes_t nframes, void *arg) {
        ((JackAudio*)arg)->samplerateCallback(nframes);
        return 0;
      }, this);

    jack_set_buffer_size_callback(client,
      [](jack_nframes_t nframes, void *arg) {
        ((JackAudio*)arg)->buffersizeCallback(nframes);
        return 0;
      }, this);

    jack_set_error_function(jackError);
    jack_set_info_function(jackLogInfo);

    jack_on_shutdown(client,
      [] (void *arg) {
        ((JackAudio*) arg)->exit();
      }, this);

    bufferSize = jack_get_buffer_size(client);

    if (jack_activate(client)) {
      LOGF << "Cannot activate JACK client";
      Globals::exit();
      return;
    }

    setupPorts();

    LOGI << "Initialized JackAudio";
  }

  void JackAudio::startProcess() {
    isProcessing = true;
  }

  void JackAudio::exit() {
    LOGI << "Closing Jack client";
    jack_client_close(client);
    Globals::exit();
  }

  void JackAudio::samplerateCallback(uint srate) {
    LOGI << fmt::format("Jack changed the sample rate to {}", srate);
    Globals::samplerate = srate;
    Globals::events.samplerateChanged.runAll(srate);
  }

  void JackAudio::buffersizeCallback(uint buffsize) {
    LOGI << fmt::format("Jack changed the buffer size to {}", buffsize);
    bufferSize = buffsize;
    Globals::events.bufferSizeChanged.runAll(buffsize);
  }

  void JackAudio::setupPorts() {

    // Audio ports
    ports.input = jack_port_register(
      client, "input", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

    if (ports.input == NULL) {
      LOGF << "Couldn't register input port";
      Globals::exit();
      return;
    }

    ports.outL = jack_port_register(
      client, "outLeft", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    ports.outR = jack_port_register(
      client, "outRight", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    auto inputs  = findPorts(JackPortIsPhysical | JackPortIsOutput);
    auto outputs = findPorts(JackPortIsPhysical | JackPortIsInput);

    if (inputs.empty()) {
      LOGF << "Couldn't find physical input port";
      Globals::exit();
      return;
    }
    if (outputs.empty()) {
      LOGF << "Couldn't find physical output ports";
      Globals::exit();
      return;
    }

    bool s;

    s = connectPorts(jack_port_name(ports.input), inputs[0]);
    if (!s) {Globals::exit(); return;}

    s = connectPorts(outputs[0 % outputs.size()], jack_port_name(ports.outL));
    if (!s) {Globals::exit(); return;}

    s = connectPorts(outputs[1 % outputs.size()], jack_port_name(ports.outR));
    if (!s) {Globals::exit(); return;}


    // Midi ports
    ports.midiIn = jack_port_register(
      client, "midiIn", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);

    if (ports.midiIn == NULL) {
      LOGF << "Couldn't register midi_in port";
      Globals::exit();
      return;
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

  std::vector<std::string> JackAudio::findPorts(int criteria, PortType type) {
    const char **ports = jack_get_ports(client, nullptr,
      (type == PortType::Audio) ? "audio" : "midi", criteria);
    std::vector<std::string> ret;
    if (ports == nullptr) return ret;
    for (int i = 0; ports[i] != nullptr; i++) {
      ret.emplace_back(ports[i]);
    }
    return ret;
  };

  // Helper function for connections
  bool JackAudio::connectPorts(std::string src, std::string dest) {
    return !jack_connect(client, dest.c_str(), src.c_str());
  }

  void shutdown(void *arg) {
    LOGI << "JACK shut down, exiting";
  }

  void JackAudio::process(uint nframes) {
    if (!(isProcessing && Globals::running())) return;

    static auto& timer = timer::dispatcher.timers["Audio Frame time"];
    if (timer.running) timer.stopTimer();
    timer.startTimer();

    if (nframes > bufferSize) {
      LOGE << "Jack requested more frames than expected";
      return;
    }

    // Clear the old data
    ProcessData processData;
    processData.nframes = nframes;
    procBuf.clear();

    float* outLData = (float*) jack_port_get_buffer(ports.outL, nframes);
    float* outRData = (float*) jack_port_get_buffer(ports.outR, nframes);
    float* inData = (float*) jack_port_get_buffer(ports.input, nframes);

    processData.audio.outL  = {outLData, nframes};
    processData.audio.outR  = {outRData, nframes};
    processData.audio.input = {inData, nframes};
    processData.audio.proc  = {procBuf.data(), nframes};

    // Get new midi events
    void *midiBuf = jack_port_get_buffer(ports.midiIn, nframes);
    uint nevents = jack_midi_get_event_count(midiBuf);

    jack_midi_event_t event;
    for (uint i = 0; i < nevents; i++) {
      using namespace midi;

      jack_midi_event_get(&event, midiBuf, i);
      midi::MidiEvent mEvent;

      mEvent.channel = event.buffer[0] & 0b00001111;
      mEvent.data = event.buffer + 1;
      mEvent.time = event.time;

      MidiEvent::byte type = event.buffer[0] >> 4;
      switch (type) {
      case MidiEvent::NOTE_OFF:
        mEvent.type = MidiEvent::NOTE_OFF;
        processData.midi.emplace_back(new NoteOffEvent(mEvent));
        break;
      case MidiEvent::NOTE_ON:
        mEvent.type = MidiEvent::NOTE_ON;
        processData.midi.emplace_back(new NoteOnEvent(mEvent));
        break;
      case MidiEvent::CONTROL_CHANGE:
        mEvent.type = MidiEvent::CONTROL_CHANGE;
        processData.midi.emplace_back(new ControlChangeEvent(mEvent));
        break;
      }
    }

    Globals::synth.process(processData);
    Globals::drums.process(processData);
    Globals::effect.process(processData);
    Globals::tapedeck.process(processData);
    Globals::mixer.process(processData);
    Globals::metronome.process(processData);

    // TODO: fix or replace poly_ptr so it works with smart pointers
    for (auto&& e : processData.midi) {
      delete e;
    }
  }

} // top1::audio
