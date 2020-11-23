#pragma once

#include <bitset>

#include "lib/meta.hpp"
#include "lib/reflect.hpp"

namespace otto::itc {

  /// The concept that state types need to fulfill.
  template<typename T>
  concept AState = std::semiregular<T>&& reflect::WithStructure<T>;

  /// A function that modifies a state
  template<typename T, typename State>
  concept AnAction = util::callable<T, void(State&)>;

  /// A std::bitset with an entry for each field in the flattened state struct
  template<AState State>
  using BitSet = std::bitset<reflect::flat_size<State>()>;

  // Forward Declarations

  /// A Channel through which a single Producer can send state to multiple consumers
  template<AState... States>
  struct Channel;

  /// Sends state to multiple Consumers through a Channel
  template<AState... States>
  struct Producer;

  /// Receives state from a single producer through a Channel
  template<AState... States>
  struct Consumer;

  namespace detail {
    struct StateDiffTraits {
      template<reflect::AMemberInfo Info, reflect::AMemberInfo... Parents>
      struct Member {
        using BitSet = std::bitset<reflect::flat_size<typename meta::head_t<meta::list<Parents..., Info>>::struct_t>()>;

        Member(BitSet& b) : bitset_(b) {}

        bool has_changed() const
        {
          return bitset_.test(reflect::flat_idx<Info, Parents...>());
        }

      private:
        BitSet& bitset_;
      };
    };
  } // namespace detail

  template<AState State>
  struct Diff : reflect::structure<State, detail::StateDiffTraits> {
    using BitSet = std::bitset<reflect::flat_size<State>()>;

    Diff(BitSet b = {}) : reflect::structure<State, detail::StateDiffTraits>(bitset_), bitset_(b) {}

    BitSet& bitset()
    {
      return bitset_;
    }

  private:
    BitSet bitset_;
  };

  template<AState State>
  struct Updater;

  namespace detail {
    struct UpdaterTraits {
      template<reflect::AMemberInfo Info, reflect::AMemberInfo... Parents>
      struct Member {
        using State = typename meta::head_t<meta::list<Parents..., Info>>::struct_t;

        Member(Updater<State>& u) : updater_(u) {}

        /// Mark this field (and all subfields) as changed, and return a reference
        typename Info::value_type& update()
        {
          for (int i = 0; i < reflect::flat_size<typename Info::value_type>(); i++) {
            updater_.bitset()[reflect::flat_idx<Info, Parents...>() + i] = true;
          }
          return reflect::get<Info, Parents...>(updater_.state());
        }

        const typename Info::value_type& get() const
        {
          return reflect::get<Info, Parents...>(updater_.state());
        }

        typename Info::value_type& operator()()
        {
          return update();
        }

      private:
        Updater<State>& updater_;
      };
    };
  } // namespace detail

  template<AState State>
  struct Updater : reflect::structure<State, detail::UpdaterTraits> {
    using BitSet = typename Diff<State>::BitSet;

    Updater(State& s, BitSet b = {}) : reflect::structure<State, detail::UpdaterTraits>(*this), state_(s), bitset_(b) {}

    BitSet& bitset()
    {
      return bitset_;
    }

    State& state()
    {
      return state_;
    }

    State& state() const
    {
      return state_;
    }

  private:
    State& state_;
    BitSet bitset_;
  };

  namespace detail {

    template<AState State, reflect::AMemberInfo M, reflect::AMemberInfo... Members, reflect::AMemberInfo... Parents>
    void for_each_changed_impl(State& s, const BitSet<State>& changed, auto&& f, Parents... parents)
    {
      if (changed[reflect::flat_idx<M, Parents...>()]) {
        f(reflect::Member<M, reflect::EmptyStructureTraits, Parents...>());
      } else {
        [&]<typename... Ms>(meta::list<Ms...>)
        {
          if constexpr (sizeof...(Ms) > 0) {
            for_each_changed_impl<State, Ms...>(s, changed, f, parents..., M());
          }
        }
        (reflect::members_t<typename M::value_type>());
      }
      if constexpr (sizeof...(Members) > 0) for_each_changed_impl<State, Members...>(s, changed, f, parents...);
    }
  } // namespace detail

  template<AState State>
  void for_each_changed(State& s, const BitSet<State>& changed, auto&& f)
  {
    [&]<typename... Ms>(meta::list<Ms...>)
    {
      if constexpr (sizeof...(Ms) > 0) {
        detail::for_each_changed_impl<State, Ms...>(s, changed, f);
      }
    }
    (reflect::members_t<State>());
  }

} // namespace otto::itc
