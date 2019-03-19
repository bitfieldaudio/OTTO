#pragma once

#include "core/engine/engine.hpp"

#include "util/iterator.hpp"

#include <AudioFile.h>
#include <Gamma/Filter.h>
#include <Gamma/SamplePlayer.h>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;


  struct Sampler : SynthEngine<Sampler>, EngineWithEnvelope {
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

      Property<bool> cut = false;
      Property<bool> loop = false;

      DECL_REFLECTION(Props, file, volume, filter, speed, fadein, fadeout, startpoint, cut, loop);
    } props;

    Sampler();

    void restart();
    void finish();

    float operator()() noexcept;

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    ui::Screen& envelope_screen() override;
    ui::Screen& voices_screen() override;

  private:
    friend struct SamplerScreen;
    friend struct SamplerEnvelopeScreen;

    void load_file(fs::path path);
    gam::SamplePlayer<> sample;
    gam::Array<float> samplecontainer;
    AudioFile<float> samplefile;
    int frames;
    bool note_on = false;

    gam::Biquad<> _lo_filter;
    gam::Biquad<> _hi_filter;


    std::unique_ptr<ui::Screen> _envelope_screen;
  };

} // namespace otto::engines
