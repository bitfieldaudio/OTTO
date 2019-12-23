#pragma once

#include "core/engine/engine.hpp"
#include "core/engine/nullengine.hpp"
#include "util/flat_map.hpp"
#include "util/spin_lock.hpp"
#include "util/variant_w_base.hpp"

namespace otto::core::engine {

  struct EngineSelectorScreen;

  using SelectedEngine = itc::PropTypes<struct selected_engine_tag, int>;
  using SelectedPreset = itc::PropTypes<struct selected_preset_tag, int>;
  using CurrentScreen = itc::PropTypes<struct current_screen_tag, int>;
  using PublishEngineNames = itc::PropTypes<struct publish_engine_names_tag, gsl::span<const util::string_ref>>;

  /// Owns engines of type `ET`, and dispatches to a selected one of them
  template<EngineType ET, typename... Engines>
  struct EngineDispatcher : input::InputHandler {
    using Sender = services::UISender<EngineSelectorScreen>;

    constexpr static std::array<util::string_ref, sizeof...(Engines)> engine_names = {{Engines::name...}};
    constexpr static bool has_off_engine = std::is_same_v<meta::head_t<meta::list<Engines...>>, OffEngine<ET>>;

    struct Props {
      template<typename Tag, typename Type, typename... Mixins>
      using Prop = typename Sender::template Prop<Tag, Type, Mixins...>;

      Sender sender;
      SelectedEngine::Prop<Sender> selected_engine_idx = {sender, 0, props::limits(0, sizeof...(Engines) - 1)};
      SelectedPreset::Prop<Sender> selected_preset_idx = {sender, 0, props::limits(0, 12)};
      CurrentScreen::Prop<Sender> current_screen = {sender, 0, props::limits(0, 1)};
    };

    EngineDispatcher() noexcept;

    ui::ScreenAndInput selector_screen() noexcept;
    ui::ScreenAndInput engine_screen() noexcept;
    ITypedEngine<ET>& current();
    ITypedEngine<ET>* operator->();

    template<int N>
    auto process(audio::ProcessData<N> data) noexcept;

    DECL_REFLECTION_EMPTY();

    void encoder(input::EncoderEvent) override;
    bool keypress(input::Key) override;

  private:
    std::atomic<bool> engine_is_constructed_ = true;
    util::variant_w_base<ITypedEngine<ET>, Engines...> current_engine_ = std::in_place_index_t<0>();
    std::unique_ptr<EngineSelectorScreen> screen_;
    Props props = {{*screen_}};
  };
} // namespace otto::core::engine

#include "engine_dispatcher.inl"
#include "engine_selector_screen.hpp"
