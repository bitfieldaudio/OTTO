#include "testing.t.hpp"

#include "core/engine/engine.hpp"
#include "itc/itc.hpp"

namespace otto::engines::test_engine {

  using namespace core;
  using namespace itc;

  struct Audio;
  struct Screen;

  using AudioAQH = ActionSender<Audio>;
  using GraphicsAQH = ActionSender<Screen>;
  using Sndr = JoinedActionSender<AudioAQH, GraphicsAQH>;

  struct Props {
    Sndr* sndr;

    Sndr::Prop<struct float_prop_tag, float> float_prop = {sndr, 0};
    Sndr::Prop<struct int_prop_tag, int> int_prop = {sndr, 0};
    Sndr::Prop<struct int_prop_tag, int, props::has_limits> int_prop_w_limits = {sndr, 0, props::limits(0, 10)};
  };

  struct Audio {};

  struct Engine : engine::MiscEngine<Engine> {
    static constexpr util::string_ref name = "TestEngine";
    using Props = Props;

    Props props;
  };
} // namespace otto::engines::test_engine
