#pragma once

#include <tl/optional.hpp>
#include <tuple>
#include <vector>

#include "util/algorithm.hpp"
#include "util/iterator.hpp"

namespace otto::util {

  template<typename K, typename V>
  struct flat_map {
    using key_type = K;
    using mapped_type = V;
    using value_type = std::tuple<K, V>;
    using key_iterator = typename std::vector<key_type>::iterator;
    using mapped_iterator = typename std::vector<mapped_type>::iterator;
    using iterator = util::zipped_iterator<key_iterator, mapped_iterator>;
    using const_key_iterator = typename std::vector<key_type>::const_iterator;
    using const_mapped_iterator = typename std::vector<mapped_type>::const_iterator;
    using const_iterator = util::zipped_iterator<const_key_iterator, const_mapped_iterator>;

    std::size_t size() const noexcept
    {
      return key_store_.size();
    }

    iterator begin()
    {
      return {key_store_.begin(), val_store_.begin()};
    }

    const_iterator begin() const
    {
      return {key_store_.begin(), val_store_.begin()};
    }

    iterator end()
    {
      return {key_store_.end(), val_store_.end()};
    }

    const_iterator end() const
    {
      return {key_store_.end(), val_store_.end()};
    }

    iterator find(const key_type& k) {
      auto found = util::find(key_store_, k);
      return {found, corresponding(found)};
    }

    const_iterator find(const key_type& k) const {
      auto found = util::find(key_store_, k);
      return {found, corresponding(found)};
    }

    tl::optional<mapped_type&> operator[](const key_type& k)
    {
      auto found = util::find(key_store_, k);
      if (found == key_store_.end()) return tl::nullopt;
      return *corresponding(found);
    }

    /// Insert element and return iterator to it.
    ///
    /// If it already exists, return iterator to the existing element
    ///
    /// @return a pair of the iterator and whether the insertion was performed
    std::pair<iterator, bool> insert(key_type k, mapped_type v)
    {
      if (auto found = util::find(key_store_, k); found != key_store_.end()) {
        return {{found, corresponding(found)}, false};
      }
      auto& kref = key_store_.emplace_back(k);
      auto ki = key_store_.begin() + (&kref - key_store_.data());
      auto& vref = val_store_.emplace_back(v);
      auto vi = val_store_.begin() + (&vref - val_store_.data());
      return {{ki, vi}, true};
    }

    /// Erase the element mapped to by k
    /// 
    /// @return true if the element existed, false otherwise
    bool erase(const key_type& k) {
      auto found = util::find(key_store_, k);
      if (found == key_store_.end()) return false;
      val_store_.erase(corresponding(found));
      key_store_.erase(found);
      return true;
    }

    /// Erase the element at the iterator
    /// 
    /// @return an iterator pointing to the element right after the deleted one
    iterator erase(iterator i) {
      auto ki = key_store_.erase(std::get<0>(i.iterators));
      auto vi = val_store_.erase(std::get<1>(i.iterators));
      return {ki, vi};
    }

    /// Erase the elements in the iterator range
    /// 
    /// @return an iterator pointing to the element right after the last deleted
    iterator erase(iterator f, iterator l) {
      auto ki = key_store_.erase(std::get<0>(f.iterators), std::get<0>(l.iterators));
      auto vi = val_store_.erase(std::get<1>(f.iterators), std::get<1>(l.iterators));
      return {ki, vi};
    }

  private:
    mapped_iterator corresponding(key_iterator ki) noexcept
    {
      return val_store_.begin() + (ki - key_store_.begin());
    }

    const_mapped_iterator corresponding(const_key_iterator ki) const noexcept
    {
      return val_store_.begin() + (ki - key_store_.begin());
    }

    std::vector<key_type> key_store_;
    std::vector<mapped_type> val_store_;
  };

} // namespace otto::util
