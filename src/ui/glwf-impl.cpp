#define GLFW_INCLUDE_ES3
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include <nanovg/nanovg.h>
#define NANOVG_GLES3_IMPLEMENTATION
#include <nanovg/nanovg_gl.h>
#include <nanovg/nanovg_gl_utils.h>

#include "base.h"
#include "mainui.h"
#include "utils.h"
#include "../globals.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

static void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
  
}

static void render_routine() {
  MainUI& self = MainUI::getInstance();

  GLFWwindow* window;
	NVGcontext* vg = NULL;
	double prevt = 0;

	if (!glfwInit()) {
		printf("Failed to init GLFW.");
	}

	//glfwSetErrorCallback(errorcb);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(drawing::WIDTH, drawing::HEIGHT, "TOP-1", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return;
	}

	glfwSetKeyCallback(window, key);

	glfwMakeContextCurrent(window);

	vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
	if (vg == NULL) {
		printf("Could not init nanovg.\n");
		return;
	}

	glfwSwapInterval(0);

	glfwSetTime(0);
	prevt = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		double mx, my, t, dt;
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		float pxRatio;

		t = glfwGetTime();
		dt = t - prevt;
		prevt = t;

		glfwGetCursorPos(window, &mx, &my);
		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
		// Calculate pixel ration for hi-dpi devices.
		pxRatio = (float)fbWidth / (float)winWidth;

		// Update and render
		glViewport(0, 0, fbWidth, fbHeight);

    glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

    self.draw(vg);

		nvgEndFrame(vg);

		glEnable(GL_DEPTH_TEST);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	nvgDeleteGLES3(vg);

	glfwTerminate();

  GLOB.running = false;
}

void MainUI::mainRoutine() {
  auto& self = getInstance();
  std::thread renderThread = std::thread(render_routine);

  while (GLOB.running);
}
