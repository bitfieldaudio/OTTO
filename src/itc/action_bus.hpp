#pragma once

#include <nanorange.hpp>

#include "action_queue.hpp"
#include "action_receiver_registry.hpp"

namespace otto::itc {

  struct AudioBus {};
  struct GraphicsBus {};
  struct LogicBus {};

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
        DLOGI("Action {} received on {} by {} receivers", get_type_name<Tag>(), get_type_name<BusTag>(), registry.size());
        registry.call_all(ad.args);
      });
    }

    static ActionQueue queue;
  };

  template<typename BusTag>
  ActionQueue ActionBus<BusTag>::queue;

  /// Send an action to receivers on one or more busses
  template<typename... BusTags, typename Tag, typename... Args, typename... ArgRefs>
  void send_to_bus(Action<Tag, Args...> a, ArgRefs&&... args) {
    meta::for_each<meta::flatten_t<meta::list<BusTags...>>>([&] (auto one) {
        using BusTag = meta::_t<decltype(one)>;
        ActionBus<BusTag>::send(Action<Tag, Args...>::data(args...));
    });
  }

  /// An @ref ActionReceiver that registers and unregisters itself on a global action bus.
  ///
  /// @tparam BusTag the tag type denoting the bus to register on
  /// @tparam Actions the actions to register for. Can be a mixture of actions and `meta::list`s of actions
  template<typename BusTag, typename... Actions>
  struct ActionReceiverOnBus : ActionReceiver<Actions...> {
    using ActionReceiver = ActionReceiver<Actions...>;
    using typename ActionReceiver::ActionList;

    static_assert(is_bus_tag_v<BusTag>, "First template parameter to ActionReceiverOnBus must be the tag of a bus");

    /// It's not strictly necessary to delete the copy constructor,
    /// so if we ever have a real usecase for keeping it, remove this.
    /// Usually though, these are objects that we dont want to be copied.
    ActionReceiverOnBus(const ActionReceiverOnBus&) = delete;

    ActionReceiverOnBus() noexcept
    {
      meta::for_each<ActionList>([this](auto one) {
        using Action = meta::_t<decltype(one)>;
        DLOGI("Receiver registered on {} for {}", get_type_name<BusTag>(), get_type_name<typename Action::tag_type>());
        detail::action_receiver_registry<BusTag, Action>.add(this);
      });
    }

    ~ActionReceiverOnBus() noexcept
    {
      meta::for_each<ActionList>([this](auto one) {
        using Action = meta::_t<decltype(one)>;
        DLOGI("Receiver unregistered on {} for {}", get_type_name<BusTag>(), get_type_name<typename Action::tag_type>());
        detail::action_receiver_registry<BusTag, Action>.remove(this);
      });
    }
  };
} // namespace otto::itc
