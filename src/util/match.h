#pragma once

#include <functional>
#include <mapbox/variant.hpp>

/*
 * Pattern matching
 * Example:
 * std::string command;
 * int cmdId = match<int>(command)
 *   .c("help", 0)
 *   .c("list", [&] () {
 *     return getIdForArgs(args);
 *   })
 *   .c("add", 2)
 *   .d([&] () {
 *     error = "Unrecognized command"
 *     return 0;
 *   });
 *
 *
 */

namespace top1 {

template<typename T,
    typename retType = void,
    typename cmp = std::equal_to<T>>
struct matcher {

  const T& obj;
  bool found = false;
  retType retVal;

  const cmp compare;

  explicit matcher(const T& obj) : obj (obj), compare () {}

  /// match a case with a lambda
  matcher& c(const T&, const std::function<retType()>&);
  matcher& c(const T&, const std::function<retType(const T&)>&);
  /// match with an in-place expression
  matcher& c(const T&, retType);
  /// Default lambda
  retType d(const std::function<retType()>&);
  retType d(const std::function<retType(const T&)>&);
  /// Default value
  retType d(retType);
  retType get();

  operator retType() {
    return get();
  }
};

// Specialization for retType = void, since void doesn't have a value
template<typename T, typename cmp>
struct matcher<T, void, cmp> {

  const T& obj;
  bool found = false;

  const cmp compare;

  explicit matcher(const T& obj) : obj (obj), compare () {}

  /// match a case with a lambda
  matcher& c(const T&, const std::function<void()>&);
  matcher& c(const T&, const std::function<void(const T&)>&);
  /// Default lambda
  void d(const std::function<void()>&);
  void d(const std::function<void(const T&)>&);
};
}

template<typename retType, typename T>
inline top1::matcher<T, retType> match(const T &t) {
  return top1::matcher<T, retType>(t);
}

template<typename T, typename retType, typename cmp>
inline top1::matcher<T, retType, cmp>& top1::matcher<T, retType, cmp>::c(
  const T& p, const std::function<retType()>& func) {
  if (!found && compare(obj, p)) {
    found = true;
    retVal = func();
  }
  return *this;
}

template<typename T, typename retType, typename cmp>
inline top1::matcher<T, retType, cmp>& top1::matcher<T, retType, cmp>::c(
  const T& p, const std::function<retType(const T&)>& func) {
  if (!found && compare(obj, p)) {
    found = true;
    retVal = func(obj);
  }
  return *this;
}

template<typename T, typename retType, typename cmp>
inline top1::matcher<T, retType, cmp>& top1::matcher<T, retType, cmp>::c(
  const T& p, retType r) {
  if (!found && compare(obj, p)) {
    found = true;
    retVal = r;
  }
  return *this;
}

template<typename T, typename retType, typename cmp>
inline retType top1::matcher<T, retType, cmp>::d(
  const std::function<retType()>& func) {
  if (!found) {
    found = true;
    retVal = func();
  }
  return get();
}

template<typename T, typename retType, typename cmp>
inline retType top1::matcher<T, retType, cmp>::d(
  const std::function<retType(const T&)>& func) {
  if (!found) {
    found = true;
    retVal = func(obj);
  }
  return get();
}

template<typename T, typename retType, typename cmp>
inline retType top1::matcher<T, retType, cmp>::d(retType r) {
  if (!found) {
    found = true;
    retVal = r;
  }
  return get();
}

template<typename T, typename retType, typename cmp>
inline retType top1::matcher<T, retType, cmp>::get() {
  return retVal;
}

// Custom implementations for retType = void
template<typename T>
inline top1::matcher<T, void> match(const T &t) {
  return top1::matcher<T, void>(t);
}

template<typename T, typename cmp>
inline top1::matcher<T, void, cmp>& top1::matcher<T, void, cmp>::c(
  const T& p, const std::function<void()>& func) {
  if (!found && compare(obj, p)) {
    found = true;
    func();
  }
  return *this;
}

template<typename T, typename cmp>
inline top1::matcher<T, void, cmp>& top1::matcher<T, void, cmp>::c(
  const T& p, const std::function<void(const T&)>& func) {
  if (!found && compare(obj, p)) {
    found = true;
    func(obj);
  }
  return *this;
}

template<typename T, typename cmp>
inline void top1::matcher<T, void, cmp>::d(
  const std::function<void()>& func) {
  if (!found) {
    found = true;
    func();
  }
}

template<typename T, typename cmp>
inline void top1::matcher<T, void, cmp>::d(
  const std::function<void(const T&)>& func) {
  if (!found) {
    found = true;
    func(obj);
  }
}

