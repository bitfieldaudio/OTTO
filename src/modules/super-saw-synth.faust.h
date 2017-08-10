//----------------------------------------------------------
// name: "super-saw-synth"
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
#define FAUSTCLASS faust_super_saw_synth
#endif

class faust_super_saw_synth : public dsp {
  private:
	int 	iVec0[2];
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
	float 	fVec1[2];
	float 	fRec4[2];
	float 	fVec2[2];
	float 	fConst3;
	float 	fConst4;
	int 	IOTA;
	float 	fVec3[4096];
	float 	fConst5;
	float 	fRec3[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("name", "super-saw-synth");
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
		fConst2 = (1382.3008f / fConst0);
		fConst3 = float(fConst0);
		fConst4 = (0.25f * fConst3);
		fConst5 = (0.5f * fConst3);
	}
	virtual void instanceResetUserInterface() {
		fbutton0 = 0.0;
		fslider0 = 1.0f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 0.2f;
		fslider4 = 1.0f;
		fslider5 = 69.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		IOTA = 0;
		for (int i=0; i<4096; i++) fVec3[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
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
	virtual faust_super_saw_synth* clone() {
		return new faust_super_saw_synth();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("super-saw-synth");
		ui_interface->openHorizontalBox("ENVELOPE");
		ui_interface->addVerticalSlider("ATTACK", &fslider1, 0.0f, 0.0f, 2.0f, 0.02f);
		ui_interface->addVerticalSlider("DECAY", &fslider2, 0.0f, 0.0f, 2.0f, 0.02f);
		ui_interface->addVerticalSlider("RELEASE", &fslider3, 0.2f, 0.0f, 2.0f, 0.02f);
		ui_interface->addVerticalSlider("SUSTAIN", &fslider0, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addVerticalSlider("KEY", &fslider5, 69.0f, 0.0f, 127.0f, 1.0f);
		ui_interface->addButton("TRIGGER", &fbutton0);
		ui_interface->addVerticalSlider("VELOCITY", &fslider4, 1.0f, 0.0f, 1.0f, 0.01f);
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
		float 	fSlow16 = powf(2.0f,(0.083333336f * (float(fslider5) + -69.0f)));
		float 	fSlow17 = (fConst2 * fSlow16);
		float 	fSlow18 = max((4.4e+02f * fSlow16), 23.44895f);
		float 	fSlow19 = max(2e+01f, fabsf(fSlow18));
		float 	fSlow20 = (fConst4 / fSlow19);
		float 	fSlow21 = max((float)0, min((float)2047, (fConst5 / fSlow18)));
		int 	iSlow22 = int(fSlow21);
		int 	iSlow23 = int((iSlow22 + 1));
		float 	fSlow24 = floorf(fSlow21);
		float 	fSlow25 = (fSlow21 - fSlow24);
		float 	fSlow26 = (fSlow24 + (1 - fSlow21));
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec1[0] = ((iSlow6)?0:min(fSlow5, (fRec1[1] + 1)));
			int iTemp0 = int((fRec1[0] < fSlow3));
			fRec0[0] = ((iSlow10)?(iSlow9 * ((iTemp0)?((int((fRec1[0] < 0)))?0:((iTemp0)?(fSlow8 * fRec1[0]):1)):((int((fRec1[0] < fSlow5)))?((fSlow7 * (fRec1[0] - fSlow3)) + 1):fSlow1))):fRec0[1]);
			fRec2[0] = ((iSlow13)?0:min(fSlow12, (fRec2[1] + 1)));
			float fTemp1 = ((int((fRec2[0] < 0)))?fRec0[0]:((int((fRec2[0] < fSlow12)))?(fRec0[0] + (fSlow14 * (fRec2[0] * (0 - fRec0[0])))):0));
			float fTemp2 = tanf((fSlow17 * ((fSlow15 * fTemp1) + 1)));
			float fTemp3 = (1.0f / fTemp2);
			float fTemp4 = (((fTemp3 + 0.125f) / fTemp2) + 1);
			fVec1[0] = fSlow19;
			float fTemp5 = ((fConst1 * fVec1[1]) + fRec4[1]);
			fRec4[0] = (fTemp5 - floorf(fTemp5));
			float fTemp6 = faustpower<2>(((2 * fRec4[0]) + -1));
			fVec2[0] = fTemp6;
			float fTemp7 = (fSlow20 * (iVec0[1] * (fVec2[0] - fVec2[1])));
			fVec3[IOTA&4095] = fTemp7;
			fRec3[0] = (fVec3[IOTA&4095] - (((fSlow26 * fVec3[(IOTA-iSlow22)&4095]) + (fSlow25 * fVec3[(IOTA-iSlow23)&4095])) + (((fRec3[2] * (((fTemp3 + -0.125f) / fTemp2) + 1)) + (2 * (fRec3[1] * (1 - (1.0f / faustpower<2>(fTemp2)))))) / fTemp4)));
			output0[i] = (FAUSTFLOAT)((fTemp1 * (fRec3[2] + (fRec3[0] + (2.0f * fRec3[1])))) / fTemp4);
			// post processing
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			IOTA = IOTA+1;
			fVec2[1] = fVec2[0];
			fRec4[1] = fRec4[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			iVec0[1] = iVec0[0];
		}
	}
};


