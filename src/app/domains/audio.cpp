#include "app/domains/audio.hpp"

namespace otto {

  // NOLINTNEXTLINE
  tl::optional<util::AudioBufferPool> AudioDomain::buffer_pool_ = tl::nullopt;

} // namespace otto
