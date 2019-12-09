#pragma once

#include "action.hpp"
#include "action_queue.hpp"
#include "action_sender.hpp"
#include "prop.hpp"

namespace otto::itc {
  /// A helper type to declare Prop and action types.
  /// 
  /// This is useful especially when the Screen/audio is not templated,
  /// but the props are, or in general, whenever the Screen/Audio does not
  /// have access to the definition of the props. This type can then be used
  /// to declare the tag, prop and action types in a single place.
  /// 
  /// ## Usage
  /// 
  /// ```cpp
  /// using FilterFreq = itc::PropTypes<struct filter_freq_tag, float>;
  /// 
  /// struct Props {
  ///   Sender sender;
  ///   FilterFreq::Prop<Sender, props::wrap> filter_freq = {sender, 0};
  /// };
  /// 
  /// struct Screen {
  ///   void action(FilterFreq::action, float) noexcept;
  /// };
  /// ```
  template<typename Tag, typename ValueType>
  struct PropTypes {
    using tag = Tag;
    using action = itc::Action<Tag, ValueType>;
    template<typename Sender, typename... Mixins>
    using Prop = typename Sender::template Prop<Tag, ValueType, Mixins...>;
  };
} // namespace otto::itc
