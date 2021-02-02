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

struct CustomInt {
  int i = 0;
  void serialize_into(json::value& json) const
  {
    json = i;
  }

  void deserialize_from(const json::value& json)
  {
    i = json.get<int>();
  }

  bool operator==(const CustomInt&) const = default;

  friend std::ostream& operator<<(std::ostream& s, const CustomInt& self)
  {
    return s << self.i;
  }
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
  }

  SECTION ("direct member functions") {
    static_assert(util::ASerializable<CustomSer>);
    CustomSer obj = {10};
    REQUIRE(util::serialize(obj) == json::value(10));
    util::deserialize_from(json::value(100), obj);
    REQUIRE(obj.i == 100);
  }

  SECTION ("Vectors") {
    std::vector<CustomInt> input = {{1}, {2}, {3}, {4}};
    SECTION ("deserialize(serialize(x)) == x") {
      REQUIRE_THAT(util::deserialize<std::vector<CustomInt>>(util::serialize(input)), Catch::Matchers::Equals(input));
    }
    SECTION ("deserialize_from clears the vector") {
      std::vector<CustomInt> res = {{10}, {11}, {12}};
      util::deserialize_from(util::serialize(input), res);
      REQUIRE_THAT(res, Catch::Matchers::Equals(input));
    }
    SECTION ("serialize_into clears the json array") {
      std::vector<CustomInt> v2 = {{10}, {11}, {12}, {13}, {14}, {15}, {16}};
      auto json = util::serialize(v2);
      util::serialize_into(json, input);
      REQUIRE_THAT(util::deserialize<std::vector<CustomInt>>(json), Catch::Matchers::Equals(input));
    }
  }

  SECTION ("std::array") {
    const std::array<CustomInt, 4> ar = {{{1}, {2}, {3}, {4}}};
    SECTION ("deserialize(serialize(x)) == x") {
      REQUIRE((util::deserialize<std::array<CustomInt, 4>>(util::serialize(ar))) == ar);
    }
    SECTION ("deserialize_from throws when array size is wrong") {
      auto arcp = ar;
      auto json = json::array{10, 10, 10};
      REQUIRE_THROWS_AS(util::deserialize_from(json, arcp), std::invalid_argument);
    }
  }

  SECTION ("Enums") {
    enum struct TestEnum {
      enum1,
      enum2,
      enum3,
    };

    REQUIRE(util::serialize(TestEnum::enum1) == "enum1");
    REQUIRE(util::serialize(TestEnum::enum2) == "enum2");
    REQUIRE(util::deserialize<TestEnum>("enum1") == TestEnum::enum1);
    REQUIRE(util::deserialize<TestEnum>("enum2") == TestEnum::enum2);

    REQUIRE_THROWS_AS(util::deserialize<TestEnum>("no_such_enum"), std::invalid_argument);
  }

  SECTION ("chrono::duration") {
    using namespace std::chrono_literals;
    const auto time = chrono::days(14) + 2h + 23min + 5s + 32ms + 14us + 13ns;
    REQUIRE(util::deserialize<chrono::duration>(util::serialize(time)) == time);
  }
}
