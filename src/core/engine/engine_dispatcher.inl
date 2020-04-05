#pragma once
#include <thread>

#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/nvg/util.hpp"
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
      send_data_for(name);
    }
    props.selected_engine_idx.observe(this, [this](int idx) {
      save_engine_state();
      engine_is_constructed_ = false;
      services::AudioManager::current().wait_one();
      current_engine_.emplace_by_index(idx);
      engine_states_[current_engine_->name()].map([&](auto&& j) { current_engine_->from_json(j); });
      engine_is_constructed_ = true;
      update_max_preset_idx();
    });
    props.selected_preset_idx.observe(this, [this](int idx) {
      if (idx == 0) {
        engine_states_[current_engine_->name()].map([&](auto&& json) { current_engine_->from_json(json); });
      } else {
        services::PresetManager::current().apply_preset(*current_engine_, idx - 1);
      }
    });
    update_max_preset_idx();
  }

  ENGDISPTEMPLATE
  void ENGDISP::send_data_for(util::string_ref engine_name)
  {
    auto presets = std::vector<std::string>{"Last State"};
    nano::copy(services::PresetManager::current().preset_names(engine_name), nano::back_inserter(presets));
    props.sender.push(Actions::publish_engine_data::data({
      .name = engine_name,
      .icon = ui::Icon(icon_register(engine_name)),
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
    send_data_for(current_engine_->name());
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
    } else if constexpr (ET == EngineType::synth) {
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

  ENGDISPTEMPLATE
  ui::Icon::IconDrawer ENGDISP::icon_register(util::string_ref engine_name)
  {
    if (engine_name == "OFF") {
      return [](ui::IconData& i, nvg::Canvas& ctx) {
        ctx.beginPath();
        ctx.circle(i.size.center(), i.size.min() / 4.f);
        ctx.fill(i.color);
      };
    }
    if (engine_name == "OTTO.FM") {
      return [](ui::IconData& i, nvg::Canvas& ctx) {
        ctx.beginPath();
        ctx.roundedRect({0, 0}, {i.size.w * 0.4f, i.size.h * 0.4f}, i.size.min() / 8.f);
        ctx.roundedRect({i.size.w, i.size.h}, {-i.size.w * 0.4f, -i.size.h * 0.4f}, i.size.min() / 8.f);
        ctx.fill(i.color);
        ctx.stroke(i.color, i.line_width);
        ctx.beginPath();
        ctx.lineJoin(ui::vg::LineJoin::ROUND);
        ctx.moveTo(i.size.w * 0.2f, i.size.h * 0.2f);
        ctx.lineTo(i.size.w * 0.8f, i.size.h * 0.2f);
        ctx.lineTo(i.size.w * 0.8f, i.size.h * 0.8f);
        ctx.stroke(i.color, i.line_width);
      };
    }
    if (engine_name == "Goss") {
      return [](ui::IconData& i, nvg::Canvas& ctx) {
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.lineTo(0, i.size.h * 0.5);
        ctx.moveTo(i.size.h * 0.33, 0);
        ctx.lineTo(i.size.h * 0.33, i.size.h * 0.9);
        ctx.moveTo(i.size.h * 0.66, 0);
        ctx.lineTo(i.size.h * 0.66, i.size.h * 0.3);
        ctx.moveTo(i.size.h, 0);
        ctx.lineTo(i.size.h, i.size.h * 0.6);
        ctx.stroke(i.color, i.line_width);
      };
    }
    if (engine_name == "Chorus") {
      return [](ui::IconData& i, nvg::Canvas& ctx) {
        ctx.beginPath();
        ctx.translate({-5, 12});
        ctx.scaleTowards(0.33, {i.size.w / 2.f, i.size.h});
        ctx.moveTo(0, 0);
        ctx.lineTo(0, -173.0 + 153.6);
        ctx.bezierCurveTo(121.4 - 130.8, -173.0 + 148.5, 115.0 - 130.8, -173.0 + 138.6, 115.0 - 130.8, -173.0 + 127.1);
        ctx.lineTo(115.0 - 130.8, -173.0 + 107.3);
        ctx.bezierCurveTo(115.0 - 130.8, -173.0 + 85.1, 133.0 - 130.8, -173.0 + 67.0, 155.2 - 130.8, -173.0 + 67.0);
        ctx.bezierCurveTo(177.4 - 130.8, -173.0 + 67.0, 195.5 - 130.8, -173.0 + 85.1, 195.5 - 130.8, -173.0 + 107.3);
        ctx.lineTo(195.5 - 130.8, -173.0 + 117.8);
        ctx.lineTo(204.4 - 130.8, -173.0 + 130.0);
        ctx.bezierCurveTo(205.4 - 130.8, -173.0 + 131.4, 205.1 - 130.8, -173.0 + 133.4, 203.7 - 130.8, -173.0 + 134.4);
        ctx.bezierCurveTo(203.2 - 130.8, -173.0 + 134.8, 202.5 - 130.8, -173.0 + 135.0, 201.8 - 130.8, -173.0 + 135.0);
        ctx.lineTo(195.5 - 130.8, -173.0 + 135.0);
        ctx.lineTo(195.5 - 130.8, -173.0 + 152.4);
        ctx.bezierCurveTo(195.5 - 130.8, -173.0 + 155.1, 193.3 - 130.8, -173.0 + 157.2, 190.7 - 130.8, -173.0 + 157.2);
        ctx.lineTo(179.7 - 130.8, -173.0 + 157.2);
        ctx.lineTo(179.7 - 130.8, -173.0 + 173.0);
        ctx.stroke(i.color, i.line_width * 3);
      };
    }
    if (engine_name == "Wormhole") {
      return [](ui::IconData& i, nvg::Canvas& ctx) {
        ctx.beginPath();
        ctx.moveTo({0, 0});
        ctx.bezierCurveTo(0, 0, 2.f * i.size.w / 6.f, i.size.h / 3.f, 3.f * i.size.w / 6.f, i.size.h / 3.f);
        ctx.bezierCurveTo(4.f * i.size.w / 6.f, i.size.w / 3.f, i.size.w, 0, i.size.w, 0);
        ctx.lineTo(i.size.w, i.size.h);
        ctx.bezierCurveTo(i.size.w, i.size.h, 4.f * i.size.w / 6.f, 2.f * i.size.h / 3.f, 3.f * i.size.w / 6.f,
                          2.f * i.size.h / 3.f);
        ctx.bezierCurveTo(2.f * i.size.w / 6.f, 2.f * i.size.w / 3.f, 0, i.size.h, 0, i.size.h);
        ctx.closePath();
        ctx.stroke(i.color, i.line_width);
      };
    }
    // Default icon
    return [](ui::IconData& i, nvg::Canvas& ctx) {
      ctx.beginPath();
      ctx.roundedRect({0, 0}, i.size, i.size.min() / 4.f);
      ctx.stroke(i.color, i.line_width);
      ctx.beginPath();
      ctx.circle(i.size.center(), i.size.min() / 4.f);
      ctx.fill(i.color);
    };
  }

#undef ENGDISPTEMPLATE
#undef ENGDISP

} // namespace otto::core::engine
