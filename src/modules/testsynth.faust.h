//----------------------------------------------------------
// name: "TestSynth"
//
// Code generated with Faust 0.9.104 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
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
#define FAUSTCLASS faust_testsynth
#endif

class faust_testsynth : public dsp {
  private:
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec0[2];
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			for (int i=0; i<2; i++) iRec0[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec0[0] = (iRec0[1] + 1);
				output[i] = sinf((9.58738e-05f * float((iRec0[0] + -1))));
				// post processing
				iRec0[1] = iRec0[0];
			}
		}
	};


	static float 	ftbl0[65537];
	FAUSTFLOAT 	fslider0;
	float 	fConst0;
	float 	fRec1[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("name", "TestSynth");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(65537,ftbl0);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / float(min(1.92e+05f, max(1e+03f, (float)fSamplingFreq))));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 4.4e+02f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec1[i] = 0;
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
		ui_interface->openVerticalBox("TestSynth");
		ui_interface->addVerticalSlider("FREQ", &fslider0, 4.4e+02f, 6e+01f, 9e+02f, 0.0001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (fConst0 * float(fslider0));
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			fRec1[0] = (fSlow0 + (fRec1[1] - floorf((fSlow0 + fRec1[1]))));
			float fTemp0 = (65536.0f * fRec1[0]);
			int iTemp1 = int(fTemp0);
			float fTemp2 = ftbl0[iTemp1];
			output0[i] = (FAUSTFLOAT)(fTemp2 + ((fTemp0 - floorf(fTemp0)) * (ftbl0[(iTemp1 + 1)] - fTemp2)));
			// post processing
			fRec1[1] = fRec1[0];
		}
	}
};


float 	faust_testsynth::ftbl0[65537];
