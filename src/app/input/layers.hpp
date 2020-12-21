#pragma once

#include "lib/util/ranges.hpp"
#include "lib/util/smart_ptr.hpp"

#include "app/input.hpp"
#include "app/leds.hpp"

namespace otto {

  struct IInputLayer : IInputHandler {
    [[nodiscard]] virtual util::enum_bitset<Key> covered_keys() const noexcept = 0;
  };

  struct ILEDLayer : ILedController {
    [[nodiscard]] virtual util::enum_bitset<Led> covered_leds() const noexcept = 0;
  };

  struct InputLayerStack final : IInputLayer, ILEDLayer {
    void handle(KeyPress e) noexcept final;
    void handle(KeyRelease e) noexcept final;
    void handle(EncoderEvent e) noexcept final;
    void leds(LEDColorSet& colors) noexcept final;

    [[nodiscard]] util::enum_bitset<Key> covered_keys() const noexcept final;
    [[nodiscard]] util::enum_bitset<Led> covered_leds() const noexcept final;

    IInputLayer* layer_for(Key k) noexcept;
    ILEDLayer* layer_for(Led led) noexcept;

    void add_layer(IInputLayer& layer);
    void add_layer(ILEDLayer& layer);

    bool remove_layer(IInputLayer& layer);
    bool remove_layer(ILEDLayer& layer);

  private:
    std::vector<IInputLayer*> input_layers_;
    std::vector<ILEDLayer*> led_layers_;
  };

  /// An `IInputLayer` implementation which takes the set of keys at construction time
  struct ConstInputLayer : IInputLayer {
    ConstInputLayer(const util::enum_bitset<Key>& keys) : keys_(keys) {}

    [[nodiscard]] util::enum_bitset<Key> covered_keys() const noexcept final
    {
      return keys_;
    }

  private:
    util::enum_bitset<Key> keys_;
  };

  /// An `ILEDLayer` implementation which takes the set of leds at construction time
  struct ConstLEDLayer : ILEDLayer {
    ConstLEDLayer(const util::enum_bitset<Led>& leds) : leds_(leds) {}

    [[nodiscard]] util::enum_bitset<Led> covered_leds() const noexcept final
    {
      return leds_;
    }

  private:
    util::enum_bitset<Led> leds_;
  };
} // namespace otto
