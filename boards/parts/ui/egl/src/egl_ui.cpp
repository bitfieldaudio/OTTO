#include <fcntl.h>
#include <sys/mman.h>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <string>
#include <thread>

#include "core/ui/canvas.hpp"
#include "core/ui/vector_graphics.hpp"
#include "services/ui_manager.hpp"

#define NANOVG_GLES2_IMPLEMENTATION

#include "./egl_connection.hpp"
#include "./egl_deps.hpp"
#include "./fbcp.hpp"
#include "board/ui/egl_ui_manager.hpp"

static nlohmann::json config = {{"FPS", 30.f}, {"Debug", false}};

namespace otto::services {

  using namespace core::ui;
  using namespace board::ui;

  void EGLUIManager::main_ui_loop()
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

    NVGcontext* nvg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (nvg == NULL) {
      LOGF("Could not init nanovg.\n");
      Application::current().exit(Application::ErrorCode::graphics_error);
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
    float fps = 0;
    duration<double> lastFrameTime;

//    std::thread kbd_thread = std::thread([this] { read_keyboard(); });

    while (Application::current().running()) {
      t0 = clock::now();

      Controller::current().flush_leds();

      // Update and render
      egl.beginFrame();
      canvas.clearColor(vg::Colours::Black);
      canvas.beginFrame(egl.draw_size.width, egl.draw_size.height);
      canvas.scale(xscale, yscale);
      draw_frame(canvas);

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

//    kbd_thread.join();
  }
} // namespace otto::services
