#pragma once

#include <functional>
#include <util/flat_map.hpp>
#include <vector>

namespace otto::util {

  namespace obs_detail {
    /// Private base type of all observables, used to type-erase for `OwnsObservers`
    struct ObservableBase {
      virtual void remove_observer(unsigned key) noexcept;
    };
  } // namespace obs_detail

  /// A subtype of this type can be given as the first argument to `Observable::observe`,
  /// and thus used to manage the lifetime of an observer.
  ///
  /// Any class which wishes to observe observables should extend this.
  struct OwnsObservers {
    ~OwnsObservers() noexcept
    {
      for (auto&& [o, idx] : observers) {
        o.remove_observer(idx);
      }
    }

  private:
    template<typename T>
    friend struct Observable;
    std::vector<std::pair<obs_detail::ObservableBase&, unsigned>> observers;
  };

  /// An object that can have observers attached to it.
  /// 
  /// Observers are functions of type `void(T)`, which will be called with the value,
  /// whenever notified.
  template<typename T>
  struct Observable : private obs_detail::ObservableBase {
    using Observer = std::function<void(T)>;
    using KeyType = unsigned;

    /// Add a function as an observer of this observable, tied to the lifetime of an owner.
    ///
    /// The observer will be called instantly with the current value as well.
    ///
    /// The observer is removed in the destructor of the owner, and thus this observable must
    /// live longer than the owner. Otherwise it must be manually removed using @ref remove_observer
    ///
    /// @returns the key of the observer. Can later be used to manually remove the observer using
    /// @ref remove_observer
    KeyType observe(OwnsObservers* owner, Observer o)
    {
      auto func = observers.emplace(last_key, std::move(o)).first;
      if (owner) owner.observers.emplace_back(*this, last_key);
      last_key++;
      (*func)();
      return last_key - 1;
    }

    /// Add a function as an observer of this observable, tied to the lifetime of an owner.
    ///
    /// The observer will be called instantly with the current value as well.
    ///
    /// The observer is removed in the destructor of the owner, and thus this observable must
    /// live longer than the owner. Otherwise it must be manually removed using @ref remove_observer
    ///
    /// @returns the key of the observer. Can later be used to manually remove the observer using
    /// @ref remove_observer
    KeyType observe(OwnsObservers& owner, Observer o)
    {
      return observe(&owner, std::move(o));
    }

    /// Notify all attached observers
    void notify_observers()
    {
      T value = get_value();
      for (auto& o : observers) {
        o(value);
      }
    }

    /// Remove the observer matching `key`
    /// 
    /// `key` is the result of calling `observe`.
    /// 
    /// In the usual case, where the observable lives longer than the observer, the observer should 
    /// simply be attached to an owner of type `OwnsObservers`.
    void remove_observer(KeyType key) noexcept final
    {
      observers.erase(key);
    }

  protected:
    virtual T get_value() = 0;

  private:
    KeyType last_key = 0;
    util::flat_map<KeyType, Observer> observers;
  };
} // namespace otto::util
