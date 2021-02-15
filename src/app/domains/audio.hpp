#pragma once

#include "lib/util/audio_buffer.hpp"

#include "lib/itc/domain.hpp"

namespace otto::services {
  struct Audio;
}

namespace otto {

  struct AudioDomain : itc::StaticDomain<struct audio_domain_tag> {
    static util::AudioBufferPool& buffer_pool() noexcept
    {
      OTTO_ASSERT(buffer_pool_.has_value());
      return *buffer_pool_;
    }

  private:
    // TODO: Implement this part properly
    friend struct ::otto::services::Audio;
    static tl::optional<util::AudioBufferPool> buffer_pool_; // NOLINT
  };

} // namespace otto
