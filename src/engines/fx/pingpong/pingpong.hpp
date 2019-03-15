#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Pingpong : EffectEngine {
    static constexpr std::string_view name = "Pingpong";

    struct DelayLine : Properties<faust_link> {
      using Properties::Properties;
      Property<float, faust_link, no_serialize> level = {
        this, "level", 0, has_limits::init(0, 5), faust_link::init(FaustLink::Type::FromFaust)};
    };

    static_assert(sizeof(Properties<>) <= 112);

    struct Props : Properties<faust_link> {
      Property<float, faust_link> delaytime = {this, "delaytime", 0.5, has_limits::init(0.01, 0.99),
                                               steppable::init(0.01)};
      Property<bool, faust_link> bpm_follow = {this, "bpm_follow", false};
      Property<float, faust_link> feedback = {this, "feedback", 0.5, has_limits::init(0, 1),
                                              steppable::init(0.01)};
      Property<float, faust_link> tone = {this, "tone", 0.5, has_limits::init(0, 1),
                                          steppable::init(0.01)};
      Property<float, faust_link> spread = {this, "spread", 0, has_limits::init(0, 1),
                                            steppable::init(0.01)};

      std::array<DelayLine, 20> delay_level = {
        {{this, "delayline0"},  {this, "delayline1"},  {this, "delayline2"},
         {this, "delayline3"},  {this, "delayline4"},  {this, "delayline5"},
         {this, "delayline6"},  {this, "delayline7"},  {this, "delayline8"},
         {this, "delayline9"},  {this, "delayline10"}, {this, "delayline11"},
         {this, "delayline12"}, {this, "delayline13"}, {this, "delayline14"},
         {this, "delayline15"}, {this, "delayline16"}, {this, "delayline17"},
         {this, "delayline18"}, {this, "delayline19"}}};

    } props;



    Pingpong();


    audio::ProcessData<2> process(audio::ProcessData<1>) override;

  private:
    audio::FaustWrapper<1, 2> faust_;
  };

} // namespace otto::engines
