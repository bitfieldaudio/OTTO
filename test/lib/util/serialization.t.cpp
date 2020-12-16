#include "testing.t.hpp"

#include "lib/util/serialization.hpp"

using namespace otto;
namespace otoml = otto::toml;

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
  void serialize_into(otoml::value& toml) const
  {
    toml = i;
  }

  void deserialize_from(const otoml::value& toml)
  {
    i = toml.as_integer();
  }

  DECL_VISIT(str);
};

TEST_CASE ("serialization") {
  static_assert(otoml::ATomlSerializable<int>);
  static_assert(otoml::ATomlSerializable<std::string>);
  static_assert(otoml::ATomlSerializable<std::string_view>);

  static_assert(util::ASerializable<int>);
  static_assert(util::ASerializable<std::string>);
  static_assert(util::ASerializable<std::string_view>);

  REQUIRE(util::serialize(5) == otoml::value(otoml::integer(5)));
  REQUIRE(util::deserialize<int>(otoml::integer(5)) == 5);

  SECTION ("Visitables") {
    static_assert(util::ASerializable<TestObj>);
    SECTION ("serialize") {
      TestObj obj;
      auto toml = util::serialize(obj);
      REQUIRE(toml.as_table() == otoml::table{
                                   {"i", 1},
                                   {
                                     "nested",
                                     otoml::table{{"j", 2}},
                                   },
                                 });
    }
    SECTION ("deserialize") {
      auto toml = otoml::table{
        {"i", 10},
        {
          "nested",
          otoml::table{{"j", 20}},
        },
      };
      auto obj = util::deserialize<TestObj>(toml);
      REQUIRE(obj.i == 10);
      REQUIRE(obj.nested.j == 20);
    }

    SECTION ("serialize preserving comments") {
      auto toml = otoml::from_str(R"(
i = 10
[nested]
# comment
j = 20
)");
      REQUIRE(toml.as_table()["nested"]["j"].comments().size() == 1);
      TestObj obj;
      util::serialize_into(toml, obj);
      REQUIRE(toml.as_table()["nested"]["j"].comments().size() == 1);
    }
  }

  SECTION ("direct member functions") {
    static_assert(util::ASerializable<CustomSer>);
    CustomSer obj = {10};
    REQUIRE(util::serialize(obj).as_integer() == otoml::integer(10));
    util::deserialize_from(otoml::integer(100), obj);
    REQUIRE(obj.i == 100);
  }
}
