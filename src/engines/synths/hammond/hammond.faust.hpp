/* ------------------------------------------------------------
name: "hammond"
Code generated with Faust 2.11.10 (https://faust.grame.fr)
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
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iRec3[l3] = 0;
			
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
	float fVec0[2];
	FAUSTFLOAT fHslider1;
	int iRec1[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fRec0[2];
	float fConst5;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fRec5[2];
	float fConst6;
	float fRec6[2];
	float fRec4[2];
	FAUSTFLOAT fHslider7;
	float fRec7[2];
	float fConst7;
	float fRec8[2];
	FAUSTFLOAT fHslider8;
	float fRec9[2];
	float fConst8;
	float fRec10[2];
	FAUSTFLOAT fHslider9;
	float fRec11[2];
	float fConst9;
	float fRec12[2];
	float fConst10;
	float fConst11;
	float fRec13[2];
	int iRec15[2];
	float fRec14[4];
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fRec2[3];
	float fConst16;
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fButton1;
	float fVec1[2];
	int iRec17[2];
	float fRec16[2];
	FAUSTFLOAT fHslider11;
	float fRec19[2];
	float fRec20[2];
	float fRec21[2];
	float fRec22[2];
	float fRec23[2];
	float fRec18[3];
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fButton2;
	float fVec2[2];
	int iRec25[2];
	float fRec24[2];
	FAUSTFLOAT fHslider13;
	float fRec27[2];
	float fRec28[2];
	float fRec29[2];
	float fRec30[2];
	float fRec31[2];
	float fRec26[3];
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fButton3;
	float fVec3[2];
	int iRec33[2];
	float fRec32[2];
	FAUSTFLOAT fHslider15;
	float fRec35[2];
	float fRec36[2];
	float fRec37[2];
	float fRec38[2];
	float fRec39[2];
	float fRec34[3];
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fButton4;
	float fVec4[2];
	int iRec41[2];
	float fRec40[2];
	FAUSTFLOAT fHslider17;
	float fRec43[2];
	float fRec44[2];
	float fRec45[2];
	float fRec46[2];
	float fRec47[2];
	float fRec42[3];
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fButton5;
	float fVec5[2];
	int iRec49[2];
	float fRec48[2];
	FAUSTFLOAT fHslider19;
	float fRec51[2];
	float fRec52[2];
	float fRec53[2];
	float fRec54[2];
	float fRec55[2];
	float fRec50[3];
	
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
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
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
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = std::tan((5654.8667f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / (((fConst2 + 1.41421354f) / fConst1) + 1.0f));
		fConst4 = (6.90999985f / fConst0);
		fConst5 = (1.0f / fConst0);
		fConst6 = (10.0f / fConst0);
		fConst7 = (0.5f / fConst0);
		fConst8 = (1.33483982f / fConst0);
		fConst9 = (2.0f / fConst0);
		fConst10 = (2.5f / fConst0);
		fConst11 = (0.0199999996f * fConst0);
		fConst12 = (((fConst2 + -1.41421354f) / fConst1) + 1.0f);
		fConst13 = faust_hammond_faustpower2_f(fConst1);
		fConst14 = (1.0f / fConst13);
		fConst15 = (2.0f * (1.0f - fConst14));
		fConst16 = (0.0f - (2.0f / fConst13));
		
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
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec1[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec4[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec8[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec9[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec10[l10] = 0.0f;
			
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
		for (int l15 = 0; (l15 < 4); l15 = (l15 + 1)) {
			fRec14[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
			fRec2[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec1[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			iRec17[l18] = 0;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec16[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec19[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec20[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec21[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec22[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec23[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec18[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fVec2[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			iRec25[l27] = 0;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec24[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec27[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec28[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec29[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec30[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec31[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec26[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec3[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			iRec33[l36] = 0;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec32[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec35[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec36[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec37[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec38[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec39[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec34[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fVec4[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			iRec41[l45] = 0;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec40[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec43[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec44[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec45[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec46[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec47[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec42[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fVec5[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			iRec49[l54] = 0;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec48[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec51[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec52[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec53[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec54[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec55[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec50[l61] = 0.0f;
			
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
		ui_interface->addHorizontalSlider("drawbar1", &fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("drawbar2", &fHslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("drawbar3", &fHslider9, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fHslider2, 0.00100000005f, 0.00100000005f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Decay", &fHslider3, 0.0f, 0.0f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Release", &fHslider1, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Sustain", &fHslider4, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("leslie", &fHslider6, 0.5f, 0.0f, 1.0f, 0.00999999978f);
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
		float fSlow1 = float(fButton0);
		int iSlow2 = (fSlow1 > 0.0f);
		float fSlow3 = float(fHslider1);
		float fSlow4 = float(fHslider2);
		int iSlow5 = int((fConst0 * fSlow4));
		float fSlow6 = float(fHslider3);
		float fSlow7 = (6.90999985f * fSlow4);
		float fSlow8 = float(fHslider4);
		float fSlow9 = (float(iSlow2) * fSlow8);
		float fSlow10 = float(fHslider5);
		float fSlow11 = (fConst5 * fSlow10);
		float fSlow12 = (0.00100000005f * float(fHslider6));
		float fSlow13 = (0.00100000005f * float(fHslider7));
		float fSlow14 = (fConst7 * fSlow10);
		float fSlow15 = (0.00100000005f * float(fHslider8));
		float fSlow16 = (fConst8 * fSlow10);
		float fSlow17 = (0.00100000005f * float(fHslider9));
		float fSlow18 = (fConst9 * fSlow10);
		float fSlow19 = float(fHslider10);
		float fSlow20 = float(fButton1);
		int iSlow21 = (fSlow20 > 0.0f);
		float fSlow22 = (float(iSlow21) * fSlow8);
		float fSlow23 = float(fHslider11);
		float fSlow24 = (fConst5 * fSlow23);
		float fSlow25 = (fConst7 * fSlow23);
		float fSlow26 = (fConst8 * fSlow23);
		float fSlow27 = (fConst9 * fSlow23);
		float fSlow28 = float(fHslider12);
		float fSlow29 = float(fButton2);
		int iSlow30 = (fSlow29 > 0.0f);
		float fSlow31 = (float(iSlow30) * fSlow8);
		float fSlow32 = float(fHslider13);
		float fSlow33 = (fConst5 * fSlow32);
		float fSlow34 = (fConst7 * fSlow32);
		float fSlow35 = (fConst8 * fSlow32);
		float fSlow36 = (fConst9 * fSlow32);
		float fSlow37 = float(fHslider14);
		float fSlow38 = float(fButton3);
		int iSlow39 = (fSlow38 > 0.0f);
		float fSlow40 = (float(iSlow39) * fSlow8);
		float fSlow41 = float(fHslider15);
		float fSlow42 = (fConst5 * fSlow41);
		float fSlow43 = (fConst7 * fSlow41);
		float fSlow44 = (fConst8 * fSlow41);
		float fSlow45 = (fConst9 * fSlow41);
		float fSlow46 = float(fHslider16);
		float fSlow47 = float(fButton4);
		int iSlow48 = (fSlow47 > 0.0f);
		float fSlow49 = (float(iSlow48) * fSlow8);
		float fSlow50 = float(fHslider17);
		float fSlow51 = (fConst5 * fSlow50);
		float fSlow52 = (fConst7 * fSlow50);
		float fSlow53 = (fConst8 * fSlow50);
		float fSlow54 = (fConst9 * fSlow50);
		float fSlow55 = float(fHslider18);
		float fSlow56 = float(fButton5);
		int iSlow57 = (fSlow56 > 0.0f);
		float fSlow58 = (float(iSlow57) * fSlow8);
		float fSlow59 = float(fHslider19);
		float fSlow60 = (fConst5 * fSlow59);
		float fSlow61 = (fConst7 * fSlow59);
		float fSlow62 = (fConst8 * fSlow59);
		float fSlow63 = (fConst9 * fSlow59);
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[0] = fSlow1;
			iRec1[0] = (iSlow2 * (iRec1[1] + 1));
			int iTemp0 = (iRec1[0] < iSlow5);
			float fTemp1 = std::exp((0.0f - (fConst4 / (iSlow2?(iTemp0?fSlow7:fSlow6):fSlow3))));
			fRec0[0] = ((fRec0[1] * fTemp1) + ((iSlow2?(iTemp0?1.58730161f:fSlow9):0.0f) * (1.0f - fTemp1)));
			fRec5[0] = (fSlow12 + (0.999000013f * fRec5[1]));
			float fTemp2 = (fRec6[1] + (fConst6 * fRec5[0]));
			fRec6[0] = (fTemp2 - std::floor(fTemp2));
			float fTemp3 = (fRec5[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec6[0]))]);
			float fTemp4 = ((0.0199999996f * fTemp3) + 1.0f);
			float fTemp5 = (fRec4[1] + (fSlow11 * fTemp4));
			fRec4[0] = (fTemp5 - std::floor(fTemp5));
			fRec7[0] = (fSlow13 + (0.999000013f * fRec7[1]));
			fRec8[0] = (fSlow14 + (fRec8[1] - std::floor((fSlow14 + fRec8[1]))));
			fRec9[0] = (fSlow15 + (0.999000013f * fRec9[1]));
			float fTemp6 = (fRec10[1] + (fSlow16 * fTemp4));
			fRec10[0] = (fTemp6 - std::floor(fTemp6));
			fRec11[0] = (fSlow17 + (0.999000013f * fRec11[1]));
			float fTemp7 = (fRec12[1] + (fSlow18 * fTemp4));
			fRec12[0] = (fTemp7 - std::floor(fTemp7));
			fRec13[0] = ((((fSlow1 - fVec0[1]) > 0.0f) > 0)?fConst11:std::max<float>(0.0f, (fRec13[1] + -1.0f)));
			iRec15[0] = ((1103515245 * iRec15[1]) + 12345);
			fRec14[0] = (((0.522189379f * fRec14[3]) + ((4.65661287e-10f * float(iRec15[0])) + (2.49495602f * fRec14[1]))) - (2.0172658f * fRec14[2]));
			float fTemp8 = (((0.0499220341f * fRec14[0]) + (0.0506126992f * fRec14[2])) - ((0.0959935337f * fRec14[1]) + (0.00440878607f * fRec14[3])));
			fRec2[0] = ((0.5f * ((((ftbl0faust_hammondSIG0[int((65536.0f * fRec4[0]))] + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec8[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec10[0]))])) + (fRec11[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec12[0]))])) + (fConst10 * ((fRec5[0] * fRec13[0]) * fTemp8)))) - (fConst3 * ((fConst12 * fRec2[2]) + (fConst15 * fRec2[1]))));
			float fTemp9 = ((0.5f * fTemp3) + 1.0f);
			fVec1[0] = fSlow20;
			iRec17[0] = (iSlow21 * (iRec17[1] + 1));
			int iTemp10 = (iRec17[0] < iSlow5);
			float fTemp11 = std::exp((0.0f - (fConst4 / (iSlow21?(iTemp10?fSlow7:fSlow6):fSlow3))));
			fRec16[0] = ((fRec16[1] * fTemp11) + ((iSlow21?(iTemp10?1.58730161f:fSlow22):0.0f) * (1.0f - fTemp11)));
			float fTemp12 = (fRec19[1] + (fSlow24 * fTemp4));
			fRec19[0] = (fTemp12 - std::floor(fTemp12));
			fRec20[0] = (fSlow25 + (fRec20[1] - std::floor((fSlow25 + fRec20[1]))));
			float fTemp13 = (fRec21[1] + (fSlow26 * fTemp4));
			fRec21[0] = (fTemp13 - std::floor(fTemp13));
			float fTemp14 = (fRec22[1] + (fSlow27 * fTemp4));
			fRec22[0] = (fTemp14 - std::floor(fTemp14));
			fRec23[0] = ((((fSlow20 - fVec1[1]) > 0.0f) > 0)?fConst11:std::max<float>(0.0f, (fRec23[1] + -1.0f)));
			fRec18[0] = ((0.5f * ((((ftbl0faust_hammondSIG0[int((65536.0f * fRec19[0]))] + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec20[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec21[0]))])) + (fRec11[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec22[0]))])) + (fConst10 * ((fRec5[0] * fRec23[0]) * fTemp8)))) - (fConst3 * ((fConst12 * fRec18[2]) + (fConst15 * fRec18[1]))));
			fVec2[0] = fSlow29;
			iRec25[0] = (iSlow30 * (iRec25[1] + 1));
			int iTemp15 = (iRec25[0] < iSlow5);
			float fTemp16 = std::exp((0.0f - (fConst4 / (iSlow30?(iTemp15?fSlow7:fSlow6):fSlow3))));
			fRec24[0] = ((fRec24[1] * fTemp16) + ((iSlow30?(iTemp15?1.58730161f:fSlow31):0.0f) * (1.0f - fTemp16)));
			float fTemp17 = (fRec27[1] + (fSlow33 * fTemp4));
			fRec27[0] = (fTemp17 - std::floor(fTemp17));
			fRec28[0] = (fSlow34 + (fRec28[1] - std::floor((fSlow34 + fRec28[1]))));
			float fTemp18 = (fRec29[1] + (fSlow35 * fTemp4));
			fRec29[0] = (fTemp18 - std::floor(fTemp18));
			float fTemp19 = (fRec30[1] + (fSlow36 * fTemp4));
			fRec30[0] = (fTemp19 - std::floor(fTemp19));
			fRec31[0] = ((((fSlow29 - fVec2[1]) > 0.0f) > 0)?fConst11:std::max<float>(0.0f, (fRec31[1] + -1.0f)));
			fRec26[0] = ((0.5f * ((((ftbl0faust_hammondSIG0[int((65536.0f * fRec27[0]))] + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec28[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec29[0]))])) + (fRec11[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec30[0]))])) + (fConst10 * ((fRec5[0] * fRec31[0]) * fTemp8)))) - (fConst3 * ((fConst12 * fRec26[2]) + (fConst15 * fRec26[1]))));
			fVec3[0] = fSlow38;
			iRec33[0] = (iSlow39 * (iRec33[1] + 1));
			int iTemp20 = (iRec33[0] < iSlow5);
			float fTemp21 = std::exp((0.0f - (fConst4 / (iSlow39?(iTemp20?fSlow7:fSlow6):fSlow3))));
			fRec32[0] = ((fRec32[1] * fTemp21) + ((iSlow39?(iTemp20?1.58730161f:fSlow40):0.0f) * (1.0f - fTemp21)));
			float fTemp22 = (fRec35[1] + (fSlow42 * fTemp4));
			fRec35[0] = (fTemp22 - std::floor(fTemp22));
			fRec36[0] = (fSlow43 + (fRec36[1] - std::floor((fSlow43 + fRec36[1]))));
			float fTemp23 = (fRec37[1] + (fSlow44 * fTemp4));
			fRec37[0] = (fTemp23 - std::floor(fTemp23));
			float fTemp24 = (fRec38[1] + (fSlow45 * fTemp4));
			fRec38[0] = (fTemp24 - std::floor(fTemp24));
			fRec39[0] = ((((fSlow38 - fVec3[1]) > 0.0f) > 0)?fConst11:std::max<float>(0.0f, (fRec39[1] + -1.0f)));
			fRec34[0] = ((0.5f * ((((ftbl0faust_hammondSIG0[int((65536.0f * fRec35[0]))] + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec36[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec37[0]))])) + (fRec11[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec38[0]))])) + (fConst10 * ((fRec5[0] * fRec39[0]) * fTemp8)))) - (fConst3 * ((fConst12 * fRec34[2]) + (fConst15 * fRec34[1]))));
			fVec4[0] = fSlow47;
			iRec41[0] = (iSlow48 * (iRec41[1] + 1));
			int iTemp25 = (iRec41[0] < iSlow5);
			float fTemp26 = std::exp((0.0f - (fConst4 / (iSlow48?(iTemp25?fSlow7:fSlow6):fSlow3))));
			fRec40[0] = ((fRec40[1] * fTemp26) + ((iSlow48?(iTemp25?1.58730161f:fSlow49):0.0f) * (1.0f - fTemp26)));
			float fTemp27 = (fRec43[1] + (fSlow51 * fTemp4));
			fRec43[0] = (fTemp27 - std::floor(fTemp27));
			fRec44[0] = (fSlow52 + (fRec44[1] - std::floor((fSlow52 + fRec44[1]))));
			float fTemp28 = (fRec45[1] + (fSlow53 * fTemp4));
			fRec45[0] = (fTemp28 - std::floor(fTemp28));
			float fTemp29 = (fRec46[1] + (fSlow54 * fTemp4));
			fRec46[0] = (fTemp29 - std::floor(fTemp29));
			fRec47[0] = ((((fSlow47 - fVec4[1]) > 0.0f) > 0)?fConst11:std::max<float>(0.0f, (fRec47[1] + -1.0f)));
			fRec42[0] = ((0.5f * ((((ftbl0faust_hammondSIG0[int((65536.0f * fRec43[0]))] + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec44[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec45[0]))])) + (fRec11[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec46[0]))])) + (fConst10 * ((fRec5[0] * fRec47[0]) * fTemp8)))) - (fConst3 * ((fConst12 * fRec42[2]) + (fConst15 * fRec42[1]))));
			fVec5[0] = fSlow56;
			iRec49[0] = (iSlow57 * (iRec49[1] + 1));
			int iTemp30 = (iRec49[0] < iSlow5);
			float fTemp31 = std::exp((0.0f - (fConst4 / (iSlow57?(iTemp30?fSlow7:fSlow6):fSlow3))));
			fRec48[0] = ((fRec48[1] * fTemp31) + ((iSlow57?(iTemp30?1.58730161f:fSlow58):0.0f) * (1.0f - fTemp31)));
			float fTemp32 = (fRec51[1] + (fSlow60 * fTemp4));
			fRec51[0] = (fTemp32 - std::floor(fTemp32));
			fRec52[0] = (fSlow61 + (fRec52[1] - std::floor((fSlow61 + fRec52[1]))));
			float fTemp33 = (fRec53[1] + (fSlow62 * fTemp4));
			fRec53[0] = (fTemp33 - std::floor(fTemp33));
			float fTemp34 = (fRec54[1] + (fSlow63 * fTemp4));
			fRec54[0] = (fTemp34 - std::floor(fTemp34));
			fRec55[0] = ((((fSlow56 - fVec5[1]) > 0.0f) > 0)?fConst11:std::max<float>(0.0f, (fRec55[1] + -1.0f)));
			fRec50[0] = ((0.5f * ((((ftbl0faust_hammondSIG0[int((65536.0f * fRec51[0]))] + (fRec7[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec52[0]))])) + (fRec9[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec53[0]))])) + (fRec11[0] * ftbl0faust_hammondSIG0[int((65536.0f * fRec54[0]))])) + (fConst10 * ((fRec5[0] * fRec55[0]) * fTemp8)))) - (fConst3 * ((fConst12 * fRec50[2]) + (fConst15 * fRec50[1]))));
			output0[i] = FAUSTFLOAT((fConst3 * ((((((fSlow0 * (std::min<float>(1.0f, fRec0[0]) * (((fRec2[2] + (fRec2[0] + (2.0f * fRec2[1]))) * fTemp9) + (((fConst14 * fRec2[0]) + (fConst16 * fRec2[1])) + (fConst14 * fRec2[2]))))) + (fSlow19 * (std::min<float>(1.0f, fRec16[0]) * ((fTemp9 * (fRec18[2] + (fRec18[0] + (2.0f * fRec18[1])))) + (((fConst14 * fRec18[0]) + (fConst16 * fRec18[1])) + (fConst14 * fRec18[2])))))) + (fSlow28 * (std::min<float>(1.0f, fRec24[0]) * ((fTemp9 * (fRec26[2] + (fRec26[0] + (2.0f * fRec26[1])))) + (((fConst14 * fRec26[0]) + (fConst16 * fRec26[1])) + (fConst14 * fRec26[2])))))) + (fSlow37 * (std::min<float>(1.0f, fRec32[0]) * ((fTemp9 * (fRec34[2] + (fRec34[0] + (2.0f * fRec34[1])))) + (((fConst14 * fRec34[0]) + (fConst16 * fRec34[1])) + (fConst14 * fRec34[2])))))) + (fSlow46 * (std::min<float>(1.0f, fRec40[0]) * ((fTemp9 * (fRec42[2] + (fRec42[0] + (2.0f * fRec42[1])))) + (((fConst14 * fRec42[0]) + (fConst16 * fRec42[1])) + (fConst14 * fRec42[2])))))) + (fSlow55 * (std::min<float>(1.0f, fRec48[0]) * ((fTemp9 * (fRec50[2] + (fRec50[0] + (2.0f * fRec50[1])))) + (((fConst14 * fRec50[0]) + (fConst16 * fRec50[1])) + (fConst14 * fRec50[2]))))))));
			fVec0[1] = fVec0[0];
			iRec1[1] = iRec1[0];
			fRec0[1] = fRec0[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			iRec15[1] = iRec15[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec14[j0] = fRec14[(j0 - 1)];
				
			}
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			iRec17[1] = iRec17[0];
			fRec16[1] = fRec16[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fVec2[1] = fVec2[0];
			iRec25[1] = iRec25[0];
			fRec24[1] = fRec24[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fVec3[1] = fVec3[0];
			iRec33[1] = iRec33[0];
			fRec32[1] = fRec32[0];
			fRec35[1] = fRec35[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fVec4[1] = fVec4[0];
			iRec41[1] = iRec41[0];
			fRec40[1] = fRec40[0];
			fRec43[1] = fRec43[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec46[1] = fRec46[0];
			fRec47[1] = fRec47[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fVec5[1] = fVec5[0];
			iRec49[1] = iRec49[0];
			fRec48[1] = fRec48[0];
			fRec51[1] = fRec51[0];
			fRec52[1] = fRec52[0];
			fRec53[1] = fRec53[0];
			fRec54[1] = fRec54[0];
			fRec55[1] = fRec55[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			
		}
		
	}

	
};

#endif
