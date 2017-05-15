/* ------------------------------------------------------------
name: "TestSynth"
Code generated with Faust 2.0.a64 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __faust_testsynth_H__
#define  __faust_testsynth_H__

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


class faust_testsynthSIG0 {
	
  private:
	
	int iRec0[2];
	
  public:
	
	int getNumInputsfaust_testsynthSIG0() {
		return 0;
		
	}
	int getNumOutputsfaust_testsynthSIG0() {
		return 1;
		
	}
	int getInputRatefaust_testsynthSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatefaust_testsynthSIG0(int channel) {
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
	
	void instanceInitfaust_testsynthSIG0(int samplingFreq) {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
			
		}
		
	}
	
	void fillfaust_testsynthSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			output[i] = sinf((9.58738019e-05f * float((iRec0[0] + -1))));
			iRec0[1] = iRec0[0];
			
		}
		
	}
};

faust_testsynthSIG0* newfaust_testsynthSIG0() { return (faust_testsynthSIG0*)new faust_testsynthSIG0(); }
void deletefaust_testsynthSIG0(faust_testsynthSIG0* dsp) { delete dsp; }

static float ftbl0faust_testsynthSIG0[65537];

#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_testsynth
#endif

class faust_testsynth : public dsp {
	
 private:
	
	int fSamplingFreq;
	float fRec1[2];
	float fConst0;
	FAUSTFLOAT fVslider0;
	
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
		faust_testsynthSIG0* sig0 = newfaust_testsynthSIG0();
		sig0->instanceInitfaust_testsynthSIG0(samplingFreq);
		sig0->fillfaust_testsynthSIG0(65537, ftbl0faust_testsynthSIG0);
		deletefaust_testsynthSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(440.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
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
	
	virtual faust_testsynth* clone() {
		return new faust_testsynth();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("0x00");
		ui_interface->addVerticalSlider("FREQ", &fVslider0, 440.0f, 60.0f, 900.0f, 9.99999975e-05f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (fConst0 * float(fVslider0));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow0 + (fRec1[1] - floorf((fSlow0 + fRec1[1]))));
			float fTemp0 = (65536.0f * fRec1[0]);
			int iTemp1 = int(fTemp0);
			output0[i] = FAUSTFLOAT((ftbl0faust_testsynthSIG0[iTemp1] + ((fTemp0 - floorf(fTemp0)) * (ftbl0faust_testsynthSIG0[(iTemp1 + 1)] - ftbl0faust_testsynthSIG0[iTemp1]))));
			fRec1[1] = fRec1[0];
			
		}
		
	}

	
};


#endif
