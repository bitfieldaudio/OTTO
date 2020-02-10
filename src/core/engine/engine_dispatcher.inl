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
      send_presets_for(name);
    }
    props.selected_engine_idx.on_change().connect([this](int idx) {
      save_engine_state();
      engine_is_constructed_ = false;
      services::AudioManager::current().wait_one();
      current_engine_.emplace_by_index(idx);
      engine_states_[current_engine_->name()].map([&](auto&& j) { current_engine_->from_json(j); });
      engine_is_constructed_ = true;
      update_max_preset_idx();
    });
    props.selected_preset_idx.on_change().connect([this](int idx) {
      if (idx == 0) {
        engine_states_[current_engine_->name()].map([&](auto&& json) { current_engine_->from_json(json); });
      } else {
        services::PresetManager::current().apply_preset(*current_engine_, idx - 1);
      }
    });
    update_max_preset_idx();
  }

  ENGDISPTEMPLATE
  void ENGDISP::send_presets_for(util::string_ref engine_name)
  {
    auto presets = std::vector<std::string>{"Last State"};
    nano::copy(services::PresetManager::current().preset_names(engine_name), nano::back_inserter(presets));
    props.sender.push(Actions::publish_engine_data::data({
      .name = engine_name,
      .icon = ui::Icon(placeholder_engine_icon),
      .presets = presets,
    }));
  }

  ENGDISPTEMPLATE
  void ENGDISP::update_max_preset_idx()
  {
    OTTO_ASSERT(engine_is_constructed_.load());
    props.selected_preset_idx.max = services::PresetManager::current().preset_names(current_engine_->name()).size();
  }


  ENGDISPTEMPLATE
  void ENGDISP::save_engine_state()
  {
    OTTO_ASSERT(engine_is_constructed_.load());
    engine_states_.insert_or_assign(std::string(current_engine_->name()), current_engine_->to_json());
  }

  ENGDISPTEMPLATE
  void ENGDISP::action(Actions::make_new_preset, std::string name)
  {
    services::PresetManager::current().create_preset(current_engine_->name(), name, current_engine_->to_json());
    send_presets_for(current_engine_->name());
    update_max_preset_idx();
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
    } else  if constexpr (ET == EngineType::synth){
      auto buf = services::AudioManager::current().buffer_pool().allocate_clear();
      return data.with(buf);
    } else {
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

  ENGDISPTEMPLATE
  nlohmann::json ENGDISP::to_json() const
  {
    auto states = engine_states_;
    if (engine_is_constructed_) {
      states.insert_or_assign(std::string(current_engine_->name()), current_engine_->to_json());
    }
    return {
      {"selected", current_engine_->name()},
      {"states", util::serialize(states)},
    };
  }
  ENGDISPTEMPLATE
  void ENGDISP::from_json(const nlohmann::json& j)
  {
    util::deserialize(engine_states_, j.at("states"));
    auto idx = nano::find(engine_names, j.at("selected")) - engine_names.begin();
    props.selected_engine_idx = idx;
  }

  // Free functions to actually integrate with nlohmann::json

  ENGDISPTEMPLATE
  void to_json(nlohmann::json& j, const ENGDISP& e)
  {
    j = e.to_json();
  }
  ENGDISPTEMPLATE
  void from_json(const nlohmann::json& j, ENGDISP& e)
  {
    e.from_json(j);
  }

#undef ENGDISPTEMPLATE
#undef ENGDISP

} // namespace otto::core::engine
