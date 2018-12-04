#include "accord.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/cache.hpp"
#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "services/log_manager.hpp"
#include "services/state_manager.hpp"


#if false

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct AccordScreen : EngineScreen<Accord> {
    using EngineScreen<Accord>::EngineScreen;

    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    void draw_normal(Canvas& ctx);
    void draw_recording(Canvas& ctx);

    void refresh_state();

  };

  Accord::Accord() : SequencerEngine("Accord", props, std::make_unique<AccordScreen>(this))
  {

  }

  audio::ProcessData<0> Accord::process(audio::ProcessData<0> data)
  {
      if (auto recording = this->recording; recording) {
        //Create and select new hit if it doesn't exist
        if (!step_occupied(props.cur_step)){
            props.hits.push_back(Hit(cur_step, 1, {}));
            props.selected = props.hits.size() - 1,
        } else {

        }
        for (auto& event : data.midi) {
          util::match(event,
                      [&](midi::NoteOnEvent& ev) {
                        if (!_has_pressed_keys) {
                          util::fill(recording.value(), -1);
                          current.notes.set(recording.value());
                          _has_pressed_keys = true;
                        }
                        for (auto& note : recording.value()) {
                          if (note >= 0) continue;
                          note = ev.key;
                          break;
                        }
                        util::unique(recording.value(), std::equal_to<char>());
                        current.notes = recording.value();
                      },
                      [&](midi::NoteOffEvent& ev) {
                        for (auto& note : recording.value()) {
                          if (note != ev.key) continue;
                          note = -1;
                        }
                        if (util::all_of(recording.value(), [](int note) { return note < 0; })) {
                          recording = std::nullopt;
                        }
                      },
                      [](auto&&) {});
          this->recording = recording;
          if (!recording) break;
          ;
        }
      }
  }



  // SCREEN //
  bool AccordScreen::keypress(Key key)
  {
    switch (key) {
    case ui::Key::blue_click: [[fallthrough]];
    case ui::Key::green_click: [[fallthrough]];
    case ui::Key::white_click: [[fallthrough]];
    case ui::Key::red_click:
      if (engine.recording) {
        engine.recording = std::nullopt;
      } else {
        engine._has_pressed_keys = false;
        engine.recording = engine.props.hits.at().notes;
      }
      break;
    case ui::Key::play: engine._should_run = !engine._should_run; break;
    default: return false; ;
    }
  }

  void AccordScreen::rotary(ui::RotaryEvent ev)
  {
    if (engine.recording) return;

    switch (ev.rotary) {
    case Rotary::Blue: engine.props.cur_step.step(ev.clicks); break;
    case Rotary::Green: current.length.step(ev.clicks); break;
    case Rotary::White: current.hits.step(ev.clicks); break;
    case Rotary::Red: current.rotation.step(ev.clicks); break;
    }

  }

  bool AccordScreen::keypress(ui::Key key)
  {
    switch (key) {
    case ui::Key::blue_click: [[fallthrough]];
    case ui::Key::green_click: [[fallthrough]];
    case ui::Key::white_click: [[fallthrough]];
    case ui::Key::red_click:
      if (engine.recording) {
        engine.recording = std::nullopt;
      } else {
        engine._has_pressed_keys = false;
        engine.recording = engine.current_channel().notes;
      }
      break;
    case ui::Key::play: engine._should_run = !engine._should_run; break;
    default: return false; ;
    }
    return true;
  }

  void AccordScreen::draw(ui::vg::Canvas& ctx)
  {
    draw_normal(ctx);
    if (engine.recording)
      draw_recording(ctx);
  }

  void AccordScreen::draw_recording(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;


  }

  void AccordScreen::draw_normal(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;


  }

  void AccordScreen::refresh_state()
  {

  }

} // namespace otto::engines

#endif
