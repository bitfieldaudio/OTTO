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

  template<typename Tag, typename ValueType>
  struct Prop {
    using value_type = ValueType;
    using tag_type = Tag;
    using change_action = Action<Tag, value_type, value_type>;

    Prop(value_type v) : value(v) {}

    value_type value;

    ActionData<change_action> set(value_type new_val)
    {
      auto res = change_action::data(new_val, value);
      value = new_val;
      return res;
    }

    bool operator==(const value_type& rhs) const
    {
      return value == rhs;
    }
  };

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
