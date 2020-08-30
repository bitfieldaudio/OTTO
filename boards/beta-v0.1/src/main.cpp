#include <assert.h>
#include <stdio.h>
#include <cstdio>
#include <iostream>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <bcm_host.h>

#include "GrContext.h"
#include "SkCanvas.h"
#include "SkData.h"
#include "SkImage.h"
#include "SkPaint.h"
#include "SkStream.h"
#include "SkSurface.h"
#include "gl/GrGLInterface.h"
#include "gl/GrGLTypes.h"

typedef struct {
  uint32_t screen_width;
  uint32_t screen_height;
  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;
} CUBE_STATE_T;

static CUBE_STATE_T _state, *state = &_state;

static void init_ogl(CUBE_STATE_T* state)
{
  int32_t success = 0;
  EGLBoolean result;
  EGLint num_config;

  static EGL_DISPMANX_WINDOW_T nativewindow;

  DISPMANX_ELEMENT_HANDLE_T dispman_element;
  DISPMANX_DISPLAY_HANDLE_T dispman_display;
  DISPMANX_UPDATE_HANDLE_T dispman_update;
  VC_RECT_T dst_rect;
  VC_RECT_T src_rect;

  static const EGLint attribute_list[] = {EGL_RED_SIZE,
                                          8,
                                          EGL_GREEN_SIZE,
                                          8,
                                          EGL_BLUE_SIZE,
                                          8,
                                          EGL_ALPHA_SIZE,
                                          8,
                                          EGL_DEPTH_SIZE,
                                          0,
                                          EGL_STENCIL_SIZE,
                                          8,
                                          EGL_SURFACE_TYPE,
                                          EGL_WINDOW_BIT,
                                          EGL_RENDERABLE_TYPE,
                                          EGL_OPENGL_ES2_BIT,
                                          EGL_NONE};

  const EGLint context_attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

  EGLConfig config;

  state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  assert(state->display != EGL_NO_DISPLAY);

  result = eglInitialize(state->display, NULL, NULL);
  assert(EGL_FALSE != result);

  result = eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);
  assert(EGL_FALSE != result);

  result = eglBindAPI(EGL_OPENGL_ES_API);
  assert(EGL_FALSE != result);

  state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, context_attrib_list);
  assert(state->context != EGL_NO_CONTEXT);

  success = graphics_get_display_size(0, &state->screen_width, &state->screen_height);
  assert(success >= 0);

  dst_rect.x = 0;
  dst_rect.y = 0;
  dst_rect.width = state->screen_width;
  dst_rect.height = state->screen_height;

  src_rect.x = 0;
  src_rect.y = 0;
  src_rect.width = state->screen_width << 16;
  src_rect.height = state->screen_height << 16;

  dispman_display = vc_dispmanx_display_open(0 /* LCD */);
  dispman_update = vc_dispmanx_update_start(0);

  dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0, &dst_rect, 0, &src_rect,
                                            DISPMANX_PROTECTION_NONE, 0, 0, DISPMANX_NO_ROTATE);

  nativewindow.element = dispman_element;
  nativewindow.width = state->screen_width;
  nativewindow.height = state->screen_height;
  vc_dispmanx_update_submit_sync(dispman_update);

  state->surface = eglCreateWindowSurface(state->display, config, &nativewindow, NULL);
  assert(state->surface != EGL_NO_SURFACE);

  result = eglMakeCurrent(state->display, state->surface, state->surface, state->context);
  assert(EGL_FALSE != result);
}

static void exit_func(void)
{
  eglMakeCurrent(state->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  eglDestroySurface(state->display, state->surface);
  eglDestroyContext(state->display, state->context);
  eglTerminate(state->display);
  bcm_host_deinit();
}

int main(int argc, char* argv[])
{
  bcm_host_init();
  memset(state, 0, sizeof(*state));
  init_ogl(state);

  printf("EGL Information:\n");
  printf("\tVendor:\t\t%s\n", eglQueryString(state->display, EGL_VENDOR));
  printf("\tVersion:\t%s\n", eglQueryString(state->display, EGL_VERSION));
  printf("\tClient APIs:\t%s\n", eglQueryString(state->display, EGL_CLIENT_APIS));
  printf("\tExtensions:\t%s\n", eglQueryString(state->display, EGL_EXTENSIONS));
  printf("\n");
  printf("OpenGL Information:\n");
  printf("\tVendor:\t\t%s\n", glGetString(GL_VENDOR));
  printf("\tRenderer:\t%s\n", glGetString(GL_RENDERER));
  printf("\tVersion:\t%s\n", glGetString(GL_VERSION));
  printf("\tExtensions:\t%s\n", glGetString(GL_EXTENSIONS));
  printf("\n");

  glViewport(0, 0, (GLsizei) state->screen_width, (GLsizei) state->screen_height);
  glClearColor(1, 0, 0, 1);
  glClearStencil(0);
  glStencilMask(0xffffffff);
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  sk_sp<const GrGLInterface> interface(GrGLCreateNativeInterface());
  sk_sp<GrContext> grContext(GrContext::MakeGL(interface));
  GrGLFramebufferInfo fbInfo;
  fbInfo.fFBOID = 0;
  fbInfo.fFormat = 0x8051;
  GrBackendRenderTarget desc(state->screen_width, state->screen_height, 0, 8, fbInfo);
  // desc.fWidth = state->screen_width;
  // desc.fHeight = state->screen_height;
  // desc.fConfig = kSkia8888_GrPixelConfig;
  // desc.fOrigin = kBottomLeft_GrSurfaceOrigin;
  // desc.fSampleCnt = 0;
  // desc.fStencilBits = 8;
  SkSurface* surface = SkSurface::MakeFromBackendRenderTarget(grContext.release(), desc, kBottomLeft_GrSurfaceOrigin,
                                                              SkColorType::kRGB_888x_SkColorType, nullptr, nullptr)
                         .release();
  SkCanvas* canvas = surface->getCanvas();

  canvas->clear(SK_ColorBLACK);

  SkPaint paint;
  paint.setAntiAlias(true);
  paint.setColor(SK_ColorRED);
  canvas->drawCircle({160, 120}, 60, paint);
  paint.setColor(SK_ColorBLUE);
  canvas->drawCircle({160, 120}, 40, paint);

  canvas->flush();
  eglSwapBuffers(state->display, state->surface);

  getchar();
  exit_func();
  printf("Finished!\n");
  return 0;
}
