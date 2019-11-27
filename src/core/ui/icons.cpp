#include "icons.hpp"

namespace otto::core::ui {

  Icon::Icon(IconDrawer drawer, nvg::Size s, nvg::Color c, float lw) : drawer_(std::move(drawer)), data_{s, c, lw} {}

  void Icon::draw(nvg::Canvas& ctx)
  {
    if (drawer_ == nullptr) return;
    drawer_(data_, ctx);
  }

  void Icon::set_size(nvg::Size size)
  {
    data_.size = size;
  }

  void Icon::set_color(nvg::Color color)
  {
    data_.color = color;
  }

  void Icon::set_line_width(float width)
  {
    data_.line_width = width;
  }

  nvg::Box IconData::square()
  {
    float min = size.min();
    return {nvg::Point((size.w - min), (size.h - min)) / 2.f, nvg::Size(min, min)};
  }

  namespace icons {
    void plus(IconData& i, nvg::Canvas& ctx)
    {
      auto box = i.square();
      auto size = box.size();
      ctx.translate(box.pmin());
      ctx.beginPath();
      ctx.moveTo(size.w / 2, 0);
      ctx.lineTo(size.w / 2, size.h);
      ctx.moveTo(0, size.h / 2);
      ctx.lineTo(size.w, size.h / 2);
      ctx.stroke(i.color);
    }

    void plus_clockwise_circle_arrow(IconData& i, nvg::Canvas& ctx)
    {
      // #layer1
      ctx.save();
      auto box = i.square();
      auto size = box.size();
      ctx.translate(box.pmin());
      ctx.scale(size.w / 26.f, size.h / 26.f);
      auto line_width = i.line_width / (size.w / 26.f);
      ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, 0.000000, -343.267710);

      // #path12
      ctx.beginPath();
      ctx.moveTo(13.000000, 369.267700);
      ctx.bezierCurveTo(6.798033, 369.267700, 1.459733, 364.886668, 0.249791, 358.803870);
      ctx.bezierCurveTo(-0.960148, 352.721076, 2.295250, 346.630659, 8.025115, 344.257270);
      ctx.bezierCurveTo(13.754984, 341.883880, 20.363477, 343.888544, 23.809105, 349.045290);
      ctx.bezierCurveTo(27.254732, 354.202036, 26.577840, 361.074638, 22.192388, 365.460090);
      ctx.lineWidth(line_width);
      ctx.stroke(i.color);

      // #path822
      ctx.beginPath();
      ctx.moveTo(13.000000, 364.267710);
      ctx.bezierCurveTo(13.000000, 364.267710, 13.000000, 348.267710, 13.000000, 348.267710);
      ctx.lineWidth(line_width);
      ctx.stroke(i.color);

      // #path833
      ctx.beginPath();
      ctx.moveTo(5.000000, 356.267710);
      ctx.bezierCurveTo(5.000000, 356.267710, 21.000000, 356.267710, 21.000000, 356.267710);
      ctx.lineWidth(line_width);
      ctx.stroke(i.color);

      // #path835
      ctx.beginPath();
      ctx.moveTo(27.148438, 364.629040);
      ctx.bezierCurveTo(27.148438, 364.629040, 22.192388, 365.460090, 22.192388, 365.460090);
      ctx.bezierCurveTo(22.192388, 365.460090, 21.000000, 361.267710, 21.000000, 361.267710);
      ctx.lineWidth(line_width);
      ctx.stroke(i.color);
      ctx.restore();
    }
  } // namespace icons

} // namespace otto::core::ui
