#pragma once

#include <functional>
#include <memory>

#include "lib/util/eventdivider.hpp"

#include "lib/engine.hpp"
#include "lib/engines/synthdispatcher/state.hpp"
#include "lib/engines/synthdispatcher/synthdispatcher.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/itc.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "app/input.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"

namespace otto {

  // SELECTOR SCREEN //

  struct DispatcherSelectorScreen final : itc::Consumer<SynthDispatcherState>,
                                          ScreenBase,
                                          itc::Receiver<EncoderEvent>,
                                          itc::Sender<SynthDispatcherCommand> {
    using Consumer::Consumer;

    DispatcherSelectorScreen(itc::Context& c) : Consumer(c), Receiver(c), Sender(c) {}

    void draw(skia::Canvas& ctx) noexcept
    {
      // Super simple graphics
      skia::place_text(ctx, state().name.c_str(), fonts::regular(32), paints::fill(colors::blue),
                       {320 / 2.f, 240 / 2.f}, anchors::center);
    }

    void receive(EncoderEvent e) noexcept override
    {
      // TODO
      switch (e.encoder) {
        case Encoder::blue: {
          if (divider(e) != 0) send(SynthDispatcherCommand::toggle_engine);
        } break;
        default: break;
      }
    }
    otto::util::EventDivider<6> divider;
  };

  // PROXIES //

  struct DispatcherMainScreen final : itc::Consumer<SynthDispatcherState>, ScreenBase {
    using Consumer::Consumer;

    DispatcherMainScreen(itc::Context& c) : Consumer(c) {}

    void draw(skia::Canvas& ctx) noexcept
    {
      if (auto scr = state().main_screen; scr != nullptr) scr.screen->draw(ctx);
    }
  };

  struct DispatcherModScreen final : itc::Consumer<SynthDispatcherState>, ScreenBase {
    using Consumer::Consumer;

    DispatcherModScreen(itc::Context& c) : Consumer(c) {}

    void draw(skia::Canvas& ctx) noexcept
    {
      if (auto scr = state().mod_screen; scr != nullptr) scr.screen->draw(ctx);
    }
  };

  struct DispatcherVoicesScreen final : itc::Consumer<SynthDispatcherState>, ScreenBase {
    using Consumer::Consumer;

    DispatcherVoicesScreen(itc::Context& c) : Consumer(c) {}

    void draw(skia::Canvas& ctx) noexcept
    {
      if (auto scr = state().voices_screen; scr != nullptr) scr.screen->draw(ctx);
    }
  };

  // Handlers //

  struct DispatcherMainHandler final : LogicDomain,
                                       itc::Consumer<SynthDispatcherState>,
                                       EventHandlerProxy<DispatcherMainHandler, KeyPress, KeyRelease, EncoderEvent>,
                                       IInputLayer {
    using EventHandlerProxy::handle;

    DispatcherMainHandler(itc::Context& c) : Consumer(c) {}

    IInputLayer& proxy_target() const
    {
      return *state().main_screen.input;
    }
    KeySet key_mask() const noexcept override
    {
      return proxy_target().key_mask();
    };
  };

  struct DispatcherModHandler final : LogicDomain,
                                      itc::Consumer<SynthDispatcherState>,
                                      EventHandlerProxy<DispatcherModHandler, KeyPress, KeyRelease, EncoderEvent>,
                                      IInputLayer {
    using EventHandlerProxy::handle;

    DispatcherModHandler(itc::Context& c) : Consumer(c) {}

    IInputLayer& proxy_target() const
    {
      return *state().mod_screen.input;
    }
    KeySet key_mask() const noexcept override
    {
      return proxy_target().key_mask();
    };
  };

  struct DispatcherVoicesHandler final : LogicDomain,
                                         itc::Consumer<SynthDispatcherState>,
                                         EventHandlerProxy<DispatcherVoicesHandler, KeyPress, KeyRelease, EncoderEvent>,
                                         IInputLayer {
    using EventHandlerProxy::handle;

    DispatcherVoicesHandler(itc::Context& c) : Consumer(c) {}

    IInputLayer& proxy_target() const
    {
      return *state().voices_screen.input;
    }
    KeySet key_mask() const noexcept override
    {
      return proxy_target().key_mask();
    };
  };

  inline ScreenWithHandler make_synthdispatcher_main_screen(itc::Context& c)
  {
    return {
      .screen = std::make_unique<DispatcherMainScreen>(c),
      .input = std::make_unique<DispatcherMainHandler>(c),
    };
  }

  inline ScreenWithHandler make_synthdispatcher_mod_screen(itc::Context& c)
  {
    return {
      .screen = std::make_unique<DispatcherModScreen>(c),
      .input = std::make_unique<DispatcherModHandler>(c),
    };
  }

  inline ScreenWithHandler make_synthdispatcher_voices_screen(itc::Context& c)
  {
    return {
      .screen = std::make_unique<DispatcherVoicesScreen>(c),
      .input = std::make_unique<DispatcherVoicesHandler>(c),
    };
  }

} // namespace otto
