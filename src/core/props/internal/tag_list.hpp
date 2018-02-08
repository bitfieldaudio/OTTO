#pragma once

#include "type_traits.hpp"

namespace otto::core::props {

  /// !!! Warning: `boost::hana` ahead !!!
  ///
  /// This code is used to:
  ///  - create lists of tags
  ///  - append tags required by tags already in the list, to the list
  ///  - sort and uniquify these tag lists, so the type is independent of
  ///    ordering
  ///  - Inherit all the mixin implementations of a tag list.
  ///
  /// Everything here should be kept well documented and internal to this file.
  /// Public interfaces should be exposed outside the namespace, and should use
  /// a standard interface instead of the hana interface.
  namespace black_magic {

    namespace hana = boost::hana;

    /// Sort tags by their name and uniquify the list
    ///
    /// This is a `boost::hana` function that operates on types. Do not use it
    /// in runtime a context
    ///
    /// \requires `TagList == tag_list<...>`
    template<typename TagList>
    constexpr auto sort_tags(TagList const& tl)
    {
      return hana::unique(hana::sort(tl, [](auto tag1, auto tag2) {
        return decltype(+tag1)::type::name < decltype(+tag2)::type::name;
      }));
    }

    /// Add all tags required by tags in TagList. Sort and uniquify
    ///
    /// This is a `boost::hana` function that operates on types. Do not use it
    /// in runtime a context
    ///
    /// \requires `TagList == tag_list<...>`
    template<typename TagList>
    constexpr auto with_required(TagList const& tl)
    {
      return sort_tags(hana::concat(
        tl, hana::flatten(hana::transform(tl, [](auto tag) {
          return MixinTag::required_tags_t<typename decltype(+tag)::type>();
        }))));
    }

    /// Simple type that inherits publicly from all of `SuperClasses...`
    ///
    /// Also uses all operators and constructors
    template<typename... SuperClasses>
    struct inherit_from_all : SuperClasses... {
      using SuperClasses::SuperClasses...;
      using SuperClasses::operator=...;
    };

    /// Get a type that inherits from all types in `typelist`
    ///
    /// This is a `boost::hana` function that operates on types. Do not use it
    /// in runtime a context
    ///
    /// \returns a `boost::hana::type` containing the result type
    template<typename... MixinTypes>
    constexpr auto inherit_from_all_types_impl(
      hana::tuple<MixinTypes...> const& typelist)
    {
      return hana::type_c<
        inherit_from_all<typename std::decay_t<MixinTypes>::type...>>;
    }

    /// Get a type that inherits from all the mixins coresponding to TagList.
    ///
    /// Does not add required mixins.
    ///
    /// This is a `boost::hana` function that operates on types. Do not use it
    /// in runtime a context
    ///
    /// \requires `TagList == tag_list<...>`
    /// \returns a `boost::hana::type` containing the result type
    template<typename ValueType, typename TagList>
    constexpr auto inherit_from_all_mixins_impl(TagList const& tl)
    {
      return inherit_from_all_types_impl(hana::transform(tl, [](auto tag) {
        return hana::type_c<
          MixinTag::mixin_t<typename decltype(+tag)::type, ValueType, TagList>>;
      }));
    }
  } // namespace black_magic

  /// Type trait to see if a tag_list contains a tag.
  template<typename TagList, typename T>
  static constexpr bool contains_tag_v =
    boost::hana::contains(TagList(), boost::hana::type_c<T>);

  /// This type inherits from all mixins matched by `Tags`
  ///
  /// \see inherit_from_all_mixins_impl
  /// \requires `TagList == tag_list<...>`
  template<typename ValueType, typename TagList>
  using inherits_from_mixins_t =
    typename decltype(black_magic::inherit_from_all_mixins_impl<ValueType>(
      std::declval<TagList>()))::type;

  /// Make a tag_list type with all `Tags` and their requirements
  template<typename... Tags>
  using make_tag_list_t = decltype(black_magic::with_required(
    boost::hana::make_tuple(boost::hana::type_c<Tags>...)));


  template<typename Tag, typename... Args>
  struct TaggedTuple {
    using tag_type = Tag;
    std::tuple<Args...> args;

    static constexpr bool _this_is_a_mixin_initializer_type_ = true;
  };

  template<typename Tag, typename... Args>
  auto make_initializer(Args&&... args) {
    return TaggedTuple<Tag, Args...>{std::forward_as_tuple(std::forward<Args>(args)...)};
  }

  template<typename Initializer, typename = void>
  struct is_initializer : std::false_type {};

  template<typename Initializer>
  struct is_initializer<
    Initializer,
    std::void_t<decltype(Initializer::_this_is_a_mixin_initializer_type_),
                typename Initializer::tag_type>> {
    constexpr static const bool value =
      Initializer::_this_is_a_mixin_initializer_type_;
  };

  template<typename Initializer>
  constexpr static bool is_initializer_v = is_initializer<Initializer>::value;

} // namespace otto::core::props
