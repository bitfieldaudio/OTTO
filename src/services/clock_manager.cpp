#include "clock_manager.hpp"

#include "util/type_traits.hpp"

namespace otto::services {

  // ClockManager //

  using Client = ClockManager::Client;
  using Source = ClockManager::Source;

  tl::optional<Client> ClockManager::request_client(Source s)
  {
    return _client_exists[util::underlying(s)] ? tl::nullopt : tl::make_optional(Client(*this, s));
  }

  Source ClockManager::active_source() const noexcept
  {
    return _active_source;
  }

  // ClockManager::Client //

  void Client::start()
  {
    _cm._active_source = _source;
    _cm.start(_source);
  }

  /// Stop the clock
  void Client::stop()
  {
    _cm.stop();
  }

  ClockManager& Client::clock_manager() noexcept
  {
    return _cm;
  }

} // namespace otto::services
