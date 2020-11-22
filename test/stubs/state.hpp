#pragma once

#include <string>
namespace otto::stubs {
  struct [[otto::reflect]] State1 {
    int i1 = 0;
    int i2 = 0;
    struct [[otto::reflect]] Nested {
      float f1 = 0;
      float f2 = 0;
    } nested;
    std::string str1;
    int i3 = 0;
  };

  struct [[otto::reflect]] State2 {
    int i = 0;
    bool operator==(const State2&) const = default;
  };

  namespace simple_states {
    struct [[otto::reflect]] S1 {
      int i1 = 1;
      bool operator==(const S1&) const = default;
    };

    struct [[otto::reflect]] S2 {
      int i2 = 2;
      bool operator==(const S2&) const = default;
    };

    struct [[otto::reflect]] S3 {
      int i3 = 3;
      bool operator==(const S3&) const = default;
    };
  } // namespace simple_states
} // namespace otto::stubs
