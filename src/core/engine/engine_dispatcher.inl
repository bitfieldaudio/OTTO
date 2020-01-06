#pragma once
#include <thread>

#include "engine_dispatcher.hpp"
#include "services/audio_manager.hpp"
#include "services/controller.hpp"
#include "services/engine_manager.hpp"
#include "services/preset_manager.hpp"
#include "util/meta.hpp"
#include "util/string_conversions.hpp"

namespace otto::core::engine {

#define ENGDISPTEMPLATE template<EngineType ET, typename... Engines>
#define ENGDISP EngineDispatcher<ET, Engines...>

  void placeholder_engine_icon(ui::IconData& i, nvg::Canvas& ctx);

  ENGDISPTEMPLATE
  ENGDISP::EngineDispatcher() noexcept
    : screen_(std::make_unique<EngineSelectorScreen>(services::ControllerSender(*this)))
  {
    for (auto name : engine_names) {
      auto presets = std::vector<std::string>{"Last State"};
      nano::copy(services::PresetManager::current().preset_names(name), nano::back_inserter(presets));
      props.sender.push(PublishEngineData::action::data({
        .name = name,
        .icon = ui::Icon(placeholder_engine_icon),
        .presets = presets,
      }));
    }
    props.selected_engine_idx.on_change().connect([this](int idx) {
      engine_is_constructed_ = false;
      services::AudioManager::current().wait_one();
      current_engine_.emplace_by_index(idx);
      engine_is_constructed_ = true;
      update_max_preset_idx();
    });
    props.selected_preset_idx.on_change().connect([this] (int idx) {
      services::PresetManager::current().apply_preset(*current_engine_, idx);
    });
    update_max_preset_idx();
  }

  ENGDISPTEMPLATE
  void ENGDISP::update_max_preset_idx()
  {
    OTTO_ASSERT(engine_is_constructed_.load());
    props.selected_preset_idx.max = services::PresetManager::current().preset_names(current_engine_->name()).size();
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
      nano::fill(data.audio, 0);
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
    props.sender.push(input::EncoderAction::data(e));
  }

  ENGDISPTEMPLATE
  bool ENGDISP::keypress(input::Key key)
  {
    props.sender.push(input::KeyPressAction::data(key));
    return false;
  }

#undef ENGDISPTEMPLATE
#undef ENGDISP

} // namespace otto::core::engine
