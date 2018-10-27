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
	float 	fConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fbutton0;
	float 	fRec3[2];
	int 	iTempPerm2;
	int 	iTempPerm3;
	float 	fRec2[2];
	float 	fConst2;
	float 	fRec4[2];
	float 	fConst3;
	int 	iTempPerm4;
	int 	iTempPerm5;
	float 	fTempPerm6;
	float 	fTempPerm7;
	float 	fConst4;
	float 	fRec5[2];
	float 	fTempPerm8;
	FAUSTFLOAT 	fslider4;
	float 	fRec7[2];
	int 	iTempPerm9;
	int 	iTempPerm10;
	float 	fRec6[2];
	float 	fTempPerm11;
	float 	fTempPerm12;
	float 	fTempPerm13;
	float 	fRec8[2];
	float 	fTempPerm14;
	float 	fTempPerm15;
	FAUSTFLOAT 	fslider5;
	float 	fRec10[2];
	int 	iTempPerm16;
	int 	iTempPerm17;
	float 	fRec9[2];
	float 	fTempPerm18;
	float 	fTempPerm19;
	float 	fTempPerm20;
	FAUSTFLOAT 	fslider6;
	float 	fRec12[2];
	int 	iTempPerm21;
	int 	iTempPerm22;
	float 	fRec11[2];
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider7;
	float 	fRec15[2];
	int 	iTempPerm26;
	float 	fConst5;
	int 	iTempPerm27;
	float 	fRec14[2];
	float 	fTempPerm28;
	float 	fTempPerm29;
	float 	fRec16[2];
	float 	fTempPerm30;
	FAUSTFLOAT 	fslider8;
	float 	fRec18[2];
	int 	iTempPerm31;
	int 	iTempPerm32;
	float 	fRec17[2];
	float 	fTempPerm33;
	float 	fTempPerm34;
	float 	fTempPerm35;
	FAUSTFLOAT 	fslider9;
	float 	fRec19[2];
	float 	fTempPerm36;
	float 	fTempPerm37;
	float 	fRec20[2];
	float 	fTempPerm38;
	float 	fTempPerm39;
	float 	fTempPerm40;
	float 	fTempPerm41;
	float 	fTempPerm42;
	float 	fTempPerm43;
	float 	fRec21[2];
	float 	fTempPerm44;
	float 	fTempPerm45;
	float 	fTempPerm46;
	float 	fTempPerm47;
	float 	fTempPerm48;
	float 	fTempPerm49;
	float 	fTempPerm50;
	float 	fTempPerm51;
	float 	fTempPerm52;
	float 	fRec22[2];
	float 	fTempPerm53;
	float 	fTempPerm54;
	float 	fTempPerm55;
	float 	fRec23[2];
	float 	fTempPerm56;
	float 	fTempPerm57;
	float 	fTempPerm58;
	float 	fTempPerm59;
	float 	fTempPerm60;
	float 	fTempPerm61;
	float 	fRec24[2];
	float 	fTempPerm62;
	float 	fTempPerm63;
	float 	fTempPerm64;
	float 	fTempPerm65;
	float 	fRec25[2];
	float 	fTempPerm66;
	float 	fTempPerm67;
	float 	fRec26[2];
	float 	fTempPerm68;
	float 	fTempPerm69;
	float 	fTempPerm70;
	float 	fTempPerm71;
	float 	fRec27[2];
	float 	fTempPerm72;
	float 	fTempPerm73;
	float 	fRec28[2];
	float 	fTempPerm74;
	float 	fRec29[2];
	float 	fTempPerm75;
	float 	fTempPerm76;
	float 	fRec30[2];
	float 	fTempPerm77;
	float 	fTempPerm78;
	float 	fTempPerm79;
	float 	fRec31[2];
	float 	fTempPerm80;
	float 	fTempPerm81;
	float 	fRec32[2];
	float 	fTempPerm82;
	float 	fTempPerm83;
	float 	fTempPerm84;
	float 	fTempPerm85;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	int 	iRec34[2];
	int 	iTempPerm86;
	float 	fConst6;
	float 	fTempPerm87;
	FAUSTFLOAT 	fslider13;
	float 	fRec33[2];
	FAUSTFLOAT 	fslider14;
	float 	fRec35[2];
	float 	fTempPerm88;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fbutton1;
	float 	fRec37[2];
	int 	iTempPerm89;
	int 	iTempPerm90;
	float 	fRec36[2];
	float 	fRec38[2];
	int 	iTempPerm91;
	int 	iTempPerm92;
	float 	fTempPerm93;
	float 	fTempPerm94;
	float 	fRec39[2];
	float 	fTempPerm95;
	float 	fRec41[2];
	int 	iTempPerm96;
	int 	iTempPerm97;
	float 	fRec40[2];
	float 	fTempPerm98;
	float 	fTempPerm99;
	float 	fTempPerm100;
	float 	fRec42[2];
	float 	fTempPerm101;
	float 	fTempPerm102;
	float 	fRec44[2];
	int 	iTempPerm103;
	int 	iTempPerm104;
	float 	fRec43[2];
	float 	fTempPerm105;
	float 	fTempPerm106;
	float 	fTempPerm107;
	float 	fRec46[2];
	int 	iTempPerm108;
	int 	iTempPerm109;
	float 	fRec45[2];
	float 	fTempPerm110;
	float 	fTempPerm111;
	float 	fTempPerm112;
	float 	fRec47[2];
	float 	fRec49[2];
	int 	iTempPerm113;
	int 	iTempPerm114;
	float 	fRec48[2];
	float 	fTempPerm115;
	float 	fTempPerm116;
	float 	fRec50[2];
	float 	fTempPerm117;
	float 	fRec52[2];
	int 	iTempPerm118;
	int 	iTempPerm119;
	float 	fRec51[2];
	float 	fTempPerm120;
	float 	fTempPerm121;
	float 	fTempPerm122;
	float 	fRec53[2];
	float 	fTempPerm123;
	float 	fTempPerm124;
	float 	fRec54[2];
	float 	fTempPerm125;
	float 	fTempPerm126;
	float 	fTempPerm127;
	float 	fTempPerm128;
	float 	fTempPerm129;
	float 	fTempPerm130;
	float 	fRec55[2];
	float 	fTempPerm131;
	float 	fTempPerm132;
	float 	fTempPerm133;
	float 	fTempPerm134;
	float 	fTempPerm135;
	float 	fTempPerm136;
	float 	fTempPerm137;
	float 	fTempPerm138;
	float 	fTempPerm139;
	float 	fRec56[2];
	float 	fTempPerm140;
	float 	fTempPerm141;
	float 	fTempPerm142;
	float 	fRec57[2];
	float 	fTempPerm143;
	float 	fTempPerm144;
	float 	fTempPerm145;
	float 	fTempPerm146;
	float 	fTempPerm147;
	float 	fTempPerm148;
	float 	fRec58[2];
	float 	fTempPerm149;
	float 	fTempPerm150;
	float 	fTempPerm151;
	float 	fTempPerm152;
	float 	fRec59[2];
	float 	fTempPerm153;
	float 	fTempPerm154;
	float 	fRec60[2];
	float 	fTempPerm155;
	float 	fTempPerm156;
	float 	fTempPerm157;
	float 	fTempPerm158;
	float 	fRec61[2];
	float 	fTempPerm159;
	float 	fTempPerm160;
	float 	fRec62[2];
	float 	fTempPerm161;
	float 	fRec63[2];
	float 	fTempPerm162;
	float 	fTempPerm163;
	float 	fRec64[2];
	float 	fTempPerm164;
	float 	fTempPerm165;
	float 	fTempPerm166;
	float 	fRec65[2];
	float 	fTempPerm167;
	float 	fTempPerm168;
	float 	fRec66[2];
	float 	fTempPerm169;
	float 	fTempPerm170;
	float 	fTempPerm171;
	float 	fTempPerm172;
	int 	iRec68[2];
	int 	iTempPerm173;
	float 	fTempPerm174;
	float 	fRec67[2];
	FAUSTFLOAT 	fslider16;
	float 	fRec69[2];
	float 	fTempPerm175;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fbutton2;
	float 	fRec71[2];
	int 	iTempPerm176;
	int 	iTempPerm177;
	float 	fRec70[2];
	float 	fRec72[2];
	int 	iTempPerm178;
	int 	iTempPerm179;
	float 	fTempPerm180;
	float 	fTempPerm181;
	float 	fRec73[2];
	float 	fTempPerm182;
	float 	fRec75[2];
	int 	iTempPerm183;
	int 	iTempPerm184;
	float 	fRec74[2];
	float 	fTempPerm185;
	float 	fTempPerm186;
	float 	fTempPerm187;
	float 	fRec76[2];
	float 	fTempPerm188;
	float 	fTempPerm189;
	float 	fRec78[2];
	int 	iTempPerm190;
	int 	iTempPerm191;
	float 	fRec77[2];
	float 	fTempPerm192;
	float 	fTempPerm193;
	float 	fTempPerm194;
	float 	fRec80[2];
	int 	iTempPerm195;
	int 	iTempPerm196;
	float 	fRec79[2];
	float 	fTempPerm197;
	float 	fTempPerm198;
	float 	fTempPerm199;
	float 	fRec81[2];
	float 	fRec83[2];
	int 	iTempPerm200;
	int 	iTempPerm201;
	float 	fRec82[2];
	float 	fTempPerm202;
	float 	fTempPerm203;
	float 	fRec84[2];
	float 	fTempPerm204;
	float 	fRec86[2];
	int 	iTempPerm205;
	int 	iTempPerm206;
	float 	fRec85[2];
	float 	fTempPerm207;
	float 	fTempPerm208;
	float 	fTempPerm209;
	float 	fRec87[2];
	float 	fTempPerm210;
	float 	fTempPerm211;
	float 	fRec88[2];
	float 	fTempPerm212;
	float 	fTempPerm213;
	float 	fTempPerm214;
	float 	fTempPerm215;
	float 	fTempPerm216;
	float 	fTempPerm217;
	float 	fRec89[2];
	float 	fTempPerm218;
	float 	fTempPerm219;
	float 	fTempPerm220;
	float 	fTempPerm221;
	float 	fTempPerm222;
	float 	fTempPerm223;
	float 	fTempPerm224;
	float 	fTempPerm225;
	float 	fTempPerm226;
	float 	fRec90[2];
	float 	fTempPerm227;
	float 	fTempPerm228;
	float 	fTempPerm229;
	float 	fRec91[2];
	float 	fTempPerm230;
	float 	fTempPerm231;
	float 	fTempPerm232;
	float 	fTempPerm233;
	float 	fTempPerm234;
	float 	fTempPerm235;
	float 	fRec92[2];
	float 	fTempPerm236;
	float 	fTempPerm237;
	float 	fTempPerm238;
	float 	fTempPerm239;
	float 	fRec93[2];
	float 	fTempPerm240;
	float 	fTempPerm241;
	float 	fRec94[2];
	float 	fTempPerm242;
	float 	fTempPerm243;
	float 	fTempPerm244;
	float 	fTempPerm245;
	float 	fRec95[2];
	float 	fTempPerm246;
	float 	fTempPerm247;
	float 	fRec96[2];
	float 	fTempPerm248;
	float 	fRec97[2];
	float 	fTempPerm249;
	float 	fTempPerm250;
	float 	fRec98[2];
	float 	fTempPerm251;
	float 	fTempPerm252;
	float 	fTempPerm253;
	float 	fRec99[2];
	float 	fTempPerm254;
	float 	fTempPerm255;
	float 	fRec100[2];
	float 	fTempPerm256;
	float 	fTempPerm257;
	float 	fTempPerm258;
	float 	fTempPerm259;
	int 	iRec102[2];
	int 	iTempPerm260;
	float 	fTempPerm261;
	float 	fRec101[2];
	FAUSTFLOAT 	fslider18;
	float 	fRec103[2];
	float 	fTempPerm262;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fbutton3;
	float 	fRec105[2];
	int 	iTempPerm263;
	int 	iTempPerm264;
	float 	fRec104[2];
	float 	fRec106[2];
	int 	iTempPerm265;
	int 	iTempPerm266;
	float 	fTempPerm267;
	float 	fTempPerm268;
	float 	fRec107[2];
	float 	fTempPerm269;
	float 	fRec109[2];
	int 	iTempPerm270;
	int 	iTempPerm271;
	float 	fRec108[2];
	float 	fTempPerm272;
	float 	fTempPerm273;
	float 	fTempPerm274;
	float 	fRec110[2];
	float 	fTempPerm275;
	float 	fTempPerm276;
	float 	fRec112[2];
	int 	iTempPerm277;
	int 	iTempPerm278;
	float 	fRec111[2];
	float 	fTempPerm279;
	float 	fTempPerm280;
	float 	fTempPerm281;
	float 	fRec114[2];
	int 	iTempPerm282;
	int 	iTempPerm283;
	float 	fRec113[2];
	float 	fTempPerm284;
	float 	fTempPerm285;
	float 	fTempPerm286;
	float 	fRec115[2];
	float 	fRec117[2];
	int 	iTempPerm287;
	int 	iTempPerm288;
	float 	fRec116[2];
	float 	fTempPerm289;
	float 	fTempPerm290;
	float 	fRec118[2];
	float 	fTempPerm291;
	float 	fRec120[2];
	int 	iTempPerm292;
	int 	iTempPerm293;
	float 	fRec119[2];
	float 	fTempPerm294;
	float 	fTempPerm295;
	float 	fTempPerm296;
	float 	fRec121[2];
	float 	fTempPerm297;
	float 	fTempPerm298;
	float 	fRec122[2];
	float 	fTempPerm299;
	float 	fTempPerm300;
	float 	fTempPerm301;
	float 	fTempPerm302;
	float 	fTempPerm303;
	float 	fTempPerm304;
	float 	fRec123[2];
	float 	fTempPerm305;
	float 	fTempPerm306;
	float 	fTempPerm307;
	float 	fTempPerm308;
	float 	fTempPerm309;
	float 	fTempPerm310;
	float 	fTempPerm311;
	float 	fTempPerm312;
	float 	fTempPerm313;
	float 	fRec124[2];
	float 	fTempPerm314;
	float 	fTempPerm315;
	float 	fTempPerm316;
	float 	fRec125[2];
	float 	fTempPerm317;
	float 	fTempPerm318;
	float 	fTempPerm319;
	float 	fTempPerm320;
	float 	fTempPerm321;
	float 	fTempPerm322;
	float 	fRec126[2];
	float 	fTempPerm323;
	float 	fTempPerm324;
	float 	fTempPerm325;
	float 	fTempPerm326;
	float 	fRec127[2];
	float 	fTempPerm327;
	float 	fTempPerm328;
	float 	fRec128[2];
	float 	fTempPerm329;
	float 	fTempPerm330;
	float 	fTempPerm331;
	float 	fTempPerm332;
	float 	fRec129[2];
	float 	fTempPerm333;
	float 	fTempPerm334;
	float 	fRec130[2];
	float 	fTempPerm335;
	float 	fRec131[2];
	float 	fTempPerm336;
	float 	fTempPerm337;
	float 	fRec132[2];
	float 	fTempPerm338;
	float 	fTempPerm339;
	float 	fTempPerm340;
	float 	fRec133[2];
	float 	fTempPerm341;
	float 	fTempPerm342;
	float 	fRec134[2];
	float 	fTempPerm343;
	float 	fTempPerm344;
	float 	fTempPerm345;
	float 	fTempPerm346;
	int 	iRec136[2];
	int 	iTempPerm347;
	float 	fTempPerm348;
	float 	fRec135[2];
	FAUSTFLOAT 	fslider20;
	float 	fRec137[2];
	float 	fTempPerm349;
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fbutton4;
	float 	fRec139[2];
	int 	iTempPerm350;
	int 	iTempPerm351;
	float 	fRec138[2];
	float 	fRec140[2];
	int 	iTempPerm352;
	int 	iTempPerm353;
	float 	fTempPerm354;
	float 	fTempPerm355;
	float 	fRec141[2];
	float 	fTempPerm356;
	float 	fRec143[2];
	int 	iTempPerm357;
	int 	iTempPerm358;
	float 	fRec142[2];
	float 	fTempPerm359;
	float 	fTempPerm360;
	float 	fTempPerm361;
	float 	fRec144[2];
	float 	fTempPerm362;
	float 	fTempPerm363;
	float 	fRec146[2];
	int 	iTempPerm364;
	int 	iTempPerm365;
	float 	fRec145[2];
	float 	fTempPerm366;
	float 	fTempPerm367;
	float 	fTempPerm368;
	float 	fRec148[2];
	int 	iTempPerm369;
	int 	iTempPerm370;
	float 	fRec147[2];
	float 	fTempPerm371;
	float 	fTempPerm372;
	float 	fTempPerm373;
	float 	fRec149[2];
	float 	fRec151[2];
	int 	iTempPerm374;
	int 	iTempPerm375;
	float 	fRec150[2];
	float 	fTempPerm376;
	float 	fTempPerm377;
	float 	fRec152[2];
	float 	fTempPerm378;
	float 	fRec154[2];
	int 	iTempPerm379;
	int 	iTempPerm380;
	float 	fRec153[2];
	float 	fTempPerm381;
	float 	fTempPerm382;
	float 	fTempPerm383;
	float 	fRec155[2];
	float 	fTempPerm384;
	float 	fTempPerm385;
	float 	fRec156[2];
	float 	fTempPerm386;
	float 	fTempPerm387;
	float 	fTempPerm388;
	float 	fTempPerm389;
	float 	fTempPerm390;
	float 	fTempPerm391;
	float 	fRec157[2];
	float 	fTempPerm392;
	float 	fTempPerm393;
	float 	fTempPerm394;
	float 	fTempPerm395;
	float 	fTempPerm396;
	float 	fTempPerm397;
	float 	fTempPerm398;
	float 	fTempPerm399;
	float 	fTempPerm400;
	float 	fRec158[2];
	float 	fTempPerm401;
	float 	fTempPerm402;
	float 	fTempPerm403;
	float 	fRec159[2];
	float 	fTempPerm404;
	float 	fTempPerm405;
	float 	fTempPerm406;
	float 	fTempPerm407;
	float 	fTempPerm408;
	float 	fTempPerm409;
	float 	fRec160[2];
	float 	fTempPerm410;
	float 	fTempPerm411;
	float 	fTempPerm412;
	float 	fTempPerm413;
	float 	fRec161[2];
	float 	fTempPerm414;
	float 	fTempPerm415;
	float 	fRec162[2];
	float 	fTempPerm416;
	float 	fTempPerm417;
	float 	fTempPerm418;
	float 	fTempPerm419;
	float 	fRec163[2];
	float 	fTempPerm420;
	float 	fTempPerm421;
	float 	fRec164[2];
	float 	fTempPerm422;
	float 	fRec165[2];
	float 	fTempPerm423;
	float 	fTempPerm424;
	float 	fRec166[2];
	float 	fTempPerm425;
	float 	fTempPerm426;
	float 	fTempPerm427;
	float 	fRec167[2];
	float 	fTempPerm428;
	float 	fTempPerm429;
	float 	fRec168[2];
	float 	fTempPerm430;
	float 	fTempPerm431;
	float 	fTempPerm432;
	float 	fTempPerm433;
	int 	iRec170[2];
	int 	iTempPerm434;
	float 	fTempPerm435;
	float 	fRec169[2];
	FAUSTFLOAT 	fslider22;
	float 	fRec171[2];
	float 	fTempPerm436;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fbutton5;
	float 	fRec173[2];
	int 	iTempPerm437;
	int 	iTempPerm438;
	float 	fRec172[2];
	float 	fRec174[2];
	int 	iTempPerm439;
	int 	iTempPerm440;
	float 	fTempPerm441;
	float 	fTempPerm442;
	float 	fRec175[2];
	float 	fTempPerm443;
	float 	fRec177[2];
	int 	iTempPerm444;
	int 	iTempPerm445;
	float 	fRec176[2];
	float 	fTempPerm446;
	float 	fTempPerm447;
	float 	fTempPerm448;
	float 	fRec178[2];
	float 	fTempPerm449;
	float 	fTempPerm450;
	float 	fRec180[2];
	int 	iTempPerm451;
	int 	iTempPerm452;
	float 	fRec179[2];
	float 	fTempPerm453;
	float 	fTempPerm454;
	float 	fTempPerm455;
	float 	fRec182[2];
	int 	iTempPerm456;
	int 	iTempPerm457;
	float 	fRec181[2];
	float 	fTempPerm458;
	float 	fTempPerm459;
	float 	fTempPerm460;
	float 	fRec183[2];
	float 	fRec185[2];
	int 	iTempPerm461;
	int 	iTempPerm462;
	float 	fRec184[2];
	float 	fTempPerm463;
	float 	fTempPerm464;
	float 	fRec186[2];
	float 	fTempPerm465;
	float 	fRec188[2];
	int 	iTempPerm466;
	int 	iTempPerm467;
	float 	fRec187[2];
	float 	fTempPerm468;
	float 	fTempPerm469;
	float 	fTempPerm470;
	float 	fRec189[2];
	float 	fTempPerm471;
	float 	fTempPerm472;
	float 	fRec190[2];
	float 	fTempPerm473;
	float 	fTempPerm474;
	float 	fTempPerm475;
	float 	fTempPerm476;
	float 	fTempPerm477;
	float 	fTempPerm478;
	float 	fRec191[2];
	float 	fTempPerm479;
	float 	fTempPerm480;
	float 	fTempPerm481;
	float 	fTempPerm482;
	float 	fTempPerm483;
	float 	fTempPerm484;
	float 	fTempPerm485;
	float 	fTempPerm486;
	float 	fTempPerm487;
	float 	fRec192[2];
	float 	fTempPerm488;
	float 	fTempPerm489;
	float 	fTempPerm490;
	float 	fRec193[2];
	float 	fTempPerm491;
	float 	fTempPerm492;
	float 	fTempPerm493;
	float 	fTempPerm494;
	float 	fTempPerm495;
	float 	fTempPerm496;
	float 	fRec194[2];
	float 	fTempPerm497;
	float 	fTempPerm498;
	float 	fTempPerm499;
	float 	fTempPerm500;
	float 	fRec195[2];
	float 	fTempPerm501;
	float 	fTempPerm502;
	float 	fRec196[2];
	float 	fTempPerm503;
	float 	fTempPerm504;
	float 	fTempPerm505;
	float 	fTempPerm506;
	float 	fRec197[2];
	float 	fTempPerm507;
	float 	fTempPerm508;
	float 	fRec198[2];
	float 	fTempPerm509;
	float 	fRec199[2];
	float 	fTempPerm510;
	float 	fTempPerm511;
	float 	fRec200[2];
	float 	fTempPerm512;
	float 	fTempPerm513;
	float 	fTempPerm514;
	float 	fRec201[2];
	float 	fTempPerm515;
	float 	fTempPerm516;
	float 	fRec202[2];
	float 	fTempPerm517;
	float 	fTempPerm518;
	float 	fTempPerm519;
	float 	fTempPerm520;
	int 	iRec204[2];
	int 	iTempPerm521;
	float 	fTempPerm522;
	float 	fRec203[2];
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
		iTempPerm2 = 0;
		iTempPerm3 = 0;
		fConst2 = (0.001f * fConst0);
		fConst3 = (1000.0f / fConst0);
		iTempPerm4 = 0;
		iTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fConst4 = (14.0f / fConst0);
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
		iTempPerm21 = 0;
		iTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		iTempPerm26 = 0;
		fConst5 = (99.0f / fConst0);
		iTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		iTempPerm31 = 0;
		iTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
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
		iTempPerm86 = 0;
		fConst6 = (6.9100000000000001f / fConst0);
		fTempPerm87 = 0;
		fTempPerm88 = 0;
		iTempPerm89 = 0;
		iTempPerm90 = 0;
		iTempPerm91 = 0;
		iTempPerm92 = 0;
		fTempPerm93 = 0;
		fTempPerm94 = 0;
		fTempPerm95 = 0;
		iTempPerm96 = 0;
		iTempPerm97 = 0;
		fTempPerm98 = 0;
		fTempPerm99 = 0;
		fTempPerm100 = 0;
		fTempPerm101 = 0;
		fTempPerm102 = 0;
		iTempPerm103 = 0;
		iTempPerm104 = 0;
		fTempPerm105 = 0;
		fTempPerm106 = 0;
		fTempPerm107 = 0;
		iTempPerm108 = 0;
		iTempPerm109 = 0;
		fTempPerm110 = 0;
		fTempPerm111 = 0;
		fTempPerm112 = 0;
		iTempPerm113 = 0;
		iTempPerm114 = 0;
		fTempPerm115 = 0;
		fTempPerm116 = 0;
		fTempPerm117 = 0;
		iTempPerm118 = 0;
		iTempPerm119 = 0;
		fTempPerm120 = 0;
		fTempPerm121 = 0;
		fTempPerm122 = 0;
		fTempPerm123 = 0;
		fTempPerm124 = 0;
		fTempPerm125 = 0;
		fTempPerm126 = 0;
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
		iTempPerm173 = 0;
		fTempPerm174 = 0;
		fTempPerm175 = 0;
		iTempPerm176 = 0;
		iTempPerm177 = 0;
		iTempPerm178 = 0;
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
		fTempPerm189 = 0;
		iTempPerm190 = 0;
		iTempPerm191 = 0;
		fTempPerm192 = 0;
		fTempPerm193 = 0;
		fTempPerm194 = 0;
		iTempPerm195 = 0;
		iTempPerm196 = 0;
		fTempPerm197 = 0;
		fTempPerm198 = 0;
		fTempPerm199 = 0;
		iTempPerm200 = 0;
		iTempPerm201 = 0;
		fTempPerm202 = 0;
		fTempPerm203 = 0;
		fTempPerm204 = 0;
		iTempPerm205 = 0;
		iTempPerm206 = 0;
		fTempPerm207 = 0;
		fTempPerm208 = 0;
		fTempPerm209 = 0;
		fTempPerm210 = 0;
		fTempPerm211 = 0;
		fTempPerm212 = 0;
		fTempPerm213 = 0;
		fTempPerm214 = 0;
		fTempPerm215 = 0;
		fTempPerm216 = 0;
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
		iTempPerm260 = 0;
		fTempPerm261 = 0;
		fTempPerm262 = 0;
		iTempPerm263 = 0;
		iTempPerm264 = 0;
		iTempPerm265 = 0;
		iTempPerm266 = 0;
		fTempPerm267 = 0;
		fTempPerm268 = 0;
		fTempPerm269 = 0;
		iTempPerm270 = 0;
		iTempPerm271 = 0;
		fTempPerm272 = 0;
		fTempPerm273 = 0;
		fTempPerm274 = 0;
		fTempPerm275 = 0;
		fTempPerm276 = 0;
		iTempPerm277 = 0;
		iTempPerm278 = 0;
		fTempPerm279 = 0;
		fTempPerm280 = 0;
		fTempPerm281 = 0;
		iTempPerm282 = 0;
		iTempPerm283 = 0;
		fTempPerm284 = 0;
		fTempPerm285 = 0;
		fTempPerm286 = 0;
		iTempPerm287 = 0;
		iTempPerm288 = 0;
		fTempPerm289 = 0;
		fTempPerm290 = 0;
		fTempPerm291 = 0;
		iTempPerm292 = 0;
		iTempPerm293 = 0;
		fTempPerm294 = 0;
		fTempPerm295 = 0;
		fTempPerm296 = 0;
		fTempPerm297 = 0;
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
		iTempPerm347 = 0;
		fTempPerm348 = 0;
		fTempPerm349 = 0;
		iTempPerm350 = 0;
		iTempPerm351 = 0;
		iTempPerm352 = 0;
		iTempPerm353 = 0;
		fTempPerm354 = 0;
		fTempPerm355 = 0;
		fTempPerm356 = 0;
		iTempPerm357 = 0;
		iTempPerm358 = 0;
		fTempPerm359 = 0;
		fTempPerm360 = 0;
		fTempPerm361 = 0;
		fTempPerm362 = 0;
		fTempPerm363 = 0;
		iTempPerm364 = 0;
		iTempPerm365 = 0;
		fTempPerm366 = 0;
		fTempPerm367 = 0;
		fTempPerm368 = 0;
		iTempPerm369 = 0;
		iTempPerm370 = 0;
		fTempPerm371 = 0;
		fTempPerm372 = 0;
		fTempPerm373 = 0;
		iTempPerm374 = 0;
		iTempPerm375 = 0;
		fTempPerm376 = 0;
		fTempPerm377 = 0;
		fTempPerm378 = 0;
		iTempPerm379 = 0;
		iTempPerm380 = 0;
		fTempPerm381 = 0;
		fTempPerm382 = 0;
		fTempPerm383 = 0;
		fTempPerm384 = 0;
		fTempPerm385 = 0;
		fTempPerm386 = 0;
		fTempPerm387 = 0;
		fTempPerm388 = 0;
		fTempPerm389 = 0;
		fTempPerm390 = 0;
		fTempPerm391 = 0;
		fTempPerm392 = 0;
		fTempPerm393 = 0;
		fTempPerm394 = 0;
		fTempPerm395 = 0;
		fTempPerm396 = 0;
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
		iTempPerm434 = 0;
		fTempPerm435 = 0;
		fTempPerm436 = 0;
		iTempPerm437 = 0;
		iTempPerm438 = 0;
		iTempPerm439 = 0;
		iTempPerm440 = 0;
		fTempPerm441 = 0;
		fTempPerm442 = 0;
		fTempPerm443 = 0;
		iTempPerm444 = 0;
		iTempPerm445 = 0;
		fTempPerm446 = 0;
		fTempPerm447 = 0;
		fTempPerm448 = 0;
		fTempPerm449 = 0;
		fTempPerm450 = 0;
		iTempPerm451 = 0;
		iTempPerm452 = 0;
		fTempPerm453 = 0;
		fTempPerm454 = 0;
		fTempPerm455 = 0;
		iTempPerm456 = 0;
		iTempPerm457 = 0;
		fTempPerm458 = 0;
		fTempPerm459 = 0;
		fTempPerm460 = 0;
		iTempPerm461 = 0;
		iTempPerm462 = 0;
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
		fTempPerm473 = 0;
		fTempPerm474 = 0;
		fTempPerm475 = 0;
		fTempPerm476 = 0;
		fTempPerm477 = 0;
		fTempPerm478 = 0;
		fTempPerm479 = 0;
		fTempPerm480 = 0;
		fTempPerm481 = 0;
		fTempPerm482 = 0;
		fTempPerm483 = 0;
		fTempPerm484 = 0;
		fTempPerm485 = 0;
		fTempPerm486 = 0;
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
		iTempPerm521 = 0;
		fTempPerm522 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 440.0f;
		fslider2 = 1.0f;
		fslider3 = 3.0f;
		fbutton0 = 0.0;
		fslider4 = 3.0f;
		fslider5 = 3.0f;
		fslider6 = 3.0f;
		fslider7 = 3.0f;
		fslider8 = 3.0f;
		fslider9 = 0.0f;
		fslider10 = 0.0f;
		fslider11 = 0.0f;
		fslider12 = 0.001f;
		fslider13 = 1.0f;
		fslider14 = 440.0f;
		fslider15 = 1.0f;
		fbutton1 = 0.0;
		fslider16 = 440.0f;
		fslider17 = 1.0f;
		fbutton2 = 0.0;
		fslider18 = 440.0f;
		fslider19 = 1.0f;
		fbutton3 = 0.0;
		fslider20 = 440.0f;
		fslider21 = 1.0f;
		fbutton4 = 0.0;
		fslider22 = 440.0f;
		fslider23 = 1.0f;
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
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) iRec34[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
		for (int i=0; i<2; i++) fRec56[i] = 0;
		for (int i=0; i<2; i++) fRec57[i] = 0;
		for (int i=0; i<2; i++) fRec58[i] = 0;
		for (int i=0; i<2; i++) fRec59[i] = 0;
		for (int i=0; i<2; i++) fRec60[i] = 0;
		for (int i=0; i<2; i++) fRec61[i] = 0;
		for (int i=0; i<2; i++) fRec62[i] = 0;
		for (int i=0; i<2; i++) fRec63[i] = 0;
		for (int i=0; i<2; i++) fRec64[i] = 0;
		for (int i=0; i<2; i++) fRec65[i] = 0;
		for (int i=0; i<2; i++) fRec66[i] = 0;
		for (int i=0; i<2; i++) iRec68[i] = 0;
		for (int i=0; i<2; i++) fRec67[i] = 0;
		for (int i=0; i<2; i++) fRec69[i] = 0;
		for (int i=0; i<2; i++) fRec71[i] = 0;
		for (int i=0; i<2; i++) fRec70[i] = 0;
		for (int i=0; i<2; i++) fRec72[i] = 0;
		for (int i=0; i<2; i++) fRec73[i] = 0;
		for (int i=0; i<2; i++) fRec75[i] = 0;
		for (int i=0; i<2; i++) fRec74[i] = 0;
		for (int i=0; i<2; i++) fRec76[i] = 0;
		for (int i=0; i<2; i++) fRec78[i] = 0;
		for (int i=0; i<2; i++) fRec77[i] = 0;
		for (int i=0; i<2; i++) fRec80[i] = 0;
		for (int i=0; i<2; i++) fRec79[i] = 0;
		for (int i=0; i<2; i++) fRec81[i] = 0;
		for (int i=0; i<2; i++) fRec83[i] = 0;
		for (int i=0; i<2; i++) fRec82[i] = 0;
		for (int i=0; i<2; i++) fRec84[i] = 0;
		for (int i=0; i<2; i++) fRec86[i] = 0;
		for (int i=0; i<2; i++) fRec85[i] = 0;
		for (int i=0; i<2; i++) fRec87[i] = 0;
		for (int i=0; i<2; i++) fRec88[i] = 0;
		for (int i=0; i<2; i++) fRec89[i] = 0;
		for (int i=0; i<2; i++) fRec90[i] = 0;
		for (int i=0; i<2; i++) fRec91[i] = 0;
		for (int i=0; i<2; i++) fRec92[i] = 0;
		for (int i=0; i<2; i++) fRec93[i] = 0;
		for (int i=0; i<2; i++) fRec94[i] = 0;
		for (int i=0; i<2; i++) fRec95[i] = 0;
		for (int i=0; i<2; i++) fRec96[i] = 0;
		for (int i=0; i<2; i++) fRec97[i] = 0;
		for (int i=0; i<2; i++) fRec98[i] = 0;
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) fRec100[i] = 0;
		for (int i=0; i<2; i++) iRec102[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<2; i++) fRec104[i] = 0;
		for (int i=0; i<2; i++) fRec106[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<2; i++) fRec108[i] = 0;
		for (int i=0; i<2; i++) fRec110[i] = 0;
		for (int i=0; i<2; i++) fRec112[i] = 0;
		for (int i=0; i<2; i++) fRec111[i] = 0;
		for (int i=0; i<2; i++) fRec114[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<2; i++) fRec116[i] = 0;
		for (int i=0; i<2; i++) fRec118[i] = 0;
		for (int i=0; i<2; i++) fRec120[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<2; i++) fRec122[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
		for (int i=0; i<2; i++) fRec124[i] = 0;
		for (int i=0; i<2; i++) fRec125[i] = 0;
		for (int i=0; i<2; i++) fRec126[i] = 0;
		for (int i=0; i<2; i++) fRec127[i] = 0;
		for (int i=0; i<2; i++) fRec128[i] = 0;
		for (int i=0; i<2; i++) fRec129[i] = 0;
		for (int i=0; i<2; i++) fRec130[i] = 0;
		for (int i=0; i<2; i++) fRec131[i] = 0;
		for (int i=0; i<2; i++) fRec132[i] = 0;
		for (int i=0; i<2; i++) fRec133[i] = 0;
		for (int i=0; i<2; i++) fRec134[i] = 0;
		for (int i=0; i<2; i++) iRec136[i] = 0;
		for (int i=0; i<2; i++) fRec135[i] = 0;
		for (int i=0; i<2; i++) fRec137[i] = 0;
		for (int i=0; i<2; i++) fRec139[i] = 0;
		for (int i=0; i<2; i++) fRec138[i] = 0;
		for (int i=0; i<2; i++) fRec140[i] = 0;
		for (int i=0; i<2; i++) fRec141[i] = 0;
		for (int i=0; i<2; i++) fRec143[i] = 0;
		for (int i=0; i<2; i++) fRec142[i] = 0;
		for (int i=0; i<2; i++) fRec144[i] = 0;
		for (int i=0; i<2; i++) fRec146[i] = 0;
		for (int i=0; i<2; i++) fRec145[i] = 0;
		for (int i=0; i<2; i++) fRec148[i] = 0;
		for (int i=0; i<2; i++) fRec147[i] = 0;
		for (int i=0; i<2; i++) fRec149[i] = 0;
		for (int i=0; i<2; i++) fRec151[i] = 0;
		for (int i=0; i<2; i++) fRec150[i] = 0;
		for (int i=0; i<2; i++) fRec152[i] = 0;
		for (int i=0; i<2; i++) fRec154[i] = 0;
		for (int i=0; i<2; i++) fRec153[i] = 0;
		for (int i=0; i<2; i++) fRec155[i] = 0;
		for (int i=0; i<2; i++) fRec156[i] = 0;
		for (int i=0; i<2; i++) fRec157[i] = 0;
		for (int i=0; i<2; i++) fRec158[i] = 0;
		for (int i=0; i<2; i++) fRec159[i] = 0;
		for (int i=0; i<2; i++) fRec160[i] = 0;
		for (int i=0; i<2; i++) fRec161[i] = 0;
		for (int i=0; i<2; i++) fRec162[i] = 0;
		for (int i=0; i<2; i++) fRec163[i] = 0;
		for (int i=0; i<2; i++) fRec164[i] = 0;
		for (int i=0; i<2; i++) fRec165[i] = 0;
		for (int i=0; i<2; i++) fRec166[i] = 0;
		for (int i=0; i<2; i++) fRec167[i] = 0;
		for (int i=0; i<2; i++) fRec168[i] = 0;
		for (int i=0; i<2; i++) iRec170[i] = 0;
		for (int i=0; i<2; i++) fRec169[i] = 0;
		for (int i=0; i<2; i++) fRec171[i] = 0;
		for (int i=0; i<2; i++) fRec173[i] = 0;
		for (int i=0; i<2; i++) fRec172[i] = 0;
		for (int i=0; i<2; i++) fRec174[i] = 0;
		for (int i=0; i<2; i++) fRec175[i] = 0;
		for (int i=0; i<2; i++) fRec177[i] = 0;
		for (int i=0; i<2; i++) fRec176[i] = 0;
		for (int i=0; i<2; i++) fRec178[i] = 0;
		for (int i=0; i<2; i++) fRec180[i] = 0;
		for (int i=0; i<2; i++) fRec179[i] = 0;
		for (int i=0; i<2; i++) fRec182[i] = 0;
		for (int i=0; i<2; i++) fRec181[i] = 0;
		for (int i=0; i<2; i++) fRec183[i] = 0;
		for (int i=0; i<2; i++) fRec185[i] = 0;
		for (int i=0; i<2; i++) fRec184[i] = 0;
		for (int i=0; i<2; i++) fRec186[i] = 0;
		for (int i=0; i<2; i++) fRec188[i] = 0;
		for (int i=0; i<2; i++) fRec187[i] = 0;
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
		for (int i=0; i<2; i++) fRec199[i] = 0;
		for (int i=0; i<2; i++) fRec200[i] = 0;
		for (int i=0; i<2; i++) fRec201[i] = 0;
		for (int i=0; i<2; i++) fRec202[i] = 0;
		for (int i=0; i<2; i++) iRec204[i] = 0;
		for (int i=0; i<2; i++) fRec203[i] = 0;
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
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fslider12, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider11, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider10, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider13, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("feedback", &fslider9, 0.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_0", &fslider3, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_1", &fslider4, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_2", &fslider5, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_3", &fslider6, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_4", &fslider7, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("opRateScale_5", &fslider8, 3.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider22, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider23, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider18, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider19, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider14, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider15, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider20, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider21, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider16, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider17, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider1, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider2, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
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
		float 	fSlow34 = (fSlow33 + 0.75f);
		float 	fSlow35 = (fConst1 * fSlow34);
		float 	fSlow36 = float(fslider2);
		float 	fSlow37 = (18.75f * fSlow36);
		float 	fSlow38 = (fSlow37 + 56.25f);
		float 	fSlow39 = powf((0.010101010101010102f * min((float)99, fSlow38)),0.69999999999999996f);
		float 	fSlow40 = powf((0.014705882352941176f * (float((fSlow38 >= 30.0f)) * min((fSlow37 + 26.25f), (float)68))),1.8f);
		int 	iSlow41 = int((0.0f > fSlow38));
		float 	fSlow42 = float(fslider3);
		float 	fSlow43 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow34))) + 48.0f) * fSlow42));
		float 	fSlow44 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow43 + 25.0f))));
		float 	fSlow45 = max(0.0080000000000000002f, (318.0f * powf(fSlow44,12.6f)));
		float 	fSlow46 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow44)));
		float 	fSlow47 = (24.75f * fSlow36);
		float 	fSlow48 = (fSlow47 + 74.25f);
		float 	fSlow49 = powf((0.010101010101010102f * min((float)99, fSlow48)),0.69999999999999996f);
		float 	fSlow50 = powf((0.014705882352941176f * (float((fSlow48 >= 30.0f)) * min((fSlow47 + 44.25f), (float)68))),1.8f);
		int 	iSlow51 = int((fSlow38 > fSlow48));
		int 	iSlow52 = int((fSlow48 > 0.0f));
		float 	fSlow53 = ((iSlow52)?fSlow50:fSlow49);
		float 	fSlow54 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow43 + 96.0f))));
		float 	fSlow55 = max(0.001f, fabsf((-1 * (((iSlow52)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow54))):max(0.0080000000000000002f, (318.0f * powf(fSlow54,12.6f)))) * fSlow53))));
		float 	fSlow56 = (fSlow55 + max(0.001f, fabsf((((iSlow51)?fSlow46:fSlow45) * (((iSlow51)?fSlow40:fSlow39) - ((iSlow51)?fSlow50:fSlow49))))));
		float 	fSlow57 = (fSlow56 + max(0.001f, fabsf((((iSlow41)?fSlow46:fSlow45) * ((iSlow41)?fSlow40:fSlow39)))));
		float 	fSlow58 = (0 - (fConst0 * (fSlow56 - fSlow57)));
		float 	fSlow59 = (fConst0 * fSlow56);
		float 	fSlow60 = (fConst0 * fSlow57);
		float 	fSlow61 = float(fbutton0);
		int 	iSlow62 = int(((fSlow61 == 0.0f) > 0));
		float 	fSlow63 = (0 - (fConst0 * (fSlow55 - fSlow56)));
		float 	fSlow64 = (fConst0 * fSlow55);
		float 	fSlow65 = (-18.0f - (6.0f * fSlow36));
		float 	fSlow66 = (fConst1 * fSlow48);
		int 	iSlow67 = (fSlow61 > 0.0f);
		float 	fSlow68 = float(iSlow67);
		int 	iSlow69 = int(iSlow67);
		int 	iSlow70 = int((iSlow67 > 0));
		float 	fSlow71 = (fConst4 * fSlow33);
		float 	fSlow72 = (38.446969696969695f * fSlow36);
		float 	fSlow73 = (fSlow72 + 5.4924242424242422f);
		float 	fSlow74 = powf((0.010101010101010102f * min((float)99, fSlow73)),0.69999999999999996f);
		float 	fSlow75 = powf((0.014705882352941176f * (float((fSlow73 >= 30.0f)) * min((fSlow72 + -24.507575757575758f), (float)68))),1.8f);
		int 	iSlow76 = int((0.0f > fSlow73));
		float 	fSlow77 = float(fslider4);
		float 	fSlow78 = (0.057142857142857148f * (((17.312340490667559f * logf((0.031818181818181815f * fSlow33))) + 48.0f) * fSlow77));
		float 	fSlow79 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow78 + 35.0f))));
		float 	fSlow80 = (50.75f * fSlow36);
		float 	fSlow81 = (fSlow80 + 7.25f);
		float 	fSlow82 = powf((0.010101010101010102f * min((float)99, fSlow81)),0.69999999999999996f);
		float 	fSlow83 = powf((0.014705882352941176f * (float((fSlow81 >= 30.0f)) * min((fSlow80 + -22.75f), (float)68))),1.8f);
		int 	iSlow84 = int((fSlow73 > fSlow81));
		float 	fSlow85 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow78 + 50.0f))));
		int 	iSlow86 = int((fSlow81 > 0.0f));
		float 	fSlow87 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow78 + 95.0f))));
		float 	fSlow88 = max(0.001f, fabsf((-1 * (((iSlow86)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow87))):max(0.0080000000000000002f, (318.0f * powf(fSlow87,12.6f)))) * ((iSlow86)?fSlow83:fSlow82)))));
		float 	fSlow89 = (fSlow88 + max(0.001f, fabsf((((iSlow84)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow85))):max(0.0080000000000000002f, (318.0f * powf(fSlow85,12.6f)))) * (((iSlow84)?fSlow75:fSlow74) - ((iSlow84)?fSlow83:fSlow82))))));
		float 	fSlow90 = (fSlow89 + max(0.001f, fabsf((((iSlow76)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow79))):max(0.0080000000000000002f, (318.0f * powf(fSlow79,12.6f)))) * ((iSlow76)?fSlow75:fSlow74)))));
		float 	fSlow91 = (0 - (fConst0 * (fSlow89 - fSlow90)));
		float 	fSlow92 = (fConst0 * fSlow89);
		float 	fSlow93 = (fConst0 * fSlow90);
		float 	fSlow94 = (0 - (fConst0 * (fSlow88 - fSlow89)));
		float 	fSlow95 = (fConst0 * fSlow88);
		float 	fSlow96 = (-1.7575757575757578f - (12.303030303030305f * fSlow36));
		float 	fSlow97 = (fConst1 * fSlow81);
		float 	fSlow98 = (fConst1 * fSlow33);
		float 	fSlow99 = (23.75f * fSlow36);
		float 	fSlow100 = (fSlow99 + 71.25f);
		float 	fSlow101 = powf((0.010101010101010102f * min((float)99, fSlow100)),0.69999999999999996f);
		float 	fSlow102 = powf((0.014705882352941176f * (float((fSlow100 >= 30.0f)) * min((fSlow99 + 41.25f), (float)68))),1.8f);
		int 	iSlow103 = int((0.0f > fSlow100));
		float 	fSlow104 = float(fslider5);
		float 	fSlow105 = ((17.312340490667559f * logf((0.0022727272727272726f * fSlow33))) + 48.0f);
		float 	fSlow106 = (0.057142857142857148f * (fSlow105 * fSlow104));
		float 	fSlow107 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow106 + 20.0f))));
		float 	fSlow108 = max(0.0080000000000000002f, (318.0f * powf(fSlow107,12.6f)));
		float 	fSlow109 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow107)));
		int 	iSlow110 = int((fSlow100 > fSlow48));
		float 	fSlow111 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow106 + 95.0f))));
		float 	fSlow112 = max(0.001f, fabsf((-1 * (fSlow53 * ((iSlow52)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow111))):max(0.0080000000000000002f, (318.0f * powf(fSlow111,12.6f))))))));
		float 	fSlow113 = (fSlow112 + max(0.001f, fabsf((((iSlow110)?fSlow109:fSlow108) * (((iSlow110)?fSlow102:fSlow101) - ((iSlow110)?fSlow50:fSlow49))))));
		float 	fSlow114 = (fSlow113 + max(0.001f, fabsf((((iSlow103)?fSlow109:fSlow108) * ((iSlow103)?fSlow102:fSlow101)))));
		float 	fSlow115 = (0 - (fConst0 * (fSlow113 - fSlow114)));
		float 	fSlow116 = (fConst0 * fSlow113);
		float 	fSlow117 = (fConst0 * fSlow114);
		float 	fSlow118 = (0 - (fConst0 * (fSlow112 - fSlow113)));
		float 	fSlow119 = (fConst0 * fSlow112);
		float 	fSlow120 = (-3.0f - fSlow36);
		float 	fSlow121 = (64.053030303030297f * fSlow36);
		float 	fSlow122 = (fSlow121 + 21.3510101010101f);
		float 	fSlow123 = powf((0.010101010101010102f * min((float)99, fSlow122)),0.69999999999999996f);
		float 	fSlow124 = powf((0.014705882352941176f * (float((fSlow122 >= 30.0f)) * min((fSlow121 + -8.6489898989898997f), (float)68))),1.8f);
		int 	iSlow125 = int((0.0f > fSlow122));
		float 	fSlow126 = float(fslider6);
		float 	fSlow127 = (0.057142857142857148f * (fSlow105 * fSlow126));
		float 	fSlow128 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow127 + 20.0f))));
		float 	fSlow129 = (66.75f * fSlow36);
		float 	fSlow130 = (fSlow129 + 22.25f);
		float 	fSlow131 = powf((0.010101010101010102f * min((float)99, fSlow130)),0.69999999999999996f);
		float 	fSlow132 = powf((0.014705882352941176f * (float((fSlow130 >= 30.0f)) * min((fSlow129 + -7.75f), (float)68))),1.8f);
		int 	iSlow133 = int((fSlow122 > fSlow130));
		float 	fSlow134 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow127 + 29.0f))));
		int 	iSlow135 = int((fSlow130 > 0.0f));
		float 	fSlow136 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow127 + 95.0f))));
		float 	fSlow137 = max(0.001f, fabsf((-1 * (((iSlow135)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow136))):max(0.0080000000000000002f, (318.0f * powf(fSlow136,12.6f)))) * ((iSlow135)?fSlow132:fSlow131)))));
		float 	fSlow138 = (fSlow137 + max(0.001f, fabsf((((iSlow133)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow134))):max(0.0080000000000000002f, (318.0f * powf(fSlow134,12.6f)))) * (((iSlow133)?fSlow124:fSlow123) - ((iSlow133)?fSlow132:fSlow131))))));
		float 	fSlow139 = (fSlow138 + max(0.001f, fabsf((((iSlow125)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow128))):max(0.0080000000000000002f, (318.0f * powf(fSlow128,12.6f)))) * ((iSlow125)?fSlow124:fSlow123)))));
		float 	fSlow140 = (0 - (fConst0 * (fSlow138 - fSlow139)));
		float 	fSlow141 = (fConst0 * fSlow138);
		float 	fSlow142 = (fConst0 * fSlow139);
		float 	fSlow143 = (0 - (fConst0 * (fSlow137 - fSlow138)));
		float 	fSlow144 = (fConst0 * fSlow137);
		float 	fSlow145 = (-0.89898989898989967f - (2.6969696969697026f * fSlow36));
		float 	fSlow146 = (fConst1 * fSlow130);
		float 	fSlow147 = (fSlow33 + -1.75f);
		float 	fSlow148 = (fConst1 * fSlow147);
		float 	fSlow149 = float(fslider7);
		float 	fSlow150 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow147))) + 48.0f) * fSlow149));
		float 	fSlow151 = max(0.0080000000000000002f, (318.0f * powf((0.007874015748031496f * (127.0f - min((float)99, (fSlow150 + 20.0f)))),12.6f)));
		float 	fSlow152 = max(0.001f, fabsf((-1 * max(0.0030000000000000001f, (38.0f * faustpower<12>((0.007874015748031496f * (127.0f - min((float)99, (fSlow150 + 95.0f))))))))));
		float 	fSlow153 = (fSlow152 + max(0.001f, fabsf((0 - (0.028457312138301938f * fSlow151)))));
		float 	fSlow154 = (fConst0 * fSlow153);
		float 	fSlow155 = (fSlow153 + max(0.001f, fabsf((0.97154268786169806f * fSlow151))));
		float 	fSlow156 = (fConst0 * fSlow155);
		float 	fSlow157 = (1.0f / (0 - (fConst0 * (fSlow153 - fSlow155))));
		float 	fSlow158 = (fConst0 * fSlow152);
		float 	fSlow159 = (1.0f / (0 - (fConst0 * (fSlow152 - fSlow153))));
		float 	fSlow160 = (fConst5 / fSlow152);
		float 	fSlow161 = (fSlow33 + 1.75f);
		float 	fSlow162 = (fConst1 * fSlow161);
		float 	fSlow163 = (56.856060606060609f * fSlow36);
		float 	fSlow164 = (fSlow163 + 18.952020202020204f);
		float 	fSlow165 = powf((0.010101010101010102f * min((float)99, fSlow164)),0.69999999999999996f);
		float 	fSlow166 = powf((0.014705882352941176f * (float((fSlow164 >= 30.0f)) * min((fSlow163 + -11.047979797979796f), (float)68))),1.8f);
		int 	iSlow167 = int((0.0f > fSlow164));
		float 	fSlow168 = float(fslider8);
		float 	fSlow169 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow161))) + 48.0f) * fSlow168));
		float 	fSlow170 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow169 + 20.0f))));
		float 	fSlow171 = (59.25f * fSlow36);
		float 	fSlow172 = (fSlow171 + 19.75f);
		float 	fSlow173 = powf((0.010101010101010102f * min((float)99, fSlow172)),0.69999999999999996f);
		float 	fSlow174 = powf((0.014705882352941176f * (float((fSlow172 >= 30.0f)) * min((fSlow171 + -10.25f), (float)68))),1.8f);
		int 	iSlow175 = int((fSlow164 > fSlow172));
		float 	fSlow176 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow169 + 29.0f))));
		int 	iSlow177 = int((fSlow172 > 0.0f));
		float 	fSlow178 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow169 + 95.0f))));
		float 	fSlow179 = max(0.001f, fabsf((-1 * (((iSlow177)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow178))):max(0.0080000000000000002f, (318.0f * powf(fSlow178,12.6f)))) * ((iSlow177)?fSlow174:fSlow173)))));
		float 	fSlow180 = (fSlow179 + max(0.001f, fabsf((((iSlow175)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow176))):max(0.0080000000000000002f, (318.0f * powf(fSlow176,12.6f)))) * (((iSlow175)?fSlow166:fSlow165) - ((iSlow175)?fSlow174:fSlow173))))));
		float 	fSlow181 = (fSlow180 + max(0.001f, fabsf((((iSlow167)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow170))):max(0.0080000000000000002f, (318.0f * powf(fSlow170,12.6f)))) * ((iSlow167)?fSlow166:fSlow165)))));
		float 	fSlow182 = (0 - (fConst0 * (fSlow180 - fSlow181)));
		float 	fSlow183 = (fConst0 * fSlow180);
		float 	fSlow184 = (fConst0 * fSlow181);
		float 	fSlow185 = (0 - (fConst0 * (fSlow179 - fSlow180)));
		float 	fSlow186 = (fConst0 * fSlow179);
		float 	fSlow187 = (-0.79797979797979579f - (2.3939393939393909f * fSlow36));
		float 	fSlow188 = (fConst1 * fSlow172);
		float 	fSlow189 = float(fslider9);
		float 	fSlow190 = (39321.599999999999f * fSlow189);
		float 	fSlow191 = (6553.6000000000004f * fSlow189);
		float 	fSlow192 = (26214.400000000001f * fSlow189);
		float 	fSlow193 = (32768.0f * fSlow189);
		float 	fSlow194 = (13107.200000000001f * fSlow189);
		float 	fSlow195 = float(fslider10);
		float 	fSlow196 = float(fslider11);
		float 	fSlow197 = float(fslider12);
		float 	fSlow198 = (6.9100000000000001f * fSlow197);
		int 	iSlow199 = int((fConst0 * fSlow197));
		float 	fSlow200 = float(fslider13);
		float 	fSlow201 = (fSlow68 * fSlow200);
		float 	fSlow202 = float(fslider14);
		float 	fSlow203 = (fSlow202 + 0.75f);
		float 	fSlow204 = (fConst1 * fSlow203);
		float 	fSlow205 = float(fslider15);
		float 	fSlow206 = (18.75f * fSlow205);
		float 	fSlow207 = (fSlow206 + 56.25f);
		float 	fSlow208 = powf((0.010101010101010102f * min((float)99, fSlow207)),0.69999999999999996f);
		float 	fSlow209 = powf((0.014705882352941176f * (float((fSlow207 >= 30.0f)) * min((fSlow206 + 26.25f), (float)68))),1.8f);
		int 	iSlow210 = int((0.0f > fSlow207));
		float 	fSlow211 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow203))) + 48.0f) * fSlow42));
		float 	fSlow212 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow211 + 25.0f))));
		float 	fSlow213 = max(0.0080000000000000002f, (318.0f * powf(fSlow212,12.6f)));
		float 	fSlow214 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow212)));
		float 	fSlow215 = (24.75f * fSlow205);
		float 	fSlow216 = (fSlow215 + 74.25f);
		float 	fSlow217 = powf((0.010101010101010102f * min((float)99, fSlow216)),0.69999999999999996f);
		float 	fSlow218 = powf((0.014705882352941176f * (float((fSlow216 >= 30.0f)) * min((fSlow215 + 44.25f), (float)68))),1.8f);
		int 	iSlow219 = int((fSlow207 > fSlow216));
		int 	iSlow220 = int((fSlow216 > 0.0f));
		float 	fSlow221 = ((iSlow220)?fSlow218:fSlow217);
		float 	fSlow222 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow211 + 96.0f))));
		float 	fSlow223 = max(0.001f, fabsf((-1 * (((iSlow220)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow222))):max(0.0080000000000000002f, (318.0f * powf(fSlow222,12.6f)))) * fSlow221))));
		float 	fSlow224 = (fSlow223 + max(0.001f, fabsf((((iSlow219)?fSlow214:fSlow213) * (((iSlow219)?fSlow209:fSlow208) - ((iSlow219)?fSlow218:fSlow217))))));
		float 	fSlow225 = (fSlow224 + max(0.001f, fabsf((((iSlow210)?fSlow214:fSlow213) * ((iSlow210)?fSlow209:fSlow208)))));
		float 	fSlow226 = (0 - (fConst0 * (fSlow224 - fSlow225)));
		float 	fSlow227 = (fConst0 * fSlow224);
		float 	fSlow228 = (fConst0 * fSlow225);
		float 	fSlow229 = float(fbutton1);
		int 	iSlow230 = int(((fSlow229 == 0.0f) > 0));
		float 	fSlow231 = (0 - (fConst0 * (fSlow223 - fSlow224)));
		float 	fSlow232 = (fConst0 * fSlow223);
		float 	fSlow233 = (-18.0f - (6.0f * fSlow205));
		float 	fSlow234 = (fConst1 * fSlow216);
		int 	iSlow235 = (fSlow229 > 0.0f);
		float 	fSlow236 = float(iSlow235);
		int 	iSlow237 = int(iSlow235);
		int 	iSlow238 = int((iSlow235 > 0));
		float 	fSlow239 = (fConst4 * fSlow202);
		float 	fSlow240 = (38.446969696969695f * fSlow205);
		float 	fSlow241 = (fSlow240 + 5.4924242424242422f);
		float 	fSlow242 = powf((0.010101010101010102f * min((float)99, fSlow241)),0.69999999999999996f);
		float 	fSlow243 = powf((0.014705882352941176f * (float((fSlow241 >= 30.0f)) * min((fSlow240 + -24.507575757575758f), (float)68))),1.8f);
		int 	iSlow244 = int((0.0f > fSlow241));
		float 	fSlow245 = (0.057142857142857148f * (((17.312340490667559f * logf((0.031818181818181815f * fSlow202))) + 48.0f) * fSlow77));
		float 	fSlow246 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow245 + 35.0f))));
		float 	fSlow247 = (50.75f * fSlow205);
		float 	fSlow248 = (fSlow247 + 7.25f);
		float 	fSlow249 = powf((0.010101010101010102f * min((float)99, fSlow248)),0.69999999999999996f);
		float 	fSlow250 = powf((0.014705882352941176f * (float((fSlow248 >= 30.0f)) * min((fSlow247 + -22.75f), (float)68))),1.8f);
		int 	iSlow251 = int((fSlow241 > fSlow248));
		float 	fSlow252 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow245 + 50.0f))));
		int 	iSlow253 = int((fSlow248 > 0.0f));
		float 	fSlow254 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow245 + 95.0f))));
		float 	fSlow255 = max(0.001f, fabsf((-1 * (((iSlow253)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow254))):max(0.0080000000000000002f, (318.0f * powf(fSlow254,12.6f)))) * ((iSlow253)?fSlow250:fSlow249)))));
		float 	fSlow256 = (fSlow255 + max(0.001f, fabsf((((iSlow251)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow252))):max(0.0080000000000000002f, (318.0f * powf(fSlow252,12.6f)))) * (((iSlow251)?fSlow243:fSlow242) - ((iSlow251)?fSlow250:fSlow249))))));
		float 	fSlow257 = (fSlow256 + max(0.001f, fabsf((((iSlow244)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow246))):max(0.0080000000000000002f, (318.0f * powf(fSlow246,12.6f)))) * ((iSlow244)?fSlow243:fSlow242)))));
		float 	fSlow258 = (0 - (fConst0 * (fSlow256 - fSlow257)));
		float 	fSlow259 = (fConst0 * fSlow256);
		float 	fSlow260 = (fConst0 * fSlow257);
		float 	fSlow261 = (0 - (fConst0 * (fSlow255 - fSlow256)));
		float 	fSlow262 = (fConst0 * fSlow255);
		float 	fSlow263 = (-1.7575757575757578f - (12.303030303030305f * fSlow205));
		float 	fSlow264 = (fConst1 * fSlow248);
		float 	fSlow265 = (fConst1 * fSlow202);
		float 	fSlow266 = (23.75f * fSlow205);
		float 	fSlow267 = (fSlow266 + 71.25f);
		float 	fSlow268 = powf((0.010101010101010102f * min((float)99, fSlow267)),0.69999999999999996f);
		float 	fSlow269 = powf((0.014705882352941176f * (float((fSlow267 >= 30.0f)) * min((fSlow266 + 41.25f), (float)68))),1.8f);
		int 	iSlow270 = int((0.0f > fSlow267));
		float 	fSlow271 = ((17.312340490667559f * logf((0.0022727272727272726f * fSlow202))) + 48.0f);
		float 	fSlow272 = (0.057142857142857148f * (fSlow271 * fSlow104));
		float 	fSlow273 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow272 + 20.0f))));
		float 	fSlow274 = max(0.0080000000000000002f, (318.0f * powf(fSlow273,12.6f)));
		float 	fSlow275 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow273)));
		int 	iSlow276 = int((fSlow267 > fSlow216));
		float 	fSlow277 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow272 + 95.0f))));
		float 	fSlow278 = max(0.001f, fabsf((-1 * (fSlow221 * ((iSlow220)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow277))):max(0.0080000000000000002f, (318.0f * powf(fSlow277,12.6f))))))));
		float 	fSlow279 = (fSlow278 + max(0.001f, fabsf((((iSlow276)?fSlow275:fSlow274) * (((iSlow276)?fSlow269:fSlow268) - ((iSlow276)?fSlow218:fSlow217))))));
		float 	fSlow280 = (fSlow279 + max(0.001f, fabsf((((iSlow270)?fSlow275:fSlow274) * ((iSlow270)?fSlow269:fSlow268)))));
		float 	fSlow281 = (0 - (fConst0 * (fSlow279 - fSlow280)));
		float 	fSlow282 = (fConst0 * fSlow279);
		float 	fSlow283 = (fConst0 * fSlow280);
		float 	fSlow284 = (0 - (fConst0 * (fSlow278 - fSlow279)));
		float 	fSlow285 = (fConst0 * fSlow278);
		float 	fSlow286 = (-3.0f - fSlow205);
		float 	fSlow287 = (64.053030303030297f * fSlow205);
		float 	fSlow288 = (fSlow287 + 21.3510101010101f);
		float 	fSlow289 = powf((0.010101010101010102f * min((float)99, fSlow288)),0.69999999999999996f);
		float 	fSlow290 = powf((0.014705882352941176f * (float((fSlow288 >= 30.0f)) * min((fSlow287 + -8.6489898989898997f), (float)68))),1.8f);
		int 	iSlow291 = int((0.0f > fSlow288));
		float 	fSlow292 = (0.057142857142857148f * (fSlow271 * fSlow126));
		float 	fSlow293 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow292 + 20.0f))));
		float 	fSlow294 = (66.75f * fSlow205);
		float 	fSlow295 = (fSlow294 + 22.25f);
		float 	fSlow296 = powf((0.010101010101010102f * min((float)99, fSlow295)),0.69999999999999996f);
		float 	fSlow297 = powf((0.014705882352941176f * (float((fSlow295 >= 30.0f)) * min((fSlow294 + -7.75f), (float)68))),1.8f);
		int 	iSlow298 = int((fSlow288 > fSlow295));
		float 	fSlow299 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow292 + 29.0f))));
		int 	iSlow300 = int((fSlow295 > 0.0f));
		float 	fSlow301 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow292 + 95.0f))));
		float 	fSlow302 = max(0.001f, fabsf((-1 * (((iSlow300)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow301))):max(0.0080000000000000002f, (318.0f * powf(fSlow301,12.6f)))) * ((iSlow300)?fSlow297:fSlow296)))));
		float 	fSlow303 = (fSlow302 + max(0.001f, fabsf((((iSlow298)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow299))):max(0.0080000000000000002f, (318.0f * powf(fSlow299,12.6f)))) * (((iSlow298)?fSlow290:fSlow289) - ((iSlow298)?fSlow297:fSlow296))))));
		float 	fSlow304 = (fSlow303 + max(0.001f, fabsf((((iSlow291)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow293))):max(0.0080000000000000002f, (318.0f * powf(fSlow293,12.6f)))) * ((iSlow291)?fSlow290:fSlow289)))));
		float 	fSlow305 = (0 - (fConst0 * (fSlow303 - fSlow304)));
		float 	fSlow306 = (fConst0 * fSlow303);
		float 	fSlow307 = (fConst0 * fSlow304);
		float 	fSlow308 = (0 - (fConst0 * (fSlow302 - fSlow303)));
		float 	fSlow309 = (fConst0 * fSlow302);
		float 	fSlow310 = (-0.89898989898989967f - (2.6969696969697026f * fSlow205));
		float 	fSlow311 = (fConst1 * fSlow295);
		float 	fSlow312 = (fSlow202 + -1.75f);
		float 	fSlow313 = (fConst1 * fSlow312);
		float 	fSlow314 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow312))) + 48.0f) * fSlow149));
		float 	fSlow315 = max(0.0080000000000000002f, (318.0f * powf((0.007874015748031496f * (127.0f - min((float)99, (fSlow314 + 20.0f)))),12.6f)));
		float 	fSlow316 = max(0.001f, fabsf((-1 * max(0.0030000000000000001f, (38.0f * faustpower<12>((0.007874015748031496f * (127.0f - min((float)99, (fSlow314 + 95.0f))))))))));
		float 	fSlow317 = (fSlow316 + max(0.001f, fabsf((0 - (0.028457312138301938f * fSlow315)))));
		float 	fSlow318 = (fConst0 * fSlow317);
		float 	fSlow319 = (fSlow317 + max(0.001f, fabsf((0.97154268786169806f * fSlow315))));
		float 	fSlow320 = (fConst0 * fSlow319);
		float 	fSlow321 = (1.0f / (0 - (fConst0 * (fSlow317 - fSlow319))));
		float 	fSlow322 = (fConst0 * fSlow316);
		float 	fSlow323 = (1.0f / (0 - (fConst0 * (fSlow316 - fSlow317))));
		float 	fSlow324 = (fConst5 / fSlow316);
		float 	fSlow325 = (fSlow202 + 1.75f);
		float 	fSlow326 = (fConst1 * fSlow325);
		float 	fSlow327 = (56.856060606060609f * fSlow205);
		float 	fSlow328 = (fSlow327 + 18.952020202020204f);
		float 	fSlow329 = powf((0.010101010101010102f * min((float)99, fSlow328)),0.69999999999999996f);
		float 	fSlow330 = powf((0.014705882352941176f * (float((fSlow328 >= 30.0f)) * min((fSlow327 + -11.047979797979796f), (float)68))),1.8f);
		int 	iSlow331 = int((0.0f > fSlow328));
		float 	fSlow332 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow325))) + 48.0f) * fSlow168));
		float 	fSlow333 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow332 + 20.0f))));
		float 	fSlow334 = (59.25f * fSlow205);
		float 	fSlow335 = (fSlow334 + 19.75f);
		float 	fSlow336 = powf((0.010101010101010102f * min((float)99, fSlow335)),0.69999999999999996f);
		float 	fSlow337 = powf((0.014705882352941176f * (float((fSlow335 >= 30.0f)) * min((fSlow334 + -10.25f), (float)68))),1.8f);
		int 	iSlow338 = int((fSlow328 > fSlow335));
		float 	fSlow339 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow332 + 29.0f))));
		int 	iSlow340 = int((fSlow335 > 0.0f));
		float 	fSlow341 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow332 + 95.0f))));
		float 	fSlow342 = max(0.001f, fabsf((-1 * (((iSlow340)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow341))):max(0.0080000000000000002f, (318.0f * powf(fSlow341,12.6f)))) * ((iSlow340)?fSlow337:fSlow336)))));
		float 	fSlow343 = (fSlow342 + max(0.001f, fabsf((((iSlow338)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow339))):max(0.0080000000000000002f, (318.0f * powf(fSlow339,12.6f)))) * (((iSlow338)?fSlow330:fSlow329) - ((iSlow338)?fSlow337:fSlow336))))));
		float 	fSlow344 = (fSlow343 + max(0.001f, fabsf((((iSlow331)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow333))):max(0.0080000000000000002f, (318.0f * powf(fSlow333,12.6f)))) * ((iSlow331)?fSlow330:fSlow329)))));
		float 	fSlow345 = (0 - (fConst0 * (fSlow343 - fSlow344)));
		float 	fSlow346 = (fConst0 * fSlow343);
		float 	fSlow347 = (fConst0 * fSlow344);
		float 	fSlow348 = (0 - (fConst0 * (fSlow342 - fSlow343)));
		float 	fSlow349 = (fConst0 * fSlow342);
		float 	fSlow350 = (-0.79797979797979579f - (2.3939393939393909f * fSlow205));
		float 	fSlow351 = (fConst1 * fSlow335);
		float 	fSlow352 = (fSlow236 * fSlow200);
		float 	fSlow353 = float(fslider16);
		float 	fSlow354 = (fSlow353 + 0.75f);
		float 	fSlow355 = (fConst1 * fSlow354);
		float 	fSlow356 = float(fslider17);
		float 	fSlow357 = (18.75f * fSlow356);
		float 	fSlow358 = (fSlow357 + 56.25f);
		float 	fSlow359 = powf((0.010101010101010102f * min((float)99, fSlow358)),0.69999999999999996f);
		float 	fSlow360 = powf((0.014705882352941176f * (float((fSlow358 >= 30.0f)) * min((fSlow357 + 26.25f), (float)68))),1.8f);
		int 	iSlow361 = int((0.0f > fSlow358));
		float 	fSlow362 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow354))) + 48.0f) * fSlow42));
		float 	fSlow363 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow362 + 25.0f))));
		float 	fSlow364 = max(0.0080000000000000002f, (318.0f * powf(fSlow363,12.6f)));
		float 	fSlow365 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow363)));
		float 	fSlow366 = (24.75f * fSlow356);
		float 	fSlow367 = (fSlow366 + 74.25f);
		float 	fSlow368 = powf((0.010101010101010102f * min((float)99, fSlow367)),0.69999999999999996f);
		float 	fSlow369 = powf((0.014705882352941176f * (float((fSlow367 >= 30.0f)) * min((fSlow366 + 44.25f), (float)68))),1.8f);
		int 	iSlow370 = int((fSlow358 > fSlow367));
		int 	iSlow371 = int((fSlow367 > 0.0f));
		float 	fSlow372 = ((iSlow371)?fSlow369:fSlow368);
		float 	fSlow373 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow362 + 96.0f))));
		float 	fSlow374 = max(0.001f, fabsf((-1 * (((iSlow371)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow373))):max(0.0080000000000000002f, (318.0f * powf(fSlow373,12.6f)))) * fSlow372))));
		float 	fSlow375 = (fSlow374 + max(0.001f, fabsf((((iSlow370)?fSlow365:fSlow364) * (((iSlow370)?fSlow360:fSlow359) - ((iSlow370)?fSlow369:fSlow368))))));
		float 	fSlow376 = (fSlow375 + max(0.001f, fabsf((((iSlow361)?fSlow365:fSlow364) * ((iSlow361)?fSlow360:fSlow359)))));
		float 	fSlow377 = (0 - (fConst0 * (fSlow375 - fSlow376)));
		float 	fSlow378 = (fConst0 * fSlow375);
		float 	fSlow379 = (fConst0 * fSlow376);
		float 	fSlow380 = float(fbutton2);
		int 	iSlow381 = int(((fSlow380 == 0.0f) > 0));
		float 	fSlow382 = (0 - (fConst0 * (fSlow374 - fSlow375)));
		float 	fSlow383 = (fConst0 * fSlow374);
		float 	fSlow384 = (-18.0f - (6.0f * fSlow356));
		float 	fSlow385 = (fConst1 * fSlow367);
		int 	iSlow386 = (fSlow380 > 0.0f);
		float 	fSlow387 = float(iSlow386);
		int 	iSlow388 = int(iSlow386);
		int 	iSlow389 = int((iSlow386 > 0));
		float 	fSlow390 = (fConst4 * fSlow353);
		float 	fSlow391 = (38.446969696969695f * fSlow356);
		float 	fSlow392 = (fSlow391 + 5.4924242424242422f);
		float 	fSlow393 = powf((0.010101010101010102f * min((float)99, fSlow392)),0.69999999999999996f);
		float 	fSlow394 = powf((0.014705882352941176f * (float((fSlow392 >= 30.0f)) * min((fSlow391 + -24.507575757575758f), (float)68))),1.8f);
		int 	iSlow395 = int((0.0f > fSlow392));
		float 	fSlow396 = (0.057142857142857148f * (((17.312340490667559f * logf((0.031818181818181815f * fSlow353))) + 48.0f) * fSlow77));
		float 	fSlow397 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow396 + 35.0f))));
		float 	fSlow398 = (50.75f * fSlow356);
		float 	fSlow399 = (fSlow398 + 7.25f);
		float 	fSlow400 = powf((0.010101010101010102f * min((float)99, fSlow399)),0.69999999999999996f);
		float 	fSlow401 = powf((0.014705882352941176f * (float((fSlow399 >= 30.0f)) * min((fSlow398 + -22.75f), (float)68))),1.8f);
		int 	iSlow402 = int((fSlow392 > fSlow399));
		float 	fSlow403 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow396 + 50.0f))));
		int 	iSlow404 = int((fSlow399 > 0.0f));
		float 	fSlow405 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow396 + 95.0f))));
		float 	fSlow406 = max(0.001f, fabsf((-1 * (((iSlow404)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow405))):max(0.0080000000000000002f, (318.0f * powf(fSlow405,12.6f)))) * ((iSlow404)?fSlow401:fSlow400)))));
		float 	fSlow407 = (fSlow406 + max(0.001f, fabsf((((iSlow402)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow403))):max(0.0080000000000000002f, (318.0f * powf(fSlow403,12.6f)))) * (((iSlow402)?fSlow394:fSlow393) - ((iSlow402)?fSlow401:fSlow400))))));
		float 	fSlow408 = (fSlow407 + max(0.001f, fabsf((((iSlow395)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow397))):max(0.0080000000000000002f, (318.0f * powf(fSlow397,12.6f)))) * ((iSlow395)?fSlow394:fSlow393)))));
		float 	fSlow409 = (0 - (fConst0 * (fSlow407 - fSlow408)));
		float 	fSlow410 = (fConst0 * fSlow407);
		float 	fSlow411 = (fConst0 * fSlow408);
		float 	fSlow412 = (0 - (fConst0 * (fSlow406 - fSlow407)));
		float 	fSlow413 = (fConst0 * fSlow406);
		float 	fSlow414 = (-1.7575757575757578f - (12.303030303030305f * fSlow356));
		float 	fSlow415 = (fConst1 * fSlow399);
		float 	fSlow416 = (fConst1 * fSlow353);
		float 	fSlow417 = (23.75f * fSlow356);
		float 	fSlow418 = (fSlow417 + 71.25f);
		float 	fSlow419 = powf((0.010101010101010102f * min((float)99, fSlow418)),0.69999999999999996f);
		float 	fSlow420 = powf((0.014705882352941176f * (float((fSlow418 >= 30.0f)) * min((fSlow417 + 41.25f), (float)68))),1.8f);
		int 	iSlow421 = int((0.0f > fSlow418));
		float 	fSlow422 = ((17.312340490667559f * logf((0.0022727272727272726f * fSlow353))) + 48.0f);
		float 	fSlow423 = (0.057142857142857148f * (fSlow422 * fSlow104));
		float 	fSlow424 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow423 + 20.0f))));
		float 	fSlow425 = max(0.0080000000000000002f, (318.0f * powf(fSlow424,12.6f)));
		float 	fSlow426 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow424)));
		int 	iSlow427 = int((fSlow418 > fSlow367));
		float 	fSlow428 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow423 + 95.0f))));
		float 	fSlow429 = max(0.001f, fabsf((-1 * (fSlow372 * ((iSlow371)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow428))):max(0.0080000000000000002f, (318.0f * powf(fSlow428,12.6f))))))));
		float 	fSlow430 = (fSlow429 + max(0.001f, fabsf((((iSlow427)?fSlow426:fSlow425) * (((iSlow427)?fSlow420:fSlow419) - ((iSlow427)?fSlow369:fSlow368))))));
		float 	fSlow431 = (fSlow430 + max(0.001f, fabsf((((iSlow421)?fSlow426:fSlow425) * ((iSlow421)?fSlow420:fSlow419)))));
		float 	fSlow432 = (0 - (fConst0 * (fSlow430 - fSlow431)));
		float 	fSlow433 = (fConst0 * fSlow430);
		float 	fSlow434 = (fConst0 * fSlow431);
		float 	fSlow435 = (0 - (fConst0 * (fSlow429 - fSlow430)));
		float 	fSlow436 = (fConst0 * fSlow429);
		float 	fSlow437 = (-3.0f - fSlow356);
		float 	fSlow438 = (64.053030303030297f * fSlow356);
		float 	fSlow439 = (fSlow438 + 21.3510101010101f);
		float 	fSlow440 = powf((0.010101010101010102f * min((float)99, fSlow439)),0.69999999999999996f);
		float 	fSlow441 = powf((0.014705882352941176f * (float((fSlow439 >= 30.0f)) * min((fSlow438 + -8.6489898989898997f), (float)68))),1.8f);
		int 	iSlow442 = int((0.0f > fSlow439));
		float 	fSlow443 = (0.057142857142857148f * (fSlow422 * fSlow126));
		float 	fSlow444 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow443 + 20.0f))));
		float 	fSlow445 = (66.75f * fSlow356);
		float 	fSlow446 = (fSlow445 + 22.25f);
		float 	fSlow447 = powf((0.010101010101010102f * min((float)99, fSlow446)),0.69999999999999996f);
		float 	fSlow448 = powf((0.014705882352941176f * (float((fSlow446 >= 30.0f)) * min((fSlow445 + -7.75f), (float)68))),1.8f);
		int 	iSlow449 = int((fSlow439 > fSlow446));
		float 	fSlow450 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow443 + 29.0f))));
		int 	iSlow451 = int((fSlow446 > 0.0f));
		float 	fSlow452 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow443 + 95.0f))));
		float 	fSlow453 = max(0.001f, fabsf((-1 * (((iSlow451)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow452))):max(0.0080000000000000002f, (318.0f * powf(fSlow452,12.6f)))) * ((iSlow451)?fSlow448:fSlow447)))));
		float 	fSlow454 = (fSlow453 + max(0.001f, fabsf((((iSlow449)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow450))):max(0.0080000000000000002f, (318.0f * powf(fSlow450,12.6f)))) * (((iSlow449)?fSlow441:fSlow440) - ((iSlow449)?fSlow448:fSlow447))))));
		float 	fSlow455 = (fSlow454 + max(0.001f, fabsf((((iSlow442)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow444))):max(0.0080000000000000002f, (318.0f * powf(fSlow444,12.6f)))) * ((iSlow442)?fSlow441:fSlow440)))));
		float 	fSlow456 = (0 - (fConst0 * (fSlow454 - fSlow455)));
		float 	fSlow457 = (fConst0 * fSlow454);
		float 	fSlow458 = (fConst0 * fSlow455);
		float 	fSlow459 = (0 - (fConst0 * (fSlow453 - fSlow454)));
		float 	fSlow460 = (fConst0 * fSlow453);
		float 	fSlow461 = (-0.89898989898989967f - (2.6969696969697026f * fSlow356));
		float 	fSlow462 = (fConst1 * fSlow446);
		float 	fSlow463 = (fSlow353 + -1.75f);
		float 	fSlow464 = (fConst1 * fSlow463);
		float 	fSlow465 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow463))) + 48.0f) * fSlow149));
		float 	fSlow466 = max(0.0080000000000000002f, (318.0f * powf((0.007874015748031496f * (127.0f - min((float)99, (fSlow465 + 20.0f)))),12.6f)));
		float 	fSlow467 = max(0.001f, fabsf((-1 * max(0.0030000000000000001f, (38.0f * faustpower<12>((0.007874015748031496f * (127.0f - min((float)99, (fSlow465 + 95.0f))))))))));
		float 	fSlow468 = (fSlow467 + max(0.001f, fabsf((0 - (0.028457312138301938f * fSlow466)))));
		float 	fSlow469 = (fConst0 * fSlow468);
		float 	fSlow470 = (fSlow468 + max(0.001f, fabsf((0.97154268786169806f * fSlow466))));
		float 	fSlow471 = (fConst0 * fSlow470);
		float 	fSlow472 = (1.0f / (0 - (fConst0 * (fSlow468 - fSlow470))));
		float 	fSlow473 = (fConst0 * fSlow467);
		float 	fSlow474 = (1.0f / (0 - (fConst0 * (fSlow467 - fSlow468))));
		float 	fSlow475 = (fConst5 / fSlow467);
		float 	fSlow476 = (fSlow353 + 1.75f);
		float 	fSlow477 = (fConst1 * fSlow476);
		float 	fSlow478 = (56.856060606060609f * fSlow356);
		float 	fSlow479 = (fSlow478 + 18.952020202020204f);
		float 	fSlow480 = powf((0.010101010101010102f * min((float)99, fSlow479)),0.69999999999999996f);
		float 	fSlow481 = powf((0.014705882352941176f * (float((fSlow479 >= 30.0f)) * min((fSlow478 + -11.047979797979796f), (float)68))),1.8f);
		int 	iSlow482 = int((0.0f > fSlow479));
		float 	fSlow483 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow476))) + 48.0f) * fSlow168));
		float 	fSlow484 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow483 + 20.0f))));
		float 	fSlow485 = (59.25f * fSlow356);
		float 	fSlow486 = (fSlow485 + 19.75f);
		float 	fSlow487 = powf((0.010101010101010102f * min((float)99, fSlow486)),0.69999999999999996f);
		float 	fSlow488 = powf((0.014705882352941176f * (float((fSlow486 >= 30.0f)) * min((fSlow485 + -10.25f), (float)68))),1.8f);
		int 	iSlow489 = int((fSlow479 > fSlow486));
		float 	fSlow490 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow483 + 29.0f))));
		int 	iSlow491 = int((fSlow486 > 0.0f));
		float 	fSlow492 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow483 + 95.0f))));
		float 	fSlow493 = max(0.001f, fabsf((-1 * (((iSlow491)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow492))):max(0.0080000000000000002f, (318.0f * powf(fSlow492,12.6f)))) * ((iSlow491)?fSlow488:fSlow487)))));
		float 	fSlow494 = (fSlow493 + max(0.001f, fabsf((((iSlow489)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow490))):max(0.0080000000000000002f, (318.0f * powf(fSlow490,12.6f)))) * (((iSlow489)?fSlow481:fSlow480) - ((iSlow489)?fSlow488:fSlow487))))));
		float 	fSlow495 = (fSlow494 + max(0.001f, fabsf((((iSlow482)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow484))):max(0.0080000000000000002f, (318.0f * powf(fSlow484,12.6f)))) * ((iSlow482)?fSlow481:fSlow480)))));
		float 	fSlow496 = (0 - (fConst0 * (fSlow494 - fSlow495)));
		float 	fSlow497 = (fConst0 * fSlow494);
		float 	fSlow498 = (fConst0 * fSlow495);
		float 	fSlow499 = (0 - (fConst0 * (fSlow493 - fSlow494)));
		float 	fSlow500 = (fConst0 * fSlow493);
		float 	fSlow501 = (-0.79797979797979579f - (2.3939393939393909f * fSlow356));
		float 	fSlow502 = (fConst1 * fSlow486);
		float 	fSlow503 = (fSlow387 * fSlow200);
		float 	fSlow504 = float(fslider18);
		float 	fSlow505 = (fSlow504 + 0.75f);
		float 	fSlow506 = (fConst1 * fSlow505);
		float 	fSlow507 = float(fslider19);
		float 	fSlow508 = (18.75f * fSlow507);
		float 	fSlow509 = (fSlow508 + 56.25f);
		float 	fSlow510 = powf((0.010101010101010102f * min((float)99, fSlow509)),0.69999999999999996f);
		float 	fSlow511 = powf((0.014705882352941176f * (float((fSlow509 >= 30.0f)) * min((fSlow508 + 26.25f), (float)68))),1.8f);
		int 	iSlow512 = int((0.0f > fSlow509));
		float 	fSlow513 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow505))) + 48.0f) * fSlow42));
		float 	fSlow514 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow513 + 25.0f))));
		float 	fSlow515 = max(0.0080000000000000002f, (318.0f * powf(fSlow514,12.6f)));
		float 	fSlow516 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow514)));
		float 	fSlow517 = (24.75f * fSlow507);
		float 	fSlow518 = (fSlow517 + 74.25f);
		float 	fSlow519 = powf((0.010101010101010102f * min((float)99, fSlow518)),0.69999999999999996f);
		float 	fSlow520 = powf((0.014705882352941176f * (float((fSlow518 >= 30.0f)) * min((fSlow517 + 44.25f), (float)68))),1.8f);
		int 	iSlow521 = int((fSlow509 > fSlow518));
		int 	iSlow522 = int((fSlow518 > 0.0f));
		float 	fSlow523 = ((iSlow522)?fSlow520:fSlow519);
		float 	fSlow524 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow513 + 96.0f))));
		float 	fSlow525 = max(0.001f, fabsf((-1 * (((iSlow522)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow524))):max(0.0080000000000000002f, (318.0f * powf(fSlow524,12.6f)))) * fSlow523))));
		float 	fSlow526 = (fSlow525 + max(0.001f, fabsf((((iSlow521)?fSlow516:fSlow515) * (((iSlow521)?fSlow511:fSlow510) - ((iSlow521)?fSlow520:fSlow519))))));
		float 	fSlow527 = (fSlow526 + max(0.001f, fabsf((((iSlow512)?fSlow516:fSlow515) * ((iSlow512)?fSlow511:fSlow510)))));
		float 	fSlow528 = (0 - (fConst0 * (fSlow526 - fSlow527)));
		float 	fSlow529 = (fConst0 * fSlow526);
		float 	fSlow530 = (fConst0 * fSlow527);
		float 	fSlow531 = float(fbutton3);
		int 	iSlow532 = int(((fSlow531 == 0.0f) > 0));
		float 	fSlow533 = (0 - (fConst0 * (fSlow525 - fSlow526)));
		float 	fSlow534 = (fConst0 * fSlow525);
		float 	fSlow535 = (-18.0f - (6.0f * fSlow507));
		float 	fSlow536 = (fConst1 * fSlow518);
		int 	iSlow537 = (fSlow531 > 0.0f);
		float 	fSlow538 = float(iSlow537);
		int 	iSlow539 = int(iSlow537);
		int 	iSlow540 = int((iSlow537 > 0));
		float 	fSlow541 = (fConst4 * fSlow504);
		float 	fSlow542 = (38.446969696969695f * fSlow507);
		float 	fSlow543 = (fSlow542 + 5.4924242424242422f);
		float 	fSlow544 = powf((0.010101010101010102f * min((float)99, fSlow543)),0.69999999999999996f);
		float 	fSlow545 = powf((0.014705882352941176f * (float((fSlow543 >= 30.0f)) * min((fSlow542 + -24.507575757575758f), (float)68))),1.8f);
		int 	iSlow546 = int((0.0f > fSlow543));
		float 	fSlow547 = (0.057142857142857148f * (((17.312340490667559f * logf((0.031818181818181815f * fSlow504))) + 48.0f) * fSlow77));
		float 	fSlow548 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow547 + 35.0f))));
		float 	fSlow549 = (50.75f * fSlow507);
		float 	fSlow550 = (fSlow549 + 7.25f);
		float 	fSlow551 = powf((0.010101010101010102f * min((float)99, fSlow550)),0.69999999999999996f);
		float 	fSlow552 = powf((0.014705882352941176f * (float((fSlow550 >= 30.0f)) * min((fSlow549 + -22.75f), (float)68))),1.8f);
		int 	iSlow553 = int((fSlow543 > fSlow550));
		float 	fSlow554 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow547 + 50.0f))));
		int 	iSlow555 = int((fSlow550 > 0.0f));
		float 	fSlow556 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow547 + 95.0f))));
		float 	fSlow557 = max(0.001f, fabsf((-1 * (((iSlow555)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow556))):max(0.0080000000000000002f, (318.0f * powf(fSlow556,12.6f)))) * ((iSlow555)?fSlow552:fSlow551)))));
		float 	fSlow558 = (fSlow557 + max(0.001f, fabsf((((iSlow553)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow554))):max(0.0080000000000000002f, (318.0f * powf(fSlow554,12.6f)))) * (((iSlow553)?fSlow545:fSlow544) - ((iSlow553)?fSlow552:fSlow551))))));
		float 	fSlow559 = (fSlow558 + max(0.001f, fabsf((((iSlow546)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow548))):max(0.0080000000000000002f, (318.0f * powf(fSlow548,12.6f)))) * ((iSlow546)?fSlow545:fSlow544)))));
		float 	fSlow560 = (0 - (fConst0 * (fSlow558 - fSlow559)));
		float 	fSlow561 = (fConst0 * fSlow558);
		float 	fSlow562 = (fConst0 * fSlow559);
		float 	fSlow563 = (0 - (fConst0 * (fSlow557 - fSlow558)));
		float 	fSlow564 = (fConst0 * fSlow557);
		float 	fSlow565 = (-1.7575757575757578f - (12.303030303030305f * fSlow507));
		float 	fSlow566 = (fConst1 * fSlow550);
		float 	fSlow567 = (fConst1 * fSlow504);
		float 	fSlow568 = (23.75f * fSlow507);
		float 	fSlow569 = (fSlow568 + 71.25f);
		float 	fSlow570 = powf((0.010101010101010102f * min((float)99, fSlow569)),0.69999999999999996f);
		float 	fSlow571 = powf((0.014705882352941176f * (float((fSlow569 >= 30.0f)) * min((fSlow568 + 41.25f), (float)68))),1.8f);
		int 	iSlow572 = int((0.0f > fSlow569));
		float 	fSlow573 = ((17.312340490667559f * logf((0.0022727272727272726f * fSlow504))) + 48.0f);
		float 	fSlow574 = (0.057142857142857148f * (fSlow573 * fSlow104));
		float 	fSlow575 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow574 + 20.0f))));
		float 	fSlow576 = max(0.0080000000000000002f, (318.0f * powf(fSlow575,12.6f)));
		float 	fSlow577 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow575)));
		int 	iSlow578 = int((fSlow569 > fSlow518));
		float 	fSlow579 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow574 + 95.0f))));
		float 	fSlow580 = max(0.001f, fabsf((-1 * (fSlow523 * ((iSlow522)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow579))):max(0.0080000000000000002f, (318.0f * powf(fSlow579,12.6f))))))));
		float 	fSlow581 = (fSlow580 + max(0.001f, fabsf((((iSlow578)?fSlow577:fSlow576) * (((iSlow578)?fSlow571:fSlow570) - ((iSlow578)?fSlow520:fSlow519))))));
		float 	fSlow582 = (fSlow581 + max(0.001f, fabsf((((iSlow572)?fSlow577:fSlow576) * ((iSlow572)?fSlow571:fSlow570)))));
		float 	fSlow583 = (0 - (fConst0 * (fSlow581 - fSlow582)));
		float 	fSlow584 = (fConst0 * fSlow581);
		float 	fSlow585 = (fConst0 * fSlow582);
		float 	fSlow586 = (0 - (fConst0 * (fSlow580 - fSlow581)));
		float 	fSlow587 = (fConst0 * fSlow580);
		float 	fSlow588 = (-3.0f - fSlow507);
		float 	fSlow589 = (64.053030303030297f * fSlow507);
		float 	fSlow590 = (fSlow589 + 21.3510101010101f);
		float 	fSlow591 = powf((0.010101010101010102f * min((float)99, fSlow590)),0.69999999999999996f);
		float 	fSlow592 = powf((0.014705882352941176f * (float((fSlow590 >= 30.0f)) * min((fSlow589 + -8.6489898989898997f), (float)68))),1.8f);
		int 	iSlow593 = int((0.0f > fSlow590));
		float 	fSlow594 = (0.057142857142857148f * (fSlow573 * fSlow126));
		float 	fSlow595 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow594 + 20.0f))));
		float 	fSlow596 = (66.75f * fSlow507);
		float 	fSlow597 = (fSlow596 + 22.25f);
		float 	fSlow598 = powf((0.010101010101010102f * min((float)99, fSlow597)),0.69999999999999996f);
		float 	fSlow599 = powf((0.014705882352941176f * (float((fSlow597 >= 30.0f)) * min((fSlow596 + -7.75f), (float)68))),1.8f);
		int 	iSlow600 = int((fSlow590 > fSlow597));
		float 	fSlow601 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow594 + 29.0f))));
		int 	iSlow602 = int((fSlow597 > 0.0f));
		float 	fSlow603 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow594 + 95.0f))));
		float 	fSlow604 = max(0.001f, fabsf((-1 * (((iSlow602)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow603))):max(0.0080000000000000002f, (318.0f * powf(fSlow603,12.6f)))) * ((iSlow602)?fSlow599:fSlow598)))));
		float 	fSlow605 = (fSlow604 + max(0.001f, fabsf((((iSlow600)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow601))):max(0.0080000000000000002f, (318.0f * powf(fSlow601,12.6f)))) * (((iSlow600)?fSlow592:fSlow591) - ((iSlow600)?fSlow599:fSlow598))))));
		float 	fSlow606 = (fSlow605 + max(0.001f, fabsf((((iSlow593)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow595))):max(0.0080000000000000002f, (318.0f * powf(fSlow595,12.6f)))) * ((iSlow593)?fSlow592:fSlow591)))));
		float 	fSlow607 = (0 - (fConst0 * (fSlow605 - fSlow606)));
		float 	fSlow608 = (fConst0 * fSlow605);
		float 	fSlow609 = (fConst0 * fSlow606);
		float 	fSlow610 = (0 - (fConst0 * (fSlow604 - fSlow605)));
		float 	fSlow611 = (fConst0 * fSlow604);
		float 	fSlow612 = (-0.89898989898989967f - (2.6969696969697026f * fSlow507));
		float 	fSlow613 = (fConst1 * fSlow597);
		float 	fSlow614 = (fSlow504 + -1.75f);
		float 	fSlow615 = (fConst1 * fSlow614);
		float 	fSlow616 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow614))) + 48.0f) * fSlow149));
		float 	fSlow617 = max(0.0080000000000000002f, (318.0f * powf((0.007874015748031496f * (127.0f - min((float)99, (fSlow616 + 20.0f)))),12.6f)));
		float 	fSlow618 = max(0.001f, fabsf((-1 * max(0.0030000000000000001f, (38.0f * faustpower<12>((0.007874015748031496f * (127.0f - min((float)99, (fSlow616 + 95.0f))))))))));
		float 	fSlow619 = (fSlow618 + max(0.001f, fabsf((0 - (0.028457312138301938f * fSlow617)))));
		float 	fSlow620 = (fConst0 * fSlow619);
		float 	fSlow621 = (fSlow619 + max(0.001f, fabsf((0.97154268786169806f * fSlow617))));
		float 	fSlow622 = (fConst0 * fSlow621);
		float 	fSlow623 = (1.0f / (0 - (fConst0 * (fSlow619 - fSlow621))));
		float 	fSlow624 = (fConst0 * fSlow618);
		float 	fSlow625 = (1.0f / (0 - (fConst0 * (fSlow618 - fSlow619))));
		float 	fSlow626 = (fConst5 / fSlow618);
		float 	fSlow627 = (fSlow504 + 1.75f);
		float 	fSlow628 = (fConst1 * fSlow627);
		float 	fSlow629 = (56.856060606060609f * fSlow507);
		float 	fSlow630 = (fSlow629 + 18.952020202020204f);
		float 	fSlow631 = powf((0.010101010101010102f * min((float)99, fSlow630)),0.69999999999999996f);
		float 	fSlow632 = powf((0.014705882352941176f * (float((fSlow630 >= 30.0f)) * min((fSlow629 + -11.047979797979796f), (float)68))),1.8f);
		int 	iSlow633 = int((0.0f > fSlow630));
		float 	fSlow634 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow627))) + 48.0f) * fSlow168));
		float 	fSlow635 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow634 + 20.0f))));
		float 	fSlow636 = (59.25f * fSlow507);
		float 	fSlow637 = (fSlow636 + 19.75f);
		float 	fSlow638 = powf((0.010101010101010102f * min((float)99, fSlow637)),0.69999999999999996f);
		float 	fSlow639 = powf((0.014705882352941176f * (float((fSlow637 >= 30.0f)) * min((fSlow636 + -10.25f), (float)68))),1.8f);
		int 	iSlow640 = int((fSlow630 > fSlow637));
		float 	fSlow641 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow634 + 29.0f))));
		int 	iSlow642 = int((fSlow637 > 0.0f));
		float 	fSlow643 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow634 + 95.0f))));
		float 	fSlow644 = max(0.001f, fabsf((-1 * (((iSlow642)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow643))):max(0.0080000000000000002f, (318.0f * powf(fSlow643,12.6f)))) * ((iSlow642)?fSlow639:fSlow638)))));
		float 	fSlow645 = (fSlow644 + max(0.001f, fabsf((((iSlow640)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow641))):max(0.0080000000000000002f, (318.0f * powf(fSlow641,12.6f)))) * (((iSlow640)?fSlow632:fSlow631) - ((iSlow640)?fSlow639:fSlow638))))));
		float 	fSlow646 = (fSlow645 + max(0.001f, fabsf((((iSlow633)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow635))):max(0.0080000000000000002f, (318.0f * powf(fSlow635,12.6f)))) * ((iSlow633)?fSlow632:fSlow631)))));
		float 	fSlow647 = (0 - (fConst0 * (fSlow645 - fSlow646)));
		float 	fSlow648 = (fConst0 * fSlow645);
		float 	fSlow649 = (fConst0 * fSlow646);
		float 	fSlow650 = (0 - (fConst0 * (fSlow644 - fSlow645)));
		float 	fSlow651 = (fConst0 * fSlow644);
		float 	fSlow652 = (-0.79797979797979579f - (2.3939393939393909f * fSlow507));
		float 	fSlow653 = (fConst1 * fSlow637);
		float 	fSlow654 = (fSlow538 * fSlow200);
		float 	fSlow655 = float(fslider20);
		float 	fSlow656 = (fSlow655 + 0.75f);
		float 	fSlow657 = (fConst1 * fSlow656);
		float 	fSlow658 = float(fslider21);
		float 	fSlow659 = (18.75f * fSlow658);
		float 	fSlow660 = (fSlow659 + 56.25f);
		float 	fSlow661 = powf((0.010101010101010102f * min((float)99, fSlow660)),0.69999999999999996f);
		float 	fSlow662 = powf((0.014705882352941176f * (float((fSlow660 >= 30.0f)) * min((fSlow659 + 26.25f), (float)68))),1.8f);
		int 	iSlow663 = int((0.0f > fSlow660));
		float 	fSlow664 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow656))) + 48.0f) * fSlow42));
		float 	fSlow665 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow664 + 25.0f))));
		float 	fSlow666 = max(0.0080000000000000002f, (318.0f * powf(fSlow665,12.6f)));
		float 	fSlow667 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow665)));
		float 	fSlow668 = (24.75f * fSlow658);
		float 	fSlow669 = (fSlow668 + 74.25f);
		float 	fSlow670 = powf((0.010101010101010102f * min((float)99, fSlow669)),0.69999999999999996f);
		float 	fSlow671 = powf((0.014705882352941176f * (float((fSlow669 >= 30.0f)) * min((fSlow668 + 44.25f), (float)68))),1.8f);
		int 	iSlow672 = int((fSlow660 > fSlow669));
		int 	iSlow673 = int((fSlow669 > 0.0f));
		float 	fSlow674 = ((iSlow673)?fSlow671:fSlow670);
		float 	fSlow675 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow664 + 96.0f))));
		float 	fSlow676 = max(0.001f, fabsf((-1 * (((iSlow673)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow675))):max(0.0080000000000000002f, (318.0f * powf(fSlow675,12.6f)))) * fSlow674))));
		float 	fSlow677 = (fSlow676 + max(0.001f, fabsf((((iSlow672)?fSlow667:fSlow666) * (((iSlow672)?fSlow662:fSlow661) - ((iSlow672)?fSlow671:fSlow670))))));
		float 	fSlow678 = (fSlow677 + max(0.001f, fabsf((((iSlow663)?fSlow667:fSlow666) * ((iSlow663)?fSlow662:fSlow661)))));
		float 	fSlow679 = (0 - (fConst0 * (fSlow677 - fSlow678)));
		float 	fSlow680 = (fConst0 * fSlow677);
		float 	fSlow681 = (fConst0 * fSlow678);
		float 	fSlow682 = float(fbutton4);
		int 	iSlow683 = int(((fSlow682 == 0.0f) > 0));
		float 	fSlow684 = (0 - (fConst0 * (fSlow676 - fSlow677)));
		float 	fSlow685 = (fConst0 * fSlow676);
		float 	fSlow686 = (-18.0f - (6.0f * fSlow658));
		float 	fSlow687 = (fConst1 * fSlow669);
		int 	iSlow688 = (fSlow682 > 0.0f);
		float 	fSlow689 = float(iSlow688);
		int 	iSlow690 = int(iSlow688);
		int 	iSlow691 = int((iSlow688 > 0));
		float 	fSlow692 = (fConst4 * fSlow655);
		float 	fSlow693 = (38.446969696969695f * fSlow658);
		float 	fSlow694 = (fSlow693 + 5.4924242424242422f);
		float 	fSlow695 = powf((0.010101010101010102f * min((float)99, fSlow694)),0.69999999999999996f);
		float 	fSlow696 = powf((0.014705882352941176f * (float((fSlow694 >= 30.0f)) * min((fSlow693 + -24.507575757575758f), (float)68))),1.8f);
		int 	iSlow697 = int((0.0f > fSlow694));
		float 	fSlow698 = (0.057142857142857148f * (((17.312340490667559f * logf((0.031818181818181815f * fSlow655))) + 48.0f) * fSlow77));
		float 	fSlow699 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow698 + 35.0f))));
		float 	fSlow700 = (50.75f * fSlow658);
		float 	fSlow701 = (fSlow700 + 7.25f);
		float 	fSlow702 = powf((0.010101010101010102f * min((float)99, fSlow701)),0.69999999999999996f);
		float 	fSlow703 = powf((0.014705882352941176f * (float((fSlow701 >= 30.0f)) * min((fSlow700 + -22.75f), (float)68))),1.8f);
		int 	iSlow704 = int((fSlow694 > fSlow701));
		float 	fSlow705 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow698 + 50.0f))));
		int 	iSlow706 = int((fSlow701 > 0.0f));
		float 	fSlow707 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow698 + 95.0f))));
		float 	fSlow708 = max(0.001f, fabsf((-1 * (((iSlow706)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow707))):max(0.0080000000000000002f, (318.0f * powf(fSlow707,12.6f)))) * ((iSlow706)?fSlow703:fSlow702)))));
		float 	fSlow709 = (fSlow708 + max(0.001f, fabsf((((iSlow704)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow705))):max(0.0080000000000000002f, (318.0f * powf(fSlow705,12.6f)))) * (((iSlow704)?fSlow696:fSlow695) - ((iSlow704)?fSlow703:fSlow702))))));
		float 	fSlow710 = (fSlow709 + max(0.001f, fabsf((((iSlow697)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow699))):max(0.0080000000000000002f, (318.0f * powf(fSlow699,12.6f)))) * ((iSlow697)?fSlow696:fSlow695)))));
		float 	fSlow711 = (0 - (fConst0 * (fSlow709 - fSlow710)));
		float 	fSlow712 = (fConst0 * fSlow709);
		float 	fSlow713 = (fConst0 * fSlow710);
		float 	fSlow714 = (0 - (fConst0 * (fSlow708 - fSlow709)));
		float 	fSlow715 = (fConst0 * fSlow708);
		float 	fSlow716 = (-1.7575757575757578f - (12.303030303030305f * fSlow658));
		float 	fSlow717 = (fConst1 * fSlow701);
		float 	fSlow718 = (fConst1 * fSlow655);
		float 	fSlow719 = (23.75f * fSlow658);
		float 	fSlow720 = (fSlow719 + 71.25f);
		float 	fSlow721 = powf((0.010101010101010102f * min((float)99, fSlow720)),0.69999999999999996f);
		float 	fSlow722 = powf((0.014705882352941176f * (float((fSlow720 >= 30.0f)) * min((fSlow719 + 41.25f), (float)68))),1.8f);
		int 	iSlow723 = int((0.0f > fSlow720));
		float 	fSlow724 = ((17.312340490667559f * logf((0.0022727272727272726f * fSlow655))) + 48.0f);
		float 	fSlow725 = (0.057142857142857148f * (fSlow724 * fSlow104));
		float 	fSlow726 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow725 + 20.0f))));
		float 	fSlow727 = max(0.0080000000000000002f, (318.0f * powf(fSlow726,12.6f)));
		float 	fSlow728 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow726)));
		int 	iSlow729 = int((fSlow720 > fSlow669));
		float 	fSlow730 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow725 + 95.0f))));
		float 	fSlow731 = max(0.001f, fabsf((-1 * (fSlow674 * ((iSlow673)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow730))):max(0.0080000000000000002f, (318.0f * powf(fSlow730,12.6f))))))));
		float 	fSlow732 = (fSlow731 + max(0.001f, fabsf((((iSlow729)?fSlow728:fSlow727) * (((iSlow729)?fSlow722:fSlow721) - ((iSlow729)?fSlow671:fSlow670))))));
		float 	fSlow733 = (fSlow732 + max(0.001f, fabsf((((iSlow723)?fSlow728:fSlow727) * ((iSlow723)?fSlow722:fSlow721)))));
		float 	fSlow734 = (0 - (fConst0 * (fSlow732 - fSlow733)));
		float 	fSlow735 = (fConst0 * fSlow732);
		float 	fSlow736 = (fConst0 * fSlow733);
		float 	fSlow737 = (0 - (fConst0 * (fSlow731 - fSlow732)));
		float 	fSlow738 = (fConst0 * fSlow731);
		float 	fSlow739 = (-3.0f - fSlow658);
		float 	fSlow740 = (64.053030303030297f * fSlow658);
		float 	fSlow741 = (fSlow740 + 21.3510101010101f);
		float 	fSlow742 = powf((0.010101010101010102f * min((float)99, fSlow741)),0.69999999999999996f);
		float 	fSlow743 = powf((0.014705882352941176f * (float((fSlow741 >= 30.0f)) * min((fSlow740 + -8.6489898989898997f), (float)68))),1.8f);
		int 	iSlow744 = int((0.0f > fSlow741));
		float 	fSlow745 = (0.057142857142857148f * (fSlow724 * fSlow126));
		float 	fSlow746 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow745 + 20.0f))));
		float 	fSlow747 = (66.75f * fSlow658);
		float 	fSlow748 = (fSlow747 + 22.25f);
		float 	fSlow749 = powf((0.010101010101010102f * min((float)99, fSlow748)),0.69999999999999996f);
		float 	fSlow750 = powf((0.014705882352941176f * (float((fSlow748 >= 30.0f)) * min((fSlow747 + -7.75f), (float)68))),1.8f);
		int 	iSlow751 = int((fSlow741 > fSlow748));
		float 	fSlow752 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow745 + 29.0f))));
		int 	iSlow753 = int((fSlow748 > 0.0f));
		float 	fSlow754 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow745 + 95.0f))));
		float 	fSlow755 = max(0.001f, fabsf((-1 * (((iSlow753)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow754))):max(0.0080000000000000002f, (318.0f * powf(fSlow754,12.6f)))) * ((iSlow753)?fSlow750:fSlow749)))));
		float 	fSlow756 = (fSlow755 + max(0.001f, fabsf((((iSlow751)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow752))):max(0.0080000000000000002f, (318.0f * powf(fSlow752,12.6f)))) * (((iSlow751)?fSlow743:fSlow742) - ((iSlow751)?fSlow750:fSlow749))))));
		float 	fSlow757 = (fSlow756 + max(0.001f, fabsf((((iSlow744)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow746))):max(0.0080000000000000002f, (318.0f * powf(fSlow746,12.6f)))) * ((iSlow744)?fSlow743:fSlow742)))));
		float 	fSlow758 = (0 - (fConst0 * (fSlow756 - fSlow757)));
		float 	fSlow759 = (fConst0 * fSlow756);
		float 	fSlow760 = (fConst0 * fSlow757);
		float 	fSlow761 = (0 - (fConst0 * (fSlow755 - fSlow756)));
		float 	fSlow762 = (fConst0 * fSlow755);
		float 	fSlow763 = (-0.89898989898989967f - (2.6969696969697026f * fSlow658));
		float 	fSlow764 = (fConst1 * fSlow748);
		float 	fSlow765 = (fSlow655 + -1.75f);
		float 	fSlow766 = (fConst1 * fSlow765);
		float 	fSlow767 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow765))) + 48.0f) * fSlow149));
		float 	fSlow768 = max(0.0080000000000000002f, (318.0f * powf((0.007874015748031496f * (127.0f - min((float)99, (fSlow767 + 20.0f)))),12.6f)));
		float 	fSlow769 = max(0.001f, fabsf((-1 * max(0.0030000000000000001f, (38.0f * faustpower<12>((0.007874015748031496f * (127.0f - min((float)99, (fSlow767 + 95.0f))))))))));
		float 	fSlow770 = (fSlow769 + max(0.001f, fabsf((0 - (0.028457312138301938f * fSlow768)))));
		float 	fSlow771 = (fConst0 * fSlow770);
		float 	fSlow772 = (fSlow770 + max(0.001f, fabsf((0.97154268786169806f * fSlow768))));
		float 	fSlow773 = (fConst0 * fSlow772);
		float 	fSlow774 = (1.0f / (0 - (fConst0 * (fSlow770 - fSlow772))));
		float 	fSlow775 = (fConst0 * fSlow769);
		float 	fSlow776 = (1.0f / (0 - (fConst0 * (fSlow769 - fSlow770))));
		float 	fSlow777 = (fConst5 / fSlow769);
		float 	fSlow778 = (fSlow655 + 1.75f);
		float 	fSlow779 = (fConst1 * fSlow778);
		float 	fSlow780 = (56.856060606060609f * fSlow658);
		float 	fSlow781 = (fSlow780 + 18.952020202020204f);
		float 	fSlow782 = powf((0.010101010101010102f * min((float)99, fSlow781)),0.69999999999999996f);
		float 	fSlow783 = powf((0.014705882352941176f * (float((fSlow781 >= 30.0f)) * min((fSlow780 + -11.047979797979796f), (float)68))),1.8f);
		int 	iSlow784 = int((0.0f > fSlow781));
		float 	fSlow785 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow778))) + 48.0f) * fSlow168));
		float 	fSlow786 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow785 + 20.0f))));
		float 	fSlow787 = (59.25f * fSlow658);
		float 	fSlow788 = (fSlow787 + 19.75f);
		float 	fSlow789 = powf((0.010101010101010102f * min((float)99, fSlow788)),0.69999999999999996f);
		float 	fSlow790 = powf((0.014705882352941176f * (float((fSlow788 >= 30.0f)) * min((fSlow787 + -10.25f), (float)68))),1.8f);
		int 	iSlow791 = int((fSlow781 > fSlow788));
		float 	fSlow792 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow785 + 29.0f))));
		int 	iSlow793 = int((fSlow788 > 0.0f));
		float 	fSlow794 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow785 + 95.0f))));
		float 	fSlow795 = max(0.001f, fabsf((-1 * (((iSlow793)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow794))):max(0.0080000000000000002f, (318.0f * powf(fSlow794,12.6f)))) * ((iSlow793)?fSlow790:fSlow789)))));
		float 	fSlow796 = (fSlow795 + max(0.001f, fabsf((((iSlow791)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow792))):max(0.0080000000000000002f, (318.0f * powf(fSlow792,12.6f)))) * (((iSlow791)?fSlow783:fSlow782) - ((iSlow791)?fSlow790:fSlow789))))));
		float 	fSlow797 = (fSlow796 + max(0.001f, fabsf((((iSlow784)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow786))):max(0.0080000000000000002f, (318.0f * powf(fSlow786,12.6f)))) * ((iSlow784)?fSlow783:fSlow782)))));
		float 	fSlow798 = (0 - (fConst0 * (fSlow796 - fSlow797)));
		float 	fSlow799 = (fConst0 * fSlow796);
		float 	fSlow800 = (fConst0 * fSlow797);
		float 	fSlow801 = (0 - (fConst0 * (fSlow795 - fSlow796)));
		float 	fSlow802 = (fConst0 * fSlow795);
		float 	fSlow803 = (-0.79797979797979579f - (2.3939393939393909f * fSlow658));
		float 	fSlow804 = (fConst1 * fSlow788);
		float 	fSlow805 = (fSlow689 * fSlow200);
		float 	fSlow806 = float(fslider22);
		float 	fSlow807 = (fSlow806 + 0.75f);
		float 	fSlow808 = (fConst1 * fSlow807);
		float 	fSlow809 = float(fslider23);
		float 	fSlow810 = (18.75f * fSlow809);
		float 	fSlow811 = (fSlow810 + 56.25f);
		float 	fSlow812 = powf((0.010101010101010102f * min((float)99, fSlow811)),0.69999999999999996f);
		float 	fSlow813 = powf((0.014705882352941176f * (float((fSlow811 >= 30.0f)) * min((fSlow810 + 26.25f), (float)68))),1.8f);
		int 	iSlow814 = int((0.0f > fSlow811));
		float 	fSlow815 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow807))) + 48.0f) * fSlow42));
		float 	fSlow816 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow815 + 25.0f))));
		float 	fSlow817 = max(0.0080000000000000002f, (318.0f * powf(fSlow816,12.6f)));
		float 	fSlow818 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow816)));
		float 	fSlow819 = (24.75f * fSlow809);
		float 	fSlow820 = (fSlow819 + 74.25f);
		float 	fSlow821 = powf((0.010101010101010102f * min((float)99, fSlow820)),0.69999999999999996f);
		float 	fSlow822 = powf((0.014705882352941176f * (float((fSlow820 >= 30.0f)) * min((fSlow819 + 44.25f), (float)68))),1.8f);
		int 	iSlow823 = int((fSlow811 > fSlow820));
		int 	iSlow824 = int((fSlow820 > 0.0f));
		float 	fSlow825 = ((iSlow824)?fSlow822:fSlow821);
		float 	fSlow826 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow815 + 96.0f))));
		float 	fSlow827 = max(0.001f, fabsf((-1 * (((iSlow824)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow826))):max(0.0080000000000000002f, (318.0f * powf(fSlow826,12.6f)))) * fSlow825))));
		float 	fSlow828 = (fSlow827 + max(0.001f, fabsf((((iSlow823)?fSlow818:fSlow817) * (((iSlow823)?fSlow813:fSlow812) - ((iSlow823)?fSlow822:fSlow821))))));
		float 	fSlow829 = (fSlow828 + max(0.001f, fabsf((((iSlow814)?fSlow818:fSlow817) * ((iSlow814)?fSlow813:fSlow812)))));
		float 	fSlow830 = (0 - (fConst0 * (fSlow828 - fSlow829)));
		float 	fSlow831 = (fConst0 * fSlow828);
		float 	fSlow832 = (fConst0 * fSlow829);
		float 	fSlow833 = float(fbutton5);
		int 	iSlow834 = int(((fSlow833 == 0.0f) > 0));
		float 	fSlow835 = (0 - (fConst0 * (fSlow827 - fSlow828)));
		float 	fSlow836 = (fConst0 * fSlow827);
		float 	fSlow837 = (-18.0f - (6.0f * fSlow809));
		float 	fSlow838 = (fConst1 * fSlow820);
		int 	iSlow839 = (fSlow833 > 0.0f);
		float 	fSlow840 = float(iSlow839);
		int 	iSlow841 = int(iSlow839);
		int 	iSlow842 = int((iSlow839 > 0));
		float 	fSlow843 = (fConst4 * fSlow806);
		float 	fSlow844 = (38.446969696969695f * fSlow809);
		float 	fSlow845 = (fSlow844 + 5.4924242424242422f);
		float 	fSlow846 = powf((0.010101010101010102f * min((float)99, fSlow845)),0.69999999999999996f);
		float 	fSlow847 = powf((0.014705882352941176f * (float((fSlow845 >= 30.0f)) * min((fSlow844 + -24.507575757575758f), (float)68))),1.8f);
		int 	iSlow848 = int((0.0f > fSlow845));
		float 	fSlow849 = (0.057142857142857148f * (((17.312340490667559f * logf((0.031818181818181815f * fSlow806))) + 48.0f) * fSlow77));
		float 	fSlow850 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow849 + 35.0f))));
		float 	fSlow851 = (50.75f * fSlow809);
		float 	fSlow852 = (fSlow851 + 7.25f);
		float 	fSlow853 = powf((0.010101010101010102f * min((float)99, fSlow852)),0.69999999999999996f);
		float 	fSlow854 = powf((0.014705882352941176f * (float((fSlow852 >= 30.0f)) * min((fSlow851 + -22.75f), (float)68))),1.8f);
		int 	iSlow855 = int((fSlow845 > fSlow852));
		float 	fSlow856 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow849 + 50.0f))));
		int 	iSlow857 = int((fSlow852 > 0.0f));
		float 	fSlow858 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow849 + 95.0f))));
		float 	fSlow859 = max(0.001f, fabsf((-1 * (((iSlow857)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow858))):max(0.0080000000000000002f, (318.0f * powf(fSlow858,12.6f)))) * ((iSlow857)?fSlow854:fSlow853)))));
		float 	fSlow860 = (fSlow859 + max(0.001f, fabsf((((iSlow855)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow856))):max(0.0080000000000000002f, (318.0f * powf(fSlow856,12.6f)))) * (((iSlow855)?fSlow847:fSlow846) - ((iSlow855)?fSlow854:fSlow853))))));
		float 	fSlow861 = (fSlow860 + max(0.001f, fabsf((((iSlow848)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow850))):max(0.0080000000000000002f, (318.0f * powf(fSlow850,12.6f)))) * ((iSlow848)?fSlow847:fSlow846)))));
		float 	fSlow862 = (0 - (fConst0 * (fSlow860 - fSlow861)));
		float 	fSlow863 = (fConst0 * fSlow860);
		float 	fSlow864 = (fConst0 * fSlow861);
		float 	fSlow865 = (0 - (fConst0 * (fSlow859 - fSlow860)));
		float 	fSlow866 = (fConst0 * fSlow859);
		float 	fSlow867 = (-1.7575757575757578f - (12.303030303030305f * fSlow809));
		float 	fSlow868 = (fConst1 * fSlow852);
		float 	fSlow869 = (fConst1 * fSlow806);
		float 	fSlow870 = (23.75f * fSlow809);
		float 	fSlow871 = (fSlow870 + 71.25f);
		float 	fSlow872 = powf((0.010101010101010102f * min((float)99, fSlow871)),0.69999999999999996f);
		float 	fSlow873 = powf((0.014705882352941176f * (float((fSlow871 >= 30.0f)) * min((fSlow870 + 41.25f), (float)68))),1.8f);
		int 	iSlow874 = int((0.0f > fSlow871));
		float 	fSlow875 = ((17.312340490667559f * logf((0.0022727272727272726f * fSlow806))) + 48.0f);
		float 	fSlow876 = (0.057142857142857148f * (fSlow875 * fSlow104));
		float 	fSlow877 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow876 + 20.0f))));
		float 	fSlow878 = max(0.0080000000000000002f, (318.0f * powf(fSlow877,12.6f)));
		float 	fSlow879 = max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow877)));
		int 	iSlow880 = int((fSlow871 > fSlow820));
		float 	fSlow881 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow876 + 95.0f))));
		float 	fSlow882 = max(0.001f, fabsf((-1 * (fSlow825 * ((iSlow824)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow881))):max(0.0080000000000000002f, (318.0f * powf(fSlow881,12.6f))))))));
		float 	fSlow883 = (fSlow882 + max(0.001f, fabsf((((iSlow880)?fSlow879:fSlow878) * (((iSlow880)?fSlow873:fSlow872) - ((iSlow880)?fSlow822:fSlow821))))));
		float 	fSlow884 = (fSlow883 + max(0.001f, fabsf((((iSlow874)?fSlow879:fSlow878) * ((iSlow874)?fSlow873:fSlow872)))));
		float 	fSlow885 = (0 - (fConst0 * (fSlow883 - fSlow884)));
		float 	fSlow886 = (fConst0 * fSlow883);
		float 	fSlow887 = (fConst0 * fSlow884);
		float 	fSlow888 = (0 - (fConst0 * (fSlow882 - fSlow883)));
		float 	fSlow889 = (fConst0 * fSlow882);
		float 	fSlow890 = (-3.0f - fSlow809);
		float 	fSlow891 = (64.053030303030297f * fSlow809);
		float 	fSlow892 = (fSlow891 + 21.3510101010101f);
		float 	fSlow893 = powf((0.010101010101010102f * min((float)99, fSlow892)),0.69999999999999996f);
		float 	fSlow894 = powf((0.014705882352941176f * (float((fSlow892 >= 30.0f)) * min((fSlow891 + -8.6489898989898997f), (float)68))),1.8f);
		int 	iSlow895 = int((0.0f > fSlow892));
		float 	fSlow896 = (0.057142857142857148f * (fSlow875 * fSlow126));
		float 	fSlow897 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow896 + 20.0f))));
		float 	fSlow898 = (66.75f * fSlow809);
		float 	fSlow899 = (fSlow898 + 22.25f);
		float 	fSlow900 = powf((0.010101010101010102f * min((float)99, fSlow899)),0.69999999999999996f);
		float 	fSlow901 = powf((0.014705882352941176f * (float((fSlow899 >= 30.0f)) * min((fSlow898 + -7.75f), (float)68))),1.8f);
		int 	iSlow902 = int((fSlow892 > fSlow899));
		float 	fSlow903 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow896 + 29.0f))));
		int 	iSlow904 = int((fSlow899 > 0.0f));
		float 	fSlow905 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow896 + 95.0f))));
		float 	fSlow906 = max(0.001f, fabsf((-1 * (((iSlow904)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow905))):max(0.0080000000000000002f, (318.0f * powf(fSlow905,12.6f)))) * ((iSlow904)?fSlow901:fSlow900)))));
		float 	fSlow907 = (fSlow906 + max(0.001f, fabsf((((iSlow902)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow903))):max(0.0080000000000000002f, (318.0f * powf(fSlow903,12.6f)))) * (((iSlow902)?fSlow894:fSlow893) - ((iSlow902)?fSlow901:fSlow900))))));
		float 	fSlow908 = (fSlow907 + max(0.001f, fabsf((((iSlow895)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow897))):max(0.0080000000000000002f, (318.0f * powf(fSlow897,12.6f)))) * ((iSlow895)?fSlow894:fSlow893)))));
		float 	fSlow909 = (0 - (fConst0 * (fSlow907 - fSlow908)));
		float 	fSlow910 = (fConst0 * fSlow907);
		float 	fSlow911 = (fConst0 * fSlow908);
		float 	fSlow912 = (0 - (fConst0 * (fSlow906 - fSlow907)));
		float 	fSlow913 = (fConst0 * fSlow906);
		float 	fSlow914 = (-0.89898989898989967f - (2.6969696969697026f * fSlow809));
		float 	fSlow915 = (fConst1 * fSlow899);
		float 	fSlow916 = (fSlow806 + -1.75f);
		float 	fSlow917 = (fConst1 * fSlow916);
		float 	fSlow918 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow916))) + 48.0f) * fSlow149));
		float 	fSlow919 = max(0.0080000000000000002f, (318.0f * powf((0.007874015748031496f * (127.0f - min((float)99, (fSlow918 + 20.0f)))),12.6f)));
		float 	fSlow920 = max(0.001f, fabsf((-1 * max(0.0030000000000000001f, (38.0f * faustpower<12>((0.007874015748031496f * (127.0f - min((float)99, (fSlow918 + 95.0f))))))))));
		float 	fSlow921 = (fSlow920 + max(0.001f, fabsf((0 - (0.028457312138301938f * fSlow919)))));
		float 	fSlow922 = (fConst0 * fSlow921);
		float 	fSlow923 = (fSlow921 + max(0.001f, fabsf((0.97154268786169806f * fSlow919))));
		float 	fSlow924 = (fConst0 * fSlow923);
		float 	fSlow925 = (1.0f / (0 - (fConst0 * (fSlow921 - fSlow923))));
		float 	fSlow926 = (fConst0 * fSlow920);
		float 	fSlow927 = (1.0f / (0 - (fConst0 * (fSlow920 - fSlow921))));
		float 	fSlow928 = (fConst5 / fSlow920);
		float 	fSlow929 = (fSlow806 + 1.75f);
		float 	fSlow930 = (fConst1 * fSlow929);
		float 	fSlow931 = (56.856060606060609f * fSlow809);
		float 	fSlow932 = (fSlow931 + 18.952020202020204f);
		float 	fSlow933 = powf((0.010101010101010102f * min((float)99, fSlow932)),0.69999999999999996f);
		float 	fSlow934 = powf((0.014705882352941176f * (float((fSlow932 >= 30.0f)) * min((fSlow931 + -11.047979797979796f), (float)68))),1.8f);
		int 	iSlow935 = int((0.0f > fSlow932));
		float 	fSlow936 = (0.057142857142857148f * (((17.312340490667559f * logf((0.0022727272727272726f * fSlow929))) + 48.0f) * fSlow168));
		float 	fSlow937 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow936 + 20.0f))));
		float 	fSlow938 = (59.25f * fSlow809);
		float 	fSlow939 = (fSlow938 + 19.75f);
		float 	fSlow940 = powf((0.010101010101010102f * min((float)99, fSlow939)),0.69999999999999996f);
		float 	fSlow941 = powf((0.014705882352941176f * (float((fSlow939 >= 30.0f)) * min((fSlow938 + -10.25f), (float)68))),1.8f);
		int 	iSlow942 = int((fSlow932 > fSlow939));
		float 	fSlow943 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow936 + 29.0f))));
		int 	iSlow944 = int((fSlow939 > 0.0f));
		float 	fSlow945 = (0.007874015748031496f * (127.0f - min((float)99, (fSlow936 + 95.0f))));
		float 	fSlow946 = max(0.001f, fabsf((-1 * (((iSlow944)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow945))):max(0.0080000000000000002f, (318.0f * powf(fSlow945,12.6f)))) * ((iSlow944)?fSlow941:fSlow940)))));
		float 	fSlow947 = (fSlow946 + max(0.001f, fabsf((((iSlow942)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow943))):max(0.0080000000000000002f, (318.0f * powf(fSlow943,12.6f)))) * (((iSlow942)?fSlow934:fSlow933) - ((iSlow942)?fSlow941:fSlow940))))));
		float 	fSlow948 = (fSlow947 + max(0.001f, fabsf((((iSlow935)?max(0.0030000000000000001f, (38.0f * faustpower<12>(fSlow937))):max(0.0080000000000000002f, (318.0f * powf(fSlow937,12.6f)))) * ((iSlow935)?fSlow934:fSlow933)))));
		float 	fSlow949 = (0 - (fConst0 * (fSlow947 - fSlow948)));
		float 	fSlow950 = (fConst0 * fSlow947);
		float 	fSlow951 = (fConst0 * fSlow948);
		float 	fSlow952 = (0 - (fConst0 * (fSlow946 - fSlow947)));
		float 	fSlow953 = (fConst0 * fSlow946);
		float 	fSlow954 = (-0.79797979797979579f - (2.3939393939393909f * fSlow809));
		float 	fSlow955 = (fConst1 * fSlow939);
		float 	fSlow956 = (fSlow840 * fSlow200);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec1[0] = (fSlow35 + (fRec1[1] - floorf((fSlow35 + fRec1[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm1 = (65536.0f * fRec1[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec3[0] = ((iSlow62)?0.0f:min(fSlow60, (fRec3[1] + 1.0f)));
				iTempPerm2 = int((fRec3[0] < fSlow59));
				iTempPerm3 = int((fRec3[0] < fSlow64));
				fRec2[0] = ((iSlow69)?(fSlow68 * ((iTempPerm2)?((iTempPerm3)?((int((fRec3[0] < 0.0f)))?0.0f:((iTempPerm3)?(fSlow66 * (fRec3[0] / fSlow55)):fSlow48)):((iTempPerm2)?(fSlow47 + ((fSlow65 * ((fRec3[0] - fSlow64) / fSlow63)) + 74.25f)):fSlow38)):((int((fRec3[0] < fSlow60)))?(fSlow37 + (((0 - (fSlow38 * (fRec3[0] - fSlow59))) / fSlow58) + 56.25f)):0.0f))):fRec2[1]);
				fRec4[0] = ((iSlow70)?0.0f:min(fConst2, (fRec4[1] + 1.0f)));
				iTempPerm4 = int((fRec4[0] < fConst2));
				iTempPerm5 = int((fRec4[0] < 0.0f));
				fTempPerm6 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm5)?fRec2[0]:((iTempPerm4)?(fRec2[0] + (fConst3 * (0 - (fRec4[0] * fRec2[0])))):0.0f)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm7 = (fTempPerm6 * ftbl0[(((int(fTempPerm1) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec5[0] = (fSlow71 + (fRec5[1] - floorf((fSlow71 + fRec5[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm8 = (65536.0f * fRec5[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec7[0] = ((iSlow62)?0.0f:min(fSlow93, (fRec7[1] + 1.0f)));
				iTempPerm9 = int((fRec7[0] < fSlow92));
				iTempPerm10 = int((fRec7[0] < fSlow95));
				fRec6[0] = ((iSlow69)?(fSlow68 * ((iTempPerm9)?((iTempPerm10)?((int((fRec7[0] < 0.0f)))?0.0f:((iTempPerm10)?(fSlow97 * (fRec7[0] / fSlow88)):fSlow81)):((iTempPerm9)?(fSlow80 + ((fSlow96 * ((fRec7[0] - fSlow95) / fSlow94)) + 7.25f)):fSlow73)):((int((fRec7[0] < fSlow93)))?(fSlow72 + (((0 - (fSlow73 * (fRec7[0] - fSlow92))) / fSlow91) + 5.4924242424242422f)):0.0f))):fRec6[1]);
				fTempPerm11 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm5)?fRec6[0]:((iTempPerm4)?(fRec6[0] + (fConst3 * (0 - (fRec4[0] * fRec6[0])))):0.0f)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm12 = (fTempPerm11 * ftbl0[(((int(fTempPerm8) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm13 = (fTempPerm12 + fTempPerm7);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec8[0] = (fSlow98 + (fRec8[1] - floorf((fSlow98 + fRec8[1]))));
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm14 = (65536.0f * fRec8[0]);
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm15 = ftbl0[(((int(fTempPerm14) % 65536) + 65536) % 65536)];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec10[0] = ((iSlow62)?0.0f:min(fSlow117, (fRec10[1] + 1.0f)));
				iTempPerm16 = int((fRec10[0] < fSlow116));
				iTempPerm17 = int((fRec10[0] < fSlow119));
				fRec9[0] = ((iSlow69)?(fSlow68 * ((iTempPerm16)?((iTempPerm17)?((int((fRec10[0] < 0.0f)))?0.0f:((iTempPerm17)?(fSlow66 * (fRec10[0] / fSlow112)):fSlow48)):((iTempPerm16)?(fSlow47 + ((fSlow120 * ((fRec10[0] - fSlow119) / fSlow118)) + 74.25f)):fSlow100)):((int((fRec10[0] < fSlow117)))?(fSlow99 + (((0 - (fSlow100 * (fRec10[0] - fSlow116))) / fSlow115) + 71.25f)):0.0f))):fRec9[1]);
				fTempPerm18 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm5)?fRec9[0]:((iTempPerm4)?(fRec9[0] + (fConst3 * (0 - (fRec4[0] * fRec9[0])))):0.0f)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm19 = (fTempPerm18 * fTempPerm15);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm20 = (fTempPerm19 + fTempPerm13);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec12[0] = ((iSlow62)?0.0f:min(fSlow142, (fRec12[1] + 1.0f)));
				iTempPerm21 = int((fRec12[0] < fSlow141));
				iTempPerm22 = int((fRec12[0] < fSlow144));
				fRec11[0] = ((iSlow69)?(fSlow68 * ((iTempPerm21)?((iTempPerm22)?((int((fRec12[0] < 0.0f)))?0.0f:((iTempPerm22)?(fSlow146 * (fRec12[0] / fSlow137)):fSlow130)):((iTempPerm21)?(fSlow129 + ((fSlow145 * ((fRec12[0] - fSlow144) / fSlow143)) + 22.25f)):fSlow122)):((int((fRec12[0] < fSlow142)))?(fSlow121 + (((0 - (fSlow122 * (fRec12[0] - fSlow141))) / fSlow140) + 21.3510101010101f)):0.0f))):fRec11[1]);
				fTempPerm23 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm5)?fRec11[0]:((iTempPerm4)?(fRec11[0] + (fConst3 * (0 - (fRec4[0] * fRec11[0])))):0.0f)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm24 = (fTempPerm23 * fTempPerm15);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm25 = (fTempPerm24 + fTempPerm20);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec13[0] = (fSlow148 + (fRec13[1] - floorf((fSlow148 + fRec13[1]))));
				fRec15[0] = ((iSlow62)?0.0f:min(fSlow156, (fRec15[1] + 1.0f)));
				iTempPerm26 = int((fRec15[0] < fSlow154));
				iTempPerm27 = int((fRec15[0] < fSlow158));
				fRec14[0] = ((iSlow69)?(fSlow68 * ((iTempPerm26)?((iTempPerm27)?((int((fRec15[0] < 0.0f)))?0.0f:((iTempPerm27)?(fSlow160 * fRec15[0]):99.0f)):((iTempPerm26)?((fSlow159 * (0 - (4.0f * (fRec15[0] - fSlow158)))) + 99.0f):95.0f)):((int((fRec15[0] < fSlow156)))?((fSlow157 * (0 - (95.0f * (fRec15[0] - fSlow154)))) + 95.0f):0.0f))):fRec14[1]);
				fTempPerm28 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm5)?fRec14[0]:((iTempPerm4)?(fRec14[0] + (fConst3 * (0 - (fRec4[0] * fRec14[0])))):0.0f)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm29 = (fTempPerm28 * ftbl0[(((int((65536.0f * fRec13[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec16[0] = (fSlow162 + (fRec16[1] - floorf((fSlow162 + fRec16[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm30 = (65536.0f * fRec16[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec18[0] = ((iSlow62)?0.0f:min(fSlow184, (fRec18[1] + 1.0f)));
				iTempPerm31 = int((fRec18[0] < fSlow183));
				iTempPerm32 = int((fRec18[0] < fSlow186));
				fRec17[0] = ((iSlow69)?(fSlow68 * ((iTempPerm31)?((iTempPerm32)?((int((fRec18[0] < 0.0f)))?0.0f:((iTempPerm32)?(fSlow188 * (fRec18[0] / fSlow179)):fSlow172)):((iTempPerm31)?(fSlow171 + ((fSlow187 * ((fRec18[0] - fSlow186) / fSlow185)) + 19.75f)):fSlow164)):((int((fRec18[0] < fSlow184)))?(fSlow163 + (((0 - (fSlow164 * (fRec18[0] - fSlow183))) / fSlow182) + 18.952020202020204f)):0.0f))):fRec17[1]);
				fTempPerm33 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm5)?fRec17[0]:((iTempPerm4)?(fRec17[0] + (fConst3 * (0 - (fRec4[0] * fRec17[0])))):0.0f)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm34 = (fTempPerm33 * ftbl0[(((int(fTempPerm30) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm35 = (2.0879500000000002f * (fTempPerm34 + (fTempPerm29 + fTempPerm25)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec19[0] = (fTempPerm33 * ftbl0[(((int((65536.0f * (fRec16[0] + (fSlow189 * fRec19[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm36 = (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec19[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm37 = (2.0879500000000002f * (fTempPerm36 + fTempPerm25));
			}
			if (iSlow5 || iSlow3) {
				fRec20[0] = (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow189 * fRec20[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm38 = (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + fRec20[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm39 = (2.0879500000000002f * (fTempPerm34 + (fTempPerm13 + fTempPerm38)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm40 = (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + fTempPerm24))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm41 = (2.0879500000000002f * (fTempPerm36 + (fTempPerm40 + fTempPerm13)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm42 = (fTempPerm6 * ftbl0[(((int((65536.0f * (fRec1[0] + fTempPerm12))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm43 = (2.0879500000000002f * (fTempPerm34 + (fTempPerm42 + fTempPerm38)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec21[0] = (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + (fSlow189 * fRec21[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm44 = (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec5[0] + fRec21[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm45 = (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + (fTempPerm34 + fTempPerm29)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm46 = (2.0879500000000002f * (fTempPerm45 + (fTempPerm44 + fTempPerm7)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm47 = (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec5[0] + fTempPerm19))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm48 = (fTempPerm47 + fTempPerm7);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm49 = (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + (fRec19[0] + fTempPerm29)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm50 = (2.0879500000000002f * (fTempPerm49 + fTempPerm48));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm51 = (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + fRec19[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm52 = (2.0879500000000002f * (fTempPerm36 + (fTempPerm51 + fTempPerm20)));
			}
			if (iSlow9) {
				fRec22[0] = (fTempPerm33 * ftbl0[(((int((fTempPerm30 + (fSlow190 * fRec22[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm53 = ftbl0[(((int((65536.0f * (fRec8[0] + fRec22[0]))) % 65536) + 65536) % 65536)];
				fTempPerm54 = (2.0879500000000002f * (((fTempPerm13 + (fTempPerm18 * fTempPerm53)) + (fTempPerm23 * fTempPerm53)) + (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec22[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm55 = (2.0879500000000002f * (fTempPerm36 + (fTempPerm48 + fTempPerm51)));
			}
			if (iSlow28 || iSlow11) {
				fRec23[0] = (fTempPerm33 * ftbl0[(((int((fTempPerm30 + (fSlow191 * fRec23[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm56 = (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec23[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm57 = ((ftbl0[(((int((65536.0f * (fRec8[0] + fRec23[0]))) % 65536) + 65536) % 65536)] * (fTempPerm18 + (2.0879500000000002f * fTempPerm23))) + (2.0879500000000002f * (fTempPerm56 + (fTempPerm6 * ftbl0[(((int((fTempPerm1 + (136835.89120000001f * fTempPerm12))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm58 = ((fTempPerm6 * ftbl0[(((int((65536.0f * (fRec1[0] + fRec21[0]))) % 65536) + 65536) % 65536)]) + fTempPerm44);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm59 = (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm34))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm60 = (2.0879500000000002f * (fTempPerm59 + (fTempPerm58 + (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + fTempPerm34))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm61 = (2.0879500000000002f * (fTempPerm45 + fTempPerm58));
			}
			if (iSlow14) {
				fRec24[0] = (fTempPerm33 * ftbl0[(((int((fTempPerm30 + (fSlow192 * fRec24[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm62 = (fTempPerm6 * ftbl0[(((int((65536.0f * (fRec1[0] + fTempPerm47))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm63 = (2.0879500000000002f * ((fTempPerm62 + (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + fRec24[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec24[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm64 = (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + fTempPerm59))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm65 = (2.0879500000000002f * (fTempPerm6 * ftbl0[(((int((65536.0f * (fRec1[0] + (fTempPerm64 + (fRec21[0] + fTempPerm12))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec25[0] = (fTempPerm11 * ftbl0[(((int((fTempPerm8 + (fSlow193 * fRec25[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm66 = (2.0879500000000002f * (fTempPerm6 * ftbl0[(((int((65536.0f * (fRec1[0] + (fTempPerm40 + (fRec25[0] + fTempPerm59))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm67 = (2.0879500000000002f * (fTempPerm6 * ftbl0[(((int((65536.0f * (fRec1[0] + (fTempPerm40 + (fTempPerm12 + fTempPerm36))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec26[0] = (fTempPerm11 * ftbl0[(((int((fTempPerm8 + (fSlow192 * fRec26[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm68 = (fTempPerm6 * ftbl0[(((int((65536.0f * (fRec1[0] + fRec26[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm69 = (2.0879500000000002f * (fTempPerm68 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + fTempPerm45))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm70 = (2.0879500000000002f * (fTempPerm42 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + fTempPerm49))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm71 = (2.0879500000000002f * (fTempPerm42 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + (fTempPerm29 + (fRec19[0] + fTempPerm24))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec27[0] = (fTempPerm11 * ftbl0[(((int((fTempPerm8 + (fSlow194 * fRec27[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm72 = (fTempPerm6 * ftbl0[(((int((65536.0f * (fRec1[0] + fRec27[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm73 = (2.0879500000000002f * (fTempPerm72 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + (fTempPerm29 + (fTempPerm34 + fTempPerm24))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec28[0] = (fTempPerm33 * ftbl0[(((int((fTempPerm30 + (fSlow194 * fRec28[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm74 = (2.0879500000000002f * (fTempPerm62 + (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + (fRec28[0] + fTempPerm29)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec29[0] = (fTempPerm18 * ftbl0[(((int((fTempPerm14 + (fSlow194 * fRec29[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm75 = (2.0879500000000002f * (fTempPerm45 + (fTempPerm6 * ftbl0[(((int((65536.0f * (fRec1[0] + (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec5[0] + fRec29[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm76 = (2.0879500000000002f * (fTempPerm68 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + (fTempPerm59 + fTempPerm24)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec30[0] = (fTempPerm23 * ftbl0[(((int((fTempPerm14 + (fSlow191 * fRec30[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm77 = (2.0879500000000002f * (fTempPerm42 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + (fRec30[0] + fTempPerm59)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm78 = (2.0879500000000002f * (fTempPerm42 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + (fTempPerm36 + fTempPerm24)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm79 = (fTempPerm42 + fTempPerm40);
			}
			if (iSlow27) {
				fRec31[0] = (2.0879500000000002f * (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec13[0] + (fTempPerm33 * ftbl0[(((int((65536.0f * (fRec16[0] + (fSlow189 * fRec31[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm80 = (fRec31[0] + (2.0879500000000002f * fTempPerm79));
			}
			if (iSlow28) {
				fTempPerm81 = (2.0879500000000002f * (fTempPerm79 + fTempPerm56));
			}
			if (iSlow29) {
				fRec32[0] = (2.0879500000000002f * (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec13[0] + (fTempPerm33 * ftbl0[(((int((65536.0f * (fRec16[0] + (fSlow189 * fRec32[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm82 = (fRec32[0] + (2.0879500000000002f * fTempPerm62));
			}
			if (iSlow30) {
				fTempPerm83 = (2.0879500000000002f * (fTempPerm62 + (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + fTempPerm36))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm84 = (2.0879500000000002f * (fTempPerm72 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + fTempPerm64))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm85 = (2.0879500000000002f * (fTempPerm42 + (fTempPerm18 * ftbl0[(((int((65536.0f * (fRec8[0] + (fTempPerm23 * ftbl0[(((int((65536.0f * (fRec8[0] + (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec13[0] + fRec28[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec34[0] = (iSlow67 * (iRec34[1] + 1));
			iTempPerm86 = int((iRec34[0] < iSlow199));
			fTempPerm87 = expf((0 - (fConst6 / ((iSlow69)?((iTempPerm86)?fSlow198:fSlow196):fSlow195))));
			fRec33[0] = ((fRec33[1] * fTempPerm87) + (((iSlow69)?((iTempPerm86)?1.5873015873015872f:fSlow201):0.0f) * (1.0f - fTempPerm87)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec35[0] = (fSlow204 + (fRec35[1] - floorf((fSlow204 + fRec35[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm88 = (65536.0f * fRec35[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec37[0] = ((iSlow230)?0.0f:min(fSlow228, (fRec37[1] + 1.0f)));
				iTempPerm89 = int((fRec37[0] < fSlow227));
				iTempPerm90 = int((fRec37[0] < fSlow232));
				fRec36[0] = ((iSlow237)?(fSlow236 * ((iTempPerm89)?((iTempPerm90)?((int((fRec37[0] < 0.0f)))?0.0f:((iTempPerm90)?(fSlow234 * (fRec37[0] / fSlow223)):fSlow216)):((iTempPerm89)?(fSlow215 + ((fSlow233 * ((fRec37[0] - fSlow232) / fSlow231)) + 74.25f)):fSlow207)):((int((fRec37[0] < fSlow228)))?(fSlow206 + (((0 - (fSlow207 * (fRec37[0] - fSlow227))) / fSlow226) + 56.25f)):0.0f))):fRec36[1]);
				fRec38[0] = ((iSlow238)?0.0f:min(fConst2, (fRec38[1] + 1.0f)));
				iTempPerm91 = int((fRec38[0] < fConst2));
				iTempPerm92 = int((fRec38[0] < 0.0f));
				fTempPerm93 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm92)?fRec36[0]:((iTempPerm91)?(fRec36[0] + (fConst3 * (0 - (fRec38[0] * fRec36[0])))):0.0f)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm94 = (fTempPerm93 * ftbl0[(((int(fTempPerm88) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec39[0] = (fSlow239 + (fRec39[1] - floorf((fSlow239 + fRec39[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm95 = (65536.0f * fRec39[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec41[0] = ((iSlow230)?0.0f:min(fSlow260, (fRec41[1] + 1.0f)));
				iTempPerm96 = int((fRec41[0] < fSlow259));
				iTempPerm97 = int((fRec41[0] < fSlow262));
				fRec40[0] = ((iSlow237)?(fSlow236 * ((iTempPerm96)?((iTempPerm97)?((int((fRec41[0] < 0.0f)))?0.0f:((iTempPerm97)?(fSlow264 * (fRec41[0] / fSlow255)):fSlow248)):((iTempPerm96)?(fSlow247 + ((fSlow263 * ((fRec41[0] - fSlow262) / fSlow261)) + 7.25f)):fSlow241)):((int((fRec41[0] < fSlow260)))?(fSlow240 + (((0 - (fSlow241 * (fRec41[0] - fSlow259))) / fSlow258) + 5.4924242424242422f)):0.0f))):fRec40[1]);
				fTempPerm98 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm92)?fRec40[0]:((iTempPerm91)?(fRec40[0] + (fConst3 * (0 - (fRec38[0] * fRec40[0])))):0.0f)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm99 = (fTempPerm98 * ftbl0[(((int(fTempPerm95) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm100 = (fTempPerm99 + fTempPerm94);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec42[0] = (fSlow265 + (fRec42[1] - floorf((fSlow265 + fRec42[1]))));
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm101 = (65536.0f * fRec42[0]);
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm102 = ftbl0[(((int(fTempPerm101) % 65536) + 65536) % 65536)];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec44[0] = ((iSlow230)?0.0f:min(fSlow283, (fRec44[1] + 1.0f)));
				iTempPerm103 = int((fRec44[0] < fSlow282));
				iTempPerm104 = int((fRec44[0] < fSlow285));
				fRec43[0] = ((iSlow237)?(fSlow236 * ((iTempPerm103)?((iTempPerm104)?((int((fRec44[0] < 0.0f)))?0.0f:((iTempPerm104)?(fSlow234 * (fRec44[0] / fSlow278)):fSlow216)):((iTempPerm103)?(fSlow215 + ((fSlow286 * ((fRec44[0] - fSlow285) / fSlow284)) + 74.25f)):fSlow267)):((int((fRec44[0] < fSlow283)))?(fSlow266 + (((0 - (fSlow267 * (fRec44[0] - fSlow282))) / fSlow281) + 71.25f)):0.0f))):fRec43[1]);
				fTempPerm105 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm92)?fRec43[0]:((iTempPerm91)?(fRec43[0] + (fConst3 * (0 - (fRec38[0] * fRec43[0])))):0.0f)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm106 = (fTempPerm105 * fTempPerm102);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm107 = (fTempPerm106 + fTempPerm100);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec46[0] = ((iSlow230)?0.0f:min(fSlow307, (fRec46[1] + 1.0f)));
				iTempPerm108 = int((fRec46[0] < fSlow306));
				iTempPerm109 = int((fRec46[0] < fSlow309));
				fRec45[0] = ((iSlow237)?(fSlow236 * ((iTempPerm108)?((iTempPerm109)?((int((fRec46[0] < 0.0f)))?0.0f:((iTempPerm109)?(fSlow311 * (fRec46[0] / fSlow302)):fSlow295)):((iTempPerm108)?(fSlow294 + ((fSlow310 * ((fRec46[0] - fSlow309) / fSlow308)) + 22.25f)):fSlow288)):((int((fRec46[0] < fSlow307)))?(fSlow287 + (((0 - (fSlow288 * (fRec46[0] - fSlow306))) / fSlow305) + 21.3510101010101f)):0.0f))):fRec45[1]);
				fTempPerm110 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm92)?fRec45[0]:((iTempPerm91)?(fRec45[0] + (fConst3 * (0 - (fRec38[0] * fRec45[0])))):0.0f)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm111 = (fTempPerm110 * fTempPerm102);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm112 = (fTempPerm111 + fTempPerm107);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec47[0] = (fSlow313 + (fRec47[1] - floorf((fSlow313 + fRec47[1]))));
				fRec49[0] = ((iSlow230)?0.0f:min(fSlow320, (fRec49[1] + 1.0f)));
				iTempPerm113 = int((fRec49[0] < fSlow318));
				iTempPerm114 = int((fRec49[0] < fSlow322));
				fRec48[0] = ((iSlow237)?(fSlow236 * ((iTempPerm113)?((iTempPerm114)?((int((fRec49[0] < 0.0f)))?0.0f:((iTempPerm114)?(fSlow324 * fRec49[0]):99.0f)):((iTempPerm113)?((fSlow323 * (0 - (4.0f * (fRec49[0] - fSlow322)))) + 99.0f):95.0f)):((int((fRec49[0] < fSlow320)))?((fSlow321 * (0 - (95.0f * (fRec49[0] - fSlow318)))) + 95.0f):0.0f))):fRec48[1]);
				fTempPerm115 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm92)?fRec48[0]:((iTempPerm91)?(fRec48[0] + (fConst3 * (0 - (fRec38[0] * fRec48[0])))):0.0f)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm116 = (fTempPerm115 * ftbl0[(((int((65536.0f * fRec47[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec50[0] = (fSlow326 + (fRec50[1] - floorf((fSlow326 + fRec50[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm117 = (65536.0f * fRec50[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec52[0] = ((iSlow230)?0.0f:min(fSlow347, (fRec52[1] + 1.0f)));
				iTempPerm118 = int((fRec52[0] < fSlow346));
				iTempPerm119 = int((fRec52[0] < fSlow349));
				fRec51[0] = ((iSlow237)?(fSlow236 * ((iTempPerm118)?((iTempPerm119)?((int((fRec52[0] < 0.0f)))?0.0f:((iTempPerm119)?(fSlow351 * (fRec52[0] / fSlow342)):fSlow335)):((iTempPerm118)?(fSlow334 + ((fSlow350 * ((fRec52[0] - fSlow349) / fSlow348)) + 19.75f)):fSlow328)):((int((fRec52[0] < fSlow347)))?(fSlow327 + (((0 - (fSlow328 * (fRec52[0] - fSlow346))) / fSlow345) + 18.952020202020204f)):0.0f))):fRec51[1]);
				fTempPerm120 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm92)?fRec51[0]:((iTempPerm91)?(fRec51[0] + (fConst3 * (0 - (fRec38[0] * fRec51[0])))):0.0f)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm121 = (fTempPerm120 * ftbl0[(((int(fTempPerm117) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm122 = (2.0879500000000002f * (fTempPerm121 + (fTempPerm116 + fTempPerm112)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec53[0] = (fTempPerm120 * ftbl0[(((int((65536.0f * (fRec50[0] + (fSlow189 * fRec53[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm123 = (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec47[0] + fRec53[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm124 = (2.0879500000000002f * (fTempPerm123 + fTempPerm112));
			}
			if (iSlow5 || iSlow3) {
				fRec54[0] = (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec47[0] + (fSlow189 * fRec54[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm125 = (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + fRec54[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm126 = (2.0879500000000002f * (fTempPerm121 + (fTempPerm100 + fTempPerm125)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm127 = (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + fTempPerm111))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm128 = (2.0879500000000002f * (fTempPerm123 + (fTempPerm127 + fTempPerm100)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm129 = (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec35[0] + fTempPerm99))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm130 = (2.0879500000000002f * (fTempPerm121 + (fTempPerm129 + fTempPerm125)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec55[0] = (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + (fSlow189 * fRec55[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm131 = (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec39[0] + fRec55[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm132 = (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + (fTempPerm121 + fTempPerm116)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm133 = (2.0879500000000002f * (fTempPerm132 + (fTempPerm131 + fTempPerm94)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm134 = (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm106))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm135 = (fTempPerm134 + fTempPerm94);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm136 = (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + (fRec53[0] + fTempPerm116)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm137 = (2.0879500000000002f * (fTempPerm136 + fTempPerm135));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm138 = (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + fRec53[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm139 = (2.0879500000000002f * (fTempPerm123 + (fTempPerm138 + fTempPerm107)));
			}
			if (iSlow9) {
				fRec56[0] = (fTempPerm120 * ftbl0[(((int((fTempPerm117 + (fSlow190 * fRec56[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm140 = ftbl0[(((int((65536.0f * (fRec42[0] + fRec56[0]))) % 65536) + 65536) % 65536)];
				fTempPerm141 = (2.0879500000000002f * (((fTempPerm100 + (fTempPerm105 * fTempPerm140)) + (fTempPerm110 * fTempPerm140)) + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec47[0] + fRec56[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm142 = (2.0879500000000002f * (fTempPerm123 + (fTempPerm135 + fTempPerm138)));
			}
			if (iSlow28 || iSlow11) {
				fRec57[0] = (fTempPerm120 * ftbl0[(((int((fTempPerm117 + (fSlow191 * fRec57[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm143 = (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec47[0] + fRec57[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm144 = ((ftbl0[(((int((65536.0f * (fRec42[0] + fRec57[0]))) % 65536) + 65536) % 65536)] * (fTempPerm105 + (2.0879500000000002f * fTempPerm110))) + (2.0879500000000002f * (fTempPerm143 + (fTempPerm93 * ftbl0[(((int((fTempPerm88 + (136835.89120000001f * fTempPerm99))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm145 = ((fTempPerm93 * ftbl0[(((int((65536.0f * (fRec35[0] + fRec55[0]))) % 65536) + 65536) % 65536)]) + fTempPerm131);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm146 = (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec47[0] + fTempPerm121))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm147 = (2.0879500000000002f * (fTempPerm146 + (fTempPerm145 + (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + fTempPerm121))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm148 = (2.0879500000000002f * (fTempPerm132 + fTempPerm145));
			}
			if (iSlow14) {
				fRec58[0] = (fTempPerm120 * ftbl0[(((int((fTempPerm117 + (fSlow192 * fRec58[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm149 = (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec35[0] + fTempPerm134))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm150 = (2.0879500000000002f * ((fTempPerm149 + (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + fRec58[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec47[0] + fRec58[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm151 = (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + fTempPerm146))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm152 = (2.0879500000000002f * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec35[0] + (fTempPerm151 + (fRec55[0] + fTempPerm99))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec59[0] = (fTempPerm98 * ftbl0[(((int((fTempPerm95 + (fSlow193 * fRec59[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm153 = (2.0879500000000002f * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec35[0] + (fTempPerm127 + (fRec59[0] + fTempPerm146))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm154 = (2.0879500000000002f * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec35[0] + (fTempPerm127 + (fTempPerm99 + fTempPerm123))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec60[0] = (fTempPerm98 * ftbl0[(((int((fTempPerm95 + (fSlow192 * fRec60[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm155 = (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec35[0] + fRec60[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm156 = (2.0879500000000002f * (fTempPerm155 + (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + fTempPerm132))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm157 = (2.0879500000000002f * (fTempPerm129 + (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + fTempPerm136))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm158 = (2.0879500000000002f * (fTempPerm129 + (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + (fTempPerm116 + (fRec53[0] + fTempPerm111))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec61[0] = (fTempPerm98 * ftbl0[(((int((fTempPerm95 + (fSlow194 * fRec61[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm159 = (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec35[0] + fRec61[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm160 = (2.0879500000000002f * (fTempPerm159 + (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + (fTempPerm116 + (fTempPerm121 + fTempPerm111))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec62[0] = (fTempPerm120 * ftbl0[(((int((fTempPerm117 + (fSlow194 * fRec62[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm161 = (2.0879500000000002f * (fTempPerm149 + (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + (fRec62[0] + fTempPerm116)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec63[0] = (fTempPerm105 * ftbl0[(((int((fTempPerm101 + (fSlow194 * fRec63[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm162 = (2.0879500000000002f * (fTempPerm132 + (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec35[0] + (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec39[0] + fRec63[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm163 = (2.0879500000000002f * (fTempPerm155 + (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + (fTempPerm146 + fTempPerm111)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec64[0] = (fTempPerm110 * ftbl0[(((int((fTempPerm101 + (fSlow191 * fRec64[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm164 = (2.0879500000000002f * (fTempPerm129 + (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + (fRec64[0] + fTempPerm146)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm165 = (2.0879500000000002f * (fTempPerm129 + (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + (fTempPerm123 + fTempPerm111)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm166 = (fTempPerm129 + fTempPerm127);
			}
			if (iSlow27) {
				fRec65[0] = (2.0879500000000002f * (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec47[0] + (fTempPerm120 * ftbl0[(((int((65536.0f * (fRec50[0] + (fSlow189 * fRec65[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm167 = (fRec65[0] + (2.0879500000000002f * fTempPerm166));
			}
			if (iSlow28) {
				fTempPerm168 = (2.0879500000000002f * (fTempPerm166 + fTempPerm143));
			}
			if (iSlow29) {
				fRec66[0] = (2.0879500000000002f * (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec47[0] + (fTempPerm120 * ftbl0[(((int((65536.0f * (fRec50[0] + (fSlow189 * fRec66[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm169 = (fRec66[0] + (2.0879500000000002f * fTempPerm149));
			}
			if (iSlow30) {
				fTempPerm170 = (2.0879500000000002f * (fTempPerm149 + (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + fTempPerm123))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm171 = (2.0879500000000002f * (fTempPerm159 + (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + fTempPerm151))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm172 = (2.0879500000000002f * (fTempPerm129 + (fTempPerm105 * ftbl0[(((int((65536.0f * (fRec42[0] + (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec42[0] + (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec47[0] + fRec62[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec68[0] = (iSlow235 * (iRec68[1] + 1));
			iTempPerm173 = int((iRec68[0] < iSlow199));
			fTempPerm174 = expf((0 - (fConst6 / ((iSlow237)?((iTempPerm173)?fSlow198:fSlow196):fSlow195))));
			fRec67[0] = ((fRec67[1] * fTempPerm174) + (((iSlow237)?((iTempPerm173)?1.5873015873015872f:fSlow352):0.0f) * (1.0f - fTempPerm174)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec69[0] = (fSlow355 + (fRec69[1] - floorf((fSlow355 + fRec69[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm175 = (65536.0f * fRec69[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec71[0] = ((iSlow381)?0.0f:min(fSlow379, (fRec71[1] + 1.0f)));
				iTempPerm176 = int((fRec71[0] < fSlow378));
				iTempPerm177 = int((fRec71[0] < fSlow383));
				fRec70[0] = ((iSlow388)?(fSlow387 * ((iTempPerm176)?((iTempPerm177)?((int((fRec71[0] < 0.0f)))?0.0f:((iTempPerm177)?(fSlow385 * (fRec71[0] / fSlow374)):fSlow367)):((iTempPerm176)?(fSlow366 + ((fSlow384 * ((fRec71[0] - fSlow383) / fSlow382)) + 74.25f)):fSlow358)):((int((fRec71[0] < fSlow379)))?(fSlow357 + (((0 - (fSlow358 * (fRec71[0] - fSlow378))) / fSlow377) + 56.25f)):0.0f))):fRec70[1]);
				fRec72[0] = ((iSlow389)?0.0f:min(fConst2, (fRec72[1] + 1.0f)));
				iTempPerm178 = int((fRec72[0] < fConst2));
				iTempPerm179 = int((fRec72[0] < 0.0f));
				fTempPerm180 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm179)?fRec70[0]:((iTempPerm178)?(fRec70[0] + (fConst3 * (0 - (fRec72[0] * fRec70[0])))):0.0f)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm181 = (fTempPerm180 * ftbl0[(((int(fTempPerm175) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec73[0] = (fSlow390 + (fRec73[1] - floorf((fSlow390 + fRec73[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm182 = (65536.0f * fRec73[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec75[0] = ((iSlow381)?0.0f:min(fSlow411, (fRec75[1] + 1.0f)));
				iTempPerm183 = int((fRec75[0] < fSlow410));
				iTempPerm184 = int((fRec75[0] < fSlow413));
				fRec74[0] = ((iSlow388)?(fSlow387 * ((iTempPerm183)?((iTempPerm184)?((int((fRec75[0] < 0.0f)))?0.0f:((iTempPerm184)?(fSlow415 * (fRec75[0] / fSlow406)):fSlow399)):((iTempPerm183)?(fSlow398 + ((fSlow414 * ((fRec75[0] - fSlow413) / fSlow412)) + 7.25f)):fSlow392)):((int((fRec75[0] < fSlow411)))?(fSlow391 + (((0 - (fSlow392 * (fRec75[0] - fSlow410))) / fSlow409) + 5.4924242424242422f)):0.0f))):fRec74[1]);
				fTempPerm185 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm179)?fRec74[0]:((iTempPerm178)?(fRec74[0] + (fConst3 * (0 - (fRec72[0] * fRec74[0])))):0.0f)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm186 = (fTempPerm185 * ftbl0[(((int(fTempPerm182) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm187 = (fTempPerm186 + fTempPerm181);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec76[0] = (fSlow416 + (fRec76[1] - floorf((fSlow416 + fRec76[1]))));
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm188 = (65536.0f * fRec76[0]);
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm189 = ftbl0[(((int(fTempPerm188) % 65536) + 65536) % 65536)];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec78[0] = ((iSlow381)?0.0f:min(fSlow434, (fRec78[1] + 1.0f)));
				iTempPerm190 = int((fRec78[0] < fSlow433));
				iTempPerm191 = int((fRec78[0] < fSlow436));
				fRec77[0] = ((iSlow388)?(fSlow387 * ((iTempPerm190)?((iTempPerm191)?((int((fRec78[0] < 0.0f)))?0.0f:((iTempPerm191)?(fSlow385 * (fRec78[0] / fSlow429)):fSlow367)):((iTempPerm190)?(fSlow366 + ((fSlow437 * ((fRec78[0] - fSlow436) / fSlow435)) + 74.25f)):fSlow418)):((int((fRec78[0] < fSlow434)))?(fSlow417 + (((0 - (fSlow418 * (fRec78[0] - fSlow433))) / fSlow432) + 71.25f)):0.0f))):fRec77[1]);
				fTempPerm192 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm179)?fRec77[0]:((iTempPerm178)?(fRec77[0] + (fConst3 * (0 - (fRec72[0] * fRec77[0])))):0.0f)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm193 = (fTempPerm192 * fTempPerm189);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm194 = (fTempPerm193 + fTempPerm187);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec80[0] = ((iSlow381)?0.0f:min(fSlow458, (fRec80[1] + 1.0f)));
				iTempPerm195 = int((fRec80[0] < fSlow457));
				iTempPerm196 = int((fRec80[0] < fSlow460));
				fRec79[0] = ((iSlow388)?(fSlow387 * ((iTempPerm195)?((iTempPerm196)?((int((fRec80[0] < 0.0f)))?0.0f:((iTempPerm196)?(fSlow462 * (fRec80[0] / fSlow453)):fSlow446)):((iTempPerm195)?(fSlow445 + ((fSlow461 * ((fRec80[0] - fSlow460) / fSlow459)) + 22.25f)):fSlow439)):((int((fRec80[0] < fSlow458)))?(fSlow438 + (((0 - (fSlow439 * (fRec80[0] - fSlow457))) / fSlow456) + 21.3510101010101f)):0.0f))):fRec79[1]);
				fTempPerm197 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm179)?fRec79[0]:((iTempPerm178)?(fRec79[0] + (fConst3 * (0 - (fRec72[0] * fRec79[0])))):0.0f)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm198 = (fTempPerm197 * fTempPerm189);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm199 = (fTempPerm198 + fTempPerm194);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec81[0] = (fSlow464 + (fRec81[1] - floorf((fSlow464 + fRec81[1]))));
				fRec83[0] = ((iSlow381)?0.0f:min(fSlow471, (fRec83[1] + 1.0f)));
				iTempPerm200 = int((fRec83[0] < fSlow469));
				iTempPerm201 = int((fRec83[0] < fSlow473));
				fRec82[0] = ((iSlow388)?(fSlow387 * ((iTempPerm200)?((iTempPerm201)?((int((fRec83[0] < 0.0f)))?0.0f:((iTempPerm201)?(fSlow475 * fRec83[0]):99.0f)):((iTempPerm200)?((fSlow474 * (0 - (4.0f * (fRec83[0] - fSlow473)))) + 99.0f):95.0f)):((int((fRec83[0] < fSlow471)))?((fSlow472 * (0 - (95.0f * (fRec83[0] - fSlow469)))) + 95.0f):0.0f))):fRec82[1]);
				fTempPerm202 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm179)?fRec82[0]:((iTempPerm178)?(fRec82[0] + (fConst3 * (0 - (fRec72[0] * fRec82[0])))):0.0f)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm203 = (fTempPerm202 * ftbl0[(((int((65536.0f * fRec81[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec84[0] = (fSlow477 + (fRec84[1] - floorf((fSlow477 + fRec84[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm204 = (65536.0f * fRec84[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec86[0] = ((iSlow381)?0.0f:min(fSlow498, (fRec86[1] + 1.0f)));
				iTempPerm205 = int((fRec86[0] < fSlow497));
				iTempPerm206 = int((fRec86[0] < fSlow500));
				fRec85[0] = ((iSlow388)?(fSlow387 * ((iTempPerm205)?((iTempPerm206)?((int((fRec86[0] < 0.0f)))?0.0f:((iTempPerm206)?(fSlow502 * (fRec86[0] / fSlow493)):fSlow486)):((iTempPerm205)?(fSlow485 + ((fSlow501 * ((fRec86[0] - fSlow500) / fSlow499)) + 19.75f)):fSlow479)):((int((fRec86[0] < fSlow498)))?(fSlow478 + (((0 - (fSlow479 * (fRec86[0] - fSlow497))) / fSlow496) + 18.952020202020204f)):0.0f))):fRec85[1]);
				fTempPerm207 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm179)?fRec85[0]:((iTempPerm178)?(fRec85[0] + (fConst3 * (0 - (fRec72[0] * fRec85[0])))):0.0f)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm208 = (fTempPerm207 * ftbl0[(((int(fTempPerm204) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm209 = (2.0879500000000002f * (fTempPerm208 + (fTempPerm203 + fTempPerm199)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec87[0] = (fTempPerm207 * ftbl0[(((int((65536.0f * (fRec84[0] + (fSlow189 * fRec87[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm210 = (fTempPerm202 * ftbl0[(((int((65536.0f * (fRec81[0] + fRec87[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm211 = (2.0879500000000002f * (fTempPerm210 + fTempPerm199));
			}
			if (iSlow5 || iSlow3) {
				fRec88[0] = (fTempPerm202 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow189 * fRec88[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm212 = (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + fRec88[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm213 = (2.0879500000000002f * (fTempPerm208 + (fTempPerm187 + fTempPerm212)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm214 = (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + fTempPerm198))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm215 = (2.0879500000000002f * (fTempPerm210 + (fTempPerm214 + fTempPerm187)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm216 = (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm186))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm217 = (2.0879500000000002f * (fTempPerm208 + (fTempPerm216 + fTempPerm212)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec89[0] = (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + (fSlow189 * fRec89[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm218 = (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec73[0] + fRec89[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm219 = (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + (fTempPerm208 + fTempPerm203)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm220 = (2.0879500000000002f * (fTempPerm219 + (fTempPerm218 + fTempPerm181)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm221 = (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm193))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm222 = (fTempPerm221 + fTempPerm181);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm223 = (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + (fRec87[0] + fTempPerm203)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm224 = (2.0879500000000002f * (fTempPerm223 + fTempPerm222));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm225 = (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + fRec87[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm226 = (2.0879500000000002f * (fTempPerm210 + (fTempPerm225 + fTempPerm194)));
			}
			if (iSlow9) {
				fRec90[0] = (fTempPerm207 * ftbl0[(((int((fTempPerm204 + (fSlow190 * fRec90[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm227 = ftbl0[(((int((65536.0f * (fRec76[0] + fRec90[0]))) % 65536) + 65536) % 65536)];
				fTempPerm228 = (2.0879500000000002f * (((fTempPerm187 + (fTempPerm192 * fTempPerm227)) + (fTempPerm197 * fTempPerm227)) + (fTempPerm202 * ftbl0[(((int((65536.0f * (fRec81[0] + fRec90[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm229 = (2.0879500000000002f * (fTempPerm210 + (fTempPerm222 + fTempPerm225)));
			}
			if (iSlow28 || iSlow11) {
				fRec91[0] = (fTempPerm207 * ftbl0[(((int((fTempPerm204 + (fSlow191 * fRec91[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm230 = (fTempPerm202 * ftbl0[(((int((65536.0f * (fRec81[0] + fRec91[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm231 = ((ftbl0[(((int((65536.0f * (fRec76[0] + fRec91[0]))) % 65536) + 65536) % 65536)] * (fTempPerm192 + (2.0879500000000002f * fTempPerm197))) + (2.0879500000000002f * (fTempPerm230 + (fTempPerm180 * ftbl0[(((int((fTempPerm175 + (136835.89120000001f * fTempPerm186))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm232 = ((fTempPerm180 * ftbl0[(((int((65536.0f * (fRec69[0] + fRec89[0]))) % 65536) + 65536) % 65536)]) + fTempPerm218);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm233 = (fTempPerm202 * ftbl0[(((int((65536.0f * (fRec81[0] + fTempPerm208))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm234 = (2.0879500000000002f * (fTempPerm233 + (fTempPerm232 + (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + fTempPerm208))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm235 = (2.0879500000000002f * (fTempPerm219 + fTempPerm232));
			}
			if (iSlow14) {
				fRec92[0] = (fTempPerm207 * ftbl0[(((int((fTempPerm204 + (fSlow192 * fRec92[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm236 = (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm221))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm237 = (2.0879500000000002f * ((fTempPerm236 + (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + fRec92[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm202 * ftbl0[(((int((65536.0f * (fRec81[0] + fRec92[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm238 = (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + fTempPerm233))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm239 = (2.0879500000000002f * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec69[0] + (fTempPerm238 + (fRec89[0] + fTempPerm186))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec93[0] = (fTempPerm185 * ftbl0[(((int((fTempPerm182 + (fSlow193 * fRec93[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm240 = (2.0879500000000002f * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec69[0] + (fTempPerm214 + (fRec93[0] + fTempPerm233))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm241 = (2.0879500000000002f * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec69[0] + (fTempPerm214 + (fTempPerm186 + fTempPerm210))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec94[0] = (fTempPerm185 * ftbl0[(((int((fTempPerm182 + (fSlow192 * fRec94[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm242 = (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec69[0] + fRec94[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm243 = (2.0879500000000002f * (fTempPerm242 + (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + fTempPerm219))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm244 = (2.0879500000000002f * (fTempPerm216 + (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + fTempPerm223))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm245 = (2.0879500000000002f * (fTempPerm216 + (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + (fTempPerm203 + (fRec87[0] + fTempPerm198))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec95[0] = (fTempPerm185 * ftbl0[(((int((fTempPerm182 + (fSlow194 * fRec95[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm246 = (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec69[0] + fRec95[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm247 = (2.0879500000000002f * (fTempPerm246 + (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + (fTempPerm203 + (fTempPerm208 + fTempPerm198))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec96[0] = (fTempPerm207 * ftbl0[(((int((fTempPerm204 + (fSlow194 * fRec96[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm248 = (2.0879500000000002f * (fTempPerm236 + (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + (fRec96[0] + fTempPerm203)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec97[0] = (fTempPerm192 * ftbl0[(((int((fTempPerm188 + (fSlow194 * fRec97[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm249 = (2.0879500000000002f * (fTempPerm219 + (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec69[0] + (fTempPerm185 * ftbl0[(((int((65536.0f * (fRec73[0] + fRec97[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm250 = (2.0879500000000002f * (fTempPerm242 + (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + (fTempPerm233 + fTempPerm198)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec98[0] = (fTempPerm197 * ftbl0[(((int((fTempPerm188 + (fSlow191 * fRec98[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm251 = (2.0879500000000002f * (fTempPerm216 + (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + (fRec98[0] + fTempPerm233)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm252 = (2.0879500000000002f * (fTempPerm216 + (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + (fTempPerm210 + fTempPerm198)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm253 = (fTempPerm216 + fTempPerm214);
			}
			if (iSlow27) {
				fRec99[0] = (2.0879500000000002f * (fTempPerm202 * ftbl0[(((int((65536.0f * (fRec81[0] + (fTempPerm207 * ftbl0[(((int((65536.0f * (fRec84[0] + (fSlow189 * fRec99[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm254 = (fRec99[0] + (2.0879500000000002f * fTempPerm253));
			}
			if (iSlow28) {
				fTempPerm255 = (2.0879500000000002f * (fTempPerm253 + fTempPerm230));
			}
			if (iSlow29) {
				fRec100[0] = (2.0879500000000002f * (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + (fTempPerm202 * ftbl0[(((int((65536.0f * (fRec81[0] + (fTempPerm207 * ftbl0[(((int((65536.0f * (fRec84[0] + (fSlow189 * fRec100[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm256 = (fRec100[0] + (2.0879500000000002f * fTempPerm236));
			}
			if (iSlow30) {
				fTempPerm257 = (2.0879500000000002f * (fTempPerm236 + (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + fTempPerm210))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm258 = (2.0879500000000002f * (fTempPerm246 + (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + fTempPerm238))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm259 = (2.0879500000000002f * (fTempPerm216 + (fTempPerm192 * ftbl0[(((int((65536.0f * (fRec76[0] + (fTempPerm197 * ftbl0[(((int((65536.0f * (fRec76[0] + (fTempPerm202 * ftbl0[(((int((65536.0f * (fRec81[0] + fRec96[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec102[0] = (iSlow386 * (iRec102[1] + 1));
			iTempPerm260 = int((iRec102[0] < iSlow199));
			fTempPerm261 = expf((0 - (fConst6 / ((iSlow388)?((iTempPerm260)?fSlow198:fSlow196):fSlow195))));
			fRec101[0] = ((fRec101[1] * fTempPerm261) + (((iSlow388)?((iTempPerm260)?1.5873015873015872f:fSlow503):0.0f) * (1.0f - fTempPerm261)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec103[0] = (fSlow506 + (fRec103[1] - floorf((fSlow506 + fRec103[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm262 = (65536.0f * fRec103[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec105[0] = ((iSlow532)?0.0f:min(fSlow530, (fRec105[1] + 1.0f)));
				iTempPerm263 = int((fRec105[0] < fSlow529));
				iTempPerm264 = int((fRec105[0] < fSlow534));
				fRec104[0] = ((iSlow539)?(fSlow538 * ((iTempPerm263)?((iTempPerm264)?((int((fRec105[0] < 0.0f)))?0.0f:((iTempPerm264)?(fSlow536 * (fRec105[0] / fSlow525)):fSlow518)):((iTempPerm263)?(fSlow517 + ((fSlow535 * ((fRec105[0] - fSlow534) / fSlow533)) + 74.25f)):fSlow509)):((int((fRec105[0] < fSlow530)))?(fSlow508 + (((0 - (fSlow509 * (fRec105[0] - fSlow529))) / fSlow528) + 56.25f)):0.0f))):fRec104[1]);
				fRec106[0] = ((iSlow540)?0.0f:min(fConst2, (fRec106[1] + 1.0f)));
				iTempPerm265 = int((fRec106[0] < fConst2));
				iTempPerm266 = int((fRec106[0] < 0.0f));
				fTempPerm267 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm266)?fRec104[0]:((iTempPerm265)?(fRec104[0] + (fConst3 * (0 - (fRec106[0] * fRec104[0])))):0.0f)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm268 = (fTempPerm267 * ftbl0[(((int(fTempPerm262) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec107[0] = (fSlow541 + (fRec107[1] - floorf((fSlow541 + fRec107[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm269 = (65536.0f * fRec107[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec109[0] = ((iSlow532)?0.0f:min(fSlow562, (fRec109[1] + 1.0f)));
				iTempPerm270 = int((fRec109[0] < fSlow561));
				iTempPerm271 = int((fRec109[0] < fSlow564));
				fRec108[0] = ((iSlow539)?(fSlow538 * ((iTempPerm270)?((iTempPerm271)?((int((fRec109[0] < 0.0f)))?0.0f:((iTempPerm271)?(fSlow566 * (fRec109[0] / fSlow557)):fSlow550)):((iTempPerm270)?(fSlow549 + ((fSlow565 * ((fRec109[0] - fSlow564) / fSlow563)) + 7.25f)):fSlow543)):((int((fRec109[0] < fSlow562)))?(fSlow542 + (((0 - (fSlow543 * (fRec109[0] - fSlow561))) / fSlow560) + 5.4924242424242422f)):0.0f))):fRec108[1]);
				fTempPerm272 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm266)?fRec108[0]:((iTempPerm265)?(fRec108[0] + (fConst3 * (0 - (fRec106[0] * fRec108[0])))):0.0f)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm273 = (fTempPerm272 * ftbl0[(((int(fTempPerm269) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm274 = (fTempPerm273 + fTempPerm268);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec110[0] = (fSlow567 + (fRec110[1] - floorf((fSlow567 + fRec110[1]))));
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm275 = (65536.0f * fRec110[0]);
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm276 = ftbl0[(((int(fTempPerm275) % 65536) + 65536) % 65536)];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec112[0] = ((iSlow532)?0.0f:min(fSlow585, (fRec112[1] + 1.0f)));
				iTempPerm277 = int((fRec112[0] < fSlow584));
				iTempPerm278 = int((fRec112[0] < fSlow587));
				fRec111[0] = ((iSlow539)?(fSlow538 * ((iTempPerm277)?((iTempPerm278)?((int((fRec112[0] < 0.0f)))?0.0f:((iTempPerm278)?(fSlow536 * (fRec112[0] / fSlow580)):fSlow518)):((iTempPerm277)?(fSlow517 + ((fSlow588 * ((fRec112[0] - fSlow587) / fSlow586)) + 74.25f)):fSlow569)):((int((fRec112[0] < fSlow585)))?(fSlow568 + (((0 - (fSlow569 * (fRec112[0] - fSlow584))) / fSlow583) + 71.25f)):0.0f))):fRec111[1]);
				fTempPerm279 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm266)?fRec111[0]:((iTempPerm265)?(fRec111[0] + (fConst3 * (0 - (fRec106[0] * fRec111[0])))):0.0f)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm280 = (fTempPerm279 * fTempPerm276);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm281 = (fTempPerm280 + fTempPerm274);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec114[0] = ((iSlow532)?0.0f:min(fSlow609, (fRec114[1] + 1.0f)));
				iTempPerm282 = int((fRec114[0] < fSlow608));
				iTempPerm283 = int((fRec114[0] < fSlow611));
				fRec113[0] = ((iSlow539)?(fSlow538 * ((iTempPerm282)?((iTempPerm283)?((int((fRec114[0] < 0.0f)))?0.0f:((iTempPerm283)?(fSlow613 * (fRec114[0] / fSlow604)):fSlow597)):((iTempPerm282)?(fSlow596 + ((fSlow612 * ((fRec114[0] - fSlow611) / fSlow610)) + 22.25f)):fSlow590)):((int((fRec114[0] < fSlow609)))?(fSlow589 + (((0 - (fSlow590 * (fRec114[0] - fSlow608))) / fSlow607) + 21.3510101010101f)):0.0f))):fRec113[1]);
				fTempPerm284 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm266)?fRec113[0]:((iTempPerm265)?(fRec113[0] + (fConst3 * (0 - (fRec106[0] * fRec113[0])))):0.0f)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm285 = (fTempPerm284 * fTempPerm276);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm286 = (fTempPerm285 + fTempPerm281);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec115[0] = (fSlow615 + (fRec115[1] - floorf((fSlow615 + fRec115[1]))));
				fRec117[0] = ((iSlow532)?0.0f:min(fSlow622, (fRec117[1] + 1.0f)));
				iTempPerm287 = int((fRec117[0] < fSlow620));
				iTempPerm288 = int((fRec117[0] < fSlow624));
				fRec116[0] = ((iSlow539)?(fSlow538 * ((iTempPerm287)?((iTempPerm288)?((int((fRec117[0] < 0.0f)))?0.0f:((iTempPerm288)?(fSlow626 * fRec117[0]):99.0f)):((iTempPerm287)?((fSlow625 * (0 - (4.0f * (fRec117[0] - fSlow624)))) + 99.0f):95.0f)):((int((fRec117[0] < fSlow622)))?((fSlow623 * (0 - (95.0f * (fRec117[0] - fSlow620)))) + 95.0f):0.0f))):fRec116[1]);
				fTempPerm289 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm266)?fRec116[0]:((iTempPerm265)?(fRec116[0] + (fConst3 * (0 - (fRec106[0] * fRec116[0])))):0.0f)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm290 = (fTempPerm289 * ftbl0[(((int((65536.0f * fRec115[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec118[0] = (fSlow628 + (fRec118[1] - floorf((fSlow628 + fRec118[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm291 = (65536.0f * fRec118[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec120[0] = ((iSlow532)?0.0f:min(fSlow649, (fRec120[1] + 1.0f)));
				iTempPerm292 = int((fRec120[0] < fSlow648));
				iTempPerm293 = int((fRec120[0] < fSlow651));
				fRec119[0] = ((iSlow539)?(fSlow538 * ((iTempPerm292)?((iTempPerm293)?((int((fRec120[0] < 0.0f)))?0.0f:((iTempPerm293)?(fSlow653 * (fRec120[0] / fSlow644)):fSlow637)):((iTempPerm292)?(fSlow636 + ((fSlow652 * ((fRec120[0] - fSlow651) / fSlow650)) + 19.75f)):fSlow630)):((int((fRec120[0] < fSlow649)))?(fSlow629 + (((0 - (fSlow630 * (fRec120[0] - fSlow648))) / fSlow647) + 18.952020202020204f)):0.0f))):fRec119[1]);
				fTempPerm294 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm266)?fRec119[0]:((iTempPerm265)?(fRec119[0] + (fConst3 * (0 - (fRec106[0] * fRec119[0])))):0.0f)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm295 = (fTempPerm294 * ftbl0[(((int(fTempPerm291) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm296 = (2.0879500000000002f * (fTempPerm295 + (fTempPerm290 + fTempPerm286)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec121[0] = (fTempPerm294 * ftbl0[(((int((65536.0f * (fRec118[0] + (fSlow189 * fRec121[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm297 = (fTempPerm289 * ftbl0[(((int((65536.0f * (fRec115[0] + fRec121[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm298 = (2.0879500000000002f * (fTempPerm297 + fTempPerm286));
			}
			if (iSlow5 || iSlow3) {
				fRec122[0] = (fTempPerm289 * ftbl0[(((int((65536.0f * (fRec115[0] + (fSlow189 * fRec122[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm299 = (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + fRec122[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm300 = (2.0879500000000002f * (fTempPerm295 + (fTempPerm274 + fTempPerm299)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm301 = (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + fTempPerm285))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm302 = (2.0879500000000002f * (fTempPerm297 + (fTempPerm301 + fTempPerm274)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm303 = (fTempPerm267 * ftbl0[(((int((65536.0f * (fRec103[0] + fTempPerm273))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm304 = (2.0879500000000002f * (fTempPerm295 + (fTempPerm303 + fTempPerm299)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec123[0] = (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + (fSlow189 * fRec123[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm305 = (fTempPerm272 * ftbl0[(((int((65536.0f * (fRec107[0] + fRec123[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm306 = (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + (fTempPerm295 + fTempPerm290)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm307 = (2.0879500000000002f * (fTempPerm306 + (fTempPerm305 + fTempPerm268)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm308 = (fTempPerm272 * ftbl0[(((int((65536.0f * (fRec107[0] + fTempPerm280))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm309 = (fTempPerm308 + fTempPerm268);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm310 = (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + (fRec121[0] + fTempPerm290)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm311 = (2.0879500000000002f * (fTempPerm310 + fTempPerm309));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm312 = (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + fRec121[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm313 = (2.0879500000000002f * (fTempPerm297 + (fTempPerm312 + fTempPerm281)));
			}
			if (iSlow9) {
				fRec124[0] = (fTempPerm294 * ftbl0[(((int((fTempPerm291 + (fSlow190 * fRec124[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm314 = ftbl0[(((int((65536.0f * (fRec110[0] + fRec124[0]))) % 65536) + 65536) % 65536)];
				fTempPerm315 = (2.0879500000000002f * (((fTempPerm274 + (fTempPerm279 * fTempPerm314)) + (fTempPerm284 * fTempPerm314)) + (fTempPerm289 * ftbl0[(((int((65536.0f * (fRec115[0] + fRec124[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm316 = (2.0879500000000002f * (fTempPerm297 + (fTempPerm309 + fTempPerm312)));
			}
			if (iSlow28 || iSlow11) {
				fRec125[0] = (fTempPerm294 * ftbl0[(((int((fTempPerm291 + (fSlow191 * fRec125[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm317 = (fTempPerm289 * ftbl0[(((int((65536.0f * (fRec115[0] + fRec125[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm318 = ((ftbl0[(((int((65536.0f * (fRec110[0] + fRec125[0]))) % 65536) + 65536) % 65536)] * (fTempPerm279 + (2.0879500000000002f * fTempPerm284))) + (2.0879500000000002f * (fTempPerm317 + (fTempPerm267 * ftbl0[(((int((fTempPerm262 + (136835.89120000001f * fTempPerm273))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm319 = ((fTempPerm267 * ftbl0[(((int((65536.0f * (fRec103[0] + fRec123[0]))) % 65536) + 65536) % 65536)]) + fTempPerm305);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm320 = (fTempPerm289 * ftbl0[(((int((65536.0f * (fRec115[0] + fTempPerm295))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm321 = (2.0879500000000002f * (fTempPerm320 + (fTempPerm319 + (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + fTempPerm295))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm322 = (2.0879500000000002f * (fTempPerm306 + fTempPerm319));
			}
			if (iSlow14) {
				fRec126[0] = (fTempPerm294 * ftbl0[(((int((fTempPerm291 + (fSlow192 * fRec126[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm323 = (fTempPerm267 * ftbl0[(((int((65536.0f * (fRec103[0] + fTempPerm308))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm324 = (2.0879500000000002f * ((fTempPerm323 + (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + fRec126[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm289 * ftbl0[(((int((65536.0f * (fRec115[0] + fRec126[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm325 = (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + fTempPerm320))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm326 = (2.0879500000000002f * (fTempPerm267 * ftbl0[(((int((65536.0f * (fRec103[0] + (fTempPerm325 + (fRec123[0] + fTempPerm273))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec127[0] = (fTempPerm272 * ftbl0[(((int((fTempPerm269 + (fSlow193 * fRec127[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm327 = (2.0879500000000002f * (fTempPerm267 * ftbl0[(((int((65536.0f * (fRec103[0] + (fTempPerm301 + (fRec127[0] + fTempPerm320))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm328 = (2.0879500000000002f * (fTempPerm267 * ftbl0[(((int((65536.0f * (fRec103[0] + (fTempPerm301 + (fTempPerm273 + fTempPerm297))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec128[0] = (fTempPerm272 * ftbl0[(((int((fTempPerm269 + (fSlow192 * fRec128[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm329 = (fTempPerm267 * ftbl0[(((int((65536.0f * (fRec103[0] + fRec128[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm330 = (2.0879500000000002f * (fTempPerm329 + (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + fTempPerm306))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm331 = (2.0879500000000002f * (fTempPerm303 + (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + fTempPerm310))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm332 = (2.0879500000000002f * (fTempPerm303 + (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + (fTempPerm290 + (fRec121[0] + fTempPerm285))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec129[0] = (fTempPerm272 * ftbl0[(((int((fTempPerm269 + (fSlow194 * fRec129[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm333 = (fTempPerm267 * ftbl0[(((int((65536.0f * (fRec103[0] + fRec129[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm334 = (2.0879500000000002f * (fTempPerm333 + (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + (fTempPerm290 + (fTempPerm295 + fTempPerm285))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec130[0] = (fTempPerm294 * ftbl0[(((int((fTempPerm291 + (fSlow194 * fRec130[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm335 = (2.0879500000000002f * (fTempPerm323 + (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + (fRec130[0] + fTempPerm290)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec131[0] = (fTempPerm279 * ftbl0[(((int((fTempPerm275 + (fSlow194 * fRec131[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm336 = (2.0879500000000002f * (fTempPerm306 + (fTempPerm267 * ftbl0[(((int((65536.0f * (fRec103[0] + (fTempPerm272 * ftbl0[(((int((65536.0f * (fRec107[0] + fRec131[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm337 = (2.0879500000000002f * (fTempPerm329 + (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + (fTempPerm320 + fTempPerm285)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec132[0] = (fTempPerm284 * ftbl0[(((int((fTempPerm275 + (fSlow191 * fRec132[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm338 = (2.0879500000000002f * (fTempPerm303 + (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + (fRec132[0] + fTempPerm320)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm339 = (2.0879500000000002f * (fTempPerm303 + (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + (fTempPerm297 + fTempPerm285)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm340 = (fTempPerm303 + fTempPerm301);
			}
			if (iSlow27) {
				fRec133[0] = (2.0879500000000002f * (fTempPerm289 * ftbl0[(((int((65536.0f * (fRec115[0] + (fTempPerm294 * ftbl0[(((int((65536.0f * (fRec118[0] + (fSlow189 * fRec133[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm341 = (fRec133[0] + (2.0879500000000002f * fTempPerm340));
			}
			if (iSlow28) {
				fTempPerm342 = (2.0879500000000002f * (fTempPerm340 + fTempPerm317));
			}
			if (iSlow29) {
				fRec134[0] = (2.0879500000000002f * (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + (fTempPerm289 * ftbl0[(((int((65536.0f * (fRec115[0] + (fTempPerm294 * ftbl0[(((int((65536.0f * (fRec118[0] + (fSlow189 * fRec134[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm343 = (fRec134[0] + (2.0879500000000002f * fTempPerm323));
			}
			if (iSlow30) {
				fTempPerm344 = (2.0879500000000002f * (fTempPerm323 + (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + fTempPerm297))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm345 = (2.0879500000000002f * (fTempPerm333 + (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + fTempPerm325))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm346 = (2.0879500000000002f * (fTempPerm303 + (fTempPerm279 * ftbl0[(((int((65536.0f * (fRec110[0] + (fTempPerm284 * ftbl0[(((int((65536.0f * (fRec110[0] + (fTempPerm289 * ftbl0[(((int((65536.0f * (fRec115[0] + fRec130[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec136[0] = (iSlow537 * (iRec136[1] + 1));
			iTempPerm347 = int((iRec136[0] < iSlow199));
			fTempPerm348 = expf((0 - (fConst6 / ((iSlow539)?((iTempPerm347)?fSlow198:fSlow196):fSlow195))));
			fRec135[0] = ((fRec135[1] * fTempPerm348) + (((iSlow539)?((iTempPerm347)?1.5873015873015872f:fSlow654):0.0f) * (1.0f - fTempPerm348)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec137[0] = (fSlow657 + (fRec137[1] - floorf((fSlow657 + fRec137[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm349 = (65536.0f * fRec137[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec139[0] = ((iSlow683)?0.0f:min(fSlow681, (fRec139[1] + 1.0f)));
				iTempPerm350 = int((fRec139[0] < fSlow680));
				iTempPerm351 = int((fRec139[0] < fSlow685));
				fRec138[0] = ((iSlow690)?(fSlow689 * ((iTempPerm350)?((iTempPerm351)?((int((fRec139[0] < 0.0f)))?0.0f:((iTempPerm351)?(fSlow687 * (fRec139[0] / fSlow676)):fSlow669)):((iTempPerm350)?(fSlow668 + ((fSlow686 * ((fRec139[0] - fSlow685) / fSlow684)) + 74.25f)):fSlow660)):((int((fRec139[0] < fSlow681)))?(fSlow659 + (((0 - (fSlow660 * (fRec139[0] - fSlow680))) / fSlow679) + 56.25f)):0.0f))):fRec138[1]);
				fRec140[0] = ((iSlow691)?0.0f:min(fConst2, (fRec140[1] + 1.0f)));
				iTempPerm352 = int((fRec140[0] < fConst2));
				iTempPerm353 = int((fRec140[0] < 0.0f));
				fTempPerm354 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm353)?fRec138[0]:((iTempPerm352)?(fRec138[0] + (fConst3 * (0 - (fRec140[0] * fRec138[0])))):0.0f)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm355 = (fTempPerm354 * ftbl0[(((int(fTempPerm349) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec141[0] = (fSlow692 + (fRec141[1] - floorf((fSlow692 + fRec141[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm356 = (65536.0f * fRec141[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec143[0] = ((iSlow683)?0.0f:min(fSlow713, (fRec143[1] + 1.0f)));
				iTempPerm357 = int((fRec143[0] < fSlow712));
				iTempPerm358 = int((fRec143[0] < fSlow715));
				fRec142[0] = ((iSlow690)?(fSlow689 * ((iTempPerm357)?((iTempPerm358)?((int((fRec143[0] < 0.0f)))?0.0f:((iTempPerm358)?(fSlow717 * (fRec143[0] / fSlow708)):fSlow701)):((iTempPerm357)?(fSlow700 + ((fSlow716 * ((fRec143[0] - fSlow715) / fSlow714)) + 7.25f)):fSlow694)):((int((fRec143[0] < fSlow713)))?(fSlow693 + (((0 - (fSlow694 * (fRec143[0] - fSlow712))) / fSlow711) + 5.4924242424242422f)):0.0f))):fRec142[1]);
				fTempPerm359 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm353)?fRec142[0]:((iTempPerm352)?(fRec142[0] + (fConst3 * (0 - (fRec140[0] * fRec142[0])))):0.0f)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm360 = (fTempPerm359 * ftbl0[(((int(fTempPerm356) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm361 = (fTempPerm360 + fTempPerm355);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec144[0] = (fSlow718 + (fRec144[1] - floorf((fSlow718 + fRec144[1]))));
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm362 = (65536.0f * fRec144[0]);
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm363 = ftbl0[(((int(fTempPerm362) % 65536) + 65536) % 65536)];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec146[0] = ((iSlow683)?0.0f:min(fSlow736, (fRec146[1] + 1.0f)));
				iTempPerm364 = int((fRec146[0] < fSlow735));
				iTempPerm365 = int((fRec146[0] < fSlow738));
				fRec145[0] = ((iSlow690)?(fSlow689 * ((iTempPerm364)?((iTempPerm365)?((int((fRec146[0] < 0.0f)))?0.0f:((iTempPerm365)?(fSlow687 * (fRec146[0] / fSlow731)):fSlow669)):((iTempPerm364)?(fSlow668 + ((fSlow739 * ((fRec146[0] - fSlow738) / fSlow737)) + 74.25f)):fSlow720)):((int((fRec146[0] < fSlow736)))?(fSlow719 + (((0 - (fSlow720 * (fRec146[0] - fSlow735))) / fSlow734) + 71.25f)):0.0f))):fRec145[1]);
				fTempPerm366 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm353)?fRec145[0]:((iTempPerm352)?(fRec145[0] + (fConst3 * (0 - (fRec140[0] * fRec145[0])))):0.0f)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm367 = (fTempPerm366 * fTempPerm363);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm368 = (fTempPerm367 + fTempPerm361);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec148[0] = ((iSlow683)?0.0f:min(fSlow760, (fRec148[1] + 1.0f)));
				iTempPerm369 = int((fRec148[0] < fSlow759));
				iTempPerm370 = int((fRec148[0] < fSlow762));
				fRec147[0] = ((iSlow690)?(fSlow689 * ((iTempPerm369)?((iTempPerm370)?((int((fRec148[0] < 0.0f)))?0.0f:((iTempPerm370)?(fSlow764 * (fRec148[0] / fSlow755)):fSlow748)):((iTempPerm369)?(fSlow747 + ((fSlow763 * ((fRec148[0] - fSlow762) / fSlow761)) + 22.25f)):fSlow741)):((int((fRec148[0] < fSlow760)))?(fSlow740 + (((0 - (fSlow741 * (fRec148[0] - fSlow759))) / fSlow758) + 21.3510101010101f)):0.0f))):fRec147[1]);
				fTempPerm371 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm353)?fRec147[0]:((iTempPerm352)?(fRec147[0] + (fConst3 * (0 - (fRec140[0] * fRec147[0])))):0.0f)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm372 = (fTempPerm371 * fTempPerm363);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm373 = (fTempPerm372 + fTempPerm368);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec149[0] = (fSlow766 + (fRec149[1] - floorf((fSlow766 + fRec149[1]))));
				fRec151[0] = ((iSlow683)?0.0f:min(fSlow773, (fRec151[1] + 1.0f)));
				iTempPerm374 = int((fRec151[0] < fSlow771));
				iTempPerm375 = int((fRec151[0] < fSlow775));
				fRec150[0] = ((iSlow690)?(fSlow689 * ((iTempPerm374)?((iTempPerm375)?((int((fRec151[0] < 0.0f)))?0.0f:((iTempPerm375)?(fSlow777 * fRec151[0]):99.0f)):((iTempPerm374)?((fSlow776 * (0 - (4.0f * (fRec151[0] - fSlow775)))) + 99.0f):95.0f)):((int((fRec151[0] < fSlow773)))?((fSlow774 * (0 - (95.0f * (fRec151[0] - fSlow771)))) + 95.0f):0.0f))):fRec150[1]);
				fTempPerm376 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm353)?fRec150[0]:((iTempPerm352)?(fRec150[0] + (fConst3 * (0 - (fRec140[0] * fRec150[0])))):0.0f)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm377 = (fTempPerm376 * ftbl0[(((int((65536.0f * fRec149[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec152[0] = (fSlow779 + (fRec152[1] - floorf((fSlow779 + fRec152[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm378 = (65536.0f * fRec152[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec154[0] = ((iSlow683)?0.0f:min(fSlow800, (fRec154[1] + 1.0f)));
				iTempPerm379 = int((fRec154[0] < fSlow799));
				iTempPerm380 = int((fRec154[0] < fSlow802));
				fRec153[0] = ((iSlow690)?(fSlow689 * ((iTempPerm379)?((iTempPerm380)?((int((fRec154[0] < 0.0f)))?0.0f:((iTempPerm380)?(fSlow804 * (fRec154[0] / fSlow795)):fSlow788)):((iTempPerm379)?(fSlow787 + ((fSlow803 * ((fRec154[0] - fSlow802) / fSlow801)) + 19.75f)):fSlow781)):((int((fRec154[0] < fSlow800)))?(fSlow780 + (((0 - (fSlow781 * (fRec154[0] - fSlow799))) / fSlow798) + 18.952020202020204f)):0.0f))):fRec153[1]);
				fTempPerm381 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm353)?fRec153[0]:((iTempPerm352)?(fRec153[0] + (fConst3 * (0 - (fRec140[0] * fRec153[0])))):0.0f)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm382 = (fTempPerm381 * ftbl0[(((int(fTempPerm378) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm383 = (2.0879500000000002f * (fTempPerm382 + (fTempPerm377 + fTempPerm373)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec155[0] = (fTempPerm381 * ftbl0[(((int((65536.0f * (fRec152[0] + (fSlow189 * fRec155[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm384 = (fTempPerm376 * ftbl0[(((int((65536.0f * (fRec149[0] + fRec155[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm385 = (2.0879500000000002f * (fTempPerm384 + fTempPerm373));
			}
			if (iSlow5 || iSlow3) {
				fRec156[0] = (fTempPerm376 * ftbl0[(((int((65536.0f * (fRec149[0] + (fSlow189 * fRec156[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm386 = (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + fRec156[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm387 = (2.0879500000000002f * (fTempPerm382 + (fTempPerm361 + fTempPerm386)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm388 = (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + fTempPerm372))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm389 = (2.0879500000000002f * (fTempPerm384 + (fTempPerm388 + fTempPerm361)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm390 = (fTempPerm354 * ftbl0[(((int((65536.0f * (fRec137[0] + fTempPerm360))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm391 = (2.0879500000000002f * (fTempPerm382 + (fTempPerm390 + fTempPerm386)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec157[0] = (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + (fSlow189 * fRec157[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm392 = (fTempPerm359 * ftbl0[(((int((65536.0f * (fRec141[0] + fRec157[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm393 = (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + (fTempPerm382 + fTempPerm377)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm394 = (2.0879500000000002f * (fTempPerm393 + (fTempPerm392 + fTempPerm355)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm395 = (fTempPerm359 * ftbl0[(((int((65536.0f * (fRec141[0] + fTempPerm367))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm396 = (fTempPerm395 + fTempPerm355);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm397 = (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + (fRec155[0] + fTempPerm377)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm398 = (2.0879500000000002f * (fTempPerm397 + fTempPerm396));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm399 = (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + fRec155[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm400 = (2.0879500000000002f * (fTempPerm384 + (fTempPerm399 + fTempPerm368)));
			}
			if (iSlow9) {
				fRec158[0] = (fTempPerm381 * ftbl0[(((int((fTempPerm378 + (fSlow190 * fRec158[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm401 = ftbl0[(((int((65536.0f * (fRec144[0] + fRec158[0]))) % 65536) + 65536) % 65536)];
				fTempPerm402 = (2.0879500000000002f * (((fTempPerm361 + (fTempPerm366 * fTempPerm401)) + (fTempPerm371 * fTempPerm401)) + (fTempPerm376 * ftbl0[(((int((65536.0f * (fRec149[0] + fRec158[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm403 = (2.0879500000000002f * (fTempPerm384 + (fTempPerm396 + fTempPerm399)));
			}
			if (iSlow28 || iSlow11) {
				fRec159[0] = (fTempPerm381 * ftbl0[(((int((fTempPerm378 + (fSlow191 * fRec159[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm404 = (fTempPerm376 * ftbl0[(((int((65536.0f * (fRec149[0] + fRec159[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm405 = ((ftbl0[(((int((65536.0f * (fRec144[0] + fRec159[0]))) % 65536) + 65536) % 65536)] * (fTempPerm366 + (2.0879500000000002f * fTempPerm371))) + (2.0879500000000002f * (fTempPerm404 + (fTempPerm354 * ftbl0[(((int((fTempPerm349 + (136835.89120000001f * fTempPerm360))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm406 = ((fTempPerm354 * ftbl0[(((int((65536.0f * (fRec137[0] + fRec157[0]))) % 65536) + 65536) % 65536)]) + fTempPerm392);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm407 = (fTempPerm376 * ftbl0[(((int((65536.0f * (fRec149[0] + fTempPerm382))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm408 = (2.0879500000000002f * (fTempPerm407 + (fTempPerm406 + (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + fTempPerm382))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm409 = (2.0879500000000002f * (fTempPerm393 + fTempPerm406));
			}
			if (iSlow14) {
				fRec160[0] = (fTempPerm381 * ftbl0[(((int((fTempPerm378 + (fSlow192 * fRec160[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm410 = (fTempPerm354 * ftbl0[(((int((65536.0f * (fRec137[0] + fTempPerm395))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm411 = (2.0879500000000002f * ((fTempPerm410 + (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + fRec160[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm376 * ftbl0[(((int((65536.0f * (fRec149[0] + fRec160[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm412 = (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + fTempPerm407))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm413 = (2.0879500000000002f * (fTempPerm354 * ftbl0[(((int((65536.0f * (fRec137[0] + (fTempPerm412 + (fRec157[0] + fTempPerm360))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec161[0] = (fTempPerm359 * ftbl0[(((int((fTempPerm356 + (fSlow193 * fRec161[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm414 = (2.0879500000000002f * (fTempPerm354 * ftbl0[(((int((65536.0f * (fRec137[0] + (fTempPerm388 + (fRec161[0] + fTempPerm407))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm415 = (2.0879500000000002f * (fTempPerm354 * ftbl0[(((int((65536.0f * (fRec137[0] + (fTempPerm388 + (fTempPerm360 + fTempPerm384))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec162[0] = (fTempPerm359 * ftbl0[(((int((fTempPerm356 + (fSlow192 * fRec162[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm416 = (fTempPerm354 * ftbl0[(((int((65536.0f * (fRec137[0] + fRec162[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm417 = (2.0879500000000002f * (fTempPerm416 + (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + fTempPerm393))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm418 = (2.0879500000000002f * (fTempPerm390 + (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + fTempPerm397))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm419 = (2.0879500000000002f * (fTempPerm390 + (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + (fTempPerm377 + (fRec155[0] + fTempPerm372))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec163[0] = (fTempPerm359 * ftbl0[(((int((fTempPerm356 + (fSlow194 * fRec163[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm420 = (fTempPerm354 * ftbl0[(((int((65536.0f * (fRec137[0] + fRec163[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm421 = (2.0879500000000002f * (fTempPerm420 + (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + (fTempPerm377 + (fTempPerm382 + fTempPerm372))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec164[0] = (fTempPerm381 * ftbl0[(((int((fTempPerm378 + (fSlow194 * fRec164[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm422 = (2.0879500000000002f * (fTempPerm410 + (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + (fRec164[0] + fTempPerm377)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec165[0] = (fTempPerm366 * ftbl0[(((int((fTempPerm362 + (fSlow194 * fRec165[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm423 = (2.0879500000000002f * (fTempPerm393 + (fTempPerm354 * ftbl0[(((int((65536.0f * (fRec137[0] + (fTempPerm359 * ftbl0[(((int((65536.0f * (fRec141[0] + fRec165[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm424 = (2.0879500000000002f * (fTempPerm416 + (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + (fTempPerm407 + fTempPerm372)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec166[0] = (fTempPerm371 * ftbl0[(((int((fTempPerm362 + (fSlow191 * fRec166[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm425 = (2.0879500000000002f * (fTempPerm390 + (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + (fRec166[0] + fTempPerm407)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm426 = (2.0879500000000002f * (fTempPerm390 + (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + (fTempPerm384 + fTempPerm372)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm427 = (fTempPerm390 + fTempPerm388);
			}
			if (iSlow27) {
				fRec167[0] = (2.0879500000000002f * (fTempPerm376 * ftbl0[(((int((65536.0f * (fRec149[0] + (fTempPerm381 * ftbl0[(((int((65536.0f * (fRec152[0] + (fSlow189 * fRec167[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm428 = (fRec167[0] + (2.0879500000000002f * fTempPerm427));
			}
			if (iSlow28) {
				fTempPerm429 = (2.0879500000000002f * (fTempPerm427 + fTempPerm404));
			}
			if (iSlow29) {
				fRec168[0] = (2.0879500000000002f * (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + (fTempPerm376 * ftbl0[(((int((65536.0f * (fRec149[0] + (fTempPerm381 * ftbl0[(((int((65536.0f * (fRec152[0] + (fSlow189 * fRec168[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm430 = (fRec168[0] + (2.0879500000000002f * fTempPerm410));
			}
			if (iSlow30) {
				fTempPerm431 = (2.0879500000000002f * (fTempPerm410 + (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + fTempPerm384))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm432 = (2.0879500000000002f * (fTempPerm420 + (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + fTempPerm412))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm433 = (2.0879500000000002f * (fTempPerm390 + (fTempPerm366 * ftbl0[(((int((65536.0f * (fRec144[0] + (fTempPerm371 * ftbl0[(((int((65536.0f * (fRec144[0] + (fTempPerm376 * ftbl0[(((int((65536.0f * (fRec149[0] + fRec164[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec170[0] = (iSlow688 * (iRec170[1] + 1));
			iTempPerm434 = int((iRec170[0] < iSlow199));
			fTempPerm435 = expf((0 - (fConst6 / ((iSlow690)?((iTempPerm434)?fSlow198:fSlow196):fSlow195))));
			fRec169[0] = ((fRec169[1] * fTempPerm435) + (((iSlow690)?((iTempPerm434)?1.5873015873015872f:fSlow805):0.0f) * (1.0f - fTempPerm435)));
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec171[0] = (fSlow808 + (fRec171[1] - floorf((fSlow808 + fRec171[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm436 = (65536.0f * fRec171[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec173[0] = ((iSlow834)?0.0f:min(fSlow832, (fRec173[1] + 1.0f)));
				iTempPerm437 = int((fRec173[0] < fSlow831));
				iTempPerm438 = int((fRec173[0] < fSlow836));
				fRec172[0] = ((iSlow841)?(fSlow840 * ((iTempPerm437)?((iTempPerm438)?((int((fRec173[0] < 0.0f)))?0.0f:((iTempPerm438)?(fSlow838 * (fRec173[0] / fSlow827)):fSlow820)):((iTempPerm437)?(fSlow819 + ((fSlow837 * ((fRec173[0] - fSlow836) / fSlow835)) + 74.25f)):fSlow811)):((int((fRec173[0] < fSlow832)))?(fSlow810 + (((0 - (fSlow811 * (fRec173[0] - fSlow831))) / fSlow830) + 56.25f)):0.0f))):fRec172[1]);
				fRec174[0] = ((iSlow842)?0.0f:min(fConst2, (fRec174[1] + 1.0f)));
				iTempPerm439 = int((fRec174[0] < fConst2));
				iTempPerm440 = int((fRec174[0] < 0.0f));
				fTempPerm441 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm440)?fRec172[0]:((iTempPerm439)?(fRec172[0] + (fConst3 * (0 - (fRec174[0] * fRec172[0])))):0.0f)))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm442 = (fTempPerm441 * ftbl0[(((int(fTempPerm436) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec175[0] = (fSlow843 + (fRec175[1] - floorf((fSlow843 + fRec175[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm443 = (65536.0f * fRec175[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec177[0] = ((iSlow834)?0.0f:min(fSlow864, (fRec177[1] + 1.0f)));
				iTempPerm444 = int((fRec177[0] < fSlow863));
				iTempPerm445 = int((fRec177[0] < fSlow866));
				fRec176[0] = ((iSlow841)?(fSlow840 * ((iTempPerm444)?((iTempPerm445)?((int((fRec177[0] < 0.0f)))?0.0f:((iTempPerm445)?(fSlow868 * (fRec177[0] / fSlow859)):fSlow852)):((iTempPerm444)?(fSlow851 + ((fSlow867 * ((fRec177[0] - fSlow866) / fSlow865)) + 7.25f)):fSlow845)):((int((fRec177[0] < fSlow864)))?(fSlow844 + (((0 - (fSlow845 * (fRec177[0] - fSlow863))) / fSlow862) + 5.4924242424242422f)):0.0f))):fRec176[1]);
				fTempPerm446 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm440)?fRec176[0]:((iTempPerm439)?(fRec176[0] + (fConst3 * (0 - (fRec174[0] * fRec176[0])))):0.0f)))));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow17 || iSlow15 || iSlow11 || iSlow9 || iSlow8 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm447 = (fTempPerm446 * ftbl0[(((int(fTempPerm443) % 65536) + 65536) % 65536)]);
			}
			if (iSlow9 || iSlow8 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fTempPerm448 = (fTempPerm447 + fTempPerm442);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec178[0] = (fSlow869 + (fRec178[1] - floorf((fSlow869 + fRec178[1]))));
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm449 = (65536.0f * fRec178[0]);
			}
			if (iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow22 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm450 = ftbl0[(((int(fTempPerm449) % 65536) + 65536) % 65536)];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec180[0] = ((iSlow834)?0.0f:min(fSlow887, (fRec180[1] + 1.0f)));
				iTempPerm451 = int((fRec180[0] < fSlow886));
				iTempPerm452 = int((fRec180[0] < fSlow889));
				fRec179[0] = ((iSlow841)?(fSlow840 * ((iTempPerm451)?((iTempPerm452)?((int((fRec180[0] < 0.0f)))?0.0f:((iTempPerm452)?(fSlow838 * (fRec180[0] / fSlow882)):fSlow820)):((iTempPerm451)?(fSlow819 + ((fSlow890 * ((fRec180[0] - fSlow889) / fSlow888)) + 74.25f)):fSlow871)):((int((fRec180[0] < fSlow887)))?(fSlow870 + (((0 - (fSlow871 * (fRec180[0] - fSlow886))) / fSlow885) + 71.25f)):0.0f))):fRec179[1]);
				fTempPerm453 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm440)?fRec179[0]:((iTempPerm439)?(fRec179[0] + (fConst3 * (0 - (fRec174[0] * fRec179[0])))):0.0f)))));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow8 || iSlow7 || iSlow2 || iSlow1) {
				fTempPerm454 = (fTempPerm453 * fTempPerm450);
			}
			if (iSlow8 || iSlow2 || iSlow1) {
				fTempPerm455 = (fTempPerm454 + fTempPerm448);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec182[0] = ((iSlow834)?0.0f:min(fSlow911, (fRec182[1] + 1.0f)));
				iTempPerm456 = int((fRec182[0] < fSlow910));
				iTempPerm457 = int((fRec182[0] < fSlow913));
				fRec181[0] = ((iSlow841)?(fSlow840 * ((iTempPerm456)?((iTempPerm457)?((int((fRec182[0] < 0.0f)))?0.0f:((iTempPerm457)?(fSlow915 * (fRec182[0] / fSlow906)):fSlow899)):((iTempPerm456)?(fSlow898 + ((fSlow914 * ((fRec182[0] - fSlow913) / fSlow912)) + 22.25f)):fSlow892)):((int((fRec182[0] < fSlow911)))?(fSlow891 + (((0 - (fSlow892 * (fRec182[0] - fSlow910))) / fSlow909) + 21.3510101010101f)):0.0f))):fRec181[1]);
				fTempPerm458 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm440)?fRec181[0]:((iTempPerm439)?(fRec181[0] + (fConst3 * (0 - (fRec174[0] * fRec181[0])))):0.0f)))));
			}
			if (iSlow28 || iSlow27 || iSlow26 || iSlow24 || iSlow21 || iSlow20 || iSlow17 || iSlow16 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm459 = (fTempPerm458 * fTempPerm450);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm460 = (fTempPerm459 + fTempPerm455);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec183[0] = (fSlow917 + (fRec183[1] - floorf((fSlow917 + fRec183[1]))));
				fRec185[0] = ((iSlow834)?0.0f:min(fSlow924, (fRec185[1] + 1.0f)));
				iTempPerm461 = int((fRec185[0] < fSlow922));
				iTempPerm462 = int((fRec185[0] < fSlow926));
				fRec184[0] = ((iSlow841)?(fSlow840 * ((iTempPerm461)?((iTempPerm462)?((int((fRec185[0] < 0.0f)))?0.0f:((iTempPerm462)?(fSlow928 * fRec185[0]):99.0f)):((iTempPerm461)?((fSlow927 * (0 - (4.0f * (fRec185[0] - fSlow926)))) + 99.0f):95.0f)):((int((fRec185[0] < fSlow924)))?((fSlow925 * (0 - (95.0f * (fRec185[0] - fSlow922)))) + 95.0f):0.0f))):fRec184[1]);
				fTempPerm463 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm440)?fRec184[0]:((iTempPerm439)?(fRec184[0] + (fConst3 * (0 - (fRec174[0] * fRec184[0])))):0.0f)))));
			}
			if (iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow13 || iSlow7 || iSlow6 || iSlow1) {
				fTempPerm464 = (fTempPerm463 * ftbl0[(((int((65536.0f * fRec183[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec186[0] = (fSlow930 + (fRec186[1] - floorf((fSlow930 + fRec186[1]))));
			}
			if (iSlow32 || iSlow31 || iSlow28 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow9 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm465 = (65536.0f * fRec186[0]);
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec188[0] = ((iSlow834)?0.0f:min(fSlow951, (fRec188[1] + 1.0f)));
				iTempPerm466 = int((fRec188[0] < fSlow950));
				iTempPerm467 = int((fRec188[0] < fSlow953));
				fRec187[0] = ((iSlow841)?(fSlow840 * ((iTempPerm466)?((iTempPerm467)?((int((fRec188[0] < 0.0f)))?0.0f:((iTempPerm467)?(fSlow955 * (fRec188[0] / fSlow946)):fSlow939)):((iTempPerm466)?(fSlow938 + ((fSlow954 * ((fRec188[0] - fSlow953) / fSlow952)) + 19.75f)):fSlow932)):((int((fRec188[0] < fSlow951)))?(fSlow931 + (((0 - (fSlow932 * (fRec188[0] - fSlow950))) / fSlow949) + 18.952020202020204f)):0.0f))):fRec187[1]);
				fTempPerm468 = faustpower<8>((0.01020408163265306f * min((float)98, ((iTempPerm440)?fRec187[0]:((iTempPerm439)?(fRec187[0] + (fConst3 * (0 - (fRec174[0] * fRec187[0])))):0.0f)))));
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow23 || iSlow21 || iSlow18 || iSlow16 || iSlow15 || iSlow13 || iSlow12 || iSlow6 || iSlow5 || iSlow3 || iSlow1) {
				fTempPerm469 = (fTempPerm468 * ftbl0[(((int(fTempPerm465) % 65536) + 65536) % 65536)]);
			}
			if (iSlow1) {
				fTempPerm470 = (2.0879500000000002f * (fTempPerm469 + (fTempPerm464 + fTempPerm460)));
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec189[0] = (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec186[0] + (fSlow189 * fRec189[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow26 || iSlow17 || iSlow10 || iSlow8 || iSlow4 || iSlow2) {
				fTempPerm471 = (fTempPerm463 * ftbl0[(((int((65536.0f * (fRec183[0] + fRec189[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2) {
				fTempPerm472 = (2.0879500000000002f * (fTempPerm471 + fTempPerm460));
			}
			if (iSlow5 || iSlow3) {
				fRec190[0] = (fTempPerm463 * ftbl0[(((int((65536.0f * (fRec183[0] + (fSlow189 * fRec190[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm473 = (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + fRec190[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow3) {
				fTempPerm474 = (2.0879500000000002f * (fTempPerm469 + (fTempPerm448 + fTempPerm473)));
			}
			if (iSlow28 || iSlow27 || iSlow17 || iSlow16 || iSlow4) {
				fTempPerm475 = (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + fTempPerm459))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4) {
				fTempPerm476 = (2.0879500000000002f * (fTempPerm471 + (fTempPerm475 + fTempPerm448)));
			}
			if (iSlow32 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow20 || iSlow19 || iSlow5) {
				fTempPerm477 = (fTempPerm441 * ftbl0[(((int((65536.0f * (fRec171[0] + fTempPerm447))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow5) {
				fTempPerm478 = (2.0879500000000002f * (fTempPerm469 + (fTempPerm477 + fTempPerm473)));
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec191[0] = (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + (fSlow189 * fRec191[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow13 || iSlow12 || iSlow6) {
				fTempPerm479 = (fTempPerm446 * ftbl0[(((int((65536.0f * (fRec175[0] + fRec191[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow23 || iSlow18 || iSlow13 || iSlow6) {
				fTempPerm480 = (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + (fTempPerm469 + fTempPerm464)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow6) {
				fTempPerm481 = (2.0879500000000002f * (fTempPerm480 + (fTempPerm479 + fTempPerm442)));
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14 || iSlow10 || iSlow7) {
				fTempPerm482 = (fTempPerm446 * ftbl0[(((int((65536.0f * (fRec175[0] + fTempPerm454))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow10 || iSlow7) {
				fTempPerm483 = (fTempPerm482 + fTempPerm442);
			}
			if (iSlow19 || iSlow7) {
				fTempPerm484 = (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + (fRec189[0] + fTempPerm464)))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow7) {
				fTempPerm485 = (2.0879500000000002f * (fTempPerm484 + fTempPerm483));
			}
			if (iSlow10 || iSlow8) {
				fTempPerm486 = (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + fRec189[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow8) {
				fTempPerm487 = (2.0879500000000002f * (fTempPerm471 + (fTempPerm486 + fTempPerm455)));
			}
			if (iSlow9) {
				fRec192[0] = (fTempPerm468 * ftbl0[(((int((fTempPerm465 + (fSlow190 * fRec192[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm488 = ftbl0[(((int((65536.0f * (fRec178[0] + fRec192[0]))) % 65536) + 65536) % 65536)];
				fTempPerm489 = (2.0879500000000002f * (((fTempPerm448 + (fTempPerm453 * fTempPerm488)) + (fTempPerm458 * fTempPerm488)) + (fTempPerm463 * ftbl0[(((int((65536.0f * (fRec183[0] + fRec192[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow10) {
				fTempPerm490 = (2.0879500000000002f * (fTempPerm471 + (fTempPerm483 + fTempPerm486)));
			}
			if (iSlow28 || iSlow11) {
				fRec193[0] = (fTempPerm468 * ftbl0[(((int((fTempPerm465 + (fSlow191 * fRec193[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm491 = (fTempPerm463 * ftbl0[(((int((65536.0f * (fRec183[0] + fRec193[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow11) {
				fTempPerm492 = ((ftbl0[(((int((65536.0f * (fRec178[0] + fRec193[0]))) % 65536) + 65536) % 65536)] * (fTempPerm453 + (2.0879500000000002f * fTempPerm458))) + (2.0879500000000002f * (fTempPerm491 + (fTempPerm441 * ftbl0[(((int((fTempPerm436 + (136835.89120000001f * fTempPerm447))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13 || iSlow12) {
				fTempPerm493 = ((fTempPerm441 * ftbl0[(((int((65536.0f * (fRec171[0] + fRec191[0]))) % 65536) + 65536) % 65536)]) + fTempPerm479);
			}
			if (iSlow31 || iSlow25 || iSlow24 || iSlow16 || iSlow15 || iSlow12) {
				fTempPerm494 = (fTempPerm463 * ftbl0[(((int((65536.0f * (fRec183[0] + fTempPerm469))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12) {
				fTempPerm495 = (2.0879500000000002f * (fTempPerm494 + (fTempPerm493 + (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + fTempPerm469))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow13) {
				fTempPerm496 = (2.0879500000000002f * (fTempPerm480 + fTempPerm493));
			}
			if (iSlow14) {
				fRec194[0] = (fTempPerm468 * ftbl0[(((int((fTempPerm465 + (fSlow192 * fRec194[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow30 || iSlow29 || iSlow22 || iSlow14) {
				fTempPerm497 = (fTempPerm441 * ftbl0[(((int((65536.0f * (fRec171[0] + fTempPerm482))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow14) {
				fTempPerm498 = (2.0879500000000002f * ((fTempPerm497 + (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + fRec194[0]))) % 65536) + 65536) % 65536)])) + (fTempPerm463 * ftbl0[(((int((65536.0f * (fRec183[0] + fRec194[0]))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow15) {
				fTempPerm499 = (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + fTempPerm494))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow15) {
				fTempPerm500 = (2.0879500000000002f * (fTempPerm441 * ftbl0[(((int((65536.0f * (fRec171[0] + (fTempPerm499 + (fRec191[0] + fTempPerm447))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow16) {
				fRec195[0] = (fTempPerm446 * ftbl0[(((int((fTempPerm443 + (fSlow193 * fRec195[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm501 = (2.0879500000000002f * (fTempPerm441 * ftbl0[(((int((65536.0f * (fRec171[0] + (fTempPerm475 + (fRec195[0] + fTempPerm494))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow17) {
				fTempPerm502 = (2.0879500000000002f * (fTempPerm441 * ftbl0[(((int((65536.0f * (fRec171[0] + (fTempPerm475 + (fTempPerm447 + fTempPerm471))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow24 || iSlow18) {
				fRec196[0] = (fTempPerm446 * ftbl0[(((int((fTempPerm443 + (fSlow192 * fRec196[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm503 = (fTempPerm441 * ftbl0[(((int((65536.0f * (fRec171[0] + fRec196[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow18) {
				fTempPerm504 = (2.0879500000000002f * (fTempPerm503 + (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + fTempPerm480))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow19) {
				fTempPerm505 = (2.0879500000000002f * (fTempPerm477 + (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + fTempPerm484))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow20) {
				fTempPerm506 = (2.0879500000000002f * (fTempPerm477 + (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + (fTempPerm464 + (fRec189[0] + fTempPerm459))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31 || iSlow21) {
				fRec197[0] = (fTempPerm446 * ftbl0[(((int((fTempPerm443 + (fSlow194 * fRec197[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm507 = (fTempPerm441 * ftbl0[(((int((65536.0f * (fRec171[0] + fRec197[0]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow21) {
				fTempPerm508 = (2.0879500000000002f * (fTempPerm507 + (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + (fTempPerm464 + (fTempPerm469 + fTempPerm459))))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32 || iSlow22) {
				fRec198[0] = (fTempPerm468 * ftbl0[(((int((fTempPerm465 + (fSlow194 * fRec198[1]))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow22) {
				fTempPerm509 = (2.0879500000000002f * (fTempPerm497 + (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + (fRec198[0] + fTempPerm464)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow23) {
				fRec199[0] = (fTempPerm453 * ftbl0[(((int((fTempPerm449 + (fSlow194 * fRec199[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm510 = (2.0879500000000002f * (fTempPerm480 + (fTempPerm441 * ftbl0[(((int((65536.0f * (fRec171[0] + (fTempPerm446 * ftbl0[(((int((65536.0f * (fRec175[0] + fRec199[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow24) {
				fTempPerm511 = (2.0879500000000002f * (fTempPerm503 + (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + (fTempPerm494 + fTempPerm459)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow25) {
				fRec200[0] = (fTempPerm458 * ftbl0[(((int((fTempPerm449 + (fSlow191 * fRec200[1]))) % 65536) + 65536) % 65536)]);
				fTempPerm512 = (2.0879500000000002f * (fTempPerm477 + (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + (fRec200[0] + fTempPerm494)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow26) {
				fTempPerm513 = (2.0879500000000002f * (fTempPerm477 + (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + (fTempPerm471 + fTempPerm459)))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow28 || iSlow27) {
				fTempPerm514 = (fTempPerm477 + fTempPerm475);
			}
			if (iSlow27) {
				fRec201[0] = (2.0879500000000002f * (fTempPerm463 * ftbl0[(((int((65536.0f * (fRec183[0] + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec186[0] + (fSlow189 * fRec201[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm515 = (fRec201[0] + (2.0879500000000002f * fTempPerm514));
			}
			if (iSlow28) {
				fTempPerm516 = (2.0879500000000002f * (fTempPerm514 + fTempPerm491));
			}
			if (iSlow29) {
				fRec202[0] = (2.0879500000000002f * (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + (fTempPerm463 * ftbl0[(((int((65536.0f * (fRec183[0] + (fTempPerm468 * ftbl0[(((int((65536.0f * (fRec186[0] + (fSlow189 * fRec202[1])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)]));
				fTempPerm517 = (fRec202[0] + (2.0879500000000002f * fTempPerm497));
			}
			if (iSlow30) {
				fTempPerm518 = (2.0879500000000002f * (fTempPerm497 + (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + fTempPerm471))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow31) {
				fTempPerm519 = (2.0879500000000002f * (fTempPerm507 + (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + fTempPerm499))) % 65536) + 65536) % 65536)])));
			}
			if (iSlow32) {
				fTempPerm520 = (2.0879500000000002f * (fTempPerm477 + (fTempPerm453 * ftbl0[(((int((65536.0f * (fRec178[0] + (fTempPerm458 * ftbl0[(((int((65536.0f * (fRec178[0] + (fTempPerm463 * ftbl0[(((int((65536.0f * (fRec183[0] + fRec198[0]))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])))) % 65536) + 65536) % 65536)])));
			}
			iRec204[0] = (iSlow839 * (iRec204[1] + 1));
			iTempPerm521 = int((iRec204[0] < iSlow199));
			fTempPerm522 = expf((0 - (fConst6 / ((iSlow841)?((iTempPerm521)?fSlow198:fSlow196):fSlow195))));
			fRec203[0] = ((fRec203[1] * fTempPerm522) + (((iSlow841)?((iTempPerm521)?1.5873015873015872f:fSlow956):0.0f) * (1.0f - fTempPerm522)));
			output0[i] = (FAUSTFLOAT)((((((fSlow809 * (min(1.0f, fRec203[0]) * (((((((((((((((((((((((((((((((fTempPerm520 + fTempPerm519) + fTempPerm518) + fTempPerm517) + fTempPerm516) + fTempPerm515) + fTempPerm513) + fTempPerm512) + fTempPerm511) + fTempPerm510) + fTempPerm509) + fTempPerm508) + fTempPerm506) + fTempPerm505) + fTempPerm504) + fTempPerm502) + fTempPerm501) + fTempPerm500) + fTempPerm498) + fTempPerm496) + fTempPerm495) + fTempPerm492) + fTempPerm490) + fTempPerm489) + fTempPerm487) + fTempPerm485) + fTempPerm481) + fTempPerm478) + fTempPerm476) + fTempPerm474) + fTempPerm472) + fTempPerm470))) + (fSlow658 * (min(1.0f, fRec169[0]) * (((((((((((((((((((((((((((((((fTempPerm433 + fTempPerm432) + fTempPerm431) + fTempPerm430) + fTempPerm429) + fTempPerm428) + fTempPerm426) + fTempPerm425) + fTempPerm424) + fTempPerm423) + fTempPerm422) + fTempPerm421) + fTempPerm419) + fTempPerm418) + fTempPerm417) + fTempPerm415) + fTempPerm414) + fTempPerm413) + fTempPerm411) + fTempPerm409) + fTempPerm408) + fTempPerm405) + fTempPerm403) + fTempPerm402) + fTempPerm400) + fTempPerm398) + fTempPerm394) + fTempPerm391) + fTempPerm389) + fTempPerm387) + fTempPerm385) + fTempPerm383)))) + (fSlow507 * (min(1.0f, fRec135[0]) * (((((((((((((((((((((((((((((((fTempPerm346 + fTempPerm345) + fTempPerm344) + fTempPerm343) + fTempPerm342) + fTempPerm341) + fTempPerm339) + fTempPerm338) + fTempPerm337) + fTempPerm336) + fTempPerm335) + fTempPerm334) + fTempPerm332) + fTempPerm331) + fTempPerm330) + fTempPerm328) + fTempPerm327) + fTempPerm326) + fTempPerm324) + fTempPerm322) + fTempPerm321) + fTempPerm318) + fTempPerm316) + fTempPerm315) + fTempPerm313) + fTempPerm311) + fTempPerm307) + fTempPerm304) + fTempPerm302) + fTempPerm300) + fTempPerm298) + fTempPerm296)))) + (fSlow356 * (min(1.0f, fRec101[0]) * (((((((((((((((((((((((((((((((fTempPerm259 + fTempPerm258) + fTempPerm257) + fTempPerm256) + fTempPerm255) + fTempPerm254) + fTempPerm252) + fTempPerm251) + fTempPerm250) + fTempPerm249) + fTempPerm248) + fTempPerm247) + fTempPerm245) + fTempPerm244) + fTempPerm243) + fTempPerm241) + fTempPerm240) + fTempPerm239) + fTempPerm237) + fTempPerm235) + fTempPerm234) + fTempPerm231) + fTempPerm229) + fTempPerm228) + fTempPerm226) + fTempPerm224) + fTempPerm220) + fTempPerm217) + fTempPerm215) + fTempPerm213) + fTempPerm211) + fTempPerm209)))) + (fSlow205 * (min(1.0f, fRec67[0]) * (((((((((((((((((((((((((((((((fTempPerm172 + fTempPerm171) + fTempPerm170) + fTempPerm169) + fTempPerm168) + fTempPerm167) + fTempPerm165) + fTempPerm164) + fTempPerm163) + fTempPerm162) + fTempPerm161) + fTempPerm160) + fTempPerm158) + fTempPerm157) + fTempPerm156) + fTempPerm154) + fTempPerm153) + fTempPerm152) + fTempPerm150) + fTempPerm148) + fTempPerm147) + fTempPerm144) + fTempPerm142) + fTempPerm141) + fTempPerm139) + fTempPerm137) + fTempPerm133) + fTempPerm130) + fTempPerm128) + fTempPerm126) + fTempPerm124) + fTempPerm122)))) + (fSlow36 * (min(1.0f, fRec33[0]) * (((((((((((((((((((((((((((((((fTempPerm85 + fTempPerm84) + fTempPerm83) + fTempPerm82) + fTempPerm81) + fTempPerm80) + fTempPerm78) + fTempPerm77) + fTempPerm76) + fTempPerm75) + fTempPerm74) + fTempPerm73) + fTempPerm71) + fTempPerm70) + fTempPerm69) + fTempPerm67) + fTempPerm66) + fTempPerm65) + fTempPerm63) + fTempPerm61) + fTempPerm60) + fTempPerm57) + fTempPerm55) + fTempPerm54) + fTempPerm52) + fTempPerm50) + fTempPerm46) + fTempPerm43) + fTempPerm41) + fTempPerm39) + fTempPerm37) + fTempPerm35))));
			// post processing
			fRec203[1] = fRec203[0];
			iRec204[1] = iRec204[0];
			if (iSlow29) {
				fRec202[1] = fRec202[0];
			}
			if (iSlow27) {
				fRec201[1] = fRec201[0];
			}
			if (iSlow25) {
				fRec200[1] = fRec200[0];
			}
			if (iSlow23) {
				fRec199[1] = fRec199[0];
			}
			if (iSlow32 || iSlow22) {
				fRec198[1] = fRec198[0];
			}
			if (iSlow31 || iSlow21) {
				fRec197[1] = fRec197[0];
			}
			if (iSlow24 || iSlow18) {
				fRec196[1] = fRec196[0];
			}
			if (iSlow16) {
				fRec195[1] = fRec195[0];
			}
			if (iSlow14) {
				fRec194[1] = fRec194[0];
			}
			if (iSlow28 || iSlow11) {
				fRec193[1] = fRec193[0];
			}
			if (iSlow9) {
				fRec192[1] = fRec192[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec191[1] = fRec191[0];
			}
			if (iSlow5 || iSlow3) {
				fRec190[1] = fRec190[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec189[1] = fRec189[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec187[1] = fRec187[0];
				fRec188[1] = fRec188[0];
				fRec186[1] = fRec186[0];
				fRec184[1] = fRec184[0];
				fRec185[1] = fRec185[0];
				fRec183[1] = fRec183[0];
				fRec181[1] = fRec181[0];
				fRec182[1] = fRec182[0];
				fRec179[1] = fRec179[0];
				fRec180[1] = fRec180[0];
				fRec178[1] = fRec178[0];
				fRec176[1] = fRec176[0];
				fRec177[1] = fRec177[0];
				fRec175[1] = fRec175[0];
				fRec174[1] = fRec174[0];
				fRec172[1] = fRec172[0];
				fRec173[1] = fRec173[0];
				fRec171[1] = fRec171[0];
			}
			fRec169[1] = fRec169[0];
			iRec170[1] = iRec170[0];
			if (iSlow29) {
				fRec168[1] = fRec168[0];
			}
			if (iSlow27) {
				fRec167[1] = fRec167[0];
			}
			if (iSlow25) {
				fRec166[1] = fRec166[0];
			}
			if (iSlow23) {
				fRec165[1] = fRec165[0];
			}
			if (iSlow32 || iSlow22) {
				fRec164[1] = fRec164[0];
			}
			if (iSlow31 || iSlow21) {
				fRec163[1] = fRec163[0];
			}
			if (iSlow24 || iSlow18) {
				fRec162[1] = fRec162[0];
			}
			if (iSlow16) {
				fRec161[1] = fRec161[0];
			}
			if (iSlow14) {
				fRec160[1] = fRec160[0];
			}
			if (iSlow28 || iSlow11) {
				fRec159[1] = fRec159[0];
			}
			if (iSlow9) {
				fRec158[1] = fRec158[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec157[1] = fRec157[0];
			}
			if (iSlow5 || iSlow3) {
				fRec156[1] = fRec156[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec155[1] = fRec155[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec153[1] = fRec153[0];
				fRec154[1] = fRec154[0];
				fRec152[1] = fRec152[0];
				fRec150[1] = fRec150[0];
				fRec151[1] = fRec151[0];
				fRec149[1] = fRec149[0];
				fRec147[1] = fRec147[0];
				fRec148[1] = fRec148[0];
				fRec145[1] = fRec145[0];
				fRec146[1] = fRec146[0];
				fRec144[1] = fRec144[0];
				fRec142[1] = fRec142[0];
				fRec143[1] = fRec143[0];
				fRec141[1] = fRec141[0];
				fRec140[1] = fRec140[0];
				fRec138[1] = fRec138[0];
				fRec139[1] = fRec139[0];
				fRec137[1] = fRec137[0];
			}
			fRec135[1] = fRec135[0];
			iRec136[1] = iRec136[0];
			if (iSlow29) {
				fRec134[1] = fRec134[0];
			}
			if (iSlow27) {
				fRec133[1] = fRec133[0];
			}
			if (iSlow25) {
				fRec132[1] = fRec132[0];
			}
			if (iSlow23) {
				fRec131[1] = fRec131[0];
			}
			if (iSlow32 || iSlow22) {
				fRec130[1] = fRec130[0];
			}
			if (iSlow31 || iSlow21) {
				fRec129[1] = fRec129[0];
			}
			if (iSlow24 || iSlow18) {
				fRec128[1] = fRec128[0];
			}
			if (iSlow16) {
				fRec127[1] = fRec127[0];
			}
			if (iSlow14) {
				fRec126[1] = fRec126[0];
			}
			if (iSlow28 || iSlow11) {
				fRec125[1] = fRec125[0];
			}
			if (iSlow9) {
				fRec124[1] = fRec124[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec123[1] = fRec123[0];
			}
			if (iSlow5 || iSlow3) {
				fRec122[1] = fRec122[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec121[1] = fRec121[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec119[1] = fRec119[0];
				fRec120[1] = fRec120[0];
				fRec118[1] = fRec118[0];
				fRec116[1] = fRec116[0];
				fRec117[1] = fRec117[0];
				fRec115[1] = fRec115[0];
				fRec113[1] = fRec113[0];
				fRec114[1] = fRec114[0];
				fRec111[1] = fRec111[0];
				fRec112[1] = fRec112[0];
				fRec110[1] = fRec110[0];
				fRec108[1] = fRec108[0];
				fRec109[1] = fRec109[0];
				fRec107[1] = fRec107[0];
				fRec106[1] = fRec106[0];
				fRec104[1] = fRec104[0];
				fRec105[1] = fRec105[0];
				fRec103[1] = fRec103[0];
			}
			fRec101[1] = fRec101[0];
			iRec102[1] = iRec102[0];
			if (iSlow29) {
				fRec100[1] = fRec100[0];
			}
			if (iSlow27) {
				fRec99[1] = fRec99[0];
			}
			if (iSlow25) {
				fRec98[1] = fRec98[0];
			}
			if (iSlow23) {
				fRec97[1] = fRec97[0];
			}
			if (iSlow32 || iSlow22) {
				fRec96[1] = fRec96[0];
			}
			if (iSlow31 || iSlow21) {
				fRec95[1] = fRec95[0];
			}
			if (iSlow24 || iSlow18) {
				fRec94[1] = fRec94[0];
			}
			if (iSlow16) {
				fRec93[1] = fRec93[0];
			}
			if (iSlow14) {
				fRec92[1] = fRec92[0];
			}
			if (iSlow28 || iSlow11) {
				fRec91[1] = fRec91[0];
			}
			if (iSlow9) {
				fRec90[1] = fRec90[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec89[1] = fRec89[0];
			}
			if (iSlow5 || iSlow3) {
				fRec88[1] = fRec88[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec87[1] = fRec87[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec85[1] = fRec85[0];
				fRec86[1] = fRec86[0];
				fRec84[1] = fRec84[0];
				fRec82[1] = fRec82[0];
				fRec83[1] = fRec83[0];
				fRec81[1] = fRec81[0];
				fRec79[1] = fRec79[0];
				fRec80[1] = fRec80[0];
				fRec77[1] = fRec77[0];
				fRec78[1] = fRec78[0];
				fRec76[1] = fRec76[0];
				fRec74[1] = fRec74[0];
				fRec75[1] = fRec75[0];
				fRec73[1] = fRec73[0];
				fRec72[1] = fRec72[0];
				fRec70[1] = fRec70[0];
				fRec71[1] = fRec71[0];
				fRec69[1] = fRec69[0];
			}
			fRec67[1] = fRec67[0];
			iRec68[1] = iRec68[0];
			if (iSlow29) {
				fRec66[1] = fRec66[0];
			}
			if (iSlow27) {
				fRec65[1] = fRec65[0];
			}
			if (iSlow25) {
				fRec64[1] = fRec64[0];
			}
			if (iSlow23) {
				fRec63[1] = fRec63[0];
			}
			if (iSlow32 || iSlow22) {
				fRec62[1] = fRec62[0];
			}
			if (iSlow31 || iSlow21) {
				fRec61[1] = fRec61[0];
			}
			if (iSlow24 || iSlow18) {
				fRec60[1] = fRec60[0];
			}
			if (iSlow16) {
				fRec59[1] = fRec59[0];
			}
			if (iSlow14) {
				fRec58[1] = fRec58[0];
			}
			if (iSlow28 || iSlow11) {
				fRec57[1] = fRec57[0];
			}
			if (iSlow9) {
				fRec56[1] = fRec56[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec55[1] = fRec55[0];
			}
			if (iSlow5 || iSlow3) {
				fRec54[1] = fRec54[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec53[1] = fRec53[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec51[1] = fRec51[0];
				fRec52[1] = fRec52[0];
				fRec50[1] = fRec50[0];
				fRec48[1] = fRec48[0];
				fRec49[1] = fRec49[0];
				fRec47[1] = fRec47[0];
				fRec45[1] = fRec45[0];
				fRec46[1] = fRec46[0];
				fRec43[1] = fRec43[0];
				fRec44[1] = fRec44[0];
				fRec42[1] = fRec42[0];
				fRec40[1] = fRec40[0];
				fRec41[1] = fRec41[0];
				fRec39[1] = fRec39[0];
				fRec38[1] = fRec38[0];
				fRec36[1] = fRec36[0];
				fRec37[1] = fRec37[0];
				fRec35[1] = fRec35[0];
			}
			fRec33[1] = fRec33[0];
			iRec34[1] = iRec34[0];
			if (iSlow29) {
				fRec32[1] = fRec32[0];
			}
			if (iSlow27) {
				fRec31[1] = fRec31[0];
			}
			if (iSlow25) {
				fRec30[1] = fRec30[0];
			}
			if (iSlow23) {
				fRec29[1] = fRec29[0];
			}
			if (iSlow32 || iSlow22) {
				fRec28[1] = fRec28[0];
			}
			if (iSlow31 || iSlow21) {
				fRec27[1] = fRec27[0];
			}
			if (iSlow24 || iSlow18) {
				fRec26[1] = fRec26[0];
			}
			if (iSlow16) {
				fRec25[1] = fRec25[0];
			}
			if (iSlow14) {
				fRec24[1] = fRec24[0];
			}
			if (iSlow28 || iSlow11) {
				fRec23[1] = fRec23[0];
			}
			if (iSlow9) {
				fRec22[1] = fRec22[0];
			}
			if (iSlow15 || iSlow13 || iSlow12 || iSlow6) {
				fRec21[1] = fRec21[0];
			}
			if (iSlow5 || iSlow3) {
				fRec20[1] = fRec20[0];
			}
			if (iSlow30 || iSlow26 || iSlow20 || iSlow19 || iSlow17 || iSlow10 || iSlow8 || iSlow7 || iSlow4 || iSlow2) {
				fRec19[1] = fRec19[0];
			}
			if (iSlow32 || iSlow31 || iSlow30 || iSlow29 || iSlow28 || iSlow27 || iSlow26 || iSlow25 || iSlow24 || iSlow23 || iSlow22 || iSlow21 || iSlow20 || iSlow19 || iSlow18 || iSlow17 || iSlow16 || iSlow15 || iSlow14 || iSlow13 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec17[1] = fRec17[0];
				fRec18[1] = fRec18[0];
				fRec16[1] = fRec16[0];
				fRec14[1] = fRec14[0];
				fRec15[1] = fRec15[0];
				fRec13[1] = fRec13[0];
				fRec11[1] = fRec11[0];
				fRec12[1] = fRec12[0];
				fRec9[1] = fRec9[0];
				fRec10[1] = fRec10[0];
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
