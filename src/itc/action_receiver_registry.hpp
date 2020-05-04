#pragma once

#include "action.hpp"
#include "util/flat_map.hpp"

namespace otto::itc {

  /// ActionChannels are 'sub-busses'. They exist to, for instance, differentiate between two identical engines loaded
  /// into different slots (e.g. Audio Effects or Sampler engines)
  enum struct ActionChannel {
    master,
    ext_send_left,
    ext_send_right,
    ext_send_stereo,
    external,
    arpeggiator,
    instrument,
    instrument_send,
    fx1,
    fx2,
    sequencer,
    sampler1,
    sampler2,
    sampler3,
    sampler4,
    sampler5,
    sampler6,
    sampler7,
    sampler8,
    sampler9,
    sampler1_send,
    sampler2_send,
    sampler3_send,
    sampler4_send,
    sampler5_send,
    sampler6_send,
    sampler7_send,
    sampler8_send,
    sampler9_send,
  };

  template<typename ActionType>
  struct ActionReceiverRegistry;

  /// A registry of action receivers
  template<typename Tag, typename... Args>
  struct ActionReceiverRegistry<Action<Tag, Args...>> {
    using ActionType = Action<Tag, Args...>;

    std::size_t size() const noexcept
    {
      return channels.size();
    }

    /// Add to the registry.
    void add_to(itc::ActionChannel channel, ActionReceiver<ActionType>* rec) noexcept
    {
      channels.insert(channel, {}).first->second.insert(rec);
    }

    /// Removes an ActionReceiver from a single channel
    void remove_from(ActionChannel channel, ActionReceiver<ActionType>* rec) noexcept
    {
      auto&& opt_receivers = channels[channel];
      if (opt_receivers) {
        opt_receivers->erase(rec);
      }
    }

    /// Removes an ActionReceiver from all channels
    void remove_from_all(ActionReceiver<ActionType>* rec) noexcept
    {
      // Note that empty sets are being left. They can be deleted afterwards if needed
      // Since there is a finite set of channels, and erasing the sets is a fairly expensive
      // operation, especially if the set is in the middle of a list, it probably makes 
      // sense to leave them
      for (auto&& channel : channels.values()) {
        channel.erase(rec);
      }
    }

    void call_all(typename ActionType::args_tuple args) noexcept
    {
      for (auto&& channel : channels.values()) {
        for (auto&& actrec : channel) {
          std::apply([&](Args... args) { actrec->action(ActionType(), args...); }, args);  
        }
      }
    }

    void call_for_channel(ActionChannel channel, typename ActionType::args_tuple args) noexcept
    {
      auto&& receivers = channels[channel];
      if (receivers) {
        for (auto&& rec : *receivers) {
          std::apply([&](Args... args) { rec->action(ActionType(), args...); }, args);  
        }
      }
    }

  private:
    util::flat_map<itc::ActionChannel, util::flat_set<ActionReceiver<ActionType>*>> channels;
  };

} // namespace otto::itc
