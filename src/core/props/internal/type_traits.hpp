#pragma once

#include <string>

#include "util/meta.hpp"
#include "util/type_traits.hpp"

#include "base.hpp"

namespace otto::core::props {

  /// Type used to list tags
  template<typename... Tags>
  using tag_list = meta::list<Tags...>;

  // Type traits for mixins //

  namespace mixin {
    template<typename Tag>
    struct required_tags {
      using type = tag_list<>;
    };

    template<typename Tag>
    using required_tags_t = meta::_t<required_tags<Tag>>;

    template<typename Tag, typename ValueType, typename TagList>
    struct leaf;

    template<typename Tag>
    struct hooks {};

    /// Tag type used to create a hook with the value type as its argument
    struct value_type {};

    template<typename Argument>
    struct hook {
      template<typename HookTag, typename Val, HookOrder HO>
      struct type {
        using value_type = Val;
        using arg_type = Argument;

        type(const arg_type& a) : _arg(a) {}
        type(arg_type&& a) : _arg(std::move(a)) {}

        template<HookOrder HO1>
        type(type<HookTag, Val, HO1>&& rhs) : _arg(std::move(rhs.value()))
        {}
        operator arg_type&()
        {
          return _arg;
        }
        operator arg_type const&() const
        {
          return _arg;
        }
        arg_type& value()
        {
          return _arg;
        }
        arg_type const& value() const
        {
          return _arg;
        }

      private:
        arg_type _arg;
      };
    };

    template<>
    struct hook<void> {
      template<typename HookTag, typename Val, ::otto::core::props::HookOrder HO>
      struct type {
        using value_type = Val;
        using arg_type = void;
        type() = default;
        template<::otto::core::props::HookOrder HO1>
        type(type<HookTag, Val, HO1>&& rhs)
        {}
      };
    };

    template<>
    struct hook<value_type> {
      template<typename HookTag, typename Val, ::otto::core::props::HookOrder HO>
      using type = typename hook<Val>::template type<HookTag, Val, HO>;
    };
  } // namespace mixin

  // Concepts //

  // namespace cpts = nano::concepts;

  template<typename T>
  constexpr auto is_MixinValue = !std::is_void_v<T>;

  /// A hook implementation concept
  struct Hook {
    template<typename T>
    using value_type = typename T::value_type;

  private:
    static std::false_type _is(...);
    template<typename T, typename = std::enable_if_t<is_MixinValue<typename T::value_type>>>
    static std::true_type _is(T);

  public:
    template<typename T>
    static constexpr auto is = decltype(_is(std::declval<T>()))::value;
  };

  /// Concept of a Hook with a value
  struct HookWithValue {
    /// The value type of the property this belongs to
    template<typename H>
    using value_type = typename H::value_type;

    /// The argument type of the hook
    template<typename H>
    using arg_type = typename H::arg_type;

  private:
    static std::false_type _is(...);

    template<typename T,                  //
             typename = std::enable_if_t< //
               is_MixinValue<value_type<T>> && !std::is_void_v<arg_type<T>> &&
               std::is_same_v<arg_type<T>&, decltype(std::declval<T>().value())> &&
               std::is_convertible_v<T, arg_type<T>&>>>
    static std::true_type _is(T);

  public:
    template<typename T>
    static constexpr auto is = Hook::is<T>&& decltype(_is(std::declval<T>()))::value;
  };

  /// Concept of a hook tag type
  struct HookTag {
    /// Get the hook type from a tag and a value type
    template<typename HT, typename VT, HookOrder HO = HookOrder::Middle>
    using impl_t = typename HT::template type<HT, VT, HO>;

  private:
    static std::false_type _is(...);

    template<typename T,
             typename ValueType,
             HookOrder HO = HookOrder::Middle,
             typename = std::enable_if_t<Hook::is<typename T::template type<T, ValueType, HO>>>>
    static std::true_type _is(T, ValueType, meta::c<HO>);

  public:
    template<typename T, typename ValueType, HookOrder HO = HookOrder::Middle>
    static constexpr auto is =
      decltype(_is(std::declval<T>(), std::declval<ValueType>(), meta::c<HO>()))::value;
  };

  struct MixinImpl {
  private:
    static std::false_type _is(...);
    template<typename T,
             typename = std::enable_if_t<
               !std::is_void_v<typename T::value_type> && !std::is_void_v<typename T::tag_list> &&
               !std::is_void_v<typename T::hooks> && !std::is_void_v<typename T::property_type>>>
    static std::true_type _is(T);

  public:
    template<typename T>
    static constexpr auto is = decltype(_is(std::declval<T>()))::value;

    // HOOKS //

    /// Get the hook type from a tag and a Mixin type
    template<typename Mixin,
             typename HT,
             HookOrder HO = HookOrder::Middle,
             typename = std::enable_if_t<HookTag::is<HT, typename Mixin::value_type>>>
    using hook_t = HookTag::impl_t<HT, typename Mixin::value_type, HO>;

    /// Check if Mixin has a handler for Hook
    /// \privatesection
    template<typename Mixin, typename HT, HookOrder HO, typename = void>
    struct has_handler : std::false_type {
      static_assert(MixinImpl::is<Mixin> && HookTag::is<HT, typename Mixin::value_type>);
    };

    /// Check if Mixin has a handler for Hook
    /// \privatesection
    template<typename Mixin, typename HT, HookOrder HO>
    struct has_handler<
      Mixin,
      HT,
      HO,
      std::void_t<decltype(std::declval<Mixin>().on_hook(std::declval<hook_t<Mixin, HT, HO>&>()))>>
      : std::true_type {
      static_assert(MixinImpl::is<Mixin> && HookTag::is<HT, typename Mixin::value_type>);
    };

    /// Check if Mixin has a handler for Hook
    template<typename Mixin, typename Hook, HookOrder HO>
    constexpr static const bool has_handler_v = has_handler<Mixin, Hook, HO>::value;
  };

  /// Concept for a Tag used to identify a mixin
  struct MixinTag {
  private:
    static std::false_type _is(...);
    template<typename Tag,
             typename = std::enable_if_t<std::is_same_v<const char*, decltype(Tag::name)>>>
    static std::true_type _is(Tag);

  public:
    template<typename T>
    static constexpr auto is = decltype(_is(std::declval<T>()))::value;
    // Required Tags impl //

    /// Get all required tags for `Tag`
    template<typename Tag>
    using required_tags_t = typename mixin::required_tags<Tag>::type;

    /// Get mixin type for type `T` and tag `Tag`
    template<typename Tag, typename T, typename TagList>
    using leaf = mixin::leaf<Tag, T, TagList>;
  };

  namespace detail {

    /// Run `Mixin`'s handler for `Hook` if it has one
    template<typename HT,
             HookOrder HO,
             typename Mixin,
             typename = std::enable_if_t<HookTag::is<HT, typename Mixin::value_type>>>
    void run_hook_if_handler(Mixin& m, MixinImpl::hook_t<Mixin, HT, HO>& h)
    {
      if constexpr (MixinImpl::has_handler_v<Mixin, HT, HO>) {
        m.on_hook(h);
      }
    }

    template<typename H,
             typename Mixin,
             HookOrder HO,
             typename = std::enable_if_t<HookTag::is<H, typename Mixin::value_type>>>
    auto run_all_hooks_impl(Mixin& m, MixinImpl::hook_t<Mixin, H, HO>&& hook)
    {
      meta::for_each<typename Mixin::tag_list>([&hook, &m](auto&& mtype) {
        run_hook_if_handler<H, HO>(m.template as<decltype(mtype._t())>(), hook);
      });
      return std::move(hook);
    }

    /// Run handler for `Hook` for all of `Mixin`s siblings
    template<typename H,
             typename Mixin,
             typename = std::enable_if_t<HookTag::is<H, typename Mixin::value_type> &&
                                         !HookWithValue::is<MixinImpl::hook_t<Mixin, H>>>>
    void run_hook(Mixin& m)
    {
      MixinImpl::hook_t<Mixin, H, HookOrder::Before> hook{};
      auto h1 = run_all_hooks_impl<H, Mixin, HookOrder::Before>(m, std::move(hook));
      auto h2 = run_all_hooks_impl<H, Mixin, HookOrder::Early>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::Early>(std::move(h1)));
      auto h3 = run_all_hooks_impl<H, Mixin, HookOrder::Middle>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::Middle>(std::move(h2)));
      auto h4 = run_all_hooks_impl<H, Mixin, HookOrder::Late>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::Late>(std::move(h3)));
      [[maybe_unused]] auto h5 = run_all_hooks_impl<H, Mixin, HookOrder::After>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::After>(std::move(h4)));
    }

    /// Run handler for `Hook` for all of `Mixin`s siblings
    template<typename H,
             typename Mixin,
             typename = std::enable_if_t<HookTag::is<H, typename Mixin::value_type> &&
                                         HookWithValue::is<MixinImpl::hook_t<Mixin, H>>>>
    auto run_hook(Mixin& m, const HookWithValue::arg_type<MixinImpl::hook_t<Mixin, H>>& arg)
    {
      MixinImpl::hook_t<Mixin, H, HookOrder::Before> hook{arg};
      auto h1 = run_all_hooks_impl<H, Mixin, HookOrder::Before>(m, std::move(hook));
      auto h2 = run_all_hooks_impl<H, Mixin, HookOrder::Early>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::Early>(std::move(h1)));
      auto h3 = run_all_hooks_impl<H, Mixin, HookOrder::Middle>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::Middle>(std::move(h2)));
      auto h4 = run_all_hooks_impl<H, Mixin, HookOrder::Late>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::Late>(std::move(h3)));
      auto h5 = run_all_hooks_impl<H, Mixin, HookOrder::After>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::After>(std::move(h4)));
      return h5.value();
    }
  } // namespace detail

} // namespace otto::core::props
