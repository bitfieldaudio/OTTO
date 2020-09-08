#include <fcntl.h>
#include <sys/mman.h>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <functional>
#include <string>
#include <thread>

#include <GrBackendSurface.h>
#include <GrContext.h>
#include <SkCanvas.h>
#include <SkColorSpace.h>
#include <SkFont.h>
#include <SkSurface.h>
#include <gl/GrGLAssembleInterface.h>
#include <gl/GrGLInterface.h>

#include <json.hpp>

#include "app/services/config.hpp"
#include "app/services/impl/graphics.hpp"
#include "lib/util/concepts.hpp"

#include "./egl_deps.hpp"

#define GR_GL_RGB8 0x8051
#define GR_GL_RGBA8 0x8058

namespace otto::board::ui {

  struct EGLUIConfig : Config<EGLUIConfig> {
    static constexpr util::string_ref name = "EGLGraphics";
    int fps = 30;

    DECL_VISIT(fps)
  };

  struct CubeState {
    uint32_t screen_width = 0;
    uint32_t screen_height = 0;
    EGLDisplay display = nullptr;
    EGLSurface surface = nullptr;
    EGLContext context = nullptr;

    ~CubeState()
    {
      exit();
    };

    void init();
    void exit();
  };

  void CubeState::init()
  {
    int32_t success = 0;
    EGLBoolean result;
    EGLint num_config;

    static EGL_DISPMANX_WINDOW_T nativewindow;

    DISPMANX_ELEMENT_HANDLE_T dispman_element;
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;

    static const EGLint attribute_list[] = {EGL_RED_SIZE,
                                            8,
                                            EGL_GREEN_SIZE,
                                            8,
                                            EGL_BLUE_SIZE,
                                            8,
                                            EGL_ALPHA_SIZE,
                                            8,
                                            EGL_DEPTH_SIZE,
                                            0,
                                            EGL_STENCIL_SIZE,
                                            8,
                                            EGL_SURFACE_TYPE,
                                            EGL_WINDOW_BIT,
                                            EGL_RENDERABLE_TYPE,
                                            EGL_OPENGL_ES2_BIT,
                                            EGL_NONE};

    const EGLint context_attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

    EGLConfig config;

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(display != EGL_NO_DISPLAY);

    result = eglInitialize(display, NULL, NULL);
    assert(EGL_FALSE != result);

    result = eglChooseConfig(display, attribute_list, &config, 1, &num_config);
    assert(EGL_FALSE != result);

    result = eglBindAPI(EGL_OPENGL_ES_API);
    assert(EGL_FALSE != result);

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attrib_list);
    assert(context != EGL_NO_CONTEXT);

    success = graphics_get_display_size(0, &screen_width, &screen_height);
    assert(success >= 0);

    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.width = screen_width;
    dst_rect.height = screen_height;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = screen_width << 16;
    src_rect.height = screen_height << 16;

    dispman_display = vc_dispmanx_display_open(0 /* LCD */);
    dispman_update = vc_dispmanx_update_start(0);

    dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0, &dst_rect, 0, &src_rect,
                                              DISPMANX_PROTECTION_NONE, 0, 0, DISPMANX_NO_ROTATE);

    nativewindow.element = dispman_element;
    nativewindow.width = screen_width;
    nativewindow.height = screen_height;
    vc_dispmanx_update_submit_sync(dispman_update);

    surface = eglCreateWindowSurface(display, config, &nativewindow, NULL);
    assert(surface != EGL_NO_SURFACE);

    result = eglMakeCurrent(display, surface, surface, context);
    assert(EGL_FALSE != result);
  }

  void CubeState::exit()
  {
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(display, surface);
    eglDestroyContext(display, context);
    eglTerminate(display);
    bcm_host_deinit();
  }

  void show_ui(const EGLUIConfig& conf, util::callable<bool(SkCanvas&)> auto&& f)
  {
    bcm_host_init();
    CubeState state;
    state.init();

    glViewport(0, 0, (GLsizei) state.screen_width, (GLsizei) state.screen_height);
    glClearColor(1, 0, 0, 1);
    glClearStencil(0);
    glStencilMask(0xffffffff);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    sk_sp<const GrGLInterface> interface(GrGLCreateNativeInterface());
    sk_sp<GrContext> grContext(GrContext::MakeGL(interface));
    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = 0;
    fbInfo.fFormat = 0x8051;
    // Screen sizes are gathered from graphics driver
    GrBackendRenderTarget desc(state.screen_width, state.screen_height, 0, 8, fbInfo);

    SkSurface* surface = SkSurface::MakeFromBackendRenderTarget(grContext.release(), desc, kBottomLeft_GrSurfaceOrigin,
                                                                SkColorType::kRGB_888x_SkColorType, nullptr, nullptr)
                           .release();
    SkCanvas* canvas = surface->getCanvas();

    // Timing setup
    using std::chrono::duration;
    using std::chrono::nanoseconds;
    using clock = std::chrono::high_resolution_clock;
    auto one_second = 1e9f;

    auto waitTime = nanoseconds(int(one_second / conf.fps));
    auto t0 = clock::now();

    float fps = 0;
    duration<double> lastFrameTime;

    bool run = true;

    while (run) {
      t0 = clock::now();

      // Update and render
      canvas->clear(SK_ColorBLACK);
      run = std::invoke(f, *canvas);
      canvas->flush();
      eglSwapBuffers(state.display, state.surface);

      lastFrameTime = clock::now() - t0;
      std::this_thread::sleep_for(waitTime - lastFrameTime);

      auto ms = std::chrono::duration_cast<nanoseconds>(lastFrameTime).count();
      fps = one_second / ms;
    }
  }

} // namespace otto::board::ui

using namespace otto::board::ui;

namespace otto::board {
  struct EGLGraphics final : services::GraphicsImpl, core::ServiceAccessor<services::Runtime> {
    EGLGraphics(EGLUIConfig::Handle c = {})
      : conf(c), thread_([this] {
          show_ui(*conf, [this](SkCanvas& ctx) { return loop_function(ctx); });
          service<services::Runtime>().request_stop();
          exit_thread();
        })
    {}

  private:
    EGLUIConfig::Handle conf;
    std::jthread thread_;
  };

  core::ServiceHandle<services::Graphics> make_graphics()
  {
    return core::make_handle<EGLGraphics>();
  }
} // namespace otto::board


// kak: other_file=../include/board/ui/egl_ui.hpp
