#pragma once

#include <choreograph/Timeline.h>

#include "lib/util/ref_count_block.hpp"

#include "lib/itc/domain.hpp"

namespace otto {

  struct GraphicsDomain : itc::StaticDomain<struct graphics_domain_tag> {
    GraphicsDomain() noexcept
    {
      globals_.increment();
    }
    ~GraphicsDomain() noexcept
    {
      globals_.decrement();
    }
    choreograph::Timeline& timeline() // NOLINT
    {
      return globals_.data()->timeline;
    }

  private:
    struct Globals {
      choreograph::Timeline timeline;
    };
    inline static util::RefCountBlock<Globals> globals_; // NOLINT
  };
} // namespace otto
