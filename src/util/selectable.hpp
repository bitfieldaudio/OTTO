#pragma once

#include <utility>

#include "util/reflection.hpp"

#include "services/log_manager.hpp"

namespace otto::util {

  template<typename Cont>
  struct selectable {
    using value_type = typename Cont::value_type;
    using iterator = typename Cont::iterator;
    using const_iterator = typename Cont::const_iterator;

    selectable() = default;

    selectable(const Cont& cont) : _cont(cont), _cur(begin()) {}
    selectable(Cont&& cont) : _cont(std::move(cont)), _cur(begin()) {}

    iterator select(iterator i)
    {
      return _cur = i;
    }

    iterator select(std::size_t i)
    {
      OTTO_ASSERT(i < size(), "i = {} should be < size() = {}", i, size());
      return _cur = begin() + i;
    }

    value_type& current()
    {
      return *_cur;
    }

    const value_type& current() const
    {
      return *_cur;
    }

    std::size_t current_idx() const
    {
      return _cur - _cont.begin();
    }

    std::size_t size() const noexcept
    {
      return _cont.size();
    }

    iterator begin()
    {
      return _cont.begin();
    }
    iterator end()
    {
      return _cont.end();
    }

    const_iterator begin() const
    {
      return _cont.begin();
    }
    const_iterator end() const
    {
      return _cont.end();
    }

    value_type& operator[](std::size_t i)
    {
      return _cont[i];
    }

    const value_type& operator[](std::size_t i) const
    {
      return _cont[i];
    }

    value_type& at(std::size_t i)
    {
      return _cont.at(i);
    }

    const value_type& at(std::size_t i) const
    {
      return _cont.at(i);
    }

    Cont& cont()
    {
      return _cont;
    }

    const Cont& cont() const
    {
      return _cont;
    }

    DECL_REFLECTION(selectable,
                    ("cont", &selectable::_cont),
                    ("current", &selectable::current_idx, [](selectable& s, std::size_t v) { s.select(v); }));

  private:
    Cont _cont = {};
    iterator _cur = _cont.begin();
  };

} // namespace otto::util
