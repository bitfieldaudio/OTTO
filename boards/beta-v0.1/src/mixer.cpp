#include "lib/alsamixer.hpp"

#include "app/drivers/audio_driver.hpp"

using namespace otto;

/// Models the linux driver `snd_rpi_proto`, which interfaces with a wm8731
/// We use this driver on the target hardware
struct AlsaSndRpiProto {
  alsa::Mixer mixer = {"default"};
  /// Master output volume
  alsa::ElemProp<alsa::PlaybackVolumeAll> master = mixer.find_elem("Master");
  /// TODO: What does this do?
  alsa::ElemProp<alsa::PlaybackSwitchAll> master_playback_zc = mixer.find_elem("Master Playback ZC");
  /// Hardware monitoring volume
  alsa::ElemProp<alsa::PlaybackVolumeAll> sidetone = mixer.find_elem("Sidetone");
  /// Presumably switches the line input?
  alsa::ElemProp<alsa::CaptureSwitchAll> line = mixer.find_elem("Line");
  /// Presumably switches the mic input?
  alsa::ElemProp<alsa::CaptureSwitchAll> mic = mixer.find_elem("Mic");
  /// A Mic gain boost. Should probably be on for internal mic
  alsa::ElemProp<alsa::PlaybackVolumeAll> mic_boost = mixer.find_elem("Mic Boost");
  /// TODO: What does this do?
  alsa::ElemProp<alsa::PlaybackSwitchAll> playback_deemphasis = mixer.find_elem("Playback Deemphasis");
  /// Presumably input gain
  alsa::ElemProp<alsa::CaptureVolumeAll> capture = mixer.find_elem("Capture");
  /// Presumably a high pass filter can be toggled for the line/mic input
  alsa::ElemProp<alsa::PlaybackSwitchAll> adc_high_pass_filter = mixer.find_elem("ADC High Pass Filter");
  /// Switches between `Line In` and `Mic` for the input (so what do the `line` and `mic` switches do?)
  alsa::ElemProp<alsa::EnumControl> input_mux = mixer.find_elem("Input Mux");
  /// I don't know what it does, but it needs to be on to get output
  alsa::ElemProp<alsa::PlaybackSwitchAll> output_mixer_hifi = mixer.find_elem("Output Mixer HiFi");
  /// Maybe toggles line in monitoring?
  alsa::ElemProp<alsa::PlaybackSwitchAll> output_mixer_line_bypass = mixer.find_elem("Output Mixer Line Bypass");
  /// Toggle hardware mic monitoring
  alsa::ElemProp<alsa::PlaybackSwitchAll> output_mixer_mic_sidetone = mixer.find_elem("Output Mixer Mic Sidetone");
  /// TODO: Is this on input, output or both?
  alsa::ElemProp<alsa::PlaybackSwitchAll> store_dc_offset = mixer.find_elem("Store DC Offset");

  /// Value for `input_mux` to select mic as input
  int input_mux_mic = input_mux.index_of("Mic");
  /// Value for `input_mux` to select line in as input
  int input_mux_line = input_mux.index_of("Line In");

  /// Set up initial/default parameters
  void init()
  {
    master = 1.f;
    master_playback_zc = true;
    sidetone = 0.f;
    line = true;
    mic = true;
    mic_boost = 1.f;
    playback_deemphasis = false;
    capture = 1.f;
    adc_high_pass_filter = false;
    input_mux = input_mux_mic;
    output_mixer_hifi = true;
    output_mixer_line_bypass = false;
    output_mixer_mic_sidetone = false;
    store_dc_offset = false;
  }
};

namespace otto::drivers {
  struct RpiProtoAlsaMixer final : IAudioMixer {
    AlsaSndRpiProto sndcrd;
    RpiProtoAlsaMixer()
    {
      sndcrd.init();
    }

    [[nodiscard]] float get_volume() const override
    {
      return sndcrd.master.get_value();
    }

    void set_volume(float v) override
    {
      sndcrd.master.set_value(v);
    }
  };

  std::unique_ptr<IAudioMixer> IAudioMixer::make_default(IAudioDriver&)
  {
    return std::make_unique<RpiProtoAlsaMixer>();
  }
} // namespace otto::drivers
