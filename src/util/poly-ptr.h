#pragma once

#include <type_traits>
#include <memory>
#include <tuple>

namespace top1 {

namespace detail {
// Implementations of C++17 std::conjunction/std::disjunction
template<typename...>
struct conjunction : std::true_type {};

template<typename B1>
struct conjunction<B1> : B1 {};

template<typename B1, typename B2>
struct conjunction<B1, B2> : std::conditional<B1::value, B2, B1>::type {};

template<typename B1, typename... Bs>
struct conjunction<B1, Bs...> : std::conditional<B1::value, conjunction<Bs...>, B1>::type {};

template<typename...>
struct disjunction : std::false_type {};

template<typename B1>
struct disjunction<B1> : B1 {};

template<typename B1, typename B2>
struct disjunction<B1, B2> : std::conditional<B1::value, B1, B2>::type {};

template<typename B1, typename... Bs>
struct disjunction<B1, Bs...> : std::conditional<B1::value, B1, disjunction<Bs...>>::type {};


template <typename R, typename... Args>
struct FunctionArgsBase{
  using args  = std::tuple<Args...>;
  using arity = std::integral_constant<unsigned, sizeof...(Args)>;
  using result = R;
};

template <typename T>
struct FunctionArgs;

template <typename R, typename... Args>
struct FunctionArgs<R(*)(Args...)> : FunctionArgsBase<R, Args...> {};
template <typename R, typename... Args>
struct FunctionArgs<R(Args...)> : FunctionArgsBase<R, Args...> {};
template <typename R, typename C, typename... Args>
struct FunctionArgs<R(C::*)(Args...)> : FunctionArgsBase<R, Args...> {};
template <typename R, typename C, typename... Args>
struct FunctionArgs<R(C::*)(Args...) const> : FunctionArgsBase<R, Args...> {};

using TypeIndex = unsigned int;

static constexpr TypeIndex baseType = -1;
static constexpr TypeIndex invalidType = -2;

template<class Base, class T, class... Ts>
struct getTypeIndex;

template<class Base, class T, class T1, class... Ts>
struct getTypeIndex<Base, T, T1, Ts...> {
  static constexpr TypeIndex index = std::is_same<T, T1>::value
    ? sizeof...(Ts)
    : getTypeIndex<Base, T, Ts...>::index;
};

template<class Base, class T>
struct getTypeIndex<Base, T> {
  static constexpr TypeIndex index = std::is_same<T, Base>::value
    ? baseType
    : invalidType;
};

}// detail

template<typename PtrType, typename Base, typename ...Types>
class BasicPolyPtr {

  static_assert(detail::conjunction<std::is_base_of<Base, Types>...>::value,
   "the first template parameter needs to be a common baseclass of \
    all the other template parameters");

  using TypeIndex = detail::TypeIndex;
  static constexpr TypeIndex baseType = detail::baseType;
  static constexpr TypeIndex invalidType = detail::invalidType;

  template<typename T>
  using getTypeIndex = detail::getTypeIndex<Base, T, Types...>;

  template<typename T>
  using checkType = std::enable_if_t<
    getTypeIndex<T>::index != invalidType>;

  template<typename ...Cases>
  struct visitor;

  template<typename Case>
  struct visitor<Case> : Case {

    using Case::operator();

    visitor(Case _case) : Case(_case) {};
  };

  template<typename Case, typename ...Cases>
  struct visitor<Case, Cases...> : Case, visitor<Cases...> {

    using Case::operator();
    using visitor<Cases...>::operator();

    visitor(Case _case, Cases ...cases)
      : Case(_case), visitor<Cases...>(cases...) {};
  };

  template<typename F, typename R, typename ...Ts>
  struct dispatcher;

  template<typename F, typename R, typename T, typename ...Ts>
  struct dispatcher<F, R, T, Ts...> {

    static R apply(BasicPolyPtr *p, F&& f) {
      if (p->template is<T>()) {
        return f(p->get<T>());
      } else {
        static_assert(sizeof...(Ts) > 0, "Unmatched");
        return dispatcher<F, R, Ts...>::apply(p, std::forward<F>(f));
      }
    }
  };

  template<typename F, typename R, typename T>
  struct dispatcher<F, R, T> {

    static void apply(BasicPolyPtr *p, F&& f) {
      f(p->get<T>());
    }
  };

  struct Exception : std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  TypeIndex typeIndex;
  PtrType data = (Base*)malloc(sizeof(Base*));


public:

  using first_type = std::tuple_element_t<0, std::tuple<Types...>>;

  BasicPolyPtr() {};
  BasicPolyPtr(PtrType &&ptr) : data (ptr) {}

  template<typename T, typename = checkType<T>>
  BasicPolyPtr(T *t) {
    set(t);
  }

  bool valid() const {
    return typeIndex != invalidType;
  }

  template<typename T, typename = checkType<T>>
  bool is() const {
    if (getTypeIndex<T>::index == baseType) return true;
    return typeIndex == getTypeIndex<T>::index;
  }

  template<typename T, typename = checkType<T>>
  T *get() {
    TypeIndex req = getTypeIndex<T>::index;
    if (typeIndex == req) {
      return (T *)(Base *)data;
    }
    if (typeIndex == getTypeIndex<T>::index) {
      return (T *)(Base *)data;
    } else {
      throw Exception(__PRETTY_FUNCTION__);
    }
  }

  template<typename T, typename = checkType<T>>
  void set(T *t) {
    data = t;
    typeIndex = getTypeIndex<T>::index;
  }

  Base *base() const { return data; }

  Base *operator->() const { return base(); }
  operator Base *() const { return base(); }

  template<typename T, typename = checkType<T>>
  auto operator=(T *t) { set(t); return *this; }

  bool operator==(const BasicPolyPtr&& other) const { base() == other.base(); }
  bool operator!=(const BasicPolyPtr&& other) const { base() != other.base(); }

  template<typename V>
  decltype(auto) visit(V v) {
    using R = std::result_of_t<V(first_type *)>;
    return dispatcher<V, R, first_type, Types...>::apply(this, std::forward<V>(v));
  }

  // Magic

  template<typename ...Cases>
  decltype(auto) match(Cases ...cases) {
    return visit(visitor<Cases...>(cases...));
  }
};

template<typename Base, typename ...Types>
using PolyPtr = BasicPolyPtr<Base *, Base, Types...>;

template<typename Base, typename ...Types>
using SmartPolyPtr = BasicPolyPtr<std::unique_ptr<Base>, Base, Types...>;
}
