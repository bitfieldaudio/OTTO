#include "app/drivers/audio_driver.hpp"

namespace otto::drivers {
  std::unique_ptr<IAudioMixer> IAudioMixer::make_default(IAudioDriver& d)
  {
    return IAudioMixer::make_software(d);
  }
} // namespace otto::drivers
