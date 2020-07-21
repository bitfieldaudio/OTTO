#include "board/ui/glfw_ui.hpp"

#include <GrBackendSurface.h>
#include <GrContext.h>
#include <SkCanvas.h>
#include <SkColorSpace.h>
#include <SkSurface.h>
#include <gl/GrGLAssembleInterface.h>
#include <gl/GrGLInterface.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "util/exception.hpp"

namespace otto::glfw {
  using namespace std::literals;

  static GrGLFuncPtr glfw_get(void* ctx, const char name[])
  {
    SkASSERT(nullptr == ctx);
    SkASSERT(glfwGetCurrentContext());
    if (name == "eglQueryString"sv) {
      return nullptr;
      return (GrGLFuncPtr)(static_cast<GrEGLQueryStringFn*>([](void* dpy, int name) -> const char* { return ""; }));
    }
    return glfwGetProcAddress(name);
  }

  sk_sp<const GrGLInterface> GrGLMakeNativeInterface_glfw()
  {
    if (nullptr == glfwGetCurrentContext()) {
      return nullptr;
    }

    return GrGLMakeAssembledInterface(nullptr, glfw_get);
  }

  Window::Window(int width, int height, const std::string& name)
  {
    if (!glfwInit()) {
      // LOG_F(ERROR, "Failed to init GLFW.");
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //(uncomment to enable correct color spaces) glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
    glfwWindowHint(GLFW_STENCIL_BITS, 0);
    // glfwWindowHint(GLFW_ALPHA_BITS, 0);
    glfwWindowHint(GLFW_DEPTH_BITS, 0);

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

  SkPoint Window::cursor_pos()
  {
    double x, y;
    glfwGetCursorPos(_glfw_win, &x, &y);
    return SkPoint::Make(x, y);
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


  SkiaWindow::SkiaWindow(int width, int height, const std::string& name) : Window(width, height, name)
  {
    make_current();
    auto interface = GrGLMakeNativeInterface_glfw();
    context_ = GrContext::MakeGL(interface);
    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = 0;
    fbInfo.fFormat = GL_RGBA8;
    GrBackendRenderTarget backendRenderTarget(width, height,
                                              0, // sample count
                                              0, // stencil bits
                                              fbInfo);

    surface_ = SkSurface::MakeFromBackendRenderTarget(context_.get(), backendRenderTarget, kBottomLeft_GrSurfaceOrigin,
                                                      kN32_SkColorType, nullptr, nullptr);
    if (!surface_) {
      SkDebugf("SkSurface::MakeRenderTarget returned null\n");
      return;
    }
    canvas_ = surface_->getCanvas();
  }

  SkiaWindow::~SkiaWindow() noexcept {}

  SkCanvas& SkiaWindow::canvas()
  {
    return *canvas_;
  }

  void SkiaWindow::begin_frame()
  {
    make_current();
  }

  void SkiaWindow::end_frame()
  {
    context_->flush();
    swap_buffers();
  }
} // namespace otto::glfw

#include "testing.t.hpp"

using namespace otto;

TEST_CASE ("Graphics test") {
  glfw::SkiaWindow win = glfw::SkiaWindow(320, 240, "OTTO Test");

  glfwSetTime(0);
  double t, spent;

  while (!win.should_close()) {
    t = glfwGetTime();
    win.begin_frame();
    SkPaint paint;
    paint.setColor(SK_ColorWHITE);
    win.canvas().drawPaint(paint);
    paint.setColor(SK_ColorBLUE);
    win.canvas().drawRect({0, 0, 20, 20}, paint);
    win.end_frame();

    glfwPollEvents();

    spent = glfwGetTime() - t;

    std::this_thread::sleep_for(std::chrono::milliseconds(int(1000.0 / 120 - spent * 1000)));
  }
}

#if false
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

    glfw::SkiaWindow main_win(vg::width, vg::height, "OTTO");

    board::Emulator* const emulator = dynamic_cast<board::Emulator*>(&services::Controller::current());

    vg::Size canvas_size = {vg::width, vg::height};
    float scale = 1;

    if (emulator) {
      main_win.set_window_aspect_ration(emulator->size.w, emulator->size.h);
      main_win.set_window_size(emulator->size.w, emulator->size.h);
      canvas_size = emulator->size;
      main_win.mouse_button_callback = [&](glfw::Button b, glfw::Action a, glfw::Modifiers) {
        if (a == glfw::Action::press)
          emulator->handle_click(main_win.cursor_pos() / scale, board::Emulator::ClickAction::down);
        if (a == glfw::Action::release)
          emulator->handle_click(main_win.cursor_pos() / scale, board::Emulator::ClickAction::up);
      };
      main_win.scroll_callback = [&](double x, double y) { emulator->handle_scroll(main_win.cursor_pos() / scale, y); };
    } else {
      main_win.set_window_aspect_ration(4, 3);
      main_win.set_window_size_limits(320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);
    }

    main_win.key_callback = [](auto&& action, auto&& mods, auto&& key) {
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
#endif

// kak: other_file=../include/board/ui/glfw_ui.hpp
