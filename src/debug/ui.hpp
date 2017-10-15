#pragma once

#include <vector>
#include <functional>

#include <imgui.h>

#include "util/ringbuffer.hpp"
#include "util/algorithm.hpp"

namespace otto::debug {

  class Info {
  public:
    std::size_t index;

    Info();
    virtual ~Info();

    virtual void draw() = 0;

  protected:
    template<typename T, std::size_t N>
    static void plot(util::ringbuffer<T, N>& buf, float min, float max) {
      ImGui::PlotLines("", [] (void* data, int n) {
          return (*static_cast<util::ringbuffer<T, N>*>(data))[n];
        }, &buf, buf.size(), 0, nullptr, min, max, ImVec2(0, 80));
    }
  };

  namespace ui {

    inline std::vector<Info*> info_ptrs;

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
    }

  }

  inline Info::Info() {
    #ifdef OTTO_DEBUG_UI
    index = ui::add_info(*this);
    #endif
  }

  inline Info::~Info() {
    #ifdef OTTO_DEBUG_UI
    ui::info_ptrs[index] = nullptr;
    #endif
  }
}

/*
 * Macros
 */

#ifdef OTTO_DEBUG_UI

#define IF_DEBUG(...)                        \
  __VA_ARGS__;                               \

#define CALL_IF_DEBUG(lambda)                   \
  lambda();

#else // OTTO_DEBUG_UI

#define CALL_IF_DEBUG(lambda)
#define IF_DEBUG(...)

#endif // OTTO_DEBUG_UI
