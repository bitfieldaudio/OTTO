#include "testing.t.hpp"

#include "util/dyn-array.hpp"

SCENARIO("DynArrays can be resized", "[DynArray]") {

  GIVEN("A DynArray of ints, with initial size 0") {
    top1::util::dyn_array<int> a(0);

    WHEN("It is newly initialized") {
      THEN("the size is 0") {
        REQUIRE(a.size() == 0);
      }
    }

    WHEN("It is resized to a greater number") {

      int newSize = Random::get(10, 30);
      CAPTURE(newSize);
      a.resize(newSize);

      THEN("the size changes") {
        REQUIRE(a.size() == newSize);
      }

      THEN("all elements are 0") {
        REQUIRE(std::all_of(std::begin(a), std::end(a),
            [](auto&& a) {return a == 0;}));
      }
    }

    WHEN("It is resized to a smaller number") {

      int newSize = Random::get(1, 10);
      CAPTURE(newSize);
      a.resize(newSize);

      THEN("the size changes") {
        REQUIRE(a.size() == newSize);
      }

      THEN("all elements are 0") {
        REQUIRE(std::all_of(std::begin(a), std::end(a),
            [](auto&& a) {return a == 0;}));
      }
    }

    WHEN("It is resized to zero") {
      a.resize(0);

      THEN("the size changes") {
        REQUIRE(a.size() == 0);
      }
    }
  }
}

SCENARIO("DynArrays can be random-accessed", "[DynArray]") {
  GIVEN("A DynArray of floats with a size greater than 0") {
    const int size = Random::get(10, 30);
    top1::util::dyn_array<float> a(size);
    CAPTURE(size);

    WHEN("It is newly initialized") {

      THEN("the size is as initialized") {
        REQUIRE(a.size() == size);
      }

      THEN("all elements are 0") {
        REQUIRE(std::all_of(std::begin(a), std::end(a),
            [](auto&& a) {return a == 0;}));
      }
    }

    WHEN("An element is changed using the [] operator") {

      const int index = Random::get(0, size);
      CAPTURE(index);
      const float newValue = Random::get<float>(0.0, std::numeric_limits<float>::max());
      CAPTURE(newValue);

      a[index] = newValue;

      THEN("Accessing the same element will yield the set value") {
        REQUIRE(a[index] == newValue);
      }
    }
  }
}

SCENARIO("DynArrays can be cleared", "DynArray") {

  GIVEN("A DynArray of floats with a size greater than 0") {
    const int size = Random::get(10, 30);
    top1::util::dyn_array<float> a(size);
    CAPTURE(size);

    WHEN("All values are initialized with random values") {
      for (int i = 0; i < size; i++) {
        a[i] = Random::get(std::numeric_limits<float>::min(),
          std::numeric_limits<float>::max());
      }
    }

    WHEN("The array is cleared") {
      a.clear();

      THEN("Its size is preserved") {
        REQUIRE(a.size() == size);
      }

      THEN("All elements are 0") {
        REQUIRE(std::all_of(std::begin(a), std::end(a),
            [](auto&& a) {return a == 0;}));
      }
    }
  }
}

// TODO: more
