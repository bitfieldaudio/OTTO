#include "graphics.t.hpp"

#include "testing.t.hpp"

#ifndef OTTO_BOARD_PARTS_UI_GLFW

namespace otto::test {

  void show_gui(core::ui::vg::Size size, std::function<void(core::ui::vg::Canvas& ctx)> draw) {
    WARN("show_gui run, but isn't implemented without GLFW");
  }

}

#else

#include "board/ui/glfw_ui_manager.hpp"

namespace otto::test {

  void show_gui(core::ui::vg::Size size, std::function<void(core::ui::vg::Canvas& ctx)> draw) {
    glfw::NVGWindow window = {int(size.w), int(size.h), Catch::getCurrentContext().getResultCapture()->getCurrentTestName()};

    core::ui::vg::initUtils(window.canvas());

    glfwSetTime(0);

    double t, spent;
    while(!window.should_close()) {

      window.begin_frame();

      window.canvas().lineWidth(6);
      window.canvas().lineCap(core::ui::vg::LineCap::ROUND);
      window.canvas().lineJoin(core::ui::vg::LineJoin::ROUND);
      draw(window.canvas());
      window.end_frame();

      glfwPollEvents();
      spent = glfwGetTime() - t;

      std::this_thread::sleep_for(std::chrono::milliseconds(int(1000 / 120 - spent * 1000)));
    }
  }

}
#endif
