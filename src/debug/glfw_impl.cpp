#include "ui.hpp"

#ifdef DEBUG_UI

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>
#include <algorithm>

#include <plog/Log.h>

// Use GL3 on OSX, GLES3 on linux
#ifdef __APPLE__

#define GLFW_INCLUDE_GLCOREARB
#define NANOVG_GL3_IMPLEMENTATION
#define TOP1_NVG_CREATE nvgCreateGL3
#define TOP1_NVG_DELETE nvgDeleteGL3
#define TOP1_INSERT_GLFW_HINTS                                     \
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);    \
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);   \
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);             \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                   \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#else // ifdef __APPLE__

#define GLFW_INCLUDE_ES3
#define NANOVG_GLES3_IMPLEMENTATION
#define TOP1_NVG_CREATE nvgCreateGLES3
#define TOP1_NVG_DELETE nvgDeleteGLES3
#define TOP1_INSERT_GLFW_HINTS                                     \
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);             \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                   \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

#endif // ifdef __APPLE__

#include <NanoCanvas.h>

// C APIs. Include last
#include <GLFW/glfw3.h>
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

namespace top1::debug::ui {

  namespace {

    void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
      using namespace ui;
      if (action == GLFW_PRESS) {
      } else if (action == GLFW_REPEAT) {
      } else if (action == GLFW_RELEASE) {
      }
    }
  }

  void error_callback(int error, const char* description) {
    LOGF << description;
  }

  void MainUI::mainRoutine() {
    MainUI& self = Globals::ui;
    GLFWwindow* window;
    NVGcontext* vg = NULL;
    double prevt = 0;

    if (!glfwInit()) {
      LOGE << ("Failed to init GLFW.");
    }

    glfwSetErrorCallback(error_callback);

    TOP1_INSERT_GLFW_HINTS

    window = glfwCreateWindow(drawing::WIDTH, drawing::HEIGHT, "TOP-1", NULL, NULL);
    if (!window) {
      glfwTerminate();
      return;
    }

    glfwSetWindowAspectRatio(window, 4, 3);
    glfwSetWindowSizeLimits(window, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetKeyCallback(window, key);

    glfwMakeContextCurrent(window);

    vg = TOP1_NVG_CREATE(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (vg == NULL) {
      printf("Could not init nanovg.\n");
      return;
    }

    glfwSwapInterval(0);

    glfwSetTime(0);
    prevt = glfwGetTime();

    drawing::Canvas canvas(vg, drawing::WIDTH, drawing::HEIGHT);
    drawing::initUtils(canvas);

    LOGD << "Opening GLFW Window";

    while (!glfwWindowShouldClose(window) && Globals::running())
      {
        double mx, my, t, dt, spent;
        int winWidth, winHeight;
        int fbWidth, fbHeight;
        float pxRatio;
        float scale;

        t = glfwGetTime();
        dt = t - prevt;
        prevt = t;

        glfwGetCursorPos(window, &mx, &my);
        glfwGetWindowSize(window, &winWidth, &winHeight);
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        // Calculate pixel ration for hi-dpi devices.
        pxRatio = (float)fbWidth / (float)winWidth;
        scale = std::min((float)winWidth/(float)drawing::WIDTH, (float)winHeight/(float)drawing::HEIGHT);
        canvas.setSize(winWidth, winHeight);

        // Update and render
        glViewport(0, 0, fbWidth, fbHeight);

        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        canvas.clearColor(drawing::Colours::Black);
        canvas.begineFrame(winWidth, winHeight);

        canvas.scale(scale, scale);
        self.draw(canvas);

        canvas.endFrame();

        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);

        glfwPollEvents();

        spent = glfwGetTime() - t;

        std::this_thread::sleep_for(
                                    std::chrono::milliseconds(int(100/6 - spent*1000)));

      }

    TOP1_NVG_DELETE(vg);

    glfwTerminate();

    Globals::exit();
  }

} // top1::ui


#endif // DEBUG_UI
