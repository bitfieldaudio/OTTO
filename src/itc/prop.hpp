#pragma once

#include "action.hpp"
#include "action_bus.hpp"
#include "core/props/props.hpp"

namespace otto::core::props::mixin {

  template<typename Tag, typename ActionBusOrList>
  struct action;

  template<typename Tag, typename ActionBusTag>
  struct action {
    using ActionBusList = meta::list<ActionBusTag>;
    using tag_type = action<Tag, ActionBusList>;
    using hooks = ::otto::core::props::mixin::hooks<action<Tag, ActionBusList>>;
    constexpr static const char* name = "action";
  };

  template<typename Tag, typename... ActionBusTags>
  struct action<Tag, meta::list<ActionBusTags...>> {
    using ActionBusList = meta::list<ActionBusTags...>;
    using tag_type = action<Tag, ActionBusList>;
    using hooks = ::otto::core::props::mixin::hooks<action<Tag, ActionBusList>>;
    constexpr static const char* name = "action";
  };

  template<typename PropTag, typename BusList, typename ValueType, typename TagList>
  struct leaf<action<PropTag, BusList>, ValueType, TagList> : itc::ActionReceiverOnBus<itc::LogicBus> {
    using action_mixin = action<PropTag, BusList>;
    OTTO_PROPS_MIXIN_DECLS(action_mixin);
    using change_action = itc::Action<PropTag, value_type>;

    void on_hook(hook<common::hooks::after_set>& hook) noexcept
    {
      send_actions();
    }

    /// Send change actions with the current value to all receivers
    void send_actions() const noexcept
    {
      send_action(change_action(), as_prop().get());
    }
  };

} // namespace otto::core::props::mixin
namespace otto::itc {

  /// A property which queues change_actions on set
  ///
  /// @tparam Sndr An @ref ActionSender to which the actions will be enqueued
  /// @tparam Tag A unique tag type for this property
  /// @tparam Val The property value type
  /// @tparam Mixins property mixins for this property
  template<typename BusTags, typename Tag, typename Val, typename... Mixins>
  struct ActionProp : core::props::Property<Val, core::props::mixin::action<Tag, BusTags>, Mixins...> {
    using prop_impl_t = core::props::Property<Val, core::props::mixin::action<Tag, BusTags>, Mixins...>;
    using value_type = Val;
    using action_mixin = core::props::mixin::action<Tag, BusTags>;
    using change_action = itc::Action<Tag, value_type>;

    using prop_impl_t::prop_impl_t;
    using prop_impl_t::operator=;
    using prop_impl_t::operator const value_type&;

    DECL_REFLECTION(ActionProp, ("value", &ActionProp::get, &ActionProp::set))
  };

  /// Serialize a property to json
  template<typename Bus, typename Tag, typename ValueType, typename... Mixins>
  inline nlohmann::json serialize(const ActionProp<Bus, Tag, ValueType, Mixins...>& prop)
  {
    using ::otto::util::serialize;
    return serialize(prop.get());
  }

  /// Deserialize a property from json
  template<typename Bus, typename Tag, typename ValueType, typename... Mixins>
  inline void deserialize(ActionProp<Bus, Tag, ValueType, Mixins...>& prop, const nlohmann::json& json)
  {
    using ::otto::util::deserialize;
    static_assert(std::is_default_constructible_v<ValueType>,
                  "A property type must be default constructible to be deserializable");
    ValueType v{};
    deserialize(v, json);
    prop.set(std::move(v));
  }

  /// Get the property type from a member pointer to it
  struct PropTypeFor {
    static constexpr auto _get(...) -> void;
    template<typename PropType, typename Class>
    static constexpr auto _get(PropType Class::*member_ptr) -> std::decay_t<PropType>;

    template<auto PropPtr>
    using get = decltype(_get(PropPtr));
  };

  /// The Action type for a property member pointer
  template<auto PropPtr>
  using prop_change = typename PropTypeFor::get<PropPtr>::change_action;

  /// The Action type for a property tag type
  template<typename PropTag, typename ValueType>
  using prop_tag_change = Action<PropTag, ValueType>;

} // namespace otto::itc
