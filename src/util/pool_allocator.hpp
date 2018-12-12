#pragma once

#include <limits>
#include <memory>

#include "util/dyn-array.hpp"

namespace otto::util {

  template<typename T>
  struct memory_pool {
    memory_pool(std::size_t size) noexcept
    {
      // Allocate uninitialized storage
      auto [ptr, len] = std::get_temporary_buffer<T>(size);
      _data = ptr;
      _size = len;
    };

    T* data() const noexcept
    {
      return _data;
    }

    std::size_t size() const noexcept
    {
      return _size;
    }

  private:
    T* _data;
    std::size_t _size;
  };

  template<typename T>
  struct pool_allocator {
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    template<typename U>
    struct rebind {
      typedef pool_allocator<U> other;
    };

    // return address of values
    pointer address(reference value) const
    {
      return &value;
    }

    const_pointer address(const_reference value) const
    {
      return &value;
    }

    /* constructors and destructor
     * - nothing to do because the allocator has no state
     */
    pool_allocator() noexcept = default;
    pool_allocator(const pool_allocator&) noexcept = default;

    template<typename U>
    pool_allocator(const pool_allocator<U>&) noexcept {};

    ~pool_allocator() noexcept = default;

    // return maximum number of elements that can be allocated
    size_type max_size() const noexcept
    {
      return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    // allocate but don't initialize num elements of type T
    pointer allocate(size_type num, const void* = 0)
    {
      pointer ret = (pointer)(::operator new(num * sizeof(T)));
      return ret;
    }

    // initialize elements of allocated storage p with value value
    void construct(pointer p, const T& value)
    {
      // initialize memory with placement new
      new ((void*) p) T(value);
    }

    // destroy elements of initialized storage p
    void destroy(pointer p)
    {
      // destroy objects by calling their destructor
      p->~T();
    }

    // deallocate storage p of deleted elements
    void deallocate(pointer p, size_type num)
    {
      // print message and deallocate memory with global delete
      ::operator delete((void*) p);
    }

  private:
    memory_pool<value_type>& _mem_pool;
  };

  // return that all specializations of this allocator are interchangeable
  template<class T1, class T2>
  bool operator==(const pool_allocator<T1>&, const pool_allocator<T2>&) noexcept
  {
    return true;
  }
  template<class T1, class T2>
  bool operator!=(const pool_allocator<T1>&, const pool_allocator<T2>&) noexcept
  {
    return false;
  }
} // namespace otto::util
