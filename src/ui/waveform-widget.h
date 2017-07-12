#pragma once

#include <memory>

#include "../util/waveform.h"
#include "base.h"
#include "utils.h"

class WaveformWidget : public ui::Widget {
public:
  drawing::Colour lineCol;

  WaveformWidget() {};

  WaveformWidget(std::shared_ptr<Waveform> wf, float w, float h ) :
    Widget (w, h), wf (wf) {}

  void draw(NanoCanvas::Canvas &) override;

private:
  std::shared_ptr<Waveform> wf;
};

/****************************************/
/* WaveformWidget Implementation        */
/****************************************/

inline void WaveformWidget::draw(NanoCanvas::Canvas &ctx) {
  using namespace drawing;

  const float pxPrPt = w / float(wf->size());

  ctx.beginPath();
  ctx.lineCap(Canvas::LineCap::ROUND);
  ctx.lineJoin(Canvas::LineJoin::ROUND);
  if (wf->size() == 0) {
    ctx.moveTo(0, h - 0);
    ctx.lineTo(w, h - 0);
  } else {
    ctx.moveTo(0, (1 - wf->operator[](0)) * h);
    for (int i = 1, wp = w/pxPrPt; i < wp; i++) {
      ctx.lineTo(i * pxPrPt, (1 - wf->operator[](i)) * h);
    }
  }
  ctx.strokeStyle(lineCol);
  ctx.stroke();
}
