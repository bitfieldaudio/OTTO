#pragma once

#include <SkCanvas.h>

#include "board/ui/keys.hpp"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;
namespace otto::glfw {

  using board::ui::Button;
  using board::ui::Action;
  using board::ui::Key;
  using board::ui::Modifiers;

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

    SkPoint cursor_pos();
    std::pair<int, int> window_size();
    std::pair<int, int> framebuffer_size();

    std::function<void(Button, Action, Modifiers)> mouse_button_callback = nullptr;
    std::function<void(Action, Modifiers, Key)> key_callback = nullptr;
    std::function<void(char)> char_callback = nullptr;
    std::function<void(double x, double y)> scroll_callback = nullptr;

  private:
    GLFWwindow* _glfw_win;
  };

  struct SkiaWindow : Window {
    SkiaWindow(int width, int height, const std::string& name);
    ~SkiaWindow() noexcept;

    SkCanvas& canvas();

    void begin_frame();
    void end_frame();

  private:
    sk_sp<GrContext> context_;
    sk_sp<SkSurface> surface_;
    SkCanvas* canvas_;
  };

} // namespace otto::glfw

// kak: other_file=../../../src/glfw_ui.cpp
