#pragma once

#include "core/ui/screen.hpp"
#include "voice_props.hpp"

namespace otto::core::voices {

  struct EnvelopeScreen final : ui::Screen,
                                itc::ActionReceiverOnBus<itc::GraphicsBus,
                                                         attack_tag::action,
                                                         decay_tag::action,
                                                         sustain_tag::action,
                                                         release_tag::action> //
  {
    void draw(ui::vg::Canvas&) override;

    void action(attack_tag::action, float a) noexcept final;
    void action(decay_tag::action, float d) noexcept final;
    void action(sustain_tag::action, float s) noexcept final;
    void action(release_tag::action, float r) noexcept final;

  private:
    float attack = 0;
    float decay = 0;
    float sustain = 0;
    float release = 0;
  };

  struct SettingsScreen final : ui::Screen,
                                itc::ActionReceiverOnBus<itc::GraphicsBus,
                                                         portamento_tag::action,
                                                         legato_tag::action,
                                                         retrig_tag::action,
                                                         play_mode_tag::action,
                                                         rand_tag::action,
                                                         sub_tag::action,
                                                         detune_tag::action,
                                                         interval_tag::action> //
  {
    void draw(ui::vg::Canvas&) override;

    void action(portamento_tag::action, float portamento) noexcept final;
    void action(legato_tag::action, bool legato) noexcept final;
    void action(retrig_tag::action, bool retrig) noexcept final;

    void action(play_mode_tag::action, PlayMode play_mode) noexcept final;
    void action(rand_tag::action, float rand) noexcept final;
    void action(sub_tag::action, float sub) noexcept final;
    void action(detune_tag::action, float detune) noexcept final;
    void action(interval_tag::action, int interval) noexcept final;

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
