#pragma once

#include <memory>
#include <algorithm>

#include "../util/waveform.h"
#include "../utils.h"
#include "base.h"
#include "utils.h"

template<typename Container>
class WaveformWidget : public ui::Widget {
public:

  using Range = Section<std::size_t>;

  Range viewRange;
  drawing::Colour lineCol;

  WaveformWidget() {};

  WaveformWidget(std::shared_ptr<Container> wf, drawing::Size s ) :
    Widget (s), wf (wf) {
    viewRange = {0, int(wf->size()) - 1};
  }

  void draw(drawing::Canvas &) override;

  void drawRange(drawing::Canvas&, Range range, drawing::Colour);

  void drawRange(drawing::Canvas& ctx, Range range) {
    drawRange(ctx, range, lineCol);
  }

  drawing::Point coord(std::size_t idx) const;

private:
  std::shared_ptr<Container> wf;
};

/****************************************/
/* WaveformWidget Implementation        */
/****************************************/

template<typename C>
inline void WaveformWidget<C>::draw(drawing::Canvas &ctx) {
  drawRange(ctx, viewRange);
}

template<typename C>
inline void WaveformWidget<C>::drawRange(
  drawing::Canvas &ctx,
  Range range,
  drawing::Colour colour)
{
  using namespace drawing;

  const float pxPrPt = size.w / float(viewRange.size());

  ctx.beginPath();
  ctx.lineCap(Canvas::LineCap::ROUND);
  ctx.lineJoin(Canvas::LineJoin::ROUND);
  if (range.size() < 3) {
    ctx.moveTo(range.in / pxPrPt, size.h);
    ctx.lineTo(range.out / pxPrPt, size.h - 0);
  } else {
    const int inc = std::max<int>(1, 1/pxPrPt);
    std::vector<Point> pts;
    for (int i = 0, end = range.size(); i < end; i += inc) {
      pts.push_back(coord(range.in + i));
    }
    ctx.bzCurve(pts.begin(), pts.end());
  }
  ctx.strokeStyle(colour);
  ctx.stroke();
}

template<typename C>
inline drawing::Point WaveformWidget<C>::coord(std::size_t idx) const {
  return {
    (idx - viewRange.in) / float(viewRange.size()) * size.w,
    (1 - (*wf)[idx]) * size.h
  };
}
