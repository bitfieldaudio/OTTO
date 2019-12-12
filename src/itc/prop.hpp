#pragma once

#include "action.hpp"
#include "core/props/props.hpp"

namespace otto::core::props::mixin {

  template<typename Tag, typename ActionSender>
  struct action {
    using tag_type = action<Tag, ActionSender>;
    using hooks = ::otto::core::props::mixin::hooks<action<Tag, ActionSender>>;
    constexpr static const char* name = "action";
    template<typename... Args>
    static auto init(Args&&... args)
    {
      return ::otto::core::props::make_initializer<action<Tag, ActionSender>>(std::forward<Args>(args)...);
    }
  };

  template<typename PropTag, typename Sender, typename ValueType, typename TagList>
  struct leaf<action<PropTag, Sender>, ValueType, TagList> {
    using action_mixin = action<PropTag, Sender>;
    OTTO_PROPS_MIXIN_DECLS(action_mixin);
    using change_action = itc::Action<PropTag, value_type>;

    void init(Sender& sndr) noexcept
    {
      sender = &sndr;
    }

    void init(Sender* sndr) noexcept
    {
      sender = sndr;
    }

    void on_hook(hook<common::hooks::after_set>& hook) noexcept
    {
      send_actions();
    }

    /// Send change actions with the current value to all receivers
    void send_actions() const noexcept
    {
      OTTO_ASSERT(sender != nullptr);
      sender->push(change_action::data(as_prop().get()));
    }

  private:
    Sender* sender = nullptr;
  };

} // namespace otto::core::props::mixin
namespace otto::itc {

  /// A property which queues change_actions on set
  ///
  /// @tparam Sndr An @ref ActionSender to which the actions will be enqueued
  /// @tparam Tag A unique tag type for this property
  /// @tparam Val The property value type
  /// @tparam Mixins property mixins for this property
  template<typename Sndr, typename Tag, typename Val, typename... Mixins>
  struct ActionProp : core::props::Property<Val, core::props::mixin::action<Tag, Sndr>, Mixins...> {
    using prop_impl_t = core::props::Property<Val, core::props::mixin::action<Tag, Sndr>, Mixins...>;
    using value_type = Val;
    using action_mixin = core::props::mixin::action<Tag, Sndr>;
    using change_action = itc::Action<Tag, value_type>;

    template<typename TRef, typename... Args>
    ActionProp(Sndr* sndr, TRef&& value, Args&&... args)
      : core::props::Property<Val, core::props::mixin::action<Tag, Sndr>, Mixins...>(std::forward<TRef>(value),
                                                                                     action_mixin::init(sndr),
                                                                                     FWD(args)...)
    {
      this->send_actions();
    }

    template<typename TRef, typename... Args>
    ActionProp(Sndr& sndr, TRef&& value, Args&&... args) : ActionProp(&sndr, FWD(value), FWD(args)...)
    {}

    using prop_impl_t::operator=;
    using prop_impl_t::operator const value_type&;

    DECL_REFLECTION(ActionProp, ("value", &ActionProp::get, &ActionProp::set))
  };

  /// Serialize a property to json
  template<typename Sndr, typename Tag, typename ValueType, typename... Mixins>
  inline nlohmann::json serialize(const ActionProp<Sndr, Tag, ValueType, Mixins...>& prop)
  {
    using ::otto::util::serialize;
    return serialize(prop.get());
  }

  /// Deserialize a property from json
  template<typename Sndr, typename Tag, typename ValueType, typename... Mixins>
  inline void deserialize(ActionProp<Sndr, Tag, ValueType, Mixins...>& prop, const nlohmann::json& json)
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
