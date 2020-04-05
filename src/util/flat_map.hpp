#pragma once

#include <gsl/span>
#include <tl/optional.hpp>
#include <tuple>
#include <vector>

#include "util/algorithm.hpp"
#include "util/iterator.hpp"
#include "util/macros.hpp"
#include "util/serialize.hpp"

namespace otto::util {
  inline namespace flat_map_ns {
    namespace detail {

      template<typename K, typename V, bool is_const>
      struct flat_map_reference {
        std::conditional_t<is_const, const K&, K&> first;
        std::conditional_t<is_const, const V&, V&> second;

        operator std::pair<K, V>() const&
        {
          return {first, second};
        }

        operator std::pair<K, V>() &&
        {
          if constexpr (is_const) {
            return {first, second};
          } else {
            return {std::move(first), std::move(second)};
          }
        }
      };

      template<typename K, typename V, typename key_iterator, typename mapped_iterator, bool is_const>
      struct flat_map_iterator : iterator_facade<flat_map_iterator<K, V, key_iterator, mapped_iterator, is_const>,
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

        flat_map_iterator(key_iterator k, mapped_iterator m) : key_iter(k), mapped_iter(m) {}

        void advance(int n)
        {
          std::advance(key_iter, n);
          std::advance(mapped_iter, n);
        }

        reference dereference() const
        {
          return reference{*key_iter, *mapped_iter};
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
      using iterator = detail::flat_map_iterator<K, V, key_iterator, mapped_iterator, false>;
      using const_iterator = detail::flat_map_iterator<K, V, const_key_iterator, const_mapped_iterator, true>;

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
        auto found = nano::find_if(key_store_, [&](auto&& v) { return v == k; });
        return {found, corresponding(found)};
      }

      template<typename TransparentKey>
      const_iterator find(const TransparentKey& k) const
      {
        auto found = nano::find_if(key_store_, [&](auto&& v) { return v == k; });
        return {found, corresponding(found)};
      }

      template<typename TransparentKey>
      bool contains(const TransparentKey& k) const
      {
        auto found = nano::find_if(key_store_, [&](auto&& v) { return v == k; });
        return found != key_store_.end();
      }

      template<typename TransparentKey>
      tl::optional<mapped_type&> operator[](TransparentKey&& k)
      {
        auto found = nano::find_if(key_store_, [&](auto&& v) { return v == k; });
        if (found == key_store_.end()) return tl::nullopt;
        return *corresponding(found);
      }

      template<typename TransparentKey>
      tl::optional<mapped_type&> operator[](TransparentKey&& k) const
      {
        auto found = nano::find_if(key_store_, [&](auto&& v) { return v == k; });
        if (found == key_store_.end()) return tl::nullopt;
        return *corresponding(found);
      }

      gsl::span<const mapped_type> values() const noexcept
      {
        return val_store_;
      }

      gsl::span<mapped_type> values() noexcept
      {
        return val_store_;
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
        if (auto found = nano::find(key_store_, key); found != key_store_.end()) {
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
        if (auto found = nano::find(key_store_, key); found != key_store_.end()) {
          return {{found, corresponding(found)}, false};
        }
        auto& kref = key_store_.emplace_back(key);
        auto& vref = val_store_.emplace_back(FWD(args)...);

        auto ki = key_store_.begin() + (&kref - key_store_.data());
        auto vi = val_store_.begin() + (&vref - val_store_.data());
        return {{ki, vi}, true};
      }

      iterator insert_or_assign(key_type k, mapped_type v)
      {
        return emplace_or_assign(std::move(k), std::move(v));
      }

      template<typename... KArgs, typename... VArgs>
      iterator emplace_or_assign(std::piecewise_construct_t, std::tuple<KArgs...> kargs, std::tuple<VArgs...> vargs)
      {
        return std::apply(
          [&](auto&&... args) {
            return try_emplace_or_assign(std::apply([](auto&&... args) { return key_type{FWD(args)...}; }, kargs),
                                         FWD(args)...);
          },
          vargs);
      }

      template<typename KRef, typename VRef>
      iterator emplace_or_assign(KRef&& k, VRef&& v)
      {
        return emplace_or_assign(std::piecewise_construct_t(), std::forward_as_tuple(k), std::forward_as_tuple(v));
      }


      template<typename... Args>
      iterator try_emplace_or_assign(key_type&& key, Args&&... args)
      {
        if (auto found = nano::find(key_store_, key); found != key_store_.end()) {
          *corresponding(found) = mapped_type(args...);
          return {found, corresponding(found)};
        }
        return try_emplace(key, FWD(args)...).first;
      }

      template<typename... Args>
      iterator try_emplace_or_assign(const key_type& key, Args&&... args)
      {
        if (auto found = nano::find(key_store_, key); found != key_store_.end()) {
          *corresponding(found) = mapped_type(args...);
          return {found, corresponding(found)};
        }
        return try_emplace(key, FWD(args)...).first;
      }

      /// Erase the element mapped to by k
      ///
      /// @return true if the element existed, false otherwise
      template<typename TransparentKey>
      bool erase(const TransparentKey& k)
      {
        auto found = nano::find_if(key_store_, [&](auto&& v) { return v == k; });
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


    template<typename K, typename V>
    void to_json(nlohmann::json& res, const util::flat_map<K, V>& map)
    {
      for (auto&& pair : map) {
        res.emplace(to_string(pair.first), serialize(pair.second));
      }
    }

    template<typename K, typename V>
    void from_json(const nlohmann::json& res, util::flat_map<K, V>& map)
    {
      for (auto it = res.begin(); it != res.end(); ++it) {
        map.emplace(*from_string<K>(it.key()), it.value());
      }
    }

    template<typename T>
    struct flat_set {
      using Vector = std::vector<T>;
      using value_type = typename Vector::value_type;
      using iterator = typename Vector::iterator;
      using const_iterator = typename Vector::const_iterator;

      flat_set() {}

      flat_set(std::initializer_list<value_type> il)
      {
        for (const T& v : il) {
          insert(v);
        }
      }

      // Queries

      std::size_t capacity() noexcept
      {
        return vector_.capacity();
      }

      std::size_t size() const noexcept
      {
        return vector_.size();
      }

      bool empty() const noexcept
      {
        return vector_.empty();
      }

      bool full() const noexcept
      {
        return vector_.full();
      }

      // Iterators

      auto begin() noexcept
      {
        return vector_.begin();
      }

      auto begin() const noexcept
      {
        return vector_.begin();
      }

      auto end() noexcept
      {
        return vector_.end();
      }

      auto end() const noexcept
      {
        return vector_.end();
      }

      auto rbegin() noexcept
      {
        return vector_.rbegin();
      }

      auto rbegin() const noexcept
      {
        return vector_.rbegin();
      }

      auto rend() noexcept
      {
        return vector_.rend();
      }

      auto rend() const noexcept
      {
        return vector_.rend();
      }

      // Accessors

      value_type& front() noexcept
      {
        return vector_.front();
      }

      const value_type& front() const noexcept
      {
        return vector_.front();
      }

      value_type& back() noexcept
      {
        return vector_.back();
      }

      const value_type& back() const noexcept
      {
        return vector_.back();
      }

      value_type& operator[](std::size_t idx) noexcept
      {
        return vector_.operator[](idx);
      }
      const value_type& operator[](std::size_t idx) const noexcept
      {
        return vector_.operator[](idx);
      }
      value_type* data() noexcept
      {
        return vector_.data();
      }

      const value_type* data() const noexcept
      {
        return vector_.data();
      }

      // Modifiers

      std::pair<iterator, bool> insert(const value_type& e)
      {
        auto pos = std::upper_bound(begin(), end(), e);
        auto prev = pos - 1;
        if (pos == begin() || *prev != e) return {vector_.insert(pos, e), true};
        return {prev, false};
      }

      std::pair<iterator, bool> insert(value_type&& e)
      {
        auto pos = std::upper_bound(begin(), end(), e);
        auto prev = pos - 1;
        if (pos == begin() || *prev != e) return {vector_.insert(pos, std::move(e)), true};
        return {prev, false};
      }

      void pop_back() noexcept
      {
        return vector_.pop_back();
      }

      void clear() noexcept
      {
        vector_.clear();
      }

      iterator erase(iterator first, iterator last) noexcept
      {
        return vector_.erase(first, last);
      }

      iterator erase(iterator it) noexcept
      {
        return vector_.erase(it);
      }

      iterator erase(const value_type& val) noexcept
      {
        return erase(std::find(begin(), end(), val));
      }

    private:
      Vector vector_;
    };

  } // namespace flat_map_ns

} // namespace otto::util
