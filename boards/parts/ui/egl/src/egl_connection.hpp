#pragma once

#include <string>
#include "./egl_deps.hpp"

class EGLConnection {
public:
  using DMXDisplay  = DISPMANX_DISPLAY_HANDLE_T;
  using DMXResource = DISPMANX_RESOURCE_HANDLE_T;
  using DMXWindow   = EGL_DISPMANX_WINDOW_T;
  using DMXElement  = DISPMANX_ELEMENT_HANDLE_T;
  using DMXUpdate   = DISPMANX_UPDATE_HANDLE_T;
  using VCRect      = VC_RECT_T;

  void init();
  void exit();

  void beginFrame();
  void endFrame();

  void initEGL();

  struct EGLData {
    int width;
    int height;
    int bitdepth = 4;
    int screenDatasize;

    DMXDisplay display;
    DMXResource resource;
    DMXWindow nativeWindow;
    unsigned short* data = nullptr;

    int nConfig;
    VCRect rect;
  } eglData;

  struct EGLState {
    uint width;
    uint height;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
  } state;
};
