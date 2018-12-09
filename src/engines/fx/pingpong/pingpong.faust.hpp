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
	float 	fTempPerm1;
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	int 	IOTA;
	float 	fRec2[4194304];
	FAUSTFLOAT 	fslider1;
	float 	fConst3;
	FAUSTFLOAT 	fcheckbox0;
	float 	fVec0[262144];
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
	FAUSTFLOAT 	fbargraph10;
	FAUSTFLOAT 	fbargraph11;
	FAUSTFLOAT 	fbargraph12;
	FAUSTFLOAT 	fbargraph13;
	FAUSTFLOAT 	fbargraph14;
	FAUSTFLOAT 	fbargraph15;
	FAUSTFLOAT 	fbargraph16;
	FAUSTFLOAT 	fbargraph17;
	FAUSTFLOAT 	fbargraph18;
	FAUSTFLOAT 	fbargraph19;
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider2;
	float 	fRec3[2];
	float 	fConst4;
	float 	fTempPerm3;
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fTempPerm8;
	float 	fTempPerm9;
	float 	fRec6[2];
	float 	fRec5[2];
	float 	fTempPerm10;
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	FAUSTFLOAT 	fslider3;
	float 	fTempPerm14;
	float 	fVec1[131072];
	float 	fTempPerm15;
	int 	iTempPerm16;
	int 	iTempPerm17;
	float 	fTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	int 	iTempPerm21;
	int 	iTempPerm22;
	int 	iTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fTempPerm26;
	int 	iTempPerm27;
	float 	fRec4[3];
	float 	fRec0[262144];
	float 	fTempPerm28;
	float 	fVec2[131072];
	float 	fRec7[3];
	float 	fRec1[262144];
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
		fTempPerm1 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = expf((0 - (5.0f / fConst0)));
		fConst2 = (1.0f - fConst1);
		fConst3 = (0.125f * fConst0);
		fTempPerm2 = 0;
		fConst4 = (3.1415926535897931f / fConst0);
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		iTempPerm16 = 0;
		iTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		iTempPerm21 = 0;
		iTempPerm22 = 0;
		iTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		iTempPerm27 = 0;
		fTempPerm28 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.5f;
		fcheckbox0 = 0.0;
		fslider2 = 0.5f;
		fslider3 = 0.5f;
	}
	virtual void instanceClear() {
		IOTA = 0;
		for (int i=0; i<4194304; i++) fRec2[i] = 0;
		for (int i=0; i<262144; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<131072; i++) fVec1[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<262144; i++) fRec0[i] = 0;
		for (int i=0; i<131072; i++) fVec2[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<262144; i++) fRec1[i] = 0;
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
		ui_interface->addHorizontalBargraph("level", &fbargraph19, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline1");
		ui_interface->addHorizontalBargraph("level", &fbargraph18, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline10");
		ui_interface->addHorizontalBargraph("level", &fbargraph9, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline11");
		ui_interface->addHorizontalBargraph("level", &fbargraph8, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline12");
		ui_interface->addHorizontalBargraph("level", &fbargraph7, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline13");
		ui_interface->addHorizontalBargraph("level", &fbargraph6, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline14");
		ui_interface->addHorizontalBargraph("level", &fbargraph5, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline15");
		ui_interface->addHorizontalBargraph("level", &fbargraph4, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline16");
		ui_interface->addHorizontalBargraph("level", &fbargraph3, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline17");
		ui_interface->addHorizontalBargraph("level", &fbargraph2, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline18");
		ui_interface->addHorizontalBargraph("level", &fbargraph1, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline19");
		ui_interface->addHorizontalBargraph("level", &fbargraph0, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline2");
		ui_interface->addHorizontalBargraph("level", &fbargraph17, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline3");
		ui_interface->addHorizontalBargraph("level", &fbargraph16, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline4");
		ui_interface->addHorizontalBargraph("level", &fbargraph15, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline5");
		ui_interface->addHorizontalBargraph("level", &fbargraph14, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline6");
		ui_interface->addHorizontalBargraph("level", &fbargraph13, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline7");
		ui_interface->addHorizontalBargraph("level", &fbargraph12, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline8");
		ui_interface->addHorizontalBargraph("level", &fbargraph11, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline9");
		ui_interface->addHorizontalBargraph("level", &fbargraph10, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("delaytime", &fslider1, 0.5f, 0.01f, 0.999f, 0.001f);
		ui_interface->addHorizontalSlider("feedback", &fslider3, 0.5f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("spread", &fslider0, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("tone", &fslider2, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		int 	iSlow1 = (fSlow0 == 1.0f);
		float 	fSlow2 = float(iSlow1);
		float 	fSlow3 = max(0.01f, min((float)1, float(fslider1)));
		float 	fSlow4 = ((int(float(fcheckbox0)))?(fConst3 * ceilf((4.0f * fSlow3))):float(int((fConst0 * fSlow3))));
		int 	iSlow5 = int((19.0f * fSlow4));
		int 	iSlow6 = int((18.0f * fSlow4));
		int 	iSlow7 = int((17.0f * fSlow4));
		int 	iSlow8 = int((16.0f * fSlow4));
		int 	iSlow9 = int((15.0f * fSlow4));
		int 	iSlow10 = int((14.0f * fSlow4));
		int 	iSlow11 = int((13.0f * fSlow4));
		int 	iSlow12 = int((12.0f * fSlow4));
		int 	iSlow13 = int((11.0f * fSlow4));
		int 	iSlow14 = int((10.0f * fSlow4));
		int 	iSlow15 = int((9.0f * fSlow4));
		int 	iSlow16 = int((8.0f * fSlow4));
		int 	iSlow17 = int((7.0f * fSlow4));
		int 	iSlow18 = int((6.0f * fSlow4));
		int 	iSlow19 = int((5.0f * fSlow4));
		int 	iSlow20 = int((4.0f * fSlow4));
		int 	iSlow21 = int((3.0f * fSlow4));
		int 	iSlow22 = int((2.0f * fSlow4));
		int 	iSlow23 = int(fSlow4);
		int 	iSlow24 = (1 - iSlow1);
		float 	fSlow25 = float(iSlow24);
		float 	fSlow26 = (0.0010000000000000009f * ((1900.0f * float(fslider2)) + 100.0f));
		int 	iSlow27 = int((iSlow23 + 1));
		int 	iSlow28 = int((int((float((iSlow24 * int((1000.0f * fSlow0)))) + fSlow4)) + 1));
		int 	iSlow29 = int(iSlow24);
		float 	fSlow30 = float(fslider3);
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fTempPerm1 = fabsf(fTempPerm0);
			fRec2[IOTA&4194303] = max(fTempPerm1, ((fConst1 * fRec2[(IOTA-1)&4194303]) + (fConst2 * fTempPerm1)));
			fVec0[IOTA&262143] = fSlow4;
			fbargraph0 = fRec2[(IOTA-iSlow5)&4194303];
			fbargraph1 = fRec2[(IOTA-iSlow6)&4194303];
			fbargraph2 = fRec2[(IOTA-iSlow7)&4194303];
			fbargraph3 = fRec2[(IOTA-iSlow8)&4194303];
			fbargraph4 = fRec2[(IOTA-iSlow9)&4194303];
			fbargraph5 = fRec2[(IOTA-iSlow10)&4194303];
			fbargraph6 = fRec2[(IOTA-iSlow11)&4194303];
			fbargraph7 = fRec2[(IOTA-iSlow12)&4194303];
			fbargraph8 = fRec2[(IOTA-iSlow13)&4194303];
			fbargraph9 = fRec2[(IOTA-iSlow14)&4194303];
			fbargraph10 = fRec2[(IOTA-iSlow15)&4194303];
			fbargraph11 = fRec2[(IOTA-iSlow16)&4194303];
			fbargraph12 = fRec2[(IOTA-iSlow17)&4194303];
			fbargraph13 = fRec2[(IOTA-iSlow18)&4194303];
			fbargraph14 = fRec2[(IOTA-iSlow19)&4194303];
			fbargraph15 = fRec2[(IOTA-iSlow20)&4194303];
			fbargraph16 = fRec2[(IOTA-iSlow21)&4194303];
			fbargraph17 = fRec2[(IOTA-iSlow22)&4194303];
			fbargraph18 = fRec2[(IOTA-iSlow23)&4194303];
			fbargraph19 = fRec2[(IOTA-0)&4194303];
			fTempPerm2 = fTempPerm0;
			fRec3[0] = (fSlow26 + (0.999f * fRec3[1]));
			fTempPerm3 = tanf((fConst4 * fRec3[0]));
			fTempPerm4 = (1.0f / fTempPerm3);
			fTempPerm5 = (((fTempPerm4 + 1.0f) / fTempPerm3) + 1.0f);
			fTempPerm6 = (fTempPerm3 * fTempPerm5);
			fTempPerm7 = (0 - (1.0f / fTempPerm6));
			fTempPerm8 = (1.0f - (1.0f / faustpower<2>(fTempPerm3)));
			fTempPerm9 = (1.0f - ((1.0f - fTempPerm4) / fTempPerm3));
			fRec6[0] = ((0.999f * fRec6[1]) + (0.012000000000000011f * ((fVec0[(IOTA-iSlow23)&262143] - fSlow4) / fSlow4)));
			fRec5[0] = fmodf((fRec5[1] + (251.0f - powf(2,(0.083333333333333329f * fRec6[0])))),250);
			fTempPerm10 = min((0.02f * fRec5[0]), (float)1);
			fTempPerm11 = (1.0f - fTempPerm10);
			fTempPerm12 = fRec1[(IOTA-iSlow27)&262143];
			fTempPerm13 = fRec0[(IOTA-iSlow28)&262143];
			fTempPerm14 = (fSlow30 * ((iSlow29)?fTempPerm13:fTempPerm12));
			fVec1[IOTA&131071] = fTempPerm14;
			fTempPerm15 = (fRec5[0] + 250.0f);
			iTempPerm16 = int(fTempPerm15);
			iTempPerm17 = int(min(65537, max(0, (iTempPerm16 + 1))));
			fTempPerm18 = floorf(fTempPerm15);
			fTempPerm19 = (fRec5[0] + (250.0f - fTempPerm18));
			fTempPerm20 = (fTempPerm18 + (-249.0f - fRec5[0]));
			iTempPerm21 = int(min(65537, max(0, iTempPerm16)));
			iTempPerm22 = int(fRec5[0]);
			iTempPerm23 = int(min(65537, max(0, (iTempPerm22 + 1))));
			fTempPerm24 = floorf(fRec5[0]);
			fTempPerm25 = (fRec5[0] - fTempPerm24);
			fTempPerm26 = (fTempPerm24 + (1.0f - fRec5[0]));
			iTempPerm27 = int(min(65537, max(0, iTempPerm22)));
			fRec4[0] = (((((fVec1[(IOTA-iTempPerm27)&131071] * fTempPerm26) + (fTempPerm25 * fVec1[(IOTA-iTempPerm23)&131071])) * fTempPerm10) + (((fVec1[(IOTA-iTempPerm21)&131071] * fTempPerm20) + (fTempPerm19 * fVec1[(IOTA-iTempPerm17)&131071])) * fTempPerm11)) - (((fRec4[2] * fTempPerm9) + (2.0f * (fRec4[1] * fTempPerm8))) / fTempPerm5));
			fRec0[IOTA&262143] = (((fRec4[0] / fTempPerm6) + (fRec4[2] * fTempPerm7)) + (fSlow25 * fTempPerm2));
			fTempPerm28 = (fSlow30 * ((iSlow29)?fTempPerm12:fTempPerm13));
			fVec2[IOTA&131071] = fTempPerm28;
			fRec7[0] = (((fTempPerm10 * ((fTempPerm26 * fVec2[(IOTA-iTempPerm27)&131071]) + (fTempPerm25 * fVec2[(IOTA-iTempPerm23)&131071]))) + (fTempPerm11 * ((fTempPerm20 * fVec2[(IOTA-iTempPerm21)&131071]) + (fTempPerm19 * fVec2[(IOTA-iTempPerm17)&131071])))) - (((fTempPerm9 * fRec7[2]) + (2.0f * (fTempPerm8 * fRec7[1]))) / fTempPerm5));
			fRec1[IOTA&262143] = ((fTempPerm7 * fRec7[2]) + (fTempPerm2 + (fRec7[0] / fTempPerm6)));
			output0[i] = (FAUSTFLOAT)(fRec0[(IOTA-0)&262143] + (fSlow2 * (float)input1[i]));
			output1[i] = (FAUSTFLOAT)fRec1[(IOTA-0)&262143];
			// post processing
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec3[1] = fRec3[0];
			IOTA = IOTA+1;
		}
	}
};


