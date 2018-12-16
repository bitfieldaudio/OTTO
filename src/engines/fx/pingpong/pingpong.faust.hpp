/* ------------------------------------------------------------
name: "pingpong"
Code generated with Faust 2.13.11 (https://faust.grame.fr)
Compilation options: cpp, -vec -lv 0 -vs 32 -ftz 0 -mcd 16
------------------------------------------------------------ */

#ifndef  __faust_pingpong_H__
#define  __faust_pingpong_H__

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

#include <algorithm>
#include <cmath>
#include <math.h>


class faust_pingpongSIG0 {
	
  private:
	
	int iRec10[2];
	
  public:
	
	int getNumInputsfaust_pingpongSIG0() {
		return 0;
		
	}
	int getNumOutputsfaust_pingpongSIG0() {
		return 1;
		
	}
	int getInputRatefaust_pingpongSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatefaust_pingpongSIG0(int channel) {
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
	
	void instanceInitfaust_pingpongSIG0(int samplingFreq) {
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			iRec10[l10] = 0;
			
		}
		
	}
	
	void fillfaust_pingpongSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec10[0] = (iRec10[1] + 1);
			output[i] = std::sin((9.58738019e-05f * float((iRec10[0] + -1))));
			iRec10[1] = iRec10[0];
			
		}
		
	}
};

faust_pingpongSIG0* newfaust_pingpongSIG0() { return (faust_pingpongSIG0*)new faust_pingpongSIG0(); }
void deletefaust_pingpongSIG0(faust_pingpongSIG0* dsp) { delete dsp; }


class faust_pingpongSIG1 {
	
  private:
	
	int iRec11[2];
	
  public:
	
	int getNumInputsfaust_pingpongSIG1() {
		return 0;
		
	}
	int getNumOutputsfaust_pingpongSIG1() {
		return 1;
		
	}
	int getInputRatefaust_pingpongSIG1(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatefaust_pingpongSIG1(int channel) {
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
	
	void instanceInitfaust_pingpongSIG1(int samplingFreq) {
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			iRec11[l12] = 0;
			
		}
		
	}
	
	void fillfaust_pingpongSIG1(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec11[0] = (iRec11[1] + 1);
			output[i] = std::cos((9.58738019e-05f * float((iRec11[0] + -1))));
			iRec11[1] = iRec11[0];
			
		}
		
	}
};

faust_pingpongSIG1* newfaust_pingpongSIG1() { return (faust_pingpongSIG1*)new faust_pingpongSIG1(); }
void deletefaust_pingpongSIG1(faust_pingpongSIG1* dsp) { delete dsp; }

static float faust_pingpong_faustpower2_f(float value) {
	return (value * value);
	
}
static float ftbl0faust_pingpongSIG0[65536];
static float ftbl1faust_pingpongSIG1[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_pingpong
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faust_pingpong : public dsp {
	
 private:
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fRec2_perm[4];
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider1;
	float fConst2;
	float fVec0[262144];
	int fVec0_idx;
	int fVec0_idx_save;
	float fRec5_perm[4];
	float fRec4_perm[4];
	FAUSTFLOAT fHslider2;
	float fRec6_perm[4];
	FAUSTFLOAT fHslider3;
	float fYec0[131072];
	int fYec0_idx;
	int fYec0_idx_save;
	float fConst3;
	float fRec3_perm[4];
	float fConst4;
	float fConst5;
	float fRec7[4194304];
	int fRec7_idx;
	int fRec7_idx_save;
	float fConst6;
	float fRec8_perm[4];
	float fConst7;
	float fRec9_perm[4];
	float fYec1[8192];
	int fYec1_idx;
	int fYec1_idx_save;
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fHbargraph1;
	FAUSTFLOAT fHbargraph2;
	FAUSTFLOAT fHbargraph3;
	FAUSTFLOAT fHbargraph4;
	FAUSTFLOAT fHbargraph5;
	FAUSTFLOAT fHbargraph6;
	FAUSTFLOAT fHbargraph7;
	FAUSTFLOAT fHbargraph8;
	FAUSTFLOAT fHbargraph9;
	FAUSTFLOAT fHbargraph10;
	FAUSTFLOAT fHbargraph11;
	FAUSTFLOAT fHbargraph12;
	FAUSTFLOAT fHbargraph13;
	FAUSTFLOAT fHbargraph14;
	FAUSTFLOAT fHbargraph15;
	FAUSTFLOAT fHbargraph16;
	FAUSTFLOAT fHbargraph17;
	FAUSTFLOAT fHbargraph18;
	FAUSTFLOAT fHbargraph19;
	float fRec0[262144];
	int fRec0_idx;
	int fRec0_idx_save;
	float fYec2[131072];
	int fYec2_idx;
	int fYec2_idx_save;
	float fRec12_perm[4];
	float fYec3[8192];
	int fYec3_idx;
	int fYec3_idx_save;
	float fRec1[262144];
	int fRec1_idx;
	int fRec1_idx_save;
	
 public:
	
	void metadata(Meta* m) { 
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
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 1;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
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
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
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
		faust_pingpongSIG0* sig0 = newfaust_pingpongSIG0();
		sig0->instanceInitfaust_pingpongSIG0(samplingFreq);
		sig0->fillfaust_pingpongSIG0(65536, ftbl0faust_pingpongSIG0);
		faust_pingpongSIG1* sig1 = newfaust_pingpongSIG1();
		sig1->instanceInitfaust_pingpongSIG1(samplingFreq);
		sig1->fillfaust_pingpongSIG1(65536, ftbl1faust_pingpongSIG1);
		deletefaust_pingpongSIG0(sig0);
		deletefaust_pingpongSIG1(sig1);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = (7.0f / fConst0);
		fConst2 = (0.125f * fConst0);
		fConst3 = (3.14159274f / fConst0);
		fConst4 = std::exp((0.0f - (5.0f / fConst0)));
		fConst5 = (1.0f - fConst4);
		fConst6 = (3.5f / fConst0);
		fConst7 = (1.75f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			fRec2_perm[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 262144); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
			
		}
		fVec0_idx = 0;
		fVec0_idx_save = 0;
		for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) {
			fRec5_perm[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) {
			fRec4_perm[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 4); l4 = (l4 + 1)) {
			fRec6_perm[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 131072); l5 = (l5 + 1)) {
			fYec0[l5] = 0.0f;
			
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l6 = 0; (l6 < 4); l6 = (l6 + 1)) {
			fRec3_perm[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 4194304); l7 = (l7 + 1)) {
			fRec7[l7] = 0.0f;
			
		}
		fRec7_idx = 0;
		fRec7_idx_save = 0;
		for (int l8 = 0; (l8 < 4); l8 = (l8 + 1)) {
			fRec8_perm[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 4); l9 = (l9 + 1)) {
			fRec9_perm[l9] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 8192); l11 = (l11 + 1)) {
			fYec1[l11] = 0.0f;
			
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l13 = 0; (l13 < 262144); l13 = (l13 + 1)) {
			fRec0[l13] = 0.0f;
			
		}
		fRec0_idx = 0;
		fRec0_idx_save = 0;
		for (int l14 = 0; (l14 < 131072); l14 = (l14 + 1)) {
			fYec2[l14] = 0.0f;
			
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l15 = 0; (l15 < 4); l15 = (l15 + 1)) {
			fRec12_perm[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 8192); l16 = (l16 + 1)) {
			fYec3[l16] = 0.0f;
			
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l17 = 0; (l17 < 262144); l17 = (l17 + 1)) {
			fRec1[l17] = 0.0f;
			
		}
		fRec1_idx = 0;
		fRec1_idx_save = 0;
		
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
		ui_interface->addCheckButton("bpm_follow", &fCheckbox0);
		ui_interface->openVerticalBox("delayline0");
		ui_interface->addHorizontalBargraph("level", &fHbargraph0, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline1");
		ui_interface->addHorizontalBargraph("level", &fHbargraph1, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline10");
		ui_interface->addHorizontalBargraph("level", &fHbargraph10, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline11");
		ui_interface->addHorizontalBargraph("level", &fHbargraph11, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline12");
		ui_interface->addHorizontalBargraph("level", &fHbargraph12, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline13");
		ui_interface->addHorizontalBargraph("level", &fHbargraph13, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline14");
		ui_interface->addHorizontalBargraph("level", &fHbargraph14, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline15");
		ui_interface->addHorizontalBargraph("level", &fHbargraph15, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline16");
		ui_interface->addHorizontalBargraph("level", &fHbargraph16, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline17");
		ui_interface->addHorizontalBargraph("level", &fHbargraph17, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline18");
		ui_interface->addHorizontalBargraph("level", &fHbargraph18, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline19");
		ui_interface->addHorizontalBargraph("level", &fHbargraph19, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline2");
		ui_interface->addHorizontalBargraph("level", &fHbargraph2, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline3");
		ui_interface->addHorizontalBargraph("level", &fHbargraph3, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline4");
		ui_interface->addHorizontalBargraph("level", &fHbargraph4, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline5");
		ui_interface->addHorizontalBargraph("level", &fHbargraph5, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline6");
		ui_interface->addHorizontalBargraph("level", &fHbargraph6, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline7");
		ui_interface->addHorizontalBargraph("level", &fHbargraph7, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline8");
		ui_interface->addHorizontalBargraph("level", &fHbargraph8, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("delayline9");
		ui_interface->addHorizontalBargraph("level", &fHbargraph9, 0.0f, 5.0f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("delaytime", &fHslider1, 0.5f, 0.00999999978f, 0.999000013f, 0.00100000005f);
		ui_interface->addHorizontalSlider("feedback", &fHslider3, 0.5f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("spread", &fHslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("tone", &fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = std::max<float>(0.0f, (0.5f - fSlow0));
		float fSlow2 = (fConst1 * fSlow1);
		float fZec0[32];
		float fRec2_tmp[36];
		float* fRec2 = &fRec2_tmp[4];
		float fSlow3 = std::max<float>(0.00999999978f, std::min<float>(1.0f, float(fHslider1)));
		float fSlow4 = (int(float(fCheckbox0))?(fConst2 * std::ceil((4.0f * fSlow3))):float(int((fConst0 * fSlow3))));
		int iSlow5 = int(fSlow4);
		float fRec5_tmp[36];
		float* fRec5 = &fRec5_tmp[4];
		float fRec4_tmp[36];
		float* fRec4 = &fRec4_tmp[4];
		float fSlow6 = (0.00100000005f * ((1900.0f * float(fHslider2)) + 100.0f));
		float fRec6_tmp[36];
		float* fRec6 = &fRec6_tmp[4];
		float fSlow7 = float(fHslider3);
		int iSlow8 = (fSlow0 == 1.0f);
		int iSlow9 = (1 - iSlow8);
		int iSlow10 = (iSlow5 + 1);
		float fZec1[32];
		int iSlow11 = (int((float((iSlow9 * int((2000.0f * std::max<float>(0.0f, (fSlow0 + -0.5f)))))) + fSlow4)) + 1);
		float fZec2[32];
		int iZec3[32];
		int iZec4[32];
		float fZec5[32];
		float fZec6[32];
		float fZec7[32];
		int iZec8[32];
		float fZec9[32];
		float fZec10[32];
		int iZec11[32];
		int iZec12[32];
		float fZec13[32];
		float fZec14[32];
		float fZec15[32];
		int iZec16[32];
		float fZec17[32];
		float fZec18[32];
		float fZec19[32];
		float fZec20[32];
		float fZec21[32];
		float fZec22[32];
		float fZec23[32];
		float fRec3_tmp[36];
		float* fRec3 = &fRec3_tmp[4];
		float fZec24[32];
		float fSlow12 = (fConst6 * fSlow1);
		float fZec25[32];
		float fRec8_tmp[36];
		float* fRec8 = &fRec8_tmp[4];
		float fSlow13 = (fConst7 * fSlow1);
		float fZec26[32];
		float fRec9_tmp[36];
		float* fRec9 = &fRec9_tmp[4];
		float fZec27[32];
		float fZec28[32];
		float fZec29[32];
		float fZec30[32];
		float fZec31[32];
		float fZec32[32];
		int iZec33[32];
		int iZec34[32];
		int iZec35[32];
		float fZec36[32];
		float fSlow14 = (2.0f * (1.0f - fSlow1));
		float fSlow15 = float(iSlow9);
		int iSlow16 = int((2.0f * fSlow4));
		int iSlow17 = int((3.0f * fSlow4));
		int iSlow18 = int((4.0f * fSlow4));
		int iSlow19 = int((5.0f * fSlow4));
		int iSlow20 = int((6.0f * fSlow4));
		int iSlow21 = int((7.0f * fSlow4));
		int iSlow22 = int((8.0f * fSlow4));
		int iSlow23 = int((9.0f * fSlow4));
		int iSlow24 = int((10.0f * fSlow4));
		int iSlow25 = int((11.0f * fSlow4));
		int iSlow26 = int((12.0f * fSlow4));
		int iSlow27 = int((13.0f * fSlow4));
		int iSlow28 = int((14.0f * fSlow4));
		int iSlow29 = int((15.0f * fSlow4));
		int iSlow30 = int((16.0f * fSlow4));
		int iSlow31 = int((17.0f * fSlow4));
		int iSlow32 = int((18.0f * fSlow4));
		int iSlow33 = int((19.0f * fSlow4));
		float fZec37[32];
		float fZec38[32];
		int iZec39[32];
		int iZec40[32];
		float fZec41[32];
		float fZec42[32];
		float fZec43[32];
		int iZec44[32];
		float fZec45[32];
		int iZec46[32];
		int iZec47[32];
		float fZec48[32];
		float fZec49[32];
		float fZec50[32];
		int iZec51[32];
		float fZec52[32];
		float fRec12_tmp[36];
		float* fRec12 = &fRec12_tmp[4];
		float fZec53[32];
		float fSlow34 = float(iSlow8);
		int fullcount = count;
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; (vindex <= (fullcount - 32)); vindex = (vindex + 32)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 32;
			/* Vectorizable loop 0 */
			/* Pre code */
			fVec0_idx = ((fVec0_idx + fVec0_idx_save) & 262143);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fVec0[((i + fVec0_idx) & 262143)] = fSlow4;
				
			}
			/* Post code */
			fVec0_idx_save = vsize;
			/* Recursive loop 1 */
			/* Pre code */
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				fRec6_tmp[j6] = fRec6_perm[j6];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec6[i] = (fSlow6 + (0.999000013f * fRec6[(i - 1)]));
				
			}
			/* Post code */
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				fRec6_perm[j7] = fRec6_tmp[(vsize + j7)];
				
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec5_tmp[j2] = fRec5_perm[j2];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec5[i] = ((0.999000013f * fRec5[(i - 1)]) + (0.0120000001f * ((fVec0[(((i + fVec0_idx) - iSlow5) & 262143)] - fSlow4) / fSlow4)));
				
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec5_perm[j3] = fRec5_tmp[(vsize + j3)];
				
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec19[i] = std::tan((fConst3 * fRec6[i]));
				
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec2_tmp[j0] = fRec2_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec0[i] = fRec2[(i - 1)];
				fRec2[i] = (fSlow2 + (fZec0[i] - std::floor((fSlow2 + fZec0[i]))));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec2_perm[j1] = fRec2_tmp[(vsize + j1)];
				
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec4_tmp[j4] = fRec4_perm[j4];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec4[i] = std::fmod((fRec4[(i - 1)] + (251.0f - std::pow(2.0f, (0.0833333358f * fRec5[i])))), 250.0f);
				
			}
			/* Post code */
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec4_perm[j5] = fRec4_tmp[(vsize + j5)];
				
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec20[i] = (1.0f / fZec19[i]);
				
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
				fRec8_tmp[j10] = fRec8_perm[j10];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec25[i] = fRec8[(i - 1)];
				fRec8[i] = (fSlow12 + (fZec25[i] - std::floor((fSlow12 + fZec25[i]))));
				
			}
			/* Post code */
			for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
				fRec8_perm[j11] = fRec8_tmp[(vsize + j11)];
				
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
				fRec9_tmp[j12] = fRec9_perm[j12];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec26[i] = fRec9[(i - 1)];
				fRec9[i] = (fSlow13 + (fZec26[i] - std::floor((fSlow13 + fZec26[i]))));
				
			}
			/* Post code */
			for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
				fRec9_perm[j13] = fRec9_tmp[(vsize + j13)];
				
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec24[i] = std::fabs(float(input0[i]));
				
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec10[i] = (fRec4[i] + 250.0f);
				
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec23[i] = (((fZec20[i] + 1.0f) / fZec19[i]) + 1.0f);
				
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec27[i] = std::min<float>(8192.0f, ((153.600006f * ftbl0faust_pingpongSIG0[int((65536.0f * fRec2[i]))]) + 1024.0f));
				
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec38[i] = std::min<float>(8192.0f, ((153.600006f * ftbl1faust_pingpongSIG1[int((65536.0f * fRec8[i]))]) + 2048.0f));
				
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec45[i] = std::min<float>(8192.0f, ((153.600006f * (0.0f - ftbl1faust_pingpongSIG1[int((65536.0f * fRec9[i]))])) + 4096.0f));
				
			}
			/* Recursive loop 15 */
			/* Pre code */
			fRec7_idx = ((fRec7_idx + fRec7_idx_save) & 4194303);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec7[((i + fRec7_idx) & 4194303)] = std::max<float>(fZec24[i], ((fConst4 * fRec7[(((i + fRec7_idx) - 1) & 4194303)]) + (fConst5 * fZec24[i])));
				
			}
			/* Post code */
			fRec7_idx_save = vsize;
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec3[i] = int(fRec4[i]);
				
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec5[i] = std::floor(fRec4[i]);
				
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec9[i] = std::min<float>((0.0199999996f * fRec4[i]), 1.0f);
				
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec11[i] = int(fZec10[i]);
				
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec13[i] = std::floor(fZec10[i]);
				
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec28[i] = std::floor(fZec27[i]);
				
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec30[i] = (fZec19[i] * fZec23[i]);
				
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec33[i] = int(fZec27[i]);
				
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec39[i] = int(fZec38[i]);
				
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec41[i] = std::floor(fZec38[i]);
				
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec46[i] = int(fZec45[i]);
				
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec48[i] = std::floor(fZec45[i]);
				
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec4[i] = std::min<int>(65537, std::max<int>(0, iZec3[i]));
				
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = (fZec5[i] + (1.0f - fRec4[i]));
				
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec7[i] = (fRec4[i] - fZec5[i]);
				
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec8[i] = std::min<int>(65537, std::max<int>(0, (iZec3[i] + 1)));
				
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec12[i] = std::min<int>(65537, std::max<int>(0, iZec11[i]));
				
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec14[i] = (fZec13[i] + (-249.0f - fRec4[i]));
				
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec15[i] = (fRec4[i] + (250.0f - fZec13[i]));
				
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec16[i] = std::min<int>(65537, std::max<int>(0, (iZec11[i] + 1)));
				
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec17[i] = (1.0f - fZec9[i]);
				
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec21[i] = (1.0f - ((1.0f - fZec20[i]) / fZec19[i]));
				
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec22[i] = (1.0f - (1.0f / faust_pingpong_faustpower2_f(fZec19[i])));
				
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec29[i] = (fZec27[i] - fZec28[i]);
				
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec31[i] = (0.0f - (0.800000012f / fZec30[i]));
				
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec34[i] = std::min<int>(8193, std::max<int>(0, (iZec33[i] + 1)));
				
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec35[i] = std::min<int>(8193, std::max<int>(0, iZec33[i]));
				
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec36[i] = (fZec28[i] + (1.0f - fZec27[i]));
				
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fHbargraph0 = FAUSTFLOAT(fRec7[((i + fRec7_idx) & 4194303)]);
				fHbargraph1 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow5) & 4194303)]);
				fHbargraph2 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow16) & 4194303)]);
				fHbargraph3 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow17) & 4194303)]);
				fHbargraph4 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow18) & 4194303)]);
				fHbargraph5 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow19) & 4194303)]);
				fHbargraph6 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow20) & 4194303)]);
				fHbargraph7 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow21) & 4194303)]);
				fHbargraph8 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow22) & 4194303)]);
				fHbargraph9 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow23) & 4194303)]);
				fHbargraph10 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow24) & 4194303)]);
				fHbargraph11 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow25) & 4194303)]);
				fHbargraph12 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow26) & 4194303)]);
				fHbargraph13 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow27) & 4194303)]);
				fHbargraph14 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow28) & 4194303)]);
				fHbargraph15 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow29) & 4194303)]);
				fHbargraph16 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow30) & 4194303)]);
				fHbargraph17 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow31) & 4194303)]);
				fHbargraph18 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow32) & 4194303)]);
				fHbargraph19 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow33) & 4194303)]);
				fZec37[i] = float(input0[i]);
				
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec40[i] = std::min<int>(8193, std::max<int>(0, iZec39[i]));
				
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec42[i] = (fZec41[i] + (1.0f - fZec38[i]));
				
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec43[i] = (fZec38[i] - fZec41[i]);
				
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec44[i] = std::min<int>(8193, std::max<int>(0, (iZec39[i] + 1)));
				
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec47[i] = std::min<int>(8193, std::max<int>(0, iZec46[i]));
				
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec49[i] = (fZec48[i] + (1.0f - fZec45[i]));
				
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec50[i] = (fZec45[i] - fZec48[i]);
				
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec51[i] = std::min<int>(8193, std::max<int>(0, (iZec46[i] + 1)));
				
			}
			/* Recursive loop 53 */
			/* Pre code */
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 131071);
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				fRec3_tmp[j8] = fRec3_perm[j8];
				
			}
			fYec1_idx = ((fYec1_idx + fYec1_idx_save) & 8191);
			fRec0_idx = ((fRec0_idx + fRec0_idx_save) & 262143);
			fYec2_idx = ((fYec2_idx + fYec2_idx_save) & 131071);
			for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
				fRec12_tmp[j14] = fRec12_perm[j14];
				
			}
			fYec3_idx = ((fYec3_idx + fYec3_idx_save) & 8191);
			fRec1_idx = ((fRec1_idx + fRec1_idx_save) & 262143);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec1[i] = fRec1[(((i + fRec1_idx) - iSlow10) & 262143)];
				fZec2[i] = fRec0[(((i + fRec0_idx) - iSlow11) & 262143)];
				fYec0[((i + fYec0_idx) & 131071)] = (fSlow7 * (iSlow9?fZec2[i]:fZec1[i]));
				fZec18[i] = fRec3[(i - 2)];
				fRec3[i] = (((((fYec0[(((i + fYec0_idx) - iZec4[i]) & 131071)] * fZec6[i]) + (fZec7[i] * fYec0[(((i + fYec0_idx) - iZec8[i]) & 131071)])) * fZec9[i]) + (((fYec0[(((i + fYec0_idx) - iZec12[i]) & 131071)] * fZec14[i]) + (fZec15[i] * fYec0[(((i + fYec0_idx) - iZec16[i]) & 131071)])) * fZec17[i])) - (((fZec18[i] * fZec21[i]) + (2.0f * (fRec3[(i - 1)] * fZec22[i]))) / fZec23[i]));
				fZec32[i] = ((0.800000012f * (fRec3[i] / fZec30[i])) + (fZec18[i] * fZec31[i]));
				fYec1[((i + fYec1_idx) & 8191)] = (fSlow1 * fZec32[i]);
				fRec0[((i + fRec0_idx) & 262143)] = ((((fZec29[i] * fYec1[(((i + fYec1_idx) - iZec34[i]) & 8191)]) + ((fYec1[(((i + fYec1_idx) - iZec35[i]) & 8191)] * fZec36[i]) + (fSlow14 * fZec32[i]))) + (fSlow15 * fZec37[i])) - ((0.707106769f * ((fYec1[(((i + fYec1_idx) - iZec40[i]) & 8191)] * fZec42[i]) + (fZec43[i] * fYec1[(((i + fYec1_idx) - iZec44[i]) & 8191)]))) + (0.707106769f * ((fYec1[(((i + fYec1_idx) - iZec47[i]) & 8191)] * fZec49[i]) + (fZec50[i] * fYec1[(((i + fYec1_idx) - iZec51[i]) & 8191)])))));
				fYec2[((i + fYec2_idx) & 131071)] = (fSlow7 * (iSlow9?fZec1[i]:fZec2[i]));
				fZec52[i] = fRec12[(i - 2)];
				fRec12[i] = (((fZec9[i] * ((fZec6[i] * fYec2[(((i + fYec2_idx) - iZec4[i]) & 131071)]) + (fZec7[i] * fYec2[(((i + fYec2_idx) - iZec8[i]) & 131071)]))) + (fZec17[i] * ((fZec14[i] * fYec2[(((i + fYec2_idx) - iZec12[i]) & 131071)]) + (fZec15[i] * fYec2[(((i + fYec2_idx) - iZec16[i]) & 131071)])))) - (((fZec21[i] * fZec52[i]) + (2.0f * (fZec22[i] * fRec12[(i - 1)]))) / fZec23[i]));
				fZec53[i] = ((0.800000012f * (fRec12[i] / fZec30[i])) + (fZec31[i] * fZec52[i]));
				fYec3[((i + fYec3_idx) & 8191)] = (fSlow1 * fZec53[i]);
				fRec1[((i + fRec1_idx) & 262143)] = (((fZec29[i] * fYec3[(((i + fYec3_idx) - iZec34[i]) & 8191)]) + ((fZec36[i] * fYec3[(((i + fYec3_idx) - iZec35[i]) & 8191)]) + (fZec37[i] + (fSlow14 * fZec53[i])))) - ((0.707106769f * ((fZec42[i] * fYec3[(((i + fYec3_idx) - iZec40[i]) & 8191)]) + (fZec43[i] * fYec3[(((i + fYec3_idx) - iZec44[i]) & 8191)]))) + (0.707106769f * ((fZec49[i] * fYec3[(((i + fYec3_idx) - iZec47[i]) & 8191)]) + (fZec50[i] * fYec3[(((i + fYec3_idx) - iZec51[i]) & 8191)])))));
				
			}
			/* Post code */
			fYec3_idx_save = vsize;
			fYec2_idx_save = vsize;
			for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
				fRec12_perm[j15] = fRec12_tmp[(vsize + j15)];
				
			}
			fYec1_idx_save = vsize;
			fYec0_idx_save = vsize;
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				fRec3_perm[j9] = fRec3_tmp[(vsize + j9)];
				
			}
			fRec0_idx_save = vsize;
			fRec1_idx_save = vsize;
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((fRec0[((i + fRec0_idx) & 262143)] + (fSlow34 * fZec37[i])));
				
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output1[i] = FAUSTFLOAT(fRec1[((i + fRec1_idx) & 262143)]);
				
			}
			
		}
		/* Remaining frames */
		if (vindex < fullcount) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = (fullcount - vindex);
			/* Vectorizable loop 0 */
			/* Pre code */
			fVec0_idx = ((fVec0_idx + fVec0_idx_save) & 262143);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fVec0[((i + fVec0_idx) & 262143)] = fSlow4;
				
			}
			/* Post code */
			fVec0_idx_save = vsize;
			/* Recursive loop 1 */
			/* Pre code */
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				fRec6_tmp[j6] = fRec6_perm[j6];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec6[i] = (fSlow6 + (0.999000013f * fRec6[(i - 1)]));
				
			}
			/* Post code */
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				fRec6_perm[j7] = fRec6_tmp[(vsize + j7)];
				
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec5_tmp[j2] = fRec5_perm[j2];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec5[i] = ((0.999000013f * fRec5[(i - 1)]) + (0.0120000001f * ((fVec0[(((i + fVec0_idx) - iSlow5) & 262143)] - fSlow4) / fSlow4)));
				
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec5_perm[j3] = fRec5_tmp[(vsize + j3)];
				
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec19[i] = std::tan((fConst3 * fRec6[i]));
				
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec2_tmp[j0] = fRec2_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec0[i] = fRec2[(i - 1)];
				fRec2[i] = (fSlow2 + (fZec0[i] - std::floor((fSlow2 + fZec0[i]))));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec2_perm[j1] = fRec2_tmp[(vsize + j1)];
				
			}
			/* Recursive loop 5 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec4_tmp[j4] = fRec4_perm[j4];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec4[i] = std::fmod((fRec4[(i - 1)] + (251.0f - std::pow(2.0f, (0.0833333358f * fRec5[i])))), 250.0f);
				
			}
			/* Post code */
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec4_perm[j5] = fRec4_tmp[(vsize + j5)];
				
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec20[i] = (1.0f / fZec19[i]);
				
			}
			/* Recursive loop 7 */
			/* Pre code */
			for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
				fRec8_tmp[j10] = fRec8_perm[j10];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec25[i] = fRec8[(i - 1)];
				fRec8[i] = (fSlow12 + (fZec25[i] - std::floor((fSlow12 + fZec25[i]))));
				
			}
			/* Post code */
			for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
				fRec8_perm[j11] = fRec8_tmp[(vsize + j11)];
				
			}
			/* Recursive loop 8 */
			/* Pre code */
			for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
				fRec9_tmp[j12] = fRec9_perm[j12];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec26[i] = fRec9[(i - 1)];
				fRec9[i] = (fSlow13 + (fZec26[i] - std::floor((fSlow13 + fZec26[i]))));
				
			}
			/* Post code */
			for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
				fRec9_perm[j13] = fRec9_tmp[(vsize + j13)];
				
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec24[i] = std::fabs(float(input0[i]));
				
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec10[i] = (fRec4[i] + 250.0f);
				
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec23[i] = (((fZec20[i] + 1.0f) / fZec19[i]) + 1.0f);
				
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec27[i] = std::min<float>(8192.0f, ((153.600006f * ftbl0faust_pingpongSIG0[int((65536.0f * fRec2[i]))]) + 1024.0f));
				
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec38[i] = std::min<float>(8192.0f, ((153.600006f * ftbl1faust_pingpongSIG1[int((65536.0f * fRec8[i]))]) + 2048.0f));
				
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec45[i] = std::min<float>(8192.0f, ((153.600006f * (0.0f - ftbl1faust_pingpongSIG1[int((65536.0f * fRec9[i]))])) + 4096.0f));
				
			}
			/* Recursive loop 15 */
			/* Pre code */
			fRec7_idx = ((fRec7_idx + fRec7_idx_save) & 4194303);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec7[((i + fRec7_idx) & 4194303)] = std::max<float>(fZec24[i], ((fConst4 * fRec7[(((i + fRec7_idx) - 1) & 4194303)]) + (fConst5 * fZec24[i])));
				
			}
			/* Post code */
			fRec7_idx_save = vsize;
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec3[i] = int(fRec4[i]);
				
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec5[i] = std::floor(fRec4[i]);
				
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec9[i] = std::min<float>((0.0199999996f * fRec4[i]), 1.0f);
				
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec11[i] = int(fZec10[i]);
				
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec13[i] = std::floor(fZec10[i]);
				
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec28[i] = std::floor(fZec27[i]);
				
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec30[i] = (fZec19[i] * fZec23[i]);
				
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec33[i] = int(fZec27[i]);
				
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec39[i] = int(fZec38[i]);
				
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec41[i] = std::floor(fZec38[i]);
				
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec46[i] = int(fZec45[i]);
				
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec48[i] = std::floor(fZec45[i]);
				
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec4[i] = std::min<int>(65537, std::max<int>(0, iZec3[i]));
				
			}
			/* Vectorizable loop 29 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = (fZec5[i] + (1.0f - fRec4[i]));
				
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec7[i] = (fRec4[i] - fZec5[i]);
				
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec8[i] = std::min<int>(65537, std::max<int>(0, (iZec3[i] + 1)));
				
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec12[i] = std::min<int>(65537, std::max<int>(0, iZec11[i]));
				
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec14[i] = (fZec13[i] + (-249.0f - fRec4[i]));
				
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec15[i] = (fRec4[i] + (250.0f - fZec13[i]));
				
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec16[i] = std::min<int>(65537, std::max<int>(0, (iZec11[i] + 1)));
				
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec17[i] = (1.0f - fZec9[i]);
				
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec21[i] = (1.0f - ((1.0f - fZec20[i]) / fZec19[i]));
				
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec22[i] = (1.0f - (1.0f / faust_pingpong_faustpower2_f(fZec19[i])));
				
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec29[i] = (fZec27[i] - fZec28[i]);
				
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec31[i] = (0.0f - (0.800000012f / fZec30[i]));
				
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec34[i] = std::min<int>(8193, std::max<int>(0, (iZec33[i] + 1)));
				
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec35[i] = std::min<int>(8193, std::max<int>(0, iZec33[i]));
				
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec36[i] = (fZec28[i] + (1.0f - fZec27[i]));
				
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fHbargraph0 = FAUSTFLOAT(fRec7[((i + fRec7_idx) & 4194303)]);
				fHbargraph1 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow5) & 4194303)]);
				fHbargraph2 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow16) & 4194303)]);
				fHbargraph3 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow17) & 4194303)]);
				fHbargraph4 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow18) & 4194303)]);
				fHbargraph5 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow19) & 4194303)]);
				fHbargraph6 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow20) & 4194303)]);
				fHbargraph7 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow21) & 4194303)]);
				fHbargraph8 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow22) & 4194303)]);
				fHbargraph9 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow23) & 4194303)]);
				fHbargraph10 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow24) & 4194303)]);
				fHbargraph11 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow25) & 4194303)]);
				fHbargraph12 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow26) & 4194303)]);
				fHbargraph13 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow27) & 4194303)]);
				fHbargraph14 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow28) & 4194303)]);
				fHbargraph15 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow29) & 4194303)]);
				fHbargraph16 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow30) & 4194303)]);
				fHbargraph17 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow31) & 4194303)]);
				fHbargraph18 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow32) & 4194303)]);
				fHbargraph19 = FAUSTFLOAT(fRec7[(((i + fRec7_idx) - iSlow33) & 4194303)]);
				fZec37[i] = float(input0[i]);
				
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec40[i] = std::min<int>(8193, std::max<int>(0, iZec39[i]));
				
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec42[i] = (fZec41[i] + (1.0f - fZec38[i]));
				
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec43[i] = (fZec38[i] - fZec41[i]);
				
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec44[i] = std::min<int>(8193, std::max<int>(0, (iZec39[i] + 1)));
				
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec47[i] = std::min<int>(8193, std::max<int>(0, iZec46[i]));
				
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec49[i] = (fZec48[i] + (1.0f - fZec45[i]));
				
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec50[i] = (fZec45[i] - fZec48[i]);
				
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec51[i] = std::min<int>(8193, std::max<int>(0, (iZec46[i] + 1)));
				
			}
			/* Recursive loop 53 */
			/* Pre code */
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 131071);
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				fRec3_tmp[j8] = fRec3_perm[j8];
				
			}
			fYec1_idx = ((fYec1_idx + fYec1_idx_save) & 8191);
			fRec0_idx = ((fRec0_idx + fRec0_idx_save) & 262143);
			fYec2_idx = ((fYec2_idx + fYec2_idx_save) & 131071);
			for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
				fRec12_tmp[j14] = fRec12_perm[j14];
				
			}
			fYec3_idx = ((fYec3_idx + fYec3_idx_save) & 8191);
			fRec1_idx = ((fRec1_idx + fRec1_idx_save) & 262143);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec1[i] = fRec1[(((i + fRec1_idx) - iSlow10) & 262143)];
				fZec2[i] = fRec0[(((i + fRec0_idx) - iSlow11) & 262143)];
				fYec0[((i + fYec0_idx) & 131071)] = (fSlow7 * (iSlow9?fZec2[i]:fZec1[i]));
				fZec18[i] = fRec3[(i - 2)];
				fRec3[i] = (((((fYec0[(((i + fYec0_idx) - iZec4[i]) & 131071)] * fZec6[i]) + (fZec7[i] * fYec0[(((i + fYec0_idx) - iZec8[i]) & 131071)])) * fZec9[i]) + (((fYec0[(((i + fYec0_idx) - iZec12[i]) & 131071)] * fZec14[i]) + (fZec15[i] * fYec0[(((i + fYec0_idx) - iZec16[i]) & 131071)])) * fZec17[i])) - (((fZec18[i] * fZec21[i]) + (2.0f * (fRec3[(i - 1)] * fZec22[i]))) / fZec23[i]));
				fZec32[i] = ((0.800000012f * (fRec3[i] / fZec30[i])) + (fZec18[i] * fZec31[i]));
				fYec1[((i + fYec1_idx) & 8191)] = (fSlow1 * fZec32[i]);
				fRec0[((i + fRec0_idx) & 262143)] = ((((fZec29[i] * fYec1[(((i + fYec1_idx) - iZec34[i]) & 8191)]) + ((fYec1[(((i + fYec1_idx) - iZec35[i]) & 8191)] * fZec36[i]) + (fSlow14 * fZec32[i]))) + (fSlow15 * fZec37[i])) - ((0.707106769f * ((fYec1[(((i + fYec1_idx) - iZec40[i]) & 8191)] * fZec42[i]) + (fZec43[i] * fYec1[(((i + fYec1_idx) - iZec44[i]) & 8191)]))) + (0.707106769f * ((fYec1[(((i + fYec1_idx) - iZec47[i]) & 8191)] * fZec49[i]) + (fZec50[i] * fYec1[(((i + fYec1_idx) - iZec51[i]) & 8191)])))));
				fYec2[((i + fYec2_idx) & 131071)] = (fSlow7 * (iSlow9?fZec1[i]:fZec2[i]));
				fZec52[i] = fRec12[(i - 2)];
				fRec12[i] = (((fZec9[i] * ((fZec6[i] * fYec2[(((i + fYec2_idx) - iZec4[i]) & 131071)]) + (fZec7[i] * fYec2[(((i + fYec2_idx) - iZec8[i]) & 131071)]))) + (fZec17[i] * ((fZec14[i] * fYec2[(((i + fYec2_idx) - iZec12[i]) & 131071)]) + (fZec15[i] * fYec2[(((i + fYec2_idx) - iZec16[i]) & 131071)])))) - (((fZec21[i] * fZec52[i]) + (2.0f * (fZec22[i] * fRec12[(i - 1)]))) / fZec23[i]));
				fZec53[i] = ((0.800000012f * (fRec12[i] / fZec30[i])) + (fZec31[i] * fZec52[i]));
				fYec3[((i + fYec3_idx) & 8191)] = (fSlow1 * fZec53[i]);
				fRec1[((i + fRec1_idx) & 262143)] = (((fZec29[i] * fYec3[(((i + fYec3_idx) - iZec34[i]) & 8191)]) + ((fZec36[i] * fYec3[(((i + fYec3_idx) - iZec35[i]) & 8191)]) + (fZec37[i] + (fSlow14 * fZec53[i])))) - ((0.707106769f * ((fZec42[i] * fYec3[(((i + fYec3_idx) - iZec40[i]) & 8191)]) + (fZec43[i] * fYec3[(((i + fYec3_idx) - iZec44[i]) & 8191)]))) + (0.707106769f * ((fZec49[i] * fYec3[(((i + fYec3_idx) - iZec47[i]) & 8191)]) + (fZec50[i] * fYec3[(((i + fYec3_idx) - iZec51[i]) & 8191)])))));
				
			}
			/* Post code */
			fYec3_idx_save = vsize;
			fYec2_idx_save = vsize;
			for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
				fRec12_perm[j15] = fRec12_tmp[(vsize + j15)];
				
			}
			fYec1_idx_save = vsize;
			fYec0_idx_save = vsize;
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				fRec3_perm[j9] = fRec3_tmp[(vsize + j9)];
				
			}
			fRec0_idx_save = vsize;
			fRec1_idx_save = vsize;
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((fRec0[((i + fRec0_idx) & 262143)] + (fSlow34 * fZec37[i])));
				
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output1[i] = FAUSTFLOAT(fRec1[((i + fRec1_idx) & 262143)]);
				
			}
			
		}
		
	}

	
};

#endif
