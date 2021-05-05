#pragma once

#include "lib/util/change_checker.hpp"
#include "lib/util/serialization.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/producer.hpp"

namespace otto::engines::slots {

  struct SlotState {
    util::StaticallyBounded<float, 0, 1, util::bounds_policies::wrap> selected_color_f = 0.5f;
    DECL_VISIT(selected_color_f);
  };

  struct SoundSlotsState {
    util::StaticallyBounded<int, 0, 9> active_idx = 0;
    std::array<SlotState, 10> slot_states;
    DECL_VISIT(active_idx, slot_states);
  };

  // Put in a separate struct because it is not needed for the screen and contains a lot of data.
  struct SlotData {
    std::array<json::value, 10> json_objects;
    DECL_VISIT(json_objects);
  };

  struct Logic : ILogic, itc::Producer<SoundSlotsState, SlotState> {
    Logic(itc::Context& ctx) : Producer(ctx) {}

    void on_state_change(const SoundSlotsState& state) override;
    void on_state_change(const SlotState& state) override {}
    void set_managed(util::DynSerializable&& ctx);

  private:
    util::DynSerializable _ctx;
    SlotData data_;
    util::change_checker<int> idx;
  };

  struct SoundSlots {
    std::unique_ptr<Logic> logic;
    ScreenWithHandler overlay_screen;

    static SoundSlots make(itc::Context& ctx);
  };

} // namespace otto::engines::slots
