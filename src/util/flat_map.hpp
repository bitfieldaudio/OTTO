#pragma once

#include <tl/optional.hpp>
#include <tuple>
#include <vector>

#include "util/algorithm.hpp"
#include "util/iterator.hpp"
#include "util/macros.hpp"

namespace otto::util {
  namespace detail {

    template<typename K, typename V, typename key_iterator, typename mapped_iterator>
    struct flat_map_iterator : iterator_facade<flat_map_iterator<K, V, key_iterator, mapped_iterator>,
                                               std::pair<K, V>,
                                               std::random_access_iterator_tag,
                                               std::pair<K&, V&>> {
      using iterator_category = std::random_access_iterator_tag;
      using value_type = std::pair<K, V>;
      using reference = std::pair<K&, V&>;
      struct pointer {
        mutable reference pair;
        reference* operator->() const noexcept
        {
          return &pair;
        }
      };

      flat_map_iterator(key_iterator k, mapped_iterator m) : key_iter(k), mapped_iter(m) {}

      void advance(int n)
      {
        std::advance(key_iter, n);
        std::advance(mapped_iter, n);
      }

      reference dereference() const
      {
        return {*key_iter, *mapped_iter};
      }

      pointer operator->() const
      {
        return pointer{dereference()};
      }

      bool equal(const flat_map_iterator& o) const
      {
        return key_iter == o.key_iter && mapped_iter == o.mapped_iter;
      }

      key_iterator key_iter;
      mapped_iterator mapped_iter;
    };
  } // namespace detail

  template<typename K, typename V>
  struct flat_map {
    using key_type = K;
    using mapped_type = V;
    using value_type = std::pair<K, V>;
    using key_iterator = typename std::vector<key_type>::iterator;
    using mapped_iterator = typename std::vector<mapped_type>::iterator;
    using const_key_iterator = typename std::vector<key_type>::const_iterator;
    using const_mapped_iterator = typename std::vector<mapped_type>::const_iterator;
    using iterator = util::detail::flat_map_iterator<K, V, key_iterator, mapped_iterator>;
    using const_iterator = util::detail::flat_map_iterator<K, V, const_key_iterator, const_mapped_iterator>;

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

    template<typename TransparentKey>
    iterator find(const TransparentKey& k)
    {
      auto found = util::find(key_store_, k);
      return {found, corresponding(found)};
    }

    template<typename TransparentKey>
    const_iterator find(const TransparentKey& k) const
    {
      auto found = util::find(key_store_, k);
      return {found, corresponding(found)};
    }

    template<typename TransparentKey>
    bool contains(const TransparentKey& k) const
    {
      auto found = util::find(key_store_, k);
      return found != key_store_.end();
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
      return emplace(std::move(k), std::move(v));
    }

    template<typename... KArgs, typename... VArgs>
    std::pair<iterator, bool> emplace(std::piecewise_construct_t,
                                      std::tuple<KArgs...> kargs,
                                      std::tuple<VArgs...> vargs)
    {
      return std::apply(
        [&](auto&&... args) {
          return try_emplace(std::apply([](auto&&... args) { return key_type{FWD(args)...}; }, kargs), FWD(args)...);
        },
        vargs);
    }

    template<typename KRef, typename VRef>
    std::pair<iterator, bool> emplace(KRef&& k, VRef&& v)
    {
      return emplace(std::piecewise_construct_t(), std::forward_as_tuple(k), std::forward_as_tuple(v));
    }

    template<typename... Args>
    std::pair<iterator, bool> try_emplace(key_type&& key, Args&&... args)
    {
      if (auto found = util::find(key_store_, key); found != key_store_.end()) {
        return {{found, corresponding(found)}, false};
      }
      auto& kref = key_store_.emplace_back(std::move(key));
      auto& vref = val_store_.emplace_back(FWD(args)...);

      auto ki = key_store_.begin() + (&kref - key_store_.data());
      auto vi = val_store_.begin() + (&vref - val_store_.data());
      return {{ki, vi}, true};
    }

    template<typename... Args>
    std::pair<iterator, bool> try_emplace(const key_type& key, Args&&... args)
    {
      if (auto found = util::find(key_store_, key); found != key_store_.end()) {
        return {{found, corresponding(found)}, false};
      }
      auto& kref = key_store_.emplace_back(key);
      auto& vref = val_store_.emplace_back(FWD(args)...);

      auto ki = key_store_.begin() + (&kref - key_store_.data());
      auto vi = val_store_.begin() + (&vref - val_store_.data());
      return {{ki, vi}, true};
    }

    /// Erase the element mapped to by k
    ///
    /// @return true if the element existed, false otherwise
    template<typename TransparentKey>
    bool erase(const TransparentKey& k)
    {
      auto found = util::find(key_store_, k);
      if (found == key_store_.end()) return false;
      val_store_.erase(corresponding(found));
      key_store_.erase(found);
      return true;
    }

    /// Erase the element at the iterator
    ///
    /// @return an iterator pointing to the element right after the deleted one
    iterator erase(iterator i)
    {
      auto ki = key_store_.erase(i.key_iter);
      auto vi = val_store_.erase(i.mapped_iter);
      return {ki, vi};
    }

    /// Erase the elements in the iterator range
    ///
    /// @return an iterator pointing to the element right after the last deleted
    iterator erase(iterator f, iterator l)
    {
      auto ki = key_store_.erase(f.key_iter, l.key_iter);
      auto vi = val_store_.erase(f.mapped_iter, l.mapped_iter);
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
