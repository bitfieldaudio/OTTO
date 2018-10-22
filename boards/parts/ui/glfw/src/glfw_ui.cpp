#include <chrono>
#include <thread>

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "services/debug_ui.hpp"
#include "services/logger.hpp"
#include "services/ui.hpp"

#define NANOVG_GL3_IMPLEMENTATION
#define OTTO_NVG_CREATE nvgCreateGL3
#define OTTO_NVG_DELETE nvgDeleteGL3

#include "board/ui/keys.hpp"

// C APIs. Include last
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <nanovg_gl.h>

namespace otto::service::ui {

  using namespace core::ui;

  namespace {
    void key(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      board::ui::handle_keyevent(board::ui::Action{action}, board::ui::Modifiers{mods}, board::ui::Key{key});
    }

    void error_callback(int error, const char* description)
    {
      LOG_F(ERROR, "GLFW UI: {}", description);
    }

  } // namespace

  void main_ui_loop()
  {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
      LOG_F(ERROR, "Failed to init GLFW.");
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    debug_ui::init();

    GLFWwindow* window =
      glfwCreateWindow(vg::width, vg::height, "OTTO", NULL, NULL);
    if (!window) {
      glfwTerminate();
      return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gl3wInit();

    glfwSetWindowAspectRatio(window, 4, 3);
    glfwSetWindowSizeLimits(window, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetKeyCallback(window, key);

    NVGcontext* vg =
      OTTO_NVG_CREATE(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (vg == NULL) {
      printf("Could not init nanovg.\n");
      return;
    }

    vg::Canvas canvas(vg, vg::width, vg::height);
    vg::initUtils(canvas);

    LOG_F(INFO, "Opening GLFW Window");

    struct DbgInfo : debug_ui::Info {
      float FPS_limit = 60.f;
      util::ringbuffer<std::pair<float, float>, 512> fps_history;

      void draw() override
      {
#if OTTO_DEBUG_UI
        ImGui::Begin("Graphics");
        ImGui::Text("FPS limit");
        ImGui::SliderFloat("", &FPS_limit, 0.f, 300.f);
        auto fps = fps_history.front();
        ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / fps.first,
                    fps.first);
        ImGui::Text("FPS History");
        ImGui::PlotLines("",
                         [](void* self, int n) {
                           return ((DbgInfo*) self)->fps_history[n].first;
                         },
                         this, fps_history.size(), 0, nullptr, 0, 120,
                         ImVec2(0, 80));
        ImGui::Text("Percentage of time used rendering");
        ImGui::PlotLines("",
                         [](void* self, int n) {
                           auto&& el = ((DbgInfo*) self)->fps_history[n];
                           return el.first / el.second * 100.f;
                         },
                         this, fps_history.size(), 0, nullptr, 0, 0,
                         ImVec2(0, 80));
        ImGui::End();
#endif
      }
    } info;

    glfwSetTime(0);

    double mx, my, t, spent;
    while (!glfwWindowShouldClose(window) && global::running()) {
      int winWidth, winHeight;
      int fbWidth, fbHeight;
      float scale;

      t = glfwGetTime();

      glfwGetCursorPos(window, &mx, &my);
      glfwGetWindowSize(window, &winWidth, &winHeight);
      glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

      // Calculate pixel ration for hi-dpi devices.
      scale = std::min((float) winWidth / (float) vg::width,
                       (float) winHeight / (float) vg::height);
      canvas.setSize(winWidth, winHeight);

      // Update and render
      glViewport(0, 0, fbWidth, fbHeight);

      glClearColor(0, 0, 0, 0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
              GL_STENCIL_BUFFER_BIT);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_CULL_FACE);
      glDisable(GL_DEPTH_TEST);

      canvas.clearColor(vg::Colours::Black);
      canvas.begineFrame(winWidth, winHeight);

      canvas.scale(scale, scale);
      ui::impl::draw_frame(canvas);

      canvas.endFrame();

      glEnable(GL_DEPTH_TEST);

      glfwSwapBuffers(window);

      glfwPollEvents();
      ui::impl::flush_events();

      debug_ui::draw_frame();

      spent = glfwGetTime() - t;

      std::this_thread::sleep_for(
        std::chrono::milliseconds(int(1000 / info.FPS_limit - spent * 1000)));

      #if OTTO_DEBUG_UI
      info.fps_history.push({ImGui::GetIO().Framerate, 1.f / spent});
      #endif
    }

    OTTO_NVG_DELETE(vg);

    glfwTerminate();

    global::exit(global::ErrorCode::ui_closed);
  }
} // namespace otto::service::ui
