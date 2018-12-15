//----------------------------------------------------------
// name: "wormhole"
//
// Code generated with Faust 2.13.11 (https://faust.grame.fr)
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
#define FAUSTCLASS faust_wormhole
#endif

class faust_wormhole : public dsp {
  private:
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec14[2];
		float 	fTempPerm3;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm3 = 0;
			for (int i=0; i<2; i++) iRec14[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec14[0] = (iRec14[1] + 1);
				fTempPerm3 = sinf((9.5873799242852573e-05f * float((iRec14[0] + -1))));
				output[i] = fTempPerm3;
				// post processing
				iRec14[1] = iRec14[0];
			}
		}
	};


	float 	fTempPerm0;
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider0;
	float 	fRec13[2];
	float 	fRec12[3];
	float 	fTempPerm2;
	int 	IOTA;
	float 	fVec0[512];
	static float 	ftbl0[65536];
	float 	fConst6;
	float 	fRec15[2];
	float 	fTempPerm4;
	float 	fTempPerm5;
	float 	fTempPerm6;
	int 	iTempPerm7;
	int 	iTempPerm8;
	float 	fTempPerm9;
	float 	fTempPerm10;
	float 	fTempPerm11;
	int 	iTempPerm12;
	float 	fRec10[2];
	float 	fTempPerm13;
	float 	fVec1[1024];
	float 	fTempPerm14;
	float 	fTempPerm15;
	int 	iTempPerm16;
	int 	iTempPerm17;
	float 	fTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	int 	iTempPerm21;
	float 	fRec8[2];
	float 	fTempPerm22;
	float 	fVec2[4096];
	float 	fTempPerm23;
	float 	fTempPerm24;
	int 	iTempPerm25;
	int 	iTempPerm26;
	float 	fTempPerm27;
	float 	fTempPerm28;
	float 	fTempPerm29;
	int 	iTempPerm30;
	float 	fRec6[2];
	float 	fTempPerm31;
	float 	fVec3[4096];
	float 	fTempPerm32;
	float 	fTempPerm33;
	int 	iTempPerm34;
	int 	iTempPerm35;
	float 	fTempPerm36;
	float 	fTempPerm37;
	float 	fTempPerm38;
	int 	iTempPerm39;
	float 	fRec4[2];
	float 	fTempPerm40;
	float 	fVec4[2048];
	float 	fTempPerm41;
	int 	iTempPerm42;
	float 	fTempPerm43;
	float 	fRec0[2];
	float 	fRec24[3];
	float 	fTempPerm44;
	float 	fVec5[512];
	float 	fRec22[2];
	float 	fTempPerm45;
	float 	fVec6[1024];
	float 	fRec20[2];
	float 	fTempPerm46;
	float 	fVec7[4096];
	float 	fRec18[2];
	float 	fTempPerm47;
	float 	fVec8[4096];
	float 	fRec16[2];
	float 	fTempPerm48;
	float 	fVec9[2048];
	float 	fTempPerm49;
	int 	iTempPerm50;
	float 	fTempPerm51;
	float 	fRec1[2];
	float 	fConst7;
	float 	fConst8;
	float 	fConst9;
	float 	fConst10;
	float 	fConst11;
	float 	fConst12;
	float 	fConst13;
	float 	fRec34[3];
	float 	fTempPerm52;
	float 	fVec10[512];
	float 	fRec32[2];
	float 	fTempPerm53;
	float 	fVec11[1024];
	float 	fRec30[2];
	float 	fTempPerm54;
	float 	fVec12[4096];
	float 	fRec28[2];
	float 	fTempPerm55;
	float 	fVec13[4096];
	float 	fRec26[2];
	float 	fTempPerm56;
	float 	fVec14[4096];
	float 	fTempPerm57;
	int 	iTempPerm58;
	float 	fTempPerm59;
	float 	fRec25[3];
	float 	fConst14;
	float 	fRec2[2];
	float 	fTempPerm60;
	float 	fTempPerm61;
	float 	fRec35[2];
	float 	fTempPerm62;
	float 	fRec44[3];
	float 	fTempPerm63;
	float 	fVec15[512];
	float 	fRec42[2];
	float 	fTempPerm64;
	float 	fVec16[1024];
	float 	fRec40[2];
	float 	fTempPerm65;
	float 	fVec17[4096];
	float 	fRec38[2];
	float 	fTempPerm66;
	float 	fVec18[4096];
	float 	fRec36[2];
	float 	fTempPerm67;
	float 	fVec19[131072];
	float 	fTempPerm68;
	float 	fTempPerm69;
	int 	iTempPerm70;
	float 	fTempPerm71;
	int 	iTempPerm72;
	float 	fTempPerm73;
	FAUSTFLOAT 	fslider1;
	float 	fRec3[2];
	float 	fTempPerm74;
	FAUSTFLOAT 	fslider2;
	float 	fRec45[2];
	float 	fTempPerm75;
	float 	fTempPerm76;
	float 	fTempPerm77;
	float 	fTempPerm78;
	float 	fConst15;
	float 	fConst16;
	FAUSTFLOAT 	fslider3;
	float 	fRec48[2];
	float 	fTempPerm79;
	float 	fConst17;
	float 	fRec50[2];
	int 	iTempPerm80;
	int 	iVec20[2];
	int 	iConst18;
	int 	iRec51[2];
	float 	fTempPerm81;
	float 	fTempPerm82;
	float 	fRec47[2];
	float 	fRec46[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filename", "wormhole");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "wormhole");
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
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fTempPerm0 = 0;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = tanf((31415.926535897932f / fConst0));
		fConst2 = (2.0f * (1.0f - (1.0f / faustpower<2>(fConst1))));
		fConst3 = (1.0f / fConst1);
		fConst4 = (((fConst3 + -1.4142135623730949f) / fConst1) + 1.0f);
		fConst5 = (1.0f / (((fConst3 + 1.4142135623730949f) / fConst1) + 1.0f));
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst6 = (0.25f / fConst0);
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		iTempPerm7 = 0;
		iTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		iTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		iTempPerm16 = 0;
		iTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		iTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		iTempPerm25 = 0;
		iTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		iTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		iTempPerm34 = 0;
		iTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		iTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		iTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		iTempPerm50 = 0;
		fTempPerm51 = 0;
		fConst7 = tanf((314.15926535897933f / fConst0));
		fConst8 = faustpower<2>(fConst7);
		fConst9 = (1.0f / fConst8);
		fConst10 = (2.0f * (1.0f - fConst9));
		fConst11 = (1.0f / fConst7);
		fConst12 = (((fConst11 + -1.4142135623730949f) / fConst7) + 1.0f);
		fConst13 = (1.0f / (((fConst11 + 1.4142135623730949f) / fConst7) + 1.0f));
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		iTempPerm58 = 0;
		fTempPerm59 = 0;
		fConst14 = (0 - (2.0f / fConst8));
		fTempPerm60 = 0;
		fTempPerm61 = 0;
		fTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		fTempPerm66 = 0;
		fTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		iTempPerm70 = 0;
		fTempPerm71 = 0;
		iTempPerm72 = 0;
		fTempPerm73 = 0;
		fTempPerm74 = 0;
		fTempPerm75 = 0;
		fTempPerm76 = 0;
		fTempPerm77 = 0;
		fTempPerm78 = 0;
		fConst15 = expf((0 - (1000.0f / fConst0)));
		fConst16 = expf((0 - (25.0f / fConst0)));
		fTempPerm79 = 0;
		fConst17 = (1.0f - fConst15);
		iTempPerm80 = 0;
		iConst18 = int((0.01f * fConst0));
		fTempPerm81 = 0;
		fTempPerm82 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.0f;
		fslider2 = 0.0f;
		fslider3 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<3; i++) fRec12[i] = 0;
		IOTA = 0;
		for (int i=0; i<512; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<1024; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<4096; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<4096; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2048; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec24[i] = 0;
		for (int i=0; i<512; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<1024; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<4096; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<4096; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2048; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) fRec34[i] = 0;
		for (int i=0; i<512; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<1024; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<4096; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<4096; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<4096; i++) fVec14[i] = 0;
		for (int i=0; i<3; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<3; i++) fRec44[i] = 0;
		for (int i=0; i<512; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<1024; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<4096; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<4096; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<131072; i++) fVec19[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) iVec20[i] = 0;
		for (int i=0; i<2; i++) iRec51[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
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
	virtual faust_wormhole* clone() {
		return new faust_wormhole();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("wormhole");
		ui_interface->addHorizontalSlider("LENGTH", &fslider0, 0.5f, 0.0f, 1.5f, 0.01f);
		ui_interface->declare(&fslider3, "scale", "log");
		ui_interface->addHorizontalSlider("SHAPE", &fslider3, 1.0f, 0.0f, 2.0f, 0.01f);
		ui_interface->addHorizontalSlider("SHIMMER", &fslider1, 0.0f, 0.0f, 1.2f, 0.01f);
		ui_interface->addHorizontalSlider("SPREAD", &fslider2, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = (0.0010000000000000009f * float(fslider0));
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = (1.0f - fSlow1);
		float 	fSlow3 = (0.0010000000000000009f * float(fslider2));
		float 	fSlow4 = (0.0010000000000000009f * float(fslider3));
		//zone2b
		//zone3
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fTempPerm0 = (float)input0[i];
			fTempPerm1 = (fRec0[1] + fRec2[1]);
			fRec13[0] = (fSlow0 + (0.999f * fRec13[1]));
			fRec12[0] = ((fRec13[0] * (fRec3[1] + (fTempPerm1 + fRec1[1]))) - (fConst5 * ((fConst4 * fRec12[2]) + (fConst2 * fRec12[1]))));
			fTempPerm2 = (((0.59999999999999998f * fRec10[1]) + (fConst5 * (fRec12[2] + (fRec12[0] + (2.0f * fRec12[1]))))) + fTempPerm0);
			fVec0[IOTA&511] = fTempPerm2;
			fRec15[0] = (fConst6 + (fRec15[1] - floorf((fConst6 + fRec15[1]))));
			fTempPerm4 = ((0.001f * ftbl0[int((65536.0f * fRec15[0]))]) + 1.0f);
			fTempPerm5 = (441.0f * fTempPerm4);
			fTempPerm6 = (fTempPerm5 + -1.0f);
			iTempPerm7 = int(fTempPerm6);
			iTempPerm8 = int(min(2049, max(0, (iTempPerm7 + 1))));
			fTempPerm9 = floorf(fTempPerm6);
			fTempPerm10 = (fTempPerm5 + (-1.0f - fTempPerm9));
			fTempPerm11 = (fTempPerm9 + (2.0f - fTempPerm5));
			iTempPerm12 = int(min(2049, max(0, iTempPerm7)));
			fRec10[0] = ((fVec0[(IOTA-iTempPerm12)&511] * fTempPerm11) + (fTempPerm10 * fVec0[(IOTA-iTempPerm8)&511]));
			float 	fRec11 = (0 - (0.59999999999999998f * fVec0[IOTA&511]));
			fTempPerm13 = (fRec10[1] + (fRec11 + (0.59999999999999998f * fRec8[1])));
			fVec1[IOTA&1023] = fTempPerm13;
			fTempPerm14 = (727.0f * fTempPerm4);
			fTempPerm15 = (fTempPerm14 + -1.0f);
			iTempPerm16 = int(fTempPerm15);
			iTempPerm17 = int(min(2049, max(0, (iTempPerm16 + 1))));
			fTempPerm18 = floorf(fTempPerm15);
			fTempPerm19 = (fTempPerm14 + (-1.0f - fTempPerm18));
			fTempPerm20 = (fTempPerm18 + (2.0f - fTempPerm14));
			iTempPerm21 = int(min(2049, max(0, iTempPerm16)));
			fRec8[0] = ((fVec1[(IOTA-iTempPerm21)&1023] * fTempPerm20) + (fTempPerm19 * fVec1[(IOTA-iTempPerm17)&1023]));
			float 	fRec9 = (0 - (0.59999999999999998f * fVec1[IOTA&1023]));
			fTempPerm22 = (fRec8[1] + (fRec9 + (0.59999999999999998f * fRec6[1])));
			fVec2[IOTA&4095] = fTempPerm22;
			fTempPerm23 = (2403.0f * fTempPerm4);
			fTempPerm24 = (fTempPerm23 + -1.0f);
			iTempPerm25 = int(fTempPerm24);
			iTempPerm26 = int(min(2049, max(0, (iTempPerm25 + 1))));
			fTempPerm27 = floorf(fTempPerm24);
			fTempPerm28 = (fTempPerm23 + (-1.0f - fTempPerm27));
			fTempPerm29 = (fTempPerm27 + (2.0f - fTempPerm23));
			iTempPerm30 = int(min(2049, max(0, iTempPerm25)));
			fRec6[0] = ((fVec2[(IOTA-iTempPerm30)&4095] * fTempPerm29) + (fTempPerm28 * fVec2[(IOTA-iTempPerm26)&4095]));
			float 	fRec7 = (0 - (0.59999999999999998f * fVec2[IOTA&4095]));
			fTempPerm31 = (fRec6[1] + (fRec7 + (0.59999999999999998f * fRec4[1])));
			fVec3[IOTA&4095] = fTempPerm31;
			fTempPerm32 = (3119.0f * fTempPerm4);
			fTempPerm33 = (fTempPerm32 + -1.0f);
			iTempPerm34 = int(fTempPerm33);
			iTempPerm35 = int(min(2049, max(0, (iTempPerm34 + 1))));
			fTempPerm36 = floorf(fTempPerm33);
			fTempPerm37 = (fTempPerm32 + (-1.0f - fTempPerm36));
			fTempPerm38 = (fTempPerm36 + (2.0f - fTempPerm32));
			iTempPerm39 = int(min(2049, max(0, iTempPerm34)));
			fRec4[0] = ((fVec3[(IOTA-iTempPerm39)&4095] * fTempPerm38) + (fTempPerm37 * fVec3[(IOTA-iTempPerm35)&4095]));
			float 	fRec5 = (0 - (0.59999999999999998f * fVec3[IOTA&4095]));
			fTempPerm40 = (fRec5 + fRec4[1]);
			fVec4[IOTA&2047] = fTempPerm40;
			fTempPerm41 = (1422.0f * fTempPerm4);
			iTempPerm42 = int(fTempPerm41);
			fTempPerm43 = floorf(fTempPerm41);
			fRec0[0] = (0.5f * ((fVec4[(IOTA-int(min(8193, max(0, iTempPerm42))))&2047] * (fTempPerm43 + (1.0f - fTempPerm41))) + ((fTempPerm41 - fTempPerm43) * fVec4[(IOTA-int(min(8193, max(0, (iTempPerm42 + 1)))))&2047])));
			fRec24[0] = ((fRec13[0] * (fTempPerm1 - (fRec1[1] + fRec3[1]))) - (fConst5 * ((fConst4 * fRec24[2]) + (fConst2 * fRec24[1]))));
			fTempPerm44 = (((0.59999999999999998f * fRec22[1]) + (fConst5 * (fRec24[2] + (fRec24[0] + (2.0f * fRec24[1]))))) + fTempPerm0);
			fVec5[IOTA&511] = fTempPerm44;
			fRec22[0] = ((fTempPerm11 * fVec5[(IOTA-iTempPerm12)&511]) + (fTempPerm10 * fVec5[(IOTA-iTempPerm8)&511]));
			float 	fRec23 = (0 - (0.59999999999999998f * fVec5[IOTA&511]));
			fTempPerm45 = (fRec22[1] + (fRec23 + (0.59999999999999998f * fRec20[1])));
			fVec6[IOTA&1023] = fTempPerm45;
			fRec20[0] = ((fTempPerm20 * fVec6[(IOTA-iTempPerm21)&1023]) + (fTempPerm19 * fVec6[(IOTA-iTempPerm17)&1023]));
			float 	fRec21 = (0 - (0.59999999999999998f * fVec6[IOTA&1023]));
			fTempPerm46 = (fRec20[1] + (fRec21 + (0.59999999999999998f * fRec18[1])));
			fVec7[IOTA&4095] = fTempPerm46;
			fRec18[0] = ((fTempPerm29 * fVec7[(IOTA-iTempPerm30)&4095]) + (fTempPerm28 * fVec7[(IOTA-iTempPerm26)&4095]));
			float 	fRec19 = (0 - (0.59999999999999998f * fVec7[IOTA&4095]));
			fTempPerm47 = (fRec18[1] + (fRec19 + (0.59999999999999998f * fRec16[1])));
			fVec8[IOTA&4095] = fTempPerm47;
			fRec16[0] = ((fTempPerm38 * fVec8[(IOTA-iTempPerm39)&4095]) + (fTempPerm37 * fVec8[(IOTA-iTempPerm35)&4095]));
			float 	fRec17 = (0 - (0.59999999999999998f * fVec8[IOTA&4095]));
			fTempPerm48 = (fRec17 + fRec16[1]);
			fVec9[IOTA&2047] = fTempPerm48;
			fTempPerm49 = (1617.0f * fTempPerm4);
			iTempPerm50 = int(fTempPerm49);
			fTempPerm51 = floorf(fTempPerm49);
			fRec1[0] = (0.5f * ((fVec9[(IOTA-int(min(8193, max(0, iTempPerm50))))&2047] * (fTempPerm51 + (1.0f - fTempPerm49))) + ((fTempPerm49 - fTempPerm51) * fVec9[(IOTA-int(min(8193, max(0, (iTempPerm50 + 1)))))&2047])));
			fRec34[0] = ((fRec13[0] * ((fRec0[1] + fRec1[1]) - (fRec2[1] + fRec3[1]))) - (fConst5 * ((fConst4 * fRec34[2]) + (fConst2 * fRec34[1]))));
			fTempPerm52 = (((0.59999999999999998f * fRec32[1]) + (fConst5 * (fRec34[2] + (fRec34[0] + (2.0f * fRec34[1]))))) + fTempPerm0);
			fVec10[IOTA&511] = fTempPerm52;
			fRec32[0] = ((fTempPerm11 * fVec10[(IOTA-iTempPerm12)&511]) + (fTempPerm10 * fVec10[(IOTA-iTempPerm8)&511]));
			float 	fRec33 = (0 - (0.59999999999999998f * fVec10[IOTA&511]));
			fTempPerm53 = (fRec32[1] + (fRec33 + (0.59999999999999998f * fRec30[1])));
			fVec11[IOTA&1023] = fTempPerm53;
			fRec30[0] = ((fTempPerm20 * fVec11[(IOTA-iTempPerm21)&1023]) + (fTempPerm19 * fVec11[(IOTA-iTempPerm17)&1023]));
			float 	fRec31 = (0 - (0.59999999999999998f * fVec11[IOTA&1023]));
			fTempPerm54 = (fRec30[1] + (fRec31 + (0.59999999999999998f * fRec28[1])));
			fVec12[IOTA&4095] = fTempPerm54;
			fRec28[0] = ((fTempPerm29 * fVec12[(IOTA-iTempPerm30)&4095]) + (fTempPerm28 * fVec12[(IOTA-iTempPerm26)&4095]));
			float 	fRec29 = (0 - (0.59999999999999998f * fVec12[IOTA&4095]));
			fTempPerm55 = (fRec28[1] + (fRec29 + (0.59999999999999998f * fRec26[1])));
			fVec13[IOTA&4095] = fTempPerm55;
			fRec26[0] = ((fTempPerm38 * fVec13[(IOTA-iTempPerm39)&4095]) + (fTempPerm37 * fVec13[(IOTA-iTempPerm35)&4095]));
			float 	fRec27 = (0 - (0.59999999999999998f * fVec13[IOTA&4095]));
			fTempPerm56 = (fRec27 + fRec26[1]);
			fVec14[IOTA&4095] = fTempPerm56;
			fTempPerm57 = (2401.0f * fTempPerm4);
			iTempPerm58 = int(fTempPerm57);
			fTempPerm59 = floorf(fTempPerm57);
			fRec25[0] = ((0.5f * ((fVec14[(IOTA-int(min(8193, max(0, iTempPerm58))))&4095] * (fTempPerm59 + (1.0f - fTempPerm57))) + ((fTempPerm57 - fTempPerm59) * fVec14[(IOTA-int(min(8193, max(0, (iTempPerm58 + 1)))))&4095]))) - (fConst13 * ((fConst12 * fRec25[2]) + (fConst10 * fRec25[1]))));
			fRec2[0] = (fConst13 * (((fConst9 * fRec25[0]) + (fConst14 * fRec25[1])) + (fConst9 * fRec25[2])));
			fTempPerm60 = (6561.0f * fTempPerm4);
			fTempPerm61 = (fTempPerm60 + 8192.0f);
			fRec35[0] = fmodf(((fTempPerm60 + fRec35[1]) + 8191.0f),fTempPerm61);
			fTempPerm62 = min((fRec35[0] / fTempPerm61), (float)1);
			fRec44[0] = ((fRec13[0] * ((fRec0[1] + fRec3[1]) - (fRec2[1] + fRec1[1]))) - (fConst5 * ((fConst4 * fRec44[2]) + (fConst2 * fRec44[1]))));
			fTempPerm63 = (((0.59999999999999998f * fRec42[1]) + (fConst5 * (fRec44[2] + (fRec44[0] + (2.0f * fRec44[1]))))) + fTempPerm0);
			fVec15[IOTA&511] = fTempPerm63;
			fRec42[0] = ((fTempPerm11 * fVec15[(IOTA-iTempPerm12)&511]) + (fTempPerm10 * fVec15[(IOTA-iTempPerm8)&511]));
			float 	fRec43 = (0 - (0.59999999999999998f * fVec15[IOTA&511]));
			fTempPerm64 = (fRec42[1] + (fRec43 + (0.59999999999999998f * fRec40[1])));
			fVec16[IOTA&1023] = fTempPerm64;
			fRec40[0] = ((fTempPerm20 * fVec16[(IOTA-iTempPerm21)&1023]) + (fTempPerm19 * fVec16[(IOTA-iTempPerm17)&1023]));
			float 	fRec41 = (0 - (0.59999999999999998f * fVec16[IOTA&1023]));
			fTempPerm65 = (fRec40[1] + (fRec41 + (0.59999999999999998f * fRec38[1])));
			fVec17[IOTA&4095] = fTempPerm65;
			fRec38[0] = ((fTempPerm29 * fVec17[(IOTA-iTempPerm30)&4095]) + (fTempPerm28 * fVec17[(IOTA-iTempPerm26)&4095]));
			float 	fRec39 = (0 - (0.59999999999999998f * fVec17[IOTA&4095]));
			fTempPerm66 = (fRec38[1] + (fRec39 + (0.59999999999999998f * fRec36[1])));
			fVec18[IOTA&4095] = fTempPerm66;
			fRec36[0] = ((fTempPerm38 * fVec18[(IOTA-iTempPerm39)&4095]) + (fTempPerm37 * fVec18[(IOTA-iTempPerm35)&4095]));
			float 	fRec37 = (0 - (0.59999999999999998f * fVec18[IOTA&4095]));
			fTempPerm67 = (fRec37 + fRec36[1]);
			fVec19[IOTA&131071] = fTempPerm67;
			fTempPerm68 = (fRec35[0] + fTempPerm60);
			fTempPerm69 = (fTempPerm68 + 8192.0f);
			iTempPerm70 = int(fTempPerm69);
			fTempPerm71 = floorf(fTempPerm69);
			iTempPerm72 = int(fRec35[0]);
			fTempPerm73 = floorf(fRec35[0]);
			fRec3[0] = (0.5f * ((fSlow2 * fVec19[(IOTA-int(min((float)8192, max((float)0, fTempPerm61))))&131071]) + (fSlow1 * ((((fVec19[(IOTA-int(min(65537, max(0, iTempPerm72))))&131071] * (fTempPerm73 + (1.0f - fRec35[0]))) + ((fRec35[0] - fTempPerm73) * fVec19[(IOTA-int(min(65537, max(0, (iTempPerm72 + 1)))))&131071])) * fTempPerm62) + (((fVec19[(IOTA-int(min(65537, max(0, iTempPerm70))))&131071] * (fTempPerm71 + (-8191.0f - fTempPerm68))) + ((fTempPerm68 + (8192.0f - fTempPerm71)) * fVec19[(IOTA-int(min(65537, max(0, (iTempPerm70 + 1)))))&131071])) * (1.0f - fTempPerm62))))));
			fTempPerm74 = (fRec3[0] + fRec1[0]);
			fRec45[0] = (fSlow3 + (0.999f * fRec45[1]));
			fTempPerm75 = (fRec45[0] + 1.0f);
			fTempPerm76 = (fRec0[0] + fRec2[0]);
			fTempPerm77 = (1.0f - fRec45[0]);
			fTempPerm78 = ((fTempPerm77 * fTempPerm76) + (fTempPerm75 * fTempPerm74));
			fRec48[0] = (fSlow4 + (0.999f * fRec48[1]));
			fTempPerm79 = ((fTempPerm77 * fTempPerm74) + (fTempPerm76 * fTempPerm75));
			fRec50[0] = ((fConst15 * fRec50[1]) + (fConst17 * fabsf((fabsf(fTempPerm78) + fabsf(fTempPerm79)))));
			float 	fRec49 = fRec50[0];
			iTempPerm80 = (fRec49 > powf(10,(0.050000000000000003f * ((64.0f * max((float)0, (fRec48[0] + -1.0f))) + -60.0f))));
			iVec20[0] = iTempPerm80;
			iRec51[0] = max((int)(iConst18 * (iVec20[0] < iVec20[1])), (int)(iRec51[1] + -1));
			fTempPerm81 = fabsf(max(float(iVec20[0]), (float)(iRec51[0] > 0)));
			fTempPerm82 = ((int((fRec46[1] > fTempPerm81)))?fConst16:fConst15);
			fRec47[0] = ((fRec47[1] * fTempPerm82) + (fTempPerm81 * (1.0f - fTempPerm82)));
			fRec46[0] = fRec47[0];
			output0[i] = (FAUSTFLOAT)(fRec46[0] * fTempPerm78);
			output1[i] = (FAUSTFLOAT)(fRec46[0] * fTempPerm79);
			// post processing
			fRec46[1] = fRec46[0];
			fRec47[1] = fRec47[0];
			iRec51[1] = iRec51[0];
			iVec20[1] = iVec20[0];
			fRec50[1] = fRec50[0];
			fRec48[1] = fRec48[0];
			fRec45[1] = fRec45[0];
			fRec3[1] = fRec3[0];
			fRec36[1] = fRec36[0];
			fRec38[1] = fRec38[0];
			fRec40[1] = fRec40[0];
			fRec42[1] = fRec42[0];
			fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
			fRec35[1] = fRec35[0];
			fRec2[1] = fRec2[0];
			fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec32[1] = fRec32[0];
			fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
			fRec1[1] = fRec1[0];
			fRec16[1] = fRec16[0];
			fRec18[1] = fRec18[0];
			fRec20[1] = fRec20[0];
			fRec22[1] = fRec22[0];
			fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fRec8[1] = fRec8[0];
			fRec10[1] = fRec10[0];
			fRec15[1] = fRec15[0];
			IOTA = IOTA+1;
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
		}
	}
};


float 	faust_wormhole::ftbl0[65536];
