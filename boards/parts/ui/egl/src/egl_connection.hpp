#pragma once

#include <string>
#include "./egl_deps.hpp"

namespace otto::board::ui {

  class EGLConnection {
  public:
    using DMXDisplay = DISPMANX_DISPLAY_HANDLE_T;
    using DMXResource = DISPMANX_RESOURCE_HANDLE_T;
    using DMXWindow = EGL_DISPMANX_WINDOW_T;
    using DMXElement = DISPMANX_ELEMENT_HANDLE_T;
    using DMXUpdate = DISPMANX_UPDATE_HANDLE_T;
    using VCRect = VC_RECT_T;

    void init();
    void exit();

    void beginFrame();
    void endFrame();

    void initEGL();

    struct EGLData {
      int width = 0;
      int height = 0;
      int bitdepth = 4;
      int screenDatasize = 0;

      DMXDisplay display = {};
      DMXResource resource = {};
      DMXWindow nativeWindow = {};
      unsigned short* data = nullptr;

      int nConfig = 0;
      VCRect rect = {};
    } eglData;

    struct Size {
      int width = 320;
      int height = 240;
    } draw_size;

    struct EGLState {
      uint width = 0;
      uint height = 0;
      EGLDisplay display = nullptr;
      EGLSurface surface = nullptr;
      EGLContext context = nullptr;
    } state;
  };

} // namespace otto::board::ui
