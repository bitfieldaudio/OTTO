#pragma once

#include <json.hpp>
#include <unordered_map>
#include "util/locked.hpp"

#include "core/engine/engine.hpp"
#include "core/service.hpp"
#include "core/ui/screen.hpp"
#include "services/application.hpp"

namespace otto::board::ui {
  enum struct Action;
  struct Modifiers;
  enum struct Key;
  void handle_keyevent(board::ui::Action, board::ui::Modifiers, board::ui::Key);
} // namespace otto::board::ui

namespace otto::services {

  struct UIManager : core::Service {
    struct KeyPress {
      core::ui::Key key;
    };
    struct KeyRelease {
      core::ui::Key key;
    };
    using KeyEvent = mpark::variant<KeyPress, KeyRelease>;

    /// Function type for key handlers
    using KeyHandler = std::function<void(core::ui::Key k)>;

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

    /// Check if a key is currently pressed.
    bool is_pressed(core::ui::Key k) noexcept;

    /// Register a key handler
    void register_key_handler(core::ui::Key k,
                              KeyHandler press_handler,
                              KeyHandler release_handler = nullptr);
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

  protected:
    /// Draws the current screen and overlays.
    void draw_frame(core::ui::vg::Canvas& ctx);

    /// Dispatches to the event handler for the current screen, and handles
    /// global keys.
    ///
    /// Can be executed from a separate thread
    void keypress(core::ui::Key key);

    /// Dispatches to the event handler for the current screen, and handles
    /// global keys.
    ///
    /// Can be executed from a separate thread, but must be the same thread as keypress
    void keyrelease(core::ui::Key key);

    /// Send rotary event
    ///
    /// Can be executed from a separate thread
    void rotary(core::ui::RotaryEvent ev);

    /// Actually executes the key and rotary events
    void flush_events();

    /// Temporary solution
    ///
    /// @TODO replace with something cleaner
    friend void ::otto::board::ui::handle_keyevent(board::ui::Action,
                                                   board::ui::Modifiers,
                                                   board::ui::Key);

  private:
    bool handle_global(core::ui::Key key, bool is_press = true);

    struct EmptyScreen : core::ui::Screen {
      void draw(core::ui::vg::Canvas& ctx) {}
    } empty_screen;

    std::string _selected_engine_name = "";
    core::ui::Screen* cur_screen = &empty_screen;

    core::ui::PressedKeys keys;
    std::unordered_multimap<core::ui::Key, std::pair<KeyHandler, KeyHandler>> key_handlers;
    util::atomic_swap<std::vector<KeyEvent>> key_events;
    util::atomic_swap<std::vector<core::ui::RotaryEvent>> rotary_events;

    unsigned _frame_count = 0;

    static constexpr const char* initial_engine = "Synth";
  };

} // namespace otto::services
