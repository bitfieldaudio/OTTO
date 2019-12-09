#pragma once

#include "core/engine/engine.hpp"
#include "core/engine/nullengine.hpp"
#include "util/flat_map.hpp"
#include "util/variant_w_base.hpp"

namespace otto::core::engine {

  struct EngineSelectorScreen;

  using SelectedEngine = itc::PropTypes<struct selected_engine_tag, int>;
  using SelectedPreset = itc::PropTypes<struct selected_preset_tag, int>;
  using CurrentScreen = itc::PropTypes<struct current_screen_tag, int>;
  using PublishEngineNames = itc::PropTypes<struct publish_engine_names_tag, gsl::span<const util::string_ref>>;

  /// Owns engines of type `ET`, and dispatches to a selected one of them
  template<EngineType ET, typename... Engines>
  struct EngineDispatcher {
    using Sender = services::UISender<EngineSelectorScreen>;

    struct Props {
      template<typename Tag, typename Type, typename... Mixins>
      using Prop = typename Sender::template Prop<Tag, Type, Mixins...>;

      Sender sender;
      CurrentScreen::Prop<Sender> current_screen = {sender, 0};
    };

    ui::Screen& selector_screen();
    ITypedEngine<ET>& current();
    ITypedEngine<ET>* operator->();

    template<int N>
    auto process(audio::ProcessData<N> data) noexcept;

    DECL_REFLECTION_EMPTY();

  private:
    util::variant_w_base<ITypedEngine<ET>, Engines...> current_engine_ = std::in_place_index_t<0>();
  };
} // namespace otto::core::engine

#include "engine_dispatcher.inl"
