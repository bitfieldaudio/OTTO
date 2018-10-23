/* ------------------------------------------------------------
name: "hammond"
Code generated with Faust 2.10.0 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faust_hammond_H__
#define  __faust_hammond_H__

#include <math.h>
#include <algorithm>

#include <faust/gui/UI.h>
#include <faust/gui/meta.h>
#include <faust/dsp/dsp.h>

using std::max;
using std::min;

/********************************
	VECTOR INTRINSICS
*********************************/


/********************************
	ABSTRACT USER INTERFACE
*********************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>


class faust_hammondSIG0 {
	
  private:
	
	int iRec3[2];
	
  public:
	
	int getNumInputsfaust_hammondSIG0() {
		return 0;
		
	}
	int getNumOutputsfaust_hammondSIG0() {
		return 1;
		
	}
	int getInputRatefaust_hammondSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatefaust_hammondSIG0(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	void instanceInitfaust_hammondSIG0(int samplingFreq) {
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec3[l2] = 0;
			
		}
		
	}
	
	void fillfaust_hammondSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec3[0] = (iRec3[1] + 1);
			output[i] = std::sin((9.58738019e-05f * float((iRec3[0] + -1))));
			iRec3[1] = iRec3[0];
			
		}
		
	}
};

faust_hammondSIG0* newfaust_hammondSIG0() { return (faust_hammondSIG0*)new faust_hammondSIG0(); }
void deletefaust_hammondSIG0(faust_hammondSIG0* dsp) { delete dsp; }

static float ftbl0faust_hammondSIG0[65536];
static float faust_hammond_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_hammond
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faust_hammond : public dsp {
	
 private:
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fHslider0;
	float fConst4;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider1;
	int iRec1[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fRec0[2];
	float fConst5;
	FAUSTFLOAT fHslider5;
	float fRec4[2];
	FAUSTFLOAT fHslider6;
	float fRec5[2];
	float fConst6;
	float fRec6[2];
	FAUSTFLOAT fHslider7;
	float fRec7[2];
	float fConst7;
	float fRec8[2];
	FAUSTFLOAT fHslider8;
	float fRec9[2];
	float fConst8;
	float fRec10[2];
	float fConst9;
	float fConst10;
	float fConst11;
	float fRec2[3];
	FAUSTFLOAT fHslider9;
	float fRec11[2];
	float fConst12;
	float fRec12[2];
	float fConst13;
	float fConst14;
	float fRec13[2];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fButton1;
	int iRec15[2];
	float fRec14[2];
	FAUSTFLOAT fHslider11;
	float fRec17[2];
	float fRec18[2];
	float fRec19[2];
	float fRec20[2];
	float fRec16[3];
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fButton2;
	int iRec22[2];
	float fRec21[2];
	FAUSTFLOAT fHslider13;
	float fRec24[2];
	float fRec25[2];
	float fRec26[2];
	float fRec27[2];
	float fRec23[3];
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fButton3;
	int iRec29[2];
	float fRec28[2];
	FAUSTFLOAT fHslider15;
	float fRec31[2];
	float fRec32[2];
	float fRec33[2];
	float fRec34[2];
	float fRec30[3];
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fButton4;
	int iRec36[2];
	float fRec35[2];
	FAUSTFLOAT fHslider17;
	float fRec38[2];
	float fRec39[2];
	float fRec40[2];
	float fRec41[2];
	float fRec37[3];
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fButton5;
	int iRec43[2];
	float fRec42[2];
	FAUSTFLOAT fHslider19;
	float fRec45[2];
	float fRec46[2];
	float fRec47[2];
	float fRec48[2];
	float fRec44[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "hammond");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "hammond");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		faust_hammondSIG0* sig0 = newfaust_hammondSIG0();
		sig0->instanceInitfaust_hammondSIG0(samplingFreq);
		sig0->fillfaust_hammondSIG0(65536, ftbl0faust_hammondSIG0);
		deletefaust_hammondSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min(192000.0f, std::max(1.0f, float(fSamplingFreq)));
		fConst1 = std::tan((6283.18555f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / (((fConst2 + 1.41421354f) / fConst1) + 1.0f));
		fConst4 = (6.90999985f / fConst0);
		fConst5 = (1.0f / fConst0);
		fConst6 = (0.5f / fConst0);
		fConst7 = (1.33483982f / fConst0);
		fConst8 = (2.0f / fConst0);
		fConst9 = (((fConst2 + -1.41421354f) / fConst1) + 1.0f);
		fConst10 = (1.0f / faust_hammond_faustpower2_f(fConst1));
		fConst11 = (2.0f * (1.0f - fConst10));
		fConst12 = (7.0f / fConst0);
		fConst13 = (2.0f * (0.0f - fConst10));
		fConst14 = (3.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.001f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(1.0f);
		fHslider5 = FAUSTFLOAT(440.0f);
		fHslider6 = FAUSTFLOAT(0.5f);
		fHslider7 = FAUSTFLOAT(0.5f);
		fHslider8 = FAUSTFLOAT(0.5f);
		fHslider9 = FAUSTFLOAT(0.5f);
		fHslider10 = FAUSTFLOAT(1.0f);
		fButton1 = FAUSTFLOAT(0.0f);
		fHslider11 = FAUSTFLOAT(440.0f);
		fHslider12 = FAUSTFLOAT(1.0f);
		fButton2 = FAUSTFLOAT(0.0f);
		fHslider13 = FAUSTFLOAT(440.0f);
		fHslider14 = FAUSTFLOAT(1.0f);
		fButton3 = FAUSTFLOAT(0.0f);
		fHslider15 = FAUSTFLOAT(440.0f);
		fHslider16 = FAUSTFLOAT(1.0f);
		fButton4 = FAUSTFLOAT(0.0f);
		fHslider17 = FAUSTFLOAT(440.0f);
		fHslider18 = FAUSTFLOAT(1.0f);
		fButton5 = FAUSTFLOAT(0.0f);
		fHslider19 = FAUSTFLOAT(440.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec1[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec8[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec9[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec10[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec2[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec11[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec12[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec13[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			iRec15[l14] = 0;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec14[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec17[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec18[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec19[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec20[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec16[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			iRec22[l21] = 0;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec21[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec24[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec25[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec26[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec27[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec23[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			iRec29[l28] = 0;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec28[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec31[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec32[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec33[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec34[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec30[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			iRec36[l35] = 0;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec35[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec38[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec39[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec40[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec41[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec37[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			iRec43[l42] = 0;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec42[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec45[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec46[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec47[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec48[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec44[l48] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual faust_hammond* clone() {
		return new faust_hammond();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("hammond");
		ui_interface->addHorizontalSlider("drawbar1", &fHslider6, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("drawbar2", &fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("drawbar3", &fHslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fHslider2, 0.00100000005f, 0.00100000005f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Decay", &fHslider3, 0.0f, 0.0f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Release", &fHslider1, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Sustain", &fHslider4, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("leslie", &fHslider9, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider5, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton0);
		ui_interface->addHorizontalSlider("velocity", &fHslider0, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider13, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton2);
		ui_interface->addHorizontalSlider("velocity", &fHslider12, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider17, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton4);
		ui_interface->addHorizontalSlider("velocity", &fHslider16, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider11, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton1);
		ui_interface->addHorizontalSlider("velocity", &fHslider10, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider15, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton3);
		ui_interface->addHorizontalSlider("velocity", &fHslider14, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider19, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton5);
		ui_interface->addHorizontalSlider("velocity", &fHslider18, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		int iSlow1 = (float(fButton0) > 0.0f);
		float fSlow2 = float(fHslider1);
		float fSlow3 = float(fHslider2);
		int iSlow4 = int((fConst0 * fSlow3));
		float fSlow5 = float(fHslider3);
		float fSlow6 = (6.90999985f * fSlow3);
		float fSlow7 = float(fHslider4);
		float fSlow8 = (float(iSlow1) * fSlow7);
		float fSlow9 = float(fHslider5);
		float fSlow10 = (fConst5 * fSlow9);
		float fSlow11 = (0.00100000005f * float(fHslider6));
		float fSlow12 = (fConst6 * fSlow9);
		float fSlow13 = (0.00100000005f * float(fHslider7));
		float fSlow14 = (fConst7 * fSlow9);
		float fSlow15 = (0.00100000005f * float(fHslider8));
		float fSlow16 = (fConst8 * fSlow9);
		float fSlow17 = (0.00100000005f * float(fHslider9));
		float fSlow18 = float(fHslider10);
		int iSlow19 = (float(fButton1) > 0.0f);
		float fSlow20 = (float(iSlow19) * fSlow7);
		float fSlow21 = float(fHslider11);
		float fSlow22 = (fConst5 * fSlow21);
		float fSlow23 = (fConst6 * fSlow21);
		float fSlow24 = (fConst7 * fSlow21);
		float fSlow25 = (fConst8 * fSlow21);
		float fSlow26 = float(fHslider12);
		int iSlow27 = (float(fButton2) > 0.0f);
		float fSlow28 = (float(iSlow27) * fSlow7);
		float fSlow29 = float(fHslider13);
		float fSlow30 = (fConst5 * fSlow29);
		float fSlow31 = (fConst6 * fSlow29);
		float fSlow32 = (fConst7 * fSlow29);
		float fSlow33 = (fConst8 * fSlow29);
		float fSlow34 = float(fHslider14);
		int iSlow35 = (float(fButton3) > 0.0f);
		float fSlow36 = (float(iSlow35) * fSlow7);
		float fSlow37 = float(fHslider15);
		float fSlow38 = (fConst5 * fSlow37);
		float fSlow39 = (fConst6 * fSlow37);
		float fSlow40 = (fConst7 * fSlow37);
		float fSlow41 = (fConst8 * fSlow37);
		float fSlow42 = float(fHslider16);
		int iSlow43 = (float(fButton4) > 0.0f);
		float fSlow44 = (float(iSlow43) * fSlow7);
		float fSlow45 = float(fHslider17);
		float fSlow46 = (fConst5 * fSlow45);
		float fSlow47 = (fConst6 * fSlow45);
		float fSlow48 = (fConst7 * fSlow45);
		float fSlow49 = (fConst8 * fSlow45);
		float fSlow50 = float(fHslider18);
		int iSlow51 = (float(fButton5) > 0.0f);
		float fSlow52 = (float(iSlow51) * fSlow7);
		float fSlow53 = float(fHslider19);
		float fSlow54 = (fConst5 * fSlow53);
		float fSlow55 = (fConst6 * fSlow53);
		float fSlow56 = (fConst7 * fSlow53);
		float fSlow57 = (fConst8 * fSlow53);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec1[0] = (iSlow1 * (iRec1[1] + 1));
			int iTemp0 = (iRec1[0] < iSlow4);
			float fTemp1 = std::exp((0.0f - (fConst4 / (iSlow1?(iTemp0?fSlow6:fSlow5):fSlow2))));
			fRec0[0] = ((fRec0[1] * fTemp1) + ((iSlow1?(iTemp0?1.58730161f:fSlow8):0.0f) * (1.0f - fTemp1)));
			fRec4[0] = (fSlow10 + (fRec4[1] - std::floor((fSlow10 + fRec4[1]))));
			fRec5[0] = (fSlow11 + (0.999000013f * fRec5[1]));
			fRec6[0] = (fSlow12 + (fRec6[1] - std::floor((fSlow12 + fRec6[1]))));
			fRec7[0] = (fSlow13 + (0.999000013f * fRec7[1]));
			fRec8[0] = (fSlow14 + (fRec8[1] - std::floor((fSlow14 + fRec8[1]))));
			fRec9[0] = (fSlow15 + (0.999000013f * fRec9[1]));
			fRec10[0] = (fSlow16 + (fRec10[1] - std::floor((fSlow16 + fRec10[1]))));
			fRec2[0] = ((0.5f * (((ftbl0faust_hammondSIG0[int((65536.0f * fRec4[0]))] + (fRec5[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec6[0]))])) + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec8[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec10[0]))]))) - (fConst3 * ((fConst9 * fRec2[2]) + (fConst11 * fRec2[1]))));
			fRec11[0] = (fSlow17 + (0.999000013f * fRec11[1]));
			float fTemp2 = (fRec12[1] + (fConst12 * fRec11[0]));
			fRec12[0] = (fTemp2 - std::floor(fTemp2));
			float fTemp3 = ((0.5f * (fRec11[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec12[0]))])) + 1.0f);
			float fTemp4 = (fRec13[1] + (fConst14 * fRec11[0]));
			fRec13[0] = (fTemp4 - std::floor(fTemp4));
			float fTemp5 = ((0.5f * (fRec11[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec13[0]))])) + 1.0f);
			iRec15[0] = (iSlow19 * (iRec15[1] + 1));
			int iTemp6 = (iRec15[0] < iSlow4);
			float fTemp7 = std::exp((0.0f - (fConst4 / (iSlow19?(iTemp6?fSlow6:fSlow5):fSlow2))));
			fRec14[0] = ((fRec14[1] * fTemp7) + ((iSlow19?(iTemp6?1.58730161f:fSlow20):0.0f) * (1.0f - fTemp7)));
			fRec17[0] = (fSlow22 + (fRec17[1] - std::floor((fSlow22 + fRec17[1]))));
			fRec18[0] = (fSlow23 + (fRec18[1] - std::floor((fSlow23 + fRec18[1]))));
			fRec19[0] = (fSlow24 + (fRec19[1] - std::floor((fSlow24 + fRec19[1]))));
			fRec20[0] = (fSlow25 + (fRec20[1] - std::floor((fSlow25 + fRec20[1]))));
			fRec16[0] = ((0.5f * (((ftbl0faust_hammondSIG0[int((65536.0f * fRec17[0]))] + (fRec5[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec18[0]))])) + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec19[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec20[0]))]))) - (fConst3 * ((fConst9 * fRec16[2]) + (fConst11 * fRec16[1]))));
			iRec22[0] = (iSlow27 * (iRec22[1] + 1));
			int iTemp8 = (iRec22[0] < iSlow4);
			float fTemp9 = std::exp((0.0f - (fConst4 / (iSlow27?(iTemp8?fSlow6:fSlow5):fSlow2))));
			fRec21[0] = ((fRec21[1] * fTemp9) + ((iSlow27?(iTemp8?1.58730161f:fSlow28):0.0f) * (1.0f - fTemp9)));
			fRec24[0] = (fSlow30 + (fRec24[1] - std::floor((fSlow30 + fRec24[1]))));
			fRec25[0] = (fSlow31 + (fRec25[1] - std::floor((fSlow31 + fRec25[1]))));
			fRec26[0] = (fSlow32 + (fRec26[1] - std::floor((fSlow32 + fRec26[1]))));
			fRec27[0] = (fSlow33 + (fRec27[1] - std::floor((fSlow33 + fRec27[1]))));
			fRec23[0] = ((0.5f * (((ftbl0faust_hammondSIG0[int((65536.0f * fRec24[0]))] + (fRec5[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec25[0]))])) + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec26[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec27[0]))]))) - (fConst3 * ((fConst9 * fRec23[2]) + (fConst11 * fRec23[1]))));
			iRec29[0] = (iSlow35 * (iRec29[1] + 1));
			int iTemp10 = (iRec29[0] < iSlow4);
			float fTemp11 = std::exp((0.0f - (fConst4 / (iSlow35?(iTemp10?fSlow6:fSlow5):fSlow2))));
			fRec28[0] = ((fRec28[1] * fTemp11) + ((iSlow35?(iTemp10?1.58730161f:fSlow36):0.0f) * (1.0f - fTemp11)));
			fRec31[0] = (fSlow38 + (fRec31[1] - std::floor((fSlow38 + fRec31[1]))));
			fRec32[0] = (fSlow39 + (fRec32[1] - std::floor((fSlow39 + fRec32[1]))));
			fRec33[0] = (fSlow40 + (fRec33[1] - std::floor((fSlow40 + fRec33[1]))));
			fRec34[0] = (fSlow41 + (fRec34[1] - std::floor((fSlow41 + fRec34[1]))));
			fRec30[0] = ((0.5f * (((ftbl0faust_hammondSIG0[int((65536.0f * fRec31[0]))] + (fRec5[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec32[0]))])) + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec33[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec34[0]))]))) - (fConst3 * ((fConst9 * fRec30[2]) + (fConst11 * fRec30[1]))));
			iRec36[0] = (iSlow43 * (iRec36[1] + 1));
			int iTemp12 = (iRec36[0] < iSlow4);
			float fTemp13 = std::exp((0.0f - (fConst4 / (iSlow43?(iTemp12?fSlow6:fSlow5):fSlow2))));
			fRec35[0] = ((fRec35[1] * fTemp13) + ((iSlow43?(iTemp12?1.58730161f:fSlow44):0.0f) * (1.0f - fTemp13)));
			fRec38[0] = (fSlow46 + (fRec38[1] - std::floor((fSlow46 + fRec38[1]))));
			fRec39[0] = (fSlow47 + (fRec39[1] - std::floor((fSlow47 + fRec39[1]))));
			fRec40[0] = (fSlow48 + (fRec40[1] - std::floor((fSlow48 + fRec40[1]))));
			fRec41[0] = (fSlow49 + (fRec41[1] - std::floor((fSlow49 + fRec41[1]))));
			fRec37[0] = ((0.5f * (((ftbl0faust_hammondSIG0[int((65536.0f * fRec38[0]))] + (fRec5[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec39[0]))])) + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec40[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec41[0]))]))) - (fConst3 * ((fConst9 * fRec37[2]) + (fConst11 * fRec37[1]))));
			iRec43[0] = (iSlow51 * (iRec43[1] + 1));
			int iTemp14 = (iRec43[0] < iSlow4);
			float fTemp15 = std::exp((0.0f - (fConst4 / (iSlow51?(iTemp14?fSlow6:fSlow5):fSlow2))));
			fRec42[0] = ((fRec42[1] * fTemp15) + ((iSlow51?(iTemp14?1.58730161f:fSlow52):0.0f) * (1.0f - fTemp15)));
			fRec45[0] = (fSlow54 + (fRec45[1] - std::floor((fSlow54 + fRec45[1]))));
			fRec46[0] = (fSlow55 + (fRec46[1] - std::floor((fSlow55 + fRec46[1]))));
			fRec47[0] = (fSlow56 + (fRec47[1] - std::floor((fSlow56 + fRec47[1]))));
			fRec48[0] = (fSlow57 + (fRec48[1] - std::floor((fSlow57 + fRec48[1]))));
			fRec44[0] = ((0.5f * (((ftbl0faust_hammondSIG0[int((65536.0f * fRec45[0]))] + (fRec5[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec46[0]))])) + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec47[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec48[0]))]))) - (fConst3 * ((fConst9 * fRec44[2]) + (fConst11 * fRec44[1]))));
			output0[i] = FAUSTFLOAT((fConst3 * ((((((fSlow0 * (std::min(1.0f, fRec0[0]) * (((fRec2[2] + (fRec2[0] + (2.0f * fRec2[1]))) * fTemp3) + ((((fConst10 * fRec2[0]) + (fConst13 * fRec2[1])) + (fConst10 * fRec2[2])) * fTemp5)))) + (fSlow18 * (std::min(1.0f, fRec14[0]) * ((fTemp3 * (fRec16[2] + (fRec16[0] + (2.0f * fRec16[1])))) + (fTemp5 * (((fConst10 * fRec16[0]) + (fConst13 * fRec16[1])) + (fConst10 * fRec16[2]))))))) + (fSlow26 * (std::min(1.0f, fRec21[0]) * ((fTemp3 * (fRec23[2] + (fRec23[0] + (2.0f * fRec23[1])))) + (fTemp5 * (((fConst10 * fRec23[0]) + (fConst13 * fRec23[1])) + (fConst10 * fRec23[2]))))))) + (fSlow34 * (std::min(1.0f, fRec28[0]) * ((fTemp3 * (fRec30[2] + (fRec30[0] + (2.0f * fRec30[1])))) + (fTemp5 * (((fConst10 * fRec30[0]) + (fConst13 * fRec30[1])) + (fConst10 * fRec30[2]))))))) + (fSlow42 * (std::min(1.0f, fRec35[0]) * ((fTemp3 * (fRec37[2] + (fRec37[0] + (2.0f * fRec37[1])))) + (fTemp5 * (((fConst10 * fRec37[0]) + (fConst13 * fRec37[1])) + (fConst10 * fRec37[2]))))))) + (fSlow50 * (std::min(1.0f, fRec42[0]) * ((fTemp3 * (fRec44[2] + (fRec44[0] + (2.0f * fRec44[1])))) + (fTemp5 * (((fConst10 * fRec44[0]) + (fConst13 * fRec44[1])) + (fConst10 * fRec44[2])))))))));
			iRec1[1] = iRec1[0];
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			iRec15[1] = iRec15[0];
			fRec14[1] = fRec14[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			iRec22[1] = iRec22[0];
			fRec21[1] = fRec21[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			iRec29[1] = iRec29[0];
			fRec28[1] = fRec28[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			iRec36[1] = iRec36[0];
			fRec35[1] = fRec35[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec40[1] = fRec40[0];
			fRec41[1] = fRec41[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			iRec43[1] = iRec43[0];
			fRec42[1] = fRec42[0];
			fRec45[1] = fRec45[0];
			fRec46[1] = fRec46[0];
			fRec47[1] = fRec47[0];
			fRec48[1] = fRec48[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			
		}
		
	}

	
};

#endif
