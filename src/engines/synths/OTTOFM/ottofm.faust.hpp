//----------------------------------------------------------
// name: "ottofm"
//
// Code generated with Faust 2.11.10 (https://faust.grame.fr)
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
#define FAUSTCLASS faust_ottofm
#endif

class faust_ottofm : public dsp {
  private:
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec0[2];
		float 	fTempPerm0;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm0 = 0;
			for (int i=0; i<2; i++) iRec0[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec0[0] = (iRec0[1] + 1);
				fTempPerm0 = sinf((9.5873799242852573e-05f * float((iRec0[0] + -1))));
				output[i] = fTempPerm0;
				// post processing
				iRec0[1] = iRec0[0];
			}
		}
	};


	FAUSTFLOAT 	fslider0;
	static float 	ftbl0[65536];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider5;
	float 	fConst2;
	FAUSTFLOAT 	fslider6;
	float 	fRec3[2];
	float 	fConst3;
	int 	iTempPerm2;
	float 	fRec2[2];
	float 	fRec4[2];
	float 	fTempPerm3;
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm4;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	float 	fTempPerm5;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	float 	fRec5[2];
	float 	fTempPerm6;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	float 	fRec7[2];
	int 	iTempPerm7;
	float 	fRec6[2];
	float 	fRec8[2];
	float 	fTempPerm8;
	FAUSTFLOAT 	fbargraph1;
	float 	fTempPerm9;
	float 	fTempPerm10;
	FAUSTFLOAT 	fslider14;
	float 	fTempPerm11;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	float 	fRec9[2];
	float 	fTempPerm12;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fslider19;
	float 	fRec11[2];
	int 	iTempPerm13;
	float 	fRec10[2];
	float 	fRec12[2];
	float 	fTempPerm14;
	FAUSTFLOAT 	fbargraph2;
	float 	fTempPerm15;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	int 	iRec15[2];
	int 	iTempPerm16;
	float 	fConst4;
	float 	fTempPerm17;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	float 	fRec14[2];
	float 	fTempPerm18;
	FAUSTFLOAT 	fbargraph3;
	float 	fTempPerm19;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT 	fslider31;
	float 	fTempPerm20;
	FAUSTFLOAT 	fslider32;
	float 	fRec16[2];
	float 	fTempPerm21;
	FAUSTFLOAT 	fbutton1;
	float 	fRec18[2];
	int 	iTempPerm22;
	float 	fRec17[2];
	float 	fRec19[2];
	float 	fTempPerm23;
	FAUSTFLOAT 	fbargraph4;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fRec20[2];
	float 	fTempPerm26;
	float 	fRec22[2];
	int 	iTempPerm27;
	float 	fRec21[2];
	float 	fRec23[2];
	float 	fTempPerm28;
	FAUSTFLOAT 	fbargraph5;
	float 	fTempPerm29;
	float 	fTempPerm30;
	float 	fTempPerm31;
	float 	fRec24[2];
	float 	fTempPerm32;
	float 	fRec26[2];
	int 	iTempPerm33;
	float 	fRec25[2];
	float 	fRec27[2];
	float 	fTempPerm34;
	FAUSTFLOAT 	fbargraph6;
	float 	fTempPerm35;
	float 	fRec28[2];
	int 	iRec30[2];
	int 	iTempPerm36;
	float 	fTempPerm37;
	float 	fRec29[2];
	float 	fTempPerm38;
	FAUSTFLOAT 	fbargraph7;
	float 	fTempPerm39;
	FAUSTFLOAT 	fslider33;
	float 	fTempPerm40;
	FAUSTFLOAT 	fslider34;
	float 	fRec31[2];
	float 	fTempPerm41;
	FAUSTFLOAT 	fbutton2;
	float 	fRec33[2];
	int 	iTempPerm42;
	float 	fRec32[2];
	float 	fRec34[2];
	float 	fTempPerm43;
	FAUSTFLOAT 	fbargraph8;
	float 	fTempPerm44;
	float 	fTempPerm45;
	float 	fRec35[2];
	float 	fTempPerm46;
	float 	fRec37[2];
	int 	iTempPerm47;
	float 	fRec36[2];
	float 	fRec38[2];
	float 	fTempPerm48;
	FAUSTFLOAT 	fbargraph9;
	float 	fTempPerm49;
	float 	fTempPerm50;
	float 	fTempPerm51;
	float 	fRec39[2];
	float 	fTempPerm52;
	float 	fRec41[2];
	int 	iTempPerm53;
	float 	fRec40[2];
	float 	fRec42[2];
	float 	fTempPerm54;
	FAUSTFLOAT 	fbargraph10;
	float 	fTempPerm55;
	float 	fRec43[2];
	int 	iRec45[2];
	int 	iTempPerm56;
	float 	fTempPerm57;
	float 	fRec44[2];
	float 	fTempPerm58;
	FAUSTFLOAT 	fbargraph11;
	float 	fTempPerm59;
	FAUSTFLOAT 	fslider35;
	float 	fTempPerm60;
	FAUSTFLOAT 	fslider36;
	float 	fRec46[2];
	float 	fTempPerm61;
	FAUSTFLOAT 	fbutton3;
	float 	fRec48[2];
	int 	iTempPerm62;
	float 	fRec47[2];
	float 	fRec49[2];
	float 	fTempPerm63;
	FAUSTFLOAT 	fbargraph12;
	float 	fTempPerm64;
	float 	fTempPerm65;
	float 	fRec50[2];
	float 	fTempPerm66;
	float 	fRec52[2];
	int 	iTempPerm67;
	float 	fRec51[2];
	float 	fRec53[2];
	float 	fTempPerm68;
	FAUSTFLOAT 	fbargraph13;
	float 	fTempPerm69;
	float 	fTempPerm70;
	float 	fTempPerm71;
	float 	fRec54[2];
	float 	fTempPerm72;
	float 	fRec56[2];
	int 	iTempPerm73;
	float 	fRec55[2];
	float 	fRec57[2];
	float 	fTempPerm74;
	FAUSTFLOAT 	fbargraph14;
	float 	fTempPerm75;
	float 	fRec58[2];
	int 	iRec60[2];
	int 	iTempPerm76;
	float 	fTempPerm77;
	float 	fRec59[2];
	float 	fTempPerm78;
	FAUSTFLOAT 	fbargraph15;
	float 	fTempPerm79;
	FAUSTFLOAT 	fslider37;
	float 	fTempPerm80;
	FAUSTFLOAT 	fslider38;
	float 	fRec61[2];
	float 	fTempPerm81;
	FAUSTFLOAT 	fbutton4;
	float 	fRec63[2];
	int 	iTempPerm82;
	float 	fRec62[2];
	float 	fRec64[2];
	float 	fTempPerm83;
	FAUSTFLOAT 	fbargraph16;
	float 	fTempPerm84;
	float 	fTempPerm85;
	float 	fRec65[2];
	float 	fTempPerm86;
	float 	fRec67[2];
	int 	iTempPerm87;
	float 	fRec66[2];
	float 	fRec68[2];
	float 	fTempPerm88;
	FAUSTFLOAT 	fbargraph17;
	float 	fTempPerm89;
	float 	fTempPerm90;
	float 	fTempPerm91;
	float 	fRec69[2];
	float 	fTempPerm92;
	float 	fRec71[2];
	int 	iTempPerm93;
	float 	fRec70[2];
	float 	fRec72[2];
	float 	fTempPerm94;
	FAUSTFLOAT 	fbargraph18;
	float 	fTempPerm95;
	float 	fRec73[2];
	int 	iRec75[2];
	int 	iTempPerm96;
	float 	fTempPerm97;
	float 	fRec74[2];
	float 	fTempPerm98;
	FAUSTFLOAT 	fbargraph19;
	float 	fTempPerm99;
	FAUSTFLOAT 	fslider39;
	float 	fTempPerm100;
	FAUSTFLOAT 	fslider40;
	float 	fRec76[2];
	float 	fTempPerm101;
	FAUSTFLOAT 	fslider41;
	FAUSTFLOAT 	fslider42;
	FAUSTFLOAT 	fbutton5;
	int 	iRec78[2];
	int 	iTempPerm102;
	float 	fTempPerm103;
	FAUSTFLOAT 	fslider43;
	float 	fRec77[2];
	float 	fTempPerm104;
	FAUSTFLOAT 	fbargraph20;
	float 	fTempPerm105;
	float 	fRec79[2];
	float 	fTempPerm106;
	FAUSTFLOAT 	fslider44;
	FAUSTFLOAT 	fslider45;
	int 	iTempPerm107;
	float 	fTempPerm108;
	FAUSTFLOAT 	fslider46;
	float 	fRec80[2];
	float 	fTempPerm109;
	FAUSTFLOAT 	fbargraph21;
	float 	fTempPerm110;
	float 	fTempPerm111;
	float 	fRec81[2];
	float 	fTempPerm112;
	int 	iTempPerm113;
	float 	fTempPerm114;
	float 	fRec82[2];
	float 	fTempPerm115;
	FAUSTFLOAT 	fbargraph22;
	float 	fTempPerm116;
	float 	fTempPerm117;
	float 	fRec83[2];
	float 	fTempPerm118;
	FAUSTFLOAT 	fslider47;
	FAUSTFLOAT 	fslider48;
	int 	iTempPerm119;
	float 	fTempPerm120;
	FAUSTFLOAT 	fslider49;
	float 	fRec84[2];
	float 	fTempPerm121;
	FAUSTFLOAT 	fbargraph23;
	float 	fTempPerm122;
	FAUSTFLOAT 	fslider50;
	float 	fTempPerm123;
	FAUSTFLOAT 	fslider51;
	FAUSTFLOAT 	fslider52;
	FAUSTFLOAT 	fslider53;
	float 	fRec86[2];
	int 	iTempPerm124;
	float 	fRec85[2];
	float 	fRec87[2];
	float 	fTempPerm125;
	FAUSTFLOAT 	fbargraph24;
	float 	fTempPerm126;
	float 	fRec89[2];
	int 	iTempPerm127;
	float 	fRec88[2];
	float 	fRec90[2];
	float 	fTempPerm128;
	FAUSTFLOAT 	fbargraph25;
	float 	fTempPerm129;
	float 	fTempPerm130;
	float 	fTempPerm131;
	float 	fTempPerm132;
	float 	fTempPerm133;
	float 	fTempPerm134;
	float 	fRec92[2];
	int 	iTempPerm135;
	float 	fRec91[2];
	float 	fRec93[2];
	float 	fTempPerm136;
	FAUSTFLOAT 	fbargraph26;
	float 	fTempPerm137;
	float 	fTempPerm138;
	float 	fTempPerm139;
	float 	fRec95[2];
	int 	iTempPerm140;
	float 	fRec94[2];
	float 	fRec96[2];
	float 	fTempPerm141;
	FAUSTFLOAT 	fbargraph27;
	float 	fTempPerm142;
	float 	fTempPerm143;
	float 	fTempPerm144;
	float 	fTempPerm145;
	float 	fTempPerm146;
	float 	fTempPerm147;
	float 	fTempPerm148;
	float 	fTempPerm149;
	float 	fTempPerm150;
	float 	fTempPerm151;
	float 	fTempPerm152;
	float 	fTempPerm153;
	float 	fTempPerm154;
	float 	fTempPerm155;
	float 	fTempPerm156;
	float 	fTempPerm157;
	float 	fTempPerm158;
	float 	fTempPerm159;
	float 	fTempPerm160;
	int 	iTempPerm161;
	float 	fTempPerm162;
	float 	fRec97[2];
	float 	fTempPerm163;
	FAUSTFLOAT 	fbargraph28;
	float 	fTempPerm164;
	float 	fTempPerm165;
	float 	fTempPerm166;
	float 	fTempPerm167;
	float 	fTempPerm168;
	float 	fTempPerm169;
	float 	fTempPerm170;
	float 	fTempPerm171;
	float 	fTempPerm172;
	int 	iTempPerm173;
	float 	fTempPerm174;
	float 	fRec98[2];
	float 	fTempPerm175;
	FAUSTFLOAT 	fbargraph29;
	float 	fTempPerm176;
	float 	fTempPerm177;
	float 	fTempPerm178;
	float 	fTempPerm179;
	float 	fRec100[2];
	int 	iTempPerm180;
	float 	fRec99[2];
	float 	fRec101[2];
	float 	fTempPerm181;
	FAUSTFLOAT 	fbargraph30;
	float 	fTempPerm182;
	int 	iTempPerm183;
	float 	fTempPerm184;
	float 	fRec102[2];
	float 	fTempPerm185;
	FAUSTFLOAT 	fbargraph31;
	float 	fTempPerm186;
	float 	fTempPerm187;
	float 	fTempPerm188;
	float 	fTempPerm189;
	float 	fTempPerm190;
	float 	fTempPerm191;
	float 	fTempPerm192;
	float 	fTempPerm193;
	float 	fTempPerm194;
	int 	iTempPerm195;
	float 	fTempPerm196;
	float 	fRec103[2];
	float 	fTempPerm197;
	FAUSTFLOAT 	fbargraph32;
	float 	fTempPerm198;
	float 	fTempPerm199;
	float 	fTempPerm200;
	float 	fTempPerm201;
	float 	fTempPerm202;
	float 	fTempPerm203;
	float 	fTempPerm204;
	float 	fTempPerm205;
	float 	fTempPerm206;
	int 	iTempPerm207;
	float 	fTempPerm208;
	float 	fRec104[2];
	float 	fTempPerm209;
	FAUSTFLOAT 	fbargraph33;
	float 	fTempPerm210;
	float 	fTempPerm211;
	float 	fTempPerm212;
	float 	fTempPerm213;
	float 	fRec106[2];
	int 	iTempPerm214;
	float 	fRec105[2];
	float 	fRec107[2];
	float 	fTempPerm215;
	FAUSTFLOAT 	fbargraph34;
	float 	fTempPerm216;
	int 	iTempPerm217;
	float 	fTempPerm218;
	float 	fRec108[2];
	float 	fTempPerm219;
	FAUSTFLOAT 	fbargraph35;
	float 	fTempPerm220;
	float 	fTempPerm221;
	float 	fTempPerm222;
	float 	fTempPerm223;
	float 	fTempPerm224;
	float 	fTempPerm225;
	float 	fTempPerm226;
	float 	fTempPerm227;
	float 	fTempPerm228;
	int 	iTempPerm229;
	float 	fTempPerm230;
	float 	fRec109[2];
	float 	fTempPerm231;
	FAUSTFLOAT 	fbargraph36;
	float 	fTempPerm232;
	float 	fTempPerm233;
	float 	fTempPerm234;
	float 	fTempPerm235;
	float 	fTempPerm236;
	float 	fTempPerm237;
	float 	fTempPerm238;
	float 	fTempPerm239;
	float 	fTempPerm240;
	int 	iTempPerm241;
	float 	fTempPerm242;
	float 	fRec110[2];
	float 	fTempPerm243;
	FAUSTFLOAT 	fbargraph37;
	float 	fTempPerm244;
	float 	fTempPerm245;
	float 	fTempPerm246;
	float 	fTempPerm247;
	float 	fRec112[2];
	int 	iTempPerm248;
	float 	fRec111[2];
	float 	fRec113[2];
	float 	fTempPerm249;
	FAUSTFLOAT 	fbargraph38;
	float 	fTempPerm250;
	int 	iTempPerm251;
	float 	fTempPerm252;
	float 	fRec114[2];
	float 	fTempPerm253;
	FAUSTFLOAT 	fbargraph39;
	float 	fTempPerm254;
	float 	fTempPerm255;
	float 	fTempPerm256;
	float 	fTempPerm257;
	float 	fTempPerm258;
	float 	fTempPerm259;
	float 	fTempPerm260;
	float 	fTempPerm261;
	float 	fTempPerm262;
	int 	iTempPerm263;
	float 	fTempPerm264;
	float 	fRec115[2];
	float 	fTempPerm265;
	FAUSTFLOAT 	fbargraph40;
	float 	fTempPerm266;
	float 	fTempPerm267;
	float 	fTempPerm268;
	float 	fTempPerm269;
	float 	fTempPerm270;
	float 	fTempPerm271;
	float 	fTempPerm272;
	float 	fTempPerm273;
	float 	fTempPerm274;
	int 	iTempPerm275;
	float 	fTempPerm276;
	float 	fRec116[2];
	float 	fTempPerm277;
	FAUSTFLOAT 	fbargraph41;
	float 	fTempPerm278;
	float 	fTempPerm279;
	float 	fTempPerm280;
	float 	fTempPerm281;
	float 	fRec118[2];
	int 	iTempPerm282;
	float 	fRec117[2];
	float 	fRec119[2];
	float 	fTempPerm283;
	FAUSTFLOAT 	fbargraph42;
	float 	fTempPerm284;
	int 	iTempPerm285;
	float 	fTempPerm286;
	float 	fRec120[2];
	float 	fTempPerm287;
	FAUSTFLOAT 	fbargraph43;
	float 	fTempPerm288;
	float 	fTempPerm289;
	float 	fTempPerm290;
	float 	fTempPerm291;
	float 	fTempPerm292;
	float 	fTempPerm293;
	float 	fTempPerm294;
	float 	fTempPerm295;
	float 	fTempPerm296;
	int 	iTempPerm297;
	float 	fTempPerm298;
	float 	fRec121[2];
	float 	fTempPerm299;
	FAUSTFLOAT 	fbargraph44;
	float 	fTempPerm300;
	float 	fTempPerm301;
	float 	fTempPerm302;
	float 	fTempPerm303;
	float 	fTempPerm304;
	float 	fTempPerm305;
	float 	fTempPerm306;
	float 	fTempPerm307;
	float 	fTempPerm308;
	int 	iTempPerm309;
	float 	fTempPerm310;
	float 	fRec122[2];
	float 	fTempPerm311;
	FAUSTFLOAT 	fbargraph45;
	float 	fTempPerm312;
	float 	fTempPerm313;
	float 	fTempPerm314;
	float 	fTempPerm315;
	float 	fRec124[2];
	int 	iTempPerm316;
	float 	fRec123[2];
	float 	fRec125[2];
	float 	fTempPerm317;
	FAUSTFLOAT 	fbargraph46;
	float 	fTempPerm318;
	int 	iTempPerm319;
	float 	fTempPerm320;
	float 	fRec126[2];
	float 	fTempPerm321;
	FAUSTFLOAT 	fbargraph47;
	float 	fTempPerm322;
	float 	fTempPerm323;
	float 	fTempPerm324;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "ottofm");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "ottofm");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(65536,ftbl0);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (1.0f / fConst0);
		fTempPerm1 = 0;
		fConst2 = (3.0f * fConst0);
		fConst3 = (0.33333333333333331f / fConst0);
		iTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		iTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		iTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		iTempPerm16 = 0;
		fConst4 = (6.9100000000000001f / fConst0);
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		iTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		iTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		iTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		iTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		iTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		iTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		iTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		iTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fTempPerm59 = 0;
		fTempPerm60 = 0;
		fTempPerm61 = 0;
		iTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		fTempPerm66 = 0;
		iTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		fTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		iTempPerm73 = 0;
		fTempPerm74 = 0;
		fTempPerm75 = 0;
		iTempPerm76 = 0;
		fTempPerm77 = 0;
		fTempPerm78 = 0;
		fTempPerm79 = 0;
		fTempPerm80 = 0;
		fTempPerm81 = 0;
		iTempPerm82 = 0;
		fTempPerm83 = 0;
		fTempPerm84 = 0;
		fTempPerm85 = 0;
		fTempPerm86 = 0;
		iTempPerm87 = 0;
		fTempPerm88 = 0;
		fTempPerm89 = 0;
		fTempPerm90 = 0;
		fTempPerm91 = 0;
		fTempPerm92 = 0;
		iTempPerm93 = 0;
		fTempPerm94 = 0;
		fTempPerm95 = 0;
		iTempPerm96 = 0;
		fTempPerm97 = 0;
		fTempPerm98 = 0;
		fTempPerm99 = 0;
		fTempPerm100 = 0;
		fTempPerm101 = 0;
		iTempPerm102 = 0;
		fTempPerm103 = 0;
		fTempPerm104 = 0;
		fTempPerm105 = 0;
		fTempPerm106 = 0;
		iTempPerm107 = 0;
		fTempPerm108 = 0;
		fTempPerm109 = 0;
		fTempPerm110 = 0;
		fTempPerm111 = 0;
		fTempPerm112 = 0;
		iTempPerm113 = 0;
		fTempPerm114 = 0;
		fTempPerm115 = 0;
		fTempPerm116 = 0;
		fTempPerm117 = 0;
		fTempPerm118 = 0;
		iTempPerm119 = 0;
		fTempPerm120 = 0;
		fTempPerm121 = 0;
		fTempPerm122 = 0;
		fTempPerm123 = 0;
		iTempPerm124 = 0;
		fTempPerm125 = 0;
		fTempPerm126 = 0;
		iTempPerm127 = 0;
		fTempPerm128 = 0;
		fTempPerm129 = 0;
		fTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		fTempPerm133 = 0;
		fTempPerm134 = 0;
		iTempPerm135 = 0;
		fTempPerm136 = 0;
		fTempPerm137 = 0;
		fTempPerm138 = 0;
		fTempPerm139 = 0;
		iTempPerm140 = 0;
		fTempPerm141 = 0;
		fTempPerm142 = 0;
		fTempPerm143 = 0;
		fTempPerm144 = 0;
		fTempPerm145 = 0;
		fTempPerm146 = 0;
		fTempPerm147 = 0;
		fTempPerm148 = 0;
		fTempPerm149 = 0;
		fTempPerm150 = 0;
		fTempPerm151 = 0;
		fTempPerm152 = 0;
		fTempPerm153 = 0;
		fTempPerm154 = 0;
		fTempPerm155 = 0;
		fTempPerm156 = 0;
		fTempPerm157 = 0;
		fTempPerm158 = 0;
		fTempPerm159 = 0;
		fTempPerm160 = 0;
		iTempPerm161 = 0;
		fTempPerm162 = 0;
		fTempPerm163 = 0;
		fTempPerm164 = 0;
		fTempPerm165 = 0;
		fTempPerm166 = 0;
		fTempPerm167 = 0;
		fTempPerm168 = 0;
		fTempPerm169 = 0;
		fTempPerm170 = 0;
		fTempPerm171 = 0;
		fTempPerm172 = 0;
		iTempPerm173 = 0;
		fTempPerm174 = 0;
		fTempPerm175 = 0;
		fTempPerm176 = 0;
		fTempPerm177 = 0;
		fTempPerm178 = 0;
		fTempPerm179 = 0;
		iTempPerm180 = 0;
		fTempPerm181 = 0;
		fTempPerm182 = 0;
		iTempPerm183 = 0;
		fTempPerm184 = 0;
		fTempPerm185 = 0;
		fTempPerm186 = 0;
		fTempPerm187 = 0;
		fTempPerm188 = 0;
		fTempPerm189 = 0;
		fTempPerm190 = 0;
		fTempPerm191 = 0;
		fTempPerm192 = 0;
		fTempPerm193 = 0;
		fTempPerm194 = 0;
		iTempPerm195 = 0;
		fTempPerm196 = 0;
		fTempPerm197 = 0;
		fTempPerm198 = 0;
		fTempPerm199 = 0;
		fTempPerm200 = 0;
		fTempPerm201 = 0;
		fTempPerm202 = 0;
		fTempPerm203 = 0;
		fTempPerm204 = 0;
		fTempPerm205 = 0;
		fTempPerm206 = 0;
		iTempPerm207 = 0;
		fTempPerm208 = 0;
		fTempPerm209 = 0;
		fTempPerm210 = 0;
		fTempPerm211 = 0;
		fTempPerm212 = 0;
		fTempPerm213 = 0;
		iTempPerm214 = 0;
		fTempPerm215 = 0;
		fTempPerm216 = 0;
		iTempPerm217 = 0;
		fTempPerm218 = 0;
		fTempPerm219 = 0;
		fTempPerm220 = 0;
		fTempPerm221 = 0;
		fTempPerm222 = 0;
		fTempPerm223 = 0;
		fTempPerm224 = 0;
		fTempPerm225 = 0;
		fTempPerm226 = 0;
		fTempPerm227 = 0;
		fTempPerm228 = 0;
		iTempPerm229 = 0;
		fTempPerm230 = 0;
		fTempPerm231 = 0;
		fTempPerm232 = 0;
		fTempPerm233 = 0;
		fTempPerm234 = 0;
		fTempPerm235 = 0;
		fTempPerm236 = 0;
		fTempPerm237 = 0;
		fTempPerm238 = 0;
		fTempPerm239 = 0;
		fTempPerm240 = 0;
		iTempPerm241 = 0;
		fTempPerm242 = 0;
		fTempPerm243 = 0;
		fTempPerm244 = 0;
		fTempPerm245 = 0;
		fTempPerm246 = 0;
		fTempPerm247 = 0;
		iTempPerm248 = 0;
		fTempPerm249 = 0;
		fTempPerm250 = 0;
		iTempPerm251 = 0;
		fTempPerm252 = 0;
		fTempPerm253 = 0;
		fTempPerm254 = 0;
		fTempPerm255 = 0;
		fTempPerm256 = 0;
		fTempPerm257 = 0;
		fTempPerm258 = 0;
		fTempPerm259 = 0;
		fTempPerm260 = 0;
		fTempPerm261 = 0;
		fTempPerm262 = 0;
		iTempPerm263 = 0;
		fTempPerm264 = 0;
		fTempPerm265 = 0;
		fTempPerm266 = 0;
		fTempPerm267 = 0;
		fTempPerm268 = 0;
		fTempPerm269 = 0;
		fTempPerm270 = 0;
		fTempPerm271 = 0;
		fTempPerm272 = 0;
		fTempPerm273 = 0;
		fTempPerm274 = 0;
		iTempPerm275 = 0;
		fTempPerm276 = 0;
		fTempPerm277 = 0;
		fTempPerm278 = 0;
		fTempPerm279 = 0;
		fTempPerm280 = 0;
		fTempPerm281 = 0;
		iTempPerm282 = 0;
		fTempPerm283 = 0;
		fTempPerm284 = 0;
		iTempPerm285 = 0;
		fTempPerm286 = 0;
		fTempPerm287 = 0;
		fTempPerm288 = 0;
		fTempPerm289 = 0;
		fTempPerm290 = 0;
		fTempPerm291 = 0;
		fTempPerm292 = 0;
		fTempPerm293 = 0;
		fTempPerm294 = 0;
		fTempPerm295 = 0;
		fTempPerm296 = 0;
		iTempPerm297 = 0;
		fTempPerm298 = 0;
		fTempPerm299 = 0;
		fTempPerm300 = 0;
		fTempPerm301 = 0;
		fTempPerm302 = 0;
		fTempPerm303 = 0;
		fTempPerm304 = 0;
		fTempPerm305 = 0;
		fTempPerm306 = 0;
		fTempPerm307 = 0;
		fTempPerm308 = 0;
		iTempPerm309 = 0;
		fTempPerm310 = 0;
		fTempPerm311 = 0;
		fTempPerm312 = 0;
		fTempPerm313 = 0;
		fTempPerm314 = 0;
		fTempPerm315 = 0;
		iTempPerm316 = 0;
		fTempPerm317 = 0;
		fTempPerm318 = 0;
		iTempPerm319 = 0;
		fTempPerm320 = 0;
		fTempPerm321 = 0;
		fTempPerm322 = 0;
		fTempPerm323 = 0;
		fTempPerm324 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 1.0f;
		fslider2 = 440.0f;
		fslider3 = 0.0f;
		fslider4 = 0.0f;
		fbutton0 = 0.0;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		fslider7 = 1.0f;
		fslider8 = 1.0f;
		fslider9 = 1.0f;
		fslider10 = 0.0f;
		fslider11 = 0.0f;
		fslider12 = 0.0f;
		fslider13 = 0.0f;
		fslider14 = 1.0f;
		fslider15 = 1.0f;
		fslider16 = 0.0f;
		fslider17 = 0.0f;
		fslider18 = 0.0f;
		fslider19 = 0.0f;
		fslider20 = 1.0f;
		fslider21 = 1.0f;
		fslider22 = 0.0f;
		fslider23 = 0.0f;
		fslider24 = 0.0f;
		fslider25 = 0.0f;
		fslider26 = 0.0f;
		fslider27 = 0.001f;
		fslider28 = 0.0f;
		fslider29 = 1.0f;
		fslider30 = 1.0f;
		fslider31 = 1.0f;
		fslider32 = 440.0f;
		fbutton1 = 0.0;
		fslider33 = 1.0f;
		fslider34 = 440.0f;
		fbutton2 = 0.0;
		fslider35 = 1.0f;
		fslider36 = 440.0f;
		fbutton3 = 0.0;
		fslider37 = 1.0f;
		fslider38 = 440.0f;
		fbutton4 = 0.0;
		fslider39 = 1.0f;
		fslider40 = 440.0f;
		fslider41 = 0.0f;
		fslider42 = 0.0f;
		fbutton5 = 0.0;
		fslider43 = 0.0f;
		fslider44 = 0.0f;
		fslider45 = 0.0f;
		fslider46 = 0.0f;
		fslider47 = 0.0f;
		fslider48 = 0.0f;
		fslider49 = 0.0f;
		fslider50 = 1.0f;
		fslider51 = 0.0f;
		fslider52 = 0.0f;
		fslider53 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) iRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) iRec30[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) iRec45[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<2; i++) fRec56[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
		for (int i=0; i<2; i++) fRec57[i] = 0;
		for (int i=0; i<2; i++) fRec58[i] = 0;
		for (int i=0; i<2; i++) iRec60[i] = 0;
		for (int i=0; i<2; i++) fRec59[i] = 0;
		for (int i=0; i<2; i++) fRec61[i] = 0;
		for (int i=0; i<2; i++) fRec63[i] = 0;
		for (int i=0; i<2; i++) fRec62[i] = 0;
		for (int i=0; i<2; i++) fRec64[i] = 0;
		for (int i=0; i<2; i++) fRec65[i] = 0;
		for (int i=0; i<2; i++) fRec67[i] = 0;
		for (int i=0; i<2; i++) fRec66[i] = 0;
		for (int i=0; i<2; i++) fRec68[i] = 0;
		for (int i=0; i<2; i++) fRec69[i] = 0;
		for (int i=0; i<2; i++) fRec71[i] = 0;
		for (int i=0; i<2; i++) fRec70[i] = 0;
		for (int i=0; i<2; i++) fRec72[i] = 0;
		for (int i=0; i<2; i++) fRec73[i] = 0;
		for (int i=0; i<2; i++) iRec75[i] = 0;
		for (int i=0; i<2; i++) fRec74[i] = 0;
		for (int i=0; i<2; i++) fRec76[i] = 0;
		for (int i=0; i<2; i++) iRec78[i] = 0;
		for (int i=0; i<2; i++) fRec77[i] = 0;
		for (int i=0; i<2; i++) fRec79[i] = 0;
		for (int i=0; i<2; i++) fRec80[i] = 0;
		for (int i=0; i<2; i++) fRec81[i] = 0;
		for (int i=0; i<2; i++) fRec82[i] = 0;
		for (int i=0; i<2; i++) fRec83[i] = 0;
		for (int i=0; i<2; i++) fRec84[i] = 0;
		for (int i=0; i<2; i++) fRec86[i] = 0;
		for (int i=0; i<2; i++) fRec85[i] = 0;
		for (int i=0; i<2; i++) fRec87[i] = 0;
		for (int i=0; i<2; i++) fRec89[i] = 0;
		for (int i=0; i<2; i++) fRec88[i] = 0;
		for (int i=0; i<2; i++) fRec90[i] = 0;
		for (int i=0; i<2; i++) fRec92[i] = 0;
		for (int i=0; i<2; i++) fRec91[i] = 0;
		for (int i=0; i<2; i++) fRec93[i] = 0;
		for (int i=0; i<2; i++) fRec95[i] = 0;
		for (int i=0; i<2; i++) fRec94[i] = 0;
		for (int i=0; i<2; i++) fRec96[i] = 0;
		for (int i=0; i<2; i++) fRec97[i] = 0;
		for (int i=0; i<2; i++) fRec98[i] = 0;
		for (int i=0; i<2; i++) fRec100[i] = 0;
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) fRec102[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) fRec104[i] = 0;
		for (int i=0; i<2; i++) fRec106[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) fRec108[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<2; i++) fRec110[i] = 0;
		for (int i=0; i<2; i++) fRec112[i] = 0;
		for (int i=0; i<2; i++) fRec111[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) fRec114[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<2; i++) fRec116[i] = 0;
		for (int i=0; i<2; i++) fRec118[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) fRec120[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<2; i++) fRec122[i] = 0;
		for (int i=0; i<2; i++) fRec124[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
		for (int i=0; i<2; i++) fRec125[i] = 0;
		for (int i=0; i<2; i++) fRec126[i] = 0;
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
	virtual faust_ottofm* clone() {
		return new faust_ottofm();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("ottofm");
		ui_interface->addHorizontalSlider("algN", &fslider0, 0.0f, 0.0f, 11.0f, 1.0f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fslider27, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider25, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider24, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider29, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("fmAmount", &fslider7, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider26, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider23, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider28, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider22, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider52, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider53, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider51, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider30, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider21, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider45, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider44, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider46, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider16, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider18, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider19, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider17, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider20, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider15, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider42, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider41, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider43, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider10, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider12, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider13, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider11, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider14, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider9, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider48, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider47, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider49, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider3, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider5, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider6, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider8, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider1, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v0");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph22, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph24, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph21, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph26, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph20, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph27, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph23, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph25, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v1");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph19, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph30, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph28, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph18, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph29, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph17, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph31, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph16, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v2");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph15, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph34, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph32, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph14, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph33, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph13, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph35, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph12, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v3");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph11, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph38, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph36, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph10, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph37, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph9, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph39, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph8, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v4");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph7, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph42, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph40, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph6, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph41, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph5, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph43, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph4, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v5");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph3, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph46, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph44, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph2, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph45, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph1, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph47, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph0, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider40, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider50, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider38, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider39, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider36, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider37, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider34, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider35, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider32, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider33, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider2, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider31, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fslider0));
		int 	iSlow1 = (float((iSlow0 == 0)) != 0.0f);
		int 	iSlow2 = (float((iSlow0 == 1)) != 0.0f);
		int 	iSlow3 = (float((iSlow0 == 2)) != 0.0f);
		int 	iSlow4 = (float((iSlow0 == 3)) != 0.0f);
		int 	iSlow5 = (float((iSlow0 == 4)) != 0.0f);
		int 	iSlow6 = (float((iSlow0 == 5)) != 0.0f);
		int 	iSlow7 = (float((iSlow0 == 6)) != 0.0f);
		int 	iSlow8 = (float((iSlow0 == 7)) != 0.0f);
		int 	iSlow9 = (float((iSlow0 == 8)) != 0.0f);
		int 	iSlow10 = (float((iSlow0 == 9)) != 0.0f);
		int 	iSlow11 = (float((iSlow0 == 10)) != 0.0f);
		float 	fSlow12 = float(fslider1);
		float 	fSlow13 = float(fslider2);
		float 	fSlow14 = (25.0f * float(fslider3));
		float 	fSlow15 = (fConst1 * (fSlow14 + (fSlow13 * fSlow12)));
		float 	fSlow16 = float(fslider4);
		float 	fSlow17 = float(fbutton0);
		float 	fSlow18 = (fSlow17 * fSlow16);
		float 	fSlow19 = float(fslider5);
		float 	fSlow20 = (fConst2 * fSlow19);
		float 	fSlow21 = float(fslider6);
		float 	fSlow22 = (((1.0f - fSlow16) * fSlow21) + fSlow19);
		float 	fSlow23 = (fConst2 * fSlow22);
		int 	iSlow24 = int(((fSlow17 == 0.0f) > 0));
		float 	fSlow25 = (fSlow22 - fSlow19);
		float 	fSlow26 = (fConst3 * ((fSlow18 + -1.0f) / fSlow25));
		float 	fSlow27 = (fConst3 / fSlow19);
		int 	iSlow28 = (fSlow17 > 0.0f);
		float 	fSlow29 = float(iSlow28);
		int 	iSlow30 = int(iSlow28);
		float 	fSlow31 = max(0.001f, (fConst2 * (fSlow16 * fSlow21)));
		int 	iSlow32 = int((iSlow28 > 0));
		float 	fSlow33 = (1.0f / fSlow31);
		float 	fSlow34 = float(fslider7);
		float 	fSlow35 = float(fslider8);
		float 	fSlow36 = (fSlow35 * fSlow34);
		float 	fSlow37 = float(fslider9);
		float 	fSlow38 = (25.0f * float(fslider10));
		float 	fSlow39 = (fConst1 * (fSlow38 + (fSlow13 * fSlow37)));
		float 	fSlow40 = float(fslider11);
		float 	fSlow41 = (fSlow17 * fSlow40);
		float 	fSlow42 = float(fslider12);
		float 	fSlow43 = (fConst2 * fSlow42);
		float 	fSlow44 = float(fslider13);
		float 	fSlow45 = (((1.0f - fSlow40) * fSlow44) + fSlow42);
		float 	fSlow46 = (fConst2 * fSlow45);
		float 	fSlow47 = (fSlow45 - fSlow42);
		float 	fSlow48 = (fConst3 * ((fSlow41 + -1.0f) / fSlow47));
		float 	fSlow49 = (fConst3 / fSlow42);
		float 	fSlow50 = max(0.001f, (fConst2 * (fSlow40 * fSlow44)));
		float 	fSlow51 = (1.0f / fSlow50);
		float 	fSlow52 = float(fslider14);
		float 	fSlow53 = (fSlow52 * fSlow34);
		float 	fSlow54 = float(fslider15);
		float 	fSlow55 = (25.0f * float(fslider16));
		float 	fSlow56 = (fConst1 * (fSlow55 + (fSlow13 * fSlow54)));
		float 	fSlow57 = float(fslider17);
		float 	fSlow58 = (fSlow17 * fSlow57);
		float 	fSlow59 = float(fslider18);
		float 	fSlow60 = (fConst2 * fSlow59);
		float 	fSlow61 = float(fslider19);
		float 	fSlow62 = (((1.0f - fSlow57) * fSlow61) + fSlow59);
		float 	fSlow63 = (fConst2 * fSlow62);
		float 	fSlow64 = (fSlow62 - fSlow59);
		float 	fSlow65 = (fConst3 * ((fSlow58 + -1.0f) / fSlow64));
		float 	fSlow66 = (fConst3 / fSlow59);
		float 	fSlow67 = max(0.001f, (fConst2 * (fSlow57 * fSlow61)));
		float 	fSlow68 = (1.0f / fSlow67);
		float 	fSlow69 = float(fslider20);
		float 	fSlow70 = (fSlow69 * fSlow34);
		float 	fSlow71 = float(fslider21);
		float 	fSlow72 = (25.0f * float(fslider22));
		float 	fSlow73 = (fConst1 * (fSlow72 + (fSlow13 * fSlow71)));
		float 	fSlow74 = float(fslider24);
		float 	fSlow75 = max((float)0, (fSlow74 + float(fslider23)));
		float 	fSlow76 = float(fslider25);
		float 	fSlow77 = float(fslider27);
		float 	fSlow78 = max((float)0, (fSlow77 + float(fslider26)));
		float 	fSlow79 = (6.9100000000000001f * fSlow78);
		int 	iSlow80 = int((fConst0 * fSlow78));
		float 	fSlow81 = float(fslider29);
		float 	fSlow82 = max((float)0, (fSlow81 + (0.5f * float(fslider28))));
		float 	fSlow83 = (fSlow29 * fSlow82);
		float 	fSlow84 = float(fslider30);
		float 	fSlow85 = float(fslider31);
		float 	fSlow86 = (fSlow85 * fSlow84);
		float 	fSlow87 = float(fslider32);
		float 	fSlow88 = (fConst1 * (fSlow14 + (fSlow87 * fSlow12)));
		float 	fSlow89 = float(fbutton1);
		float 	fSlow90 = (fSlow89 * fSlow16);
		int 	iSlow91 = int(((fSlow89 == 0.0f) > 0));
		float 	fSlow92 = (fConst3 * ((fSlow90 + -1.0f) / fSlow25));
		int 	iSlow93 = (fSlow89 > 0.0f);
		float 	fSlow94 = float(iSlow93);
		int 	iSlow95 = int(iSlow93);
		int 	iSlow96 = int((iSlow93 > 0));
		float 	fSlow97 = (fConst1 * (fSlow38 + (fSlow87 * fSlow37)));
		float 	fSlow98 = (fSlow89 * fSlow40);
		float 	fSlow99 = (fConst3 * ((fSlow98 + -1.0f) / fSlow47));
		float 	fSlow100 = (fConst1 * (fSlow55 + (fSlow87 * fSlow54)));
		float 	fSlow101 = (fSlow89 * fSlow57);
		float 	fSlow102 = (fConst3 * ((fSlow101 + -1.0f) / fSlow64));
		float 	fSlow103 = (fConst1 * (fSlow72 + (fSlow87 * fSlow71)));
		float 	fSlow104 = (fSlow94 * fSlow82);
		float 	fSlow105 = float(fslider33);
		float 	fSlow106 = (fSlow84 * fSlow105);
		float 	fSlow107 = float(fslider34);
		float 	fSlow108 = (fConst1 * (fSlow14 + (fSlow107 * fSlow12)));
		float 	fSlow109 = float(fbutton2);
		float 	fSlow110 = (fSlow109 * fSlow16);
		int 	iSlow111 = int(((fSlow109 == 0.0f) > 0));
		float 	fSlow112 = (fConst3 * ((fSlow110 + -1.0f) / fSlow25));
		int 	iSlow113 = (fSlow109 > 0.0f);
		float 	fSlow114 = float(iSlow113);
		int 	iSlow115 = int(iSlow113);
		int 	iSlow116 = int((iSlow113 > 0));
		float 	fSlow117 = (fConst1 * (fSlow38 + (fSlow107 * fSlow37)));
		float 	fSlow118 = (fSlow109 * fSlow40);
		float 	fSlow119 = (fConst3 * ((fSlow118 + -1.0f) / fSlow47));
		float 	fSlow120 = (fConst1 * (fSlow55 + (fSlow107 * fSlow54)));
		float 	fSlow121 = (fSlow109 * fSlow57);
		float 	fSlow122 = (fConst3 * ((fSlow121 + -1.0f) / fSlow64));
		float 	fSlow123 = (fConst1 * (fSlow72 + (fSlow107 * fSlow71)));
		float 	fSlow124 = (fSlow114 * fSlow82);
		float 	fSlow125 = float(fslider35);
		float 	fSlow126 = (fSlow84 * fSlow125);
		float 	fSlow127 = float(fslider36);
		float 	fSlow128 = (fConst1 * (fSlow14 + (fSlow127 * fSlow12)));
		float 	fSlow129 = float(fbutton3);
		float 	fSlow130 = (fSlow129 * fSlow16);
		int 	iSlow131 = int(((fSlow129 == 0.0f) > 0));
		float 	fSlow132 = (fConst3 * ((fSlow130 + -1.0f) / fSlow25));
		int 	iSlow133 = (fSlow129 > 0.0f);
		float 	fSlow134 = float(iSlow133);
		int 	iSlow135 = int(iSlow133);
		int 	iSlow136 = int((iSlow133 > 0));
		float 	fSlow137 = (fConst1 * (fSlow38 + (fSlow127 * fSlow37)));
		float 	fSlow138 = (fSlow129 * fSlow40);
		float 	fSlow139 = (fConst3 * ((fSlow138 + -1.0f) / fSlow47));
		float 	fSlow140 = (fConst1 * (fSlow55 + (fSlow127 * fSlow54)));
		float 	fSlow141 = (fSlow129 * fSlow57);
		float 	fSlow142 = (fConst3 * ((fSlow141 + -1.0f) / fSlow64));
		float 	fSlow143 = (fConst1 * (fSlow72 + (fSlow127 * fSlow71)));
		float 	fSlow144 = (fSlow134 * fSlow82);
		float 	fSlow145 = float(fslider37);
		float 	fSlow146 = (fSlow84 * fSlow145);
		float 	fSlow147 = float(fslider38);
		float 	fSlow148 = (fConst1 * (fSlow14 + (fSlow147 * fSlow12)));
		float 	fSlow149 = float(fbutton4);
		float 	fSlow150 = (fSlow149 * fSlow16);
		int 	iSlow151 = int(((fSlow149 == 0.0f) > 0));
		float 	fSlow152 = (fConst3 * ((fSlow150 + -1.0f) / fSlow25));
		int 	iSlow153 = (fSlow149 > 0.0f);
		float 	fSlow154 = float(iSlow153);
		int 	iSlow155 = int(iSlow153);
		int 	iSlow156 = int((iSlow153 > 0));
		float 	fSlow157 = (fConst1 * (fSlow38 + (fSlow147 * fSlow37)));
		float 	fSlow158 = (fSlow149 * fSlow40);
		float 	fSlow159 = (fConst3 * ((fSlow158 + -1.0f) / fSlow47));
		float 	fSlow160 = (fConst1 * (fSlow55 + (fSlow147 * fSlow54)));
		float 	fSlow161 = (fSlow149 * fSlow57);
		float 	fSlow162 = (fConst3 * ((fSlow161 + -1.0f) / fSlow64));
		float 	fSlow163 = (fConst1 * (fSlow72 + (fSlow147 * fSlow71)));
		float 	fSlow164 = (fSlow154 * fSlow82);
		float 	fSlow165 = float(fslider39);
		float 	fSlow166 = (fSlow84 * fSlow165);
		float 	fSlow167 = float(fslider40);
		float 	fSlow168 = (fConst1 * ((fSlow167 * fSlow37) + fSlow38));
		float 	fSlow169 = max((float)0, (fSlow74 + float(fslider41)));
		float 	fSlow170 = max((float)0, (fSlow77 + float(fslider42)));
		float 	fSlow171 = (6.9100000000000001f * fSlow170);
		int 	iSlow172 = int((fConst0 * fSlow170));
		float 	fSlow173 = float(fbutton5);
		int 	iSlow174 = (fSlow173 > 0.0f);
		int 	iSlow175 = int(iSlow174);
		float 	fSlow176 = max((float)0, (fSlow81 + (0.5f * float(fslider43))));
		float 	fSlow177 = float(iSlow174);
		float 	fSlow178 = (fSlow177 * fSlow176);
		float 	fSlow179 = (fConst1 * ((fSlow167 * fSlow54) + fSlow55));
		float 	fSlow180 = max((float)0, (fSlow74 + float(fslider44)));
		float 	fSlow181 = max((float)0, (fSlow77 + float(fslider45)));
		float 	fSlow182 = (6.9100000000000001f * fSlow181);
		int 	iSlow183 = int((fConst0 * fSlow181));
		float 	fSlow184 = max((float)0, (fSlow81 + (0.5f * float(fslider46))));
		float 	fSlow185 = (fSlow177 * fSlow184);
		float 	fSlow186 = (fConst1 * ((fSlow167 * fSlow71) + fSlow72));
		float 	fSlow187 = (fSlow177 * fSlow82);
		float 	fSlow188 = (fConst1 * ((fSlow167 * fSlow12) + fSlow14));
		float 	fSlow189 = max((float)0, (fSlow74 + float(fslider47)));
		float 	fSlow190 = max((float)0, (fSlow77 + float(fslider48)));
		float 	fSlow191 = (6.9100000000000001f * fSlow190);
		int 	iSlow192 = int((fConst0 * fSlow190));
		float 	fSlow193 = max((float)0, (fSlow81 + (0.5f * float(fslider49))));
		float 	fSlow194 = (fSlow177 * fSlow193);
		float 	fSlow195 = float(fslider50);
		float 	fSlow196 = float(fslider51);
		float 	fSlow197 = (fSlow173 * fSlow196);
		float 	fSlow198 = float(fslider52);
		float 	fSlow199 = (fConst2 * fSlow198);
		float 	fSlow200 = float(fslider53);
		float 	fSlow201 = (((1.0f - fSlow196) * fSlow200) + fSlow198);
		float 	fSlow202 = (fConst2 * fSlow201);
		int 	iSlow203 = int(((fSlow173 == 0.0f) > 0));
		float 	fSlow204 = (fSlow201 - fSlow198);
		float 	fSlow205 = (fConst3 * ((fSlow197 + -1.0f) / fSlow204));
		float 	fSlow206 = (fConst3 / fSlow198);
		float 	fSlow207 = max(0.001f, (fConst2 * (fSlow196 * fSlow200)));
		int 	iSlow208 = int((iSlow174 > 0));
		float 	fSlow209 = (1.0f / fSlow207);
		float 	fSlow210 = (fSlow84 * fSlow34);
		float 	fSlow211 = (fSlow173 * fSlow16);
		float 	fSlow212 = (fConst3 * ((fSlow211 + -1.0f) / fSlow25));
		float 	fSlow213 = (fSlow173 * fSlow57);
		float 	fSlow214 = (fConst3 * ((fSlow213 + -1.0f) / fSlow64));
		float 	fSlow215 = (fSlow173 * fSlow40);
		float 	fSlow216 = (fConst3 * ((fSlow215 + -1.0f) / fSlow47));
		float 	fSlow217 = (fSlow84 * fSlow195);
		float 	fSlow218 = (fSlow154 * fSlow184);
		float 	fSlow219 = (fSlow154 * fSlow176);
		float 	fSlow220 = (fSlow149 * fSlow196);
		float 	fSlow221 = (fConst3 * ((fSlow220 + -1.0f) / fSlow204));
		float 	fSlow222 = (fSlow154 * fSlow193);
		float 	fSlow223 = (fSlow134 * fSlow184);
		float 	fSlow224 = (fSlow134 * fSlow176);
		float 	fSlow225 = (fSlow129 * fSlow196);
		float 	fSlow226 = (fConst3 * ((fSlow225 + -1.0f) / fSlow204));
		float 	fSlow227 = (fSlow134 * fSlow193);
		float 	fSlow228 = (fSlow114 * fSlow184);
		float 	fSlow229 = (fSlow114 * fSlow176);
		float 	fSlow230 = (fSlow109 * fSlow196);
		float 	fSlow231 = (fConst3 * ((fSlow230 + -1.0f) / fSlow204));
		float 	fSlow232 = (fSlow114 * fSlow193);
		float 	fSlow233 = (fSlow94 * fSlow184);
		float 	fSlow234 = (fSlow94 * fSlow176);
		float 	fSlow235 = (fSlow89 * fSlow196);
		float 	fSlow236 = (fConst3 * ((fSlow235 + -1.0f) / fSlow204));
		float 	fSlow237 = (fSlow94 * fSlow193);
		float 	fSlow238 = (fSlow29 * fSlow184);
		float 	fSlow239 = (fSlow29 * fSlow176);
		float 	fSlow240 = (fSlow17 * fSlow196);
		float 	fSlow241 = (fConst3 * ((fSlow240 + -1.0f) / fSlow204));
		float 	fSlow242 = (fSlow29 * fSlow193);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec1[0] = (fSlow15 + (fRec1[1] - floorf((fSlow15 + fRec1[1]))));
				fTempPerm1 = ftbl0[(((int((65536.0f * fRec1[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec3[0] = ((iSlow24)?0.0f:min(fSlow23, (fRec3[1] + 1.0f)));
				iTempPerm2 = int((fRec3[0] < fSlow20));
				fRec2[0] = ((iSlow30)?(fSlow29 * ((iTempPerm2)?((int((fRec3[0] < 0.0f)))?0.0f:((iTempPerm2)?(fSlow27 * fRec3[0]):1.0f)):((int((fRec3[0] < fSlow23)))?((fSlow26 * (fRec3[0] - fSlow20)) + 1.0f):fSlow18))):fRec2[1]);
				fRec4[0] = ((iSlow32)?0.0f:min(fSlow31, (fRec4[1] + 1.0f)));
				fTempPerm3 = ((int((fRec4[0] < 0.0f)))?fRec2[0]:((int((fRec4[0] < fSlow31)))?(fRec2[0] + (fSlow33 * (0 - (fRec4[0] * fRec2[0])))):0.0f));
				fbargraph0 = fTempPerm3;
				fTempPerm4 = (fTempPerm3 * fTempPerm1);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm5 = (fSlow36 * fTempPerm4);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec5[0] = (fSlow39 + (fRec5[1] - floorf((fSlow39 + fRec5[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm6 = ftbl0[(((int((65536.0f * (fRec5[0] + fTempPerm5))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec7[0] = ((iSlow24)?0.0f:min(fSlow46, (fRec7[1] + 1.0f)));
				iTempPerm7 = int((fRec7[0] < fSlow43));
				fRec6[0] = ((iSlow30)?(fSlow29 * ((iTempPerm7)?((int((fRec7[0] < 0.0f)))?0.0f:((iTempPerm7)?(fSlow49 * fRec7[0]):1.0f)):((int((fRec7[0] < fSlow46)))?((fSlow48 * (fRec7[0] - fSlow43)) + 1.0f):fSlow41))):fRec6[1]);
				fRec8[0] = ((iSlow32)?0.0f:min(fSlow50, (fRec8[1] + 1.0f)));
				fTempPerm8 = ((int((fRec8[0] < 0.0f)))?fRec6[0]:((int((fRec8[0] < fSlow50)))?(fRec6[0] + (fSlow51 * (0 - (fRec8[0] * fRec6[0])))):0.0f));
				fbargraph1 = fTempPerm8;
				fTempPerm9 = fTempPerm8;
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm10 = (fTempPerm9 * fTempPerm6);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm11 = (fSlow53 * fTempPerm10);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec9[0] = (fSlow56 + (fRec9[1] - floorf((fSlow56 + fRec9[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm12 = ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm11))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec11[0] = ((iSlow24)?0.0f:min(fSlow63, (fRec11[1] + 1.0f)));
				iTempPerm13 = int((fRec11[0] < fSlow60));
				fRec10[0] = ((iSlow30)?(fSlow29 * ((iTempPerm13)?((int((fRec11[0] < 0.0f)))?0.0f:((iTempPerm13)?(fSlow66 * fRec11[0]):1.0f)):((int((fRec11[0] < fSlow63)))?((fSlow65 * (fRec11[0] - fSlow60)) + 1.0f):fSlow58))):fRec10[1]);
				fRec12[0] = ((iSlow32)?0.0f:min(fSlow67, (fRec12[1] + 1.0f)));
				fTempPerm14 = ((int((fRec12[0] < 0.0f)))?fRec10[0]:((int((fRec12[0] < fSlow67)))?(fRec10[0] + (fSlow68 * (0 - (fRec12[0] * fRec10[0])))):0.0f));
				fbargraph2 = fTempPerm14;
				fTempPerm15 = fTempPerm14;
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec13[0] = (fSlow73 + (fRec13[1] - floorf((fSlow73 + fRec13[1]))));
				iRec15[0] = (iSlow28 * (iRec15[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm16 = int((iRec15[0] < iSlow80));
				fTempPerm17 = expf((0 - (fConst4 / ((iSlow30)?((iTempPerm16)?fSlow79:fSlow76):fSlow75))));
				fRec14[0] = ((fRec14[1] * fTempPerm17) + (((iSlow30)?((iTempPerm16)?1.5873015873015872f:fSlow83):0.0f) * (1.0f - fTempPerm17)));
				fTempPerm18 = min(1.0f, fRec14[0]);
				fbargraph3 = fTempPerm18;
				fTempPerm19 = fTempPerm18;
			}
			if (iSlow2 || iSlow1) {
				fTempPerm20 = (fSlow86 * (fTempPerm19 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow70 * (fTempPerm15 * fTempPerm12))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec16[0] = (fSlow88 + (fRec16[1] - floorf((fSlow88 + fRec16[1]))));
				fTempPerm21 = ftbl0[(((int((65536.0f * fRec16[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec18[0] = ((iSlow91)?0.0f:min(fSlow23, (fRec18[1] + 1.0f)));
				iTempPerm22 = int((fRec18[0] < fSlow20));
				fRec17[0] = ((iSlow95)?(fSlow94 * ((iTempPerm22)?((int((fRec18[0] < 0.0f)))?0.0f:((iTempPerm22)?(fSlow27 * fRec18[0]):1.0f)):((int((fRec18[0] < fSlow23)))?((fSlow92 * (fRec18[0] - fSlow20)) + 1.0f):fSlow90))):fRec17[1]);
				fRec19[0] = ((iSlow96)?0.0f:min(fSlow31, (fRec19[1] + 1.0f)));
				fTempPerm23 = ((int((fRec19[0] < 0.0f)))?fRec17[0]:((int((fRec19[0] < fSlow31)))?(fRec17[0] + (fSlow33 * (0 - (fRec19[0] * fRec17[0])))):0.0f));
				fbargraph4 = fTempPerm23;
				fTempPerm24 = (fTempPerm23 * fTempPerm21);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm25 = (fSlow36 * fTempPerm24);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec20[0] = (fSlow97 + (fRec20[1] - floorf((fSlow97 + fRec20[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm26 = ftbl0[(((int((65536.0f * (fRec20[0] + fTempPerm25))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec22[0] = ((iSlow91)?0.0f:min(fSlow46, (fRec22[1] + 1.0f)));
				iTempPerm27 = int((fRec22[0] < fSlow43));
				fRec21[0] = ((iSlow95)?(fSlow94 * ((iTempPerm27)?((int((fRec22[0] < 0.0f)))?0.0f:((iTempPerm27)?(fSlow49 * fRec22[0]):1.0f)):((int((fRec22[0] < fSlow46)))?((fSlow99 * (fRec22[0] - fSlow43)) + 1.0f):fSlow98))):fRec21[1]);
				fRec23[0] = ((iSlow96)?0.0f:min(fSlow50, (fRec23[1] + 1.0f)));
				fTempPerm28 = ((int((fRec23[0] < 0.0f)))?fRec21[0]:((int((fRec23[0] < fSlow50)))?(fRec21[0] + (fSlow51 * (0 - (fRec23[0] * fRec21[0])))):0.0f));
				fbargraph5 = fTempPerm28;
				fTempPerm29 = fTempPerm28;
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm30 = (fTempPerm29 * fTempPerm26);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm31 = (fSlow53 * fTempPerm30);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec24[0] = (fSlow100 + (fRec24[1] - floorf((fSlow100 + fRec24[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm32 = ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm31))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec26[0] = ((iSlow91)?0.0f:min(fSlow63, (fRec26[1] + 1.0f)));
				iTempPerm33 = int((fRec26[0] < fSlow60));
				fRec25[0] = ((iSlow95)?(fSlow94 * ((iTempPerm33)?((int((fRec26[0] < 0.0f)))?0.0f:((iTempPerm33)?(fSlow66 * fRec26[0]):1.0f)):((int((fRec26[0] < fSlow63)))?((fSlow102 * (fRec26[0] - fSlow60)) + 1.0f):fSlow101))):fRec25[1]);
				fRec27[0] = ((iSlow96)?0.0f:min(fSlow67, (fRec27[1] + 1.0f)));
				fTempPerm34 = ((int((fRec27[0] < 0.0f)))?fRec25[0]:((int((fRec27[0] < fSlow67)))?(fRec25[0] + (fSlow68 * (0 - (fRec27[0] * fRec25[0])))):0.0f));
				fbargraph6 = fTempPerm34;
				fTempPerm35 = fTempPerm34;
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec28[0] = (fSlow103 + (fRec28[1] - floorf((fSlow103 + fRec28[1]))));
				iRec30[0] = (iSlow93 * (iRec30[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm36 = int((iRec30[0] < iSlow80));
				fTempPerm37 = expf((0 - (fConst4 / ((iSlow95)?((iTempPerm36)?fSlow79:fSlow76):fSlow75))));
				fRec29[0] = ((fRec29[1] * fTempPerm37) + (((iSlow95)?((iTempPerm36)?1.5873015873015872f:fSlow104):0.0f) * (1.0f - fTempPerm37)));
				fTempPerm38 = min(1.0f, fRec29[0]);
				fbargraph7 = fTempPerm38;
				fTempPerm39 = fTempPerm38;
			}
			if (iSlow2 || iSlow1) {
				fTempPerm40 = (fSlow106 * (fTempPerm39 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow70 * (fTempPerm35 * fTempPerm32))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec31[0] = (fSlow108 + (fRec31[1] - floorf((fSlow108 + fRec31[1]))));
				fTempPerm41 = ftbl0[(((int((65536.0f * fRec31[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec33[0] = ((iSlow111)?0.0f:min(fSlow23, (fRec33[1] + 1.0f)));
				iTempPerm42 = int((fRec33[0] < fSlow20));
				fRec32[0] = ((iSlow115)?(fSlow114 * ((iTempPerm42)?((int((fRec33[0] < 0.0f)))?0.0f:((iTempPerm42)?(fSlow27 * fRec33[0]):1.0f)):((int((fRec33[0] < fSlow23)))?((fSlow112 * (fRec33[0] - fSlow20)) + 1.0f):fSlow110))):fRec32[1]);
				fRec34[0] = ((iSlow116)?0.0f:min(fSlow31, (fRec34[1] + 1.0f)));
				fTempPerm43 = ((int((fRec34[0] < 0.0f)))?fRec32[0]:((int((fRec34[0] < fSlow31)))?(fRec32[0] + (fSlow33 * (0 - (fRec34[0] * fRec32[0])))):0.0f));
				fbargraph8 = fTempPerm43;
				fTempPerm44 = (fTempPerm43 * fTempPerm41);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm45 = (fSlow36 * fTempPerm44);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec35[0] = (fSlow117 + (fRec35[1] - floorf((fSlow117 + fRec35[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm46 = ftbl0[(((int((65536.0f * (fRec35[0] + fTempPerm45))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec37[0] = ((iSlow111)?0.0f:min(fSlow46, (fRec37[1] + 1.0f)));
				iTempPerm47 = int((fRec37[0] < fSlow43));
				fRec36[0] = ((iSlow115)?(fSlow114 * ((iTempPerm47)?((int((fRec37[0] < 0.0f)))?0.0f:((iTempPerm47)?(fSlow49 * fRec37[0]):1.0f)):((int((fRec37[0] < fSlow46)))?((fSlow119 * (fRec37[0] - fSlow43)) + 1.0f):fSlow118))):fRec36[1]);
				fRec38[0] = ((iSlow116)?0.0f:min(fSlow50, (fRec38[1] + 1.0f)));
				fTempPerm48 = ((int((fRec38[0] < 0.0f)))?fRec36[0]:((int((fRec38[0] < fSlow50)))?(fRec36[0] + (fSlow51 * (0 - (fRec38[0] * fRec36[0])))):0.0f));
				fbargraph9 = fTempPerm48;
				fTempPerm49 = fTempPerm48;
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm50 = (fTempPerm49 * fTempPerm46);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm51 = (fSlow53 * fTempPerm50);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec39[0] = (fSlow120 + (fRec39[1] - floorf((fSlow120 + fRec39[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm52 = ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm51))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec41[0] = ((iSlow111)?0.0f:min(fSlow63, (fRec41[1] + 1.0f)));
				iTempPerm53 = int((fRec41[0] < fSlow60));
				fRec40[0] = ((iSlow115)?(fSlow114 * ((iTempPerm53)?((int((fRec41[0] < 0.0f)))?0.0f:((iTempPerm53)?(fSlow66 * fRec41[0]):1.0f)):((int((fRec41[0] < fSlow63)))?((fSlow122 * (fRec41[0] - fSlow60)) + 1.0f):fSlow121))):fRec40[1]);
				fRec42[0] = ((iSlow116)?0.0f:min(fSlow67, (fRec42[1] + 1.0f)));
				fTempPerm54 = ((int((fRec42[0] < 0.0f)))?fRec40[0]:((int((fRec42[0] < fSlow67)))?(fRec40[0] + (fSlow68 * (0 - (fRec42[0] * fRec40[0])))):0.0f));
				fbargraph10 = fTempPerm54;
				fTempPerm55 = fTempPerm54;
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec43[0] = (fSlow123 + (fRec43[1] - floorf((fSlow123 + fRec43[1]))));
				iRec45[0] = (iSlow113 * (iRec45[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm56 = int((iRec45[0] < iSlow80));
				fTempPerm57 = expf((0 - (fConst4 / ((iSlow115)?((iTempPerm56)?fSlow79:fSlow76):fSlow75))));
				fRec44[0] = ((fRec44[1] * fTempPerm57) + (((iSlow115)?((iTempPerm56)?1.5873015873015872f:fSlow124):0.0f) * (1.0f - fTempPerm57)));
				fTempPerm58 = min(1.0f, fRec44[0]);
				fbargraph11 = fTempPerm58;
				fTempPerm59 = fTempPerm58;
			}
			if (iSlow2 || iSlow1) {
				fTempPerm60 = (fSlow126 * (fTempPerm59 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow70 * (fTempPerm55 * fTempPerm52))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec46[0] = (fSlow128 + (fRec46[1] - floorf((fSlow128 + fRec46[1]))));
				fTempPerm61 = ftbl0[(((int((65536.0f * fRec46[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec48[0] = ((iSlow131)?0.0f:min(fSlow23, (fRec48[1] + 1.0f)));
				iTempPerm62 = int((fRec48[0] < fSlow20));
				fRec47[0] = ((iSlow135)?(fSlow134 * ((iTempPerm62)?((int((fRec48[0] < 0.0f)))?0.0f:((iTempPerm62)?(fSlow27 * fRec48[0]):1.0f)):((int((fRec48[0] < fSlow23)))?((fSlow132 * (fRec48[0] - fSlow20)) + 1.0f):fSlow130))):fRec47[1]);
				fRec49[0] = ((iSlow136)?0.0f:min(fSlow31, (fRec49[1] + 1.0f)));
				fTempPerm63 = ((int((fRec49[0] < 0.0f)))?fRec47[0]:((int((fRec49[0] < fSlow31)))?(fRec47[0] + (fSlow33 * (0 - (fRec49[0] * fRec47[0])))):0.0f));
				fbargraph12 = fTempPerm63;
				fTempPerm64 = (fTempPerm63 * fTempPerm61);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm65 = (fSlow36 * fTempPerm64);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec50[0] = (fSlow137 + (fRec50[1] - floorf((fSlow137 + fRec50[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm66 = ftbl0[(((int((65536.0f * (fRec50[0] + fTempPerm65))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec52[0] = ((iSlow131)?0.0f:min(fSlow46, (fRec52[1] + 1.0f)));
				iTempPerm67 = int((fRec52[0] < fSlow43));
				fRec51[0] = ((iSlow135)?(fSlow134 * ((iTempPerm67)?((int((fRec52[0] < 0.0f)))?0.0f:((iTempPerm67)?(fSlow49 * fRec52[0]):1.0f)):((int((fRec52[0] < fSlow46)))?((fSlow139 * (fRec52[0] - fSlow43)) + 1.0f):fSlow138))):fRec51[1]);
				fRec53[0] = ((iSlow136)?0.0f:min(fSlow50, (fRec53[1] + 1.0f)));
				fTempPerm68 = ((int((fRec53[0] < 0.0f)))?fRec51[0]:((int((fRec53[0] < fSlow50)))?(fRec51[0] + (fSlow51 * (0 - (fRec53[0] * fRec51[0])))):0.0f));
				fbargraph13 = fTempPerm68;
				fTempPerm69 = fTempPerm68;
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm70 = (fTempPerm69 * fTempPerm66);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm71 = (fSlow53 * fTempPerm70);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec54[0] = (fSlow140 + (fRec54[1] - floorf((fSlow140 + fRec54[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm72 = ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm71))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec56[0] = ((iSlow131)?0.0f:min(fSlow63, (fRec56[1] + 1.0f)));
				iTempPerm73 = int((fRec56[0] < fSlow60));
				fRec55[0] = ((iSlow135)?(fSlow134 * ((iTempPerm73)?((int((fRec56[0] < 0.0f)))?0.0f:((iTempPerm73)?(fSlow66 * fRec56[0]):1.0f)):((int((fRec56[0] < fSlow63)))?((fSlow142 * (fRec56[0] - fSlow60)) + 1.0f):fSlow141))):fRec55[1]);
				fRec57[0] = ((iSlow136)?0.0f:min(fSlow67, (fRec57[1] + 1.0f)));
				fTempPerm74 = ((int((fRec57[0] < 0.0f)))?fRec55[0]:((int((fRec57[0] < fSlow67)))?(fRec55[0] + (fSlow68 * (0 - (fRec57[0] * fRec55[0])))):0.0f));
				fbargraph14 = fTempPerm74;
				fTempPerm75 = fTempPerm74;
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec58[0] = (fSlow143 + (fRec58[1] - floorf((fSlow143 + fRec58[1]))));
				iRec60[0] = (iSlow133 * (iRec60[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm76 = int((iRec60[0] < iSlow80));
				fTempPerm77 = expf((0 - (fConst4 / ((iSlow135)?((iTempPerm76)?fSlow79:fSlow76):fSlow75))));
				fRec59[0] = ((fRec59[1] * fTempPerm77) + (((iSlow135)?((iTempPerm76)?1.5873015873015872f:fSlow144):0.0f) * (1.0f - fTempPerm77)));
				fTempPerm78 = min(1.0f, fRec59[0]);
				fbargraph15 = fTempPerm78;
				fTempPerm79 = fTempPerm78;
			}
			if (iSlow2 || iSlow1) {
				fTempPerm80 = (fSlow146 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow70 * (fTempPerm75 * fTempPerm72))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec61[0] = (fSlow148 + (fRec61[1] - floorf((fSlow148 + fRec61[1]))));
				fTempPerm81 = ftbl0[(((int((65536.0f * fRec61[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec63[0] = ((iSlow151)?0.0f:min(fSlow23, (fRec63[1] + 1.0f)));
				iTempPerm82 = int((fRec63[0] < fSlow20));
				fRec62[0] = ((iSlow155)?(fSlow154 * ((iTempPerm82)?((int((fRec63[0] < 0.0f)))?0.0f:((iTempPerm82)?(fSlow27 * fRec63[0]):1.0f)):((int((fRec63[0] < fSlow23)))?((fSlow152 * (fRec63[0] - fSlow20)) + 1.0f):fSlow150))):fRec62[1]);
				fRec64[0] = ((iSlow156)?0.0f:min(fSlow31, (fRec64[1] + 1.0f)));
				fTempPerm83 = ((int((fRec64[0] < 0.0f)))?fRec62[0]:((int((fRec64[0] < fSlow31)))?(fRec62[0] + (fSlow33 * (0 - (fRec64[0] * fRec62[0])))):0.0f));
				fbargraph16 = fTempPerm83;
				fTempPerm84 = (fTempPerm83 * fTempPerm81);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm85 = (fSlow36 * fTempPerm84);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec65[0] = (fSlow157 + (fRec65[1] - floorf((fSlow157 + fRec65[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm86 = ftbl0[(((int((65536.0f * (fRec65[0] + fTempPerm85))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec67[0] = ((iSlow151)?0.0f:min(fSlow46, (fRec67[1] + 1.0f)));
				iTempPerm87 = int((fRec67[0] < fSlow43));
				fRec66[0] = ((iSlow155)?(fSlow154 * ((iTempPerm87)?((int((fRec67[0] < 0.0f)))?0.0f:((iTempPerm87)?(fSlow49 * fRec67[0]):1.0f)):((int((fRec67[0] < fSlow46)))?((fSlow159 * (fRec67[0] - fSlow43)) + 1.0f):fSlow158))):fRec66[1]);
				fRec68[0] = ((iSlow156)?0.0f:min(fSlow50, (fRec68[1] + 1.0f)));
				fTempPerm88 = ((int((fRec68[0] < 0.0f)))?fRec66[0]:((int((fRec68[0] < fSlow50)))?(fRec66[0] + (fSlow51 * (0 - (fRec68[0] * fRec66[0])))):0.0f));
				fbargraph17 = fTempPerm88;
				fTempPerm89 = fTempPerm88;
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm90 = (fTempPerm89 * fTempPerm86);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm91 = (fSlow53 * fTempPerm90);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec69[0] = (fSlow160 + (fRec69[1] - floorf((fSlow160 + fRec69[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm92 = ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm91))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec71[0] = ((iSlow151)?0.0f:min(fSlow63, (fRec71[1] + 1.0f)));
				iTempPerm93 = int((fRec71[0] < fSlow60));
				fRec70[0] = ((iSlow155)?(fSlow154 * ((iTempPerm93)?((int((fRec71[0] < 0.0f)))?0.0f:((iTempPerm93)?(fSlow66 * fRec71[0]):1.0f)):((int((fRec71[0] < fSlow63)))?((fSlow162 * (fRec71[0] - fSlow60)) + 1.0f):fSlow161))):fRec70[1]);
				fRec72[0] = ((iSlow156)?0.0f:min(fSlow67, (fRec72[1] + 1.0f)));
				fTempPerm94 = ((int((fRec72[0] < 0.0f)))?fRec70[0]:((int((fRec72[0] < fSlow67)))?(fRec70[0] + (fSlow68 * (0 - (fRec72[0] * fRec70[0])))):0.0f));
				fbargraph18 = fTempPerm94;
				fTempPerm95 = fTempPerm94;
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec73[0] = (fSlow163 + (fRec73[1] - floorf((fSlow163 + fRec73[1]))));
				iRec75[0] = (iSlow153 * (iRec75[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm96 = int((iRec75[0] < iSlow80));
				fTempPerm97 = expf((0 - (fConst4 / ((iSlow155)?((iTempPerm96)?fSlow79:fSlow76):fSlow75))));
				fRec74[0] = ((fRec74[1] * fTempPerm97) + (((iSlow155)?((iTempPerm96)?1.5873015873015872f:fSlow164):0.0f) * (1.0f - fTempPerm97)));
				fTempPerm98 = min(1.0f, fRec74[0]);
				fbargraph19 = fTempPerm98;
				fTempPerm99 = fTempPerm98;
			}
			if (iSlow2 || iSlow1) {
				fTempPerm100 = (fSlow166 * (fTempPerm99 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow70 * (fTempPerm95 * fTempPerm92))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec76[0] = (fSlow168 + (fRec76[1] - floorf((fSlow168 + fRec76[1]))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm101 = ftbl0[(((int((65536.0f * fRec76[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec78[0] = (iSlow174 * (iRec78[1] + 1));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm102 = int((iRec78[0] < iSlow172));
				fTempPerm103 = expf((0 - (fConst4 / ((iSlow175)?((iTempPerm102)?fSlow171:fSlow76):fSlow169))));
				fRec77[0] = ((fRec77[1] * fTempPerm103) + (((iSlow175)?((iTempPerm102)?1.5873015873015872f:fSlow178):0.0f) * (1.0f - fTempPerm103)));
				fTempPerm104 = min(1.0f, fRec77[0]);
				fbargraph20 = fTempPerm104;
				fTempPerm105 = fTempPerm104;
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec79[0] = (fSlow179 + (fRec79[1] - floorf((fSlow179 + fRec79[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm106 = ftbl0[(((int((65536.0f * fRec79[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm107 = int((iRec78[0] < iSlow183));
				fTempPerm108 = expf((0 - (fConst4 / ((iSlow175)?((iTempPerm107)?fSlow182:fSlow76):fSlow180))));
				fRec80[0] = ((fRec80[1] * fTempPerm108) + (((iSlow175)?((iTempPerm107)?1.5873015873015872f:fSlow185):0.0f) * (1.0f - fTempPerm108)));
				fTempPerm109 = min(1.0f, fRec80[0]);
				fbargraph21 = fTempPerm109;
				fTempPerm110 = fTempPerm109;
			}
			if (iSlow11 || iSlow10) {
				fTempPerm111 = (fSlow69 * (fTempPerm110 * fTempPerm106));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec81[0] = (fSlow186 + (fRec81[1] - floorf((fSlow186 + fRec81[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm112 = ftbl0[(((int((65536.0f * fRec81[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm113 = int((iRec78[0] < iSlow80));
				fTempPerm114 = expf((0 - (fConst4 / ((iSlow175)?((iTempPerm113)?fSlow79:fSlow76):fSlow75))));
				fRec82[0] = ((fRec82[1] * fTempPerm114) + (((iSlow175)?((iTempPerm113)?1.5873015873015872f:fSlow187):0.0f) * (1.0f - fTempPerm114)));
				fTempPerm115 = min(1.0f, fRec82[0]);
				fbargraph22 = fTempPerm115;
				fTempPerm116 = fTempPerm115;
			}
			if (iSlow11 || iSlow6) {
				fTempPerm117 = (fSlow84 * (fTempPerm116 * fTempPerm112));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec83[0] = (fSlow188 + (fRec83[1] - floorf((fSlow188 + fRec83[1]))));
				fTempPerm118 = ftbl0[(((int((65536.0f * fRec83[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10) {
				iTempPerm119 = int((iRec78[0] < iSlow192));
				fTempPerm120 = expf((0 - (fConst4 / ((iSlow175)?((iTempPerm119)?fSlow191:fSlow76):fSlow189))));
				fRec84[0] = ((fRec84[1] * fTempPerm120) + (((iSlow175)?((iTempPerm119)?1.5873015873015872f:fSlow194):0.0f) * (1.0f - fTempPerm120)));
				fTempPerm121 = min(1.0f, fRec84[0]);
				fbargraph23 = fTempPerm121;
				fTempPerm122 = (fSlow35 * (fTempPerm121 * fTempPerm118));
			}
			if (iSlow11) {
				fTempPerm123 = (fSlow195 * (fTempPerm122 + ((fTempPerm117 + fTempPerm111) + (fSlow52 * (fTempPerm105 * fTempPerm101)))));
			}
			if (iSlow10) {
				fRec86[0] = ((iSlow203)?0.0f:min(fSlow202, (fRec86[1] + 1.0f)));
				iTempPerm124 = int((fRec86[0] < fSlow199));
				fRec85[0] = ((iSlow175)?(fSlow177 * ((iTempPerm124)?((int((fRec86[0] < 0.0f)))?0.0f:((iTempPerm124)?(fSlow206 * fRec86[0]):1.0f)):((int((fRec86[0] < fSlow202)))?((fSlow205 * (fRec86[0] - fSlow199)) + 1.0f):fSlow197))):fRec85[1]);
				fRec87[0] = ((iSlow208)?0.0f:min(fSlow207, (fRec87[1] + 1.0f)));
				fTempPerm125 = ((int((fRec87[0] < 0.0f)))?fRec85[0]:((int((fRec87[0] < fSlow207)))?(fRec85[0] + (fSlow209 * (0 - (fRec87[0] * fRec85[0])))):0.0f));
				fbargraph24 = fTempPerm125;
				fTempPerm126 = (fSlow195 * ((fTempPerm122 + fTempPerm111) + (fSlow52 * (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec76[0] + (fSlow210 * (fTempPerm112 * fTempPerm125))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec89[0] = ((iSlow203)?0.0f:min(fSlow23, (fRec89[1] + 1.0f)));
				iTempPerm127 = int((fRec89[0] < fSlow20));
				fRec88[0] = ((iSlow175)?(fSlow177 * ((iTempPerm127)?((int((fRec89[0] < 0.0f)))?0.0f:((iTempPerm127)?(fSlow27 * fRec89[0]):1.0f)):((int((fRec89[0] < fSlow23)))?((fSlow212 * (fRec89[0] - fSlow20)) + 1.0f):fSlow211))):fRec88[1]);
				fRec90[0] = ((iSlow208)?0.0f:min(fSlow31, (fRec90[1] + 1.0f)));
				fTempPerm128 = ((int((fRec90[0] < 0.0f)))?fRec88[0]:((int((fRec90[0] < fSlow31)))?(fRec88[0] + (fSlow33 * (0 - (fRec90[0] * fRec88[0])))):0.0f));
				fbargraph25 = fTempPerm128;
				fTempPerm129 = (fTempPerm128 * fTempPerm118);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm130 = (fSlow36 * fTempPerm129);
			}
			if (iSlow9 || iSlow4) {
				fTempPerm131 = ftbl0[(((int((65536.0f * (fRec79[0] + fTempPerm130))) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm132 = ftbl0[(((int((65536.0f * (fRec76[0] + fTempPerm130))) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8) {
				fTempPerm133 = (fSlow52 * (fTempPerm105 * fTempPerm132));
			}
			if (iSlow9) {
				fTempPerm134 = (fSlow195 * (fTempPerm133 + ((fSlow84 * (fTempPerm116 * ftbl0[(((int((65536.0f * (fRec81[0] + fTempPerm130))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm110 * fTempPerm131)))));
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec92[0] = ((iSlow203)?0.0f:min(fSlow63, (fRec92[1] + 1.0f)));
				iTempPerm135 = int((fRec92[0] < fSlow60));
				fRec91[0] = ((iSlow175)?(fSlow177 * ((iTempPerm135)?((int((fRec92[0] < 0.0f)))?0.0f:((iTempPerm135)?(fSlow66 * fRec92[0]):1.0f)):((int((fRec92[0] < fSlow63)))?((fSlow214 * (fRec92[0] - fSlow60)) + 1.0f):fSlow213))):fRec91[1]);
				fRec93[0] = ((iSlow208)?0.0f:min(fSlow67, (fRec93[1] + 1.0f)));
				fTempPerm136 = ((int((fRec93[0] < 0.0f)))?fRec91[0]:((int((fRec93[0] < fSlow67)))?(fRec91[0] + (fSlow68 * (0 - (fRec93[0] * fRec91[0])))):0.0f));
				fbargraph26 = fTempPerm136;
				fTempPerm137 = fTempPerm136;
			}
			if (iSlow8 || iSlow7) {
				fTempPerm138 = (fTempPerm137 * fTempPerm106);
			}
			if (iSlow8) {
				fTempPerm139 = (fSlow195 * ((fSlow84 * (fTempPerm116 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow70 * fTempPerm138)))) % 65536) + 65536) % 65536)])) + fTempPerm133));
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec95[0] = ((iSlow203)?0.0f:min(fSlow46, (fRec95[1] + 1.0f)));
				iTempPerm140 = int((fRec95[0] < fSlow43));
				fRec94[0] = ((iSlow175)?(fSlow177 * ((iTempPerm140)?((int((fRec95[0] < 0.0f)))?0.0f:((iTempPerm140)?(fSlow49 * fRec95[0]):1.0f)):((int((fRec95[0] < fSlow46)))?((fSlow216 * (fRec95[0] - fSlow43)) + 1.0f):fSlow215))):fRec94[1]);
				fRec96[0] = ((iSlow208)?0.0f:min(fSlow50, (fRec96[1] + 1.0f)));
				fTempPerm141 = ((int((fRec96[0] < 0.0f)))?fRec94[0]:((int((fRec96[0] < fSlow50)))?(fRec94[0] + (fSlow51 * (0 - (fRec96[0] * fRec94[0])))):0.0f));
				fbargraph27 = fTempPerm141;
				fTempPerm142 = fTempPerm141;
			}
			if (iSlow7 || iSlow3) {
				fTempPerm143 = (fTempPerm142 * fTempPerm101);
				fTempPerm144 = (fSlow35 * fTempPerm129);
			}
			if (iSlow7) {
				fTempPerm145 = (fSlow217 * (fTempPerm116 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow34 * ((fTempPerm144 + (fSlow52 * fTempPerm143)) + (fSlow69 * fTempPerm138)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm146 = (fTempPerm142 * fTempPerm132);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm147 = (fSlow53 * fTempPerm146);
				fTempPerm148 = ftbl0[(((int((65536.0f * (fRec79[0] + fTempPerm147))) % 65536) + 65536) % 65536)];
			}
			if (iSlow6 || iSlow5) {
				fTempPerm149 = (fSlow69 * (fTempPerm110 * fTempPerm148));
			}
			if (iSlow6) {
				fTempPerm150 = (fSlow195 * (fTempPerm149 + fTempPerm117));
			}
			if (iSlow5) {
				fTempPerm151 = (fSlow195 * ((fSlow84 * (fTempPerm116 * ftbl0[(((int((65536.0f * (fRec81[0] + fTempPerm147))) % 65536) + 65536) % 65536)])) + fTempPerm149));
			}
			if (iSlow4) {
				fTempPerm152 = (fSlow217 * (fTempPerm116 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow34 * ((fSlow52 * fTempPerm146) + (fSlow69 * (fTempPerm137 * fTempPerm131))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm153 = (fSlow217 * (fTempPerm116 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow34 * (fTempPerm144 + (fSlow69 * (fTempPerm137 * ftbl0[(((int((65536.0f * (fRec79[0] + (fSlow53 * fTempPerm143)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow2 || iSlow1) {
				fTempPerm154 = (fSlow217 * (fTempPerm116 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow70 * (fTempPerm137 * fTempPerm148))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm155 = ftbl0[(((int((65536.0f * fRec65[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm156 = (fTempPerm89 * fTempPerm155);
				fTempPerm157 = (fSlow35 * fTempPerm84);
			}
			if (iSlow3) {
				fTempPerm158 = (fSlow166 * (fTempPerm99 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow34 * (fTempPerm157 + (fSlow69 * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec69[0] + (fSlow53 * fTempPerm156)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm159 = ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm85))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm160 = (fSlow166 * (fTempPerm99 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow34 * ((fSlow52 * fTempPerm90) + (fSlow69 * (fTempPerm95 * fTempPerm159))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm161 = int((iRec75[0] < iSlow183));
				fTempPerm162 = expf((0 - (fConst4 / ((iSlow155)?((iTempPerm161)?fSlow182:fSlow76):fSlow180))));
				fRec97[0] = ((fRec97[1] * fTempPerm162) + (((iSlow155)?((iTempPerm161)?1.5873015873015872f:fSlow218):0.0f) * (1.0f - fTempPerm162)));
				fTempPerm163 = min(1.0f, fRec97[0]);
				fbargraph28 = fTempPerm163;
				fTempPerm164 = fTempPerm163;
			}
			if (iSlow6 || iSlow5) {
				fTempPerm165 = (fSlow69 * (fTempPerm164 * fTempPerm92));
			}
			if (iSlow5) {
				fTempPerm166 = (fSlow165 * ((fSlow84 * (fTempPerm99 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm91))) % 65536) + 65536) % 65536)])) + fTempPerm165));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm167 = ftbl0[(((int((65536.0f * fRec73[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm168 = (fSlow84 * (fTempPerm99 * fTempPerm167));
			}
			if (iSlow6) {
				fTempPerm169 = (fSlow165 * (fTempPerm165 + fTempPerm168));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm170 = ftbl0[(((int((65536.0f * fRec69[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm171 = (fTempPerm95 * fTempPerm170);
			}
			if (iSlow7) {
				fTempPerm172 = (fSlow166 * (fTempPerm99 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow34 * ((fTempPerm157 + (fSlow52 * fTempPerm156)) + (fSlow69 * fTempPerm171)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm173 = int((iRec75[0] < iSlow172));
				fTempPerm174 = expf((0 - (fConst4 / ((iSlow155)?((iTempPerm173)?fSlow171:fSlow76):fSlow169))));
				fRec98[0] = ((fRec98[1] * fTempPerm174) + (((iSlow155)?((iTempPerm173)?1.5873015873015872f:fSlow219):0.0f) * (1.0f - fTempPerm174)));
				fTempPerm175 = min(1.0f, fRec98[0]);
				fbargraph29 = fTempPerm175;
				fTempPerm176 = fTempPerm175;
			}
			if (iSlow9 || iSlow8) {
				fTempPerm177 = (fSlow52 * (fTempPerm176 * fTempPerm86));
			}
			if (iSlow8) {
				fTempPerm178 = (fSlow165 * ((fSlow84 * (fTempPerm99 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow70 * fTempPerm171)))) % 65536) + 65536) % 65536)])) + fTempPerm177));
			}
			if (iSlow9) {
				fTempPerm179 = (fSlow165 * (fTempPerm177 + ((fSlow84 * (fTempPerm99 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm85))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm164 * fTempPerm159)))));
			}
			if (iSlow10) {
				fRec100[0] = ((iSlow151)?0.0f:min(fSlow202, (fRec100[1] + 1.0f)));
				iTempPerm180 = int((fRec100[0] < fSlow199));
				fRec99[0] = ((iSlow155)?(fSlow154 * ((iTempPerm180)?((int((fRec100[0] < 0.0f)))?0.0f:((iTempPerm180)?(fSlow206 * fRec100[0]):1.0f)):((int((fRec100[0] < fSlow202)))?((fSlow221 * (fRec100[0] - fSlow199)) + 1.0f):fSlow220))):fRec99[1]);
				fRec101[0] = ((iSlow156)?0.0f:min(fSlow207, (fRec101[1] + 1.0f)));
				fTempPerm181 = ((int((fRec101[0] < 0.0f)))?fRec99[0]:((int((fRec101[0] < fSlow207)))?(fRec99[0] + (fSlow209 * (0 - (fRec101[0] * fRec99[0])))):0.0f));
				fbargraph30 = fTempPerm181;
			}
			if (iSlow11 || iSlow10) {
				fTempPerm182 = (fSlow69 * (fTempPerm164 * fTempPerm170));
				iTempPerm183 = int((iRec75[0] < iSlow192));
				fTempPerm184 = expf((0 - (fConst4 / ((iSlow155)?((iTempPerm183)?fSlow191:fSlow76):fSlow189))));
				fRec102[0] = ((fRec102[1] * fTempPerm184) + (((iSlow155)?((iTempPerm183)?1.5873015873015872f:fSlow222):0.0f) * (1.0f - fTempPerm184)));
				fTempPerm185 = min(1.0f, fRec102[0]);
				fbargraph31 = fTempPerm185;
				fTempPerm186 = (fSlow35 * (fTempPerm185 * fTempPerm81));
			}
			if (iSlow10) {
				fTempPerm187 = (fSlow165 * ((fTempPerm186 + fTempPerm182) + (fSlow52 * (fTempPerm176 * ftbl0[(((int((65536.0f * (fRec65[0] + (fSlow210 * (fTempPerm167 * fTempPerm181))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm188 = (fSlow165 * (fTempPerm186 + ((fTempPerm168 + fTempPerm182) + (fSlow52 * (fTempPerm176 * fTempPerm155)))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm189 = ftbl0[(((int((65536.0f * fRec50[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm190 = (fTempPerm69 * fTempPerm189);
				fTempPerm191 = (fSlow35 * fTempPerm64);
			}
			if (iSlow3) {
				fTempPerm192 = (fSlow146 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow34 * (fTempPerm191 + (fSlow69 * (fTempPerm75 * ftbl0[(((int((65536.0f * (fRec54[0] + (fSlow53 * fTempPerm190)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm193 = ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm65))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm194 = (fSlow146 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow34 * ((fSlow52 * fTempPerm70) + (fSlow69 * (fTempPerm75 * fTempPerm193))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm195 = int((iRec60[0] < iSlow183));
				fTempPerm196 = expf((0 - (fConst4 / ((iSlow135)?((iTempPerm195)?fSlow182:fSlow76):fSlow180))));
				fRec103[0] = ((fRec103[1] * fTempPerm196) + (((iSlow135)?((iTempPerm195)?1.5873015873015872f:fSlow223):0.0f) * (1.0f - fTempPerm196)));
				fTempPerm197 = min(1.0f, fRec103[0]);
				fbargraph32 = fTempPerm197;
				fTempPerm198 = fTempPerm197;
			}
			if (iSlow6 || iSlow5) {
				fTempPerm199 = (fSlow69 * (fTempPerm198 * fTempPerm72));
			}
			if (iSlow5) {
				fTempPerm200 = (fSlow145 * ((fSlow84 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec58[0] + fTempPerm71))) % 65536) + 65536) % 65536)])) + fTempPerm199));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm201 = ftbl0[(((int((65536.0f * fRec58[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm202 = (fSlow84 * (fTempPerm79 * fTempPerm201));
			}
			if (iSlow6) {
				fTempPerm203 = (fSlow145 * (fTempPerm199 + fTempPerm202));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm204 = ftbl0[(((int((65536.0f * fRec54[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm205 = (fTempPerm75 * fTempPerm204);
			}
			if (iSlow7) {
				fTempPerm206 = (fSlow146 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow34 * ((fTempPerm191 + (fSlow52 * fTempPerm190)) + (fSlow69 * fTempPerm205)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm207 = int((iRec60[0] < iSlow172));
				fTempPerm208 = expf((0 - (fConst4 / ((iSlow135)?((iTempPerm207)?fSlow171:fSlow76):fSlow169))));
				fRec104[0] = ((fRec104[1] * fTempPerm208) + (((iSlow135)?((iTempPerm207)?1.5873015873015872f:fSlow224):0.0f) * (1.0f - fTempPerm208)));
				fTempPerm209 = min(1.0f, fRec104[0]);
				fbargraph33 = fTempPerm209;
				fTempPerm210 = fTempPerm209;
			}
			if (iSlow9 || iSlow8) {
				fTempPerm211 = (fSlow52 * (fTempPerm210 * fTempPerm66));
			}
			if (iSlow8) {
				fTempPerm212 = (fSlow145 * ((fSlow84 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow70 * fTempPerm205)))) % 65536) + 65536) % 65536)])) + fTempPerm211));
			}
			if (iSlow9) {
				fTempPerm213 = (fSlow145 * (fTempPerm211 + ((fSlow84 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec58[0] + fTempPerm65))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm198 * fTempPerm193)))));
			}
			if (iSlow10) {
				fRec106[0] = ((iSlow131)?0.0f:min(fSlow202, (fRec106[1] + 1.0f)));
				iTempPerm214 = int((fRec106[0] < fSlow199));
				fRec105[0] = ((iSlow135)?(fSlow134 * ((iTempPerm214)?((int((fRec106[0] < 0.0f)))?0.0f:((iTempPerm214)?(fSlow206 * fRec106[0]):1.0f)):((int((fRec106[0] < fSlow202)))?((fSlow226 * (fRec106[0] - fSlow199)) + 1.0f):fSlow225))):fRec105[1]);
				fRec107[0] = ((iSlow136)?0.0f:min(fSlow207, (fRec107[1] + 1.0f)));
				fTempPerm215 = ((int((fRec107[0] < 0.0f)))?fRec105[0]:((int((fRec107[0] < fSlow207)))?(fRec105[0] + (fSlow209 * (0 - (fRec107[0] * fRec105[0])))):0.0f));
				fbargraph34 = fTempPerm215;
			}
			if (iSlow11 || iSlow10) {
				fTempPerm216 = (fSlow69 * (fTempPerm198 * fTempPerm204));
				iTempPerm217 = int((iRec60[0] < iSlow192));
				fTempPerm218 = expf((0 - (fConst4 / ((iSlow135)?((iTempPerm217)?fSlow191:fSlow76):fSlow189))));
				fRec108[0] = ((fRec108[1] * fTempPerm218) + (((iSlow135)?((iTempPerm217)?1.5873015873015872f:fSlow227):0.0f) * (1.0f - fTempPerm218)));
				fTempPerm219 = min(1.0f, fRec108[0]);
				fbargraph35 = fTempPerm219;
				fTempPerm220 = (fSlow35 * (fTempPerm219 * fTempPerm61));
			}
			if (iSlow10) {
				fTempPerm221 = (fSlow145 * ((fTempPerm220 + fTempPerm216) + (fSlow52 * (fTempPerm210 * ftbl0[(((int((65536.0f * (fRec50[0] + (fSlow210 * (fTempPerm201 * fTempPerm215))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm222 = (fSlow145 * (fTempPerm220 + ((fTempPerm202 + fTempPerm216) + (fSlow52 * (fTempPerm210 * fTempPerm189)))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm223 = ftbl0[(((int((65536.0f * fRec35[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm224 = (fTempPerm49 * fTempPerm223);
				fTempPerm225 = (fSlow35 * fTempPerm44);
			}
			if (iSlow3) {
				fTempPerm226 = (fSlow126 * (fTempPerm59 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow34 * (fTempPerm225 + (fSlow69 * (ftbl0[(((int((65536.0f * (fRec39[0] + (fSlow53 * fTempPerm224)))) % 65536) + 65536) % 65536)] * fTempPerm55))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm227 = ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm45))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm228 = (fSlow126 * (fTempPerm59 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow34 * ((fSlow52 * fTempPerm50) + (fSlow69 * (fTempPerm55 * fTempPerm227))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm229 = int((iRec45[0] < iSlow183));
				fTempPerm230 = expf((0 - (fConst4 / ((iSlow115)?((iTempPerm229)?fSlow182:fSlow76):fSlow180))));
				fRec109[0] = ((fRec109[1] * fTempPerm230) + (((iSlow115)?((iTempPerm229)?1.5873015873015872f:fSlow228):0.0f) * (1.0f - fTempPerm230)));
				fTempPerm231 = min(1.0f, fRec109[0]);
				fbargraph36 = fTempPerm231;
				fTempPerm232 = fTempPerm231;
			}
			if (iSlow6 || iSlow5) {
				fTempPerm233 = (fSlow69 * (fTempPerm232 * fTempPerm52));
			}
			if (iSlow5) {
				fTempPerm234 = (fSlow125 * ((fSlow84 * (fTempPerm59 * ftbl0[(((int((65536.0f * (fRec43[0] + fTempPerm51))) % 65536) + 65536) % 65536)])) + fTempPerm233));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm235 = ftbl0[(((int((65536.0f * fRec43[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm236 = (fSlow84 * (fTempPerm59 * fTempPerm235));
			}
			if (iSlow6) {
				fTempPerm237 = (fSlow125 * (fTempPerm233 + fTempPerm236));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm238 = ftbl0[(((int((65536.0f * fRec39[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm239 = (fTempPerm55 * fTempPerm238);
			}
			if (iSlow7) {
				fTempPerm240 = (fSlow126 * (fTempPerm59 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow34 * ((fTempPerm225 + (fSlow52 * fTempPerm224)) + (fSlow69 * fTempPerm239)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm241 = int((iRec45[0] < iSlow172));
				fTempPerm242 = expf((0 - (fConst4 / ((iSlow115)?((iTempPerm241)?fSlow171:fSlow76):fSlow169))));
				fRec110[0] = ((fRec110[1] * fTempPerm242) + (((iSlow115)?((iTempPerm241)?1.5873015873015872f:fSlow229):0.0f) * (1.0f - fTempPerm242)));
				fTempPerm243 = min(1.0f, fRec110[0]);
				fbargraph37 = fTempPerm243;
				fTempPerm244 = fTempPerm243;
			}
			if (iSlow9 || iSlow8) {
				fTempPerm245 = (fSlow52 * (fTempPerm244 * fTempPerm46));
			}
			if (iSlow8) {
				fTempPerm246 = (fSlow125 * ((fSlow84 * (fTempPerm59 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow70 * fTempPerm239)))) % 65536) + 65536) % 65536)])) + fTempPerm245));
			}
			if (iSlow9) {
				fTempPerm247 = (fSlow125 * (fTempPerm245 + ((fSlow84 * (fTempPerm59 * ftbl0[(((int((65536.0f * (fRec43[0] + fTempPerm45))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm232 * fTempPerm227)))));
			}
			if (iSlow10) {
				fRec112[0] = ((iSlow111)?0.0f:min(fSlow202, (fRec112[1] + 1.0f)));
				iTempPerm248 = int((fRec112[0] < fSlow199));
				fRec111[0] = ((iSlow115)?(fSlow114 * ((iTempPerm248)?((int((fRec112[0] < 0.0f)))?0.0f:((iTempPerm248)?(fSlow206 * fRec112[0]):1.0f)):((int((fRec112[0] < fSlow202)))?((fSlow231 * (fRec112[0] - fSlow199)) + 1.0f):fSlow230))):fRec111[1]);
				fRec113[0] = ((iSlow116)?0.0f:min(fSlow207, (fRec113[1] + 1.0f)));
				fTempPerm249 = ((int((fRec113[0] < 0.0f)))?fRec111[0]:((int((fRec113[0] < fSlow207)))?(fRec111[0] + (fSlow209 * (0 - (fRec113[0] * fRec111[0])))):0.0f));
				fbargraph38 = fTempPerm249;
			}
			if (iSlow11 || iSlow10) {
				fTempPerm250 = (fSlow69 * (fTempPerm232 * fTempPerm238));
				iTempPerm251 = int((iRec45[0] < iSlow192));
				fTempPerm252 = expf((0 - (fConst4 / ((iSlow115)?((iTempPerm251)?fSlow191:fSlow76):fSlow189))));
				fRec114[0] = ((fRec114[1] * fTempPerm252) + (((iSlow115)?((iTempPerm251)?1.5873015873015872f:fSlow232):0.0f) * (1.0f - fTempPerm252)));
				fTempPerm253 = min(1.0f, fRec114[0]);
				fbargraph39 = fTempPerm253;
				fTempPerm254 = (fSlow35 * (fTempPerm253 * fTempPerm41));
			}
			if (iSlow10) {
				fTempPerm255 = (fSlow125 * ((fTempPerm254 + fTempPerm250) + (fSlow52 * (fTempPerm244 * ftbl0[(((int((65536.0f * (fRec35[0] + (fSlow210 * (fTempPerm235 * fTempPerm249))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm256 = (fSlow125 * (fTempPerm254 + ((fTempPerm236 + fTempPerm250) + (fSlow52 * (fTempPerm244 * fTempPerm223)))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm257 = ftbl0[(((int((65536.0f * fRec20[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm258 = (fTempPerm29 * fTempPerm257);
				fTempPerm259 = (fSlow35 * fTempPerm24);
			}
			if (iSlow3) {
				fTempPerm260 = (fSlow106 * (fTempPerm39 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow34 * (fTempPerm259 + (fSlow69 * (fTempPerm35 * ftbl0[(((int((65536.0f * (fRec24[0] + (fSlow53 * fTempPerm258)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm261 = ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm25))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm262 = (fSlow106 * (fTempPerm39 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow34 * ((fSlow52 * fTempPerm30) + (fSlow69 * (fTempPerm35 * fTempPerm261))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm263 = int((iRec30[0] < iSlow183));
				fTempPerm264 = expf((0 - (fConst4 / ((iSlow95)?((iTempPerm263)?fSlow182:fSlow76):fSlow180))));
				fRec115[0] = ((fRec115[1] * fTempPerm264) + (((iSlow95)?((iTempPerm263)?1.5873015873015872f:fSlow233):0.0f) * (1.0f - fTempPerm264)));
				fTempPerm265 = min(1.0f, fRec115[0]);
				fbargraph40 = fTempPerm265;
				fTempPerm266 = fTempPerm265;
			}
			if (iSlow6 || iSlow5) {
				fTempPerm267 = (fSlow69 * (fTempPerm266 * fTempPerm32));
			}
			if (iSlow5) {
				fTempPerm268 = (fSlow105 * ((fSlow84 * (fTempPerm39 * ftbl0[(((int((65536.0f * (fRec28[0] + fTempPerm31))) % 65536) + 65536) % 65536)])) + fTempPerm267));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm269 = ftbl0[(((int((65536.0f * fRec28[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm270 = (fSlow84 * (fTempPerm39 * fTempPerm269));
			}
			if (iSlow6) {
				fTempPerm271 = (fSlow105 * (fTempPerm267 + fTempPerm270));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm272 = ftbl0[(((int((65536.0f * fRec24[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm273 = (fTempPerm35 * fTempPerm272);
			}
			if (iSlow7) {
				fTempPerm274 = (fSlow106 * (fTempPerm39 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow34 * ((fTempPerm259 + (fSlow52 * fTempPerm258)) + (fSlow69 * fTempPerm273)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm275 = int((iRec30[0] < iSlow172));
				fTempPerm276 = expf((0 - (fConst4 / ((iSlow95)?((iTempPerm275)?fSlow171:fSlow76):fSlow169))));
				fRec116[0] = ((fRec116[1] * fTempPerm276) + (((iSlow95)?((iTempPerm275)?1.5873015873015872f:fSlow234):0.0f) * (1.0f - fTempPerm276)));
				fTempPerm277 = min(1.0f, fRec116[0]);
				fbargraph41 = fTempPerm277;
				fTempPerm278 = fTempPerm277;
			}
			if (iSlow9 || iSlow8) {
				fTempPerm279 = (fSlow52 * (fTempPerm278 * fTempPerm26));
			}
			if (iSlow8) {
				fTempPerm280 = (fSlow105 * ((fSlow84 * (fTempPerm39 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow70 * fTempPerm273)))) % 65536) + 65536) % 65536)])) + fTempPerm279));
			}
			if (iSlow9) {
				fTempPerm281 = (fSlow105 * (fTempPerm279 + ((fSlow84 * (fTempPerm39 * ftbl0[(((int((65536.0f * (fRec28[0] + fTempPerm25))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm266 * fTempPerm261)))));
			}
			if (iSlow10) {
				fRec118[0] = ((iSlow91)?0.0f:min(fSlow202, (fRec118[1] + 1.0f)));
				iTempPerm282 = int((fRec118[0] < fSlow199));
				fRec117[0] = ((iSlow95)?(fSlow94 * ((iTempPerm282)?((int((fRec118[0] < 0.0f)))?0.0f:((iTempPerm282)?(fSlow206 * fRec118[0]):1.0f)):((int((fRec118[0] < fSlow202)))?((fSlow236 * (fRec118[0] - fSlow199)) + 1.0f):fSlow235))):fRec117[1]);
				fRec119[0] = ((iSlow96)?0.0f:min(fSlow207, (fRec119[1] + 1.0f)));
				fTempPerm283 = ((int((fRec119[0] < 0.0f)))?fRec117[0]:((int((fRec119[0] < fSlow207)))?(fRec117[0] + (fSlow209 * (0 - (fRec119[0] * fRec117[0])))):0.0f));
				fbargraph42 = fTempPerm283;
			}
			if (iSlow11 || iSlow10) {
				fTempPerm284 = (fSlow69 * (fTempPerm266 * fTempPerm272));
				iTempPerm285 = int((iRec30[0] < iSlow192));
				fTempPerm286 = expf((0 - (fConst4 / ((iSlow95)?((iTempPerm285)?fSlow191:fSlow76):fSlow189))));
				fRec120[0] = ((fRec120[1] * fTempPerm286) + (((iSlow95)?((iTempPerm285)?1.5873015873015872f:fSlow237):0.0f) * (1.0f - fTempPerm286)));
				fTempPerm287 = min(1.0f, fRec120[0]);
				fbargraph43 = fTempPerm287;
				fTempPerm288 = (fSlow35 * (fTempPerm287 * fTempPerm21));
			}
			if (iSlow10) {
				fTempPerm289 = (fSlow105 * ((fTempPerm288 + fTempPerm284) + (fSlow52 * (fTempPerm278 * ftbl0[(((int((65536.0f * (fRec20[0] + (fSlow210 * (fTempPerm269 * fTempPerm283))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm290 = (fSlow105 * (fTempPerm288 + ((fTempPerm270 + fTempPerm284) + (fSlow52 * (fTempPerm278 * fTempPerm257)))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm291 = ftbl0[(((int((65536.0f * fRec5[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm292 = (fTempPerm9 * fTempPerm291);
				fTempPerm293 = (fSlow35 * fTempPerm4);
			}
			if (iSlow3) {
				fTempPerm294 = (fSlow86 * (fTempPerm19 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow34 * (fTempPerm293 + (fSlow69 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec9[0] + (fSlow53 * fTempPerm292)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm295 = ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm5))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm296 = (fSlow86 * (fTempPerm19 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow34 * ((fSlow52 * fTempPerm10) + (fSlow69 * (fTempPerm15 * fTempPerm295))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm297 = int((iRec15[0] < iSlow183));
				fTempPerm298 = expf((0 - (fConst4 / ((iSlow30)?((iTempPerm297)?fSlow182:fSlow76):fSlow180))));
				fRec121[0] = ((fRec121[1] * fTempPerm298) + (((iSlow30)?((iTempPerm297)?1.5873015873015872f:fSlow238):0.0f) * (1.0f - fTempPerm298)));
				fTempPerm299 = min(1.0f, fRec121[0]);
				fbargraph44 = fTempPerm299;
				fTempPerm300 = fTempPerm299;
			}
			if (iSlow6 || iSlow5) {
				fTempPerm301 = (fSlow69 * (fTempPerm300 * fTempPerm12));
			}
			if (iSlow5) {
				fTempPerm302 = (fSlow85 * ((fSlow84 * (fTempPerm19 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm11))) % 65536) + 65536) % 65536)])) + fTempPerm301));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm303 = ftbl0[(((int((65536.0f * fRec13[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm304 = (fSlow84 * (fTempPerm19 * fTempPerm303));
			}
			if (iSlow6) {
				fTempPerm305 = (fSlow85 * (fTempPerm301 + fTempPerm304));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm306 = ftbl0[(((int((65536.0f * fRec9[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm307 = (fTempPerm15 * fTempPerm306);
			}
			if (iSlow7) {
				fTempPerm308 = (fSlow86 * (fTempPerm19 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow34 * ((fTempPerm293 + (fSlow52 * fTempPerm292)) + (fSlow69 * fTempPerm307)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm309 = int((iRec15[0] < iSlow172));
				fTempPerm310 = expf((0 - (fConst4 / ((iSlow30)?((iTempPerm309)?fSlow171:fSlow76):fSlow169))));
				fRec122[0] = ((fRec122[1] * fTempPerm310) + (((iSlow30)?((iTempPerm309)?1.5873015873015872f:fSlow239):0.0f) * (1.0f - fTempPerm310)));
				fTempPerm311 = min(1.0f, fRec122[0]);
				fbargraph45 = fTempPerm311;
				fTempPerm312 = fTempPerm311;
			}
			if (iSlow9 || iSlow8) {
				fTempPerm313 = (fSlow52 * (fTempPerm312 * fTempPerm6));
			}
			if (iSlow8) {
				fTempPerm314 = (fSlow85 * ((fSlow84 * (fTempPerm19 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow70 * fTempPerm307)))) % 65536) + 65536) % 65536)])) + fTempPerm313));
			}
			if (iSlow9) {
				fTempPerm315 = (fSlow85 * (fTempPerm313 + ((fSlow84 * (fTempPerm19 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm5))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm300 * fTempPerm295)))));
			}
			if (iSlow10) {
				fRec124[0] = ((iSlow24)?0.0f:min(fSlow202, (fRec124[1] + 1.0f)));
				iTempPerm316 = int((fRec124[0] < fSlow199));
				fRec123[0] = ((iSlow30)?(fSlow29 * ((iTempPerm316)?((int((fRec124[0] < 0.0f)))?0.0f:((iTempPerm316)?(fSlow206 * fRec124[0]):1.0f)):((int((fRec124[0] < fSlow202)))?((fSlow241 * (fRec124[0] - fSlow199)) + 1.0f):fSlow240))):fRec123[1]);
				fRec125[0] = ((iSlow32)?0.0f:min(fSlow207, (fRec125[1] + 1.0f)));
				fTempPerm317 = ((int((fRec125[0] < 0.0f)))?fRec123[0]:((int((fRec125[0] < fSlow207)))?(fRec123[0] + (fSlow209 * (0 - (fRec125[0] * fRec123[0])))):0.0f));
				fbargraph46 = fTempPerm317;
			}
			if (iSlow11 || iSlow10) {
				fTempPerm318 = (fSlow69 * (fTempPerm300 * fTempPerm306));
				iTempPerm319 = int((iRec15[0] < iSlow192));
				fTempPerm320 = expf((0 - (fConst4 / ((iSlow30)?((iTempPerm319)?fSlow191:fSlow76):fSlow189))));
				fRec126[0] = ((fRec126[1] * fTempPerm320) + (((iSlow30)?((iTempPerm319)?1.5873015873015872f:fSlow242):0.0f) * (1.0f - fTempPerm320)));
				fTempPerm321 = min(1.0f, fRec126[0]);
				fbargraph47 = fTempPerm321;
				fTempPerm322 = (fSlow35 * (fTempPerm321 * fTempPerm1));
			}
			if (iSlow10) {
				fTempPerm323 = (fSlow85 * ((fTempPerm322 + fTempPerm318) + (fSlow52 * (fTempPerm312 * ftbl0[(((int((65536.0f * (fRec5[0] + (fSlow210 * (fTempPerm303 * fTempPerm317))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm324 = (fSlow85 * (fTempPerm322 + ((fTempPerm304 + fTempPerm318) + (fSlow52 * (fTempPerm312 * fTempPerm291)))));
			}
			output0[i] = (FAUSTFLOAT)(fTempPerm324 + (fTempPerm323 + (fTempPerm315 + (fTempPerm314 + (fTempPerm308 + (fTempPerm305 + (fTempPerm302 + (fTempPerm296 + (fTempPerm294 + (fTempPerm20 + ((fTempPerm290 + (fTempPerm289 + (fTempPerm281 + (fTempPerm280 + (fTempPerm274 + (fTempPerm271 + (fTempPerm268 + (fTempPerm262 + (fTempPerm260 + (fTempPerm40 + ((fTempPerm256 + (fTempPerm255 + (fTempPerm247 + (fTempPerm246 + (fTempPerm240 + (fTempPerm237 + (fTempPerm234 + (fTempPerm228 + (fTempPerm226 + (fTempPerm60 + ((fTempPerm222 + (fTempPerm221 + (fTempPerm213 + (fTempPerm212 + (fTempPerm206 + (fTempPerm203 + (fTempPerm200 + (fTempPerm194 + (fTempPerm192 + (fTempPerm80 + ((fTempPerm188 + (fTempPerm187 + (fTempPerm179 + (fTempPerm178 + (fTempPerm172 + (fTempPerm169 + (fTempPerm166 + (fTempPerm160 + (fTempPerm158 + (fTempPerm100 + (((((((((((fTempPerm154 + fTempPerm154) + fTempPerm153) + fTempPerm152) + fTempPerm151) + fTempPerm150) + fTempPerm145) + fTempPerm139) + fTempPerm134) + fTempPerm126) + fTempPerm123) + fTempPerm100))))))))))) + fTempPerm80))))))))))) + fTempPerm60))))))))))) + fTempPerm40))))))))))) + fTempPerm20)))))))))));
			// post processing
			if (iSlow11 || iSlow10) {
				fRec126[1] = fRec126[0];
			}
			if (iSlow10) {
				fRec125[1] = fRec125[0];
				fRec123[1] = fRec123[0];
				fRec124[1] = fRec124[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec122[1] = fRec122[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec121[1] = fRec121[0];
			}
			if (iSlow11 || iSlow10) {
				fRec120[1] = fRec120[0];
			}
			if (iSlow10) {
				fRec119[1] = fRec119[0];
				fRec117[1] = fRec117[0];
				fRec118[1] = fRec118[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec116[1] = fRec116[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec115[1] = fRec115[0];
			}
			if (iSlow11 || iSlow10) {
				fRec114[1] = fRec114[0];
			}
			if (iSlow10) {
				fRec113[1] = fRec113[0];
				fRec111[1] = fRec111[0];
				fRec112[1] = fRec112[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec110[1] = fRec110[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec109[1] = fRec109[0];
			}
			if (iSlow11 || iSlow10) {
				fRec108[1] = fRec108[0];
			}
			if (iSlow10) {
				fRec107[1] = fRec107[0];
				fRec105[1] = fRec105[0];
				fRec106[1] = fRec106[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec104[1] = fRec104[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec103[1] = fRec103[0];
			}
			if (iSlow11 || iSlow10) {
				fRec102[1] = fRec102[0];
			}
			if (iSlow10) {
				fRec101[1] = fRec101[0];
				fRec99[1] = fRec99[0];
				fRec100[1] = fRec100[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec98[1] = fRec98[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec97[1] = fRec97[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec96[1] = fRec96[0];
				fRec94[1] = fRec94[0];
				fRec95[1] = fRec95[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec93[1] = fRec93[0];
				fRec91[1] = fRec91[0];
				fRec92[1] = fRec92[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec90[1] = fRec90[0];
				fRec88[1] = fRec88[0];
				fRec89[1] = fRec89[0];
			}
			if (iSlow10) {
				fRec87[1] = fRec87[0];
				fRec85[1] = fRec85[0];
				fRec86[1] = fRec86[0];
			}
			if (iSlow11 || iSlow10) {
				fRec84[1] = fRec84[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec83[1] = fRec83[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec82[1] = fRec82[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec81[1] = fRec81[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec80[1] = fRec80[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec79[1] = fRec79[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec77[1] = fRec77[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec78[1] = iRec78[0];
				fRec76[1] = fRec76[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec74[1] = fRec74[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec75[1] = iRec75[0];
				fRec73[1] = fRec73[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec72[1] = fRec72[0];
				fRec70[1] = fRec70[0];
				fRec71[1] = fRec71[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec69[1] = fRec69[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec68[1] = fRec68[0];
				fRec66[1] = fRec66[0];
				fRec67[1] = fRec67[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec65[1] = fRec65[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec64[1] = fRec64[0];
				fRec62[1] = fRec62[0];
				fRec63[1] = fRec63[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec61[1] = fRec61[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec59[1] = fRec59[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec60[1] = iRec60[0];
				fRec58[1] = fRec58[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec57[1] = fRec57[0];
				fRec55[1] = fRec55[0];
				fRec56[1] = fRec56[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec54[1] = fRec54[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec53[1] = fRec53[0];
				fRec51[1] = fRec51[0];
				fRec52[1] = fRec52[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec50[1] = fRec50[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec49[1] = fRec49[0];
				fRec47[1] = fRec47[0];
				fRec48[1] = fRec48[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec46[1] = fRec46[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec44[1] = fRec44[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec45[1] = iRec45[0];
				fRec43[1] = fRec43[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec42[1] = fRec42[0];
				fRec40[1] = fRec40[0];
				fRec41[1] = fRec41[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec39[1] = fRec39[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec38[1] = fRec38[0];
				fRec36[1] = fRec36[0];
				fRec37[1] = fRec37[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec35[1] = fRec35[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec34[1] = fRec34[0];
				fRec32[1] = fRec32[0];
				fRec33[1] = fRec33[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec31[1] = fRec31[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec29[1] = fRec29[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec30[1] = iRec30[0];
				fRec28[1] = fRec28[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec27[1] = fRec27[0];
				fRec25[1] = fRec25[0];
				fRec26[1] = fRec26[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec24[1] = fRec24[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec23[1] = fRec23[0];
				fRec21[1] = fRec21[0];
				fRec22[1] = fRec22[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec20[1] = fRec20[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec19[1] = fRec19[0];
				fRec17[1] = fRec17[0];
				fRec18[1] = fRec18[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec16[1] = fRec16[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec14[1] = fRec14[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec15[1] = iRec15[0];
				fRec13[1] = fRec13[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec12[1] = fRec12[0];
				fRec10[1] = fRec10[0];
				fRec11[1] = fRec11[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec9[1] = fRec9[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec8[1] = fRec8[0];
				fRec6[1] = fRec6[0];
				fRec7[1] = fRec7[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec5[1] = fRec5[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec4[1] = fRec4[0];
				fRec2[1] = fRec2[0];
				fRec3[1] = fRec3[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec1[1] = fRec1[0];
			}
		}
	}
};


float 	faust_ottofm::ftbl0[65536];
