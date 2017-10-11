#pragma once

#include <imgui.h>

#include "util/ringbuffer.hpp"

namespace top1::debug::ui {

  inline float FPS_limit = 60.f;
  inline util::ringbuffer<std::pair<float, float>, 512> fps_history;

  inline void draw() {
    ImGui::Begin("Graphics");
    ImGui::SliderFloat("FPS limit", &FPS_limit, 0.f, 300.f);
    auto fps = fps_history.front();
    ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / fps.first, fps.first);
    ImGui::Text("FPS History");
    ImGui::PlotLines("", [] (void*, int n) {
        return fps_history[n].first;
      }, nullptr, fps_history.size(), 0, nullptr, 0, 120, ImVec2(0, 100));
    ImGui::Text("Percentage of time used rendering");
    ImGui::PlotLines("", [] (void*, int n) {
        auto&& el = fps_history[n];
        return el.first / el.second * 100.f;
      }, nullptr, fps_history.size(), 0, nullptr, 0, 120, ImVec2(0, 100));
    ImGui::End();
  }

}
