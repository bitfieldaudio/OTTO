#pragma once

#include <functional>
#include <util/flat_map.hpp>
#include <util/flat_multimap.hpp>
#include <vector>

namespace otto::util {

  struct OwnsObservers;

  namespace obs_detail {
    /// Private base type of all observables, used to type-erase for `OwnsObservers`
    struct ObservableBase {
      virtual void remove_observer(unsigned key) noexcept = 0;
      virtual void remove_owner(OwnsObservers*) noexcept = 0;
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
        o->remove_observer(idx);
      }
      for (auto o : observers.keys()) {
        o->remove_owner(this);
      }
    }

  private:
    template<typename T>
    friend struct Observable;
    util::flat_multimap<obs_detail::ObservableBase*, unsigned> observers;
  };

  /// An object that can have observers attached to it.
  ///
  /// Observers are functions of type `void(T)`, which will be called with the value,
  /// whenever notified.
  template<typename T>
  struct Observable : private obs_detail::ObservableBase {
    using Observer = std::function<void(T)>;
    using KeyType = unsigned;

    virtual ~Observable()
    {
      for (auto owner_ptr : owners) {
        owner_ptr->observers.erase_all((obs_detail::ObservableBase*) this);
      }
    }

    /// Add a function as an observer of this observable, tied to the lifetime of an owner.
    ///
    /// The observer will be called instantly with the current value as well.
    ///
    /// The observer is removed in the destructor of the owner, or can alternatively be manually
    /// removed using @ref remove_observer.
    ///
    /// If you want to manage the lifetime of the observer manually, you can do this by explicitly
    /// passing `nullptr` as the owner.
    ///
    /// @returns the key of the observer. Can later be used to manually remove the observer using
    /// @ref remove_observer
    KeyType observe(OwnsObservers* owner, Observer o)
    {
      auto [key, func] = *observers.emplace(last_key, std::move(o)).first;
      if (owner) {
        owner->observers.emplace((obs_detail::ObservableBase*) this, last_key);
        owners.insert(owner);
      }
      last_key++;
      func(get_value());
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

    /// Add a function as an observer of this observable, tied to the lifetime of an owner.
    ///
    /// The observer will be called instantly as well.
    ///
    /// The observer is removed in the destructor of the owner, and thus this observable must
    /// live longer than the owner. Otherwise it must be manually removed using @ref remove_observer
    ///
    /// @returns the key of the observer. Can later be used to manually remove the observer using
    /// @ref remove_observer
    template<typename Callable, typename = std::enable_if_t<std::is_invocable_v<Callable>>>
    KeyType observe(OwnsObservers* owner, Callable&& c)
    {
      return observe(owner, [func = FWD(c)](T) { func(); });
    }

    /// Add a function as an observer of this observable, tied to the lifetime of an owner.
    ///
    /// The observer will be called instantly as well.
    ///
    /// The observer is removed in the destructor of the owner, and thus this observable must
    /// live longer than the owner. Otherwise it must be manually removed using @ref remove_observer
    ///
    /// @returns the key of the observer. Can later be used to manually remove the observer using
    /// @ref remove_observer
    template<typename Callable, typename = std::enable_if_t<std::is_invocable_v<Callable>>>
    KeyType observe(OwnsObservers& owner, Callable&& c)
    {
      return observe(&owner, [func = FWD(c)](T) { func(); });
    }

    /// Add a function as an observer of this observable, tied to the lifetime of an owner.
    ///
    /// The observer will NOT be called instantly with the current value as well.
    ///
    /// The observer is removed in the destructor of the owner, or can alternatively be manually
    /// removed using @ref remove_observer.
    ///
    /// If you want to manage the lifetime of the observer manually, you can do this by explicitly
    /// passing `nullptr` as the owner.
    ///
    /// @returns the key of the observer. Can later be used to manually remove the observer using
    /// @ref remove_observer
    KeyType observe_no_imidiate_call(OwnsObservers* owner, Observer o)
    {
      observers.emplace(last_key, std::move(o));
      if (owner) {
        owner->observers.emplace((obs_detail::ObservableBase*) this, last_key);
        owners.insert(owner);
      }
      last_key++;
      return last_key - 1;
    }

    /// Add a function as an observer of this observable, tied to the lifetime of an owner.
    ///
    /// The observer will NOT be called instantly with the current value as well.
    ///
    /// The observer is removed in the destructor of the owner, and thus this observable must
    /// live longer than the owner. Otherwise it must be manually removed using @ref remove_observer
    ///
    /// @returns the key of the observer. Can later be used to manually remove the observer using
    /// @ref remove_observer
    KeyType observe_no_imidiate_call(OwnsObservers& owner, Observer o)
    {
      return observe_no_imidiate_call(&owner, std::move(o));
    }

    /// Add a function as an observer of this observable, tied to the lifetime of an owner.
    ///
    /// The observer will NOT be called instantly as well.
    ///
    /// The observer is removed in the destructor of the owner, and thus this observable must
    /// live longer than the owner. Otherwise it must be manually removed using @ref remove_observer
    ///
    /// @returns the key of the observer. Can later be used to manually remove the observer using
    /// @ref remove_observer
    template<typename Callable, typename = std::enable_if_t<std::is_invocable_v<Callable>>>
    KeyType observe_no_imidiate_call(OwnsObservers* owner, Callable&& c)
    {
      return observe_no_imidiate_call(owner, [func = FWD(c)](T) { func(); });
    }

    /// Add a function as an observer of this observable, tied to the lifetime of an owner.
    ///
    /// The observer will NOT be called instantly as well.
    ///
    /// The observer is removed in the destructor of the owner, and thus this observable must
    /// live longer than the owner. Otherwise it must be manually removed using @ref remove_observer
    ///
    /// @returns the key of the observer. Can later be used to manually remove the observer using
    /// @ref remove_observer
    template<typename Callable, typename = std::enable_if_t<std::is_invocable_v<Callable>>>
    KeyType observe_no_imidiate_call(OwnsObservers& owner, Callable&& c)
    {
      return observe_no_imidiate_call(&owner, [func = FWD(c)](T) { func(); });
    }

    /// Notify all attached observers
    void notify_observers()
    {
      T value = get_value();
      for (auto&& func : observers.values()) {
        func(value);
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

    friend OwnsObservers;
    void remove_owner(OwnsObservers* owner) noexcept final
    {
      owners.erase(owner);
    }

  private:
    KeyType last_key = 0;
    util::flat_map<KeyType, Observer> observers;
    util::flat_set<OwnsObservers*> owners;
  };
} // namespace otto::util
