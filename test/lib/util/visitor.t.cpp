#include "testing.t.hpp"

#include "lib/util/visitor.hpp"

using namespace otto;

struct S1 {
  int i = 0;
  float f = 1.f;
  std::string s = "hello";

  void visit(util::AVisitorOf<int, float, std::string> auto& visitor)
  {
    visitor("i", i);
    visitor("f", f);
    visitor("s", s);
  };
};

TEST_CASE ("Visitor") {
  std::string str;
  auto v1 = util::overloaded([&](util::string_ref name, const int& i) { str += fmt::format("{}{}", name, i); },
                             [&](util::string_ref name, const float& f) { str += fmt::format("{}{:.0}", name, f); },
                             [&](util::string_ref name, const std::string& s) { str += fmt::format("{}{}", name, s); });

  SUBCASE ("manually declared visitable") {
    S1 s1;
    s1.visit(v1);
    REQUIRE(str == "i0f1shello");
  }
}

struct S2 {
  int i2 = 0;
  S1 s1;

  DECL_VISIT(i2, s1)
};

struct V2 {
  void operator()(util::string_ref name, const auto& i)
  {
    str += fmt::format("{}{}", name, i);
  }
  void operator()(util::string_ref name, S1& s)
  {
    str += name;
    str += "{";
    s.visit(*this);
    str += "}";
  }
  std::string str;
} v2;

TEST_CASE ("Visitor") {
  SUBCASE ("DECL_VISIT") {
    S2 s2;
    s2.visit(v2);
    REQUIRE(v2.str == "i20s1{i0f1.0shello}");
  }
}
