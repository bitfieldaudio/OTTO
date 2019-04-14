#include "clock_manager.hpp"

#include "util/type_traits.hpp"

namespace otto::services {

  // ClockManager //

  using Client = ClockManager::Client;
  using Source = ClockManager::Source;
  using Time = ClockManager::Time;

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

  void Client::stop()
  {
    _cm.stop();
  }

  void Client::set_bpm()
  {
    _cm.set_bpm();
  }

  void Client::set_current(Time time)
  {
    _cm.set_current(time);
  }

  ClockManager& Client::clock_manager() noexcept
  {
    return _cm;
  }

  // DefaultClockManager //

  struct DefaultClockManager : ClockManager {
    Time current_time() override;
    bool running() override;

  protected:
    void start(Source) override;
    void stop() override;
    void set_bpm() override;
    void set_current(Time) override;
  };

  // ClockManager::create_default //

  std::unique_ptr<ClockManager> ClockManager::create_default()
  {
    return std::make_unique<DefaultClockManager>();
  }

  // DefaultClockManager implementation //

  Time DefaultClockManager::current_time()
  {
    return Time{0};
  }
  bool DefaultClockManager::running()
  {
    return false;
  }

  void DefaultClockManager::start(Source) {}
  void DefaultClockManager::stop() {}
  void DefaultClockManager::set_bpm() {}
  void DefaultClockManager::set_current(Time) {}

} // namespace otto::services
