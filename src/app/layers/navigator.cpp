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
      if (current_screen_.screen->is_overlay() && prev_screen_ != nullptr) prev_screen_.screen->draw(ctx);
      swh.screen->draw(ctx);
    }
  }

  void Navigator::handle(EncoderEvent e) noexcept
  {
    if (const auto swh = current_screen_; swh != nullptr) {
      swh.input->handle(e);
    }
  }

  void Navigator::handle(KeyRelease e) noexcept
  {
    if (const auto swh = current_screen_; swh != nullptr) {
      swh.input->handle(e);
    }
  }

  void Navigator::handle(KeyPress e) noexcept
  {
    if (const auto swh = current_screen_; swh != nullptr) {
      swh.input->handle(e);
    }
  }

  ScreenWithHandlerPtr Navigator::current_screen() noexcept
  {
    return current_screen_;
  }

  // NAV KEYMAP

  NavKeyMap::NavKeyMap(Conf conf, util::smart_ptr<Navigator> n) : conf(conf), nav_(std::move(n)) {}

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
      if (bind == nav().current_screen() && bind.screen->is_overlay()) {
        nav().navigate_back();
      } else {
        nav().navigate_to(bind);
      }
    } else {
      nav().handle(e);
    }
  }

  void NavKeyMap::handle(KeyRelease e) noexcept
  {
    auto bind = binds_[e.key];
    if (bind != nullptr) {
      // NOLINTNEXTLINE
      if (bind == nav().current_screen() && (e.timestamp - last_nav_time_) > conf.peek_timeout) {
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

  ScreenWithHandlerPtr NavKeyMap::screen()
  {
    return {&nav(), this};
  }

  void Navigator::leds(LEDColorSet& output) noexcept
  {
    if (current_screen_ != nullptr) current_screen_.screen->leds(output);
  }
  LedSet Navigator::led_mask() const noexcept
  {
    if (current_screen_ != nullptr) return current_screen_.screen->led_mask();
    return {};
  }
  KeySet Navigator::key_mask() const noexcept
  {
    if (current_screen_ != nullptr) return current_screen_.input->key_mask();
    return {};
  }

  KeySet NavKeyMap::key_mask() const noexcept
  {
    return nav_->key_mask() | KeySet(util::transform(binds_, LAMBDAFY(std::get<0>)));
  }

  LedSet NavKeyMap::led_mask() const noexcept
  {
    auto res = nav_->led_mask();
    for (auto&& [k, v] : binds_) {
      if (auto l = led_from(k)) {
        res += *l;
      }
    }
    return res;
  }

  void NavKeyMap::leds(LEDColorSet& output) noexcept
  {
    auto current = nav_->current_screen();
    for (auto&& [k, scrn] : binds_) {
      if (auto led = led_from(k)) {
        if (scrn == current) {
          output[*led] = conf.selected_color;
        } else {
          output[*led] = conf.deselected_color;
        }
      }
    }
    nav_->leds(output);
  }

  void NavKeyMap::draw(skia::Canvas& ctx) noexcept
  {
    return nav_->draw(ctx);
  }
} // namespace otto
