#include "sequencer.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/cache.hpp"
#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "services/log_manager.hpp"
#include "services/state_manager.hpp"
#include "services/audio_manager.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  using Channel = Sequencer::Channel;

  struct SequencerScreen : EngineScreen<Sequencer> {
    using EngineScreen<Sequencer>::EngineScreen;

    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;
  };

  Sequencer::Sequencer() : MiscEngine<Sequencer>(std::make_unique<SequencerScreen>(this))
  {}

  std::pair<bool, int> get_sequencer_number(int key)
  {
    DLOGI("Raw key: {}", key);
    int octave_pos = (key + 7) % 12;
    std::array<std::pair<bool, int>, 12> octave = {{{true, 0},
                                                    {false, 0},
                                                    {true, 1},
                                                    {false, 1},
                                                    {true, 2},
                                                    {true, 3},
                                                    {false, 2},
                                                    {true, 4},
                                                    {false, 3},
                                                    {true, 5},
                                                    {false, 4},
                                                    {true, 6}}};
    bool is_white = octave[octave_pos].first;
    if (is_white)
      return {true, octave[octave_pos].second + (key / 12) * 7};
    else
      return {false, octave[octave_pos].second + (key / 12) * 5};
  }

  audio::ProcessData<1> Sequencer::process(audio::ProcessData<0> data)
  {
    for (auto& event : data.midi) {
      util::match(event,
                  [&](midi::NoteOnEvent& ev) {
                    auto key = get_sequencer_number((int) ev.key);
                    if (key.first) {
                      int step = (key.second - 21) % 16;
                      DLOGI("White key: step {}", step);
                      channels[current_channel].triggers[step] =
                        !channels[current_channel].triggers[step];
                    } else {
                      current_channel = (key.second - 16) % 16;
                      DLOGI("Changing channel: {}", current_channel);
                    }
                  },
                  [](auto&&) {});
    }

    if (_running) _next_beat = _samples_per_beat - _counter;


    if (_next_beat <= data.nframes) {
      _beat++;
      for (auto& chan : channels) {
        if (chan.triggers[_beat]) {
          // Reset and trigger appropriate samples
          chan.sampler.restart();
        }
      }
    }

    auto buf = Application::current().audio_manager->buffer_pool().allocate();
    for (auto&& frm : buf) {
      for (auto& chan : channels) {
        frm += chan.sampler();
      }
    }

    _counter += data.nframes;
    _counter %= _samples_per_beat;

    return data.redirect(buf);
  }

  bool SequencerScreen::keypress(ui::Key key)
  {
    switch (key) {
    case ui::Key::play: {
      engine._running = !engine._running;
      engine._beat = 0;
      engine._next_beat = engine._samples_per_beat;
      engine._counter = engine._samples_per_beat;
      break;
    }
    default: return false; ;
    }
    return true;
  }

  void SequencerScreen::rotary(ui::RotaryEvent ev)
  {
    switch (ev.rotary) {
    case Rotary::blue: [[fallthrough]];
    case Rotary::green: [[fallthrough]];
    case Rotary::yellow: [[fallthrough]];
    case Rotary::red: break;
    }
  }

  void SequencerScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    int pad = 10;

    int x_sp = (width - 2 * pad) / 16;
    int y_sp = (height - 2 * pad) / engine.number_of_channels;

    for (int i = 0; i < engine.number_of_channels; i++) {
      for (int j = 0; j < 16; j++) {
        int x = pad + j * x_sp;
        int y = pad + i * y_sp;
        ctx.beginPath();
        ctx.circle(x, y, 5);
        if (engine.channels[i].triggers[j] && engine.current_channel != i)
          ctx.fill(Colours::Pink);
        else if (engine.channels[i].triggers[j] && engine.current_channel == i)
          ctx.fill(Colours::Blue);
        else if (!engine.channels[i].triggers[j] && engine.current_channel == i)
          ctx.fill(Colours::Gray70);
        else
          ctx.fill(Colours::Gray50);
      }
    }
  }
} // namespace otto::engines
