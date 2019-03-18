#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Master : MiscEngine<Master> {
    static constexpr std::string_view name = "Master";

    struct Props : Properties<faust_link> {
      Property<float, faust_link> volume = {this, "VOLUME", 0.5, has_limits::init(0, 1), steppable::init(0.01)};
      DECL_REFLECTION(Props, volume);
    } props;

    Master();

    audio::ProcessData<2> process(audio::ProcessData<2>);

  private:
    audio::FaustWrapper<2, 2> faust_;
  };

} // namespace otto::engines
