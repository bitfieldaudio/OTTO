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
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider0;
	float fConst6;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider1;
	int iRec2[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fRec1[2];
	float fConst7;
	FAUSTFLOAT fHslider5;
	float fRec3[2];
	FAUSTFLOAT fHslider6;
	float fRec5[2];
	int iRec6[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fButton1;
	int iRec8[2];
	float fRec7[2];
	FAUSTFLOAT fHslider8;
	float fRec9[2];
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT fButton2;
	int iRec12[2];
	float fRec11[2];
	FAUSTFLOAT fHslider10;
	float fRec13[2];
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fButton3;
	int iRec16[2];
	float fRec15[2];
	FAUSTFLOAT fHslider12;
	float fRec17[2];
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fButton4;
	int iRec20[2];
	float fRec19[2];
	FAUSTFLOAT fHslider14;
	float fRec21[2];
	FAUSTFLOAT fHslider15;
	FAUSTFLOAT fButton5;
	int iRec24[2];
	float fRec23[2];
	FAUSTFLOAT fHslider16;
	float fRec25[2];
	float fConst8;
	float fConst9;
	float fConst10;
	float fRec0[3];
	float fConst11;
	float fRec28[3];
	float fConst12;
	float fConst13;
	float fConst14;
	float fRec27[2];
	float fRec32[2];
	FAUSTFLOAT fHslider17;
	float fRec33[2];
	int iVec0[2];
	int iConst15;
	int iRec34[2];
	float fRec30[2];
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
	float fRec35[3];
	float fConst24;
	float fRec37[3];
	float fConst25;
	float fRec36[2];
	float fRec41[2];
	int iVec1[2];
	int iRec42[2];
	float fRec39[2];
	float fConst26;
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fRec43[3];
	float fConst34;
	float fRec45[3];
	float fConst35;
	float fRec44[2];
	float fRec49[2];
	int iVec2[2];
	int iRec50[2];
	float fRec47[2];
	float fConst36;
	float fConst37;
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fRec51[3];
	float fConst44;
	float fRec53[3];
	float fConst45;
	float fRec52[2];
	float fRec57[2];
	int iVec3[2];
	int iRec58[2];
	float fRec55[2];
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec59[3];
	float fConst54;
	float fRec61[3];
	float fConst55;
	float fRec60[2];
	float fRec65[2];
	int iVec4[2];
	int iRec66[2];
	float fRec63[2];
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fConst63;
	float fRec67[3];
	float fConst64;
	float fRec69[3];
	float fConst65;
	float fRec68[2];
	float fRec73[2];
	int iVec5[2];
	int iRec74[2];
	float fRec71[2];
	float fConst66;
	float fConst67;
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fRec75[3];
	float fConst74;
	float fRec77[3];
	float fConst75;
	float fRec76[2];
	float fRec81[2];
	int iVec6[2];
	int iRec82[2];
	float fRec79[2];
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fConst80;
	float fConst81;
	float fConst82;
	float fRec83[3];
	float fRec85[3];
	float fConst83;
	float fRec84[2];
	float fRec89[2];
	int iVec7[2];
	int iRec90[2];
	float fRec87[2];
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fConst91;
	float fRec91[3];
	float fConst92;
	float fRec93[3];
	float fConst93;
	float fRec92[2];
	float fRec97[2];
	int iVec8[2];
	int iRec98[2];
	float fRec95[2];
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fConst99;
	float fConst100;
	float fConst101;
	float fRec99[3];
	float fConst102;
	float fRec101[3];
	float fConst103;
	float fRec100[2];
	float fRec105[2];
	int iVec9[2];
	int iRec106[2];
	float fRec103[2];
	float fConst104;
	float fConst105;
	float fConst106;
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fConst111;
	float fRec107[3];
	float fConst112;
	float fRec109[3];
	float fConst113;
	float fRec108[2];
	float fRec113[2];
	int iVec10[2];
	int iRec114[2];
	float fRec111[2];
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fConst120;
	float fRec115[3];
	float fRec117[3];
	float fConst121;
	float fRec116[2];
	float fRec121[2];
	int iVec11[2];
	int iRec122[2];
	float fRec119[2];
	float fConst122;
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec123[3];
	float fConst130;
	float fRec125[3];
	float fConst131;
	float fRec124[2];
	float fRec129[2];
	int iVec12[2];
	int iRec130[2];
	float fRec127[2];
	float fConst132;
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fConst139;
	float fRec131[3];
	float fConst140;
	float fRec133[3];
	float fConst141;
	float fRec132[2];
	float fRec137[2];
	int iVec13[2];
	int iRec138[2];
	float fRec135[2];
	float fConst142;
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec139[3];
	float fConst150;
	float fRec141[3];
	float fConst151;
	float fRec140[2];
	float fRec145[2];
	int iVec14[2];
	int iRec146[2];
	float fRec143[2];
	float fConst152;
	float fConst153;
	float fConst154;
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fConst159;
	float fRec147[3];
	float fConst160;
	float fRec149[3];
	float fConst161;
	float fRec148[2];
	float fRec153[2];
	int iVec15[2];
	int iRec154[2];
	float fRec151[2];
	FAUSTFLOAT fHslider18;
	float fRec155[2];
	
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
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
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
		fConst1 = std::tan((328.296417f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (((fConst2 + 0.231561884f) / fConst1) + 1.0f);
		fConst4 = (fConst3 * fConst1);
		fConst5 = (5.0f / fConst4);
		fConst6 = (6.90999985f / fConst0);
		fConst7 = (1.0f / fConst0);
		fConst8 = (1.0f / fConst3);
		fConst9 = (((fConst2 + -0.231561884f) / fConst1) + 1.0f);
		fConst10 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst1))));
		fConst11 = (1.0f / fConst4);
		fConst12 = (0.0f - fConst11);
		fConst13 = std::exp((0.0f - (100.0f / fConst0)));
		fConst14 = (1.0f - fConst13);
		iConst15 = int((9.99999975e-05f * fConst0));
		fConst16 = std::tan((563.915894f / fConst0));
		fConst17 = (1.0f / fConst16);
		fConst18 = (((fConst17 + 0.231561884f) / fConst16) + 1.0f);
		fConst19 = (fConst18 * fConst16);
		fConst20 = (5.0f / fConst19);
		fConst21 = (1.0f / fConst18);
		fConst22 = (((fConst17 + -0.231561884f) / fConst16) + 1.0f);
		fConst23 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst16))));
		fConst24 = (1.0f / fConst19);
		fConst25 = (0.0f - fConst24);
		fConst26 = std::tan((709.999939f / fConst0));
		fConst27 = (1.0f / fConst26);
		fConst28 = (((fConst27 + 0.231561884f) / fConst26) + 1.0f);
		fConst29 = (fConst28 * fConst26);
		fConst30 = (4.0f / fConst29);
		fConst31 = (1.0f / fConst28);
		fConst32 = (((fConst27 + -0.231561884f) / fConst26) + 1.0f);
		fConst33 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst26))));
		fConst34 = (1.0f / fConst29);
		fConst35 = (0.0f - fConst34);
		fConst36 = std::tan((893.783081f / fConst0));
		fConst37 = (1.0f / fConst36);
		fConst38 = (((fConst37 + 0.231561884f) / fConst36) + 1.0f);
		fConst39 = (fConst38 * fConst36);
		fConst40 = (1.5f / fConst39);
		fConst41 = (1.0f / fConst38);
		fConst42 = (((fConst37 + -0.231561884f) / fConst36) + 1.0f);
		fConst43 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst36))));
		fConst44 = (1.0f / fConst39);
		fConst45 = (0.0f - fConst44);
		fConst46 = std::tan((1126.26099f / fConst0));
		fConst47 = (1.0f / fConst46);
		fConst48 = (((fConst47 + 0.231561884f) / fConst46) + 1.0f);
		fConst49 = (fConst48 * fConst46);
		fConst50 = (1.39999998f / fConst49);
		fConst51 = (1.0f / fConst48);
		fConst52 = (((fConst47 + -0.231561884f) / fConst46) + 1.0f);
		fConst53 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst46))));
		fConst54 = (1.0f / fConst49);
		fConst55 = (0.0f - fConst54);
		fConst56 = std::tan((1419.99988f / fConst0));
		fConst57 = (1.0f / fConst56);
		fConst58 = (((fConst57 + 0.231561884f) / fConst56) + 1.0f);
		fConst59 = (fConst58 * fConst56);
		fConst60 = (1.29999995f / fConst59);
		fConst61 = (1.0f / fConst58);
		fConst62 = (((fConst57 + -0.231561884f) / fConst56) + 1.0f);
		fConst63 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst56))));
		fConst64 = (1.0f / fConst59);
		fConst65 = (0.0f - fConst64);
		fConst66 = std::tan((1789.13696f / fConst0));
		fConst67 = (1.0f / fConst66);
		fConst68 = (((fConst67 + 0.231561884f) / fConst66) + 1.0f);
		fConst69 = (fConst68 * fConst66);
		fConst70 = (1.29999995f / fConst69);
		fConst71 = (1.0f / fConst68);
		fConst72 = (((fConst67 + -0.231561884f) / fConst66) + 1.0f);
		fConst73 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst66))));
		fConst74 = (1.0f / fConst69);
		fConst75 = (0.0f - fConst74);
		fConst76 = std::tan((2254.09277f / fConst0));
		fConst77 = (1.0f / fConst76);
		fConst78 = (((fConst77 + 0.231561884f) / fConst76) + 1.0f);
		fConst79 = (1.0f / (fConst78 * fConst76));
		fConst80 = (1.0f / fConst78);
		fConst81 = (((fConst77 + -0.231561884f) / fConst76) + 1.0f);
		fConst82 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst76))));
		fConst83 = (0.0f - fConst79);
		fConst84 = std::tan((2839.99976f / fConst0));
		fConst85 = (1.0f / fConst84);
		fConst86 = (((fConst85 + 0.231561884f) / fConst84) + 1.0f);
		fConst87 = (fConst86 * fConst84);
		fConst88 = (1.10000002f / fConst87);
		fConst89 = (1.0f / fConst86);
		fConst90 = (((fConst85 + -0.231561884f) / fConst84) + 1.0f);
		fConst91 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst84))));
		fConst92 = (1.0f / fConst87);
		fConst93 = (0.0f - fConst92);
		fConst94 = std::tan((3578.27393f / fConst0));
		fConst95 = (1.0f / fConst94);
		fConst96 = (((fConst95 + 0.231561884f) / fConst94) + 1.0f);
		fConst97 = (fConst96 * fConst94);
		fConst98 = (1.20000005f / fConst97);
		fConst99 = (1.0f / fConst96);
		fConst100 = (((fConst95 + -0.231561884f) / fConst94) + 1.0f);
		fConst101 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst94))));
		fConst102 = (1.0f / fConst97);
		fConst103 = (0.0f - fConst102);
		fConst104 = std::tan((4508.18555f / fConst0));
		fConst105 = (1.0f / fConst104);
		fConst106 = (((fConst105 + 0.231561884f) / fConst104) + 1.0f);
		fConst107 = (fConst106 * fConst104);
		fConst108 = (0.850000024f / fConst107);
		fConst109 = (1.0f / fConst106);
		fConst110 = (((fConst105 + -0.231561884f) / fConst104) + 1.0f);
		fConst111 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst104))));
		fConst112 = (1.0f / fConst107);
		fConst113 = (0.0f - fConst112);
		fConst114 = std::tan((5679.99951f / fConst0));
		fConst115 = (1.0f / fConst114);
		fConst116 = (((fConst115 + 0.231561884f) / fConst114) + 1.0f);
		fConst117 = (1.0f / (fConst116 * fConst114));
		fConst118 = (1.0f / fConst116);
		fConst119 = (((fConst115 + -0.231561884f) / fConst114) + 1.0f);
		fConst120 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst114))));
		fConst121 = (0.0f - fConst117);
		fConst122 = std::tan((7099.99951f / fConst0));
		fConst123 = (1.0f / fConst122);
		fConst124 = (((fConst123 + 0.231561884f) / fConst122) + 1.0f);
		fConst125 = (fConst124 * fConst122);
		fConst126 = (0.850000024f / fConst125);
		fConst127 = (1.0f / fConst124);
		fConst128 = (((fConst123 + -0.231561884f) / fConst122) + 1.0f);
		fConst129 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst122))));
		fConst130 = (1.0f / fConst125);
		fConst131 = (0.0f - fConst130);
		fConst132 = std::tan((8959.82227f / fConst0));
		fConst133 = (1.0f / fConst132);
		fConst134 = (((fConst133 + 0.231561884f) / fConst132) + 1.0f);
		fConst135 = (fConst134 * fConst132);
		fConst136 = (0.949999988f / fConst135);
		fConst137 = (1.0f / fConst134);
		fConst138 = (((fConst133 + -0.231561884f) / fConst132) + 1.0f);
		fConst139 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst132))));
		fConst140 = (1.0f / fConst135);
		fConst141 = (0.0f - fConst140);
		fConst142 = std::tan((11359.999f / fConst0));
		fConst143 = (1.0f / fConst142);
		fConst144 = (((fConst143 + 0.231561884f) / fConst142) + 1.0f);
		fConst145 = (fConst144 * fConst142);
		fConst146 = (0.899999976f / fConst145);
		fConst147 = (1.0f / fConst144);
		fConst148 = (((fConst143 + -0.231561884f) / fConst142) + 1.0f);
		fConst149 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst142))));
		fConst150 = (1.0f / fConst145);
		fConst151 = (0.0f - fConst150);
		fConst152 = std::tan((14313.0957f / fConst0));
		fConst153 = (1.0f / fConst152);
		fConst154 = (((fConst153 + 0.231561884f) / fConst152) + 1.0f);
		fConst155 = (fConst154 * fConst152);
		fConst156 = (0.850000024f / fConst155);
		fConst157 = (1.0f / fConst154);
		fConst158 = (((fConst153 + -0.231561884f) / fConst152) + 1.0f);
		fConst159 = (2.0f * (1.0f - (1.0f / faust_vocoder_faustpower2_f(fConst152))));
		fConst160 = (1.0f / fConst155);
		fConst161 = (0.0f - fConst160);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.001f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(1.0f);
		fHslider5 = FAUSTFLOAT(440.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(1.0f);
		fButton1 = FAUSTFLOAT(0.0f);
		fHslider8 = FAUSTFLOAT(440.0f);
		fHslider9 = FAUSTFLOAT(1.0f);
		fButton2 = FAUSTFLOAT(0.0f);
		fHslider10 = FAUSTFLOAT(440.0f);
		fHslider11 = FAUSTFLOAT(1.0f);
		fButton3 = FAUSTFLOAT(0.0f);
		fHslider12 = FAUSTFLOAT(440.0f);
		fHslider13 = FAUSTFLOAT(1.0f);
		fButton4 = FAUSTFLOAT(0.0f);
		fHslider14 = FAUSTFLOAT(440.0f);
		fHslider15 = FAUSTFLOAT(1.0f);
		fButton5 = FAUSTFLOAT(0.0f);
		fHslider16 = FAUSTFLOAT(440.0f);
		fHslider17 = FAUSTFLOAT(0.5f);
		fHslider18 = FAUSTFLOAT(0.5f);
		
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
			fRec5[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			iRec6[l4] = 0;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iRec8[l5] = 0;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec9[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec12[l8] = 0;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec11[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec13[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			iRec16[l11] = 0;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec15[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec17[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			iRec20[l14] = 0;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec19[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec21[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			iRec24[l17] = 0;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec23[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec25[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec0[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec28[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec27[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec32[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec33[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			iVec0[l25] = 0;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			iRec34[l26] = 0;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec30[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			fRec35[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec37[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec36[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec41[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			iVec1[l32] = 0;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			iRec42[l33] = 0;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec39[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec43[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec45[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec44[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec49[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			iVec2[l39] = 0;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			iRec50[l40] = 0;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec47[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec51[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec53[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec52[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec57[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			iVec3[l46] = 0;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			iRec58[l47] = 0;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec55[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec59[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec61[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec60[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec65[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			iVec4[l53] = 0;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			iRec66[l54] = 0;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec63[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec67[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec69[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec68[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec73[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			iVec5[l60] = 0;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			iRec74[l61] = 0;
			
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec71[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec75[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec77[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec76[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec81[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			iVec6[l67] = 0;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			iRec82[l68] = 0;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec79[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec83[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec85[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec84[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec89[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			iVec7[l74] = 0;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			iRec90[l75] = 0;
			
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			fRec87[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec91[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec93[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec92[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fRec97[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			iVec8[l81] = 0;
			
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			iRec98[l82] = 0;
			
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec95[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec99[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec101[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec100[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec105[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			iVec9[l88] = 0;
			
		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			iRec106[l89] = 0;
			
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			fRec103[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec107[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec109[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fRec108[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec113[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			iVec10[l95] = 0;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			iRec114[l96] = 0;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fRec111[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec115[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec117[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fRec116[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec121[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			iVec11[l102] = 0;
			
		}
		for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			iRec122[l103] = 0;
			
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			fRec119[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec123[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec125[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			fRec124[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fRec129[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			iVec12[l109] = 0;
			
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			iRec130[l110] = 0;
			
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fRec127[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec131[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec133[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			fRec132[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec137[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			iVec13[l116] = 0;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			iRec138[l117] = 0;
			
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			fRec135[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec139[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec141[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			fRec140[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec145[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			iVec14[l123] = 0;
			
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			iRec146[l124] = 0;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec143[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec147[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 3); l127 = (l127 + 1)) {
			fRec149[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			fRec148[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fRec153[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			iVec15[l130] = 0;
			
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			iRec154[l131] = 0;
			
		}
		for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) {
			fRec151[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			fRec155[l133] = 0.0f;
			
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
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fHslider2, 0.00100000005f, 0.00100000005f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Decay", &fHslider3, 0.0f, 0.0f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Release", &fHslider1, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Sustain", &fHslider4, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("gateamount", &fHslider17, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("mix", &fHslider18, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("noise", &fHslider6, 0.0f, 0.0f, 1.0f, 0.00999999978f);
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
		ui_interface->addHorizontalSlider("freq", &fHslider10, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton2);
		ui_interface->addHorizontalSlider("velocity", &fHslider9, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider14, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton4);
		ui_interface->addHorizontalSlider("velocity", &fHslider13, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider8, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton1);
		ui_interface->addHorizontalSlider("velocity", &fHslider7, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider12, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton3);
		ui_interface->addHorizontalSlider("velocity", &fHslider11, 1.0f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider16, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton5);
		ui_interface->addHorizontalSlider("velocity", &fHslider15, 1.0f, 0.0f, 1.0f, 0.00787401572f);
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
		float fSlow10 = (fConst7 * fSlow9);
		float fSlow11 = (1.0f - (fConst0 / fSlow9));
		float fSlow12 = (2.99999992e-05f * float(fHslider6));
		float fSlow13 = float(fHslider7);
		int iSlow14 = (float(fButton1) > 0.0f);
		float fSlow15 = (float(iSlow14) * fSlow7);
		float fSlow16 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider8)));
		float fSlow17 = (fConst7 * fSlow16);
		float fSlow18 = (1.0f - (fConst0 / fSlow16));
		float fSlow19 = float(fHslider9);
		int iSlow20 = (float(fButton2) > 0.0f);
		float fSlow21 = (float(iSlow20) * fSlow7);
		float fSlow22 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider10)));
		float fSlow23 = (fConst7 * fSlow22);
		float fSlow24 = (1.0f - (fConst0 / fSlow22));
		float fSlow25 = float(fHslider11);
		int iSlow26 = (float(fButton3) > 0.0f);
		float fSlow27 = (float(iSlow26) * fSlow7);
		float fSlow28 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider12)));
		float fSlow29 = (fConst7 * fSlow28);
		float fSlow30 = (1.0f - (fConst0 / fSlow28));
		float fSlow31 = float(fHslider13);
		int iSlow32 = (float(fButton4) > 0.0f);
		float fSlow33 = (float(iSlow32) * fSlow7);
		float fSlow34 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider14)));
		float fSlow35 = (fConst7 * fSlow34);
		float fSlow36 = (1.0f - (fConst0 / fSlow34));
		float fSlow37 = float(fHslider15);
		int iSlow38 = (float(fButton5) > 0.0f);
		float fSlow39 = (float(iSlow38) * fSlow7);
		float fSlow40 = std::max<float>(1.00000001e-07f, std::fabs(float(fHslider16)));
		float fSlow41 = (fConst7 * fSlow40);
		float fSlow42 = (1.0f - (fConst0 / fSlow40));
		float fSlow43 = (0.00100000005f * float(fHslider17));
		float fSlow44 = (0.00100000005f * float(fHslider18));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec2[0] = (iSlow1 * (iRec2[1] + 1));
			int iTemp0 = (iRec2[0] < iSlow4);
			float fTemp1 = std::exp((0.0f - (fConst6 / (iSlow1?(iTemp0?fSlow6:fSlow5):fSlow2))));
			fRec1[0] = ((fRec1[1] * fTemp1) + ((iSlow1?(iTemp0?1.58730161f:fSlow8):0.0f) * (1.0f - fTemp1)));
			float fTemp2 = (fSlow10 + (fRec3[1] + -1.0f));
			int iTemp3 = (fTemp2 < 0.0f);
			float fTemp4 = (fSlow10 + fRec3[1]);
			fRec3[0] = (iTemp3?fTemp4:fTemp2);
			float fRec4 = (iTemp3?fTemp4:(fSlow10 + (fRec3[1] + (fSlow11 * fTemp2))));
			fRec5[0] = (fSlow12 + (0.999000013f * fRec5[1]));
			iRec6[0] = ((1103515245 * iRec6[1]) + 12345);
			float fTemp5 = (4.65661287e-10f * (fRec5[0] * float(iRec6[0])));
			iRec8[0] = (iSlow14 * (iRec8[1] + 1));
			int iTemp6 = (iRec8[0] < iSlow4);
			float fTemp7 = std::exp((0.0f - (fConst6 / (iSlow14?(iTemp6?fSlow6:fSlow5):fSlow2))));
			fRec7[0] = ((fRec7[1] * fTemp7) + ((iSlow14?(iTemp6?1.58730161f:fSlow15):0.0f) * (1.0f - fTemp7)));
			float fTemp8 = (fSlow17 + (fRec9[1] + -1.0f));
			int iTemp9 = (fTemp8 < 0.0f);
			float fTemp10 = (fSlow17 + fRec9[1]);
			fRec9[0] = (iTemp9?fTemp10:fTemp8);
			float fRec10 = (iTemp9?fTemp10:(fSlow17 + (fRec9[1] + (fSlow18 * fTemp8))));
			iRec12[0] = (iSlow20 * (iRec12[1] + 1));
			int iTemp11 = (iRec12[0] < iSlow4);
			float fTemp12 = std::exp((0.0f - (fConst6 / (iSlow20?(iTemp11?fSlow6:fSlow5):fSlow2))));
			fRec11[0] = ((fRec11[1] * fTemp12) + ((iSlow20?(iTemp11?1.58730161f:fSlow21):0.0f) * (1.0f - fTemp12)));
			float fTemp13 = (fSlow23 + (fRec13[1] + -1.0f));
			int iTemp14 = (fTemp13 < 0.0f);
			float fTemp15 = (fSlow23 + fRec13[1]);
			fRec13[0] = (iTemp14?fTemp15:fTemp13);
			float fRec14 = (iTemp14?fTemp15:(fSlow23 + (fRec13[1] + (fSlow24 * fTemp13))));
			iRec16[0] = (iSlow26 * (iRec16[1] + 1));
			int iTemp16 = (iRec16[0] < iSlow4);
			float fTemp17 = std::exp((0.0f - (fConst6 / (iSlow26?(iTemp16?fSlow6:fSlow5):fSlow2))));
			fRec15[0] = ((fRec15[1] * fTemp17) + ((iSlow26?(iTemp16?1.58730161f:fSlow27):0.0f) * (1.0f - fTemp17)));
			float fTemp18 = (fSlow29 + (fRec17[1] + -1.0f));
			int iTemp19 = (fTemp18 < 0.0f);
			float fTemp20 = (fSlow29 + fRec17[1]);
			fRec17[0] = (iTemp19?fTemp20:fTemp18);
			float fRec18 = (iTemp19?fTemp20:(fSlow29 + (fRec17[1] + (fSlow30 * fTemp18))));
			iRec20[0] = (iSlow32 * (iRec20[1] + 1));
			int iTemp21 = (iRec20[0] < iSlow4);
			float fTemp22 = std::exp((0.0f - (fConst6 / (iSlow32?(iTemp21?fSlow6:fSlow5):fSlow2))));
			fRec19[0] = ((fRec19[1] * fTemp22) + ((iSlow32?(iTemp21?1.58730161f:fSlow33):0.0f) * (1.0f - fTemp22)));
			float fTemp23 = (fSlow35 + (fRec21[1] + -1.0f));
			int iTemp24 = (fTemp23 < 0.0f);
			float fTemp25 = (fSlow35 + fRec21[1]);
			fRec21[0] = (iTemp24?fTemp25:fTemp23);
			float fRec22 = (iTemp24?fTemp25:(fSlow35 + (fRec21[1] + (fSlow36 * fTemp23))));
			iRec24[0] = (iSlow38 * (iRec24[1] + 1));
			int iTemp26 = (iRec24[0] < iSlow4);
			float fTemp27 = std::exp((0.0f - (fConst6 / (iSlow38?(iTemp26?fSlow6:fSlow5):fSlow2))));
			fRec23[0] = ((fRec23[1] * fTemp27) + ((iSlow38?(iTemp26?1.58730161f:fSlow39):0.0f) * (1.0f - fTemp27)));
			float fTemp28 = (fSlow41 + (fRec25[1] + -1.0f));
			int iTemp29 = (fTemp28 < 0.0f);
			float fTemp30 = (fSlow41 + fRec25[1]);
			fRec25[0] = (iTemp29?fTemp30:fTemp28);
			float fRec26 = (iTemp29?fTemp30:(fSlow41 + (fRec25[1] + (fSlow42 * fTemp28))));
			float fTemp31 = ((((((fSlow0 * (std::min<float>(1.0f, fRec1[0]) * ((0.200000003f * ((2.0f * fRec4) + -1.0f)) + fTemp5))) + (fSlow13 * (std::min<float>(1.0f, fRec7[0]) * (fTemp5 + (0.200000003f * ((2.0f * fRec10) + -1.0f)))))) + (fSlow19 * (std::min<float>(1.0f, fRec11[0]) * (fTemp5 + (0.200000003f * ((2.0f * fRec14) + -1.0f)))))) + (fSlow25 * (std::min<float>(1.0f, fRec15[0]) * (fTemp5 + (0.200000003f * ((2.0f * fRec18) + -1.0f)))))) + (fSlow31 * (std::min<float>(1.0f, fRec19[0]) * (fTemp5 + (0.200000003f * ((2.0f * fRec22) + -1.0f)))))) + (fSlow37 * (std::min<float>(1.0f, fRec23[0]) * (fTemp5 + (0.200000003f * ((2.0f * fRec26) + -1.0f))))));
			fRec0[0] = (fTemp31 - (fConst8 * ((fConst9 * fRec0[2]) + (fConst10 * fRec0[1]))));
			float fTemp32 = float(input0[i]);
			fRec28[0] = (fTemp32 - (fConst8 * ((fConst9 * fRec28[2]) + (fConst10 * fRec28[1]))));
			float fTemp33 = std::fabs(((fConst11 * fRec28[0]) + (fConst12 * fRec28[2])));
			fRec27[0] = std::max<float>(fTemp33, ((fConst13 * fRec27[1]) + (fConst14 * fTemp33)));
			fRec32[0] = ((fConst13 * fRec32[1]) + (fConst14 * std::fabs(fRec27[0])));
			float fRec31 = fRec32[0];
			fRec33[0] = (fSlow43 + (0.999000013f * fRec33[1]));
			float fTemp34 = exp10f((0.0500000007f * ((20.0f * fRec33[0]) + -40.0f)));
			int iTemp35 = (fRec31 > fTemp34);
			iVec0[0] = iTemp35;
			iRec34[0] = std::max<int>(int((iConst15 * (iTemp35 < iVec0[1]))), int((iRec34[1] + -1)));
			fRec30[0] = ((fConst13 * fRec30[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp35), float((iRec34[0] > 0))))));
			float fRec29 = fRec30[0];
			fRec35[0] = (fTemp31 - (fConst21 * ((fConst22 * fRec35[2]) + (fConst23 * fRec35[1]))));
			fRec37[0] = (fTemp32 - (fConst21 * ((fConst22 * fRec37[2]) + (fConst23 * fRec37[1]))));
			float fTemp36 = std::fabs(((fConst24 * fRec37[0]) + (fConst25 * fRec37[2])));
			fRec36[0] = std::max<float>(fTemp36, ((fConst13 * fRec36[1]) + (fConst14 * fTemp36)));
			fRec41[0] = ((fConst13 * fRec41[1]) + (fConst14 * std::fabs(fRec36[0])));
			float fRec40 = fRec41[0];
			int iTemp37 = (fRec40 > fTemp34);
			iVec1[0] = iTemp37;
			iRec42[0] = std::max<int>(int((iConst15 * (iTemp37 < iVec1[1]))), int((iRec42[1] + -1)));
			fRec39[0] = ((fConst13 * fRec39[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp37), float((iRec42[0] > 0))))));
			float fRec38 = fRec39[0];
			fRec43[0] = (fTemp31 - (fConst31 * ((fConst32 * fRec43[2]) + (fConst33 * fRec43[1]))));
			fRec45[0] = (fTemp32 - (fConst31 * ((fConst32 * fRec45[2]) + (fConst33 * fRec45[1]))));
			float fTemp38 = std::fabs(((fConst34 * fRec45[0]) + (fConst35 * fRec45[2])));
			fRec44[0] = std::max<float>(fTemp38, ((fConst13 * fRec44[1]) + (fConst14 * fTemp38)));
			fRec49[0] = ((fConst13 * fRec49[1]) + (fConst14 * std::fabs(fRec44[0])));
			float fRec48 = fRec49[0];
			int iTemp39 = (fRec48 > fTemp34);
			iVec2[0] = iTemp39;
			iRec50[0] = std::max<int>(int((iConst15 * (iTemp39 < iVec2[1]))), int((iRec50[1] + -1)));
			fRec47[0] = ((fConst13 * fRec47[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp39), float((iRec50[0] > 0))))));
			float fRec46 = fRec47[0];
			fRec51[0] = (fTemp31 - (fConst41 * ((fConst42 * fRec51[2]) + (fConst43 * fRec51[1]))));
			fRec53[0] = (fTemp32 - (fConst41 * ((fConst42 * fRec53[2]) + (fConst43 * fRec53[1]))));
			float fTemp40 = std::fabs(((fConst44 * fRec53[0]) + (fConst45 * fRec53[2])));
			fRec52[0] = std::max<float>(fTemp40, ((fConst13 * fRec52[1]) + (fConst14 * fTemp40)));
			fRec57[0] = ((fConst13 * fRec57[1]) + (fConst14 * std::fabs(fRec52[0])));
			float fRec56 = fRec57[0];
			int iTemp41 = (fRec56 > fTemp34);
			iVec3[0] = iTemp41;
			iRec58[0] = std::max<int>(int((iConst15 * (iTemp41 < iVec3[1]))), int((iRec58[1] + -1)));
			fRec55[0] = ((fConst13 * fRec55[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp41), float((iRec58[0] > 0))))));
			float fRec54 = fRec55[0];
			fRec59[0] = (fTemp31 - (fConst51 * ((fConst52 * fRec59[2]) + (fConst53 * fRec59[1]))));
			fRec61[0] = (fTemp32 - (fConst51 * ((fConst52 * fRec61[2]) + (fConst53 * fRec61[1]))));
			float fTemp42 = std::fabs(((fConst54 * fRec61[0]) + (fConst55 * fRec61[2])));
			fRec60[0] = std::max<float>(fTemp42, ((fConst13 * fRec60[1]) + (fConst14 * fTemp42)));
			fRec65[0] = ((fConst13 * fRec65[1]) + (fConst14 * std::fabs(fRec60[0])));
			float fRec64 = fRec65[0];
			int iTemp43 = (fRec64 > fTemp34);
			iVec4[0] = iTemp43;
			iRec66[0] = std::max<int>(int((iConst15 * (iTemp43 < iVec4[1]))), int((iRec66[1] + -1)));
			fRec63[0] = ((fConst13 * fRec63[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp43), float((iRec66[0] > 0))))));
			float fRec62 = fRec63[0];
			fRec67[0] = (fTemp31 - (fConst61 * ((fConst62 * fRec67[2]) + (fConst63 * fRec67[1]))));
			fRec69[0] = (fTemp32 - (fConst61 * ((fConst62 * fRec69[2]) + (fConst63 * fRec69[1]))));
			float fTemp44 = std::fabs(((fConst64 * fRec69[0]) + (fConst65 * fRec69[2])));
			fRec68[0] = std::max<float>(fTemp44, ((fConst13 * fRec68[1]) + (fConst14 * fTemp44)));
			fRec73[0] = ((fConst13 * fRec73[1]) + (fConst14 * std::fabs(fRec68[0])));
			float fRec72 = fRec73[0];
			int iTemp45 = (fRec72 > fTemp34);
			iVec5[0] = iTemp45;
			iRec74[0] = std::max<int>(int((iConst15 * (iTemp45 < iVec5[1]))), int((iRec74[1] + -1)));
			fRec71[0] = ((fConst13 * fRec71[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp45), float((iRec74[0] > 0))))));
			float fRec70 = fRec71[0];
			fRec75[0] = (fTemp31 - (fConst71 * ((fConst72 * fRec75[2]) + (fConst73 * fRec75[1]))));
			fRec77[0] = (fTemp32 - (fConst71 * ((fConst72 * fRec77[2]) + (fConst73 * fRec77[1]))));
			float fTemp46 = std::fabs(((fConst74 * fRec77[0]) + (fConst75 * fRec77[2])));
			fRec76[0] = std::max<float>(fTemp46, ((fConst13 * fRec76[1]) + (fConst14 * fTemp46)));
			fRec81[0] = ((fConst13 * fRec81[1]) + (fConst14 * std::fabs(fRec76[0])));
			float fRec80 = fRec81[0];
			int iTemp47 = (fRec80 > fTemp34);
			iVec6[0] = iTemp47;
			iRec82[0] = std::max<int>(int((iConst15 * (iTemp47 < iVec6[1]))), int((iRec82[1] + -1)));
			fRec79[0] = ((fConst13 * fRec79[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp47), float((iRec82[0] > 0))))));
			float fRec78 = fRec79[0];
			fRec83[0] = (fTemp31 - (fConst80 * ((fConst81 * fRec83[2]) + (fConst82 * fRec83[1]))));
			fRec85[0] = (fTemp32 - (fConst80 * ((fConst81 * fRec85[2]) + (fConst82 * fRec85[1]))));
			float fTemp48 = std::fabs(((fConst79 * fRec85[0]) + (fConst83 * fRec85[2])));
			fRec84[0] = std::max<float>(fTemp48, ((fConst13 * fRec84[1]) + (fConst14 * fTemp48)));
			fRec89[0] = ((fConst13 * fRec89[1]) + (fConst14 * std::fabs(fRec84[0])));
			float fRec88 = fRec89[0];
			int iTemp49 = (fRec88 > fTemp34);
			iVec7[0] = iTemp49;
			iRec90[0] = std::max<int>(int((iConst15 * (iTemp49 < iVec7[1]))), int((iRec90[1] + -1)));
			fRec87[0] = ((fConst13 * fRec87[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp49), float((iRec90[0] > 0))))));
			float fRec86 = fRec87[0];
			fRec91[0] = (fTemp31 - (fConst89 * ((fConst90 * fRec91[2]) + (fConst91 * fRec91[1]))));
			fRec93[0] = (fTemp32 - (fConst89 * ((fConst90 * fRec93[2]) + (fConst91 * fRec93[1]))));
			float fTemp50 = std::fabs(((fConst92 * fRec93[0]) + (fConst93 * fRec93[2])));
			fRec92[0] = std::max<float>(fTemp50, ((fConst13 * fRec92[1]) + (fConst14 * fTemp50)));
			fRec97[0] = ((fConst13 * fRec97[1]) + (fConst14 * std::fabs(fRec92[0])));
			float fRec96 = fRec97[0];
			int iTemp51 = (fRec96 > fTemp34);
			iVec8[0] = iTemp51;
			iRec98[0] = std::max<int>(int((iConst15 * (iTemp51 < iVec8[1]))), int((iRec98[1] + -1)));
			fRec95[0] = ((fConst13 * fRec95[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp51), float((iRec98[0] > 0))))));
			float fRec94 = fRec95[0];
			fRec99[0] = (fTemp31 - (fConst99 * ((fConst100 * fRec99[2]) + (fConst101 * fRec99[1]))));
			fRec101[0] = (fTemp32 - (fConst99 * ((fConst100 * fRec101[2]) + (fConst101 * fRec101[1]))));
			float fTemp52 = std::fabs(((fConst102 * fRec101[0]) + (fConst103 * fRec101[2])));
			fRec100[0] = std::max<float>(fTemp52, ((fConst13 * fRec100[1]) + (fConst14 * fTemp52)));
			fRec105[0] = ((fConst13 * fRec105[1]) + (fConst14 * std::fabs(fRec100[0])));
			float fRec104 = fRec105[0];
			int iTemp53 = (fRec104 > fTemp34);
			iVec9[0] = iTemp53;
			iRec106[0] = std::max<int>(int((iConst15 * (iTemp53 < iVec9[1]))), int((iRec106[1] + -1)));
			fRec103[0] = ((fConst13 * fRec103[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp53), float((iRec106[0] > 0))))));
			float fRec102 = fRec103[0];
			fRec107[0] = (fTemp31 - (fConst109 * ((fConst110 * fRec107[2]) + (fConst111 * fRec107[1]))));
			fRec109[0] = (fTemp32 - (fConst109 * ((fConst110 * fRec109[2]) + (fConst111 * fRec109[1]))));
			float fTemp54 = std::fabs(((fConst112 * fRec109[0]) + (fConst113 * fRec109[2])));
			fRec108[0] = std::max<float>(fTemp54, ((fConst13 * fRec108[1]) + (fConst14 * fTemp54)));
			fRec113[0] = ((fConst13 * fRec113[1]) + (fConst14 * std::fabs(fRec108[0])));
			float fRec112 = fRec113[0];
			int iTemp55 = (fRec112 > fTemp34);
			iVec10[0] = iTemp55;
			iRec114[0] = std::max<int>(int((iConst15 * (iTemp55 < iVec10[1]))), int((iRec114[1] + -1)));
			fRec111[0] = ((fConst13 * fRec111[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp55), float((iRec114[0] > 0))))));
			float fRec110 = fRec111[0];
			fRec115[0] = (fTemp31 - (fConst118 * ((fConst119 * fRec115[2]) + (fConst120 * fRec115[1]))));
			fRec117[0] = (fTemp32 - (fConst118 * ((fConst119 * fRec117[2]) + (fConst120 * fRec117[1]))));
			float fTemp56 = std::fabs(((fConst117 * fRec117[0]) + (fConst121 * fRec117[2])));
			fRec116[0] = std::max<float>(fTemp56, ((fConst13 * fRec116[1]) + (fConst14 * fTemp56)));
			fRec121[0] = ((fConst13 * fRec121[1]) + (fConst14 * std::fabs(fRec116[0])));
			float fRec120 = fRec121[0];
			int iTemp57 = (fRec120 > fTemp34);
			iVec11[0] = iTemp57;
			iRec122[0] = std::max<int>(int((iConst15 * (iTemp57 < iVec11[1]))), int((iRec122[1] + -1)));
			fRec119[0] = ((fConst13 * fRec119[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp57), float((iRec122[0] > 0))))));
			float fRec118 = fRec119[0];
			fRec123[0] = (fTemp31 - (fConst127 * ((fConst128 * fRec123[2]) + (fConst129 * fRec123[1]))));
			fRec125[0] = (fTemp32 - (fConst127 * ((fConst128 * fRec125[2]) + (fConst129 * fRec125[1]))));
			float fTemp58 = std::fabs(((fConst130 * fRec125[0]) + (fConst131 * fRec125[2])));
			fRec124[0] = std::max<float>(fTemp58, ((fConst13 * fRec124[1]) + (fConst14 * fTemp58)));
			fRec129[0] = ((fConst13 * fRec129[1]) + (fConst14 * std::fabs(fRec124[0])));
			float fRec128 = fRec129[0];
			int iTemp59 = (fRec128 > fTemp34);
			iVec12[0] = iTemp59;
			iRec130[0] = std::max<int>(int((iConst15 * (iTemp59 < iVec12[1]))), int((iRec130[1] + -1)));
			fRec127[0] = ((fConst13 * fRec127[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp59), float((iRec130[0] > 0))))));
			float fRec126 = fRec127[0];
			fRec131[0] = (fTemp31 - (fConst137 * ((fConst138 * fRec131[2]) + (fConst139 * fRec131[1]))));
			fRec133[0] = (fTemp32 - (fConst137 * ((fConst138 * fRec133[2]) + (fConst139 * fRec133[1]))));
			float fTemp60 = std::fabs(((fConst140 * fRec133[0]) + (fConst141 * fRec133[2])));
			fRec132[0] = std::max<float>(fTemp60, ((fConst13 * fRec132[1]) + (fConst14 * fTemp60)));
			fRec137[0] = ((fConst13 * fRec137[1]) + (fConst14 * std::fabs(fRec132[0])));
			float fRec136 = fRec137[0];
			int iTemp61 = (fRec136 > fTemp34);
			iVec13[0] = iTemp61;
			iRec138[0] = std::max<int>(int((iConst15 * (iTemp61 < iVec13[1]))), int((iRec138[1] + -1)));
			fRec135[0] = ((fConst13 * fRec135[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp61), float((iRec138[0] > 0))))));
			float fRec134 = fRec135[0];
			fRec139[0] = (fTemp31 - (fConst147 * ((fConst148 * fRec139[2]) + (fConst149 * fRec139[1]))));
			fRec141[0] = (fTemp32 - (fConst147 * ((fConst148 * fRec141[2]) + (fConst149 * fRec141[1]))));
			float fTemp62 = std::fabs(((fConst150 * fRec141[0]) + (fConst151 * fRec141[2])));
			fRec140[0] = std::max<float>(fTemp62, ((fConst13 * fRec140[1]) + (fConst14 * fTemp62)));
			fRec145[0] = ((fConst13 * fRec145[1]) + (fConst14 * std::fabs(fRec140[0])));
			float fRec144 = fRec145[0];
			int iTemp63 = (fRec144 > fTemp34);
			iVec14[0] = iTemp63;
			iRec146[0] = std::max<int>(int((iConst15 * (iTemp63 < iVec14[1]))), int((iRec146[1] + -1)));
			fRec143[0] = ((fConst13 * fRec143[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp63), float((iRec146[0] > 0))))));
			float fRec142 = fRec143[0];
			fRec147[0] = (fTemp31 - (fConst157 * ((fConst158 * fRec147[2]) + (fConst159 * fRec147[1]))));
			fRec149[0] = (fTemp32 - (fConst157 * ((fConst158 * fRec149[2]) + (fConst159 * fRec149[1]))));
			float fTemp64 = std::fabs(((fConst160 * fRec149[0]) + (fConst161 * fRec149[2])));
			fRec148[0] = std::max<float>(fTemp64, ((fConst13 * fRec148[1]) + (fConst14 * fTemp64)));
			fRec153[0] = ((fConst13 * fRec153[1]) + (fConst14 * std::fabs(fRec148[0])));
			float fRec152 = fRec153[0];
			int iTemp65 = (fRec152 > fTemp34);
			iVec15[0] = iTemp65;
			iRec154[0] = std::max<int>(int((iConst15 * (iTemp65 < iVec15[1]))), int((iRec154[1] + -1)));
			fRec151[0] = ((fConst13 * fRec151[1]) + (fConst14 * std::fabs(std::max<float>(float(iTemp65), float((iRec154[0] > 0))))));
			float fRec150 = fRec151[0];
			fRec155[0] = (fSlow44 + (0.999000013f * fRec155[1]));
			output0[i] = FAUSTFLOAT(((((((((((((((((0.400000006f * ((fConst5 * ((fRec0[0] * fRec27[0]) * fRec29)) + (fRec0[2] * (0.0f - (fConst5 * (fRec27[0] * fRec29)))))) + (0.850000024f * ((fConst20 * ((fRec35[0] * fRec36[0]) * fRec38)) + (fRec35[2] * (0.0f - (fConst20 * (fRec36[0] * fRec38))))))) + (1.10000002f * ((fConst30 * ((fRec43[0] * fRec44[0]) * fRec46)) + (fRec43[2] * (0.0f - (fConst30 * (fRec44[0] * fRec46))))))) + (1.35000002f * ((fConst40 * ((fRec51[0] * fRec52[0]) * fRec54)) + (fRec51[2] * (0.0f - (fConst40 * (fRec52[0] * fRec54))))))) + (1.54999995f * ((fConst50 * ((fRec59[0] * fRec60[0]) * fRec62)) + (fRec59[2] * (0.0f - (fConst50 * (fRec60[0] * fRec62))))))) + (1.79999995f * ((fConst60 * ((fRec67[0] * fRec68[0]) * fRec70)) + (fRec67[2] * (0.0f - (fConst60 * (fRec68[0] * fRec70))))))) + (2.0f * ((fConst70 * ((fRec75[0] * fRec76[0]) * fRec78)) + (fRec75[2] * (0.0f - (fConst70 * (fRec76[0] * fRec78))))))) + (2.25f * ((fConst79 * ((fRec83[0] * fRec84[0]) * fRec86)) + (fRec83[2] * (0.0f - (fConst79 * (fRec84[0] * fRec86))))))) + (2.5f * ((fConst88 * ((fRec91[0] * fRec92[0]) * fRec94)) + (fRec91[2] * (0.0f - (fConst88 * (fRec92[0] * fRec94))))))) + (2.75f * ((fConst98 * ((fRec99[0] * fRec100[0]) * fRec102)) + (fRec99[2] * (0.0f - (fConst98 * (fRec100[0] * fRec102))))))) + (3.25f * ((fConst108 * ((fRec107[0] * fRec108[0]) * fRec110)) + (fRec107[2] * (0.0f - (fConst108 * (fRec108[0] * fRec110))))))) + (3.5f * ((fConst117 * ((fRec115[0] * fRec116[0]) * fRec118)) + (fRec115[2] * (0.0f - (fConst117 * (fRec116[0] * fRec118))))))) + (4.5f * (((fConst126 * ((fRec123[0] * fRec124[0]) * fRec126)) + (fRec123[2] * (0.0f - (fConst126 * (fRec124[0] * fRec126))))) + ((fConst136 * ((fRec131[0] * fRec132[0]) * fRec134)) + (fRec131[2] * (0.0f - (fConst136 * (fRec132[0] * fRec134)))))))) + (5.0f * ((fConst146 * ((fRec139[0] * fRec140[0]) * fRec142)) + (fRec139[2] * (0.0f - (fConst146 * (fRec140[0] * fRec142))))))) + (5.25f * ((fConst156 * ((fRec147[0] * fRec148[0]) * fRec150)) + (fRec147[2] * (0.0f - (fConst156 * (fRec148[0] * fRec150))))))) + (fRec155[0] * fTemp32)));
			iRec2[1] = iRec2[0];
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			iRec6[1] = iRec6[0];
			iRec8[1] = iRec8[0];
			fRec7[1] = fRec7[0];
			fRec9[1] = fRec9[0];
			iRec12[1] = iRec12[0];
			fRec11[1] = fRec11[0];
			fRec13[1] = fRec13[0];
			iRec16[1] = iRec16[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			iRec20[1] = iRec20[0];
			fRec19[1] = fRec19[0];
			fRec21[1] = fRec21[0];
			iRec24[1] = iRec24[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			iVec0[1] = iVec0[0];
			iRec34[1] = iRec34[0];
			fRec30[1] = fRec30[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec41[1] = fRec41[0];
			iVec1[1] = iVec1[0];
			iRec42[1] = iRec42[0];
			fRec39[1] = fRec39[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec49[1] = fRec49[0];
			iVec2[1] = iVec2[0];
			iRec50[1] = iRec50[0];
			fRec47[1] = fRec47[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[1] = fRec52[0];
			fRec57[1] = fRec57[0];
			iVec3[1] = iVec3[0];
			iRec58[1] = iRec58[0];
			fRec55[1] = fRec55[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[1] = fRec60[0];
			fRec65[1] = fRec65[0];
			iVec4[1] = iVec4[0];
			iRec66[1] = iRec66[0];
			fRec63[1] = fRec63[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[1] = fRec68[0];
			fRec73[1] = fRec73[0];
			iVec5[1] = iVec5[0];
			iRec74[1] = iRec74[0];
			fRec71[1] = fRec71[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[1] = fRec76[0];
			fRec81[1] = fRec81[0];
			iVec6[1] = iVec6[0];
			iRec82[1] = iRec82[0];
			fRec79[1] = fRec79[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[1] = fRec84[0];
			fRec89[1] = fRec89[0];
			iVec7[1] = iVec7[0];
			iRec90[1] = iRec90[0];
			fRec87[1] = fRec87[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[1] = fRec92[0];
			fRec97[1] = fRec97[0];
			iVec8[1] = iVec8[0];
			iRec98[1] = iRec98[0];
			fRec95[1] = fRec95[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec100[1] = fRec100[0];
			fRec105[1] = fRec105[0];
			iVec9[1] = iVec9[0];
			iRec106[1] = iRec106[0];
			fRec103[1] = fRec103[0];
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec108[1] = fRec108[0];
			fRec113[1] = fRec113[0];
			iVec10[1] = iVec10[0];
			iRec114[1] = iRec114[0];
			fRec111[1] = fRec111[0];
			fRec115[2] = fRec115[1];
			fRec115[1] = fRec115[0];
			fRec117[2] = fRec117[1];
			fRec117[1] = fRec117[0];
			fRec116[1] = fRec116[0];
			fRec121[1] = fRec121[0];
			iVec11[1] = iVec11[0];
			iRec122[1] = iRec122[0];
			fRec119[1] = fRec119[0];
			fRec123[2] = fRec123[1];
			fRec123[1] = fRec123[0];
			fRec125[2] = fRec125[1];
			fRec125[1] = fRec125[0];
			fRec124[1] = fRec124[0];
			fRec129[1] = fRec129[0];
			iVec12[1] = iVec12[0];
			iRec130[1] = iRec130[0];
			fRec127[1] = fRec127[0];
			fRec131[2] = fRec131[1];
			fRec131[1] = fRec131[0];
			fRec133[2] = fRec133[1];
			fRec133[1] = fRec133[0];
			fRec132[1] = fRec132[0];
			fRec137[1] = fRec137[0];
			iVec13[1] = iVec13[0];
			iRec138[1] = iRec138[0];
			fRec135[1] = fRec135[0];
			fRec139[2] = fRec139[1];
			fRec139[1] = fRec139[0];
			fRec141[2] = fRec141[1];
			fRec141[1] = fRec141[0];
			fRec140[1] = fRec140[0];
			fRec145[1] = fRec145[0];
			iVec14[1] = iVec14[0];
			iRec146[1] = iRec146[0];
			fRec143[1] = fRec143[0];
			fRec147[2] = fRec147[1];
			fRec147[1] = fRec147[0];
			fRec149[2] = fRec149[1];
			fRec149[1] = fRec149[0];
			fRec148[1] = fRec148[0];
			fRec153[1] = fRec153[0];
			iVec15[1] = iVec15[0];
			iRec154[1] = iRec154[0];
			fRec151[1] = fRec151[0];
			fRec155[1] = fRec155[0];
			
		}
		
	}

	
};

#endif
