#include "app/services/audio.hpp"
#include "arp.hpp"

namespace otto::engines::arp {
  struct Audio final : AudioDomain,
                       itc::Consumer<State>,
                       IMidiFXAudio,
                       core::ServiceAccessor<services::Audio> {
    Audio(itc::ChannelGroup& ch) : Consumer(ch) {}

    midi::IMidiHandler& midi_handler() noexcept override
    {
      return midi_handler_;
    }

    // A process function should return what?

    void on_state_change(const State& s) noexcept override
    {
    }

  private:
    midi::MidiHandler midi_handler_;
  };

  std::unique_ptr<IMidiFXAudio> make_audio(itc::ChannelGroup& chan)
  {
    return std::make_unique<Audio>(chan);
  }

}
  