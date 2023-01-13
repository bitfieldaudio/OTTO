#pragma once

#include "lib/util/change_checker.hpp"
#include "lib/util/serialization.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/state/producer.hpp"

#include "app/domains/logic.hpp"

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
  };

  struct Logic : ILogic, itc::Producer<SoundSlotsState>, itc::Persistant {
    Logic(itc::Context& ctx) : Producer(ctx), itc::Persistant(ctx, "slots"), persistance_provider(ctx["slots"]) {}

    void on_state_change(const SoundSlotsState& state) noexcept override;

    /// Any objects registered on this context will be serialized and deserialized when switching slots
    itc::Context& managed_ctx()
    {
      return persistance_provider.context();
    }

    void serialize_into(json::value& json) const override
    {
      util::serialize_into(json["slots"], data_.json_objects);
      json["slots"][state().active_idx] = util::serialize(persistance_provider);
    }

    void deserialize_from(const json::value& json) override
    {
      auto slots = json::get_or_null(json, "slots");
      util::deserialize_from(slots, data_.json_objects);
      util::deserialize_from(json::get_or_null(json, state().active_idx), persistance_provider);
    }

  private:
    itc::PersistanceProvider persistance_provider;
    SlotData data_;
    util::change_checker<int> idx;
  };

  struct SoundSlots {
    std::unique_ptr<Logic> logic;
    ScreenWithHandler overlay_screen;

    static SoundSlots make(itc::Context& ctx);
  };

} // namespace otto::engines::slots
