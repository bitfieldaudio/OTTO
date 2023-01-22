#include "navigator.hpp"

#include "lib/logging.hpp"

#include "app/domains/graphics.hpp"

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

  ScreenWithHandlerPtr Navigator::prev_screen() noexcept
  {
    return prev_screen_;
  }

  // NAV KEYMAP

  NavKeyMap::NavKeyMap(Conf conf, util::smart_ptr<Navigator> n) : conf(conf), nav_(std::move(n)) {}

  Navigator& NavKeyMap::nav()
  {
    return *nav_;
  }

  std::unordered_map<Key, ScreenWithHandlerPtr>& NavKeyMap::current_binds()
  {
    if (shift_held) {
      return shift_binds_;
    }
    return binds_;
  }

  const std::unordered_map<Key, ScreenWithHandlerPtr>& NavKeyMap::current_binds() const
  {
    if (shift_held) {
      return shift_binds_;
    }
    return binds_;
  }

  void NavKeyMap::bind_nav_key(Key key, ScreenWithHandlerPtr scrn, bool shift_held)
  {
    if (shift_held) {
      shift_binds_[key] = scrn;
    } else {
      binds_[key] = scrn;
    }
  }

  void NavKeyMap::handle(KeyPress e) noexcept
  {
    GraphicsDomain::static_executor().execute([this, e] {
      auto found = current_binds().find(e.key);
      if (found != current_binds().end() && found->second != nullptr) {
        auto bind = found->second;
        last_nav_time_ = e.timestamp;
        if (bind == nav().current_screen() && bind.screen->is_overlay()) {
          nav().navigate_back();
        } else {
          nav().navigate_to(bind);
        }
      } else {
        if (e.key == Key::shift) shift_held = true;
        nav().handle(e);
      }
    });
  }

  void NavKeyMap::handle(KeyRelease e) noexcept
  {
    GraphicsDomain::static_executor().execute([this, e] {
      auto found = current_binds().find(e.key);
      if (found != current_binds().end() && found->second != nullptr) {
        auto bind = found->second;
        // NOLINTNEXTLINE
        if (bind == nav().current_screen() && (e.timestamp - last_nav_time_) > conf.peek_timeout) {
          nav().navigate_back();
        }
      } else {
        if (e.key == Key::shift) shift_held = false;
        nav().handle(e);
      }
    });
  }

  void NavKeyMap::handle(EncoderEvent e) noexcept
  {
    GraphicsDomain::static_executor().execute([this, e] { nav().handle(e); });
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
    return nav_->key_mask() | KeySet(util::transform(current_binds(), LAMBDAFY(std::get<0>))) | KeySet({Key::shift});
  }

  LedSet NavKeyMap::led_mask() const noexcept
  {
    auto res = nav_->led_mask();
    for (auto&& [k, v] : current_binds()) {
      if (auto l = led_from(k)) {
        res += *l;
      }
    }
    return res;
  }

  void NavKeyMap::leds(LEDColorSet& output) noexcept
  {
    auto current = nav_->current_screen();
    for (auto&& [k, scrn] : current_binds()) {
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

  void NavKeyMap::deserialize_from(const json::value& json)
  {
    if (auto obj = json::get_or_null(json, "previous"); obj.is_string()) {
      auto prev = util::deserialize<Key>(obj);
      auto found = binds_.find(prev);
      if (found == binds_.end()) return;

      GraphicsDomain::static_executor().execute([=] { nav().navigate_to(found->second); });
    }

    if (auto obj = json::get_or_null(json, "current"); obj.is_string()) {
      auto cur = util::deserialize<Key>(obj);
      auto found = binds_.find(cur);
      if (found == binds_.end()) return;
      GraphicsDomain::static_executor().execute([=] { nav().navigate_to(found->second); });
    }
  }

  void NavKeyMap::serialize_into(json::value& json) const
  {
    auto cur = nav_->current_screen();
    auto prev = nav_->prev_screen();
    json = json::object();
    for (auto&& [k, v] : binds_) {
      if (v == cur) util::serialize_into(json["current"], k);
      if (v == prev) util::serialize_into(json["previous"], k);
    }
  }
} // namespace otto
