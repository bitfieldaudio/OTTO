#pragma once

#include <memory>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cstring>
#include <type_traits>

namespace otto::util {

  /// Dynamic array
  ///
  /// Default initialized. Cleared on resize.
  template<typename T>
  class dyn_array {
    std::size_t cur_size;
    std::unique_ptr<T[]> _data;
  public:

    dyn_array(std::size_t size)
      : cur_size (size),
        _data (std::make_unique<T[]>(size))
    {
      clear();
    }

    decltype(auto) operator[](std::size_t i) {return _data[i];}
    decltype(auto) operator[](std::size_t i) const {return _data[i];}

    T* begin() { return _data.get(); }
    T* end() { return _data.get() + cur_size; }

    const T* begin() const { return _data.get(); }
    const T* end() const { return _data.get() + cur_size; }

    T* data() { return _data.get(); }
    const T* data() const { return _data.get(); }

    std::size_t size() const { return cur_size; }

    /// Replace the array with a new one of size `new_size`
    ///
    /// Also default initializes the data
    void resize(std::size_t new_size)
    {
      _data = std::make_unique<T[]>(new_size);
      cur_size = new_size;
      clear();
    }

    /// Fill the array with default initialized values
    void clear()
    {
      if (cur_size != 0) std::fill(begin(), end(), T{});
    }
  };
}
