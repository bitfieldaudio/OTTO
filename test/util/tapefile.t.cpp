#include "../testing.t.hpp"

#include "util/tapefile.hpp"

namespace otto::util {

  bool operator==(const TapeFile::SliceData& l, const TapeFile::SliceData& r) {
    return l.in == r.in && l.out == r.out;
  }

  TapeFile f {};

  TEST_CASE("Slices", "[TapeFile] [util]") {
    fs::path somePath = test::dir / "test1.tape";

    f.open(somePath);

    REQUIRE(std::all_of(std::begin(f.slices), std::end(f.slices),
        [] (auto&& slices) {
          return slices.count == 0;
        }));

    std::array<TapeFile::SliceData, 128> testData;
    std::generate(std::begin(testData), std::end(testData),
      [] () -> TapeFile::SliceData {
        return {Random::get<uint32_t>(), Random::get<uint32_t>()};
      });

    std::copy(std::begin(testData), std::end(testData),
      std::begin(f.slices[0].array));

    f.close();

    f.open(somePath);

    REQUIRE(std::equal(std::begin(testData), std::end(testData),
        std::begin(f.slices[0].array)));
  }
}
