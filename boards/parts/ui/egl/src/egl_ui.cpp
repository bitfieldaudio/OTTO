#include <fcntl.h>
#include <sys/mman.h>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <string>
#include <thread>

#include "core/globals.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/vector_graphics.hpp"
#include "services/ui.hpp"

#define NANOVG_GLES2_IMPLEMENTATION

#include "./egl_connection.hpp"
#include "./egl_deps.hpp"
#include "./fbcp.hpp"
#include "./rpi_input.hpp"

static nlohmann::json config = {{"FPS", 60.f}, {"Debug", true}};

namespace otto::service::ui {

  using namespace core::ui;
  using namespace board::ui;

  void main_ui_loop()
  {
    EGLConnection egl;
    egl.init();
    #if OTTO_USE_FBCP
    auto fbcp = RpiFBCP{egl.eglData};
    bool use_fbcp = true;
    try {
      fbcp.init();
    } catch (util::exception& e) {
      LOGW("Error starting FBCP: {}", e.what());
      LOGI("If you are using an HDMI screen you probably meant to compile with OTTO_USE_FBCP=OFF");
      LOGI("FBCP has been disabled. /dev/fb0 will not be copied to /dev/fb1");
      use_fbcp = false;
    }
    #endif

    NVGcontext* nvg =
      nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (nvg == NULL) {
      LOGF("Could not init nanovg.\n");
      global::exit(global::ErrorCode::graphics_error);
      return;
    }

    vg::Canvas canvas(nvg, vg::width, vg::height);
    vg::initUtils(canvas);

    // I am unable to resize the EGL display, it is fixed at 720x480px, so this
    // is the temporary fix. Stretch everything to fill the display, and then
    // scale it down in fbcp. Actually only rendering 320x240 should also help
    // performance, so it is definately desired at some point
    float xscale = egl.draw_size.width / float(vg::width);
    float yscale = egl.draw_size.height / float(vg::height);

    canvas.setSize(egl.draw_size.width, egl.draw_size.height);

    using std::chrono::duration;
    using std::chrono::nanoseconds;
    using clock = std::chrono::high_resolution_clock;
    auto one_second = 1e9f;

    auto targetFPS = config["FPS"].get<float>();
    auto waitTime = nanoseconds(int(one_second / targetFPS));
    auto t0 = clock::now();

    bool showFps = config["Debug"];
    float fps;
    duration<double> lastFrameTime;

    std::thread kbd_thread = std::thread(otto::service::ui::read_keyboard);

    while (global::running()) {
      t0 = clock::now();

      otto::service::ui::impl::flush_events();

      // Update and render
      egl.beginFrame();
      canvas.clearColor(vg::Colours::Black);
      canvas.begineFrame(egl.draw_size.width, egl.draw_size.height);
      canvas.scale(xscale, yscale);
      ui::impl::draw_frame(canvas);

      if (showFps) {
        canvas.beginPath();
        canvas.font(15);
        canvas.font(vg::Fonts::Norm);
        canvas.fillStyle(vg::Colours::White);
        canvas.textAlign(vg::TextAlign::Left, vg::TextAlign::Baseline);
        canvas.fillText(fmt::format("{:.2f} FPS", fps), {0, vg::height});
      }

      canvas.endFrame();
      egl.endFrame();

      #if OTTO_USE_FBCP
      if (use_fbcp) fbcp.copy();
      #endif

      lastFrameTime = clock::now() - t0;
      std::this_thread::sleep_for(waitTime - lastFrameTime);

      auto ms = std::chrono::duration_cast<nanoseconds>(lastFrameTime).count();
      fps = one_second / ms;
    }

    nvgDeleteGLES2(nvg);

    egl.exit();

    global::exit(global::ErrorCode::ui_closed);
  }
} // namespace otto::service::ui
