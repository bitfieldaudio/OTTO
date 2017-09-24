#pragma once

#include <memory>
#include <type_traits>
#include "util/algorithm.hpp"
#include "util/type_traits.hpp"

namespace top1 {

  namespace detail {

    using TypeIndex = std::size_t;

    static constexpr TypeIndex base_index = -1;
    static constexpr TypeIndex invalid_index = -2;

    template<typename Base, typename T, TypeIndex I, typename... Ts>
    struct type_index_impl;

    template<typename Base, typename T, TypeIndex I,
      typename T1, typename... Ts>
    struct type_index_impl<Base, T, I, T1, Ts...> {
      static constexpr TypeIndex value = std::is_same_v<T, T1> ?
        I - 1 - sizeof...(Ts) : type_index_impl<Base, T, I, Ts...>::value;
    };

    template<typename Base, typename T, TypeIndex I>
    struct type_index_impl<Base, T, I> {
      static constexpr TypeIndex value = std::is_same_v<T, Base> ?
        base_index : invalid_index;
    };

    template<typename Base, typename T, typename... Ts>
    using type_index = type_index_impl<Base, T, sizeof...(Ts), Ts...>;

    template<typename Base, typename T, typename... Ts>
    constexpr TypeIndex type_index_v = type_index<Base, T, Ts...>::value;

    template<typename Base, TypeIndex I, typename... Ts>
    struct type_for_index {
      using type = typename std::tuple_element_t<I, std::tuple<Ts...>>;
    };

    template<typename Base, typename... Ts>
    struct type_for_index<Base, base_index, Ts...> {
      using type = Base;
    };

    template<typename Base, typename... Ts>
    struct type_for_index<Base, invalid_index, Ts...> {};

    template<typename Base, TypeIndex I, typename... Ts>
    using type_for_index_t = typename type_for_index<Base, I, Ts...>::type;
  }

  /**
   * A pointer type to help with polymorphism
   *
   * A `poly_ptr` is instantiatetd with a base type, and a list of types
   * that inherit from the base. It is then implicitly convertable to the
   * base class, and explicitly convertible to the child type that currently
   * stored. In this sense, it behaves a bit like a `std::variant`, with the
   * added difference of not providing storage for the enclosed type.
   *
   * Two partial specializations, <top1::poly_ptr> and <top1::unique_poly_ptr>
   * are provided. <top1::poly_ptr> uses raw pointers for storage, and as such
   * ownership should be managed elsewhere. <top1::unique_poly_ptr> uses
   * `std::unique_ptr`, and therefore owns its elements.
   *
   * This is especially useful for storing a predefined set of types,
   * that all inherit from the same base class, in a container.
   * In the TOP-1 it's used for midi events, to be able to store the
   * events in a vector, and only access the subtypes when necessary.
   *
   * You should use either `top1::poly_ptr` or `top1::unique_poly_ptr`
   * in nearly all cases.
   *
   * @Storage The underlying pointer to use for storage.
   *         Must be pointer-like (TODO: define)
   * @Base The base class.
   * @Types All of the possible types. Must all inherit from <Base>.
   */
  template<typename Storage, typename Base, typename... Types>
  class basic_poly_ptr {
    static_assert(std::conjunction_v<std::is_base_of<Base, Types>...>,
      "Base must be a base of all Types...");
    //static_assert(std::is_polymorphic_v<Base>, "Base must be polymorphic");

    /// Used for <match>
    ///
    /// invokes the visitor with the correct derived conversion
    /// @Ret the return type of the visit. Compute using std::common_type
    /// @Ts the types left to check in recursion
    template<typename Visitor, typename Ret, typename... Ts>
    struct visitor_dispatch;

    template<typename Visitor, typename Ret, typename T1, typename... Ts>
    struct visitor_dispatch<Visitor, Ret, T1, Ts...> {
      static Ret apply(basic_poly_ptr* p, Visitor&& v) {
        if constexpr (sizeof...(Ts) > 0) {
            if (p->is<T1>()) {
              if constexpr (std::is_void_v<Ret>) {
                  std::invoke(std::forward<Visitor>(v), p->get<T1>());
                } else {
                return std::invoke(std::forward<Visitor>(v), p->get<T1>());
              }
            } else {
              return visitor_dispatch<Visitor, Ret, Ts...>::apply(
                p, std::forward<Visitor>(v));
            }
          } else {
          if constexpr (std::is_void_v<Ret>) {
              std::invoke(std::forward<Visitor>(v), p->get<T1>());
            } else {
            return std::invoke(std::forward<Visitor>(v), p->get<T1>());
          }
        }
      }
    };

    public:
      // Type traits

    static constexpr detail::TypeIndex invalid_index = detail::invalid_index;
    static constexpr detail::TypeIndex base_index = detail::base_index;

    /// Shorthand for `get_index<T>::value`
    template<typename T>
    static constexpr detail::TypeIndex get_index_v =
      detail::type_index<Base, T, Types...>::value;

    template<detail::TypeIndex I>
    using get_type_t = typename detail::type_for_index<Base, I, Types...>::type;

    /// Member `value` is `true` if `T` is 
    template<typename T>
    using is_valid_type = std::integral_constant<bool,
      get_index_v<T> != invalid_index>;

    /// Shorthand for `is_valid_type<T>::value`
    template<typename T>
    static constexpr bool is_valid_type_v = is_valid_type<T>::value;

    // Member types

    /// Index
    using index_type = detail::TypeIndex;
    /// The underlying storage.
    ///
    /// Alias for <Storage>
    using storage_type = Storage;
    /// The base type. Alias for <Base>
    using base_type = Base;

    /// Default constructor. Stores a nullptr
    basic_poly_ptr();

    /// Construct from storage type
    basic_poly_ptr(const storage_type&);
    /// Move storage into this
    basic_poly_ptr(storage_type&&);

    /// Construct from a pointer to `T`
    ///
    /// @T Must be a valid type.
    /// @t Will be stored. Must have a lifetime at least as long as this object.
    ///    It will be passed to the storage type, which decides what to do with
    ///    it. In the case of a `unique_poly_ptr`, this means <t> will be
    ///    destroyed with this object. With a non-owning `poly_ptr`, the
    ///    lifetime will not be affected.
    template<typename T, typename = is_valid_type<T>>
    basic_poly_ptr(T* t);

    basic_poly_ptr(const basic_poly_ptr&);
    basic_poly_ptr(basic_poly_ptr&&);

    basic_poly_ptr& operator=(basic_poly_ptr);

    /// Check if the `poly_ptr` currently holds a value of type <T>
    ///
    /// @T Must be a valid type.
    /// @return `true` if the currently stored type is `T`,
    ///         or if `T` is <Base>
    template<typename T>
    auto is() const -> std::enable_if_t<is_valid_type_v<T>, bool>;

    /// Check if the `poly_ptr` currently holds a value of type <T>
    ///
    /// @I Must be in range `[-2, sizeof...(Types...))`
    /// @return `true` if the currently stored type is `T`,
    ///         or if `T` is <Base>
    template<index_type I>
    auto is() const -> std::enable_if_t<is_valid_type_v<get_type_t<I>>, bool>;

    /// Get the value of type `T`
    ///
    /// @T Must be a valid type.
    /// @return A reference to the stored value, if the `poly_ptr` is holding a
    ///         type `T`, which is not null. If the `poly_ptr` is holding any
    ///         other type, it will throw `std::bad_cast`
    template<typename T>
    auto get() -> std::enable_if_t<is_valid_type_v<T>, T&>;

    /// Get the value of type with index T
    ///
    /// @I Must be in range `[-2, sizeof...(Types...))`
    /// @return A reference to the stored value, if the `poly_ptr` is holding a
    ///         type `T`, which is not null. If the `poly_ptr` is holding any
    ///         other type, it will throw `std::bad_cast`
    template<index_type I>
    auto get() -> std::enable_if_t<is_valid_type_v<get_type_t<I>>,
      get_type_t<I>&>;

    /// Update the stored value and type
    ///
    /// @T Must be a valid type.
    /// @t Will be stored. It must have a lifetime at least as long as this
    ///    object. It will be passed to the storage type, which decides what to
    ///    do with it. In the case of a `unique_poly_ptr`, this means <t> will
    ///    be destroyed with this object. With a non-owning `poly_ptr`, the
    ///    lifetime will not be affected.
    template<typename T>
    auto operator=(T* t) -> std::enable_if_t<is_valid_type_v<T>,
      basic_poly_ptr&>;

    /// Update the stored value and type
    ///
    /// @T Must be a valid type.
    /// @t Will be stored. It must have a lifetime at least as long as this
    ///    object. It will be passed to the storage type, which decides what to
    ///    do with it. In the case of a `unique_poly_ptr`, this means <t> will
    ///    be destroyed with this object. With a non-owning `poly_ptr`, the
    ///    lifetime will not be affected.
    template<typename T>
    auto operator=(T& t) -> std::enable_if_t<is_valid_type_v<T>,
      basic_poly_ptr&>;

    /// Dereference the stored value as the base class
    ///
    /// This method is what differentiates the `poly_ptr` from a variant of
    /// pointers. In any non-null state, the value can be accessed as a <Base>.
    ///
    /// Invoking this method while the `poly_ptr` is storing null, is undefined
    /// behaviour.
    ///
    /// @return a reference to the stored base.
    base_type& base();

    /// Dereference the internal pointer as <Base>
    ///
    /// An alias to <base()>
    base_type& operator*();

    /// Access the stored value as <Base>*
    base_type* operator->();

    /// Implicitly convert to <Base>*
    operator base_type*();

    /// Pattern matching with lambdas
    ///
    /// TODO: Document
    template<typename... Funcs>
    auto match(Funcs&&... f) -> std::common_type_t<
      std::invoke_result_t<overloaded<Funcs...>, base_type&>,
      std::invoke_result_t<overloaded<Funcs...>, Types&>...>;

    protected:

    index_type index;
    storage_type store;
  };

  /*
   * Helper classes
   */
  namespace detail {

    /// Storage type for `unique_poly_ptr`
    ///
    /// poly_ptr needs some operations that are not supported by
    /// `std::unique_ptr`.
    template<typename T>
    struct unique_poly_storage {

      std::unique_ptr<T> ptr;

      unique_poly_storage(T* ptr = nullptr) : ptr (ptr) {}
      unique_poly_storage(unique_poly_storage& o) = delete;
      unique_poly_storage(unique_poly_storage&& o) : ptr (std::move(o.ptr)) {}

      unique_poly_storage& operator=(unique_poly_storage&& o) {
        ptr = std::move(o.ptr);
        return *this;
      }

      unique_poly_storage& operator=(T* o) {
        ptr.reset(o);
        return *this;
      }

      operator T*() const {return ptr.get();}
      T* operator->() const {return ptr.get();}
      T& operator*() {return *ptr;}

      bool operator==(T* o) const {return ptr == o;}
      bool operator!=(T* o) const {return ptr != o;}
      bool operator<(T* o) const {return ptr < o;}
      bool operator>(T* o) const {return ptr > o;}
      bool operator<=(T* o) const {return ptr <= o;}
      bool operator>=(T* o) const {return ptr >= o;}
    };

  }

  /*
   * Aliases
   */

  template<typename Base, typename... Ts>
  using poly_ptr = basic_poly_ptr<Base*, Base, Ts...>;
  
  template<typename Base, typename... Ts>
  using unique_poly_ptr = basic_poly_ptr<
    detail::unique_poly_storage<Base>, Base, Ts...>;


  /*
   * Implementation
   */

  template<typename S, typename B, typename... Ts>
  basic_poly_ptr<S, B, Ts...>::basic_poly_ptr()
    : index (base_index), store (nullptr) {}

  template<typename S, typename B, typename... Ts>
  basic_poly_ptr<S, B, Ts...>::basic_poly_ptr(const storage_type& ptr)
    : index (base_index), store (ptr) {}

  template<typename S, typename B, typename... Ts>
  basic_poly_ptr<S, B, Ts...>::basic_poly_ptr(storage_type&& ptr)
    : index (base_index), store (std::move(ptr)) {}

  template<typename S, typename B, typename... Ts>
  template<typename T, typename E>
  basic_poly_ptr<S, B, Ts...>::basic_poly_ptr(T* t)
    : index (get_index_v<T>), store (t) {}

  template<typename S, typename B, typename... Ts>
  basic_poly_ptr<S, B, Ts...>::basic_poly_ptr(const basic_poly_ptr& o)
    : index (o.index), store (o.store)  {}

  template<typename S, typename B, typename... Ts>
  basic_poly_ptr<S, B, Ts...>::basic_poly_ptr(basic_poly_ptr&& o)
    : index (std::move(o.index)), store (std::move(o.store))  {}

  template<typename S, typename B, typename... Ts>
  basic_poly_ptr<S, B, Ts...>&
  basic_poly_ptr<S, B, Ts...>::operator=(basic_poly_ptr o) {
    std::swap(store, o.store);
    std::swap(index, o.index);
  }

  template<typename S, typename B, typename... Ts>
  template<typename T>
  auto basic_poly_ptr<S, B, Ts...>::is() const ->
  std::enable_if_t<is_valid_type_v<T>, bool> {
    return index == get_index_v<T>;
  }

  template<typename S, typename B, typename... Ts>
  template<detail::TypeIndex I>
  auto basic_poly_ptr<S, B, Ts...>::is() const ->
  std::enable_if_t<is_valid_type_v<get_type_t<I>>, bool> {
    return index == I;
  }

  template<typename S, typename B, typename... Ts>
  template<typename T>
  auto basic_poly_ptr<S, B, Ts...>::get() ->
  std::enable_if_t<is_valid_type_v<T>, T&> {
    if constexpr (std::is_same_v<T, base_type>) {
        return static_cast<T&>(*store);
      } else {
      if (is<T>()) {
        return static_cast<T&>(*store);
      } else {
        throw std::bad_cast();
      }
    }
  }

  template<typename S, typename B, typename... Ts>
  template<detail::TypeIndex I>
  auto basic_poly_ptr<S, B, Ts...>::get() ->
  std::enable_if_t<is_valid_type_v<get_type_t<I>>, get_type_t<I>&> {
    if constexpr (I == base_index) {
        return static_cast<base_type&>(*store);
      } else {
      if (is<I>()) {
        return static_cast<get_type_t<I>>(*store);
      } else {
        throw std::bad_cast();
      }
    }
  }

  template<typename S, typename B, typename... Ts>
  template<typename T>
  auto basic_poly_ptr<S, B, Ts...>::operator=(T* t) ->
  std::enable_if_t<is_valid_type_v<T>, basic_poly_ptr&> {
    store = storage_type(t);
    index = get_index_v<T>;
    return *this;
  }

  template<typename S, typename B, typename... Ts>
  template<typename T>
  auto basic_poly_ptr<S, B, Ts...>::operator=(T& t) ->
  std::enable_if_t<is_valid_type_v<T>, basic_poly_ptr&> {
    store = storage_type(&t);
    index = get_index_v<T>;
    return *this;
  }

  template<typename S, typename B, typename... Ts>
  auto basic_poly_ptr<S, B, Ts...>::base() -> base_type& {
    return static_cast<base_type&>(*store);
  }

  template<typename S, typename B, typename... Ts>
  auto basic_poly_ptr<S, B, Ts...>::operator*() -> base_type& {
    return base();
  }

  template<typename S, typename B, typename... Ts>
  auto basic_poly_ptr<S, B, Ts...>::operator->() -> base_type* {
    return store;
  }

  template<typename S, typename B, typename... Ts>
  basic_poly_ptr<S, B, Ts...>::operator base_type*() {
    return static_cast<base_type*>(store);
  }

  template<typename S, typename B, typename... Ts>
  template<typename... Funcs>
  auto basic_poly_ptr<S, B, Ts...>::match(Funcs&&... f) ->
  std::common_type_t<std::invoke_result_t<overloaded<Funcs...>, base_type&>,
    std::invoke_result_t<overloaded<Funcs...>, Ts&>...> {
    using Visitor = overloaded<Funcs...>;
    using R = std::common_type_t<
      std::invoke_result_t<Visitor, base_type&>,
      std::invoke_result_t<Visitor, Ts&>...>;

    if constexpr (std::is_void_v<R>) {
        visitor_dispatch<Visitor, R, Ts..., B>::apply(this,
          Visitor(std::forward<Funcs>(f)...));
      } else {
      return visitor_dispatch<Visitor, R, Ts..., B>::apply(this,
        Visitor(std::forward<Funcs>(f)...));
    }
  }
}
