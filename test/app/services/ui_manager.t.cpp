#include "testing.t.hpp"

#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/runtime.hpp"
#include "app/services/ui_manager.hpp"

#include "stubs/audio.hpp"
#include "stubs/graphics.hpp"

using namespace otto;
using namespace services;

using Events = std::vector<midi::IMidiHandler::variant>;

TEST_CASE ("UIManager") {
  drivers::LocalMCUPort port;
  auto app = services::start_app(LogicThread::make(),                                              //
                                 ConfigManager::make(),                                            //
                                 Controller::make([&port] { return &port; }),                      //
                                 Audio::make(std::make_unique<stubs::DummyAudioDriver>),           //
                                 Graphics::make(std::make_unique<stubs::NoProcessGraphicsDriver>), //
                                 UIManager::make());
}
