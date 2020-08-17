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

#include "./egl_connection.hpp"
#include "./egl_deps.hpp"
#include "./fbcp.hpp"

#define GR_GL_RGB8 0x8051
#define GR_GL_RGBA8 0x8058

namespace otto::board::ui {

  struct EGLUIConfig : Config<EGLUIConfig> {
    static constexpr util::string_ref name = "EGLGraphics";
    int fps = 30;
    bool framebuffer_copy = true;

    DECL_VISIT(fps, framebuffer_copy)
  };

  void show_ui(const EGLUIConfig& conf, util::callable<bool(SkCanvas&)> auto&& f)
  {
    EGLConnection egl;
    egl.init();

    auto width = 320, height = 240;

    auto interface = GrGLMakeNativeInterface();
    sk_sp<GrContext> context = GrContext::MakeGL(interface);
    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = 0;
    fbInfo.fFormat = GR_GL_RGB8;
    auto backendRenderTarget = GrBackendRenderTarget(width, height, 0, 0, fbInfo);

    auto surface = SkSurface::MakeFromBackendRenderTarget(
      context.get(), backendRenderTarget, kBottomLeft_GrSurfaceOrigin, kRGB_888x_SkColorType, nullptr, nullptr);

    auto* canvas = surface->getCanvas();

    using std::chrono::duration;
    using std::chrono::nanoseconds;
    using clock = std::chrono::high_resolution_clock;
    auto one_second = 1e9f;

    auto waitTime = nanoseconds(int(one_second / conf.fps));
    auto t0 = clock::now();

    float fps = 0;
    duration<double> lastFrameTime;

    std::optional<RpiFBCP> fbcp = std::nullopt;
    if (conf.framebuffer_copy) fbcp.emplace(egl.eglData);
    if (fbcp) fbcp->init();

    bool run = true;

    while (run) {
      t0 = clock::now();

      // Update and render
      egl.beginFrame();
      canvas->clear(SK_ColorBLACK);
      run = std::invoke(f, *canvas);
      context->flush();
      egl.endFrame();

      if (fbcp) fbcp->copy();

      lastFrameTime = clock::now() - t0;
      std::this_thread::sleep_for(waitTime - lastFrameTime);

      auto ms = std::chrono::duration_cast<nanoseconds>(lastFrameTime).count();
      fps = one_second / ms;
    }

    egl.exit();
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
