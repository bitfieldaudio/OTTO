#include "graphics.t.hpp"
#include "testing.t.hpp"
#include "wifi_selector_screen.hpp"

namespace otto {

  using namespace core::engine;
  using namespace core::input;
  using namespace core::props;

  using namespace board::wifi;

  struct TestWFMan : board::wifi::WiFiManager
  {
    std::array<Network, 4> networks = {{
    {"PrettyFlyForAWiFi"},
    {"It Hurts When IP"},
    {"Kogle69Skinke04Hybel"},
    {"Yell Penis for password"},}};

    gsl::span<Network> get_networks() override 
    {
      return networks;
    }
  };
  

  TEST_CASE ("[graphics] WiFiScreen" * doctest::skip()) {
    using Sender = itc::DirectActionSender<NetworkSelectorScreen>;

    TestWFMan wfman;
    board::wifi::NetworkSelectorScreen screen{wfman};

    Sender sender = {screen};

    struct Props : InputHandler {
      Sender sender;

      itc::PropTypes<struct selected_network_tag, int>::Prop<Sender> selected_network_idx = {sender, 0, limits(0, 3)};

      Props(const Sender& sender) : sender(sender) {}
    } props{sender};

    test::show_gui([&](nvg::Canvas& ctx) { 
      screen.draw(ctx);
    }, &props);
  }

  

} // namespace otto
