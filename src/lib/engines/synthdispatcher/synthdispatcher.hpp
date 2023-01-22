#pragma once

#include <functional>
#include <memory>

#include "lib/util/change_checker.hpp"
#include "lib/util/math.hpp"

#include "lib/audio.hpp"
#include "lib/engine.hpp"
#include "lib/engines/synthdispatcher/audio.hpp"
#include "lib/engines/synthdispatcher/screens.hpp"
#include "lib/engines/synthdispatcher/state.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/state/producer.hpp"
#include "lib/midi.hpp"

namespace otto {

  struct SynthEngineInstance {
    std::unique_ptr<ILogic> logic;
    std::unique_ptr<ISynthAudio> audio;
    ScreenWithHandler main_screen;
    ScreenWithHandler mod_screen;
    ScreenWithHandler voices_screen;

    SynthEngineInstance() = default;

    SynthEngineInstance(const SynthEngineInstance&) = delete;
    SynthEngineInstance(SynthEngineInstance&&) = default;
    SynthEngineInstance& operator=(const SynthEngineInstance&) = delete;
    SynthEngineInstance& operator=(SynthEngineInstance&& rhs) noexcept
    {
      reset();
      logic = std::move(rhs.logic);
      audio = std::move(rhs.audio);
      main_screen = std::move(rhs.main_screen);
      mod_screen = std::move(rhs.mod_screen);
      voices_screen = std::move(rhs.voices_screen);
      return *this;
    };

    ~SynthEngineInstance() noexcept
    {
      reset();
    }

    void reset() noexcept
    {
      if (audio != nullptr) {
        AudioDomain::static_executor().execute([audio = std::move(audio)] {});
        AudioDomain::static_executor().sync();
      }
      if (main_screen.screen != nullptr && mod_screen.screen != nullptr && voices_screen.screen != nullptr) {
        // Pass ownership to graphics thread. These will be destructed when the function has been called, i.e. on the
        // graphics thread
        GraphicsDomain::static_executor().execute([main_screen = std::move(this->main_screen.screen),
                                                   mod_screen = std::move(this->mod_screen.screen),
                                                   voices_screen = std::move(this->voices_screen.screen)] {});
        GraphicsDomain::static_executor().sync();
      }
      logic.reset();
    }
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

    SynthEngineInstance make_all(itc::Context& ctx) const
    {
      SynthEngineInstance res;
      res.logic = make_logic(ctx);
      res.audio = AudioDomain::static_executor().block_on(make_audio, ctx);
      res.main_screen = GraphicsDomain::static_executor().block_on(make_main_screen, ctx);
      res.mod_screen = GraphicsDomain::static_executor().block_on(make_mod_screen, ctx);
      res.voices_screen = GraphicsDomain::static_executor().block_on(make_voices_screen, ctx);
      return res;
    }

    SynthEngineInstance make_without_audio(itc::Context& ctx) const
    {
      SynthEngineInstance res;
      res.logic = make_logic(ctx);
      res.audio = nullptr;
      res.main_screen = GraphicsDomain::static_executor().block_on(make_main_screen, ctx);
      res.mod_screen = GraphicsDomain::static_executor().block_on(make_mod_screen, ctx);
      res.voices_screen = GraphicsDomain::static_executor().block_on(make_voices_screen, ctx);
      return res;
    }

    SynthEngineInstance make_without_screens(itc::Context& ctx) const
    {
      SynthEngineInstance res;
      res.logic = make_logic(ctx);
      res.audio = AudioDomain::static_executor().block_on(make_audio, ctx);
      res.main_screen = {nullptr, nullptr};
      res.mod_screen = {nullptr, nullptr};
      res.voices_screen = {nullptr, nullptr};
      return res;
    }
  };

  struct SynthDispatcherLogic : ILogic,
                                itc::Producer<SynthDispatcherState>,
                                itc::Receiver<SynthDispatcherCommand>,
                                itc::Persistant {
    using Producer::Producer;

    SynthDispatcherLogic(itc::Context& ctx)
      : Producer(ctx), Receiver(ctx), Persistant(ctx, "synth_dispatcher"), persistance_provider(ctx["engine"])
    {}

    void register_engine(SynthEngineFactory&& factory)
    {
      // First engine is set as default
      _factories.push_back(std::move(factory));
      commit([&](SynthDispatcherState& state) {
        state.all_engines.clear();
        for (const auto& f : _factories) {
          state.all_engines.push_back(f._metadata);
        }
      });
      if (_factories.size() == 1) {
        activate_engine(0);
      }
    }

    SynthEngineInstance& current()
    {
      return _active;
    }

    void select_engine(int index)
    {
      deactivate_engine();
      activate_engine(index);
    }

    void receive(SynthDispatcherCommand cmd) noexcept override
    {
      using namespace synth_dispatcher_cmd;
      util::match(cmd, //
                  [&](SelectEngine e) { select_engine(std::clamp(e.index, 0, (int) _factories.size() - 1)); });
    }

    void on_state_change(const SynthDispatcherState& state) noexcept override
    {
      if (_factories.empty() && active_index.check_changed(state.active_engine)) {
        select_engine(state.active_engine);
      }
    }

    void serialize_into(json::value& json) const override
    {
      if (!_factories.empty()) {
        json["active_engine"] = _factories[state().active_engine]._metadata.name;
        util::serialize_into(json["state"], persistance_provider);
      }
    }

    void deserialize_from(const json::value& json) override
    {
      deactivate_engine();
      if (auto active = json::get_or_null(json, "active_engine"); !active.is_null()) {
        int idx = std::ranges::find_if(_factories, [&](SynthEngineFactory& x) { return x._metadata.name == active; }) -
                  _factories.begin();
        if (idx == _factories.size()) {
          idx = 0;
        }
        activate_engine(idx);
        util::deserialize_from(json::get_or_null(json, "state"), persistance_provider);
      } else if (!_factories.empty()) {
        activate_engine(0);
      }
    }

  private:
    void deactivate_engine()
    {
      wipe_state();
      AudioDomain::static_executor().sync();
      GraphicsDomain::static_executor().sync();
      // Destructs the engine
      _active = SynthEngineInstance();
    }

    /// Make sure `deactivate_engine` has been called first
    void activate_engine(std::size_t idx)
    {
      LOGT("Activating engine {}", idx);
      // Constructs the engine
      if (idx < _factories.size()) {
        _active = _factories[idx].make_all(engine_ctx());
      }
      update_state(idx);
      AudioDomain::static_executor().sync();
      GraphicsDomain::static_executor().sync();
    }

    [[nodiscard]] itc::Context& engine_ctx()
    {
      return Producer::context()["engine"];
    }

    [[nodiscard]] const itc::Context& engine_ctx() const
    {
      return Producer::context()["engine"];
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

    itc::PersistanceProvider persistance_provider;
    std::vector<SynthEngineFactory> _factories;
    util::change_checker<int> active_index;
    SynthEngineInstance _active = {};
  };

  inline std::unique_ptr<SynthDispatcherLogic> make_synthdispatcher_logic(itc::Context& c)
  {
    return std::make_unique<SynthDispatcherLogic>(c);
  }

  // Handler //

  inline ScreenWithHandler make_synthdispatcher_selector_screen(itc::Context& c)
  {
    return make_with_internal_handler<DispatcherSelectorScreen>(c, key_groups::enc_clicks);
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
