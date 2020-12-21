#include "layers.hpp"

namespace otto {

  bool InputLayerStack::remove_layer(ILEDLayer& layer)
  {
    return std::erase(led_layers_, &layer) > 0;
  }

  bool InputLayerStack::remove_layer(IInputLayer& layer)
  {
    return std::erase(input_layers_, &layer) > 0;
  }

  void InputLayerStack::add_layer(ILEDLayer& layer)
  {
    led_layers_.emplace_back(&layer);
  }

  void InputLayerStack::add_layer(IInputLayer& layer)
  {
    input_layers_.emplace_back(&layer);
  }

  ILEDLayer* InputLayerStack::layer_for(Led led) noexcept
  {
    for (auto& l : util::reverse(led_layers_)) {
      if (l->covered_leds()[led]) return l;
    }
    return nullptr;
  }

  IInputLayer* InputLayerStack::layer_for(Key k) noexcept
  {
    for (auto& l : util::reverse(input_layers_)) {
      if (l->covered_keys()[k]) return l;
    }
    return nullptr;
  }

  util::enum_bitset<Led> InputLayerStack::covered_leds() const noexcept
  {
    util::enum_bitset<Led> res;
    for (const auto& l : led_layers_) {
      res |= l->covered_leds();
    }
    return res;
  }

  util::enum_bitset<Key> InputLayerStack::covered_keys() const noexcept
  {
    util::enum_bitset<Key> res;
    for (const auto& l : input_layers_) {
      res |= l->covered_keys();
    }
    return res;
  }

  static void masked_copy(const LEDColorSet& src, LEDColorSet& dst, const util::enum_bitset<Led>& mask)
  {
    for (Led l : util::enum_values<Led>()) {
      if (mask[l]) dst[l] = src[l];
    }
  }

  void InputLayerStack::leds(LEDColorSet& colors) noexcept
  {
    LEDColorSet tmp;
    for (auto& l : led_layers_) {
      l->leds(tmp);
      masked_copy(tmp, colors, l->covered_leds());
    }
  }

  void InputLayerStack::handle(KeyRelease e) noexcept
  {
    if (auto* l = layer_for(e.key)) l->handle(e);
  }

  void InputLayerStack::handle(KeyPress e) noexcept
  {
    if (auto* l = layer_for(e.key)) l->handle(e);
  }

  void InputLayerStack::handle(EncoderEvent e) noexcept
  {
    for (auto& l : util::reverse(input_layers_)) {
      l->handle(e);
    }
  }
} // namespace otto
