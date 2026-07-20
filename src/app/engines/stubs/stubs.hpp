#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "lib/skia/skia.hpp"

#include "lib/graphics.hpp"

#include "app/input.hpp"
#include "app/layers.hpp"
#include "app/layers/navigator.hpp"
#include "app/leds.hpp"
#include "app/services/graphics.hpp"

namespace otto::engines::stubs {

  struct TransportModel {
    bool playing = false;
    bool recording = false;
  };

  /// Global play/record handling (must win over NavKeyMap for those keys).
  struct TransportLayer final : IInputLayer, ILEDLayer {
    explicit TransportLayer(std::shared_ptr<TransportModel> model) : model_(std::move(model)) {}

    [[nodiscard]] KeySet key_mask() const noexcept override
    {
      return KeySet({Key::play, Key::record});
    }
    void handle(KeyPress e) noexcept override
    {
      if (e.key == Key::play) model_->playing = !model_->playing;
      if (e.key == Key::record) model_->recording = !model_->recording;
    }
    void handle(KeyRelease) noexcept override {}
    void handle(EncoderEvent) noexcept override {}

    [[nodiscard]] LedSet led_mask() const noexcept override
    {
      return LedSet({Led::play, Led::record});
    }
    void leds(LEDColorSet& colors) noexcept override
    {
      colors[Led::play] = model_->playing ? led_colors::green : led_colors::inactive;
      colors[Led::record] = model_->recording ? led_colors::red : led_colors::inactive;
    }

    std::shared_ptr<TransportModel> model_;
  };

  namespace detail {
    struct PlaceholderScreen final : ScreenBase {
      PlaceholderScreen(std::string title, std::string subtitle)
        : title_(std::move(title)), subtitle_(std::move(subtitle))
      {}

      void draw(skia::Canvas& ctx) noexcept override
      {
        skia::place_text(ctx, title_, fonts::black(28), paints::fill(colors::white), {160, 90}, anchors::center);
        skia::place_text(ctx, subtitle_, fonts::regular(18), paints::fill(colors::grey50), {160, 130}, anchors::center);
        skia::place_text(ctx, "Use encoders / nav keys", fonts::regular(14), paints::fill(colors::grey70), {160, 180},
                         anchors::center);
      }

      std::string title_;
      std::string subtitle_;
    };

    struct EmptyHandler final : IInputLayer {
      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }
      void handle(KeyPress) noexcept override {}
      void handle(KeyRelease) noexcept override {}
      void handle(EncoderEvent) noexcept override {}
    };

    struct TransportScreen final : ScreenBase {
      explicit TransportScreen(std::shared_ptr<TransportModel> model) : model_(std::move(model)) {}

      void draw(skia::Canvas& ctx) noexcept override
      {
        skia::place_text(ctx, "TRANSPORT", fonts::black(22), paints::fill(colors::white), {160, 40}, anchors::center);
        skia::place_text(ctx, model_->playing ? "PLAYING" : "STOPPED", fonts::black(32),
                         paints::fill(model_->playing ? colors::green : colors::grey50), {160, 110}, anchors::center);
        skia::place_text(ctx, model_->recording ? "REC ARMED" : "rec idle", fonts::regular(18),
                         paints::fill(model_->recording ? colors::red : colors::grey70), {160, 160}, anchors::center);
        skia::place_text(ctx, "Play / Record keys toggle", fonts::regular(14), paints::fill(colors::grey70), {160, 210},
                         anchors::center);
      }

      std::shared_ptr<TransportModel> model_;
    };
  } // namespace detail

  inline ScreenWithHandler make_placeholder(std::string title, std::string subtitle = "Coming soon")
  {
    return {
      std::make_unique<detail::PlaceholderScreen>(std::move(title), std::move(subtitle)),
      std::make_unique<detail::EmptyHandler>(),
    };
  }

  inline ScreenWithHandler make_transport_screen(std::shared_ptr<TransportModel> model)
  {
    return {
      std::make_unique<detail::TransportScreen>(std::move(model)),
      std::make_unique<detail::EmptyHandler>(),
    };
  }

  /// Bind every unbound screen-group key to a placeholder so the panel navigates.
  inline void bind_missing_nav_keys(NavKeyMap& nav)
  {
    struct Item {
      Key key;
      const char* title;
      const char* subtitle;
    };
    // Keep alive for process lifetime (NavKeyMap stores raw pointers into these).
    static std::vector<ScreenWithHandler> held;
    held.clear();
    const Item items[] = {
      {Key::sequencer, "SEQUENCER", "Not in this build"},
      {Key::sampler, "SAMPLER", "Not in this build"},
      {Key::looper, "LOOPER", "Not in this build"},
      {Key::mixer, "MIXER", "Not in this build"},
      {Key::fx1, "FX 1", "Not in this build"},
      {Key::fx2, "FX 2", "Not in this build"},
      {Key::sends, "SENDS", "Not in this build"},
      {Key::external, "EXTERNAL", "Not in this build"},
      {Key::settings, "SETTINGS", "See docs/MAC.md"},
      {Key::omega, "OMEGA", "Not in this build"},
      {Key::twist1, "TWIST 1", "Not in this build"},
      {Key::twist2, "TWIST 2", "Not in this build"},
    };
    held.reserve(std::size(items));
    for (const auto& it : items) {
      held.push_back(make_placeholder(it.title, it.subtitle));
      nav.bind_nav_key(it.key, held.back());
    }
  }

} // namespace otto::engines::stubs
