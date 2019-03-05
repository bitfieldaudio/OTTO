#pragma once

#include "core/engine/engine.hpp"

#include "util/iterator.hpp"

#include "list"

#include <Gamma/SamplePlayer.h>
#include <Gamma/Filter.h>
#include <AudioFile.h>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;


  struct Sampler : SynthEngine, EngineWithEnvelope {
    struct Props : Properties<> {
      Property<std::string> file = {this, "FILENAME", ""};
      Property<float> volume = {this, "VOLUME", 1, has_limits::init(0, 4), steppable::init(0.01)};
      Property<float> filter = {this, "FILTER", 5, has_limits::init(1, 20), steppable::init(0.3)};
      Property<float> speed = {this, "SPEED", 1, has_limits::init(-10, 10), steppable::init(0.01)};
      Property<float> fadein = {this, "FADEIN", 0, has_limits::init(0, 1), steppable::init(0.01)};
      Property<float> fadeout = {this, "FADEOUT", 0, has_limits::init(0, 1), steppable::init(0.01)};
      Property<float> startpoint = {this, "STARTPOINT", 0, has_limits::init(0, 1), steppable::init(0.001)};
      Property<float> endpoint = {this, "ENDPOINT", 1, has_limits::init(0, 1),steppable::init(0.001)};

      Property<bool> cut = {this, "CUT", false};
      Property<bool> loop = {this, "LOOP", false};

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
