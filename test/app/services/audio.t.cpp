#include "app/services/config.hpp"
#include "testing.t.hpp"

#include <Gamma/Oscillator.h>

#include "app/services/audio.hpp"
#include "app/services/impl/runtime.hpp"

using namespace otto;
using namespace otto::services;
using namespace std::literals;

TEST_CASE (test::interactive() * "audio_loopback") {
  auto app = start_app(core::make_handle<ConfigManager>(), Audio::make_board());
  app.service<Audio>().set_process_callback([](Audio::CallbackData& data) { data.output = data.input; });
  std::this_thread::sleep_for(2s);
}

TEST_CASE (test::interactive() * "audio_sine") {
  auto app = start_app(core::make_handle<ConfigManager>(), Audio::make_board());
  gam::Sine<> osc = {440};
  app.service<Audio>().set_process_callback([&](Audio::CallbackData& data) {
    std::ranges::generate(data.output.left, osc);
    std::ranges::copy(data.output.left, data.output.right.begin());
  });
  std::this_thread::sleep_for(2s);
}
