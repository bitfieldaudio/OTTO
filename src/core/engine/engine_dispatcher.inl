#pragma once
#include <thread>

#include "engine_dispatcher.hpp"
#include "services/audio_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/preset_manager.hpp"
#include "util/meta.hpp"
#include "util/string_conversions.hpp"

namespace otto::core::engine {

#define ENGDISPTEMPLATE template<EngineType ET, typename... Engines>
#define ENGDISP EngineDispatcher<ET, Engines...>

  ENGDISPTEMPLATE
  ENGDISP::EngineDispatcher() noexcept : screen_(std::make_unique<EngineSelectorScreen>())
  {
    props.sender.push(PublishEngineNames::action::data(engine_names));
    props.selected_engine_idx.on_change().connect([this](int idx) {
      engine_is_constructed_ = false;
      services::AudioManager::current().wait_one();
      current_engine_.emplace_by_index(idx);
      engine_is_constructed_ = true;
    });
  }

  ENGDISPTEMPLATE
  ITypedEngine<ET>& ENGDISP::current()
  {
    return *current_engine_;
  }

  ENGDISPTEMPLATE
  ITypedEngine<ET>* ENGDISP::operator->()
  {
    return &*current_engine_;
  }

  ENGDISPTEMPLATE
  template<int N>
  auto ENGDISP::process(audio::ProcessData<N> data) noexcept
  {
    if (engine_is_constructed_) {
      return util::match(current_engine_, [&](auto& engine) { return engine.audio->process(data); });
    }
    if constexpr (ET == EngineType::arpeggiator) {
      return data;
    } else if constexpr (ET == EngineType::effect) {
      auto buf = services::AudioManager::current().buffer_pool().allocate_multi_clear<2>();
      return data.with(buf);
    } else {
      util::fill(data.audio, 0);
      return data;
    }
  }

  ENGDISPTEMPLATE
  ui::ScreenAndInput ENGDISP::selector_screen() noexcept
  {
    return {*screen_, *this};
  }

  ENGDISPTEMPLATE
  ui::ScreenAndInput ENGDISP::engine_screen() noexcept
  {
    if (current().name() == "OFF") return selector_screen();
    return current().screen();
  }


  ENGDISPTEMPLATE
  void ENGDISP::encoder(input::EncoderEvent e)
  {
    using namespace input;
    switch (e.encoder) {
      case Encoder::blue:
        if (props.current_screen != 0)
          props.current_screen = 0;
        else
          props.selected_engine_idx.step(e.steps);
        break;
      case Encoder::green:
        if (props.current_screen != 1)
          props.current_screen = 1;
        else
          props.selected_preset_idx.step(e.steps);
        break;
      default: break;
    }
  }

  ENGDISPTEMPLATE
  bool ENGDISP::keypress(input::Key key)
  {
    using namespace input;
    switch (key) {
      case Key::blue_click: //
        props.current_screen = 1;
        return true;
      default: return false;
    }
  }


#undef ENGDISPTEMPLATE
#undef ENGDISP

} // namespace otto::core::engine
