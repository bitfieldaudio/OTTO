#include "board/ui/glfw_ui.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include <GrBackendSurface.h>
#include <SkCanvas.h>
#include <SkColorSpace.h>
#include <SkFont.h>
#include <SkSurface.h>
#include <blockingconcurrentqueue.h>
#include <gl/GrGLAssembleInterface.h>
#include <gl/GrGLInterface.h>

#include "lib/util/exception.hpp"
#include "lib/util/thread.hpp"

#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"

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
    context_ = GrDirectContext::MakeGL(interface);
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

namespace otto::drivers {

  using namespace services;

  void handle_keyevent(glfw::Action action, glfw::Modifiers mods, glfw::Key key, IInputHandler& handler);

  struct GlfwGraphicsDriver final : IGraphicsDriver {
    void run(std::function<bool(SkCanvas&)> f) override
    {
      otto::glfw::SkiaWindow win = {320, 240, "OTTO"};
      win.key_callback = [this](glfw::Action a, glfw::Modifiers m, glfw::Key k) { key_callback(a, m, k); };
      win.show(std::move(f));
    }

  private:
    void key_callback(glfw::Action a, glfw::Modifiers m, glfw::Key k) noexcept;
  };

  std::unique_ptr<IGraphicsDriver> IGraphicsDriver::make_default()
  {
    return std::make_unique<GlfwGraphicsDriver>();
  }

  struct GlfwMCUPort final : LocalMCUPort {
    static GlfwMCUPort* instance;
    GlfwMCUPort()
    {
      instance = this;
    }
    ~GlfwMCUPort()
    {
      instance = nullptr;
    }
    GlfwMCUPort(const GlfwMCUPort&) = delete;
    GlfwMCUPort(GlfwMCUPort&&) = delete;
  };

  GlfwMCUPort* GlfwMCUPort::instance = nullptr;

  std::unique_ptr<MCUPort> MCUPort::make_default()
  {
    return std::make_unique<GlfwMCUPort>();
  }

  void GlfwGraphicsDriver::key_callback(glfw::Action a, glfw::Modifiers m, glfw::Key k) noexcept
  {
    if (auto* port = GlfwMCUPort::instance; //
        port != nullptr) {
      handle_keyevent(a, m, k, *port);
    }
  }

} // namespace otto::drivers
