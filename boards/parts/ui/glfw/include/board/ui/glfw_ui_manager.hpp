#pragma once

#include "services/debug_ui.hpp"
#include "services/ui_manager.hpp"

#include "board/ui/keys.hpp"
#include "core/ui/canvas.hpp"

struct GLFWwindow;
namespace otto::glfw {

  using board::ui::Button;
  using board::ui::Action;
  using board::ui::Key;
  using board::ui::Modifier;
  using board::ui::Modifiers;
  namespace vg = core::ui::vg;

  struct Window {
    Window(int width, int height, const std::string& name);
    ~Window() noexcept;

    operator GLFWwindow*();
    GLFWwindow* unwrap();
    static Window* get_for(GLFWwindow* glfw_win);

    void make_current();
    void swap_buffers();

    void set_window_aspect_ration(int x, int y);
    void set_window_size_limits(int min_x, int min_y, int max_x, int max_y);
    void set_window_size(int x, int y);

    bool should_close();

    vg::Point cursor_pos();
    std::pair<int, int> window_size();
    std::pair<int, int> framebuffer_size();

    std::function<void(Button, Action, Modifiers)> mouse_button_callback = nullptr;
    std::function<void(Action, Modifiers, Key)> key_callback = nullptr;
    std::function<void(char)> char_callback = nullptr;
    std::function<void(double x, double y)> scroll_callback = nullptr;

  private:
    GLFWwindow* _glfw_win;
  };

  struct NVGWindow : Window {
    NVGWindow(int width, int height, const std::string& name);
    ~NVGWindow() noexcept;

    vg::Canvas& canvas();

    void begin_frame();
    void end_frame();

  private:
    NVGcontext* _vg;
    vg::Canvas _canvas;
  };

} // namespace otto::glfw

namespace otto::services {

  struct GLFWUIManager final : UIManager {
    GLFWUIManager() = default;

    void main_ui_loop() override;
  };

} // namespace otto::services

// kak: other_file=../../../src/glfw_ui.cpp
