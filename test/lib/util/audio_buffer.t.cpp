#include <tl/optional.hpp>
#include "testing.t.hpp"

#include "lib/util/audio_buffer.hpp"

using namespace otto;

namespace rngs = std::ranges;

TEST_CASE ("audio_buffer") {
  std::int8_t refc = 0;
  std::vector<float> data = {0, 0.1, 0.2, 0.3, 0.4, 0.5};
  SUBCASE ("scoped reference counting") {
    {
      util::audio_buffer ab = util::audio_buffer(std::span(data), &refc);
      REQUIRE(refc == 1);
      REQUIRE(rngs::equal(data, ab));
    }
    REQUIRE(refc == 0);
  }

  SUBCASE ("Disable refcount with nullptr") {
    // No REQUIRE, the test is that we dont get a segfault
    util::audio_buffer ab = util::audio_buffer(data, nullptr);
  }
}

TEST_CASE ("AudioBufferPool") {
  auto abp = util::AudioBufferPool(8, 64);

  auto idx = [&abp](util::audio_buffer& ab) { return (ab.data() - abp.data().data()) / 64; };

  SUBCASE ("allocate single") {
    auto buf = abp.allocate();
    REQUIRE(buf.size() == 64);
    REQUIRE(idx(buf) == 0);
  };

  SUBCASE ("allocate multiple") {
    tl::optional b1 = abp.allocate();
    tl::optional b2 = abp.allocate();
    REQUIRE(b2->size() == 64);
    REQUIRE(idx(*b1) == 0);
    REQUIRE(idx(*b2) == 1);
    b1 = tl::nullopt;
    auto b3 = abp.allocate();
    REQUIRE(idx(b3) == 0);
  };

  SUBCASE ("allocate larger buffer") {
    tl::optional b1 = abp.allocate(1);
    tl::optional b2 = abp.allocate(2);
    tl::optional b3 = abp.allocate(1);
    REQUIRE(b2->size() == 64 * 2);
    REQUIRE(idx(*b2) == 1);
    REQUIRE(idx(*b3) == 3);
  };

  SUBCASE ("allocate larger buffer in between smaller ones") {
    tl::optional b0 = abp.allocate();
    tl::optional b1 = abp.allocate();
    tl::optional b2 = abp.allocate();
    tl::optional b3 = abp.allocate();
    tl::optional b4 = abp.allocate();
    tl::optional b5 = abp.allocate();
    b1 = tl::nullopt;
    b3 = tl::nullopt;
    b4 = tl::nullopt;
    tl::optional b6 = abp.allocate(2);
    REQUIRE(idx(*b6) == 3);
    b6 = tl::nullopt;
    b1 = abp.allocate();
    b3 = abp.allocate();
    b4 = abp.allocate();
    REQUIRE(idx(*b1) == 1);
    REQUIRE(idx(*b3) == 3);
    REQUIRE(idx(*b4) == 4);
  };
}
