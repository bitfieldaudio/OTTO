#include "../testing.t.hpp"

#include <iterator>

#include "util/bytefile.hpp"
#include "util/algorithm.hpp"

namespace top1 {

  TEST_CASE("Bytefile", "[util]") {

    ByteFile::Path somePath = "testdata/test1.bytes";

    ByteFile f;

    SECTION("Open / close") {

      REQUIRE(!f.is_open());
      REQUIRE_NOTHROW(f.open(somePath));

      REQUIRE_NOTHROW(f.close());

      REQUIRE(!f.is_open());
      // REQUIRE(filesystem::exists(somePath));
      // REQUIRE(filesystem::is_regular_file(somePath));
    }

    SECTION("seek") {

      ByteFile::Position somePos = 10;

      REQUIRE(!f.is_open());
      REQUIRE_THROWS_AS(f.position(), ByteFile::Error);

      REQUIRE_NOTHROW(f.open(somePath));
      REQUIRE_NOTHROW(f.position() == 0);

      REQUIRE_NOTHROW(f.seek(somePos) == somePos);
    }

    SECTION("Write / Read bytes") {

      constexpr std::size_t someSize = 2048;

      REQUIRE_NOTHROW(f.open(somePath));

      std::array<std::byte, someSize> bytes;

      REQUIRE_NOTHROW(f.write_bytes(bytes.begin(), bytes.end()));
      REQUIRE_NOTHROW(f.position() == someSize);
      REQUIRE_NOTHROW(f.size() == someSize);
      REQUIRE_NOTHROW(f.close());

      std::array<std::byte, someSize> readBytes;
      REQUIRE_NOTHROW(f.open(somePath));
      REQUIRE_NOTHROW(f.read_bytes(readBytes.begin(), readBytes.end()));

      REQUIRE_NOTHROW(f.position() == someSize);
      REQUIRE_NOTHROW(f.size() == someSize);

      // Compare arrays
      REQUIRE(std::equal(readBytes.begin(), readBytes.end(), bytes.begin()));
    }
  }

}
