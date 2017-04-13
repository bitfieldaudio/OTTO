/* ------------------------------------------------------------
name: "TestSynth"
Code generated with Faust 2.0.a64 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __testsynth_H__
#define  __testsynth_H__

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

#include <math.h>


class testsynthSIG0 {
	
  private:
	
	int iRec0[2];
	
  public:
	
	int getNumInputstestsynthSIG0() {
		return 0;
		
	}
	int getNumOutputstestsynthSIG0() {
		return 1;
		
	}
	int getInputRatetestsynthSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatetestsynthSIG0(int channel) {
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
	
	void instanceInittestsynthSIG0(int samplingFreq) {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
			
		}
		
	}
	
	void filltestsynthSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			output[i] = sinf((9.58738019e-05f * float((iRec0[0] + -1))));
			iRec0[1] = iRec0[0];
			
		}
		
	}
};

testsynthSIG0* newtestsynthSIG0() { return (testsynthSIG0*)new testsynthSIG0(); }
void deletetestsynthSIG0(testsynthSIG0* dsp) { delete dsp; }

static float ftbl0testsynthSIG0[65537];

#ifndef FAUSTCLASS 
#define FAUSTCLASS testsynth
#endif

class testsynth : public dsp {
	
 private:
	
	int fSamplingFreq;
	float fRec2[2];
	float fRec1[2];
	float fConst0;
	float fConst1;
	float fConst2;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.0");
		m->declare("name", "TestSynth");
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
		testsynthSIG0* sig0 = newtestsynthSIG0();
		sig0->instanceInittestsynthSIG0(samplingFreq);
		sig0->filltestsynthSIG0(65537, ftbl0testsynthSIG0);
		deletetestsynthSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (0.100000001f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		
	}
	
	virtual void instanceClear() {
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
			
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
	
	virtual testsynth* clone() {
		return new testsynth();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("0x00");
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec2[0] = (fConst2 + (fRec2[1] - floorf((fConst2 + fRec2[1]))));
			float fTemp0 = (65536.0f * fRec2[0]);
			int iTemp1 = int(fTemp0);
			float fTemp2 = (fRec1[1] + (fConst1 * ((200.0f * (ftbl0testsynthSIG0[iTemp1] + ((fTemp0 - floorf(fTemp0)) * (ftbl0testsynthSIG0[(iTemp1 + 1)] - ftbl0testsynthSIG0[iTemp1])))) + 440.0f)));
			fRec1[0] = (fTemp2 - floorf(fTemp2));
			float fTemp3 = (65536.0f * fRec1[0]);
			int iTemp4 = int(fTemp3);
			output0[i] = FAUSTFLOAT((ftbl0testsynthSIG0[iTemp4] + ((fTemp3 - floorf(fTemp3)) * (ftbl0testsynthSIG0[(iTemp4 + 1)] - ftbl0testsynthSIG0[iTemp4]))));
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			
		}
		
	}

	
};


#endif
