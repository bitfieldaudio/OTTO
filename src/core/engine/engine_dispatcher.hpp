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

  struct EngineSelectorScreen;

  struct selected_engine_tag;
  struct selected_preset_tag;
  struct publish_engine_data_tag;
  struct make_new_preset_tag;

  using SelectedEngine = itc::PropTypes<selected_engine_tag, int>;
  using SelectedPreset = itc::PropTypes<selected_preset_tag, int>;
  struct Actions {
    using publish_engine_data = itc::Action<publish_engine_data_tag, EngineSelectorData>;
    using make_new_preset = itc::Action<make_new_preset_tag, std::string>;
  };

  /// Owns engines of type `ET`, and dispatches to a selected one of them
  template<EngineType ET, typename... Engines>
  struct EngineDispatcher : input::InputHandler,
                            util::OwnsObservers,
                            itc::ActionReceiverOnBus< //
                              itc::LogicBus,
                              SelectedEngine::action,
                              SelectedPreset::action,
                              Actions::make_new_preset> //
  {
    static constexpr EngineType engine_type = ET;
    constexpr static std::array<util::string_ref, sizeof...(Engines)> engine_names = {{Engines::name...}};
    constexpr static bool has_off_engine = std::is_same_v<meta::head_t<meta::list<Engines...>>, OffEngine<engine_type>>;

    struct Props : props::Properties<Props> {
      SelectedEngine::GAProp<> selected_engine_idx = {0, props::limits(0, sizeof...(Engines) - 1)};
      SelectedPreset::GAProp<> selected_preset_idx = {0, props::limits(0, 12)};
      REFLECT_PROPS(Props, selected_engine_idx, selected_preset_idx);
    };

    EngineDispatcher(itc::ActionChannel) noexcept;

    ui::ScreenAndInput selector_screen() noexcept;
    ui::ScreenAndInput engine_screen() noexcept;
    ITypedEngine<engine_type>& current();
    ITypedEngine<engine_type>* operator->();

    template<int N>
    auto process(audio::ProcessData<N> data) noexcept;

    void encoder(input::EncoderEvent) override;
    bool keypress(input::Key) override;

    void action(SelectedEngine::action, int v) noexcept final
    {
      props.selected_engine_idx = v;
    }

    void action(SelectedPreset::action, int v) noexcept final
    {
      props.selected_preset_idx = v;
    }

    void action(Actions::make_new_preset, std::string name) noexcept final;

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
    util::variant_w_base<ITypedEngine<engine_type>, Engines...> current_engine_;
    std::unique_ptr<EngineSelectorScreen> screen_;
    util::flat_map<std::string, nlohmann::json> engine_states_;
    Props props;
  };

} // namespace otto::core::engine

#include "engine_dispatcher.inl"
