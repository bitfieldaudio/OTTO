//----------------------------------------------------------
// name: "dxotto"
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
#define FAUSTCLASS faust_dxotto
#endif

class faust_dxotto : public dsp {
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
	FAUSTFLOAT 	fslider4;
	float 	fConst0;
	float 	fConst1;
	float 	fTempPerm1;
	float 	fRec1[2];
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fbutton0;
	float 	fRec3[2];
	int 	iTempPerm3;
	int 	iTempPerm4;
	float 	fRec2[2];
	float 	fRec4[2];
	float 	fTempPerm5;
	float 	fTempPerm6;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fslider19;
	float 	fTempPerm7;
	float 	fRec5[2];
	float 	fTempPerm8;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fslider30;
	float 	fRec7[2];
	int 	iTempPerm9;
	int 	iTempPerm10;
	float 	fRec6[2];
	float 	fRec8[2];
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	FAUSTFLOAT 	fslider33;
	float 	fTempPerm14;
	float 	fRec9[2];
	float 	fTempPerm15;
	FAUSTFLOAT 	fslider34;
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fslider36;
	FAUSTFLOAT 	fslider37;
	FAUSTFLOAT 	fslider38;
	FAUSTFLOAT 	fslider39;
	FAUSTFLOAT 	fslider40;
	FAUSTFLOAT 	fslider41;
	FAUSTFLOAT 	fslider42;
	FAUSTFLOAT 	fslider43;
	FAUSTFLOAT 	fslider44;
	float 	fRec11[2];
	int 	iTempPerm16;
	int 	iTempPerm17;
	float 	fRec10[2];
	float 	fRec12[2];
	float 	fTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	FAUSTFLOAT 	fslider45;
	FAUSTFLOAT 	fslider46;
	FAUSTFLOAT 	fslider47;
	float 	fTempPerm21;
	float 	fRec13[2];
	float 	fTempPerm22;
	FAUSTFLOAT 	fslider48;
	FAUSTFLOAT 	fslider49;
	FAUSTFLOAT 	fslider50;
	FAUSTFLOAT 	fslider51;
	FAUSTFLOAT 	fslider52;
	FAUSTFLOAT 	fslider53;
	FAUSTFLOAT 	fslider54;
	FAUSTFLOAT 	fslider55;
	FAUSTFLOAT 	fslider56;
	FAUSTFLOAT 	fslider57;
	FAUSTFLOAT 	fslider58;
	float 	fRec15[2];
	int 	iTempPerm23;
	int 	iTempPerm24;
	float 	fRec14[2];
	float 	fRec16[2];
	float 	fTempPerm25;
	float 	fTempPerm26;
	float 	fTempPerm27;
	FAUSTFLOAT 	fslider59;
	FAUSTFLOAT 	fslider60;
	FAUSTFLOAT 	fslider61;
	float 	fTempPerm28;
	float 	fRec17[2];
	FAUSTFLOAT 	fslider62;
	FAUSTFLOAT 	fslider63;
	FAUSTFLOAT 	fslider64;
	FAUSTFLOAT 	fslider65;
	FAUSTFLOAT 	fslider66;
	FAUSTFLOAT 	fslider67;
	FAUSTFLOAT 	fslider68;
	FAUSTFLOAT 	fslider69;
	FAUSTFLOAT 	fslider70;
	FAUSTFLOAT 	fslider71;
	FAUSTFLOAT 	fslider72;
	float 	fRec19[2];
	int 	iTempPerm29;
	int 	iTempPerm30;
	float 	fRec18[2];
	float 	fRec20[2];
	float 	fTempPerm31;
	float 	fTempPerm32;
	FAUSTFLOAT 	fslider73;
	FAUSTFLOAT 	fslider74;
	FAUSTFLOAT 	fslider75;
	float 	fTempPerm33;
	float 	fRec21[2];
	float 	fTempPerm34;
	FAUSTFLOAT 	fslider76;
	FAUSTFLOAT 	fslider77;
	FAUSTFLOAT 	fslider78;
	FAUSTFLOAT 	fslider79;
	FAUSTFLOAT 	fslider80;
	FAUSTFLOAT 	fslider81;
	FAUSTFLOAT 	fslider82;
	FAUSTFLOAT 	fslider83;
	FAUSTFLOAT 	fslider84;
	FAUSTFLOAT 	fslider85;
	FAUSTFLOAT 	fslider86;
	float 	fRec23[2];
	int 	iTempPerm35;
	int 	iTempPerm36;
	float 	fRec22[2];
	float 	fRec24[2];
	float 	fTempPerm37;
	float 	fTempPerm38;
	float 	fTempPerm39;
	FAUSTFLOAT 	fslider87;
	float 	fRec25[2];
	float 	fTempPerm40;
	float 	fTempPerm41;
	float 	fRec26[2];
	float 	fTempPerm42;
	float 	fTempPerm43;
	float 	fTempPerm44;
	float 	fTempPerm45;
	float 	fTempPerm46;
	float 	fTempPerm47;
	float 	fRec27[2];
	float 	fTempPerm48;
	float 	fTempPerm49;
	float 	fTempPerm50;
	float 	fTempPerm51;
	float 	fTempPerm52;
	float 	fTempPerm53;
	float 	fTempPerm54;
	float 	fTempPerm55;
	float 	fTempPerm56;
	float 	fRec28[2];
	float 	fTempPerm57;
	float 	fTempPerm58;
	float 	fRec29[2];
	float 	fTempPerm59;
	float 	fTempPerm60;
	float 	fTempPerm61;
	float 	fTempPerm62;
	float 	fTempPerm63;
	float 	fTempPerm64;
	float 	fRec30[2];
	float 	fTempPerm65;
	float 	fTempPerm66;
	float 	fTempPerm67;
	float 	fTempPerm68;
	float 	fRec31[2];
	float 	fTempPerm69;
	float 	fTempPerm70;
	float 	fRec32[2];
	float 	fTempPerm71;
	float 	fTempPerm72;
	float 	fTempPerm73;
	float 	fTempPerm74;
	float 	fRec33[2];
	float 	fTempPerm75;
	float 	fTempPerm76;
	float 	fRec34[2];
	float 	fTempPerm77;
	float 	fRec35[2];
	float 	fTempPerm78;
	float 	fTempPerm79;
	float 	fRec36[2];
	float 	fTempPerm80;
	float 	fTempPerm81;
	float 	fTempPerm82;
	float 	fRec37[2];
	float 	fTempPerm83;
	float 	fTempPerm84;
	float 	fRec38[2];
	float 	fTempPerm85;
	float 	fTempPerm86;
	float 	fTempPerm87;
	float 	fTempPerm88;
	FAUSTFLOAT 	fslider88;
	FAUSTFLOAT 	fslider89;
	FAUSTFLOAT 	fslider90;
	int 	iRec40[2];
	int 	iTempPerm89;
	float 	fConst2;
	float 	fTempPerm90;
	FAUSTFLOAT 	fslider91;
	float 	fRec39[2];
	FAUSTFLOAT 	fslider92;
	float 	fTempPerm91;
	float 	fRec41[2];
	float 	fTempPerm92;
	FAUSTFLOAT 	fslider93;
	FAUSTFLOAT 	fbutton1;
	float 	fRec43[2];
	int 	iTempPerm93;
	int 	iTempPerm94;
	float 	fRec42[2];
	float 	fRec44[2];
	float 	fTempPerm95;
	float 	fTempPerm96;
	float 	fTempPerm97;
	float 	fRec45[2];
	float 	fTempPerm98;
	float 	fRec47[2];
	int 	iTempPerm99;
	int 	iTempPerm100;
	float 	fRec46[2];
	float 	fRec48[2];
	float 	fTempPerm101;
	float 	fTempPerm102;
	float 	fTempPerm103;
	float 	fTempPerm104;
	float 	fRec49[2];
	float 	fTempPerm105;
	float 	fRec51[2];
	int 	iTempPerm106;
	int 	iTempPerm107;
	float 	fRec50[2];
	float 	fRec52[2];
	float 	fTempPerm108;
	float 	fTempPerm109;
	float 	fTempPerm110;
	float 	fTempPerm111;
	float 	fRec53[2];
	float 	fTempPerm112;
	float 	fRec55[2];
	int 	iTempPerm113;
	int 	iTempPerm114;
	float 	fRec54[2];
	float 	fRec56[2];
	float 	fTempPerm115;
	float 	fTempPerm116;
	float 	fTempPerm117;
	float 	fTempPerm118;
	float 	fRec57[2];
	float 	fRec59[2];
	int 	iTempPerm119;
	int 	iTempPerm120;
	float 	fRec58[2];
	float 	fRec60[2];
	float 	fTempPerm121;
	float 	fTempPerm122;
	float 	fTempPerm123;
	float 	fRec61[2];
	float 	fTempPerm124;
	float 	fRec63[2];
	int 	iTempPerm125;
	int 	iTempPerm126;
	float 	fRec62[2];
	float 	fRec64[2];
	float 	fTempPerm127;
	float 	fTempPerm128;
	float 	fTempPerm129;
	float 	fRec65[2];
	float 	fTempPerm130;
	float 	fTempPerm131;
	float 	fRec66[2];
	float 	fTempPerm132;
	float 	fTempPerm133;
	float 	fTempPerm134;
	float 	fTempPerm135;
	float 	fTempPerm136;
	float 	fTempPerm137;
	float 	fRec67[2];
	float 	fTempPerm138;
	float 	fTempPerm139;
	float 	fTempPerm140;
	float 	fTempPerm141;
	float 	fTempPerm142;
	float 	fTempPerm143;
	float 	fTempPerm144;
	float 	fTempPerm145;
	float 	fTempPerm146;
	float 	fRec68[2];
	float 	fTempPerm147;
	float 	fTempPerm148;
	float 	fRec69[2];
	float 	fTempPerm149;
	float 	fTempPerm150;
	float 	fTempPerm151;
	float 	fTempPerm152;
	float 	fTempPerm153;
	float 	fTempPerm154;
	float 	fRec70[2];
	float 	fTempPerm155;
	float 	fTempPerm156;
	float 	fTempPerm157;
	float 	fTempPerm158;
	float 	fRec71[2];
	float 	fTempPerm159;
	float 	fTempPerm160;
	float 	fRec72[2];
	float 	fTempPerm161;
	float 	fTempPerm162;
	float 	fTempPerm163;
	float 	fTempPerm164;
	float 	fRec73[2];
	float 	fTempPerm165;
	float 	fTempPerm166;
	float 	fRec74[2];
	float 	fTempPerm167;
	float 	fRec75[2];
	float 	fTempPerm168;
	float 	fTempPerm169;
	float 	fRec76[2];
	float 	fTempPerm170;
	float 	fTempPerm171;
	float 	fTempPerm172;
	float 	fRec77[2];
	float 	fTempPerm173;
	float 	fTempPerm174;
	float 	fRec78[2];
	float 	fTempPerm175;
	float 	fTempPerm176;
	float 	fTempPerm177;
	float 	fTempPerm178;
	int 	iRec80[2];
	int 	iTempPerm179;
	float 	fTempPerm180;
	float 	fRec79[2];
	FAUSTFLOAT 	fslider94;
	float 	fTempPerm181;
	float 	fRec81[2];
	float 	fTempPerm182;
	FAUSTFLOAT 	fslider95;
	FAUSTFLOAT 	fbutton2;
	float 	fRec83[2];
	int 	iTempPerm183;
	int 	iTempPerm184;
	float 	fRec82[2];
	float 	fRec84[2];
	float 	fTempPerm185;
	float 	fTempPerm186;
	float 	fTempPerm187;
	float 	fRec85[2];
	float 	fTempPerm188;
	float 	fRec87[2];
	int 	iTempPerm189;
	int 	iTempPerm190;
	float 	fRec86[2];
	float 	fRec88[2];
	float 	fTempPerm191;
	float 	fTempPerm192;
	float 	fTempPerm193;
	float 	fTempPerm194;
	float 	fRec89[2];
	float 	fTempPerm195;
	float 	fRec91[2];
	int 	iTempPerm196;
	int 	iTempPerm197;
	float 	fRec90[2];
	float 	fRec92[2];
	float 	fTempPerm198;
	float 	fTempPerm199;
	float 	fTempPerm200;
	float 	fTempPerm201;
	float 	fRec93[2];
	float 	fTempPerm202;
	float 	fRec95[2];
	int 	iTempPerm203;
	int 	iTempPerm204;
	float 	fRec94[2];
	float 	fRec96[2];
	float 	fTempPerm205;
	float 	fTempPerm206;
	float 	fTempPerm207;
	float 	fTempPerm208;
	float 	fRec97[2];
	float 	fRec99[2];
	int 	iTempPerm209;
	int 	iTempPerm210;
	float 	fRec98[2];
	float 	fRec100[2];
	float 	fTempPerm211;
	float 	fTempPerm212;
	float 	fTempPerm213;
	float 	fRec101[2];
	float 	fTempPerm214;
	float 	fRec103[2];
	int 	iTempPerm215;
	int 	iTempPerm216;
	float 	fRec102[2];
	float 	fRec104[2];
	float 	fTempPerm217;
	float 	fTempPerm218;
	float 	fTempPerm219;
	float 	fRec105[2];
	float 	fTempPerm220;
	float 	fTempPerm221;
	float 	fRec106[2];
	float 	fTempPerm222;
	float 	fTempPerm223;
	float 	fTempPerm224;
	float 	fTempPerm225;
	float 	fTempPerm226;
	float 	fTempPerm227;
	float 	fRec107[2];
	float 	fTempPerm228;
	float 	fTempPerm229;
	float 	fTempPerm230;
	float 	fTempPerm231;
	float 	fTempPerm232;
	float 	fTempPerm233;
	float 	fTempPerm234;
	float 	fTempPerm235;
	float 	fTempPerm236;
	float 	fRec108[2];
	float 	fTempPerm237;
	float 	fTempPerm238;
	float 	fRec109[2];
	float 	fTempPerm239;
	float 	fTempPerm240;
	float 	fTempPerm241;
	float 	fTempPerm242;
	float 	fTempPerm243;
	float 	fTempPerm244;
	float 	fRec110[2];
	float 	fTempPerm245;
	float 	fTempPerm246;
	float 	fTempPerm247;
	float 	fTempPerm248;
	float 	fRec111[2];
	float 	fTempPerm249;
	float 	fTempPerm250;
	float 	fRec112[2];
	float 	fTempPerm251;
	float 	fTempPerm252;
	float 	fTempPerm253;
	float 	fTempPerm254;
	float 	fRec113[2];
	float 	fTempPerm255;
	float 	fTempPerm256;
	float 	fRec114[2];
	float 	fTempPerm257;
	float 	fRec115[2];
	float 	fTempPerm258;
	float 	fTempPerm259;
	float 	fRec116[2];
	float 	fTempPerm260;
	float 	fTempPerm261;
	float 	fTempPerm262;
	float 	fRec117[2];
	float 	fTempPerm263;
	float 	fTempPerm264;
	float 	fRec118[2];
	float 	fTempPerm265;
	float 	fTempPerm266;
	float 	fTempPerm267;
	float 	fTempPerm268;
	int 	iRec120[2];
	int 	iTempPerm269;
	float 	fTempPerm270;
	float 	fRec119[2];
	FAUSTFLOAT 	fslider96;
	float 	fTempPerm271;
	float 	fRec121[2];
	float 	fTempPerm272;
	FAUSTFLOAT 	fslider97;
	FAUSTFLOAT 	fbutton3;
	float 	fRec123[2];
	int 	iTempPerm273;
	int 	iTempPerm274;
	float 	fRec122[2];
	float 	fRec124[2];
	float 	fTempPerm275;
	float 	fTempPerm276;
	float 	fTempPerm277;
	float 	fRec125[2];
	float 	fTempPerm278;
	float 	fRec127[2];
	int 	iTempPerm279;
	int 	iTempPerm280;
	float 	fRec126[2];
	float 	fRec128[2];
	float 	fTempPerm281;
	float 	fTempPerm282;
	float 	fTempPerm283;
	float 	fTempPerm284;
	float 	fRec129[2];
	float 	fTempPerm285;
	float 	fRec131[2];
	int 	iTempPerm286;
	int 	iTempPerm287;
	float 	fRec130[2];
	float 	fRec132[2];
	float 	fTempPerm288;
	float 	fTempPerm289;
	float 	fTempPerm290;
	float 	fTempPerm291;
	float 	fRec133[2];
	float 	fTempPerm292;
	float 	fRec135[2];
	int 	iTempPerm293;
	int 	iTempPerm294;
	float 	fRec134[2];
	float 	fRec136[2];
	float 	fTempPerm295;
	float 	fTempPerm296;
	float 	fTempPerm297;
	float 	fTempPerm298;
	float 	fRec137[2];
	float 	fRec139[2];
	int 	iTempPerm299;
	int 	iTempPerm300;
	float 	fRec138[2];
	float 	fRec140[2];
	float 	fTempPerm301;
	float 	fTempPerm302;
	float 	fTempPerm303;
	float 	fRec141[2];
	float 	fTempPerm304;
	float 	fRec143[2];
	int 	iTempPerm305;
	int 	iTempPerm306;
	float 	fRec142[2];
	float 	fRec144[2];
	float 	fTempPerm307;
	float 	fTempPerm308;
	float 	fTempPerm309;
	float 	fRec145[2];
	float 	fTempPerm310;
	float 	fTempPerm311;
	float 	fRec146[2];
	float 	fTempPerm312;
	float 	fTempPerm313;
	float 	fTempPerm314;
	float 	fTempPerm315;
	float 	fTempPerm316;
	float 	fTempPerm317;
	float 	fRec147[2];
	float 	fTempPerm318;
	float 	fTempPerm319;
	float 	fTempPerm320;
	float 	fTempPerm321;
	float 	fTempPerm322;
	float 	fTempPerm323;
	float 	fTempPerm324;
	float 	fTempPerm325;
	float 	fTempPerm326;
	float 	fRec148[2];
	float 	fTempPerm327;
	float 	fTempPerm328;
	float 	fRec149[2];
	float 	fTempPerm329;
	float 	fTempPerm330;
	float 	fTempPerm331;
	float 	fTempPerm332;
	float 	fTempPerm333;
	float 	fTempPerm334;
	float 	fRec150[2];
	float 	fTempPerm335;
	float 	fTempPerm336;
	float 	fTempPerm337;
	float 	fTempPerm338;
	float 	fRec151[2];
	float 	fTempPerm339;
	float 	fTempPerm340;
	float 	fRec152[2];
	float 	fTempPerm341;
	float 	fTempPerm342;
	float 	fTempPerm343;
	float 	fTempPerm344;
	float 	fRec153[2];
	float 	fTempPerm345;
	float 	fTempPerm346;
	float 	fRec154[2];
	float 	fTempPerm347;
	float 	fRec155[2];
	float 	fTempPerm348;
	float 	fTempPerm349;
	float 	fRec156[2];
	float 	fTempPerm350;
	float 	fTempPerm351;
	float 	fTempPerm352;
	float 	fRec157[2];
	float 	fTempPerm353;
	float 	fTempPerm354;
	float 	fRec158[2];
	float 	fTempPerm355;
	float 	fTempPerm356;
	float 	fTempPerm357;
	float 	fTempPerm358;
	int 	iRec160[2];
	int 	iTempPerm359;
	float 	fTempPerm360;
	float 	fRec159[2];
	FAUSTFLOAT 	fslider98;
	float 	fTempPerm361;
	float 	fRec161[2];
	float 	fTempPerm362;
	FAUSTFLOAT 	fslider99;
	FAUSTFLOAT 	fbutton4;
	float 	fRec163[2];
	int 	iTempPerm363;
	int 	iTempPerm364;
	float 	fRec162[2];
	float 	fRec164[2];
	float 	fTempPerm365;
	float 	fTempPerm366;
	float 	fTempPerm367;
	float 	fRec165[2];
	float 	fTempPerm368;
	float 	fRec167[2];
	int 	iTempPerm369;
	int 	iTempPerm370;
	float 	fRec166[2];
	float 	fRec168[2];
	float 	fTempPerm371;
	float 	fTempPerm372;
	float 	fTempPerm373;
	float 	fTempPerm374;
	float 	fRec169[2];
	float 	fTempPerm375;
	float 	fRec171[2];
	int 	iTempPerm376;
	int 	iTempPerm377;
	float 	fRec170[2];
	float 	fRec172[2];
	float 	fTempPerm378;
	float 	fTempPerm379;
	float 	fTempPerm380;
	float 	fTempPerm381;
	float 	fRec173[2];
	float 	fTempPerm382;
	float 	fRec175[2];
	int 	iTempPerm383;
	int 	iTempPerm384;
	float 	fRec174[2];
	float 	fRec176[2];
	float 	fTempPerm385;
	float 	fTempPerm386;
	float 	fTempPerm387;
	float 	fTempPerm388;
	float 	fRec177[2];
	float 	fRec179[2];
	int 	iTempPerm389;
	int 	iTempPerm390;
	float 	fRec178[2];
	float 	fRec180[2];
	float 	fTempPerm391;
	float 	fTempPerm392;
	float 	fTempPerm393;
	float 	fRec181[2];
	float 	fTempPerm394;
	float 	fRec183[2];
	int 	iTempPerm395;
	int 	iTempPerm396;
	float 	fRec182[2];
	float 	fRec184[2];
	float 	fTempPerm397;
	float 	fTempPerm398;
	float 	fTempPerm399;
	float 	fRec185[2];
	float 	fTempPerm400;
	float 	fTempPerm401;
	float 	fRec186[2];
	float 	fTempPerm402;
	float 	fTempPerm403;
	float 	fTempPerm404;
	float 	fTempPerm405;
	float 	fTempPerm406;
	float 	fTempPerm407;
	float 	fRec187[2];
	float 	fTempPerm408;
	float 	fTempPerm409;
	float 	fTempPerm410;
	float 	fTempPerm411;
	float 	fTempPerm412;
	float 	fTempPerm413;
	float 	fTempPerm414;
	float 	fTempPerm415;
	float 	fTempPerm416;
	float 	fRec188[2];
	float 	fTempPerm417;
	float 	fTempPerm418;
	float 	fRec189[2];
	float 	fTempPerm419;
	float 	fTempPerm420;
	float 	fTempPerm421;
	float 	fTempPerm422;
	float 	fTempPerm423;
	float 	fTempPerm424;
	float 	fRec190[2];
	float 	fTempPerm425;
	float 	fTempPerm426;
	float 	fTempPerm427;
	float 	fTempPerm428;
	float 	fRec191[2];
	float 	fTempPerm429;
	float 	fTempPerm430;
	float 	fRec192[2];
	float 	fTempPerm431;
	float 	fTempPerm432;
	float 	fTempPerm433;
	float 	fTempPerm434;
	float 	fRec193[2];
	float 	fTempPerm435;
	float 	fTempPerm436;
	float 	fRec194[2];
	float 	fTempPerm437;
	float 	fRec195[2];
	float 	fTempPerm438;
	float 	fTempPerm439;
	float 	fRec196[2];
	float 	fTempPerm440;
	float 	fTempPerm441;
	float 	fTempPerm442;
	float 	fRec197[2];
	float 	fTempPerm443;
	float 	fTempPerm444;
	float 	fRec198[2];
	float 	fTempPerm445;
	float 	fTempPerm446;
	float 	fTempPerm447;
	float 	fTempPerm448;
	int 	iRec200[2];
	int 	iTempPerm449;
	float 	fTempPerm450;
	float 	fRec199[2];
	FAUSTFLOAT 	fslider100;
	float 	fTempPerm451;
	float 	fRec201[2];
	float 	fTempPerm452;
	FAUSTFLOAT 	fslider101;
	FAUSTFLOAT 	fbutton5;
	float 	fRec203[2];
	int 	iTempPerm453;
	int 	iTempPerm454;
	float 	fRec202[2];
	float 	fRec204[2];
	float 	fTempPerm455;
	float 	fTempPerm456;
	float 	fTempPerm457;
	float 	fRec205[2];
	float 	fTempPerm458;
	float 	fRec207[2];
	int 	iTempPerm459;
	int 	iTempPerm460;
	float 	fRec206[2];
	float 	fRec208[2];
	float 	fTempPerm461;
	float 	fTempPerm462;
	float 	fTempPerm463;
	float 	fTempPerm464;
	float 	fRec209[2];
	float 	fTempPerm465;
	float 	fRec211[2];
	int 	iTempPerm466;
	int 	iTempPerm467;
	float 	fRec210[2];
	float 	fRec212[2];
	float 	fTempPerm468;
	float 	fTempPerm469;
	float 	fTempPerm470;
	float 	fTempPerm471;
	float 	fRec213[2];
	float 	fTempPerm472;
	float 	fRec215[2];
	int 	iTempPerm473;
	int 	iTempPerm474;
	float 	fRec214[2];
	float 	fRec216[2];
	float 	fTempPerm475;
	float 	fTempPerm476;
	float 	fTempPerm477;
	float 	fTempPerm478;
	float 	fRec217[2];
	float 	fRec219[2];
	int 	iTempPerm479;
	int 	iTempPerm480;
	float 	fRec218[2];
	float 	fRec220[2];
	float 	fTempPerm481;
	float 	fTempPerm482;
	float 	fTempPerm483;
	float 	fRec221[2];
	float 	fTempPerm484;
	float 	fRec223[2];
	int 	iTempPerm485;
	int 	iTempPerm486;
	float 	fRec222[2];
	float 	fRec224[2];
	float 	fTempPerm487;
	float 	fTempPerm488;
	float 	fTempPerm489;
	float 	fRec225[2];
	float 	fTempPerm490;
	float 	fTempPerm491;
	float 	fRec226[2];
	float 	fTempPerm492;
	float 	fTempPerm493;
	float 	fTempPerm494;
	float 	fTempPerm495;
	float 	fTempPerm496;
	float 	fTempPerm497;
	float 	fRec227[2];
	float 	fTempPerm498;
	float 	fTempPerm499;
	float 	fTempPerm500;
	float 	fTempPerm501;
	float 	fTempPerm502;
	float 	fTempPerm503;
	float 	fTempPerm504;
	float 	fTempPerm505;
	float 	fTempPerm506;
	float 	fRec228[2];
	float 	fTempPerm507;
	float 	fTempPerm508;
	float 	fRec229[2];
	float 	fTempPerm509;
	float 	fTempPerm510;
	float 	fTempPerm511;
	float 	fTempPerm512;
	float 	fTempPerm513;
	float 	fTempPerm514;
	float 	fRec230[2];
	float 	fTempPerm515;
	float 	fTempPerm516;
	float 	fTempPerm517;
	float 	fTempPerm518;
	float 	fRec231[2];
	float 	fTempPerm519;
	float 	fTempPerm520;
	float 	fRec232[2];
	float 	fTempPerm521;
	float 	fTempPerm522;
	float 	fTempPerm523;
	float 	fTempPerm524;
	float 	fRec233[2];
	float 	fTempPerm525;
	float 	fTempPerm526;
	float 	fRec234[2];
	float 	fTempPerm527;
	float 	fRec235[2];
	float 	fTempPerm528;
	float 	fTempPerm529;
	float 	fRec236[2];
	float 	fTempPerm530;
	float 	fTempPerm531;
	float 	fTempPerm532;
	float 	fRec237[2];
	float 	fTempPerm533;
	float 	fTempPerm534;
	float 	fRec238[2];
	float 	fTempPerm535;
	float 	fTempPerm536;
	float 	fTempPerm537;
	float 	fTempPerm538;
	int 	iRec240[2];
	int 	iTempPerm539;
	float 	fTempPerm540;
	float 	fRec239[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filename", "dxotto");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "dxotto");
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
		fTempPerm2 = 0;
		iTempPerm3 = 0;
		iTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		iTempPerm9 = 0;
		iTempPerm10 = 0;
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
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		iTempPerm23 = 0;
		iTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		iTempPerm29 = 0;
		iTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		iTempPerm35 = 0;
		iTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fTempPerm59 = 0;
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
		fTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		fTempPerm73 = 0;
		fTempPerm74 = 0;
		fTempPerm75 = 0;
		fTempPerm76 = 0;
		fTempPerm77 = 0;
		fTempPerm78 = 0;
		fTempPerm79 = 0;
		fTempPerm80 = 0;
		fTempPerm81 = 0;
		fTempPerm82 = 0;
		fTempPerm83 = 0;
		fTempPerm84 = 0;
		fTempPerm85 = 0;
		fTempPerm86 = 0;
		fTempPerm87 = 0;
		fTempPerm88 = 0;
		iTempPerm89 = 0;
		fConst2 = (6.9100000000000001f / fConst0);
		fTempPerm90 = 0;
		fTempPerm91 = 0;
		fTempPerm92 = 0;
		iTempPerm93 = 0;
		iTempPerm94 = 0;
		fTempPerm95 = 0;
		fTempPerm96 = 0;
		fTempPerm97 = 0;
		fTempPerm98 = 0;
		iTempPerm99 = 0;
		iTempPerm100 = 0;
		fTempPerm101 = 0;
		fTempPerm102 = 0;
		fTempPerm103 = 0;
		fTempPerm104 = 0;
		fTempPerm105 = 0;
		iTempPerm106 = 0;
		iTempPerm107 = 0;
		fTempPerm108 = 0;
		fTempPerm109 = 0;
		fTempPerm110 = 0;
		fTempPerm111 = 0;
		fTempPerm112 = 0;
		iTempPerm113 = 0;
		iTempPerm114 = 0;
		fTempPerm115 = 0;
		fTempPerm116 = 0;
		fTempPerm117 = 0;
		fTempPerm118 = 0;
		iTempPerm119 = 0;
		iTempPerm120 = 0;
		fTempPerm121 = 0;
		fTempPerm122 = 0;
		fTempPerm123 = 0;
		fTempPerm124 = 0;
		iTempPerm125 = 0;
		iTempPerm126 = 0;
		fTempPerm127 = 0;
		fTempPerm128 = 0;
		fTempPerm129 = 0;
		fTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		fTempPerm133 = 0;
		fTempPerm134 = 0;
		fTempPerm135 = 0;
		fTempPerm136 = 0;
		fTempPerm137 = 0;
		fTempPerm138 = 0;
		fTempPerm139 = 0;
		fTempPerm140 = 0;
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
		fTempPerm161 = 0;
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
		fTempPerm173 = 0;
		fTempPerm174 = 0;
		fTempPerm175 = 0;
		fTempPerm176 = 0;
		fTempPerm177 = 0;
		fTempPerm178 = 0;
		iTempPerm179 = 0;
		fTempPerm180 = 0;
		fTempPerm181 = 0;
		fTempPerm182 = 0;
		iTempPerm183 = 0;
		iTempPerm184 = 0;
		fTempPerm185 = 0;
		fTempPerm186 = 0;
		fTempPerm187 = 0;
		fTempPerm188 = 0;
		iTempPerm189 = 0;
		iTempPerm190 = 0;
		fTempPerm191 = 0;
		fTempPerm192 = 0;
		fTempPerm193 = 0;
		fTempPerm194 = 0;
		fTempPerm195 = 0;
		iTempPerm196 = 0;
		iTempPerm197 = 0;
		fTempPerm198 = 0;
		fTempPerm199 = 0;
		fTempPerm200 = 0;
		fTempPerm201 = 0;
		fTempPerm202 = 0;
		iTempPerm203 = 0;
		iTempPerm204 = 0;
		fTempPerm205 = 0;
		fTempPerm206 = 0;
		fTempPerm207 = 0;
		fTempPerm208 = 0;
		iTempPerm209 = 0;
		iTempPerm210 = 0;
		fTempPerm211 = 0;
		fTempPerm212 = 0;
		fTempPerm213 = 0;
		fTempPerm214 = 0;
		iTempPerm215 = 0;
		iTempPerm216 = 0;
		fTempPerm217 = 0;
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
		fTempPerm229 = 0;
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
		fTempPerm241 = 0;
		fTempPerm242 = 0;
		fTempPerm243 = 0;
		fTempPerm244 = 0;
		fTempPerm245 = 0;
		fTempPerm246 = 0;
		fTempPerm247 = 0;
		fTempPerm248 = 0;
		fTempPerm249 = 0;
		fTempPerm250 = 0;
		fTempPerm251 = 0;
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
		fTempPerm263 = 0;
		fTempPerm264 = 0;
		fTempPerm265 = 0;
		fTempPerm266 = 0;
		fTempPerm267 = 0;
		fTempPerm268 = 0;
		iTempPerm269 = 0;
		fTempPerm270 = 0;
		fTempPerm271 = 0;
		fTempPerm272 = 0;
		iTempPerm273 = 0;
		iTempPerm274 = 0;
		fTempPerm275 = 0;
		fTempPerm276 = 0;
		fTempPerm277 = 0;
		fTempPerm278 = 0;
		iTempPerm279 = 0;
		iTempPerm280 = 0;
		fTempPerm281 = 0;
		fTempPerm282 = 0;
		fTempPerm283 = 0;
		fTempPerm284 = 0;
		fTempPerm285 = 0;
		iTempPerm286 = 0;
		iTempPerm287 = 0;
		fTempPerm288 = 0;
		fTempPerm289 = 0;
		fTempPerm290 = 0;
		fTempPerm291 = 0;
		fTempPerm292 = 0;
		iTempPerm293 = 0;
		iTempPerm294 = 0;
		fTempPerm295 = 0;
		fTempPerm296 = 0;
		fTempPerm297 = 0;
		fTempPerm298 = 0;
		iTempPerm299 = 0;
		iTempPerm300 = 0;
		fTempPerm301 = 0;
		fTempPerm302 = 0;
		fTempPerm303 = 0;
		fTempPerm304 = 0;
		iTempPerm305 = 0;
		iTempPerm306 = 0;
		fTempPerm307 = 0;
		fTempPerm308 = 0;
		fTempPerm309 = 0;
		fTempPerm310 = 0;
		fTempPerm311 = 0;
		fTempPerm312 = 0;
		fTempPerm313 = 0;
		fTempPerm314 = 0;
		fTempPerm315 = 0;
		fTempPerm316 = 0;
		fTempPerm317 = 0;
		fTempPerm318 = 0;
		fTempPerm319 = 0;
		fTempPerm320 = 0;
		fTempPerm321 = 0;
		fTempPerm322 = 0;
		fTempPerm323 = 0;
		fTempPerm324 = 0;
		fTempPerm325 = 0;
		fTempPerm326 = 0;
		fTempPerm327 = 0;
		fTempPerm328 = 0;
		fTempPerm329 = 0;
		fTempPerm330 = 0;
		fTempPerm331 = 0;
		fTempPerm332 = 0;
		fTempPerm333 = 0;
		fTempPerm334 = 0;
		fTempPerm335 = 0;
		fTempPerm336 = 0;
		fTempPerm337 = 0;
		fTempPerm338 = 0;
		fTempPerm339 = 0;
		fTempPerm340 = 0;
		fTempPerm341 = 0;
		fTempPerm342 = 0;
		fTempPerm343 = 0;
		fTempPerm344 = 0;
		fTempPerm345 = 0;
		fTempPerm346 = 0;
		fTempPerm347 = 0;
		fTempPerm348 = 0;
		fTempPerm349 = 0;
		fTempPerm350 = 0;
		fTempPerm351 = 0;
		fTempPerm352 = 0;
		fTempPerm353 = 0;
		fTempPerm354 = 0;
		fTempPerm355 = 0;
		fTempPerm356 = 0;
		fTempPerm357 = 0;
		fTempPerm358 = 0;
		iTempPerm359 = 0;
		fTempPerm360 = 0;
		fTempPerm361 = 0;
		fTempPerm362 = 0;
		iTempPerm363 = 0;
		iTempPerm364 = 0;
		fTempPerm365 = 0;
		fTempPerm366 = 0;
		fTempPerm367 = 0;
		fTempPerm368 = 0;
		iTempPerm369 = 0;
		iTempPerm370 = 0;
		fTempPerm371 = 0;
		fTempPerm372 = 0;
		fTempPerm373 = 0;
		fTempPerm374 = 0;
		fTempPerm375 = 0;
		iTempPerm376 = 0;
		iTempPerm377 = 0;
		fTempPerm378 = 0;
		fTempPerm379 = 0;
		fTempPerm380 = 0;
		fTempPerm381 = 0;
		fTempPerm382 = 0;
		iTempPerm383 = 0;
		iTempPerm384 = 0;
		fTempPerm385 = 0;
		fTempPerm386 = 0;
		fTempPerm387 = 0;
		fTempPerm388 = 0;
		iTempPerm389 = 0;
		iTempPerm390 = 0;
		fTempPerm391 = 0;
		fTempPerm392 = 0;
		fTempPerm393 = 0;
		fTempPerm394 = 0;
		iTempPerm395 = 0;
		iTempPerm396 = 0;
		fTempPerm397 = 0;
		fTempPerm398 = 0;
		fTempPerm399 = 0;
		fTempPerm400 = 0;
		fTempPerm401 = 0;
		fTempPerm402 = 0;
		fTempPerm403 = 0;
		fTempPerm404 = 0;
		fTempPerm405 = 0;
		fTempPerm406 = 0;
		fTempPerm407 = 0;
		fTempPerm408 = 0;
		fTempPerm409 = 0;
		fTempPerm410 = 0;
		fTempPerm411 = 0;
		fTempPerm412 = 0;
		fTempPerm413 = 0;
		fTempPerm414 = 0;
		fTempPerm415 = 0;
		fTempPerm416 = 0;
		fTempPerm417 = 0;
		fTempPerm418 = 0;
		fTempPerm419 = 0;
		fTempPerm420 = 0;
		fTempPerm421 = 0;
		fTempPerm422 = 0;
		fTempPerm423 = 0;
		fTempPerm424 = 0;
		fTempPerm425 = 0;
		fTempPerm426 = 0;
		fTempPerm427 = 0;
		fTempPerm428 = 0;
		fTempPerm429 = 0;
		fTempPerm430 = 0;
		fTempPerm431 = 0;
		fTempPerm432 = 0;
		fTempPerm433 = 0;
		fTempPerm434 = 0;
		fTempPerm435 = 0;
		fTempPerm436 = 0;
		fTempPerm437 = 0;
		fTempPerm438 = 0;
		fTempPerm439 = 0;
		fTempPerm440 = 0;
		fTempPerm441 = 0;
		fTempPerm442 = 0;
		fTempPerm443 = 0;
		fTempPerm444 = 0;
		fTempPerm445 = 0;
		fTempPerm446 = 0;
		fTempPerm447 = 0;
		fTempPerm448 = 0;
		iTempPerm449 = 0;
		fTempPerm450 = 0;
		fTempPerm451 = 0;
		fTempPerm452 = 0;
		iTempPerm453 = 0;
		iTempPerm454 = 0;
		fTempPerm455 = 0;
		fTempPerm456 = 0;
		fTempPerm457 = 0;
		fTempPerm458 = 0;
		iTempPerm459 = 0;
		iTempPerm460 = 0;
		fTempPerm461 = 0;
		fTempPerm462 = 0;
		fTempPerm463 = 0;
		fTempPerm464 = 0;
		fTempPerm465 = 0;
		iTempPerm466 = 0;
		iTempPerm467 = 0;
		fTempPerm468 = 0;
		fTempPerm469 = 0;
		fTempPerm470 = 0;
		fTempPerm471 = 0;
		fTempPerm472 = 0;
		iTempPerm473 = 0;
		iTempPerm474 = 0;
		fTempPerm475 = 0;
		fTempPerm476 = 0;
		fTempPerm477 = 0;
		fTempPerm478 = 0;
		iTempPerm479 = 0;
		iTempPerm480 = 0;
		fTempPerm481 = 0;
		fTempPerm482 = 0;
		fTempPerm483 = 0;
		fTempPerm484 = 0;
		iTempPerm485 = 0;
		iTempPerm486 = 0;
		fTempPerm487 = 0;
		fTempPerm488 = 0;
		fTempPerm489 = 0;
		fTempPerm490 = 0;
		fTempPerm491 = 0;
		fTempPerm492 = 0;
		fTempPerm493 = 0;
		fTempPerm494 = 0;
		fTempPerm495 = 0;
		fTempPerm496 = 0;
		fTempPerm497 = 0;
		fTempPerm498 = 0;
		fTempPerm499 = 0;
		fTempPerm500 = 0;
		fTempPerm501 = 0;
		fTempPerm502 = 0;
		fTempPerm503 = 0;
		fTempPerm504 = 0;
		fTempPerm505 = 0;
		fTempPerm506 = 0;
		fTempPerm507 = 0;
		fTempPerm508 = 0;
		fTempPerm509 = 0;
		fTempPerm510 = 0;
		fTempPerm511 = 0;
		fTempPerm512 = 0;
		fTempPerm513 = 0;
		fTempPerm514 = 0;
		fTempPerm515 = 0;
		fTempPerm516 = 0;
		fTempPerm517 = 0;
		fTempPerm518 = 0;
		fTempPerm519 = 0;
		fTempPerm520 = 0;
		fTempPerm521 = 0;
		fTempPerm522 = 0;
		fTempPerm523 = 0;
		fTempPerm524 = 0;
		fTempPerm525 = 0;
		fTempPerm526 = 0;
		fTempPerm527 = 0;
		fTempPerm528 = 0;
		fTempPerm529 = 0;
		fTempPerm530 = 0;
		fTempPerm531 = 0;
		fTempPerm532 = 0;
		fTempPerm533 = 0;
		fTempPerm534 = 0;
		fTempPerm535 = 0;
		fTempPerm536 = 0;
		fTempPerm537 = 0;
		fTempPerm538 = 0;
		iTempPerm539 = 0;
		fTempPerm540 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 1.0f;
		fslider2 = 440.0f;
		fslider3 = 0.0f;
		fslider4 = 0.0f;
		fslider5 = 1.0f;
		fslider6 = 99.0f;
		fslider7 = 99.0f;
		fslider8 = 1.0f;
		fslider9 = 1.0f;
		fslider10 = 3.0f;
		fslider11 = 1.0f;
		fslider12 = 1.0f;
		fslider13 = 1.0f;
		fslider14 = 1.0f;
		fslider15 = 1.0f;
		fslider16 = 1.0f;
		fbutton0 = 0.0;
		fslider17 = 1.0f;
		fslider18 = 0.0f;
		fslider19 = 0.0f;
		fslider20 = 1.0f;
		fslider21 = 99.0f;
		fslider22 = 99.0f;
		fslider23 = 1.0f;
		fslider24 = 3.0f;
		fslider25 = 1.0f;
		fslider26 = 1.0f;
		fslider27 = 1.0f;
		fslider28 = 1.0f;
		fslider29 = 1.0f;
		fslider30 = 1.0f;
		fslider31 = 1.0f;
		fslider32 = 0.0f;
		fslider33 = 0.0f;
		fslider34 = 1.0f;
		fslider35 = 99.0f;
		fslider36 = 99.0f;
		fslider37 = 1.0f;
		fslider38 = 3.0f;
		fslider39 = 1.0f;
		fslider40 = 1.0f;
		fslider41 = 1.0f;
		fslider42 = 1.0f;
		fslider43 = 1.0f;
		fslider44 = 1.0f;
		fslider45 = 1.0f;
		fslider46 = 0.0f;
		fslider47 = 0.0f;
		fslider48 = 1.0f;
		fslider49 = 99.0f;
		fslider50 = 99.0f;
		fslider51 = 1.0f;
		fslider52 = 3.0f;
		fslider53 = 1.0f;
		fslider54 = 1.0f;
		fslider55 = 1.0f;
		fslider56 = 1.0f;
		fslider57 = 1.0f;
		fslider58 = 1.0f;
		fslider59 = 1.0f;
		fslider60 = 0.0f;
		fslider61 = 0.0f;
		fslider62 = 1.0f;
		fslider63 = 99.0f;
		fslider64 = 99.0f;
		fslider65 = 1.0f;
		fslider66 = 3.0f;
		fslider67 = 1.0f;
		fslider68 = 1.0f;
		fslider69 = 1.0f;
		fslider70 = 1.0f;
		fslider71 = 1.0f;
		fslider72 = 1.0f;
		fslider73 = 1.0f;
		fslider74 = 0.0f;
		fslider75 = 0.0f;
		fslider76 = 1.0f;
		fslider77 = 99.0f;
		fslider78 = 99.0f;
		fslider79 = 1.0f;
		fslider80 = 3.0f;
		fslider81 = 1.0f;
		fslider82 = 1.0f;
		fslider83 = 1.0f;
		fslider84 = 1.0f;
		fslider85 = 1.0f;
		fslider86 = 1.0f;
		fslider87 = 0.0f;
		fslider88 = 0.0f;
		fslider89 = 0.0f;
		fslider90 = 0.001f;
		fslider91 = 1.0f;
		fslider92 = 440.0f;
		fslider93 = 1.0f;
		fbutton1 = 0.0;
		fslider94 = 440.0f;
		fslider95 = 1.0f;
		fbutton2 = 0.0;
		fslider96 = 440.0f;
		fslider97 = 1.0f;
		fbutton3 = 0.0;
		fslider98 = 440.0f;
		fslider99 = 1.0f;
		fbutton4 = 0.0;
		fslider100 = 440.0f;
		fslider101 = 1.0f;
		fbutton5 = 0.0;
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
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) iRec40[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<2; i++) fRec56[i] = 0;
		for (int i=0; i<2; i++) fRec57[i] = 0;
		for (int i=0; i<2; i++) fRec59[i] = 0;
		for (int i=0; i<2; i++) fRec58[i] = 0;
		for (int i=0; i<2; i++) fRec60[i] = 0;
		for (int i=0; i<2; i++) fRec61[i] = 0;
		for (int i=0; i<2; i++) fRec63[i] = 0;
		for (int i=0; i<2; i++) fRec62[i] = 0;
		for (int i=0; i<2; i++) fRec64[i] = 0;
		for (int i=0; i<2; i++) fRec65[i] = 0;
		for (int i=0; i<2; i++) fRec66[i] = 0;
		for (int i=0; i<2; i++) fRec67[i] = 0;
		for (int i=0; i<2; i++) fRec68[i] = 0;
		for (int i=0; i<2; i++) fRec69[i] = 0;
		for (int i=0; i<2; i++) fRec70[i] = 0;
		for (int i=0; i<2; i++) fRec71[i] = 0;
		for (int i=0; i<2; i++) fRec72[i] = 0;
		for (int i=0; i<2; i++) fRec73[i] = 0;
		for (int i=0; i<2; i++) fRec74[i] = 0;
		for (int i=0; i<2; i++) fRec75[i] = 0;
		for (int i=0; i<2; i++) fRec76[i] = 0;
		for (int i=0; i<2; i++) fRec77[i] = 0;
		for (int i=0; i<2; i++) fRec78[i] = 0;
		for (int i=0; i<2; i++) iRec80[i] = 0;
		for (int i=0; i<2; i++) fRec79[i] = 0;
		for (int i=0; i<2; i++) fRec81[i] = 0;
		for (int i=0; i<2; i++) fRec83[i] = 0;
		for (int i=0; i<2; i++) fRec82[i] = 0;
		for (int i=0; i<2; i++) fRec84[i] = 0;
		for (int i=0; i<2; i++) fRec85[i] = 0;
		for (int i=0; i<2; i++) fRec87[i] = 0;
		for (int i=0; i<2; i++) fRec86[i] = 0;
		for (int i=0; i<2; i++) fRec88[i] = 0;
		for (int i=0; i<2; i++) fRec89[i] = 0;
		for (int i=0; i<2; i++) fRec91[i] = 0;
		for (int i=0; i<2; i++) fRec90[i] = 0;
		for (int i=0; i<2; i++) fRec92[i] = 0;
		for (int i=0; i<2; i++) fRec93[i] = 0;
		for (int i=0; i<2; i++) fRec95[i] = 0;
		for (int i=0; i<2; i++) fRec94[i] = 0;
		for (int i=0; i<2; i++) fRec96[i] = 0;
		for (int i=0; i<2; i++) fRec97[i] = 0;
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) fRec98[i] = 0;
		for (int i=0; i<2; i++) fRec100[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) fRec102[i] = 0;
		for (int i=0; i<2; i++) fRec104[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<2; i++) fRec106[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) fRec108[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<2; i++) fRec110[i] = 0;
		for (int i=0; i<2; i++) fRec111[i] = 0;
		for (int i=0; i<2; i++) fRec112[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) fRec114[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<2; i++) fRec116[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<2; i++) fRec118[i] = 0;
		for (int i=0; i<2; i++) iRec120[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
		for (int i=0; i<2; i++) fRec122[i] = 0;
		for (int i=0; i<2; i++) fRec124[i] = 0;
		for (int i=0; i<2; i++) fRec125[i] = 0;
		for (int i=0; i<2; i++) fRec127[i] = 0;
		for (int i=0; i<2; i++) fRec126[i] = 0;
		for (int i=0; i<2; i++) fRec128[i] = 0;
		for (int i=0; i<2; i++) fRec129[i] = 0;
		for (int i=0; i<2; i++) fRec131[i] = 0;
		for (int i=0; i<2; i++) fRec130[i] = 0;
		for (int i=0; i<2; i++) fRec132[i] = 0;
		for (int i=0; i<2; i++) fRec133[i] = 0;
		for (int i=0; i<2; i++) fRec135[i] = 0;
		for (int i=0; i<2; i++) fRec134[i] = 0;
		for (int i=0; i<2; i++) fRec136[i] = 0;
		for (int i=0; i<2; i++) fRec137[i] = 0;
		for (int i=0; i<2; i++) fRec139[i] = 0;
		for (int i=0; i<2; i++) fRec138[i] = 0;
		for (int i=0; i<2; i++) fRec140[i] = 0;
		for (int i=0; i<2; i++) fRec141[i] = 0;
		for (int i=0; i<2; i++) fRec143[i] = 0;
		for (int i=0; i<2; i++) fRec142[i] = 0;
		for (int i=0; i<2; i++) fRec144[i] = 0;
		for (int i=0; i<2; i++) fRec145[i] = 0;
		for (int i=0; i<2; i++) fRec146[i] = 0;
		for (int i=0; i<2; i++) fRec147[i] = 0;
		for (int i=0; i<2; i++) fRec148[i] = 0;
		for (int i=0; i<2; i++) fRec149[i] = 0;
		for (int i=0; i<2; i++) fRec150[i] = 0;
		for (int i=0; i<2; i++) fRec151[i] = 0;
		for (int i=0; i<2; i++) fRec152[i] = 0;
		for (int i=0; i<2; i++) fRec153[i] = 0;
		for (int i=0; i<2; i++) fRec154[i] = 0;
		for (int i=0; i<2; i++) fRec155[i] = 0;
		for (int i=0; i<2; i++) fRec156[i] = 0;
		for (int i=0; i<2; i++) fRec157[i] = 0;
		for (int i=0; i<2; i++) fRec158[i] = 0;
		for (int i=0; i<2; i++) iRec160[i] = 0;
		for (int i=0; i<2; i++) fRec159[i] = 0;
		for (int i=0; i<2; i++) fRec161[i] = 0;
		for (int i=0; i<2; i++) fRec163[i] = 0;
		for (int i=0; i<2; i++) fRec162[i] = 0;
		for (int i=0; i<2; i++) fRec164[i] = 0;
		for (int i=0; i<2; i++) fRec165[i] = 0;
		for (int i=0; i<2; i++) fRec167[i] = 0;
		for (int i=0; i<2; i++) fRec166[i] = 0;
		for (int i=0; i<2; i++) fRec168[i] = 0;
		for (int i=0; i<2; i++) fRec169[i] = 0;
		for (int i=0; i<2; i++) fRec171[i] = 0;
		for (int i=0; i<2; i++) fRec170[i] = 0;
		for (int i=0; i<2; i++) fRec172[i] = 0;
		for (int i=0; i<2; i++) fRec173[i] = 0;
		for (int i=0; i<2; i++) fRec175[i] = 0;
		for (int i=0; i<2; i++) fRec174[i] = 0;
		for (int i=0; i<2; i++) fRec176[i] = 0;
		for (int i=0; i<2; i++) fRec177[i] = 0;
		for (int i=0; i<2; i++) fRec179[i] = 0;
		for (int i=0; i<2; i++) fRec178[i] = 0;
		for (int i=0; i<2; i++) fRec180[i] = 0;
		for (int i=0; i<2; i++) fRec181[i] = 0;
		for (int i=0; i<2; i++) fRec183[i] = 0;
		for (int i=0; i<2; i++) fRec182[i] = 0;
		for (int i=0; i<2; i++) fRec184[i] = 0;
		for (int i=0; i<2; i++) fRec185[i] = 0;
		for (int i=0; i<2; i++) fRec186[i] = 0;
		for (int i=0; i<2; i++) fRec187[i] = 0;
		for (int i=0; i<2; i++) fRec188[i] = 0;
		for (int i=0; i<2; i++) fRec189[i] = 0;
		for (int i=0; i<2; i++) fRec190[i] = 0;
		for (int i=0; i<2; i++) fRec191[i] = 0;
		for (int i=0; i<2; i++) fRec192[i] = 0;
		for (int i=0; i<2; i++) fRec193[i] = 0;
		for (int i=0; i<2; i++) fRec194[i] = 0;
		for (int i=0; i<2; i++) fRec195[i] = 0;
		for (int i=0; i<2; i++) fRec196[i] = 0;
		for (int i=0; i<2; i++) fRec197[i] = 0;
		for (int i=0; i<2; i++) fRec198[i] = 0;
		for (int i=0; i<2; i++) iRec200[i] = 0;
		for (int i=0; i<2; i++) fRec199[i] = 0;
		for (int i=0; i<2; i++) fRec201[i] = 0;
		for (int i=0; i<2; i++) fRec203[i] = 0;
		for (int i=0; i<2; i++) fRec202[i] = 0;
		for (int i=0; i<2; i++) fRec204[i] = 0;
		for (int i=0; i<2; i++) fRec205[i] = 0;
		for (int i=0; i<2; i++) fRec207[i] = 0;
		for (int i=0; i<2; i++) fRec206[i] = 0;
		for (int i=0; i<2; i++) fRec208[i] = 0;
		for (int i=0; i<2; i++) fRec209[i] = 0;
		for (int i=0; i<2; i++) fRec211[i] = 0;
		for (int i=0; i<2; i++) fRec210[i] = 0;
		for (int i=0; i<2; i++) fRec212[i] = 0;
		for (int i=0; i<2; i++) fRec213[i] = 0;
		for (int i=0; i<2; i++) fRec215[i] = 0;
		for (int i=0; i<2; i++) fRec214[i] = 0;
		for (int i=0; i<2; i++) fRec216[i] = 0;
		for (int i=0; i<2; i++) fRec217[i] = 0;
		for (int i=0; i<2; i++) fRec219[i] = 0;
		for (int i=0; i<2; i++) fRec218[i] = 0;
		for (int i=0; i<2; i++) fRec220[i] = 0;
		for (int i=0; i<2; i++) fRec221[i] = 0;
		for (int i=0; i<2; i++) fRec223[i] = 0;
		for (int i=0; i<2; i++) fRec222[i] = 0;
		for (int i=0; i<2; i++) fRec224[i] = 0;
		for (int i=0; i<2; i++) fRec225[i] = 0;
		for (int i=0; i<2; i++) fRec226[i] = 0;
		for (int i=0; i<2; i++) fRec227[i] = 0;
		for (int i=0; i<2; i++) fRec228[i] = 0;
		for (int i=0; i<2; i++) fRec229[i] = 0;
		for (int i=0; i<2; i++) fRec230[i] = 0;
		for (int i=0; i<2; i++) fRec231[i] = 0;
		for (int i=0; i<2; i++) fRec232[i] = 0;
		for (int i=0; i<2; i++) fRec233[i] = 0;
		for (int i=0; i<2; i++) fRec234[i] = 0;
		for (int i=0; i<2; i++) fRec235[i] = 0;
		for (int i=0; i<2; i++) fRec236[i] = 0;
		for (int i=0; i<2; i++) fRec237[i] = 0;
		for (int i=0; i<2; i++) fRec238[i] = 0;
		for (int i=0; i<2; i++) iRec240[i] = 0;
		for (int i=0; i<2; i++) fRec239[i] = 0;
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
	virtual faust_dxotto* clone() {
		return new faust_dxotto();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("dxotto");
		ui_interface->addHorizontalSlider("algN", &fslider0, 0.0f, 0.0f, 31.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL1_0", &fslider14, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL1_1", &fslider28, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL1_2", &fslider42, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL1_3", &fslider56, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL1_4", &fslider70, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL1_5", &fslider84, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL2_0", &fslider12, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL2_1", &fslider26, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL2_2", &fslider40, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL2_3", &fslider54, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL2_4", &fslider68, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL2_5", &fslider82, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL3_0", &fslider9, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL3_1", &fslider23, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL3_2", &fslider37, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL3_3", &fslider51, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL3_4", &fslider65, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL3_5", &fslider79, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL4_0", &fslider5, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL4_1", &fslider20, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL4_2", &fslider34, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL4_3", &fslider48, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL4_4", &fslider62, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egL4_5", &fslider76, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR1_0", &fslider16, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR1_1", &fslider30, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR1_2", &fslider44, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR1_3", &fslider58, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR1_4", &fslider72, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR1_5", &fslider86, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR2_0", &fslider15, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR2_1", &fslider29, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR2_2", &fslider43, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR2_3", &fslider57, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR2_4", &fslider71, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR2_5", &fslider85, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR3_0", &fslider13, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR3_1", &fslider27, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR3_2", &fslider41, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR3_3", &fslider55, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR3_4", &fslider69, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR3_5", &fslider83, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR4_0", &fslider11, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR4_1", &fslider25, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR4_2", &fslider39, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR4_3", &fslider53, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR4_4", &fslider67, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("egR4_5", &fslider81, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fslider90, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider89, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider88, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider91, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("feedback", &fslider87, 0.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("keyVelSens_0", &fslider7, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("keyVelSens_1", &fslider22, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("keyVelSens_2", &fslider36, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("keyVelSens_3", &fslider50, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("keyVelSens_4", &fslider64, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("keyVelSens_5", &fslider78, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opDetune_0", &fslider4, 0.0f, -7.0f, 7.0f, 1.0f);
		ui_interface->addHorizontalSlider("opDetune_1", &fslider19, 0.0f, -7.0f, 7.0f, 1.0f);
		ui_interface->addHorizontalSlider("opDetune_2", &fslider33, 0.0f, -7.0f, 7.0f, 1.0f);
		ui_interface->addHorizontalSlider("opDetune_3", &fslider47, 0.0f, -7.0f, 7.0f, 1.0f);
		ui_interface->addHorizontalSlider("opDetune_4", &fslider61, 0.0f, -7.0f, 7.0f, 1.0f);
		ui_interface->addHorizontalSlider("opDetune_5", &fslider75, 0.0f, -7.0f, 7.0f, 1.0f);
		ui_interface->addHorizontalSlider("opFreq_0", &fslider1, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opFreq_1", &fslider17, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opFreq_2", &fslider31, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opFreq_3", &fslider45, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opFreq_4", &fslider59, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opFreq_5", &fslider73, 1.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opMode_0", &fslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("opMode_1", &fslider18, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("opMode_2", &fslider32, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("opMode_3", &fslider46, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("opMode_4", &fslider60, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("opMode_5", &fslider74, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_0", &fslider10, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_1", &fslider24, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_2", &fslider38, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_3", &fslider52, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_4", &fslider66, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_5", &fslider80, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLevel_0", &fslider6, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLevel_1", &fslider21, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLevel_2", &fslider35, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLevel_3", &fslider49, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLevel_4", &fslider63, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLevel_5", &fslider77, 99.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider100, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider101, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider96, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider97, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider92, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider93, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider98, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider99, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider94, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider95, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider2, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider8, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fslider0));
		int 	iSlow1 = (float((iSlow0 == 31)) != 0.0f);
		int 	iSlow2 = (float((iSlow0 == 30)) != 0.0f);
		int 	iSlow3 = (float((iSlow0 == 29)) != 0.0f);
		int 	iSlow4 = (float((iSlow0 == 28)) != 0.0f);
		int 	iSlow5 = (float((iSlow0 == 27)) != 0.0f);
		int 	iSlow6 = (float((iSlow0 == 26)) != 0.0f);
		int 	iSlow7 = (float((iSlow0 == 25)) != 0.0f);
		int 	iSlow8 = (float((iSlow0 == 24)) != 0.0f);
		int 	iSlow9 = (float((iSlow0 == 23)) != 0.0f);
		int 	iSlow10 = (float((iSlow0 == 22)) != 0.0f);
		int 	iSlow11 = (float((iSlow0 == 21)) != 0.0f);
		int 	iSlow12 = (float((iSlow0 == 20)) != 0.0f);
		int 	iSlow13 = (float((iSlow0 == 19)) != 0.0f);
		int 	iSlow14 = (float((iSlow0 == 18)) != 0.0f);
		int 	iSlow15 = (float((iSlow0 == 17)) != 0.0f);
		int 	iSlow16 = (float((iSlow0 == 16)) != 0.0f);
		int 	iSlow17 = (float((iSlow0 == 15)) != 0.0f);
		int 	iSlow18 = (float((iSlow0 == 14)) != 0.0f);
		int 	iSlow19 = (float((iSlow0 == 13)) != 0.0f);
		int 	iSlow20 = (float((iSlow0 == 12)) != 0.0f);
		int 	iSlow21 = (float((iSlow0 == 11)) != 0.0f);
		int 	iSlow22 = (float((iSlow0 == 10)) != 0.0f);
		int 	iSlow23 = (float((iSlow0 == 9)) != 0.0f);
		int 	iSlow24 = (float((iSlow0 == 8)) != 0.0f);
		int 	iSlow25 = (float((iSlow0 == 7)) != 0.0f);
		int 	iSlow26 = (float((iSlow0 == 6)) != 0.0f);
		int 	iSlow27 = (float((iSlow0 == 5)) != 0.0f);
		int 	iSlow28 = (float((iSlow0 == 4)) != 0.0f);
		int 	iSlow29 = (float((iSlow0 == 3)) != 0.0f);
		int 	iSlow30 = (float((iSlow0 == 2)) != 0.0f);
		int 	iSlow31 = (float((iSlow0 == 1)) != 0.0f);
		int 	iSlow32 = (float((iSlow0 == 0)) != 0.0f);
		float 	fSlow33 = float(fslider1);
		float 	fSlow34 = float(fslider2);
		int 	iSlow35 = int(float(fslider3));
		float 	fSlow36 = (0.25f * float(fslider4));
		float 	fSlow37 = (fSlow36 + ((iSlow35)?fSlow33:(fSlow34 * fSlow33)));
		float 	fSlow38 = (fConst1 * fSlow37);
		float 	fSlow39 = float(fslider5);
		float 	fSlow40 = float(fslider6);
		float 	fSlow41 = float(fslider7);
		float 	fSlow42 = float(fslider8);
		float 	fSlow43 = (0.010101010101010102f * (1.0f - (0.125f * fSlow41)));
		float 	fSlow44 = (fSlow43 + (0.0012626262626262627f * (fSlow42 * fSlow41)));
		float 	fSlow45 = (fSlow44 * fSlow40);
		float 	fSlow46 = (fSlow45 * fSlow39);
		float 	fSlow47 = powf((0.010101010101010102f * min((float)99, fSlow46)),0.69999999999999996f);
		float 	fSlow48 = powf((0.014705882352941176f * (float((fSlow46 >= 30.0f)) * min((fSlow46 + -30.0f), (float)68))),1.8f);
		float 	fSlow49 = float(fslider9);
		float 	fSlow50 = (fSlow45 * fSlow49);
		int 	iSlow51 = int((fSlow50 <= fSlow46));
		float 	fSlow52 = powf((0.010101010101010102f * min((float)99, fSlow50)),0.69999999999999996f);
		float 	fSlow53 = powf((0.014705882352941176f * (float((fSlow50 >= 30.0f)) * min((fSlow50 + -30.0f), (float)68))),1.8f);
		float 	fSlow54 = (0.057142857142857148f * float(fslider10));
		float 	fSlow55 = (fSlow54 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow37))) + 48.0f));
		float 	fSlow56 = float(fslider11);
		float 	fSlow57 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow56 + fSlow55))));
		float 	fSlow58 = max(0.001f, fabsf((((iSlow51)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow57))):max(0.0080000000000000002f, (318.0f * powf(fSlow57,12.6f)))) * (((iSlow51)?fSlow53:fSlow52) - ((iSlow51)?fSlow48:fSlow47)))));
		float 	fSlow59 = float(fslider12);
		float 	fSlow60 = (fSlow45 * fSlow59);
		int 	iSlow61 = int((fSlow50 > fSlow60));
		float 	fSlow62 = powf((0.010101010101010102f * min((float)99, fSlow60)),0.69999999999999996f);
		float 	fSlow63 = powf((0.014705882352941176f * (float((fSlow60 >= 30.0f)) * min((fSlow60 + -30.0f), (float)68))),1.8f);
		float 	fSlow64 = float(fslider13);
		float 	fSlow65 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow64 + fSlow55))));
		float 	fSlow66 = float(fslider14);
		float 	fSlow67 = (fSlow45 * fSlow66);
		float 	fSlow68 = powf((0.010101010101010102f * min((float)99, fSlow67)),0.69999999999999996f);
		float 	fSlow69 = powf((0.014705882352941176f * (float((fSlow67 >= 30.0f)) * min((fSlow67 + -30.0f), (float)68))),1.8f);
		int 	iSlow70 = int((fSlow60 > fSlow67));
		float 	fSlow71 = float(fslider15);
		float 	fSlow72 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow71 + fSlow55))));
		int 	iSlow73 = int((fSlow67 > fSlow46));
		float 	fSlow74 = float(fslider16);
		float 	fSlow75 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow74 + fSlow55))));
		float 	fSlow76 = max(0.001f, fabsf((((iSlow73)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow75))):max(0.0080000000000000002f, (318.0f * powf(fSlow75,12.6f)))) * (((iSlow73)?fSlow48:fSlow47) - ((iSlow73)?fSlow69:fSlow68)))));
		float 	fSlow77 = (fSlow76 + max(0.001f, fabsf((((iSlow70)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow72))):max(0.0080000000000000002f, (318.0f * powf(fSlow72,12.6f)))) * (((iSlow70)?fSlow63:fSlow62) - ((iSlow70)?fSlow69:fSlow68))))));
		float 	fSlow78 = (fSlow77 + max(0.001f, fabsf((((iSlow61)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow65))):max(0.0080000000000000002f, (318.0f * powf(fSlow65,12.6f)))) * (((iSlow61)?fSlow63:fSlow62) - ((iSlow61)?fSlow53:fSlow52))))));
		float 	fSlow79 = (0 - (fConst0 * (fSlow77 - fSlow78)));
		float 	fSlow80 = (fConst0 * fSlow77);
		float 	fSlow81 = (fConst0 * fSlow78);
		float 	fSlow82 = float(fbutton0);
		int 	iSlow83 = int(((fSlow82 == 0.0f) > 0));
		float 	fSlow84 = (fSlow49 - fSlow59);
		float 	fSlow85 = (0 - (fConst0 * (fSlow76 - fSlow77)));
		float 	fSlow86 = (fConst0 * fSlow76);
		float 	fSlow87 = (fSlow66 - fSlow59);
		float 	fSlow88 = (0 - ((fSlow87 * fSlow44) * fSlow40));
		float 	fSlow89 = (fSlow39 - fSlow66);
		float 	fSlow90 = (fConst1 * (0 - ((fSlow89 * fSlow44) * fSlow40)));
		int 	iSlow91 = (fSlow82 > 0.0f);
		float 	fSlow92 = float(iSlow91);
		int 	iSlow93 = int(iSlow91);
		float 	fSlow94 = (fConst0 * fSlow58);
		int 	iSlow95 = int((iSlow91 > 0));
		float 	fSlow96 = float(fslider17);
		int 	iSlow97 = int(float(fslider18));
		float 	fSlow98 = (0.25f * float(fslider19));
		float 	fSlow99 = (fSlow98 + ((iSlow97)?fSlow96:(fSlow34 * fSlow96)));
		float 	fSlow100 = (fConst1 * fSlow99);
		float 	fSlow101 = float(fslider20);
		float 	fSlow102 = float(fslider21);
		float 	fSlow103 = float(fslider22);
		float 	fSlow104 = (0.010101010101010102f * (1.0f - (0.125f * fSlow103)));
		float 	fSlow105 = (fSlow104 + (0.0012626262626262627f * (fSlow42 * fSlow103)));
		float 	fSlow106 = (fSlow105 * fSlow102);
		float 	fSlow107 = (fSlow106 * fSlow101);
		float 	fSlow108 = powf((0.010101010101010102f * min((float)99, fSlow107)),0.69999999999999996f);
		float 	fSlow109 = powf((0.014705882352941176f * (float((fSlow107 >= 30.0f)) * min((fSlow107 + -30.0f), (float)68))),1.8f);
		float 	fSlow110 = float(fslider23);
		float 	fSlow111 = (fSlow106 * fSlow110);
		int 	iSlow112 = int((fSlow111 <= fSlow107));
		float 	fSlow113 = powf((0.010101010101010102f * min((float)99, fSlow111)),0.69999999999999996f);
		float 	fSlow114 = powf((0.014705882352941176f * (float((fSlow111 >= 30.0f)) * min((fSlow111 + -30.0f), (float)68))),1.8f);
		float 	fSlow115 = (0.057142857142857148f * float(fslider24));
		float 	fSlow116 = (fSlow115 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow99))) + 48.0f));
		float 	fSlow117 = float(fslider25);
		float 	fSlow118 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow117 + fSlow116))));
		float 	fSlow119 = max(0.001f, fabsf((((iSlow112)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow118))):max(0.0080000000000000002f, (318.0f * powf(fSlow118,12.6f)))) * (((iSlow112)?fSlow114:fSlow113) - ((iSlow112)?fSlow109:fSlow108)))));
		float 	fSlow120 = float(fslider26);
		float 	fSlow121 = (fSlow106 * fSlow120);
		int 	iSlow122 = int((fSlow111 > fSlow121));
		float 	fSlow123 = powf((0.010101010101010102f * min((float)99, fSlow121)),0.69999999999999996f);
		float 	fSlow124 = powf((0.014705882352941176f * (float((fSlow121 >= 30.0f)) * min((fSlow121 + -30.0f), (float)68))),1.8f);
		float 	fSlow125 = float(fslider27);
		float 	fSlow126 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow125 + fSlow116))));
		float 	fSlow127 = float(fslider28);
		float 	fSlow128 = (fSlow106 * fSlow127);
		float 	fSlow129 = powf((0.010101010101010102f * min((float)99, fSlow128)),0.69999999999999996f);
		float 	fSlow130 = powf((0.014705882352941176f * (float((fSlow128 >= 30.0f)) * min((fSlow128 + -30.0f), (float)68))),1.8f);
		int 	iSlow131 = int((fSlow121 > fSlow128));
		float 	fSlow132 = float(fslider29);
		float 	fSlow133 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow132 + fSlow116))));
		int 	iSlow134 = int((fSlow128 > fSlow107));
		float 	fSlow135 = float(fslider30);
		float 	fSlow136 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow135 + fSlow116))));
		float 	fSlow137 = max(0.001f, fabsf((((iSlow134)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow136))):max(0.0080000000000000002f, (318.0f * powf(fSlow136,12.6f)))) * (((iSlow134)?fSlow109:fSlow108) - ((iSlow134)?fSlow130:fSlow129)))));
		float 	fSlow138 = (fSlow137 + max(0.001f, fabsf((((iSlow131)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow133))):max(0.0080000000000000002f, (318.0f * powf(fSlow133,12.6f)))) * (((iSlow131)?fSlow124:fSlow123) - ((iSlow131)?fSlow130:fSlow129))))));
		float 	fSlow139 = (fSlow138 + max(0.001f, fabsf((((iSlow122)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow126))):max(0.0080000000000000002f, (318.0f * powf(fSlow126,12.6f)))) * (((iSlow122)?fSlow124:fSlow123) - ((iSlow122)?fSlow114:fSlow113))))));
		float 	fSlow140 = (0 - (fConst0 * (fSlow138 - fSlow139)));
		float 	fSlow141 = (fConst0 * fSlow138);
		float 	fSlow142 = (fConst0 * fSlow139);
		float 	fSlow143 = (fSlow110 - fSlow120);
		float 	fSlow144 = (0 - (fConst0 * (fSlow137 - fSlow138)));
		float 	fSlow145 = (fConst0 * fSlow137);
		float 	fSlow146 = (fSlow127 - fSlow120);
		float 	fSlow147 = (0 - ((fSlow146 * fSlow105) * fSlow102));
		float 	fSlow148 = (fSlow101 - fSlow127);
		float 	fSlow149 = (fConst1 * (0 - ((fSlow148 * fSlow105) * fSlow102)));
		float 	fSlow150 = (fConst0 * fSlow119);
		float 	fSlow151 = float(fslider31);
		int 	iSlow152 = int(float(fslider32));
		float 	fSlow153 = (0.25f * float(fslider33));
		float 	fSlow154 = (fSlow153 + ((iSlow152)?fSlow151:(fSlow34 * fSlow151)));
		float 	fSlow155 = (fConst1 * fSlow154);
		float 	fSlow156 = float(fslider34);
		float 	fSlow157 = float(fslider35);
		float 	fSlow158 = float(fslider36);
		float 	fSlow159 = (0.010101010101010102f * (1.0f - (0.125f * fSlow158)));
		float 	fSlow160 = (fSlow159 + (0.0012626262626262627f * (fSlow42 * fSlow158)));
		float 	fSlow161 = (fSlow160 * fSlow157);
		float 	fSlow162 = (fSlow161 * fSlow156);
		float 	fSlow163 = powf((0.010101010101010102f * min((float)99, fSlow162)),0.69999999999999996f);
		float 	fSlow164 = powf((0.014705882352941176f * (float((fSlow162 >= 30.0f)) * min((fSlow162 + -30.0f), (float)68))),1.8f);
		float 	fSlow165 = float(fslider37);
		float 	fSlow166 = (fSlow161 * fSlow165);
		int 	iSlow167 = int((fSlow166 <= fSlow162));
		float 	fSlow168 = powf((0.010101010101010102f * min((float)99, fSlow166)),0.69999999999999996f);
		float 	fSlow169 = powf((0.014705882352941176f * (float((fSlow166 >= 30.0f)) * min((fSlow166 + -30.0f), (float)68))),1.8f);
		float 	fSlow170 = (0.057142857142857148f * float(fslider38));
		float 	fSlow171 = (fSlow170 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow154))) + 48.0f));
		float 	fSlow172 = float(fslider39);
		float 	fSlow173 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow172 + fSlow171))));
		float 	fSlow174 = max(0.001f, fabsf((((iSlow167)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow173))):max(0.0080000000000000002f, (318.0f * powf(fSlow173,12.6f)))) * (((iSlow167)?fSlow169:fSlow168) - ((iSlow167)?fSlow164:fSlow163)))));
		float 	fSlow175 = float(fslider40);
		float 	fSlow176 = (fSlow161 * fSlow175);
		int 	iSlow177 = int((fSlow166 > fSlow176));
		float 	fSlow178 = powf((0.010101010101010102f * min((float)99, fSlow176)),0.69999999999999996f);
		float 	fSlow179 = powf((0.014705882352941176f * (float((fSlow176 >= 30.0f)) * min((fSlow176 + -30.0f), (float)68))),1.8f);
		float 	fSlow180 = float(fslider41);
		float 	fSlow181 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow180 + fSlow171))));
		float 	fSlow182 = float(fslider42);
		float 	fSlow183 = (fSlow161 * fSlow182);
		float 	fSlow184 = powf((0.010101010101010102f * min((float)99, fSlow183)),0.69999999999999996f);
		float 	fSlow185 = powf((0.014705882352941176f * (float((fSlow183 >= 30.0f)) * min((fSlow183 + -30.0f), (float)68))),1.8f);
		int 	iSlow186 = int((fSlow176 > fSlow183));
		float 	fSlow187 = float(fslider43);
		float 	fSlow188 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow187 + fSlow171))));
		int 	iSlow189 = int((fSlow183 > fSlow162));
		float 	fSlow190 = float(fslider44);
		float 	fSlow191 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow190 + fSlow171))));
		float 	fSlow192 = max(0.001f, fabsf((((iSlow189)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow191))):max(0.0080000000000000002f, (318.0f * powf(fSlow191,12.6f)))) * (((iSlow189)?fSlow164:fSlow163) - ((iSlow189)?fSlow185:fSlow184)))));
		float 	fSlow193 = (fSlow192 + max(0.001f, fabsf((((iSlow186)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow188))):max(0.0080000000000000002f, (318.0f * powf(fSlow188,12.6f)))) * (((iSlow186)?fSlow179:fSlow178) - ((iSlow186)?fSlow185:fSlow184))))));
		float 	fSlow194 = (fSlow193 + max(0.001f, fabsf((((iSlow177)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow181))):max(0.0080000000000000002f, (318.0f * powf(fSlow181,12.6f)))) * (((iSlow177)?fSlow179:fSlow178) - ((iSlow177)?fSlow169:fSlow168))))));
		float 	fSlow195 = (0 - (fConst0 * (fSlow193 - fSlow194)));
		float 	fSlow196 = (fConst0 * fSlow193);
		float 	fSlow197 = (fConst0 * fSlow194);
		float 	fSlow198 = (fSlow165 - fSlow175);
		float 	fSlow199 = (0 - (fConst0 * (fSlow192 - fSlow193)));
		float 	fSlow200 = (fConst0 * fSlow192);
		float 	fSlow201 = (fSlow182 - fSlow175);
		float 	fSlow202 = (0 - ((fSlow201 * fSlow160) * fSlow157));
		float 	fSlow203 = (fSlow156 - fSlow182);
		float 	fSlow204 = (fConst1 * (0 - ((fSlow203 * fSlow160) * fSlow157)));
		float 	fSlow205 = (fConst0 * fSlow174);
		float 	fSlow206 = float(fslider45);
		int 	iSlow207 = int(float(fslider46));
		float 	fSlow208 = (0.25f * float(fslider47));
		float 	fSlow209 = (fSlow208 + ((iSlow207)?fSlow206:(fSlow34 * fSlow206)));
		float 	fSlow210 = (fConst1 * fSlow209);
		float 	fSlow211 = float(fslider48);
		float 	fSlow212 = float(fslider49);
		float 	fSlow213 = float(fslider50);
		float 	fSlow214 = (0.010101010101010102f * (1.0f - (0.125f * fSlow213)));
		float 	fSlow215 = (fSlow214 + (0.0012626262626262627f * (fSlow42 * fSlow213)));
		float 	fSlow216 = (fSlow215 * fSlow212);
		float 	fSlow217 = (fSlow216 * fSlow211);
		float 	fSlow218 = powf((0.010101010101010102f * min((float)99, fSlow217)),0.69999999999999996f);
		float 	fSlow219 = powf((0.014705882352941176f * (float((fSlow217 >= 30.0f)) * min((fSlow217 + -30.0f), (float)68))),1.8f);
		float 	fSlow220 = float(fslider51);
		float 	fSlow221 = (fSlow216 * fSlow220);
		int 	iSlow222 = int((fSlow221 <= fSlow217));
		float 	fSlow223 = powf((0.010101010101010102f * min((float)99, fSlow221)),0.69999999999999996f);
		float 	fSlow224 = powf((0.014705882352941176f * (float((fSlow221 >= 30.0f)) * min((fSlow221 + -30.0f), (float)68))),1.8f);
		float 	fSlow225 = (0.057142857142857148f * float(fslider52));
		float 	fSlow226 = (fSlow225 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow209))) + 48.0f));
		float 	fSlow227 = float(fslider53);
		float 	fSlow228 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow227 + fSlow226))));
		float 	fSlow229 = max(0.001f, fabsf((((iSlow222)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow228))):max(0.0080000000000000002f, (318.0f * powf(fSlow228,12.6f)))) * (((iSlow222)?fSlow224:fSlow223) - ((iSlow222)?fSlow219:fSlow218)))));
		float 	fSlow230 = float(fslider54);
		float 	fSlow231 = (fSlow216 * fSlow230);
		int 	iSlow232 = int((fSlow221 > fSlow231));
		float 	fSlow233 = powf((0.010101010101010102f * min((float)99, fSlow231)),0.69999999999999996f);
		float 	fSlow234 = powf((0.014705882352941176f * (float((fSlow231 >= 30.0f)) * min((fSlow231 + -30.0f), (float)68))),1.8f);
		float 	fSlow235 = float(fslider55);
		float 	fSlow236 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow235 + fSlow226))));
		float 	fSlow237 = float(fslider56);
		float 	fSlow238 = (fSlow216 * fSlow237);
		float 	fSlow239 = powf((0.010101010101010102f * min((float)99, fSlow238)),0.69999999999999996f);
		float 	fSlow240 = powf((0.014705882352941176f * (float((fSlow238 >= 30.0f)) * min((fSlow238 + -30.0f), (float)68))),1.8f);
		int 	iSlow241 = int((fSlow231 > fSlow238));
		float 	fSlow242 = float(fslider57);
		float 	fSlow243 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow242 + fSlow226))));
		int 	iSlow244 = int((fSlow238 > fSlow217));
		float 	fSlow245 = float(fslider58);
		float 	fSlow246 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow245 + fSlow226))));
		float 	fSlow247 = max(0.001f, fabsf((((iSlow244)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow246))):max(0.0080000000000000002f, (318.0f * powf(fSlow246,12.6f)))) * (((iSlow244)?fSlow219:fSlow218) - ((iSlow244)?fSlow240:fSlow239)))));
		float 	fSlow248 = (fSlow247 + max(0.001f, fabsf((((iSlow241)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow243))):max(0.0080000000000000002f, (318.0f * powf(fSlow243,12.6f)))) * (((iSlow241)?fSlow234:fSlow233) - ((iSlow241)?fSlow240:fSlow239))))));
		float 	fSlow249 = (fSlow248 + max(0.001f, fabsf((((iSlow232)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow236))):max(0.0080000000000000002f, (318.0f * powf(fSlow236,12.6f)))) * (((iSlow232)?fSlow234:fSlow233) - ((iSlow232)?fSlow224:fSlow223))))));
		float 	fSlow250 = (0 - (fConst0 * (fSlow248 - fSlow249)));
		float 	fSlow251 = (fConst0 * fSlow248);
		float 	fSlow252 = (fConst0 * fSlow249);
		float 	fSlow253 = (fSlow220 - fSlow230);
		float 	fSlow254 = (0 - (fConst0 * (fSlow247 - fSlow248)));
		float 	fSlow255 = (fConst0 * fSlow247);
		float 	fSlow256 = (fSlow237 - fSlow230);
		float 	fSlow257 = (0 - ((fSlow256 * fSlow215) * fSlow212));
		float 	fSlow258 = (fSlow211 - fSlow237);
		float 	fSlow259 = (fConst1 * (0 - ((fSlow258 * fSlow215) * fSlow212)));
		float 	fSlow260 = (fConst0 * fSlow229);
		float 	fSlow261 = float(fslider59);
		int 	iSlow262 = int(float(fslider60));
		float 	fSlow263 = (0.25f * float(fslider61));
		float 	fSlow264 = (fSlow263 + ((iSlow262)?fSlow261:(fSlow34 * fSlow261)));
		float 	fSlow265 = (fConst1 * fSlow264);
		float 	fSlow266 = float(fslider62);
		float 	fSlow267 = float(fslider63);
		float 	fSlow268 = float(fslider64);
		float 	fSlow269 = (0.010101010101010102f * (1.0f - (0.125f * fSlow268)));
		float 	fSlow270 = (fSlow269 + (0.0012626262626262627f * (fSlow42 * fSlow268)));
		float 	fSlow271 = (fSlow270 * fSlow267);
		float 	fSlow272 = (fSlow271 * fSlow266);
		float 	fSlow273 = powf((0.010101010101010102f * min((float)99, fSlow272)),0.69999999999999996f);
		float 	fSlow274 = powf((0.014705882352941176f * (float((fSlow272 >= 30.0f)) * min((fSlow272 + -30.0f), (float)68))),1.8f);
		float 	fSlow275 = float(fslider65);
		float 	fSlow276 = (fSlow271 * fSlow275);
		int 	iSlow277 = int((fSlow276 <= fSlow272));
		float 	fSlow278 = powf((0.010101010101010102f * min((float)99, fSlow276)),0.69999999999999996f);
		float 	fSlow279 = powf((0.014705882352941176f * (float((fSlow276 >= 30.0f)) * min((fSlow276 + -30.0f), (float)68))),1.8f);
		float 	fSlow280 = (0.057142857142857148f * float(fslider66));
		float 	fSlow281 = (fSlow280 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow264))) + 48.0f));
		float 	fSlow282 = float(fslider67);
		float 	fSlow283 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow282 + fSlow281))));
		float 	fSlow284 = max(0.001f, fabsf((((iSlow277)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow283))):max(0.0080000000000000002f, (318.0f * powf(fSlow283,12.6f)))) * (((iSlow277)?fSlow279:fSlow278) - ((iSlow277)?fSlow274:fSlow273)))));
		float 	fSlow285 = float(fslider68);
		float 	fSlow286 = (fSlow271 * fSlow285);
		int 	iSlow287 = int((fSlow276 > fSlow286));
		float 	fSlow288 = powf((0.010101010101010102f * min((float)99, fSlow286)),0.69999999999999996f);
		float 	fSlow289 = powf((0.014705882352941176f * (float((fSlow286 >= 30.0f)) * min((fSlow286 + -30.0f), (float)68))),1.8f);
		float 	fSlow290 = float(fslider69);
		float 	fSlow291 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow290 + fSlow281))));
		float 	fSlow292 = float(fslider70);
		float 	fSlow293 = (fSlow271 * fSlow292);
		float 	fSlow294 = powf((0.010101010101010102f * min((float)99, fSlow293)),0.69999999999999996f);
		float 	fSlow295 = powf((0.014705882352941176f * (float((fSlow293 >= 30.0f)) * min((fSlow293 + -30.0f), (float)68))),1.8f);
		int 	iSlow296 = int((fSlow286 > fSlow293));
		float 	fSlow297 = float(fslider71);
		float 	fSlow298 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow297 + fSlow281))));
		int 	iSlow299 = int((fSlow293 > fSlow272));
		float 	fSlow300 = float(fslider72);
		float 	fSlow301 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow300 + fSlow281))));
		float 	fSlow302 = max(0.001f, fabsf((((iSlow299)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow301))):max(0.0080000000000000002f, (318.0f * powf(fSlow301,12.6f)))) * (((iSlow299)?fSlow274:fSlow273) - ((iSlow299)?fSlow295:fSlow294)))));
		float 	fSlow303 = (fSlow302 + max(0.001f, fabsf((((iSlow296)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow298))):max(0.0080000000000000002f, (318.0f * powf(fSlow298,12.6f)))) * (((iSlow296)?fSlow289:fSlow288) - ((iSlow296)?fSlow295:fSlow294))))));
		float 	fSlow304 = (fSlow303 + max(0.001f, fabsf((((iSlow287)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow291))):max(0.0080000000000000002f, (318.0f * powf(fSlow291,12.6f)))) * (((iSlow287)?fSlow289:fSlow288) - ((iSlow287)?fSlow279:fSlow278))))));
		float 	fSlow305 = (0 - (fConst0 * (fSlow303 - fSlow304)));
		float 	fSlow306 = (fConst0 * fSlow303);
		float 	fSlow307 = (fConst0 * fSlow304);
		float 	fSlow308 = (fSlow275 - fSlow285);
		float 	fSlow309 = (0 - (fConst0 * (fSlow302 - fSlow303)));
		float 	fSlow310 = (fConst0 * fSlow302);
		float 	fSlow311 = (fSlow292 - fSlow285);
		float 	fSlow312 = (0 - ((fSlow311 * fSlow270) * fSlow267));
		float 	fSlow313 = (fSlow266 - fSlow292);
		float 	fSlow314 = (fConst1 * (0 - ((fSlow313 * fSlow270) * fSlow267)));
		float 	fSlow315 = (fConst0 * fSlow284);
		float 	fSlow316 = float(fslider73);
		int 	iSlow317 = int(float(fslider74));
		float 	fSlow318 = (0.25f * float(fslider75));
		float 	fSlow319 = (fSlow318 + ((iSlow317)?fSlow316:(fSlow34 * fSlow316)));
		float 	fSlow320 = (fConst1 * fSlow319);
		float 	fSlow321 = float(fslider76);
		float 	fSlow322 = float(fslider77);
		float 	fSlow323 = float(fslider78);
		float 	fSlow324 = (0.010101010101010102f * (1.0f - (0.125f * fSlow323)));
		float 	fSlow325 = (fSlow324 + (0.0012626262626262627f * (fSlow42 * fSlow323)));
		float 	fSlow326 = (fSlow325 * fSlow322);
		float 	fSlow327 = (fSlow326 * fSlow321);
		float 	fSlow328 = powf((0.010101010101010102f * min((float)99, fSlow327)),0.69999999999999996f);
		float 	fSlow329 = powf((0.014705882352941176f * (float((fSlow327 >= 30.0f)) * min((fSlow327 + -30.0f), (float)68))),1.8f);
		float 	fSlow330 = float(fslider79);
		float 	fSlow331 = (fSlow326 * fSlow330);
		int 	iSlow332 = int((fSlow331 <= fSlow327));
		float 	fSlow333 = powf((0.010101010101010102f * min((float)99, fSlow331)),0.69999999999999996f);
		float 	fSlow334 = powf((0.014705882352941176f * (float((fSlow331 >= 30.0f)) * min((fSlow331 + -30.0f), (float)68))),1.8f);
		float 	fSlow335 = (0.057142857142857148f * float(fslider80));
		float 	fSlow336 = (fSlow335 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow319))) + 48.0f));
		float 	fSlow337 = float(fslider81);
		float 	fSlow338 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow337 + fSlow336))));
		float 	fSlow339 = max(0.001f, fabsf((((iSlow332)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow338))):max(0.0080000000000000002f, (318.0f * powf(fSlow338,12.6f)))) * (((iSlow332)?fSlow334:fSlow333) - ((iSlow332)?fSlow329:fSlow328)))));
		float 	fSlow340 = float(fslider82);
		float 	fSlow341 = (fSlow326 * fSlow340);
		int 	iSlow342 = int((fSlow331 > fSlow341));
		float 	fSlow343 = powf((0.010101010101010102f * min((float)99, fSlow341)),0.69999999999999996f);
		float 	fSlow344 = powf((0.014705882352941176f * (float((fSlow341 >= 30.0f)) * min((fSlow341 + -30.0f), (float)68))),1.8f);
		float 	fSlow345 = float(fslider83);
		float 	fSlow346 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow345 + fSlow336))));
		float 	fSlow347 = float(fslider84);
		float 	fSlow348 = (fSlow326 * fSlow347);
		float 	fSlow349 = powf((0.010101010101010102f * min((float)99, fSlow348)),0.69999999999999996f);
		float 	fSlow350 = powf((0.014705882352941176f * (float((fSlow348 >= 30.0f)) * min((fSlow348 + -30.0f), (float)68))),1.8f);
		int 	iSlow351 = int((fSlow341 > fSlow348));
		float 	fSlow352 = float(fslider85);
		float 	fSlow353 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow352 + fSlow336))));
		int 	iSlow354 = int((fSlow348 > fSlow327));
		float 	fSlow355 = float(fslider86);
		float 	fSlow356 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow355 + fSlow336))));
		float 	fSlow357 = max(0.001f, fabsf((((iSlow354)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow356))):max(0.0080000000000000002f, (318.0f * powf(fSlow356,12.6f)))) * (((iSlow354)?fSlow329:fSlow328) - ((iSlow354)?fSlow350:fSlow349)))));
		float 	fSlow358 = (fSlow357 + max(0.001f, fabsf((((iSlow351)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow353))):max(0.0080000000000000002f, (318.0f * powf(fSlow353,12.6f)))) * (((iSlow351)?fSlow344:fSlow343) - ((iSlow351)?fSlow350:fSlow349))))));
		float 	fSlow359 = (fSlow358 + max(0.001f, fabsf((((iSlow342)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow346))):max(0.0080000000000000002f, (318.0f * powf(fSlow346,12.6f)))) * (((iSlow342)?fSlow344:fSlow343) - ((iSlow342)?fSlow334:fSlow333))))));
		float 	fSlow360 = (0 - (fConst0 * (fSlow358 - fSlow359)));
		float 	fSlow361 = (fConst0 * fSlow358);
		float 	fSlow362 = (fConst0 * fSlow359);
		float 	fSlow363 = (fSlow330 - fSlow340);
		float 	fSlow364 = (0 - (fConst0 * (fSlow357 - fSlow358)));
		float 	fSlow365 = (fConst0 * fSlow357);
		float 	fSlow366 = (fSlow347 - fSlow340);
		float 	fSlow367 = (0 - ((fSlow366 * fSlow325) * fSlow322));
		float 	fSlow368 = (fSlow321 - fSlow347);
		float 	fSlow369 = (fConst1 * (0 - ((fSlow368 * fSlow325) * fSlow322)));
		float 	fSlow370 = (fConst0 * fSlow339);
		float 	fSlow371 = float(fslider87);
		float 	fSlow372 = (39321.599999999999f * fSlow371);
		float 	fSlow373 = (6553.6000000000004f * fSlow371);
		float 	fSlow374 = (26214.400000000001f * fSlow371);
		float 	fSlow375 = (32768.0f * fSlow371);
		float 	fSlow376 = (13107.200000000001f * fSlow371);
		float 	fSlow377 = float(fslider88);
		float 	fSlow378 = float(fslider89);
		float 	fSlow379 = float(fslider90);
		float 	fSlow380 = (6.9100000000000001f * fSlow379);
		int 	iSlow381 = int((fConst0 * fSlow379));
		float 	fSlow382 = float(fslider91);
		float 	fSlow383 = (fSlow92 * fSlow382);
		float 	fSlow384 = float(fslider92);
		float 	fSlow385 = (fSlow36 + ((iSlow35)?fSlow33:(fSlow384 * fSlow33)));
		float 	fSlow386 = (fConst1 * fSlow385);
		float 	fSlow387 = float(fslider93);
		float 	fSlow388 = (fSlow43 + (0.0012626262626262627f * (fSlow387 * fSlow41)));
		float 	fSlow389 = (fSlow388 * fSlow40);
		float 	fSlow390 = (fSlow389 * fSlow39);
		float 	fSlow391 = powf((0.010101010101010102f * min((float)99, fSlow390)),0.69999999999999996f);
		float 	fSlow392 = powf((0.014705882352941176f * (float((fSlow390 >= 30.0f)) * min((fSlow390 + -30.0f), (float)68))),1.8f);
		float 	fSlow393 = (fSlow389 * fSlow49);
		int 	iSlow394 = int((fSlow393 <= fSlow390));
		float 	fSlow395 = powf((0.010101010101010102f * min((float)99, fSlow393)),0.69999999999999996f);
		float 	fSlow396 = powf((0.014705882352941176f * (float((fSlow393 >= 30.0f)) * min((fSlow393 + -30.0f), (float)68))),1.8f);
		float 	fSlow397 = (fSlow54 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow385))) + 48.0f));
		float 	fSlow398 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow56 + fSlow397))));
		float 	fSlow399 = max(0.001f, fabsf((((iSlow394)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow398))):max(0.0080000000000000002f, (318.0f * powf(fSlow398,12.6f)))) * (((iSlow394)?fSlow396:fSlow395) - ((iSlow394)?fSlow392:fSlow391)))));
		float 	fSlow400 = (fSlow389 * fSlow59);
		int 	iSlow401 = int((fSlow393 > fSlow400));
		float 	fSlow402 = powf((0.010101010101010102f * min((float)99, fSlow400)),0.69999999999999996f);
		float 	fSlow403 = powf((0.014705882352941176f * (float((fSlow400 >= 30.0f)) * min((fSlow400 + -30.0f), (float)68))),1.8f);
		float 	fSlow404 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow64 + fSlow397))));
		float 	fSlow405 = (fSlow389 * fSlow66);
		float 	fSlow406 = powf((0.010101010101010102f * min((float)99, fSlow405)),0.69999999999999996f);
		float 	fSlow407 = powf((0.014705882352941176f * (float((fSlow405 >= 30.0f)) * min((fSlow405 + -30.0f), (float)68))),1.8f);
		int 	iSlow408 = int((fSlow400 > fSlow405));
		float 	fSlow409 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow71 + fSlow397))));
		int 	iSlow410 = int((fSlow405 > fSlow390));
		float 	fSlow411 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow74 + fSlow397))));
		float 	fSlow412 = max(0.001f, fabsf((((iSlow410)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow411))):max(0.0080000000000000002f, (318.0f * powf(fSlow411,12.6f)))) * (((iSlow410)?fSlow392:fSlow391) - ((iSlow410)?fSlow407:fSlow406)))));
		float 	fSlow413 = (fSlow412 + max(0.001f, fabsf((((iSlow408)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow409))):max(0.0080000000000000002f, (318.0f * powf(fSlow409,12.6f)))) * (((iSlow408)?fSlow403:fSlow402) - ((iSlow408)?fSlow407:fSlow406))))));
		float 	fSlow414 = (fSlow413 + max(0.001f, fabsf((((iSlow401)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow404))):max(0.0080000000000000002f, (318.0f * powf(fSlow404,12.6f)))) * (((iSlow401)?fSlow403:fSlow402) - ((iSlow401)?fSlow396:fSlow395))))));
		float 	fSlow415 = (0 - (fConst0 * (fSlow413 - fSlow414)));
		float 	fSlow416 = (fConst0 * fSlow413);
		float 	fSlow417 = (fConst0 * fSlow414);
		float 	fSlow418 = float(fbutton1);
		int 	iSlow419 = int(((fSlow418 == 0.0f) > 0));
		float 	fSlow420 = (0 - (fConst0 * (fSlow412 - fSlow413)));
		float 	fSlow421 = (fConst0 * fSlow412);
		float 	fSlow422 = (0 - ((fSlow87 * fSlow388) * fSlow40));
		float 	fSlow423 = (fConst1 * (0 - ((fSlow89 * fSlow388) * fSlow40)));
		int 	iSlow424 = (fSlow418 > 0.0f);
		float 	fSlow425 = float(iSlow424);
		int 	iSlow426 = int(iSlow424);
		float 	fSlow427 = (fConst0 * fSlow399);
		int 	iSlow428 = int((iSlow424 > 0));
		float 	fSlow429 = (fSlow98 + ((iSlow97)?fSlow96:(fSlow384 * fSlow96)));
		float 	fSlow430 = (fConst1 * fSlow429);
		float 	fSlow431 = (fSlow104 + (0.0012626262626262627f * (fSlow387 * fSlow103)));
		float 	fSlow432 = (fSlow431 * fSlow102);
		float 	fSlow433 = (fSlow432 * fSlow101);
		float 	fSlow434 = powf((0.010101010101010102f * min((float)99, fSlow433)),0.69999999999999996f);
		float 	fSlow435 = powf((0.014705882352941176f * (float((fSlow433 >= 30.0f)) * min((fSlow433 + -30.0f), (float)68))),1.8f);
		float 	fSlow436 = (fSlow432 * fSlow110);
		int 	iSlow437 = int((fSlow436 <= fSlow433));
		float 	fSlow438 = powf((0.010101010101010102f * min((float)99, fSlow436)),0.69999999999999996f);
		float 	fSlow439 = powf((0.014705882352941176f * (float((fSlow436 >= 30.0f)) * min((fSlow436 + -30.0f), (float)68))),1.8f);
		float 	fSlow440 = (fSlow115 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow429))) + 48.0f));
		float 	fSlow441 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow117 + fSlow440))));
		float 	fSlow442 = max(0.001f, fabsf((((iSlow437)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow441))):max(0.0080000000000000002f, (318.0f * powf(fSlow441,12.6f)))) * (((iSlow437)?fSlow439:fSlow438) - ((iSlow437)?fSlow435:fSlow434)))));
		float 	fSlow443 = (fSlow432 * fSlow120);
		int 	iSlow444 = int((fSlow436 > fSlow443));
		float 	fSlow445 = powf((0.010101010101010102f * min((float)99, fSlow443)),0.69999999999999996f);
		float 	fSlow446 = powf((0.014705882352941176f * (float((fSlow443 >= 30.0f)) * min((fSlow443 + -30.0f), (float)68))),1.8f);
		float 	fSlow447 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow125 + fSlow440))));
		float 	fSlow448 = (fSlow432 * fSlow127);
		float 	fSlow449 = powf((0.010101010101010102f * min((float)99, fSlow448)),0.69999999999999996f);
		float 	fSlow450 = powf((0.014705882352941176f * (float((fSlow448 >= 30.0f)) * min((fSlow448 + -30.0f), (float)68))),1.8f);
		int 	iSlow451 = int((fSlow443 > fSlow448));
		float 	fSlow452 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow132 + fSlow440))));
		int 	iSlow453 = int((fSlow448 > fSlow433));
		float 	fSlow454 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow135 + fSlow440))));
		float 	fSlow455 = max(0.001f, fabsf((((iSlow453)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow454))):max(0.0080000000000000002f, (318.0f * powf(fSlow454,12.6f)))) * (((iSlow453)?fSlow435:fSlow434) - ((iSlow453)?fSlow450:fSlow449)))));
		float 	fSlow456 = (fSlow455 + max(0.001f, fabsf((((iSlow451)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow452))):max(0.0080000000000000002f, (318.0f * powf(fSlow452,12.6f)))) * (((iSlow451)?fSlow446:fSlow445) - ((iSlow451)?fSlow450:fSlow449))))));
		float 	fSlow457 = (fSlow456 + max(0.001f, fabsf((((iSlow444)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow447))):max(0.0080000000000000002f, (318.0f * powf(fSlow447,12.6f)))) * (((iSlow444)?fSlow446:fSlow445) - ((iSlow444)?fSlow439:fSlow438))))));
		float 	fSlow458 = (0 - (fConst0 * (fSlow456 - fSlow457)));
		float 	fSlow459 = (fConst0 * fSlow456);
		float 	fSlow460 = (fConst0 * fSlow457);
		float 	fSlow461 = (0 - (fConst0 * (fSlow455 - fSlow456)));
		float 	fSlow462 = (fConst0 * fSlow455);
		float 	fSlow463 = (0 - ((fSlow146 * fSlow431) * fSlow102));
		float 	fSlow464 = (fConst1 * (0 - ((fSlow148 * fSlow431) * fSlow102)));
		float 	fSlow465 = (fConst0 * fSlow442);
		float 	fSlow466 = (fSlow153 + ((iSlow152)?fSlow151:(fSlow384 * fSlow151)));
		float 	fSlow467 = (fConst1 * fSlow466);
		float 	fSlow468 = (fSlow159 + (0.0012626262626262627f * (fSlow387 * fSlow158)));
		float 	fSlow469 = (fSlow468 * fSlow157);
		float 	fSlow470 = (fSlow469 * fSlow156);
		float 	fSlow471 = powf((0.010101010101010102f * min((float)99, fSlow470)),0.69999999999999996f);
		float 	fSlow472 = powf((0.014705882352941176f * (float((fSlow470 >= 30.0f)) * min((fSlow470 + -30.0f), (float)68))),1.8f);
		float 	fSlow473 = (fSlow469 * fSlow165);
		int 	iSlow474 = int((fSlow473 <= fSlow470));
		float 	fSlow475 = powf((0.010101010101010102f * min((float)99, fSlow473)),0.69999999999999996f);
		float 	fSlow476 = powf((0.014705882352941176f * (float((fSlow473 >= 30.0f)) * min((fSlow473 + -30.0f), (float)68))),1.8f);
		float 	fSlow477 = (fSlow170 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow466))) + 48.0f));
		float 	fSlow478 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow172 + fSlow477))));
		float 	fSlow479 = max(0.001f, fabsf((((iSlow474)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow478))):max(0.0080000000000000002f, (318.0f * powf(fSlow478,12.6f)))) * (((iSlow474)?fSlow476:fSlow475) - ((iSlow474)?fSlow472:fSlow471)))));
		float 	fSlow480 = (fSlow469 * fSlow175);
		int 	iSlow481 = int((fSlow473 > fSlow480));
		float 	fSlow482 = powf((0.010101010101010102f * min((float)99, fSlow480)),0.69999999999999996f);
		float 	fSlow483 = powf((0.014705882352941176f * (float((fSlow480 >= 30.0f)) * min((fSlow480 + -30.0f), (float)68))),1.8f);
		float 	fSlow484 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow180 + fSlow477))));
		float 	fSlow485 = (fSlow469 * fSlow182);
		float 	fSlow486 = powf((0.010101010101010102f * min((float)99, fSlow485)),0.69999999999999996f);
		float 	fSlow487 = powf((0.014705882352941176f * (float((fSlow485 >= 30.0f)) * min((fSlow485 + -30.0f), (float)68))),1.8f);
		int 	iSlow488 = int((fSlow480 > fSlow485));
		float 	fSlow489 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow187 + fSlow477))));
		int 	iSlow490 = int((fSlow485 > fSlow470));
		float 	fSlow491 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow190 + fSlow477))));
		float 	fSlow492 = max(0.001f, fabsf((((iSlow490)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow491))):max(0.0080000000000000002f, (318.0f * powf(fSlow491,12.6f)))) * (((iSlow490)?fSlow472:fSlow471) - ((iSlow490)?fSlow487:fSlow486)))));
		float 	fSlow493 = (fSlow492 + max(0.001f, fabsf((((iSlow488)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow489))):max(0.0080000000000000002f, (318.0f * powf(fSlow489,12.6f)))) * (((iSlow488)?fSlow483:fSlow482) - ((iSlow488)?fSlow487:fSlow486))))));
		float 	fSlow494 = (fSlow493 + max(0.001f, fabsf((((iSlow481)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow484))):max(0.0080000000000000002f, (318.0f * powf(fSlow484,12.6f)))) * (((iSlow481)?fSlow483:fSlow482) - ((iSlow481)?fSlow476:fSlow475))))));
		float 	fSlow495 = (0 - (fConst0 * (fSlow493 - fSlow494)));
		float 	fSlow496 = (fConst0 * fSlow493);
		float 	fSlow497 = (fConst0 * fSlow494);
		float 	fSlow498 = (0 - (fConst0 * (fSlow492 - fSlow493)));
		float 	fSlow499 = (fConst0 * fSlow492);
		float 	fSlow500 = (0 - ((fSlow201 * fSlow468) * fSlow157));
		float 	fSlow501 = (fConst1 * (0 - ((fSlow203 * fSlow468) * fSlow157)));
		float 	fSlow502 = (fConst0 * fSlow479);
		float 	fSlow503 = (fSlow208 + ((iSlow207)?fSlow206:(fSlow384 * fSlow206)));
		float 	fSlow504 = (fConst1 * fSlow503);
		float 	fSlow505 = (fSlow214 + (0.0012626262626262627f * (fSlow387 * fSlow213)));
		float 	fSlow506 = (fSlow505 * fSlow212);
		float 	fSlow507 = (fSlow506 * fSlow211);
		float 	fSlow508 = powf((0.010101010101010102f * min((float)99, fSlow507)),0.69999999999999996f);
		float 	fSlow509 = powf((0.014705882352941176f * (float((fSlow507 >= 30.0f)) * min((fSlow507 + -30.0f), (float)68))),1.8f);
		float 	fSlow510 = (fSlow506 * fSlow220);
		int 	iSlow511 = int((fSlow510 <= fSlow507));
		float 	fSlow512 = powf((0.010101010101010102f * min((float)99, fSlow510)),0.69999999999999996f);
		float 	fSlow513 = powf((0.014705882352941176f * (float((fSlow510 >= 30.0f)) * min((fSlow510 + -30.0f), (float)68))),1.8f);
		float 	fSlow514 = (fSlow225 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow503))) + 48.0f));
		float 	fSlow515 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow227 + fSlow514))));
		float 	fSlow516 = max(0.001f, fabsf((((iSlow511)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow515))):max(0.0080000000000000002f, (318.0f * powf(fSlow515,12.6f)))) * (((iSlow511)?fSlow513:fSlow512) - ((iSlow511)?fSlow509:fSlow508)))));
		float 	fSlow517 = (fSlow506 * fSlow230);
		int 	iSlow518 = int((fSlow510 > fSlow517));
		float 	fSlow519 = powf((0.010101010101010102f * min((float)99, fSlow517)),0.69999999999999996f);
		float 	fSlow520 = powf((0.014705882352941176f * (float((fSlow517 >= 30.0f)) * min((fSlow517 + -30.0f), (float)68))),1.8f);
		float 	fSlow521 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow235 + fSlow514))));
		float 	fSlow522 = (fSlow506 * fSlow237);
		float 	fSlow523 = powf((0.010101010101010102f * min((float)99, fSlow522)),0.69999999999999996f);
		float 	fSlow524 = powf((0.014705882352941176f * (float((fSlow522 >= 30.0f)) * min((fSlow522 + -30.0f), (float)68))),1.8f);
		int 	iSlow525 = int((fSlow517 > fSlow522));
		float 	fSlow526 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow242 + fSlow514))));
		int 	iSlow527 = int((fSlow522 > fSlow507));
		float 	fSlow528 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow245 + fSlow514))));
		float 	fSlow529 = max(0.001f, fabsf((((iSlow527)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow528))):max(0.0080000000000000002f, (318.0f * powf(fSlow528,12.6f)))) * (((iSlow527)?fSlow509:fSlow508) - ((iSlow527)?fSlow524:fSlow523)))));
		float 	fSlow530 = (fSlow529 + max(0.001f, fabsf((((iSlow525)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow526))):max(0.0080000000000000002f, (318.0f * powf(fSlow526,12.6f)))) * (((iSlow525)?fSlow520:fSlow519) - ((iSlow525)?fSlow524:fSlow523))))));
		float 	fSlow531 = (fSlow530 + max(0.001f, fabsf((((iSlow518)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow521))):max(0.0080000000000000002f, (318.0f * powf(fSlow521,12.6f)))) * (((iSlow518)?fSlow520:fSlow519) - ((iSlow518)?fSlow513:fSlow512))))));
		float 	fSlow532 = (0 - (fConst0 * (fSlow530 - fSlow531)));
		float 	fSlow533 = (fConst0 * fSlow530);
		float 	fSlow534 = (fConst0 * fSlow531);
		float 	fSlow535 = (0 - (fConst0 * (fSlow529 - fSlow530)));
		float 	fSlow536 = (fConst0 * fSlow529);
		float 	fSlow537 = (0 - ((fSlow256 * fSlow505) * fSlow212));
		float 	fSlow538 = (fConst1 * (0 - ((fSlow258 * fSlow505) * fSlow212)));
		float 	fSlow539 = (fConst0 * fSlow516);
		float 	fSlow540 = (fSlow263 + ((iSlow262)?fSlow261:(fSlow384 * fSlow261)));
		float 	fSlow541 = (fConst1 * fSlow540);
		float 	fSlow542 = (fSlow269 + (0.0012626262626262627f * (fSlow387 * fSlow268)));
		float 	fSlow543 = (fSlow542 * fSlow267);
		float 	fSlow544 = (fSlow543 * fSlow266);
		float 	fSlow545 = powf((0.010101010101010102f * min((float)99, fSlow544)),0.69999999999999996f);
		float 	fSlow546 = powf((0.014705882352941176f * (float((fSlow544 >= 30.0f)) * min((fSlow544 + -30.0f), (float)68))),1.8f);
		float 	fSlow547 = (fSlow543 * fSlow275);
		int 	iSlow548 = int((fSlow547 <= fSlow544));
		float 	fSlow549 = powf((0.010101010101010102f * min((float)99, fSlow547)),0.69999999999999996f);
		float 	fSlow550 = powf((0.014705882352941176f * (float((fSlow547 >= 30.0f)) * min((fSlow547 + -30.0f), (float)68))),1.8f);
		float 	fSlow551 = (fSlow280 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow540))) + 48.0f));
		float 	fSlow552 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow282 + fSlow551))));
		float 	fSlow553 = max(0.001f, fabsf((((iSlow548)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow552))):max(0.0080000000000000002f, (318.0f * powf(fSlow552,12.6f)))) * (((iSlow548)?fSlow550:fSlow549) - ((iSlow548)?fSlow546:fSlow545)))));
		float 	fSlow554 = (fSlow543 * fSlow285);
		int 	iSlow555 = int((fSlow547 > fSlow554));
		float 	fSlow556 = powf((0.010101010101010102f * min((float)99, fSlow554)),0.69999999999999996f);
		float 	fSlow557 = powf((0.014705882352941176f * (float((fSlow554 >= 30.0f)) * min((fSlow554 + -30.0f), (float)68))),1.8f);
		float 	fSlow558 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow290 + fSlow551))));
		float 	fSlow559 = (fSlow543 * fSlow292);
		float 	fSlow560 = powf((0.010101010101010102f * min((float)99, fSlow559)),0.69999999999999996f);
		float 	fSlow561 = powf((0.014705882352941176f * (float((fSlow559 >= 30.0f)) * min((fSlow559 + -30.0f), (float)68))),1.8f);
		int 	iSlow562 = int((fSlow554 > fSlow559));
		float 	fSlow563 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow297 + fSlow551))));
		int 	iSlow564 = int((fSlow559 > fSlow544));
		float 	fSlow565 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow300 + fSlow551))));
		float 	fSlow566 = max(0.001f, fabsf((((iSlow564)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow565))):max(0.0080000000000000002f, (318.0f * powf(fSlow565,12.6f)))) * (((iSlow564)?fSlow546:fSlow545) - ((iSlow564)?fSlow561:fSlow560)))));
		float 	fSlow567 = (fSlow566 + max(0.001f, fabsf((((iSlow562)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow563))):max(0.0080000000000000002f, (318.0f * powf(fSlow563,12.6f)))) * (((iSlow562)?fSlow557:fSlow556) - ((iSlow562)?fSlow561:fSlow560))))));
		float 	fSlow568 = (fSlow567 + max(0.001f, fabsf((((iSlow555)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow558))):max(0.0080000000000000002f, (318.0f * powf(fSlow558,12.6f)))) * (((iSlow555)?fSlow557:fSlow556) - ((iSlow555)?fSlow550:fSlow549))))));
		float 	fSlow569 = (0 - (fConst0 * (fSlow567 - fSlow568)));
		float 	fSlow570 = (fConst0 * fSlow567);
		float 	fSlow571 = (fConst0 * fSlow568);
		float 	fSlow572 = (0 - (fConst0 * (fSlow566 - fSlow567)));
		float 	fSlow573 = (fConst0 * fSlow566);
		float 	fSlow574 = (0 - ((fSlow311 * fSlow542) * fSlow267));
		float 	fSlow575 = (fConst1 * (0 - ((fSlow313 * fSlow542) * fSlow267)));
		float 	fSlow576 = (fConst0 * fSlow553);
		float 	fSlow577 = (fSlow318 + ((iSlow317)?fSlow316:(fSlow384 * fSlow316)));
		float 	fSlow578 = (fConst1 * fSlow577);
		float 	fSlow579 = (fSlow324 + (0.0012626262626262627f * (fSlow387 * fSlow323)));
		float 	fSlow580 = (fSlow579 * fSlow322);
		float 	fSlow581 = (fSlow580 * fSlow321);
		float 	fSlow582 = powf((0.010101010101010102f * min((float)99, fSlow581)),0.69999999999999996f);
		float 	fSlow583 = powf((0.014705882352941176f * (float((fSlow581 >= 30.0f)) * min((fSlow581 + -30.0f), (float)68))),1.8f);
		float 	fSlow584 = (fSlow580 * fSlow330);
		int 	iSlow585 = int((fSlow584 <= fSlow581));
		float 	fSlow586 = powf((0.010101010101010102f * min((float)99, fSlow584)),0.69999999999999996f);
		float 	fSlow587 = powf((0.014705882352941176f * (float((fSlow584 >= 30.0f)) * min((fSlow584 + -30.0f), (float)68))),1.8f);
		float 	fSlow588 = (fSlow335 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow577))) + 48.0f));
		float 	fSlow589 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow337 + fSlow588))));
		float 	fSlow590 = max(0.001f, fabsf((((iSlow585)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow589))):max(0.0080000000000000002f, (318.0f * powf(fSlow589,12.6f)))) * (((iSlow585)?fSlow587:fSlow586) - ((iSlow585)?fSlow583:fSlow582)))));
		float 	fSlow591 = (fSlow580 * fSlow340);
		int 	iSlow592 = int((fSlow584 > fSlow591));
		float 	fSlow593 = powf((0.010101010101010102f * min((float)99, fSlow591)),0.69999999999999996f);
		float 	fSlow594 = powf((0.014705882352941176f * (float((fSlow591 >= 30.0f)) * min((fSlow591 + -30.0f), (float)68))),1.8f);
		float 	fSlow595 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow345 + fSlow588))));
		float 	fSlow596 = (fSlow580 * fSlow347);
		float 	fSlow597 = powf((0.010101010101010102f * min((float)99, fSlow596)),0.69999999999999996f);
		float 	fSlow598 = powf((0.014705882352941176f * (float((fSlow596 >= 30.0f)) * min((fSlow596 + -30.0f), (float)68))),1.8f);
		int 	iSlow599 = int((fSlow591 > fSlow596));
		float 	fSlow600 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow352 + fSlow588))));
		int 	iSlow601 = int((fSlow596 > fSlow581));
		float 	fSlow602 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow355 + fSlow588))));
		float 	fSlow603 = max(0.001f, fabsf((((iSlow601)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow602))):max(0.0080000000000000002f, (318.0f * powf(fSlow602,12.6f)))) * (((iSlow601)?fSlow583:fSlow582) - ((iSlow601)?fSlow598:fSlow597)))));
		float 	fSlow604 = (fSlow603 + max(0.001f, fabsf((((iSlow599)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow600))):max(0.0080000000000000002f, (318.0f * powf(fSlow600,12.6f)))) * (((iSlow599)?fSlow594:fSlow593) - ((iSlow599)?fSlow598:fSlow597))))));
		float 	fSlow605 = (fSlow604 + max(0.001f, fabsf((((iSlow592)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow595))):max(0.0080000000000000002f, (318.0f * powf(fSlow595,12.6f)))) * (((iSlow592)?fSlow594:fSlow593) - ((iSlow592)?fSlow587:fSlow586))))));
		float 	fSlow606 = (0 - (fConst0 * (fSlow604 - fSlow605)));
		float 	fSlow607 = (fConst0 * fSlow604);
		float 	fSlow608 = (fConst0 * fSlow605);
		float 	fSlow609 = (0 - (fConst0 * (fSlow603 - fSlow604)));
		float 	fSlow610 = (fConst0 * fSlow603);
		float 	fSlow611 = (0 - ((fSlow366 * fSlow579) * fSlow322));
		float 	fSlow612 = (fConst1 * (0 - ((fSlow368 * fSlow579) * fSlow322)));
		float 	fSlow613 = (fConst0 * fSlow590);
		float 	fSlow614 = (fSlow425 * fSlow382);
		float 	fSlow615 = float(fslider94);
		float 	fSlow616 = (fSlow36 + ((iSlow35)?fSlow33:(fSlow615 * fSlow33)));
		float 	fSlow617 = (fConst1 * fSlow616);
		float 	fSlow618 = float(fslider95);
		float 	fSlow619 = (fSlow43 + (0.0012626262626262627f * (fSlow618 * fSlow41)));
		float 	fSlow620 = (fSlow619 * fSlow40);
		float 	fSlow621 = (fSlow620 * fSlow39);
		float 	fSlow622 = powf((0.010101010101010102f * min((float)99, fSlow621)),0.69999999999999996f);
		float 	fSlow623 = powf((0.014705882352941176f * (float((fSlow621 >= 30.0f)) * min((fSlow621 + -30.0f), (float)68))),1.8f);
		float 	fSlow624 = (fSlow620 * fSlow49);
		int 	iSlow625 = int((fSlow624 <= fSlow621));
		float 	fSlow626 = powf((0.010101010101010102f * min((float)99, fSlow624)),0.69999999999999996f);
		float 	fSlow627 = powf((0.014705882352941176f * (float((fSlow624 >= 30.0f)) * min((fSlow624 + -30.0f), (float)68))),1.8f);
		float 	fSlow628 = (fSlow54 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow616))) + 48.0f));
		float 	fSlow629 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow56 + fSlow628))));
		float 	fSlow630 = max(0.001f, fabsf((((iSlow625)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow629))):max(0.0080000000000000002f, (318.0f * powf(fSlow629,12.6f)))) * (((iSlow625)?fSlow627:fSlow626) - ((iSlow625)?fSlow623:fSlow622)))));
		float 	fSlow631 = (fSlow620 * fSlow59);
		int 	iSlow632 = int((fSlow624 > fSlow631));
		float 	fSlow633 = powf((0.010101010101010102f * min((float)99, fSlow631)),0.69999999999999996f);
		float 	fSlow634 = powf((0.014705882352941176f * (float((fSlow631 >= 30.0f)) * min((fSlow631 + -30.0f), (float)68))),1.8f);
		float 	fSlow635 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow64 + fSlow628))));
		float 	fSlow636 = (fSlow620 * fSlow66);
		float 	fSlow637 = powf((0.010101010101010102f * min((float)99, fSlow636)),0.69999999999999996f);
		float 	fSlow638 = powf((0.014705882352941176f * (float((fSlow636 >= 30.0f)) * min((fSlow636 + -30.0f), (float)68))),1.8f);
		int 	iSlow639 = int((fSlow631 > fSlow636));
		float 	fSlow640 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow71 + fSlow628))));
		int 	iSlow641 = int((fSlow636 > fSlow621));
		float 	fSlow642 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow74 + fSlow628))));
		float 	fSlow643 = max(0.001f, fabsf((((iSlow641)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow642))):max(0.0080000000000000002f, (318.0f * powf(fSlow642,12.6f)))) * (((iSlow641)?fSlow623:fSlow622) - ((iSlow641)?fSlow638:fSlow637)))));
		float 	fSlow644 = (fSlow643 + max(0.001f, fabsf((((iSlow639)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow640))):max(0.0080000000000000002f, (318.0f * powf(fSlow640,12.6f)))) * (((iSlow639)?fSlow634:fSlow633) - ((iSlow639)?fSlow638:fSlow637))))));
		float 	fSlow645 = (fSlow644 + max(0.001f, fabsf((((iSlow632)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow635))):max(0.0080000000000000002f, (318.0f * powf(fSlow635,12.6f)))) * (((iSlow632)?fSlow634:fSlow633) - ((iSlow632)?fSlow627:fSlow626))))));
		float 	fSlow646 = (0 - (fConst0 * (fSlow644 - fSlow645)));
		float 	fSlow647 = (fConst0 * fSlow644);
		float 	fSlow648 = (fConst0 * fSlow645);
		float 	fSlow649 = float(fbutton2);
		int 	iSlow650 = int(((fSlow649 == 0.0f) > 0));
		float 	fSlow651 = (0 - (fConst0 * (fSlow643 - fSlow644)));
		float 	fSlow652 = (fConst0 * fSlow643);
		float 	fSlow653 = (0 - ((fSlow87 * fSlow619) * fSlow40));
		float 	fSlow654 = (fConst1 * (0 - ((fSlow89 * fSlow619) * fSlow40)));
		int 	iSlow655 = (fSlow649 > 0.0f);
		float 	fSlow656 = float(iSlow655);
		int 	iSlow657 = int(iSlow655);
		float 	fSlow658 = (fConst0 * fSlow630);
		int 	iSlow659 = int((iSlow655 > 0));
		float 	fSlow660 = (fSlow98 + ((iSlow97)?fSlow96:(fSlow615 * fSlow96)));
		float 	fSlow661 = (fConst1 * fSlow660);
		float 	fSlow662 = (fSlow104 + (0.0012626262626262627f * (fSlow618 * fSlow103)));
		float 	fSlow663 = (fSlow662 * fSlow102);
		float 	fSlow664 = (fSlow663 * fSlow101);
		float 	fSlow665 = powf((0.010101010101010102f * min((float)99, fSlow664)),0.69999999999999996f);
		float 	fSlow666 = powf((0.014705882352941176f * (float((fSlow664 >= 30.0f)) * min((fSlow664 + -30.0f), (float)68))),1.8f);
		float 	fSlow667 = (fSlow663 * fSlow110);
		int 	iSlow668 = int((fSlow667 <= fSlow664));
		float 	fSlow669 = powf((0.010101010101010102f * min((float)99, fSlow667)),0.69999999999999996f);
		float 	fSlow670 = powf((0.014705882352941176f * (float((fSlow667 >= 30.0f)) * min((fSlow667 + -30.0f), (float)68))),1.8f);
		float 	fSlow671 = (fSlow115 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow660))) + 48.0f));
		float 	fSlow672 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow117 + fSlow671))));
		float 	fSlow673 = max(0.001f, fabsf((((iSlow668)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow672))):max(0.0080000000000000002f, (318.0f * powf(fSlow672,12.6f)))) * (((iSlow668)?fSlow670:fSlow669) - ((iSlow668)?fSlow666:fSlow665)))));
		float 	fSlow674 = (fSlow663 * fSlow120);
		int 	iSlow675 = int((fSlow667 > fSlow674));
		float 	fSlow676 = powf((0.010101010101010102f * min((float)99, fSlow674)),0.69999999999999996f);
		float 	fSlow677 = powf((0.014705882352941176f * (float((fSlow674 >= 30.0f)) * min((fSlow674 + -30.0f), (float)68))),1.8f);
		float 	fSlow678 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow125 + fSlow671))));
		float 	fSlow679 = (fSlow663 * fSlow127);
		float 	fSlow680 = powf((0.010101010101010102f * min((float)99, fSlow679)),0.69999999999999996f);
		float 	fSlow681 = powf((0.014705882352941176f * (float((fSlow679 >= 30.0f)) * min((fSlow679 + -30.0f), (float)68))),1.8f);
		int 	iSlow682 = int((fSlow674 > fSlow679));
		float 	fSlow683 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow132 + fSlow671))));
		int 	iSlow684 = int((fSlow679 > fSlow664));
		float 	fSlow685 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow135 + fSlow671))));
		float 	fSlow686 = max(0.001f, fabsf((((iSlow684)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow685))):max(0.0080000000000000002f, (318.0f * powf(fSlow685,12.6f)))) * (((iSlow684)?fSlow666:fSlow665) - ((iSlow684)?fSlow681:fSlow680)))));
		float 	fSlow687 = (fSlow686 + max(0.001f, fabsf((((iSlow682)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow683))):max(0.0080000000000000002f, (318.0f * powf(fSlow683,12.6f)))) * (((iSlow682)?fSlow677:fSlow676) - ((iSlow682)?fSlow681:fSlow680))))));
		float 	fSlow688 = (fSlow687 + max(0.001f, fabsf((((iSlow675)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow678))):max(0.0080000000000000002f, (318.0f * powf(fSlow678,12.6f)))) * (((iSlow675)?fSlow677:fSlow676) - ((iSlow675)?fSlow670:fSlow669))))));
		float 	fSlow689 = (0 - (fConst0 * (fSlow687 - fSlow688)));
		float 	fSlow690 = (fConst0 * fSlow687);
		float 	fSlow691 = (fConst0 * fSlow688);
		float 	fSlow692 = (0 - (fConst0 * (fSlow686 - fSlow687)));
		float 	fSlow693 = (fConst0 * fSlow686);
		float 	fSlow694 = (0 - ((fSlow146 * fSlow662) * fSlow102));
		float 	fSlow695 = (fConst1 * (0 - ((fSlow148 * fSlow662) * fSlow102)));
		float 	fSlow696 = (fConst0 * fSlow673);
		float 	fSlow697 = (fSlow153 + ((iSlow152)?fSlow151:(fSlow615 * fSlow151)));
		float 	fSlow698 = (fConst1 * fSlow697);
		float 	fSlow699 = (fSlow159 + (0.0012626262626262627f * (fSlow618 * fSlow158)));
		float 	fSlow700 = (fSlow699 * fSlow157);
		float 	fSlow701 = (fSlow700 * fSlow156);
		float 	fSlow702 = powf((0.010101010101010102f * min((float)99, fSlow701)),0.69999999999999996f);
		float 	fSlow703 = powf((0.014705882352941176f * (float((fSlow701 >= 30.0f)) * min((fSlow701 + -30.0f), (float)68))),1.8f);
		float 	fSlow704 = (fSlow700 * fSlow165);
		int 	iSlow705 = int((fSlow704 <= fSlow701));
		float 	fSlow706 = powf((0.010101010101010102f * min((float)99, fSlow704)),0.69999999999999996f);
		float 	fSlow707 = powf((0.014705882352941176f * (float((fSlow704 >= 30.0f)) * min((fSlow704 + -30.0f), (float)68))),1.8f);
		float 	fSlow708 = (fSlow170 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow697))) + 48.0f));
		float 	fSlow709 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow172 + fSlow708))));
		float 	fSlow710 = max(0.001f, fabsf((((iSlow705)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow709))):max(0.0080000000000000002f, (318.0f * powf(fSlow709,12.6f)))) * (((iSlow705)?fSlow707:fSlow706) - ((iSlow705)?fSlow703:fSlow702)))));
		float 	fSlow711 = (fSlow700 * fSlow175);
		int 	iSlow712 = int((fSlow704 > fSlow711));
		float 	fSlow713 = powf((0.010101010101010102f * min((float)99, fSlow711)),0.69999999999999996f);
		float 	fSlow714 = powf((0.014705882352941176f * (float((fSlow711 >= 30.0f)) * min((fSlow711 + -30.0f), (float)68))),1.8f);
		float 	fSlow715 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow180 + fSlow708))));
		float 	fSlow716 = (fSlow700 * fSlow182);
		float 	fSlow717 = powf((0.010101010101010102f * min((float)99, fSlow716)),0.69999999999999996f);
		float 	fSlow718 = powf((0.014705882352941176f * (float((fSlow716 >= 30.0f)) * min((fSlow716 + -30.0f), (float)68))),1.8f);
		int 	iSlow719 = int((fSlow711 > fSlow716));
		float 	fSlow720 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow187 + fSlow708))));
		int 	iSlow721 = int((fSlow716 > fSlow701));
		float 	fSlow722 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow190 + fSlow708))));
		float 	fSlow723 = max(0.001f, fabsf((((iSlow721)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow722))):max(0.0080000000000000002f, (318.0f * powf(fSlow722,12.6f)))) * (((iSlow721)?fSlow703:fSlow702) - ((iSlow721)?fSlow718:fSlow717)))));
		float 	fSlow724 = (fSlow723 + max(0.001f, fabsf((((iSlow719)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow720))):max(0.0080000000000000002f, (318.0f * powf(fSlow720,12.6f)))) * (((iSlow719)?fSlow714:fSlow713) - ((iSlow719)?fSlow718:fSlow717))))));
		float 	fSlow725 = (fSlow724 + max(0.001f, fabsf((((iSlow712)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow715))):max(0.0080000000000000002f, (318.0f * powf(fSlow715,12.6f)))) * (((iSlow712)?fSlow714:fSlow713) - ((iSlow712)?fSlow707:fSlow706))))));
		float 	fSlow726 = (0 - (fConst0 * (fSlow724 - fSlow725)));
		float 	fSlow727 = (fConst0 * fSlow724);
		float 	fSlow728 = (fConst0 * fSlow725);
		float 	fSlow729 = (0 - (fConst0 * (fSlow723 - fSlow724)));
		float 	fSlow730 = (fConst0 * fSlow723);
		float 	fSlow731 = (0 - ((fSlow201 * fSlow699) * fSlow157));
		float 	fSlow732 = (fConst1 * (0 - ((fSlow203 * fSlow699) * fSlow157)));
		float 	fSlow733 = (fConst0 * fSlow710);
		float 	fSlow734 = (fSlow208 + ((iSlow207)?fSlow206:(fSlow615 * fSlow206)));
		float 	fSlow735 = (fConst1 * fSlow734);
		float 	fSlow736 = (fSlow214 + (0.0012626262626262627f * (fSlow618 * fSlow213)));
		float 	fSlow737 = (fSlow736 * fSlow212);
		float 	fSlow738 = (fSlow737 * fSlow211);
		float 	fSlow739 = powf((0.010101010101010102f * min((float)99, fSlow738)),0.69999999999999996f);
		float 	fSlow740 = powf((0.014705882352941176f * (float((fSlow738 >= 30.0f)) * min((fSlow738 + -30.0f), (float)68))),1.8f);
		float 	fSlow741 = (fSlow737 * fSlow220);
		int 	iSlow742 = int((fSlow741 <= fSlow738));
		float 	fSlow743 = powf((0.010101010101010102f * min((float)99, fSlow741)),0.69999999999999996f);
		float 	fSlow744 = powf((0.014705882352941176f * (float((fSlow741 >= 30.0f)) * min((fSlow741 + -30.0f), (float)68))),1.8f);
		float 	fSlow745 = (fSlow225 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow734))) + 48.0f));
		float 	fSlow746 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow227 + fSlow745))));
		float 	fSlow747 = max(0.001f, fabsf((((iSlow742)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow746))):max(0.0080000000000000002f, (318.0f * powf(fSlow746,12.6f)))) * (((iSlow742)?fSlow744:fSlow743) - ((iSlow742)?fSlow740:fSlow739)))));
		float 	fSlow748 = (fSlow737 * fSlow230);
		int 	iSlow749 = int((fSlow741 > fSlow748));
		float 	fSlow750 = powf((0.010101010101010102f * min((float)99, fSlow748)),0.69999999999999996f);
		float 	fSlow751 = powf((0.014705882352941176f * (float((fSlow748 >= 30.0f)) * min((fSlow748 + -30.0f), (float)68))),1.8f);
		float 	fSlow752 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow235 + fSlow745))));
		float 	fSlow753 = (fSlow737 * fSlow237);
		float 	fSlow754 = powf((0.010101010101010102f * min((float)99, fSlow753)),0.69999999999999996f);
		float 	fSlow755 = powf((0.014705882352941176f * (float((fSlow753 >= 30.0f)) * min((fSlow753 + -30.0f), (float)68))),1.8f);
		int 	iSlow756 = int((fSlow748 > fSlow753));
		float 	fSlow757 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow242 + fSlow745))));
		int 	iSlow758 = int((fSlow753 > fSlow738));
		float 	fSlow759 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow245 + fSlow745))));
		float 	fSlow760 = max(0.001f, fabsf((((iSlow758)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow759))):max(0.0080000000000000002f, (318.0f * powf(fSlow759,12.6f)))) * (((iSlow758)?fSlow740:fSlow739) - ((iSlow758)?fSlow755:fSlow754)))));
		float 	fSlow761 = (fSlow760 + max(0.001f, fabsf((((iSlow756)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow757))):max(0.0080000000000000002f, (318.0f * powf(fSlow757,12.6f)))) * (((iSlow756)?fSlow751:fSlow750) - ((iSlow756)?fSlow755:fSlow754))))));
		float 	fSlow762 = (fSlow761 + max(0.001f, fabsf((((iSlow749)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow752))):max(0.0080000000000000002f, (318.0f * powf(fSlow752,12.6f)))) * (((iSlow749)?fSlow751:fSlow750) - ((iSlow749)?fSlow744:fSlow743))))));
		float 	fSlow763 = (0 - (fConst0 * (fSlow761 - fSlow762)));
		float 	fSlow764 = (fConst0 * fSlow761);
		float 	fSlow765 = (fConst0 * fSlow762);
		float 	fSlow766 = (0 - (fConst0 * (fSlow760 - fSlow761)));
		float 	fSlow767 = (fConst0 * fSlow760);
		float 	fSlow768 = (0 - ((fSlow256 * fSlow736) * fSlow212));
		float 	fSlow769 = (fConst1 * (0 - ((fSlow258 * fSlow736) * fSlow212)));
		float 	fSlow770 = (fConst0 * fSlow747);
		float 	fSlow771 = (fSlow263 + ((iSlow262)?fSlow261:(fSlow615 * fSlow261)));
		float 	fSlow772 = (fConst1 * fSlow771);
		float 	fSlow773 = (fSlow269 + (0.0012626262626262627f * (fSlow618 * fSlow268)));
		float 	fSlow774 = (fSlow773 * fSlow267);
		float 	fSlow775 = (fSlow774 * fSlow266);
		float 	fSlow776 = powf((0.010101010101010102f * min((float)99, fSlow775)),0.69999999999999996f);
		float 	fSlow777 = powf((0.014705882352941176f * (float((fSlow775 >= 30.0f)) * min((fSlow775 + -30.0f), (float)68))),1.8f);
		float 	fSlow778 = (fSlow774 * fSlow275);
		int 	iSlow779 = int((fSlow778 <= fSlow775));
		float 	fSlow780 = powf((0.010101010101010102f * min((float)99, fSlow778)),0.69999999999999996f);
		float 	fSlow781 = powf((0.014705882352941176f * (float((fSlow778 >= 30.0f)) * min((fSlow778 + -30.0f), (float)68))),1.8f);
		float 	fSlow782 = (fSlow280 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow771))) + 48.0f));
		float 	fSlow783 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow282 + fSlow782))));
		float 	fSlow784 = max(0.001f, fabsf((((iSlow779)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow783))):max(0.0080000000000000002f, (318.0f * powf(fSlow783,12.6f)))) * (((iSlow779)?fSlow781:fSlow780) - ((iSlow779)?fSlow777:fSlow776)))));
		float 	fSlow785 = (fSlow774 * fSlow285);
		int 	iSlow786 = int((fSlow778 > fSlow785));
		float 	fSlow787 = powf((0.010101010101010102f * min((float)99, fSlow785)),0.69999999999999996f);
		float 	fSlow788 = powf((0.014705882352941176f * (float((fSlow785 >= 30.0f)) * min((fSlow785 + -30.0f), (float)68))),1.8f);
		float 	fSlow789 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow290 + fSlow782))));
		float 	fSlow790 = (fSlow774 * fSlow292);
		float 	fSlow791 = powf((0.010101010101010102f * min((float)99, fSlow790)),0.69999999999999996f);
		float 	fSlow792 = powf((0.014705882352941176f * (float((fSlow790 >= 30.0f)) * min((fSlow790 + -30.0f), (float)68))),1.8f);
		int 	iSlow793 = int((fSlow785 > fSlow790));
		float 	fSlow794 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow297 + fSlow782))));
		int 	iSlow795 = int((fSlow790 > fSlow775));
		float 	fSlow796 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow300 + fSlow782))));
		float 	fSlow797 = max(0.001f, fabsf((((iSlow795)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow796))):max(0.0080000000000000002f, (318.0f * powf(fSlow796,12.6f)))) * (((iSlow795)?fSlow777:fSlow776) - ((iSlow795)?fSlow792:fSlow791)))));
		float 	fSlow798 = (fSlow797 + max(0.001f, fabsf((((iSlow793)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow794))):max(0.0080000000000000002f, (318.0f * powf(fSlow794,12.6f)))) * (((iSlow793)?fSlow788:fSlow787) - ((iSlow793)?fSlow792:fSlow791))))));
		float 	fSlow799 = (fSlow798 + max(0.001f, fabsf((((iSlow786)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow789))):max(0.0080000000000000002f, (318.0f * powf(fSlow789,12.6f)))) * (((iSlow786)?fSlow788:fSlow787) - ((iSlow786)?fSlow781:fSlow780))))));
		float 	fSlow800 = (0 - (fConst0 * (fSlow798 - fSlow799)));
		float 	fSlow801 = (fConst0 * fSlow798);
		float 	fSlow802 = (fConst0 * fSlow799);
		float 	fSlow803 = (0 - (fConst0 * (fSlow797 - fSlow798)));
		float 	fSlow804 = (fConst0 * fSlow797);
		float 	fSlow805 = (0 - ((fSlow311 * fSlow773) * fSlow267));
		float 	fSlow806 = (fConst1 * (0 - ((fSlow313 * fSlow773) * fSlow267)));
		float 	fSlow807 = (fConst0 * fSlow784);
		float 	fSlow808 = (fSlow318 + ((iSlow317)?fSlow316:(fSlow615 * fSlow316)));
		float 	fSlow809 = (fConst1 * fSlow808);
		float 	fSlow810 = (fSlow324 + (0.0012626262626262627f * (fSlow618 * fSlow323)));
		float 	fSlow811 = (fSlow810 * fSlow322);
		float 	fSlow812 = (fSlow811 * fSlow321);
		float 	fSlow813 = powf((0.010101010101010102f * min((float)99, fSlow812)),0.69999999999999996f);
		float 	fSlow814 = powf((0.014705882352941176f * (float((fSlow812 >= 30.0f)) * min((fSlow812 + -30.0f), (float)68))),1.8f);
		float 	fSlow815 = (fSlow811 * fSlow330);
		int 	iSlow816 = int((fSlow815 <= fSlow812));
		float 	fSlow817 = powf((0.010101010101010102f * min((float)99, fSlow815)),0.69999999999999996f);
		float 	fSlow818 = powf((0.014705882352941176f * (float((fSlow815 >= 30.0f)) * min((fSlow815 + -30.0f), (float)68))),1.8f);
		float 	fSlow819 = (fSlow335 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow808))) + 48.0f));
		float 	fSlow820 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow337 + fSlow819))));
		float 	fSlow821 = max(0.001f, fabsf((((iSlow816)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow820))):max(0.0080000000000000002f, (318.0f * powf(fSlow820,12.6f)))) * (((iSlow816)?fSlow818:fSlow817) - ((iSlow816)?fSlow814:fSlow813)))));
		float 	fSlow822 = (fSlow811 * fSlow340);
		int 	iSlow823 = int((fSlow815 > fSlow822));
		float 	fSlow824 = powf((0.010101010101010102f * min((float)99, fSlow822)),0.69999999999999996f);
		float 	fSlow825 = powf((0.014705882352941176f * (float((fSlow822 >= 30.0f)) * min((fSlow822 + -30.0f), (float)68))),1.8f);
		float 	fSlow826 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow345 + fSlow819))));
		float 	fSlow827 = (fSlow811 * fSlow347);
		float 	fSlow828 = powf((0.010101010101010102f * min((float)99, fSlow827)),0.69999999999999996f);
		float 	fSlow829 = powf((0.014705882352941176f * (float((fSlow827 >= 30.0f)) * min((fSlow827 + -30.0f), (float)68))),1.8f);
		int 	iSlow830 = int((fSlow822 > fSlow827));
		float 	fSlow831 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow352 + fSlow819))));
		int 	iSlow832 = int((fSlow827 > fSlow812));
		float 	fSlow833 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow355 + fSlow819))));
		float 	fSlow834 = max(0.001f, fabsf((((iSlow832)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow833))):max(0.0080000000000000002f, (318.0f * powf(fSlow833,12.6f)))) * (((iSlow832)?fSlow814:fSlow813) - ((iSlow832)?fSlow829:fSlow828)))));
		float 	fSlow835 = (fSlow834 + max(0.001f, fabsf((((iSlow830)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow831))):max(0.0080000000000000002f, (318.0f * powf(fSlow831,12.6f)))) * (((iSlow830)?fSlow825:fSlow824) - ((iSlow830)?fSlow829:fSlow828))))));
		float 	fSlow836 = (fSlow835 + max(0.001f, fabsf((((iSlow823)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow826))):max(0.0080000000000000002f, (318.0f * powf(fSlow826,12.6f)))) * (((iSlow823)?fSlow825:fSlow824) - ((iSlow823)?fSlow818:fSlow817))))));
		float 	fSlow837 = (0 - (fConst0 * (fSlow835 - fSlow836)));
		float 	fSlow838 = (fConst0 * fSlow835);
		float 	fSlow839 = (fConst0 * fSlow836);
		float 	fSlow840 = (0 - (fConst0 * (fSlow834 - fSlow835)));
		float 	fSlow841 = (fConst0 * fSlow834);
		float 	fSlow842 = (0 - ((fSlow366 * fSlow810) * fSlow322));
		float 	fSlow843 = (fConst1 * (0 - ((fSlow368 * fSlow810) * fSlow322)));
		float 	fSlow844 = (fConst0 * fSlow821);
		float 	fSlow845 = (fSlow656 * fSlow382);
		float 	fSlow846 = float(fslider96);
		float 	fSlow847 = (fSlow36 + ((iSlow35)?fSlow33:(fSlow846 * fSlow33)));
		float 	fSlow848 = (fConst1 * fSlow847);
		float 	fSlow849 = float(fslider97);
		float 	fSlow850 = (fSlow43 + (0.0012626262626262627f * (fSlow849 * fSlow41)));
		float 	fSlow851 = (fSlow850 * fSlow40);
		float 	fSlow852 = (fSlow851 * fSlow39);
		float 	fSlow853 = powf((0.010101010101010102f * min((float)99, fSlow852)),0.69999999999999996f);
		float 	fSlow854 = powf((0.014705882352941176f * (float((fSlow852 >= 30.0f)) * min((fSlow852 + -30.0f), (float)68))),1.8f);
		float 	fSlow855 = (fSlow851 * fSlow49);
		int 	iSlow856 = int((fSlow855 <= fSlow852));
		float 	fSlow857 = powf((0.010101010101010102f * min((float)99, fSlow855)),0.69999999999999996f);
		float 	fSlow858 = powf((0.014705882352941176f * (float((fSlow855 >= 30.0f)) * min((fSlow855 + -30.0f), (float)68))),1.8f);
		float 	fSlow859 = (fSlow54 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow847))) + 48.0f));
		float 	fSlow860 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow56 + fSlow859))));
		float 	fSlow861 = max(0.001f, fabsf((((iSlow856)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow860))):max(0.0080000000000000002f, (318.0f * powf(fSlow860,12.6f)))) * (((iSlow856)?fSlow858:fSlow857) - ((iSlow856)?fSlow854:fSlow853)))));
		float 	fSlow862 = (fSlow851 * fSlow59);
		int 	iSlow863 = int((fSlow855 > fSlow862));
		float 	fSlow864 = powf((0.010101010101010102f * min((float)99, fSlow862)),0.69999999999999996f);
		float 	fSlow865 = powf((0.014705882352941176f * (float((fSlow862 >= 30.0f)) * min((fSlow862 + -30.0f), (float)68))),1.8f);
		float 	fSlow866 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow64 + fSlow859))));
		float 	fSlow867 = (fSlow851 * fSlow66);
		float 	fSlow868 = powf((0.010101010101010102f * min((float)99, fSlow867)),0.69999999999999996f);
		float 	fSlow869 = powf((0.014705882352941176f * (float((fSlow867 >= 30.0f)) * min((fSlow867 + -30.0f), (float)68))),1.8f);
		int 	iSlow870 = int((fSlow862 > fSlow867));
		float 	fSlow871 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow71 + fSlow859))));
		int 	iSlow872 = int((fSlow867 > fSlow852));
		float 	fSlow873 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow74 + fSlow859))));
		float 	fSlow874 = max(0.001f, fabsf((((iSlow872)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow873))):max(0.0080000000000000002f, (318.0f * powf(fSlow873,12.6f)))) * (((iSlow872)?fSlow854:fSlow853) - ((iSlow872)?fSlow869:fSlow868)))));
		float 	fSlow875 = (fSlow874 + max(0.001f, fabsf((((iSlow870)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow871))):max(0.0080000000000000002f, (318.0f * powf(fSlow871,12.6f)))) * (((iSlow870)?fSlow865:fSlow864) - ((iSlow870)?fSlow869:fSlow868))))));
		float 	fSlow876 = (fSlow875 + max(0.001f, fabsf((((iSlow863)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow866))):max(0.0080000000000000002f, (318.0f * powf(fSlow866,12.6f)))) * (((iSlow863)?fSlow865:fSlow864) - ((iSlow863)?fSlow858:fSlow857))))));
		float 	fSlow877 = (0 - (fConst0 * (fSlow875 - fSlow876)));
		float 	fSlow878 = (fConst0 * fSlow875);
		float 	fSlow879 = (fConst0 * fSlow876);
		float 	fSlow880 = float(fbutton3);
		int 	iSlow881 = int(((fSlow880 == 0.0f) > 0));
		float 	fSlow882 = (0 - (fConst0 * (fSlow874 - fSlow875)));
		float 	fSlow883 = (fConst0 * fSlow874);
		float 	fSlow884 = (0 - ((fSlow87 * fSlow850) * fSlow40));
		float 	fSlow885 = (fConst1 * (0 - ((fSlow89 * fSlow850) * fSlow40)));
		int 	iSlow886 = (fSlow880 > 0.0f);
		float 	fSlow887 = float(iSlow886);
		int 	iSlow888 = int(iSlow886);
		float 	fSlow889 = (fConst0 * fSlow861);
		int 	iSlow890 = int((iSlow886 > 0));
		float 	fSlow891 = (fSlow98 + ((iSlow97)?fSlow96:(fSlow846 * fSlow96)));
		float 	fSlow892 = (fConst1 * fSlow891);
		float 	fSlow893 = (fSlow104 + (0.0012626262626262627f * (fSlow849 * fSlow103)));
		float 	fSlow894 = (fSlow893 * fSlow102);
		float 	fSlow895 = (fSlow894 * fSlow101);
		float 	fSlow896 = powf((0.010101010101010102f * min((float)99, fSlow895)),0.69999999999999996f);
		float 	fSlow897 = powf((0.014705882352941176f * (float((fSlow895 >= 30.0f)) * min((fSlow895 + -30.0f), (float)68))),1.8f);
		float 	fSlow898 = (fSlow894 * fSlow110);
		int 	iSlow899 = int((fSlow898 <= fSlow895));
		float 	fSlow900 = powf((0.010101010101010102f * min((float)99, fSlow898)),0.69999999999999996f);
		float 	fSlow901 = powf((0.014705882352941176f * (float((fSlow898 >= 30.0f)) * min((fSlow898 + -30.0f), (float)68))),1.8f);
		float 	fSlow902 = (fSlow115 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow891))) + 48.0f));
		float 	fSlow903 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow117 + fSlow902))));
		float 	fSlow904 = max(0.001f, fabsf((((iSlow899)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow903))):max(0.0080000000000000002f, (318.0f * powf(fSlow903,12.6f)))) * (((iSlow899)?fSlow901:fSlow900) - ((iSlow899)?fSlow897:fSlow896)))));
		float 	fSlow905 = (fSlow894 * fSlow120);
		int 	iSlow906 = int((fSlow898 > fSlow905));
		float 	fSlow907 = powf((0.010101010101010102f * min((float)99, fSlow905)),0.69999999999999996f);
		float 	fSlow908 = powf((0.014705882352941176f * (float((fSlow905 >= 30.0f)) * min((fSlow905 + -30.0f), (float)68))),1.8f);
		float 	fSlow909 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow125 + fSlow902))));
		float 	fSlow910 = (fSlow894 * fSlow127);
		float 	fSlow911 = powf((0.010101010101010102f * min((float)99, fSlow910)),0.69999999999999996f);
		float 	fSlow912 = powf((0.014705882352941176f * (float((fSlow910 >= 30.0f)) * min((fSlow910 + -30.0f), (float)68))),1.8f);
		int 	iSlow913 = int((fSlow905 > fSlow910));
		float 	fSlow914 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow132 + fSlow902))));
		int 	iSlow915 = int((fSlow910 > fSlow895));
		float 	fSlow916 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow135 + fSlow902))));
		float 	fSlow917 = max(0.001f, fabsf((((iSlow915)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow916))):max(0.0080000000000000002f, (318.0f * powf(fSlow916,12.6f)))) * (((iSlow915)?fSlow897:fSlow896) - ((iSlow915)?fSlow912:fSlow911)))));
		float 	fSlow918 = (fSlow917 + max(0.001f, fabsf((((iSlow913)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow914))):max(0.0080000000000000002f, (318.0f * powf(fSlow914,12.6f)))) * (((iSlow913)?fSlow908:fSlow907) - ((iSlow913)?fSlow912:fSlow911))))));
		float 	fSlow919 = (fSlow918 + max(0.001f, fabsf((((iSlow906)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow909))):max(0.0080000000000000002f, (318.0f * powf(fSlow909,12.6f)))) * (((iSlow906)?fSlow908:fSlow907) - ((iSlow906)?fSlow901:fSlow900))))));
		float 	fSlow920 = (0 - (fConst0 * (fSlow918 - fSlow919)));
		float 	fSlow921 = (fConst0 * fSlow918);
		float 	fSlow922 = (fConst0 * fSlow919);
		float 	fSlow923 = (0 - (fConst0 * (fSlow917 - fSlow918)));
		float 	fSlow924 = (fConst0 * fSlow917);
		float 	fSlow925 = (0 - ((fSlow146 * fSlow893) * fSlow102));
		float 	fSlow926 = (fConst1 * (0 - ((fSlow148 * fSlow893) * fSlow102)));
		float 	fSlow927 = (fConst0 * fSlow904);
		float 	fSlow928 = (fSlow153 + ((iSlow152)?fSlow151:(fSlow846 * fSlow151)));
		float 	fSlow929 = (fConst1 * fSlow928);
		float 	fSlow930 = (fSlow159 + (0.0012626262626262627f * (fSlow849 * fSlow158)));
		float 	fSlow931 = (fSlow930 * fSlow157);
		float 	fSlow932 = (fSlow931 * fSlow156);
		float 	fSlow933 = powf((0.010101010101010102f * min((float)99, fSlow932)),0.69999999999999996f);
		float 	fSlow934 = powf((0.014705882352941176f * (float((fSlow932 >= 30.0f)) * min((fSlow932 + -30.0f), (float)68))),1.8f);
		float 	fSlow935 = (fSlow931 * fSlow165);
		int 	iSlow936 = int((fSlow935 <= fSlow932));
		float 	fSlow937 = powf((0.010101010101010102f * min((float)99, fSlow935)),0.69999999999999996f);
		float 	fSlow938 = powf((0.014705882352941176f * (float((fSlow935 >= 30.0f)) * min((fSlow935 + -30.0f), (float)68))),1.8f);
		float 	fSlow939 = (fSlow170 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow928))) + 48.0f));
		float 	fSlow940 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow172 + fSlow939))));
		float 	fSlow941 = max(0.001f, fabsf((((iSlow936)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow940))):max(0.0080000000000000002f, (318.0f * powf(fSlow940,12.6f)))) * (((iSlow936)?fSlow938:fSlow937) - ((iSlow936)?fSlow934:fSlow933)))));
		float 	fSlow942 = (fSlow931 * fSlow175);
		int 	iSlow943 = int((fSlow935 > fSlow942));
		float 	fSlow944 = powf((0.010101010101010102f * min((float)99, fSlow942)),0.69999999999999996f);
		float 	fSlow945 = powf((0.014705882352941176f * (float((fSlow942 >= 30.0f)) * min((fSlow942 + -30.0f), (float)68))),1.8f);
		float 	fSlow946 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow180 + fSlow939))));
		float 	fSlow947 = (fSlow931 * fSlow182);
		float 	fSlow948 = powf((0.010101010101010102f * min((float)99, fSlow947)),0.69999999999999996f);
		float 	fSlow949 = powf((0.014705882352941176f * (float((fSlow947 >= 30.0f)) * min((fSlow947 + -30.0f), (float)68))),1.8f);
		int 	iSlow950 = int((fSlow942 > fSlow947));
		float 	fSlow951 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow187 + fSlow939))));
		int 	iSlow952 = int((fSlow947 > fSlow932));
		float 	fSlow953 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow190 + fSlow939))));
		float 	fSlow954 = max(0.001f, fabsf((((iSlow952)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow953))):max(0.0080000000000000002f, (318.0f * powf(fSlow953,12.6f)))) * (((iSlow952)?fSlow934:fSlow933) - ((iSlow952)?fSlow949:fSlow948)))));
		float 	fSlow955 = (fSlow954 + max(0.001f, fabsf((((iSlow950)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow951))):max(0.0080000000000000002f, (318.0f * powf(fSlow951,12.6f)))) * (((iSlow950)?fSlow945:fSlow944) - ((iSlow950)?fSlow949:fSlow948))))));
		float 	fSlow956 = (fSlow955 + max(0.001f, fabsf((((iSlow943)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow946))):max(0.0080000000000000002f, (318.0f * powf(fSlow946,12.6f)))) * (((iSlow943)?fSlow945:fSlow944) - ((iSlow943)?fSlow938:fSlow937))))));
		float 	fSlow957 = (0 - (fConst0 * (fSlow955 - fSlow956)));
		float 	fSlow958 = (fConst0 * fSlow955);
		float 	fSlow959 = (fConst0 * fSlow956);
		float 	fSlow960 = (0 - (fConst0 * (fSlow954 - fSlow955)));
		float 	fSlow961 = (fConst0 * fSlow954);
		float 	fSlow962 = (0 - ((fSlow201 * fSlow930) * fSlow157));
		float 	fSlow963 = (fConst1 * (0 - ((fSlow203 * fSlow930) * fSlow157)));
		float 	fSlow964 = (fConst0 * fSlow941);
		float 	fSlow965 = (fSlow208 + ((iSlow207)?fSlow206:(fSlow846 * fSlow206)));
		float 	fSlow966 = (fConst1 * fSlow965);
		float 	fSlow967 = (fSlow214 + (0.0012626262626262627f * (fSlow849 * fSlow213)));
		float 	fSlow968 = (fSlow967 * fSlow212);
		float 	fSlow969 = (fSlow968 * fSlow211);
		float 	fSlow970 = powf((0.010101010101010102f * min((float)99, fSlow969)),0.69999999999999996f);
		float 	fSlow971 = powf((0.014705882352941176f * (float((fSlow969 >= 30.0f)) * min((fSlow969 + -30.0f), (float)68))),1.8f);
		float 	fSlow972 = (fSlow968 * fSlow220);
		int 	iSlow973 = int((fSlow972 <= fSlow969));
		float 	fSlow974 = powf((0.010101010101010102f * min((float)99, fSlow972)),0.69999999999999996f);
		float 	fSlow975 = powf((0.014705882352941176f * (float((fSlow972 >= 30.0f)) * min((fSlow972 + -30.0f), (float)68))),1.8f);
		float 	fSlow976 = (fSlow225 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow965))) + 48.0f));
		float 	fSlow977 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow227 + fSlow976))));
		float 	fSlow978 = max(0.001f, fabsf((((iSlow973)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow977))):max(0.0080000000000000002f, (318.0f * powf(fSlow977,12.6f)))) * (((iSlow973)?fSlow975:fSlow974) - ((iSlow973)?fSlow971:fSlow970)))));
		float 	fSlow979 = (fSlow968 * fSlow230);
		int 	iSlow980 = int((fSlow972 > fSlow979));
		float 	fSlow981 = powf((0.010101010101010102f * min((float)99, fSlow979)),0.69999999999999996f);
		float 	fSlow982 = powf((0.014705882352941176f * (float((fSlow979 >= 30.0f)) * min((fSlow979 + -30.0f), (float)68))),1.8f);
		float 	fSlow983 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow235 + fSlow976))));
		float 	fSlow984 = (fSlow968 * fSlow237);
		float 	fSlow985 = powf((0.010101010101010102f * min((float)99, fSlow984)),0.69999999999999996f);
		float 	fSlow986 = powf((0.014705882352941176f * (float((fSlow984 >= 30.0f)) * min((fSlow984 + -30.0f), (float)68))),1.8f);
		int 	iSlow987 = int((fSlow979 > fSlow984));
		float 	fSlow988 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow242 + fSlow976))));
		int 	iSlow989 = int((fSlow984 > fSlow969));
		float 	fSlow990 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow245 + fSlow976))));
		float 	fSlow991 = max(0.001f, fabsf((((iSlow989)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow990))):max(0.0080000000000000002f, (318.0f * powf(fSlow990,12.6f)))) * (((iSlow989)?fSlow971:fSlow970) - ((iSlow989)?fSlow986:fSlow985)))));
		float 	fSlow992 = (fSlow991 + max(0.001f, fabsf((((iSlow987)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow988))):max(0.0080000000000000002f, (318.0f * powf(fSlow988,12.6f)))) * (((iSlow987)?fSlow982:fSlow981) - ((iSlow987)?fSlow986:fSlow985))))));
		float 	fSlow993 = (fSlow992 + max(0.001f, fabsf((((iSlow980)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow983))):max(0.0080000000000000002f, (318.0f * powf(fSlow983,12.6f)))) * (((iSlow980)?fSlow982:fSlow981) - ((iSlow980)?fSlow975:fSlow974))))));
		float 	fSlow994 = (0 - (fConst0 * (fSlow992 - fSlow993)));
		float 	fSlow995 = (fConst0 * fSlow992);
		float 	fSlow996 = (fConst0 * fSlow993);
		float 	fSlow997 = (0 - (fConst0 * (fSlow991 - fSlow992)));
		float 	fSlow998 = (fConst0 * fSlow991);
		float 	fSlow999 = (0 - ((fSlow256 * fSlow967) * fSlow212));
		float 	fSlow1000 = (fConst1 * (0 - ((fSlow258 * fSlow967) * fSlow212)));
		float 	fSlow1001 = (fConst0 * fSlow978);
		float 	fSlow1002 = (fSlow263 + ((iSlow262)?fSlow261:(fSlow846 * fSlow261)));
		float 	fSlow1003 = (fConst1 * fSlow1002);
		float 	fSlow1004 = (fSlow269 + (0.0012626262626262627f * (fSlow849 * fSlow268)));
		float 	fSlow1005 = (fSlow1004 * fSlow267);
		float 	fSlow1006 = (fSlow1005 * fSlow266);
		float 	fSlow1007 = powf((0.010101010101010102f * min((float)99, fSlow1006)),0.69999999999999996f);
		float 	fSlow1008 = powf((0.014705882352941176f * (float((fSlow1006 >= 30.0f)) * min((fSlow1006 + -30.0f), (float)68))),1.8f);
		float 	fSlow1009 = (fSlow1005 * fSlow275);
		int 	iSlow1010 = int((fSlow1009 <= fSlow1006));
		float 	fSlow1011 = powf((0.010101010101010102f * min((float)99, fSlow1009)),0.69999999999999996f);
		float 	fSlow1012 = powf((0.014705882352941176f * (float((fSlow1009 >= 30.0f)) * min((fSlow1009 + -30.0f), (float)68))),1.8f);
		float 	fSlow1013 = (fSlow280 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1002))) + 48.0f));
		float 	fSlow1014 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow282 + fSlow1013))));
		float 	fSlow1015 = max(0.001f, fabsf((((iSlow1010)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1014))):max(0.0080000000000000002f, (318.0f * powf(fSlow1014,12.6f)))) * (((iSlow1010)?fSlow1012:fSlow1011) - ((iSlow1010)?fSlow1008:fSlow1007)))));
		float 	fSlow1016 = (fSlow1005 * fSlow285);
		int 	iSlow1017 = int((fSlow1009 > fSlow1016));
		float 	fSlow1018 = powf((0.010101010101010102f * min((float)99, fSlow1016)),0.69999999999999996f);
		float 	fSlow1019 = powf((0.014705882352941176f * (float((fSlow1016 >= 30.0f)) * min((fSlow1016 + -30.0f), (float)68))),1.8f);
		float 	fSlow1020 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow290 + fSlow1013))));
		float 	fSlow1021 = (fSlow1005 * fSlow292);
		float 	fSlow1022 = powf((0.010101010101010102f * min((float)99, fSlow1021)),0.69999999999999996f);
		float 	fSlow1023 = powf((0.014705882352941176f * (float((fSlow1021 >= 30.0f)) * min((fSlow1021 + -30.0f), (float)68))),1.8f);
		int 	iSlow1024 = int((fSlow1016 > fSlow1021));
		float 	fSlow1025 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow297 + fSlow1013))));
		int 	iSlow1026 = int((fSlow1021 > fSlow1006));
		float 	fSlow1027 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow300 + fSlow1013))));
		float 	fSlow1028 = max(0.001f, fabsf((((iSlow1026)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1027))):max(0.0080000000000000002f, (318.0f * powf(fSlow1027,12.6f)))) * (((iSlow1026)?fSlow1008:fSlow1007) - ((iSlow1026)?fSlow1023:fSlow1022)))));
		float 	fSlow1029 = (fSlow1028 + max(0.001f, fabsf((((iSlow1024)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1025))):max(0.0080000000000000002f, (318.0f * powf(fSlow1025,12.6f)))) * (((iSlow1024)?fSlow1019:fSlow1018) - ((iSlow1024)?fSlow1023:fSlow1022))))));
		float 	fSlow1030 = (fSlow1029 + max(0.001f, fabsf((((iSlow1017)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1020))):max(0.0080000000000000002f, (318.0f * powf(fSlow1020,12.6f)))) * (((iSlow1017)?fSlow1019:fSlow1018) - ((iSlow1017)?fSlow1012:fSlow1011))))));
		float 	fSlow1031 = (0 - (fConst0 * (fSlow1029 - fSlow1030)));
		float 	fSlow1032 = (fConst0 * fSlow1029);
		float 	fSlow1033 = (fConst0 * fSlow1030);
		float 	fSlow1034 = (0 - (fConst0 * (fSlow1028 - fSlow1029)));
		float 	fSlow1035 = (fConst0 * fSlow1028);
		float 	fSlow1036 = (0 - ((fSlow311 * fSlow1004) * fSlow267));
		float 	fSlow1037 = (fConst1 * (0 - ((fSlow313 * fSlow1004) * fSlow267)));
		float 	fSlow1038 = (fConst0 * fSlow1015);
		float 	fSlow1039 = (fSlow318 + ((iSlow317)?fSlow316:(fSlow846 * fSlow316)));
		float 	fSlow1040 = (fConst1 * fSlow1039);
		float 	fSlow1041 = (fSlow324 + (0.0012626262626262627f * (fSlow849 * fSlow323)));
		float 	fSlow1042 = (fSlow1041 * fSlow322);
		float 	fSlow1043 = (fSlow1042 * fSlow321);
		float 	fSlow1044 = powf((0.010101010101010102f * min((float)99, fSlow1043)),0.69999999999999996f);
		float 	fSlow1045 = powf((0.014705882352941176f * (float((fSlow1043 >= 30.0f)) * min((fSlow1043 + -30.0f), (float)68))),1.8f);
		float 	fSlow1046 = (fSlow1042 * fSlow330);
		int 	iSlow1047 = int((fSlow1046 <= fSlow1043));
		float 	fSlow1048 = powf((0.010101010101010102f * min((float)99, fSlow1046)),0.69999999999999996f);
		float 	fSlow1049 = powf((0.014705882352941176f * (float((fSlow1046 >= 30.0f)) * min((fSlow1046 + -30.0f), (float)68))),1.8f);
		float 	fSlow1050 = (fSlow335 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1039))) + 48.0f));
		float 	fSlow1051 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow337 + fSlow1050))));
		float 	fSlow1052 = max(0.001f, fabsf((((iSlow1047)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1051))):max(0.0080000000000000002f, (318.0f * powf(fSlow1051,12.6f)))) * (((iSlow1047)?fSlow1049:fSlow1048) - ((iSlow1047)?fSlow1045:fSlow1044)))));
		float 	fSlow1053 = (fSlow1042 * fSlow340);
		int 	iSlow1054 = int((fSlow1046 > fSlow1053));
		float 	fSlow1055 = powf((0.010101010101010102f * min((float)99, fSlow1053)),0.69999999999999996f);
		float 	fSlow1056 = powf((0.014705882352941176f * (float((fSlow1053 >= 30.0f)) * min((fSlow1053 + -30.0f), (float)68))),1.8f);
		float 	fSlow1057 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow345 + fSlow1050))));
		float 	fSlow1058 = (fSlow1042 * fSlow347);
		float 	fSlow1059 = powf((0.010101010101010102f * min((float)99, fSlow1058)),0.69999999999999996f);
		float 	fSlow1060 = powf((0.014705882352941176f * (float((fSlow1058 >= 30.0f)) * min((fSlow1058 + -30.0f), (float)68))),1.8f);
		int 	iSlow1061 = int((fSlow1053 > fSlow1058));
		float 	fSlow1062 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow352 + fSlow1050))));
		int 	iSlow1063 = int((fSlow1058 > fSlow1043));
		float 	fSlow1064 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow355 + fSlow1050))));
		float 	fSlow1065 = max(0.001f, fabsf((((iSlow1063)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1064))):max(0.0080000000000000002f, (318.0f * powf(fSlow1064,12.6f)))) * (((iSlow1063)?fSlow1045:fSlow1044) - ((iSlow1063)?fSlow1060:fSlow1059)))));
		float 	fSlow1066 = (fSlow1065 + max(0.001f, fabsf((((iSlow1061)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1062))):max(0.0080000000000000002f, (318.0f * powf(fSlow1062,12.6f)))) * (((iSlow1061)?fSlow1056:fSlow1055) - ((iSlow1061)?fSlow1060:fSlow1059))))));
		float 	fSlow1067 = (fSlow1066 + max(0.001f, fabsf((((iSlow1054)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1057))):max(0.0080000000000000002f, (318.0f * powf(fSlow1057,12.6f)))) * (((iSlow1054)?fSlow1056:fSlow1055) - ((iSlow1054)?fSlow1049:fSlow1048))))));
		float 	fSlow1068 = (0 - (fConst0 * (fSlow1066 - fSlow1067)));
		float 	fSlow1069 = (fConst0 * fSlow1066);
		float 	fSlow1070 = (fConst0 * fSlow1067);
		float 	fSlow1071 = (0 - (fConst0 * (fSlow1065 - fSlow1066)));
		float 	fSlow1072 = (fConst0 * fSlow1065);
		float 	fSlow1073 = (0 - ((fSlow366 * fSlow1041) * fSlow322));
		float 	fSlow1074 = (fConst1 * (0 - ((fSlow368 * fSlow1041) * fSlow322)));
		float 	fSlow1075 = (fConst0 * fSlow1052);
		float 	fSlow1076 = (fSlow887 * fSlow382);
		float 	fSlow1077 = float(fslider98);
		float 	fSlow1078 = (fSlow36 + ((iSlow35)?fSlow33:(fSlow1077 * fSlow33)));
		float 	fSlow1079 = (fConst1 * fSlow1078);
		float 	fSlow1080 = float(fslider99);
		float 	fSlow1081 = (fSlow43 + (0.0012626262626262627f * (fSlow1080 * fSlow41)));
		float 	fSlow1082 = (fSlow1081 * fSlow40);
		float 	fSlow1083 = (fSlow1082 * fSlow39);
		float 	fSlow1084 = powf((0.010101010101010102f * min((float)99, fSlow1083)),0.69999999999999996f);
		float 	fSlow1085 = powf((0.014705882352941176f * (float((fSlow1083 >= 30.0f)) * min((fSlow1083 + -30.0f), (float)68))),1.8f);
		float 	fSlow1086 = (fSlow1082 * fSlow49);
		int 	iSlow1087 = int((fSlow1086 <= fSlow1083));
		float 	fSlow1088 = powf((0.010101010101010102f * min((float)99, fSlow1086)),0.69999999999999996f);
		float 	fSlow1089 = powf((0.014705882352941176f * (float((fSlow1086 >= 30.0f)) * min((fSlow1086 + -30.0f), (float)68))),1.8f);
		float 	fSlow1090 = (fSlow54 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1078))) + 48.0f));
		float 	fSlow1091 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow56 + fSlow1090))));
		float 	fSlow1092 = max(0.001f, fabsf((((iSlow1087)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1091))):max(0.0080000000000000002f, (318.0f * powf(fSlow1091,12.6f)))) * (((iSlow1087)?fSlow1089:fSlow1088) - ((iSlow1087)?fSlow1085:fSlow1084)))));
		float 	fSlow1093 = (fSlow1082 * fSlow59);
		int 	iSlow1094 = int((fSlow1086 > fSlow1093));
		float 	fSlow1095 = powf((0.010101010101010102f * min((float)99, fSlow1093)),0.69999999999999996f);
		float 	fSlow1096 = powf((0.014705882352941176f * (float((fSlow1093 >= 30.0f)) * min((fSlow1093 + -30.0f), (float)68))),1.8f);
		float 	fSlow1097 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow64 + fSlow1090))));
		float 	fSlow1098 = (fSlow1082 * fSlow66);
		float 	fSlow1099 = powf((0.010101010101010102f * min((float)99, fSlow1098)),0.69999999999999996f);
		float 	fSlow1100 = powf((0.014705882352941176f * (float((fSlow1098 >= 30.0f)) * min((fSlow1098 + -30.0f), (float)68))),1.8f);
		int 	iSlow1101 = int((fSlow1093 > fSlow1098));
		float 	fSlow1102 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow71 + fSlow1090))));
		int 	iSlow1103 = int((fSlow1098 > fSlow1083));
		float 	fSlow1104 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow74 + fSlow1090))));
		float 	fSlow1105 = max(0.001f, fabsf((((iSlow1103)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1104))):max(0.0080000000000000002f, (318.0f * powf(fSlow1104,12.6f)))) * (((iSlow1103)?fSlow1085:fSlow1084) - ((iSlow1103)?fSlow1100:fSlow1099)))));
		float 	fSlow1106 = (fSlow1105 + max(0.001f, fabsf((((iSlow1101)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1102))):max(0.0080000000000000002f, (318.0f * powf(fSlow1102,12.6f)))) * (((iSlow1101)?fSlow1096:fSlow1095) - ((iSlow1101)?fSlow1100:fSlow1099))))));
		float 	fSlow1107 = (fSlow1106 + max(0.001f, fabsf((((iSlow1094)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1097))):max(0.0080000000000000002f, (318.0f * powf(fSlow1097,12.6f)))) * (((iSlow1094)?fSlow1096:fSlow1095) - ((iSlow1094)?fSlow1089:fSlow1088))))));
		float 	fSlow1108 = (0 - (fConst0 * (fSlow1106 - fSlow1107)));
		float 	fSlow1109 = (fConst0 * fSlow1106);
		float 	fSlow1110 = (fConst0 * fSlow1107);
		float 	fSlow1111 = float(fbutton4);
		int 	iSlow1112 = int(((fSlow1111 == 0.0f) > 0));
		float 	fSlow1113 = (0 - (fConst0 * (fSlow1105 - fSlow1106)));
		float 	fSlow1114 = (fConst0 * fSlow1105);
		float 	fSlow1115 = (0 - ((fSlow87 * fSlow1081) * fSlow40));
		float 	fSlow1116 = (fConst1 * (0 - ((fSlow89 * fSlow1081) * fSlow40)));
		int 	iSlow1117 = (fSlow1111 > 0.0f);
		float 	fSlow1118 = float(iSlow1117);
		int 	iSlow1119 = int(iSlow1117);
		float 	fSlow1120 = (fConst0 * fSlow1092);
		int 	iSlow1121 = int((iSlow1117 > 0));
		float 	fSlow1122 = (fSlow98 + ((iSlow97)?fSlow96:(fSlow1077 * fSlow96)));
		float 	fSlow1123 = (fConst1 * fSlow1122);
		float 	fSlow1124 = (fSlow104 + (0.0012626262626262627f * (fSlow1080 * fSlow103)));
		float 	fSlow1125 = (fSlow1124 * fSlow102);
		float 	fSlow1126 = (fSlow1125 * fSlow101);
		float 	fSlow1127 = powf((0.010101010101010102f * min((float)99, fSlow1126)),0.69999999999999996f);
		float 	fSlow1128 = powf((0.014705882352941176f * (float((fSlow1126 >= 30.0f)) * min((fSlow1126 + -30.0f), (float)68))),1.8f);
		float 	fSlow1129 = (fSlow1125 * fSlow110);
		int 	iSlow1130 = int((fSlow1129 <= fSlow1126));
		float 	fSlow1131 = powf((0.010101010101010102f * min((float)99, fSlow1129)),0.69999999999999996f);
		float 	fSlow1132 = powf((0.014705882352941176f * (float((fSlow1129 >= 30.0f)) * min((fSlow1129 + -30.0f), (float)68))),1.8f);
		float 	fSlow1133 = (fSlow115 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1122))) + 48.0f));
		float 	fSlow1134 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow117 + fSlow1133))));
		float 	fSlow1135 = max(0.001f, fabsf((((iSlow1130)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1134))):max(0.0080000000000000002f, (318.0f * powf(fSlow1134,12.6f)))) * (((iSlow1130)?fSlow1132:fSlow1131) - ((iSlow1130)?fSlow1128:fSlow1127)))));
		float 	fSlow1136 = (fSlow1125 * fSlow120);
		int 	iSlow1137 = int((fSlow1129 > fSlow1136));
		float 	fSlow1138 = powf((0.010101010101010102f * min((float)99, fSlow1136)),0.69999999999999996f);
		float 	fSlow1139 = powf((0.014705882352941176f * (float((fSlow1136 >= 30.0f)) * min((fSlow1136 + -30.0f), (float)68))),1.8f);
		float 	fSlow1140 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow125 + fSlow1133))));
		float 	fSlow1141 = (fSlow1125 * fSlow127);
		float 	fSlow1142 = powf((0.010101010101010102f * min((float)99, fSlow1141)),0.69999999999999996f);
		float 	fSlow1143 = powf((0.014705882352941176f * (float((fSlow1141 >= 30.0f)) * min((fSlow1141 + -30.0f), (float)68))),1.8f);
		int 	iSlow1144 = int((fSlow1136 > fSlow1141));
		float 	fSlow1145 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow132 + fSlow1133))));
		int 	iSlow1146 = int((fSlow1141 > fSlow1126));
		float 	fSlow1147 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow135 + fSlow1133))));
		float 	fSlow1148 = max(0.001f, fabsf((((iSlow1146)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1147))):max(0.0080000000000000002f, (318.0f * powf(fSlow1147,12.6f)))) * (((iSlow1146)?fSlow1128:fSlow1127) - ((iSlow1146)?fSlow1143:fSlow1142)))));
		float 	fSlow1149 = (fSlow1148 + max(0.001f, fabsf((((iSlow1144)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1145))):max(0.0080000000000000002f, (318.0f * powf(fSlow1145,12.6f)))) * (((iSlow1144)?fSlow1139:fSlow1138) - ((iSlow1144)?fSlow1143:fSlow1142))))));
		float 	fSlow1150 = (fSlow1149 + max(0.001f, fabsf((((iSlow1137)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1140))):max(0.0080000000000000002f, (318.0f * powf(fSlow1140,12.6f)))) * (((iSlow1137)?fSlow1139:fSlow1138) - ((iSlow1137)?fSlow1132:fSlow1131))))));
		float 	fSlow1151 = (0 - (fConst0 * (fSlow1149 - fSlow1150)));
		float 	fSlow1152 = (fConst0 * fSlow1149);
		float 	fSlow1153 = (fConst0 * fSlow1150);
		float 	fSlow1154 = (0 - (fConst0 * (fSlow1148 - fSlow1149)));
		float 	fSlow1155 = (fConst0 * fSlow1148);
		float 	fSlow1156 = (0 - ((fSlow146 * fSlow1124) * fSlow102));
		float 	fSlow1157 = (fConst1 * (0 - ((fSlow148 * fSlow1124) * fSlow102)));
		float 	fSlow1158 = (fConst0 * fSlow1135);
		float 	fSlow1159 = (fSlow153 + ((iSlow152)?fSlow151:(fSlow1077 * fSlow151)));
		float 	fSlow1160 = (fConst1 * fSlow1159);
		float 	fSlow1161 = (fSlow159 + (0.0012626262626262627f * (fSlow1080 * fSlow158)));
		float 	fSlow1162 = (fSlow1161 * fSlow157);
		float 	fSlow1163 = (fSlow1162 * fSlow156);
		float 	fSlow1164 = powf((0.010101010101010102f * min((float)99, fSlow1163)),0.69999999999999996f);
		float 	fSlow1165 = powf((0.014705882352941176f * (float((fSlow1163 >= 30.0f)) * min((fSlow1163 + -30.0f), (float)68))),1.8f);
		float 	fSlow1166 = (fSlow1162 * fSlow165);
		int 	iSlow1167 = int((fSlow1166 <= fSlow1163));
		float 	fSlow1168 = powf((0.010101010101010102f * min((float)99, fSlow1166)),0.69999999999999996f);
		float 	fSlow1169 = powf((0.014705882352941176f * (float((fSlow1166 >= 30.0f)) * min((fSlow1166 + -30.0f), (float)68))),1.8f);
		float 	fSlow1170 = (fSlow170 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1159))) + 48.0f));
		float 	fSlow1171 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow172 + fSlow1170))));
		float 	fSlow1172 = max(0.001f, fabsf((((iSlow1167)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1171))):max(0.0080000000000000002f, (318.0f * powf(fSlow1171,12.6f)))) * (((iSlow1167)?fSlow1169:fSlow1168) - ((iSlow1167)?fSlow1165:fSlow1164)))));
		float 	fSlow1173 = (fSlow1162 * fSlow175);
		int 	iSlow1174 = int((fSlow1166 > fSlow1173));
		float 	fSlow1175 = powf((0.010101010101010102f * min((float)99, fSlow1173)),0.69999999999999996f);
		float 	fSlow1176 = powf((0.014705882352941176f * (float((fSlow1173 >= 30.0f)) * min((fSlow1173 + -30.0f), (float)68))),1.8f);
		float 	fSlow1177 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow180 + fSlow1170))));
		float 	fSlow1178 = (fSlow1162 * fSlow182);
		float 	fSlow1179 = powf((0.010101010101010102f * min((float)99, fSlow1178)),0.69999999999999996f);
		float 	fSlow1180 = powf((0.014705882352941176f * (float((fSlow1178 >= 30.0f)) * min((fSlow1178 + -30.0f), (float)68))),1.8f);
		int 	iSlow1181 = int((fSlow1173 > fSlow1178));
		float 	fSlow1182 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow187 + fSlow1170))));
		int 	iSlow1183 = int((fSlow1178 > fSlow1163));
		float 	fSlow1184 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow190 + fSlow1170))));
		float 	fSlow1185 = max(0.001f, fabsf((((iSlow1183)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1184))):max(0.0080000000000000002f, (318.0f * powf(fSlow1184,12.6f)))) * (((iSlow1183)?fSlow1165:fSlow1164) - ((iSlow1183)?fSlow1180:fSlow1179)))));
		float 	fSlow1186 = (fSlow1185 + max(0.001f, fabsf((((iSlow1181)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1182))):max(0.0080000000000000002f, (318.0f * powf(fSlow1182,12.6f)))) * (((iSlow1181)?fSlow1176:fSlow1175) - ((iSlow1181)?fSlow1180:fSlow1179))))));
		float 	fSlow1187 = (fSlow1186 + max(0.001f, fabsf((((iSlow1174)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1177))):max(0.0080000000000000002f, (318.0f * powf(fSlow1177,12.6f)))) * (((iSlow1174)?fSlow1176:fSlow1175) - ((iSlow1174)?fSlow1169:fSlow1168))))));
		float 	fSlow1188 = (0 - (fConst0 * (fSlow1186 - fSlow1187)));
		float 	fSlow1189 = (fConst0 * fSlow1186);
		float 	fSlow1190 = (fConst0 * fSlow1187);
		float 	fSlow1191 = (0 - (fConst0 * (fSlow1185 - fSlow1186)));
		float 	fSlow1192 = (fConst0 * fSlow1185);
		float 	fSlow1193 = (0 - ((fSlow201 * fSlow1161) * fSlow157));
		float 	fSlow1194 = (fConst1 * (0 - ((fSlow203 * fSlow1161) * fSlow157)));
		float 	fSlow1195 = (fConst0 * fSlow1172);
		float 	fSlow1196 = (fSlow208 + ((iSlow207)?fSlow206:(fSlow1077 * fSlow206)));
		float 	fSlow1197 = (fConst1 * fSlow1196);
		float 	fSlow1198 = (fSlow214 + (0.0012626262626262627f * (fSlow1080 * fSlow213)));
		float 	fSlow1199 = (fSlow1198 * fSlow212);
		float 	fSlow1200 = (fSlow1199 * fSlow211);
		float 	fSlow1201 = powf((0.010101010101010102f * min((float)99, fSlow1200)),0.69999999999999996f);
		float 	fSlow1202 = powf((0.014705882352941176f * (float((fSlow1200 >= 30.0f)) * min((fSlow1200 + -30.0f), (float)68))),1.8f);
		float 	fSlow1203 = (fSlow1199 * fSlow220);
		int 	iSlow1204 = int((fSlow1203 <= fSlow1200));
		float 	fSlow1205 = powf((0.010101010101010102f * min((float)99, fSlow1203)),0.69999999999999996f);
		float 	fSlow1206 = powf((0.014705882352941176f * (float((fSlow1203 >= 30.0f)) * min((fSlow1203 + -30.0f), (float)68))),1.8f);
		float 	fSlow1207 = (fSlow225 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1196))) + 48.0f));
		float 	fSlow1208 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow227 + fSlow1207))));
		float 	fSlow1209 = max(0.001f, fabsf((((iSlow1204)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1208))):max(0.0080000000000000002f, (318.0f * powf(fSlow1208,12.6f)))) * (((iSlow1204)?fSlow1206:fSlow1205) - ((iSlow1204)?fSlow1202:fSlow1201)))));
		float 	fSlow1210 = (fSlow1199 * fSlow230);
		int 	iSlow1211 = int((fSlow1203 > fSlow1210));
		float 	fSlow1212 = powf((0.010101010101010102f * min((float)99, fSlow1210)),0.69999999999999996f);
		float 	fSlow1213 = powf((0.014705882352941176f * (float((fSlow1210 >= 30.0f)) * min((fSlow1210 + -30.0f), (float)68))),1.8f);
		float 	fSlow1214 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow235 + fSlow1207))));
		float 	fSlow1215 = (fSlow1199 * fSlow237);
		float 	fSlow1216 = powf((0.010101010101010102f * min((float)99, fSlow1215)),0.69999999999999996f);
		float 	fSlow1217 = powf((0.014705882352941176f * (float((fSlow1215 >= 30.0f)) * min((fSlow1215 + -30.0f), (float)68))),1.8f);
		int 	iSlow1218 = int((fSlow1210 > fSlow1215));
		float 	fSlow1219 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow242 + fSlow1207))));
		int 	iSlow1220 = int((fSlow1215 > fSlow1200));
		float 	fSlow1221 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow245 + fSlow1207))));
		float 	fSlow1222 = max(0.001f, fabsf((((iSlow1220)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1221))):max(0.0080000000000000002f, (318.0f * powf(fSlow1221,12.6f)))) * (((iSlow1220)?fSlow1202:fSlow1201) - ((iSlow1220)?fSlow1217:fSlow1216)))));
		float 	fSlow1223 = (fSlow1222 + max(0.001f, fabsf((((iSlow1218)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1219))):max(0.0080000000000000002f, (318.0f * powf(fSlow1219,12.6f)))) * (((iSlow1218)?fSlow1213:fSlow1212) - ((iSlow1218)?fSlow1217:fSlow1216))))));
		float 	fSlow1224 = (fSlow1223 + max(0.001f, fabsf((((iSlow1211)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1214))):max(0.0080000000000000002f, (318.0f * powf(fSlow1214,12.6f)))) * (((iSlow1211)?fSlow1213:fSlow1212) - ((iSlow1211)?fSlow1206:fSlow1205))))));
		float 	fSlow1225 = (0 - (fConst0 * (fSlow1223 - fSlow1224)));
		float 	fSlow1226 = (fConst0 * fSlow1223);
		float 	fSlow1227 = (fConst0 * fSlow1224);
		float 	fSlow1228 = (0 - (fConst0 * (fSlow1222 - fSlow1223)));
		float 	fSlow1229 = (fConst0 * fSlow1222);
		float 	fSlow1230 = (0 - ((fSlow256 * fSlow1198) * fSlow212));
		float 	fSlow1231 = (fConst1 * (0 - ((fSlow258 * fSlow1198) * fSlow212)));
		float 	fSlow1232 = (fConst0 * fSlow1209);
		float 	fSlow1233 = (fSlow263 + ((iSlow262)?fSlow261:(fSlow1077 * fSlow261)));
		float 	fSlow1234 = (fConst1 * fSlow1233);
		float 	fSlow1235 = (fSlow269 + (0.0012626262626262627f * (fSlow1080 * fSlow268)));
		float 	fSlow1236 = (fSlow1235 * fSlow267);
		float 	fSlow1237 = (fSlow1236 * fSlow266);
		float 	fSlow1238 = powf((0.010101010101010102f * min((float)99, fSlow1237)),0.69999999999999996f);
		float 	fSlow1239 = powf((0.014705882352941176f * (float((fSlow1237 >= 30.0f)) * min((fSlow1237 + -30.0f), (float)68))),1.8f);
		float 	fSlow1240 = (fSlow1236 * fSlow275);
		int 	iSlow1241 = int((fSlow1240 <= fSlow1237));
		float 	fSlow1242 = powf((0.010101010101010102f * min((float)99, fSlow1240)),0.69999999999999996f);
		float 	fSlow1243 = powf((0.014705882352941176f * (float((fSlow1240 >= 30.0f)) * min((fSlow1240 + -30.0f), (float)68))),1.8f);
		float 	fSlow1244 = (fSlow280 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1233))) + 48.0f));
		float 	fSlow1245 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow282 + fSlow1244))));
		float 	fSlow1246 = max(0.001f, fabsf((((iSlow1241)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1245))):max(0.0080000000000000002f, (318.0f * powf(fSlow1245,12.6f)))) * (((iSlow1241)?fSlow1243:fSlow1242) - ((iSlow1241)?fSlow1239:fSlow1238)))));
		float 	fSlow1247 = (fSlow1236 * fSlow285);
		int 	iSlow1248 = int((fSlow1240 > fSlow1247));
		float 	fSlow1249 = powf((0.010101010101010102f * min((float)99, fSlow1247)),0.69999999999999996f);
		float 	fSlow1250 = powf((0.014705882352941176f * (float((fSlow1247 >= 30.0f)) * min((fSlow1247 + -30.0f), (float)68))),1.8f);
		float 	fSlow1251 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow290 + fSlow1244))));
		float 	fSlow1252 = (fSlow1236 * fSlow292);
		float 	fSlow1253 = powf((0.010101010101010102f * min((float)99, fSlow1252)),0.69999999999999996f);
		float 	fSlow1254 = powf((0.014705882352941176f * (float((fSlow1252 >= 30.0f)) * min((fSlow1252 + -30.0f), (float)68))),1.8f);
		int 	iSlow1255 = int((fSlow1247 > fSlow1252));
		float 	fSlow1256 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow297 + fSlow1244))));
		int 	iSlow1257 = int((fSlow1252 > fSlow1237));
		float 	fSlow1258 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow300 + fSlow1244))));
		float 	fSlow1259 = max(0.001f, fabsf((((iSlow1257)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1258))):max(0.0080000000000000002f, (318.0f * powf(fSlow1258,12.6f)))) * (((iSlow1257)?fSlow1239:fSlow1238) - ((iSlow1257)?fSlow1254:fSlow1253)))));
		float 	fSlow1260 = (fSlow1259 + max(0.001f, fabsf((((iSlow1255)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1256))):max(0.0080000000000000002f, (318.0f * powf(fSlow1256,12.6f)))) * (((iSlow1255)?fSlow1250:fSlow1249) - ((iSlow1255)?fSlow1254:fSlow1253))))));
		float 	fSlow1261 = (fSlow1260 + max(0.001f, fabsf((((iSlow1248)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1251))):max(0.0080000000000000002f, (318.0f * powf(fSlow1251,12.6f)))) * (((iSlow1248)?fSlow1250:fSlow1249) - ((iSlow1248)?fSlow1243:fSlow1242))))));
		float 	fSlow1262 = (0 - (fConst0 * (fSlow1260 - fSlow1261)));
		float 	fSlow1263 = (fConst0 * fSlow1260);
		float 	fSlow1264 = (fConst0 * fSlow1261);
		float 	fSlow1265 = (0 - (fConst0 * (fSlow1259 - fSlow1260)));
		float 	fSlow1266 = (fConst0 * fSlow1259);
		float 	fSlow1267 = (0 - ((fSlow311 * fSlow1235) * fSlow267));
		float 	fSlow1268 = (fConst1 * (0 - ((fSlow313 * fSlow1235) * fSlow267)));
		float 	fSlow1269 = (fConst0 * fSlow1246);
		float 	fSlow1270 = (fSlow318 + ((iSlow317)?fSlow316:(fSlow1077 * fSlow316)));
		float 	fSlow1271 = (fConst1 * fSlow1270);
		float 	fSlow1272 = (fSlow324 + (0.0012626262626262627f * (fSlow1080 * fSlow323)));
		float 	fSlow1273 = (fSlow1272 * fSlow322);
		float 	fSlow1274 = (fSlow1273 * fSlow321);
		float 	fSlow1275 = powf((0.010101010101010102f * min((float)99, fSlow1274)),0.69999999999999996f);
		float 	fSlow1276 = powf((0.014705882352941176f * (float((fSlow1274 >= 30.0f)) * min((fSlow1274 + -30.0f), (float)68))),1.8f);
		float 	fSlow1277 = (fSlow1273 * fSlow330);
		int 	iSlow1278 = int((fSlow1277 <= fSlow1274));
		float 	fSlow1279 = powf((0.010101010101010102f * min((float)99, fSlow1277)),0.69999999999999996f);
		float 	fSlow1280 = powf((0.014705882352941176f * (float((fSlow1277 >= 30.0f)) * min((fSlow1277 + -30.0f), (float)68))),1.8f);
		float 	fSlow1281 = (fSlow335 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1270))) + 48.0f));
		float 	fSlow1282 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow337 + fSlow1281))));
		float 	fSlow1283 = max(0.001f, fabsf((((iSlow1278)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1282))):max(0.0080000000000000002f, (318.0f * powf(fSlow1282,12.6f)))) * (((iSlow1278)?fSlow1280:fSlow1279) - ((iSlow1278)?fSlow1276:fSlow1275)))));
		float 	fSlow1284 = (fSlow1273 * fSlow340);
		int 	iSlow1285 = int((fSlow1277 > fSlow1284));
		float 	fSlow1286 = powf((0.010101010101010102f * min((float)99, fSlow1284)),0.69999999999999996f);
		float 	fSlow1287 = powf((0.014705882352941176f * (float((fSlow1284 >= 30.0f)) * min((fSlow1284 + -30.0f), (float)68))),1.8f);
		float 	fSlow1288 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow345 + fSlow1281))));
		float 	fSlow1289 = (fSlow1273 * fSlow347);
		float 	fSlow1290 = powf((0.010101010101010102f * min((float)99, fSlow1289)),0.69999999999999996f);
		float 	fSlow1291 = powf((0.014705882352941176f * (float((fSlow1289 >= 30.0f)) * min((fSlow1289 + -30.0f), (float)68))),1.8f);
		int 	iSlow1292 = int((fSlow1284 > fSlow1289));
		float 	fSlow1293 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow352 + fSlow1281))));
		int 	iSlow1294 = int((fSlow1289 > fSlow1274));
		float 	fSlow1295 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow355 + fSlow1281))));
		float 	fSlow1296 = max(0.001f, fabsf((((iSlow1294)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1295))):max(0.0080000000000000002f, (318.0f * powf(fSlow1295,12.6f)))) * (((iSlow1294)?fSlow1276:fSlow1275) - ((iSlow1294)?fSlow1291:fSlow1290)))));
		float 	fSlow1297 = (fSlow1296 + max(0.001f, fabsf((((iSlow1292)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1293))):max(0.0080000000000000002f, (318.0f * powf(fSlow1293,12.6f)))) * (((iSlow1292)?fSlow1287:fSlow1286) - ((iSlow1292)?fSlow1291:fSlow1290))))));
		float 	fSlow1298 = (fSlow1297 + max(0.001f, fabsf((((iSlow1285)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1288))):max(0.0080000000000000002f, (318.0f * powf(fSlow1288,12.6f)))) * (((iSlow1285)?fSlow1287:fSlow1286) - ((iSlow1285)?fSlow1280:fSlow1279))))));
		float 	fSlow1299 = (0 - (fConst0 * (fSlow1297 - fSlow1298)));
		float 	fSlow1300 = (fConst0 * fSlow1297);
		float 	fSlow1301 = (fConst0 * fSlow1298);
		float 	fSlow1302 = (0 - (fConst0 * (fSlow1296 - fSlow1297)));
		float 	fSlow1303 = (fConst0 * fSlow1296);
		float 	fSlow1304 = (0 - ((fSlow366 * fSlow1272) * fSlow322));
		float 	fSlow1305 = (fConst1 * (0 - ((fSlow368 * fSlow1272) * fSlow322)));
		float 	fSlow1306 = (fConst0 * fSlow1283);
		float 	fSlow1307 = (fSlow1118 * fSlow382);
		float 	fSlow1308 = float(fslider100);
		float 	fSlow1309 = (fSlow36 + ((iSlow35)?fSlow33:(fSlow1308 * fSlow33)));
		float 	fSlow1310 = (fConst1 * fSlow1309);
		float 	fSlow1311 = float(fslider101);
		float 	fSlow1312 = (fSlow43 + (0.0012626262626262627f * (fSlow1311 * fSlow41)));
		float 	fSlow1313 = (fSlow1312 * fSlow40);
		float 	fSlow1314 = (fSlow1313 * fSlow39);
		float 	fSlow1315 = powf((0.010101010101010102f * min((float)99, fSlow1314)),0.69999999999999996f);
		float 	fSlow1316 = powf((0.014705882352941176f * (float((fSlow1314 >= 30.0f)) * min((fSlow1314 + -30.0f), (float)68))),1.8f);
		float 	fSlow1317 = (fSlow1313 * fSlow49);
		int 	iSlow1318 = int((fSlow1317 <= fSlow1314));
		float 	fSlow1319 = powf((0.010101010101010102f * min((float)99, fSlow1317)),0.69999999999999996f);
		float 	fSlow1320 = powf((0.014705882352941176f * (float((fSlow1317 >= 30.0f)) * min((fSlow1317 + -30.0f), (float)68))),1.8f);
		float 	fSlow1321 = (fSlow54 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1309))) + 48.0f));
		float 	fSlow1322 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow56 + fSlow1321))));
		float 	fSlow1323 = max(0.001f, fabsf((((iSlow1318)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1322))):max(0.0080000000000000002f, (318.0f * powf(fSlow1322,12.6f)))) * (((iSlow1318)?fSlow1320:fSlow1319) - ((iSlow1318)?fSlow1316:fSlow1315)))));
		float 	fSlow1324 = (fSlow1313 * fSlow59);
		int 	iSlow1325 = int((fSlow1317 > fSlow1324));
		float 	fSlow1326 = powf((0.010101010101010102f * min((float)99, fSlow1324)),0.69999999999999996f);
		float 	fSlow1327 = powf((0.014705882352941176f * (float((fSlow1324 >= 30.0f)) * min((fSlow1324 + -30.0f), (float)68))),1.8f);
		float 	fSlow1328 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow64 + fSlow1321))));
		float 	fSlow1329 = (fSlow1313 * fSlow66);
		float 	fSlow1330 = powf((0.010101010101010102f * min((float)99, fSlow1329)),0.69999999999999996f);
		float 	fSlow1331 = powf((0.014705882352941176f * (float((fSlow1329 >= 30.0f)) * min((fSlow1329 + -30.0f), (float)68))),1.8f);
		int 	iSlow1332 = int((fSlow1324 > fSlow1329));
		float 	fSlow1333 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow71 + fSlow1321))));
		int 	iSlow1334 = int((fSlow1329 > fSlow1314));
		float 	fSlow1335 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow74 + fSlow1321))));
		float 	fSlow1336 = max(0.001f, fabsf((((iSlow1334)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1335))):max(0.0080000000000000002f, (318.0f * powf(fSlow1335,12.6f)))) * (((iSlow1334)?fSlow1316:fSlow1315) - ((iSlow1334)?fSlow1331:fSlow1330)))));
		float 	fSlow1337 = (fSlow1336 + max(0.001f, fabsf((((iSlow1332)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1333))):max(0.0080000000000000002f, (318.0f * powf(fSlow1333,12.6f)))) * (((iSlow1332)?fSlow1327:fSlow1326) - ((iSlow1332)?fSlow1331:fSlow1330))))));
		float 	fSlow1338 = (fSlow1337 + max(0.001f, fabsf((((iSlow1325)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1328))):max(0.0080000000000000002f, (318.0f * powf(fSlow1328,12.6f)))) * (((iSlow1325)?fSlow1327:fSlow1326) - ((iSlow1325)?fSlow1320:fSlow1319))))));
		float 	fSlow1339 = (0 - (fConst0 * (fSlow1337 - fSlow1338)));
		float 	fSlow1340 = (fConst0 * fSlow1337);
		float 	fSlow1341 = (fConst0 * fSlow1338);
		float 	fSlow1342 = float(fbutton5);
		int 	iSlow1343 = int(((fSlow1342 == 0.0f) > 0));
		float 	fSlow1344 = (0 - (fConst0 * (fSlow1336 - fSlow1337)));
		float 	fSlow1345 = (fConst0 * fSlow1336);
		float 	fSlow1346 = (0 - ((fSlow1312 * fSlow87) * fSlow40));
		float 	fSlow1347 = (fConst1 * (0 - ((fSlow1312 * fSlow89) * fSlow40)));
		int 	iSlow1348 = (fSlow1342 > 0.0f);
		float 	fSlow1349 = float(iSlow1348);
		int 	iSlow1350 = int(iSlow1348);
		float 	fSlow1351 = (fConst0 * fSlow1323);
		int 	iSlow1352 = int((iSlow1348 > 0));
		float 	fSlow1353 = (fSlow98 + ((iSlow97)?fSlow96:(fSlow1308 * fSlow96)));
		float 	fSlow1354 = (fConst1 * fSlow1353);
		float 	fSlow1355 = (fSlow104 + (0.0012626262626262627f * (fSlow1311 * fSlow103)));
		float 	fSlow1356 = (fSlow1355 * fSlow102);
		float 	fSlow1357 = (fSlow1356 * fSlow101);
		float 	fSlow1358 = powf((0.010101010101010102f * min((float)99, fSlow1357)),0.69999999999999996f);
		float 	fSlow1359 = powf((0.014705882352941176f * (float((fSlow1357 >= 30.0f)) * min((fSlow1357 + -30.0f), (float)68))),1.8f);
		float 	fSlow1360 = (fSlow1356 * fSlow110);
		int 	iSlow1361 = int((fSlow1360 <= fSlow1357));
		float 	fSlow1362 = powf((0.010101010101010102f * min((float)99, fSlow1360)),0.69999999999999996f);
		float 	fSlow1363 = powf((0.014705882352941176f * (float((fSlow1360 >= 30.0f)) * min((fSlow1360 + -30.0f), (float)68))),1.8f);
		float 	fSlow1364 = (fSlow115 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1353))) + 48.0f));
		float 	fSlow1365 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow117 + fSlow1364))));
		float 	fSlow1366 = max(0.001f, fabsf((((iSlow1361)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1365))):max(0.0080000000000000002f, (318.0f * powf(fSlow1365,12.6f)))) * (((iSlow1361)?fSlow1363:fSlow1362) - ((iSlow1361)?fSlow1359:fSlow1358)))));
		float 	fSlow1367 = (fSlow1356 * fSlow120);
		int 	iSlow1368 = int((fSlow1360 > fSlow1367));
		float 	fSlow1369 = powf((0.010101010101010102f * min((float)99, fSlow1367)),0.69999999999999996f);
		float 	fSlow1370 = powf((0.014705882352941176f * (float((fSlow1367 >= 30.0f)) * min((fSlow1367 + -30.0f), (float)68))),1.8f);
		float 	fSlow1371 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow125 + fSlow1364))));
		float 	fSlow1372 = (fSlow1356 * fSlow127);
		float 	fSlow1373 = powf((0.010101010101010102f * min((float)99, fSlow1372)),0.69999999999999996f);
		float 	fSlow1374 = powf((0.014705882352941176f * (float((fSlow1372 >= 30.0f)) * min((fSlow1372 + -30.0f), (float)68))),1.8f);
		int 	iSlow1375 = int((fSlow1367 > fSlow1372));
		float 	fSlow1376 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow132 + fSlow1364))));
		int 	iSlow1377 = int((fSlow1372 > fSlow1357));
		float 	fSlow1378 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow135 + fSlow1364))));
		float 	fSlow1379 = max(0.001f, fabsf((((iSlow1377)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1378))):max(0.0080000000000000002f, (318.0f * powf(fSlow1378,12.6f)))) * (((iSlow1377)?fSlow1359:fSlow1358) - ((iSlow1377)?fSlow1374:fSlow1373)))));
		float 	fSlow1380 = (fSlow1379 + max(0.001f, fabsf((((iSlow1375)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1376))):max(0.0080000000000000002f, (318.0f * powf(fSlow1376,12.6f)))) * (((iSlow1375)?fSlow1370:fSlow1369) - ((iSlow1375)?fSlow1374:fSlow1373))))));
		float 	fSlow1381 = (fSlow1380 + max(0.001f, fabsf((((iSlow1368)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1371))):max(0.0080000000000000002f, (318.0f * powf(fSlow1371,12.6f)))) * (((iSlow1368)?fSlow1370:fSlow1369) - ((iSlow1368)?fSlow1363:fSlow1362))))));
		float 	fSlow1382 = (0 - (fConst0 * (fSlow1380 - fSlow1381)));
		float 	fSlow1383 = (fConst0 * fSlow1380);
		float 	fSlow1384 = (fConst0 * fSlow1381);
		float 	fSlow1385 = (0 - (fConst0 * (fSlow1379 - fSlow1380)));
		float 	fSlow1386 = (fConst0 * fSlow1379);
		float 	fSlow1387 = (0 - ((fSlow1355 * fSlow146) * fSlow102));
		float 	fSlow1388 = (fConst1 * (0 - ((fSlow1355 * fSlow148) * fSlow102)));
		float 	fSlow1389 = (fConst0 * fSlow1366);
		float 	fSlow1390 = (fSlow153 + ((iSlow152)?fSlow151:(fSlow1308 * fSlow151)));
		float 	fSlow1391 = (fConst1 * fSlow1390);
		float 	fSlow1392 = (fSlow159 + (0.0012626262626262627f * (fSlow1311 * fSlow158)));
		float 	fSlow1393 = (fSlow1392 * fSlow157);
		float 	fSlow1394 = (fSlow1393 * fSlow156);
		float 	fSlow1395 = powf((0.010101010101010102f * min((float)99, fSlow1394)),0.69999999999999996f);
		float 	fSlow1396 = powf((0.014705882352941176f * (float((fSlow1394 >= 30.0f)) * min((fSlow1394 + -30.0f), (float)68))),1.8f);
		float 	fSlow1397 = (fSlow1393 * fSlow165);
		int 	iSlow1398 = int((fSlow1397 <= fSlow1394));
		float 	fSlow1399 = powf((0.010101010101010102f * min((float)99, fSlow1397)),0.69999999999999996f);
		float 	fSlow1400 = powf((0.014705882352941176f * (float((fSlow1397 >= 30.0f)) * min((fSlow1397 + -30.0f), (float)68))),1.8f);
		float 	fSlow1401 = (fSlow170 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1390))) + 48.0f));
		float 	fSlow1402 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow172 + fSlow1401))));
		float 	fSlow1403 = max(0.001f, fabsf((((iSlow1398)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1402))):max(0.0080000000000000002f, (318.0f * powf(fSlow1402,12.6f)))) * (((iSlow1398)?fSlow1400:fSlow1399) - ((iSlow1398)?fSlow1396:fSlow1395)))));
		float 	fSlow1404 = (fSlow1393 * fSlow175);
		int 	iSlow1405 = int((fSlow1397 > fSlow1404));
		float 	fSlow1406 = powf((0.010101010101010102f * min((float)99, fSlow1404)),0.69999999999999996f);
		float 	fSlow1407 = powf((0.014705882352941176f * (float((fSlow1404 >= 30.0f)) * min((fSlow1404 + -30.0f), (float)68))),1.8f);
		float 	fSlow1408 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow180 + fSlow1401))));
		float 	fSlow1409 = (fSlow1393 * fSlow182);
		float 	fSlow1410 = powf((0.010101010101010102f * min((float)99, fSlow1409)),0.69999999999999996f);
		float 	fSlow1411 = powf((0.014705882352941176f * (float((fSlow1409 >= 30.0f)) * min((fSlow1409 + -30.0f), (float)68))),1.8f);
		int 	iSlow1412 = int((fSlow1404 > fSlow1409));
		float 	fSlow1413 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow187 + fSlow1401))));
		int 	iSlow1414 = int((fSlow1409 > fSlow1394));
		float 	fSlow1415 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow190 + fSlow1401))));
		float 	fSlow1416 = max(0.001f, fabsf((((iSlow1414)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1415))):max(0.0080000000000000002f, (318.0f * powf(fSlow1415,12.6f)))) * (((iSlow1414)?fSlow1396:fSlow1395) - ((iSlow1414)?fSlow1411:fSlow1410)))));
		float 	fSlow1417 = (fSlow1416 + max(0.001f, fabsf((((iSlow1412)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1413))):max(0.0080000000000000002f, (318.0f * powf(fSlow1413,12.6f)))) * (((iSlow1412)?fSlow1407:fSlow1406) - ((iSlow1412)?fSlow1411:fSlow1410))))));
		float 	fSlow1418 = (fSlow1417 + max(0.001f, fabsf((((iSlow1405)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1408))):max(0.0080000000000000002f, (318.0f * powf(fSlow1408,12.6f)))) * (((iSlow1405)?fSlow1407:fSlow1406) - ((iSlow1405)?fSlow1400:fSlow1399))))));
		float 	fSlow1419 = (0 - (fConst0 * (fSlow1417 - fSlow1418)));
		float 	fSlow1420 = (fConst0 * fSlow1417);
		float 	fSlow1421 = (fConst0 * fSlow1418);
		float 	fSlow1422 = (0 - (fConst0 * (fSlow1416 - fSlow1417)));
		float 	fSlow1423 = (fConst0 * fSlow1416);
		float 	fSlow1424 = (0 - ((fSlow1392 * fSlow201) * fSlow157));
		float 	fSlow1425 = (fConst1 * (0 - ((fSlow1392 * fSlow203) * fSlow157)));
		float 	fSlow1426 = (fConst0 * fSlow1403);
		float 	fSlow1427 = (fSlow208 + ((iSlow207)?fSlow206:(fSlow1308 * fSlow206)));
		float 	fSlow1428 = (fConst1 * fSlow1427);
		float 	fSlow1429 = (fSlow214 + (0.0012626262626262627f * (fSlow1311 * fSlow213)));
		float 	fSlow1430 = (fSlow1429 * fSlow212);
		float 	fSlow1431 = (fSlow1430 * fSlow211);
		float 	fSlow1432 = powf((0.010101010101010102f * min((float)99, fSlow1431)),0.69999999999999996f);
		float 	fSlow1433 = powf((0.014705882352941176f * (float((fSlow1431 >= 30.0f)) * min((fSlow1431 + -30.0f), (float)68))),1.8f);
		float 	fSlow1434 = (fSlow1430 * fSlow220);
		int 	iSlow1435 = int((fSlow1434 <= fSlow1431));
		float 	fSlow1436 = powf((0.010101010101010102f * min((float)99, fSlow1434)),0.69999999999999996f);
		float 	fSlow1437 = powf((0.014705882352941176f * (float((fSlow1434 >= 30.0f)) * min((fSlow1434 + -30.0f), (float)68))),1.8f);
		float 	fSlow1438 = (fSlow225 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1427))) + 48.0f));
		float 	fSlow1439 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow227 + fSlow1438))));
		float 	fSlow1440 = max(0.001f, fabsf((((iSlow1435)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1439))):max(0.0080000000000000002f, (318.0f * powf(fSlow1439,12.6f)))) * (((iSlow1435)?fSlow1437:fSlow1436) - ((iSlow1435)?fSlow1433:fSlow1432)))));
		float 	fSlow1441 = (fSlow1430 * fSlow230);
		int 	iSlow1442 = int((fSlow1434 > fSlow1441));
		float 	fSlow1443 = powf((0.010101010101010102f * min((float)99, fSlow1441)),0.69999999999999996f);
		float 	fSlow1444 = powf((0.014705882352941176f * (float((fSlow1441 >= 30.0f)) * min((fSlow1441 + -30.0f), (float)68))),1.8f);
		float 	fSlow1445 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow235 + fSlow1438))));
		float 	fSlow1446 = (fSlow1430 * fSlow237);
		float 	fSlow1447 = powf((0.010101010101010102f * min((float)99, fSlow1446)),0.69999999999999996f);
		float 	fSlow1448 = powf((0.014705882352941176f * (float((fSlow1446 >= 30.0f)) * min((fSlow1446 + -30.0f), (float)68))),1.8f);
		int 	iSlow1449 = int((fSlow1441 > fSlow1446));
		float 	fSlow1450 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow242 + fSlow1438))));
		int 	iSlow1451 = int((fSlow1446 > fSlow1431));
		float 	fSlow1452 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow245 + fSlow1438))));
		float 	fSlow1453 = max(0.001f, fabsf((((iSlow1451)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1452))):max(0.0080000000000000002f, (318.0f * powf(fSlow1452,12.6f)))) * (((iSlow1451)?fSlow1433:fSlow1432) - ((iSlow1451)?fSlow1448:fSlow1447)))));
		float 	fSlow1454 = (fSlow1453 + max(0.001f, fabsf((((iSlow1449)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1450))):max(0.0080000000000000002f, (318.0f * powf(fSlow1450,12.6f)))) * (((iSlow1449)?fSlow1444:fSlow1443) - ((iSlow1449)?fSlow1448:fSlow1447))))));
		float 	fSlow1455 = (fSlow1454 + max(0.001f, fabsf((((iSlow1442)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1445))):max(0.0080000000000000002f, (318.0f * powf(fSlow1445,12.6f)))) * (((iSlow1442)?fSlow1444:fSlow1443) - ((iSlow1442)?fSlow1437:fSlow1436))))));
		float 	fSlow1456 = (0 - (fConst0 * (fSlow1454 - fSlow1455)));
		float 	fSlow1457 = (fConst0 * fSlow1454);
		float 	fSlow1458 = (fConst0 * fSlow1455);
		float 	fSlow1459 = (0 - (fConst0 * (fSlow1453 - fSlow1454)));
		float 	fSlow1460 = (fConst0 * fSlow1453);
		float 	fSlow1461 = (0 - ((fSlow1429 * fSlow256) * fSlow212));
		float 	fSlow1462 = (fConst1 * (0 - ((fSlow1429 * fSlow258) * fSlow212)));
		float 	fSlow1463 = (fConst0 * fSlow1440);
		float 	fSlow1464 = (fSlow263 + ((iSlow262)?fSlow261:(fSlow1308 * fSlow261)));
		float 	fSlow1465 = (fConst1 * fSlow1464);
		float 	fSlow1466 = (fSlow269 + (0.0012626262626262627f * (fSlow1311 * fSlow268)));
		float 	fSlow1467 = (fSlow1466 * fSlow267);
		float 	fSlow1468 = (fSlow1467 * fSlow266);
		float 	fSlow1469 = powf((0.010101010101010102f * min((float)99, fSlow1468)),0.69999999999999996f);
		float 	fSlow1470 = powf((0.014705882352941176f * (float((fSlow1468 >= 30.0f)) * min((fSlow1468 + -30.0f), (float)68))),1.8f);
		float 	fSlow1471 = (fSlow1467 * fSlow275);
		int 	iSlow1472 = int((fSlow1471 <= fSlow1468));
		float 	fSlow1473 = powf((0.010101010101010102f * min((float)99, fSlow1471)),0.69999999999999996f);
		float 	fSlow1474 = powf((0.014705882352941176f * (float((fSlow1471 >= 30.0f)) * min((fSlow1471 + -30.0f), (float)68))),1.8f);
		float 	fSlow1475 = (fSlow280 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1464))) + 48.0f));
		float 	fSlow1476 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow282 + fSlow1475))));
		float 	fSlow1477 = max(0.001f, fabsf((((iSlow1472)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1476))):max(0.0080000000000000002f, (318.0f * powf(fSlow1476,12.6f)))) * (((iSlow1472)?fSlow1474:fSlow1473) - ((iSlow1472)?fSlow1470:fSlow1469)))));
		float 	fSlow1478 = (fSlow1467 * fSlow285);
		int 	iSlow1479 = int((fSlow1471 > fSlow1478));
		float 	fSlow1480 = powf((0.010101010101010102f * min((float)99, fSlow1478)),0.69999999999999996f);
		float 	fSlow1481 = powf((0.014705882352941176f * (float((fSlow1478 >= 30.0f)) * min((fSlow1478 + -30.0f), (float)68))),1.8f);
		float 	fSlow1482 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow290 + fSlow1475))));
		float 	fSlow1483 = (fSlow1467 * fSlow292);
		float 	fSlow1484 = powf((0.010101010101010102f * min((float)99, fSlow1483)),0.69999999999999996f);
		float 	fSlow1485 = powf((0.014705882352941176f * (float((fSlow1483 >= 30.0f)) * min((fSlow1483 + -30.0f), (float)68))),1.8f);
		int 	iSlow1486 = int((fSlow1478 > fSlow1483));
		float 	fSlow1487 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow297 + fSlow1475))));
		int 	iSlow1488 = int((fSlow1483 > fSlow1468));
		float 	fSlow1489 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow300 + fSlow1475))));
		float 	fSlow1490 = max(0.001f, fabsf((((iSlow1488)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1489))):max(0.0080000000000000002f, (318.0f * powf(fSlow1489,12.6f)))) * (((iSlow1488)?fSlow1470:fSlow1469) - ((iSlow1488)?fSlow1485:fSlow1484)))));
		float 	fSlow1491 = (fSlow1490 + max(0.001f, fabsf((((iSlow1486)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1487))):max(0.0080000000000000002f, (318.0f * powf(fSlow1487,12.6f)))) * (((iSlow1486)?fSlow1481:fSlow1480) - ((iSlow1486)?fSlow1485:fSlow1484))))));
		float 	fSlow1492 = (fSlow1491 + max(0.001f, fabsf((((iSlow1479)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1482))):max(0.0080000000000000002f, (318.0f * powf(fSlow1482,12.6f)))) * (((iSlow1479)?fSlow1481:fSlow1480) - ((iSlow1479)?fSlow1474:fSlow1473))))));
		float 	fSlow1493 = (0 - (fConst0 * (fSlow1491 - fSlow1492)));
		float 	fSlow1494 = (fConst0 * fSlow1491);
		float 	fSlow1495 = (fConst0 * fSlow1492);
		float 	fSlow1496 = (0 - (fConst0 * (fSlow1490 - fSlow1491)));
		float 	fSlow1497 = (fConst0 * fSlow1490);
		float 	fSlow1498 = (0 - ((fSlow1466 * fSlow311) * fSlow267));
		float 	fSlow1499 = (fConst1 * (0 - ((fSlow1466 * fSlow313) * fSlow267)));
		float 	fSlow1500 = (fConst0 * fSlow1477);
		float 	fSlow1501 = (fSlow318 + ((iSlow317)?fSlow316:(fSlow1308 * fSlow316)));
		float 	fSlow1502 = (fConst1 * fSlow1501);
		float 	fSlow1503 = (fSlow324 + (0.0012626262626262627f * (fSlow1311 * fSlow323)));
		float 	fSlow1504 = (fSlow1503 * fSlow322);
		float 	fSlow1505 = (fSlow1504 * fSlow321);
		float 	fSlow1506 = powf((0.010101010101010102f * min((float)99, fSlow1505)),0.69999999999999996f);
		float 	fSlow1507 = powf((0.014705882352941176f * (float((fSlow1505 >= 30.0f)) * min((fSlow1505 + -30.0f), (float)68))),1.8f);
		float 	fSlow1508 = (fSlow1504 * fSlow330);
		int 	iSlow1509 = int((fSlow1508 <= fSlow1505));
		float 	fSlow1510 = powf((0.010101010101010102f * min((float)99, fSlow1508)),0.69999999999999996f);
		float 	fSlow1511 = powf((0.014705882352941176f * (float((fSlow1508 >= 30.0f)) * min((fSlow1508 + -30.0f), (float)68))),1.8f);
		float 	fSlow1512 = (fSlow335 * ((17.312340490667559f * logf((0.0022727272727272726f * fSlow1501))) + 48.0f));
		float 	fSlow1513 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow337 + fSlow1512))));
		float 	fSlow1514 = max(0.001f, fabsf((((iSlow1509)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1513))):max(0.0080000000000000002f, (318.0f * powf(fSlow1513,12.6f)))) * (((iSlow1509)?fSlow1511:fSlow1510) - ((iSlow1509)?fSlow1507:fSlow1506)))));
		float 	fSlow1515 = (fSlow1504 * fSlow340);
		int 	iSlow1516 = int((fSlow1508 > fSlow1515));
		float 	fSlow1517 = powf((0.010101010101010102f * min((float)99, fSlow1515)),0.69999999999999996f);
		float 	fSlow1518 = powf((0.014705882352941176f * (float((fSlow1515 >= 30.0f)) * min((fSlow1515 + -30.0f), (float)68))),1.8f);
		float 	fSlow1519 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow345 + fSlow1512))));
		float 	fSlow1520 = (fSlow1504 * fSlow347);
		float 	fSlow1521 = powf((0.010101010101010102f * min((float)99, fSlow1520)),0.69999999999999996f);
		float 	fSlow1522 = powf((0.014705882352941176f * (float((fSlow1520 >= 30.0f)) * min((fSlow1520 + -30.0f), (float)68))),1.8f);
		int 	iSlow1523 = int((fSlow1515 > fSlow1520));
		float 	fSlow1524 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow352 + fSlow1512))));
		int 	iSlow1525 = int((fSlow1520 > fSlow1505));
		float 	fSlow1526 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow355 + fSlow1512))));
		float 	fSlow1527 = max(0.001f, fabsf((((iSlow1525)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1526))):max(0.0080000000000000002f, (318.0f * powf(fSlow1526,12.6f)))) * (((iSlow1525)?fSlow1507:fSlow1506) - ((iSlow1525)?fSlow1522:fSlow1521)))));
		float 	fSlow1528 = (fSlow1527 + max(0.001f, fabsf((((iSlow1523)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1524))):max(0.0080000000000000002f, (318.0f * powf(fSlow1524,12.6f)))) * (((iSlow1523)?fSlow1518:fSlow1517) - ((iSlow1523)?fSlow1522:fSlow1521))))));
		float 	fSlow1529 = (fSlow1528 + max(0.001f, fabsf((((iSlow1516)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow1519))):max(0.0080000000000000002f, (318.0f * powf(fSlow1519,12.6f)))) * (((iSlow1516)?fSlow1518:fSlow1517) - ((iSlow1516)?fSlow1511:fSlow1510))))));
		float 	fSlow1530 = (0 - (fConst0 * (fSlow1528 - fSlow1529)));
		float 	fSlow1531 = (fConst0 * fSlow1528);
		float 	fSlow1532 = (fConst0 * fSlow1529);
		float 	fSlow1533 = (0 - (fConst0 * (fSlow1527 - fSlow1528)));
		float 	fSlow1534 = (fConst0 * fSlow1527);
		float 	fSlow1535 = (0 - ((fSlow1503 * fSlow366) * fSlow322));
		float 	fSlow1536 = (fConst1 * (0 - ((fSlow1503 * fSlow368) * fSlow322)));
		float 	fSlow1537 = (fConst0 * fSlow1514);
		float 	fSlow1538 = (fSlow1349 * fSlow382);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm1 = (fRec1[1] + fSlow38);
				fRec1[0] = (fTempPerm1 - floorf(fTempPerm1));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm2 = (65536.0f * fRec1[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec3[0] = ((iSlow83)?0.0f:min(fSlow81, (fRec3[1] + 1.0f)));
				iTempPerm3 = int((fRec3[0] < fSlow80));
				iTempPerm4 = int((fRec3[0] < fSlow86));
				fRec2[0] = ((iSlow93)?(fSlow92 * ((iTempPerm3)?((iTempPerm4)?((int((fRec3[0] < 0.0f)))?fSlow46:((iTempPerm4)?(fSlow46 + (fSlow90 * (fRec3[0] / fSlow76))):fSlow67)):((iTempPerm3)?(fSlow67 + (fSlow88 * ((fRec3[0] - fSlow86) / fSlow85))):fSlow60)):((int((fRec3[0] < fSlow81)))?(fSlow45 * (fSlow59 + (fSlow84 * ((fRec3[0] - fSlow80) / fSlow79)))):fSlow50))):fRec2[1]);
				fRec4[0] = ((iSlow95)?0.0f:min(fSlow94, (fRec4[1] + 1.0f)));
				fTempPerm5 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec4[0] < 0.0f)))?fRec2[0]:((int((fRec4[0] < fSlow94)))?(fRec2[0] + (fConst1 * ((fRec4[0] * (fSlow46 - fRec2[0])) / fSlow58))):fSlow46)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm6 = (fTempPerm5 * ftbl0[(((int(fTempPerm2) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm7 = (fRec5[1] + fSlow100);
				fRec5[0] = (fTempPerm7 - floorf(fTempPerm7));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm8 = (65536.0f * fRec5[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec7[0] = ((iSlow83)?0.0f:min(fSlow142, (fRec7[1] + 1.0f)));
				iTempPerm9 = int((fRec7[0] < fSlow141));
				iTempPerm10 = int((fRec7[0] < fSlow145));
				fRec6[0] = ((iSlow93)?(fSlow92 * ((iTempPerm9)?((iTempPerm10)?((int((fRec7[0] < 0.0f)))?fSlow107:((iTempPerm10)?(fSlow107 + (fSlow149 * (fRec7[0] / fSlow137))):fSlow128)):((iTempPerm9)?(fSlow128 + (fSlow147 * ((fRec7[0] - fSlow145) / fSlow144))):fSlow121)):((int((fRec7[0] < fSlow142)))?(fSlow106 * (fSlow120 + (fSlow143 * ((fRec7[0] - fSlow141) / fSlow140)))):fSlow111))):fRec6[1]);
				fRec8[0] = ((iSlow95)?0.0f:min(fSlow150, (fRec8[1] + 1.0f)));
				fTempPerm11 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec8[0] < 0.0f)))?fRec6[0]:((int((fRec8[0] < fSlow150)))?(fRec6[0] + (fConst1 * ((fRec8[0] * (fSlow107 - fRec6[0])) / fSlow119))):fSlow107)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm12 = (fTempPerm11 * ftbl0[(((int(fTempPerm8) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm13 = (fTempPerm12 + fTempPerm6);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm14 = (fRec9[1] + fSlow155);
				fRec9[0] = (fTempPerm14 - floorf(fTempPerm14));
			}
			if (iSlow30 || iSlow29 || iSlow23 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm15 = (65536.0f * fRec9[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec11[0] = ((iSlow83)?0.0f:min(fSlow197, (fRec11[1] + 1.0f)));
				iTempPerm16 = int((fRec11[0] < fSlow196));
				iTempPerm17 = int((fRec11[0] < fSlow200));
				fRec10[0] = ((iSlow93)?(fSlow92 * ((iTempPerm16)?((iTempPerm17)?((int((fRec11[0] < 0.0f)))?fSlow162:((iTempPerm17)?(fSlow162 + (fSlow204 * (fRec11[0] / fSlow192))):fSlow183)):((iTempPerm16)?(fSlow183 + (fSlow202 * ((fRec11[0] - fSlow200) / fSlow199))):fSlow176)):((int((fRec11[0] < fSlow197)))?(fSlow161 * (fSlow175 + (fSlow198 * ((fRec11[0] - fSlow196) / fSlow195)))):fSlow166))):fRec10[1]);
				fRec12[0] = ((iSlow95)?0.0f:min(fSlow205, (fRec12[1] + 1.0f)));
				fTempPerm18 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec12[0] < 0.0f)))?fRec10[0]:((int((fRec12[0] < fSlow205)))?(fRec10[0] + (fConst1 * ((fRec12[0] * (fSlow162 - fRec10[0])) / fSlow174))):fSlow162)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm19 = (fTempPerm18 * ftbl0[(((int(fTempPerm15) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm20 = (fTempPerm19 + fTempPerm13);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm21 = (fRec13[1] + fSlow210);
				fRec13[0] = (fTempPerm21 - floorf(fTempPerm21));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm22 = (65536.0f * fRec13[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec15[0] = ((iSlow83)?0.0f:min(fSlow252, (fRec15[1] + 1.0f)));
				iTempPerm23 = int((fRec15[0] < fSlow251));
				iTempPerm24 = int((fRec15[0] < fSlow255));
				fRec14[0] = ((iSlow93)?(fSlow92 * ((iTempPerm23)?((iTempPerm24)?((int((fRec15[0] < 0.0f)))?fSlow217:((iTempPerm24)?(fSlow217 + (fSlow259 * (fRec15[0] / fSlow247))):fSlow238)):((iTempPerm23)?(fSlow238 + (fSlow257 * ((fRec15[0] - fSlow255) / fSlow254))):fSlow231)):((int((fRec15[0] < fSlow252)))?(fSlow216 * (fSlow230 + (fSlow253 * ((fRec15[0] - fSlow251) / fSlow250)))):fSlow221))):fRec14[1]);
				fRec16[0] = ((iSlow95)?0.0f:min(fSlow260, (fRec16[1] + 1.0f)));
				fTempPerm25 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec16[0] < 0.0f)))?fRec14[0]:((int((fRec16[0] < fSlow260)))?(fRec14[0] + (fConst1 * ((fRec16[0] * (fSlow217 - fRec14[0])) / fSlow229))):fSlow217)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm26 = (fTempPerm25 * ftbl0[(((int(fTempPerm22) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm27 = (fTempPerm26 + fTempPerm20);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm28 = (fRec17[1] + fSlow265);
				fRec17[0] = (fTempPerm28 - floorf(fTempPerm28));
				fRec19[0] = ((iSlow83)?0.0f:min(fSlow307, (fRec19[1] + 1.0f)));
				iTempPerm29 = int((fRec19[0] < fSlow306));
				iTempPerm30 = int((fRec19[0] < fSlow310));
				fRec18[0] = ((iSlow93)?(fSlow92 * ((iTempPerm29)?((iTempPerm30)?((int((fRec19[0] < 0.0f)))?fSlow272:((iTempPerm30)?(fSlow272 + (fSlow314 * (fRec19[0] / fSlow302))):fSlow293)):((iTempPerm29)?(fSlow293 + (fSlow312 * ((fRec19[0] - fSlow310) / fSlow309))):fSlow286)):((int((fRec19[0] < fSlow307)))?(fSlow271 * (fSlow285 + (fSlow308 * ((fRec19[0] - fSlow306) / fSlow305)))):fSlow276))):fRec18[1]);
				fRec20[0] = ((iSlow95)?0.0f:min(fSlow315, (fRec20[1] + 1.0f)));
				fTempPerm31 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec20[0] < 0.0f)))?fRec18[0]:((int((fRec20[0] < fSlow315)))?(fRec18[0] + (fConst1 * ((fRec20[0] * (fSlow272 - fRec18[0])) / fSlow284))):fSlow272)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm32 = (fTempPerm31 * ftbl0[(((int((65536.0f * fRec17[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm33 = (fRec21[1] + fSlow320);
				fRec21[0] = (fTempPerm33 - floorf(fTempPerm33));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm34 = (65536.0f * fRec21[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec23[0] = ((iSlow83)?0.0f:min(fSlow362, (fRec23[1] + 1.0f)));
				iTempPerm35 = int((fRec23[0] < fSlow361));
				iTempPerm36 = int((fRec23[0] < fSlow365));
				fRec22[0] = ((iSlow93)?(fSlow92 * ((iTempPerm35)?((iTempPerm36)?((int((fRec23[0] < 0.0f)))?fSlow327:((iTempPerm36)?(fSlow327 + (fSlow369 * (fRec23[0] / fSlow357))):fSlow348)):((iTempPerm35)?(fSlow348 + (fSlow367 * ((fRec23[0] - fSlow365) / fSlow364))):fSlow341)):((int((fRec23[0] < fSlow362)))?(fSlow326 * (fSlow340 + (fSlow363 * ((fRec23[0] - fSlow361) / fSlow360)))):fSlow331))):fRec22[1]);
				fRec24[0] = ((iSlow95)?0.0f:min(fSlow370, (fRec24[1] + 1.0f)));
				fTempPerm37 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec24[0] < 0.0f)))?fRec22[0]:((int((fRec24[0] < fSlow370)))?(fRec22[0] + (fConst1 * ((fRec24[0] * (fSlow327 - fRec22[0])) / fSlow339))):fSlow327)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm38 = (fTempPerm37 * ftbl0[(((int(fTempPerm34) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm39 = (2.0879500000000002f * (fTempPerm38 + (fTempPerm32 + fTempPerm27)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec25[0] = (fTempPerm37 * ftbl0[(((int((65536.0f * (fRec21[0] + (fSlow371 * fRec25[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm40 = (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec17[0] + fRec25[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm41 = (2.0879500000000002f * (fTempPerm40 + fTempPerm27));
			}
			if (iSlow5 || iSlow3) {
				fRec26[0] = (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec17[0] + (fSlow371 * fRec26[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm42 = (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec26[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm43 = (2.0879500000000002f * (fTempPerm38 + (fTempPerm13 + fTempPerm42)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm44 = (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm26))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm45 = (2.0879500000000002f * (fTempPerm40 + (fTempPerm44 + fTempPerm13)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm46 = (fTempPerm5 * ftbl0[(((int((65536.0f * (fRec1[0] + fTempPerm12))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm47 = (2.0879500000000002f * (fTempPerm38 + (fTempPerm46 + fTempPerm42)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec27[0] = (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + (fSlow371 * fRec27[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm48 = (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec5[0] + fRec27[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm49 = (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + (fTempPerm38 + fTempPerm32)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm50 = (2.0879500000000002f * (fTempPerm49 + (fTempPerm48 + fTempPerm6)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm51 = (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec5[0] + fTempPerm19))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm52 = (fTempPerm51 + fTempPerm6);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm53 = (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + (fRec25[0] + fTempPerm32)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm54 = (2.0879500000000002f * (fTempPerm53 + fTempPerm52));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm55 = (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec25[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm56 = (2.0879500000000002f * (fTempPerm40 + (fTempPerm55 + fTempPerm20)));
			}
			if (iSlow9) {
				fRec28[0] = (fTempPerm37 * ftbl0[(((int((fTempPerm34 + (fSlow372 * fRec28[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm57 = (2.0879500000000002f * (((fTempPerm13 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + fRec28[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec28[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec17[0] + fRec28[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm58 = (2.0879500000000002f * (fTempPerm40 + (fTempPerm52 + fTempPerm55)));
			}
			if (iSlow28 || iSlow11) {
				fRec29[0] = (fTempPerm37 * ftbl0[(((int((fTempPerm34 + (fSlow373 * fRec29[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm59 = (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec17[0] + fRec29[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm60 = ((fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + fRec29[0]))) % 65536) + 65536) % 65536)]) + (2.0879500000000002f * (fTempPerm59 + ((fTempPerm5 * ftbl0[(((int((fTempPerm2 + (136835.89120000001f * fTempPerm12))) % 65536) + 65536) % 65536)]) + (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec29[0]))) % 65536) + 65536) % 65536)])))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm61 = ((fTempPerm5 * ftbl0[(((int((65536.0f * (fRec1[0] + fRec27[0]))) % 65536) + 65536) % 65536)]) + fTempPerm48);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm62 = (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec17[0] + fTempPerm38))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm63 = (2.0879500000000002f * (fTempPerm62 + (fTempPerm61 + (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm38))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm64 = (2.0879500000000002f * (fTempPerm49 + fTempPerm61));
			}
			if (iSlow14) {
				fRec30[0] = (fTempPerm37 * ftbl0[(((int((fTempPerm34 + (fSlow374 * fRec30[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm65 = (fTempPerm5 * ftbl0[(((int((65536.0f * (fRec1[0] + fTempPerm51))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm66 = (2.0879500000000002f * ((fTempPerm65 + (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec30[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec17[0] + fRec30[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm67 = (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm62))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm68 = (2.0879500000000002f * (fTempPerm5 * ftbl0[(((int((65536.0f * (fRec1[0] + (fTempPerm67 + (fRec27[0] + fTempPerm12))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec31[0] = (fTempPerm11 * ftbl0[(((int((fTempPerm8 + (fSlow375 * fRec31[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm69 = (2.0879500000000002f * (fTempPerm5 * ftbl0[(((int((65536.0f * (fRec1[0] + (fTempPerm44 + (fRec31[0] + fTempPerm62))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm70 = (2.0879500000000002f * (fTempPerm5 * ftbl0[(((int((65536.0f * (fRec1[0] + (fTempPerm44 + (fTempPerm12 + fTempPerm40))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec32[0] = (fTempPerm11 * ftbl0[(((int((fTempPerm8 + (fSlow374 * fRec32[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm71 = (fTempPerm5 * ftbl0[(((int((65536.0f * (fRec1[0] + fRec32[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm72 = (2.0879500000000002f * (fTempPerm71 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm49))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm73 = (2.0879500000000002f * (fTempPerm46 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm53))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm74 = (2.0879500000000002f * (fTempPerm46 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + (fTempPerm32 + (fRec25[0] + fTempPerm26))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec33[0] = (fTempPerm11 * ftbl0[(((int((fTempPerm8 + (fSlow376 * fRec33[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm75 = (fTempPerm5 * ftbl0[(((int((65536.0f * (fRec1[0] + fRec33[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm76 = (2.0879500000000002f * (fTempPerm75 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + (fTempPerm32 + (fTempPerm38 + fTempPerm26))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec34[0] = (fTempPerm37 * ftbl0[(((int((fTempPerm34 + (fSlow376 * fRec34[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm77 = (2.0879500000000002f * (fTempPerm65 + (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + (fRec34[0] + fTempPerm32)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec35[0] = (fTempPerm18 * ftbl0[(((int((fTempPerm15 + (fSlow376 * fRec35[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm78 = (2.0879500000000002f * (fTempPerm49 + (fTempPerm5 * ftbl0[(((int((65536.0f * (fRec1[0] + (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec5[0] + fRec35[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm79 = (2.0879500000000002f * (fTempPerm71 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + (fTempPerm62 + fTempPerm26)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec36[0] = (fTempPerm25 * ftbl0[(((int((fTempPerm22 + (fSlow373 * fRec36[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm80 = (2.0879500000000002f * (fTempPerm46 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + (fRec36[0] + fTempPerm62)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm81 = (2.0879500000000002f * (fTempPerm46 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + (fTempPerm40 + fTempPerm26)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm82 = (fTempPerm46 + fTempPerm44);
			}
			if (iSlow27) {
				fRec37[0] = (2.0879500000000002f * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec17[0] + (fTempPerm37 * ftbl0[(((int((65536.0f * (fRec21[0] + (fSlow371 * fRec37[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm83 = (fRec37[0] + (2.0879500000000002f * fTempPerm82));
			}
			if (iSlow28) {
				fTempPerm84 = (2.0879500000000002f * (fTempPerm82 + fTempPerm59));
			}
			if (iSlow29) {
				fRec38[0] = (2.0879500000000002f * (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec17[0] + (fTempPerm37 * ftbl0[(((int((65536.0f * (fRec21[0] + (fSlow371 * fRec38[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm85 = (fRec38[0] + (2.0879500000000002f * fTempPerm65));
			}
			if (iSlow30) {
				fTempPerm86 = (2.0879500000000002f * (fTempPerm65 + (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm40))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm87 = (2.0879500000000002f * (fTempPerm75 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm67))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm88 = (2.0879500000000002f * (fTempPerm46 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec9[0] + (fTempPerm25 * ftbl0[(((int((65536.0f * (fRec13[0] + (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec17[0] + fRec34[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec40[0] = (iSlow91 * (iRec40[1] + 1));
			iTempPerm89 = int((iRec40[0] < iSlow381));
			fTempPerm90 = expf((0 - (fConst2 / ((iSlow93)?((iTempPerm89)?fSlow380:fSlow378):fSlow377))));
			fRec39[0] = ((fRec39[1] * fTempPerm90) + (((iSlow93)?((iTempPerm89)?1.5873015873015872f:fSlow383):0.0f) * (1.0f - fTempPerm90)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm91 = (fRec41[1] + fSlow386);
				fRec41[0] = (fTempPerm91 - floorf(fTempPerm91));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm92 = (65536.0f * fRec41[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec43[0] = ((iSlow419)?0.0f:min(fSlow417, (fRec43[1] + 1.0f)));
				iTempPerm93 = int((fRec43[0] < fSlow416));
				iTempPerm94 = int((fRec43[0] < fSlow421));
				fRec42[0] = ((iSlow426)?(fSlow425 * ((iTempPerm93)?((iTempPerm94)?((int((fRec43[0] < 0.0f)))?fSlow390:((iTempPerm94)?(fSlow390 + (fSlow423 * (fRec43[0] / fSlow412))):fSlow405)):((iTempPerm93)?(fSlow405 + (fSlow422 * ((fRec43[0] - fSlow421) / fSlow420))):fSlow400)):((int((fRec43[0] < fSlow417)))?(fSlow389 * (fSlow59 + (fSlow84 * ((fRec43[0] - fSlow416) / fSlow415)))):fSlow393))):fRec42[1]);
				fRec44[0] = ((iSlow428)?0.0f:min(fSlow427, (fRec44[1] + 1.0f)));
				fTempPerm95 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec44[0] < 0.0f)))?fRec42[0]:((int((fRec44[0] < fSlow427)))?(fRec42[0] + (fConst1 * ((fRec44[0] * (fSlow390 - fRec42[0])) / fSlow399))):fSlow390)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm96 = (fTempPerm95 * ftbl0[(((int(fTempPerm92) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm97 = (fRec45[1] + fSlow430);
				fRec45[0] = (fTempPerm97 - floorf(fTempPerm97));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm98 = (65536.0f * fRec45[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec47[0] = ((iSlow419)?0.0f:min(fSlow460, (fRec47[1] + 1.0f)));
				iTempPerm99 = int((fRec47[0] < fSlow459));
				iTempPerm100 = int((fRec47[0] < fSlow462));
				fRec46[0] = ((iSlow426)?(fSlow425 * ((iTempPerm99)?((iTempPerm100)?((int((fRec47[0] < 0.0f)))?fSlow433:((iTempPerm100)?(fSlow433 + (fSlow464 * (fRec47[0] / fSlow455))):fSlow448)):((iTempPerm99)?(fSlow448 + (fSlow463 * ((fRec47[0] - fSlow462) / fSlow461))):fSlow443)):((int((fRec47[0] < fSlow460)))?(fSlow432 * (fSlow120 + (fSlow143 * ((fRec47[0] - fSlow459) / fSlow458)))):fSlow436))):fRec46[1]);
				fRec48[0] = ((iSlow428)?0.0f:min(fSlow465, (fRec48[1] + 1.0f)));
				fTempPerm101 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec48[0] < 0.0f)))?fRec46[0]:((int((fRec48[0] < fSlow465)))?(fRec46[0] + (fConst1 * ((fRec48[0] * (fSlow433 - fRec46[0])) / fSlow442))):fSlow433)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm102 = (fTempPerm101 * ftbl0[(((int(fTempPerm98) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm103 = (fTempPerm102 + fTempPerm96);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm104 = (fRec49[1] + fSlow467);
				fRec49[0] = (fTempPerm104 - floorf(fTempPerm104));
			}
			if (iSlow30 || iSlow29 || iSlow23 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm105 = (65536.0f * fRec49[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec51[0] = ((iSlow419)?0.0f:min(fSlow497, (fRec51[1] + 1.0f)));
				iTempPerm106 = int((fRec51[0] < fSlow496));
				iTempPerm107 = int((fRec51[0] < fSlow499));
				fRec50[0] = ((iSlow426)?(fSlow425 * ((iTempPerm106)?((iTempPerm107)?((int((fRec51[0] < 0.0f)))?fSlow470:((iTempPerm107)?(fSlow470 + (fSlow501 * (fRec51[0] / fSlow492))):fSlow485)):((iTempPerm106)?(fSlow485 + (fSlow500 * ((fRec51[0] - fSlow499) / fSlow498))):fSlow480)):((int((fRec51[0] < fSlow497)))?(fSlow469 * (fSlow175 + (fSlow198 * ((fRec51[0] - fSlow496) / fSlow495)))):fSlow473))):fRec50[1]);
				fRec52[0] = ((iSlow428)?0.0f:min(fSlow502, (fRec52[1] + 1.0f)));
				fTempPerm108 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec52[0] < 0.0f)))?fRec50[0]:((int((fRec52[0] < fSlow502)))?(fRec50[0] + (fConst1 * ((fRec52[0] * (fSlow470 - fRec50[0])) / fSlow479))):fSlow470)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm109 = (fTempPerm108 * ftbl0[(((int(fTempPerm105) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm110 = (fTempPerm109 + fTempPerm103);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm111 = (fRec53[1] + fSlow504);
				fRec53[0] = (fTempPerm111 - floorf(fTempPerm111));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm112 = (65536.0f * fRec53[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec55[0] = ((iSlow419)?0.0f:min(fSlow534, (fRec55[1] + 1.0f)));
				iTempPerm113 = int((fRec55[0] < fSlow533));
				iTempPerm114 = int((fRec55[0] < fSlow536));
				fRec54[0] = ((iSlow426)?(fSlow425 * ((iTempPerm113)?((iTempPerm114)?((int((fRec55[0] < 0.0f)))?fSlow507:((iTempPerm114)?(fSlow507 + (fSlow538 * (fRec55[0] / fSlow529))):fSlow522)):((iTempPerm113)?(fSlow522 + (fSlow537 * ((fRec55[0] - fSlow536) / fSlow535))):fSlow517)):((int((fRec55[0] < fSlow534)))?(fSlow506 * (fSlow230 + (fSlow253 * ((fRec55[0] - fSlow533) / fSlow532)))):fSlow510))):fRec54[1]);
				fRec56[0] = ((iSlow428)?0.0f:min(fSlow539, (fRec56[1] + 1.0f)));
				fTempPerm115 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec56[0] < 0.0f)))?fRec54[0]:((int((fRec56[0] < fSlow539)))?(fRec54[0] + (fConst1 * ((fRec56[0] * (fSlow507 - fRec54[0])) / fSlow516))):fSlow507)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm116 = (fTempPerm115 * ftbl0[(((int(fTempPerm112) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm117 = (fTempPerm116 + fTempPerm110);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm118 = (fRec57[1] + fSlow541);
				fRec57[0] = (fTempPerm118 - floorf(fTempPerm118));
				fRec59[0] = ((iSlow419)?0.0f:min(fSlow571, (fRec59[1] + 1.0f)));
				iTempPerm119 = int((fRec59[0] < fSlow570));
				iTempPerm120 = int((fRec59[0] < fSlow573));
				fRec58[0] = ((iSlow426)?(fSlow425 * ((iTempPerm119)?((iTempPerm120)?((int((fRec59[0] < 0.0f)))?fSlow544:((iTempPerm120)?(fSlow544 + (fSlow575 * (fRec59[0] / fSlow566))):fSlow559)):((iTempPerm119)?(fSlow559 + (fSlow574 * ((fRec59[0] - fSlow573) / fSlow572))):fSlow554)):((int((fRec59[0] < fSlow571)))?(fSlow543 * (fSlow285 + (fSlow308 * ((fRec59[0] - fSlow570) / fSlow569)))):fSlow547))):fRec58[1]);
				fRec60[0] = ((iSlow428)?0.0f:min(fSlow576, (fRec60[1] + 1.0f)));
				fTempPerm121 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec60[0] < 0.0f)))?fRec58[0]:((int((fRec60[0] < fSlow576)))?(fRec58[0] + (fConst1 * ((fRec60[0] * (fSlow544 - fRec58[0])) / fSlow553))):fSlow544)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm122 = (fTempPerm121 * ftbl0[(((int((65536.0f * fRec57[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm123 = (fRec61[1] + fSlow578);
				fRec61[0] = (fTempPerm123 - floorf(fTempPerm123));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm124 = (65536.0f * fRec61[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec63[0] = ((iSlow419)?0.0f:min(fSlow608, (fRec63[1] + 1.0f)));
				iTempPerm125 = int((fRec63[0] < fSlow607));
				iTempPerm126 = int((fRec63[0] < fSlow610));
				fRec62[0] = ((iSlow426)?(fSlow425 * ((iTempPerm125)?((iTempPerm126)?((int((fRec63[0] < 0.0f)))?fSlow581:((iTempPerm126)?(fSlow581 + (fSlow612 * (fRec63[0] / fSlow603))):fSlow596)):((iTempPerm125)?(fSlow596 + (fSlow611 * ((fRec63[0] - fSlow610) / fSlow609))):fSlow591)):((int((fRec63[0] < fSlow608)))?(fSlow580 * (fSlow340 + (fSlow363 * ((fRec63[0] - fSlow607) / fSlow606)))):fSlow584))):fRec62[1]);
				fRec64[0] = ((iSlow428)?0.0f:min(fSlow613, (fRec64[1] + 1.0f)));
				fTempPerm127 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec64[0] < 0.0f)))?fRec62[0]:((int((fRec64[0] < fSlow613)))?(fRec62[0] + (fConst1 * ((fRec64[0] * (fSlow581 - fRec62[0])) / fSlow590))):fSlow581)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm128 = (fTempPerm127 * ftbl0[(((int(fTempPerm124) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm129 = (2.0879500000000002f * (fTempPerm128 + (fTempPerm122 + fTempPerm117)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec65[0] = (fTempPerm127 * ftbl0[(((int((65536.0f * (fRec61[0] + (fSlow371 * fRec65[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm130 = (fTempPerm121 * ftbl0[(((int((65536.0f * (fRec57[0] + fRec65[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm131 = (2.0879500000000002f * (fTempPerm130 + fTempPerm117));
			}
			if (iSlow5 || iSlow3) {
				fRec66[0] = (fTempPerm121 * ftbl0[(((int((65536.0f * (fRec57[0] + (fSlow371 * fRec66[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm132 = (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + fRec66[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm133 = (2.0879500000000002f * (fTempPerm128 + (fTempPerm103 + fTempPerm132)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm134 = (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + fTempPerm116))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm135 = (2.0879500000000002f * (fTempPerm130 + (fTempPerm134 + fTempPerm103)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm136 = (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec41[0] + fTempPerm102))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm137 = (2.0879500000000002f * (fTempPerm128 + (fTempPerm136 + fTempPerm132)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec67[0] = (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + (fSlow371 * fRec67[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm138 = (fTempPerm101 * ftbl0[(((int((65536.0f * (fRec45[0] + fRec67[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm139 = (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + (fTempPerm128 + fTempPerm122)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm140 = (2.0879500000000002f * (fTempPerm139 + (fTempPerm138 + fTempPerm96)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm141 = (fTempPerm101 * ftbl0[(((int((65536.0f * (fRec45[0] + fTempPerm109))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm142 = (fTempPerm141 + fTempPerm96);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm143 = (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + (fRec65[0] + fTempPerm122)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm144 = (2.0879500000000002f * (fTempPerm143 + fTempPerm142));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm145 = (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + fRec65[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm146 = (2.0879500000000002f * (fTempPerm130 + (fTempPerm145 + fTempPerm110)));
			}
			if (iSlow9) {
				fRec68[0] = (fTempPerm127 * ftbl0[(((int((fTempPerm124 + (fSlow372 * fRec68[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm147 = (2.0879500000000002f * (((fTempPerm103 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + fRec68[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + fRec68[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm121 * ftbl0[(((int((65536.0f * (fRec57[0] + fRec68[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm148 = (2.0879500000000002f * (fTempPerm130 + (fTempPerm142 + fTempPerm145)));
			}
			if (iSlow28 || iSlow11) {
				fRec69[0] = (fTempPerm127 * ftbl0[(((int((fTempPerm124 + (fSlow373 * fRec69[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm149 = (fTempPerm121 * ftbl0[(((int((65536.0f * (fRec57[0] + fRec69[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm150 = ((fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + fRec69[0]))) % 65536) + 65536) % 65536)]) + (2.0879500000000002f * (fTempPerm149 + ((fTempPerm95 * ftbl0[(((int((fTempPerm92 + (136835.89120000001f * fTempPerm102))) % 65536) + 65536) % 65536)]) + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + fRec69[0]))) % 65536) + 65536) % 65536)])))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm151 = ((fTempPerm95 * ftbl0[(((int((65536.0f * (fRec41[0] + fRec67[0]))) % 65536) + 65536) % 65536)]) + fTempPerm138);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm152 = (fTempPerm121 * ftbl0[(((int((65536.0f * (fRec57[0] + fTempPerm128))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm153 = (2.0879500000000002f * (fTempPerm152 + (fTempPerm151 + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + fTempPerm128))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm154 = (2.0879500000000002f * (fTempPerm139 + fTempPerm151));
			}
			if (iSlow14) {
				fRec70[0] = (fTempPerm127 * ftbl0[(((int((fTempPerm124 + (fSlow374 * fRec70[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm155 = (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec41[0] + fTempPerm141))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm156 = (2.0879500000000002f * ((fTempPerm155 + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + fRec70[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm121 * ftbl0[(((int((65536.0f * (fRec57[0] + fRec70[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm157 = (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + fTempPerm152))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm158 = (2.0879500000000002f * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec41[0] + (fTempPerm157 + (fRec67[0] + fTempPerm102))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec71[0] = (fTempPerm101 * ftbl0[(((int((fTempPerm98 + (fSlow375 * fRec71[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm159 = (2.0879500000000002f * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec41[0] + (fTempPerm134 + (fRec71[0] + fTempPerm152))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm160 = (2.0879500000000002f * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec41[0] + (fTempPerm134 + (fTempPerm102 + fTempPerm130))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec72[0] = (fTempPerm101 * ftbl0[(((int((fTempPerm98 + (fSlow374 * fRec72[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm161 = (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec41[0] + fRec72[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm162 = (2.0879500000000002f * (fTempPerm161 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + fTempPerm139))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm163 = (2.0879500000000002f * (fTempPerm136 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + fTempPerm143))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm164 = (2.0879500000000002f * (fTempPerm136 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + (fTempPerm122 + (fRec65[0] + fTempPerm116))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec73[0] = (fTempPerm101 * ftbl0[(((int((fTempPerm98 + (fSlow376 * fRec73[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm165 = (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec41[0] + fRec73[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm166 = (2.0879500000000002f * (fTempPerm165 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + (fTempPerm122 + (fTempPerm128 + fTempPerm116))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec74[0] = (fTempPerm127 * ftbl0[(((int((fTempPerm124 + (fSlow376 * fRec74[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm167 = (2.0879500000000002f * (fTempPerm155 + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + (fRec74[0] + fTempPerm122)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec75[0] = (fTempPerm108 * ftbl0[(((int((fTempPerm105 + (fSlow376 * fRec75[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm168 = (2.0879500000000002f * (fTempPerm139 + (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec41[0] + (fTempPerm101 * ftbl0[(((int((65536.0f * (fRec45[0] + fRec75[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm169 = (2.0879500000000002f * (fTempPerm161 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + (fTempPerm152 + fTempPerm116)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec76[0] = (fTempPerm115 * ftbl0[(((int((fTempPerm112 + (fSlow373 * fRec76[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm170 = (2.0879500000000002f * (fTempPerm136 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + (fRec76[0] + fTempPerm152)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm171 = (2.0879500000000002f * (fTempPerm136 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + (fTempPerm130 + fTempPerm116)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm172 = (fTempPerm136 + fTempPerm134);
			}
			if (iSlow27) {
				fRec77[0] = (2.0879500000000002f * (fTempPerm121 * ftbl0[(((int((65536.0f * (fRec57[0] + (fTempPerm127 * ftbl0[(((int((65536.0f * (fRec61[0] + (fSlow371 * fRec77[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm173 = (fRec77[0] + (2.0879500000000002f * fTempPerm172));
			}
			if (iSlow28) {
				fTempPerm174 = (2.0879500000000002f * (fTempPerm172 + fTempPerm149));
			}
			if (iSlow29) {
				fRec78[0] = (2.0879500000000002f * (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + (fTempPerm121 * ftbl0[(((int((65536.0f * (fRec57[0] + (fTempPerm127 * ftbl0[(((int((65536.0f * (fRec61[0] + (fSlow371 * fRec78[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm175 = (fRec78[0] + (2.0879500000000002f * fTempPerm155));
			}
			if (iSlow30) {
				fTempPerm176 = (2.0879500000000002f * (fTempPerm155 + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + fTempPerm130))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm177 = (2.0879500000000002f * (fTempPerm165 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + fTempPerm157))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm178 = (2.0879500000000002f * (fTempPerm136 + (fTempPerm108 * ftbl0[(((int((65536.0f * (fRec49[0] + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec53[0] + (fTempPerm121 * ftbl0[(((int((65536.0f * (fRec57[0] + fRec74[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec80[0] = (iSlow424 * (iRec80[1] + 1));
			iTempPerm179 = int((iRec80[0] < iSlow381));
			fTempPerm180 = expf((0 - (fConst2 / ((iSlow426)?((iTempPerm179)?fSlow380:fSlow378):fSlow377))));
			fRec79[0] = ((fRec79[1] * fTempPerm180) + (((iSlow426)?((iTempPerm179)?1.5873015873015872f:fSlow614):0.0f) * (1.0f - fTempPerm180)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm181 = (fRec81[1] + fSlow617);
				fRec81[0] = (fTempPerm181 - floorf(fTempPerm181));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm182 = (65536.0f * fRec81[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec83[0] = ((iSlow650)?0.0f:min(fSlow648, (fRec83[1] + 1.0f)));
				iTempPerm183 = int((fRec83[0] < fSlow647));
				iTempPerm184 = int((fRec83[0] < fSlow652));
				fRec82[0] = ((iSlow657)?(fSlow656 * ((iTempPerm183)?((iTempPerm184)?((int((fRec83[0] < 0.0f)))?fSlow621:((iTempPerm184)?(fSlow621 + (fSlow654 * (fRec83[0] / fSlow643))):fSlow636)):((iTempPerm183)?(fSlow636 + (fSlow653 * ((fRec83[0] - fSlow652) / fSlow651))):fSlow631)):((int((fRec83[0] < fSlow648)))?(fSlow620 * (fSlow59 + (fSlow84 * ((fRec83[0] - fSlow647) / fSlow646)))):fSlow624))):fRec82[1]);
				fRec84[0] = ((iSlow659)?0.0f:min(fSlow658, (fRec84[1] + 1.0f)));
				fTempPerm185 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec84[0] < 0.0f)))?fRec82[0]:((int((fRec84[0] < fSlow658)))?(fRec82[0] + (fConst1 * ((fRec84[0] * (fSlow621 - fRec82[0])) / fSlow630))):fSlow621)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm186 = (fTempPerm185 * ftbl0[(((int(fTempPerm182) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm187 = (fRec85[1] + fSlow661);
				fRec85[0] = (fTempPerm187 - floorf(fTempPerm187));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm188 = (65536.0f * fRec85[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec87[0] = ((iSlow650)?0.0f:min(fSlow691, (fRec87[1] + 1.0f)));
				iTempPerm189 = int((fRec87[0] < fSlow690));
				iTempPerm190 = int((fRec87[0] < fSlow693));
				fRec86[0] = ((iSlow657)?(fSlow656 * ((iTempPerm189)?((iTempPerm190)?((int((fRec87[0] < 0.0f)))?fSlow664:((iTempPerm190)?(fSlow664 + (fSlow695 * (fRec87[0] / fSlow686))):fSlow679)):((iTempPerm189)?(fSlow679 + (fSlow694 * ((fRec87[0] - fSlow693) / fSlow692))):fSlow674)):((int((fRec87[0] < fSlow691)))?(fSlow663 * (fSlow120 + (fSlow143 * ((fRec87[0] - fSlow690) / fSlow689)))):fSlow667))):fRec86[1]);
				fRec88[0] = ((iSlow659)?0.0f:min(fSlow696, (fRec88[1] + 1.0f)));
				fTempPerm191 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec88[0] < 0.0f)))?fRec86[0]:((int((fRec88[0] < fSlow696)))?(fRec86[0] + (fConst1 * ((fRec88[0] * (fSlow664 - fRec86[0])) / fSlow673))):fSlow664)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm192 = (fTempPerm191 * ftbl0[(((int(fTempPerm188) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm193 = (fTempPerm192 + fTempPerm186);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm194 = (fRec89[1] + fSlow698);
				fRec89[0] = (fTempPerm194 - floorf(fTempPerm194));
			}
			if (iSlow30 || iSlow29 || iSlow23 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm195 = (65536.0f * fRec89[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec91[0] = ((iSlow650)?0.0f:min(fSlow728, (fRec91[1] + 1.0f)));
				iTempPerm196 = int((fRec91[0] < fSlow727));
				iTempPerm197 = int((fRec91[0] < fSlow730));
				fRec90[0] = ((iSlow657)?(fSlow656 * ((iTempPerm196)?((iTempPerm197)?((int((fRec91[0] < 0.0f)))?fSlow701:((iTempPerm197)?(fSlow701 + (fSlow732 * (fRec91[0] / fSlow723))):fSlow716)):((iTempPerm196)?(fSlow716 + (fSlow731 * ((fRec91[0] - fSlow730) / fSlow729))):fSlow711)):((int((fRec91[0] < fSlow728)))?(fSlow700 * (fSlow175 + (fSlow198 * ((fRec91[0] - fSlow727) / fSlow726)))):fSlow704))):fRec90[1]);
				fRec92[0] = ((iSlow659)?0.0f:min(fSlow733, (fRec92[1] + 1.0f)));
				fTempPerm198 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec92[0] < 0.0f)))?fRec90[0]:((int((fRec92[0] < fSlow733)))?(fRec90[0] + (fConst1 * ((fRec92[0] * (fSlow701 - fRec90[0])) / fSlow710))):fSlow701)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm199 = (fTempPerm198 * ftbl0[(((int(fTempPerm195) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm200 = (fTempPerm199 + fTempPerm193);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm201 = (fRec93[1] + fSlow735);
				fRec93[0] = (fTempPerm201 - floorf(fTempPerm201));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm202 = (65536.0f * fRec93[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec95[0] = ((iSlow650)?0.0f:min(fSlow765, (fRec95[1] + 1.0f)));
				iTempPerm203 = int((fRec95[0] < fSlow764));
				iTempPerm204 = int((fRec95[0] < fSlow767));
				fRec94[0] = ((iSlow657)?(fSlow656 * ((iTempPerm203)?((iTempPerm204)?((int((fRec95[0] < 0.0f)))?fSlow738:((iTempPerm204)?(fSlow738 + (fSlow769 * (fRec95[0] / fSlow760))):fSlow753)):((iTempPerm203)?(fSlow753 + (fSlow768 * ((fRec95[0] - fSlow767) / fSlow766))):fSlow748)):((int((fRec95[0] < fSlow765)))?(fSlow737 * (fSlow230 + (fSlow253 * ((fRec95[0] - fSlow764) / fSlow763)))):fSlow741))):fRec94[1]);
				fRec96[0] = ((iSlow659)?0.0f:min(fSlow770, (fRec96[1] + 1.0f)));
				fTempPerm205 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec96[0] < 0.0f)))?fRec94[0]:((int((fRec96[0] < fSlow770)))?(fRec94[0] + (fConst1 * ((fRec96[0] * (fSlow738 - fRec94[0])) / fSlow747))):fSlow738)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm206 = (fTempPerm205 * ftbl0[(((int(fTempPerm202) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm207 = (fTempPerm206 + fTempPerm200);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm208 = (fRec97[1] + fSlow772);
				fRec97[0] = (fTempPerm208 - floorf(fTempPerm208));
				fRec99[0] = ((iSlow650)?0.0f:min(fSlow802, (fRec99[1] + 1.0f)));
				iTempPerm209 = int((fRec99[0] < fSlow801));
				iTempPerm210 = int((fRec99[0] < fSlow804));
				fRec98[0] = ((iSlow657)?(fSlow656 * ((iTempPerm209)?((iTempPerm210)?((int((fRec99[0] < 0.0f)))?fSlow775:((iTempPerm210)?(fSlow775 + (fSlow806 * (fRec99[0] / fSlow797))):fSlow790)):((iTempPerm209)?(fSlow790 + (fSlow805 * ((fRec99[0] - fSlow804) / fSlow803))):fSlow785)):((int((fRec99[0] < fSlow802)))?(fSlow774 * (fSlow285 + (fSlow308 * ((fRec99[0] - fSlow801) / fSlow800)))):fSlow778))):fRec98[1]);
				fRec100[0] = ((iSlow659)?0.0f:min(fSlow807, (fRec100[1] + 1.0f)));
				fTempPerm211 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec100[0] < 0.0f)))?fRec98[0]:((int((fRec100[0] < fSlow807)))?(fRec98[0] + (fConst1 * ((fRec100[0] * (fSlow775 - fRec98[0])) / fSlow784))):fSlow775)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm212 = (fTempPerm211 * ftbl0[(((int((65536.0f * fRec97[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm213 = (fRec101[1] + fSlow809);
				fRec101[0] = (fTempPerm213 - floorf(fTempPerm213));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm214 = (65536.0f * fRec101[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec103[0] = ((iSlow650)?0.0f:min(fSlow839, (fRec103[1] + 1.0f)));
				iTempPerm215 = int((fRec103[0] < fSlow838));
				iTempPerm216 = int((fRec103[0] < fSlow841));
				fRec102[0] = ((iSlow657)?(fSlow656 * ((iTempPerm215)?((iTempPerm216)?((int((fRec103[0] < 0.0f)))?fSlow812:((iTempPerm216)?(fSlow812 + (fSlow843 * (fRec103[0] / fSlow834))):fSlow827)):((iTempPerm215)?(fSlow827 + (fSlow842 * ((fRec103[0] - fSlow841) / fSlow840))):fSlow822)):((int((fRec103[0] < fSlow839)))?(fSlow811 * (fSlow340 + (fSlow363 * ((fRec103[0] - fSlow838) / fSlow837)))):fSlow815))):fRec102[1]);
				fRec104[0] = ((iSlow659)?0.0f:min(fSlow844, (fRec104[1] + 1.0f)));
				fTempPerm217 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec104[0] < 0.0f)))?fRec102[0]:((int((fRec104[0] < fSlow844)))?(fRec102[0] + (fConst1 * ((fRec104[0] * (fSlow812 - fRec102[0])) / fSlow821))):fSlow812)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm218 = (fTempPerm217 * ftbl0[(((int(fTempPerm214) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm219 = (2.0879500000000002f * (fTempPerm218 + (fTempPerm212 + fTempPerm207)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec105[0] = (fTempPerm217 * ftbl0[(((int((65536.0f * (fRec101[0] + (fSlow371 * fRec105[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm220 = (fTempPerm211 * ftbl0[(((int((65536.0f * (fRec97[0] + fRec105[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm221 = (2.0879500000000002f * (fTempPerm220 + fTempPerm207));
			}
			if (iSlow5 || iSlow3) {
				fRec106[0] = (fTempPerm211 * ftbl0[(((int((65536.0f * (fRec97[0] + (fSlow371 * fRec106[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm222 = (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + fRec106[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm223 = (2.0879500000000002f * (fTempPerm218 + (fTempPerm193 + fTempPerm222)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm224 = (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + fTempPerm206))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm225 = (2.0879500000000002f * (fTempPerm220 + (fTempPerm224 + fTempPerm193)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm226 = (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec81[0] + fTempPerm192))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm227 = (2.0879500000000002f * (fTempPerm218 + (fTempPerm226 + fTempPerm222)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec107[0] = (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + (fSlow371 * fRec107[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm228 = (fTempPerm191 * ftbl0[(((int((65536.0f * (fRec85[0] + fRec107[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm229 = (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + (fTempPerm218 + fTempPerm212)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm230 = (2.0879500000000002f * (fTempPerm229 + (fTempPerm228 + fTempPerm186)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm231 = (fTempPerm191 * ftbl0[(((int((65536.0f * (fRec85[0] + fTempPerm199))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm232 = (fTempPerm231 + fTempPerm186);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm233 = (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + (fRec105[0] + fTempPerm212)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm234 = (2.0879500000000002f * (fTempPerm233 + fTempPerm232));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm235 = (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + fRec105[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm236 = (2.0879500000000002f * (fTempPerm220 + (fTempPerm235 + fTempPerm200)));
			}
			if (iSlow9) {
				fRec108[0] = (fTempPerm217 * ftbl0[(((int((fTempPerm214 + (fSlow372 * fRec108[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm237 = (2.0879500000000002f * (((fTempPerm193 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + fRec108[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + fRec108[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm211 * ftbl0[(((int((65536.0f * (fRec97[0] + fRec108[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm238 = (2.0879500000000002f * (fTempPerm220 + (fTempPerm232 + fTempPerm235)));
			}
			if (iSlow28 || iSlow11) {
				fRec109[0] = (fTempPerm217 * ftbl0[(((int((fTempPerm214 + (fSlow373 * fRec109[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm239 = (fTempPerm211 * ftbl0[(((int((65536.0f * (fRec97[0] + fRec109[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm240 = ((fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + fRec109[0]))) % 65536) + 65536) % 65536)]) + (2.0879500000000002f * (fTempPerm239 + ((fTempPerm185 * ftbl0[(((int((fTempPerm182 + (136835.89120000001f * fTempPerm192))) % 65536) + 65536) % 65536)]) + (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + fRec109[0]))) % 65536) + 65536) % 65536)])))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm241 = ((fTempPerm185 * ftbl0[(((int((65536.0f * (fRec81[0] + fRec107[0]))) % 65536) + 65536) % 65536)]) + fTempPerm228);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm242 = (fTempPerm211 * ftbl0[(((int((65536.0f * (fRec97[0] + fTempPerm218))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm243 = (2.0879500000000002f * (fTempPerm242 + (fTempPerm241 + (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + fTempPerm218))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm244 = (2.0879500000000002f * (fTempPerm229 + fTempPerm241));
			}
			if (iSlow14) {
				fRec110[0] = (fTempPerm217 * ftbl0[(((int((fTempPerm214 + (fSlow374 * fRec110[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm245 = (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec81[0] + fTempPerm231))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm246 = (2.0879500000000002f * ((fTempPerm245 + (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + fRec110[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm211 * ftbl0[(((int((65536.0f * (fRec97[0] + fRec110[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm247 = (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + fTempPerm242))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm248 = (2.0879500000000002f * (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec81[0] + (fTempPerm247 + (fRec107[0] + fTempPerm192))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec111[0] = (fTempPerm191 * ftbl0[(((int((fTempPerm188 + (fSlow375 * fRec111[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm249 = (2.0879500000000002f * (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec81[0] + (fTempPerm224 + (fRec111[0] + fTempPerm242))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm250 = (2.0879500000000002f * (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec81[0] + (fTempPerm224 + (fTempPerm192 + fTempPerm220))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec112[0] = (fTempPerm191 * ftbl0[(((int((fTempPerm188 + (fSlow374 * fRec112[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm251 = (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec81[0] + fRec112[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm252 = (2.0879500000000002f * (fTempPerm251 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + fTempPerm229))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm253 = (2.0879500000000002f * (fTempPerm226 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + fTempPerm233))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm254 = (2.0879500000000002f * (fTempPerm226 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + (fTempPerm212 + (fRec105[0] + fTempPerm206))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec113[0] = (fTempPerm191 * ftbl0[(((int((fTempPerm188 + (fSlow376 * fRec113[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm255 = (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec81[0] + fRec113[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm256 = (2.0879500000000002f * (fTempPerm255 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + (fTempPerm212 + (fTempPerm218 + fTempPerm206))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec114[0] = (fTempPerm217 * ftbl0[(((int((fTempPerm214 + (fSlow376 * fRec114[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm257 = (2.0879500000000002f * (fTempPerm245 + (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + (fRec114[0] + fTempPerm212)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec115[0] = (fTempPerm198 * ftbl0[(((int((fTempPerm195 + (fSlow376 * fRec115[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm258 = (2.0879500000000002f * (fTempPerm229 + (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec81[0] + (fTempPerm191 * ftbl0[(((int((65536.0f * (fRec85[0] + fRec115[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm259 = (2.0879500000000002f * (fTempPerm251 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + (fTempPerm242 + fTempPerm206)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec116[0] = (fTempPerm205 * ftbl0[(((int((fTempPerm202 + (fSlow373 * fRec116[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm260 = (2.0879500000000002f * (fTempPerm226 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + (fRec116[0] + fTempPerm242)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm261 = (2.0879500000000002f * (fTempPerm226 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + (fTempPerm220 + fTempPerm206)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm262 = (fTempPerm226 + fTempPerm224);
			}
			if (iSlow27) {
				fRec117[0] = (2.0879500000000002f * (fTempPerm211 * ftbl0[(((int((65536.0f * (fRec97[0] + (fTempPerm217 * ftbl0[(((int((65536.0f * (fRec101[0] + (fSlow371 * fRec117[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm263 = (fRec117[0] + (2.0879500000000002f * fTempPerm262));
			}
			if (iSlow28) {
				fTempPerm264 = (2.0879500000000002f * (fTempPerm262 + fTempPerm239));
			}
			if (iSlow29) {
				fRec118[0] = (2.0879500000000002f * (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + (fTempPerm211 * ftbl0[(((int((65536.0f * (fRec97[0] + (fTempPerm217 * ftbl0[(((int((65536.0f * (fRec101[0] + (fSlow371 * fRec118[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm265 = (fRec118[0] + (2.0879500000000002f * fTempPerm245));
			}
			if (iSlow30) {
				fTempPerm266 = (2.0879500000000002f * (fTempPerm245 + (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + fTempPerm220))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm267 = (2.0879500000000002f * (fTempPerm255 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + fTempPerm247))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm268 = (2.0879500000000002f * (fTempPerm226 + (fTempPerm198 * ftbl0[(((int((65536.0f * (fRec89[0] + (fTempPerm205 * ftbl0[(((int((65536.0f * (fRec93[0] + (fTempPerm211 * ftbl0[(((int((65536.0f * (fRec97[0] + fRec114[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec120[0] = (iSlow655 * (iRec120[1] + 1));
			iTempPerm269 = int((iRec120[0] < iSlow381));
			fTempPerm270 = expf((0 - (fConst2 / ((iSlow657)?((iTempPerm269)?fSlow380:fSlow378):fSlow377))));
			fRec119[0] = ((fRec119[1] * fTempPerm270) + (((iSlow657)?((iTempPerm269)?1.5873015873015872f:fSlow845):0.0f) * (1.0f - fTempPerm270)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm271 = (fRec121[1] + fSlow848);
				fRec121[0] = (fTempPerm271 - floorf(fTempPerm271));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm272 = (65536.0f * fRec121[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec123[0] = ((iSlow881)?0.0f:min(fSlow879, (fRec123[1] + 1.0f)));
				iTempPerm273 = int((fRec123[0] < fSlow878));
				iTempPerm274 = int((fRec123[0] < fSlow883));
				fRec122[0] = ((iSlow888)?(fSlow887 * ((iTempPerm273)?((iTempPerm274)?((int((fRec123[0] < 0.0f)))?fSlow852:((iTempPerm274)?(fSlow852 + (fSlow885 * (fRec123[0] / fSlow874))):fSlow867)):((iTempPerm273)?(fSlow867 + (fSlow884 * ((fRec123[0] - fSlow883) / fSlow882))):fSlow862)):((int((fRec123[0] < fSlow879)))?(fSlow851 * (fSlow59 + (fSlow84 * ((fRec123[0] - fSlow878) / fSlow877)))):fSlow855))):fRec122[1]);
				fRec124[0] = ((iSlow890)?0.0f:min(fSlow889, (fRec124[1] + 1.0f)));
				fTempPerm275 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec124[0] < 0.0f)))?fRec122[0]:((int((fRec124[0] < fSlow889)))?(fRec122[0] + (fConst1 * ((fRec124[0] * (fSlow852 - fRec122[0])) / fSlow861))):fSlow852)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm276 = (fTempPerm275 * ftbl0[(((int(fTempPerm272) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm277 = (fRec125[1] + fSlow892);
				fRec125[0] = (fTempPerm277 - floorf(fTempPerm277));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm278 = (65536.0f * fRec125[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec127[0] = ((iSlow881)?0.0f:min(fSlow922, (fRec127[1] + 1.0f)));
				iTempPerm279 = int((fRec127[0] < fSlow921));
				iTempPerm280 = int((fRec127[0] < fSlow924));
				fRec126[0] = ((iSlow888)?(fSlow887 * ((iTempPerm279)?((iTempPerm280)?((int((fRec127[0] < 0.0f)))?fSlow895:((iTempPerm280)?(fSlow895 + (fSlow926 * (fRec127[0] / fSlow917))):fSlow910)):((iTempPerm279)?(fSlow910 + (fSlow925 * ((fRec127[0] - fSlow924) / fSlow923))):fSlow905)):((int((fRec127[0] < fSlow922)))?(fSlow894 * (fSlow120 + (fSlow143 * ((fRec127[0] - fSlow921) / fSlow920)))):fSlow898))):fRec126[1]);
				fRec128[0] = ((iSlow890)?0.0f:min(fSlow927, (fRec128[1] + 1.0f)));
				fTempPerm281 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec128[0] < 0.0f)))?fRec126[0]:((int((fRec128[0] < fSlow927)))?(fRec126[0] + (fConst1 * ((fRec128[0] * (fSlow895 - fRec126[0])) / fSlow904))):fSlow895)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm282 = (fTempPerm281 * ftbl0[(((int(fTempPerm278) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm283 = (fTempPerm282 + fTempPerm276);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm284 = (fRec129[1] + fSlow929);
				fRec129[0] = (fTempPerm284 - floorf(fTempPerm284));
			}
			if (iSlow30 || iSlow29 || iSlow23 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm285 = (65536.0f * fRec129[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec131[0] = ((iSlow881)?0.0f:min(fSlow959, (fRec131[1] + 1.0f)));
				iTempPerm286 = int((fRec131[0] < fSlow958));
				iTempPerm287 = int((fRec131[0] < fSlow961));
				fRec130[0] = ((iSlow888)?(fSlow887 * ((iTempPerm286)?((iTempPerm287)?((int((fRec131[0] < 0.0f)))?fSlow932:((iTempPerm287)?(fSlow932 + (fSlow963 * (fRec131[0] / fSlow954))):fSlow947)):((iTempPerm286)?(fSlow947 + (fSlow962 * ((fRec131[0] - fSlow961) / fSlow960))):fSlow942)):((int((fRec131[0] < fSlow959)))?(fSlow931 * (fSlow175 + (fSlow198 * ((fRec131[0] - fSlow958) / fSlow957)))):fSlow935))):fRec130[1]);
				fRec132[0] = ((iSlow890)?0.0f:min(fSlow964, (fRec132[1] + 1.0f)));
				fTempPerm288 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec132[0] < 0.0f)))?fRec130[0]:((int((fRec132[0] < fSlow964)))?(fRec130[0] + (fConst1 * ((fRec132[0] * (fSlow932 - fRec130[0])) / fSlow941))):fSlow932)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm289 = (fTempPerm288 * ftbl0[(((int(fTempPerm285) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm290 = (fTempPerm289 + fTempPerm283);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm291 = (fRec133[1] + fSlow966);
				fRec133[0] = (fTempPerm291 - floorf(fTempPerm291));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm292 = (65536.0f * fRec133[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec135[0] = ((iSlow881)?0.0f:min(fSlow996, (fRec135[1] + 1.0f)));
				iTempPerm293 = int((fRec135[0] < fSlow995));
				iTempPerm294 = int((fRec135[0] < fSlow998));
				fRec134[0] = ((iSlow888)?(fSlow887 * ((iTempPerm293)?((iTempPerm294)?((int((fRec135[0] < 0.0f)))?fSlow969:((iTempPerm294)?(fSlow969 + (fSlow1000 * (fRec135[0] / fSlow991))):fSlow984)):((iTempPerm293)?(fSlow984 + (fSlow999 * ((fRec135[0] - fSlow998) / fSlow997))):fSlow979)):((int((fRec135[0] < fSlow996)))?(fSlow968 * (fSlow230 + (fSlow253 * ((fRec135[0] - fSlow995) / fSlow994)))):fSlow972))):fRec134[1]);
				fRec136[0] = ((iSlow890)?0.0f:min(fSlow1001, (fRec136[1] + 1.0f)));
				fTempPerm295 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec136[0] < 0.0f)))?fRec134[0]:((int((fRec136[0] < fSlow1001)))?(fRec134[0] + (fConst1 * ((fRec136[0] * (fSlow969 - fRec134[0])) / fSlow978))):fSlow969)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm296 = (fTempPerm295 * ftbl0[(((int(fTempPerm292) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm297 = (fTempPerm296 + fTempPerm290);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm298 = (fRec137[1] + fSlow1003);
				fRec137[0] = (fTempPerm298 - floorf(fTempPerm298));
				fRec139[0] = ((iSlow881)?0.0f:min(fSlow1033, (fRec139[1] + 1.0f)));
				iTempPerm299 = int((fRec139[0] < fSlow1032));
				iTempPerm300 = int((fRec139[0] < fSlow1035));
				fRec138[0] = ((iSlow888)?(fSlow887 * ((iTempPerm299)?((iTempPerm300)?((int((fRec139[0] < 0.0f)))?fSlow1006:((iTempPerm300)?(fSlow1006 + (fSlow1037 * (fRec139[0] / fSlow1028))):fSlow1021)):((iTempPerm299)?(fSlow1021 + (fSlow1036 * ((fRec139[0] - fSlow1035) / fSlow1034))):fSlow1016)):((int((fRec139[0] < fSlow1033)))?(fSlow1005 * (fSlow285 + (fSlow308 * ((fRec139[0] - fSlow1032) / fSlow1031)))):fSlow1009))):fRec138[1]);
				fRec140[0] = ((iSlow890)?0.0f:min(fSlow1038, (fRec140[1] + 1.0f)));
				fTempPerm301 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec140[0] < 0.0f)))?fRec138[0]:((int((fRec140[0] < fSlow1038)))?(fRec138[0] + (fConst1 * ((fRec140[0] * (fSlow1006 - fRec138[0])) / fSlow1015))):fSlow1006)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm302 = (fTempPerm301 * ftbl0[(((int((65536.0f * fRec137[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm303 = (fRec141[1] + fSlow1040);
				fRec141[0] = (fTempPerm303 - floorf(fTempPerm303));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm304 = (65536.0f * fRec141[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec143[0] = ((iSlow881)?0.0f:min(fSlow1070, (fRec143[1] + 1.0f)));
				iTempPerm305 = int((fRec143[0] < fSlow1069));
				iTempPerm306 = int((fRec143[0] < fSlow1072));
				fRec142[0] = ((iSlow888)?(fSlow887 * ((iTempPerm305)?((iTempPerm306)?((int((fRec143[0] < 0.0f)))?fSlow1043:((iTempPerm306)?(fSlow1043 + (fSlow1074 * (fRec143[0] / fSlow1065))):fSlow1058)):((iTempPerm305)?(fSlow1058 + (fSlow1073 * ((fRec143[0] - fSlow1072) / fSlow1071))):fSlow1053)):((int((fRec143[0] < fSlow1070)))?(fSlow1042 * (fSlow340 + (fSlow363 * ((fRec143[0] - fSlow1069) / fSlow1068)))):fSlow1046))):fRec142[1]);
				fRec144[0] = ((iSlow890)?0.0f:min(fSlow1075, (fRec144[1] + 1.0f)));
				fTempPerm307 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec144[0] < 0.0f)))?fRec142[0]:((int((fRec144[0] < fSlow1075)))?(fRec142[0] + (fConst1 * ((fRec144[0] * (fSlow1043 - fRec142[0])) / fSlow1052))):fSlow1043)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm308 = (fTempPerm307 * ftbl0[(((int(fTempPerm304) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm309 = (2.0879500000000002f * (fTempPerm308 + (fTempPerm302 + fTempPerm297)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec145[0] = (fTempPerm307 * ftbl0[(((int((65536.0f * (fRec141[0] + (fSlow371 * fRec145[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm310 = (fTempPerm301 * ftbl0[(((int((65536.0f * (fRec137[0] + fRec145[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm311 = (2.0879500000000002f * (fTempPerm310 + fTempPerm297));
			}
			if (iSlow5 || iSlow3) {
				fRec146[0] = (fTempPerm301 * ftbl0[(((int((65536.0f * (fRec137[0] + (fSlow371 * fRec146[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm312 = (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + fRec146[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm313 = (2.0879500000000002f * (fTempPerm308 + (fTempPerm283 + fTempPerm312)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm314 = (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + fTempPerm296))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm315 = (2.0879500000000002f * (fTempPerm310 + (fTempPerm314 + fTempPerm283)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm316 = (fTempPerm275 * ftbl0[(((int((65536.0f * (fRec121[0] + fTempPerm282))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm317 = (2.0879500000000002f * (fTempPerm308 + (fTempPerm316 + fTempPerm312)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec147[0] = (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + (fSlow371 * fRec147[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm318 = (fTempPerm281 * ftbl0[(((int((65536.0f * (fRec125[0] + fRec147[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm319 = (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + (fTempPerm308 + fTempPerm302)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm320 = (2.0879500000000002f * (fTempPerm319 + (fTempPerm318 + fTempPerm276)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm321 = (fTempPerm281 * ftbl0[(((int((65536.0f * (fRec125[0] + fTempPerm289))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm322 = (fTempPerm321 + fTempPerm276);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm323 = (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + (fRec145[0] + fTempPerm302)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm324 = (2.0879500000000002f * (fTempPerm323 + fTempPerm322));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm325 = (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + fRec145[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm326 = (2.0879500000000002f * (fTempPerm310 + (fTempPerm325 + fTempPerm290)));
			}
			if (iSlow9) {
				fRec148[0] = (fTempPerm307 * ftbl0[(((int((fTempPerm304 + (fSlow372 * fRec148[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm327 = (2.0879500000000002f * (((fTempPerm283 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + fRec148[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + fRec148[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm301 * ftbl0[(((int((65536.0f * (fRec137[0] + fRec148[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm328 = (2.0879500000000002f * (fTempPerm310 + (fTempPerm322 + fTempPerm325)));
			}
			if (iSlow28 || iSlow11) {
				fRec149[0] = (fTempPerm307 * ftbl0[(((int((fTempPerm304 + (fSlow373 * fRec149[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm329 = (fTempPerm301 * ftbl0[(((int((65536.0f * (fRec137[0] + fRec149[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm330 = ((fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + fRec149[0]))) % 65536) + 65536) % 65536)]) + (2.0879500000000002f * (fTempPerm329 + ((fTempPerm275 * ftbl0[(((int((fTempPerm272 + (136835.89120000001f * fTempPerm282))) % 65536) + 65536) % 65536)]) + (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + fRec149[0]))) % 65536) + 65536) % 65536)])))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm331 = ((fTempPerm275 * ftbl0[(((int((65536.0f * (fRec121[0] + fRec147[0]))) % 65536) + 65536) % 65536)]) + fTempPerm318);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm332 = (fTempPerm301 * ftbl0[(((int((65536.0f * (fRec137[0] + fTempPerm308))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm333 = (2.0879500000000002f * (fTempPerm332 + (fTempPerm331 + (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + fTempPerm308))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm334 = (2.0879500000000002f * (fTempPerm319 + fTempPerm331));
			}
			if (iSlow14) {
				fRec150[0] = (fTempPerm307 * ftbl0[(((int((fTempPerm304 + (fSlow374 * fRec150[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm335 = (fTempPerm275 * ftbl0[(((int((65536.0f * (fRec121[0] + fTempPerm321))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm336 = (2.0879500000000002f * ((fTempPerm335 + (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + fRec150[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm301 * ftbl0[(((int((65536.0f * (fRec137[0] + fRec150[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm337 = (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + fTempPerm332))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm338 = (2.0879500000000002f * (fTempPerm275 * ftbl0[(((int((65536.0f * (fRec121[0] + (fTempPerm337 + (fRec147[0] + fTempPerm282))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec151[0] = (fTempPerm281 * ftbl0[(((int((fTempPerm278 + (fSlow375 * fRec151[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm339 = (2.0879500000000002f * (fTempPerm275 * ftbl0[(((int((65536.0f * (fRec121[0] + (fTempPerm314 + (fRec151[0] + fTempPerm332))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm340 = (2.0879500000000002f * (fTempPerm275 * ftbl0[(((int((65536.0f * (fRec121[0] + (fTempPerm314 + (fTempPerm282 + fTempPerm310))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec152[0] = (fTempPerm281 * ftbl0[(((int((fTempPerm278 + (fSlow374 * fRec152[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm341 = (fTempPerm275 * ftbl0[(((int((65536.0f * (fRec121[0] + fRec152[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm342 = (2.0879500000000002f * (fTempPerm341 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + fTempPerm319))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm343 = (2.0879500000000002f * (fTempPerm316 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + fTempPerm323))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm344 = (2.0879500000000002f * (fTempPerm316 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + (fTempPerm302 + (fRec145[0] + fTempPerm296))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec153[0] = (fTempPerm281 * ftbl0[(((int((fTempPerm278 + (fSlow376 * fRec153[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm345 = (fTempPerm275 * ftbl0[(((int((65536.0f * (fRec121[0] + fRec153[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm346 = (2.0879500000000002f * (fTempPerm345 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + (fTempPerm302 + (fTempPerm308 + fTempPerm296))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec154[0] = (fTempPerm307 * ftbl0[(((int((fTempPerm304 + (fSlow376 * fRec154[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm347 = (2.0879500000000002f * (fTempPerm335 + (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + (fRec154[0] + fTempPerm302)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec155[0] = (fTempPerm288 * ftbl0[(((int((fTempPerm285 + (fSlow376 * fRec155[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm348 = (2.0879500000000002f * (fTempPerm319 + (fTempPerm275 * ftbl0[(((int((65536.0f * (fRec121[0] + (fTempPerm281 * ftbl0[(((int((65536.0f * (fRec125[0] + fRec155[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm349 = (2.0879500000000002f * (fTempPerm341 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + (fTempPerm332 + fTempPerm296)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec156[0] = (fTempPerm295 * ftbl0[(((int((fTempPerm292 + (fSlow373 * fRec156[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm350 = (2.0879500000000002f * (fTempPerm316 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + (fRec156[0] + fTempPerm332)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm351 = (2.0879500000000002f * (fTempPerm316 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + (fTempPerm310 + fTempPerm296)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm352 = (fTempPerm316 + fTempPerm314);
			}
			if (iSlow27) {
				fRec157[0] = (2.0879500000000002f * (fTempPerm301 * ftbl0[(((int((65536.0f * (fRec137[0] + (fTempPerm307 * ftbl0[(((int((65536.0f * (fRec141[0] + (fSlow371 * fRec157[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm353 = (fRec157[0] + (2.0879500000000002f * fTempPerm352));
			}
			if (iSlow28) {
				fTempPerm354 = (2.0879500000000002f * (fTempPerm352 + fTempPerm329));
			}
			if (iSlow29) {
				fRec158[0] = (2.0879500000000002f * (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + (fTempPerm301 * ftbl0[(((int((65536.0f * (fRec137[0] + (fTempPerm307 * ftbl0[(((int((65536.0f * (fRec141[0] + (fSlow371 * fRec158[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm355 = (fRec158[0] + (2.0879500000000002f * fTempPerm335));
			}
			if (iSlow30) {
				fTempPerm356 = (2.0879500000000002f * (fTempPerm335 + (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + fTempPerm310))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm357 = (2.0879500000000002f * (fTempPerm345 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + fTempPerm337))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm358 = (2.0879500000000002f * (fTempPerm316 + (fTempPerm288 * ftbl0[(((int((65536.0f * (fRec129[0] + (fTempPerm295 * ftbl0[(((int((65536.0f * (fRec133[0] + (fTempPerm301 * ftbl0[(((int((65536.0f * (fRec137[0] + fRec154[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec160[0] = (iSlow886 * (iRec160[1] + 1));
			iTempPerm359 = int((iRec160[0] < iSlow381));
			fTempPerm360 = expf((0 - (fConst2 / ((iSlow888)?((iTempPerm359)?fSlow380:fSlow378):fSlow377))));
			fRec159[0] = ((fRec159[1] * fTempPerm360) + (((iSlow888)?((iTempPerm359)?1.5873015873015872f:fSlow1076):0.0f) * (1.0f - fTempPerm360)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm361 = (fRec161[1] + fSlow1079);
				fRec161[0] = (fTempPerm361 - floorf(fTempPerm361));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm362 = (65536.0f * fRec161[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec163[0] = ((iSlow1112)?0.0f:min(fSlow1110, (fRec163[1] + 1.0f)));
				iTempPerm363 = int((fRec163[0] < fSlow1109));
				iTempPerm364 = int((fRec163[0] < fSlow1114));
				fRec162[0] = ((iSlow1119)?(fSlow1118 * ((iTempPerm363)?((iTempPerm364)?((int((fRec163[0] < 0.0f)))?fSlow1083:((iTempPerm364)?(fSlow1083 + (fSlow1116 * (fRec163[0] / fSlow1105))):fSlow1098)):((iTempPerm363)?(fSlow1098 + (fSlow1115 * ((fRec163[0] - fSlow1114) / fSlow1113))):fSlow1093)):((int((fRec163[0] < fSlow1110)))?(fSlow1082 * (fSlow59 + (fSlow84 * ((fRec163[0] - fSlow1109) / fSlow1108)))):fSlow1086))):fRec162[1]);
				fRec164[0] = ((iSlow1121)?0.0f:min(fSlow1120, (fRec164[1] + 1.0f)));
				fTempPerm365 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec164[0] < 0.0f)))?fRec162[0]:((int((fRec164[0] < fSlow1120)))?(fRec162[0] + (fConst1 * ((fRec164[0] * (fSlow1083 - fRec162[0])) / fSlow1092))):fSlow1083)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm366 = (fTempPerm365 * ftbl0[(((int(fTempPerm362) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm367 = (fRec165[1] + fSlow1123);
				fRec165[0] = (fTempPerm367 - floorf(fTempPerm367));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm368 = (65536.0f * fRec165[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec167[0] = ((iSlow1112)?0.0f:min(fSlow1153, (fRec167[1] + 1.0f)));
				iTempPerm369 = int((fRec167[0] < fSlow1152));
				iTempPerm370 = int((fRec167[0] < fSlow1155));
				fRec166[0] = ((iSlow1119)?(fSlow1118 * ((iTempPerm369)?((iTempPerm370)?((int((fRec167[0] < 0.0f)))?fSlow1126:((iTempPerm370)?(fSlow1126 + (fSlow1157 * (fRec167[0] / fSlow1148))):fSlow1141)):((iTempPerm369)?(fSlow1141 + (fSlow1156 * ((fRec167[0] - fSlow1155) / fSlow1154))):fSlow1136)):((int((fRec167[0] < fSlow1153)))?(fSlow1125 * (fSlow120 + (fSlow143 * ((fRec167[0] - fSlow1152) / fSlow1151)))):fSlow1129))):fRec166[1]);
				fRec168[0] = ((iSlow1121)?0.0f:min(fSlow1158, (fRec168[1] + 1.0f)));
				fTempPerm371 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec168[0] < 0.0f)))?fRec166[0]:((int((fRec168[0] < fSlow1158)))?(fRec166[0] + (fConst1 * ((fRec168[0] * (fSlow1126 - fRec166[0])) / fSlow1135))):fSlow1126)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm372 = (fTempPerm371 * ftbl0[(((int(fTempPerm368) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm373 = (fTempPerm372 + fTempPerm366);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm374 = (fRec169[1] + fSlow1160);
				fRec169[0] = (fTempPerm374 - floorf(fTempPerm374));
			}
			if (iSlow30 || iSlow29 || iSlow23 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm375 = (65536.0f * fRec169[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec171[0] = ((iSlow1112)?0.0f:min(fSlow1190, (fRec171[1] + 1.0f)));
				iTempPerm376 = int((fRec171[0] < fSlow1189));
				iTempPerm377 = int((fRec171[0] < fSlow1192));
				fRec170[0] = ((iSlow1119)?(fSlow1118 * ((iTempPerm376)?((iTempPerm377)?((int((fRec171[0] < 0.0f)))?fSlow1163:((iTempPerm377)?(fSlow1163 + (fSlow1194 * (fRec171[0] / fSlow1185))):fSlow1178)):((iTempPerm376)?(fSlow1178 + (fSlow1193 * ((fRec171[0] - fSlow1192) / fSlow1191))):fSlow1173)):((int((fRec171[0] < fSlow1190)))?(fSlow1162 * (fSlow175 + (fSlow198 * ((fRec171[0] - fSlow1189) / fSlow1188)))):fSlow1166))):fRec170[1]);
				fRec172[0] = ((iSlow1121)?0.0f:min(fSlow1195, (fRec172[1] + 1.0f)));
				fTempPerm378 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec172[0] < 0.0f)))?fRec170[0]:((int((fRec172[0] < fSlow1195)))?(fRec170[0] + (fConst1 * ((fRec172[0] * (fSlow1163 - fRec170[0])) / fSlow1172))):fSlow1163)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm379 = (fTempPerm378 * ftbl0[(((int(fTempPerm375) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm380 = (fTempPerm379 + fTempPerm373);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm381 = (fRec173[1] + fSlow1197);
				fRec173[0] = (fTempPerm381 - floorf(fTempPerm381));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm382 = (65536.0f * fRec173[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec175[0] = ((iSlow1112)?0.0f:min(fSlow1227, (fRec175[1] + 1.0f)));
				iTempPerm383 = int((fRec175[0] < fSlow1226));
				iTempPerm384 = int((fRec175[0] < fSlow1229));
				fRec174[0] = ((iSlow1119)?(fSlow1118 * ((iTempPerm383)?((iTempPerm384)?((int((fRec175[0] < 0.0f)))?fSlow1200:((iTempPerm384)?(fSlow1200 + (fSlow1231 * (fRec175[0] / fSlow1222))):fSlow1215)):((iTempPerm383)?(fSlow1215 + (fSlow1230 * ((fRec175[0] - fSlow1229) / fSlow1228))):fSlow1210)):((int((fRec175[0] < fSlow1227)))?(fSlow1199 * (fSlow230 + (fSlow253 * ((fRec175[0] - fSlow1226) / fSlow1225)))):fSlow1203))):fRec174[1]);
				fRec176[0] = ((iSlow1121)?0.0f:min(fSlow1232, (fRec176[1] + 1.0f)));
				fTempPerm385 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec176[0] < 0.0f)))?fRec174[0]:((int((fRec176[0] < fSlow1232)))?(fRec174[0] + (fConst1 * ((fRec176[0] * (fSlow1200 - fRec174[0])) / fSlow1209))):fSlow1200)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm386 = (fTempPerm385 * ftbl0[(((int(fTempPerm382) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm387 = (fTempPerm386 + fTempPerm380);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm388 = (fRec177[1] + fSlow1234);
				fRec177[0] = (fTempPerm388 - floorf(fTempPerm388));
				fRec179[0] = ((iSlow1112)?0.0f:min(fSlow1264, (fRec179[1] + 1.0f)));
				iTempPerm389 = int((fRec179[0] < fSlow1263));
				iTempPerm390 = int((fRec179[0] < fSlow1266));
				fRec178[0] = ((iSlow1119)?(fSlow1118 * ((iTempPerm389)?((iTempPerm390)?((int((fRec179[0] < 0.0f)))?fSlow1237:((iTempPerm390)?(fSlow1237 + (fSlow1268 * (fRec179[0] / fSlow1259))):fSlow1252)):((iTempPerm389)?(fSlow1252 + (fSlow1267 * ((fRec179[0] - fSlow1266) / fSlow1265))):fSlow1247)):((int((fRec179[0] < fSlow1264)))?(fSlow1236 * (fSlow285 + (fSlow308 * ((fRec179[0] - fSlow1263) / fSlow1262)))):fSlow1240))):fRec178[1]);
				fRec180[0] = ((iSlow1121)?0.0f:min(fSlow1269, (fRec180[1] + 1.0f)));
				fTempPerm391 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec180[0] < 0.0f)))?fRec178[0]:((int((fRec180[0] < fSlow1269)))?(fRec178[0] + (fConst1 * ((fRec180[0] * (fSlow1237 - fRec178[0])) / fSlow1246))):fSlow1237)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm392 = (fTempPerm391 * ftbl0[(((int((65536.0f * fRec177[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm393 = (fRec181[1] + fSlow1271);
				fRec181[0] = (fTempPerm393 - floorf(fTempPerm393));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm394 = (65536.0f * fRec181[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec183[0] = ((iSlow1112)?0.0f:min(fSlow1301, (fRec183[1] + 1.0f)));
				iTempPerm395 = int((fRec183[0] < fSlow1300));
				iTempPerm396 = int((fRec183[0] < fSlow1303));
				fRec182[0] = ((iSlow1119)?(fSlow1118 * ((iTempPerm395)?((iTempPerm396)?((int((fRec183[0] < 0.0f)))?fSlow1274:((iTempPerm396)?(fSlow1274 + (fSlow1305 * (fRec183[0] / fSlow1296))):fSlow1289)):((iTempPerm395)?(fSlow1289 + (fSlow1304 * ((fRec183[0] - fSlow1303) / fSlow1302))):fSlow1284)):((int((fRec183[0] < fSlow1301)))?(fSlow1273 * (fSlow340 + (fSlow363 * ((fRec183[0] - fSlow1300) / fSlow1299)))):fSlow1277))):fRec182[1]);
				fRec184[0] = ((iSlow1121)?0.0f:min(fSlow1306, (fRec184[1] + 1.0f)));
				fTempPerm397 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec184[0] < 0.0f)))?fRec182[0]:((int((fRec184[0] < fSlow1306)))?(fRec182[0] + (fConst1 * ((fRec184[0] * (fSlow1274 - fRec182[0])) / fSlow1283))):fSlow1274)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm398 = (fTempPerm397 * ftbl0[(((int(fTempPerm394) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm399 = (2.0879500000000002f * (fTempPerm398 + (fTempPerm392 + fTempPerm387)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec185[0] = (fTempPerm397 * ftbl0[(((int((65536.0f * (fRec181[0] + (fSlow371 * fRec185[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm400 = (fTempPerm391 * ftbl0[(((int((65536.0f * (fRec177[0] + fRec185[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm401 = (2.0879500000000002f * (fTempPerm400 + fTempPerm387));
			}
			if (iSlow5 || iSlow3) {
				fRec186[0] = (fTempPerm391 * ftbl0[(((int((65536.0f * (fRec177[0] + (fSlow371 * fRec186[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm402 = (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + fRec186[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm403 = (2.0879500000000002f * (fTempPerm398 + (fTempPerm373 + fTempPerm402)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm404 = (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + fTempPerm386))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm405 = (2.0879500000000002f * (fTempPerm400 + (fTempPerm404 + fTempPerm373)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm406 = (fTempPerm365 * ftbl0[(((int((65536.0f * (fRec161[0] + fTempPerm372))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm407 = (2.0879500000000002f * (fTempPerm398 + (fTempPerm406 + fTempPerm402)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec187[0] = (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + (fSlow371 * fRec187[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm408 = (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec165[0] + fRec187[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm409 = (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + (fTempPerm398 + fTempPerm392)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm410 = (2.0879500000000002f * (fTempPerm409 + (fTempPerm408 + fTempPerm366)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm411 = (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec165[0] + fTempPerm379))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm412 = (fTempPerm411 + fTempPerm366);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm413 = (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + (fRec185[0] + fTempPerm392)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm414 = (2.0879500000000002f * (fTempPerm413 + fTempPerm412));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm415 = (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + fRec185[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm416 = (2.0879500000000002f * (fTempPerm400 + (fTempPerm415 + fTempPerm380)));
			}
			if (iSlow9) {
				fRec188[0] = (fTempPerm397 * ftbl0[(((int((fTempPerm394 + (fSlow372 * fRec188[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm417 = (2.0879500000000002f * (((fTempPerm373 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + fRec188[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + fRec188[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm391 * ftbl0[(((int((65536.0f * (fRec177[0] + fRec188[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm418 = (2.0879500000000002f * (fTempPerm400 + (fTempPerm412 + fTempPerm415)));
			}
			if (iSlow28 || iSlow11) {
				fRec189[0] = (fTempPerm397 * ftbl0[(((int((fTempPerm394 + (fSlow373 * fRec189[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm419 = (fTempPerm391 * ftbl0[(((int((65536.0f * (fRec177[0] + fRec189[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm420 = ((fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + fRec189[0]))) % 65536) + 65536) % 65536)]) + (2.0879500000000002f * (fTempPerm419 + ((fTempPerm365 * ftbl0[(((int((fTempPerm362 + (136835.89120000001f * fTempPerm372))) % 65536) + 65536) % 65536)]) + (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + fRec189[0]))) % 65536) + 65536) % 65536)])))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm421 = ((fTempPerm365 * ftbl0[(((int((65536.0f * (fRec161[0] + fRec187[0]))) % 65536) + 65536) % 65536)]) + fTempPerm408);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm422 = (fTempPerm391 * ftbl0[(((int((65536.0f * (fRec177[0] + fTempPerm398))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm423 = (2.0879500000000002f * (fTempPerm422 + (fTempPerm421 + (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + fTempPerm398))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm424 = (2.0879500000000002f * (fTempPerm409 + fTempPerm421));
			}
			if (iSlow14) {
				fRec190[0] = (fTempPerm397 * ftbl0[(((int((fTempPerm394 + (fSlow374 * fRec190[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm425 = (fTempPerm365 * ftbl0[(((int((65536.0f * (fRec161[0] + fTempPerm411))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm426 = (2.0879500000000002f * ((fTempPerm425 + (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + fRec190[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm391 * ftbl0[(((int((65536.0f * (fRec177[0] + fRec190[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm427 = (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + fTempPerm422))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm428 = (2.0879500000000002f * (fTempPerm365 * ftbl0[(((int((65536.0f * (fRec161[0] + (fTempPerm427 + (fRec187[0] + fTempPerm372))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec191[0] = (fTempPerm371 * ftbl0[(((int((fTempPerm368 + (fSlow375 * fRec191[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm429 = (2.0879500000000002f * (fTempPerm365 * ftbl0[(((int((65536.0f * (fRec161[0] + (fTempPerm404 + (fRec191[0] + fTempPerm422))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm430 = (2.0879500000000002f * (fTempPerm365 * ftbl0[(((int((65536.0f * (fRec161[0] + (fTempPerm404 + (fTempPerm372 + fTempPerm400))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec192[0] = (fTempPerm371 * ftbl0[(((int((fTempPerm368 + (fSlow374 * fRec192[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm431 = (fTempPerm365 * ftbl0[(((int((65536.0f * (fRec161[0] + fRec192[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm432 = (2.0879500000000002f * (fTempPerm431 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + fTempPerm409))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm433 = (2.0879500000000002f * (fTempPerm406 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + fTempPerm413))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm434 = (2.0879500000000002f * (fTempPerm406 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + (fTempPerm392 + (fRec185[0] + fTempPerm386))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec193[0] = (fTempPerm371 * ftbl0[(((int((fTempPerm368 + (fSlow376 * fRec193[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm435 = (fTempPerm365 * ftbl0[(((int((65536.0f * (fRec161[0] + fRec193[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm436 = (2.0879500000000002f * (fTempPerm435 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + (fTempPerm392 + (fTempPerm398 + fTempPerm386))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec194[0] = (fTempPerm397 * ftbl0[(((int((fTempPerm394 + (fSlow376 * fRec194[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm437 = (2.0879500000000002f * (fTempPerm425 + (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + (fRec194[0] + fTempPerm392)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec195[0] = (fTempPerm378 * ftbl0[(((int((fTempPerm375 + (fSlow376 * fRec195[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm438 = (2.0879500000000002f * (fTempPerm409 + (fTempPerm365 * ftbl0[(((int((65536.0f * (fRec161[0] + (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec165[0] + fRec195[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm439 = (2.0879500000000002f * (fTempPerm431 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + (fTempPerm422 + fTempPerm386)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec196[0] = (fTempPerm385 * ftbl0[(((int((fTempPerm382 + (fSlow373 * fRec196[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm440 = (2.0879500000000002f * (fTempPerm406 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + (fRec196[0] + fTempPerm422)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm441 = (2.0879500000000002f * (fTempPerm406 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + (fTempPerm400 + fTempPerm386)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm442 = (fTempPerm406 + fTempPerm404);
			}
			if (iSlow27) {
				fRec197[0] = (2.0879500000000002f * (fTempPerm391 * ftbl0[(((int((65536.0f * (fRec177[0] + (fTempPerm397 * ftbl0[(((int((65536.0f * (fRec181[0] + (fSlow371 * fRec197[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm443 = (fRec197[0] + (2.0879500000000002f * fTempPerm442));
			}
			if (iSlow28) {
				fTempPerm444 = (2.0879500000000002f * (fTempPerm442 + fTempPerm419));
			}
			if (iSlow29) {
				fRec198[0] = (2.0879500000000002f * (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + (fTempPerm391 * ftbl0[(((int((65536.0f * (fRec177[0] + (fTempPerm397 * ftbl0[(((int((65536.0f * (fRec181[0] + (fSlow371 * fRec198[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm445 = (fRec198[0] + (2.0879500000000002f * fTempPerm425));
			}
			if (iSlow30) {
				fTempPerm446 = (2.0879500000000002f * (fTempPerm425 + (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + fTempPerm400))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm447 = (2.0879500000000002f * (fTempPerm435 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + fTempPerm427))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm448 = (2.0879500000000002f * (fTempPerm406 + (fTempPerm378 * ftbl0[(((int((65536.0f * (fRec169[0] + (fTempPerm385 * ftbl0[(((int((65536.0f * (fRec173[0] + (fTempPerm391 * ftbl0[(((int((65536.0f * (fRec177[0] + fRec194[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec200[0] = (iSlow1117 * (iRec200[1] + 1));
			iTempPerm449 = int((iRec200[0] < iSlow381));
			fTempPerm450 = expf((0 - (fConst2 / ((iSlow1119)?((iTempPerm449)?fSlow380:fSlow378):fSlow377))));
			fRec199[0] = ((fRec199[1] * fTempPerm450) + (((iSlow1119)?((iTempPerm449)?1.5873015873015872f:fSlow1307):0.0f) * (1.0f - fTempPerm450)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm451 = (fRec201[1] + fSlow1310);
				fRec201[0] = (fTempPerm451 - floorf(fTempPerm451));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm452 = (65536.0f * fRec201[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec203[0] = ((iSlow1343)?0.0f:min(fSlow1341, (fRec203[1] + 1.0f)));
				iTempPerm453 = int((fRec203[0] < fSlow1340));
				iTempPerm454 = int((fRec203[0] < fSlow1345));
				fRec202[0] = ((iSlow1350)?(fSlow1349 * ((iTempPerm453)?((iTempPerm454)?((int((fRec203[0] < 0.0f)))?fSlow1314:((iTempPerm454)?(fSlow1314 + (fSlow1347 * (fRec203[0] / fSlow1336))):fSlow1329)):((iTempPerm453)?(fSlow1329 + (fSlow1346 * ((fRec203[0] - fSlow1345) / fSlow1344))):fSlow1324)):((int((fRec203[0] < fSlow1341)))?(fSlow1313 * (fSlow59 + (fSlow84 * ((fRec203[0] - fSlow1340) / fSlow1339)))):fSlow1317))):fRec202[1]);
				fRec204[0] = ((iSlow1352)?0.0f:min(fSlow1351, (fRec204[1] + 1.0f)));
				fTempPerm455 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec204[0] < 0.0f)))?fRec202[0]:((int((fRec204[0] < fSlow1351)))?(fRec202[0] + (fConst1 * ((fRec204[0] * (fSlow1314 - fRec202[0])) / fSlow1323))):fSlow1314)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm456 = (fTempPerm455 * ftbl0[(((int(fTempPerm452) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm457 = (fRec205[1] + fSlow1354);
				fRec205[0] = (fTempPerm457 - floorf(fTempPerm457));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm458 = (65536.0f * fRec205[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec207[0] = ((iSlow1343)?0.0f:min(fSlow1384, (fRec207[1] + 1.0f)));
				iTempPerm459 = int((fRec207[0] < fSlow1383));
				iTempPerm460 = int((fRec207[0] < fSlow1386));
				fRec206[0] = ((iSlow1350)?(fSlow1349 * ((iTempPerm459)?((iTempPerm460)?((int((fRec207[0] < 0.0f)))?fSlow1357:((iTempPerm460)?(fSlow1357 + (fSlow1388 * (fRec207[0] / fSlow1379))):fSlow1372)):((iTempPerm459)?(fSlow1372 + (fSlow1387 * ((fRec207[0] - fSlow1386) / fSlow1385))):fSlow1367)):((int((fRec207[0] < fSlow1384)))?(fSlow1356 * (fSlow120 + (fSlow143 * ((fRec207[0] - fSlow1383) / fSlow1382)))):fSlow1360))):fRec206[1]);
				fRec208[0] = ((iSlow1352)?0.0f:min(fSlow1389, (fRec208[1] + 1.0f)));
				fTempPerm461 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec208[0] < 0.0f)))?fRec206[0]:((int((fRec208[0] < fSlow1389)))?(fRec206[0] + (fConst1 * ((fRec208[0] * (fSlow1357 - fRec206[0])) / fSlow1366))):fSlow1357)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm462 = (fTempPerm461 * ftbl0[(((int(fTempPerm458) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm463 = (fTempPerm462 + fTempPerm456);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm464 = (fRec209[1] + fSlow1391);
				fRec209[0] = (fTempPerm464 - floorf(fTempPerm464));
			}
			if (iSlow30 || iSlow29 || iSlow23 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm465 = (65536.0f * fRec209[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec211[0] = ((iSlow1343)?0.0f:min(fSlow1421, (fRec211[1] + 1.0f)));
				iTempPerm466 = int((fRec211[0] < fSlow1420));
				iTempPerm467 = int((fRec211[0] < fSlow1423));
				fRec210[0] = ((iSlow1350)?(fSlow1349 * ((iTempPerm466)?((iTempPerm467)?((int((fRec211[0] < 0.0f)))?fSlow1394:((iTempPerm467)?(fSlow1394 + (fSlow1425 * (fRec211[0] / fSlow1416))):fSlow1409)):((iTempPerm466)?(fSlow1409 + (fSlow1424 * ((fRec211[0] - fSlow1423) / fSlow1422))):fSlow1404)):((int((fRec211[0] < fSlow1421)))?(fSlow1393 * (fSlow175 + (fSlow198 * ((fRec211[0] - fSlow1420) / fSlow1419)))):fSlow1397))):fRec210[1]);
				fRec212[0] = ((iSlow1352)?0.0f:min(fSlow1426, (fRec212[1] + 1.0f)));
				fTempPerm468 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec212[0] < 0.0f)))?fRec210[0]:((int((fRec212[0] < fSlow1426)))?(fRec210[0] + (fConst1 * ((fRec212[0] * (fSlow1394 - fRec210[0])) / fSlow1403))):fSlow1394)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm469 = (fTempPerm468 * ftbl0[(((int(fTempPerm465) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm470 = (fTempPerm469 + fTempPerm463);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm471 = (fRec213[1] + fSlow1428);
				fRec213[0] = (fTempPerm471 - floorf(fTempPerm471));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm472 = (65536.0f * fRec213[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec215[0] = ((iSlow1343)?0.0f:min(fSlow1458, (fRec215[1] + 1.0f)));
				iTempPerm473 = int((fRec215[0] < fSlow1457));
				iTempPerm474 = int((fRec215[0] < fSlow1460));
				fRec214[0] = ((iSlow1350)?(fSlow1349 * ((iTempPerm473)?((iTempPerm474)?((int((fRec215[0] < 0.0f)))?fSlow1431:((iTempPerm474)?(fSlow1431 + (fSlow1462 * (fRec215[0] / fSlow1453))):fSlow1446)):((iTempPerm473)?(fSlow1446 + (fSlow1461 * ((fRec215[0] - fSlow1460) / fSlow1459))):fSlow1441)):((int((fRec215[0] < fSlow1458)))?(fSlow1430 * (fSlow230 + (fSlow253 * ((fRec215[0] - fSlow1457) / fSlow1456)))):fSlow1434))):fRec214[1]);
				fRec216[0] = ((iSlow1352)?0.0f:min(fSlow1463, (fRec216[1] + 1.0f)));
				fTempPerm475 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec216[0] < 0.0f)))?fRec214[0]:((int((fRec216[0] < fSlow1463)))?(fRec214[0] + (fConst1 * ((fRec216[0] * (fSlow1431 - fRec214[0])) / fSlow1440))):fSlow1431)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm476 = (fTempPerm475 * ftbl0[(((int(fTempPerm472) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm477 = (fTempPerm476 + fTempPerm470);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm478 = (fRec217[1] + fSlow1465);
				fRec217[0] = (fTempPerm478 - floorf(fTempPerm478));
				fRec219[0] = ((iSlow1343)?0.0f:min(fSlow1495, (fRec219[1] + 1.0f)));
				iTempPerm479 = int((fRec219[0] < fSlow1494));
				iTempPerm480 = int((fRec219[0] < fSlow1497));
				fRec218[0] = ((iSlow1350)?(fSlow1349 * ((iTempPerm479)?((iTempPerm480)?((int((fRec219[0] < 0.0f)))?fSlow1468:((iTempPerm480)?(fSlow1468 + (fSlow1499 * (fRec219[0] / fSlow1490))):fSlow1483)):((iTempPerm479)?(fSlow1483 + (fSlow1498 * ((fRec219[0] - fSlow1497) / fSlow1496))):fSlow1478)):((int((fRec219[0] < fSlow1495)))?(fSlow1467 * (fSlow285 + (fSlow308 * ((fRec219[0] - fSlow1494) / fSlow1493)))):fSlow1471))):fRec218[1]);
				fRec220[0] = ((iSlow1352)?0.0f:min(fSlow1500, (fRec220[1] + 1.0f)));
				fTempPerm481 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec220[0] < 0.0f)))?fRec218[0]:((int((fRec220[0] < fSlow1500)))?(fRec218[0] + (fConst1 * ((fRec220[0] * (fSlow1468 - fRec218[0])) / fSlow1477))):fSlow1468)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm482 = (fTempPerm481 * ftbl0[(((int((65536.0f * fRec217[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm483 = (fRec221[1] + fSlow1502);
				fRec221[0] = (fTempPerm483 - floorf(fTempPerm483));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm484 = (65536.0f * fRec221[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec223[0] = ((iSlow1343)?0.0f:min(fSlow1532, (fRec223[1] + 1.0f)));
				iTempPerm485 = int((fRec223[0] < fSlow1531));
				iTempPerm486 = int((fRec223[0] < fSlow1534));
				fRec222[0] = ((iSlow1350)?(fSlow1349 * ((iTempPerm485)?((iTempPerm486)?((int((fRec223[0] < 0.0f)))?fSlow1505:((iTempPerm486)?(fSlow1505 + (fSlow1536 * (fRec223[0] / fSlow1527))):fSlow1520)):((iTempPerm485)?(fSlow1520 + (fSlow1535 * ((fRec223[0] - fSlow1534) / fSlow1533))):fSlow1515)):((int((fRec223[0] < fSlow1532)))?(fSlow1504 * (fSlow340 + (fSlow363 * ((fRec223[0] - fSlow1531) / fSlow1530)))):fSlow1508))):fRec222[1]);
				fRec224[0] = ((iSlow1352)?0.0f:min(fSlow1537, (fRec224[1] + 1.0f)));
				fTempPerm487 = faustpower<8>((0.01020408163265306f * min((float)98, ((int((fRec224[0] < 0.0f)))?fRec222[0]:((int((fRec224[0] < fSlow1537)))?(fRec222[0] + (fConst1 * ((fRec224[0] * (fSlow1505 - fRec222[0])) / fSlow1514))):fSlow1505)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm488 = (fTempPerm487 * ftbl0[(((int(fTempPerm484) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm489 = (2.0879500000000002f * (fTempPerm488 + (fTempPerm482 + fTempPerm477)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec225[0] = (fTempPerm487 * ftbl0[(((int((65536.0f * (fRec221[0] + (fSlow371 * fRec225[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm490 = (fTempPerm481 * ftbl0[(((int((65536.0f * (fRec217[0] + fRec225[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm491 = (2.0879500000000002f * (fTempPerm490 + fTempPerm477));
			}
			if (iSlow5 || iSlow3) {
				fRec226[0] = (fTempPerm481 * ftbl0[(((int((65536.0f * (fRec217[0] + (fSlow371 * fRec226[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm492 = (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + fRec226[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm493 = (2.0879500000000002f * (fTempPerm488 + (fTempPerm463 + fTempPerm492)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm494 = (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + fTempPerm476))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm495 = (2.0879500000000002f * (fTempPerm490 + (fTempPerm494 + fTempPerm463)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm496 = (fTempPerm455 * ftbl0[(((int((65536.0f * (fRec201[0] + fTempPerm462))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm497 = (2.0879500000000002f * (fTempPerm488 + (fTempPerm496 + fTempPerm492)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec227[0] = (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + (fSlow371 * fRec227[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm498 = (fTempPerm461 * ftbl0[(((int((65536.0f * (fRec205[0] + fRec227[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm499 = (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + (fTempPerm488 + fTempPerm482)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm500 = (2.0879500000000002f * (fTempPerm499 + (fTempPerm498 + fTempPerm456)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm501 = (fTempPerm461 * ftbl0[(((int((65536.0f * (fRec205[0] + fTempPerm469))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm502 = (fTempPerm501 + fTempPerm456);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm503 = (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + (fRec225[0] + fTempPerm482)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm504 = (2.0879500000000002f * (fTempPerm503 + fTempPerm502));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm505 = (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + fRec225[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm506 = (2.0879500000000002f * (fTempPerm490 + (fTempPerm505 + fTempPerm470)));
			}
			if (iSlow9) {
				fRec228[0] = (fTempPerm487 * ftbl0[(((int((fTempPerm484 + (fSlow372 * fRec228[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm507 = (2.0879500000000002f * (((fTempPerm463 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + fRec228[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + fRec228[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm481 * ftbl0[(((int((65536.0f * (fRec217[0] + fRec228[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm508 = (2.0879500000000002f * (fTempPerm490 + (fTempPerm502 + fTempPerm505)));
			}
			if (iSlow28 || iSlow11) {
				fRec229[0] = (fTempPerm487 * ftbl0[(((int((fTempPerm484 + (fSlow373 * fRec229[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm509 = (fTempPerm481 * ftbl0[(((int((65536.0f * (fRec217[0] + fRec229[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm510 = ((fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + fRec229[0]))) % 65536) + 65536) % 65536)]) + (2.0879500000000002f * (fTempPerm509 + ((fTempPerm455 * ftbl0[(((int((fTempPerm452 + (136835.89120000001f * fTempPerm462))) % 65536) + 65536) % 65536)]) + (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + fRec229[0]))) % 65536) + 65536) % 65536)])))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm511 = ((fTempPerm455 * ftbl0[(((int((65536.0f * (fRec201[0] + fRec227[0]))) % 65536) + 65536) % 65536)]) + fTempPerm498);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm512 = (fTempPerm481 * ftbl0[(((int((65536.0f * (fRec217[0] + fTempPerm488))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm513 = (2.0879500000000002f * (fTempPerm512 + (fTempPerm511 + (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + fTempPerm488))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm514 = (2.0879500000000002f * (fTempPerm499 + fTempPerm511));
			}
			if (iSlow14) {
				fRec230[0] = (fTempPerm487 * ftbl0[(((int((fTempPerm484 + (fSlow374 * fRec230[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm515 = (fTempPerm455 * ftbl0[(((int((65536.0f * (fRec201[0] + fTempPerm501))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm516 = (2.0879500000000002f * ((fTempPerm515 + (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + fRec230[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm481 * ftbl0[(((int((65536.0f * (fRec217[0] + fRec230[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm517 = (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + fTempPerm512))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm518 = (2.0879500000000002f * (fTempPerm455 * ftbl0[(((int((65536.0f * (fRec201[0] + (fTempPerm517 + (fRec227[0] + fTempPerm462))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec231[0] = (fTempPerm461 * ftbl0[(((int((fTempPerm458 + (fSlow375 * fRec231[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm519 = (2.0879500000000002f * (fTempPerm455 * ftbl0[(((int((65536.0f * (fRec201[0] + (fTempPerm494 + (fRec231[0] + fTempPerm512))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm520 = (2.0879500000000002f * (fTempPerm455 * ftbl0[(((int((65536.0f * (fRec201[0] + (fTempPerm494 + (fTempPerm462 + fTempPerm490))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec232[0] = (fTempPerm461 * ftbl0[(((int((fTempPerm458 + (fSlow374 * fRec232[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm521 = (fTempPerm455 * ftbl0[(((int((65536.0f * (fRec201[0] + fRec232[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm522 = (2.0879500000000002f * (fTempPerm521 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + fTempPerm499))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm523 = (2.0879500000000002f * (fTempPerm496 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + fTempPerm503))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm524 = (2.0879500000000002f * (fTempPerm496 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + (fTempPerm482 + (fRec225[0] + fTempPerm476))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec233[0] = (fTempPerm461 * ftbl0[(((int((fTempPerm458 + (fSlow376 * fRec233[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm525 = (fTempPerm455 * ftbl0[(((int((65536.0f * (fRec201[0] + fRec233[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm526 = (2.0879500000000002f * (fTempPerm525 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + (fTempPerm482 + (fTempPerm488 + fTempPerm476))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec234[0] = (fTempPerm487 * ftbl0[(((int((fTempPerm484 + (fSlow376 * fRec234[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm527 = (2.0879500000000002f * (fTempPerm515 + (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + (fRec234[0] + fTempPerm482)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec235[0] = (fTempPerm468 * ftbl0[(((int((fTempPerm465 + (fSlow376 * fRec235[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm528 = (2.0879500000000002f * (fTempPerm499 + (fTempPerm455 * ftbl0[(((int((65536.0f * (fRec201[0] + (fTempPerm461 * ftbl0[(((int((65536.0f * (fRec205[0] + fRec235[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm529 = (2.0879500000000002f * (fTempPerm521 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + (fTempPerm512 + fTempPerm476)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec236[0] = (fTempPerm475 * ftbl0[(((int((fTempPerm472 + (fSlow373 * fRec236[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm530 = (2.0879500000000002f * (fTempPerm496 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + (fRec236[0] + fTempPerm512)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm531 = (2.0879500000000002f * (fTempPerm496 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + (fTempPerm490 + fTempPerm476)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm532 = (fTempPerm496 + fTempPerm494);
			}
			if (iSlow27) {
				fRec237[0] = (2.0879500000000002f * (fTempPerm481 * ftbl0[(((int((65536.0f * (fRec217[0] + (fTempPerm487 * ftbl0[(((int((65536.0f * (fRec221[0] + (fSlow371 * fRec237[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm533 = (fRec237[0] + (2.0879500000000002f * fTempPerm532));
			}
			if (iSlow28) {
				fTempPerm534 = (2.0879500000000002f * (fTempPerm532 + fTempPerm509));
			}
			if (iSlow29) {
				fRec238[0] = (2.0879500000000002f * (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + (fTempPerm481 * ftbl0[(((int((65536.0f * (fRec217[0] + (fTempPerm487 * ftbl0[(((int((65536.0f * (fRec221[0] + (fSlow371 * fRec238[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm535 = (fRec238[0] + (2.0879500000000002f * fTempPerm515));
			}
			if (iSlow30) {
				fTempPerm536 = (2.0879500000000002f * (fTempPerm515 + (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + fTempPerm490))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm537 = (2.0879500000000002f * (fTempPerm525 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + fTempPerm517))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm538 = (2.0879500000000002f * (fTempPerm496 + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec209[0] + (fTempPerm475 * ftbl0[(((int((65536.0f * (fRec213[0] + (fTempPerm481 * ftbl0[(((int((65536.0f * (fRec217[0] + fRec234[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec240[0] = (iSlow1348 * (iRec240[1] + 1));
			iTempPerm539 = int((iRec240[0] < iSlow381));
			fTempPerm540 = expf((0 - (fConst2 / ((iSlow1350)?((iTempPerm539)?fSlow380:fSlow378):fSlow377))));
			fRec239[0] = ((fRec239[1] * fTempPerm540) + (((iSlow1350)?((iTempPerm539)?1.5873015873015872f:fSlow1538):0.0f) * (1.0f - fTempPerm540)));
			output0[i] = (FAUSTFLOAT)((((((fSlow1311 * (min(1.0f, fRec239[0]) * (((((((((((((((((((((((((((((((fTempPerm538 + fTempPerm537) + fTempPerm536) + fTempPerm535) + fTempPerm534) + fTempPerm533) + fTempPerm531) + fTempPerm530) + fTempPerm529) + fTempPerm528) + fTempPerm527) + fTempPerm526) + fTempPerm524) + fTempPerm523) + fTempPerm522) + fTempPerm520) + fTempPerm519) + fTempPerm518) + fTempPerm516) + fTempPerm514) + fTempPerm513) + fTempPerm510) + fTempPerm508) + fTempPerm507) + fTempPerm506) + fTempPerm504) + fTempPerm500) + fTempPerm497) + fTempPerm495) + fTempPerm493) + fTempPerm491) + fTempPerm489))) + (fSlow1080 * (min(1.0f, fRec199[0]) * (((((((((((((((((((((((((((((((fTempPerm448 + fTempPerm447) + fTempPerm446) + fTempPerm445) + fTempPerm444) + fTempPerm443) + fTempPerm441) + fTempPerm440) + fTempPerm439) + fTempPerm438) + fTempPerm437) + fTempPerm436) + fTempPerm434) + fTempPerm433) + fTempPerm432) + fTempPerm430) + fTempPerm429) + fTempPerm428) + fTempPerm426) + fTempPerm424) + fTempPerm423) + fTempPerm420) + fTempPerm418) + fTempPerm417) + fTempPerm416) + fTempPerm414) + fTempPerm410) + fTempPerm407) + fTempPerm405) + fTempPerm403) + fTempPerm401) + fTempPerm399)))) + (fSlow849 * (min(1.0f, fRec159[0]) * (((((((((((((((((((((((((((((((fTempPerm358 + fTempPerm357) + fTempPerm356) + fTempPerm355) + fTempPerm354) + fTempPerm353) + fTempPerm351) + fTempPerm350) + fTempPerm349) + fTempPerm348) + fTempPerm347) + fTempPerm346) + fTempPerm344) + fTempPerm343) + fTempPerm342) + fTempPerm340) + fTempPerm339) + fTempPerm338) + fTempPerm336) + fTempPerm334) + fTempPerm333) + fTempPerm330) + fTempPerm328) + fTempPerm327) + fTempPerm326) + fTempPerm324) + fTempPerm320) + fTempPerm317) + fTempPerm315) + fTempPerm313) + fTempPerm311) + fTempPerm309)))) + (fSlow618 * (min(1.0f, fRec119[0]) * (((((((((((((((((((((((((((((((fTempPerm268 + fTempPerm267) + fTempPerm266) + fTempPerm265) + fTempPerm264) + fTempPerm263) + fTempPerm261) + fTempPerm260) + fTempPerm259) + fTempPerm258) + fTempPerm257) + fTempPerm256) + fTempPerm254) + fTempPerm253) + fTempPerm252) + fTempPerm250) + fTempPerm249) + fTempPerm248) + fTempPerm246) + fTempPerm244) + fTempPerm243) + fTempPerm240) + fTempPerm238) + fTempPerm237) + fTempPerm236) + fTempPerm234) + fTempPerm230) + fTempPerm227) + fTempPerm225) + fTempPerm223) + fTempPerm221) + fTempPerm219)))) + (fSlow387 * (min(1.0f, fRec79[0]) * (((((((((((((((((((((((((((((((fTempPerm178 + fTempPerm177) + fTempPerm176) + fTempPerm175) + fTempPerm174) + fTempPerm173) + fTempPerm171) + fTempPerm170) + fTempPerm169) + fTempPerm168) + fTempPerm167) + fTempPerm166) + fTempPerm164) + fTempPerm163) + fTempPerm162) + fTempPerm160) + fTempPerm159) + fTempPerm158) + fTempPerm156) + fTempPerm154) + fTempPerm153) + fTempPerm150) + fTempPerm148) + fTempPerm147) + fTempPerm146) + fTempPerm144) + fTempPerm140) + fTempPerm137) + fTempPerm135) + fTempPerm133) + fTempPerm131) + fTempPerm129)))) + (fSlow42 * (min(1.0f, fRec39[0]) * (((((((((((((((((((((((((((((((fTempPerm88 + fTempPerm87) + fTempPerm86) + fTempPerm85) + fTempPerm84) + fTempPerm83) + fTempPerm81) + fTempPerm80) + fTempPerm79) + fTempPerm78) + fTempPerm77) + fTempPerm76) + fTempPerm74) + fTempPerm73) + fTempPerm72) + fTempPerm70) + fTempPerm69) + fTempPerm68) + fTempPerm66) + fTempPerm64) + fTempPerm63) + fTempPerm60) + fTempPerm58) + fTempPerm57) + fTempPerm56) + fTempPerm54) + fTempPerm50) + fTempPerm47) + fTempPerm45) + fTempPerm43) + fTempPerm41) + fTempPerm39))));
			// post processing
			fRec239[1] = fRec239[0];
			iRec240[1] = iRec240[0];
			if (iSlow29) {
				fRec238[1] = fRec238[0];
			}
			if (iSlow27) {
				fRec237[1] = fRec237[0];
			}
			if (iSlow25) {
				fRec236[1] = fRec236[0];
			}
			if (iSlow23) {
				fRec235[1] = fRec235[0];
			}
			if (iSlow32 || iSlow22) {
				fRec234[1] = fRec234[0];
			}
			if (iSlow31 || iSlow21) {
				fRec233[1] = fRec233[0];
			}
			if (iSlow24 || iSlow18) {
				fRec232[1] = fRec232[0];
			}
			if (iSlow16) {
				fRec231[1] = fRec231[0];
			}
			if (iSlow14) {
				fRec230[1] = fRec230[0];
			}
			if (iSlow28 || iSlow11) {
				fRec229[1] = fRec229[0];
			}
			if (iSlow9) {
				fRec228[1] = fRec228[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec227[1] = fRec227[0];
			}
			if (iSlow5 || iSlow3) {
				fRec226[1] = fRec226[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec225[1] = fRec225[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec224[1] = fRec224[0];
				fRec222[1] = fRec222[0];
				fRec223[1] = fRec223[0];
				fRec221[1] = fRec221[0];
				fRec220[1] = fRec220[0];
				fRec218[1] = fRec218[0];
				fRec219[1] = fRec219[0];
				fRec217[1] = fRec217[0];
				fRec216[1] = fRec216[0];
				fRec214[1] = fRec214[0];
				fRec215[1] = fRec215[0];
				fRec213[1] = fRec213[0];
				fRec212[1] = fRec212[0];
				fRec210[1] = fRec210[0];
				fRec211[1] = fRec211[0];
				fRec209[1] = fRec209[0];
				fRec208[1] = fRec208[0];
				fRec206[1] = fRec206[0];
				fRec207[1] = fRec207[0];
				fRec205[1] = fRec205[0];
				fRec204[1] = fRec204[0];
				fRec202[1] = fRec202[0];
				fRec203[1] = fRec203[0];
				fRec201[1] = fRec201[0];
			}
			fRec199[1] = fRec199[0];
			iRec200[1] = iRec200[0];
			if (iSlow29) {
				fRec198[1] = fRec198[0];
			}
			if (iSlow27) {
				fRec197[1] = fRec197[0];
			}
			if (iSlow25) {
				fRec196[1] = fRec196[0];
			}
			if (iSlow23) {
				fRec195[1] = fRec195[0];
			}
			if (iSlow32 || iSlow22) {
				fRec194[1] = fRec194[0];
			}
			if (iSlow31 || iSlow21) {
				fRec193[1] = fRec193[0];
			}
			if (iSlow24 || iSlow18) {
				fRec192[1] = fRec192[0];
			}
			if (iSlow16) {
				fRec191[1] = fRec191[0];
			}
			if (iSlow14) {
				fRec190[1] = fRec190[0];
			}
			if (iSlow28 || iSlow11) {
				fRec189[1] = fRec189[0];
			}
			if (iSlow9) {
				fRec188[1] = fRec188[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec187[1] = fRec187[0];
			}
			if (iSlow5 || iSlow3) {
				fRec186[1] = fRec186[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec185[1] = fRec185[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec184[1] = fRec184[0];
				fRec182[1] = fRec182[0];
				fRec183[1] = fRec183[0];
				fRec181[1] = fRec181[0];
				fRec180[1] = fRec180[0];
				fRec178[1] = fRec178[0];
				fRec179[1] = fRec179[0];
				fRec177[1] = fRec177[0];
				fRec176[1] = fRec176[0];
				fRec174[1] = fRec174[0];
				fRec175[1] = fRec175[0];
				fRec173[1] = fRec173[0];
				fRec172[1] = fRec172[0];
				fRec170[1] = fRec170[0];
				fRec171[1] = fRec171[0];
				fRec169[1] = fRec169[0];
				fRec168[1] = fRec168[0];
				fRec166[1] = fRec166[0];
				fRec167[1] = fRec167[0];
				fRec165[1] = fRec165[0];
				fRec164[1] = fRec164[0];
				fRec162[1] = fRec162[0];
				fRec163[1] = fRec163[0];
				fRec161[1] = fRec161[0];
			}
			fRec159[1] = fRec159[0];
			iRec160[1] = iRec160[0];
			if (iSlow29) {
				fRec158[1] = fRec158[0];
			}
			if (iSlow27) {
				fRec157[1] = fRec157[0];
			}
			if (iSlow25) {
				fRec156[1] = fRec156[0];
			}
			if (iSlow23) {
				fRec155[1] = fRec155[0];
			}
			if (iSlow32 || iSlow22) {
				fRec154[1] = fRec154[0];
			}
			if (iSlow31 || iSlow21) {
				fRec153[1] = fRec153[0];
			}
			if (iSlow24 || iSlow18) {
				fRec152[1] = fRec152[0];
			}
			if (iSlow16) {
				fRec151[1] = fRec151[0];
			}
			if (iSlow14) {
				fRec150[1] = fRec150[0];
			}
			if (iSlow28 || iSlow11) {
				fRec149[1] = fRec149[0];
			}
			if (iSlow9) {
				fRec148[1] = fRec148[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec147[1] = fRec147[0];
			}
			if (iSlow5 || iSlow3) {
				fRec146[1] = fRec146[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec145[1] = fRec145[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec144[1] = fRec144[0];
				fRec142[1] = fRec142[0];
				fRec143[1] = fRec143[0];
				fRec141[1] = fRec141[0];
				fRec140[1] = fRec140[0];
				fRec138[1] = fRec138[0];
				fRec139[1] = fRec139[0];
				fRec137[1] = fRec137[0];
				fRec136[1] = fRec136[0];
				fRec134[1] = fRec134[0];
				fRec135[1] = fRec135[0];
				fRec133[1] = fRec133[0];
				fRec132[1] = fRec132[0];
				fRec130[1] = fRec130[0];
				fRec131[1] = fRec131[0];
				fRec129[1] = fRec129[0];
				fRec128[1] = fRec128[0];
				fRec126[1] = fRec126[0];
				fRec127[1] = fRec127[0];
				fRec125[1] = fRec125[0];
				fRec124[1] = fRec124[0];
				fRec122[1] = fRec122[0];
				fRec123[1] = fRec123[0];
				fRec121[1] = fRec121[0];
			}
			fRec119[1] = fRec119[0];
			iRec120[1] = iRec120[0];
			if (iSlow29) {
				fRec118[1] = fRec118[0];
			}
			if (iSlow27) {
				fRec117[1] = fRec117[0];
			}
			if (iSlow25) {
				fRec116[1] = fRec116[0];
			}
			if (iSlow23) {
				fRec115[1] = fRec115[0];
			}
			if (iSlow32 || iSlow22) {
				fRec114[1] = fRec114[0];
			}
			if (iSlow31 || iSlow21) {
				fRec113[1] = fRec113[0];
			}
			if (iSlow24 || iSlow18) {
				fRec112[1] = fRec112[0];
			}
			if (iSlow16) {
				fRec111[1] = fRec111[0];
			}
			if (iSlow14) {
				fRec110[1] = fRec110[0];
			}
			if (iSlow28 || iSlow11) {
				fRec109[1] = fRec109[0];
			}
			if (iSlow9) {
				fRec108[1] = fRec108[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec107[1] = fRec107[0];
			}
			if (iSlow5 || iSlow3) {
				fRec106[1] = fRec106[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec105[1] = fRec105[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec104[1] = fRec104[0];
				fRec102[1] = fRec102[0];
				fRec103[1] = fRec103[0];
				fRec101[1] = fRec101[0];
				fRec100[1] = fRec100[0];
				fRec98[1] = fRec98[0];
				fRec99[1] = fRec99[0];
				fRec97[1] = fRec97[0];
				fRec96[1] = fRec96[0];
				fRec94[1] = fRec94[0];
				fRec95[1] = fRec95[0];
				fRec93[1] = fRec93[0];
				fRec92[1] = fRec92[0];
				fRec90[1] = fRec90[0];
				fRec91[1] = fRec91[0];
				fRec89[1] = fRec89[0];
				fRec88[1] = fRec88[0];
				fRec86[1] = fRec86[0];
				fRec87[1] = fRec87[0];
				fRec85[1] = fRec85[0];
				fRec84[1] = fRec84[0];
				fRec82[1] = fRec82[0];
				fRec83[1] = fRec83[0];
				fRec81[1] = fRec81[0];
			}
			fRec79[1] = fRec79[0];
			iRec80[1] = iRec80[0];
			if (iSlow29) {
				fRec78[1] = fRec78[0];
			}
			if (iSlow27) {
				fRec77[1] = fRec77[0];
			}
			if (iSlow25) {
				fRec76[1] = fRec76[0];
			}
			if (iSlow23) {
				fRec75[1] = fRec75[0];
			}
			if (iSlow32 || iSlow22) {
				fRec74[1] = fRec74[0];
			}
			if (iSlow31 || iSlow21) {
				fRec73[1] = fRec73[0];
			}
			if (iSlow24 || iSlow18) {
				fRec72[1] = fRec72[0];
			}
			if (iSlow16) {
				fRec71[1] = fRec71[0];
			}
			if (iSlow14) {
				fRec70[1] = fRec70[0];
			}
			if (iSlow28 || iSlow11) {
				fRec69[1] = fRec69[0];
			}
			if (iSlow9) {
				fRec68[1] = fRec68[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec67[1] = fRec67[0];
			}
			if (iSlow5 || iSlow3) {
				fRec66[1] = fRec66[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec65[1] = fRec65[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec64[1] = fRec64[0];
				fRec62[1] = fRec62[0];
				fRec63[1] = fRec63[0];
				fRec61[1] = fRec61[0];
				fRec60[1] = fRec60[0];
				fRec58[1] = fRec58[0];
				fRec59[1] = fRec59[0];
				fRec57[1] = fRec57[0];
				fRec56[1] = fRec56[0];
				fRec54[1] = fRec54[0];
				fRec55[1] = fRec55[0];
				fRec53[1] = fRec53[0];
				fRec52[1] = fRec52[0];
				fRec50[1] = fRec50[0];
				fRec51[1] = fRec51[0];
				fRec49[1] = fRec49[0];
				fRec48[1] = fRec48[0];
				fRec46[1] = fRec46[0];
				fRec47[1] = fRec47[0];
				fRec45[1] = fRec45[0];
				fRec44[1] = fRec44[0];
				fRec42[1] = fRec42[0];
				fRec43[1] = fRec43[0];
				fRec41[1] = fRec41[0];
			}
			fRec39[1] = fRec39[0];
			iRec40[1] = iRec40[0];
			if (iSlow29) {
				fRec38[1] = fRec38[0];
			}
			if (iSlow27) {
				fRec37[1] = fRec37[0];
			}
			if (iSlow25) {
				fRec36[1] = fRec36[0];
			}
			if (iSlow23) {
				fRec35[1] = fRec35[0];
			}
			if (iSlow32 || iSlow22) {
				fRec34[1] = fRec34[0];
			}
			if (iSlow31 || iSlow21) {
				fRec33[1] = fRec33[0];
			}
			if (iSlow24 || iSlow18) {
				fRec32[1] = fRec32[0];
			}
			if (iSlow16) {
				fRec31[1] = fRec31[0];
			}
			if (iSlow14) {
				fRec30[1] = fRec30[0];
			}
			if (iSlow28 || iSlow11) {
				fRec29[1] = fRec29[0];
			}
			if (iSlow9) {
				fRec28[1] = fRec28[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec27[1] = fRec27[0];
			}
			if (iSlow5 || iSlow3) {
				fRec26[1] = fRec26[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec25[1] = fRec25[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec24[1] = fRec24[0];
				fRec22[1] = fRec22[0];
				fRec23[1] = fRec23[0];
				fRec21[1] = fRec21[0];
				fRec20[1] = fRec20[0];
				fRec18[1] = fRec18[0];
				fRec19[1] = fRec19[0];
				fRec17[1] = fRec17[0];
				fRec16[1] = fRec16[0];
				fRec14[1] = fRec14[0];
				fRec15[1] = fRec15[0];
				fRec13[1] = fRec13[0];
				fRec12[1] = fRec12[0];
				fRec10[1] = fRec10[0];
				fRec11[1] = fRec11[0];
				fRec9[1] = fRec9[0];
				fRec8[1] = fRec8[0];
				fRec6[1] = fRec6[0];
				fRec7[1] = fRec7[0];
				fRec5[1] = fRec5[0];
				fRec4[1] = fRec4[0];
				fRec2[1] = fRec2[0];
				fRec3[1] = fRec3[0];
				fRec1[1] = fRec1[0];
			}
		}
	}
};


float 	faust_dxotto::ftbl0[65536];
