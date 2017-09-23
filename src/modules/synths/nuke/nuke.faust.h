//----------------------------------------------------------
// name: "nuke"
//
// Code generated with Faust 0.9.104 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
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


#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_nuke
#endif

class faust_nuke : public dsp {
  private:
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	float 	fConst0;
	FAUSTFLOAT 	fslider2;
	float 	fRec1[2];
	float 	fConst1;
	float 	fRec0[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	float 	fConst2;
	FAUSTFLOAT 	fslider6;
	float 	fConst3;
	float 	fConst4;
	float 	fRec4[2];
	float 	fRec3[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	float 	fRec7[2];
	float 	fRec6[3];
	float 	fRec10[2];
	float 	fRec9[3];
	float 	fRec13[2];
	float 	fRec12[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("name", "nuke");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1e+03f, (float)fSamplingFreq));
		fConst1 = (1.0f / fConst0);
		fConst2 = (3.1415927f / fConst0);
		fConst3 = float(fConst0);
		fConst4 = (1.0f / fConst3);
	}
	virtual void instanceResetUserInterface() {
		fbutton0 = 0.0;
		fslider0 = 1.0f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 0.2f;
		fslider4 = 1.0f;
		fslider5 = 1.0f;
		fslider6 = 69.0f;
		fslider7 = 1.0f;
		fslider8 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<3; i++) fRec12[i] = 0;
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
	virtual faust_nuke* clone() {
		return new faust_nuke();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("nuke");
		ui_interface->addHorizontalSlider("DETUNE", &fslider8, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->openHorizontalBox("ENVELOPE");
		ui_interface->addVerticalSlider("ATTACK", &fslider1, 0.0f, 0.0f, 2.0f, 0.02f);
		ui_interface->addVerticalSlider("DECAY", &fslider2, 0.0f, 0.0f, 2.0f, 0.02f);
		ui_interface->addVerticalSlider("RELEASE", &fslider3, 0.2f, 0.0f, 2.0f, 0.02f);
		ui_interface->addVerticalSlider("SUSTAIN", &fslider0, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("FILTER", &fslider4, 1.0f, 1e+01f, 1.5e+04f, 1e+01f);
		ui_interface->addHorizontalSlider("KEY", &fslider6, 69.0f, 0.0f, 127.0f, 0.1f);
		ui_interface->addButton("TRIGGER", &fbutton0);
		ui_interface->addHorizontalSlider("VELOCITY", &fslider5, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("VOICES", &fslider7, 1.0f, 1.0f, 4.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = float(fbutton0);
		float 	fSlow1 = (float(fslider0) * fSlow0);
		float 	fSlow2 = float(fslider1);
		float 	fSlow3 = (fConst0 * fSlow2);
		float 	fSlow4 = (fSlow2 + float(fslider2));
		float 	fSlow5 = (fConst0 * fSlow4);
		int 	iSlow6 = int(((fSlow0 == 0) > 0));
		float 	fSlow7 = ((fSlow1 + -1) / (0 - (fConst0 * (fSlow2 - fSlow4))));
		float 	fSlow8 = (fConst1 / fSlow2);
		int 	iSlow9 = (fSlow0 > 0);
		int 	iSlow10 = int(iSlow9);
		float 	fSlow11 = float(fslider3);
		float 	fSlow12 = (fConst0 * fSlow11);
		int 	iSlow13 = int((iSlow9 > 0));
		float 	fSlow14 = (fConst1 / fSlow11);
		float 	fSlow15 = float(fslider4);
		float 	fSlow16 = tanf((fConst2 * (float(fslider5) * fSlow15)));
		float 	fSlow17 = (2 * (1 - (1.0f / faustpower<2>(fSlow16))));
		float 	fSlow18 = (0.125f / (1.125f - (6.666667e-05f * fSlow15)));
		float 	fSlow19 = (1.0f / fSlow16);
		float 	fSlow20 = (((fSlow19 - fSlow18) / fSlow16) + 1);
		float 	fSlow21 = (1.0f / (((fSlow18 + fSlow19) / fSlow16) + 1));
		float 	fSlow22 = powf(2.0f,(0.083333336f * (float(fslider6) + -69.0f)));
		float 	fSlow23 = float(max(1e-07f, fabsf((55.0f * fSlow22))));
		float 	fSlow24 = (fConst4 * fSlow23);
		float 	fSlow25 = (1 - (fConst3 / fSlow23));
		float 	fSlow26 = float(fslider7);
		float 	fSlow27 = (fSlow26 + -3);
		float 	fSlow28 = ((int((fSlow27 > 1)))?1:((int((fSlow27 < 0)))?0:fSlow27));
		float 	fSlow29 = float(fslider8);
		float 	fSlow30 = float(max(1e-07f, fabsf((1.1e+02f * (fSlow22 * ((0.041666668f * (0 - fSlow29)) + 1))))));
		float 	fSlow31 = (fConst4 * fSlow30);
		float 	fSlow32 = (1 - (fConst3 / fSlow30));
		float 	fSlow33 = (fSlow26 + -2);
		float 	fSlow34 = ((int((fSlow33 > 1)))?1:((int((fSlow33 < 0)))?0:fSlow33));
		float 	fSlow35 = float(max(1e-07f, fabsf((2.2e+02f * (fSlow22 * ((0.041666668f * fSlow29) + 1))))));
		float 	fSlow36 = (fConst4 * fSlow35);
		float 	fSlow37 = (1 - (fConst3 / fSlow35));
		float 	fSlow38 = (fSlow26 + -1);
		float 	fSlow39 = ((int((fSlow38 > 1)))?1:((int((fSlow38 < 0)))?0:fSlow38));
		float 	fSlow40 = float(max(1e-07f, fabsf((4.4e+02f * fSlow22))));
		float 	fSlow41 = (fConst4 * fSlow40);
		float 	fSlow42 = (1 - (fConst3 / fSlow40));
		float 	fSlow43 = ((int((fSlow26 > 1)))?1:((int((fSlow26 < 0)))?0:fSlow26));
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			fRec1[0] = ((iSlow6)?0:min(fSlow5, (fRec1[1] + 1)));
			int iTemp0 = int((fRec1[0] < fSlow3));
			fRec0[0] = ((iSlow10)?(iSlow9 * ((iTemp0)?((int((fRec1[0] < 0)))?0:((iTemp0)?(fSlow8 * fRec1[0]):1)):((int((fRec1[0] < fSlow5)))?((fSlow7 * (fRec1[0] - fSlow3)) + 1):fSlow1))):fRec0[1]);
			fRec2[0] = ((iSlow13)?0:min(fSlow12, (fRec2[1] + 1)));
			float fTemp1 = (fSlow24 + (fRec4[1] + -1));
			float fTemp2 = (fSlow24 + fRec4[1]);
			int iTemp3 = int((fTemp1 < 0));
			fRec4[0] = ((iTemp3)?fTemp2:fTemp1);
			float 	fRec5 = ((iTemp3)?fTemp2:(fSlow24 + (fRec4[1] + (fSlow25 * fTemp1))));
			fRec3[0] = ((2 * fRec5) + (-1 - (fSlow21 * ((fSlow20 * fRec3[2]) + (fSlow17 * fRec3[1])))));
			float fTemp4 = (fSlow31 + (fRec7[1] + -1));
			float fTemp5 = (fSlow31 + fRec7[1]);
			int iTemp6 = int((fTemp4 < 0));
			fRec7[0] = ((iTemp6)?fTemp5:fTemp4);
			float 	fRec8 = ((iTemp6)?fTemp5:(fSlow31 + (fRec7[1] + (fSlow32 * fTemp4))));
			fRec6[0] = ((2 * fRec8) + (-1 - (fSlow21 * ((fSlow20 * fRec6[2]) + (fSlow17 * fRec6[1])))));
			float fTemp7 = (fSlow36 + (fRec10[1] + -1));
			float fTemp8 = (fSlow36 + fRec10[1]);
			int iTemp9 = int((fTemp7 < 0));
			fRec10[0] = ((iTemp9)?fTemp8:fTemp7);
			float 	fRec11 = ((iTemp9)?fTemp8:(fSlow36 + (fRec10[1] + (fSlow37 * fTemp7))));
			fRec9[0] = ((2 * fRec11) + (-1 - (fSlow21 * ((fSlow20 * fRec9[2]) + (fSlow17 * fRec9[1])))));
			float fTemp10 = (fSlow41 + (fRec13[1] + -1));
			float fTemp11 = (fSlow41 + fRec13[1]);
			int iTemp12 = int((fTemp10 < 0));
			fRec13[0] = ((iTemp12)?fTemp11:fTemp10);
			float 	fRec14 = ((iTemp12)?fTemp11:(fSlow41 + (fRec13[1] + (fSlow42 * fTemp10))));
			fRec12[0] = ((2 * fRec14) + (-1 - (fSlow21 * ((fSlow20 * fRec12[2]) + (fSlow17 * fRec12[1])))));
			output0[i] = (FAUSTFLOAT)(fSlow21 * (((((fSlow43 * (fRec12[2] + (fRec12[0] + (2.0f * fRec12[1])))) + (fSlow39 * (fRec9[2] + (fRec9[0] + (2.0f * fRec9[1]))))) + (fSlow34 * (fRec6[2] + (fRec6[0] + (2.0f * fRec6[1]))))) + (fSlow28 * (fRec3[2] + (fRec3[0] + (2.0f * fRec3[1]))))) * ((int((fRec2[0] < 0)))?fRec0[0]:((int((fRec2[0] < fSlow12)))?(fRec0[0] + (fSlow14 * (fRec2[0] * (0 - fRec0[0])))):0))));
			// post processing
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
		}
	}
};


