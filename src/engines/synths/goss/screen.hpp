#pragma once

#include "core/ui/screen.hpp"
#include "goss.hpp"

namespace otto::engines::goss {

  using namespace core2;

  struct GossScreen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;
    bool keypress(ui::Key key) override;
    void encoder(ui::EncoderEvent e) override;

    void action(core2::prop_change<&Props::drawbar1>, float d1) noexcept;
    void action(core2::prop_change<&Props::drawbar2>, float d2) noexcept;
    void action(core2::prop_change<&Props::click>, float c) noexcept;
    void action(core2::prop_change<&Props::leslie>, float l) noexcept;
    void action(Actions::rotation_variable, std::atomic<float>& v) noexcept;

    float drawbar1 = 1;
    float drawbar2 = 0;
    float click = 0;
    float leslie = 0;
    std::atomic<float>* rotation = nullptr;
  };
} // namespace otto::engines::goss
