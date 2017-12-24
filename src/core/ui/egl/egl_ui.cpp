#if OTTO_UI_EGL

#include <fcntl.h>
#include <sys/mman.h>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <string>
#include <thread>

#include "core/globals.hpp"
#include "core/ui/mainui.hpp"

#define NANOVG_GLES2_IMPLEMENTATION

#include "./egl_connection.hpp"
#include "./egl_deps.hpp"
#include "./rpi_input.hpp"

static nlohmann::json config = {{"FPS", 60.f}, {"Debug", true}};

namespace otto::ui {
  void main_ui_loop()
  {
    EGLConnection egl;
    egl.init();

    NVGcontext* vg =
      nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (vg == NULL) {
      LOGF << ("Could not init nanovg.\n");
      global::exit(global::ErrorCode::graphics_error);
      return;
    }

    vg::Canvas canvas(vg, vg::WIDTH, vg::HEIGHT);
    vg::initUtils(canvas);
    float scale = std::min(egl.eglData.width / float(vg::WIDTH),
                           egl.eglData.height / float(vg::HEIGHT));
    canvas.setSize(egl.eglData.width, egl.eglData.height);

    using std::chrono::duration;
    using std::chrono::nanoseconds;
    using clock     = std::chrono::high_resolution_clock;
    auto one_second = 1e9f;

    auto targetFPS = config["FPS"].get<float>();
    auto waitTime  = nanoseconds(int(one_second / targetFPS));
    auto t0        = clock::now();

    bool showFps = config["Debug"];
    float fps;
    duration<double> lastFrameTime;

    while (global::running()) {
      otto::ui::read_keyboard();
      t0 = clock::now();

      // Update and render
      egl.beginFrame();
      canvas.clearColor(vg::Colours::Black);
      canvas.begineFrame(egl.eglData.width, egl.eglData.height);
      canvas.scale(scale, scale);
      ui::impl::draw_frame(canvas);

      if (showFps) {
        canvas.beginPath();
        canvas.font(15);
        canvas.font(vg::Fonts::Norm);
        canvas.fillStyle(vg::Colours::White);
        canvas.textAlign(vg::TextAlign::Left, vg::TextAlign::Baseline);
        canvas.fillText(fmt::format("{:.2f} FPS", fps), {0, vg::HEIGHT});
      }

      canvas.endFrame();
      egl.endFrame();

      lastFrameTime = clock::now() - t0;
      std::this_thread::sleep_for(waitTime - lastFrameTime);

      auto ms = std::chrono::duration_cast<nanoseconds>(lastFrameTime).count();
      fps     = one_second / ms;
    }

    nvgDeleteGLES2(vg);

    egl.exit();

    global::exit(global::ErrorCode::ui_closed);
  }
} // namespace otto::ui

#endif // OTTO_UI_EGL