#pragma once

#include <better_enum.hpp>

#include <json.hpp>
#include <unordered_map>
#include "util/locked.hpp"

#include "core/engine/engine.hpp"
#include "core/service.hpp"
#include "core/ui/screen.hpp"
#include "services/application.hpp"

namespace otto::services {

  BETTER_ENUM(ChannelEnum,
              std::uint8_t,
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
              external)

  BETTER_ENUM(ScreenEnum,
              std::uint8_t,
              sends,
              routing,
              fx1,
              fx2,
              looper,
              arp,
              master,
              sequencer,
              sampler,
              synth,
              envelope,
              settings,
              external,
              twist1,
              twist2)


  struct UIManager : core::Service {
    struct State {
      ChannelEnum active_channel = ChannelEnum::internal;
      ScreenEnum current_screen = ScreenEnum::synth;
    };


    UIManager();

    /// The main ui loop
    ///
    /// This sets up all the device specific graphics, and calls
    /// @ref internal::draw_frame 60 times pr second, until @ref global::running is
    /// false, or the graphics are exitted by the user. It is also responsible for
    /// listening to keyevents, and calling @ref internal::keypress and
    /// @ref internal::keyrelease as apropriate.
    ///
    /// On some platforms (OSX), all OpenGL calls must be made from the main
    /// thread, therefore this function is called from `main()`.
    ///
    /// One important note, is that this function is implemented in the graphics
    /// drivers. The drivers can be found in the "egl" (RPI native) and "glfw" (Windowing systems)
    /// folders.
    virtual void main_ui_loop() = 0;

    /// Display a screen.
    ///
    /// Calls @ref Screen::on_hide for the old screen, and then @ref Screen::on_show
    /// for the new screen
    void display(core::ui::Screen& screen);

    /// Select an engine
    void select_engine(core::engine::IEngine& engine);

    /// Select an engine by name
    void select_engine(const std::string& engine_name);

    core::ui::Screen* current_screen();

    /// Get the currently selected engine
    const std::string& selected_engine_name();

    static UIManager& current() noexcept {
      return Application::current().ui_manager;
    }

  protected:
    /// Draws the current screen and overlays.
    void draw_frame(core::ui::vg::Canvas& ctx);

  private:
    struct EmptyScreen : core::ui::Screen {
      void draw(core::ui::vg::Canvas& ctx) {}
    } empty_screen;

    std::string _selected_engine_name = "";
    core::ui::Screen* cur_screen = &empty_screen;

    State state;

    unsigned _frame_count = 0;

    static constexpr const char* initial_engine = "Synth";
  };

} // namespace otto::services
