#pragma once

#include <memory>

#include "../util/waveform.h"
#include "base.h"
#include "utils.h"

class WaveformWidget : public ui::Widget {
public:
  drawing::Color lineCol;

  WaveformWidget() {};

  WaveformWidget(std::shared_ptr<Waveform> wf, float w, float h ) :
    Widget (w, h), wf (wf) {}

  void draw(NanoCanvas::Canvas &) override;

private:
  std::shared_ptr<Waveform> wf;
};

/************************************************************/
/* WaveformWidget Implementation      >                      */
/************************************************************/

inline void WaveformWidget::draw(NanoCanvas::Canvas &ctx) {
  using namespace drawing;

  const float pxPrPt = w / float(wf->size());

  ctx.beginPath();
  ctx.moveTo(0, wf->operator[](0) * h);
  for (int i = 1, wp = w/pxPrPt; i < wp; i++) {
    ctx.lineTo(i * pxPrPt, wf->operator[](i) * h);
  }
  ctx.strokeStyle(lineCol);
  ctx.stroke();
}
