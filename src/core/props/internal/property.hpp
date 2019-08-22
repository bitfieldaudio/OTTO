#pragma once

#include "../internal/mixin_macros.hpp"
#include "base.hpp"
#include "tag_list.hpp"
#include "util/reflection.hpp"

namespace otto::core::props {

  struct common {
    struct hooks {
      /// Allows you to change the value that is set
      struct on_set : mixin::hook<mixin::value_type> {};
      /// Fired after the value has been changed. At this point the value can be read
      /// using .value(), and the old value can be read
      struct after_set : mixin::hook<mixin::value_type> {};
    };
  };

  // PropertyImpl /////////////////////////////////////////////////////////////

  template<typename T, typename TagList>
  struct PropertyImpl;

  template<typename T, typename... Tags>
  struct PropertyImpl<T, tag_list<Tags...>> : MixinTag::leaf<Tags, T, tag_list<Tags...>>... {
    using value_type = T;
    using tag_list = tag_list<Tags...>;

    template<typename Tag>
    using mixin = MixinTag::leaf<Tag, T, tag_list>;

    using MixinTag::leaf<Tags, T, tag_list>::leaf...;
    using mixin<Tags>::operator=...;

    /// Initialize the mixin of type `Tag` with args
    template<typename Tag, typename... Args>
    void init(Args&&... args)
    {
      static_assert(meta::contains_v<tag_list, Tag>,
                    "Attempt to init a mixin which the property does not have");
      static_cast<mixin<Tag>*>(this)->init(std::forward<Args>(args)...);
    }

    template<typename Tag, typename... Args>
    void init_with_tuple(const TaggedTuple<Tag, Args...>& tt)
    {
      // Clang is bugged, and marks the `this` capture as unused if the lambda
      // is inlined in the `apply` call.
      // GCC 7.2 marks the variable `lambda` as unused.
      [[maybe_unused]] auto lambda = [this](auto&&... init_args) { this->init<Tag>(init_args...); };
      std::apply(lambda, tt.args);
    }

    template<typename TRef, typename... Args>
    PropertyImpl(TRef&& value, Args&&... args) : value_(std::forward<TRef>(value))
    {
      if constexpr ((is_initializer_v<Args> && ...)) {
        // GCC 7.2 marks this variable as unused.
        [[maybe_unused]] auto lambda = [](PropertyImpl* obj, auto&& tuple) {
          obj->init_with_tuple(tuple);
        };
        // fold expression on comma operator
        (lambda(this, std::forward<Args>(args)), ...);
      } else {
        static_cast<inherits_from_mixins_t<T, tag_list>&>(*this) = {std::forward<Args>(args)...};
      }
    }

    template<typename Tag>
    constexpr static bool is = ::otto::core::props::contains_tag_v<tag_list, Tag>;

    template<typename Tag>
    auto as() -> ::std::enable_if_t<PropertyImpl::template is<Tag>,
                                    MixinTag::leaf<Tag, value_type, tag_list>&>
    {
      return static_cast<MixinTag::leaf<Tag, value_type, tag_list>&>(*this);
    }

    template<typename Tag>
    auto as() const -> ::std::enable_if_t<PropertyImpl::template is<Tag>,
                                          const MixinTag::leaf<Tag, value_type, tag_list>&>
    {
      return static_cast<const MixinTag::leaf<Tag, value_type, tag_list>&>(*this);
    }

    template<typename Hook>
    using hook = HookTag::impl_t<Hook, value_type>;

    template<typename Hook>
    typename hook<Hook>::arg_type run_hook(const typename hook<Hook>::arg_type& arg)
    {
      return ::otto::core::props::detail::run_hook<Hook>(*this, arg);
    }

    template<typename Hook>
    typename hook<Hook>::arg_type run_hook(const typename hook<Hook>::arg_type& arg) const
    {
      return ::otto::core::props::detail::run_hook<Hook>(*this, arg);
    }

    template<typename Hook>
    typename hook<Hook>::arg_type run_hook()
    {
      return ::otto::core::props::detail::run_hook<Hook>(*this);
    }

    template<typename Hook>
    typename hook<Hook>::arg_type run_hook() const
    {
      return ::otto::core::props::detail::run_hook<Hook>(*this);
    }

    const value_type& get() const
    {
      return value_;
    }

    void set(const value_type& v)
    {
      auto oldval = value_;
      value_ = run_hook<common::hooks::on_set>(v);
      run_hook<common::hooks::after_set>(oldval);
    }

    PropertyImpl& operator=(const value_type& rhs)
    {
      set(rhs);
      return *this;
    }

    operator const value_type&() const
    {
      return get();
    }

    DECL_REFLECTION(PropertyImpl, ("value", &PropertyImpl::get, &PropertyImpl::set))
  protected:
    value_type value_;
  };

} // namespace otto::core::props

