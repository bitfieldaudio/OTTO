#pragma once

#include <boost/container/flat_map.hpp>
#include <memory>
#include <typeindex>
#include <vector>

#include "lib/util/concepts.hpp"

#include "state.hpp"

namespace otto::itc {

  struct ChannelBase {
    virtual ~ChannelBase() = default;
  };

  template<AState State>
  struct Channel : ChannelBase {
    Channel() noexcept {}
    Channel(const Channel&) = delete;
    ~Channel() noexcept
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

  protected:
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
  struct ChannelGroup {
    /// Creates or finds the channel of the given type
    template<AState State>
    Channel<State>& get()
    {
      auto found = channels_.find(std::type_index(typeid(State)));
      if (found == channels_.end()) {
        auto [iter, inserted] = channels_.emplace(typeid(State), std::make_unique<Channel<State>>());
        found = iter;
      }
      // Should this be a dynamic cast?
      return static_cast<Channel<State>&>(*found->second);
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

  private:
    boost::container::flat_map<std::string, std::unique_ptr<ChannelGroup>> nested_;
    boost::container::flat_map<std::type_index, std::unique_ptr<ChannelBase>> channels_;
  };

} // namespace otto::itc
