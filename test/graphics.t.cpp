/*
#include "graphics.t.hpp"

#include "dummy_services.hpp"
#include "testing.t.hpp"

#ifndef OTTO_BOARD_PARTS_UI_GLFW

namespace otto::test {

  void show_gui(core::ui::vg::Size size,
                std::function<void(core::ui::vg::Canvas& ctx)> draw,
                core::input::InputHandler*)
  {
    FAIL("show_gui run, but isn't implemented without GLFW");
  }

} // namespace otto::test

#else

#include "board/ui/glfw_ui_manager.hpp"

namespace otto::test {

  void show_gui(core::ui::vg::Size size,
                std::function<void(core::ui::vg::Canvas& ctx)> draw,
                core::input::InputHandler* input)
  {
    glfw::NVGWindow window = {int(size.w), int(size.h), "OTTO TEST"};

    if (input) {
      window.key_callback = [input](auto&& action, auto&& mods, auto&& key) {
        board::ui::handle_keyevent(action, mods, key, *input);
      };
    }

    core::ui::vg::initUtils(window.canvas());

    glfwSetTime(0);

    double t, spent;
    while (!window.should_close()) {
      t = glfwGetTime();

      window.begin_frame();

      window.canvas().lineWidth(6);
      window.canvas().lineCap(core::ui::vg::LineCap::ROUND);
      window.canvas().lineJoin(core::ui::vg::LineJoin::ROUND);
      window.canvas().clip(0,0, size.w, size.h);
      draw(window.canvas());
      window.end_frame();

      glfwPollEvents();
      spent = glfwGetTime() - t;

      core::ui::vg::timeline().step(1000 / 30);
      std::this_thread::sleep_for(std::chrono::milliseconds(int(1000 / 30 - spent * 1000)));
    }
  }

} // namespace otto::test
#endif
*/
