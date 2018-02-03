#pragma once

#include <vector>

namespace otto::core::props {

  /// Base class of all properties and property mixins
  struct PropertyBase {

    virtual ~PropertyBase() = default;

    /// Check if this property has the mixin corresponding to `AMixinTag`
    template<typename AMixinTag>
    bool is() const noexcept;

    /// Cast this property to the mixin corresponding to `AMixinTag` if it has it.
    ///
    /// Otherwise, throw TODO
    template<typename AMixinTag>
    AMixinTag& as();

    /// Cast this property to the mixin corresponding to `AMixinTag` if it has it.
    ///
    /// Otherwise, throw TODO
    template<typename AMixinTag>
    const AMixinTag& as() const;
  };

  /// Equality compare two PropertyBase's
  ///
  /// \returns `&lhs == &rhs`
  bool operator==(const PropertyBase& lhs, const PropertyBase& rhs);

  /// Inequality compare two PropertyBase's
  ///
  /// \returns `&lhs != &rhs`
  bool operator!=(const PropertyBase& lhs, const PropertyBase& rhs);

  struct Properties {

    // Accessors //

    std::size_t size() const noexcept;

    PropertyBase& operator[](std::size_t) noexcept;
    const PropertyBase& operator[](std::size_t) const noexcept;

    // Iterators //

    auto begin();
    auto end();
    auto begin() const;
    auto end() const;
    auto cbegin() const;
    auto cend() const;
  };

  struct Property : virtual PropertyBase {

  };

}
