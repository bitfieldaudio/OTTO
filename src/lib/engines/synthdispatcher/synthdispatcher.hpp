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


  struct SynthDispatcherLogic : ILogic, itc::Producer<SynthDispatcherState> {
    using Producer::Producer;

    SynthDispatcherLogic(itc::Context& ctx) : Producer(ctx), _ctx(ctx) {}

    void register_engine(SynthEngineFactory&& factory)
    {
      // First engine is set as default
      _factories.push_back(std::move(factory));
      if (_factories.size() == 1) {
        activate_engine(0);
        update_state();
      }
    }

    SynthEngineInstance& current()
    {
      return _active;
    }

    void toggle_engine()
    {
      wipe_state();
      sync();
      _active = SynthEngineInstance();
      activate_engine((_active_idx + 1) % _factories.size());
      update_state();
      commit();
    }

  private:
    void activate_engine(std::size_t idx)
    {
      if (idx < _factories.size()) {
        _active_idx = idx;
        _active = _factories[idx].make_all(_ctx);
      }
    }

    void wipe_state()
    {
      state().audio = nullptr;
      state().main_screen = {nullptr, nullptr};
      state().mod_screen = {nullptr, nullptr};
      state().voices_screen = {nullptr, nullptr};
    }

    void update_state()
    {
      state().audio = _active.audio.get();
      state().main_screen = ScreenWithHandlerPtr(_active.main_screen);
      state().mod_screen = ScreenWithHandlerPtr(_active.mod_screen);
      state().voices_screen = ScreenWithHandlerPtr(_active.voices_screen);
    }

    itc::Context& _ctx;
    std::vector<SynthEngineFactory> _factories;
    // TODO: Refactor this?
    // To make sure these don't come out of sync, we only allow activation through the index.
    SynthEngineInstance _active = {};
    std::size_t _active_idx;
  };

  inline std::unique_ptr<SynthDispatcherLogic> make_synthdispatcher_logic(itc::Context& c)
  {
    return std::make_unique<SynthDispatcherLogic>(c);
  }

  struct SynthDispatcher {
    std::unique_ptr<SynthDispatcherLogic> logic;
    std::unique_ptr<ISynthAudio> audio;
    ScreenWithHandler main_screen;
    ScreenWithHandler mod_screen;
    ScreenWithHandler voices_screen;
  };

  inline SynthDispatcher make_synthdispatcher(itc::Context& c)
  {
    return {
      .logic = make_synthdispatcher_logic(c),
      .audio = make_synthdispatcher_audio(c),
      .main_screen = make_synthdispatcher_main_screen(c),
      .mod_screen = make_synthdispatcher_mod_screen(c),
      .voices_screen = make_synthdispatcher_voices_screen(c),
    };
  }


} // namespace otto