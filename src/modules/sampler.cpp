#include "sampler.h"

#include "../ui/utils.h"
#include "../globals.h"

namespace module {

Sampler::Sampler() :
  sampleData (6 * GLOB.samplerate),
  editScreen (new SampleEditScreen(this)),
  recordScreen (new SampleRecordScreen(this)) {

  for (int i = 0; i < sampleData.size(); i++) {
    sampleData[i] = (i % 22050) / 22050.0;
  }
}

void Sampler::process(uint nframes) {

}

void Sampler::display() {
  GLOB.ui.display(editScreen);
}

const static float topWFwidth = 300;
const static float topWFheight = 20;

SampleEditScreen::SampleEditScreen(Sampler *m) :
  ModuleScreen (m),
  topWF (new Waveform(
     module->sampleData.size() / topWFwidth, 1.0)
  ),
  topWFW (topWF, topWFwidth, topWFheight)
{
  GLOB.events.postInit.add([&] () {
     for (auto &&s : module->sampleData) {
       topWF->addFrame(s);
     }
   });
}

void SampleEditScreen::draw(NanoCanvas::Canvas &ctx) {
  using namespace drawing;
  topWFW.lineCol = COLOR_BLUE;
  topWFW.drawAt(ctx, 20, 10);
}

}
