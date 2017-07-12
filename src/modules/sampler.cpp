#include "sampler.h"

#include <algorithm>

#include "../utils.h"
#include "../ui/utils.h"
#include "../globals.h"
#include "../util/sndfile.h"

namespace module {

Sampler::Sampler() :
  SynthModule(&data),
  maxSampleSize (16 * GLOB.samplerate),
  sampleData (maxSampleSize),
  editScreen (new SampleEditScreen(this)),
  recordScreen (new SampleRecordScreen(this)) {

  for (uint i = 0; i < sampleData.size(); i++) {
    sampleData[i] = (i % 22050) / 22050.0;
  }

  GLOB.events.samplerateChanged.add([&] (uint sr) {
    maxSampleSize = 6 * sr;
  });

}

void Sampler::process(uint nframes) {
  for (auto &&nEvent : GLOB.midiEvents) {
    nEvent.match([&] (NoteOnEvent *e) {
      currentVoiceIdx = e->key % nVoices;
      auto &&voice = data.voiceData[currentVoiceIdx];
      voice.playProgress = (voice.mode > 0) ? 0 : voice.length() - 1;
    }, [] (MidiEvent *) {});
  }

  for (auto &&voice : data.voiceData) {

    // Process audio
    if (voice.playProgress >= 0 && voice.mode != 0) {
      if (voice.mode > 0) {
        int frms = std::min<int>(nframes, voice.length() - voice.playProgress);
        for(int i = 0; i < frms; ++i) {
          GLOB.audioData.proc[i] += sampleData[voice.in + voice.playProgress];
          voice.playProgress += 1;
        }
        if (voice.playProgress >= voice.length()) {
          voice.playProgress = -1;
        }
      } else {
        int frms = std::min<int>(nframes, voice.playProgress);
        for(int i = 0; i < frms; ++i) {
          GLOB.audioData.proc[i] += sampleData[voice.in + voice.playProgress];
          voice.playProgress -= 1;
        }
      }
    }
  }

  for (auto &&nEvent : GLOB.midiEvents) {
    nEvent.match([&] (NoteOffEvent *e) {
      auto &&voice = data.voiceData[e->key % nVoices];
      if (std::abs(voice.mode) == 2) {
        voice.playProgress = -1;
      }
    }, [] (MidiEvent *) {});
  };
}

void Sampler::display() {
  GLOB.ui.display(editScreen);
}

void Sampler::load() {
  top1::SndFile<1> sf (samplePath(data.sampleName));

  size_t rs = std::min(maxSampleSize, sf.size());

  sampleData.resize(rs);
  sf.read(sampleData.data(), rs);

  // Auto assign voices
  // for (uint i = 0; i < nVoices; ++i) {
  //   auto &&vd = data.voiceData[i];

  //   vd.in = i * (sampleData.size() / nVoices);
  //   vd.out = (i + 1) * sampleData.size() / nVoices;
  // }

  auto &wf = dynamic_cast<SampleEditScreen *>(editScreen.get())->topWF;
  wf->clear();
  for (auto &&s : sampleData) {
    wf->addFrame(s);
  }

  if (sf.size() == 0) LOGD << "Empty sample file";
  sf.close();
}

void Sampler::init() {
  load();
}



/****************************************/
/* SampleEditScreen                     */
/****************************************/

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
  topWFW.drawAt(ctx, 10, 10);
}

}
