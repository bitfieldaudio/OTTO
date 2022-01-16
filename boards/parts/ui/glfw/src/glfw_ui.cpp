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
      return (GrGLFuncPtr) (static_cast<GrEGLQueryStringFn*>([](void* dpy, int name) -> const char* { return ""; }));
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
      LOGE("Failed to init GLFW.");
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
      if (auto* win = get_for(window); win && win->scroll_callback) {
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

  constexpr int max_scale_factor = 8;

  SkiaWindow::SkiaWindow(int width, int height, const std::string& name)
    : Window(width, height, name), init_size_{static_cast<SkScalar>(width), static_cast<SkScalar>(height)}
  {
    set_window_size_limits(width, height, width * max_scale_factor, height * max_scale_factor);
    make_current();
    auto interface = GrGLMakeNativeInterface_glfw();
    context_ = GrDirectContext::MakeGL(interface);
    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = 0;
    fbInfo.fFormat = GL_RGBA8;
    GrBackendRenderTarget backendRenderTarget(width * max_scale_factor, height * max_scale_factor,
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
    canvas_->save();
    canvas_->clear(SK_ColorBLACK);
    auto [wx, wy] = window_size();
    auto [rx, ry] = init_size_;
    auto scale_x = float(wx) / rx;
    auto scale_y = float(wy) / ry;
    auto scale = std::min(std::min(scale_x, scale_y), float(max_scale_factor));
    canvas().translate(0, ry * max_scale_factor);
    canvas().scale(scale, scale);
    canvas().translate(0, -ry);
  }

  void SkiaWindow::end_frame()
  {
    canvas_->restore();
    context_->flush();
    swap_buffers();
  }
  SkPoint SkiaWindow::skia_cursor_pos()
  {
    auto [px, py] = cursor_pos();
    auto [wx, wy] = window_size();
    auto [rx, ry] = init_size_;
    auto scale_x = float(wx) / rx;
    auto scale_y = float(wy) / ry;
    auto scale = std::min(std::min(scale_x, scale_y), float(max_scale_factor));
    px /= scale;
    py /= scale;
    py -= float(wy) / scale - ry;
    return SkPoint{px, py};
  }
} // namespace otto::glfw

namespace otto::drivers {

  using namespace services;

  void handle_keyevent(glfw::Action action, glfw::Modifiers mods, glfw::Key key, IInputHandler& handler);

  std::unique_ptr<IGraphicsDriver> IGraphicsDriver::make_default()
  {
    return std::make_unique<GlfwGraphicsDriver>();
  }

  std::unique_ptr<MCUPort> MCUPort::make_default(ConfigManager& confman)
  {
    return std::make_unique<GlfwMCUPort>();
  }

  GlfwGraphicsDriver* GlfwGraphicsDriver::instance = nullptr;

  GlfwGraphicsDriver::GlfwGraphicsDriver()
  {
    instance = this;
  }
  GlfwGraphicsDriver::~GlfwGraphicsDriver()
  {
    instance = nullptr;
  }

  void GlfwGraphicsDriver::key_callback(glfw::Action a, glfw::Modifiers m, glfw::Key k) noexcept
  {
    if (auto* port = GlfwMCUPort::instance; //
        port != nullptr) {
      handle_keyevent(a, m, k, *port);
    }
  }

  void GlfwGraphicsDriver::request_size(skia::Vector size)
  {
    requested_size_ = size;
  };

  void GlfwGraphicsDriver::run(std::function<bool(SkCanvas&)> f)
  {
    if (!window) {
      window = glfw::SkiaWindow{static_cast<int>(requested_size_.x()), static_cast<int>(requested_size_.y()), "OTTO"};
      window->set_window_aspect_ration(requested_size_.x(), requested_size_.y());
    }
    window->key_callback = BIND_THIS(key_callback);
    window->show(std::move(f));
  }

  GlfwMCUPort* GlfwMCUPort::instance = nullptr;

  GlfwMCUPort::GlfwMCUPort()
  {
    instance = this;
  }
  GlfwMCUPort::~GlfwMCUPort()
  {
    instance = nullptr;
  }
} // namespace otto::drivers
