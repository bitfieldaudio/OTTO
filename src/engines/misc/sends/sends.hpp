#pragma once

#include "core/engine/engine.hpp"
#include "core/ui/icons.hpp"
#include "itc/itc.hpp"

namespace otto::engines::sends {

  using namespace core::props;

  struct Screen;
  struct Audio;

  struct Props : core::props::Properties<Props> {
    itc::GAProp<struct dry_tag, float> dry = {1, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct fx1_tag, float> fx1 = {0, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct fx2_tag, float> fx2 = {0, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct pan_tag, float> pan = {0.5, limits(0, 1), step_size(0.01)};

    struct StoredLevels {
      float fx1 = 0;
      float fx2 = 0;
      float dry = 1;
      float s = 1;
    } stored_levels;

    REFLECT_PROPS(Props, dry, fx1, fx2, pan);
  };

  struct Sends : core::engine::MiscEngine<Sends>, util::OwnsObservers, itc::ActionReceiverOnBus<itc::LogicBus> {
    static constexpr util::string_ref name = "Sends";

    Sends(itc::ActionChannel, core::ui::Icon i);
    ~Sends() noexcept;

    void step_scale(int steps);
    void set_scale(float x);
    void set(float value, float& changed, float& other1, float& other2);

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Screen> screen_;

    Props props;

  private:
    /// This bool stops the on_change handlers from doing anything when the properties are set by the macro control
    /// This would otherwise lead to a never-ending recursion.
    bool is_recursive = false;
    static constexpr float threshold = 0.0001;
  };
} // namespace otto::engines::sends
