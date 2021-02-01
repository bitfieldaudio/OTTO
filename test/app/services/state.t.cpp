#include "testing.t.hpp"

#include "app/services/state.hpp"

#include "stubs/state.hpp"

using namespace otto;

TEST_CASE ("StateManager") {
  int i1 = 1;
  int i2 = 2;
  auto path = test::temp_file("statemanager.toml");
  services::StateManager stateman{path};
  stateman.add("Test", util::visitable([&](auto&& visit) {
                 visit("i1", i1);
                 visit("i2", i2);
               }));
  SECTION ("Basic") {
    stateman.write_to_file();
    i1 = 20;
    i2 = 30;
    stateman.read_from_file();
    REQUIRE(i1 == 1);
    REQUIRE(i2 == 2);
  }

  SECTION ("Ignore missing keys") {
    using namespace otto::toml::literals;
    const auto input = R"(
[Test]
i1 = 10
    )"_toml;
    util::deserialize_from(input, stateman);
    REQUIRE(i1 == 10);
  }

  SECTION ("Preserve unused options") {
    std::ofstream fs;
    fs.open(path);
    fs << otto::toml::value{{"unknown", 1234}};
    fs.close();
    stateman.read_from_file();
    stateman.write_to_file();
    auto val = otto::toml::parse(path);
    REQUIRE(val["unknown"] == otto::toml::value(1234));
    REQUIRE(val["Test"]["i1"] == otto::toml::value(1));
  }
}
