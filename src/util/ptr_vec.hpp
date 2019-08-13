#pragma once

#include <cassert>
#include <memory>
#include <type_traits>
#include <vector>
#include "util/algorithm.hpp"

namespace otto::util {

  /// An iterator wrapper that dereferences twice.
  template<typename Iter>
  struct double_iterator {
    using wrapped = Iter;

    using value_type = std::decay_t<decltype(*std::declval<typename wrapped::value_type>())>;
    using difference_type = typename wrapped::difference_type;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::random_access_iterator_tag;

    using self_t = double_iterator<Iter>;

    double_iterator(wrapped w) : _iter(std::move(w)) {}
    double_iterator() : _iter() {}

    reference operator*() const
    {
      return (**_iter);
    }
    pointer operator->() const
    {
      return &(**_iter);
    }

    self_t& operator++()
    {
      _iter.operator++();
      return *this;
    }
    self_t operator++(int i)
    {
      return _iter.operator++(i);
    }
    self_t& operator--()
    {
      _iter.operator--();
      return *this;
    }
    self_t operator--(int i)
    {
      return _iter.operator--(i);
    }

    auto operator==(const self_t& rhs) const noexcept
    {
      return _iter == rhs._iter;
    }
    auto operator!=(const self_t& rhs) const noexcept
    {
      return _iter != rhs._iter;
    }
    auto operator<(const self_t& rhs) const noexcept
    {
      return _iter < rhs._iter;
    }
    auto operator>(const self_t& rhs) const noexcept
    {
      return _iter > rhs._iter;
    }
    auto operator<=(const self_t& rhs) const noexcept
    {
      return _iter <= rhs._iter;
    }
    auto operator>=(const self_t& rhs) const noexcept
    {
      return _iter >= rhs._iter;
    }

    self_t operator+(difference_type d) const noexcept
    {
      return _iter + d;
    }
    self_t operator-(difference_type d) const noexcept
    {
      return _iter - d;
    }
    auto operator-(const self_t& rhs) const noexcept
    {
      return _iter - rhs._iter;
    }

    self_t& operator+=(difference_type d)
    {
      _iter += d;
      return *this;
    }
    self_t& operator-=(difference_type d)
    {
      _iter -= d;
      return *this;
    }

    operator wrapped&()
    {
      return _iter;
    }
    operator const wrapped&() const
    {
      return _iter;
    }

    wrapped& data()
    {
      return _iter;
    }
    const wrapped& data() const
    {
      return _iter;
    }

  private:
    wrapped _iter;
  };

  template<typename Iter>
  auto operator+(typename double_iterator<Iter>::difference_type diff, double_iterator<Iter> iter)
  {
    return iter + diff;
  }

  /// A convenience wrapper for std::vector<std::unique_ptr<T>>
  template<typename T>
  struct unique_ptr_vec {
    using value_type = T;

  private:
    std::vector<std::unique_ptr<value_type>> data_;

  public:
    using iterator = double_iterator<typename decltype(data_)::iterator>;
    using const_iterator = double_iterator<typename decltype(data_)::const_iterator>;

    using reverse_iterator = double_iterator<typename decltype(data_)::reverse_iterator>;
    using const_reverse_iterator = double_iterator<typename decltype(data_)::const_reverse_iterator>;

    value_type& push_back(const value_type& v)
    {
      auto ptr = std::make_unique<value_type>(v);
      auto res = ptr.get();
      data_.push_back(std::move(ptr));
      return *res;
    }

    value_type& push_back(value_type&& v)
    {
      auto ptr = std::make_unique<value_type>(std::move(v));
      auto res = ptr.get();
      data_.push_back(std::move(ptr));
      return *res;
    }

    value_type& push_back(std::unique_ptr<value_type> ptr)
    {
      auto res = ptr.get();
      data_.push_back(std::move(ptr));
      return *res;
    }

    template<typename... Args>
    value_type& emplace_back(Args&&... args)
    {
      return push_back(std::make_unique<value_type>(std::forward<Args>(args)...));
    }

    std::unique_ptr<value_type> erase(const value_type& v)
    {
      auto iter = std::find_if(data_.begin(), data_.end(), [&v](auto&& uptr) { return uptr.get() == &v; });
      if (iter != data_.end()) {
        auto uptr = std::move(*iter);
        data_.erase(iter);
        return uptr;
      }
      return nullptr;
    }

    std::size_t size() const noexcept
    {
      return data_.size();
    }

    bool empty() const noexcept
    {
      return data_.empty();
    }

    std::size_t capacity() const noexcept
    {
      return data_.capacity();
    }

    std::size_t max_size() const noexcept
    {
      return data_.max_size();
    }

    void reserve(std::size_t new_cap)
    {
      data_.reserve(new_cap);
    }

    void shrink_to_fit()
    {
      data_.shrink_to_fit();
    }

    value_type& operator[](std::size_t n)
    {
      return *data_[n];
    }

    const value_type& operator[](std::size_t n) const
    {
      return *data_[n];
    }

    value_type& at(std::size_t n)
    {
      return *data_.at(n);
    }

    const value_type& at(std::size_t n) const
    {
      return *data_.at(n);
    }

    iterator begin()
    {
      return data_.begin();
    }
    iterator end()
    {
      return data_.end();
    }
    const_iterator begin() const
    {
      return data_.begin();
    }
    const_iterator end() const
    {
      return data_.end();
    }

    reverse_iterator rbegin()
    {
      return data_.rbegin();
    }
    reverse_iterator rend()
    {
      return data_.rend();
    }
    const_reverse_iterator rbegin() const
    {
      return data_.rbegin();
    }
    const_reverse_iterator rend() const
    {
      return data_.rend();
    }

    value_type& front()
    {
      return *data_.front();
    }

    value_type& back()
    {
      return *data_.back();
    }

    const value_type& front() const
    {
      return *data_.front();
    }

    const value_type& back() const
    {
      return *data_.back();
    }

    std::vector<std::unique_ptr<value_type>>& underlying()
    {
      return data_;
    }
  };

  template<typename T, typename T2>
  std::unique_ptr<T> erase(unique_ptr_vec<T>& vec, T2* el)
  {
    return vec.erase(*el);
  }

  template<typename T, typename T2>
  std::unique_ptr<T> erase(unique_ptr_vec<T>& vec, T2& el)
  {
    return vec.erase(el);
  }


  /// A convenience wrapper for std::vector<std::shared_ptr<T>>
  template<typename T>
  struct shared_ptr_vec {
    using value_type = T;

  private:
    std::vector<std::shared_ptr<value_type>> data_;

  public:
    using iterator = double_iterator<typename decltype(data_)::iterator>;
    using const_iterator = double_iterator<typename decltype(data_)::const_iterator>;

    using reverse_iterator = double_iterator<typename decltype(data_)::reverse_iterator>;
    using const_reverse_iterator = double_iterator<typename decltype(data_)::const_reverse_iterator>;

    value_type& push_back(const value_type& v)
    {
      auto ptr = std::make_unique<value_type>(v);
      auto res = ptr.get();
      data_.push_back(std::move(ptr));
      return *res;
    }

    value_type& push_back(value_type&& v)
    {
      auto ptr = std::make_unique<value_type>(std::move(v));
      auto res = ptr.get();
      data_.push_back(std::move(ptr));
      return *res;
    }

    value_type& push_back(std::shared_ptr<value_type> ptr)
    {
      auto res = ptr.get();
      data_.push_back(std::move(ptr));
      return *res;
    }

    template<typename... Args>
    value_type& emplace_back(Args&&... args)
    {
      return push_back(std::make_unique<value_type>(std::forward<Args>(args)...));
    }

    std::shared_ptr<value_type> erase(const value_type& v)
    {
      auto iter = std::find_if(data_.begin(), data_.end(), [&v](auto&& uptr) { return uptr.get() == &v; });
      if (iter != data_.end()) {
        auto uptr = std::move(*iter);
        data_.erase(iter);
        return uptr;
      }
      return nullptr;
    }

    std::size_t size() const noexcept
    {
      return data_.size();
    }

    bool empty() const noexcept
    {
      return data_.empty();
    }

    std::size_t capacity() const noexcept
    {
      return data_.capacity();
    }

    std::size_t max_size() const noexcept
    {
      return data_.max_size();
    }

    void reserve(std::size_t new_cap)
    {
      data_.reserve(new_cap);
    }

    void shrink_to_fit()
    {
      data_.shrink_to_fit();
    }

    value_type& operator[](std::size_t n)
    {
      return *data_[n];
    }

    const value_type& operator[](std::size_t n) const
    {
      return *data_[n];
    }

    value_type& at(std::size_t n)
    {
      return *data_.at(n);
    }

    const value_type& at(std::size_t n) const
    {
      return *data_.at(n);
    }

    iterator begin()
    {
      return data_.begin();
    }
    iterator end()
    {
      return data_.end();
    }
    const_iterator begin() const
    {
      return data_.begin();
    }
    const_iterator end() const
    {
      return data_.end();
    }

    reverse_iterator rbegin()
    {
      return data_.rbegin();
    }
    reverse_iterator rend()
    {
      return data_.rend();
    }
    const_reverse_iterator rbegin() const
    {
      return data_.rbegin();
    }
    const_reverse_iterator rend() const
    {
      return data_.rend();
    }

    value_type& front()
    {
      return *data_.front();
    }

    value_type& back()
    {
      return *data_.back();
    }

    const value_type& front() const
    {
      return *data_.front();
    }

    const value_type& back() const
    {
      return *data_.back();
    }

    std::vector<std::shared_ptr<value_type>>& underlying()
    {
      return data_;
    }
  };

  template<typename T, typename T2>
  std::shared_ptr<T> erase(shared_ptr_vec<T>& vec, T2* el)
  {
    return vec.erase(*el);
  }

  template<typename T, typename T2>
  std::shared_ptr<T> erase(shared_ptr_vec<T>& vec, T2& el)
  {
    return vec.erase(el);
  }



  template<typename T>
  struct non_null_ptr {
    non_null_ptr() = delete;
    constexpr non_null_ptr(T* ptr) : _ptr(ptr)
    {
      assert(ptr != nullptr);
    }
    non_null_ptr(std::nullptr_t) = delete;

    constexpr non_null_ptr(const non_null_ptr&) = default;
    constexpr non_null_ptr(non_null_ptr&&) = default;
    constexpr non_null_ptr& operator=(const non_null_ptr&) = default;
    constexpr non_null_ptr& operator=(non_null_ptr&&) = default;

    constexpr T& operator*() const noexcept
    {
      return *_ptr;
    }

    constexpr T* operator->() const noexcept
    {
      return _ptr;
    }

    constexpr operator T*() noexcept
    {
      return _ptr;
    }

    constexpr operator T* const() const noexcept
    {
      return _ptr;
    }

  private:
    T* _ptr;
  };

  /// A vector of references to T
  template<typename T>
  struct ref_vec {
    using value_type = std::decay_t<T>;

  private:
    std::vector<value_type*> data_;

  public:
    using iterator = double_iterator<typename decltype(data_)::iterator>;
    using const_iterator = double_iterator<typename decltype(data_)::const_iterator>;

    using reverse_iterator = double_iterator<typename decltype(data_)::reverse_iterator>;
    using const_reverse_iterator = double_iterator<typename decltype(data_)::const_reverse_iterator>;

    ref_vec() = default;

    ref_vec(std::initializer_list<value_type*> lst) : data_{lst} {};

    template<typename InputIter,
             typename = std::enable_if_t<std::is_same_v<decltype(*std::declval<InputIter>()), value_type&>>>
    ref_vec(InputIter iter1, InputIter iter2)
    {
      data_.reserve(std::distance(iter1, iter2));
      std::transform(iter1, iter2, std::back_inserter(data_), [](auto& v) { return &v; });
    }

    template<typename Range,
             typename = std::enable_if_t<std::is_same_v<decltype(*std::declval<Range>().begin()), value_type&>>>
    ref_vec(Range&& rng) : ref_vec(std::begin(rng), std::end(rng))
    {}

    value_type& push_back(value_type& v)
    {
      data_.push_back(&v);
      return v;
    }

    value_type& push_back(non_null_ptr<value_type> ptr)
    {
      data_.push_back(ptr);
      return *ptr;
    }

    value_type& emplace_back(value_type& v)
    {
      return push_back(v);
    }

    std::unique_ptr<value_type> erase(const value_type& v)
    {
      auto iter = std::find_if(data_.begin(), data_.end(), [&v](auto&& ptr) { return ptr == &v; });
      if (iter != data_.end()) {
        auto uptr = std::move(*iter);
        data_.erase(iter);
        return uptr;
      }
      return nullptr;
    }

    std::size_t size() const noexcept
    {
      return data_.size();
    }

    bool empty() const noexcept
    {
      return data_.empty();
    }

    std::size_t capacity() const noexcept
    {
      return data_.capacity();
    }

    std::size_t max_size() const noexcept
    {
      return data_.max_size();
    }

    void reserve(std::size_t new_cap)
    {
      data_.reserve(new_cap);
    }

    void shrink_to_fit()
    {
      data_.shrink_to_fit();
    }

    value_type& operator[](std::size_t n)
    {
      return *data_[n];
    }

    const value_type& operator[](std::size_t n) const
    {
      return *data_[n];
    }

    value_type& at(std::size_t n)
    {
      return *data_.at(n);
    }

    const value_type& at(std::size_t n) const
    {
      return *data_.at(n);
    }

    iterator begin()
    {
      return data_.begin();
    }
    iterator end()
    {
      return data_.end();
    }
    const_iterator begin() const
    {
      return data_.begin();
    }
    const_iterator end() const
    {
      return data_.end();
    }

    reverse_iterator rbegin()
    {
      return data_.rbegin();
    }
    reverse_iterator rend()
    {
      return data_.rend();
    }
    const_reverse_iterator rbegin() const
    {
      return data_.rbegin();
    }
    const_reverse_iterator rend() const
    {
      return data_.rend();
    }

    value_type& front()
    {
      return *data_.front();
    }

    value_type& back()
    {
      return *data_.back();
    }

    const value_type& front() const
    {
      return *data_.front();
    }

    const value_type& back() const
    {
      return *data_.back();
    }

    std::vector<value_type*>& underlying()
    {
      return data_;
    }
  };


} // namespace otto::util
