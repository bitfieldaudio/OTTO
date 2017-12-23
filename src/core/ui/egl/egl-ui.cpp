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

#include "./egl-deps.hpp"
#include "./egl-ui.hpp"

nlohmann::json config = {{"Key repeat", false},
                         {"FPS", 60.f},
                         {"Debug", false},
                         {"Framebuffer", "/dev/fb0"}};

void EGLConnection::fatal(std::string message)
{
  printf((message + "\n").c_str());
  ::exit(1);
}

void EGLConnection::init()
{
  bcm_host_init();

  initEGL();
}

void EGLConnection::initEGL()
{
  eglData.fbfd = open(framebuffer.c_str(), O_RDWR);
  if (!eglData.fbfd) {
    fatal("Error opening framebuffer");
  }

  eglData.fbp =
    (unsigned short*) mmap(0, eglData.screenDatasize, PROT_READ | PROT_WRITE,
                           MAP_SHARED, eglData.fbfd, 0);

  if ((int) eglData.fbp == -1) {
    fatal("Error mapping memory");
  }

  static const EGLint attribute_list[] = {EGL_RED_SIZE,     8,
                                          EGL_GREEN_SIZE,   8,
                                          EGL_BLUE_SIZE,    8,
                                          EGL_ALPHA_SIZE,   8,
                                          EGL_DEPTH_SIZE,   16,
                                          EGL_STENCIL_SIZE, 8,
                                          EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                                          EGL_NONE};

  static const EGLint context_attributes[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                                              EGL_NONE};

  state.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  if (state.display == EGL_NO_DISPLAY) {
    fatal("Error opening EGL display");
  }

  EGLBoolean result = eglInitialize(state.display, nullptr, nullptr);
  if (result == EGL_FALSE) {
    fatal("Error initializing EGL display");
  }

  EGLConfig config;
  result = eglChooseConfig(state.display, attribute_list, &config, 1,
                           &eglData.nConfig);
  if (result == EGL_FALSE) {
    fatal("Error choosing EGL config");
  }

  result = eglBindAPI(EGL_OPENGL_ES_API);
  if (result == EGL_FALSE) {
    fatal("Error binding EGL API");
  }

  state.context =
    eglCreateContext(state.display, config, EGL_NO_CONTEXT, context_attributes);
  if (state.context == EGL_NO_CONTEXT) {
    fatal("Error creating EGL context");
  }

  int success = graphics_get_display_size(0, &state.width, &state.height);
  if (success < 0) {
    fatal("Error getting display size");
  }

  // What does this do?
  vc_dispmanx_rect_set(&eglData.rect, 0, 0, state.width, state.height);
  eglData.data =
    (unsigned short*) malloc(state.width * state.height * eglData.bitdepth);

  // What does this do?
  uint imagePrt;
  eglData.resource = vc_dispmanx_resource_create(VC_IMAGE_RGB565, state.width,
                                                 state.height, &imagePrt);

  if (!eglData.resource) {
    fatal("Error getting resource");
  }

  eglData.origWidth  = state.width;
  eglData.origHeight = state.height;

  state.width  = eglData.width;
  state.height = eglData.height;

  VCRect srcRect;
  VCRect dstRect;

  dstRect.x      = 0;
  dstRect.y      = 0;
  dstRect.width  = state.width;
  dstRect.height = state.height;

  srcRect.x      = 0;
  srcRect.y      = 0;
  srcRect.width  = state.width << 16;
  srcRect.height = state.height << 16;

  eglData.display = vc_dispmanx_display_open(0);
  if (!eglData.display) {
    fatal("Error opening display");
  }

  DMXDisplay dmxDisplay = eglData.display;
  DMXUpdate dmxUpdate   = vc_dispmanx_update_start(0);
  DMXElement dmxElement = vc_dispmanx_element_add(
    dmxUpdate, dmxDisplay, 0, &dstRect, 0, &srcRect, DISPMANX_PROTECTION_NONE,
    0, 0, DISPMANX_TRANSFORM_T());

  eglData.nativeWindow.element = dmxElement;
  eglData.nativeWindow.width   = state.width;
  eglData.nativeWindow.height  = state.height;

  vc_dispmanx_update_submit_sync(dmxUpdate);

  state.surface = eglCreateWindowSurface(state.display, config,
                                         &eglData.nativeWindow, nullptr);

  if (state.surface == EGL_NO_SURFACE) {
    fatal("Error creating EGL surface");
  }

  result =
    eglMakeCurrent(state.display, state.surface, state.surface, state.context);

  if (result == EGL_FALSE) {
    fatal("Error connecting the context to the surface");
  }

  // Set background color and clear buffers
  glClearColor(1.f, 1.f, 1.f, 1.f);

  // Enable back face culling.
  glEnable(GL_CULL_FACE);
}

void EGLConnection::exit()
{
  glClear(GL_COLOR_BUFFER_BIT);
  eglSwapBuffers(state.display, state.surface);

  // Release OpenGL resources
  eglMakeCurrent(state.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  eglDestroySurface(state.display, state.surface);
  eglDestroyContext(state.display, state.context);
  eglTerminate(state.display);

  free(eglData.data);
  munmap(eglData.fbp, eglData.screenDatasize);
  close(eglData.fbfd);
  vc_dispmanx_resource_delete(eglData.resource);
  vc_dispmanx_display_close(eglData.display);
}

void EGLConnection::beginFrame()
{
  // Start with a clear screen
  glViewport(0, 0, eglData.width, eglData.height);

  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glEnable(GL_STENCIL_TEST);
}

void EGLConnection::endFrame()
{
  eglSwapBuffers(state.display, state.surface);

  // Copy buffers
  vc_dispmanx_snapshot(eglData.display, eglData.resource,
                       DISPMANX_TRANSFORM_T(0));
  vc_dispmanx_resource_read_data(eglData.resource, &eglData.rect, eglData.data,
                                 eglData.width * eglData.bitdepth);

  for (int y = 0; y < eglData.height; y++) {
    memcpy(eglData.fbp + y * eglData.width,
           eglData.data + y * eglData.origWidth,
           eglData.width * eglData.bitdepth);
  }
}

namespace otto::ui {
  void main_ui_loop()
  {
    EGLConnection egl;
    egl.framebuffer = config["Framebuffer"].get<std::string>();
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

    using std::chrono::duration;
    using std::chrono::milliseconds;
    using std::chrono::seconds;
    using clock = std::chrono::high_resolution_clock;

    auto waitTime = milliseconds(int(1000.f / config["FPS"].get<float>()));
    auto t0       = clock::now();

    bool showFps = config["Debug"];
    float fps;
    duration<double> lastFrameTime;

    while (global::running()) {
      t0 = clock::now();

      float scale = std::min(egl.eglData.width / float(vg::WIDTH),
                             egl.eglData.height / float(vg::HEIGHT));

      // Update and render
      canvas.setSize(egl.eglData.width, egl.eglData.height);

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

      fps =
        1 /
        (std::chrono::duration_cast<milliseconds>(clock::now() - t0).count() /
         1000.f);
    }

    nvgDeleteGLES2(vg);

    egl.exit();

    global::exit(global::ErrorCode::ui_closed);
  }
} // namespace otto::ui

#endif // OTTO_UI_EGL