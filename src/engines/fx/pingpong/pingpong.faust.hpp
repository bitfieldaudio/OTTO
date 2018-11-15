//----------------------------------------------------------
// name: "pingpong"
//
// Code generated with Faust 2.11.10 (https://faust.grame.fr)
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
#define FAUSTCLASS faust_pingpong
#endif

class faust_pingpong : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	float 	fTempPerm0;
	FAUSTFLOAT 	fslider1;
	float 	fRec3[2];
	float 	fConst0;
	float 	fConst1;
	float 	fTempPerm1;
	float 	fTempPerm2;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	FAUSTFLOAT 	fslider2;
	float 	fConst2;
	FAUSTFLOAT 	fcheckbox0;
	int 	IOTA;
	float 	fVec0[262144];
	float 	fRec6[2];
	float 	fRec5[2];
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fTempPerm11;
	FAUSTFLOAT 	fslider3;
	float 	fTempPerm12;
	float 	fVec1[131072];
	float 	fTempPerm13;
	int 	iTempPerm14;
	int 	iTempPerm15;
	float 	fTempPerm16;
	float 	fTempPerm17;
	float 	fTempPerm18;
	int 	iTempPerm19;
	int 	iTempPerm20;
	int 	iTempPerm21;
	float 	fTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	int 	iTempPerm25;
	float 	fRec4[3];
	float 	fRec1[262144];
	float 	fTempPerm26;
	float 	fVec2[131072];
	float 	fRec7[3];
	float 	fRec2[262144];
	float 	fTempPerm27;
	float 	fTempPerm28;
	float 	fConst3;
	float 	fConst4;
	float 	fRec0[262144];
	FAUSTFLOAT 	fbargraph0;
	FAUSTFLOAT 	fbargraph1;
	FAUSTFLOAT 	fbargraph2;
	FAUSTFLOAT 	fbargraph3;
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT 	fbargraph5;
	FAUSTFLOAT 	fbargraph6;
	FAUSTFLOAT 	fbargraph7;
	FAUSTFLOAT 	fbargraph8;
	FAUSTFLOAT 	fbargraph9;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filename", "pingpong");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "pingpong");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415926535897931f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fConst2 = (0.125f * fConst0);
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		iTempPerm14 = 0;
		iTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		iTempPerm19 = 0;
		iTempPerm20 = 0;
		iTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		iTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fConst3 = expf((0 - (100.0f / fConst0)));
		fConst4 = (1.0f - fConst3);
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.5f;
		fslider2 = 0.5f;
		fcheckbox0 = 0.0;
		fslider3 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec3[i] = 0;
		IOTA = 0;
		for (int i=0; i<262144; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<131072; i++) fVec1[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<262144; i++) fRec1[i] = 0;
		for (int i=0; i<131072; i++) fVec2[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<262144; i++) fRec2[i] = 0;
		for (int i=0; i<262144; i++) fRec0[i] = 0;
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
	virtual faust_pingpong* clone() {
		return new faust_pingpong();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("pingpong");
		ui_interface->addCheckButton("bpm_follow", &fcheckbox0);
		ui_interface->openVerticalBox("delayline0");
		ui_interface->addHorizontalBargraph("level", &fbargraph9, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline1");
		ui_interface->addHorizontalBargraph("level", &fbargraph8, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline2");
		ui_interface->addHorizontalBargraph("level", &fbargraph7, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline3");
		ui_interface->addHorizontalBargraph("level", &fbargraph6, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline4");
		ui_interface->addHorizontalBargraph("level", &fbargraph5, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline5");
		ui_interface->addHorizontalBargraph("level", &fbargraph4, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline6");
		ui_interface->addHorizontalBargraph("level", &fbargraph3, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline7");
		ui_interface->addHorizontalBargraph("level", &fbargraph2, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline8");
		ui_interface->addHorizontalBargraph("level", &fbargraph1, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline9");
		ui_interface->addHorizontalBargraph("level", &fbargraph0, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("delaytime", &fslider2, 0.5f, 0.01f, 0.999f, 0.001f);
		ui_interface->addHorizontalSlider("feedback", &fslider3, 0.5f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("spread", &fslider0, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("tone", &fslider1, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		int 	iSlow1 = (fSlow0 == 1.0f);
		float 	fSlow2 = float(iSlow1);
		int 	iSlow3 = (1 - iSlow1);
		float 	fSlow4 = float(iSlow3);
		float 	fSlow5 = (0.0010000000000000009f * ((1900.0f * float(fslider1)) + 100.0f));
		float 	fSlow6 = max(0.01f, min((float)1, float(fslider2)));
		float 	fSlow7 = ((int(float(fcheckbox0)))?(fConst2 * ceilf((4.0f * fSlow6))):float(int((fConst0 * fSlow6))));
		int 	iSlow8 = int(fSlow7);
		int 	iSlow9 = int((iSlow8 + 1));
		int 	iSlow10 = int((int((float((iSlow3 * int((1000.0f * fSlow0)))) + fSlow7)) + 1));
		int 	iSlow11 = int(iSlow3);
		float 	fSlow12 = float(fslider3);
		int 	iSlow13 = int((0.90000000000000002f * fSlow7));
		int 	iSlow14 = int((0.80000000000000004f * fSlow7));
		int 	iSlow15 = int((0.69999999999999996f * fSlow7));
		int 	iSlow16 = int((0.59999999999999998f * fSlow7));
		int 	iSlow17 = int((0.5f * fSlow7));
		int 	iSlow18 = int((0.40000000000000002f * fSlow7));
		int 	iSlow19 = int((0.29999999999999999f * fSlow7));
		int 	iSlow20 = int((0.20000000000000001f * fSlow7));
		int 	iSlow21 = int((0.10000000000000001f * fSlow7));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fRec3[0] = (fSlow5 + (0.999f * fRec3[1]));
			fTempPerm1 = tanf((fConst1 * fRec3[0]));
			fTempPerm2 = (1.0f / fTempPerm1);
			fTempPerm3 = (((fTempPerm2 + 1.0f) / fTempPerm1) + 1.0f);
			fTempPerm4 = (fTempPerm1 * fTempPerm3);
			fTempPerm5 = (0 - (1.0f / fTempPerm4));
			fTempPerm6 = (1.0f - (1.0f / faustpower<2>(fTempPerm1)));
			fTempPerm7 = (1.0f - ((1.0f - fTempPerm2) / fTempPerm1));
			fVec0[IOTA&262143] = fSlow7;
			fRec6[0] = ((0.999f * fRec6[1]) + (0.012000000000000011f * ((fVec0[(IOTA-iSlow8)&262143] - fSlow7) / fSlow7)));
			fRec5[0] = fmodf((fRec5[1] + (251.0f - powf(2,(0.083333333333333329f * fRec6[0])))),250);
			fTempPerm8 = min((0.02f * fRec5[0]), (float)1);
			fTempPerm9 = (1.0f - fTempPerm8);
			fTempPerm10 = fRec2[(IOTA-iSlow9)&262143];
			fTempPerm11 = fRec1[(IOTA-iSlow10)&262143];
			fTempPerm12 = (fSlow12 * ((iSlow11)?fTempPerm11:fTempPerm10));
			fVec1[IOTA&131071] = fTempPerm12;
			fTempPerm13 = (fRec5[0] + 250.0f);
			iTempPerm14 = int(fTempPerm13);
			iTempPerm15 = int(min(65537, max(0, (iTempPerm14 + 1))));
			fTempPerm16 = floorf(fTempPerm13);
			fTempPerm17 = (fRec5[0] + (250.0f - fTempPerm16));
			fTempPerm18 = (fTempPerm16 + (-249.0f - fRec5[0]));
			iTempPerm19 = int(min(65537, max(0, iTempPerm14)));
			iTempPerm20 = int(fRec5[0]);
			iTempPerm21 = int(min(65537, max(0, (iTempPerm20 + 1))));
			fTempPerm22 = floorf(fRec5[0]);
			fTempPerm23 = (fRec5[0] - fTempPerm22);
			fTempPerm24 = (fTempPerm22 + (1.0f - fRec5[0]));
			iTempPerm25 = int(min(65537, max(0, iTempPerm20)));
			fRec4[0] = (((((fVec1[(IOTA-iTempPerm25)&131071] * fTempPerm24) + (fTempPerm23 * fVec1[(IOTA-iTempPerm21)&131071])) * fTempPerm8) + (((fVec1[(IOTA-iTempPerm19)&131071] * fTempPerm18) + (fTempPerm17 * fVec1[(IOTA-iTempPerm15)&131071])) * fTempPerm9)) - (((fRec4[2] * fTempPerm7) + (2.0f * (fRec4[1] * fTempPerm6))) / fTempPerm3));
			fRec1[IOTA&262143] = (((fRec4[0] / fTempPerm4) + (fRec4[2] * fTempPerm5)) + (fSlow4 * fTempPerm0));
			fTempPerm26 = (fSlow12 * ((iSlow11)?fTempPerm10:fTempPerm11));
			fVec2[IOTA&131071] = fTempPerm26;
			fRec7[0] = (((fTempPerm8 * ((fTempPerm24 * fVec2[(IOTA-iTempPerm25)&131071]) + (fTempPerm23 * fVec2[(IOTA-iTempPerm21)&131071]))) + (fTempPerm9 * ((fTempPerm18 * fVec2[(IOTA-iTempPerm19)&131071]) + (fTempPerm17 * fVec2[(IOTA-iTempPerm15)&131071])))) - (((fTempPerm7 * fRec7[2]) + (2.0f * (fTempPerm6 * fRec7[1]))) / fTempPerm3));
			fRec2[IOTA&262143] = (((fRec7[0] / fTempPerm4) + (fTempPerm5 * fRec7[2])) + fTempPerm0);
			fTempPerm27 = (fRec1[(IOTA-0)&262143] + (fSlow2 * (float)input1[i]));
			fTempPerm28 = fabsf(fTempPerm27);
			fRec0[IOTA&262143] = max(fTempPerm28, ((fConst3 * fRec0[(IOTA-1)&262143]) + (fConst4 * fTempPerm28)));
			fbargraph0 = fRec0[(IOTA-iSlow13)&262143];
			fbargraph1 = fRec0[(IOTA-iSlow14)&262143];
			fbargraph2 = fRec0[(IOTA-iSlow15)&262143];
			fbargraph3 = fRec0[(IOTA-iSlow16)&262143];
			fbargraph4 = fRec0[(IOTA-iSlow17)&262143];
			fbargraph5 = fRec0[(IOTA-iSlow18)&262143];
			fbargraph6 = fRec0[(IOTA-iSlow19)&262143];
			fbargraph7 = fRec0[(IOTA-iSlow20)&262143];
			fbargraph8 = fRec0[(IOTA-iSlow21)&262143];
			fbargraph9 = fRec0[(IOTA-0)&262143];
			output0[i] = (FAUSTFLOAT)fTempPerm27;
			output1[i] = (FAUSTFLOAT)fRec2[(IOTA-0)&262143];
			// post processing
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			IOTA = IOTA+1;
			fRec3[1] = fRec3[0];
		}
	}
};


