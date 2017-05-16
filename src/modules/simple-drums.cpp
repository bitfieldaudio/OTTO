#include "simple-drums.h"
#include "simple-drums.faust.h"

#include "../ui/utils.h"

SimpleDrumVoice::SimpleDrumVoice() : FaustWrapper(
  new faust_simple_drums(), {

    {"D1/FREQ",          &D1.freq},
    {"D1/NOISE",         &D1.noiseLvL},
    {"D1/TONE_DECAY",    &D1.toneDecay},
    {"D1/CUTOFF",        &D1.cutoff},
    {"D1/FILTER_SWITCH", &D1.filterSwitch},
    {"D1/DECAY_GRAPH",   &D1.decayGraph},

    {"D2/FREQ",          &D2.freq},
    {"D2/NOISE",         &D2.noiseLvL},
    {"D2/TONE_DECAY",    &D2.toneDecay},
    {"D2/CUTOFF",        &D2.cutoff},
    {"D2/FILTER_SWITCH", &D2.filterSwitch},
    {"D2/DECAY_GRAPH",   &D2.decayGraph},

    {"ENVELOPE/ATTACK",  &envelope.attack},
    {"ENVELOPE/RELEASE", &envelope.attack},
    {"ENVELOPE/SUSTAIN", &envelope.attack},

    {"TRIGGER",          &trigger},
  }) {
  LOGD << "SimpleDrumVoice";
}

SimpleDrumsModule::SimpleDrumsModule() {
  screen = new SimpleDrumsScreen(this);
}

SimpleDrumsModule::~SimpleDrumsModule() {
  delete screen;
}

void SimpleDrumsModule::process(uint nframes) {
  for (auto nEvent : GLOB.midiEvents) {
    if (nEvent->type == MidiEvent::NOTE_ON) {
      NoteOnEvent *event = dynamic_cast<NoteOnEvent*>(nEvent);
      currentVoiceIdx = event->key % 24;
      *voices[currentVoiceIdx].trigger = 1;
    }
    if (nEvent->type == MidiEvent::NOTE_OFF) {
      NoteOffEvent *event = dynamic_cast<NoteOffEvent*>(nEvent);
      *voices[event->key % 24].trigger = 0;
    }
  };
  for (auto &voice : voices) {
    voice.process(nframes);
  }
}

bool SimpleDrumsScreen::keypress(ui::Key key) {
  using namespace ui;
  auto &voice = module->voices[module->currentVoiceIdx];
  auto &osc = GLOB.ui.keys[K_SHIFT] ? voice.D2 : voice.D1;
  switch (key) {
  case K_RED_UP:
    *osc.freq = top::withBounds(10, 500, *osc.freq + 4.9); break;
  case K_RED_DOWN:
    *osc.freq = top::withBounds(10, 500, *osc.freq - 4.9); break;
  case K_BLUE_UP:
    *osc.toneDecay = top::withBounds(-1, 1, *osc.toneDecay + 0.02); break;
  case K_BLUE_DOWN:
    *osc.toneDecay = top::withBounds(-1, 1, *osc.toneDecay - 0.02); break;
  case K_WHITE_UP:
    *osc.noiseLvL = top::withBounds(0, 1, *osc.noiseLvL + 0.01); break;
  case K_WHITE_DOWN:
    *osc.noiseLvL = top::withBounds(0, 1, *osc.noiseLvL - 0.01); break;
  case K_GREEN_UP:
    *osc.cutoff = top::withBounds(5, 5000, *osc.cutoff * 1.3); break;
  case K_GREEN_DOWN:
    *osc.cutoff = top::withBounds(5, 5000, *osc.cutoff / 1.3); break;
  case K_GREEN_CLICK:
    *osc.filterSwitch = !*osc.filterSwitch; break;
  }
}

void SimpleDrumsScreen::draw(NanoCanvas::Canvas &ctx) {
  using namespace drawing;
  auto &voice = (module->voices[module->currentVoiceIdx]);
  ctx.save();
  drawOsc(ctx, voice.D1);
  ctx.translate(0, 75);
  drawOsc(ctx, voice.D2);
  ctx.restore();

  drawKbd(ctx);
}

void SimpleDrumsScreen::drawOsc(NanoCanvas::Canvas &ctx, SimpleDrumVoice::Osc &osc) {
  using namespace drawing;

	ctx.globalAlpha(1.0);
	ctx.lineJoin(Canvas::LineJoin::ROUND);
	ctx.strokeStyle(COLOR_GRAY60);
	ctx.lineCap(Canvas::LineCap::ROUND);
	ctx.miterLimit(4);
// #FREQ_G
	
// #FREQ_BOX
	ctx.beginPath();
	ctx.lineWidth(2.000000);
	ctx.rect(16.000000, 16.000000, 63.000000, 63.000000);
	ctx.stroke();

  // FREQ_TXT
	ctx.lineWidth(1.000000);
	ctx.fillStyle(COLOR_GRAY60);
	ctx.font(FONT_NORM);
	ctx.font(15);
  ctx.textAlign(TextAlign::Center, TextAlign::Baseline);
	ctx.fillText("PITCH", 47.5, 75);

// #FREQ_DIAL_BG
	ctx.beginPath();
	ctx.strokeStyle(COLOR_GRAY70);
	ctx.lineWidth(1.000000);
	ctx.moveTo(30.876403, 64.114053);
	ctx.lineTo(37.240364, 57.750093);
	ctx.moveTo(47.500000, 24.000001);
	ctx.lineTo(47.500000, 33.000001);
	ctx.moveTo(64.110261, 64.119578);
	ctx.lineTo(57.746299, 57.755616);
	ctx.moveTo(64.378424, 57.247816);
	ctx.lineTo(60.048298, 54.747817);
	ctx.moveTo(66.327053, 52.546073);
	ctx.lineTo(61.497425, 51.251978);
	ctx.moveTo(66.992384, 47.500195);
	ctx.lineTo(61.992385, 47.500195);
	ctx.moveTo(66.329075, 42.454051);
	ctx.lineTo(61.499447, 43.748146);
	ctx.moveTo(64.382329, 37.751528);
	ctx.lineTo(60.052203, 40.251527);
	ctx.moveTo(61.284815, 33.713093);
	ctx.lineTo(57.749281, 37.248627);
	ctx.moveTo(57.247622, 30.613961);
	ctx.lineTo(54.747622, 34.944087);
	ctx.moveTo(52.545878, 28.665331);
	ctx.lineTo(51.251783, 33.494960);
	ctx.moveTo(42.453856, 28.663310);
	ctx.lineTo(43.747951, 33.492938);
	ctx.moveTo(33.712898, 33.707570);
	ctx.lineTo(37.248431, 37.243103);
	ctx.moveTo(28.665136, 42.446507);
	ctx.lineTo(33.494764, 43.740602);
	ctx.moveTo(28.663114, 52.538529);
	ctx.lineTo(33.492743, 51.244433);
	ctx.moveTo(30.609860, 57.241052);
	ctx.lineTo(34.939987, 54.741052);
	ctx.moveTo(27.999805, 47.492384);
	ctx.lineTo(32.999805, 47.492384);
	ctx.moveTo(30.613766, 37.744763);
	ctx.lineTo(34.943893, 40.244763);
	ctx.moveTo(37.751332, 30.610055);
	ctx.lineTo(40.251332, 34.940182);
	ctx.stroke();
	
  // #FREQ_DIAL_RING
	ctx.beginPath();
	ctx.strokeStyle(COLOR_RED);
	ctx.lineWidth(2.000000);
	ctx.arc(47.500000, 47.500000, 11.500000, 0.000000, 6.28318531, 1);
	ctx.stroke();
	
  // #FREQ_DIAL_MARKER
	ctx.beginPath();
	ctx.strokeStyle(COLOR_RED);
	ctx.lineWidth(2.000000);
  ctx.save();
  ctx.translate(47.5, 47.5);
  ctx.rotate(-0.75 * M_PI + 1.5 * M_PI * (*osc.freq - 10) / 500);
	ctx.moveTo(0, 0);
	ctx.lineTo(0, -10.5);
  ctx.restore();
	ctx.stroke();
	
// #TONE_DECAY_G
	
// #TONE_DECAY_BOX
	ctx.beginPath();
	ctx.strokeStyle(COLOR_GRAY60);
	ctx.lineWidth(2.000000);
	ctx.rect(91.000000, 16.000000, 63.000000, 63.000000);
	ctx.stroke();
	
	
// #TXT_BG_TONE
	ctx.lineWidth(1.000000);
	ctx.fillStyle(COLOR_GRAY60);
	ctx.font(FONT_NORM);
	ctx.font(15);
  ctx.textAlign(TextAlign::Left, TextAlign::Baseline);
	ctx.fillText("PITCH", 95, 30);
	
// #TXT_BG_DELAY
	ctx.lineWidth(1.000000);
	ctx.fillStyle(COLOR_GRAY60);
	ctx.font(FONT_NORM);
	ctx.font(15);
  ctx.textAlign(TextAlign::Right, TextAlign::Baseline);
	ctx.fillText("DECAY", 150, 75);
	
// #DECAY_INDICATOR
	ctx.beginPath();
	ctx.strokeStyle(COLOR_GRAY70);
	ctx.lineWidth(2.000000);
	ctx.moveTo(95, 75);
  if (*osc.decayGraph > 0)
    ctx.bezierCurveTo(95, 75 - *osc.decayGraph * 65, 150 - *osc.decayGraph * 65, 20, 150, 20);
  else
    ctx.bezierCurveTo(95 - *osc.decayGraph * 65, 75, 150, 20 - *osc.decayGraph * 65, 150, 20);
	ctx.stroke();

// #DECAY_SETTING
	ctx.beginPath();
	ctx.strokeStyle(COLOR_BLUE);
	ctx.lineWidth(2.000000);
	ctx.moveTo(95, 75);
  if (*osc.toneDecay > 0)
    ctx.bezierCurveTo(95, 75 - *osc.toneDecay * 65, 150 - *osc.toneDecay * 65, 20, 150, 20);
  else
    ctx.bezierCurveTo(95 - *osc.toneDecay * 65, 75, 150, 20 - *osc.toneDecay * 65, 150, 20);
	ctx.stroke();

// #NOISE_G
	
// #NOISE_BOX
	ctx.beginPath();
	ctx.strokeStyle(COLOR_GRAY60);
	ctx.lineWidth(2.000000);
	ctx.rect(166.000000, 16.000000, 63.000000, 63.000000);
	ctx.stroke();
	
// #NOISE_WAVE
	ctx.beginPath();
	ctx.strokeStyle(COLOR_WHITE);
	ctx.lineWidth(1.000000);
	ctx.moveTo(204.897700, 71.868810);
	ctx.lineTo(208.738620, 71.868810);
	ctx.lineTo(209.308660, 69.660770);
	ctx.lineTo(209.919740, 74.442740);
	ctx.lineTo(211.345610, 67.911270);
	ctx.bezierCurveTo(211.345610, 67.911270, 211.549310, 75.784030, 211.956700, 75.725710);
	ctx.bezierCurveTo(212.364090, 75.667410, 213.314670, 68.319490, 213.314670, 68.319490);
	ctx.lineTo(214.265250, 73.976210);
	ctx.lineTo(215.351630, 67.503060);
	ctx.bezierCurveTo(215.351630, 67.503060, 216.370110, 75.025910, 216.505900, 75.259180);
	ctx.bezierCurveTo(216.641700, 75.492450, 217.456480, 69.194240, 217.456480, 69.194240);
	ctx.lineTo(218.814450, 74.559380);
	ctx.lineTo(219.629230, 68.202860);
	ctx.lineTo(220.261380, 71.868810);
	ctx.lineTo(224.102300, 71.868810);
	ctx.stroke();
	
// #SQUARE_WAVE
	ctx.beginPath();
	ctx.strokeStyle(COLOR_WHITE);
	ctx.lineWidth(1.000000);
	ctx.moveTo(172.000000, 72.000010);
	ctx.lineTo(177.000000, 72.000010);
	ctx.lineTo(177.000000, 75.117940);
	ctx.lineTo(182.000000, 75.118070);
	ctx.lineTo(182.000000, 68.882020);
	ctx.lineTo(187.000000, 68.882020);
	ctx.lineTo(187.000000, 72.000010);
	ctx.lineTo(192.000000, 72.000010);
	ctx.stroke();
	
// #NOISE_DIAL_RING
	ctx.beginPath();
	ctx.strokeStyle(COLOR_WHITE);
	ctx.lineWidth(2.000000);
	ctx.arc(197.500000, 47.500000, 11.500000, 0.000000, 6.28318531, 1);
	ctx.stroke();
	
// #NOISE_DIAL_MARKER
	ctx.beginPath();
	ctx.lineJoin(Canvas::LineJoin::MITER);
	ctx.strokeStyle(COLOR_WHITE);
	ctx.lineCap(Canvas::LineCap::ROUND);
	ctx.miterLimit(4);
	ctx.lineWidth(2.000000);
  ctx.save();
	ctx.translate(197.5, 47.5);
  ctx.rotate(-0.75 * M_PI + 1.5 * M_PI * (*osc.noiseLvL));
	ctx.moveTo(0, 0);
	ctx.lineTo(0, -10.5);
  ctx.restore();
	ctx.stroke();
	
// #NOISE_DIAL_BG
	ctx.beginPath();
	ctx.strokeStyle(COLOR_GRAY70);
	ctx.lineWidth(1.000000);
	ctx.moveTo(180.876400, 64.114053);
	ctx.lineTo(187.240360, 57.750093);
	ctx.moveTo(197.500000, 24.000001);
	ctx.lineTo(197.500000, 33.000001);
	ctx.moveTo(214.110260, 64.119578);
	ctx.lineTo(207.746300, 57.755616);
	ctx.moveTo(214.378420, 57.247816);
	ctx.lineTo(210.048300, 54.747817);
	ctx.moveTo(216.327050, 52.546073);
	ctx.lineTo(211.497430, 51.251978);
	ctx.moveTo(216.992380, 47.500195);
	ctx.lineTo(211.992390, 47.500195);
	ctx.moveTo(216.329070, 42.454051);
	ctx.lineTo(211.499450, 43.748146);
	ctx.moveTo(214.382330, 37.751528);
	ctx.lineTo(210.052200, 40.251527);
	ctx.moveTo(211.284810, 33.713093);
	ctx.lineTo(207.749280, 37.248627);
	ctx.moveTo(207.247620, 30.613961);
	ctx.lineTo(204.747620, 34.944087);
	ctx.moveTo(202.545880, 28.665331);
	ctx.lineTo(201.251780, 33.494960);
	ctx.moveTo(192.453860, 28.663310);
	ctx.lineTo(193.747950, 33.492938);
	ctx.moveTo(183.712900, 33.707570);
	ctx.lineTo(187.248430, 37.243103);
	ctx.moveTo(178.665140, 42.446507);
	ctx.lineTo(183.494760, 43.740602);
	ctx.moveTo(178.663110, 52.538529);
	ctx.lineTo(183.492740, 51.244433);
	ctx.moveTo(180.609860, 57.241052);
	ctx.lineTo(184.939990, 54.741052);
	ctx.moveTo(177.999810, 47.492384);
	ctx.lineTo(182.999800, 47.492384);
	ctx.moveTo(180.613770, 37.744763);
	ctx.lineTo(184.943890, 40.244763);
	ctx.moveTo(187.751330, 30.610055);
	ctx.lineTo(190.251330, 34.940182);
	ctx.stroke();
	
// #FILTER_G
	
// #FILTER_BOX
	ctx.beginPath();
	ctx.strokeStyle(COLOR_GRAY60);
	ctx.lineWidth(2.000000);
	ctx.rect(241.000000, 16.000000, 63.000000, 63.000000);
	ctx.stroke();
	
// #FILTER_RING
	ctx.save();
	ctx.beginPath();
	ctx.transform(-0.707180, 0.707033, -0.707180, -0.707033, 0.000000, 0.000000);
	ctx.strokeStyle(*osc.filterSwitch ? COLOR_GRAY70 : COLOR_GRAY60);
	ctx.miterLimit(4);
	ctx.lineWidth(1.000000);
	ctx.moveTo(-136.735470, -232.384740);
	ctx.translate(-158.881791, -226.450656);
	ctx.rotate(0.000000);
	ctx.scale(1.000000, 1.000000);
	ctx.arc(0.000000, 0.000000, 22.927557, -0.261799, 1.04719745, 0);
	ctx.scale(1.000000, 1.000000);
	ctx.rotate(-0.000000);
	ctx.translate(158.881791, 226.450656);
	ctx.translate(-158.881792, -226.450655);
	ctx.rotate(0.000000);
	ctx.scale(1.000000, 1.000000);
	ctx.arc(0.000000, 0.000000, 22.927557, 1.047197, 2.35619427, 0);
	ctx.scale(1.000000, 1.000000);
	ctx.rotate(-0.000000);
	ctx.translate(158.881792, 226.450655);
	ctx.translate(-158.881792, -226.450654);
	ctx.rotate(0.000000);
	ctx.scale(1.000000, 1.000000);
	ctx.arc(0.000000, 0.000000, 22.927557, 2.356194, 3.66519131, 0);
	ctx.scale(1.000000, 1.000000);
	ctx.rotate(-0.000000);
	ctx.translate(158.881792, 226.450654);
	ctx.translate(-158.881793, -226.450652);
	ctx.rotate(0.000000);
	ctx.scale(1.000000, 1.000000);
	ctx.arc(0.000000, 0.000000, 22.927557, -2.617994, -1.30899673, 0);
	ctx.scale(1.000000, 1.000000);
	ctx.rotate(-0.000000);
	ctx.translate(158.881793, 226.450652);
	ctx.stroke();
	ctx.restore();
	
// #FILTER_MARKER
  ctx.save();
	ctx.beginPath();
	ctx.fillStyle(*osc.filterSwitch ? COLOR_GREEN : COLOR_GRAY60);
	ctx.translate(272.5, 47.5);
  ctx.rotate(-0.75 * M_PI + 1.5 * M_PI * (*osc.cutoff - 5) / 5000);
  ctx.circle(0, -22.5, 3);
	ctx.fill();
  ctx.restore();
	
// #FILTER_BG_TXT
	ctx.lineWidth(1.000000);
  ctx.fillStyle(COLOR_GRAY60);
	ctx.font(FONT_NORM);
	ctx.font(15);
  ctx.textAlign(TextAlign::Center, TextAlign::Middle);
	ctx.fillText("FILTER", 272.5, 47.5);

}

void SimpleDrumsScreen::drawKbd(NanoCanvas::Canvas &ctx) {
  using namespace drawing;
// #KEYBOARD
	ctx.save();
	ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, 18.000000, 0.000000);

  uint ki = module->currentVoiceIdx;

  ctx.strokeStyle(COLOR_GRAY60);
  ctx.lineJoin(Canvas::LineJoin::ROUND);
  ctx.lineWidth(1);

  // WHITE KEYS
  {
    const static uint KEY_NUMS[14] = {0,2,4,5,7,9,11,12,14,16,17,19,21,23};
    for (uint i = 0; i < 14; i++) {
      ctx.beginPath();
      ctx.fillStyle(ki == KEY_NUMS[i] ? COLOR_GRAY60 : COLOR_BLACK);
      ctx.rect(15.75 + 18 * i, 165.75, 18.5, 58.5);
      ctx.stroke();
      ctx.fill();
    }
  }

  // BLACK KEYS
  {
    const static uint KEY_POS[10]  = {0,1,3,4, 5, 7, 8,10,11,12};
    const static uint KEY_NUMS[10] = {1,3,6,8,10,13,15,18,20,22};
    for (uint i = 0; i < 10; i++) {
      ctx.beginPath();
      ctx.fillStyle(ki == KEY_NUMS[i] ? COLOR_GRAY60 : COLOR_BLACK);
      ctx.rect(29.75 + 18 * KEY_POS[i], 165.75, 8.5, 33.5);
      ctx.fill();
      ctx.stroke();
    }
  }
	ctx.restore();
}
