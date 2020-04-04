#include "board/ui/glfw_ui_manager.hpp"

#include <chrono>
#include <thread>
#include <gsl/gsl_util>

#include "core/ui/vector_graphics.hpp"

#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"

#define NANOVG_GL3_IMPLEMENTATION
#define OTTO_NVG_CREATE nvgCreateGL3
#define OTTO_NVG_DELETE nvgDeleteGL3

#include "board/ui/keys.hpp"

// C APIs. Include last
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <nanovg_gl.h>

#include "board/emulator.hpp"

namespace otto::glfw {

  Window::Window(int width, int height, const std::string& name)
  {
    if (!glfwInit()) {
      LOG_F(ERROR, "Failed to init GLFW.");
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    _glfw_win = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!_glfw_win) {
      throw util::exception("Failed to create GLFW window {}", name);
    }
    glfwSetWindowUserPointer(_glfw_win, this);

    glfwSetMouseButtonCallback(_glfw_win, [](GLFWwindow* window, int button, int action, int mods) {
      if (auto* win = get_for(window); win && win->mouse_button_callback) {
        win->mouse_button_callback(board::ui::Button{button}, board::ui::Action{action}, board::ui::Modifiers{mods});
      }
    });

    glfwSetScrollCallback(_glfw_win, [](GLFWwindow* window, double x, double y) {
      if (auto* win = get_for(window); win && win->mouse_button_callback) {
        win->scroll_callback(x, y);
      }
    });

#if false
    glfwSetKeyboardCallback(_glfw_win, [](GLFWwindow* window, int key, int scancode, int action,
                                          int mods, const char* str, int) {
      if (auto* win = get_for(window); win) {
        if (win->key_callback) {
          win->key_callback(board::ui::Action{action}, board::ui::Modifiers{mods},
                            board::ui::Key{key});
        }
        if (win->char_callback && strlen(str) == 1) {
          win->char_callback(str[0]);
        }
      }
    });
#else
    glfwSetKeyCallback(_glfw_win, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      if (auto* win = get_for(window); win && win->key_callback) {
        win->key_callback(board::ui::Action{action}, board::ui::Modifiers{mods}, board::ui::Key{key});
      }
    });

    glfwSetCharCallback(_glfw_win, [](GLFWwindow* window, unsigned ch) {
      if (auto* win = get_for(window); win && win->char_callback) {
        win->char_callback((char) ch);
      }
    });
#endif

    make_current();
    gl3wInit();
  }

  Window::~Window() noexcept {}

  GLFWwindow* Window::unwrap()
  {
    return _glfw_win;
  }

  Window::operator GLFWwindow*()
  {
    return _glfw_win;
  }

  Window* Window::get_for(GLFWwindow* glfw_win)
  {
    return static_cast<Window*>(glfwGetWindowUserPointer(glfw_win));
  }

  void Window::make_current()
  {
    glfwMakeContextCurrent(_glfw_win);
  }

  void Window::swap_buffers()
  {
    glfwSwapBuffers(_glfw_win);
  }

  void Window::set_window_aspect_ration(int x, int y)
  {
    glfwSetWindowAspectRatio(_glfw_win, x, y);
  }

  void Window::set_window_size_limits(int min_x, int min_y, int max_x, int max_y)
  {
    glfwSetWindowSizeLimits(_glfw_win, min_x, min_y, max_x, max_y);
  }

  void Window::set_window_size(int x, int y)
  {
    glfwSetWindowSize(_glfw_win, x, y);
  }

  bool Window::should_close()
  {
    return glfwWindowShouldClose(_glfw_win);
  }

  vg::Point Window::cursor_pos()
  {
    double x, y;
    glfwGetCursorPos(_glfw_win, &x, &y);
    return vg::Point{(float) x, (float) y};
  }

  std::pair<int, int> Window::window_size()
  {
    int x, y;
    glfwGetWindowSize(_glfw_win, &x, &y);
    return {x, y};
  }

  std::pair<int, int> Window::framebuffer_size()
  {
    int x, y;
    glfwGetFramebufferSize(_glfw_win, &x, &y);
    return {x, y};
  }


  NVGWindow::NVGWindow(int width, int height, const std::string& name)
    : Window(width, height, name),
      _vg(OTTO_NVG_CREATE(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG)),
      _canvas(_vg, width, height)
  {}

  NVGWindow::~NVGWindow() noexcept
  {
    OTTO_NVG_DELETE(_vg);
  }

  vg::Canvas& NVGWindow::canvas()
  {
    return _canvas;
  }

  void NVGWindow::begin_frame()
  {
    make_current();
    auto [winWidth, winHeight] = window_size();
    auto [fbWidth, fbHeight] = framebuffer_size();

    _canvas.setSize(winWidth, winHeight);

    // Update and render
    glViewport(0, 0, fbWidth, fbHeight);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    _canvas.clearColor(vg::Colours::Black);
    _canvas.beginFrame(winWidth, winHeight);
  }

  void NVGWindow::end_frame()
  {
    _canvas.endFrame();
    glEnable(GL_DEPTH_TEST);
    swap_buffers();
  }
} // namespace otto::glfw

namespace otto::services {

  using namespace core::ui;

  static void error_callback(int error, const char* description)
  {
    LOG_F(ERROR, "GLFW UI: {}", description);
  }

  void GLFWUIManager::main_ui_loop()
  {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
      LOG_F(ERROR, "Failed to init GLFW.");
    }
    gsl::final_action terminate_glfw(glfwTerminate);
    gsl::final_action exit_application([] { Application::current().exit(Application::ErrorCode::ui_closed); });

    glfw::NVGWindow main_win(vg::width, vg::height, "OTTO");

    board::Emulator* const emulator = dynamic_cast<board::Emulator*>(&services::Controller::current());

    vg::Size canvas_size = {vg::width, vg::height};
    float scale = 1;

    if (emulator) {
      main_win.set_window_aspect_ration(emulator->size.w, emulator->size.h);
      main_win.set_window_size(emulator->size.w, emulator->size.h);
      canvas_size = emulator->size;
      main_win.mouse_button_callback = [&] (glfw::Button b, glfw::Action a, glfw::Modifiers)  {
        if (a == glfw::Action::press) emulator->handle_click(main_win.cursor_pos() / scale, board::Emulator::ClickAction::down);
        if (a == glfw::Action::release) emulator->handle_click(main_win.cursor_pos() / scale, board::Emulator::ClickAction::up);
      };
      main_win.scroll_callback = [&] (double x, double y) {
        emulator->handle_scroll(main_win.cursor_pos() / scale, y);
      };
    } else {
      main_win.set_window_aspect_ration(4, 3);
      main_win.set_window_size_limits(320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);
    }

    main_win.key_callback = [] (auto&& action, auto&& mods, auto&& key) {
      board::ui::handle_keyevent(action, mods, key, services::Controller::current());
    };

    vg::initUtils(main_win.canvas());

    glfwSetTime(0);

    double t, spent;
    while (!main_win.should_close() && Application::current().running()) {

      t = glfwGetTime();

      auto [winWidth, winHeight] = main_win.window_size();
      // Calculate pixel ration for hi-dpi devices.

      main_win.begin_frame();
      scale = std::min((float) winWidth / (float) canvas_size.w, (float) winHeight / (float) canvas_size.h);
      main_win.canvas().scale(scale, scale);

      if (emulator) {
        emulator->draw(main_win.canvas());
        main_win.canvas().translate(518, 28);
        main_win.canvas().scale(215.f / 320.f, 161.f / 240.f);
      }
      draw_frame(main_win.canvas());

      main_win.end_frame();

      glfwPollEvents();

      spent = glfwGetTime() - t;

      std::this_thread::sleep_for(std::chrono::milliseconds(int(1000 / 120 - spent * 1000)));

    }
  }
} // namespace otto::services

// kak: other_file=../include/board/ui/glfw_ui_manager.hpp
