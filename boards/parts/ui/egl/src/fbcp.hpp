#pragma once

#include <linux/fb.h>

#include "./egl_connection.hpp"

namespace otto::board::ui {

  /// This class is used to copy from the HDMI framebuffer on the pi, to the
  /// framebuffer which is used by fbtft. This is useful when using an SPI
  /// display.
  ///
  /// At some point in the future, we will probably want to skip some of these
  /// steps, possibly by including the spi driver directly and writing the main
  /// framebuffer to that on each frame.
  struct RpiFBCP {
    RpiFBCP(EGLConnection::EGLData& data);

    ~RpiFBCP() noexcept
    {
      this->exit();
    }

    void init();
    void copy();
    void exit() noexcept;

  private:
    EGLConnection::EGLData& egl_data;

    DISPMANX_RESOURCE_HANDLE_T screen_resource;
    VC_RECT_T rect1;
    int fbfd = 0;
    char* fbp = 0;

    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;
  };

} // namespace otto::board::ui
