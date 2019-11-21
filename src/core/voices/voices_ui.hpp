#pragma once

#include "core/ui/screen.hpp"
#include "voice_props.hpp"

namespace otto::core::voices {

  struct EnvelopeScreen : ui::Screen {
    void draw(ui::vg::Canvas&) override;

    void action(attack_tag::action, float a) noexcept;
    void action(decay_tag::action, float d) noexcept;
    void action(sustain_tag::action, float s) noexcept;
    void action(release_tag::action, float r) noexcept;

  private:
    float attack = 0;
    float decay = 0;
    float sustain = 0;
    float release = 0;
  };

  struct SettingsScreen : ui::Screen {
    void draw(ui::vg::Canvas&) override;

    void action(portamento_tag::action, float portamento) noexcept;
    void action(legato_tag::action, bool legato) noexcept;
    void action(retrig_tag::action, bool retrig) noexcept;

    void action(play_mode_tag::action, PlayMode play_mode) noexcept;
    void action(rand_tag::action, float rand) noexcept;
    void action(sub_tag::action, float sub) noexcept;
    void action(detune_tag::action, float detune) noexcept;
    void action(interval_tag::action, int interval) noexcept;

  private:
    std::string play_mode_str;
    std::string aux_name;
    std::string aux_value;
    PlayMode play_mode;
    float portamento = 0;
    bool legato = false;
    bool retrig = false;
  };

} // namespace otto::core::voices
