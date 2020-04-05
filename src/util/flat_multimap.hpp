#pragma once

#include "util/flat_map.hpp"

namespace otto::util {
  inline namespace flat_map_ns {

    namespace detail {

      template<typename K, typename V, typename mapped_iterator, bool is_const>
      struct flat_multimap_iterator : iterator_facade<flat_multimap_iterator<K, V, mapped_iterator, is_const>,
                                                      std::pair<K, V>,
                                                      std::random_access_iterator_tag,
                                                      flat_map_reference<K, V, is_const>> {
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<K, V>;
        using reference = flat_map_reference<K, V, is_const>;
        struct pointer {
          mutable reference pair;
          reference* operator->() const noexcept
          {
            return &pair;
          }
        };

        flat_multimap_iterator(std::vector<K>& keys, mapped_iterator m) : keys(&keys), mapped_iter(m) {}

        void advance(int n)
        {
          std::advance(mapped_iter, n);
        }

        reference dereference() const
        {
          return reference{(*keys)[mapped_iter->key_idx], mapped_iter->value};
        }

        pointer operator->() const
        {
          return pointer{dereference()};
        }

        bool equal(const flat_multimap_iterator& o) const
        {
          return mapped_iter == o.mapped_iter;
        }

        std::vector<K>* keys;
        mapped_iterator mapped_iter;
      };

      template<typename V>
      struct flat_multimap_mapped_store {
        template<typename... Args>
        flat_multimap_mapped_store(unsigned key_idx, Args&&... args) : key_idx(key_idx), value(FWD(args)...) {}
        unsigned key_idx;
        V value;
      };
    } // namespace detail

    template<typename K, typename V>
    struct flat_multimap {
      using key_type = K;
      using mapped_type = V;
      using mapped_store = detail::flat_multimap_mapped_store<V>;
      using value_type = std::pair<K, V>;
      using key_iterator = typename std::vector<key_type>::iterator;
      using mapped_iterator = typename std::vector<mapped_store>::iterator;
      using const_key_iterator = typename std::vector<key_type>::const_iterator;
      using const_mapped_iterator = typename std::vector<mapped_store>::const_iterator;
      using iterator = detail::flat_multimap_iterator<K, V, mapped_iterator, false>;
      using const_iterator = detail::flat_multimap_iterator<K, V, const_mapped_iterator, true>;

      std::size_t size() const noexcept
      {
        return val_store_.size();
      }

      iterator begin()
      {
        return {key_store_, val_store_.begin()};
      }

      const_iterator begin() const
      {
        return {key_store_, val_store_.begin()};
      }

      iterator end()
      {
        return {key_store_, val_store_.end()};
      }

      const_iterator end() const
      {
        return {key_store_, val_store_.end()};
      }

      template<typename TransparentKey>
      bool contains(const TransparentKey& k) const
      {
        auto found = nano::find_if(key_store_, [&](auto&& v) { return v == k; });
        return found != key_store_.end();
      }

      gsl::span<const key_type> keys() const noexcept
      {
        return key_store_;
      }

      gsl::span<key_type> keys() noexcept
      {
        return key_store_;
      }

      /// Insert element and return iterator to it.
      iterator insert(key_type k, mapped_type v)
      {
        return emplace(std::move(k), std::move(v));
      }

      template<typename... KArgs, typename... VArgs>
      iterator emplace(std::piecewise_construct_t, std::tuple<KArgs...> kargs, std::tuple<VArgs...> vargs)
      {
        return std::apply(
          [&](auto&&... args) {
            return try_emplace(std::apply([](auto&&... args) { return key_type{FWD(args)...}; }, kargs), FWD(args)...);
          },
          vargs);
      }

      template<typename... Args>
      iterator emplace(key_type&& key, Args&&... args)
      {
        auto found = find_key(key);
        if (found == key_store_.end()) {
          found = key_store_.emplace(found, std::move(key));
        }
        val_store_.emplace_back(found - key_store_.begin(), FWD(args)...);
        return {key_store_, val_store_.end() - 1};
      }

      template<typename... Args>
      
      std::pair<iterator, bool> emplace(const key_type& key, Args&&... args)
      {
        auto found = find_key(key);
        if (found == key_store_.end()) {
          found = key_store_.emplace(found, key);
        }
        val_store_.emplace_back(found - key_store_.begin(), FWD(args)...);
        return {key_store_, val_store_.end() - 1};
      }

      /// Erase all elements mapped to by k
      ///
      /// @return number of erased elements
      template<typename TransparentKey>
      int erase_all(const TransparentKey& k)
      {
        auto found = find_key(k);
        if (found == key_store_.end()) return 0;
        auto key_idx = found - key_store_.begin();
        auto iter = nano::remove_if(val_store_, [key_idx](auto& val) { return val.key_idx == key_idx; });
        int res = val_store_.end() - iter;
        val_store_.erase(iter, val_store_.end());
        maybe_erase_key(key_idx);
        return res;
      }

      /// Erase the element at the iterator
      ///
      /// @return an iterator pointing to the element right after the deleted one
      iterator erase(iterator i)
      {
        auto key_idx = i.mapped_iter->key_idx;
        auto vi = val_store_.erase(i.mapped_iter);
        maybe_erase_key(key_idx);
        return {key_store_, vi};
      }

    private:
      template<typename TransparentKey>
      key_iterator find_key(TransparentKey&& k)
      {
        return nano::find_if(key_store_, [&k](auto& key) { return key == k; });
      }

      void maybe_erase_key(unsigned key_idx)
      {
        if (nano::any_of(val_store_, [key_idx](auto& m) { return m.key_idx == key_idx; })) return;
        std::swap(key_store_[key_idx], key_store_.back());
        key_store_.pop_back();
        for (auto& m : val_store_) {
          if (m.key_idx == key_store_.size()) m.key_idx = key_idx;
        }
      }

      std::vector<key_type> key_store_;
      std::vector<mapped_store> val_store_;
    }; // namespace flat_map_ns

  } // namespace flat_map_ns

} // namespace otto::util
