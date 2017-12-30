#if OTTO_UI_GLFW

#include <chrono>
#include "core/globals.hpp"
#include "core/ui/mainui.hpp"
#include "debug/ui.hpp"

#define NANOVG_GL3_IMPLEMENTATION
#define OTTO_NVG_CREATE nvgCreateGL3
#define OTTO_NVG_DELETE nvgDeleteGL3

// C APIs. Include last
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <nanovg_gl.h>

namespace otto::ui {
  namespace {
    Key keyboardKey(int xKey, int mods)
    {
      switch (xKey) {
        // Rotaries
      case GLFW_KEY_Q:
        if (mods & GLFW_MOD_CONTROL) return Key::blue_click;
        return Key::blue_up;
      case GLFW_KEY_A:
        if (mods & GLFW_MOD_CONTROL) return Key::blue_click;
        return Key::blue_down;
      case GLFW_KEY_W:
        if (mods & GLFW_MOD_CONTROL) return Key::green_click;
        return Key::green_up;
      case GLFW_KEY_S:
        if (mods & GLFW_MOD_CONTROL) return Key::green_click;
        return Key::green_down;
      case GLFW_KEY_E:
        if (mods & GLFW_MOD_CONTROL) return Key::white_click;
        return Key::white_up;
      case GLFW_KEY_D:
        if (mods & GLFW_MOD_CONTROL) return Key::white_click;
        return Key::white_down;
      case GLFW_KEY_R:
        if (mods & GLFW_MOD_CONTROL) return Key::red_click;
        return Key::red_up;
      case GLFW_KEY_F:
        if (mods & GLFW_MOD_CONTROL) return Key::red_click;
        return Key::red_down;

      case GLFW_KEY_LEFT: return Key::left;
      case GLFW_KEY_RIGHT:
        return Key::right;

        // Tapedeck
      case GLFW_KEY_SPACE: return Key::play;
      case GLFW_KEY_Z: return Key::rec;
      case GLFW_KEY_F1: return Key::track_1;
      case GLFW_KEY_F2: return Key::track_2;
      case GLFW_KEY_F3: return Key::track_3;
      case GLFW_KEY_F4:
        return Key::track_4;

        // Numbers
      case GLFW_KEY_T:
        if (mods & GLFW_MOD_CONTROL)
          return Key::tape;
        else
          break;
      case GLFW_KEY_Y:
        if (mods & GLFW_MOD_CONTROL)
          return Key::mixer;
        else
          break;
      case GLFW_KEY_U:
        if (mods & GLFW_MOD_CONTROL)
          return Key::synth;
        else
          break;
      case GLFW_KEY_G:
        if (mods & GLFW_MOD_CONTROL)
          return Key::metronome;
        else
          break;
      case GLFW_KEY_H:
        if (mods & GLFW_MOD_CONTROL)
          return Key::sampler;
        else
          break;
      case GLFW_KEY_J:
        if (mods & GLFW_MOD_CONTROL)
          return Key::drums;
        else
          break;

      case GLFW_KEY_L: return Key::loop;
      case GLFW_KEY_I: return Key::loop_in;
      case GLFW_KEY_O: return Key::loop_out;

      case GLFW_KEY_X: return Key::cut;
      case GLFW_KEY_C:
        if (mods & GLFW_MOD_CONTROL)
          return Key::lift;
        else
          break;
      case GLFW_KEY_V:
        if (mods & GLFW_MOD_CONTROL) return Key::drop;

      case GLFW_KEY_LEFT_SHIFT:
      case GLFW_KEY_RIGHT_SHIFT: return Key::shift;

      default: return Key::none;
      }
      return Key::none;
    }

    void key(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      using namespace ui;
      Key k        = keyboardKey(key, mods);
      if (action == GLFW_PRESS) {
        impl::keypress(k);
      } else if (action == GLFW_REPEAT) {
        switch (k) {
        case Key::red_up:
        case Key::red_down:
        case Key::blue_up:
        case Key::blue_down:
        case Key::white_up:
        case Key::white_down:
        case Key::green_up:
        case Key::green_down:
        case Key::left:
        case Key::right: impl::keypress(k);
        default: break;
        }
      } else if (action == GLFW_RELEASE) {
        impl::keyrelease(k);
      }
    }

    void error_callback(int error, const char* description)
    {
      LOG_F(FATAL, "GLFW UI: {}", description);
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

    otto::debug::ui::init();

    GLFWwindow* window =
      glfwCreateWindow(vg::WIDTH, vg::HEIGHT, "OTTO", NULL, NULL);
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

    vg::Canvas canvas(vg, vg::WIDTH, vg::HEIGHT);
    vg::initUtils(canvas);

    LOG_F(INFO, "Opening GLFW Window");

    struct DbgInfo : debug::Info {
      float FPS_limit = 60.f;
      util::ringbuffer<std::pair<float, float>, 512> fps_history;

      void draw() override
      {
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
      scale   = std::min((float) winWidth / (float) vg::WIDTH,
                       (float) winHeight / (float) vg::HEIGHT);
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

      otto::debug::ui::draw_frame();

      spent = glfwGetTime() - t;

      std::this_thread::sleep_for(
        std::chrono::milliseconds(int(1000 / info.FPS_limit - spent * 1000)));

      info.fps_history.push({ImGui::GetIO().Framerate, 1.f / spent});
    }

    OTTO_NVG_DELETE(vg);

    glfwTerminate();

    global::exit(global::ErrorCode::ui_closed);
  }
} // namespace otto::ui

#endif // OTTO_UI_GLFW
