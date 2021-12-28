#pragma once

#include <functional>
#include <memory>

#include "lib/audio.hpp"
#include "lib/engine.hpp"
#include "lib/engines/synthdispatcher/audio.hpp"
#include "lib/engines/synthdispatcher/screens.hpp"
#include "lib/engines/synthdispatcher/state.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/state/producer.hpp"
#include "lib/midi.hpp"

namespace otto {

  struct EngineMetaData {
    const std::string name;
  };

  struct SynthEngineInstance {
    std::unique_ptr<ILogic> logic;
    std::unique_ptr<ISynthAudio> audio;
    ScreenWithHandler main_screen;
    ScreenWithHandler mod_screen;
    ScreenWithHandler voices_screen;
  };


  struct SynthEngineFactory {
    const EngineMetaData _metadata;
    fu2::unique_function<std::unique_ptr<ILogic>(itc::Context&) const> make_logic;
    fu2::unique_function<std::unique_ptr<ISynthAudio>(itc::Context&) const> make_audio;
    fu2::unique_function<ScreenWithHandler(itc::Context&) const> make_mod_screen;
    fu2::unique_function<ScreenWithHandler(itc::Context&) const> make_main_screen;
    fu2::unique_function<ScreenWithHandler(itc::Context&) const> make_voices_screen;

    auto& metadata()
    {
      return _metadata;
    }

    SynthEngineInstance make_all(itc::Context& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = make_audio(chan),
        .main_screen = make_main_screen(chan),
        .mod_screen = make_mod_screen(chan),
        .voices_screen = make_voices_screen(chan),
      };
    }

    SynthEngineInstance make_without_audio(itc::Context& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = nullptr,
        .main_screen = make_main_screen(chan),
        .mod_screen = make_mod_screen(chan),
        .voices_screen = make_voices_screen(chan),
      };
    }

    SynthEngineInstance make_without_screens(itc::Context& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = make_audio(chan),
        .main_screen = {nullptr, nullptr},
        .mod_screen = {nullptr, nullptr},
        .voices_screen = {nullptr, nullptr},
      };
    }
  };

  struct SynthDispatcherLogic : ILogic, itc::Producer<SynthDispatcherState>, itc::Receiver<SynthDispatcherCommand> {
    using Producer::Producer;

    SynthDispatcherLogic(itc::Context& ctx) : Producer(ctx), Receiver(ctx) {}

    void register_engine(SynthEngineFactory&& factory)
    {
      // First engine is set as default
      _factories.push_back(std::move(factory));
      if (_factories.size() == 1) {
        activate_engine(0);
      }
    }

    SynthEngineInstance& current()
    {
      return _active;
    }

    void toggle_engine()
    {
      auto current_idx = state().active_engine;
      std::size_t new_idx = (current_idx + 1) % _factories.size();
      deactivate_engine();
      activate_engine(new_idx);
    }

    void receive(SynthDispatcherCommand cmd) noexcept override
    {
      if (cmd == SynthDispatcherCommand::toggle_engine) {
        toggle_engine();
      }
    }

  private:
    void deactivate_engine()
    {
      wipe_state();
      AudioDomain::get_static_executor()->sync();
      GraphicsDomain::get_static_executor()->sync();
      // Destructs the engine
      _active = SynthEngineInstance();
    }

    void activate_engine(std::size_t idx)
    {
      // Constructs the engine
      if (idx < _factories.size()) {
        _active = _factories[idx].make_all(Producer::context());
      }
      update_state(idx);
      AudioDomain::get_static_executor()->sync();
      GraphicsDomain::get_static_executor()->sync();
    }

    void wipe_state()
    {
      commit([&](auto& state) {
        state.audio = nullptr;
        state.main_screen = {nullptr, nullptr};
        state.mod_screen = {nullptr, nullptr};
        state.voices_screen = {nullptr, nullptr};
      });
    }

    void update_state(std::size_t idx)
    {
      commit([&](auto& state) {
        state.active_engine = idx;
        state.name = _factories[idx].metadata().name;
        state.audio = _active.audio.get();
        state.main_screen = ScreenWithHandlerPtr(_active.main_screen);
        state.mod_screen = ScreenWithHandlerPtr(_active.mod_screen);
        state.voices_screen = ScreenWithHandlerPtr(_active.voices_screen);
      });
    }

    std::vector<SynthEngineFactory> _factories;
    // TODO: Refactor this?
    // To make sure these don't come out of sync, we only allow activation through the index.
    SynthEngineInstance _active = {};
  };

  inline std::unique_ptr<SynthDispatcherLogic> make_synthdispatcher_logic(itc::Context& c)
  {
    return std::make_unique<SynthDispatcherLogic>(c);
  }

  // Handler //

  inline ScreenWithHandler make_synthdispatcher_selector_screen(itc::Context& c)
  {
    return make_with_internal_handler<DispatcherSelectorScreen>(c, key_groups::enc_clicks | key_groups::func);
  }

  struct SynthDispatcher {
    std::unique_ptr<SynthDispatcherLogic> logic;
    std::unique_ptr<ISynthAudio> audio;
    ScreenWithHandler main_screen;
    ScreenWithHandler mod_screen;
    ScreenWithHandler voices_screen;
    ScreenWithHandler selector_screen;
  };

  inline SynthDispatcher make_synthdispatcher(itc::Context& c)
  {
    return {.logic = make_synthdispatcher_logic(c),
            .audio = make_synthdispatcher_audio(c),
            .main_screen = make_synthdispatcher_main_screen(c),
            .mod_screen = make_synthdispatcher_mod_screen(c),
            .voices_screen = make_synthdispatcher_voices_screen(c),
            .selector_screen = make_synthdispatcher_selector_screen(c)};
  }


} // namespace otto
