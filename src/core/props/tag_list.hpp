#pragma once

#include <boost/hana.hpp>

namespace otto::core::props {

  /// Get mixin type for type `T` and tag `Tag`
  template<typename Tag, typename T, typename TagList>
  using tag_mixin_t = typename Tag::template implementation_type<T, TagList>;

  /// Get all required tags for `Tag`
  template<typename Tag>
  using required_tags_t = typename Tag::required_tags;

  /// Type used to list tags
  template<typename... Tags>
  using tag_list = boost::hana::tuple<boost::hana::type<Tags>...>;

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
      return sort_tags(
        hana::concat(tl, hana::flatten(hana::transform(tl, [](auto tag) {
                       return required_tags_t<typename decltype(+tag)::type>();
                     }))));
    }

    /// Simple type that inherits publicly from all of `SuperClasses...`
    template<typename... SuperClasses>
    struct inherit_from_all : SuperClasses... {};

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
          tag_mixin_t<typename decltype(+tag)::type, ValueType, TagList>>;
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

} // namespace otto::core::props
