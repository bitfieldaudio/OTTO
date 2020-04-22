#pragma once

#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/screen.hpp"
#include "goss.hpp"

#include "audio.hpp"

namespace otto::engines::goss {

  using namespace itc;

  struct GossScreen final : ui::Screen,
                            itc::ActionReceiverOnBus<itc::GraphicsBus,
                                                     itc::prop_change<&Props::model>,
                                                     itc::prop_change<&Props::click>,
                                                     itc::prop_change<&Props::drive>,
                                                     itc::prop_change<&Props::leslie>> //
  {
    GossScreen(itc::Shared<float>) noexcept;
    void draw(nvg::Canvas& ctx) override;
    void draw_model(nvg::Canvas& ctx, float interpolation_value);
    void draw_horn(nvg::Canvas& ctx, float phase);
    void draw_drive(nvg::Canvas& ctx, float drive);
    void draw_click(nvg::Canvas& ctx, float click);

    void action(itc::prop_change<&Props::model>, int m) noexcept final;
    void action(itc::prop_change<&Props::click>, float c) noexcept final;
    void action(itc::prop_change<&Props::drive>, float d) noexcept final;
    void action(itc::prop_change<&Props::leslie>, float l) noexcept final;

    itc::Shared<float> rotation;
    int model = 0;
    float drive = 0;
    float click = 0;
    float leslie = 0;

    model_type model_param;
    model_type prev_model_param;
    ch::Output<float> model_interp = 0;
  };
} // namespace otto::engines::goss
