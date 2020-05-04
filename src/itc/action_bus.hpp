#pragma once

#include <nanorange.hpp>

#include "action_queue.hpp"
#include "action_receiver_registry.hpp"
#include "util/local_vector.hpp"

namespace otto::itc {

  struct AudioBus {};
  struct GraphicsBus {};
  struct LogicBus {};

  namespace detail {
    auto other_busses(AudioBus) -> meta::list<GraphicsBus, LogicBus>;
    auto other_busses(GraphicsBus) -> meta::list<LogicBus, AudioBus>;
    auto other_busses(LogicBus) -> meta::list<AudioBus, GraphicsBus>;
  } // namespace detail

  template<typename BusTag>
  using others = decltype(detail::other_busses(BusTag()));

  template<typename T>
  constexpr bool is_bus_tag_v = util::is_one_of_v<T, AudioBus, GraphicsBus, LogicBus>;

  namespace detail {
    template<typename BusTag, typename Action>
    ActionReceiverRegistry<Action> action_receiver_registry;
  }

  template<typename BusTag_>
  struct ActionBus {
    using BusTag = BusTag_;
    static_assert(is_bus_tag_v<BusTag>, "The BusTag must be one of the registered bus tag types");

    ActionBus() = delete;

    template<typename Tag, typename... Args>
    static void send(ActionData<Action<Tag, Args...>> action_data)
    {
      queue.push([ad = std::move(action_data)] { //
        auto& registry = detail::action_receiver_registry<BusTag, Action<Tag, Args...>>;
        DLOGI("Action {} received on {} by {} receivers", get_type_name<Tag>(), get_type_name<BusTag>(),
              registry.size());
        registry.call_all(ad.args);
      });
    }

    template<typename Tag, typename... Args>
    static void send_to(ActionChannel channel, ActionData<Action<Tag, Args...>> action_data)
    {
      queue.push([channel, ad = std::move(action_data)] { //
        auto& registry = detail::action_receiver_registry<BusTag, Action<Tag, Args...>>;
        DLOGI("Action {} received on ({}, {}) by {} receivers", channel, get_type_name<Tag>(), get_type_name<BusTag>(),
              registry.size());
        registry.call_for_channel(channel, ad.args);
      });
    }

    static ActionQueue queue;
  };

  template<typename BusTag>
  ActionQueue ActionBus<BusTag>::queue;

  /// Send an action to receivers on one or more busses
  template<typename... BusTags, typename Tag, typename... Args, typename... ArgRefs>
  void send_to_bus(ActionChannel c, Action<Tag, Args...> a, ArgRefs&&... args)
  {
    meta::for_each<meta::flatten_t<meta::list<BusTags...>>>([&](auto one) {
      using BusTag = meta::_t<decltype(one)>;
      ActionBus<BusTag>::send_to(c, Action<Tag, Args...>::data(args...));
    });
  }

  /// Send a function to be executed on one or more busses
  template<typename... BusTags, typename Callable, typename = std::enable_if_t<std::is_invocable_v<Callable>>>
  void send_to_bus(Callable&& c)
  {
    meta::for_each<meta::flatten_t<meta::list<BusTags...>>>([&](auto one) {
      using BusTag = meta::_t<decltype(one)>;
      ActionBus<BusTag>::queue.push(c);
    });
  }

  /// Interface for actionreceiveronbus
  struct ActionReceiverOnBusBase {
    virtual ~ActionReceiverOnBusBase() noexcept = default;
    virtual void register_to(ActionChannel) noexcept = 0;
    virtual void unregister_from(ActionChannel) noexcept = 0;
    virtual void unregister_from_all() noexcept = 0;
  };

  /// An @ref ActionReceiver that registers and unregisters itself on a global action bus.
  ///
  /// @tparam BusTag the tag type denoting the bus to register on
  /// @tparam Actions the actions to register for. Can be a mixture of actions and `meta::list`s of actions
  template<typename BusTag, typename... Actions>
  struct ActionReceiverOnBus : ActionReceiverOnBusBase, ActionReceiver<Actions...> {
    using ActionReceiverType = ActionReceiver<Actions...>;
    using typename ActionReceiverType::ActionList;

    static_assert(is_bus_tag_v<BusTag>, "First template parameter to ActionReceiverOnBus must be the tag of a bus");

    /// It's not strictly necessary to delete the copy constructor,
    /// so if we ever have a real usecase for keeping it, remove this.
    /// Usually though, these are objects that we dont want to be copied.
    ActionReceiverOnBus(const ActionReceiverOnBus&) = delete;

    ActionReceiverOnBus() noexcept {}

    ~ActionReceiverOnBus() noexcept
    {
      meta::for_each<ActionList>([this](auto one) {
        using Action = meta::_t<decltype(one)>;
        DLOGI("Receiver destroyed on {} for {}", get_type_name<BusTag>(),
              get_type_name<typename Action::tag_type>());
        detail::action_receiver_registry<BusTag, Action>.remove_from_all(this);
      });
    }

    // ActionReceivers can maximally have 16 children
    using Children = util::local_vector<ActionReceiverOnBusBase*, 16>;
    void set_children(Children children)
    {
      OTTO_ASSERT(children_.size() == 0);
      children_ = children;
    }

    template<typename... Ts>
    void set_children(Ts&&... children)
    {
      (add_child(FWD(children)), ...);
    }

    void register_to(ActionChannel channel) noexcept override
    {
      channels_.insert(channel);
      meta::for_each<ActionList>([channel, this](auto one) {
        using Action = meta::_t<decltype(one)>;
        DLOGI("Receiver registered on ({},{}) for {}", channel, get_type_name<BusTag>(),
              get_type_name<typename Action::tag_type>());
        detail::action_receiver_registry<BusTag, Action>.add_to(channel, this);
      });
      for (auto* child : children_) child->register_to(channel);
    }

    void unregister_from(ActionChannel channel) noexcept override
    {
      channels_.erase(channel);
      meta::for_each<ActionList>([&](auto one) {
        using Action = meta::_t<decltype(one)>;
        DLOGI("Receiver registered on ({},{}) for {}", channel, get_type_name<BusTag>(),
              get_type_name<typename Action::tag_type>());
        detail::action_receiver_registry<BusTag, Action>.remove_from(channel, this);
      });
      for (auto* child : children_) child->unregister_from(channel);
    }

    void unregister_from_all() noexcept override
    {
      channels_.clear();
      meta::for_each<ActionList>([this](auto one) {
        using Action = meta::_t<decltype(one)>;
        DLOGI("Receiver unregistered from (all,{}) for {}", get_type_name<BusTag>(),
              get_type_name<typename Action::tag_type>());
        detail::action_receiver_registry<BusTag, Action>.remove_from_all(this);
      });
      for (auto* child : children_) child->unregister_from_all();
    }

    template<typename ActionTag, typename... Args, typename... ArgRefs>
    void send_action(Action<ActionTag, Args...> a, ArgRefs&&... args) const noexcept
    {
      for (auto channel : channels_) {
        send_to_bus<others<BusTag>>(channel, a, FWD(args)...);
      }
    }

  private:
    void add_child(ActionReceiverOnBusBase* c)
    {
      children_.push_back(c);
    }

    void add_child(ActionReceiverOnBusBase& c)
    {
      children_.push_back(&c);
    }
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<ActionReceiverOnBusBase, T>>>
    void add_child(const std::unique_ptr<T>& c)
    {
      children_.push_back(c.get());
    }
    /// What are you doing, don't move the children in here!
    template<typename T>
    void add_child(std::unique_ptr<T>&& c) = delete;

    Children children_;
    util::flat_set<ActionChannel> channels_;
  };
} // namespace otto::itc
