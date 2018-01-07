#pragma once

#include <vector>
#include <functional>

#include <imgui.h>

#include "util/ringbuffer.hpp"
#include "util/algorithm.hpp"
#include "util/locked.hpp"

namespace otto::debug {
  struct Info {
#if OTTO_DEBUG_UI
    std::size_t index;

    Info();
    virtual ~Info();
#endif

    virtual void draw() = 0;
  };

  template<std::size_t N>
  class graph {
  public:

    void push(float val) {
#if OTTO_DEBUG_UI
      buffer.push(std::move(val));
      min = std::min(min, val);
      max = std::max(max, val);
#endif
    }

    void plot(std::string name) {
#if OTTO_DEBUG_UI
      plot(name, min, max);
#endif
    }

    void plot(std::string name, float min, float max) {
#if OTTO_DEBUG_UI
      ImGui::PlotLines(name.c_str(), [] (void* data, int n) {
          return float((*static_cast<util::ringbuffer<float, N>*>(data))[n]);
        }, &buffer, buffer.size(), 0, nullptr, min, max, ImVec2(0, 80));
#endif
    }

  private:

    util::ringbuffer<float, N> buffer;
    float min = 0, max = 0;
  };

  namespace ui {
#if OTTO_DEBUG_UI
    void init();
    void draw_frame();

    inline std::vector<std::function<void()>> draw_funcs;

    template<typename Callable>
    inline std::enable_if_t<std::is_invocable_v<Callable>, std::size_t>
    add_info(Callable&& callable)
    {
      for (std::size_t i = 0; i < draw_funcs.size(); i++) {
        auto& func = draw_funcs[i];
        if (func == nullptr) {
          func = std::forward<Callable>(callable);
          return i;
        }
      }
      draw_funcs.emplace_back(std::forward<Callable>(callable));
      return draw_funcs.size() - 1;
    }

    inline std::size_t add_info(Info& info) {
      return add_info([&info] { info.draw(); });
    }

    inline void draw() {
      for (auto& func : draw_funcs) {
        if (func != nullptr) {
          func();
        }
      }
    }
#else
    inline void init() {}
    inline void draw_frame() {}
#endif
  }

#if OTTO_DEBUG_UI
    inline Info::Info() {
      index = ui::add_info(*this);
    }

    inline Info::~Info() {
      ui::draw_funcs[index] = nullptr;
    }
#endif
}
