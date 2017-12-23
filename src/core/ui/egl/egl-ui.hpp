#if OTTO_UI_EGL

#pragma once

class EGLConnection {
public:
  std::string framebuffer = "/dev/fb1";

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

  void fatal(std::string message);

  void initEGL();

  struct EGLData {
    int width;
    int height;
    int bitdepth = 4;
    int screenDatasize;

    DMXDisplay display;
    DMXResource resource;
    DMXWindow nativeWindow;
    int fbfd             = 0;
    unsigned short* fbp  = nullptr;
    unsigned short* data = nullptr;

    int nConfig;
    VCRect rect;

    EGLData() {}
    EGLData(EGLData&)  = delete;
    EGLData(EGLData&&) = delete;
  } eglData;

  struct EGLState {
    uint width;
    uint height;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

    EGLState() {}
    EGLState(EGLState&)  = delete;
    EGLState(EGLState&&) = delete;
  } state;

  EGLConnection() {}
  EGLConnection(EGLConnection&)  = delete;
  EGLConnection(EGLConnection&&) = delete;
};

#endif // OTTO_UI_EGL