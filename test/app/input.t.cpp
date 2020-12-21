#include "testing.t.hpp"

#include "app/input.hpp"

using namespace otto;

TEST_CASE ("All keys are in a key_group") {
  auto all_groups = key_groups::piano | key_groups::func | key_groups::enc_clicks;
  CAPTURE(all_groups);
  REQUIRE(all_groups.all());
}
