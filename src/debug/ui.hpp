#pragma once

#include <vector>
#include <functional>

#include <imgui.h>

#include "util/ringbuffer.hpp"
#include "util/algorithm.hpp"
#include "util/locked.hpp"

/*
 * Macros
 */

#if OTTO_DEBUG_UI

#define IF_DEBUG(...)                           \
  __VA_ARGS__;                                  \

#define CALL_IF_DEBUG(lambda)                   \
  lambda();

#else // OTTO_DEBUG_UI

#define IF_DEBUG(...)
#define CALL_IF_DEBUG(lambda)

#endif // OTTO_DEBUG_UI


namespace otto::debug {

  class Info {
  public:
    std::size_t index;

    Info();
    virtual ~Info();

    virtual void draw() = 0;

  protected:
  };

  template<std::size_t N>
  class graph {
  public:

    void push(float val) {
      buffer.push(std::move(val));
      min = std::min(min, val);
      max = std::max(max, val);
    }

    void plot(std::string name) {
      plot(name, min, max);
    }

    void plot(std::string name, float min, float max) {
      ImGui::PlotLines(name.c_str(), [] (void* data, int n) {
          return float((*static_cast<util::ringbuffer<float, N>*>(data))[n]);
        }, &buffer, buffer.size(), 0, nullptr, min, max, ImVec2(0, 80));
    }

  private:

    util::ringbuffer<float, N> buffer;
    float min = 0, max = 0;
  };

  namespace ui {

    inline std::vector<Info*> info_ptrs;

    IF_DEBUG(
      inline std::size_t add_info(Info& new_info) {
        for (std::size_t i = 0; i < info_ptrs.size(); i++) {
          auto& info = info_ptrs[i];
          if (info == nullptr) {
            info = &new_info;
            return i;
          }
        }
        info_ptrs.push_back(&new_info);
        return info_ptrs.size() - 1;
      }

      inline void draw() {
        for (auto& info : info_ptrs) {
          if (info != nullptr) {
            info->draw();
          }
        }
      })

  }

  inline Info::Info() {
    IF_DEBUG(index = ui::add_info(*this));
  }

  inline Info::~Info() {
    IF_DEBUG(ui::info_ptrs[index] = nullptr);
  }
}
