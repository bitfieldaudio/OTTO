//----------------------------------------------------------
// name: "metronome"
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
#define FAUSTCLASS faust_metronome
#endif

class faust_metronome : public dsp {
  private:
	int 	iVec0[2];
	float 	fConst0;
	float 	fVec1[2];
	float 	fConst1;
	float 	fConst2;
	FAUSTFLOAT 	fbutton0;
	float 	fVec2[2];
	float 	fRec0[2];
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider0;
	float 	fVec3[2];
	float 	fConst5;
	float 	fRec1[2];
	float 	fVec4[2];
	float 	fConst6;
	float 	fConst7;
	int 	IOTA;
	float 	fVec5[1024];
	float 	fConst8;
	FAUSTFLOAT 	fslider1;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("name", "metronome");
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
		fConst1 = (1e-07f * fConst0);
		fConst2 = (0.0900001f * fConst0);
		fConst3 = (11.111111f / fConst0);
		fConst4 = (1e+07f / fConst0);
		fConst5 = (1.0f / fConst0);
		fConst6 = float(fConst0);
		fConst7 = (0.25f * fConst6);
		fConst8 = (0.5f * fConst6);
	}
	virtual void instanceResetUserInterface() {
		fbutton0 = 0.0;
		fslider0 = 12.0f;
		fslider1 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		IOTA = 0;
		for (int i=0; i<1024; i++) fVec5[i] = 0;
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
	virtual faust_metronome* clone() {
		return new faust_metronome();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("metronome");
		ui_interface->addHorizontalSlider("GAIN", &fslider1, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("TONE", &fslider0, 12.0f, 0.0f, 24.0f, 1.0f);
		ui_interface->addButton("TRIGGER", &fbutton0);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = float(fbutton0);
		float 	fSlow1 = max((110 * powf(2,(0.083333336f * float(fslider0)))), 23.44895f);
		float 	fSlow2 = max(2e+01f, fabsf(fSlow1));
		float 	fSlow3 = (fConst7 / fSlow2);
		float 	fSlow4 = max((float)0, min((float)2047, (fConst8 / fSlow1)));
		int 	iSlow5 = int(fSlow4);
		int 	iSlow6 = int((iSlow5 + 1));
		float 	fSlow7 = floorf(fSlow4);
		float 	fSlow8 = (fSlow4 - fSlow7);
		float 	fSlow9 = (fSlow7 + (1 - fSlow4));
		float 	fSlow10 = float(fslider1);
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fVec1[0] = fConst0;
			fVec2[0] = fSlow0;
			fRec0[0] = ((int((((fSlow0 - fVec2[1]) > 0) > 0)))?0:min(fConst2, ((fRec0[1] + (0.0900001f * (fConst0 - fVec1[1]))) + 1)));
			int iTemp0 = int((fRec0[0] < fConst1));
			fVec3[0] = fSlow2;
			float fTemp1 = ((fConst5 * fVec3[1]) + fRec1[1]);
			fRec1[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = faustpower<2>(((2 * fRec1[0]) + -1));
			fVec4[0] = fTemp2;
			float fTemp3 = (fSlow3 * (iVec0[1] * (fVec4[0] - fVec4[1])));
			fVec5[IOTA&1023] = fTemp3;
			output0[i] = (FAUSTFLOAT)(fSlow10 * ((fVec5[IOTA&1023] - ((fSlow9 * fVec5[(IOTA-iSlow5)&1023]) + (fSlow8 * fVec5[(IOTA-iSlow6)&1023]))) * ((iTemp0)?((int((fRec0[0] < 0)))?0:((iTemp0)?(fConst4 * fRec0[0]):1)):((int((fRec0[0] < fConst2)))?((fConst3 * (0 - (fRec0[0] - fConst1))) + 1):0))));
			// post processing
			IOTA = IOTA+1;
			fVec4[1] = fVec4[0];
			fRec1[1] = fRec1[0];
			fVec3[1] = fVec3[0];
			fRec0[1] = fRec0[0];
			fVec2[1] = fVec2[0];
			fVec1[1] = fVec1[0];
			iVec0[1] = iVec0[0];
		}
	}
};


