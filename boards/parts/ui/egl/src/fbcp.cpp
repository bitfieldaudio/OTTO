#if false
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "util/exception.hpp"

#include "./fbcp.hpp"

namespace otto::board::ui {

  RpiFBCP::RpiFBCP(EGLConnection::EGLData& data) : egl_data(data) {}

  void RpiFBCP::init()
  {
    bcm_host_init();

    fbfd = open("/dev/fb1", O_RDWR);
    if (fbfd == -1) {
      throw util::exception("Unable to open secondary display");
    }
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
      throw util::exception("Unable to get secondary display information");
    }
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
      throw util::exception("Unable to get secondary display information");
    }

    LOGI("Second display is {} x {} {}bps\n", vinfo.xres, vinfo.yres,
         vinfo.bits_per_pixel);

    uint32_t image_prt;
    screen_resource = vc_dispmanx_resource_create(VC_IMAGE_RGB565, vinfo.xres,
                                                  vinfo.yres, &image_prt);
    if (!screen_resource) {
      close(fbfd);
      throw util::exception("Unable to create screen buffer");
    }

    fbp = (char*) mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED,
                       fbfd, 0);
    if (fbp == nullptr) {
      close(fbfd);
      vc_dispmanx_resource_delete(screen_resource);
      throw util::exception("Unable to create mamory mapping");
    }

    vc_dispmanx_rect_set(&rect1, 0, 0, vinfo.xres, vinfo.yres);
  }

  void RpiFBCP::copy()
  {
    vc_dispmanx_snapshot(egl_data.display, screen_resource, DISPMANX_NO_ROTATE);
    vc_dispmanx_resource_read_data(screen_resource, &rect1, fbp,
                                   vinfo.xres * vinfo.bits_per_pixel / 8);
  }

  void RpiFBCP::exit() noexcept
  {
    munmap(fbp, finfo.smem_len);
    close(fbfd);
    vc_dispmanx_resource_delete(screen_resource);
  }

} // namespace otto::board::ui
#endif
