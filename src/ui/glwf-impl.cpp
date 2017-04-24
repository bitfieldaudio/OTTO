#include <GLFW/glfw3.h>
#include <nanovg/nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg/nanovg_gl.h>

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
  std::unique_lock<std::mutex> lock (currently_drawing);
  MainUI& self = MainUI::getInstance();

  GLFWwindow *window = glfwCreateWindow(drawing::WIDTH, drawing::HEIGHT, "TOP-1", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key);

	glfwMakeContextCurrent(window);

	NVGcontext *context =
    nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

	glfwSwapInterval(0);

	initGPUTimer(&gpuTimer);

	glfwSetTime(0);
	double prevt = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		double mx, my, t, dt;
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		float pxRatio;
		int i, n;

		t = glfwGetTime();
		dt = t - prevt;
		prevt = t;

		startGPUTimer(&gpuTimer);

		glfwGetCursorPos(window, &mx, &my);
		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
		// Calculate pixel ration for hi-dpi devices.
		pxRatio = (float)fbWidth / (float)winWidth;

		// Update and render
		glViewport(0, 0, fbWidth, fbHeight);
		if (premult)
			glClearColor(0,0,0,0);
		else
			glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

    self.draw(context);

		nvgEndFrame(vg);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

  GLOB.running = false;
}

void MainUI::mainRoutine() {
  auto& self = getInstance();
  std::thread renderThread = std::thread(render_routine);

  while (GLOB.running);
}
