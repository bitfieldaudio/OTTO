#pragma once

#include <functional>
#include <memory>

#include "lib/audio.hpp"
#include "lib/engine.hpp"
#include "lib/itc/itc.hpp"
#include "lib/midi.hpp"

#include "app/domains/audio.hpp"

#include "state.hpp"

namespace otto {

  struct ProxyMidiHandler final : AudioDomain,
                                  itc::Consumer<SynthDispatcherState>,
                                  EventHandlerProxy<ProxyMidiHandler,
                                                    midi::NoteOn,
                                                    midi::NoteOff,
                                                    midi::Aftertouch,
                                                    midi::PolyAftertouch,
                                                    midi::PitchBend>,
                                  midi::IMidiHandler {
    using Consumer::Consumer;
    using EventHandlerProxy::handle;

    midi::IMidiHandler& proxy_target()
    {
      if (auto audio = state().audio; audio != nullptr) {
        return audio->midi_handler();
      } else {
        return empty_target_;
      }
    }

  private:
    midi::MidiHandler empty_target_ = {};
  };

  struct SynthDispatcherAudio : AudioDomain, itc::Consumer<SynthDispatcherState>, ISynthAudio {
    using Consumer::Consumer;

    SynthDispatcherAudio(itc::Context& c) : Consumer(c), midi_handler_(ProxyMidiHandler(c)) {}

    midi::IMidiHandler& midi_handler() noexcept override
    {
      return midi_handler_;
    }

    util::audio_buffer process() noexcept override
    {
      if (auto audio = state().audio; audio != nullptr) {
        return audio->process();
      } else {
        return buffer_pool().allocate();
      }
    }

  private:
    ProxyMidiHandler midi_handler_;
  };

  inline std::unique_ptr<ISynthAudio> make_synthdispatcher_audio(itc::Context& c)
  {
    return std::make_unique<SynthDispatcherAudio>(c);
  }

} // namespace otto