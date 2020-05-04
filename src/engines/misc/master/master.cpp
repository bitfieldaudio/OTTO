#include "master.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "util/math.hpp"

#include "audio.hpp"
#include "screen.hpp"

namespace otto::engines::master {

  using namespace core::input;

  Master::Master(itc::ActionChannel channel)
    : audio(std::make_unique<Audio>()),
      screen_(std::make_unique<Screen>())
  {
    set_children(props, audio, screen_);
    register_to(channel);
    props.send_actions();
  }

  void Master::encoder(EncoderEvent e)
  {
    switch (e.encoder){
    case Encoder::blue: props.volume.step(e.steps); break;
    case Encoder::green: props.volume.step(e.steps); break;
    case Encoder::yellow: props.volume.step(e.steps); break;
    case Encoder::red: props.tempo.step(e.steps); break;
    }
  }

  core::ui::ScreenAndInput Master::screen()
  {
    return {*screen_, *this};
  }

} // namespace otto::engines

