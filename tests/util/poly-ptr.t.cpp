#include "../testing.t.hpp"

#include "util/poly-ptr.hpp"

namespace top1 {

  struct Base {
    int base_field = 4;
    virtual ~Base() {}
  };

  struct A : Base {
    float a_field = 32.32;
  };

  struct B : Base {
    float b_field = -0.2;
  };

  using PP = poly_ptr<Base, A, B>;
  using UPP = unique_poly_ptr<Base, A, B>;

  // Static asserts
  static_assert(UPP::get_index_v<Base> == UPP::base_index);
  static_assert(UPP::get_index_v<A> == 0);
  static_assert(UPP::get_index_v<B> == 1);
  static_assert(UPP::is_valid_type_v<A>);
  static_assert(UPP::is_valid_type_v<B>);
  static_assert(UPP::is_valid_type_v<Base>);
  static_assert(!UPP::is_valid_type_v<int>);
  static_assert(!UPP::is_valid_type_v<UPP>);
  static_assert(!UPP::is_valid_type_v<Base*>);
  static_assert(!UPP::is_valid_type_v<Base&>);
  static_assert(std::is_same_v<UPP::get_type_t<0>, A>);
  static_assert(std::is_same_v<UPP::get_type_t<1>, B>);
  static_assert(std::is_same_v<UPP::get_type_t<UPP::base_index>, Base>);
  static_assert(std::is_same_v<PP::storage_type, Base*>);

  TEST_CASE("Poly Pointer", "[util] [poly-ptr]") {

    PP p;

    REQUIRE(p == nullptr);
    REQUIRE(p.is<Base>());

    auto b = new Base();

    p = b;

    REQUIRE(p == b);
    REQUIRE(p.is<Base>());
    REQUIRE(!p.is<A>());
    REQUIRE(!p.is<B>());
    REQUIRE(&p.get<Base>() == b);
    REQUIRE_THROWS(p.get<A>());
    REQUIRE(&*p == &p.base());
  }

  TEST_CASE("Unique Poly Pointer", "[util] [poly-ptr]") {

    UPP p;

    REQUIRE(p == nullptr);

    auto b = new Base();

    p = b;

    REQUIRE(p == b);
    REQUIRE(p.is<Base>());
    REQUIRE(!p.is<A>());
    REQUIRE(!p.is<B>());
    REQUIRE(&p.get<Base>() == b);
    REQUIRE_THROWS(p.get<A>());
    REQUIRE(&*p == &p.base());

    auto a = new A();

    p = a;

    REQUIRE(p == a);
    REQUIRE(p.is<A>());
    REQUIRE(!p.is<B>());
    REQUIRE(!p.is<Base>());
    REQUIRE(&p.get<A>() == a);
    REQUIRE(&p.get<Base>() == a);
    REQUIRE_THROWS(p.get<B>());

    UPP pb (new B());

    REQUIRE(pb.is<B>());
  }

  TEST_CASE("Poly Pointer pattern matching", "[util], [poly-ptr]") {

    PP p;

    bool fail = true;
    p.match([&](A& a) {
        fail = true;
      }, [&] (B& b) {
        fail = true;
      }, [&] (Base& ba) {
        fail = false;
      });

    REQUIRE(fail == false);
    fail = true;

    p = new B();

    p.match([&](A& a) {
        fail = true;
      }, [&] (B& b) {
        fail = false;
      }, [&] (Base& ba) {
        fail = true;
      });

    REQUIRE(fail == false);
  }

  // Test to make sure `top1::audio::ProcessData` works
    TEST_CASE("Oddly specific Poly Pointer test", "[util] [poly-ptr]") {

    struct S {
      mutable std::vector<PP> vec;
    };

    const S s;

    s.vec.push_back(new A());

    s.vec[0]->base_field = 32;
  }
}
