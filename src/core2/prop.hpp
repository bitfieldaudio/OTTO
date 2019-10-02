#pragma once

#include "action.hpp"
#include "core/props/props.hpp"

namespace otto::core::props::mixin {

  template<typename Tag, typename ActionQueueHelper>
  struct action {
    using tag_type = action<Tag, ActionQueueHelper>;
    using hooks = ::otto::core::props::mixin::hooks<action<Tag, ActionQueueHelper>>;
    constexpr static const char* name = "action";
    template<typename... Args>
    static auto init(Args&&... args)
    {
      return ::otto::core::props::make_initializer<action<Tag, ActionQueueHelper>>(std::forward<Args>(args)...);
    }
  };

  template<typename PropTag, typename AQH, typename ValueType, typename TagList>
  struct otto::core::props::mixin::leaf<action<PropTag, AQH>, ValueType, TagList> {
    using action = action<PropTag, AQH>;
    OTTO_PROPS_MIXIN_DECLS(action);
    using change_action = core2::Action<PropTag, value_type, value_type>;

    void init(AQH& aqh) {
      action_queue_helper = &aqh;
    }

    void init(AQH* aqh) {
      action_queue_helper = aqh;
    }

    void on_hook(hook<common::hooks::after_set>& hook)
    {
      OTTO_ASSERT(action_queue_helper != nullptr);
      action_queue_helper->push(change_action::data(as_prop().get(), hook.value()));
    }

  private:
    AQH* action_queue_helper = nullptr;
  };

} // namespace otto::core::props::mixin
namespace otto::core2 {

  /// A property which queues change_actions on set
  /// 
  /// @tparam Aqh An @ref ActionQueueHelper to which the actions will be enqueued
  /// @tparam Val The property value type
  /// @tparam Tag A unique tag type for this property
  /// @tparam Mixins property mixins for this property
  template<typename Aqh, typename Val, typename Tag, typename... Mixins>
  struct ActionProp : core::props::Property<Val, core::props::mixin::action<Tag, Aqh>, Mixins...> {
    using prop_impl_t = core::props::Property<Val, core::props::mixin::action<Tag, Aqh>, Mixins...>;
    using value_type = Val;
    using action_mixin = core::props::mixin::action<Tag, Aqh>;
    using change_action = core2::Action<Tag, value_type, value_type>;

    template<typename TRef, typename... Args>
    ActionProp(TRef&& value, Aqh* aqh, Args&&... args)
      : core::props::Property<Val, core::props::mixin::action<Tag, Aqh>, Mixins...>(std::forward<TRef>(value),
                                                                        action_mixin::init(aqh),
                                                                        FWD(args)...)
    {}

    ActionProp& operator=(const value_type& rhs)
    {
      this->set(rhs);
      return *this;
    }

    operator const value_type&() const
    {
      return this->get();
    }

    DECL_REFLECTION(ActionProp, ("value", &ActionProp::get, &ActionProp::set))
  };

  /// Serialize a property to json
  template<typename Aqh, typename ValueType, typename Tag, typename... Mixins>
  inline nlohmann::json serialize(const ActionProp<Aqh, ValueType, Tag, Mixins...>& prop)
  {
    using ::otto::util::serialize;
    return serialize(prop.get());
  }

  /// Deserialize a property from json
  template<typename Aqh, typename ValueType, typename Tag, typename... Mixins>
  inline void deserialize(ActionProp<Aqh, ValueType, Tag, Mixins...>& prop, const nlohmann::json& json)
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

} // namespace otto::core2
