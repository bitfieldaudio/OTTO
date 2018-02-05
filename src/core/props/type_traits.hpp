#pragma once

#include <range/v3/utility/concepts.hpp>
#include <boost/hana.hpp>

#include "util/type_traits.hpp"

#include "base.hpp"

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

    // Type-erased Interface //
  private:
    template<typename Tag, typename = void>
    struct leaf_interface_impl {
      using type = void;
    };

    template<typename Tag>
    struct leaf_interface_impl<Tag, std::void_t<typename Tag::leaf_interface>> {
      using type = typename Tag::leaf_interface;
    };

  public:
    /// Get the type-erased leaf interface type for `Tag`
    ///
    /// The interface type is a non-templated type which provides functionality
    /// that can be used in a type-erased context. For example, the
    /// `serializable` mixin has a `JsonClient` with loader and saver functions
    /// to use independently from the specific property.
    ///
    /// If a mixin provides a type-erased interface, it should have a
    /// `interface_type& interface()` member function, which returns an instance
    /// of this type.
    ///
    /// If no interface type is provided, this is void.
    template<typename Tag>
    using leaf_interface = typename leaf_interface_impl<Tag>::type;

    /// Check if `Tag` has a type-erased interface
    ///
    /// The interface type is a non-templated type which provides functionality
    /// that can be used in a type-erased context. For example, the
    /// `serializable` mixin has a `JsonClient` with loader and saver functions
    /// to use independently from the specific property.
    ///
    /// If a mixin provides a type-erased interface, it should have a
    /// `interface_type& interface()` member function, which returns an instance
    /// of this type.
    ///
    /// If no interface type is provided, this is void.
    template<typename Tag>
    constexpr static bool has_leaf_interface = !std::is_void_v<leaf_interface<Tag>>;

  private:
    template<typename Tag, typename = void>
    struct branch_interface_impl {
      using type = BaseBranchInterface<Tag>;
    };

    template<typename Tag>
    struct branch_interface_impl<Tag, std::void_t<typename Tag::branch_interface>> {
      using type = typename Tag::branch_interface;
    };

  public:

    /// The type-erased interface for a branch of `Tag`
    ///
    /// By default, this has a vector of pointers to child interfaces and
    /// pointers to other common branch data, such as the name. These can all be
    /// accessed through accessor functions.
    template<typename Tag>
    using branch_interface = typename branch_interface_impl<Tag>::type;
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

  /// A pointer to either a branch or a leaf interface for mixin `Tag`
  ///
  /// Provides functions for checking type and accessing the value.
  template<typename Tag>
  struct BranchOrLeafPtr; // Forward declaration

  /// The base class of the type-erased interface for a branch of `Tag`
  ///
  /// Has a vector of pointers to child interfaces and pointers to other
  /// common branch data, such as the name. These can all be accessed through
  /// accessor functions.
  template<typename Tag>
  struct BaseBranchInterface {
    // Cannot be checked since this is instantiated in the declaration of the tag
    // CONCEPT_ASSERT(cpts::models<MixinTag, Tag>() &&
    //                MixinTag::has_leaf_interface<Tag>);

    using storage_type = std::vector<BranchOrLeafPtr<Tag>>;

    storage_type& children() {
      return storage_;
    }

    void push_back(BranchOrLeafPtr<Tag> ptr) {
      storage_.push_back(ptr);
    }

    const std::string& name() {
      static std::string nm = "Test";
      return nm;
    };

  private:
    storage_type storage_;
  };

  /// A pointer to either a branch or a leaf interface for mixin `Tag`
  ///
  /// Provides functions for checking type and accessing the value.
  template<typename Tag>
  struct BranchOrLeafPtr {
    // CONCEPT_ASSERT(cpts::models<MixinTag, Tag>() &&
    //                MixinTag::has_leaf_interface<Tag>);

    using branch = MixinTag::branch_interface<Tag>;
    using leaf = MixinTag::leaf_interface<Tag>;

    BranchOrLeafPtr(branch& b) : storage_(&b) {}
    BranchOrLeafPtr(leaf& l) : storage_(&l) {}

    BranchOrLeafPtr(branch* b) : storage_(b) {}
    BranchOrLeafPtr(leaf* l) : storage_(l) {}

    bool is_branch() const noexcept
    {
      return mpark::holds_alternative<0>(storage_);
    }

    bool is_leaf() const noexcept
    {
      return mpark::holds_alternative<1>(storage_);
    }

    branch& get_branch() const
    {
      return *mpark::get<0>(storage_);
    }

    leaf& get_leaf() const
    {
      return *mpark::get<1>(storage_);
    }

  private:
    mpark::variant<branch*, leaf*> storage_;
  };

}
