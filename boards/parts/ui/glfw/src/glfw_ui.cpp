#include "board/ui/glfw_ui_manager.hpp"

#include <chrono>
#include <thread>

#include "core/ui/vector_graphics.hpp"

#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"

#define NANOVG_GL3_IMPLEMENTATION
#define OTTO_NVG_CREATE nvgCreateGL3
#define OTTO_NVG_DELETE nvgDeleteGL3

#include "board/ui/keys.hpp"

// C APIs. Include last
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <nanovg_gl.h>

namespace otto::services {

  using namespace core::ui;

  static void error_callback(int error, const char* description)
  {
    LOG_F(ERROR, "GLFW UI: {}", description);
  }

  void GLFWUIManager::main_ui_loop()
  {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
      LOG_F(ERROR, "Failed to init GLFW.");
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(vg::width, vg::height, "OTTO", NULL, NULL);
    if (!window) {
      glfwTerminate();
      return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gl3wInit();

    glfwSetWindowAspectRatio(window, 4, 3);
    glfwSetWindowSizeLimits(window, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);

#if GLFW_VERSION_MINOR > 2
    glfwSetKeyboardCallback(window, [](GLFWwindow* window, int key, int scancode, int action,
                                       int mods, const char*, int) {
      board::ui::handle_keyevent(board::ui::Action{action}, board::ui::Modifiers{mods},
                                 board::ui::Key{key});
    });
#else
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      board::ui::handle_keyevent(board::ui::Action{action}, board::ui::Modifiers{mods},
                                 board::ui::Key{key});
    });
#endif

    NVGcontext* vg = OTTO_NVG_CREATE(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (vg == NULL) {
      printf("Could not init nanovg.\n");
      return;
    }

    vg::Canvas canvas(vg, vg::width, vg::height);
    vg::initUtils(canvas);

    LOG_F(INFO, "Opening GLFW Window");

    glfwSetTime(0);

    double mx, my, t, spent;
    while (!glfwWindowShouldClose(window) && Application::current().running()) {
      int winWidth, winHeight;
      int fbWidth, fbHeight;
      float scale;

      t = glfwGetTime();

      glfwGetCursorPos(window, &mx, &my);
      glfwGetWindowSize(window, &winWidth, &winHeight);
      glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

      // Calculate pixel ration for hi-dpi devices.
      scale =
        std::min((float) winWidth / (float) vg::width, (float) winHeight / (float) vg::height);
      canvas.setSize(winWidth, winHeight);

      // Update and render
      glViewport(0, 0, fbWidth, fbHeight);

      glClearColor(0, 0, 0, 0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_CULL_FACE);
      glDisable(GL_DEPTH_TEST);

      canvas.clearColor(vg::Colours::Black);
      canvas.begineFrame(winWidth, winHeight);

      canvas.scale(scale, scale);
      draw_frame(canvas);

      canvas.endFrame();

      glEnable(GL_DEPTH_TEST);

      glfwSwapBuffers(window);

      glfwPollEvents();
      flush_events();

      spent = glfwGetTime() - t;

      std::this_thread::sleep_for(std::chrono::milliseconds(int(1000 / 60 - spent * 1000)));
    }

    OTTO_NVG_DELETE(vg);

    glfwTerminate();

    Application::current().exit(Application::ErrorCode::ui_closed);
  }
} // namespace otto::services
