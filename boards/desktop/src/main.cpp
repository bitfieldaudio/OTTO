#include <csignal>

#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/itc.hpp"
#include "lib/itc/reducer.hpp"

#include "app/engines/synths/ottofm/ottofm.hpp"
#include "app/layers/navigator.hpp"
#include "app/layers/piano_key_layer.hpp"
#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/led_manager.hpp"
#include "app/services/logic_thread.hpp"
#include "app/services/runtime.hpp"
#include "app/services/ui_manager.hpp"

#include "board/midi_driver.hpp"

using namespace otto;

int main(int argc, char* argv[])
{
  using namespace services;
  auto app = start_app(ConfigManager::make_default(), //
                       LogicThread::make(),           //
                       Controller::make(),            //
                       Audio::make(),                 //
                       Graphics::make()               //
  );

  itc::ChannelGroup chan;
  auto eng = engines::ottofm::factory.make_all(chan);

  std::signal(SIGINT, [](int sig) {
    core::ServiceAccessor<Runtime> runtime;
    LOGI("Got SIGINT, stopping...");
    runtime->request_stop();
    std::signal(SIGINT, SIG_DFL);
  });

  app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
    const auto res = eng.audio->process();
    stdr::copy(util::zip(res, res), data.output.begin());
  });

  LayerStack layers;
  auto piano = layers.make_layer<PianoKeyLayer>(app.service<Audio>().midi());
  auto nav_km = layers.make_layer<NavKeyMap>();
  nav_km.bind_nav_key(Key::synth, eng.main_screen);
  nav_km.bind_nav_key(Key::envelope, eng.mod_screen);

  RtMidiDriver rt_midi_driver;

  LedManager ledman;
  app.service<Graphics>().show([&](skia::Canvas& ctx) {
    ledman.process(layers);
    nav_km.nav().draw(ctx);
  });
  app.service<Controller>().set_input_handler(layers);

  app.wait_for_stop();
  app.service<ConfigManager>().write_to_file();
  LOGI("Shutting down");
  return 0;
}
