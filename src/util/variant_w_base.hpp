#pragma once

#include "util/variant.hpp"

namespace otto::util {

  /// SOURCE: https://tower120.github.io/2018/05/18/variant_with_base.html
  template<class Base, class Variant>
  class basic_variant_w_base {
    using Self = basic_variant_w_base<Base, Variant>;

    template<class Visitor, class Base_, class Variant_>
    friend constexpr decltype(auto) mpark::visit(Visitor&&, basic_variant_w_base<Base_, Variant_>&);

    template<class T, class Base_, class Variant_>
    friend constexpr decltype(auto) std::get(basic_variant_w_base<Base_, Variant_>&);

    template<std::size_t I, class Base_, class Variant_>
    friend constexpr decltype(auto) std::get(basic_variant_w_base<Base_, Variant_>&);


    Base* m_base;
    Variant m_variant;

    void update_base()
    {
      m_base = util::visit(
        [](auto&& arg) -> Base* {
          using Arg = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<Arg, util::monostate>) {
            return nullptr;
          }

          return static_cast<Base*>(&arg);
        },
        m_variant);
    }

    template<class T>
    using is_not_self = std::enable_if_t<!std::is_same_v<std::decay_t<T>, Self>>;

  public:
    basic_variant_w_base()
    {
      update_base();
    }
    basic_variant_w_base(const basic_variant_w_base& other) : m_variant(other.m_variant)
    {
      update_base();
    }
    basic_variant_w_base(basic_variant_w_base&& other) : m_variant(std::move(other.m_variant))
    {
      update_base();
    }
    template<class T, typename = is_not_self<T>>
    basic_variant_w_base(T&& value) : m_variant(std::forward<T>(value))
    {
      update_base();
    }
    basic_variant_w_base(const Variant& var) : m_variant(var)
    {
      update_base();
    }
    basic_variant_w_base(Variant&& var) : m_variant(std::move(var))
    {
      update_base();
    }


    basic_variant_w_base& operator=(const basic_variant_w_base& other)
    {
      m_variant = other.m_variant;
      update_base();
      return *this;
    }
    basic_variant_w_base& operator=(basic_variant_w_base&& other)
    {
      m_variant = std::move(other.m_variant);
      update_base();
      return *this;
    }

    template<class T, typename = is_not_self<T>>
    basic_variant_w_base& operator=(T&& value)
    {
      m_variant = std::forward<T>(value);
      update_base();
      return *this;
    }
    basic_variant_w_base& operator=(const Variant& var)
    {
      m_variant = var;
      update_base();
      return *this;
    }
    basic_variant_w_base& operator=(Variant&& var)
    {
      m_variant = std::move(var);
      update_base();
      return *this;
    }

    template<class T, class... Args>
    T& emplace(Args&&... args)
    {
      auto& res = m_variant.template emplace<T>(std::forward<Args>(args)...);
      update_base();
      return res;
    }

    template<class T, class U, class... Args>
    T& emplace(std::initializer_list<U> il, Args&&... args)
    {
      auto& res = m_variant.template emplace<T>(std::move(il), std::forward<Args>(args)...);
      update_base();
      return res;
    }

    constexpr bool operator==(const basic_variant_w_base& other) const noexcept
    {
      return m_variant == other.m_variant;
    }
    constexpr bool operator!=(const basic_variant_w_base& other) const noexcept
    {
      return m_variant != other.m_variant;
    }


    Base* base() noexcept
    {
      return m_base;
    }
    const Base* base() const noexcept
    {
      return m_base;
    }

    Base* operator->() noexcept
    {
      return m_base;
    }

    Base* operator->() const noexcept
    {
      return m_base;
    }

    int index() const noexcept
    {
      return m_variant.index();
    }

    const Variant& variant() const
    {
      return m_variant;
    }

  private:
    // deny untracked changes
    Variant& variant()
    {
      return m_variant;
    }
  };

  template<typename Base, typename... Types>
  using variant_w_base = basic_variant_w_base<Base, util::variant<Types...>>;


} // namespace otto::util

namespace std {

  template<class Visitor, class Base, class Variant>
  constexpr decltype(auto) visit(Visitor&& vis,
                                 otto::util::basic_variant_w_base<Base, Variant>& var)
  {
    return std::visit(std::forward<Visitor>(vis), var.variant());
  }

  template<class T, class Base, class Variant>
  constexpr decltype(auto) get(otto::util::basic_variant_w_base<Base, Variant>& var)
  {
    if constexpr (std::is_same_v<T, Base>) {
      if (var.base() == nullptr) {
        throw otto::util::bad_variant_access();
      }
      // assert(var.base() != nullptr);
      return *var.base();
    } else {
      return std::get<T>(var.variant());
    }
  }

  template<std::size_t I, class Base, class Variant>
  constexpr decltype(auto) get(otto::util::basic_variant_w_base<Base, Variant>& var)
  {
    return std::get<I>(var.variant());
  }

  // TODO: get_if, swap
} // namespace std
