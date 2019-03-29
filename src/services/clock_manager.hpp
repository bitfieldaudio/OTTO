#pragma once

#include <array>
#include <memory>
#include <tl/optional.hpp>

#include "core/service.hpp"

namespace otto::services {

  /// The service managing the clock
  ///
  /// The clock can be started or stopped by an internal or external source,
  /// and should be used by the sequencer, the looper, and arpeggiators.
  struct ClockManager : core::Service {
    using Time = float;

    /// The source currently controling the clock.
    enum struct Source { internal, midi, sync };

    /// Get the current time
    virtual Time current() = 0;
    /// Whether the clock is running
    virtual bool running() = 0;

    /// A Client managing the clock.
    ///
    /// The client is an interface to start, stop and sync the clock.
    struct Client;

    /// Request a client to manage the clock.
    ///
    /// Multiple clients can exist, but only one for each source type.
    ///
    /// @return tl::nullopt if a client for the specified source has already been requested.
    /// Otherwise, a new client.
    tl::optional<Client> request_client(Source s);

    /// The source that last started the clock.
    Source active_source() const noexcept;

    /// Create an instance of the default clock manager
    static std::unique_ptr<ClockManager> create_default();

  protected:
    /// Start the clock, implementation
    ///
    /// Called by @ref Client::start
    virtual void start(Source) = 0;

    /// Stop the clock, implementation
    ///
    /// Called by @ref Client::start
    virtual void stop() = 0;

    std::array<bool, 3> _client_exists;
    Source _active_source = Source::internal;
  };

  struct ClockManager::Client {
    /// Start the clock, and set the value of @ref ClockManager::source()
    void start();

    /// Stop the clock
    void stop();

    /// Set the bpm
    void set_bpm();

    /// Set current time
    void set_current(Time);

    /// The clock manager this client is attached to.
    ClockManager& clock_manager() noexcept;

  private:
    friend ClockManager;

    /// Private constructor so it can only be constructed from @ref ClockManager::request_client
    Client(ClockManager& cm, Source source) : _cm(cm), _source(source) {}

    ClockManager& _cm;
    Source _source;
  };


} // namespace otto::services
