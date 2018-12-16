//----------------------------------------------------------
// name: "chorus"
//
// Code generated with Faust 2.13.11 (https://faust.grame.fr)
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
#define FAUSTCLASS faust_chorus
#endif

class faust_chorus : public dsp {
  private:
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec1[2];
		float 	fTempPerm2;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm2 = 0;
			for (int i=0; i<2; i++) iRec1[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec1[0] = (iRec1[1] + 1);
				fTempPerm2 = cosf((9.5873799242852573e-05f * float((iRec1[0] + -1))));
				output[i] = fTempPerm2;
				// post processing
				iRec1[1] = iRec1[0];
			}
		}
	};


	class SIG1 {
	  private:
		int fSamplingFreq;
		int 	iRec6[2];
		float 	fTempPerm7;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm7 = 0;
			for (int i=0; i<2; i++) iRec6[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec6[0] = (iRec6[1] + 1);
				fTempPerm7 = sinf((9.5873799242852573e-05f * float((iRec6[0] + -1))));
				output[i] = fTempPerm7;
				// post processing
				iRec6[1] = iRec6[0];
			}
		}
	};


	float 	fTempPerm0;
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	float 	fTempPerm1;
	int 	IOTA;
	float 	fVec0[16384];
	static float 	ftbl0[65536];
	FAUSTFLOAT 	fslider1;
	float 	fRec3[2];
	float 	fConst0;
	float 	fConst1;
	float 	fTempPerm3;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider2;
	float 	fRec5[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec4[2];
	float 	fTempPerm4;
	int 	iTempPerm5;
	float 	fTempPerm6;
	static float 	ftbl1[65536];
	float 	fConst2;
	float 	fTempPerm8;
	float 	fRec7[2];
	float 	fTempPerm9;
	float 	fTempPerm10;
	int 	iTempPerm11;
	float 	fTempPerm12;
	float 	fConst3;
	float 	fTempPerm13;
	float 	fRec8[2];
	float 	fTempPerm14;
	int 	iTempPerm15;
	float 	fTempPerm16;
	float 	fConst4;
	float 	fTempPerm17;
	float 	fRec9[2];
	int 	iTempPerm18;
	float 	fTempPerm19;
	int 	iTempPerm20;
	float 	fTempPerm21;
	float 	fConst5;
	float 	fTempPerm22;
	float 	fRec10[2];
	int 	iTempPerm23;
	float 	fTempPerm24;
	int 	iTempPerm25;
	float 	fTempPerm26;
	float 	fConst6;
	float 	fTempPerm27;
	float 	fRec11[2];
	int 	iTempPerm28;
	float 	fTempPerm29;
	int 	iTempPerm30;
	float 	fTempPerm31;
	float 	fConst7;
	float 	fTempPerm32;
	float 	fRec12[2];
	int 	iTempPerm33;
	float 	fTempPerm34;
	int 	iTempPerm35;
	float 	fTempPerm36;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filename", "chorus");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "chorus");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(65536,ftbl0);
		SIG1 sig1;
		sig1.init(samplingFreq);
		sig1.fill(65536,ftbl1);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (0.14285714285714285f / fConst0);
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		iTempPerm5 = 0;
		fTempPerm6 = 0;
		fConst2 = (1.0f / fConst0);
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		iTempPerm11 = 0;
		fTempPerm12 = 0;
		fConst3 = (0.33333333333333331f / fConst0);
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		iTempPerm15 = 0;
		fTempPerm16 = 0;
		fConst4 = (0.125f / fConst0);
		fTempPerm17 = 0;
		iTempPerm18 = 0;
		fTempPerm19 = 0;
		iTempPerm20 = 0;
		fTempPerm21 = 0;
		fConst5 = (0.16666666666666666f / fConst0);
		fTempPerm22 = 0;
		iTempPerm23 = 0;
		fTempPerm24 = 0;
		iTempPerm25 = 0;
		fTempPerm26 = 0;
		fConst6 = (0.25f / fConst0);
		fTempPerm27 = 0;
		iTempPerm28 = 0;
		fTempPerm29 = 0;
		iTempPerm30 = 0;
		fTempPerm31 = 0;
		fConst7 = (0.5f / fConst0);
		fTempPerm32 = 0;
		iTempPerm33 = 0;
		fTempPerm34 = 0;
		iTempPerm35 = 0;
		fTempPerm36 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.5f;
		fslider2 = 0.5f;
		fslider3 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec0[i] = 0;
		IOTA = 0;
		for (int i=0; i<16384; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
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
	virtual faust_chorus* clone() {
		return new faust_chorus();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("chorus");
		ui_interface->addHorizontalSlider("delay", &fslider2, 0.5f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("depth", &fslider0, 0.5f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("deviation", &fslider3, 0.5f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("rate", &fslider1, 0.5f, 0.0f, 1.0f, 0.0001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * float(fslider0));
		float 	fSlow1 = (0.0010000000000000009f * ((7.0f * float(fslider1)) + 0.01f));
		float 	fSlow2 = (8.1920000000000073f * float(fslider2));
		float 	fSlow3 = (6.2500000000000056e-05f * float(fslider3));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
			fTempPerm1 = (fRec0[0] * fTempPerm0);
			fVec0[IOTA&16383] = fTempPerm1;
			fRec3[0] = (fSlow1 + (0.999f * fRec3[1]));
			fTempPerm3 = (fRec2[1] + (fConst1 * fRec3[0]));
			fRec2[0] = (fTempPerm3 - floorf(fTempPerm3));
			fRec5[0] = (fSlow2 + (0.999f * fRec5[1]));
			fRec4[0] = ((0.999f * fRec4[1]) + (fSlow3 * fRec5[0]));
			fTempPerm4 = min((float)8192, ((0.875f * fRec5[0]) + (fRec4[0] * (0 - ftbl0[int((65536.0f * fRec2[0]))]))));
			iTempPerm5 = int(fTempPerm4);
			fTempPerm6 = floorf(fTempPerm4);
			fTempPerm8 = (fRec7[1] + (fConst2 * fRec3[0]));
			fRec7[0] = (fTempPerm8 - floorf(fTempPerm8));
			fTempPerm9 = min((float)8192, ((0.125f * fRec5[0]) + (fRec4[0] * ftbl1[int((65536.0f * fRec7[0]))])));
			fTempPerm10 = floorf(fTempPerm9);
			iTempPerm11 = int(fTempPerm9);
			fTempPerm12 = ((1.0f - fRec0[0]) * fTempPerm0);
			fTempPerm13 = (fRec8[1] + (fConst3 * fRec3[0]));
			fRec8[0] = (fTempPerm13 - floorf(fTempPerm13));
			fTempPerm14 = min((float)8192, ((0.375f * fRec5[0]) + (fRec4[0] * ftbl0[int((65536.0f * fRec8[0]))])));
			iTempPerm15 = int(fTempPerm14);
			fTempPerm16 = floorf(fTempPerm14);
			output0[i] = (FAUSTFLOAT)(((0.70710678118654757f * ((fVec0[(IOTA-int(min(8193, max(0, iTempPerm15))))&16383] * (fTempPerm16 + (1.0f - fTempPerm14))) + ((fTempPerm14 - fTempPerm16) * fVec0[(IOTA-int(min(8193, max(0, (iTempPerm15 + 1)))))&16383]))) + (((fTempPerm9 - fTempPerm10) * fVec0[(IOTA-int(min(8193, max(0, (iTempPerm11 + 1)))))&16383]) + (fTempPerm12 + (fVec0[(IOTA-int(min(8193, max(0, iTempPerm11))))&16383] * (fTempPerm10 + (1.0f - fTempPerm9)))))) - (0.70710678118654746f * ((fVec0[(IOTA-int(min(8193, max(0, iTempPerm5))))&16383] * (fTempPerm6 + (1.0f - fTempPerm4))) + ((fTempPerm4 - fTempPerm6) * fVec0[(IOTA-int(min(8193, max(0, (iTempPerm5 + 1)))))&16383]))));
			fTempPerm17 = (fRec9[1] + (fConst4 * fRec3[0]));
			fRec9[0] = (fTempPerm17 - floorf(fTempPerm17));
			iTempPerm18 = int((65536.0f * fRec9[0]));
			fTempPerm19 = min((float)8192, (fRec5[0] + (fRec4[0] * ((0.70710678118654735f * ftbl1[iTempPerm18]) - (0.70710678118654768f * ftbl0[iTempPerm18])))));
			iTempPerm20 = int(fTempPerm19);
			fTempPerm21 = floorf(fTempPerm19);
			fTempPerm22 = (fRec10[1] + (fConst5 * fRec3[0]));
			fRec10[0] = (fTempPerm22 - floorf(fTempPerm22));
			iTempPerm23 = int((65536.0f * fRec10[0]));
			fTempPerm24 = min((float)8192, ((0.75f * fRec5[0]) + (fRec4[0] * (0 - ((0.70710678118654768f * ftbl1[iTempPerm23]) + (0.70710678118654746f * ftbl0[iTempPerm23]))))));
			iTempPerm25 = int(fTempPerm24);
			fTempPerm26 = floorf(fTempPerm24);
			fTempPerm27 = (fRec11[1] + (fConst6 * fRec3[0]));
			fRec11[0] = (fTempPerm27 - floorf(fTempPerm27));
			iTempPerm28 = int((65536.0f * fRec11[0]));
			fTempPerm29 = min((float)8192, ((0.5f * fRec5[0]) + (fRec4[0] * ((0.70710678118654757f * ftbl0[iTempPerm28]) - (0.70710678118654746f * ftbl1[iTempPerm28])))));
			iTempPerm30 = int(fTempPerm29);
			fTempPerm31 = floorf(fTempPerm29);
			fTempPerm32 = (fRec12[1] + (fConst7 * fRec3[0]));
			fRec12[0] = (fTempPerm32 - floorf(fTempPerm32));
			iTempPerm33 = int((65536.0f * fRec12[0]));
			fTempPerm34 = min((float)8192, ((0.25f * fRec5[0]) + (fRec4[0] * ((0.70710678118654757f * ftbl1[iTempPerm33]) + (0.70710678118654746f * ftbl0[iTempPerm33])))));
			iTempPerm35 = int(fTempPerm34);
			fTempPerm36 = floorf(fTempPerm34);
			output1[i] = (FAUSTFLOAT)(fTempPerm12 - ((((0.38268343236508973f * ((fVec0[(IOTA-int(min(8193, max(0, iTempPerm35))))&16383] * (fTempPerm36 + (1.0f - fTempPerm34))) + ((fTempPerm34 - fTempPerm36) * fVec0[(IOTA-int(min(8193, max(0, (iTempPerm35 + 1)))))&16383]))) + (0.92387953251128674f * ((fVec0[(IOTA-int(min(8193, max(0, iTempPerm30))))&16383] * (fTempPerm31 + (1.0f - fTempPerm29))) + ((fTempPerm29 - fTempPerm31) * fVec0[(IOTA-int(min(8193, max(0, (iTempPerm30 + 1)))))&16383])))) + (0.92387953251128685f * ((fVec0[(IOTA-int(min(8193, max(0, iTempPerm25))))&16383] * (fTempPerm26 + (1.0f - fTempPerm24))) + ((fTempPerm24 - fTempPerm26) * fVec0[(IOTA-int(min(8193, max(0, (iTempPerm25 + 1)))))&16383])))) + (0.38268343236509034f * ((fVec0[(IOTA-int(min(8193, max(0, iTempPerm20))))&16383] * (fTempPerm21 + (1.0f - fTempPerm19))) + ((fTempPerm19 - fTempPerm21) * fVec0[(IOTA-int(min(8193, max(0, (iTempPerm20 + 1)))))&16383])))));
			// post processing
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			IOTA = IOTA+1;
			fRec0[1] = fRec0[0];
		}
	}
};


float 	faust_chorus::ftbl0[65536];
float 	faust_chorus::ftbl1[65536];
