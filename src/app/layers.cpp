#include "layers.hpp"

namespace otto {

  LedSet ILEDLayer::process_leds_masked(LEDColorSet& colors)
  {
    LEDColorSet tmp;
    leds(tmp);
    auto mask = led_mask();
    for (Led l : util::enum_values<Led>()) {
      if (mask[l]) colors[l] = tmp[l];
    }
    return mask;
  }

  bool LayerStack::remove_layer(ILEDLayer& layer)
  {
    return std::erase(led_layers_, &layer) > 0;
  }

  bool LayerStack::remove_layer(IInputLayer& layer)
  {
    return std::erase(input_layers_, &layer) > 0;
  }

  void LayerStack::add_layer(ILEDLayer& layer)
  {
    led_layers_.emplace_back(&layer);
  }

  void LayerStack::add_layer(IInputLayer& layer)
  {
    input_layers_.emplace_back(&layer);
  }

  ILEDLayer* LayerStack::layer_for(Led led) noexcept
  {
    for (auto& l : util::reverse(led_layers_)) {
      if (l->led_mask()[led]) return l;
    }
    return nullptr;
  }

  IInputLayer* LayerStack::layer_for(Key k) noexcept
  {
    for (auto& l : util::reverse(input_layers_)) {
      if (l->key_mask()[k]) return l;
    }
    return nullptr;
  }

  LedSet LayerStack::led_mask() const noexcept
  {
    LedSet res;
    for (const auto& l : led_layers_) {
      res |= l->led_mask();
    }
    return res;
  }

  KeySet LayerStack::key_mask() const noexcept
  {
    KeySet res;
    for (const auto& l : input_layers_) {
      res |= l->key_mask();
    }
    return res;
  }

  void LayerStack::leds(LEDColorSet& colors) noexcept
  {
    LedSet done = {};
    for (auto* l : util::reverse(led_layers_)) {
      LEDColorSet tmp = colors;
      auto mask = l->led_mask();
      l->leds(tmp);
      for (auto l : util::enum_values<Led>()) {
        if (mask[l] && !done[l]) colors[l] = tmp[l];
      }
      done |= mask;
      if (done.all()) break;
    }
  }

  void LayerStack::handle(KeyRelease e) noexcept
  {
    if (auto* l = layer_for(e.key)) l->handle(e);
  }

  void LayerStack::handle(KeyPress e) noexcept
  {
    if (auto* l = layer_for(e.key)) l->handle(e);
  }

  void LayerStack::handle(EncoderEvent e) noexcept
  {
    if (auto* l = layer_for(click_for(e.encoder))) l->handle(e);
  }

} // namespace otto
