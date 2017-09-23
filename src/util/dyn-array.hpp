#pragma once

#include <memory>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cstring>
#include <type_traits>

namespace top1 {

/**
 * STL-compatible dynamic array.
 *
 * Useful for buffers that only have to be resized when
 * jack changes the buffersize
 */
template<
    typename T,
    typename A = std::allocator<T>,
    typename = std::enable_if_t<std::is_default_constructible<T>::value>>
class DynArray {
public:

  using allocator_type = A;
  using value_type = typename A::value_type;
  using reference = typename A::reference;
  using pointer = typename A::pointer;
  using const_reference = typename A::const_reference;
  using difference_type = typename A::difference_type;
  using size_type = typename A::size_type;

  class iterator {
  public:
    using value_type = typename A::value_type;
    using reference = typename A::reference;
    using pointer = typename A::pointer;
    using difference_type = typename A::difference_type;
    using iterator_category = std::random_access_iterator_tag;

    iterator(pointer ptr) : ptr (ptr) {}

    iterator(const iterator& o) : ptr (o.ptr) {}

    iterator operator++() {
      iterator i = *this;
      ptr++;
      return i;
    }
    iterator operator++(int) {
      ptr++;
      return *this;
    }
    iterator operator--() {
      const_iterator i = *this;
      ptr--;
      return i;
    }
    iterator operator--(int) {
      ptr--;
      return *this;
    }
    iterator operator+(size_type rhs) {
      return iterator(ptr + rhs);
    }
    iterator operator-(size_type rhs) {
      return iterator(ptr - rhs);
    }
    difference_type operator-(const iterator &rhs) const {
      return ptr - rhs.ptr;
    }
    iterator& operator+=(size_type rhs) {
      ptr += rhs;
      return *this;
    }
    iterator& operator-=(size_type rhs) {
      ptr -= rhs;
      return *this;
    }
    reference operator*() { return *ptr; }
    pointer operator->() { return ptr; }

    bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
    bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }

  private:
    pointer ptr;
  };

  class const_iterator {
  public:
    using value_type = typename A::value_type;
    using reference = typename A::reference;
    using pointer = typename A::pointer;
    using difference_type = typename A::difference_type;
    using iterator_category = std::random_access_iterator_tag;

    const_iterator(pointer ptr) : ptr (ptr) {}

    const_iterator operator++() {
      const_iterator i = *this;
      ptr++;
      return i;
    }
    const_iterator operator++(int) {
      ptr++;
      return *this;
    }
    const_iterator operator--() {
      const_iterator i = *this;
      ptr--;
      return i;
    }
    const_iterator operator--(int) {
      ptr--;
      return *this;
    }
    const_iterator operator+(size_type rhs) {
      return const_iterator(ptr + rhs);
    }
    const_iterator operator-(size_type rhs) {
      return const_iterator(ptr - rhs);
    }
    difference_type operator-(const_iterator &rhs) const {
      return ptr - rhs.ptr;
    }

    const reference operator*() { return *ptr; }
    const pointer operator->() { return ptr; }

    bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
    bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }

  private:
    pointer ptr;
  };

  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;


  DynArray(size_type size) : _size(size) {
    _data = _allocator.allocate(size);
    clear();
  }

  virtual ~DynArray() {
    _allocator.deallocate(_data, _size);
  }

  size_type size() const { return _size; }
  pointer data() const { return _data; }

  reference operator[](size_type index) {
    // if (index >= _size || index < 0) {
    //   throw std::out_of_range("Out of DynArray bounds");
    // }  // Killed for performance
    return _data[index];
  }

  const reference operator[](size_type index) const {
    // if (index >= _size || index < 0) {
    //   throw std::out_of_range("Out of DynArray bounds");
    // }  // Killed for performance
    return _data[index];
  }

  iterator begin() {
    return iterator(_data);
  }

  iterator end() {
    return iterator(_data + _size);
  }

  const_iterator begin() const {
    return const_iterator(_data);
  }

  const_iterator cbegin() const {
    return const_iterator(_data);
  }

  const_iterator end() const {
    return const_iterator(_data + _size);
  }
  const_iterator cend() const {
    return const_iterator(_data + _size);
  }

  reverse_iterator rbegin() {
    return iterator(_data);
  }

  reverse_iterator rend() {
    return iterator(_data + _size);
  }

  const_reverse_iterator rbegin() const {
    return const_iterator(_data);
  }

  const_reverse_iterator crbegin() const {
    return const_iterator(_data);
  }

  const_reverse_iterator rend() const {
    return const_iterator(_data + _size);
  }
  const_reverse_iterator crend() const {
    return const_iterator(_data + _size);
  }

  /**
   * Resize the array.
   * Discards all data.
   */
  void resize(size_type size) {
    rawResize(size);
    clear();
  }

  /**
   * Fills the array with zeros
   */
  void clear() {
    std::fill(begin(), end(), value_type{});
  }

  private:
  pointer _data;
  size_type _size;
  allocator_type _allocator;

  void rawResize(size_type size) {
    _allocator.deallocate(_data, _size);
    _size = size;
    _data = _allocator.allocate(size);
  }
};

}
