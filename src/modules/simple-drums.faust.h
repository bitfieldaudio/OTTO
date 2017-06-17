//----------------------------------------------------------
// name: "simple-drums"
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
#define FAUSTCLASS faust_simple_drums
#endif

class faust_simple_drums : public dsp {
  private:
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	float 	fConst0;
	float 	fConst1;
	int 	iRec1[2];
	FAUSTFLOAT 	fslider1;
	float 	fConst2;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fVec1[2];
	FAUSTFLOAT 	fbutton0;
	float 	fVec2[2];
	float 	fRec2[2];
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fslider4;
	float 	fVec3[2];
	float 	fRec3[2];
	float 	fVec4[2];
	int 	IOTA;
	float 	fVec5[4096];
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	float 	fRec0[3];
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	float 	fVec6[2];
	float 	fRec4[2];
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fslider7;
	float 	fVec7[2];
	float 	fRec5[2];
	float 	fVec8[2];
	float 	fVec9[4096];
	FAUSTFLOAT 	fcheckbox1;
	FAUSTFLOAT 	fslider8;
	float 	fRec6[3];
	FAUSTFLOAT 	fslider9;
	float 	fVec10[2];
	float 	fRec7[2];
	FAUSTFLOAT 	fslider10;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("name", "simple-drums");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
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
		fConst1 = (3.1415927f / fConst0);
		fConst2 = (0.0001f * fConst0);
		fConst3 = (1.0f / fConst0);
		fConst4 = (1e+04f / fConst0);
		fConst5 = float(fConst0);
		fConst6 = (0.5f * fConst5);
		fConst7 = (0.25f * fConst5);
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1e+03f;
		fslider1 = 0.2f;
		fslider2 = 0.5f;
		fslider3 = 0.2f;
		fbutton0 = 0.0;
		fslider4 = 5e+02f;
		fcheckbox0 = 0.0;
		fslider5 = 0.2f;
		fslider6 = 0.5f;
		fslider7 = 5e+02f;
		fcheckbox1 = 0.0;
		fslider8 = 1e+03f;
		fslider9 = 0.0f;
		fslider10 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) iRec1[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		IOTA = 0;
		for (int i=0; i<4096; i++) fVec5[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fVec8[i] = 0;
		for (int i=0; i<4096; i++) fVec9[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
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
	virtual faust_simple_drums* clone() {
		return new faust_simple_drums();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("simple-drums");
		ui_interface->openVerticalBox("D1");
		ui_interface->addHorizontalSlider("CUTOFF", &fslider8, 1e+03f, 5.0f, 1e+04f, 0.001f);
		ui_interface->addHorizontalBargraph("DECAY_GRAPH", &fbargraph1, -1.0f, 1.0f);
		ui_interface->addCheckButton("FILTER_SWITCH", &fcheckbox1);
		ui_interface->addHorizontalSlider("FREQ", &fslider7, 5e+02f, 1e+01f, 5e+02f, 2.9f);
		ui_interface->addHorizontalSlider("NOISE", &fslider5, 0.2f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("TONE_DECAY", &fslider6, 0.5f, -1.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("D2");
		ui_interface->addHorizontalSlider("CUTOFF", &fslider0, 1e+03f, 5.0f, 1e+04f, 0.001f);
		ui_interface->addHorizontalBargraph("DECAY_GRAPH", &fbargraph0, -1.0f, 1.0f);
		ui_interface->addCheckButton("FILTER_SWITCH", &fcheckbox0);
		ui_interface->addHorizontalSlider("FREQ", &fslider4, 5e+02f, 1e+01f, 5e+02f, 2.9f);
		ui_interface->addHorizontalSlider("NOISE", &fslider1, 0.2f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("TONE_DECAY", &fslider2, 0.5f, -1.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ENVELOPE");
		ui_interface->addVerticalSlider("ATTACK", &fslider9, 0.0f, 0.0f, 2.0f, 0.02f);
		ui_interface->addVerticalSlider("RELEASE", &fslider3, 0.2f, 0.0f, 2.0f, 0.02f);
		ui_interface->addVerticalSlider("SUSTAIN", &fslider10, 1.0f, 0.0f, 2.0f, 0.02f);
		ui_interface->closeBox();
		ui_interface->addButton("TRIGGER", &fbutton0);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = tanf((fConst1 * float(fslider0)));
		float 	fSlow1 = (2 * (1 - (1.0f / faustpower<2>(fSlow0))));
		float 	fSlow2 = (1.0f / fSlow0);
		float 	fSlow3 = (((fSlow2 + -0.33333334f) / fSlow0) + 1);
		float 	fSlow4 = (((fSlow2 + 0.33333334f) / fSlow0) + 1);
		float 	fSlow5 = (1.0f / fSlow4);
		float 	fSlow6 = float(fslider1);
		float 	fSlow7 = (4.656613e-10f * fSlow6);
		float 	fSlow8 = float(fslider2);
		float 	fSlow9 = float(fslider3);
		float 	fSlow10 = ((fSlow9 * fabsf(fSlow8)) + 0.0001f);
		float 	fSlow11 = (fConst0 * fSlow10);
		float 	fSlow12 = float(fbutton0);
		float 	fSlow13 = (fConst3 / (fSlow10 + -0.0001f));
		float 	fSlow14 = float(fslider4);
		float 	fSlow15 = (fConst7 * (1 - fSlow6));
		float 	fSlow16 = float(fcheckbox0);
		float 	fSlow17 = (fSlow16 / fSlow4);
		float 	fSlow18 = float(fslider5);
		float 	fSlow19 = (4.656613e-10f * fSlow18);
		float 	fSlow20 = float(fslider6);
		float 	fSlow21 = ((fSlow9 * fabsf(fSlow20)) + 0.0001f);
		float 	fSlow22 = (fConst0 * fSlow21);
		float 	fSlow23 = (fConst3 / (fSlow21 + -0.0001f));
		float 	fSlow24 = float(fslider7);
		float 	fSlow25 = (fConst7 * (1 - fSlow18));
		float 	fSlow26 = float(fcheckbox1);
		float 	fSlow27 = (1 - fSlow26);
		float 	fSlow28 = tanf((fConst1 * float(fslider8)));
		float 	fSlow29 = (2 * (1 - (1.0f / faustpower<2>(fSlow28))));
		float 	fSlow30 = (1.0f / fSlow28);
		float 	fSlow31 = (((fSlow30 + -0.33333334f) / fSlow28) + 1);
		float 	fSlow32 = (((fSlow30 + 0.33333334f) / fSlow28) + 1);
		float 	fSlow33 = (1.0f / fSlow32);
		float 	fSlow34 = (fSlow26 / fSlow32);
		float 	fSlow35 = (1 - fSlow16);
		float 	fSlow36 = (float(fslider9) + 0.001f);
		float 	fSlow37 = (fConst0 * fSlow36);
		float 	fSlow38 = (fSlow36 + (fSlow9 + 0.001f));
		float 	fSlow39 = (fConst0 * fSlow38);
		float 	fSlow40 = (1.0f / (0 - (fConst0 * (fSlow36 - fSlow38))));
		float 	fSlow41 = (fConst3 / fSlow36);
		float 	fSlow42 = float(fslider10);
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			iRec1[0] = ((1103515245 * iRec1[1]) + 12345);
			fVec1[0] = fSlow10;
			fVec2[0] = fSlow12;
			int iTemp0 = int((((fSlow12 - fVec2[1]) > 0) > 0));
			fRec2[0] = ((iTemp0)?0:min(fSlow11, ((fRec2[1] + (fConst0 * (fSlow10 - fVec1[1]))) + 1)));
			int iTemp1 = int((fRec2[0] < fConst2));
			fbargraph0 = (fSlow8 * ((iTemp1)?((int((fRec2[0] < 0)))?0:((iTemp1)?(fConst4 * fRec2[0]):1)):((int((fRec2[0] < fSlow11)))?((fSlow13 * (0 - (fRec2[0] - fConst2))) + 1):0)));
			float fTemp2 = max((fSlow14 * (fbargraph0 + 1)), 23.44895f);
			float fTemp3 = max(2e+01f, fabsf(fTemp2));
			fVec3[0] = fTemp3;
			float fTemp4 = (fRec3[1] + (fConst3 * fVec3[1]));
			fRec3[0] = (fTemp4 - floorf(fTemp4));
			float fTemp5 = faustpower<2>(((2 * fRec3[0]) + -1));
			fVec4[0] = fTemp5;
			float fTemp6 = ((iVec0[1] * (fVec4[0] - fVec4[1])) / fVec3[0]);
			fVec5[IOTA&4095] = fTemp6;
			float fTemp7 = max((float)0, min((float)2047, (fConst6 / fTemp2)));
			int iTemp8 = int(fTemp7);
			float fTemp9 = floorf(fTemp7);
			float fTemp10 = ((fSlow15 * ((fVec5[IOTA&4095] - (fVec5[(IOTA-iTemp8)&4095] * (fTemp9 + (1 - fTemp7)))) - ((fTemp7 - fTemp9) * fVec5[(IOTA-int((iTemp8 + 1)))&4095]))) + (fSlow7 * iRec1[0]));
			fRec0[0] = (fTemp10 - (fSlow5 * ((fSlow3 * fRec0[2]) + (fSlow1 * fRec0[1]))));
			fVec6[0] = fSlow21;
			fRec4[0] = ((iTemp0)?0:min(fSlow22, ((fRec4[1] + (fConst0 * (fSlow21 - fVec6[1]))) + 1)));
			int iTemp11 = int((fRec4[0] < fConst2));
			fbargraph1 = (fSlow20 * ((iTemp11)?((int((fRec4[0] < 0)))?0:((iTemp11)?(fConst4 * fRec4[0]):1)):((int((fRec4[0] < fSlow22)))?((fSlow23 * (0 - (fRec4[0] - fConst2))) + 1):0)));
			float fTemp12 = max((fSlow24 * (fbargraph1 + 1)), 23.44895f);
			float fTemp13 = max(2e+01f, fabsf(fTemp12));
			fVec7[0] = fTemp13;
			float fTemp14 = (fRec5[1] + (fConst3 * fVec7[1]));
			fRec5[0] = (fTemp14 - floorf(fTemp14));
			float fTemp15 = faustpower<2>(((2 * fRec5[0]) + -1));
			fVec8[0] = fTemp15;
			float fTemp16 = ((iVec0[1] * (fVec8[0] - fVec8[1])) / fVec7[0]);
			fVec9[IOTA&4095] = fTemp16;
			float fTemp17 = max((float)0, min((float)2047, (fConst6 / fTemp12)));
			int iTemp18 = int(fTemp17);
			float fTemp19 = floorf(fTemp17);
			float fTemp20 = ((fSlow25 * ((fVec9[IOTA&4095] - (fVec9[(IOTA-iTemp18)&4095] * (fTemp19 + (1 - fTemp17)))) - ((fTemp17 - fTemp19) * fVec9[(IOTA-int((iTemp18 + 1)))&4095]))) + (fSlow19 * iRec1[0]));
			fRec6[0] = (fTemp20 - (fSlow33 * ((fSlow31 * fRec6[2]) + (fSlow29 * fRec6[1]))));
			fVec10[0] = fSlow38;
			fRec7[0] = ((iTemp0)?0:min(fSlow39, ((fRec7[1] + (fConst0 * (fSlow38 - fVec10[1]))) + 1)));
			int iTemp21 = int((fRec7[0] < fSlow37));
			output0[i] = (FAUSTFLOAT)(fSlow42 * (((iTemp21)?((int((fRec7[0] < 0)))?0:((iTemp21)?(fSlow41 * fRec7[0]):1)):((int((fRec7[0] < fSlow39)))?((fSlow40 * (0 - (fRec7[0] - fSlow37))) + 1):0)) * ((fSlow35 * fTemp10) + (((fSlow34 * (fRec6[2] + (fRec6[0] + (2.0f * fRec6[1])))) + (fSlow27 * fTemp20)) + (fSlow17 * (fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))))))));
			// post processing
			fRec7[1] = fRec7[0];
			fVec10[1] = fVec10[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fVec8[1] = fVec8[0];
			fRec5[1] = fRec5[0];
			fVec7[1] = fVec7[0];
			fRec4[1] = fRec4[0];
			fVec6[1] = fVec6[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			IOTA = IOTA+1;
			fVec4[1] = fVec4[0];
			fRec3[1] = fRec3[0];
			fVec3[1] = fVec3[0];
			fRec2[1] = fRec2[0];
			fVec2[1] = fVec2[0];
			fVec1[1] = fVec1[0];
			iRec1[1] = iRec1[0];
			iVec0[1] = iVec0[0];
		}
	}
};


