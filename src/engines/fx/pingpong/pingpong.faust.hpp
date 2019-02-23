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

static float faust_pingpong_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_pingpong
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faust_pingpong : public dsp {
	
 private:
	
	FAUSTFLOAT fCheckbox0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider0;
	float fConst1;
	float fVec0[262144];
	int fVec0_idx;
	int fVec0_idx_save;
	float fRec4_perm[4];
	float fRec3_perm[4];
	FAUSTFLOAT fHslider1;
	float fRec5_perm[4];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fYec0[131072];
	int fYec0_idx;
	int fYec0_idx_save;
	float fConst2;
	float fRec2_perm[4];
	float fConst3;
	float fConst4;
	float fRec6[4194304];
	int fRec6_idx;
	int fRec6_idx_save;
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
	float fYec1[131072];
	int fYec1_idx;
	int fYec1_idx_save;
	float fRec7_perm[4];
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
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = (0.125f * fConst0);
		fConst2 = (3.14159274f / fConst0);
		fConst3 = std::exp((0.0f - (5.0f / fConst0)));
		fConst4 = (1.0f - fConst3);
		
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 262144); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		fVec0_idx = 0;
		fVec0_idx_save = 0;
		for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) {
			fRec4_perm[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) {
			fRec3_perm[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) {
			fRec5_perm[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 131072); l4 = (l4 + 1)) {
			fYec0[l4] = 0.0f;
			
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l5 = 0; (l5 < 4); l5 = (l5 + 1)) {
			fRec2_perm[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 4194304); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
			
		}
		fRec6_idx = 0;
		fRec6_idx_save = 0;
		for (int l7 = 0; (l7 < 262144); l7 = (l7 + 1)) {
			fRec0[l7] = 0.0f;
			
		}
		fRec0_idx = 0;
		fRec0_idx_save = 0;
		for (int l8 = 0; (l8 < 131072); l8 = (l8 + 1)) {
			fYec1[l8] = 0.0f;
			
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l9 = 0; (l9 < 4); l9 = (l9 + 1)) {
			fRec7_perm[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 262144); l10 = (l10 + 1)) {
			fRec1[l10] = 0.0f;
			
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
		ui_interface->addHorizontalSlider("delaytime", &fHslider0, 0.5f, 0.00999999978f, 0.999000013f, 0.00100000005f);
		ui_interface->addHorizontalSlider("feedback", &fHslider2, 0.5f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("spread", &fHslider3, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("tone", &fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		float fSlow0 = std::max<float>(0.00999999978f, std::min<float>(1.0f, float(fHslider0)));
		float fSlow1 = (int(float(fCheckbox0))?(fConst1 * std::ceil((4.0f * fSlow0))):float(int((fConst0 * fSlow0))));
		int iSlow2 = int(fSlow1);
		float fRec4_tmp[36];
		float* fRec4 = &fRec4_tmp[4];
		float fRec3_tmp[36];
		float* fRec3 = &fRec3_tmp[4];
		float fSlow3 = (0.00100000005f * ((1900.0f * float(fHslider1)) + 100.0f));
		float fRec5_tmp[36];
		float* fRec5 = &fRec5_tmp[4];
		float fSlow4 = float(fHslider2);
		float fSlow5 = float(fHslider3);
		int iSlow6 = (fSlow5 == 1.0f);
		int iSlow7 = (1 - iSlow6);
		int iSlow8 = (iSlow2 + 1);
		float fZec0[32];
		int iSlow9 = (int((float((iSlow7 * int((1000.0f * fSlow5)))) + fSlow1)) + 1);
		float fZec1[32];
		int iZec2[32];
		int iZec3[32];
		float fZec4[32];
		float fZec5[32];
		float fZec6[32];
		int iZec7[32];
		float fZec8[32];
		float fZec9[32];
		int iZec10[32];
		int iZec11[32];
		float fZec12[32];
		float fZec13[32];
		float fZec14[32];
		int iZec15[32];
		float fZec16[32];
		float fZec17[32];
		float fZec18[32];
		float fZec19[32];
		float fZec20[32];
		float fZec21[32];
		float fZec22[32];
		float fRec2_tmp[36];
		float* fRec2 = &fRec2_tmp[4];
		float fZec23[32];
		float fZec24[32];
		float fZec25[32];
		float fSlow10 = float(iSlow7);
		int iSlow11 = int((2.0f * fSlow1));
		int iSlow12 = int((3.0f * fSlow1));
		int iSlow13 = int((4.0f * fSlow1));
		int iSlow14 = int((5.0f * fSlow1));
		int iSlow15 = int((6.0f * fSlow1));
		int iSlow16 = int((7.0f * fSlow1));
		int iSlow17 = int((8.0f * fSlow1));
		int iSlow18 = int((9.0f * fSlow1));
		int iSlow19 = int((10.0f * fSlow1));
		int iSlow20 = int((11.0f * fSlow1));
		int iSlow21 = int((12.0f * fSlow1));
		int iSlow22 = int((13.0f * fSlow1));
		int iSlow23 = int((14.0f * fSlow1));
		int iSlow24 = int((15.0f * fSlow1));
		int iSlow25 = int((16.0f * fSlow1));
		int iSlow26 = int((17.0f * fSlow1));
		int iSlow27 = int((18.0f * fSlow1));
		int iSlow28 = int((19.0f * fSlow1));
		float fZec26[32];
		float fZec27[32];
		float fRec7_tmp[36];
		float* fRec7 = &fRec7_tmp[4];
		float fSlow29 = float(iSlow6);
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
				fVec0[((i + fVec0_idx) & 262143)] = fSlow1;
				
			}
			/* Post code */
			fVec0_idx_save = vsize;
			/* Recursive loop 1 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec5_tmp[j4] = fRec5_perm[j4];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec5[i] = (fSlow3 + (0.999000013f * fRec5[(i - 1)]));
				
			}
			/* Post code */
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec5_perm[j5] = fRec5_tmp[(vsize + j5)];
				
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec4_tmp[j0] = fRec4_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec4[i] = ((0.999000013f * fRec4[(i - 1)]) + (0.0120000001f * ((fVec0[(((i + fVec0_idx) - iSlow2) & 262143)] - fSlow1) / fSlow1)));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec4_perm[j1] = fRec4_tmp[(vsize + j1)];
				
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec18[i] = std::tan((fConst2 * fRec5[i]));
				
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec3_tmp[j2] = fRec3_perm[j2];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec3[i] = std::fmod((fRec3[(i - 1)] + (251.0f - std::pow(2.0f, (0.0833333358f * fRec4[i])))), 250.0f);
				
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec3_perm[j3] = fRec3_tmp[(vsize + j3)];
				
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec19[i] = (1.0f / fZec18[i]);
				
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec9[i] = (fRec3[i] + 250.0f);
				
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec22[i] = (((fZec19[i] + 1.0f) / fZec18[i]) + 1.0f);
				
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec23[i] = std::fabs(float(input0[i]));
				
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec2[i] = int(fRec3[i]);
				
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec4[i] = std::floor(fRec3[i]);
				
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec8[i] = std::min<float>((0.0199999996f * fRec3[i]), 1.0f);
				
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec10[i] = int(fZec9[i]);
				
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec12[i] = std::floor(fZec9[i]);
				
			}
			/* Recursive loop 14 */
			/* Pre code */
			fRec6_idx = ((fRec6_idx + fRec6_idx_save) & 4194303);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec6[((i + fRec6_idx) & 4194303)] = std::max<float>(fZec23[i], ((fConst3 * fRec6[(((i + fRec6_idx) - 1) & 4194303)]) + (fConst4 * fZec23[i])));
				
			}
			/* Post code */
			fRec6_idx_save = vsize;
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec24[i] = (fZec18[i] * fZec22[i]);
				
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec3[i] = std::min<int>(65537, std::max<int>(0, iZec2[i]));
				
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec5[i] = (fZec4[i] + (1.0f - fRec3[i]));
				
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = (fRec3[i] - fZec4[i]);
				
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec7[i] = std::min<int>(65537, std::max<int>(0, (iZec2[i] + 1)));
				
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec11[i] = std::min<int>(65537, std::max<int>(0, iZec10[i]));
				
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec13[i] = (fZec12[i] + (-249.0f - fRec3[i]));
				
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec14[i] = (fRec3[i] + (250.0f - fZec12[i]));
				
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec15[i] = std::min<int>(65537, std::max<int>(0, (iZec10[i] + 1)));
				
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec16[i] = (1.0f - fZec8[i]);
				
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec20[i] = (1.0f - ((1.0f - fZec19[i]) / fZec18[i]));
				
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec21[i] = (1.0f - (1.0f / faust_pingpong_faustpower2_f(fZec18[i])));
				
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec25[i] = (0.0f - (1.0f / fZec24[i]));
				
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fHbargraph0 = FAUSTFLOAT(fRec6[((i + fRec6_idx) & 4194303)]);
				fHbargraph1 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow2) & 4194303)]);
				fHbargraph2 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow11) & 4194303)]);
				fHbargraph3 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow12) & 4194303)]);
				fHbargraph4 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow13) & 4194303)]);
				fHbargraph5 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow14) & 4194303)]);
				fHbargraph6 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow15) & 4194303)]);
				fHbargraph7 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow16) & 4194303)]);
				fHbargraph8 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow17) & 4194303)]);
				fHbargraph9 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow18) & 4194303)]);
				fHbargraph10 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow19) & 4194303)]);
				fHbargraph11 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow20) & 4194303)]);
				fHbargraph12 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow21) & 4194303)]);
				fHbargraph13 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow22) & 4194303)]);
				fHbargraph14 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow23) & 4194303)]);
				fHbargraph15 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow24) & 4194303)]);
				fHbargraph16 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow25) & 4194303)]);
				fHbargraph17 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow26) & 4194303)]);
				fHbargraph18 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow27) & 4194303)]);
				fHbargraph19 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow28) & 4194303)]);
				fZec26[i] = float(input0[i]);
				
			}
			/* Recursive loop 29 */
			/* Pre code */
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 131071);
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				fRec2_tmp[j6] = fRec2_perm[j6];
				
			}
			fRec0_idx = ((fRec0_idx + fRec0_idx_save) & 262143);
			fYec1_idx = ((fYec1_idx + fYec1_idx_save) & 131071);
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				fRec7_tmp[j8] = fRec7_perm[j8];
				
			}
			fRec1_idx = ((fRec1_idx + fRec1_idx_save) & 262143);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec0[i] = fRec1[(((i + fRec1_idx) - iSlow8) & 262143)];
				fZec1[i] = fRec0[(((i + fRec0_idx) - iSlow9) & 262143)];
				fYec0[((i + fYec0_idx) & 131071)] = (fSlow4 * (iSlow7?fZec1[i]:fZec0[i]));
				fZec17[i] = fRec2[(i - 2)];
				fRec2[i] = (((((fYec0[(((i + fYec0_idx) - iZec3[i]) & 131071)] * fZec5[i]) + (fZec6[i] * fYec0[(((i + fYec0_idx) - iZec7[i]) & 131071)])) * fZec8[i]) + (((fYec0[(((i + fYec0_idx) - iZec11[i]) & 131071)] * fZec13[i]) + (fZec14[i] * fYec0[(((i + fYec0_idx) - iZec15[i]) & 131071)])) * fZec16[i])) - (((fZec17[i] * fZec20[i]) + (2.0f * (fRec2[(i - 1)] * fZec21[i]))) / fZec22[i]));
				fRec0[((i + fRec0_idx) & 262143)] = (((fRec2[i] / fZec24[i]) + (fZec17[i] * fZec25[i])) + (fSlow10 * fZec26[i]));
				fYec1[((i + fYec1_idx) & 131071)] = (fSlow4 * (iSlow7?fZec0[i]:fZec1[i]));
				fZec27[i] = fRec7[(i - 2)];
				fRec7[i] = (((fZec8[i] * ((fZec5[i] * fYec1[(((i + fYec1_idx) - iZec3[i]) & 131071)]) + (fZec6[i] * fYec1[(((i + fYec1_idx) - iZec7[i]) & 131071)]))) + (fZec16[i] * ((fZec13[i] * fYec1[(((i + fYec1_idx) - iZec11[i]) & 131071)]) + (fZec14[i] * fYec1[(((i + fYec1_idx) - iZec15[i]) & 131071)])))) - (((fZec20[i] * fZec27[i]) + (2.0f * (fZec21[i] * fRec7[(i - 1)]))) / fZec22[i]));
				fRec1[((i + fRec1_idx) & 262143)] = ((fZec25[i] * fZec27[i]) + (fZec26[i] + (fRec7[i] / fZec24[i])));
				
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				fRec7_perm[j9] = fRec7_tmp[(vsize + j9)];
				
			}
			fYec0_idx_save = vsize;
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				fRec2_perm[j7] = fRec2_tmp[(vsize + j7)];
				
			}
			fRec0_idx_save = vsize;
			fRec1_idx_save = vsize;
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((fRec0[((i + fRec0_idx) & 262143)] + (fSlow29 * fZec26[i])));
				
			}
			/* Vectorizable loop 31 */
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
				fVec0[((i + fVec0_idx) & 262143)] = fSlow1;
				
			}
			/* Post code */
			fVec0_idx_save = vsize;
			/* Recursive loop 1 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec5_tmp[j4] = fRec5_perm[j4];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec5[i] = (fSlow3 + (0.999000013f * fRec5[(i - 1)]));
				
			}
			/* Post code */
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec5_perm[j5] = fRec5_tmp[(vsize + j5)];
				
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec4_tmp[j0] = fRec4_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec4[i] = ((0.999000013f * fRec4[(i - 1)]) + (0.0120000001f * ((fVec0[(((i + fVec0_idx) - iSlow2) & 262143)] - fSlow1) / fSlow1)));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec4_perm[j1] = fRec4_tmp[(vsize + j1)];
				
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec18[i] = std::tan((fConst2 * fRec5[i]));
				
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec3_tmp[j2] = fRec3_perm[j2];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec3[i] = std::fmod((fRec3[(i - 1)] + (251.0f - std::pow(2.0f, (0.0833333358f * fRec4[i])))), 250.0f);
				
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec3_perm[j3] = fRec3_tmp[(vsize + j3)];
				
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec19[i] = (1.0f / fZec18[i]);
				
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec9[i] = (fRec3[i] + 250.0f);
				
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec22[i] = (((fZec19[i] + 1.0f) / fZec18[i]) + 1.0f);
				
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec23[i] = std::fabs(float(input0[i]));
				
			}
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec2[i] = int(fRec3[i]);
				
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec4[i] = std::floor(fRec3[i]);
				
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec8[i] = std::min<float>((0.0199999996f * fRec3[i]), 1.0f);
				
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec10[i] = int(fZec9[i]);
				
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec12[i] = std::floor(fZec9[i]);
				
			}
			/* Recursive loop 14 */
			/* Pre code */
			fRec6_idx = ((fRec6_idx + fRec6_idx_save) & 4194303);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec6[((i + fRec6_idx) & 4194303)] = std::max<float>(fZec23[i], ((fConst3 * fRec6[(((i + fRec6_idx) - 1) & 4194303)]) + (fConst4 * fZec23[i])));
				
			}
			/* Post code */
			fRec6_idx_save = vsize;
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec24[i] = (fZec18[i] * fZec22[i]);
				
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec3[i] = std::min<int>(65537, std::max<int>(0, iZec2[i]));
				
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec5[i] = (fZec4[i] + (1.0f - fRec3[i]));
				
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = (fRec3[i] - fZec4[i]);
				
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec7[i] = std::min<int>(65537, std::max<int>(0, (iZec2[i] + 1)));
				
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec11[i] = std::min<int>(65537, std::max<int>(0, iZec10[i]));
				
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec13[i] = (fZec12[i] + (-249.0f - fRec3[i]));
				
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec14[i] = (fRec3[i] + (250.0f - fZec12[i]));
				
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec15[i] = std::min<int>(65537, std::max<int>(0, (iZec10[i] + 1)));
				
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec16[i] = (1.0f - fZec8[i]);
				
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec20[i] = (1.0f - ((1.0f - fZec19[i]) / fZec18[i]));
				
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec21[i] = (1.0f - (1.0f / faust_pingpong_faustpower2_f(fZec18[i])));
				
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec25[i] = (0.0f - (1.0f / fZec24[i]));
				
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fHbargraph0 = FAUSTFLOAT(fRec6[((i + fRec6_idx) & 4194303)]);
				fHbargraph1 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow2) & 4194303)]);
				fHbargraph2 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow11) & 4194303)]);
				fHbargraph3 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow12) & 4194303)]);
				fHbargraph4 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow13) & 4194303)]);
				fHbargraph5 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow14) & 4194303)]);
				fHbargraph6 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow15) & 4194303)]);
				fHbargraph7 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow16) & 4194303)]);
				fHbargraph8 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow17) & 4194303)]);
				fHbargraph9 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow18) & 4194303)]);
				fHbargraph10 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow19) & 4194303)]);
				fHbargraph11 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow20) & 4194303)]);
				fHbargraph12 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow21) & 4194303)]);
				fHbargraph13 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow22) & 4194303)]);
				fHbargraph14 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow23) & 4194303)]);
				fHbargraph15 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow24) & 4194303)]);
				fHbargraph16 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow25) & 4194303)]);
				fHbargraph17 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow26) & 4194303)]);
				fHbargraph18 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow27) & 4194303)]);
				fHbargraph19 = FAUSTFLOAT(fRec6[(((i + fRec6_idx) - iSlow28) & 4194303)]);
				fZec26[i] = float(input0[i]);
				
			}
			/* Recursive loop 29 */
			/* Pre code */
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 131071);
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				fRec2_tmp[j6] = fRec2_perm[j6];
				
			}
			fRec0_idx = ((fRec0_idx + fRec0_idx_save) & 262143);
			fYec1_idx = ((fYec1_idx + fYec1_idx_save) & 131071);
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				fRec7_tmp[j8] = fRec7_perm[j8];
				
			}
			fRec1_idx = ((fRec1_idx + fRec1_idx_save) & 262143);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec0[i] = fRec1[(((i + fRec1_idx) - iSlow8) & 262143)];
				fZec1[i] = fRec0[(((i + fRec0_idx) - iSlow9) & 262143)];
				fYec0[((i + fYec0_idx) & 131071)] = (fSlow4 * (iSlow7?fZec1[i]:fZec0[i]));
				fZec17[i] = fRec2[(i - 2)];
				fRec2[i] = (((((fYec0[(((i + fYec0_idx) - iZec3[i]) & 131071)] * fZec5[i]) + (fZec6[i] * fYec0[(((i + fYec0_idx) - iZec7[i]) & 131071)])) * fZec8[i]) + (((fYec0[(((i + fYec0_idx) - iZec11[i]) & 131071)] * fZec13[i]) + (fZec14[i] * fYec0[(((i + fYec0_idx) - iZec15[i]) & 131071)])) * fZec16[i])) - (((fZec17[i] * fZec20[i]) + (2.0f * (fRec2[(i - 1)] * fZec21[i]))) / fZec22[i]));
				fRec0[((i + fRec0_idx) & 262143)] = (((fRec2[i] / fZec24[i]) + (fZec17[i] * fZec25[i])) + (fSlow10 * fZec26[i]));
				fYec1[((i + fYec1_idx) & 131071)] = (fSlow4 * (iSlow7?fZec0[i]:fZec1[i]));
				fZec27[i] = fRec7[(i - 2)];
				fRec7[i] = (((fZec8[i] * ((fZec5[i] * fYec1[(((i + fYec1_idx) - iZec3[i]) & 131071)]) + (fZec6[i] * fYec1[(((i + fYec1_idx) - iZec7[i]) & 131071)]))) + (fZec16[i] * ((fZec13[i] * fYec1[(((i + fYec1_idx) - iZec11[i]) & 131071)]) + (fZec14[i] * fYec1[(((i + fYec1_idx) - iZec15[i]) & 131071)])))) - (((fZec20[i] * fZec27[i]) + (2.0f * (fZec21[i] * fRec7[(i - 1)]))) / fZec22[i]));
				fRec1[((i + fRec1_idx) & 262143)] = ((fZec25[i] * fZec27[i]) + (fZec26[i] + (fRec7[i] / fZec24[i])));
				
			}
			/* Post code */
			fYec1_idx_save = vsize;
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				fRec7_perm[j9] = fRec7_tmp[(vsize + j9)];
				
			}
			fYec0_idx_save = vsize;
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				fRec2_perm[j7] = fRec2_tmp[(vsize + j7)];
				
			}
			fRec0_idx_save = vsize;
			fRec1_idx_save = vsize;
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((fRec0[((i + fRec0_idx) & 262143)] + (fSlow29 * fZec26[i])));
				
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output1[i] = FAUSTFLOAT(fRec1[((i + fRec1_idx) & 262143)]);
				
			}
			
		}
		
	}

	
};

#endif
