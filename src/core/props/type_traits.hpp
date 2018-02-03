#pragma once

#include <range/v3/utility/concepts.hpp>
#include <util/type_traits.hpp>

#include <boost/hana.hpp>

namespace otto::core::props {

  /// Order of hook handlers.
  ///
  /// This is the second template argument to hook implementations, and is used
  /// to sort handlers.
  enum struct HookOrder {
    /// Should only read hook values
    Before,
    /// Change values early
    Early,
    /// Change values in the middle. Default
    Middle,
    /// Change values late
    Late,
    /// Should only read hook values
    After,
  };

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

  /// A hook implementation concept
  struct Hook {
    template<typename H>
    using value_type = typename H::value_type;

    template<typename T>
    auto requires_(T&& t) -> decltype( //
      cpts::valid_expr(                //
        cpts::model_of<MixinValue, typename T::value_type>()));
  };

  /// Concept of a Hook with a value
  struct HookWithValue : cpts::refines<Hook> {

    /// The value type of the property this belongs to
    template<typename H>
    using value_type = typename H::value_type;

    /// The argument type of the hook
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

  /// Concept of a hook tag type
  struct HookTag {

    /// Get the hook type from a tag and a value type
    template<typename HT, typename VT, HookOrder HO = HookOrder::Middle>
    using impl_t = typename HT::template type<VT, HO>;

    template<typename T, typename ValueType, HookOrder HO = HookOrder::Middle>
    auto requires_(T&& t) -> decltype( //
      cpts::valid_expr(                //
        cpts::model_of<Hook, typename T::template type<ValueType, HO>>()));
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
             HookOrder HO = HookOrder::Middle,
             CONCEPT_REQUIRES_(
               cpts::models<MixinImpl, Mixin>() &&
               cpts::models<HookTag, HT, typename Mixin::value_type>())>
    using hook_t = HookTag::impl_t<HT, typename Mixin::value_type, HO>;

    /// Check if Mixin has a handler for Hook
    template<typename Mixin, typename HT, HookOrder HO, typename = void>
    struct has_handler : std::false_type {
      CONCEPT_ASSERT(cpts::models<MixinImpl, Mixin>() &&
                     cpts::models<HookTag, HT, typename Mixin::value_type>());
    };

    /// Check if Mixin has a handler for Hook
    template<typename Mixin, typename HT, HookOrder HO>
    struct has_handler<Mixin,
                       HT,
                       HO,
                       std::void_t<decltype(std::declval<Mixin>().on_hook(
                           std::declval<hook_t<Mixin, HT, HO>&>()))>>
      : std::true_type {
      CONCEPT_ASSERT(cpts::models<MixinImpl, Mixin>() &&
                     cpts::models<HookTag, HT, typename Mixin::value_type>());
    };

    /// Check if Mixin has a handler for Hook
    template<typename Mixin, typename Hook, HookOrder HO>
    constexpr static const bool has_handler_v = has_handler<Mixin, Hook, HO>::value;
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

    // Shared Interface //
  private:
    template<typename Tag, typename = void>
    struct interface_type_impl {
      using type = void;
    };

    template<typename Tag>
    struct interface_type_impl<Tag, std::void_t<typename Tag::interface_type>> {
      using type = typename Tag::interface_type;
    };

  public:
    /// Get the shared interface type for `Tag`
    ///
    /// the interface type is a non-templated type which provides functionality
    /// that can be used polymorphically. For example, the `serializable` mixin
    /// has a `JsonClient` with loader and saver functions to use independently
    /// from the specific property.
    ///
    /// If a mixin provides a shared interface, it should have a `interface_type
    /// interface()` or `interface_type& interface()` member function, which
    /// returns an instance of this type.
    ///
    /// If no interface type is provided, this is void.
    template<typename Tag>
    using interface_type = typename interface_type_impl<Tag>::type;

    /// Check if `Tag` has a shared interface 
    ///
    /// the interface type is a non-templated type which provides functionality
    /// that can be used polymorphically. For example, the `serializable` mixin
    /// has a `JsonClient` with loader and saver functions to use independently
    /// from the specific property.
    ///
    /// If a mixin provides a shared interface, it should have a `interface_type
    /// interface()` or `interface_type& interface()` member function, which
    /// returns an instance of this type.
    ///
    /// If no interface type is provided, this is void.
    template<typename Tag>
    constexpr static bool has_interface = !std::is_void_v<interface_type<Tag>>;
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
             HookOrder HO,
             typename Mixin,
             CONCEPT_REQUIRES_(
               cpts::models<HookTag, HT, typename Mixin::value_type>() &&
               cpts::models<MixinImpl, Mixin>())>
    void run_hook_if_handler(Mixin& m, MixinImpl::hook_t<Mixin, HT, HO>& h)
    {
      if constexpr (MixinImpl::has_handler_v<Mixin, HT, HO>) {
        m.on_hook(h);
      }
    }

    template<typename H,
             typename Mixin,
             HookOrder HO,
             CONCEPT_REQUIRES_(
               cpts::models<HookTag, H, typename Mixin::value_type>() &&
               cpts::models<MixinImpl, Mixin>())>
    auto run_all_hooks_impl(Mixin& m, MixinImpl::hook_t<Mixin, H, HO>&& hook) {
      boost::hana::for_each(m.tag_list, [&hook, &m](const auto& mtype) {
          run_hook_if_handler<H, HO>(m.template as<typename decltype(+mtype)::type>(), hook);
      });
      return hook;
    };

      /// Run handler for `Hook` for all of `Mixin`s siblings
      template<typename H,
               typename Mixin,
               CONCEPT_REQUIRES_(
                 cpts::models<HookTag, H, typename Mixin::value_type>() &&
                 !cpts::models<HookWithValue, MixinImpl::hook_t<Mixin, H>>() &&
                 cpts::models<MixinImpl, Mixin>())>
      void run_hook(Mixin& m)
    {
      MixinImpl::hook_t<Mixin, H, HookOrder::Before> hook {};
      auto h1 =
        run_all_hooks_impl<H, Mixin, HookOrder::Before>(m, std::move(hook));
      auto h2 = run_all_hooks_impl<H, Mixin, HookOrder::Early>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::Early>(std::move(h1)));
      auto h3 = run_all_hooks_impl<H, Mixin, HookOrder::Middle>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::Middle>(std::move(h2)));
      auto h4 = run_all_hooks_impl<H, Mixin, HookOrder::Late>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::Late>(std::move(h3)));
      auto h5 = run_all_hooks_impl<H, Mixin, HookOrder::After>(
        m, MixinImpl::hook_t<Mixin, H, HookOrder::After>(std::move(h4)));
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
      MixinImpl::hook_t<Mixin, H, HookOrder::Before> hook {arg};
      auto h1 =
        run_all_hooks_impl<H, Mixin, HookOrder::Before>(m, std::move(hook));
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

}
