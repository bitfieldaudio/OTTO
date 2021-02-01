#pragma once

#include <string>

#include "lib/util/serialization.hpp"

namespace otto::stubs {
  struct State1 {
    int i1 = 0;
    int i2 = 0;
    struct Nested {
      float f1 = 0;
      float f2 = 0;
      struct Level2 {
        bool b1 = false;
        bool b2 = false;
        DECL_VISIT(b1, b2);
      } level2;
      DECL_VISIT(f1, f2, level2);
    } nested;
    std::string str1;
    int i3 = 0;
    DECL_VISIT(i1, i2, nested, str1, i3)
  };

  struct State2 {
    int i = 0;
    DECL_VISIT(i);
    bool operator==(const State2&) const = default;
  };

  struct NonSerializableState {
    int i1 = 0;
    std::string str = "hello";
    bool operator==(const NonSerializableState&) const = default;
  };

  namespace simple_states {
    struct S1 {
      int i1 = 1;
      DECL_VISIT(i1);
      bool operator==(const S1&) const = default;
    };

    struct S2 {
      int i2 = 2;
      DECL_VISIT(i2);
      bool operator==(const S2&) const = default;
    };

    struct S3 {
      int i3 = 3;
      DECL_VISIT(i3);
      bool operator==(const S3&) const = default;
    };
  } // namespace simple_states
} // namespace otto::stubs
