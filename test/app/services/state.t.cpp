#include "testing.t.hpp"

#include "app/services/state.hpp"

#include "app/services/runtime.hpp"

#include "stubs/state.hpp"

using namespace otto;

TEST_CASE ("StateManager") {
  int i1 = 1;
  int i2 = 2;
  auto path = test::temp_file("statemanager.json");
  services::StateManager stateman{path};
  auto v = util::visitable([&](auto&& visit) {
    visit("i1", i1);
    visit("i2", i2);
  });
  stateman.add("Test", std::ref(v));
  SECTION ("Basic") {
    stateman.write_to_file();
    i1 = 20;
    i2 = 30;
    stateman.read_from_file();
    REQUIRE(i1 == 1);
    REQUIRE(i2 == 2);
  }

  SECTION ("Ignore missing keys") {
    const auto input = json::object{
      {"Test",
       {
         {"i1", 10},
       }},
    };
    util::deserialize_from(input, stateman);
    REQUIRE(i1 == 10);
  }

  // SECTION ("Preserve unused options") {
  //   std::ofstream fs;
  //   json::write_to_file(json::object{{"unknown", 1234}}, path);
  //   stateman.read_from_file();
  //   stateman.write_to_file();
  //   auto val = json::parse_file(path);
  //   REQUIRE(val["unknown"] == json::value(1234));
  //   REQUIRE(val["Test"]["i1"] == json::value(1));
  // }

  SECTION ("Do not preserve unused options") {
    std::ofstream fs;
    json::write_to_file(json::object{{"unknown", 1234}}, path);
    stateman.read_from_file();
    stateman.write_to_file();
    auto val = json::parse_file(path);
    REQUIRE(val.contains("unknown") == false);
    REQUIRE(val["Test"]["i1"] == json::value(1));
  }
}

struct StubSer {
  ~StubSer()
  {
    ++destructed;
  }
  int i = 1;
  int j = 2;
  DECL_VISIT(i, j);

  inline static int destructed = 0;
};

TEST_CASE ("StateManager destruction 2") {
  using namespace services;
  {
    RuntimeController rt;
    StubSer st;

    auto path = test::temp_file("statemanager.json");
    {
      StateManager stateman(path);
      stateman.add("Test", std::ref(st));

      stateman.read_from_file();
      rt.wait_for_stop(1s);
      stateman.write_to_file();
    }
    REQUIRE(StubSer::destructed == 0);
  }
  REQUIRE(StubSer::destructed == 1);
}
