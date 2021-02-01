#include "testing.t.hpp"

#include "lib/util/serialization.hpp"

using namespace otto;

struct TestObj {
  int i = 1;
  struct Nested {
    int j = 2;
    DECL_VISIT(j);
  };

  Nested nested;
  DECL_VISIT(i, nested);
};

struct CustomSer {
  int i = 0;
  std::string str = "hello";
  void serialize_into(json::value& json) const
  {
    json = i;
  }

  void deserialize_from(const json::value& json)
  {
    i = json.get<int>();
  }

  DECL_VISIT(str);
};

TEST_CASE ("serialization") {
  static_assert(json::AJsonSerializable<int>);
  static_assert(json::AJsonSerializable<std::string>);
  static_assert(json::AJsonSerializable<std::string_view>);

  static_assert(util::ASerializable<int>);
  static_assert(util::ASerializable<std::string>);
  static_assert(util::ASerializable<std::string_view>);

  REQUIRE(util::serialize(5) == json::value(5));
  REQUIRE(util::deserialize<int>(json::value(5)) == 5);

  SECTION ("Visitables") {
    static_assert(util::ASerializable<TestObj>);
    SECTION ("serialize") {
      TestObj obj;
      auto json = util::serialize(obj);
      REQUIRE(json == json::object{
                        {"i", 1},
                        {"nested",
                         {
                           {"j", 2},
                         }},
                      });
    }
    SECTION ("deserialize") {
      auto json = json::object{
        {"i", 10},
        {
          "nested",
          json::object{{"j", 20}},
        },
      };
      auto obj = util::deserialize<TestObj>(json);
      REQUIRE(obj.i == 10);
      REQUIRE(obj.nested.j == 20);
    }

    SECTION ("direct member functions") {
      static_assert(util::ASerializable<CustomSer>);
      CustomSer obj = {10};
      REQUIRE(util::serialize(obj) == json::value(10));
      util::deserialize_from(json::value(100), obj);
      REQUIRE(obj.i == 100);
    }
  }
}
