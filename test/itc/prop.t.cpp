#include "testing.t.hpp"

#include "core/engine/engine.hpp"
#include "itc/itc.hpp"

namespace otto::engines::test_engine {

  using namespace core;
  using namespace itc;

  struct Audio;
  struct Screen;

  using AudioAQH = ActionQueueHelper<Audio>;
  using GraphicsAQH = ActionQueueHelper<Screen>;
  using Aqh = JoinedActionQueueHelper<AudioAQH, GraphicsAQH>;

  struct Props {
    Aqh* aqh;

    Aqh::Prop<struct float_prop_tag, float> float_prop = {aqh, 0};
    Aqh::Prop<struct int_prop_tag, int> int_prop = {aqh, 0};
    Aqh::Prop<struct int_prop_tag, int, props::has_limits> int_prop_w_limits = {aqh, 0, props::limits(0, 10)};
  };

  struct Audio {};

  struct Engine : engine::MiscEngine<Engine> {
    static constexpr util::string_ref name = "TestEngine";
    using Props = Props;

    Props props;
  };
} // namespace otto::engines::test_engine
