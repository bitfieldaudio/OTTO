#pragma once
#include <vector>


/// A State-based inter-thread communication library.
///
/// A single `Producer` can send a new `State` object to multiple `Channels`, which in
/// turn pass it on to multiple `Consumers` which receive the state on some `Bus`
///
/// State is intended to be little more than a simple `POD`-style struct, and it is up
/// to the individual consumers to determine which members have actually changed if they
/// require so.
namespace otto::itc {

  /// The concept that state types need to fulfill.
  ///
  /// Currently any type can be a state type, but it might make sense to constrain
  /// it layer
  template<typename State>
  concept AState = true;

  // Forward Declarations

  /// A Channel through which a single Producer can send state to multiple consumers
  template<AState State>
  struct Channel;

  /// Sends state to multiple Consumers through a Channel
  template<AState State>
  struct Producer;

  /// Receives state from a single producer through a Channel
  template<AState State>
  struct Consumer;

  // Declarations

  template<AState State>
  struct Channel {
    using Consumer = Consumer<State>;
    using Producer = Producer<State>;

    Channel() noexcept {}
    Channel(const Channel&) = delete;
    ~Channel() noexcept
    {
      for (auto* c : consumers_) {
        c->channel_ = nullptr;
      }
      if (producer_) producer_->remove_channel(*this);
    }

    const std::vector<Consumer*>& consumers() const noexcept
    {
      return consumers_;
    }

    Producer* producer() const noexcept
    {
      return producer_;
    }

    /// Set the producer for this channel
    ///
    /// Can be `nullptr` to clear the current producer
    void set_producer(Producer* p) noexcept
    {
      producer_ = p;
      if (p) p->channels_.emplace_back(this);
    }

    /// Set the producer for this channel
    void set_producer(Producer& p) noexcept
    {
      set_producer(&p);
    }

  protected:
    friend Producer;
    friend Consumer;

    /// Only called from Consumer constructor
    void add_consumer(Consumer* c)
    {
      consumers_.push_back(c);
    }

  private:
    std::vector<Consumer*> consumers_;
    Producer* producer_ = nullptr;
  };

  template<AState State>
  struct Producer {
    using Channel = Channel<State>;
    Producer(Channel& ch)
    {
      ch.set_producer(this);
    }

    ~Producer() noexcept
    {
      for (auto ch : channels_) {
        ch->set_producer(nullptr);
      }
    }

    /// The channels this producer is currently linked to
    const std::vector<Channel*>& channels() const noexcept
    {
      return channels_;
    }

  protected:
    friend Channel;

    /// Called only from set_producer in Channel
    void add_channel(Channel& ch)
    {
      channels_.push_back(ch);
    }
    /// Called only from Channel destructor
    void remove_channel(Channel& ch)
    {
      std::erase(channels_, &ch);
    }

  private:
    std::vector<Channel*> channels_;
  };

  template<AState State>
  struct Consumer {
    using Channel = Channel<State>;

    Consumer(Channel& ch) : channel_(&ch)
    {
      ch.add_consumer(this);
    }

    ~Consumer() noexcept
    {
      if (channel_) std::erase(channel_->consumers_, this);
    }

    /// The channel this consumer is registered on
    Channel* channel() const noexcept
    {
      return channel_;
    }

  private:
    friend Channel;
    Channel* channel_;
  };

}
