#pragma once

#include <range/v3/utility/concepts.hpp>
#include <util/type_traits.hpp>

#include <boost/hana.hpp>

namespace otto::core::props {

  namespace cpts = ranges::concepts;

  /// Type used to list tags
  template<typename... Tags>
  using tag_list = boost::hana::tuple<boost::hana::type<Tags>...>;

  struct NonVoid {
    template<typename T>
    auto requires_(T&& t) -> decltype( //
      cpts::valid_expr(                //
        cpts::is_false(std::is_void<T>())));
  };

  struct MixinValue : cpts::refines<NonVoid> {};

  struct Hook {

    template<typename H>
    using value_type = typename H::value_type;

    template<typename T>
    auto requires_(T&& t) -> decltype( //
      cpts::valid_expr(                //
        cpts::model_of<MixinValue, typename T::value_type>()));
  };

  struct HookWithValue : cpts::refines<Hook> {

    template<typename H>
    using value_type = typename H::value_type;

    template<typename H>
    using arg_type = typename H::arg_type;

    template<typename T>
    auto requires_(T&& t) -> decltype( //
      cpts::valid_expr(
        cpts::model_of<MixinValue, value_type<T>>(),
        cpts::model_of<NonVoid, arg_type<T>>(),
        cpts::has_type<arg_type<T>&>(t.value()),
        cpts::model_of<cpts::ConvertibleTo, T, arg_type<T>&>(),
        cpts::model_of<cpts::Constructible, T, const arg_type<T>&>()));
  };

  struct HookTag {

    /// Get the hook type from a tag and a value type
    template<typename HT, typename VT>
    using impl_t = typename HT::template type<VT>;

    template<typename T, typename ValueType>
    auto requires_(T&& t) -> decltype( //
      cpts::valid_expr(                //
        cpts::model_of<Hook, typename T::template type<ValueType>>()));
  };

  struct MixinImpl {
    template<typename T>
    auto requires_(T&& t) -> decltype(                       //
      cpts::valid_expr(                                      //
        cpts::model_of<NonVoid, typename T::value_type>(),   //
        cpts::model_of<NonVoid, typename T::tag_list_t>(),   //
        cpts::model_of<NonVoid, typename T::hooks>(),        //
        cpts::model_of<NonVoid, typename T::property_type>() //
        ));                                                  //

    // HOOKS //

    /// Get the hook type from a tag and a Mixin type
    template<typename Mixin,
             typename HT,
             CONCEPT_REQUIRES_(
               cpts::models<MixinImpl, Mixin>() &&
               cpts::models<HookTag, HT, typename Mixin::value_type>())>
    using hook_t = HookTag::impl_t<HT, typename Mixin::value_type>;

    /// Check if Mixin has a handler for Hook
    template<typename Mixin, typename HT, typename = void>
    struct has_handler : std::false_type {
      CONCEPT_ASSERT(cpts::models<MixinImpl, Mixin>() &&
                     cpts::models<HookTag, HT, typename Mixin::value_type>());
    };

    /// Check if Mixin has a handler for Hook
    template<typename Mixin, typename HT>
    struct has_handler<Mixin,
                       HT,
                       std::void_t<decltype(std::declval<Mixin>().on_hook(
                           std::declval<hook_t<Mixin, HT>&>()))>>
      : std::true_type {
      CONCEPT_ASSERT(cpts::models<MixinImpl, Mixin>() &&
                     cpts::models<HookTag, HT, typename Mixin::value_type>());
    };

    /// Check if Mixin has a handler for Hook
    template<typename Mixin, typename Hook>
    constexpr static const bool has_handler_v = has_handler<Mixin, Hook>::value;
  };

  /// Concept for a Tag used to identify a mixin
  struct MixinTag {
    template<typename Tag>
    auto requires_(Tag&& t) -> decltype( //
      cpts::valid_expr(                  //
        cpts::has_type<boost::hana::string>(Tag::name)));

    // Required Tags impl //

  private:
    template<typename Tag, typename = void>
    struct required_tags_impl {
      using type = tag_list<>;
    };

    template<typename Tag>
    struct required_tags_impl<Tag, std::void_t<typename Tag::required_tags>> {
      using type = typename Tag::required_tags;
    };

  public:

    /// Get all required tags for `Tag`
    template<typename Tag>
    using required_tags_t = typename required_tags_impl<Tag>::type;

    /// Get mixin type for type `T` and tag `Tag`
    template<typename Tag, typename T, typename TagList>
    using mixin_t = typename Tag::template implementation_type<T, TagList>;

  };

  namespace detail {

    /// Get the hooks struct for a tag
    template<typename Tag, typename = void>
    struct tag_hooks {
      struct type {};
    };

    /// Get the hooks struct for a tag
    template<typename Tag>
    struct tag_hooks<Tag, std::void_t<typename Tag::hooks>> {
      using type = typename Tag::hooks;
    };

    /// Get the hooks struct for a tag
    template<typename Tag>
    using tag_hooks_t = typename tag_hooks<Tag>::type;

    /// Run `Mixin`'s handler for `Hook` if it has one
    template<typename HT,
             typename Mixin,
             CONCEPT_REQUIRES_(
               cpts::models<HookTag, HT, typename Mixin::value_type>() &&
               cpts::models<MixinImpl, Mixin>())>
    void run_hook_if_handler(Mixin& m, MixinImpl::hook_t<Mixin, HT>& h)
    {
      if constexpr (MixinImpl::has_handler_v<Mixin, HT>) {
        m.on_hook(h);
      }
    }

    /// Run handler for `Hook` for all of `Mixin`s siblings
    template<typename H,
             typename Mixin,
             CONCEPT_REQUIRES_(
               cpts::models<HookTag, H, typename Mixin::value_type>() &&
               !cpts::models<HookWithValue, MixinImpl::hook_t<Mixin, H>>() &&
               cpts::models<MixinImpl, Mixin>())>
    void run_hook(Mixin& m)
    {
      MixinImpl::hook_t<Mixin, H> hook {};
      boost::hana::for_each(m.tag_list, [&hook, &m](const auto& mtype) {
          run_hook_if_handler<H>(hook,
                            m.template as<typename decltype(+mtype)::type>());
      });
    }

    /// Run handler for `Hook` for all of `Mixin`s siblings
    template<typename H,
             typename Mixin,
             CONCEPT_REQUIRES_(
               cpts::models<HookTag, H, typename Mixin::value_type>() &&
               cpts::models<HookWithValue, MixinImpl::hook_t<Mixin, H>>() &&
               cpts::models<MixinImpl, Mixin>())>
    auto run_hook(
      Mixin& m,
      const HookWithValue::arg_type<MixinImpl::hook_t<Mixin, H>>& arg)
    {
      MixinImpl::hook_t<Mixin, H> hook {arg};
      boost::hana::for_each(m.tag_list, [&hook, &m](const auto& mtype) {
          run_hook_if_handler<H>(m.template as<typename decltype(+mtype)::type>(), hook);
      });
      return hook.value();
    }
  } // namespace detail

}
