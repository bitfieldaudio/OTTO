/* ------------------------------------------------------------
name: "vocoder"
Code generated with Faust 2.11.10 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faust_vocoder_H__
#define  __faust_vocoder_H__

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

static float faust_vocoder_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_vocoder
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faust_vocoder : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider1;
	int iRec2[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fRec1[2];
	float fConst2;
	FAUSTFLOAT fHslider5;
	float fRec3[2];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fButton1;
	int iRec6[2];
	float fRec5[2];
	FAUSTFLOAT fHslider7;
	float fRec7[2];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fButton2;
	int iRec10[2];
	float fRec9[2];
	FAUSTFLOAT fHslider9;
	float fRec11[2];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fButton3;
	int iRec14[2];
	float fRec13[2];
	FAUSTFLOAT fHslider11;
	float fRec15[2];
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fButton4;
	int iRec18[2];
	float fRec17[2];
	FAUSTFLOAT fHslider13;
	float fRec19[2];
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fButton5;
	int iRec22[2];
	float fRec21[2];
	FAUSTFLOAT fHslider15;
	float fRec23[2];
	float fConst3;
	float fConst4;
	FAUSTFLOAT fHslider16;
	float fRec25[2];
	float fConst5;
	float fRec0[3];
	float fConst6;
	float fConst7;
	float fRec32[2];
	FAUSTFLOAT fHslider17;
	float fRec33[2];
	int iVec0[2];
	int iConst8;
	int iRec34[2];
	float fRec30[2];
	float fRec28[3];
	FAUSTFLOAT fHslider18;
	float fRec35[2];
	FAUSTFLOAT fHslider19;
	float fRec36[2];
	float fRec27[2];
	float fRec26[2];
	float fConst9;
	float fConst10;
	float fConst11;
	float fRec37[3];
	float fRec40[3];
	float fRec39[2];
	float fRec38[2];
	float fConst12;
	float fConst13;
	float fConst14;
	float fRec41[3];
	float fRec44[3];
	float fRec43[2];
	float fRec42[2];
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec45[3];
	float fRec48[3];
	float fRec47[2];
	float fRec46[2];
	float fConst18;
	float fConst19;
	float fConst20;
	float fRec49[3];
	float fRec52[3];
	float fRec51[2];
	float fRec50[2];
	float fConst21;
	float fConst22;
	float fConst23;
	float fRec53[3];
	float fRec56[3];
	float fRec55[2];
	float fRec54[2];
	float fConst24;
	float fConst25;
	float fConst26;
	float fRec57[3];
	float fRec60[3];
	float fRec59[2];
	float fRec58[2];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec61[3];
	float fRec64[3];
	float fRec63[2];
	float fRec62[2];
	float fConst30;
	float fConst31;
	float fConst32;
	float fRec65[3];
	float fRec68[3];
	float fRec67[2];
	float fRec66[2];
	float fConst33;
	float fConst34;
	float fConst35;
	float fRec69[3];
	float fRec72[3];
	float fRec71[2];
	float fRec70[2];
	float fConst36;
	float fConst37;
	float fConst38;
	float fRec73[3];
	float fRec76[3];
	float fRec75[2];
	float fRec74[2];
	float fConst39;
	float fConst40;
	float fConst41;
	float fRec77[3];
	float fRec80[3];
	float fRec79[2];
	float fRec78[2];
	float fConst42;
	float fConst43;
	float fConst44;
	float fRec81[3];
	float fRec84[3];
	float fRec83[2];
	float fRec82[2];
	float fConst45;
	float fConst46;
	float fConst47;
	float fRec85[3];
	float fRec88[3];
	float fRec87[2];
	float fRec86[2];
	float fConst48;
	float fConst49;
	float fConst50;
	float fRec89[3];
	float fRec92[3];
	float fRec91[2];
	float fRec90[2];
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec93[3];
	float fRec96[3];
	float fRec95[2];
	float fRec94[2];
	float fConst54;
	float fConst55;
	float fConst56;
	float fRec97[3];
	float fRec100[3];
	float fRec99[2];
	float fRec98[2];
	float fConst57;
	float fConst58;
	float fConst59;
	float fRec101[3];
	float fRec104[3];
	float fRec103[2];
	float fRec102[2];
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec105[3];
	float fRec108[3];
	float fRec107[2];
	float fRec106[2];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec109[3];
	float fRec112[3];
	float fRec111[2];
	float fRec110[2];
	float fConst66;
	float fConst67;
	float fConst68;
	float fRec113[3];
	float fRec116[3];
	float fRec115[2];
	float fRec114[2];
	float fConst69;
	float fConst70;
	float fConst71;
	float fRec117[3];
	float fRec120[3];
	float fRec119[2];
	float fRec118[2];
	float fConst72;
	float fConst73;
	float fConst74;
	float fRec121[3];
	float fRec124[3];
	float fRec123[2];
	float fRec122[2];
	float fConst75;
	float fConst76;
	float fConst77;
	float fRec125[3];
	float fRec128[3];
	float fRec127[2];
	float fRec126[2];
	float fConst78;
	float fConst79;
	float fConst80;
	float fRec129[3];
	float fRec132[3];
	float fRec131[2];
	float fRec130[2];
	float fConst81;
	float fConst82;
	float fConst83;
	float fRec133[3];
	float fRec136[3];
	float fRec135[2];
	float fRec134[2];
	float fConst84;
	float fConst85;
	float fConst86;
	float fRec137[3];
	float fRec140[3];
	float fRec139[2];
	float fRec138[2];
	float fConst87;
	float fConst88;
	float fConst89;
	float fRec141[3];
	float fRec144[3];
	float fRec143[2];
	float fRec142[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "vocoder");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "vocoder");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("vaeffects.lib/name", "Faust Virtual Analog Filter Effect Library");
		m->declare("vaeffects.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 1;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
	}
	virtual int getInputRate(int channel) {
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
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = (6.90999985f / fConst0);
		fConst2 = (1.0f / fConst0);
		fConst3 = std::tan((40212.3867f / fConst0));
		fConst4 = (1.0f / fConst3);
		fConst5 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst3))));
		fConst6 = std::exp((0.0f - (100.0f / fConst0)));
		fConst7 = (1.0f - fConst6);
		iConst8 = int((9.99999975e-05f * fConst0));
		fConst9 = std::tan((32181.0488f / fConst0));
		fConst10 = (1.0f / fConst9);
		fConst11 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst9))));
		fConst12 = std::tan((25753.7559f / fConst0));
		fConst13 = (1.0f / fConst12);
		fConst14 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst12))));
		fConst15 = std::tan((20610.1387f / fConst0));
		fConst16 = (1.0f / fConst15);
		fConst17 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst15))));
		fConst18 = std::tan((16493.8203f / fConst0));
		fConst19 = (1.0f / fConst18);
		fConst20 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst18))));
		fConst21 = std::tan((13199.626f / fConst0));
		fConst22 = (1.0f / fConst21);
		fConst23 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst21))));
		fConst24 = std::tan((10563.3574f / fConst0));
		fConst25 = (1.0f / fConst24);
		fConst26 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst24))));
		fConst27 = std::tan((8453.61328f / fConst0));
		fConst28 = (1.0f / fConst27);
		fConst29 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst27))));
		fConst30 = std::tan((6765.23242f / fConst0));
		fConst31 = (1.0f / fConst30);
		fConst32 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst30))));
		fConst33 = std::tan((5414.06006f / fConst0));
		fConst34 = (1.0f / fConst33);
		fConst35 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst33))));
		fConst36 = std::tan((4332.74805f / fConst0));
		fConst37 = (1.0f / fConst36);
		fConst38 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst36))));
		fConst39 = std::tan((3467.39868f / fConst0));
		fConst40 = (1.0f / fConst39);
		fConst41 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst39))));
		fConst42 = std::tan((2774.87964f / fConst0));
		fConst43 = (1.0f / fConst42);
		fConst44 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst42))));
		fConst45 = std::tan((2220.67236f / fConst0));
		fConst46 = (1.0f / fConst45);
		fConst47 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst45))));
		fConst48 = std::tan((1777.1532f / fConst0));
		fConst49 = (1.0f / fConst48);
		fConst50 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst48))));
		fConst51 = std::tan((1422.21484f / fConst0));
		fConst52 = (1.0f / fConst51);
		fConst53 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst51))));
		fConst54 = std::tan((1138.16589f / fConst0));
		fConst55 = (1.0f / fConst54);
		fConst56 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst54))));
		fConst57 = std::tan((910.848083f / fConst0));
		fConst58 = (1.0f / fConst57);
		fConst59 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst57))));
		fConst60 = std::tan((728.930786f / fConst0));
		fConst61 = (1.0f / fConst60);
		fConst62 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst60))));
		fConst63 = std::tan((583.346558f / fConst0));
		fConst64 = (1.0f / fConst63);
		fConst65 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst63))));
		fConst66 = std::tan((466.838867f / fConst0));
		fConst67 = (1.0f / fConst66);
		fConst68 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst66))));
		fConst69 = std::tan((373.600433f / fConst0));
		fConst70 = (1.0f / fConst69);
		fConst71 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst69))));
		fConst72 = std::tan((298.983856f / fConst0));
		fConst73 = (1.0f / fConst72);
		fConst74 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst72))));
		fConst75 = std::tan((239.269913f / fConst0));
		fConst76 = (1.0f / fConst75);
		fConst77 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst75))));
		fConst78 = std::tan((191.482224f / fConst0));
		fConst79 = (1.0f / fConst78);
		fConst80 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst78))));
		fConst81 = std::tan((153.238815f / fConst0));
		fConst82 = (1.0f / fConst81);
		fConst83 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst81))));
		fConst84 = std::tan((122.633514f / fConst0));
		fConst85 = (1.0f / fConst84);
		fConst86 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst84))));
		fConst87 = std::tan((98.1407852f / fConst0));
		fConst88 = (1.0f / fConst87);
		fConst89 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst87))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.001f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(1.0f);
		fHslider5 = FAUSTFLOAT(440.0f);
		fHslider6 = FAUSTFLOAT(1.0f);
		fButton1 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(440.0f);
		fHslider8 = FAUSTFLOAT(1.0f);
		fButton2 = FAUSTFLOAT(0.0f);
		fHslider9 = FAUSTFLOAT(440.0f);
		fHslider10 = FAUSTFLOAT(1.0f);
		fButton3 = FAUSTFLOAT(0.0f);
		fHslider11 = FAUSTFLOAT(440.0f);
		fHslider12 = FAUSTFLOAT(1.0f);
		fButton4 = FAUSTFLOAT(0.0f);
		fHslider13 = FAUSTFLOAT(440.0f);
		fHslider14 = FAUSTFLOAT(1.0f);
		fButton5 = FAUSTFLOAT(0.0f);
		fHslider15 = FAUSTFLOAT(440.0f);
		fHslider16 = FAUSTFLOAT(0.10000000000000001f);
		fHslider17 = FAUSTFLOAT(0.5f);
		fHslider18 = FAUSTFLOAT(0.5f);
		fHslider19 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec2[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iRec6[l3] = 0;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec7[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iRec10[l6] = 0;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec9[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec11[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			iRec14[l9] = 0;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec13[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec15[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			iRec18[l12] = 0;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec17[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec19[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			iRec22[l15] = 0;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec21[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec23[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec25[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec0[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec32[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec33[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			iVec0[l22] = 0;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			iRec34[l23] = 0;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec30[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec28[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec35[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec36[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec27[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec26[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec37[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec40[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec39[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec38[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec41[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec44[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec43[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec42[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec45[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec48[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec47[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec46[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec49[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec52[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec51[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec50[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec53[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec56[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec55[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec54[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec57[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec60[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec59[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec58[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec61[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec64[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec63[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec62[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec65[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec68[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec67[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec66[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec69[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec72[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec71[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec70[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec73[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec76[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec75[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec74[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec77[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec80[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec79[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec78[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec81[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec84[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			fRec83[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec82[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec85[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec88[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fRec87[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec86[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec89[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec92[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec91[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec90[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec93[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec96[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			fRec95[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			fRec94[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec97[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec100[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec99[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fRec98[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec101[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec104[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			fRec103[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fRec102[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec105[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec108[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fRec107[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec106[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec109[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec112[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			fRec111[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec110[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec113[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec116[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fRec115[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			fRec114[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec117[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec120[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			fRec119[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fRec118[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec121[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec124[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			fRec123[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			fRec122[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec125[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec128[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fRec127[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			fRec126[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			fRec129[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec132[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			fRec131[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec130[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec133[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			fRec136[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			fRec135[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fRec134[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec137[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec140[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) {
			fRec139[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			fRec138[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			fRec141[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec144[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			fRec143[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			fRec142[l137] = 0.0f;
			
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
	
	virtual faust_vocoder* clone() {
		return new faust_vocoder();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("vocoder");
		ui_interface->addHorizontalSlider("attTime", &fHslider18, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("decTime", &fHslider19, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fHslider2, 0.00100000005f, 0.00100000005f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Decay", &fHslider3, 0.0f, 0.0f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Release", &fHslider1, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Sustain", &fHslider4, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("gateamount", &fHslider17, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("ratio", &fHslider16, 0.100000001f, 0.100000001f, 2.0f, 0.00999999978f);
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider5, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton0);
		ui_interface->addHorizontalSlider("velocity", &fHslider0, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider9, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton2);
		ui_interface->addHorizontalSlider("velocity", &fHslider8, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider13, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton4);
		ui_interface->addHorizontalSlider("velocity", &fHslider12, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider7, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton1);
		ui_interface->addHorizontalSlider("velocity", &fHslider6, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider11, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton3);
		ui_interface->addHorizontalSlider("velocity", &fHslider10, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider15, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton5);
		ui_interface->addHorizontalSlider("velocity", &fHslider14, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		int iSlow1 = (float(fButton0) > 0.0f);
		float fSlow2 = float(fHslider1);
		float fSlow3 = float(fHslider2);
		int iSlow4 = int((fConst0 * fSlow3));
		float fSlow5 = float(fHslider3);
		float fSlow6 = (6.90999985f * fSlow3);
		float fSlow7 = float(fHslider4);
		float fSlow8 = (float(iSlow1) * fSlow7);
		float fSlow9 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider5)));
		float fSlow10 = (fConst2 * fSlow9);
		float fSlow11 = (1.0f - (fConst0 / fSlow9));
		float fSlow12 = float(fHslider6);
		int iSlow13 = (float(fButton1) > 0.0f);
		float fSlow14 = (float(iSlow13) * fSlow7);
		float fSlow15 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider7)));
		float fSlow16 = (fConst2 * fSlow15);
		float fSlow17 = (1.0f - (fConst0 / fSlow15));
		float fSlow18 = float(fHslider8);
		int iSlow19 = (float(fButton2) > 0.0f);
		float fSlow20 = (float(iSlow19) * fSlow7);
		float fSlow21 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider9)));
		float fSlow22 = (fConst2 * fSlow21);
		float fSlow23 = (1.0f - (fConst0 / fSlow21));
		float fSlow24 = float(fHslider10);
		int iSlow25 = (float(fButton3) > 0.0f);
		float fSlow26 = (float(iSlow25) * fSlow7);
		float fSlow27 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider11)));
		float fSlow28 = (fConst2 * fSlow27);
		float fSlow29 = (1.0f - (fConst0 / fSlow27));
		float fSlow30 = float(fHslider12);
		int iSlow31 = (float(fButton4) > 0.0f);
		float fSlow32 = (float(iSlow31) * fSlow7);
		float fSlow33 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider13)));
		float fSlow34 = (fConst2 * fSlow33);
		float fSlow35 = (1.0f - (fConst0 / fSlow33));
		float fSlow36 = float(fHslider14);
		int iSlow37 = (float(fButton5) > 0.0f);
		float fSlow38 = (float(iSlow37) * fSlow7);
		float fSlow39 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider15)));
		float fSlow40 = (fConst2 * fSlow39);
		float fSlow41 = (1.0f - (fConst0 / fSlow39));
		float fSlow42 = (0.00100000005f * float(fHslider16));
		float fSlow43 = (0.00100000005f * float(fHslider17));
		float fSlow44 = (0.00100000005f * float(fHslider18));
		float fSlow45 = (0.00100000005f * float(fHslider19));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec2[0] = (iSlow1 * (iRec2[1] + 1));
			int iTemp0 = (iRec2[0] < iSlow4);
			float fTemp1 = std::exp((0.0f - (fConst1 / (iSlow1?(iTemp0?fSlow6:fSlow5):fSlow2))));
			fRec1[0] = ((fRec1[1] * fTemp1) + ((iSlow1?(iTemp0?1.58730161f:fSlow8):0.0f) * (1.0f - fTemp1)));
			float fTemp2 = (fSlow10 + (fRec3[1] + -1.0f));
			int iTemp3 = (fTemp2 < 0.0f);
			float fTemp4 = (fSlow10 + fRec3[1]);
			fRec3[0] = (iTemp3?fTemp4:fTemp2);
			float fRec4 = (iTemp3?fTemp4:(fSlow10 + (fRec3[1] + (fSlow11 * fTemp2))));
			iRec6[0] = (iSlow13 * (iRec6[1] + 1));
			int iTemp5 = (iRec6[0] < iSlow4);
			float fTemp6 = std::exp((0.0f - (fConst1 / (iSlow13?(iTemp5?fSlow6:fSlow5):fSlow2))));
			fRec5[0] = ((fRec5[1] * fTemp6) + ((iSlow13?(iTemp5?1.58730161f:fSlow14):0.0f) * (1.0f - fTemp6)));
			float fTemp7 = (fSlow16 + (fRec7[1] + -1.0f));
			int iTemp8 = (fTemp7 < 0.0f);
			float fTemp9 = (fSlow16 + fRec7[1]);
			fRec7[0] = (iTemp8?fTemp9:fTemp7);
			float fRec8 = (iTemp8?fTemp9:(fSlow16 + (fRec7[1] + (fSlow17 * fTemp7))));
			iRec10[0] = (iSlow19 * (iRec10[1] + 1));
			int iTemp10 = (iRec10[0] < iSlow4);
			float fTemp11 = std::exp((0.0f - (fConst1 / (iSlow19?(iTemp10?fSlow6:fSlow5):fSlow2))));
			fRec9[0] = ((fRec9[1] * fTemp11) + ((iSlow19?(iTemp10?1.58730161f:fSlow20):0.0f) * (1.0f - fTemp11)));
			float fTemp12 = (fSlow22 + (fRec11[1] + -1.0f));
			int iTemp13 = (fTemp12 < 0.0f);
			float fTemp14 = (fSlow22 + fRec11[1]);
			fRec11[0] = (iTemp13?fTemp14:fTemp12);
			float fRec12 = (iTemp13?fTemp14:(fSlow22 + (fRec11[1] + (fSlow23 * fTemp12))));
			iRec14[0] = (iSlow25 * (iRec14[1] + 1));
			int iTemp15 = (iRec14[0] < iSlow4);
			float fTemp16 = std::exp((0.0f - (fConst1 / (iSlow25?(iTemp15?fSlow6:fSlow5):fSlow2))));
			fRec13[0] = ((fRec13[1] * fTemp16) + ((iSlow25?(iTemp15?1.58730161f:fSlow26):0.0f) * (1.0f - fTemp16)));
			float fTemp17 = (fSlow28 + (fRec15[1] + -1.0f));
			int iTemp18 = (fTemp17 < 0.0f);
			float fTemp19 = (fSlow28 + fRec15[1]);
			fRec15[0] = (iTemp18?fTemp19:fTemp17);
			float fRec16 = (iTemp18?fTemp19:(fSlow28 + (fRec15[1] + (fSlow29 * fTemp17))));
			iRec18[0] = (iSlow31 * (iRec18[1] + 1));
			int iTemp20 = (iRec18[0] < iSlow4);
			float fTemp21 = std::exp((0.0f - (fConst1 / (iSlow31?(iTemp20?fSlow6:fSlow5):fSlow2))));
			fRec17[0] = ((fRec17[1] * fTemp21) + ((iSlow31?(iTemp20?1.58730161f:fSlow32):0.0f) * (1.0f - fTemp21)));
			float fTemp22 = (fSlow34 + (fRec19[1] + -1.0f));
			int iTemp23 = (fTemp22 < 0.0f);
			float fTemp24 = (fSlow34 + fRec19[1]);
			fRec19[0] = (iTemp23?fTemp24:fTemp22);
			float fRec20 = (iTemp23?fTemp24:(fSlow34 + (fRec19[1] + (fSlow35 * fTemp22))));
			iRec22[0] = (iSlow37 * (iRec22[1] + 1));
			int iTemp25 = (iRec22[0] < iSlow4);
			float fTemp26 = std::exp((0.0f - (fConst1 / (iSlow37?(iTemp25?fSlow6:fSlow5):fSlow2))));
			fRec21[0] = ((fRec21[1] * fTemp26) + ((iSlow37?(iTemp25?1.58730161f:fSlow38):0.0f) * (1.0f - fTemp26)));
			float fTemp27 = (fSlow40 + (fRec23[1] + -1.0f));
			int iTemp28 = (fTemp27 < 0.0f);
			float fTemp29 = (fSlow40 + fRec23[1]);
			fRec23[0] = (iTemp28?fTemp29:fTemp27);
			float fRec24 = (iTemp28?fTemp29:(fSlow40 + (fRec23[1] + (fSlow41 * fTemp27))));
			float fTemp30 = (0.200000003f * ((((((fSlow0 * (std::min<float>(1.0f, fRec1[0]) * ((2.0f * fRec4) + -1.0f))) + (fSlow12 * (std::min<float>(1.0f, fRec5[0]) * ((2.0f * fRec8) + -1.0f)))) + (fSlow18 * (std::min<float>(1.0f, fRec9[0]) * ((2.0f * fRec12) + -1.0f)))) + (fSlow24 * (std::min<float>(1.0f, fRec13[0]) * ((2.0f * fRec16) + -1.0f)))) + (fSlow30 * (std::min<float>(1.0f, fRec17[0]) * ((2.0f * fRec20) + -1.0f)))) + (fSlow36 * (std::min<float>(1.0f, fRec21[0]) * ((2.0f * fRec24) + -1.0f)))));
			fRec25[0] = (fSlow42 + (0.999000013f * fRec25[1]));
			float fTemp31 = (0.199722961f * fRec25[0]);
			float fTemp32 = ((fConst4 * (fConst4 - fTemp31)) + 1.0f);
			float fTemp33 = ((fConst4 * (fConst4 + fTemp31)) + 1.0f);
			fRec0[0] = (fTemp30 - (((fRec0[2] * fTemp32) + (fConst5 * fRec0[1])) / fTemp33));
			float fTemp34 = float(input0[i]);
			fRec32[0] = ((fConst6 * fRec32[1]) + (fConst7 * std::fabs(fTemp34)));
			float fRec31 = fRec32[0];
			fRec33[0] = (fSlow43 + (0.999000013f * fRec33[1]));
			int iTemp35 = (fRec31 > exp10f((0.0500000007f * ((20.0f * fRec33[0]) + -40.0f))));
			iVec0[0] = iTemp35;
			iRec34[0] = std::max<int>(int((iConst8 * (iTemp35 < iVec0[1]))), int((iRec34[1] + -1)));
			fRec30[0] = ((fConst6 * fRec30[1]) + (fConst7 * std::fabs(std::max<float>(float(iTemp35), float((iRec34[0] > 0))))));
			float fRec29 = fRec30[0];
			float fTemp36 = (fRec29 * fTemp34);
			fRec28[0] = (fTemp36 - (((fTemp32 * fRec28[2]) + (fConst5 * fRec28[1])) / fTemp33));
			float fTemp37 = std::fabs(((fConst4 * (fRec28[0] / fTemp33)) + (fRec28[2] * (0.0f - (fConst4 / fTemp33)))));
			fRec35[0] = (fSlow44 + (0.999000013f * fRec35[1]));
			float fTemp38 = std::exp((0.0f - (fConst2 / fRec35[0])));
			fRec36[0] = (fSlow45 + (0.999000013f * fRec36[1]));
			float fTemp39 = std::exp((0.0f - (fConst2 / fRec36[0])));
			float fTemp40 = ((fRec26[1] > fTemp37)?fTemp39:fTemp38);
			fRec27[0] = ((fRec27[1] * fTemp40) + (fTemp37 * (1.0f - fTemp40)));
			fRec26[0] = fRec27[0];
			float fTemp41 = (0.199722961f * fRec25[0]);
			float fTemp42 = ((fConst10 * (fConst10 - fTemp41)) + 1.0f);
			float fTemp43 = ((fConst10 * (fConst10 + fTemp41)) + 1.0f);
			fRec37[0] = (fTemp30 - (((fRec37[2] * fTemp42) + (fConst11 * fRec37[1])) / fTemp43));
			fRec40[0] = (fTemp36 - (((fTemp42 * fRec40[2]) + (fConst11 * fRec40[1])) / fTemp43));
			float fTemp44 = std::fabs(((fConst10 * (fRec40[0] / fTemp43)) + (fRec40[2] * (0.0f - (fConst10 / fTemp43)))));
			float fTemp45 = ((fRec38[1] > fTemp44)?fTemp39:fTemp38);
			fRec39[0] = ((fRec39[1] * fTemp45) + (fTemp44 * (1.0f - fTemp45)));
			fRec38[0] = fRec39[0];
			float fTemp46 = (0.199722961f * fRec25[0]);
			float fTemp47 = ((fConst13 * (fConst13 - fTemp46)) + 1.0f);
			float fTemp48 = ((fConst13 * (fConst13 + fTemp46)) + 1.0f);
			fRec41[0] = (fTemp30 - (((fRec41[2] * fTemp47) + (fConst14 * fRec41[1])) / fTemp48));
			fRec44[0] = (fTemp36 - (((fTemp47 * fRec44[2]) + (fConst14 * fRec44[1])) / fTemp48));
			float fTemp49 = std::fabs(((fConst13 * (fRec44[0] / fTemp48)) + (fRec44[2] * (0.0f - (fConst13 / fTemp48)))));
			float fTemp50 = ((fRec42[1] > fTemp49)?fTemp39:fTemp38);
			fRec43[0] = ((fRec43[1] * fTemp50) + (fTemp49 * (1.0f - fTemp50)));
			fRec42[0] = fRec43[0];
			float fTemp51 = ((fConst16 * (fConst16 - fTemp41)) + 1.0f);
			float fTemp52 = ((fConst16 * (fConst16 + fTemp41)) + 1.0f);
			fRec45[0] = (fTemp30 - (((fRec45[2] * fTemp51) + (fConst17 * fRec45[1])) / fTemp52));
			fRec48[0] = (fTemp36 - (((fTemp51 * fRec48[2]) + (fConst17 * fRec48[1])) / fTemp52));
			float fTemp53 = std::fabs(((fConst16 * (fRec48[0] / fTemp52)) + (fRec48[2] * (0.0f - (fConst16 / fTemp52)))));
			float fTemp54 = ((fRec46[1] > fTemp53)?fTemp39:fTemp38);
			fRec47[0] = ((fRec47[1] * fTemp54) + (fTemp53 * (1.0f - fTemp54)));
			fRec46[0] = fRec47[0];
			float fTemp55 = (0.199722961f * fRec25[0]);
			float fTemp56 = ((fConst19 * (fConst19 - fTemp55)) + 1.0f);
			float fTemp57 = ((fConst19 * (fConst19 + fTemp55)) + 1.0f);
			fRec49[0] = (fTemp30 - (((fRec49[2] * fTemp56) + (fConst20 * fRec49[1])) / fTemp57));
			fRec52[0] = (fTemp36 - (((fTemp56 * fRec52[2]) + (fConst20 * fRec52[1])) / fTemp57));
			float fTemp58 = std::fabs(((fConst19 * (fRec52[0] / fTemp57)) + (fRec52[2] * (0.0f - (fConst19 / fTemp57)))));
			float fTemp59 = ((fRec50[1] > fTemp58)?fTemp39:fTemp38);
			fRec51[0] = ((fRec51[1] * fTemp59) + (fTemp58 * (1.0f - fTemp59)));
			fRec50[0] = fRec51[0];
			float fTemp60 = ((fConst22 * (fConst22 - fTemp46)) + 1.0f);
			float fTemp61 = ((fConst22 * (fConst22 + fTemp46)) + 1.0f);
			fRec53[0] = (fTemp30 - (((fRec53[2] * fTemp60) + (fConst23 * fRec53[1])) / fTemp61));
			fRec56[0] = (fTemp36 - (((fTemp60 * fRec56[2]) + (fConst23 * fRec56[1])) / fTemp61));
			float fTemp62 = std::fabs(((fConst22 * (fRec56[0] / fTemp61)) + (fRec56[2] * (0.0f - (fConst22 / fTemp61)))));
			float fTemp63 = ((fRec54[1] > fTemp62)?fTemp39:fTemp38);
			fRec55[0] = ((fRec55[1] * fTemp63) + (fTemp62 * (1.0f - fTemp63)));
			fRec54[0] = fRec55[0];
			float fTemp64 = ((fConst25 * (fConst25 - fTemp41)) + 1.0f);
			float fTemp65 = ((fConst25 * (fConst25 + fTemp41)) + 1.0f);
			fRec57[0] = (fTemp30 - (((fRec57[2] * fTemp64) + (fConst26 * fRec57[1])) / fTemp65));
			fRec60[0] = (fTemp36 - (((fTemp64 * fRec60[2]) + (fConst26 * fRec60[1])) / fTemp65));
			float fTemp66 = std::fabs(((fConst25 * (fRec60[0] / fTemp65)) + (fRec60[2] * (0.0f - (fConst25 / fTemp65)))));
			float fTemp67 = ((fRec58[1] > fTemp66)?fTemp39:fTemp38);
			fRec59[0] = ((fRec59[1] * fTemp67) + (fTemp66 * (1.0f - fTemp67)));
			fRec58[0] = fRec59[0];
			float fTemp68 = (0.199722961f * fRec25[0]);
			float fTemp69 = ((fConst28 * (fConst28 - fTemp68)) + 1.0f);
			float fTemp70 = ((fConst28 * (fConst28 + fTemp68)) + 1.0f);
			fRec61[0] = (fTemp30 - (((fRec61[2] * fTemp69) + (fConst29 * fRec61[1])) / fTemp70));
			fRec64[0] = (fTemp36 - (((fTemp69 * fRec64[2]) + (fConst29 * fRec64[1])) / fTemp70));
			float fTemp71 = std::fabs(((fConst28 * (fRec64[0] / fTemp70)) + (fRec64[2] * (0.0f - (fConst28 / fTemp70)))));
			float fTemp72 = ((fRec62[1] > fTemp71)?fTemp39:fTemp38);
			fRec63[0] = ((fRec63[1] * fTemp72) + (fTemp71 * (1.0f - fTemp72)));
			fRec62[0] = fRec63[0];
			float fTemp73 = ((fConst31 * (fConst31 - fTemp31)) + 1.0f);
			float fTemp74 = ((fConst31 * (fConst31 + fTemp31)) + 1.0f);
			fRec65[0] = (fTemp30 - (((fRec65[2] * fTemp73) + (fConst32 * fRec65[1])) / fTemp74));
			fRec68[0] = (fTemp36 - (((fTemp73 * fRec68[2]) + (fConst32 * fRec68[1])) / fTemp74));
			float fTemp75 = std::fabs(((fConst31 * (fRec68[0] / fTemp74)) + (fRec68[2] * (0.0f - (fConst31 / fTemp74)))));
			float fTemp76 = ((fRec66[1] > fTemp75)?fTemp39:fTemp38);
			fRec67[0] = ((fRec67[1] * fTemp76) + (fTemp75 * (1.0f - fTemp76)));
			fRec66[0] = fRec67[0];
			float fTemp77 = (0.199722961f * fRec25[0]);
			float fTemp78 = ((fConst34 * (fConst34 - fTemp77)) + 1.0f);
			float fTemp79 = ((fConst34 * (fConst34 + fTemp77)) + 1.0f);
			fRec69[0] = (fTemp30 - (((fRec69[2] * fTemp78) + (fConst35 * fRec69[1])) / fTemp79));
			fRec72[0] = (fTemp36 - (((fTemp78 * fRec72[2]) + (fConst35 * fRec72[1])) / fTemp79));
			float fTemp80 = std::fabs(((fConst34 * (fRec72[0] / fTemp79)) + (fRec72[2] * (0.0f - (fConst34 / fTemp79)))));
			float fTemp81 = ((fRec70[1] > fTemp80)?fTemp39:fTemp38);
			fRec71[0] = ((fRec71[1] * fTemp81) + (fTemp80 * (1.0f - fTemp81)));
			fRec70[0] = fRec71[0];
			float fTemp82 = ((fConst37 * (fConst37 - fTemp68)) + 1.0f);
			float fTemp83 = ((fConst37 * (fConst37 + fTemp68)) + 1.0f);
			fRec73[0] = (fTemp30 - (((fRec73[2] * fTemp82) + (fConst38 * fRec73[1])) / fTemp83));
			fRec76[0] = (fTemp36 - (((fTemp82 * fRec76[2]) + (fConst38 * fRec76[1])) / fTemp83));
			float fTemp84 = std::fabs(((fConst37 * (fRec76[0] / fTemp83)) + (fRec76[2] * (0.0f - (fConst37 / fTemp83)))));
			float fTemp85 = ((fRec74[1] > fTemp84)?fTemp39:fTemp38);
			fRec75[0] = ((fRec75[1] * fTemp85) + (fTemp84 * (1.0f - fTemp85)));
			fRec74[0] = fRec75[0];
			float fTemp86 = ((fConst40 * (fConst40 - fTemp31)) + 1.0f);
			float fTemp87 = ((fConst40 * (fConst40 + fTemp31)) + 1.0f);
			fRec77[0] = (fTemp30 - (((fRec77[2] * fTemp86) + (fConst41 * fRec77[1])) / fTemp87));
			fRec80[0] = (fTemp36 - (((fTemp86 * fRec80[2]) + (fConst41 * fRec80[1])) / fTemp87));
			float fTemp88 = std::fabs(((fConst40 * (fRec80[0] / fTemp87)) + (fRec80[2] * (0.0f - (fConst40 / fTemp87)))));
			float fTemp89 = ((fRec78[1] > fTemp88)?fTemp39:fTemp38);
			fRec79[0] = ((fRec79[1] * fTemp89) + (fTemp88 * (1.0f - fTemp89)));
			fRec78[0] = fRec79[0];
			float fTemp90 = ((fConst43 * (fConst43 - fTemp46)) + 1.0f);
			float fTemp91 = ((fConst43 * (fConst43 + fTemp46)) + 1.0f);
			fRec81[0] = (fTemp30 - (((fRec81[2] * fTemp90) + (fConst44 * fRec81[1])) / fTemp91));
			fRec84[0] = (fTemp36 - (((fTemp90 * fRec84[2]) + (fConst44 * fRec84[1])) / fTemp91));
			float fTemp92 = std::fabs(((fConst43 * (fRec84[0] / fTemp91)) + (fRec84[2] * (0.0f - (fConst43 / fTemp91)))));
			float fTemp93 = ((fRec82[1] > fTemp92)?fTemp39:fTemp38);
			fRec83[0] = ((fRec83[1] * fTemp93) + (fTemp92 * (1.0f - fTemp93)));
			fRec82[0] = fRec83[0];
			float fTemp94 = (0.199722961f * fRec25[0]);
			float fTemp95 = ((fConst46 * (fConst46 - fTemp94)) + 1.0f);
			float fTemp96 = ((fConst46 * (fConst46 + fTemp94)) + 1.0f);
			fRec85[0] = (fTemp30 - (((fRec85[2] * fTemp95) + (fConst47 * fRec85[1])) / fTemp96));
			fRec88[0] = (fTemp36 - (((fTemp95 * fRec88[2]) + (fConst47 * fRec88[1])) / fTemp96));
			float fTemp97 = std::fabs(((fConst46 * (fRec88[0] / fTemp96)) + (fRec88[2] * (0.0f - (fConst46 / fTemp96)))));
			float fTemp98 = ((fRec86[1] > fTemp97)?fTemp39:fTemp38);
			fRec87[0] = ((fRec87[1] * fTemp98) + (fTemp97 * (1.0f - fTemp98)));
			fRec86[0] = fRec87[0];
			float fTemp99 = (0.199722961f * fRec25[0]);
			float fTemp100 = ((fConst49 * (fConst49 - fTemp99)) + 1.0f);
			float fTemp101 = ((fConst49 * (fConst49 + fTemp99)) + 1.0f);
			fRec89[0] = (fTemp30 - (((fRec89[2] * fTemp100) + (fConst50 * fRec89[1])) / fTemp101));
			fRec92[0] = (fTemp36 - (((fTemp100 * fRec92[2]) + (fConst50 * fRec92[1])) / fTemp101));
			float fTemp102 = std::fabs(((fConst49 * (fRec92[0] / fTemp101)) + (fRec92[2] * (0.0f - (fConst49 / fTemp101)))));
			float fTemp103 = ((fRec90[1] > fTemp102)?fTemp39:fTemp38);
			fRec91[0] = ((fRec91[1] * fTemp103) + (fTemp102 * (1.0f - fTemp103)));
			fRec90[0] = fRec91[0];
			float fTemp104 = ((fConst52 * (fConst52 - fTemp99)) + 1.0f);
			float fTemp105 = ((fConst52 * (fConst52 + fTemp99)) + 1.0f);
			fRec93[0] = (fTemp30 - (((fRec93[2] * fTemp104) + (fConst53 * fRec93[1])) / fTemp105));
			fRec96[0] = (fTemp36 - (((fTemp104 * fRec96[2]) + (fConst53 * fRec96[1])) / fTemp105));
			float fTemp106 = std::fabs(((fConst52 * (fRec96[0] / fTemp105)) + (fRec96[2] * (0.0f - (fConst52 / fTemp105)))));
			float fTemp107 = ((fRec94[1] > fTemp106)?fTemp39:fTemp38);
			fRec95[0] = ((fRec95[1] * fTemp107) + (fTemp106 * (1.0f - fTemp107)));
			fRec94[0] = fRec95[0];
			float fTemp108 = ((fConst55 * (fConst55 - fTemp31)) + 1.0f);
			float fTemp109 = ((fConst55 * (fConst55 + fTemp31)) + 1.0f);
			fRec97[0] = (fTemp30 - (((fRec97[2] * fTemp108) + (fConst56 * fRec97[1])) / fTemp109));
			fRec100[0] = (fTemp36 - (((fTemp108 * fRec100[2]) + (fConst56 * fRec100[1])) / fTemp109));
			float fTemp110 = std::fabs(((fConst55 * (fRec100[0] / fTemp109)) + (fRec100[2] * (0.0f - (fConst55 / fTemp109)))));
			float fTemp111 = ((fRec98[1] > fTemp110)?fTemp39:fTemp38);
			fRec99[0] = ((fRec99[1] * fTemp111) + (fTemp110 * (1.0f - fTemp111)));
			fRec98[0] = fRec99[0];
			float fTemp112 = (0.199722961f * fRec25[0]);
			float fTemp113 = ((fConst58 * (fConst58 - fTemp112)) + 1.0f);
			float fTemp114 = ((fConst58 * (fConst58 + fTemp112)) + 1.0f);
			fRec101[0] = (fTemp30 - (((fRec101[2] * fTemp113) + (fConst59 * fRec101[1])) / fTemp114));
			fRec104[0] = (fTemp36 - (((fTemp113 * fRec104[2]) + (fConst59 * fRec104[1])) / fTemp114));
			float fTemp115 = std::fabs(((fConst58 * (fRec104[0] / fTemp114)) + (fRec104[2] * (0.0f - (fConst58 / fTemp114)))));
			float fTemp116 = ((fRec102[1] > fTemp115)?fTemp39:fTemp38);
			fRec103[0] = ((fRec103[1] * fTemp116) + (fTemp115 * (1.0f - fTemp116)));
			fRec102[0] = fRec103[0];
			float fTemp117 = ((fConst61 * (fConst61 - fTemp99)) + 1.0f);
			float fTemp118 = ((fConst61 * (fConst61 + fTemp99)) + 1.0f);
			fRec105[0] = (fTemp30 - (((fRec105[2] * fTemp117) + (fConst62 * fRec105[1])) / fTemp118));
			fRec108[0] = (fTemp36 - (((fTemp117 * fRec108[2]) + (fConst62 * fRec108[1])) / fTemp118));
			float fTemp119 = std::fabs(((fConst61 * (fRec108[0] / fTemp118)) + (fRec108[2] * (0.0f - (fConst61 / fTemp118)))));
			float fTemp120 = ((fRec106[1] > fTemp119)?fTemp39:fTemp38);
			fRec107[0] = ((fRec107[1] * fTemp120) + (fTemp119 * (1.0f - fTemp120)));
			fRec106[0] = fRec107[0];
			float fTemp121 = ((fConst64 * (fConst64 - fTemp112)) + 1.0f);
			float fTemp122 = ((fConst64 * (fConst64 + fTemp112)) + 1.0f);
			fRec109[0] = (fTemp30 - (((fRec109[2] * fTemp121) + (fConst65 * fRec109[1])) / fTemp122));
			fRec112[0] = (fTemp36 - (((fTemp121 * fRec112[2]) + (fConst65 * fRec112[1])) / fTemp122));
			float fTemp123 = std::fabs(((fConst64 * (fRec112[0] / fTemp122)) + (fRec112[2] * (0.0f - (fConst64 / fTemp122)))));
			float fTemp124 = ((fRec110[1] > fTemp123)?fTemp39:fTemp38);
			fRec111[0] = ((fRec111[1] * fTemp124) + (fTemp123 * (1.0f - fTemp124)));
			fRec110[0] = fRec111[0];
			float fTemp125 = (0.199722961f * fRec25[0]);
			float fTemp126 = ((fConst67 * (fConst67 - fTemp125)) + 1.0f);
			float fTemp127 = ((fConst67 * (fConst67 + fTemp125)) + 1.0f);
			fRec113[0] = (fTemp30 - (((fRec113[2] * fTemp126) + (fConst68 * fRec113[1])) / fTemp127));
			fRec116[0] = (fTemp36 - (((fTemp126 * fRec116[2]) + (fConst68 * fRec116[1])) / fTemp127));
			float fTemp128 = std::fabs(((fConst67 * (fRec116[0] / fTemp127)) + (fRec116[2] * (0.0f - (fConst67 / fTemp127)))));
			float fTemp129 = ((fRec114[1] > fTemp128)?fTemp39:fTemp38);
			fRec115[0] = ((fRec115[1] * fTemp129) + (fTemp128 * (1.0f - fTemp129)));
			fRec114[0] = fRec115[0];
			float fTemp130 = ((fConst70 * (fConst70 - fTemp46)) + 1.0f);
			float fTemp131 = ((fConst70 * (fConst70 + fTemp46)) + 1.0f);
			fRec117[0] = (fTemp30 - (((fRec117[2] * fTemp130) + (fConst71 * fRec117[1])) / fTemp131));
			fRec120[0] = (fTemp36 - (((fTemp130 * fRec120[2]) + (fConst71 * fRec120[1])) / fTemp131));
			float fTemp132 = std::fabs(((fConst70 * (fRec120[0] / fTemp131)) + (fRec120[2] * (0.0f - (fConst70 / fTemp131)))));
			float fTemp133 = ((fRec118[1] > fTemp132)?fTemp39:fTemp38);
			fRec119[0] = ((fRec119[1] * fTemp133) + (fTemp132 * (1.0f - fTemp133)));
			fRec118[0] = fRec119[0];
			float fTemp134 = (0.199722961f * fRec25[0]);
			float fTemp135 = ((fConst73 * (fConst73 - fTemp134)) + 1.0f);
			float fTemp136 = ((fConst73 * (fConst73 + fTemp134)) + 1.0f);
			fRec121[0] = (fTemp30 - (((fRec121[2] * fTemp135) + (fConst74 * fRec121[1])) / fTemp136));
			fRec124[0] = (fTemp36 - (((fTemp135 * fRec124[2]) + (fConst74 * fRec124[1])) / fTemp136));
			float fTemp137 = std::fabs(((fConst73 * (fRec124[0] / fTemp136)) + (fRec124[2] * (0.0f - (fConst73 / fTemp136)))));
			float fTemp138 = ((fRec122[1] > fTemp137)?fTemp39:fTemp38);
			fRec123[0] = ((fRec123[1] * fTemp138) + (fTemp137 * (1.0f - fTemp138)));
			fRec122[0] = fRec123[0];
			float fTemp139 = ((fConst76 * (fConst76 - fTemp134)) + 1.0f);
			float fTemp140 = ((fConst76 * (fConst76 + fTemp134)) + 1.0f);
			fRec125[0] = (fTemp30 - (((fRec125[2] * fTemp139) + (fConst77 * fRec125[1])) / fTemp140));
			fRec128[0] = (fTemp36 - (((fTemp139 * fRec128[2]) + (fConst77 * fRec128[1])) / fTemp140));
			float fTemp141 = std::fabs(((fConst76 * (fRec128[0] / fTemp140)) + (fRec128[2] * (0.0f - (fConst76 / fTemp140)))));
			float fTemp142 = ((fRec126[1] > fTemp141)?fTemp39:fTemp38);
			fRec127[0] = ((fRec127[1] * fTemp142) + (fTemp141 * (1.0f - fTemp142)));
			fRec126[0] = fRec127[0];
			float fTemp143 = ((fConst79 * (fConst79 - fTemp125)) + 1.0f);
			float fTemp144 = ((fConst79 * (fConst79 + fTemp125)) + 1.0f);
			fRec129[0] = (fTemp30 - (((fRec129[2] * fTemp143) + (fConst80 * fRec129[1])) / fTemp144));
			fRec132[0] = (fTemp36 - (((fTemp143 * fRec132[2]) + (fConst80 * fRec132[1])) / fTemp144));
			float fTemp145 = std::fabs(((fConst79 * (fRec132[0] / fTemp144)) + (fRec132[2] * (0.0f - (fConst79 / fTemp144)))));
			float fTemp146 = ((fRec130[1] > fTemp145)?fTemp39:fTemp38);
			fRec131[0] = ((fRec131[1] * fTemp146) + (fTemp145 * (1.0f - fTemp146)));
			fRec130[0] = fRec131[0];
			float fTemp147 = ((fConst82 * (fConst82 - fTemp125)) + 1.0f);
			float fTemp148 = ((fConst82 * (fConst82 + fTemp125)) + 1.0f);
			fRec133[0] = (fTemp30 - (((fRec133[2] * fTemp147) + (fConst83 * fRec133[1])) / fTemp148));
			fRec136[0] = (fTemp36 - (((fTemp147 * fRec136[2]) + (fConst83 * fRec136[1])) / fTemp148));
			float fTemp149 = std::fabs(((fConst82 * (fRec136[0] / fTemp148)) + (fRec136[2] * (0.0f - (fConst82 / fTemp148)))));
			float fTemp150 = ((fRec134[1] > fTemp149)?fTemp39:fTemp38);
			fRec135[0] = ((fRec135[1] * fTemp150) + (fTemp149 * (1.0f - fTemp150)));
			fRec134[0] = fRec135[0];
			float fTemp151 = (0.199722961f * fRec25[0]);
			float fTemp152 = ((fConst85 * (fConst85 - fTemp151)) + 1.0f);
			float fTemp153 = ((fConst85 * (fConst85 + fTemp151)) + 1.0f);
			fRec137[0] = (fTemp30 - (((fRec137[2] * fTemp152) + (fConst86 * fRec137[1])) / fTemp153));
			fRec140[0] = (fTemp36 - (((fTemp152 * fRec140[2]) + (fConst86 * fRec140[1])) / fTemp153));
			float fTemp154 = std::fabs(((fConst85 * (fRec140[0] / fTemp153)) + (fRec140[2] * (0.0f - (fConst85 / fTemp153)))));
			float fTemp155 = ((fRec138[1] > fTemp154)?fTemp39:fTemp38);
			fRec139[0] = ((fRec139[1] * fTemp155) + (fTemp154 * (1.0f - fTemp155)));
			fRec138[0] = fRec139[0];
			float fTemp156 = ((fConst88 * (fConst88 - fTemp99)) + 1.0f);
			float fTemp157 = ((fConst88 * (fConst88 + fTemp99)) + 1.0f);
			fRec141[0] = (fTemp30 - (((fRec141[2] * fTemp156) + (fConst89 * fRec141[1])) / fTemp157));
			fRec144[0] = (fTemp36 - (((fTemp156 * fRec144[2]) + (fConst89 * fRec144[1])) / fTemp157));
			float fTemp158 = std::fabs(((fConst88 * (fRec144[0] / fTemp157)) + (fRec144[2] * (0.0f - (fConst88 / fTemp157)))));
			float fTemp159 = ((fRec142[1] > fTemp158)?fTemp39:fTemp38);
			fRec143[0] = ((fRec143[1] * fTemp159) + (fTemp158 * (1.0f - fTemp159)));
			fRec142[0] = fRec143[0];
			output0[i] = FAUSTFLOAT(((fRec0[2] * (0.0f - (fConst4 * (fRec26[0] / fTemp33)))) + (((fRec37[2] * (0.0f - (fConst10 * (fRec38[0] / fTemp43)))) + (((fRec41[2] * (0.0f - (fConst13 * (fRec42[0] / fTemp48)))) + (((fRec45[2] * (0.0f - (fConst16 * (fRec46[0] / fTemp52)))) + (((fRec49[2] * (0.0f - (fConst19 * (fRec50[0] / fTemp57)))) + (((fRec53[2] * (0.0f - (fConst22 * (fRec54[0] / fTemp61)))) + (((fRec57[2] * (0.0f - (fConst25 * (fRec58[0] / fTemp65)))) + (((fRec61[2] * (0.0f - (fConst28 * (fRec62[0] / fTemp70)))) + (((fRec65[2] * (0.0f - (fConst31 * (fRec66[0] / fTemp74)))) + (((fRec69[2] * (0.0f - (fConst34 * (fRec70[0] / fTemp79)))) + (((fRec73[2] * (0.0f - (fConst37 * (fRec74[0] / fTemp83)))) + (((fRec77[2] * (0.0f - (fConst40 * (fRec78[0] / fTemp87)))) + (((fRec81[2] * (0.0f - (fConst43 * (fRec82[0] / fTemp91)))) + (((fRec85[2] * (0.0f - (fConst46 * (fRec86[0] / fTemp96)))) + (((fRec89[2] * (0.0f - (fConst49 * (fRec90[0] / fTemp101)))) + (((fRec93[2] * (0.0f - (fConst52 * (fRec94[0] / fTemp105)))) + (((fRec97[2] * (0.0f - (fConst55 * (fRec98[0] / fTemp109)))) + (((fRec101[2] * (0.0f - (fConst58 * (fRec102[0] / fTemp114)))) + (((fRec105[2] * (0.0f - (fConst61 * (fRec106[0] / fTemp118)))) + (((fRec109[2] * (0.0f - (fConst64 * (fRec110[0] / fTemp122)))) + (((fRec113[2] * (0.0f - (fConst67 * (fRec114[0] / fTemp127)))) + (((fRec117[2] * (0.0f - (fConst70 * (fRec118[0] / fTemp131)))) + (((fRec121[2] * (0.0f - (fConst73 * (fRec122[0] / fTemp136)))) + (((fRec125[2] * (0.0f - (fConst76 * (fRec126[0] / fTemp140)))) + (((fRec129[2] * (0.0f - (fConst79 * (fRec130[0] / fTemp144)))) + (((fRec133[2] * (0.0f - (fConst82 * (fRec134[0] / fTemp148)))) + (((fRec137[2] * (0.0f - (fConst85 * (fRec138[0] / fTemp153)))) + (((fConst88 * ((fRec141[0] * fRec142[0]) / fTemp157)) + (fRec141[2] * (0.0f - (fConst88 * (fRec142[0] / fTemp157))))) + (fConst85 * ((fRec137[0] * fRec138[0]) / fTemp153)))) + (fConst82 * ((fRec133[0] * fRec134[0]) / fTemp148)))) + (fConst79 * ((fRec129[0] * fRec130[0]) / fTemp144)))) + (fConst76 * ((fRec125[0] * fRec126[0]) / fTemp140)))) + (fConst73 * ((fRec121[0] * fRec122[0]) / fTemp136)))) + (fConst70 * ((fRec117[0] * fRec118[0]) / fTemp131)))) + (fConst67 * ((fRec113[0] * fRec114[0]) / fTemp127)))) + (fConst64 * ((fRec109[0] * fRec110[0]) / fTemp122)))) + (fConst61 * ((fRec105[0] * fRec106[0]) / fTemp118)))) + (fConst58 * ((fRec101[0] * fRec102[0]) / fTemp114)))) + (fConst55 * ((fRec97[0] * fRec98[0]) / fTemp109)))) + (fConst52 * ((fRec93[0] * fRec94[0]) / fTemp105)))) + (fConst49 * ((fRec89[0] * fRec90[0]) / fTemp101)))) + (fConst46 * ((fRec85[0] * fRec86[0]) / fTemp96)))) + (fConst43 * ((fRec81[0] * fRec82[0]) / fTemp91)))) + (fConst40 * ((fRec77[0] * fRec78[0]) / fTemp87)))) + (fConst37 * ((fRec73[0] * fRec74[0]) / fTemp83)))) + (fConst34 * ((fRec69[0] * fRec70[0]) / fTemp79)))) + (fConst31 * ((fRec65[0] * fRec66[0]) / fTemp74)))) + (fConst28 * ((fRec61[0] * fRec62[0]) / fTemp70)))) + (fConst25 * ((fRec57[0] * fRec58[0]) / fTemp65)))) + (fConst22 * ((fRec53[0] * fRec54[0]) / fTemp61)))) + (fConst19 * ((fRec49[0] * fRec50[0]) / fTemp57)))) + (fConst16 * ((fRec45[0] * fRec46[0]) / fTemp52)))) + (fConst13 * ((fRec41[0] * fRec42[0]) / fTemp48)))) + (fConst10 * ((fRec37[0] * fRec38[0]) / fTemp43)))) + (fConst4 * ((fRec0[0] * fRec26[0]) / fTemp33)))));
			iRec2[1] = iRec2[0];
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			iRec6[1] = iRec6[0];
			fRec5[1] = fRec5[0];
			fRec7[1] = fRec7[0];
			iRec10[1] = iRec10[0];
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			iRec14[1] = iRec14[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			iRec18[1] = iRec18[0];
			fRec17[1] = fRec17[0];
			fRec19[1] = fRec19[0];
			iRec22[1] = iRec22[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			iVec0[1] = iVec0[0];
			iRec34[1] = iRec34[0];
			fRec30[1] = fRec30[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec35[1] = fRec35[0];
			fRec36[1] = fRec36[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[1] = fRec55[0];
			fRec54[1] = fRec54[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[1] = fRec59[0];
			fRec58[1] = fRec58[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[1] = fRec63[0];
			fRec62[1] = fRec62[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[1] = fRec67[0];
			fRec66[1] = fRec66[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[1] = fRec71[0];
			fRec70[1] = fRec70[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[1] = fRec75[0];
			fRec74[1] = fRec74[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fRec79[1] = fRec79[0];
			fRec78[1] = fRec78[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec83[1] = fRec83[0];
			fRec82[1] = fRec82[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec88[2] = fRec88[1];
			fRec88[1] = fRec88[0];
			fRec87[1] = fRec87[0];
			fRec86[1] = fRec86[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec91[1] = fRec91[0];
			fRec90[1] = fRec90[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[1] = fRec95[0];
			fRec94[1] = fRec94[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec100[2] = fRec100[1];
			fRec100[1] = fRec100[0];
			fRec99[1] = fRec99[0];
			fRec98[1] = fRec98[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
			fRec103[1] = fRec103[0];
			fRec102[1] = fRec102[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec108[2] = fRec108[1];
			fRec108[1] = fRec108[0];
			fRec107[1] = fRec107[0];
			fRec106[1] = fRec106[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec111[1] = fRec111[0];
			fRec110[1] = fRec110[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec116[2] = fRec116[1];
			fRec116[1] = fRec116[0];
			fRec115[1] = fRec115[0];
			fRec114[1] = fRec114[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec120[2] = fRec120[1];
			fRec120[1] = fRec120[0];
			fRec119[1] = fRec119[0];
			fRec118[1] = fRec118[0];
			fRec121[2] = fRec121[1];
			fRec121[1] = fRec121[0];
			fRec124[2] = fRec124[1];
			fRec124[1] = fRec124[0];
			fRec123[1] = fRec123[0];
			fRec122[1] = fRec122[0];
			fRec125[2] = fRec125[1];
			fRec125[1] = fRec125[0];
			fRec128[2] = fRec128[1];
			fRec128[1] = fRec128[0];
			fRec127[1] = fRec127[0];
			fRec126[1] = fRec126[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fRec132[2] = fRec132[1];
			fRec132[1] = fRec132[0];
			fRec131[1] = fRec131[0];
			fRec130[1] = fRec130[0];
			fRec133[2] = fRec133[1];
			fRec133[1] = fRec133[0];
			fRec136[2] = fRec136[1];
			fRec136[1] = fRec136[0];
			fRec135[1] = fRec135[0];
			fRec134[1] = fRec134[0];
			fRec137[2] = fRec137[1];
			fRec137[1] = fRec137[0];
			fRec140[2] = fRec140[1];
			fRec140[1] = fRec140[0];
			fRec139[1] = fRec139[0];
			fRec138[1] = fRec138[0];
			fRec141[2] = fRec141[1];
			fRec141[1] = fRec141[0];
			fRec144[2] = fRec144[1];
			fRec144[1] = fRec144[0];
			fRec143[1] = fRec143[0];
			fRec142[1] = fRec142[0];
			
		}
		
	}

	
};

#endif
