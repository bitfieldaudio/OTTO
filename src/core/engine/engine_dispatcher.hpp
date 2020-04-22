#pragma once

#include "core/engine/engine.hpp"
#include "core/engine/nullengine.hpp"
#include "core/ui/icons.hpp"
#include "util/flat_map.hpp"
#include "util/spin_lock.hpp"
#include "util/string_ref.hpp"
#include "util/variant_w_base.hpp"

namespace otto::core::engine {

  struct EngineSelectorData {
    util::string_ref name;
    ui::Icon icon;
    std::vector<std::string> presets;
  };

  enum struct EngineSlot {
    arp,
    synth,
    fx1,
    fx2,
  };

  template<EngineSlot ES>
  struct EngineSelectorScreen;

  constexpr EngineType engine_type_for(EngineSlot es)
  {
    switch (es) {
      case EngineSlot::arp: return EngineType::arpeggiator;
      case EngineSlot::synth: return EngineType::synth;
      case EngineSlot::fx1: return EngineType::effect;
      case EngineSlot::fx2: return EngineType::effect;
    }
  }

  template<EngineSlot ES>
  struct selected_engine_tag;
  template<EngineSlot ES>
  struct selected_preset_tag;
  template<EngineSlot ES>
  struct publish_engine_data_tag;
  template<EngineSlot ES>
  struct make_new_preset_tag;

  template<EngineSlot ES>
  using SelectedEngine = itc::PropTypes<selected_engine_tag<ES>, int>;
  template<EngineSlot ES>
  using SelectedPreset = itc::PropTypes<selected_preset_tag<ES>, int>;
  template<EngineSlot ES>
  struct Actions {
    using publish_engine_data = itc::Action<publish_engine_data_tag<ES>, EngineSelectorData>;
    using make_new_preset = itc::Action<make_new_preset_tag<ES>, std::string>;
  };

  /// Owns engines of type `ET`, and dispatches to a selected one of them
  template<EngineSlot ES, typename... Engines>
  struct EngineDispatcher : input::InputHandler,
                            util::OwnsObservers,
                            itc::ActionReceiverOnBus< //
                              itc::LogicBus,
                              typename SelectedEngine<ES>::action,
                              typename SelectedPreset<ES>::action,
                              typename Actions<ES>::make_new_preset> //
  {
    static constexpr EngineType engine_type = engine_type_for(ES);
    constexpr static std::array<util::string_ref, sizeof...(Engines)> engine_names = {{Engines::name...}};
    constexpr static bool has_off_engine = std::is_same_v<meta::head_t<meta::list<Engines...>>, OffEngine<engine_type>>;

    struct Props {
      typename SelectedEngine<ES>::template GAProp<> selected_engine_idx = {0,
                                                                            props::limits(0, sizeof...(Engines) - 1)};
      typename SelectedPreset<ES>::template GAProp<> selected_preset_idx = {0, props::limits(0, 12)};
    };

    EngineDispatcher() noexcept;

    ui::ScreenAndInput selector_screen() noexcept;
    ui::ScreenAndInput engine_screen() noexcept;
    ITypedEngine<engine_type>& current();
    ITypedEngine<engine_type>* operator->();

    template<int N>
    auto process(audio::ProcessData<N> data) noexcept;

    void encoder(input::EncoderEvent) override;
    bool keypress(input::Key) override;

    void action(typename SelectedEngine<ES>::action, int v) noexcept final
    {
      props.selected_engine_idx = v;
    }

    void action(typename SelectedPreset<ES>::action, int v) noexcept final
    {
      props.selected_preset_idx = v;
    }

    void action(typename Actions<ES>::make_new_preset, std::string name) noexcept final;

    void from_json(const nlohmann::json&);
    nlohmann::json to_json() const;

    /// Returns the icon draw function for a given engine
    // TODO: move this to an actual engine register!
    ui::Icon::IconDrawer icon_register(util::string_ref);

  private:
    void send_data_for(util::string_ref engine_name);
    void update_max_preset_idx();
    void save_engine_state();

    std::atomic<bool> engine_is_constructed_ = true;
    util::variant_w_base<ITypedEngine<engine_type>, Engines...> current_engine_ = std::in_place_index_t<0>();
    std::unique_ptr<EngineSelectorScreen<ES>> screen_;
    util::flat_map<std::string, nlohmann::json> engine_states_;
    Props props;
  };

} // namespace otto::core::engine

#include "engine_dispatcher.inl"
