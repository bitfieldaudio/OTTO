#include "board/ui/glfw_ui.hpp"

#include <GrBackendSurface.h>
#include <GrContext.h>
#include <SkCanvas.h>
#include <SkColorSpace.h>
#include <SkFont.h>
#include <SkSurface.h>
#include <gl/GrGLAssembleInterface.h>
#include <gl/GrGLInterface.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "app/services/logic_thread.hpp"
#include "lib/util/exception.hpp"
#include "lib/util/thread.hpp"

#include "app/services/controller.hpp"
#include "app/services/impl/graphics.hpp"

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
      LOGF("Failed to init GLFW.");
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
        win->mouse_button_callback(Button{button}, Action{action}, Modifiers{mods});
      }
    });

    glfwSetScrollCallback(_glfw_win, [](GLFWwindow* window, double x, double y) {
      if (auto* win = get_for(window); win && win->mouse_button_callback) {
        win->scroll_callback(x, y);
      }
    });

    glfwSetKeyCallback(_glfw_win, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      if (auto* win = get_for(window); win && win->key_callback) {
        win->key_callback(Action{action}, Modifiers{mods}, Key{key});
      }
    });

    glfwSetCharCallback(_glfw_win, [](GLFWwindow* window, unsigned ch) {
      if (auto* win = get_for(window); win && win->char_callback) {
        win->char_callback((char) ch);
      }
    });

    make_current();
  }

  Window::~Window() noexcept
  {
    glfwDestroyWindow(_glfw_win);
  }

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

  void Window::close()
  {
    glfwSetWindowShouldClose(_glfw_win, true);
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
    canvas_->clear(SK_ColorBLACK);
  }

  void SkiaWindow::end_frame()
  {
    context_->flush();
    swap_buffers();
  }
} // namespace otto::glfw

namespace otto::board {

  void handle_keyevent(glfw::Action action,
                       glfw::Modifiers mods,
                       glfw::Key key,
                       itc::IExecutor& executor,
                       InputHandler& handler);

  using namespace services;

  struct GlfwGraphics final : GraphicsImpl,
                              core::ServiceAccessor<Runtime>,
                              core::UnsafeServiceAccessor<LogicThread, Controller> {
    GlfwGraphics()
      : thread_([this] {
          otto::glfw::SkiaWindow win = {320, 240, "OTTO"};
          win.key_callback = [this](glfw::Action a, glfw::Modifiers m, glfw::Key k) { key_callback(a, m, k); };
          win.show([this](SkCanvas& ctx) { return loop_function(ctx); });
          service<Runtime>().request_stop();
          exit_thread();
        })
    {}

  private:
    void key_callback(glfw::Action a, glfw::Modifiers m, glfw::Key k) noexcept;
    std::jthread thread_;
  };

  core::ServiceHandle<Graphics> make_graphics()
  {
    return core::make_handle<GlfwGraphics>();
  }

  struct GlfwController final : Controller, core::ServiceAccessor<LogicThread> {
    void set_input_handler(InputHandler& handler) override
    {
      handler_ = &handler;
    }

    void set_led_color(LED led, LEDColor) override {}

  private:
    friend GlfwGraphics;
    InputHandler* handler_ = nullptr;
  };

  void GlfwGraphics::key_callback(glfw::Action a, glfw::Modifiers m, glfw::Key k) noexcept
  {
    if (auto* gc = dynamic_cast<GlfwController*>(service_unsafe<Controller>()); //
        gc != nullptr) {
      if (gc->handler_ == nullptr) return;
      handle_keyevent(a, m, k, service_unsafe<LogicThread>()->executor(), *gc->handler_);
    }
  }

  core::ServiceHandle<Controller> make_controller()
  {
    return core::make_handle<GlfwController>();
  }

} // namespace otto::board

// kak: other_file=../include/board/ui/glfw_ui.hpp
