#include "navigator.hpp"

namespace otto {

  void Navigator::navigate_to(ScreenWithHandlerPtr screen)
  {
    prev_screen_ = current_screen_;
    current_screen_ = screen;
  }

  bool Navigator::navigate_back()
  {
    if (prev_screen_ == nullptr) return false;
    current_screen_ = prev_screen_;
    prev_screen_ = nullptr;
    return true;
  }

  void Navigator::draw(skia::Canvas& ctx) noexcept
  {
    if (const auto swh = current_screen_; swh != nullptr) {
      swh.screen->draw(ctx);
    }
  }

  void Navigator::handle(EncoderEvent e) noexcept
  {
    if (const auto swh = current_screen_; swh != nullptr) {
      swh.handler->handle(e);
    }
  }

  void Navigator::handle(KeyRelease e) noexcept
  {
    if (const auto swh = current_screen_; swh != nullptr) {
      swh.handler->handle(e);
    }
  }

  void Navigator::handle(KeyPress e) noexcept
  {
    if (const auto swh = current_screen_; swh != nullptr) {
      swh.handler->handle(e);
    }
  }

  ScreenWithHandlerPtr Navigator::current_screen() noexcept
  {
    return current_screen_;
  }

  // NAV KEYMAP

  NavKeyMap::NavKeyMap(util::any_ptr<Navigator> n, chrono::duration timeout)
    : nav_(std::move(n)), momentary_timeout_(timeout)
  {}

  Navigator& NavKeyMap::nav()
  {
    return *nav_;
  }

  void NavKeyMap::bind_nav_key(Key key, ScreenWithHandlerPtr scrn)
  {
    binds_[key] = scrn;
  }

  void NavKeyMap::handle(KeyPress e) noexcept
  {
    auto bind = binds_[e.key];
    if (bind != nullptr) {
      last_nav_time_ = e.timestamp;
      nav().navigate_to(bind);
    } else {
      nav().handle(e);
    }
  }

  void NavKeyMap::handle(KeyRelease e) noexcept
  {
    auto bind = binds_[e.key];
    if (bind != nullptr) {
      // NOLINTNEXTLINE
      if (bind == nav().current_screen() && (e.timestamp - last_nav_time_) > momentary_timeout_) {
        nav().navigate_back();
      }
    } else {
      nav().handle(e);
    }
  }

  void NavKeyMap::handle(EncoderEvent e) noexcept
  {
    nav().handle(e);
  }
} // namespace otto
