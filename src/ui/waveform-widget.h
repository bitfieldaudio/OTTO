#pragma once

#include <memory>

#include "../util/waveform.h"
#include "base.h"

class WaveformWidget : public Widget {
public:
  drawing::Color lineCol;

  WaveformWidget() {};

  WaveformWidget(std::shared_ptr<Waveform> wf, float h, float w ) :
    Widget (h, w), wf (wf) {}

  void draw(NanoCanvas::Canvas &) override;

private:
  std::shared_ptr<Waveform> wf;
}

/************************************************************/
/* WaveformWidget Implementation                            */
/************************************************************/

void WaveformWidget::draw(NanoCanvas::Canvas &ctx) {
  using namespace drawing;

  const float pxPrPt = w / float(wf.size());

  ctx.beginPath();
  ctx.moveTo(0, wf[0] * h);
  for (int i = 1, wp = w/pxPrPt; i < wp; i++) {
    ctx.lineTo(i * pxPrPt, wf[i] * h);
  }
  ctx.stroke(lineCol);
}
