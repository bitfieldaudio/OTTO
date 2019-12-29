#pragma once

#include "arp.hpp"
#include "audio.hpp"

#include "core/ui/screen.hpp"

namespace otto::engines::arp {

  using namespace core;

  inline std::string to_string(Playmode pm) noexcept
  {
    switch (pm) {
    case Playmode::up: return "Up";
    case Playmode::down: return "Down";
    case Playmode::updown: return "Up/Down";
    case Playmode::downup: return "Down/Up";
    case Playmode::updowninc: return "Up/Down Inc.";
    case Playmode::downupinc: return "Down/Up Inc.";
    case Playmode::manual: return "Manual";
    case Playmode::chord: return "Chord";
    };
    OTTO_UNREACHABLE;
  }

  inline std::string to_string(OctaveMode om) noexcept
  {
    switch (om) {
    case OctaveMode::standard: return "Boring";
    case OctaveMode::octaveup: return "+1";
    case OctaveMode::octaveupunison: return "+1Unison";
    case OctaveMode::fifthunison: return "Fifth";
    case OctaveMode::octavedownup: return "-1 & +1";
    };
    OTTO_UNREACHABLE;
  }

  struct Screen : ui::Screen {
    
    int min = 88;
    int max = 0;
    int num_steps = 0;

    std::string playmode_ = "Up/Down Inc.";
    std::string octavemode_ = "+1Unison";
    float note_length_ = 0.f;
    int subdivision_ = 1;

    void draw(nvg::Canvas& ctx) override;
    void action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept;
    void action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept;
    void action(itc::prop_change<&Props::note_length>, float nl) noexcept;
    void action(itc::prop_change<&Props::subdivision>, int s) noexcept;


  };

} // namespace otto::engines::arp
