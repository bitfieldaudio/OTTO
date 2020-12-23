#pragma once

#include "lib/util/ranges.hpp"
#include "lib/util/smart_ptr.hpp"

#include "app/input.hpp"
#include "app/leds.hpp"

namespace otto {

  struct IInputLayer : IInputHandler {
    [[nodiscard]] virtual KeySet key_mask() const noexcept = 0;
  };

  struct ILEDLayer : ILedController {
    [[nodiscard]] virtual LedSet led_mask() const noexcept = 0;

    /// Calls `leds`, but only writes leds in `led_mask()` to output
    ///
    /// @returns `led_mask()`
    LedSet process_leds_masked(LEDColorSet& colors);
  };

  struct LayerStack final : IInputLayer, ILEDLayer {
    void handle(KeyPress e) noexcept final;
    void handle(KeyRelease e) noexcept final;
    void handle(EncoderEvent e) noexcept final;
    void leds(LEDColorSet& colors) noexcept final;

    [[nodiscard]] KeySet key_mask() const noexcept final;
    [[nodiscard]] LedSet led_mask() const noexcept final;

    IInputLayer* layer_for(Key k) noexcept;
    ILEDLayer* layer_for(Led led) noexcept;

    void add_layer(IInputLayer& layer);
    void add_layer(ILEDLayer& layer);

    template<typename T>
    requires(std::is_convertible_v<T&, IInputLayer&>&& std::is_convertible_v<T&, ILEDLayer&>) //
      void add_layer(T& layer)
    {
      add_layer(static_cast<IInputLayer&>(layer));
      add_layer(static_cast<ILEDLayer&>(layer));
    }

    template<typename T, typename... Args>
    requires(std::is_convertible_v<T&, IInputLayer&>&& std::is_convertible_v<T&, ILEDLayer&>&&
               std::is_constructible_v<T, Args...>) //
      T make_layer(Args&&... args)
    {
      T res = {FWD(args)...};
      add_layer(res);
      return res;
    }

    bool remove_layer(IInputLayer& layer);
    bool remove_layer(ILEDLayer& layer);

  private:
    std::vector<IInputLayer*> input_layers_;
    std::vector<ILEDLayer*> led_layers_;
  };

  /// An `IInputLayer` implementation which takes the set of keys at construction time
  struct ConstInputLayer : IInputLayer {
    ConstInputLayer(const KeySet& keys) : keys_(keys) {}

    [[nodiscard]] KeySet key_mask() const noexcept final
    {
      return keys_;
    }

  private:
    KeySet keys_;
  };

  /// An `ILEDLayer` implementation which takes the set of leds at construction time
  struct ConstLEDLayer : ILEDLayer {
    ConstLEDLayer(const LedSet& leds) : leds_(leds) {}

    [[nodiscard]] LedSet led_mask() const noexcept final
    {
      return leds_;
    }

  private:
    LedSet leds_;
  };
} // namespace otto
