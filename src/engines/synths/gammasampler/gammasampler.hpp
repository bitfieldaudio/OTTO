#pragma once

#include "core/engine/engine.hpp"

#include "util/iterator.hpp"

#include <AudioFile.h>
#include <Gamma/Filter.h>
#include <Gamma/SamplePlayer.h>
#include <engines/misc/sends/sends.hpp>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;


  struct Sampler : SynthEngine<Sampler> {
    static constexpr util::string_ref name = "Sampler";
    struct Props {
      Property<std::string> file = "";
      Property<float> volume = {1, limits(0, 4), step_size(0.01)};
      Property<float> filter = {5, limits(1, 20), step_size(0.3)};
      Property<float> speed = {1, limits(-10, 10), step_size(0.01)};
      Property<float> fadein = {0, limits(0, 1), step_size(0.01)};
      Property<float> fadeout = {0, limits(0, 1), step_size(0.01)};
      Property<float> startpoint = {0, limits(0, 1), step_size(0.001)};
      Property<float> endpoint = {1, limits(0, 1), step_size(0.001)};

      std::vector<std::string> filenames;
      std::vector<std::string>::iterator file_it = filenames.begin();
      gam::Array<float> samplecontainer;
      float samplerate;

      engines::Sends send;

      DECL_REFLECTION(Props, file, volume, filter, speed, fadein, fadeout, startpoint, endpoint);
    } props;

    Sampler();

    void restart();
    void finish();


    float operator()() noexcept;

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    voices::IVoiceManager& voice_mgr() noexcept override
    {
      return _voice_mgr;
    }
    ui::Screen& envelope_screen() override;
    ui::Screen& voices_screen() override;

  protected:
    friend struct SamplerScreen;
    friend struct SamplerEnvelopeScreen;

    void load_file(std::string);
    gam::SamplePlayer<> sample;
    AudioFile<float> samplefile;
    int frames;
    bool note_on = false;

    gam::Biquad<> _lo_filter;
    gam::Biquad<> _hi_filter;

    struct Pre : voices::PreBase<Pre, Props> {
      using voices::PreBase<Pre, Props>::PreBase;
    };
    struct Voice : voices::VoiceBase<Voice, Pre> {
      using voices::VoiceBase<Voice, Pre>::VoiceBase;
      float operator()() noexcept
      {
        return 0;
      }
    };

    struct Post : voices::PostBase<Post, Voice> {};
    using VoiceManager = voices::VoiceManager<Post, 6>;
    VoiceManager _voice_mgr = {props};

    std::unique_ptr<ui::Screen> _envelope_screen;
  };

} // namespace otto::engines
