/* ------------------------------------------------------------
name: "metronome"
Code generated with Faust 2.5.23 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faust_metronome_H__
#define  __faust_metronome_H__

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

#include <cmath>
#include <math.h>

float faust_metronome_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_metronome
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faust_metronome : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fVec0[2];
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fVec1[2];
	int iVec2[2];
	float fConst2;
	float fRec0[2];
	float fVec3[2];
	int IOTA;
	float fVec4[1024];
	float fConst3;
	FAUSTFLOAT fButton0;
	float fVec5[2];
	float fConst4;
	float fRec1[2];
	float fConst5;
	float fConst6;
	float fConst7;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filename", "metronome");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "metronome");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
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
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (0.25f * fConst0);
		fConst2 = (1.0f / fConst0);
		fConst3 = (0.5f * fConst0);
		fConst4 = (0.0900001004f * fConst0);
		fConst5 = (1.00000001e-07f * fConst0);
		fConst6 = (11.1111107f / fConst0);
		fConst7 = (10000000.0f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(12.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iVec2[l2] = 0;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec3[l4] = 0.0f;
			
		}
		IOTA = 0;
		for (int l5 = 0; (l5 < 1024); l5 = (l5 + 1)) {
			fVec4[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec5[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec1[l7] = 0.0f;
			
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
	
	virtual faust_metronome* clone() {
		return new faust_metronome();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("metronome");
		ui_interface->addHorizontalSlider("GAIN", &fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("TONE", &fHslider1, 12.0f, 0.0f, 24.0f, 1.0f);
		ui_interface->addButton("TRIGGER", &fButton0);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = max((110.0f * powf(2.0f, (0.0833333358f * float(fHslider1)))), 23.4489498f);
		float fSlow2 = max(20.0f, fabsf(fSlow1));
		float fSlow3 = (fConst1 / fSlow2);
		float fSlow4 = max(0.0f, min(2047.0f, (fConst3 / fSlow1)));
		float fSlow5 = floorf(fSlow4);
		float fSlow6 = (fSlow5 + (1.0f - fSlow4));
		int iSlow7 = int(fSlow4);
		float fSlow8 = (fSlow4 - fSlow5);
		int iSlow9 = (iSlow7 + 1);
		float fSlow10 = float(fButton0);
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[0] = fConst0;
			fVec1[0] = fSlow2;
			iVec2[0] = 1;
			float fTemp0 = (fRec0[1] + (fConst2 * fVec1[1]));
			fRec0[0] = (fTemp0 - floorf(fTemp0));
			float fTemp1 = faust_metronome_faustpower2_f(((2.0f * fRec0[0]) + -1.0f));
			fVec3[0] = fTemp1;
			float fTemp2 = (fSlow3 * ((fTemp1 - fVec3[1]) * float(iVec2[1])));
			fVec4[(IOTA & 1023)] = fTemp2;
			fVec5[0] = fSlow10;
			fRec1[0] = ((((fSlow10 - fVec5[1]) > 0.0f) > 0)?0.0f:min(fConst4, (fRec1[1] + (1.0f - (0.0900001004f * (fVec0[1] - fConst0))))));
			int iTemp3 = (fRec1[0] < fConst5);
			output0[i] = FAUSTFLOAT((fSlow0 * ((fTemp2 - ((fSlow6 * fVec4[((IOTA - iSlow7) & 1023)]) + (fSlow8 * fVec4[((IOTA - iSlow9) & 1023)]))) * (iTemp3?((fRec1[0] < 0.0f)?0.0f:(iTemp3?(fConst7 * fRec1[0]):1.0f)):((fRec1[0] < fConst4)?((fConst6 * (0.0f - (fRec1[0] - fConst5))) + 1.0f):0.0f)))));
			fVec0[1] = fVec0[0];
			fVec1[1] = fVec1[0];
			iVec2[1] = iVec2[0];
			fRec0[1] = fRec0[0];
			fVec3[1] = fVec3[0];
			IOTA = (IOTA + 1);
			fVec5[1] = fVec5[0];
			fRec1[1] = fRec1[0];
			
		}
		
	}

	
};

#endif
