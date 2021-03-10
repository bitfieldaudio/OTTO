#pragma once

#include <memory>
#include <vector>

#include <boost/container/flat_map.hpp>

#include "lib/util/concepts.hpp"
#include "lib/util/name_of.hpp"
#include "lib/util/serialization.hpp"

#include "event.hpp"
#include "state.hpp"

namespace otto::itc {

  namespace detail {
    struct TypedChannelBase : util::ISerializable {
      virtual ~TypedChannelBase() = default;
    };
  } // namespace detail

  template<AnEvent Event>
  struct TypedChannel : detail::TypedChannelBase {
    TypedChannel() noexcept = default;

    // Non-copyable
    TypedChannel(const TypedChannel&) = delete;
    TypedChannel& operator=(const TypedChannel&) = delete;

    ~TypedChannel() noexcept override
    {
      for (auto* r : receivers_) {
        r->channel_ = nullptr;
      }
      if (sender_) sender_->internal_remove_channel(*this);
    }

    const std::vector<Receiver<Event>*>& receivers() const noexcept
    {
      return receivers_;
    }

    Sender<Event>* sender() const noexcept
    {
      return sender_;
    }

    /// Set the sender for this channel
    ///
    /// Can be `nullptr` to clear the current sender
    void set_sender(Sender<Event>* p) noexcept
    {
      sender_ = p;
      if (p) p->channels_.emplace_back(this);
    }

    /// Set the sender for this channel
    void set_sender(Sender<Event>& p) noexcept
    {
      set_sender(&p);
    }

    void serialize_into(json::value& json) const final
    {
      if constexpr (AStateEvent<Event>) {
        if constexpr (util::ASerializable<typename Event::State>) {
          // TODO Access a copy of the state in another way
          if (sender_ == nullptr) return;
          util::serialize_into(json, static_cast<Producer<typename Event::State>*>(sender_)->state());
        }
      }
    }

    void deserialize_from(const json::value& json) final
    {
      if constexpr (AStateEvent<Event>) {
        if constexpr (util::ASerializable<typename Event::State>) {
          // TODO Access a copy of the state in another way
          if (sender_ == nullptr) return;
          auto* p = static_cast<Producer<typename Event::State>*>(sender_);
          util::deserialize_from(json, p->state());
          p->commit();
        }
      }
    }

  private:
    friend Sender<Event>;
    friend Receiver<Event>;

    /// Only called from Receiver constructor
    void internal_add_receiver(Receiver<Event>* c)
    {
      receivers_.push_back(c);
    }

    void internal_send(const Event& state)
    {
      for (auto* receiver : receivers_) receiver->internal_send(state);
    }

    std::vector<Receiver<Event>*> receivers_;
    Sender<Event>* sender_ = nullptr;
  };

  /// A (nested) group of channels, where channels for any state type can be created and accessed
  struct ChannelGroup : util::ISerializable {
    ChannelGroup() = default;
    ~ChannelGroup() = default;

    ChannelGroup(ChannelGroup&) = delete;
    ChannelGroup& operator=(ChannelGroup&) = delete;

    /// Creates or finds the channel of the given type
    template<AnEvent Event>
    TypedChannel<Event>& get()
    {
      auto found = channels_.find(util::qualified_name_of<Event>);
      if (found == channels_.end()) {
        auto [iter, inserted] =
          channels_.emplace(util::qualified_name_of<Event>, std::make_unique<TypedChannel<Event>>());
        found = iter;
      }
      // Should this be a dynamic cast? probably not, since we know the type is right
      return static_cast<TypedChannel<Event>&>(*found->second);
    }

    /// Access or create a nested channel group by name
    ChannelGroup& operator[](std::string_view sv)
    {
      // Apparently transparent keys don't work in gcc for string_view/string
      // TODO: Look into that ^
      auto found = nested_.find(std::string(sv));
      if (found == nested_.end()) {
        auto [iter, inserted] = nested_.emplace(sv, std::make_unique<ChannelGroup>());
        found = iter;
      }
      return *found->second;
    }

    void serialize_into(json::value& json) const final
    {
      using namespace std::literals;
      for (const auto& [k, v] : nested_) {
        util::serialize_into(json[k], *v);
      }
      for (const auto& [k, v] : channels_) {
        util::serialize_into(json["type:"s + k.c_str()], *v);
      }
    }

    void deserialize_from(const json::value& json) final
    {
      using namespace std::literals;
      for (const auto& [k, v] : nested_) {
        util::deserialize_from_member(json, k, *v);
      }
      for (const auto& [k, v] : channels_) {
        util::deserialize_from_member(json, "type:"s + k.c_str(), *v);
      }
    }

  private:
    boost::container::flat_map<std::string, std::unique_ptr<ChannelGroup>> nested_;
    boost::container::flat_map<util::string_ref, std::unique_ptr<detail::TypedChannelBase>> channels_;
  };

} // namespace otto::itc
