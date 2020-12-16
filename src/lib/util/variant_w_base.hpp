#pragma once

#include <variant>

#include "lib/util/concepts.hpp"

#include "lib/meta.hpp"

namespace otto::util {

  /// Based on:
  /// SOURCE: https://tower120.github.io/2018/05/18/variant_with_base.html
  template<typename Base, template<typename...> typename Variant_, typename... Types>
  requires(std::is_base_of_v<Base, Types>&&...) //
    struct basic_variant_w_base {
  private:
    using Variant = Variant_<Types...>;
    using Self = basic_variant_w_base<Base, Variant_, Types...>;

    template<class T>
    using is_not_self = std::enable_if_t<!std::is_same_v<std::decay_t<T>, Self>>;

    using TypeList = meta::list<Types...>;

    template<std::size_t I>
    using nth_type = meta::at_t<I, TypeList>;

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
    basic_variant_w_base(const Variant& var) : m_variant(var)
    {
      update_base();
    }
    basic_variant_w_base(Variant&& var) : m_variant(std::move(var))
    {
      update_base();
    }
    basic_variant_w_base(util::different_from<Self> auto&& value) : m_variant(FWD(value))
    {
      update_base();
    }
    template<util::one_of<Types...> T, typename... Args>
    requires std::is_constructible_v<T, Args...> //
    basic_variant_w_base(std::in_place_type_t<T> tag, Args&&... args) : m_variant(tag, std::forward<Args>(args)...)
    {
      update_base();
    }
    template<std::size_t I, typename... Args>
    requires(I < sizeof...(Types)) //
      basic_variant_w_base(std::in_place_index_t<I> tag, Args&&... args)
      : m_variant(tag, std::forward<Args>(args)...)
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

    template<typename T>
    requires std::is_assignable_v<Variant, T> //
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

    template<util::one_of<Types...> T, typename... Args>
    requires std::is_constructible_v<T, Args...> //
      T& emplace(Args&&... args)
    {
      auto& res = m_variant.template emplace<T>(std::forward<Args>(args)...);
      update_base();
      return res;
    }

    template<typename T, typename U, typename... Args>
    requires std::is_constructible_v<T, std::initializer_list<U>, Args...> //
      T& emplace(std::initializer_list<U> il, Args&&... args)
    {
      auto& res = m_variant.template emplace<T>(std::move(il), std::forward<Args>(args)...);
      update_base();
      return res;
    }

    template<std::size_t I, typename... Args>
    requires std::is_constructible_v<nth_type<I>, Args...> //
      auto& emplace(Args&&... args)
    {
      auto& res = m_variant.template emplace<I>(std::forward<Args>(args)...);
      update_base();
      return res;
    }

    template<std::size_t I, typename U, typename... Args>
    requires std::is_constructible_v<nth_type<I>, std::initializer_list<U>, Args...> //
      auto& emplace(std::initializer_list<U> il, Args&&... args)
    {
      auto& res = m_variant.template emplace<I>(std::move(il), std::forward<Args>(args)...);
      update_base();
      return res;
    }

    template<class... Args>
    requires(std::is_constructible_v<Types, Args...>&&...) //
      Base& emplace_by_index(int idx, Args&&... args)
    {
      // Use this recursive lambda to translate idx to a compile time index
      // basically, it auto generates a switch statement for all possible indexes
      const auto impl = [&](auto c_I, auto&& impl) {
        constexpr int I = meta::_v<decltype(c_I)>;
        static_assert(I >= 0, "");
        if (I == idx) {
          emplace<I>(FWD(args)...);
        } else {
          impl(meta::c<I - 1>(), impl);
        }
      };
      impl(meta::c<int(std::variant_size_v<Variant>) - 1>(), impl);
      return *base();
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

    Base& operator*() noexcept
    {
      return *m_base;
    }

    const Base& operator*() const noexcept
    {
      return *m_base;
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

    template<typename Visitor, typename Base_, template<typename...> typename V, typename... Ts>
    friend constexpr decltype(auto) std::visit(Visitor&&, basic_variant_w_base<Base_, V, Ts...>&);

    template<typename Visitor, typename Base_, template<typename...> typename V, typename... Ts>
    friend constexpr decltype(auto) std::get(basic_variant_w_base<Base_, V, Ts...>&);

    template<typename Visitor, typename Base_, template<typename...> typename V, typename... Ts>
    friend constexpr decltype(auto) std::get(basic_variant_w_base<Base_, V, Ts...>&);


    Base* m_base;
    Variant m_variant;

    void update_base()
    {
      m_base = std::visit(
        [](auto& arg) -> Base* {
          using Arg = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<Arg, std::monostate>) {
            return nullptr;
          }

          return static_cast<Base*>(&arg);
        },
        m_variant);
    }
  };

  /// A std::variant where all types have a common base class.
  ///
  /// This allows you to always access this base class without having
  /// to do a std::visit or similar.
  template<typename Base, typename... Types>
  using variant_w_base = basic_variant_w_base<Base, std::variant, Types...>;

} // namespace otto::util

namespace std {

  template<typename Visitor, typename B, template<typename...> typename V, typename... Ts>
  constexpr decltype(auto) visit(Visitor&& vis, otto::util::basic_variant_w_base<B, V, Ts...>& var)
  {
    return std::visit(std::forward<Visitor>(vis), var.variant());
  }

  template<typename T, typename B, template<typename...> typename V, typename... Ts>
  constexpr decltype(auto) get(otto::util::basic_variant_w_base<B, V, Ts...>& var)
  {
    if constexpr (std::is_same_v<T, B>) {
      if (var.base() == nullptr) {
        throw std::bad_variant_access();
      }
      // assert(var.base() != nullptr);
      return *var.base();
    } else {
      return std::get<T>(var.variant());
    }
  }

  template<std::size_t I, typename B, template<typename...> typename V, typename... Ts>
  constexpr decltype(auto) get(otto::util::basic_variant_w_base<B, V, Ts...>& var)
  {
    return std::get<I>(var.variant());
  }

  // TODO: get_if, swap
} // namespace std
