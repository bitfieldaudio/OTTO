#pragma once

#include <chrono>
#include <json.hpp>
#include <unordered_map>

#include "core/props/props.hpp"
#include "core/service.hpp"
#include "core/ui/screen.hpp"
#include "itc/itc.hpp"
#include "services/application.hpp"
#include "util/enum.hpp"
#include "util/locked.hpp"

#include "services/application.hpp"
#include "services/controller.hpp"
#include "util/thread.hpp"

namespace otto::services {

  BETTER_ENUM(SourceEnum, std::int8_t, sequencer, internal, external)

  BETTER_ENUM(ChannelEnum,
              std::int8_t,
              sampler0 = 0,
              sampler1 = 1,
              sampler2 = 2,
              sampler3 = 3,
              sampler4 = 4,
              sampler5 = 5,
              sampler6 = 6,
              sampler7 = 7,
              sampler8 = 8,
              sampler9 = 9,
              internal,
              external_stereo,
              external_left,
              external_right)

  SourceEnum source_of(ChannelEnum) noexcept;

  BETTER_ENUM(ScreenEnum,
              std::int8_t,
              sends,
              routing,
              fx1,
              fx1_selector,
              fx2,
              fx2_selector,
              looper,
              arp,
              arp_selector,
              voices,
              master,
              sequencer,
              sampler,
              sampler_envelope,
              synth,
              synth_selector,
              synth_envelope,
              settings,
              external,
              twist1,
              twist2,
              saveslots)

  BETTER_ENUM(KeyMode, std::int8_t, midi, seq);

  struct UIManager : core::Service, util::OwnsObservers {
    /// The UI state
    ///
    /// This will dictate which state-leds light up, and which channel is currently selected etc.
    struct State {
      core::props::Property<SourceEnum> active_source = SourceEnum::internal;
      core::props::Property<ChannelEnum> active_channel = ChannelEnum::internal;
      core::props::Property<ScreenEnum> current_screen = ScreenEnum::synth;
      core::props::Property<KeyMode> key_mode = KeyMode::midi;
      core::props::Property<int> octave = {0, core::props::limits(-4, 4)};

      DECL_REFLECTION(State, active_channel, current_screen, key_mode, octave);
    };

    using ScreenSelector = std::function<core::ui::ScreenAndInput()>;

    UIManager();

    /// The main ui loop
    ///
    /// This sets up all the device specific graphics, and calls @ref draw_frame 60 times pr second,
    /// until @ref Application::running() is false, or the graphics are exitted by the user. It is
    /// also responsible for listening to keyevents, and calling @ref keypress and @ref keyrelease
    /// as apropriate.
    ///
    /// On some platforms (OSX), all OpenGL calls must be made from the main
    /// thread, therefore this function is called from `main()`.
    virtual void main_ui_loop() = 0;

    /// Select an engine
    void display(ScreenEnum screen);
    /// Pop back to previous screen
    ///
    /// Only one level is saved, so can only be used once. Otherwise, has no effect
    ScreenEnum pop_back();
    /// Push current screen to single-element stack. Overrides previous screen.
    void push_back(ScreenEnum);

    core::ui::Screen& current_screen();
    core::input::InputHandler& current_input_handler();

    static UIManager& current() noexcept
    {
      return Application::current().ui_manager;
    }

    void register_screen_selector(ScreenEnum, ScreenSelector);
    /// Register a single screen to a key
    void register_screen_key(core::input::Key key, ScreenEnum);
    /// Register a two screens to a key, one of them with a modifier
    void register_screen_key(core::input::Key key, ScreenEnum, ScreenEnum, core::input::Key modifier);

    State state;

    struct {
      util::Signal<core::ui::vg::Canvas&> on_draw;
    } signals;

    /// Push-only access to the action queue
    ///
    /// This queue is consumed at the start of each buffer.
    itc::PushOnlyActionQueue& action_queue() noexcept
    {
      return action_queue_;
    }

    /// Make an {@ref ActionSender} for the audio action queue
    template<typename... Receivers>
    auto make_sndr(Receivers&...) noexcept;

  protected:
    /// Draws the current screen and overlays.
    void draw_frame(core::ui::vg::Canvas& ctx);

    /// Display a screen.
    ///
    /// Calls @ref Screen::on_hide for the old screen, and then @ref Screen::on_show
    /// for the new screen
    void display(core::ui::ScreenAndInput screen);

  private:
    struct EmptyScreen : core::ui::Screen {
      void draw(core::ui::vg::Canvas& ctx) {}
    } empty_screen;
    core::input::InputHandler empty_input;
    core::ui::ScreenAndInput empty_sai = {empty_screen, empty_input};
    core::ui::ScreenAndInput cur_sai = empty_sai;
    core::ui::ScreenAndInput last_sai = empty_sai;

    util::enum_map<ScreenEnum, ScreenSelector> screen_selectors_;

    unsigned _frame_count = 0;

    chrono::time_point last_frame = chrono::clock::now();
    itc::ActionQueue action_queue_;

    ScreenEnum screen_stack = ScreenEnum::synth;
    void reset_timer();
    bool timer_done();
    chrono::seconds peek_time = chrono::seconds(1); // 1 second
    decltype(chrono::clock::now()) press_time = chrono::clock::now();
  };

  template<typename... Receivers>
  struct UISender : itc::ActionSender<Receivers...> {
    template<typename Tag, typename Type, typename... Mixins>
    using Prop = typename itc::ActionSender<Receivers...>::template Prop<Tag, Type, Mixins...>;

    UISender(Receivers&... r) noexcept : itc::ActionSender<Receivers...>(UIManager::current().action_queue(), r...) {}
  };

  // IMPLEMENTATION //

  template<typename... Receivers>
  auto UIManager::make_sndr(Receivers&... receivers) noexcept
  {
    return itc::ActionSender(action_queue_, receivers...);
  }

} // namespace otto::services
