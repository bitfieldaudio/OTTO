#pragma once

#include <SkCanvas.h>

#include "board/ui/keys.hpp"

#include <GLFW/glfw3.h>
#include <thread>

#include "lib/util/concepts.hpp"

struct GLFWwindow;
namespace otto::glfw {

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

    void close();

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

    /// Show graphics until the window is closed or the draw function returns false
    void show(util::callable<bool(SkCanvas&)> auto&& f)
    {
      glfwSetTime(0);
      double t, spent;

      bool run = true;
      while (run && !should_close()) {
        t = glfwGetTime();
        begin_frame();
        run = std::invoke(f, canvas());
        end_frame();
        glfwPollEvents();
        spent = glfwGetTime() - t;
        std::this_thread::sleep_for(std::chrono::milliseconds(int(1000.0 / 120 - spent * 1000)));
      }
      close();
    }

    /// Show graphics until the window is closed
    void show(util::callable<void(SkCanvas&)> auto&& f)
    {
      show([f = FWD(f)](SkCanvas& ctx) -> bool {
        std::invoke(f, ctx);
        return true;
      });
    }

  protected:
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
