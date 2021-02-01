#pragma once

#include <memory>
#include <vector>

#include <boost/container/flat_map.hpp>

#include "lib/util/concepts.hpp"
#include "lib/util/name_of.hpp"
#include "lib/util/serialization.hpp"

#include "state.hpp"

namespace otto::itc {

  namespace detail {
    struct ChannelBase : util::ISerializable {
      virtual ~ChannelBase() = default;
    };
  } // namespace detail

  template<AState State>
  struct TypedChannel : detail::ChannelBase {
    TypedChannel() noexcept = default;

    // Non-copyable
    TypedChannel(const TypedChannel&) = delete;
    TypedChannel& operator=(const TypedChannel&) = delete;

    ~TypedChannel() noexcept override
    {
      for (auto* c : consumers_) {
        c->channel_ = nullptr;
      }
      if (producer_) producer_->internal_remove_channel(*this);
    }

    const std::vector<Consumer<State>*>& consumers() const noexcept
    {
      return consumers_;
    }

    Producer<State>* producer() const noexcept
    {
      return producer_;
    }

    /// Set the producer for this channel
    ///
    /// Can be `nullptr` to clear the current producer
    void set_producer(Producer<State>* p) noexcept
    {
      producer_ = p;
      if (p) p->channels_.emplace_back(this);
    }

    /// Set the producer for this channel
    void set_producer(Producer<State>& p) noexcept
    {
      set_producer(&p);
    }

    void serialize_into(toml::value& toml) const final
    {
      if constexpr (util::ASerializable<State>) {
        // TODO Access a copy of the state in another way
        if (producer_ == nullptr) return;
        util::serialize_into(toml, producer_->state());
      }
    }

    void deserialize_from(const toml::value& toml) final
    {
      if constexpr (util::ASerializable<State>) {
        // TODO Access a copy of the state in another way
        if (producer_ == nullptr) return;
        util::deserialize_from(toml, producer_->state());
        producer_->commit();
      }
    }

  private:
    friend Producer<State>;
    friend Consumer<State>;

    /// Only called from Consumer constructor
    void internal_add_consumer(Consumer<State>* c)
    {
      consumers_.push_back(c);
    }

    void internal_commit(const State& state)
    {
      for (auto* cons : consumers_) cons->internal_commit(state);
    }

    std::vector<Consumer<State>*> consumers_;
    Producer<State>* producer_ = nullptr;
  };

  /// A (nested) group of channels, where channels for any state type can be created and accessed
  struct ChannelGroup : util::ISerializable {
    ChannelGroup() = default;
    ~ChannelGroup() = default;

    ChannelGroup(ChannelGroup&) = delete;
    ChannelGroup& operator=(ChannelGroup&) = delete;

    /// Creates or finds the channel of the given type
    template<AState State>
    TypedChannel<State>& get()
    {
      auto found = channels_.find(util::qualified_name_of<State>);
      if (found == channels_.end()) {
        auto [iter, inserted] =
          channels_.emplace(util::qualified_name_of<State>, std::make_unique<TypedChannel<State>>());
        found = iter;
      }
      // Should this be a dynamic cast? probably not, since we know the type is right
      return static_cast<TypedChannel<State>&>(*found->second);
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

    void serialize_into(toml::value& toml) const final
    {
      using namespace std::literals;
      toml::ensure_table(toml);
      for (const auto& [k, v] : nested_) {
        util::serialize_into(toml[k], *v);
      }
      for (const auto& [k, v] : channels_) {
        util::serialize_into(toml["type:"s + k.c_str()], *v);
      }
    }

    void deserialize_from(const toml::value& toml) final
    {
      using namespace std::literals;
      for (const auto& [k, v] : nested_) {
        util::deserialize_from(toml::find(toml, k), *v);
      }
      for (const auto& [k, v] : channels_) {
        util::deserialize_from(toml::find(toml, "type:"s + k.c_str()), *v);
      }
    }

  private:
    boost::container::flat_map<std::string, std::unique_ptr<ChannelGroup>> nested_;
    boost::container::flat_map<util::string_ref, std::unique_ptr<detail::ChannelBase>> channels_;
  };

} // namespace otto::itc
