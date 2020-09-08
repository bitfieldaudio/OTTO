#include <assert.h>
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <thread>

#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/impl/runtime.hpp"
#include "app/services/logic_thread.hpp"

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

using namespace otto;
using namespace otto::services;

int main(int argc, char* argv[])
{
  auto app = start_app(ConfigManager::make_default(), LogicThread::make_default(), Graphics::make_board());

  std::cout << app.service<ConfigManager>().into_toml() << std::endl;

  app.service<Graphics>().show([&](SkCanvas& ctx) {
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(SK_ColorRED);
    ctx.drawCircle({160, 120}, 50, paint);
  });

  app.wait_for_stop();
}
