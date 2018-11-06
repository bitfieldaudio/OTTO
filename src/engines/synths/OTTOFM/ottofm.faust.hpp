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
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	float 	fConst2;
	FAUSTFLOAT 	fslider6;
	float 	fRec3[2];
	float 	fConst3;
	int 	iTempPerm1;
	float 	fRec2[2];
	float 	fRec4[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	float 	fRec5[2];
	FAUSTFLOAT 	fbutton1;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	float 	fRec7[2];
	int 	iTempPerm2;
	float 	fRec6[2];
	float 	fRec8[2];
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	float 	fRec9[2];
	FAUSTFLOAT 	fbutton2;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT 	fslider21;
	float 	fRec11[2];
	int 	iTempPerm3;
	float 	fRec10[2];
	float 	fRec12[2];
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT 	fslider25;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT 	fbutton3;
	int 	iRec15[2];
	int 	iTempPerm4;
	float 	fConst4;
	float 	fTempPerm5;
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	float 	fRec14[2];
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT 	fslider34;
	float 	fTempPerm6;
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fslider36;
	FAUSTFLOAT 	fslider37;
	float 	fRec16[2];
	FAUSTFLOAT 	fbutton4;
	FAUSTFLOAT 	fslider38;
	FAUSTFLOAT 	fslider39;
	FAUSTFLOAT 	fslider40;
	float 	fRec18[2];
	int 	iTempPerm7;
	float 	fRec17[2];
	float 	fRec19[2];
	FAUSTFLOAT 	fslider41;
	FAUSTFLOAT 	fslider42;
	FAUSTFLOAT 	fslider43;
	FAUSTFLOAT 	fslider44;
	float 	fRec20[2];
	FAUSTFLOAT 	fbutton5;
	FAUSTFLOAT 	fslider45;
	FAUSTFLOAT 	fslider46;
	FAUSTFLOAT 	fslider47;
	float 	fRec22[2];
	int 	iTempPerm8;
	float 	fRec21[2];
	float 	fRec23[2];
	FAUSTFLOAT 	fslider48;
	FAUSTFLOAT 	fslider49;
	FAUSTFLOAT 	fslider50;
	FAUSTFLOAT 	fslider51;
	float 	fRec24[2];
	FAUSTFLOAT 	fbutton6;
	FAUSTFLOAT 	fslider52;
	FAUSTFLOAT 	fslider53;
	FAUSTFLOAT 	fslider54;
	float 	fRec26[2];
	int 	iTempPerm9;
	float 	fRec25[2];
	float 	fRec27[2];
	FAUSTFLOAT 	fslider55;
	FAUSTFLOAT 	fslider56;
	FAUSTFLOAT 	fslider57;
	FAUSTFLOAT 	fslider58;
	float 	fRec28[2];
	FAUSTFLOAT 	fslider59;
	FAUSTFLOAT 	fslider60;
	FAUSTFLOAT 	fbutton7;
	int 	iRec30[2];
	int 	iTempPerm10;
	float 	fTempPerm11;
	FAUSTFLOAT 	fslider61;
	float 	fRec29[2];
	FAUSTFLOAT 	fslider62;
	FAUSTFLOAT 	fslider63;
	float 	fTempPerm12;
	FAUSTFLOAT 	fslider64;
	FAUSTFLOAT 	fslider65;
	FAUSTFLOAT 	fslider66;
	float 	fRec31[2];
	FAUSTFLOAT 	fbutton8;
	FAUSTFLOAT 	fslider67;
	FAUSTFLOAT 	fslider68;
	FAUSTFLOAT 	fslider69;
	float 	fRec33[2];
	int 	iTempPerm13;
	float 	fRec32[2];
	float 	fRec34[2];
	FAUSTFLOAT 	fslider70;
	FAUSTFLOAT 	fslider71;
	FAUSTFLOAT 	fslider72;
	FAUSTFLOAT 	fslider73;
	float 	fRec35[2];
	FAUSTFLOAT 	fbutton9;
	FAUSTFLOAT 	fslider74;
	FAUSTFLOAT 	fslider75;
	FAUSTFLOAT 	fslider76;
	float 	fRec37[2];
	int 	iTempPerm14;
	float 	fRec36[2];
	float 	fRec38[2];
	FAUSTFLOAT 	fslider77;
	FAUSTFLOAT 	fslider78;
	FAUSTFLOAT 	fslider79;
	FAUSTFLOAT 	fslider80;
	float 	fRec39[2];
	FAUSTFLOAT 	fbutton10;
	FAUSTFLOAT 	fslider81;
	FAUSTFLOAT 	fslider82;
	FAUSTFLOAT 	fslider83;
	float 	fRec41[2];
	int 	iTempPerm15;
	float 	fRec40[2];
	float 	fRec42[2];
	FAUSTFLOAT 	fslider84;
	FAUSTFLOAT 	fslider85;
	FAUSTFLOAT 	fslider86;
	FAUSTFLOAT 	fslider87;
	float 	fRec43[2];
	FAUSTFLOAT 	fslider88;
	FAUSTFLOAT 	fslider89;
	FAUSTFLOAT 	fbutton11;
	int 	iRec45[2];
	int 	iTempPerm16;
	float 	fTempPerm17;
	FAUSTFLOAT 	fslider90;
	float 	fRec44[2];
	FAUSTFLOAT 	fslider91;
	FAUSTFLOAT 	fslider92;
	float 	fTempPerm18;
	FAUSTFLOAT 	fslider93;
	FAUSTFLOAT 	fslider94;
	FAUSTFLOAT 	fslider95;
	float 	fRec46[2];
	FAUSTFLOAT 	fbutton12;
	FAUSTFLOAT 	fslider96;
	FAUSTFLOAT 	fslider97;
	FAUSTFLOAT 	fslider98;
	float 	fRec48[2];
	int 	iTempPerm19;
	float 	fRec47[2];
	float 	fRec49[2];
	FAUSTFLOAT 	fslider99;
	FAUSTFLOAT 	fslider100;
	FAUSTFLOAT 	fslider101;
	FAUSTFLOAT 	fslider102;
	float 	fRec50[2];
	FAUSTFLOAT 	fbutton13;
	FAUSTFLOAT 	fslider103;
	FAUSTFLOAT 	fslider104;
	FAUSTFLOAT 	fslider105;
	float 	fRec52[2];
	int 	iTempPerm20;
	float 	fRec51[2];
	float 	fRec53[2];
	FAUSTFLOAT 	fslider106;
	FAUSTFLOAT 	fslider107;
	FAUSTFLOAT 	fslider108;
	FAUSTFLOAT 	fslider109;
	float 	fRec54[2];
	FAUSTFLOAT 	fbutton14;
	FAUSTFLOAT 	fslider110;
	FAUSTFLOAT 	fslider111;
	FAUSTFLOAT 	fslider112;
	float 	fRec56[2];
	int 	iTempPerm21;
	float 	fRec55[2];
	float 	fRec57[2];
	FAUSTFLOAT 	fslider113;
	FAUSTFLOAT 	fslider114;
	FAUSTFLOAT 	fslider115;
	FAUSTFLOAT 	fslider116;
	float 	fRec58[2];
	FAUSTFLOAT 	fslider117;
	FAUSTFLOAT 	fslider118;
	FAUSTFLOAT 	fbutton15;
	int 	iRec60[2];
	int 	iTempPerm22;
	float 	fTempPerm23;
	FAUSTFLOAT 	fslider119;
	float 	fRec59[2];
	FAUSTFLOAT 	fslider120;
	FAUSTFLOAT 	fslider121;
	float 	fTempPerm24;
	FAUSTFLOAT 	fslider122;
	FAUSTFLOAT 	fslider123;
	FAUSTFLOAT 	fslider124;
	float 	fRec61[2];
	FAUSTFLOAT 	fbutton16;
	FAUSTFLOAT 	fslider125;
	FAUSTFLOAT 	fslider126;
	FAUSTFLOAT 	fslider127;
	float 	fRec63[2];
	int 	iTempPerm25;
	float 	fRec62[2];
	float 	fRec64[2];
	FAUSTFLOAT 	fslider128;
	FAUSTFLOAT 	fslider129;
	FAUSTFLOAT 	fslider130;
	FAUSTFLOAT 	fslider131;
	float 	fRec65[2];
	FAUSTFLOAT 	fbutton17;
	FAUSTFLOAT 	fslider132;
	FAUSTFLOAT 	fslider133;
	FAUSTFLOAT 	fslider134;
	float 	fRec67[2];
	int 	iTempPerm26;
	float 	fRec66[2];
	float 	fRec68[2];
	FAUSTFLOAT 	fslider135;
	FAUSTFLOAT 	fslider136;
	FAUSTFLOAT 	fslider137;
	FAUSTFLOAT 	fslider138;
	float 	fRec69[2];
	FAUSTFLOAT 	fbutton18;
	FAUSTFLOAT 	fslider139;
	FAUSTFLOAT 	fslider140;
	FAUSTFLOAT 	fslider141;
	float 	fRec71[2];
	int 	iTempPerm27;
	float 	fRec70[2];
	float 	fRec72[2];
	FAUSTFLOAT 	fslider142;
	FAUSTFLOAT 	fslider143;
	FAUSTFLOAT 	fslider144;
	FAUSTFLOAT 	fslider145;
	float 	fRec73[2];
	FAUSTFLOAT 	fslider146;
	FAUSTFLOAT 	fslider147;
	FAUSTFLOAT 	fbutton19;
	int 	iRec75[2];
	int 	iTempPerm28;
	float 	fTempPerm29;
	FAUSTFLOAT 	fslider148;
	float 	fRec74[2];
	FAUSTFLOAT 	fslider149;
	FAUSTFLOAT 	fslider150;
	float 	fTempPerm30;
	FAUSTFLOAT 	fslider151;
	FAUSTFLOAT 	fslider152;
	FAUSTFLOAT 	fslider153;
	float 	fRec76[2];
	float 	fTempPerm31;
	FAUSTFLOAT 	fslider154;
	FAUSTFLOAT 	fslider155;
	FAUSTFLOAT 	fbutton20;
	int 	iRec78[2];
	int 	iTempPerm32;
	float 	fTempPerm33;
	FAUSTFLOAT 	fslider156;
	float 	fRec77[2];
	FAUSTFLOAT 	fslider157;
	FAUSTFLOAT 	fslider158;
	FAUSTFLOAT 	fslider159;
	FAUSTFLOAT 	fslider160;
	FAUSTFLOAT 	fslider161;
	float 	fRec79[2];
	float 	fTempPerm34;
	FAUSTFLOAT 	fslider162;
	FAUSTFLOAT 	fslider163;
	FAUSTFLOAT 	fbutton21;
	int 	iRec81[2];
	int 	iTempPerm35;
	float 	fTempPerm36;
	FAUSTFLOAT 	fslider164;
	float 	fRec80[2];
	float 	fTempPerm37;
	FAUSTFLOAT 	fslider165;
	FAUSTFLOAT 	fslider166;
	FAUSTFLOAT 	fslider167;
	FAUSTFLOAT 	fslider168;
	FAUSTFLOAT 	fslider169;
	float 	fRec82[2];
	float 	fTempPerm38;
	FAUSTFLOAT 	fslider170;
	FAUSTFLOAT 	fslider171;
	FAUSTFLOAT 	fbutton22;
	int 	iRec84[2];
	int 	iTempPerm39;
	float 	fTempPerm40;
	FAUSTFLOAT 	fslider172;
	float 	fRec83[2];
	float 	fTempPerm41;
	FAUSTFLOAT 	fslider173;
	FAUSTFLOAT 	fslider174;
	float 	fTempPerm42;
	FAUSTFLOAT 	fslider175;
	FAUSTFLOAT 	fslider176;
	FAUSTFLOAT 	fslider177;
	float 	fRec85[2];
	FAUSTFLOAT 	fslider178;
	FAUSTFLOAT 	fslider179;
	FAUSTFLOAT 	fbutton23;
	int 	iRec87[2];
	int 	iTempPerm43;
	float 	fTempPerm44;
	FAUSTFLOAT 	fslider180;
	float 	fRec86[2];
	float 	fTempPerm45;
	FAUSTFLOAT 	fslider181;
	FAUSTFLOAT 	fslider182;
	float 	fTempPerm46;
	float 	fTempPerm47;
	FAUSTFLOAT 	fslider183;
	FAUSTFLOAT 	fslider184;
	FAUSTFLOAT 	fslider185;
	float 	fRec89[2];
	int 	iTempPerm48;
	float 	fRec88[2];
	float 	fRec90[2];
	float 	fTempPerm49;
	FAUSTFLOAT 	fslider186;
	float 	fTempPerm50;
	float 	fTempPerm51;
	float 	fTempPerm52;
	float 	fTempPerm53;
	float 	fTempPerm54;
	float 	fTempPerm55;
	FAUSTFLOAT 	fslider187;
	FAUSTFLOAT 	fslider188;
	FAUSTFLOAT 	fslider189;
	float 	fRec92[2];
	int 	iTempPerm56;
	float 	fRec91[2];
	float 	fRec93[2];
	float 	fTempPerm57;
	float 	fTempPerm58;
	FAUSTFLOAT 	fslider190;
	float 	fTempPerm59;
	FAUSTFLOAT 	fslider191;
	FAUSTFLOAT 	fslider192;
	FAUSTFLOAT 	fslider193;
	float 	fRec95[2];
	int 	iTempPerm60;
	float 	fRec94[2];
	float 	fRec96[2];
	float 	fTempPerm61;
	float 	fTempPerm62;
	FAUSTFLOAT 	fslider194;
	float 	fTempPerm63;
	float 	fTempPerm64;
	float 	fTempPerm65;
	float 	fTempPerm66;
	float 	fTempPerm67;
	float 	fTempPerm68;
	float 	fTempPerm69;
	float 	fTempPerm70;
	float 	fTempPerm71;
	float 	fTempPerm72;
	float 	fTempPerm73;
	FAUSTFLOAT 	fslider195;
	FAUSTFLOAT 	fslider196;
	FAUSTFLOAT 	fslider197;
	float 	fRec97[2];
	FAUSTFLOAT 	fbutton24;
	FAUSTFLOAT 	fslider198;
	FAUSTFLOAT 	fslider199;
	FAUSTFLOAT 	fslider200;
	float 	fRec99[2];
	int 	iTempPerm74;
	float 	fRec98[2];
	float 	fRec100[2];
	FAUSTFLOAT 	fslider201;
	FAUSTFLOAT 	fslider202;
	FAUSTFLOAT 	fslider203;
	FAUSTFLOAT 	fslider204;
	float 	fRec101[2];
	FAUSTFLOAT 	fbutton25;
	FAUSTFLOAT 	fslider205;
	FAUSTFLOAT 	fslider206;
	FAUSTFLOAT 	fslider207;
	float 	fRec103[2];
	int 	iTempPerm75;
	float 	fRec102[2];
	float 	fRec104[2];
	FAUSTFLOAT 	fslider208;
	FAUSTFLOAT 	fslider209;
	FAUSTFLOAT 	fslider210;
	FAUSTFLOAT 	fslider211;
	float 	fRec105[2];
	FAUSTFLOAT 	fbutton26;
	FAUSTFLOAT 	fslider212;
	FAUSTFLOAT 	fslider213;
	FAUSTFLOAT 	fslider214;
	float 	fRec107[2];
	int 	iTempPerm76;
	float 	fRec106[2];
	float 	fRec108[2];
	FAUSTFLOAT 	fslider215;
	FAUSTFLOAT 	fslider216;
	FAUSTFLOAT 	fslider217;
	FAUSTFLOAT 	fslider218;
	float 	fRec109[2];
	FAUSTFLOAT 	fslider219;
	FAUSTFLOAT 	fslider220;
	FAUSTFLOAT 	fbutton27;
	int 	iRec111[2];
	int 	iTempPerm77;
	float 	fTempPerm78;
	FAUSTFLOAT 	fslider221;
	float 	fRec110[2];
	FAUSTFLOAT 	fslider222;
	FAUSTFLOAT 	fslider223;
	float 	fTempPerm79;
	FAUSTFLOAT 	fslider224;
	FAUSTFLOAT 	fslider225;
	FAUSTFLOAT 	fslider226;
	float 	fRec112[2];
	float 	fTempPerm80;
	FAUSTFLOAT 	fslider227;
	FAUSTFLOAT 	fbutton28;
	FAUSTFLOAT 	fslider228;
	FAUSTFLOAT 	fslider229;
	float 	fRec114[2];
	int 	iTempPerm81;
	float 	fRec113[2];
	float 	fRec115[2];
	float 	fTempPerm82;
	FAUSTFLOAT 	fslider230;
	float 	fTempPerm83;
	FAUSTFLOAT 	fslider231;
	FAUSTFLOAT 	fslider232;
	FAUSTFLOAT 	fslider233;
	float 	fRec116[2];
	float 	fTempPerm84;
	FAUSTFLOAT 	fslider234;
	FAUSTFLOAT 	fbutton29;
	FAUSTFLOAT 	fslider235;
	FAUSTFLOAT 	fslider236;
	float 	fRec118[2];
	int 	iTempPerm85;
	float 	fRec117[2];
	float 	fRec119[2];
	float 	fTempPerm86;
	float 	fTempPerm87;
	FAUSTFLOAT 	fslider237;
	float 	fTempPerm88;
	FAUSTFLOAT 	fslider238;
	FAUSTFLOAT 	fslider239;
	FAUSTFLOAT 	fslider240;
	float 	fRec120[2];
	float 	fTempPerm89;
	FAUSTFLOAT 	fslider241;
	FAUSTFLOAT 	fbutton30;
	FAUSTFLOAT 	fslider242;
	FAUSTFLOAT 	fslider243;
	float 	fRec122[2];
	int 	iTempPerm90;
	float 	fRec121[2];
	float 	fRec123[2];
	float 	fTempPerm91;
	FAUSTFLOAT 	fslider244;
	FAUSTFLOAT 	fslider245;
	FAUSTFLOAT 	fslider246;
	FAUSTFLOAT 	fslider247;
	float 	fRec124[2];
	FAUSTFLOAT 	fslider248;
	FAUSTFLOAT 	fslider249;
	FAUSTFLOAT 	fbutton31;
	int 	iRec126[2];
	int 	iTempPerm92;
	float 	fTempPerm93;
	FAUSTFLOAT 	fslider250;
	float 	fRec125[2];
	float 	fTempPerm94;
	FAUSTFLOAT 	fslider251;
	FAUSTFLOAT 	fslider252;
	float 	fTempPerm95;
	float 	fTempPerm96;
	float 	fTempPerm97;
	float 	fTempPerm98;
	float 	fTempPerm99;
	float 	fTempPerm100;
	float 	fTempPerm101;
	FAUSTFLOAT 	fslider253;
	FAUSTFLOAT 	fslider254;
	int 	iRec128[2];
	int 	iTempPerm102;
	float 	fTempPerm103;
	FAUSTFLOAT 	fslider255;
	float 	fRec127[2];
	float 	fTempPerm104;
	FAUSTFLOAT 	fslider256;
	FAUSTFLOAT 	fslider257;
	float 	fTempPerm105;
	float 	fTempPerm106;
	float 	fTempPerm107;
	float 	fTempPerm108;
	float 	fTempPerm109;
	float 	fTempPerm110;
	float 	fTempPerm111;
	FAUSTFLOAT 	fslider258;
	FAUSTFLOAT 	fslider259;
	int 	iRec130[2];
	int 	iTempPerm112;
	float 	fTempPerm113;
	FAUSTFLOAT 	fslider260;
	float 	fRec129[2];
	float 	fTempPerm114;
	FAUSTFLOAT 	fslider261;
	FAUSTFLOAT 	fslider262;
	float 	fTempPerm115;
	float 	fTempPerm116;
	float 	fTempPerm117;
	float 	fTempPerm118;
	float 	fTempPerm119;
	FAUSTFLOAT 	fslider263;
	FAUSTFLOAT 	fslider264;
	int 	iRec132[2];
	int 	iTempPerm120;
	float 	fTempPerm121;
	FAUSTFLOAT 	fslider265;
	float 	fRec131[2];
	FAUSTFLOAT 	fslider266;
	FAUSTFLOAT 	fslider267;
	float 	fTempPerm122;
	FAUSTFLOAT 	fslider268;
	FAUSTFLOAT 	fslider269;
	FAUSTFLOAT 	fslider270;
	float 	fRec133[2];
	float 	fTempPerm123;
	FAUSTFLOAT 	fslider271;
	FAUSTFLOAT 	fbutton32;
	FAUSTFLOAT 	fslider272;
	FAUSTFLOAT 	fslider273;
	float 	fRec135[2];
	int 	iTempPerm124;
	float 	fRec134[2];
	float 	fRec136[2];
	float 	fTempPerm125;
	FAUSTFLOAT 	fslider274;
	float 	fTempPerm126;
	FAUSTFLOAT 	fslider275;
	FAUSTFLOAT 	fslider276;
	FAUSTFLOAT 	fslider277;
	float 	fRec137[2];
	float 	fTempPerm127;
	FAUSTFLOAT 	fslider278;
	FAUSTFLOAT 	fbutton33;
	FAUSTFLOAT 	fslider279;
	FAUSTFLOAT 	fslider280;
	float 	fRec139[2];
	int 	iTempPerm128;
	float 	fRec138[2];
	float 	fRec140[2];
	float 	fTempPerm129;
	float 	fTempPerm130;
	FAUSTFLOAT 	fslider281;
	float 	fTempPerm131;
	FAUSTFLOAT 	fslider282;
	FAUSTFLOAT 	fslider283;
	FAUSTFLOAT 	fslider284;
	float 	fRec141[2];
	float 	fTempPerm132;
	FAUSTFLOAT 	fslider285;
	FAUSTFLOAT 	fbutton34;
	FAUSTFLOAT 	fslider286;
	FAUSTFLOAT 	fslider287;
	float 	fRec143[2];
	int 	iTempPerm133;
	float 	fRec142[2];
	float 	fRec144[2];
	float 	fTempPerm134;
	FAUSTFLOAT 	fslider288;
	FAUSTFLOAT 	fslider289;
	FAUSTFLOAT 	fslider290;
	FAUSTFLOAT 	fslider291;
	float 	fRec145[2];
	FAUSTFLOAT 	fslider292;
	FAUSTFLOAT 	fslider293;
	FAUSTFLOAT 	fbutton35;
	int 	iRec147[2];
	int 	iTempPerm135;
	float 	fTempPerm136;
	FAUSTFLOAT 	fslider294;
	float 	fRec146[2];
	float 	fTempPerm137;
	FAUSTFLOAT 	fslider295;
	FAUSTFLOAT 	fslider296;
	float 	fTempPerm138;
	float 	fTempPerm139;
	float 	fTempPerm140;
	float 	fTempPerm141;
	float 	fTempPerm142;
	float 	fTempPerm143;
	float 	fTempPerm144;
	FAUSTFLOAT 	fslider297;
	FAUSTFLOAT 	fslider298;
	int 	iRec149[2];
	int 	iTempPerm145;
	float 	fTempPerm146;
	FAUSTFLOAT 	fslider299;
	float 	fRec148[2];
	float 	fTempPerm147;
	FAUSTFLOAT 	fslider300;
	FAUSTFLOAT 	fslider301;
	float 	fTempPerm148;
	float 	fTempPerm149;
	float 	fTempPerm150;
	float 	fTempPerm151;
	float 	fTempPerm152;
	float 	fTempPerm153;
	float 	fTempPerm154;
	FAUSTFLOAT 	fslider302;
	FAUSTFLOAT 	fslider303;
	int 	iRec151[2];
	int 	iTempPerm155;
	float 	fTempPerm156;
	FAUSTFLOAT 	fslider304;
	float 	fRec150[2];
	float 	fTempPerm157;
	FAUSTFLOAT 	fslider305;
	FAUSTFLOAT 	fslider306;
	float 	fTempPerm158;
	float 	fTempPerm159;
	float 	fTempPerm160;
	float 	fTempPerm161;
	float 	fTempPerm162;
	FAUSTFLOAT 	fslider307;
	FAUSTFLOAT 	fslider308;
	int 	iRec153[2];
	int 	iTempPerm163;
	float 	fTempPerm164;
	FAUSTFLOAT 	fslider309;
	float 	fRec152[2];
	FAUSTFLOAT 	fslider310;
	FAUSTFLOAT 	fslider311;
	float 	fTempPerm165;
	FAUSTFLOAT 	fslider312;
	FAUSTFLOAT 	fslider313;
	FAUSTFLOAT 	fslider314;
	float 	fRec154[2];
	float 	fTempPerm166;
	FAUSTFLOAT 	fslider315;
	FAUSTFLOAT 	fbutton36;
	FAUSTFLOAT 	fslider316;
	FAUSTFLOAT 	fslider317;
	float 	fRec156[2];
	int 	iTempPerm167;
	float 	fRec155[2];
	float 	fRec157[2];
	float 	fTempPerm168;
	FAUSTFLOAT 	fslider318;
	float 	fTempPerm169;
	FAUSTFLOAT 	fslider319;
	FAUSTFLOAT 	fslider320;
	FAUSTFLOAT 	fslider321;
	float 	fRec158[2];
	float 	fTempPerm170;
	FAUSTFLOAT 	fslider322;
	FAUSTFLOAT 	fbutton37;
	FAUSTFLOAT 	fslider323;
	FAUSTFLOAT 	fslider324;
	float 	fRec160[2];
	int 	iTempPerm171;
	float 	fRec159[2];
	float 	fRec161[2];
	float 	fTempPerm172;
	float 	fTempPerm173;
	FAUSTFLOAT 	fslider325;
	float 	fTempPerm174;
	FAUSTFLOAT 	fslider326;
	FAUSTFLOAT 	fslider327;
	FAUSTFLOAT 	fslider328;
	float 	fRec162[2];
	float 	fTempPerm175;
	FAUSTFLOAT 	fslider329;
	FAUSTFLOAT 	fbutton38;
	FAUSTFLOAT 	fslider330;
	FAUSTFLOAT 	fslider331;
	float 	fRec164[2];
	int 	iTempPerm176;
	float 	fRec163[2];
	float 	fRec165[2];
	float 	fTempPerm177;
	FAUSTFLOAT 	fslider332;
	FAUSTFLOAT 	fslider333;
	FAUSTFLOAT 	fslider334;
	FAUSTFLOAT 	fslider335;
	float 	fRec166[2];
	FAUSTFLOAT 	fslider336;
	FAUSTFLOAT 	fslider337;
	FAUSTFLOAT 	fbutton39;
	int 	iRec168[2];
	int 	iTempPerm178;
	float 	fTempPerm179;
	FAUSTFLOAT 	fslider338;
	float 	fRec167[2];
	float 	fTempPerm180;
	FAUSTFLOAT 	fslider339;
	FAUSTFLOAT 	fslider340;
	float 	fTempPerm181;
	float 	fTempPerm182;
	float 	fTempPerm183;
	float 	fTempPerm184;
	float 	fTempPerm185;
	float 	fTempPerm186;
	float 	fTempPerm187;
	FAUSTFLOAT 	fslider341;
	FAUSTFLOAT 	fslider342;
	int 	iRec170[2];
	int 	iTempPerm188;
	float 	fTempPerm189;
	FAUSTFLOAT 	fslider343;
	float 	fRec169[2];
	float 	fTempPerm190;
	FAUSTFLOAT 	fslider344;
	FAUSTFLOAT 	fslider345;
	float 	fTempPerm191;
	float 	fTempPerm192;
	float 	fTempPerm193;
	float 	fTempPerm194;
	float 	fTempPerm195;
	float 	fTempPerm196;
	float 	fTempPerm197;
	FAUSTFLOAT 	fslider346;
	FAUSTFLOAT 	fslider347;
	int 	iRec172[2];
	int 	iTempPerm198;
	float 	fTempPerm199;
	FAUSTFLOAT 	fslider348;
	float 	fRec171[2];
	float 	fTempPerm200;
	FAUSTFLOAT 	fslider349;
	FAUSTFLOAT 	fslider350;
	float 	fTempPerm201;
	float 	fTempPerm202;
	float 	fTempPerm203;
	float 	fTempPerm204;
	float 	fTempPerm205;
	FAUSTFLOAT 	fslider351;
	FAUSTFLOAT 	fslider352;
	int 	iRec174[2];
	int 	iTempPerm206;
	float 	fTempPerm207;
	FAUSTFLOAT 	fslider353;
	float 	fRec173[2];
	FAUSTFLOAT 	fslider354;
	FAUSTFLOAT 	fslider355;
	float 	fTempPerm208;
	FAUSTFLOAT 	fslider356;
	FAUSTFLOAT 	fslider357;
	FAUSTFLOAT 	fslider358;
	float 	fRec175[2];
	float 	fTempPerm209;
	FAUSTFLOAT 	fslider359;
	FAUSTFLOAT 	fbutton40;
	FAUSTFLOAT 	fslider360;
	FAUSTFLOAT 	fslider361;
	float 	fRec177[2];
	int 	iTempPerm210;
	float 	fRec176[2];
	float 	fRec178[2];
	float 	fTempPerm211;
	FAUSTFLOAT 	fslider362;
	float 	fTempPerm212;
	FAUSTFLOAT 	fslider363;
	FAUSTFLOAT 	fslider364;
	FAUSTFLOAT 	fslider365;
	float 	fRec179[2];
	float 	fTempPerm213;
	FAUSTFLOAT 	fslider366;
	FAUSTFLOAT 	fbutton41;
	FAUSTFLOAT 	fslider367;
	FAUSTFLOAT 	fslider368;
	float 	fRec181[2];
	int 	iTempPerm214;
	float 	fRec180[2];
	float 	fRec182[2];
	float 	fTempPerm215;
	float 	fTempPerm216;
	FAUSTFLOAT 	fslider369;
	float 	fTempPerm217;
	FAUSTFLOAT 	fslider370;
	FAUSTFLOAT 	fslider371;
	FAUSTFLOAT 	fslider372;
	float 	fRec183[2];
	float 	fTempPerm218;
	FAUSTFLOAT 	fslider373;
	FAUSTFLOAT 	fbutton42;
	FAUSTFLOAT 	fslider374;
	FAUSTFLOAT 	fslider375;
	float 	fRec185[2];
	int 	iTempPerm219;
	float 	fRec184[2];
	float 	fRec186[2];
	float 	fTempPerm220;
	FAUSTFLOAT 	fslider376;
	FAUSTFLOAT 	fslider377;
	FAUSTFLOAT 	fslider378;
	FAUSTFLOAT 	fslider379;
	float 	fRec187[2];
	FAUSTFLOAT 	fslider380;
	FAUSTFLOAT 	fslider381;
	FAUSTFLOAT 	fbutton43;
	int 	iRec189[2];
	int 	iTempPerm221;
	float 	fTempPerm222;
	FAUSTFLOAT 	fslider382;
	float 	fRec188[2];
	float 	fTempPerm223;
	FAUSTFLOAT 	fslider383;
	FAUSTFLOAT 	fslider384;
	float 	fTempPerm224;
	float 	fTempPerm225;
	float 	fTempPerm226;
	float 	fTempPerm227;
	float 	fTempPerm228;
	float 	fTempPerm229;
	float 	fTempPerm230;
	FAUSTFLOAT 	fslider385;
	FAUSTFLOAT 	fslider386;
	int 	iRec191[2];
	int 	iTempPerm231;
	float 	fTempPerm232;
	FAUSTFLOAT 	fslider387;
	float 	fRec190[2];
	float 	fTempPerm233;
	FAUSTFLOAT 	fslider388;
	FAUSTFLOAT 	fslider389;
	float 	fTempPerm234;
	float 	fTempPerm235;
	float 	fTempPerm236;
	float 	fTempPerm237;
	float 	fTempPerm238;
	float 	fTempPerm239;
	float 	fTempPerm240;
	FAUSTFLOAT 	fslider390;
	FAUSTFLOAT 	fslider391;
	int 	iRec193[2];
	int 	iTempPerm241;
	float 	fTempPerm242;
	FAUSTFLOAT 	fslider392;
	float 	fRec192[2];
	float 	fTempPerm243;
	FAUSTFLOAT 	fslider393;
	FAUSTFLOAT 	fslider394;
	float 	fTempPerm244;
	float 	fTempPerm245;
	float 	fTempPerm246;
	float 	fTempPerm247;
	float 	fTempPerm248;
	FAUSTFLOAT 	fslider395;
	FAUSTFLOAT 	fslider396;
	int 	iRec195[2];
	int 	iTempPerm249;
	float 	fTempPerm250;
	FAUSTFLOAT 	fslider397;
	float 	fRec194[2];
	FAUSTFLOAT 	fslider398;
	FAUSTFLOAT 	fslider399;
	float 	fTempPerm251;
	FAUSTFLOAT 	fslider400;
	FAUSTFLOAT 	fslider401;
	FAUSTFLOAT 	fslider402;
	float 	fRec196[2];
	float 	fTempPerm252;
	FAUSTFLOAT 	fslider403;
	FAUSTFLOAT 	fbutton44;
	FAUSTFLOAT 	fslider404;
	FAUSTFLOAT 	fslider405;
	float 	fRec198[2];
	int 	iTempPerm253;
	float 	fRec197[2];
	float 	fRec199[2];
	float 	fTempPerm254;
	FAUSTFLOAT 	fslider406;
	float 	fTempPerm255;
	FAUSTFLOAT 	fslider407;
	FAUSTFLOAT 	fslider408;
	FAUSTFLOAT 	fslider409;
	float 	fRec200[2];
	float 	fTempPerm256;
	FAUSTFLOAT 	fslider410;
	FAUSTFLOAT 	fbutton45;
	FAUSTFLOAT 	fslider411;
	FAUSTFLOAT 	fslider412;
	float 	fRec202[2];
	int 	iTempPerm257;
	float 	fRec201[2];
	float 	fRec203[2];
	float 	fTempPerm258;
	float 	fTempPerm259;
	FAUSTFLOAT 	fslider413;
	float 	fTempPerm260;
	FAUSTFLOAT 	fslider414;
	FAUSTFLOAT 	fslider415;
	FAUSTFLOAT 	fslider416;
	float 	fRec204[2];
	float 	fTempPerm261;
	FAUSTFLOAT 	fslider417;
	FAUSTFLOAT 	fbutton46;
	FAUSTFLOAT 	fslider418;
	FAUSTFLOAT 	fslider419;
	float 	fRec206[2];
	int 	iTempPerm262;
	float 	fRec205[2];
	float 	fRec207[2];
	float 	fTempPerm263;
	FAUSTFLOAT 	fslider420;
	FAUSTFLOAT 	fslider421;
	FAUSTFLOAT 	fslider422;
	FAUSTFLOAT 	fslider423;
	float 	fRec208[2];
	FAUSTFLOAT 	fslider424;
	FAUSTFLOAT 	fslider425;
	FAUSTFLOAT 	fbutton47;
	int 	iRec210[2];
	int 	iTempPerm264;
	float 	fTempPerm265;
	FAUSTFLOAT 	fslider426;
	float 	fRec209[2];
	float 	fTempPerm266;
	FAUSTFLOAT 	fslider427;
	FAUSTFLOAT 	fslider428;
	float 	fTempPerm267;
	float 	fTempPerm268;
	float 	fTempPerm269;
	float 	fTempPerm270;
	float 	fTempPerm271;
	float 	fTempPerm272;
	float 	fTempPerm273;
	FAUSTFLOAT 	fslider429;
	FAUSTFLOAT 	fslider430;
	int 	iRec212[2];
	int 	iTempPerm274;
	float 	fTempPerm275;
	FAUSTFLOAT 	fslider431;
	float 	fRec211[2];
	float 	fTempPerm276;
	FAUSTFLOAT 	fslider432;
	FAUSTFLOAT 	fslider433;
	float 	fTempPerm277;
	float 	fTempPerm278;
	float 	fTempPerm279;
	float 	fTempPerm280;
	float 	fTempPerm281;
	float 	fTempPerm282;
	float 	fTempPerm283;
	FAUSTFLOAT 	fslider434;
	FAUSTFLOAT 	fslider435;
	int 	iRec214[2];
	int 	iTempPerm284;
	float 	fTempPerm285;
	FAUSTFLOAT 	fslider436;
	float 	fRec213[2];
	float 	fTempPerm286;
	FAUSTFLOAT 	fslider437;
	FAUSTFLOAT 	fslider438;
	float 	fTempPerm287;
	float 	fTempPerm288;
	float 	fTempPerm289;
	float 	fTempPerm290;
	float 	fTempPerm291;
	FAUSTFLOAT 	fslider439;
	FAUSTFLOAT 	fslider440;
	int 	iRec216[2];
	int 	iTempPerm292;
	float 	fTempPerm293;
	FAUSTFLOAT 	fslider441;
	float 	fRec215[2];
	FAUSTFLOAT 	fslider442;
	FAUSTFLOAT 	fslider443;
	float 	fTempPerm294;
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
		fConst2 = (3.0f * fConst0);
		fConst3 = (0.33333333333333331f / fConst0);
		iTempPerm1 = 0;
		iTempPerm2 = 0;
		iTempPerm3 = 0;
		iTempPerm4 = 0;
		fConst4 = (6.9100000000000001f / fConst0);
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		iTempPerm7 = 0;
		iTempPerm8 = 0;
		iTempPerm9 = 0;
		iTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		iTempPerm13 = 0;
		iTempPerm14 = 0;
		iTempPerm15 = 0;
		iTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		iTempPerm19 = 0;
		iTempPerm20 = 0;
		iTempPerm21 = 0;
		iTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		iTempPerm25 = 0;
		iTempPerm26 = 0;
		iTempPerm27 = 0;
		iTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		iTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		iTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		iTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		iTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		iTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		iTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fTempPerm59 = 0;
		iTempPerm60 = 0;
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
		iTempPerm74 = 0;
		iTempPerm75 = 0;
		iTempPerm76 = 0;
		iTempPerm77 = 0;
		fTempPerm78 = 0;
		fTempPerm79 = 0;
		fTempPerm80 = 0;
		iTempPerm81 = 0;
		fTempPerm82 = 0;
		fTempPerm83 = 0;
		fTempPerm84 = 0;
		iTempPerm85 = 0;
		fTempPerm86 = 0;
		fTempPerm87 = 0;
		fTempPerm88 = 0;
		fTempPerm89 = 0;
		iTempPerm90 = 0;
		fTempPerm91 = 0;
		iTempPerm92 = 0;
		fTempPerm93 = 0;
		fTempPerm94 = 0;
		fTempPerm95 = 0;
		fTempPerm96 = 0;
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
		fTempPerm107 = 0;
		fTempPerm108 = 0;
		fTempPerm109 = 0;
		fTempPerm110 = 0;
		fTempPerm111 = 0;
		iTempPerm112 = 0;
		fTempPerm113 = 0;
		fTempPerm114 = 0;
		fTempPerm115 = 0;
		fTempPerm116 = 0;
		fTempPerm117 = 0;
		fTempPerm118 = 0;
		fTempPerm119 = 0;
		iTempPerm120 = 0;
		fTempPerm121 = 0;
		fTempPerm122 = 0;
		fTempPerm123 = 0;
		iTempPerm124 = 0;
		fTempPerm125 = 0;
		fTempPerm126 = 0;
		fTempPerm127 = 0;
		iTempPerm128 = 0;
		fTempPerm129 = 0;
		fTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		iTempPerm133 = 0;
		fTempPerm134 = 0;
		iTempPerm135 = 0;
		fTempPerm136 = 0;
		fTempPerm137 = 0;
		fTempPerm138 = 0;
		fTempPerm139 = 0;
		fTempPerm140 = 0;
		fTempPerm141 = 0;
		fTempPerm142 = 0;
		fTempPerm143 = 0;
		fTempPerm144 = 0;
		iTempPerm145 = 0;
		fTempPerm146 = 0;
		fTempPerm147 = 0;
		fTempPerm148 = 0;
		fTempPerm149 = 0;
		fTempPerm150 = 0;
		fTempPerm151 = 0;
		fTempPerm152 = 0;
		fTempPerm153 = 0;
		fTempPerm154 = 0;
		iTempPerm155 = 0;
		fTempPerm156 = 0;
		fTempPerm157 = 0;
		fTempPerm158 = 0;
		fTempPerm159 = 0;
		fTempPerm160 = 0;
		fTempPerm161 = 0;
		fTempPerm162 = 0;
		iTempPerm163 = 0;
		fTempPerm164 = 0;
		fTempPerm165 = 0;
		fTempPerm166 = 0;
		iTempPerm167 = 0;
		fTempPerm168 = 0;
		fTempPerm169 = 0;
		fTempPerm170 = 0;
		iTempPerm171 = 0;
		fTempPerm172 = 0;
		fTempPerm173 = 0;
		fTempPerm174 = 0;
		fTempPerm175 = 0;
		iTempPerm176 = 0;
		fTempPerm177 = 0;
		iTempPerm178 = 0;
		fTempPerm179 = 0;
		fTempPerm180 = 0;
		fTempPerm181 = 0;
		fTempPerm182 = 0;
		fTempPerm183 = 0;
		fTempPerm184 = 0;
		fTempPerm185 = 0;
		fTempPerm186 = 0;
		fTempPerm187 = 0;
		iTempPerm188 = 0;
		fTempPerm189 = 0;
		fTempPerm190 = 0;
		fTempPerm191 = 0;
		fTempPerm192 = 0;
		fTempPerm193 = 0;
		fTempPerm194 = 0;
		fTempPerm195 = 0;
		fTempPerm196 = 0;
		fTempPerm197 = 0;
		iTempPerm198 = 0;
		fTempPerm199 = 0;
		fTempPerm200 = 0;
		fTempPerm201 = 0;
		fTempPerm202 = 0;
		fTempPerm203 = 0;
		fTempPerm204 = 0;
		fTempPerm205 = 0;
		iTempPerm206 = 0;
		fTempPerm207 = 0;
		fTempPerm208 = 0;
		fTempPerm209 = 0;
		iTempPerm210 = 0;
		fTempPerm211 = 0;
		fTempPerm212 = 0;
		fTempPerm213 = 0;
		iTempPerm214 = 0;
		fTempPerm215 = 0;
		fTempPerm216 = 0;
		fTempPerm217 = 0;
		fTempPerm218 = 0;
		iTempPerm219 = 0;
		fTempPerm220 = 0;
		iTempPerm221 = 0;
		fTempPerm222 = 0;
		fTempPerm223 = 0;
		fTempPerm224 = 0;
		fTempPerm225 = 0;
		fTempPerm226 = 0;
		fTempPerm227 = 0;
		fTempPerm228 = 0;
		fTempPerm229 = 0;
		fTempPerm230 = 0;
		iTempPerm231 = 0;
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
		fTempPerm248 = 0;
		iTempPerm249 = 0;
		fTempPerm250 = 0;
		fTempPerm251 = 0;
		fTempPerm252 = 0;
		iTempPerm253 = 0;
		fTempPerm254 = 0;
		fTempPerm255 = 0;
		fTempPerm256 = 0;
		iTempPerm257 = 0;
		fTempPerm258 = 0;
		fTempPerm259 = 0;
		fTempPerm260 = 0;
		fTempPerm261 = 0;
		iTempPerm262 = 0;
		fTempPerm263 = 0;
		iTempPerm264 = 0;
		fTempPerm265 = 0;
		fTempPerm266 = 0;
		fTempPerm267 = 0;
		fTempPerm268 = 0;
		fTempPerm269 = 0;
		fTempPerm270 = 0;
		fTempPerm271 = 0;
		fTempPerm272 = 0;
		fTempPerm273 = 0;
		iTempPerm274 = 0;
		fTempPerm275 = 0;
		fTempPerm276 = 0;
		fTempPerm277 = 0;
		fTempPerm278 = 0;
		fTempPerm279 = 0;
		fTempPerm280 = 0;
		fTempPerm281 = 0;
		fTempPerm282 = 0;
		fTempPerm283 = 0;
		iTempPerm284 = 0;
		fTempPerm285 = 0;
		fTempPerm286 = 0;
		fTempPerm287 = 0;
		fTempPerm288 = 0;
		fTempPerm289 = 0;
		fTempPerm290 = 0;
		fTempPerm291 = 0;
		iTempPerm292 = 0;
		fTempPerm293 = 0;
		fTempPerm294 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 1.0f;
		fslider3 = 440.0f;
		fbutton0 = 0.0;
		fslider4 = 0.0f;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		fslider7 = 1.0f;
		fslider8 = 1.0f;
		fslider9 = 0.0f;
		fslider10 = 1.0f;
		fslider11 = 440.0f;
		fbutton1 = 0.0;
		fslider12 = 0.0f;
		fslider13 = 0.0f;
		fslider14 = 0.0f;
		fslider15 = 1.0f;
		fslider16 = 0.0f;
		fslider17 = 1.0f;
		fslider18 = 440.0f;
		fbutton2 = 0.0;
		fslider19 = 0.0f;
		fslider20 = 0.0f;
		fslider21 = 0.0f;
		fslider22 = 1.0f;
		fslider23 = 0.0f;
		fslider24 = 1.0f;
		fslider25 = 440.0f;
		fslider26 = 0.0f;
		fslider27 = 0.0f;
		fslider28 = 0.0f;
		fslider29 = 0.0f;
		fslider30 = 0.001f;
		fbutton3 = 0.0;
		fslider31 = 1.0f;
		fslider32 = 0.0f;
		fslider33 = 0.0f;
		fslider34 = 1.0f;
		fslider35 = 0.0f;
		fslider36 = 1.0f;
		fslider37 = 440.0f;
		fbutton4 = 0.0;
		fslider38 = 0.0f;
		fslider39 = 0.0f;
		fslider40 = 0.0f;
		fslider41 = 1.0f;
		fslider42 = 1.0f;
		fslider43 = 440.0f;
		fslider44 = 0.0f;
		fbutton5 = 0.0;
		fslider45 = 0.0f;
		fslider46 = 0.0f;
		fslider47 = 0.0f;
		fslider48 = 1.0f;
		fslider49 = 0.0f;
		fslider50 = 1.0f;
		fslider51 = 440.0f;
		fbutton6 = 0.0;
		fslider52 = 0.0f;
		fslider53 = 0.0f;
		fslider54 = 0.0f;
		fslider55 = 1.0f;
		fslider56 = 0.0f;
		fslider57 = 1.0f;
		fslider58 = 440.0f;
		fslider59 = 0.0f;
		fslider60 = 0.0f;
		fbutton7 = 0.0;
		fslider61 = 0.0f;
		fslider62 = 0.0f;
		fslider63 = 1.0f;
		fslider64 = 0.0f;
		fslider65 = 1.0f;
		fslider66 = 440.0f;
		fbutton8 = 0.0;
		fslider67 = 0.0f;
		fslider68 = 0.0f;
		fslider69 = 0.0f;
		fslider70 = 1.0f;
		fslider71 = 0.0f;
		fslider72 = 1.0f;
		fslider73 = 440.0f;
		fbutton9 = 0.0;
		fslider74 = 0.0f;
		fslider75 = 0.0f;
		fslider76 = 0.0f;
		fslider77 = 1.0f;
		fslider78 = 0.0f;
		fslider79 = 1.0f;
		fslider80 = 440.0f;
		fbutton10 = 0.0;
		fslider81 = 0.0f;
		fslider82 = 0.0f;
		fslider83 = 0.0f;
		fslider84 = 1.0f;
		fslider85 = 0.0f;
		fslider86 = 1.0f;
		fslider87 = 440.0f;
		fslider88 = 0.0f;
		fslider89 = 0.0f;
		fbutton11 = 0.0;
		fslider90 = 0.0f;
		fslider91 = 0.0f;
		fslider92 = 1.0f;
		fslider93 = 0.0f;
		fslider94 = 1.0f;
		fslider95 = 440.0f;
		fbutton12 = 0.0;
		fslider96 = 0.0f;
		fslider97 = 0.0f;
		fslider98 = 0.0f;
		fslider99 = 1.0f;
		fslider100 = 0.0f;
		fslider101 = 1.0f;
		fslider102 = 440.0f;
		fbutton13 = 0.0;
		fslider103 = 0.0f;
		fslider104 = 0.0f;
		fslider105 = 0.0f;
		fslider106 = 1.0f;
		fslider107 = 0.0f;
		fslider108 = 1.0f;
		fslider109 = 440.0f;
		fbutton14 = 0.0;
		fslider110 = 0.0f;
		fslider111 = 0.0f;
		fslider112 = 0.0f;
		fslider113 = 1.0f;
		fslider114 = 0.0f;
		fslider115 = 1.0f;
		fslider116 = 440.0f;
		fslider117 = 0.0f;
		fslider118 = 0.0f;
		fbutton15 = 0.0;
		fslider119 = 0.0f;
		fslider120 = 0.0f;
		fslider121 = 1.0f;
		fslider122 = 0.0f;
		fslider123 = 1.0f;
		fslider124 = 440.0f;
		fbutton16 = 0.0;
		fslider125 = 0.0f;
		fslider126 = 0.0f;
		fslider127 = 0.0f;
		fslider128 = 1.0f;
		fslider129 = 0.0f;
		fslider130 = 1.0f;
		fslider131 = 440.0f;
		fbutton17 = 0.0;
		fslider132 = 0.0f;
		fslider133 = 0.0f;
		fslider134 = 0.0f;
		fslider135 = 1.0f;
		fslider136 = 0.0f;
		fslider137 = 1.0f;
		fslider138 = 440.0f;
		fbutton18 = 0.0;
		fslider139 = 0.0f;
		fslider140 = 0.0f;
		fslider141 = 0.0f;
		fslider142 = 1.0f;
		fslider143 = 0.0f;
		fslider144 = 1.0f;
		fslider145 = 440.0f;
		fslider146 = 0.0f;
		fslider147 = 0.0f;
		fbutton19 = 0.0;
		fslider148 = 0.0f;
		fslider149 = 0.0f;
		fslider150 = 1.0f;
		fslider151 = 0.0f;
		fslider152 = 1.0f;
		fslider153 = 440.0f;
		fslider154 = 0.0f;
		fslider155 = 0.0f;
		fbutton20 = 0.0;
		fslider156 = 0.0f;
		fslider157 = 0.0f;
		fslider158 = 1.0f;
		fslider159 = 0.0f;
		fslider160 = 1.0f;
		fslider161 = 440.0f;
		fslider162 = 0.0f;
		fslider163 = 0.0f;
		fbutton21 = 0.0;
		fslider164 = 0.0f;
		fslider165 = 0.0f;
		fslider166 = 1.0f;
		fslider167 = 0.0f;
		fslider168 = 1.0f;
		fslider169 = 440.0f;
		fslider170 = 0.0f;
		fslider171 = 0.0f;
		fbutton22 = 0.0;
		fslider172 = 0.0f;
		fslider173 = 0.0f;
		fslider174 = 1.0f;
		fslider175 = 0.0f;
		fslider176 = 1.0f;
		fslider177 = 440.0f;
		fslider178 = 0.0f;
		fslider179 = 0.0f;
		fbutton23 = 0.0;
		fslider180 = 0.0f;
		fslider181 = 0.0f;
		fslider182 = 1.0f;
		fslider183 = 0.0f;
		fslider184 = 0.0f;
		fslider185 = 0.0f;
		fslider186 = 1.0f;
		fslider187 = 0.0f;
		fslider188 = 0.0f;
		fslider189 = 0.0f;
		fslider190 = 1.0f;
		fslider191 = 0.0f;
		fslider192 = 0.0f;
		fslider193 = 0.0f;
		fslider194 = 1.0f;
		fslider195 = 0.0f;
		fslider196 = 1.0f;
		fslider197 = 440.0f;
		fbutton24 = 0.0;
		fslider198 = 0.0f;
		fslider199 = 0.0f;
		fslider200 = 0.0f;
		fslider201 = 1.0f;
		fslider202 = 0.0f;
		fslider203 = 1.0f;
		fslider204 = 440.0f;
		fbutton25 = 0.0;
		fslider205 = 0.0f;
		fslider206 = 0.0f;
		fslider207 = 0.0f;
		fslider208 = 1.0f;
		fslider209 = 0.0f;
		fslider210 = 1.0f;
		fslider211 = 440.0f;
		fbutton26 = 0.0;
		fslider212 = 0.0f;
		fslider213 = 0.0f;
		fslider214 = 0.0f;
		fslider215 = 1.0f;
		fslider216 = 0.0f;
		fslider217 = 1.0f;
		fslider218 = 440.0f;
		fslider219 = 0.0f;
		fslider220 = 0.0f;
		fbutton27 = 0.0;
		fslider221 = 0.0f;
		fslider222 = 0.0f;
		fslider223 = 1.0f;
		fslider224 = 0.0f;
		fslider225 = 1.0f;
		fslider226 = 440.0f;
		fslider227 = 0.0f;
		fbutton28 = 0.0;
		fslider228 = 0.0f;
		fslider229 = 0.0f;
		fslider230 = 1.0f;
		fslider231 = 0.0f;
		fslider232 = 1.0f;
		fslider233 = 440.0f;
		fslider234 = 0.0f;
		fbutton29 = 0.0;
		fslider235 = 0.0f;
		fslider236 = 0.0f;
		fslider237 = 1.0f;
		fslider238 = 0.0f;
		fslider239 = 1.0f;
		fslider240 = 440.0f;
		fslider241 = 0.0f;
		fbutton30 = 0.0;
		fslider242 = 0.0f;
		fslider243 = 0.0f;
		fslider244 = 1.0f;
		fslider245 = 0.0f;
		fslider246 = 1.0f;
		fslider247 = 440.0f;
		fslider248 = 0.0f;
		fslider249 = 0.0f;
		fbutton31 = 0.0;
		fslider250 = 0.0f;
		fslider251 = 0.0f;
		fslider252 = 1.0f;
		fslider253 = 0.0f;
		fslider254 = 0.0f;
		fslider255 = 0.0f;
		fslider256 = 0.0f;
		fslider257 = 1.0f;
		fslider258 = 0.0f;
		fslider259 = 0.0f;
		fslider260 = 0.0f;
		fslider261 = 0.0f;
		fslider262 = 1.0f;
		fslider263 = 0.0f;
		fslider264 = 0.0f;
		fslider265 = 0.0f;
		fslider266 = 0.0f;
		fslider267 = 1.0f;
		fslider268 = 0.0f;
		fslider269 = 1.0f;
		fslider270 = 440.0f;
		fslider271 = 0.0f;
		fbutton32 = 0.0;
		fslider272 = 0.0f;
		fslider273 = 0.0f;
		fslider274 = 1.0f;
		fslider275 = 0.0f;
		fslider276 = 1.0f;
		fslider277 = 440.0f;
		fslider278 = 0.0f;
		fbutton33 = 0.0;
		fslider279 = 0.0f;
		fslider280 = 0.0f;
		fslider281 = 1.0f;
		fslider282 = 0.0f;
		fslider283 = 1.0f;
		fslider284 = 440.0f;
		fslider285 = 0.0f;
		fbutton34 = 0.0;
		fslider286 = 0.0f;
		fslider287 = 0.0f;
		fslider288 = 1.0f;
		fslider289 = 0.0f;
		fslider290 = 1.0f;
		fslider291 = 440.0f;
		fslider292 = 0.0f;
		fslider293 = 0.0f;
		fbutton35 = 0.0;
		fslider294 = 0.0f;
		fslider295 = 0.0f;
		fslider296 = 1.0f;
		fslider297 = 0.0f;
		fslider298 = 0.0f;
		fslider299 = 0.0f;
		fslider300 = 0.0f;
		fslider301 = 1.0f;
		fslider302 = 0.0f;
		fslider303 = 0.0f;
		fslider304 = 0.0f;
		fslider305 = 0.0f;
		fslider306 = 1.0f;
		fslider307 = 0.0f;
		fslider308 = 0.0f;
		fslider309 = 0.0f;
		fslider310 = 0.0f;
		fslider311 = 1.0f;
		fslider312 = 0.0f;
		fslider313 = 1.0f;
		fslider314 = 440.0f;
		fslider315 = 0.0f;
		fbutton36 = 0.0;
		fslider316 = 0.0f;
		fslider317 = 0.0f;
		fslider318 = 1.0f;
		fslider319 = 0.0f;
		fslider320 = 1.0f;
		fslider321 = 440.0f;
		fslider322 = 0.0f;
		fbutton37 = 0.0;
		fslider323 = 0.0f;
		fslider324 = 0.0f;
		fslider325 = 1.0f;
		fslider326 = 0.0f;
		fslider327 = 1.0f;
		fslider328 = 440.0f;
		fslider329 = 0.0f;
		fbutton38 = 0.0;
		fslider330 = 0.0f;
		fslider331 = 0.0f;
		fslider332 = 1.0f;
		fslider333 = 0.0f;
		fslider334 = 1.0f;
		fslider335 = 440.0f;
		fslider336 = 0.0f;
		fslider337 = 0.0f;
		fbutton39 = 0.0;
		fslider338 = 0.0f;
		fslider339 = 0.0f;
		fslider340 = 1.0f;
		fslider341 = 0.0f;
		fslider342 = 0.0f;
		fslider343 = 0.0f;
		fslider344 = 0.0f;
		fslider345 = 1.0f;
		fslider346 = 0.0f;
		fslider347 = 0.0f;
		fslider348 = 0.0f;
		fslider349 = 0.0f;
		fslider350 = 1.0f;
		fslider351 = 0.0f;
		fslider352 = 0.0f;
		fslider353 = 0.0f;
		fslider354 = 0.0f;
		fslider355 = 1.0f;
		fslider356 = 0.0f;
		fslider357 = 1.0f;
		fslider358 = 440.0f;
		fslider359 = 0.0f;
		fbutton40 = 0.0;
		fslider360 = 0.0f;
		fslider361 = 0.0f;
		fslider362 = 1.0f;
		fslider363 = 0.0f;
		fslider364 = 1.0f;
		fslider365 = 440.0f;
		fslider366 = 0.0f;
		fbutton41 = 0.0;
		fslider367 = 0.0f;
		fslider368 = 0.0f;
		fslider369 = 1.0f;
		fslider370 = 0.0f;
		fslider371 = 1.0f;
		fslider372 = 440.0f;
		fslider373 = 0.0f;
		fbutton42 = 0.0;
		fslider374 = 0.0f;
		fslider375 = 0.0f;
		fslider376 = 1.0f;
		fslider377 = 0.0f;
		fslider378 = 1.0f;
		fslider379 = 440.0f;
		fslider380 = 0.0f;
		fslider381 = 0.0f;
		fbutton43 = 0.0;
		fslider382 = 0.0f;
		fslider383 = 0.0f;
		fslider384 = 1.0f;
		fslider385 = 0.0f;
		fslider386 = 0.0f;
		fslider387 = 0.0f;
		fslider388 = 0.0f;
		fslider389 = 1.0f;
		fslider390 = 0.0f;
		fslider391 = 0.0f;
		fslider392 = 0.0f;
		fslider393 = 0.0f;
		fslider394 = 1.0f;
		fslider395 = 0.0f;
		fslider396 = 0.0f;
		fslider397 = 0.0f;
		fslider398 = 0.0f;
		fslider399 = 1.0f;
		fslider400 = 0.0f;
		fslider401 = 1.0f;
		fslider402 = 440.0f;
		fslider403 = 0.0f;
		fbutton44 = 0.0;
		fslider404 = 0.0f;
		fslider405 = 0.0f;
		fslider406 = 1.0f;
		fslider407 = 0.0f;
		fslider408 = 1.0f;
		fslider409 = 440.0f;
		fslider410 = 0.0f;
		fbutton45 = 0.0;
		fslider411 = 0.0f;
		fslider412 = 0.0f;
		fslider413 = 1.0f;
		fslider414 = 0.0f;
		fslider415 = 1.0f;
		fslider416 = 440.0f;
		fslider417 = 0.0f;
		fbutton46 = 0.0;
		fslider418 = 0.0f;
		fslider419 = 0.0f;
		fslider420 = 1.0f;
		fslider421 = 0.0f;
		fslider422 = 1.0f;
		fslider423 = 440.0f;
		fslider424 = 0.0f;
		fslider425 = 0.0f;
		fbutton47 = 0.0;
		fslider426 = 0.0f;
		fslider427 = 0.0f;
		fslider428 = 1.0f;
		fslider429 = 0.0f;
		fslider430 = 0.0f;
		fslider431 = 0.0f;
		fslider432 = 0.0f;
		fslider433 = 1.0f;
		fslider434 = 0.0f;
		fslider435 = 0.0f;
		fslider436 = 0.0f;
		fslider437 = 0.0f;
		fslider438 = 1.0f;
		fslider439 = 0.0f;
		fslider440 = 0.0f;
		fslider441 = 0.0f;
		fslider442 = 0.0f;
		fslider443 = 1.0f;
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
		for (int i=0; i<2; i++) iRec81[i] = 0;
		for (int i=0; i<2; i++) fRec80[i] = 0;
		for (int i=0; i<2; i++) fRec82[i] = 0;
		for (int i=0; i<2; i++) iRec84[i] = 0;
		for (int i=0; i<2; i++) fRec83[i] = 0;
		for (int i=0; i<2; i++) fRec85[i] = 0;
		for (int i=0; i<2; i++) iRec87[i] = 0;
		for (int i=0; i<2; i++) fRec86[i] = 0;
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
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) fRec98[i] = 0;
		for (int i=0; i<2; i++) fRec100[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) fRec102[i] = 0;
		for (int i=0; i<2; i++) fRec104[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) fRec106[i] = 0;
		for (int i=0; i<2; i++) fRec108[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<2; i++) iRec111[i] = 0;
		for (int i=0; i<2; i++) fRec110[i] = 0;
		for (int i=0; i<2; i++) fRec112[i] = 0;
		for (int i=0; i<2; i++) fRec114[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<2; i++) fRec116[i] = 0;
		for (int i=0; i<2; i++) fRec118[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) fRec120[i] = 0;
		for (int i=0; i<2; i++) fRec122[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
		for (int i=0; i<2; i++) fRec124[i] = 0;
		for (int i=0; i<2; i++) iRec126[i] = 0;
		for (int i=0; i<2; i++) fRec125[i] = 0;
		for (int i=0; i<2; i++) iRec128[i] = 0;
		for (int i=0; i<2; i++) fRec127[i] = 0;
		for (int i=0; i<2; i++) iRec130[i] = 0;
		for (int i=0; i<2; i++) fRec129[i] = 0;
		for (int i=0; i<2; i++) iRec132[i] = 0;
		for (int i=0; i<2; i++) fRec131[i] = 0;
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
		for (int i=0; i<2; i++) iRec147[i] = 0;
		for (int i=0; i<2; i++) fRec146[i] = 0;
		for (int i=0; i<2; i++) iRec149[i] = 0;
		for (int i=0; i<2; i++) fRec148[i] = 0;
		for (int i=0; i<2; i++) iRec151[i] = 0;
		for (int i=0; i<2; i++) fRec150[i] = 0;
		for (int i=0; i<2; i++) iRec153[i] = 0;
		for (int i=0; i<2; i++) fRec152[i] = 0;
		for (int i=0; i<2; i++) fRec154[i] = 0;
		for (int i=0; i<2; i++) fRec156[i] = 0;
		for (int i=0; i<2; i++) fRec155[i] = 0;
		for (int i=0; i<2; i++) fRec157[i] = 0;
		for (int i=0; i<2; i++) fRec158[i] = 0;
		for (int i=0; i<2; i++) fRec160[i] = 0;
		for (int i=0; i<2; i++) fRec159[i] = 0;
		for (int i=0; i<2; i++) fRec161[i] = 0;
		for (int i=0; i<2; i++) fRec162[i] = 0;
		for (int i=0; i<2; i++) fRec164[i] = 0;
		for (int i=0; i<2; i++) fRec163[i] = 0;
		for (int i=0; i<2; i++) fRec165[i] = 0;
		for (int i=0; i<2; i++) fRec166[i] = 0;
		for (int i=0; i<2; i++) iRec168[i] = 0;
		for (int i=0; i<2; i++) fRec167[i] = 0;
		for (int i=0; i<2; i++) iRec170[i] = 0;
		for (int i=0; i<2; i++) fRec169[i] = 0;
		for (int i=0; i<2; i++) iRec172[i] = 0;
		for (int i=0; i<2; i++) fRec171[i] = 0;
		for (int i=0; i<2; i++) iRec174[i] = 0;
		for (int i=0; i<2; i++) fRec173[i] = 0;
		for (int i=0; i<2; i++) fRec175[i] = 0;
		for (int i=0; i<2; i++) fRec177[i] = 0;
		for (int i=0; i<2; i++) fRec176[i] = 0;
		for (int i=0; i<2; i++) fRec178[i] = 0;
		for (int i=0; i<2; i++) fRec179[i] = 0;
		for (int i=0; i<2; i++) fRec181[i] = 0;
		for (int i=0; i<2; i++) fRec180[i] = 0;
		for (int i=0; i<2; i++) fRec182[i] = 0;
		for (int i=0; i<2; i++) fRec183[i] = 0;
		for (int i=0; i<2; i++) fRec185[i] = 0;
		for (int i=0; i<2; i++) fRec184[i] = 0;
		for (int i=0; i<2; i++) fRec186[i] = 0;
		for (int i=0; i<2; i++) fRec187[i] = 0;
		for (int i=0; i<2; i++) iRec189[i] = 0;
		for (int i=0; i<2; i++) fRec188[i] = 0;
		for (int i=0; i<2; i++) iRec191[i] = 0;
		for (int i=0; i<2; i++) fRec190[i] = 0;
		for (int i=0; i<2; i++) iRec193[i] = 0;
		for (int i=0; i<2; i++) fRec192[i] = 0;
		for (int i=0; i<2; i++) iRec195[i] = 0;
		for (int i=0; i<2; i++) fRec194[i] = 0;
		for (int i=0; i<2; i++) fRec196[i] = 0;
		for (int i=0; i<2; i++) fRec198[i] = 0;
		for (int i=0; i<2; i++) fRec197[i] = 0;
		for (int i=0; i<2; i++) fRec199[i] = 0;
		for (int i=0; i<2; i++) fRec200[i] = 0;
		for (int i=0; i<2; i++) fRec202[i] = 0;
		for (int i=0; i<2; i++) fRec201[i] = 0;
		for (int i=0; i<2; i++) fRec203[i] = 0;
		for (int i=0; i<2; i++) fRec204[i] = 0;
		for (int i=0; i<2; i++) fRec206[i] = 0;
		for (int i=0; i<2; i++) fRec205[i] = 0;
		for (int i=0; i<2; i++) fRec207[i] = 0;
		for (int i=0; i<2; i++) fRec208[i] = 0;
		for (int i=0; i<2; i++) iRec210[i] = 0;
		for (int i=0; i<2; i++) fRec209[i] = 0;
		for (int i=0; i<2; i++) iRec212[i] = 0;
		for (int i=0; i<2; i++) fRec211[i] = 0;
		for (int i=0; i<2; i++) iRec214[i] = 0;
		for (int i=0; i<2; i++) fRec213[i] = 0;
		for (int i=0; i<2; i++) iRec216[i] = 0;
		for (int i=0; i<2; i++) fRec215[i] = 0;
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
		ui_interface->addHorizontalSlider("Attack", &fslider30, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider28, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider27, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider31, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("fmAmount", &fslider8, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("/op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider220, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider219, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider221, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider216, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider218, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider222, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider217, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton27);
		ui_interface->addHorizontalSlider("velocity", &fslider223, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op1");
		ui_interface->addHorizontalSlider("detune", &fslider209, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider211, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider213, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider214, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider212, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider215, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider210, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton26);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op2");
		ui_interface->addHorizontalSlider("detune", &fslider202, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider204, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider206, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider207, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider205, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider208, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider203, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton25);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op3");
		ui_interface->addHorizontalSlider("detune", &fslider195, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider197, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider199, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider200, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider198, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider201, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider196, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton24);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider179, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider178, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider180, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider175, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider177, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider181, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider176, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton23);
		ui_interface->addHorizontalSlider("velocity", &fslider182, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider171, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider170, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider172, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider167, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider169, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider188, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider189, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider187, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider173, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider190, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider168, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton22);
		ui_interface->addHorizontalSlider("velocity", &fslider174, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider163, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider162, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider164, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider159, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider161, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider192, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider193, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider191, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider165, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider194, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider160, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton21);
		ui_interface->addHorizontalSlider("velocity", &fslider166, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider155, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider154, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider156, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider151, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider153, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider184, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider185, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider183, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider157, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider186, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider152, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton20);
		ui_interface->addHorizontalSlider("velocity", &fslider158, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("/op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider118, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider117, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider119, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider114, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider116, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider120, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider115, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton15);
		ui_interface->addHorizontalSlider("velocity", &fslider121, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op1");
		ui_interface->addHorizontalSlider("detune", &fslider107, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider109, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider111, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider112, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider110, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider113, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider108, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton14);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op2");
		ui_interface->addHorizontalSlider("detune", &fslider100, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider102, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider104, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider105, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider103, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider106, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider101, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton13);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op3");
		ui_interface->addHorizontalSlider("detune", &fslider93, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider95, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider97, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider98, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider96, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider99, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider94, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton12);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider293, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider292, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider294, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider289, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider291, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider295, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider290, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton35);
		ui_interface->addHorizontalSlider("velocity", &fslider296, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider298, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider297, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider299, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider282, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider284, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider286, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider287, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider285, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider288, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider300, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider283, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton34);
		ui_interface->addHorizontalSlider("velocity", &fslider301, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider303, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider302, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider304, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider275, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider277, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider279, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider280, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider278, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider281, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider305, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider276, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton33);
		ui_interface->addHorizontalSlider("velocity", &fslider306, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider308, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider307, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider309, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider268, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider270, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider272, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider273, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider271, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider274, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider310, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider269, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton32);
		ui_interface->addHorizontalSlider("velocity", &fslider311, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("/op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider60, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider59, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider61, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider56, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider58, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider62, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider57, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton7);
		ui_interface->addHorizontalSlider("velocity", &fslider63, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op1");
		ui_interface->addHorizontalSlider("detune", &fslider49, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider51, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider53, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider54, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider52, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider55, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider50, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton6);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op2");
		ui_interface->addHorizontalSlider("detune", &fslider44, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider43, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider46, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider47, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider45, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider48, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider42, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op3");
		ui_interface->addHorizontalSlider("detune", &fslider35, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider37, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider39, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider40, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider38, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider41, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider36, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider381, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider380, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider382, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider377, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider379, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider383, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider378, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton43);
		ui_interface->addHorizontalSlider("velocity", &fslider384, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider386, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider385, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider387, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider370, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider372, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider374, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider375, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider373, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider376, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider388, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider371, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton42);
		ui_interface->addHorizontalSlider("velocity", &fslider389, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider391, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider390, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider392, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider363, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider365, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider367, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider368, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider366, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider369, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider393, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider364, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton41);
		ui_interface->addHorizontalSlider("velocity", &fslider394, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider396, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider395, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider397, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider356, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider358, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider360, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider361, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider359, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider362, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider398, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider357, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton40);
		ui_interface->addHorizontalSlider("velocity", &fslider399, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("/op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider147, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider146, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider148, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider143, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider145, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider149, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider144, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton19);
		ui_interface->addHorizontalSlider("velocity", &fslider150, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op1");
		ui_interface->addHorizontalSlider("detune", &fslider136, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider138, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider140, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider141, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider139, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider142, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider137, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton18);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op2");
		ui_interface->addHorizontalSlider("detune", &fslider129, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider131, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider133, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider134, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider132, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider135, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider130, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton17);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op3");
		ui_interface->addHorizontalSlider("detune", &fslider122, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider124, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider126, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider127, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider125, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider128, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider123, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton16);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider249, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider248, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider250, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider245, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider247, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider251, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider246, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton31);
		ui_interface->addHorizontalSlider("velocity", &fslider252, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider254, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider253, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider255, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider238, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider240, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider242, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider243, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider241, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider244, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider256, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider239, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton30);
		ui_interface->addHorizontalSlider("velocity", &fslider257, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider259, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider258, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider260, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider231, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider233, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider235, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider236, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider234, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider237, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider261, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider232, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton29);
		ui_interface->addHorizontalSlider("velocity", &fslider262, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider264, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider263, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider265, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider224, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider226, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider228, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider229, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider227, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider230, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider266, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider225, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton28);
		ui_interface->addHorizontalSlider("velocity", &fslider267, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("/op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider89, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider88, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider90, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider85, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider87, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider91, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider86, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton11);
		ui_interface->addHorizontalSlider("velocity", &fslider92, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op1");
		ui_interface->addHorizontalSlider("detune", &fslider78, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider80, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider82, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider83, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider81, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider84, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider79, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton10);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op2");
		ui_interface->addHorizontalSlider("detune", &fslider71, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider73, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider75, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider76, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider74, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider77, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider72, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton9);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op3");
		ui_interface->addHorizontalSlider("detune", &fslider64, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider66, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider68, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider69, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider67, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider70, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider65, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton8);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider337, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider336, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider338, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider333, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider335, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider339, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider334, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton39);
		ui_interface->addHorizontalSlider("velocity", &fslider340, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider342, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider341, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider343, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider326, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider328, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider330, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider331, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider329, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider332, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider344, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider327, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton38);
		ui_interface->addHorizontalSlider("velocity", &fslider345, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider347, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider346, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider348, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider319, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider321, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider323, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider324, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider322, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider325, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider349, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider320, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton37);
		ui_interface->addHorizontalSlider("velocity", &fslider350, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider352, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider351, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider353, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider312, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider314, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider316, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider317, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider315, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider318, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider354, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider313, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton36);
		ui_interface->addHorizontalSlider("velocity", &fslider355, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("/op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider29, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider26, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider32, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider23, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider25, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider33, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider24, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider34, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op1");
		ui_interface->addHorizontalSlider("detune", &fslider16, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider18, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider20, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider21, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider19, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider22, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider17, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op2");
		ui_interface->addHorizontalSlider("detune", &fslider9, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider11, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider13, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider14, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider12, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider15, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider10, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("/op3");
		ui_interface->addHorizontalSlider("detune", &fslider1, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider3, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider5, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider6, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider7, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider2, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider425, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider424, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider426, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider421, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider423, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider427, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider422, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton47);
		ui_interface->addHorizontalSlider("velocity", &fslider428, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider430, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider429, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider431, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider414, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider416, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider418, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider419, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider417, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider420, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider432, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider415, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton46);
		ui_interface->addHorizontalSlider("velocity", &fslider433, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider435, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider434, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider436, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider407, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider409, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider411, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider412, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider410, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider413, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider437, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider408, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton45);
		ui_interface->addHorizontalSlider("velocity", &fslider438, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider440, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider439, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider441, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider400, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider402, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider404, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider405, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider403, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider406, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider442, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider401, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton44);
		ui_interface->addHorizontalSlider("velocity", &fslider443, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
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
		float 	fSlow2 = (fConst1 * ((float(fslider3) * float(fslider2)) + (25.0f * float(fslider1))));
		float 	fSlow3 = float(fbutton0);
		float 	fSlow4 = float(fslider4);
		float 	fSlow5 = (fSlow4 * fSlow3);
		float 	fSlow6 = float(fslider5);
		float 	fSlow7 = (fConst2 * fSlow6);
		float 	fSlow8 = float(fslider6);
		float 	fSlow9 = (((1.0f - fSlow4) * fSlow8) + fSlow6);
		float 	fSlow10 = (fConst2 * fSlow9);
		int 	iSlow11 = int(((fSlow3 == 0.0f) > 0));
		float 	fSlow12 = ((fSlow5 + -1.0f) / (0 - (fConst2 * (fSlow6 - fSlow9))));
		float 	fSlow13 = (fConst3 / fSlow6);
		int 	iSlow14 = (fSlow3 > 0.0f);
		float 	fSlow15 = float(iSlow14);
		int 	iSlow16 = int(iSlow14);
		float 	fSlow17 = max(0.001f, (fConst2 * (fSlow4 * fSlow8)));
		int 	iSlow18 = int((iSlow14 > 0));
		float 	fSlow19 = (1.0f / fSlow17);
		float 	fSlow20 = float(fslider8);
		float 	fSlow21 = (fSlow20 * float(fslider7));
		float 	fSlow22 = (fConst1 * ((float(fslider11) * float(fslider10)) + (25.0f * float(fslider9))));
		float 	fSlow23 = float(fbutton1);
		float 	fSlow24 = float(fslider12);
		float 	fSlow25 = (fSlow24 * fSlow23);
		float 	fSlow26 = float(fslider13);
		float 	fSlow27 = (fConst2 * fSlow26);
		float 	fSlow28 = float(fslider14);
		float 	fSlow29 = (((1.0f - fSlow24) * fSlow28) + fSlow26);
		float 	fSlow30 = (fConst2 * fSlow29);
		int 	iSlow31 = int(((fSlow23 == 0.0f) > 0));
		float 	fSlow32 = ((fSlow25 + -1.0f) / (0 - (fConst2 * (fSlow26 - fSlow29))));
		float 	fSlow33 = (fConst3 / fSlow26);
		int 	iSlow34 = (fSlow23 > 0.0f);
		float 	fSlow35 = float(iSlow34);
		int 	iSlow36 = int(iSlow34);
		float 	fSlow37 = max(0.001f, (fConst2 * (fSlow24 * fSlow28)));
		int 	iSlow38 = int((iSlow34 > 0));
		float 	fSlow39 = (1.0f / fSlow37);
		float 	fSlow40 = (fSlow20 * float(fslider15));
		float 	fSlow41 = (fConst1 * ((float(fslider18) * float(fslider17)) + (25.0f * float(fslider16))));
		float 	fSlow42 = float(fbutton2);
		float 	fSlow43 = float(fslider19);
		float 	fSlow44 = (fSlow43 * fSlow42);
		float 	fSlow45 = float(fslider20);
		float 	fSlow46 = (fConst2 * fSlow45);
		float 	fSlow47 = float(fslider21);
		float 	fSlow48 = (((1.0f - fSlow43) * fSlow47) + fSlow45);
		float 	fSlow49 = (fConst2 * fSlow48);
		int 	iSlow50 = int(((fSlow42 == 0.0f) > 0));
		float 	fSlow51 = ((fSlow44 + -1.0f) / (0 - (fConst2 * (fSlow45 - fSlow48))));
		float 	fSlow52 = (fConst3 / fSlow45);
		int 	iSlow53 = (fSlow42 > 0.0f);
		float 	fSlow54 = float(iSlow53);
		int 	iSlow55 = int(iSlow53);
		float 	fSlow56 = max(0.001f, (fConst2 * (fSlow43 * fSlow47)));
		int 	iSlow57 = int((iSlow53 > 0));
		float 	fSlow58 = (1.0f / fSlow56);
		float 	fSlow59 = (fSlow20 * float(fslider22));
		float 	fSlow60 = (fConst1 * ((float(fslider25) * float(fslider24)) + (25.0f * float(fslider23))));
		float 	fSlow61 = float(fslider27);
		float 	fSlow62 = max((float)0, (fSlow61 + float(fslider26)));
		float 	fSlow63 = float(fslider28);
		float 	fSlow64 = float(fslider30);
		float 	fSlow65 = max((float)0, (fSlow64 + float(fslider29)));
		float 	fSlow66 = (6.9100000000000001f * fSlow65);
		int 	iSlow67 = int((fConst0 * fSlow65));
		int 	iSlow68 = (float(fbutton3) > 0.0f);
		int 	iSlow69 = int(iSlow68);
		float 	fSlow70 = float(fslider31);
		float 	fSlow71 = (float(iSlow68) * max((float)0, ((0.5f * float(fslider32)) + fSlow70)));
		float 	fSlow72 = (float(fslider34) * float(fslider33));
		float 	fSlow73 = (fConst1 * ((float(fslider37) * float(fslider36)) + (25.0f * float(fslider35))));
		float 	fSlow74 = float(fbutton4);
		float 	fSlow75 = float(fslider38);
		float 	fSlow76 = (fSlow75 * fSlow74);
		float 	fSlow77 = float(fslider39);
		float 	fSlow78 = (fConst2 * fSlow77);
		float 	fSlow79 = float(fslider40);
		float 	fSlow80 = (((1.0f - fSlow75) * fSlow79) + fSlow77);
		float 	fSlow81 = (fConst2 * fSlow80);
		int 	iSlow82 = int(((fSlow74 == 0.0f) > 0));
		float 	fSlow83 = ((fSlow76 + -1.0f) / (0 - (fConst2 * (fSlow77 - fSlow80))));
		float 	fSlow84 = (fConst3 / fSlow77);
		int 	iSlow85 = (fSlow74 > 0.0f);
		float 	fSlow86 = float(iSlow85);
		int 	iSlow87 = int(iSlow85);
		float 	fSlow88 = max(0.001f, (fConst2 * (fSlow75 * fSlow79)));
		int 	iSlow89 = int((iSlow85 > 0));
		float 	fSlow90 = (1.0f / fSlow88);
		float 	fSlow91 = (fSlow20 * float(fslider41));
		float 	fSlow92 = (fConst1 * ((25.0f * float(fslider44)) + (float(fslider43) * float(fslider42))));
		float 	fSlow93 = float(fbutton5);
		float 	fSlow94 = float(fslider45);
		float 	fSlow95 = (fSlow94 * fSlow93);
		float 	fSlow96 = float(fslider46);
		float 	fSlow97 = (fConst2 * fSlow96);
		float 	fSlow98 = float(fslider47);
		float 	fSlow99 = (((1.0f - fSlow94) * fSlow98) + fSlow96);
		float 	fSlow100 = (fConst2 * fSlow99);
		int 	iSlow101 = int(((fSlow93 == 0.0f) > 0));
		float 	fSlow102 = ((fSlow95 + -1.0f) / (0 - (fConst2 * (fSlow96 - fSlow99))));
		float 	fSlow103 = (fConst3 / fSlow96);
		int 	iSlow104 = (fSlow93 > 0.0f);
		float 	fSlow105 = float(iSlow104);
		int 	iSlow106 = int(iSlow104);
		float 	fSlow107 = max(0.001f, (fConst2 * (fSlow94 * fSlow98)));
		int 	iSlow108 = int((iSlow104 > 0));
		float 	fSlow109 = (1.0f / fSlow107);
		float 	fSlow110 = (fSlow20 * float(fslider48));
		float 	fSlow111 = (fConst1 * ((float(fslider51) * float(fslider50)) + (25.0f * float(fslider49))));
		float 	fSlow112 = float(fbutton6);
		float 	fSlow113 = float(fslider52);
		float 	fSlow114 = (fSlow113 * fSlow112);
		float 	fSlow115 = float(fslider53);
		float 	fSlow116 = (fConst2 * fSlow115);
		float 	fSlow117 = float(fslider54);
		float 	fSlow118 = (((1.0f - fSlow113) * fSlow117) + fSlow115);
		float 	fSlow119 = (fConst2 * fSlow118);
		int 	iSlow120 = int(((fSlow112 == 0.0f) > 0));
		float 	fSlow121 = ((fSlow114 + -1.0f) / (0 - (fConst2 * (fSlow115 - fSlow118))));
		float 	fSlow122 = (fConst3 / fSlow115);
		int 	iSlow123 = (fSlow112 > 0.0f);
		float 	fSlow124 = float(iSlow123);
		int 	iSlow125 = int(iSlow123);
		float 	fSlow126 = max(0.001f, (fConst2 * (fSlow113 * fSlow117)));
		int 	iSlow127 = int((iSlow123 > 0));
		float 	fSlow128 = (1.0f / fSlow126);
		float 	fSlow129 = (fSlow20 * float(fslider55));
		float 	fSlow130 = (fConst1 * ((float(fslider58) * float(fslider57)) + (25.0f * float(fslider56))));
		float 	fSlow131 = max((float)0, (fSlow61 + float(fslider59)));
		float 	fSlow132 = max((float)0, (fSlow64 + float(fslider60)));
		float 	fSlow133 = (6.9100000000000001f * fSlow132);
		int 	iSlow134 = int((fConst0 * fSlow132));
		int 	iSlow135 = (float(fbutton7) > 0.0f);
		int 	iSlow136 = int(iSlow135);
		float 	fSlow137 = (float(iSlow135) * max((float)0, ((0.5f * float(fslider61)) + fSlow70)));
		float 	fSlow138 = (float(fslider63) * float(fslider62));
		float 	fSlow139 = (fConst1 * ((float(fslider66) * float(fslider65)) + (25.0f * float(fslider64))));
		float 	fSlow140 = float(fbutton8);
		float 	fSlow141 = float(fslider67);
		float 	fSlow142 = (fSlow141 * fSlow140);
		float 	fSlow143 = float(fslider68);
		float 	fSlow144 = (fConst2 * fSlow143);
		float 	fSlow145 = float(fslider69);
		float 	fSlow146 = (((1.0f - fSlow141) * fSlow145) + fSlow143);
		float 	fSlow147 = (fConst2 * fSlow146);
		int 	iSlow148 = int(((fSlow140 == 0.0f) > 0));
		float 	fSlow149 = ((fSlow142 + -1.0f) / (0 - (fConst2 * (fSlow143 - fSlow146))));
		float 	fSlow150 = (fConst3 / fSlow143);
		int 	iSlow151 = (fSlow140 > 0.0f);
		float 	fSlow152 = float(iSlow151);
		int 	iSlow153 = int(iSlow151);
		float 	fSlow154 = max(0.001f, (fConst2 * (fSlow141 * fSlow145)));
		int 	iSlow155 = int((iSlow151 > 0));
		float 	fSlow156 = (1.0f / fSlow154);
		float 	fSlow157 = (fSlow20 * float(fslider70));
		float 	fSlow158 = (fConst1 * ((float(fslider73) * float(fslider72)) + (25.0f * float(fslider71))));
		float 	fSlow159 = float(fbutton9);
		float 	fSlow160 = float(fslider74);
		float 	fSlow161 = (fSlow160 * fSlow159);
		float 	fSlow162 = float(fslider75);
		float 	fSlow163 = (fConst2 * fSlow162);
		float 	fSlow164 = float(fslider76);
		float 	fSlow165 = (((1.0f - fSlow160) * fSlow164) + fSlow162);
		float 	fSlow166 = (fConst2 * fSlow165);
		int 	iSlow167 = int(((fSlow159 == 0.0f) > 0));
		float 	fSlow168 = ((fSlow161 + -1.0f) / (0 - (fConst2 * (fSlow162 - fSlow165))));
		float 	fSlow169 = (fConst3 / fSlow162);
		int 	iSlow170 = (fSlow159 > 0.0f);
		float 	fSlow171 = float(iSlow170);
		int 	iSlow172 = int(iSlow170);
		float 	fSlow173 = max(0.001f, (fConst2 * (fSlow160 * fSlow164)));
		int 	iSlow174 = int((iSlow170 > 0));
		float 	fSlow175 = (1.0f / fSlow173);
		float 	fSlow176 = (fSlow20 * float(fslider77));
		float 	fSlow177 = (fConst1 * ((float(fslider80) * float(fslider79)) + (25.0f * float(fslider78))));
		float 	fSlow178 = float(fbutton10);
		float 	fSlow179 = float(fslider81);
		float 	fSlow180 = (fSlow179 * fSlow178);
		float 	fSlow181 = float(fslider82);
		float 	fSlow182 = (fConst2 * fSlow181);
		float 	fSlow183 = float(fslider83);
		float 	fSlow184 = (((1.0f - fSlow179) * fSlow183) + fSlow181);
		float 	fSlow185 = (fConst2 * fSlow184);
		int 	iSlow186 = int(((fSlow178 == 0.0f) > 0));
		float 	fSlow187 = ((fSlow180 + -1.0f) / (0 - (fConst2 * (fSlow181 - fSlow184))));
		float 	fSlow188 = (fConst3 / fSlow181);
		int 	iSlow189 = (fSlow178 > 0.0f);
		float 	fSlow190 = float(iSlow189);
		int 	iSlow191 = int(iSlow189);
		float 	fSlow192 = max(0.001f, (fConst2 * (fSlow179 * fSlow183)));
		int 	iSlow193 = int((iSlow189 > 0));
		float 	fSlow194 = (1.0f / fSlow192);
		float 	fSlow195 = (fSlow20 * float(fslider84));
		float 	fSlow196 = (fConst1 * ((float(fslider87) * float(fslider86)) + (25.0f * float(fslider85))));
		float 	fSlow197 = max((float)0, (fSlow61 + float(fslider88)));
		float 	fSlow198 = max((float)0, (fSlow64 + float(fslider89)));
		float 	fSlow199 = (6.9100000000000001f * fSlow198);
		int 	iSlow200 = int((fConst0 * fSlow198));
		int 	iSlow201 = (float(fbutton11) > 0.0f);
		int 	iSlow202 = int(iSlow201);
		float 	fSlow203 = (float(iSlow201) * max((float)0, ((0.5f * float(fslider90)) + fSlow70)));
		float 	fSlow204 = (float(fslider92) * float(fslider91));
		float 	fSlow205 = (fConst1 * ((float(fslider95) * float(fslider94)) + (25.0f * float(fslider93))));
		float 	fSlow206 = float(fbutton12);
		float 	fSlow207 = float(fslider96);
		float 	fSlow208 = (fSlow207 * fSlow206);
		float 	fSlow209 = float(fslider97);
		float 	fSlow210 = (fConst2 * fSlow209);
		float 	fSlow211 = float(fslider98);
		float 	fSlow212 = (((1.0f - fSlow207) * fSlow211) + fSlow209);
		float 	fSlow213 = (fConst2 * fSlow212);
		int 	iSlow214 = int(((fSlow206 == 0.0f) > 0));
		float 	fSlow215 = ((fSlow208 + -1.0f) / (0 - (fConst2 * (fSlow209 - fSlow212))));
		float 	fSlow216 = (fConst3 / fSlow209);
		int 	iSlow217 = (fSlow206 > 0.0f);
		float 	fSlow218 = float(iSlow217);
		int 	iSlow219 = int(iSlow217);
		float 	fSlow220 = max(0.001f, (fConst2 * (fSlow207 * fSlow211)));
		int 	iSlow221 = int((iSlow217 > 0));
		float 	fSlow222 = (1.0f / fSlow220);
		float 	fSlow223 = (fSlow20 * float(fslider99));
		float 	fSlow224 = (fConst1 * ((float(fslider102) * float(fslider101)) + (25.0f * float(fslider100))));
		float 	fSlow225 = float(fbutton13);
		float 	fSlow226 = float(fslider103);
		float 	fSlow227 = (fSlow226 * fSlow225);
		float 	fSlow228 = float(fslider104);
		float 	fSlow229 = (fConst2 * fSlow228);
		float 	fSlow230 = float(fslider105);
		float 	fSlow231 = (((1.0f - fSlow226) * fSlow230) + fSlow228);
		float 	fSlow232 = (fConst2 * fSlow231);
		int 	iSlow233 = int(((fSlow225 == 0.0f) > 0));
		float 	fSlow234 = ((fSlow227 + -1.0f) / (0 - (fConst2 * (fSlow228 - fSlow231))));
		float 	fSlow235 = (fConst3 / fSlow228);
		int 	iSlow236 = (fSlow225 > 0.0f);
		float 	fSlow237 = float(iSlow236);
		int 	iSlow238 = int(iSlow236);
		float 	fSlow239 = max(0.001f, (fConst2 * (fSlow226 * fSlow230)));
		int 	iSlow240 = int((iSlow236 > 0));
		float 	fSlow241 = (1.0f / fSlow239);
		float 	fSlow242 = (fSlow20 * float(fslider106));
		float 	fSlow243 = (fConst1 * ((float(fslider109) * float(fslider108)) + (25.0f * float(fslider107))));
		float 	fSlow244 = float(fbutton14);
		float 	fSlow245 = float(fslider110);
		float 	fSlow246 = (fSlow245 * fSlow244);
		float 	fSlow247 = float(fslider111);
		float 	fSlow248 = (fConst2 * fSlow247);
		float 	fSlow249 = float(fslider112);
		float 	fSlow250 = (((1.0f - fSlow245) * fSlow249) + fSlow247);
		float 	fSlow251 = (fConst2 * fSlow250);
		int 	iSlow252 = int(((fSlow244 == 0.0f) > 0));
		float 	fSlow253 = ((fSlow246 + -1.0f) / (0 - (fConst2 * (fSlow247 - fSlow250))));
		float 	fSlow254 = (fConst3 / fSlow247);
		int 	iSlow255 = (fSlow244 > 0.0f);
		float 	fSlow256 = float(iSlow255);
		int 	iSlow257 = int(iSlow255);
		float 	fSlow258 = max(0.001f, (fConst2 * (fSlow245 * fSlow249)));
		int 	iSlow259 = int((iSlow255 > 0));
		float 	fSlow260 = (1.0f / fSlow258);
		float 	fSlow261 = (fSlow20 * float(fslider113));
		float 	fSlow262 = (fConst1 * ((float(fslider116) * float(fslider115)) + (25.0f * float(fslider114))));
		float 	fSlow263 = max((float)0, (fSlow61 + float(fslider117)));
		float 	fSlow264 = max((float)0, (fSlow64 + float(fslider118)));
		float 	fSlow265 = (6.9100000000000001f * fSlow264);
		int 	iSlow266 = int((fConst0 * fSlow264));
		int 	iSlow267 = (float(fbutton15) > 0.0f);
		int 	iSlow268 = int(iSlow267);
		float 	fSlow269 = (float(iSlow267) * max((float)0, ((0.5f * float(fslider119)) + fSlow70)));
		float 	fSlow270 = (float(fslider121) * float(fslider120));
		float 	fSlow271 = (fConst1 * ((float(fslider124) * float(fslider123)) + (25.0f * float(fslider122))));
		float 	fSlow272 = float(fbutton16);
		float 	fSlow273 = float(fslider125);
		float 	fSlow274 = (fSlow273 * fSlow272);
		float 	fSlow275 = float(fslider126);
		float 	fSlow276 = (fConst2 * fSlow275);
		float 	fSlow277 = float(fslider127);
		float 	fSlow278 = (((1.0f - fSlow273) * fSlow277) + fSlow275);
		float 	fSlow279 = (fConst2 * fSlow278);
		int 	iSlow280 = int(((fSlow272 == 0.0f) > 0));
		float 	fSlow281 = ((fSlow274 + -1.0f) / (0 - (fConst2 * (fSlow275 - fSlow278))));
		float 	fSlow282 = (fConst3 / fSlow275);
		int 	iSlow283 = (fSlow272 > 0.0f);
		float 	fSlow284 = float(iSlow283);
		int 	iSlow285 = int(iSlow283);
		float 	fSlow286 = max(0.001f, (fConst2 * (fSlow273 * fSlow277)));
		int 	iSlow287 = int((iSlow283 > 0));
		float 	fSlow288 = (1.0f / fSlow286);
		float 	fSlow289 = (fSlow20 * float(fslider128));
		float 	fSlow290 = (fConst1 * ((float(fslider131) * float(fslider130)) + (25.0f * float(fslider129))));
		float 	fSlow291 = float(fbutton17);
		float 	fSlow292 = float(fslider132);
		float 	fSlow293 = (fSlow292 * fSlow291);
		float 	fSlow294 = float(fslider133);
		float 	fSlow295 = (fConst2 * fSlow294);
		float 	fSlow296 = float(fslider134);
		float 	fSlow297 = (((1.0f - fSlow292) * fSlow296) + fSlow294);
		float 	fSlow298 = (fConst2 * fSlow297);
		int 	iSlow299 = int(((fSlow291 == 0.0f) > 0));
		float 	fSlow300 = ((fSlow293 + -1.0f) / (0 - (fConst2 * (fSlow294 - fSlow297))));
		float 	fSlow301 = (fConst3 / fSlow294);
		int 	iSlow302 = (fSlow291 > 0.0f);
		float 	fSlow303 = float(iSlow302);
		int 	iSlow304 = int(iSlow302);
		float 	fSlow305 = max(0.001f, (fConst2 * (fSlow292 * fSlow296)));
		int 	iSlow306 = int((iSlow302 > 0));
		float 	fSlow307 = (1.0f / fSlow305);
		float 	fSlow308 = (fSlow20 * float(fslider135));
		float 	fSlow309 = (fConst1 * ((float(fslider138) * float(fslider137)) + (25.0f * float(fslider136))));
		float 	fSlow310 = float(fbutton18);
		float 	fSlow311 = float(fslider139);
		float 	fSlow312 = (fSlow311 * fSlow310);
		float 	fSlow313 = float(fslider140);
		float 	fSlow314 = (fConst2 * fSlow313);
		float 	fSlow315 = float(fslider141);
		float 	fSlow316 = (((1.0f - fSlow311) * fSlow315) + fSlow313);
		float 	fSlow317 = (fConst2 * fSlow316);
		int 	iSlow318 = int(((fSlow310 == 0.0f) > 0));
		float 	fSlow319 = ((fSlow312 + -1.0f) / (0 - (fConst2 * (fSlow313 - fSlow316))));
		float 	fSlow320 = (fConst3 / fSlow313);
		int 	iSlow321 = (fSlow310 > 0.0f);
		float 	fSlow322 = float(iSlow321);
		int 	iSlow323 = int(iSlow321);
		float 	fSlow324 = max(0.001f, (fConst2 * (fSlow311 * fSlow315)));
		int 	iSlow325 = int((iSlow321 > 0));
		float 	fSlow326 = (1.0f / fSlow324);
		float 	fSlow327 = (fSlow20 * float(fslider142));
		float 	fSlow328 = (fConst1 * ((float(fslider145) * float(fslider144)) + (25.0f * float(fslider143))));
		float 	fSlow329 = max((float)0, (fSlow61 + float(fslider146)));
		float 	fSlow330 = max((float)0, (fSlow64 + float(fslider147)));
		float 	fSlow331 = (6.9100000000000001f * fSlow330);
		int 	iSlow332 = int((fConst0 * fSlow330));
		int 	iSlow333 = (float(fbutton19) > 0.0f);
		int 	iSlow334 = int(iSlow333);
		float 	fSlow335 = (float(iSlow333) * max((float)0, ((0.5f * float(fslider148)) + fSlow70)));
		float 	fSlow336 = (float(fslider150) * float(fslider149));
		int 	iSlow337 = (float((iSlow0 == 10)) != 0.0f);
		int 	iSlow338 = (float((iSlow0 == 1)) != 0.0f);
		int 	iSlow339 = (float((iSlow0 == 2)) != 0.0f);
		int 	iSlow340 = (float((iSlow0 == 3)) != 0.0f);
		int 	iSlow341 = (float((iSlow0 == 4)) != 0.0f);
		int 	iSlow342 = (float((iSlow0 == 5)) != 0.0f);
		int 	iSlow343 = (float((iSlow0 == 6)) != 0.0f);
		int 	iSlow344 = (float((iSlow0 == 7)) != 0.0f);
		int 	iSlow345 = (float((iSlow0 == 8)) != 0.0f);
		int 	iSlow346 = (float((iSlow0 == 9)) != 0.0f);
		float 	fSlow347 = (fConst1 * ((float(fslider153) * float(fslider152)) + (25.0f * float(fslider151))));
		float 	fSlow348 = max((float)0, (fSlow61 + float(fslider154)));
		float 	fSlow349 = max((float)0, (fSlow64 + float(fslider155)));
		float 	fSlow350 = (6.9100000000000001f * fSlow349);
		int 	iSlow351 = int((fConst0 * fSlow349));
		float 	fSlow352 = float(fbutton20);
		int 	iSlow353 = (fSlow352 > 0.0f);
		int 	iSlow354 = int(iSlow353);
		float 	fSlow355 = float(iSlow353);
		float 	fSlow356 = (fSlow355 * max((float)0, ((0.5f * float(fslider156)) + fSlow70)));
		float 	fSlow357 = (float(fslider158) * float(fslider157));
		float 	fSlow358 = (fConst1 * ((float(fslider161) * float(fslider160)) + (25.0f * float(fslider159))));
		float 	fSlow359 = max((float)0, (fSlow61 + float(fslider162)));
		float 	fSlow360 = max((float)0, (fSlow64 + float(fslider163)));
		float 	fSlow361 = (6.9100000000000001f * fSlow360);
		int 	iSlow362 = int((fConst0 * fSlow360));
		float 	fSlow363 = float(fbutton21);
		int 	iSlow364 = (fSlow363 > 0.0f);
		int 	iSlow365 = int(iSlow364);
		float 	fSlow366 = float(iSlow364);
		float 	fSlow367 = (fSlow366 * max((float)0, ((0.5f * float(fslider164)) + fSlow70)));
		float 	fSlow368 = (float(fslider166) * float(fslider165));
		float 	fSlow369 = (fConst1 * ((float(fslider169) * float(fslider168)) + (25.0f * float(fslider167))));
		float 	fSlow370 = max((float)0, (fSlow61 + float(fslider170)));
		float 	fSlow371 = max((float)0, (fSlow64 + float(fslider171)));
		float 	fSlow372 = (6.9100000000000001f * fSlow371);
		int 	iSlow373 = int((fConst0 * fSlow371));
		float 	fSlow374 = float(fbutton22);
		int 	iSlow375 = (fSlow374 > 0.0f);
		int 	iSlow376 = int(iSlow375);
		float 	fSlow377 = float(iSlow375);
		float 	fSlow378 = (fSlow377 * max((float)0, ((0.5f * float(fslider172)) + fSlow70)));
		float 	fSlow379 = (float(fslider174) * float(fslider173));
		float 	fSlow380 = (fConst1 * ((float(fslider177) * float(fslider176)) + (25.0f * float(fslider175))));
		float 	fSlow381 = max((float)0, (fSlow61 + float(fslider178)));
		float 	fSlow382 = max((float)0, (fSlow64 + float(fslider179)));
		float 	fSlow383 = (6.9100000000000001f * fSlow382);
		int 	iSlow384 = int((fConst0 * fSlow382));
		int 	iSlow385 = (float(fbutton23) > 0.0f);
		int 	iSlow386 = int(iSlow385);
		float 	fSlow387 = (float(iSlow385) * max((float)0, ((0.5f * float(fslider180)) + fSlow70)));
		float 	fSlow388 = (float(fslider182) * float(fslider181));
		float 	fSlow389 = float(fslider183);
		float 	fSlow390 = (fSlow352 * fSlow389);
		float 	fSlow391 = float(fslider184);
		float 	fSlow392 = (fConst2 * fSlow391);
		float 	fSlow393 = float(fslider185);
		float 	fSlow394 = (((1.0f - fSlow389) * fSlow393) + fSlow391);
		float 	fSlow395 = (fConst2 * fSlow394);
		int 	iSlow396 = int(((fSlow352 == 0.0f) > 0));
		float 	fSlow397 = ((fSlow390 + -1.0f) / (0 - (fConst2 * (fSlow391 - fSlow394))));
		float 	fSlow398 = (fConst3 / fSlow391);
		float 	fSlow399 = max(0.001f, (fConst2 * (fSlow389 * fSlow393)));
		int 	iSlow400 = int((iSlow353 > 0));
		float 	fSlow401 = (1.0f / fSlow399);
		float 	fSlow402 = float(fslider186);
		float 	fSlow403 = (fSlow20 * fSlow402);
		float 	fSlow404 = float(fslider187);
		float 	fSlow405 = (fSlow374 * fSlow404);
		float 	fSlow406 = float(fslider188);
		float 	fSlow407 = (fConst2 * fSlow406);
		float 	fSlow408 = float(fslider189);
		float 	fSlow409 = (((1.0f - fSlow404) * fSlow408) + fSlow406);
		float 	fSlow410 = (fConst2 * fSlow409);
		int 	iSlow411 = int(((fSlow374 == 0.0f) > 0));
		float 	fSlow412 = ((fSlow405 + -1.0f) / (0 - (fConst2 * (fSlow406 - fSlow409))));
		float 	fSlow413 = (fConst3 / fSlow406);
		float 	fSlow414 = max(0.001f, (fConst2 * (fSlow404 * fSlow408)));
		int 	iSlow415 = int((iSlow375 > 0));
		float 	fSlow416 = (1.0f / fSlow414);
		float 	fSlow417 = float(fslider190);
		float 	fSlow418 = (fSlow20 * fSlow417);
		float 	fSlow419 = float(fslider191);
		float 	fSlow420 = (fSlow363 * fSlow419);
		float 	fSlow421 = float(fslider192);
		float 	fSlow422 = (fConst2 * fSlow421);
		float 	fSlow423 = float(fslider193);
		float 	fSlow424 = (((1.0f - fSlow419) * fSlow423) + fSlow421);
		float 	fSlow425 = (fConst2 * fSlow424);
		int 	iSlow426 = int(((fSlow363 == 0.0f) > 0));
		float 	fSlow427 = ((fSlow420 + -1.0f) / (0 - (fConst2 * (fSlow421 - fSlow424))));
		float 	fSlow428 = (fConst3 / fSlow421);
		float 	fSlow429 = max(0.001f, (fConst2 * (fSlow419 * fSlow423)));
		int 	iSlow430 = int((iSlow364 > 0));
		float 	fSlow431 = (1.0f / fSlow429);
		float 	fSlow432 = float(fslider194);
		float 	fSlow433 = (fSlow20 * fSlow432);
		float 	fSlow434 = (fConst1 * ((float(fslider197) * float(fslider196)) + (25.0f * float(fslider195))));
		float 	fSlow435 = float(fbutton24);
		float 	fSlow436 = float(fslider198);
		float 	fSlow437 = (fSlow436 * fSlow435);
		float 	fSlow438 = float(fslider199);
		float 	fSlow439 = (fConst2 * fSlow438);
		float 	fSlow440 = float(fslider200);
		float 	fSlow441 = (((1.0f - fSlow436) * fSlow440) + fSlow438);
		float 	fSlow442 = (fConst2 * fSlow441);
		int 	iSlow443 = int(((fSlow435 == 0.0f) > 0));
		float 	fSlow444 = ((fSlow437 + -1.0f) / (0 - (fConst2 * (fSlow438 - fSlow441))));
		float 	fSlow445 = (fConst3 / fSlow438);
		int 	iSlow446 = (fSlow435 > 0.0f);
		float 	fSlow447 = float(iSlow446);
		int 	iSlow448 = int(iSlow446);
		float 	fSlow449 = max(0.001f, (fConst2 * (fSlow436 * fSlow440)));
		int 	iSlow450 = int((iSlow446 > 0));
		float 	fSlow451 = (1.0f / fSlow449);
		float 	fSlow452 = (fSlow20 * float(fslider201));
		float 	fSlow453 = (fConst1 * ((float(fslider204) * float(fslider203)) + (25.0f * float(fslider202))));
		float 	fSlow454 = float(fbutton25);
		float 	fSlow455 = float(fslider205);
		float 	fSlow456 = (fSlow455 * fSlow454);
		float 	fSlow457 = float(fslider206);
		float 	fSlow458 = (fConst2 * fSlow457);
		float 	fSlow459 = float(fslider207);
		float 	fSlow460 = (((1.0f - fSlow455) * fSlow459) + fSlow457);
		float 	fSlow461 = (fConst2 * fSlow460);
		int 	iSlow462 = int(((fSlow454 == 0.0f) > 0));
		float 	fSlow463 = ((fSlow456 + -1.0f) / (0 - (fConst2 * (fSlow457 - fSlow460))));
		float 	fSlow464 = (fConst3 / fSlow457);
		int 	iSlow465 = (fSlow454 > 0.0f);
		float 	fSlow466 = float(iSlow465);
		int 	iSlow467 = int(iSlow465);
		float 	fSlow468 = max(0.001f, (fConst2 * (fSlow455 * fSlow459)));
		int 	iSlow469 = int((iSlow465 > 0));
		float 	fSlow470 = (1.0f / fSlow468);
		float 	fSlow471 = (fSlow20 * float(fslider208));
		float 	fSlow472 = (fConst1 * ((float(fslider211) * float(fslider210)) + (25.0f * float(fslider209))));
		float 	fSlow473 = float(fbutton26);
		float 	fSlow474 = float(fslider212);
		float 	fSlow475 = (fSlow474 * fSlow473);
		float 	fSlow476 = float(fslider213);
		float 	fSlow477 = (fConst2 * fSlow476);
		float 	fSlow478 = float(fslider214);
		float 	fSlow479 = (((1.0f - fSlow474) * fSlow478) + fSlow476);
		float 	fSlow480 = (fConst2 * fSlow479);
		int 	iSlow481 = int(((fSlow473 == 0.0f) > 0));
		float 	fSlow482 = ((fSlow475 + -1.0f) / (0 - (fConst2 * (fSlow476 - fSlow479))));
		float 	fSlow483 = (fConst3 / fSlow476);
		int 	iSlow484 = (fSlow473 > 0.0f);
		float 	fSlow485 = float(iSlow484);
		int 	iSlow486 = int(iSlow484);
		float 	fSlow487 = max(0.001f, (fConst2 * (fSlow474 * fSlow478)));
		int 	iSlow488 = int((iSlow484 > 0));
		float 	fSlow489 = (1.0f / fSlow487);
		float 	fSlow490 = (fSlow20 * float(fslider215));
		float 	fSlow491 = (fConst1 * ((float(fslider218) * float(fslider217)) + (25.0f * float(fslider216))));
		float 	fSlow492 = max((float)0, (fSlow61 + float(fslider219)));
		float 	fSlow493 = max((float)0, (fSlow64 + float(fslider220)));
		float 	fSlow494 = (6.9100000000000001f * fSlow493);
		int 	iSlow495 = int((fConst0 * fSlow493));
		int 	iSlow496 = (float(fbutton27) > 0.0f);
		int 	iSlow497 = int(iSlow496);
		float 	fSlow498 = (float(iSlow496) * max((float)0, ((0.5f * float(fslider221)) + fSlow70)));
		float 	fSlow499 = (float(fslider223) * float(fslider222));
		float 	fSlow500 = (fConst1 * ((float(fslider226) * float(fslider225)) + (25.0f * float(fslider224))));
		float 	fSlow501 = float(fslider227);
		float 	fSlow502 = float(fbutton28);
		float 	fSlow503 = (fSlow502 * fSlow501);
		float 	fSlow504 = float(fslider228);
		float 	fSlow505 = (fConst2 * fSlow504);
		float 	fSlow506 = float(fslider229);
		float 	fSlow507 = (((1.0f - fSlow501) * fSlow506) + fSlow504);
		float 	fSlow508 = (fConst2 * fSlow507);
		int 	iSlow509 = int(((fSlow502 == 0.0f) > 0));
		float 	fSlow510 = ((fSlow503 + -1.0f) / (0 - (fConst2 * (fSlow504 - fSlow507))));
		float 	fSlow511 = (fConst3 / fSlow504);
		int 	iSlow512 = (fSlow502 > 0.0f);
		float 	fSlow513 = float(iSlow512);
		int 	iSlow514 = int(iSlow512);
		float 	fSlow515 = max(0.001f, (fConst2 * (fSlow501 * fSlow506)));
		int 	iSlow516 = int((iSlow512 > 0));
		float 	fSlow517 = (1.0f / fSlow515);
		float 	fSlow518 = float(fslider230);
		float 	fSlow519 = (fSlow20 * fSlow518);
		float 	fSlow520 = (fConst1 * ((float(fslider233) * float(fslider232)) + (25.0f * float(fslider231))));
		float 	fSlow521 = float(fslider234);
		float 	fSlow522 = float(fbutton29);
		float 	fSlow523 = (fSlow522 * fSlow521);
		float 	fSlow524 = float(fslider235);
		float 	fSlow525 = (fConst2 * fSlow524);
		float 	fSlow526 = float(fslider236);
		float 	fSlow527 = (((1.0f - fSlow521) * fSlow526) + fSlow524);
		float 	fSlow528 = (fConst2 * fSlow527);
		int 	iSlow529 = int(((fSlow522 == 0.0f) > 0));
		float 	fSlow530 = ((fSlow523 + -1.0f) / (0 - (fConst2 * (fSlow524 - fSlow527))));
		float 	fSlow531 = (fConst3 / fSlow524);
		int 	iSlow532 = (fSlow522 > 0.0f);
		float 	fSlow533 = float(iSlow532);
		int 	iSlow534 = int(iSlow532);
		float 	fSlow535 = max(0.001f, (fConst2 * (fSlow521 * fSlow526)));
		int 	iSlow536 = int((iSlow532 > 0));
		float 	fSlow537 = (1.0f / fSlow535);
		float 	fSlow538 = float(fslider237);
		float 	fSlow539 = (fSlow20 * fSlow538);
		float 	fSlow540 = (fConst1 * ((float(fslider240) * float(fslider239)) + (25.0f * float(fslider238))));
		float 	fSlow541 = float(fslider241);
		float 	fSlow542 = float(fbutton30);
		float 	fSlow543 = (fSlow542 * fSlow541);
		float 	fSlow544 = float(fslider242);
		float 	fSlow545 = (fConst2 * fSlow544);
		float 	fSlow546 = float(fslider243);
		float 	fSlow547 = (((1.0f - fSlow541) * fSlow546) + fSlow544);
		float 	fSlow548 = (fConst2 * fSlow547);
		int 	iSlow549 = int(((fSlow542 == 0.0f) > 0));
		float 	fSlow550 = ((fSlow543 + -1.0f) / (0 - (fConst2 * (fSlow544 - fSlow547))));
		float 	fSlow551 = (fConst3 / fSlow544);
		int 	iSlow552 = (fSlow542 > 0.0f);
		float 	fSlow553 = float(iSlow552);
		int 	iSlow554 = int(iSlow552);
		float 	fSlow555 = max(0.001f, (fConst2 * (fSlow541 * fSlow546)));
		int 	iSlow556 = int((iSlow552 > 0));
		float 	fSlow557 = (1.0f / fSlow555);
		float 	fSlow558 = float(fslider244);
		float 	fSlow559 = (fSlow20 * fSlow558);
		float 	fSlow560 = (fConst1 * ((float(fslider247) * float(fslider246)) + (25.0f * float(fslider245))));
		float 	fSlow561 = max((float)0, (fSlow61 + float(fslider248)));
		float 	fSlow562 = max((float)0, (fSlow64 + float(fslider249)));
		float 	fSlow563 = (6.9100000000000001f * fSlow562);
		int 	iSlow564 = int((fConst0 * fSlow562));
		int 	iSlow565 = (float(fbutton31) > 0.0f);
		int 	iSlow566 = int(iSlow565);
		float 	fSlow567 = (float(iSlow565) * max((float)0, ((0.5f * float(fslider250)) + fSlow70)));
		float 	fSlow568 = (float(fslider252) * float(fslider251));
		float 	fSlow569 = max((float)0, (fSlow61 + float(fslider253)));
		float 	fSlow570 = max((float)0, (fSlow64 + float(fslider254)));
		float 	fSlow571 = (6.9100000000000001f * fSlow570);
		int 	iSlow572 = int((fConst0 * fSlow570));
		float 	fSlow573 = (fSlow553 * max((float)0, ((0.5f * float(fslider255)) + fSlow70)));
		float 	fSlow574 = (float(fslider257) * float(fslider256));
		float 	fSlow575 = max((float)0, (fSlow61 + float(fslider258)));
		float 	fSlow576 = max((float)0, (fSlow64 + float(fslider259)));
		float 	fSlow577 = (6.9100000000000001f * fSlow576);
		int 	iSlow578 = int((fConst0 * fSlow576));
		float 	fSlow579 = (fSlow533 * max((float)0, ((0.5f * float(fslider260)) + fSlow70)));
		float 	fSlow580 = (float(fslider262) * float(fslider261));
		float 	fSlow581 = max((float)0, (fSlow61 + float(fslider263)));
		float 	fSlow582 = max((float)0, (fSlow64 + float(fslider264)));
		float 	fSlow583 = (6.9100000000000001f * fSlow582);
		int 	iSlow584 = int((fConst0 * fSlow582));
		float 	fSlow585 = (fSlow513 * max((float)0, ((0.5f * float(fslider265)) + fSlow70)));
		float 	fSlow586 = (float(fslider267) * float(fslider266));
		float 	fSlow587 = (fConst1 * ((float(fslider270) * float(fslider269)) + (25.0f * float(fslider268))));
		float 	fSlow588 = float(fslider271);
		float 	fSlow589 = float(fbutton32);
		float 	fSlow590 = (fSlow589 * fSlow588);
		float 	fSlow591 = float(fslider272);
		float 	fSlow592 = (fConst2 * fSlow591);
		float 	fSlow593 = float(fslider273);
		float 	fSlow594 = (((1.0f - fSlow588) * fSlow593) + fSlow591);
		float 	fSlow595 = (fConst2 * fSlow594);
		int 	iSlow596 = int(((fSlow589 == 0.0f) > 0));
		float 	fSlow597 = ((fSlow590 + -1.0f) / (0 - (fConst2 * (fSlow591 - fSlow594))));
		float 	fSlow598 = (fConst3 / fSlow591);
		int 	iSlow599 = (fSlow589 > 0.0f);
		float 	fSlow600 = float(iSlow599);
		int 	iSlow601 = int(iSlow599);
		float 	fSlow602 = max(0.001f, (fConst2 * (fSlow588 * fSlow593)));
		int 	iSlow603 = int((iSlow599 > 0));
		float 	fSlow604 = (1.0f / fSlow602);
		float 	fSlow605 = float(fslider274);
		float 	fSlow606 = (fSlow20 * fSlow605);
		float 	fSlow607 = (fConst1 * ((float(fslider277) * float(fslider276)) + (25.0f * float(fslider275))));
		float 	fSlow608 = float(fslider278);
		float 	fSlow609 = float(fbutton33);
		float 	fSlow610 = (fSlow609 * fSlow608);
		float 	fSlow611 = float(fslider279);
		float 	fSlow612 = (fConst2 * fSlow611);
		float 	fSlow613 = float(fslider280);
		float 	fSlow614 = (((1.0f - fSlow608) * fSlow613) + fSlow611);
		float 	fSlow615 = (fConst2 * fSlow614);
		int 	iSlow616 = int(((fSlow609 == 0.0f) > 0));
		float 	fSlow617 = ((fSlow610 + -1.0f) / (0 - (fConst2 * (fSlow611 - fSlow614))));
		float 	fSlow618 = (fConst3 / fSlow611);
		int 	iSlow619 = (fSlow609 > 0.0f);
		float 	fSlow620 = float(iSlow619);
		int 	iSlow621 = int(iSlow619);
		float 	fSlow622 = max(0.001f, (fConst2 * (fSlow608 * fSlow613)));
		int 	iSlow623 = int((iSlow619 > 0));
		float 	fSlow624 = (1.0f / fSlow622);
		float 	fSlow625 = float(fslider281);
		float 	fSlow626 = (fSlow20 * fSlow625);
		float 	fSlow627 = (fConst1 * ((float(fslider284) * float(fslider283)) + (25.0f * float(fslider282))));
		float 	fSlow628 = float(fslider285);
		float 	fSlow629 = float(fbutton34);
		float 	fSlow630 = (fSlow629 * fSlow628);
		float 	fSlow631 = float(fslider286);
		float 	fSlow632 = (fConst2 * fSlow631);
		float 	fSlow633 = float(fslider287);
		float 	fSlow634 = (((1.0f - fSlow628) * fSlow633) + fSlow631);
		float 	fSlow635 = (fConst2 * fSlow634);
		int 	iSlow636 = int(((fSlow629 == 0.0f) > 0));
		float 	fSlow637 = ((fSlow630 + -1.0f) / (0 - (fConst2 * (fSlow631 - fSlow634))));
		float 	fSlow638 = (fConst3 / fSlow631);
		int 	iSlow639 = (fSlow629 > 0.0f);
		float 	fSlow640 = float(iSlow639);
		int 	iSlow641 = int(iSlow639);
		float 	fSlow642 = max(0.001f, (fConst2 * (fSlow628 * fSlow633)));
		int 	iSlow643 = int((iSlow639 > 0));
		float 	fSlow644 = (1.0f / fSlow642);
		float 	fSlow645 = float(fslider288);
		float 	fSlow646 = (fSlow20 * fSlow645);
		float 	fSlow647 = (fConst1 * ((float(fslider291) * float(fslider290)) + (25.0f * float(fslider289))));
		float 	fSlow648 = max((float)0, (fSlow61 + float(fslider292)));
		float 	fSlow649 = max((float)0, (fSlow64 + float(fslider293)));
		float 	fSlow650 = (6.9100000000000001f * fSlow649);
		int 	iSlow651 = int((fConst0 * fSlow649));
		int 	iSlow652 = (float(fbutton35) > 0.0f);
		int 	iSlow653 = int(iSlow652);
		float 	fSlow654 = (float(iSlow652) * max((float)0, ((0.5f * float(fslider294)) + fSlow70)));
		float 	fSlow655 = (float(fslider296) * float(fslider295));
		float 	fSlow656 = max((float)0, (fSlow61 + float(fslider297)));
		float 	fSlow657 = max((float)0, (fSlow64 + float(fslider298)));
		float 	fSlow658 = (6.9100000000000001f * fSlow657);
		int 	iSlow659 = int((fConst0 * fSlow657));
		float 	fSlow660 = (fSlow640 * max((float)0, ((0.5f * float(fslider299)) + fSlow70)));
		float 	fSlow661 = (float(fslider301) * float(fslider300));
		float 	fSlow662 = max((float)0, (fSlow61 + float(fslider302)));
		float 	fSlow663 = max((float)0, (fSlow64 + float(fslider303)));
		float 	fSlow664 = (6.9100000000000001f * fSlow663);
		int 	iSlow665 = int((fConst0 * fSlow663));
		float 	fSlow666 = (fSlow620 * max((float)0, ((0.5f * float(fslider304)) + fSlow70)));
		float 	fSlow667 = (float(fslider306) * float(fslider305));
		float 	fSlow668 = max((float)0, (fSlow61 + float(fslider307)));
		float 	fSlow669 = max((float)0, (fSlow64 + float(fslider308)));
		float 	fSlow670 = (6.9100000000000001f * fSlow669);
		int 	iSlow671 = int((fConst0 * fSlow669));
		float 	fSlow672 = (fSlow600 * max((float)0, ((0.5f * float(fslider309)) + fSlow70)));
		float 	fSlow673 = (float(fslider311) * float(fslider310));
		float 	fSlow674 = (fConst1 * ((float(fslider314) * float(fslider313)) + (25.0f * float(fslider312))));
		float 	fSlow675 = float(fslider315);
		float 	fSlow676 = float(fbutton36);
		float 	fSlow677 = (fSlow676 * fSlow675);
		float 	fSlow678 = float(fslider316);
		float 	fSlow679 = (fConst2 * fSlow678);
		float 	fSlow680 = float(fslider317);
		float 	fSlow681 = (((1.0f - fSlow675) * fSlow680) + fSlow678);
		float 	fSlow682 = (fConst2 * fSlow681);
		int 	iSlow683 = int(((fSlow676 == 0.0f) > 0));
		float 	fSlow684 = ((fSlow677 + -1.0f) / (0 - (fConst2 * (fSlow678 - fSlow681))));
		float 	fSlow685 = (fConst3 / fSlow678);
		int 	iSlow686 = (fSlow676 > 0.0f);
		float 	fSlow687 = float(iSlow686);
		int 	iSlow688 = int(iSlow686);
		float 	fSlow689 = max(0.001f, (fConst2 * (fSlow675 * fSlow680)));
		int 	iSlow690 = int((iSlow686 > 0));
		float 	fSlow691 = (1.0f / fSlow689);
		float 	fSlow692 = float(fslider318);
		float 	fSlow693 = (fSlow20 * fSlow692);
		float 	fSlow694 = (fConst1 * ((float(fslider321) * float(fslider320)) + (25.0f * float(fslider319))));
		float 	fSlow695 = float(fslider322);
		float 	fSlow696 = float(fbutton37);
		float 	fSlow697 = (fSlow696 * fSlow695);
		float 	fSlow698 = float(fslider323);
		float 	fSlow699 = (fConst2 * fSlow698);
		float 	fSlow700 = float(fslider324);
		float 	fSlow701 = (((1.0f - fSlow695) * fSlow700) + fSlow698);
		float 	fSlow702 = (fConst2 * fSlow701);
		int 	iSlow703 = int(((fSlow696 == 0.0f) > 0));
		float 	fSlow704 = ((fSlow697 + -1.0f) / (0 - (fConst2 * (fSlow698 - fSlow701))));
		float 	fSlow705 = (fConst3 / fSlow698);
		int 	iSlow706 = (fSlow696 > 0.0f);
		float 	fSlow707 = float(iSlow706);
		int 	iSlow708 = int(iSlow706);
		float 	fSlow709 = max(0.001f, (fConst2 * (fSlow695 * fSlow700)));
		int 	iSlow710 = int((iSlow706 > 0));
		float 	fSlow711 = (1.0f / fSlow709);
		float 	fSlow712 = float(fslider325);
		float 	fSlow713 = (fSlow20 * fSlow712);
		float 	fSlow714 = (fConst1 * ((float(fslider328) * float(fslider327)) + (25.0f * float(fslider326))));
		float 	fSlow715 = float(fslider329);
		float 	fSlow716 = float(fbutton38);
		float 	fSlow717 = (fSlow716 * fSlow715);
		float 	fSlow718 = float(fslider330);
		float 	fSlow719 = (fConst2 * fSlow718);
		float 	fSlow720 = float(fslider331);
		float 	fSlow721 = (((1.0f - fSlow715) * fSlow720) + fSlow718);
		float 	fSlow722 = (fConst2 * fSlow721);
		int 	iSlow723 = int(((fSlow716 == 0.0f) > 0));
		float 	fSlow724 = ((fSlow717 + -1.0f) / (0 - (fConst2 * (fSlow718 - fSlow721))));
		float 	fSlow725 = (fConst3 / fSlow718);
		int 	iSlow726 = (fSlow716 > 0.0f);
		float 	fSlow727 = float(iSlow726);
		int 	iSlow728 = int(iSlow726);
		float 	fSlow729 = max(0.001f, (fConst2 * (fSlow715 * fSlow720)));
		int 	iSlow730 = int((iSlow726 > 0));
		float 	fSlow731 = (1.0f / fSlow729);
		float 	fSlow732 = float(fslider332);
		float 	fSlow733 = (fSlow20 * fSlow732);
		float 	fSlow734 = (fConst1 * ((float(fslider335) * float(fslider334)) + (25.0f * float(fslider333))));
		float 	fSlow735 = max((float)0, (fSlow61 + float(fslider336)));
		float 	fSlow736 = max((float)0, (fSlow64 + float(fslider337)));
		float 	fSlow737 = (6.9100000000000001f * fSlow736);
		int 	iSlow738 = int((fConst0 * fSlow736));
		int 	iSlow739 = (float(fbutton39) > 0.0f);
		int 	iSlow740 = int(iSlow739);
		float 	fSlow741 = (float(iSlow739) * max((float)0, ((0.5f * float(fslider338)) + fSlow70)));
		float 	fSlow742 = (float(fslider340) * float(fslider339));
		float 	fSlow743 = max((float)0, (fSlow61 + float(fslider341)));
		float 	fSlow744 = max((float)0, (fSlow64 + float(fslider342)));
		float 	fSlow745 = (6.9100000000000001f * fSlow744);
		int 	iSlow746 = int((fConst0 * fSlow744));
		float 	fSlow747 = (fSlow727 * max((float)0, ((0.5f * float(fslider343)) + fSlow70)));
		float 	fSlow748 = (float(fslider345) * float(fslider344));
		float 	fSlow749 = max((float)0, (fSlow61 + float(fslider346)));
		float 	fSlow750 = max((float)0, (fSlow64 + float(fslider347)));
		float 	fSlow751 = (6.9100000000000001f * fSlow750);
		int 	iSlow752 = int((fConst0 * fSlow750));
		float 	fSlow753 = (fSlow707 * max((float)0, ((0.5f * float(fslider348)) + fSlow70)));
		float 	fSlow754 = (float(fslider350) * float(fslider349));
		float 	fSlow755 = max((float)0, (fSlow61 + float(fslider351)));
		float 	fSlow756 = max((float)0, (fSlow64 + float(fslider352)));
		float 	fSlow757 = (6.9100000000000001f * fSlow756);
		int 	iSlow758 = int((fConst0 * fSlow756));
		float 	fSlow759 = (fSlow687 * max((float)0, ((0.5f * float(fslider353)) + fSlow70)));
		float 	fSlow760 = (float(fslider355) * float(fslider354));
		float 	fSlow761 = (fConst1 * ((float(fslider358) * float(fslider357)) + (25.0f * float(fslider356))));
		float 	fSlow762 = float(fslider359);
		float 	fSlow763 = float(fbutton40);
		float 	fSlow764 = (fSlow763 * fSlow762);
		float 	fSlow765 = float(fslider360);
		float 	fSlow766 = (fConst2 * fSlow765);
		float 	fSlow767 = float(fslider361);
		float 	fSlow768 = (((1.0f - fSlow762) * fSlow767) + fSlow765);
		float 	fSlow769 = (fConst2 * fSlow768);
		int 	iSlow770 = int(((fSlow763 == 0.0f) > 0));
		float 	fSlow771 = ((fSlow764 + -1.0f) / (0 - (fConst2 * (fSlow765 - fSlow768))));
		float 	fSlow772 = (fConst3 / fSlow765);
		int 	iSlow773 = (fSlow763 > 0.0f);
		float 	fSlow774 = float(iSlow773);
		int 	iSlow775 = int(iSlow773);
		float 	fSlow776 = max(0.001f, (fConst2 * (fSlow762 * fSlow767)));
		int 	iSlow777 = int((iSlow773 > 0));
		float 	fSlow778 = (1.0f / fSlow776);
		float 	fSlow779 = float(fslider362);
		float 	fSlow780 = (fSlow20 * fSlow779);
		float 	fSlow781 = (fConst1 * ((float(fslider365) * float(fslider364)) + (25.0f * float(fslider363))));
		float 	fSlow782 = float(fslider366);
		float 	fSlow783 = float(fbutton41);
		float 	fSlow784 = (fSlow783 * fSlow782);
		float 	fSlow785 = float(fslider367);
		float 	fSlow786 = (fConst2 * fSlow785);
		float 	fSlow787 = float(fslider368);
		float 	fSlow788 = (((1.0f - fSlow782) * fSlow787) + fSlow785);
		float 	fSlow789 = (fConst2 * fSlow788);
		int 	iSlow790 = int(((fSlow783 == 0.0f) > 0));
		float 	fSlow791 = ((fSlow784 + -1.0f) / (0 - (fConst2 * (fSlow785 - fSlow788))));
		float 	fSlow792 = (fConst3 / fSlow785);
		int 	iSlow793 = (fSlow783 > 0.0f);
		float 	fSlow794 = float(iSlow793);
		int 	iSlow795 = int(iSlow793);
		float 	fSlow796 = max(0.001f, (fConst2 * (fSlow782 * fSlow787)));
		int 	iSlow797 = int((iSlow793 > 0));
		float 	fSlow798 = (1.0f / fSlow796);
		float 	fSlow799 = float(fslider369);
		float 	fSlow800 = (fSlow20 * fSlow799);
		float 	fSlow801 = (fConst1 * ((float(fslider372) * float(fslider371)) + (25.0f * float(fslider370))));
		float 	fSlow802 = float(fslider373);
		float 	fSlow803 = float(fbutton42);
		float 	fSlow804 = (fSlow803 * fSlow802);
		float 	fSlow805 = float(fslider374);
		float 	fSlow806 = (fConst2 * fSlow805);
		float 	fSlow807 = float(fslider375);
		float 	fSlow808 = (((1.0f - fSlow802) * fSlow807) + fSlow805);
		float 	fSlow809 = (fConst2 * fSlow808);
		int 	iSlow810 = int(((fSlow803 == 0.0f) > 0));
		float 	fSlow811 = ((fSlow804 + -1.0f) / (0 - (fConst2 * (fSlow805 - fSlow808))));
		float 	fSlow812 = (fConst3 / fSlow805);
		int 	iSlow813 = (fSlow803 > 0.0f);
		float 	fSlow814 = float(iSlow813);
		int 	iSlow815 = int(iSlow813);
		float 	fSlow816 = max(0.001f, (fConst2 * (fSlow802 * fSlow807)));
		int 	iSlow817 = int((iSlow813 > 0));
		float 	fSlow818 = (1.0f / fSlow816);
		float 	fSlow819 = float(fslider376);
		float 	fSlow820 = (fSlow20 * fSlow819);
		float 	fSlow821 = (fConst1 * ((float(fslider379) * float(fslider378)) + (25.0f * float(fslider377))));
		float 	fSlow822 = max((float)0, (fSlow61 + float(fslider380)));
		float 	fSlow823 = max((float)0, (fSlow64 + float(fslider381)));
		float 	fSlow824 = (6.9100000000000001f * fSlow823);
		int 	iSlow825 = int((fConst0 * fSlow823));
		int 	iSlow826 = (float(fbutton43) > 0.0f);
		int 	iSlow827 = int(iSlow826);
		float 	fSlow828 = (float(iSlow826) * max((float)0, ((0.5f * float(fslider382)) + fSlow70)));
		float 	fSlow829 = (float(fslider384) * float(fslider383));
		float 	fSlow830 = max((float)0, (fSlow61 + float(fslider385)));
		float 	fSlow831 = max((float)0, (fSlow64 + float(fslider386)));
		float 	fSlow832 = (6.9100000000000001f * fSlow831);
		int 	iSlow833 = int((fConst0 * fSlow831));
		float 	fSlow834 = (fSlow814 * max((float)0, ((0.5f * float(fslider387)) + fSlow70)));
		float 	fSlow835 = (float(fslider389) * float(fslider388));
		float 	fSlow836 = max((float)0, (fSlow61 + float(fslider390)));
		float 	fSlow837 = max((float)0, (fSlow64 + float(fslider391)));
		float 	fSlow838 = (6.9100000000000001f * fSlow837);
		int 	iSlow839 = int((fConst0 * fSlow837));
		float 	fSlow840 = (fSlow794 * max((float)0, ((0.5f * float(fslider392)) + fSlow70)));
		float 	fSlow841 = (float(fslider394) * float(fslider393));
		float 	fSlow842 = max((float)0, (fSlow61 + float(fslider395)));
		float 	fSlow843 = max((float)0, (fSlow64 + float(fslider396)));
		float 	fSlow844 = (6.9100000000000001f * fSlow843);
		int 	iSlow845 = int((fConst0 * fSlow843));
		float 	fSlow846 = (fSlow774 * max((float)0, ((0.5f * float(fslider397)) + fSlow70)));
		float 	fSlow847 = (float(fslider399) * float(fslider398));
		float 	fSlow848 = (fConst1 * ((float(fslider402) * float(fslider401)) + (25.0f * float(fslider400))));
		float 	fSlow849 = float(fslider403);
		float 	fSlow850 = float(fbutton44);
		float 	fSlow851 = (fSlow850 * fSlow849);
		float 	fSlow852 = float(fslider404);
		float 	fSlow853 = (fConst2 * fSlow852);
		float 	fSlow854 = float(fslider405);
		float 	fSlow855 = (((1.0f - fSlow849) * fSlow854) + fSlow852);
		float 	fSlow856 = (fConst2 * fSlow855);
		int 	iSlow857 = int(((fSlow850 == 0.0f) > 0));
		float 	fSlow858 = ((fSlow851 + -1.0f) / (0 - (fConst2 * (fSlow852 - fSlow855))));
		float 	fSlow859 = (fConst3 / fSlow852);
		int 	iSlow860 = (fSlow850 > 0.0f);
		float 	fSlow861 = float(iSlow860);
		int 	iSlow862 = int(iSlow860);
		float 	fSlow863 = max(0.001f, (fConst2 * (fSlow849 * fSlow854)));
		int 	iSlow864 = int((iSlow860 > 0));
		float 	fSlow865 = (1.0f / fSlow863);
		float 	fSlow866 = float(fslider406);
		float 	fSlow867 = (fSlow20 * fSlow866);
		float 	fSlow868 = (fConst1 * ((float(fslider409) * float(fslider408)) + (25.0f * float(fslider407))));
		float 	fSlow869 = float(fslider410);
		float 	fSlow870 = float(fbutton45);
		float 	fSlow871 = (fSlow870 * fSlow869);
		float 	fSlow872 = float(fslider411);
		float 	fSlow873 = (fConst2 * fSlow872);
		float 	fSlow874 = float(fslider412);
		float 	fSlow875 = (((1.0f - fSlow869) * fSlow874) + fSlow872);
		float 	fSlow876 = (fConst2 * fSlow875);
		int 	iSlow877 = int(((fSlow870 == 0.0f) > 0));
		float 	fSlow878 = ((fSlow871 + -1.0f) / (0 - (fConst2 * (fSlow872 - fSlow875))));
		float 	fSlow879 = (fConst3 / fSlow872);
		int 	iSlow880 = (fSlow870 > 0.0f);
		float 	fSlow881 = float(iSlow880);
		int 	iSlow882 = int(iSlow880);
		float 	fSlow883 = max(0.001f, (fConst2 * (fSlow869 * fSlow874)));
		int 	iSlow884 = int((iSlow880 > 0));
		float 	fSlow885 = (1.0f / fSlow883);
		float 	fSlow886 = float(fslider413);
		float 	fSlow887 = (fSlow20 * fSlow886);
		float 	fSlow888 = (fConst1 * ((float(fslider416) * float(fslider415)) + (25.0f * float(fslider414))));
		float 	fSlow889 = float(fslider417);
		float 	fSlow890 = float(fbutton46);
		float 	fSlow891 = (fSlow890 * fSlow889);
		float 	fSlow892 = float(fslider418);
		float 	fSlow893 = (fConst2 * fSlow892);
		float 	fSlow894 = float(fslider419);
		float 	fSlow895 = (((1.0f - fSlow889) * fSlow894) + fSlow892);
		float 	fSlow896 = (fConst2 * fSlow895);
		int 	iSlow897 = int(((fSlow890 == 0.0f) > 0));
		float 	fSlow898 = ((fSlow891 + -1.0f) / (0 - (fConst2 * (fSlow892 - fSlow895))));
		float 	fSlow899 = (fConst3 / fSlow892);
		int 	iSlow900 = (fSlow890 > 0.0f);
		float 	fSlow901 = float(iSlow900);
		int 	iSlow902 = int(iSlow900);
		float 	fSlow903 = max(0.001f, (fConst2 * (fSlow889 * fSlow894)));
		int 	iSlow904 = int((iSlow900 > 0));
		float 	fSlow905 = (1.0f / fSlow903);
		float 	fSlow906 = float(fslider420);
		float 	fSlow907 = (fSlow20 * fSlow906);
		float 	fSlow908 = (fConst1 * ((float(fslider423) * float(fslider422)) + (25.0f * float(fslider421))));
		float 	fSlow909 = max((float)0, (fSlow61 + float(fslider424)));
		float 	fSlow910 = max((float)0, (fSlow64 + float(fslider425)));
		float 	fSlow911 = (6.9100000000000001f * fSlow910);
		int 	iSlow912 = int((fConst0 * fSlow910));
		int 	iSlow913 = (float(fbutton47) > 0.0f);
		int 	iSlow914 = int(iSlow913);
		float 	fSlow915 = (float(iSlow913) * max((float)0, ((0.5f * float(fslider426)) + fSlow70)));
		float 	fSlow916 = (float(fslider428) * float(fslider427));
		float 	fSlow917 = max((float)0, (fSlow61 + float(fslider429)));
		float 	fSlow918 = max((float)0, (fSlow64 + float(fslider430)));
		float 	fSlow919 = (6.9100000000000001f * fSlow918);
		int 	iSlow920 = int((fConst0 * fSlow918));
		float 	fSlow921 = (fSlow901 * max((float)0, ((0.5f * float(fslider431)) + fSlow70)));
		float 	fSlow922 = (float(fslider433) * float(fslider432));
		float 	fSlow923 = max((float)0, (fSlow61 + float(fslider434)));
		float 	fSlow924 = max((float)0, (fSlow64 + float(fslider435)));
		float 	fSlow925 = (6.9100000000000001f * fSlow924);
		int 	iSlow926 = int((fConst0 * fSlow924));
		float 	fSlow927 = (fSlow881 * max((float)0, ((0.5f * float(fslider436)) + fSlow70)));
		float 	fSlow928 = (float(fslider438) * float(fslider437));
		float 	fSlow929 = max((float)0, (fSlow61 + float(fslider439)));
		float 	fSlow930 = max((float)0, (fSlow64 + float(fslider440)));
		float 	fSlow931 = (6.9100000000000001f * fSlow930);
		int 	iSlow932 = int((fConst0 * fSlow930));
		float 	fSlow933 = (fSlow861 * max((float)0, ((0.5f * float(fslider441)) + fSlow70)));
		float 	fSlow934 = (float(fslider443) * float(fslider442));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			if (iSlow1) {
				fRec1[0] = (fSlow2 + (fRec1[1] - floorf((fSlow2 + fRec1[1]))));
				fRec3[0] = ((iSlow11)?0.0f:min(fSlow10, (fRec3[1] + 1.0f)));
				iTempPerm1 = int((fRec3[0] < fSlow7));
				fRec2[0] = ((iSlow16)?(fSlow15 * ((iTempPerm1)?((int((fRec3[0] < 0.0f)))?0.0f:((iTempPerm1)?(fSlow13 * fRec3[0]):1.0f)):((int((fRec3[0] < fSlow10)))?((fSlow12 * (fRec3[0] - fSlow7)) + 1.0f):fSlow5))):fRec2[1]);
				fRec4[0] = ((iSlow18)?0.0f:min(fSlow17, (fRec4[1] + 1.0f)));
				fRec5[0] = (fSlow22 + (fRec5[1] - floorf((fSlow22 + fRec5[1]))));
				fRec7[0] = ((iSlow31)?0.0f:min(fSlow30, (fRec7[1] + 1.0f)));
				iTempPerm2 = int((fRec7[0] < fSlow27));
				fRec6[0] = ((iSlow36)?(fSlow35 * ((iTempPerm2)?((int((fRec7[0] < 0.0f)))?0.0f:((iTempPerm2)?(fSlow33 * fRec7[0]):1.0f)):((int((fRec7[0] < fSlow30)))?((fSlow32 * (fRec7[0] - fSlow27)) + 1.0f):fSlow25))):fRec6[1]);
				fRec8[0] = ((iSlow38)?0.0f:min(fSlow37, (fRec8[1] + 1.0f)));
				fRec9[0] = (fSlow41 + (fRec9[1] - floorf((fSlow41 + fRec9[1]))));
				fRec11[0] = ((iSlow50)?0.0f:min(fSlow49, (fRec11[1] + 1.0f)));
				iTempPerm3 = int((fRec11[0] < fSlow46));
				fRec10[0] = ((iSlow55)?(fSlow54 * ((iTempPerm3)?((int((fRec11[0] < 0.0f)))?0.0f:((iTempPerm3)?(fSlow52 * fRec11[0]):1.0f)):((int((fRec11[0] < fSlow49)))?((fSlow51 * (fRec11[0] - fSlow46)) + 1.0f):fSlow44))):fRec10[1]);
				fRec12[0] = ((iSlow57)?0.0f:min(fSlow56, (fRec12[1] + 1.0f)));
				fRec13[0] = (fSlow60 + (fRec13[1] - floorf((fSlow60 + fRec13[1]))));
				iRec15[0] = (iSlow68 * (iRec15[1] + 1));
				iTempPerm4 = int((iRec15[0] < iSlow67));
				fTempPerm5 = expf((0 - (fConst4 / ((iSlow69)?((iTempPerm4)?fSlow66:fSlow63):fSlow62))));
				fRec14[0] = ((fRec14[1] * fTempPerm5) + (((iSlow69)?((iTempPerm4)?1.5873015873015872f:fSlow71):0.0f) * (1.0f - fTempPerm5)));
				fTempPerm6 = (fSlow72 * (min(1.0f, fRec14[0]) * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow59 * (((int((fRec12[0] < 0.0f)))?fRec10[0]:((int((fRec12[0] < fSlow56)))?(fRec10[0] + (fSlow58 * (0 - (fRec12[0] * fRec10[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec9[0] + (fSlow40 * (((int((fRec8[0] < 0.0f)))?fRec6[0]:((int((fRec8[0] < fSlow37)))?(fRec6[0] + (fSlow39 * (0 - (fRec8[0] * fRec6[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec5[0] + (fSlow21 * (((int((fRec4[0] < 0.0f)))?fRec2[0]:((int((fRec4[0] < fSlow17)))?(fRec2[0] + (fSlow19 * (0 - (fRec4[0] * fRec2[0])))):0.0f)) * ftbl0[(((int((65536.0f * fRec1[0])) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]));
				fRec16[0] = (fSlow73 + (fRec16[1] - floorf((fSlow73 + fRec16[1]))));
				fRec18[0] = ((iSlow82)?0.0f:min(fSlow81, (fRec18[1] + 1.0f)));
				iTempPerm7 = int((fRec18[0] < fSlow78));
				fRec17[0] = ((iSlow87)?(fSlow86 * ((iTempPerm7)?((int((fRec18[0] < 0.0f)))?0.0f:((iTempPerm7)?(fSlow84 * fRec18[0]):1.0f)):((int((fRec18[0] < fSlow81)))?((fSlow83 * (fRec18[0] - fSlow78)) + 1.0f):fSlow76))):fRec17[1]);
				fRec19[0] = ((iSlow89)?0.0f:min(fSlow88, (fRec19[1] + 1.0f)));
				fRec20[0] = (fSlow92 + (fRec20[1] - floorf((fSlow92 + fRec20[1]))));
				fRec22[0] = ((iSlow101)?0.0f:min(fSlow100, (fRec22[1] + 1.0f)));
				iTempPerm8 = int((fRec22[0] < fSlow97));
				fRec21[0] = ((iSlow106)?(fSlow105 * ((iTempPerm8)?((int((fRec22[0] < 0.0f)))?0.0f:((iTempPerm8)?(fSlow103 * fRec22[0]):1.0f)):((int((fRec22[0] < fSlow100)))?((fSlow102 * (fRec22[0] - fSlow97)) + 1.0f):fSlow95))):fRec21[1]);
				fRec23[0] = ((iSlow108)?0.0f:min(fSlow107, (fRec23[1] + 1.0f)));
				fRec24[0] = (fSlow111 + (fRec24[1] - floorf((fSlow111 + fRec24[1]))));
				fRec26[0] = ((iSlow120)?0.0f:min(fSlow119, (fRec26[1] + 1.0f)));
				iTempPerm9 = int((fRec26[0] < fSlow116));
				fRec25[0] = ((iSlow125)?(fSlow124 * ((iTempPerm9)?((int((fRec26[0] < 0.0f)))?0.0f:((iTempPerm9)?(fSlow122 * fRec26[0]):1.0f)):((int((fRec26[0] < fSlow119)))?((fSlow121 * (fRec26[0] - fSlow116)) + 1.0f):fSlow114))):fRec25[1]);
				fRec27[0] = ((iSlow127)?0.0f:min(fSlow126, (fRec27[1] + 1.0f)));
				fRec28[0] = (fSlow130 + (fRec28[1] - floorf((fSlow130 + fRec28[1]))));
				iRec30[0] = (iSlow135 * (iRec30[1] + 1));
				iTempPerm10 = int((iRec30[0] < iSlow134));
				fTempPerm11 = expf((0 - (fConst4 / ((iSlow136)?((iTempPerm10)?fSlow133:fSlow63):fSlow131))));
				fRec29[0] = ((fRec29[1] * fTempPerm11) + (((iSlow136)?((iTempPerm10)?1.5873015873015872f:fSlow137):0.0f) * (1.0f - fTempPerm11)));
				fTempPerm12 = (fSlow138 * (min(1.0f, fRec29[0]) * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow129 * (((int((fRec27[0] < 0.0f)))?fRec25[0]:((int((fRec27[0] < fSlow126)))?(fRec25[0] + (fSlow128 * (0 - (fRec27[0] * fRec25[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec24[0] + (fSlow110 * (((int((fRec23[0] < 0.0f)))?fRec21[0]:((int((fRec23[0] < fSlow107)))?(fRec21[0] + (fSlow109 * (0 - (fRec23[0] * fRec21[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec20[0] + (fSlow91 * (((int((fRec19[0] < 0.0f)))?fRec17[0]:((int((fRec19[0] < fSlow88)))?(fRec17[0] + (fSlow90 * (0 - (fRec19[0] * fRec17[0])))):0.0f)) * ftbl0[(((int((65536.0f * fRec16[0])) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]));
				fRec31[0] = (fSlow139 + (fRec31[1] - floorf((fSlow139 + fRec31[1]))));
				fRec33[0] = ((iSlow148)?0.0f:min(fSlow147, (fRec33[1] + 1.0f)));
				iTempPerm13 = int((fRec33[0] < fSlow144));
				fRec32[0] = ((iSlow153)?(fSlow152 * ((iTempPerm13)?((int((fRec33[0] < 0.0f)))?0.0f:((iTempPerm13)?(fSlow150 * fRec33[0]):1.0f)):((int((fRec33[0] < fSlow147)))?((fSlow149 * (fRec33[0] - fSlow144)) + 1.0f):fSlow142))):fRec32[1]);
				fRec34[0] = ((iSlow155)?0.0f:min(fSlow154, (fRec34[1] + 1.0f)));
				fRec35[0] = (fSlow158 + (fRec35[1] - floorf((fSlow158 + fRec35[1]))));
				fRec37[0] = ((iSlow167)?0.0f:min(fSlow166, (fRec37[1] + 1.0f)));
				iTempPerm14 = int((fRec37[0] < fSlow163));
				fRec36[0] = ((iSlow172)?(fSlow171 * ((iTempPerm14)?((int((fRec37[0] < 0.0f)))?0.0f:((iTempPerm14)?(fSlow169 * fRec37[0]):1.0f)):((int((fRec37[0] < fSlow166)))?((fSlow168 * (fRec37[0] - fSlow163)) + 1.0f):fSlow161))):fRec36[1]);
				fRec38[0] = ((iSlow174)?0.0f:min(fSlow173, (fRec38[1] + 1.0f)));
				fRec39[0] = (fSlow177 + (fRec39[1] - floorf((fSlow177 + fRec39[1]))));
				fRec41[0] = ((iSlow186)?0.0f:min(fSlow185, (fRec41[1] + 1.0f)));
				iTempPerm15 = int((fRec41[0] < fSlow182));
				fRec40[0] = ((iSlow191)?(fSlow190 * ((iTempPerm15)?((int((fRec41[0] < 0.0f)))?0.0f:((iTempPerm15)?(fSlow188 * fRec41[0]):1.0f)):((int((fRec41[0] < fSlow185)))?((fSlow187 * (fRec41[0] - fSlow182)) + 1.0f):fSlow180))):fRec40[1]);
				fRec42[0] = ((iSlow193)?0.0f:min(fSlow192, (fRec42[1] + 1.0f)));
				fRec43[0] = (fSlow196 + (fRec43[1] - floorf((fSlow196 + fRec43[1]))));
				iRec45[0] = (iSlow201 * (iRec45[1] + 1));
				iTempPerm16 = int((iRec45[0] < iSlow200));
				fTempPerm17 = expf((0 - (fConst4 / ((iSlow202)?((iTempPerm16)?fSlow199:fSlow63):fSlow197))));
				fRec44[0] = ((fRec44[1] * fTempPerm17) + (((iSlow202)?((iTempPerm16)?1.5873015873015872f:fSlow203):0.0f) * (1.0f - fTempPerm17)));
				fTempPerm18 = (fSlow204 * (min(1.0f, fRec44[0]) * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow195 * (((int((fRec42[0] < 0.0f)))?fRec40[0]:((int((fRec42[0] < fSlow192)))?(fRec40[0] + (fSlow194 * (0 - (fRec42[0] * fRec40[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec39[0] + (fSlow176 * (((int((fRec38[0] < 0.0f)))?fRec36[0]:((int((fRec38[0] < fSlow173)))?(fRec36[0] + (fSlow175 * (0 - (fRec38[0] * fRec36[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec35[0] + (fSlow157 * (((int((fRec34[0] < 0.0f)))?fRec32[0]:((int((fRec34[0] < fSlow154)))?(fRec32[0] + (fSlow156 * (0 - (fRec34[0] * fRec32[0])))):0.0f)) * ftbl0[(((int((65536.0f * fRec31[0])) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]));
				fRec46[0] = (fSlow205 + (fRec46[1] - floorf((fSlow205 + fRec46[1]))));
				fRec48[0] = ((iSlow214)?0.0f:min(fSlow213, (fRec48[1] + 1.0f)));
				iTempPerm19 = int((fRec48[0] < fSlow210));
				fRec47[0] = ((iSlow219)?(fSlow218 * ((iTempPerm19)?((int((fRec48[0] < 0.0f)))?0.0f:((iTempPerm19)?(fSlow216 * fRec48[0]):1.0f)):((int((fRec48[0] < fSlow213)))?((fSlow215 * (fRec48[0] - fSlow210)) + 1.0f):fSlow208))):fRec47[1]);
				fRec49[0] = ((iSlow221)?0.0f:min(fSlow220, (fRec49[1] + 1.0f)));
				fRec50[0] = (fSlow224 + (fRec50[1] - floorf((fSlow224 + fRec50[1]))));
				fRec52[0] = ((iSlow233)?0.0f:min(fSlow232, (fRec52[1] + 1.0f)));
				iTempPerm20 = int((fRec52[0] < fSlow229));
				fRec51[0] = ((iSlow238)?(fSlow237 * ((iTempPerm20)?((int((fRec52[0] < 0.0f)))?0.0f:((iTempPerm20)?(fSlow235 * fRec52[0]):1.0f)):((int((fRec52[0] < fSlow232)))?((fSlow234 * (fRec52[0] - fSlow229)) + 1.0f):fSlow227))):fRec51[1]);
				fRec53[0] = ((iSlow240)?0.0f:min(fSlow239, (fRec53[1] + 1.0f)));
				fRec54[0] = (fSlow243 + (fRec54[1] - floorf((fSlow243 + fRec54[1]))));
				fRec56[0] = ((iSlow252)?0.0f:min(fSlow251, (fRec56[1] + 1.0f)));
				iTempPerm21 = int((fRec56[0] < fSlow248));
				fRec55[0] = ((iSlow257)?(fSlow256 * ((iTempPerm21)?((int((fRec56[0] < 0.0f)))?0.0f:((iTempPerm21)?(fSlow254 * fRec56[0]):1.0f)):((int((fRec56[0] < fSlow251)))?((fSlow253 * (fRec56[0] - fSlow248)) + 1.0f):fSlow246))):fRec55[1]);
				fRec57[0] = ((iSlow259)?0.0f:min(fSlow258, (fRec57[1] + 1.0f)));
				fRec58[0] = (fSlow262 + (fRec58[1] - floorf((fSlow262 + fRec58[1]))));
				iRec60[0] = (iSlow267 * (iRec60[1] + 1));
				iTempPerm22 = int((iRec60[0] < iSlow266));
				fTempPerm23 = expf((0 - (fConst4 / ((iSlow268)?((iTempPerm22)?fSlow265:fSlow63):fSlow263))));
				fRec59[0] = ((fRec59[1] * fTempPerm23) + (((iSlow268)?((iTempPerm22)?1.5873015873015872f:fSlow269):0.0f) * (1.0f - fTempPerm23)));
				fTempPerm24 = (fSlow270 * (min(1.0f, fRec59[0]) * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow261 * (((int((fRec57[0] < 0.0f)))?fRec55[0]:((int((fRec57[0] < fSlow258)))?(fRec55[0] + (fSlow260 * (0 - (fRec57[0] * fRec55[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec54[0] + (fSlow242 * (((int((fRec53[0] < 0.0f)))?fRec51[0]:((int((fRec53[0] < fSlow239)))?(fRec51[0] + (fSlow241 * (0 - (fRec53[0] * fRec51[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec50[0] + (fSlow223 * (((int((fRec49[0] < 0.0f)))?fRec47[0]:((int((fRec49[0] < fSlow220)))?(fRec47[0] + (fSlow222 * (0 - (fRec49[0] * fRec47[0])))):0.0f)) * ftbl0[(((int((65536.0f * fRec46[0])) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]));
				fRec61[0] = (fSlow271 + (fRec61[1] - floorf((fSlow271 + fRec61[1]))));
				fRec63[0] = ((iSlow280)?0.0f:min(fSlow279, (fRec63[1] + 1.0f)));
				iTempPerm25 = int((fRec63[0] < fSlow276));
				fRec62[0] = ((iSlow285)?(fSlow284 * ((iTempPerm25)?((int((fRec63[0] < 0.0f)))?0.0f:((iTempPerm25)?(fSlow282 * fRec63[0]):1.0f)):((int((fRec63[0] < fSlow279)))?((fSlow281 * (fRec63[0] - fSlow276)) + 1.0f):fSlow274))):fRec62[1]);
				fRec64[0] = ((iSlow287)?0.0f:min(fSlow286, (fRec64[1] + 1.0f)));
				fRec65[0] = (fSlow290 + (fRec65[1] - floorf((fSlow290 + fRec65[1]))));
				fRec67[0] = ((iSlow299)?0.0f:min(fSlow298, (fRec67[1] + 1.0f)));
				iTempPerm26 = int((fRec67[0] < fSlow295));
				fRec66[0] = ((iSlow304)?(fSlow303 * ((iTempPerm26)?((int((fRec67[0] < 0.0f)))?0.0f:((iTempPerm26)?(fSlow301 * fRec67[0]):1.0f)):((int((fRec67[0] < fSlow298)))?((fSlow300 * (fRec67[0] - fSlow295)) + 1.0f):fSlow293))):fRec66[1]);
				fRec68[0] = ((iSlow306)?0.0f:min(fSlow305, (fRec68[1] + 1.0f)));
				fRec69[0] = (fSlow309 + (fRec69[1] - floorf((fSlow309 + fRec69[1]))));
				fRec71[0] = ((iSlow318)?0.0f:min(fSlow317, (fRec71[1] + 1.0f)));
				iTempPerm27 = int((fRec71[0] < fSlow314));
				fRec70[0] = ((iSlow323)?(fSlow322 * ((iTempPerm27)?((int((fRec71[0] < 0.0f)))?0.0f:((iTempPerm27)?(fSlow320 * fRec71[0]):1.0f)):((int((fRec71[0] < fSlow317)))?((fSlow319 * (fRec71[0] - fSlow314)) + 1.0f):fSlow312))):fRec70[1]);
				fRec72[0] = ((iSlow325)?0.0f:min(fSlow324, (fRec72[1] + 1.0f)));
				fRec73[0] = (fSlow328 + (fRec73[1] - floorf((fSlow328 + fRec73[1]))));
				iRec75[0] = (iSlow333 * (iRec75[1] + 1));
				iTempPerm28 = int((iRec75[0] < iSlow332));
				fTempPerm29 = expf((0 - (fConst4 / ((iSlow334)?((iTempPerm28)?fSlow331:fSlow63):fSlow329))));
				fRec74[0] = ((fRec74[1] * fTempPerm29) + (((iSlow334)?((iTempPerm28)?1.5873015873015872f:fSlow335):0.0f) * (1.0f - fTempPerm29)));
				fTempPerm30 = (fSlow336 * (min(1.0f, fRec74[0]) * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow327 * (((int((fRec72[0] < 0.0f)))?fRec70[0]:((int((fRec72[0] < fSlow324)))?(fRec70[0] + (fSlow326 * (0 - (fRec72[0] * fRec70[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec69[0] + (fSlow308 * (((int((fRec68[0] < 0.0f)))?fRec66[0]:((int((fRec68[0] < fSlow305)))?(fRec66[0] + (fSlow307 * (0 - (fRec68[0] * fRec66[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec65[0] + (fSlow289 * (((int((fRec64[0] < 0.0f)))?fRec62[0]:((int((fRec64[0] < fSlow286)))?(fRec62[0] + (fSlow288 * (0 - (fRec64[0] * fRec62[0])))):0.0f)) * ftbl0[(((int((65536.0f * fRec61[0])) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec76[0] = (fSlow347 + (fRec76[1] - floorf((fSlow347 + fRec76[1]))));
				fTempPerm31 = ftbl0[(((int((65536.0f * fRec76[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow337) {
				iRec78[0] = (iSlow353 * (iRec78[1] + 1));
				iTempPerm32 = int((iRec78[0] < iSlow351));
				fTempPerm33 = expf((0 - (fConst4 / ((iSlow354)?((iTempPerm32)?fSlow350:fSlow63):fSlow348))));
				fRec77[0] = ((fRec77[1] * fTempPerm33) + (((iSlow354)?((iTempPerm32)?1.5873015873015872f:fSlow356):0.0f) * (1.0f - fTempPerm33)));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec79[0] = (fSlow358 + (fRec79[1] - floorf((fSlow358 + fRec79[1]))));
			}
			if (iSlow337 || iSlow343 || iSlow339) {
				fTempPerm34 = ftbl0[(((int((65536.0f * fRec79[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				iRec81[0] = (iSlow364 * (iRec81[1] + 1));
				iTempPerm35 = int((iRec81[0] < iSlow362));
				fTempPerm36 = expf((0 - (fConst4 / ((iSlow365)?((iTempPerm35)?fSlow361:fSlow63):fSlow359))));
				fRec80[0] = ((fRec80[1] * fTempPerm36) + (((iSlow365)?((iTempPerm35)?1.5873015873015872f:fSlow367):0.0f) * (1.0f - fTempPerm36)));
				fTempPerm37 = min(1.0f, fRec80[0]);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec82[0] = (fSlow369 + (fRec82[1] - floorf((fSlow369 + fRec82[1]))));
			}
			if (iSlow337 || iSlow346 || iSlow344 || iSlow343) {
				fTempPerm38 = ftbl0[(((int((65536.0f * fRec82[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				iRec84[0] = (iSlow375 * (iRec84[1] + 1));
				iTempPerm39 = int((iRec84[0] < iSlow373));
				fTempPerm40 = expf((0 - (fConst4 / ((iSlow376)?((iTempPerm39)?fSlow372:fSlow63):fSlow370))));
				fRec83[0] = ((fRec83[1] * fTempPerm40) + (((iSlow376)?((iTempPerm39)?1.5873015873015872f:fSlow378):0.0f) * (1.0f - fTempPerm40)));
				fTempPerm41 = min(1.0f, fRec83[0]);
			}
			if (iSlow337 || iSlow346) {
				fTempPerm42 = (fSlow379 * (fTempPerm41 * fTempPerm38));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec85[0] = (fSlow380 + (fRec85[1] - floorf((fSlow380 + fRec85[1]))));
				iRec87[0] = (iSlow385 * (iRec87[1] + 1));
				iTempPerm43 = int((iRec87[0] < iSlow384));
				fTempPerm44 = expf((0 - (fConst4 / ((iSlow386)?((iTempPerm43)?fSlow383:fSlow63):fSlow381))));
				fRec86[0] = ((fRec86[1] * fTempPerm44) + (((iSlow386)?((iTempPerm43)?1.5873015873015872f:fSlow387):0.0f) * (1.0f - fTempPerm44)));
				fTempPerm45 = min(1.0f, fRec86[0]);
			}
			if (iSlow337 || iSlow346 || iSlow342) {
				fTempPerm46 = (fSlow388 * (fTempPerm45 * ftbl0[(((int((65536.0f * fRec85[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337) {
				fTempPerm47 = (((fTempPerm46 + fTempPerm42) + (fSlow368 * (fTempPerm37 * fTempPerm34))) + (fSlow357 * (min(1.0f, fRec77[0]) * fTempPerm31)));
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec89[0] = ((iSlow396)?0.0f:min(fSlow395, (fRec89[1] + 1.0f)));
				iTempPerm48 = int((fRec89[0] < fSlow392));
				fRec88[0] = ((iSlow354)?(fSlow355 * ((iTempPerm48)?((int((fRec89[0] < 0.0f)))?0.0f:((iTempPerm48)?(fSlow398 * fRec89[0]):1.0f)):((int((fRec89[0] < fSlow395)))?((fSlow397 * (fRec89[0] - fSlow392)) + 1.0f):fSlow390))):fRec88[1]);
				fRec90[0] = ((iSlow400)?0.0f:min(fSlow399, (fRec90[1] + 1.0f)));
				fTempPerm49 = (((int((fRec90[0] < 0.0f)))?fRec88[0]:((int((fRec90[0] < fSlow399)))?(fRec88[0] + (fSlow401 * (0 - (fRec90[0] * fRec88[0])))):0.0f)) * fTempPerm31);
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm50 = (fSlow403 * fTempPerm49);
				fTempPerm51 = ftbl0[(((int((65536.0f * (fRec79[0] + fTempPerm50))) % 65536) + 65536) % 65536)];
			}
			if (iSlow346 || iSlow345 || iSlow344) {
				fTempPerm52 = (fSlow368 * (fTempPerm37 * fTempPerm51));
			}
			if (iSlow346) {
				fTempPerm53 = (fTempPerm42 + (fTempPerm46 + fTempPerm52));
			}
			if (iSlow345 || iSlow340) {
				fTempPerm54 = ftbl0[(((int((65536.0f * (fRec82[0] + fTempPerm50))) % 65536) + 65536) % 65536)];
			}
			if (iSlow345) {
				fTempPerm55 = ((fSlow379 * (fTempPerm41 * fTempPerm54)) + (fTempPerm52 + (fSlow388 * (fTempPerm45 * ftbl0[(((int((65536.0f * (fRec85[0] + fTempPerm50))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec92[0] = ((iSlow411)?0.0f:min(fSlow410, (fRec92[1] + 1.0f)));
				iTempPerm56 = int((fRec92[0] < fSlow407));
				fRec91[0] = ((iSlow376)?(fSlow377 * ((iTempPerm56)?((int((fRec92[0] < 0.0f)))?0.0f:((iTempPerm56)?(fSlow413 * fRec92[0]):1.0f)):((int((fRec92[0] < fSlow410)))?((fSlow412 * (fRec92[0] - fSlow407)) + 1.0f):fSlow405))):fRec91[1]);
				fRec93[0] = ((iSlow415)?0.0f:min(fSlow414, (fRec93[1] + 1.0f)));
				fTempPerm57 = ((int((fRec93[0] < 0.0f)))?fRec91[0]:((int((fRec93[0] < fSlow414)))?(fRec91[0] + (fSlow416 * (0 - (fRec93[0] * fRec91[0])))):0.0f));
			}
			if (iSlow344 || iSlow343) {
				fTempPerm58 = (fTempPerm57 * fTempPerm38);
			}
			if (iSlow344) {
				fTempPerm59 = ((fSlow388 * (fTempPerm45 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow418 * fTempPerm58)))) % 65536) + 65536) % 65536)])) + fTempPerm52);
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec95[0] = ((iSlow426)?0.0f:min(fSlow425, (fRec95[1] + 1.0f)));
				iTempPerm60 = int((fRec95[0] < fSlow422));
				fRec94[0] = ((iSlow365)?(fSlow366 * ((iTempPerm60)?((int((fRec95[0] < 0.0f)))?0.0f:((iTempPerm60)?(fSlow428 * fRec95[0]):1.0f)):((int((fRec95[0] < fSlow425)))?((fSlow427 * (fRec95[0] - fSlow422)) + 1.0f):fSlow420))):fRec94[1]);
				fRec96[0] = ((iSlow430)?0.0f:min(fSlow429, (fRec96[1] + 1.0f)));
				fTempPerm61 = ((int((fRec96[0] < 0.0f)))?fRec94[0]:((int((fRec96[0] < fSlow429)))?(fRec94[0] + (fSlow431 * (0 - (fRec96[0] * fRec94[0])))):0.0f));
			}
			if (iSlow343 || iSlow339) {
				fTempPerm62 = (fTempPerm61 * fTempPerm34);
				fTempPerm63 = (fSlow402 * fTempPerm49);
			}
			if (iSlow343) {
				fTempPerm64 = (fSlow388 * (fTempPerm45 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow20 * ((fTempPerm63 + (fSlow432 * fTempPerm62)) + (fSlow417 * fTempPerm58)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm65 = (fTempPerm61 * fTempPerm51);
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm66 = (fSlow433 * fTempPerm65);
				fTempPerm67 = ftbl0[(((int((65536.0f * (fRec82[0] + fTempPerm66))) % 65536) + 65536) % 65536)];
			}
			if (iSlow342 || iSlow341) {
				fTempPerm68 = (fSlow379 * (fTempPerm41 * fTempPerm67));
			}
			if (iSlow342) {
				fTempPerm69 = (fTempPerm68 + fTempPerm46);
			}
			if (iSlow341) {
				fTempPerm70 = ((fSlow388 * (fTempPerm45 * ftbl0[(((int((65536.0f * (fRec85[0] + fTempPerm66))) % 65536) + 65536) % 65536)])) + fTempPerm68);
			}
			if (iSlow340) {
				fTempPerm71 = (fSlow388 * (fTempPerm45 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow20 * ((fSlow432 * fTempPerm65) + (fSlow417 * (fTempPerm57 * fTempPerm54))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow339) {
				fTempPerm72 = (fSlow388 * (fTempPerm45 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow20 * (fTempPerm63 + (fSlow417 * (fTempPerm57 * ftbl0[(((int((65536.0f * (fRec82[0] + (fSlow433 * fTempPerm62)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow338) {
				fTempPerm73 = (fSlow388 * (fTempPerm45 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow418 * (fTempPerm57 * fTempPerm67))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow1) {
				fRec97[0] = (fSlow434 + (fRec97[1] - floorf((fSlow434 + fRec97[1]))));
				fRec99[0] = ((iSlow443)?0.0f:min(fSlow442, (fRec99[1] + 1.0f)));
				iTempPerm74 = int((fRec99[0] < fSlow439));
				fRec98[0] = ((iSlow448)?(fSlow447 * ((iTempPerm74)?((int((fRec99[0] < 0.0f)))?0.0f:((iTempPerm74)?(fSlow445 * fRec99[0]):1.0f)):((int((fRec99[0] < fSlow442)))?((fSlow444 * (fRec99[0] - fSlow439)) + 1.0f):fSlow437))):fRec98[1]);
				fRec100[0] = ((iSlow450)?0.0f:min(fSlow449, (fRec100[1] + 1.0f)));
				fRec101[0] = (fSlow453 + (fRec101[1] - floorf((fSlow453 + fRec101[1]))));
				fRec103[0] = ((iSlow462)?0.0f:min(fSlow461, (fRec103[1] + 1.0f)));
				iTempPerm75 = int((fRec103[0] < fSlow458));
				fRec102[0] = ((iSlow467)?(fSlow466 * ((iTempPerm75)?((int((fRec103[0] < 0.0f)))?0.0f:((iTempPerm75)?(fSlow464 * fRec103[0]):1.0f)):((int((fRec103[0] < fSlow461)))?((fSlow463 * (fRec103[0] - fSlow458)) + 1.0f):fSlow456))):fRec102[1]);
				fRec104[0] = ((iSlow469)?0.0f:min(fSlow468, (fRec104[1] + 1.0f)));
				fRec105[0] = (fSlow472 + (fRec105[1] - floorf((fSlow472 + fRec105[1]))));
				fRec107[0] = ((iSlow481)?0.0f:min(fSlow480, (fRec107[1] + 1.0f)));
				iTempPerm76 = int((fRec107[0] < fSlow477));
				fRec106[0] = ((iSlow486)?(fSlow485 * ((iTempPerm76)?((int((fRec107[0] < 0.0f)))?0.0f:((iTempPerm76)?(fSlow483 * fRec107[0]):1.0f)):((int((fRec107[0] < fSlow480)))?((fSlow482 * (fRec107[0] - fSlow477)) + 1.0f):fSlow475))):fRec106[1]);
				fRec108[0] = ((iSlow488)?0.0f:min(fSlow487, (fRec108[1] + 1.0f)));
				fRec109[0] = (fSlow491 + (fRec109[1] - floorf((fSlow491 + fRec109[1]))));
				iRec111[0] = (iSlow496 * (iRec111[1] + 1));
				iTempPerm77 = int((iRec111[0] < iSlow495));
				fTempPerm78 = expf((0 - (fConst4 / ((iSlow497)?((iTempPerm77)?fSlow494:fSlow63):fSlow492))));
				fRec110[0] = ((fRec110[1] * fTempPerm78) + (((iSlow497)?((iTempPerm77)?1.5873015873015872f:fSlow498):0.0f) * (1.0f - fTempPerm78)));
				fTempPerm79 = (fSlow499 * (min(1.0f, fRec110[0]) * ftbl0[(((int((65536.0f * (fRec109[0] + (fSlow490 * (((int((fRec108[0] < 0.0f)))?fRec106[0]:((int((fRec108[0] < fSlow487)))?(fRec106[0] + (fSlow489 * (0 - (fRec108[0] * fRec106[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec105[0] + (fSlow471 * (((int((fRec104[0] < 0.0f)))?fRec102[0]:((int((fRec104[0] < fSlow468)))?(fRec102[0] + (fSlow470 * (0 - (fRec104[0] * fRec102[0])))):0.0f)) * ftbl0[(((int((65536.0f * (fRec101[0] + (fSlow452 * (((int((fRec100[0] < 0.0f)))?fRec98[0]:((int((fRec100[0] < fSlow449)))?(fRec98[0] + (fSlow451 * (0 - (fRec100[0] * fRec98[0])))):0.0f)) * ftbl0[(((int((65536.0f * fRec97[0])) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec112[0] = (fSlow500 + (fRec112[1] - floorf((fSlow500 + fRec112[1]))));
				fTempPerm80 = ftbl0[(((int((65536.0f * fRec112[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec114[0] = ((iSlow509)?0.0f:min(fSlow508, (fRec114[1] + 1.0f)));
				iTempPerm81 = int((fRec114[0] < fSlow505));
				fRec113[0] = ((iSlow514)?(fSlow513 * ((iTempPerm81)?((int((fRec114[0] < 0.0f)))?0.0f:((iTempPerm81)?(fSlow511 * fRec114[0]):1.0f)):((int((fRec114[0] < fSlow508)))?((fSlow510 * (fRec114[0] - fSlow505)) + 1.0f):fSlow503))):fRec113[1]);
				fRec115[0] = ((iSlow516)?0.0f:min(fSlow515, (fRec115[1] + 1.0f)));
				fTempPerm82 = (((int((fRec115[0] < 0.0f)))?fRec113[0]:((int((fRec115[0] < fSlow515)))?(fRec113[0] + (fSlow517 * (0 - (fRec115[0] * fRec113[0])))):0.0f)) * fTempPerm80);
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm83 = (fSlow519 * fTempPerm82);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec116[0] = (fSlow520 + (fRec116[1] - floorf((fSlow520 + fRec116[1]))));
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm84 = ftbl0[(((int((65536.0f * (fRec116[0] + fTempPerm83))) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec118[0] = ((iSlow529)?0.0f:min(fSlow528, (fRec118[1] + 1.0f)));
				iTempPerm85 = int((fRec118[0] < fSlow525));
				fRec117[0] = ((iSlow534)?(fSlow533 * ((iTempPerm85)?((int((fRec118[0] < 0.0f)))?0.0f:((iTempPerm85)?(fSlow531 * fRec118[0]):1.0f)):((int((fRec118[0] < fSlow528)))?((fSlow530 * (fRec118[0] - fSlow525)) + 1.0f):fSlow523))):fRec117[1]);
				fRec119[0] = ((iSlow536)?0.0f:min(fSlow535, (fRec119[1] + 1.0f)));
				fTempPerm86 = ((int((fRec119[0] < 0.0f)))?fRec117[0]:((int((fRec119[0] < fSlow535)))?(fRec117[0] + (fSlow537 * (0 - (fRec119[0] * fRec117[0])))):0.0f));
			}
			if (iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm87 = (fTempPerm86 * fTempPerm84);
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm88 = (fSlow539 * fTempPerm87);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec120[0] = (fSlow540 + (fRec120[1] - floorf((fSlow540 + fRec120[1]))));
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm89 = ftbl0[(((int((65536.0f * (fRec120[0] + fTempPerm88))) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec122[0] = ((iSlow549)?0.0f:min(fSlow548, (fRec122[1] + 1.0f)));
				iTempPerm90 = int((fRec122[0] < fSlow545));
				fRec121[0] = ((iSlow554)?(fSlow553 * ((iTempPerm90)?((int((fRec122[0] < 0.0f)))?0.0f:((iTempPerm90)?(fSlow551 * fRec122[0]):1.0f)):((int((fRec122[0] < fSlow548)))?((fSlow550 * (fRec122[0] - fSlow545)) + 1.0f):fSlow543))):fRec121[1]);
				fRec123[0] = ((iSlow556)?0.0f:min(fSlow555, (fRec123[1] + 1.0f)));
				fTempPerm91 = ((int((fRec123[0] < 0.0f)))?fRec121[0]:((int((fRec123[0] < fSlow555)))?(fRec121[0] + (fSlow557 * (0 - (fRec123[0] * fRec121[0])))):0.0f));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec124[0] = (fSlow560 + (fRec124[1] - floorf((fSlow560 + fRec124[1]))));
				iRec126[0] = (iSlow565 * (iRec126[1] + 1));
				iTempPerm92 = int((iRec126[0] < iSlow564));
				fTempPerm93 = expf((0 - (fConst4 / ((iSlow566)?((iTempPerm92)?fSlow563:fSlow63):fSlow561))));
				fRec125[0] = ((fRec125[1] * fTempPerm93) + (((iSlow566)?((iTempPerm92)?1.5873015873015872f:fSlow567):0.0f) * (1.0f - fTempPerm93)));
				fTempPerm94 = min(1.0f, fRec125[0]);
			}
			if (iSlow338) {
				fTempPerm95 = (fSlow568 * (fTempPerm94 * ftbl0[(((int((65536.0f * (fRec124[0] + (fSlow559 * (fTempPerm91 * fTempPerm89))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow343 || iSlow339) {
				fTempPerm96 = ftbl0[(((int((65536.0f * fRec116[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow339) {
				fTempPerm97 = (fTempPerm86 * fTempPerm96);
				fTempPerm98 = (fSlow518 * fTempPerm82);
			}
			if (iSlow339) {
				fTempPerm99 = (fSlow568 * (fTempPerm94 * ftbl0[(((int((65536.0f * (fRec124[0] + (fSlow20 * (fTempPerm98 + (fSlow558 * (fTempPerm91 * ftbl0[(((int((65536.0f * (fRec120[0] + (fSlow539 * fTempPerm97)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow345 || iSlow340) {
				fTempPerm100 = ftbl0[(((int((65536.0f * (fRec120[0] + fTempPerm83))) % 65536) + 65536) % 65536)];
			}
			if (iSlow340) {
				fTempPerm101 = (fSlow568 * (fTempPerm94 * ftbl0[(((int((65536.0f * (fRec124[0] + (fSlow20 * ((fSlow538 * fTempPerm87) + (fSlow558 * (fTempPerm91 * fTempPerm100))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				iRec128[0] = (iSlow552 * (iRec128[1] + 1));
				iTempPerm102 = int((iRec128[0] < iSlow572));
				fTempPerm103 = expf((0 - (fConst4 / ((iSlow554)?((iTempPerm102)?fSlow571:fSlow63):fSlow569))));
				fRec127[0] = ((fRec127[1] * fTempPerm103) + (((iSlow554)?((iTempPerm102)?1.5873015873015872f:fSlow573):0.0f) * (1.0f - fTempPerm103)));
				fTempPerm104 = min(1.0f, fRec127[0]);
			}
			if (iSlow342 || iSlow341) {
				fTempPerm105 = (fSlow574 * (fTempPerm104 * fTempPerm89));
			}
			if (iSlow341) {
				fTempPerm106 = ((fSlow568 * (fTempPerm94 * ftbl0[(((int((65536.0f * (fRec124[0] + fTempPerm88))) % 65536) + 65536) % 65536)])) + fTempPerm105);
			}
			if (iSlow337 || iSlow346 || iSlow342) {
				fTempPerm107 = (fSlow568 * (fTempPerm94 * ftbl0[(((int((65536.0f * fRec124[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow342) {
				fTempPerm108 = (fTempPerm105 + fTempPerm107);
			}
			if (iSlow337 || iSlow346 || iSlow344 || iSlow343) {
				fTempPerm109 = ftbl0[(((int((65536.0f * fRec120[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343) {
				fTempPerm110 = (fTempPerm91 * fTempPerm109);
			}
			if (iSlow343) {
				fTempPerm111 = (fSlow568 * (fTempPerm94 * ftbl0[(((int((65536.0f * (fRec124[0] + (fSlow20 * ((fTempPerm98 + (fSlow538 * fTempPerm97)) + (fSlow558 * fTempPerm110)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				iRec130[0] = (iSlow532 * (iRec130[1] + 1));
				iTempPerm112 = int((iRec130[0] < iSlow578));
				fTempPerm113 = expf((0 - (fConst4 / ((iSlow534)?((iTempPerm112)?fSlow577:fSlow63):fSlow575))));
				fRec129[0] = ((fRec129[1] * fTempPerm113) + (((iSlow534)?((iTempPerm112)?1.5873015873015872f:fSlow579):0.0f) * (1.0f - fTempPerm113)));
				fTempPerm114 = min(1.0f, fRec129[0]);
			}
			if (iSlow346 || iSlow345 || iSlow344) {
				fTempPerm115 = (fSlow580 * (fTempPerm114 * fTempPerm84));
			}
			if (iSlow344) {
				fTempPerm116 = ((fSlow568 * (fTempPerm94 * ftbl0[(((int((65536.0f * (fRec124[0] + (fSlow559 * fTempPerm110)))) % 65536) + 65536) % 65536)])) + fTempPerm115);
			}
			if (iSlow345) {
				fTempPerm117 = ((fSlow574 * (fTempPerm104 * fTempPerm100)) + (fTempPerm115 + (fSlow568 * (fTempPerm94 * ftbl0[(((int((65536.0f * (fRec124[0] + fTempPerm83))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow337 || iSlow346) {
				fTempPerm118 = (fSlow574 * (fTempPerm104 * fTempPerm109));
			}
			if (iSlow346) {
				fTempPerm119 = (fTempPerm118 + (fTempPerm107 + fTempPerm115));
			}
			if (iSlow337) {
				iRec132[0] = (iSlow512 * (iRec132[1] + 1));
				iTempPerm120 = int((iRec132[0] < iSlow584));
				fTempPerm121 = expf((0 - (fConst4 / ((iSlow514)?((iTempPerm120)?fSlow583:fSlow63):fSlow581))));
				fRec131[0] = ((fRec131[1] * fTempPerm121) + (((iSlow514)?((iTempPerm120)?1.5873015873015872f:fSlow585):0.0f) * (1.0f - fTempPerm121)));
				fTempPerm122 = (((fTempPerm107 + fTempPerm118) + (fSlow580 * (fTempPerm114 * fTempPerm96))) + (fSlow586 * (min(1.0f, fRec131[0]) * fTempPerm80)));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec133[0] = (fSlow587 + (fRec133[1] - floorf((fSlow587 + fRec133[1]))));
				fTempPerm123 = ftbl0[(((int((65536.0f * fRec133[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec135[0] = ((iSlow596)?0.0f:min(fSlow595, (fRec135[1] + 1.0f)));
				iTempPerm124 = int((fRec135[0] < fSlow592));
				fRec134[0] = ((iSlow601)?(fSlow600 * ((iTempPerm124)?((int((fRec135[0] < 0.0f)))?0.0f:((iTempPerm124)?(fSlow598 * fRec135[0]):1.0f)):((int((fRec135[0] < fSlow595)))?((fSlow597 * (fRec135[0] - fSlow592)) + 1.0f):fSlow590))):fRec134[1]);
				fRec136[0] = ((iSlow603)?0.0f:min(fSlow602, (fRec136[1] + 1.0f)));
				fTempPerm125 = (((int((fRec136[0] < 0.0f)))?fRec134[0]:((int((fRec136[0] < fSlow602)))?(fRec134[0] + (fSlow604 * (0 - (fRec136[0] * fRec134[0])))):0.0f)) * fTempPerm123);
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm126 = (fSlow606 * fTempPerm125);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec137[0] = (fSlow607 + (fRec137[1] - floorf((fSlow607 + fRec137[1]))));
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm127 = ftbl0[(((int((65536.0f * (fRec137[0] + fTempPerm126))) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec139[0] = ((iSlow616)?0.0f:min(fSlow615, (fRec139[1] + 1.0f)));
				iTempPerm128 = int((fRec139[0] < fSlow612));
				fRec138[0] = ((iSlow621)?(fSlow620 * ((iTempPerm128)?((int((fRec139[0] < 0.0f)))?0.0f:((iTempPerm128)?(fSlow618 * fRec139[0]):1.0f)):((int((fRec139[0] < fSlow615)))?((fSlow617 * (fRec139[0] - fSlow612)) + 1.0f):fSlow610))):fRec138[1]);
				fRec140[0] = ((iSlow623)?0.0f:min(fSlow622, (fRec140[1] + 1.0f)));
				fTempPerm129 = ((int((fRec140[0] < 0.0f)))?fRec138[0]:((int((fRec140[0] < fSlow622)))?(fRec138[0] + (fSlow624 * (0 - (fRec140[0] * fRec138[0])))):0.0f));
			}
			if (iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm130 = (fTempPerm129 * fTempPerm127);
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm131 = (fSlow626 * fTempPerm130);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec141[0] = (fSlow627 + (fRec141[1] - floorf((fSlow627 + fRec141[1]))));
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm132 = ftbl0[(((int((65536.0f * (fRec141[0] + fTempPerm131))) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec143[0] = ((iSlow636)?0.0f:min(fSlow635, (fRec143[1] + 1.0f)));
				iTempPerm133 = int((fRec143[0] < fSlow632));
				fRec142[0] = ((iSlow641)?(fSlow640 * ((iTempPerm133)?((int((fRec143[0] < 0.0f)))?0.0f:((iTempPerm133)?(fSlow638 * fRec143[0]):1.0f)):((int((fRec143[0] < fSlow635)))?((fSlow637 * (fRec143[0] - fSlow632)) + 1.0f):fSlow630))):fRec142[1]);
				fRec144[0] = ((iSlow643)?0.0f:min(fSlow642, (fRec144[1] + 1.0f)));
				fTempPerm134 = ((int((fRec144[0] < 0.0f)))?fRec142[0]:((int((fRec144[0] < fSlow642)))?(fRec142[0] + (fSlow644 * (0 - (fRec144[0] * fRec142[0])))):0.0f));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec145[0] = (fSlow647 + (fRec145[1] - floorf((fSlow647 + fRec145[1]))));
				iRec147[0] = (iSlow652 * (iRec147[1] + 1));
				iTempPerm135 = int((iRec147[0] < iSlow651));
				fTempPerm136 = expf((0 - (fConst4 / ((iSlow653)?((iTempPerm135)?fSlow650:fSlow63):fSlow648))));
				fRec146[0] = ((fRec146[1] * fTempPerm136) + (((iSlow653)?((iTempPerm135)?1.5873015873015872f:fSlow654):0.0f) * (1.0f - fTempPerm136)));
				fTempPerm137 = min(1.0f, fRec146[0]);
			}
			if (iSlow338) {
				fTempPerm138 = (fSlow655 * (fTempPerm137 * ftbl0[(((int((65536.0f * (fRec145[0] + (fSlow646 * (fTempPerm134 * fTempPerm132))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow343 || iSlow339) {
				fTempPerm139 = ftbl0[(((int((65536.0f * fRec137[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow339) {
				fTempPerm140 = (fTempPerm129 * fTempPerm139);
				fTempPerm141 = (fSlow605 * fTempPerm125);
			}
			if (iSlow339) {
				fTempPerm142 = (fSlow655 * (fTempPerm137 * ftbl0[(((int((65536.0f * (fRec145[0] + (fSlow20 * (fTempPerm141 + (fSlow645 * (fTempPerm134 * ftbl0[(((int((65536.0f * (fRec141[0] + (fSlow626 * fTempPerm140)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow345 || iSlow340) {
				fTempPerm143 = ftbl0[(((int((65536.0f * (fRec141[0] + fTempPerm126))) % 65536) + 65536) % 65536)];
			}
			if (iSlow340) {
				fTempPerm144 = (fSlow655 * (fTempPerm137 * ftbl0[(((int((65536.0f * (fRec145[0] + (fSlow20 * ((fSlow625 * fTempPerm130) + (fSlow645 * (fTempPerm134 * fTempPerm143))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				iRec149[0] = (iSlow639 * (iRec149[1] + 1));
				iTempPerm145 = int((iRec149[0] < iSlow659));
				fTempPerm146 = expf((0 - (fConst4 / ((iSlow641)?((iTempPerm145)?fSlow658:fSlow63):fSlow656))));
				fRec148[0] = ((fRec148[1] * fTempPerm146) + (((iSlow641)?((iTempPerm145)?1.5873015873015872f:fSlow660):0.0f) * (1.0f - fTempPerm146)));
				fTempPerm147 = min(1.0f, fRec148[0]);
			}
			if (iSlow342 || iSlow341) {
				fTempPerm148 = (fSlow661 * (fTempPerm147 * fTempPerm132));
			}
			if (iSlow341) {
				fTempPerm149 = ((fSlow655 * (fTempPerm137 * ftbl0[(((int((65536.0f * (fRec145[0] + fTempPerm131))) % 65536) + 65536) % 65536)])) + fTempPerm148);
			}
			if (iSlow337 || iSlow346 || iSlow342) {
				fTempPerm150 = (fSlow655 * (fTempPerm137 * ftbl0[(((int((65536.0f * fRec145[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow342) {
				fTempPerm151 = (fTempPerm148 + fTempPerm150);
			}
			if (iSlow337 || iSlow346 || iSlow344 || iSlow343) {
				fTempPerm152 = ftbl0[(((int((65536.0f * fRec141[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343) {
				fTempPerm153 = (fTempPerm134 * fTempPerm152);
			}
			if (iSlow343) {
				fTempPerm154 = (fSlow655 * (fTempPerm137 * ftbl0[(((int((65536.0f * (fRec145[0] + (fSlow20 * ((fTempPerm141 + (fSlow625 * fTempPerm140)) + (fSlow645 * fTempPerm153)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				iRec151[0] = (iSlow619 * (iRec151[1] + 1));
				iTempPerm155 = int((iRec151[0] < iSlow665));
				fTempPerm156 = expf((0 - (fConst4 / ((iSlow621)?((iTempPerm155)?fSlow664:fSlow63):fSlow662))));
				fRec150[0] = ((fRec150[1] * fTempPerm156) + (((iSlow621)?((iTempPerm155)?1.5873015873015872f:fSlow666):0.0f) * (1.0f - fTempPerm156)));
				fTempPerm157 = min(1.0f, fRec150[0]);
			}
			if (iSlow346 || iSlow345 || iSlow344) {
				fTempPerm158 = (fSlow667 * (fTempPerm157 * fTempPerm127));
			}
			if (iSlow344) {
				fTempPerm159 = ((fSlow655 * (fTempPerm137 * ftbl0[(((int((65536.0f * (fRec145[0] + (fSlow646 * fTempPerm153)))) % 65536) + 65536) % 65536)])) + fTempPerm158);
			}
			if (iSlow345) {
				fTempPerm160 = ((fSlow661 * (fTempPerm147 * fTempPerm143)) + (fTempPerm158 + (fSlow655 * (fTempPerm137 * ftbl0[(((int((65536.0f * (fRec145[0] + fTempPerm126))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow337 || iSlow346) {
				fTempPerm161 = (fSlow661 * (fTempPerm147 * fTempPerm152));
			}
			if (iSlow346) {
				fTempPerm162 = (fTempPerm161 + (fTempPerm150 + fTempPerm158));
			}
			if (iSlow337) {
				iRec153[0] = (iSlow599 * (iRec153[1] + 1));
				iTempPerm163 = int((iRec153[0] < iSlow671));
				fTempPerm164 = expf((0 - (fConst4 / ((iSlow601)?((iTempPerm163)?fSlow670:fSlow63):fSlow668))));
				fRec152[0] = ((fRec152[1] * fTempPerm164) + (((iSlow601)?((iTempPerm163)?1.5873015873015872f:fSlow672):0.0f) * (1.0f - fTempPerm164)));
				fTempPerm165 = (((fTempPerm150 + fTempPerm161) + (fSlow667 * (fTempPerm157 * fTempPerm139))) + (fSlow673 * (min(1.0f, fRec152[0]) * fTempPerm123)));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec154[0] = (fSlow674 + (fRec154[1] - floorf((fSlow674 + fRec154[1]))));
				fTempPerm166 = ftbl0[(((int((65536.0f * fRec154[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec156[0] = ((iSlow683)?0.0f:min(fSlow682, (fRec156[1] + 1.0f)));
				iTempPerm167 = int((fRec156[0] < fSlow679));
				fRec155[0] = ((iSlow688)?(fSlow687 * ((iTempPerm167)?((int((fRec156[0] < 0.0f)))?0.0f:((iTempPerm167)?(fSlow685 * fRec156[0]):1.0f)):((int((fRec156[0] < fSlow682)))?((fSlow684 * (fRec156[0] - fSlow679)) + 1.0f):fSlow677))):fRec155[1]);
				fRec157[0] = ((iSlow690)?0.0f:min(fSlow689, (fRec157[1] + 1.0f)));
				fTempPerm168 = (((int((fRec157[0] < 0.0f)))?fRec155[0]:((int((fRec157[0] < fSlow689)))?(fRec155[0] + (fSlow691 * (0 - (fRec157[0] * fRec155[0])))):0.0f)) * fTempPerm166);
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm169 = (fSlow693 * fTempPerm168);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec158[0] = (fSlow694 + (fRec158[1] - floorf((fSlow694 + fRec158[1]))));
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm170 = ftbl0[(((int((65536.0f * (fRec158[0] + fTempPerm169))) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec160[0] = ((iSlow703)?0.0f:min(fSlow702, (fRec160[1] + 1.0f)));
				iTempPerm171 = int((fRec160[0] < fSlow699));
				fRec159[0] = ((iSlow708)?(fSlow707 * ((iTempPerm171)?((int((fRec160[0] < 0.0f)))?0.0f:((iTempPerm171)?(fSlow705 * fRec160[0]):1.0f)):((int((fRec160[0] < fSlow702)))?((fSlow704 * (fRec160[0] - fSlow699)) + 1.0f):fSlow697))):fRec159[1]);
				fRec161[0] = ((iSlow710)?0.0f:min(fSlow709, (fRec161[1] + 1.0f)));
				fTempPerm172 = ((int((fRec161[0] < 0.0f)))?fRec159[0]:((int((fRec161[0] < fSlow709)))?(fRec159[0] + (fSlow711 * (0 - (fRec161[0] * fRec159[0])))):0.0f));
			}
			if (iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm173 = (fTempPerm172 * fTempPerm170);
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm174 = (fSlow713 * fTempPerm173);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec162[0] = (fSlow714 + (fRec162[1] - floorf((fSlow714 + fRec162[1]))));
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm175 = ftbl0[(((int((65536.0f * (fRec162[0] + fTempPerm174))) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec164[0] = ((iSlow723)?0.0f:min(fSlow722, (fRec164[1] + 1.0f)));
				iTempPerm176 = int((fRec164[0] < fSlow719));
				fRec163[0] = ((iSlow728)?(fSlow727 * ((iTempPerm176)?((int((fRec164[0] < 0.0f)))?0.0f:((iTempPerm176)?(fSlow725 * fRec164[0]):1.0f)):((int((fRec164[0] < fSlow722)))?((fSlow724 * (fRec164[0] - fSlow719)) + 1.0f):fSlow717))):fRec163[1]);
				fRec165[0] = ((iSlow730)?0.0f:min(fSlow729, (fRec165[1] + 1.0f)));
				fTempPerm177 = ((int((fRec165[0] < 0.0f)))?fRec163[0]:((int((fRec165[0] < fSlow729)))?(fRec163[0] + (fSlow731 * (0 - (fRec165[0] * fRec163[0])))):0.0f));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec166[0] = (fSlow734 + (fRec166[1] - floorf((fSlow734 + fRec166[1]))));
				iRec168[0] = (iSlow739 * (iRec168[1] + 1));
				iTempPerm178 = int((iRec168[0] < iSlow738));
				fTempPerm179 = expf((0 - (fConst4 / ((iSlow740)?((iTempPerm178)?fSlow737:fSlow63):fSlow735))));
				fRec167[0] = ((fRec167[1] * fTempPerm179) + (((iSlow740)?((iTempPerm178)?1.5873015873015872f:fSlow741):0.0f) * (1.0f - fTempPerm179)));
				fTempPerm180 = min(1.0f, fRec167[0]);
			}
			if (iSlow338) {
				fTempPerm181 = (fSlow742 * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec166[0] + (fSlow733 * (fTempPerm177 * fTempPerm175))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow343 || iSlow339) {
				fTempPerm182 = ftbl0[(((int((65536.0f * fRec158[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow339) {
				fTempPerm183 = (fTempPerm172 * fTempPerm182);
				fTempPerm184 = (fSlow692 * fTempPerm168);
			}
			if (iSlow339) {
				fTempPerm185 = (fSlow742 * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec166[0] + (fSlow20 * (fTempPerm184 + (fSlow732 * (fTempPerm177 * ftbl0[(((int((65536.0f * (fRec162[0] + (fSlow713 * fTempPerm183)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow345 || iSlow340) {
				fTempPerm186 = ftbl0[(((int((65536.0f * (fRec162[0] + fTempPerm169))) % 65536) + 65536) % 65536)];
			}
			if (iSlow340) {
				fTempPerm187 = (fSlow742 * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec166[0] + (fSlow20 * ((fSlow712 * fTempPerm173) + (fSlow732 * (fTempPerm177 * fTempPerm186))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				iRec170[0] = (iSlow726 * (iRec170[1] + 1));
				iTempPerm188 = int((iRec170[0] < iSlow746));
				fTempPerm189 = expf((0 - (fConst4 / ((iSlow728)?((iTempPerm188)?fSlow745:fSlow63):fSlow743))));
				fRec169[0] = ((fRec169[1] * fTempPerm189) + (((iSlow728)?((iTempPerm188)?1.5873015873015872f:fSlow747):0.0f) * (1.0f - fTempPerm189)));
				fTempPerm190 = min(1.0f, fRec169[0]);
			}
			if (iSlow342 || iSlow341) {
				fTempPerm191 = (fSlow748 * (fTempPerm190 * fTempPerm175));
			}
			if (iSlow341) {
				fTempPerm192 = ((fSlow742 * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec166[0] + fTempPerm174))) % 65536) + 65536) % 65536)])) + fTempPerm191);
			}
			if (iSlow337 || iSlow346 || iSlow342) {
				fTempPerm193 = (fSlow742 * (fTempPerm180 * ftbl0[(((int((65536.0f * fRec166[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow342) {
				fTempPerm194 = (fTempPerm191 + fTempPerm193);
			}
			if (iSlow337 || iSlow346 || iSlow344 || iSlow343) {
				fTempPerm195 = ftbl0[(((int((65536.0f * fRec162[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343) {
				fTempPerm196 = (fTempPerm177 * fTempPerm195);
			}
			if (iSlow343) {
				fTempPerm197 = (fSlow742 * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec166[0] + (fSlow20 * ((fTempPerm184 + (fSlow712 * fTempPerm183)) + (fSlow732 * fTempPerm196)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				iRec172[0] = (iSlow706 * (iRec172[1] + 1));
				iTempPerm198 = int((iRec172[0] < iSlow752));
				fTempPerm199 = expf((0 - (fConst4 / ((iSlow708)?((iTempPerm198)?fSlow751:fSlow63):fSlow749))));
				fRec171[0] = ((fRec171[1] * fTempPerm199) + (((iSlow708)?((iTempPerm198)?1.5873015873015872f:fSlow753):0.0f) * (1.0f - fTempPerm199)));
				fTempPerm200 = min(1.0f, fRec171[0]);
			}
			if (iSlow346 || iSlow345 || iSlow344) {
				fTempPerm201 = (fSlow754 * (fTempPerm200 * fTempPerm170));
			}
			if (iSlow344) {
				fTempPerm202 = ((fSlow742 * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec166[0] + (fSlow733 * fTempPerm196)))) % 65536) + 65536) % 65536)])) + fTempPerm201);
			}
			if (iSlow345) {
				fTempPerm203 = ((fSlow748 * (fTempPerm190 * fTempPerm186)) + (fTempPerm201 + (fSlow742 * (fTempPerm180 * ftbl0[(((int((65536.0f * (fRec166[0] + fTempPerm169))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow337 || iSlow346) {
				fTempPerm204 = (fSlow748 * (fTempPerm190 * fTempPerm195));
			}
			if (iSlow346) {
				fTempPerm205 = (fTempPerm204 + (fTempPerm193 + fTempPerm201));
			}
			if (iSlow337) {
				iRec174[0] = (iSlow686 * (iRec174[1] + 1));
				iTempPerm206 = int((iRec174[0] < iSlow758));
				fTempPerm207 = expf((0 - (fConst4 / ((iSlow688)?((iTempPerm206)?fSlow757:fSlow63):fSlow755))));
				fRec173[0] = ((fRec173[1] * fTempPerm207) + (((iSlow688)?((iTempPerm206)?1.5873015873015872f:fSlow759):0.0f) * (1.0f - fTempPerm207)));
				fTempPerm208 = (((fTempPerm193 + fTempPerm204) + (fSlow754 * (fTempPerm200 * fTempPerm182))) + (fSlow760 * (min(1.0f, fRec173[0]) * fTempPerm166)));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec175[0] = (fSlow761 + (fRec175[1] - floorf((fSlow761 + fRec175[1]))));
				fTempPerm209 = ftbl0[(((int((65536.0f * fRec175[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec177[0] = ((iSlow770)?0.0f:min(fSlow769, (fRec177[1] + 1.0f)));
				iTempPerm210 = int((fRec177[0] < fSlow766));
				fRec176[0] = ((iSlow775)?(fSlow774 * ((iTempPerm210)?((int((fRec177[0] < 0.0f)))?0.0f:((iTempPerm210)?(fSlow772 * fRec177[0]):1.0f)):((int((fRec177[0] < fSlow769)))?((fSlow771 * (fRec177[0] - fSlow766)) + 1.0f):fSlow764))):fRec176[1]);
				fRec178[0] = ((iSlow777)?0.0f:min(fSlow776, (fRec178[1] + 1.0f)));
				fTempPerm211 = (((int((fRec178[0] < 0.0f)))?fRec176[0]:((int((fRec178[0] < fSlow776)))?(fRec176[0] + (fSlow778 * (0 - (fRec178[0] * fRec176[0])))):0.0f)) * fTempPerm209);
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm212 = (fSlow780 * fTempPerm211);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec179[0] = (fSlow781 + (fRec179[1] - floorf((fSlow781 + fRec179[1]))));
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm213 = ftbl0[(((int((65536.0f * (fRec179[0] + fTempPerm212))) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec181[0] = ((iSlow790)?0.0f:min(fSlow789, (fRec181[1] + 1.0f)));
				iTempPerm214 = int((fRec181[0] < fSlow786));
				fRec180[0] = ((iSlow795)?(fSlow794 * ((iTempPerm214)?((int((fRec181[0] < 0.0f)))?0.0f:((iTempPerm214)?(fSlow792 * fRec181[0]):1.0f)):((int((fRec181[0] < fSlow789)))?((fSlow791 * (fRec181[0] - fSlow786)) + 1.0f):fSlow784))):fRec180[1]);
				fRec182[0] = ((iSlow797)?0.0f:min(fSlow796, (fRec182[1] + 1.0f)));
				fTempPerm215 = ((int((fRec182[0] < 0.0f)))?fRec180[0]:((int((fRec182[0] < fSlow796)))?(fRec180[0] + (fSlow798 * (0 - (fRec182[0] * fRec180[0])))):0.0f));
			}
			if (iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm216 = (fTempPerm215 * fTempPerm213);
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm217 = (fSlow800 * fTempPerm216);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec183[0] = (fSlow801 + (fRec183[1] - floorf((fSlow801 + fRec183[1]))));
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm218 = ftbl0[(((int((65536.0f * (fRec183[0] + fTempPerm217))) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec185[0] = ((iSlow810)?0.0f:min(fSlow809, (fRec185[1] + 1.0f)));
				iTempPerm219 = int((fRec185[0] < fSlow806));
				fRec184[0] = ((iSlow815)?(fSlow814 * ((iTempPerm219)?((int((fRec185[0] < 0.0f)))?0.0f:((iTempPerm219)?(fSlow812 * fRec185[0]):1.0f)):((int((fRec185[0] < fSlow809)))?((fSlow811 * (fRec185[0] - fSlow806)) + 1.0f):fSlow804))):fRec184[1]);
				fRec186[0] = ((iSlow817)?0.0f:min(fSlow816, (fRec186[1] + 1.0f)));
				fTempPerm220 = ((int((fRec186[0] < 0.0f)))?fRec184[0]:((int((fRec186[0] < fSlow816)))?(fRec184[0] + (fSlow818 * (0 - (fRec186[0] * fRec184[0])))):0.0f));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec187[0] = (fSlow821 + (fRec187[1] - floorf((fSlow821 + fRec187[1]))));
				iRec189[0] = (iSlow826 * (iRec189[1] + 1));
				iTempPerm221 = int((iRec189[0] < iSlow825));
				fTempPerm222 = expf((0 - (fConst4 / ((iSlow827)?((iTempPerm221)?fSlow824:fSlow63):fSlow822))));
				fRec188[0] = ((fRec188[1] * fTempPerm222) + (((iSlow827)?((iTempPerm221)?1.5873015873015872f:fSlow828):0.0f) * (1.0f - fTempPerm222)));
				fTempPerm223 = min(1.0f, fRec188[0]);
			}
			if (iSlow338) {
				fTempPerm224 = (fSlow829 * (fTempPerm223 * ftbl0[(((int((65536.0f * (fRec187[0] + (fSlow820 * (fTempPerm220 * fTempPerm218))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow343 || iSlow339) {
				fTempPerm225 = ftbl0[(((int((65536.0f * fRec179[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow339) {
				fTempPerm226 = (fTempPerm215 * fTempPerm225);
				fTempPerm227 = (fSlow779 * fTempPerm211);
			}
			if (iSlow339) {
				fTempPerm228 = (fSlow829 * (fTempPerm223 * ftbl0[(((int((65536.0f * (fRec187[0] + (fSlow20 * (fTempPerm227 + (fSlow819 * (fTempPerm220 * ftbl0[(((int((65536.0f * (fRec183[0] + (fSlow800 * fTempPerm226)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow345 || iSlow340) {
				fTempPerm229 = ftbl0[(((int((65536.0f * (fRec183[0] + fTempPerm212))) % 65536) + 65536) % 65536)];
			}
			if (iSlow340) {
				fTempPerm230 = (fSlow829 * (fTempPerm223 * ftbl0[(((int((65536.0f * (fRec187[0] + (fSlow20 * ((fSlow799 * fTempPerm216) + (fSlow819 * (fTempPerm220 * fTempPerm229))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				iRec191[0] = (iSlow813 * (iRec191[1] + 1));
				iTempPerm231 = int((iRec191[0] < iSlow833));
				fTempPerm232 = expf((0 - (fConst4 / ((iSlow815)?((iTempPerm231)?fSlow832:fSlow63):fSlow830))));
				fRec190[0] = ((fRec190[1] * fTempPerm232) + (((iSlow815)?((iTempPerm231)?1.5873015873015872f:fSlow834):0.0f) * (1.0f - fTempPerm232)));
				fTempPerm233 = min(1.0f, fRec190[0]);
			}
			if (iSlow342 || iSlow341) {
				fTempPerm234 = (fSlow835 * (fTempPerm233 * fTempPerm218));
			}
			if (iSlow341) {
				fTempPerm235 = ((fSlow829 * (fTempPerm223 * ftbl0[(((int((65536.0f * (fRec187[0] + fTempPerm217))) % 65536) + 65536) % 65536)])) + fTempPerm234);
			}
			if (iSlow337 || iSlow346 || iSlow342) {
				fTempPerm236 = (fSlow829 * (fTempPerm223 * ftbl0[(((int((65536.0f * fRec187[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow342) {
				fTempPerm237 = (fTempPerm234 + fTempPerm236);
			}
			if (iSlow337 || iSlow346 || iSlow344 || iSlow343) {
				fTempPerm238 = ftbl0[(((int((65536.0f * fRec183[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343) {
				fTempPerm239 = (fTempPerm220 * fTempPerm238);
			}
			if (iSlow343) {
				fTempPerm240 = (fSlow829 * (fTempPerm223 * ftbl0[(((int((65536.0f * (fRec187[0] + (fSlow20 * ((fTempPerm227 + (fSlow799 * fTempPerm226)) + (fSlow819 * fTempPerm239)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				iRec193[0] = (iSlow793 * (iRec193[1] + 1));
				iTempPerm241 = int((iRec193[0] < iSlow839));
				fTempPerm242 = expf((0 - (fConst4 / ((iSlow795)?((iTempPerm241)?fSlow838:fSlow63):fSlow836))));
				fRec192[0] = ((fRec192[1] * fTempPerm242) + (((iSlow795)?((iTempPerm241)?1.5873015873015872f:fSlow840):0.0f) * (1.0f - fTempPerm242)));
				fTempPerm243 = min(1.0f, fRec192[0]);
			}
			if (iSlow346 || iSlow345 || iSlow344) {
				fTempPerm244 = (fSlow841 * (fTempPerm243 * fTempPerm213));
			}
			if (iSlow344) {
				fTempPerm245 = ((fSlow829 * (fTempPerm223 * ftbl0[(((int((65536.0f * (fRec187[0] + (fSlow820 * fTempPerm239)))) % 65536) + 65536) % 65536)])) + fTempPerm244);
			}
			if (iSlow345) {
				fTempPerm246 = ((fSlow835 * (fTempPerm233 * fTempPerm229)) + (fTempPerm244 + (fSlow829 * (fTempPerm223 * ftbl0[(((int((65536.0f * (fRec187[0] + fTempPerm212))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow337 || iSlow346) {
				fTempPerm247 = (fSlow835 * (fTempPerm233 * fTempPerm238));
			}
			if (iSlow346) {
				fTempPerm248 = (fTempPerm247 + (fTempPerm236 + fTempPerm244));
			}
			if (iSlow337) {
				iRec195[0] = (iSlow773 * (iRec195[1] + 1));
				iTempPerm249 = int((iRec195[0] < iSlow845));
				fTempPerm250 = expf((0 - (fConst4 / ((iSlow775)?((iTempPerm249)?fSlow844:fSlow63):fSlow842))));
				fRec194[0] = ((fRec194[1] * fTempPerm250) + (((iSlow775)?((iTempPerm249)?1.5873015873015872f:fSlow846):0.0f) * (1.0f - fTempPerm250)));
				fTempPerm251 = (((fTempPerm236 + fTempPerm247) + (fSlow841 * (fTempPerm243 * fTempPerm225))) + (fSlow847 * (min(1.0f, fRec194[0]) * fTempPerm209)));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec196[0] = (fSlow848 + (fRec196[1] - floorf((fSlow848 + fRec196[1]))));
				fTempPerm252 = ftbl0[(((int((65536.0f * fRec196[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec198[0] = ((iSlow857)?0.0f:min(fSlow856, (fRec198[1] + 1.0f)));
				iTempPerm253 = int((fRec198[0] < fSlow853));
				fRec197[0] = ((iSlow862)?(fSlow861 * ((iTempPerm253)?((int((fRec198[0] < 0.0f)))?0.0f:((iTempPerm253)?(fSlow859 * fRec198[0]):1.0f)):((int((fRec198[0] < fSlow856)))?((fSlow858 * (fRec198[0] - fSlow853)) + 1.0f):fSlow851))):fRec197[1]);
				fRec199[0] = ((iSlow864)?0.0f:min(fSlow863, (fRec199[1] + 1.0f)));
				fTempPerm254 = (((int((fRec199[0] < 0.0f)))?fRec197[0]:((int((fRec199[0] < fSlow863)))?(fRec197[0] + (fSlow865 * (0 - (fRec199[0] * fRec197[0])))):0.0f)) * fTempPerm252);
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm255 = (fSlow867 * fTempPerm254);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec200[0] = (fSlow868 + (fRec200[1] - floorf((fSlow868 + fRec200[1]))));
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm256 = ftbl0[(((int((65536.0f * (fRec200[0] + fTempPerm255))) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec202[0] = ((iSlow877)?0.0f:min(fSlow876, (fRec202[1] + 1.0f)));
				iTempPerm257 = int((fRec202[0] < fSlow873));
				fRec201[0] = ((iSlow882)?(fSlow881 * ((iTempPerm257)?((int((fRec202[0] < 0.0f)))?0.0f:((iTempPerm257)?(fSlow879 * fRec202[0]):1.0f)):((int((fRec202[0] < fSlow876)))?((fSlow878 * (fRec202[0] - fSlow873)) + 1.0f):fSlow871))):fRec201[1]);
				fRec203[0] = ((iSlow884)?0.0f:min(fSlow883, (fRec203[1] + 1.0f)));
				fTempPerm258 = ((int((fRec203[0] < 0.0f)))?fRec201[0]:((int((fRec203[0] < fSlow883)))?(fRec201[0] + (fSlow885 * (0 - (fRec203[0] * fRec201[0])))):0.0f));
			}
			if (iSlow342 || iSlow341 || iSlow340 || iSlow338) {
				fTempPerm259 = (fTempPerm258 * fTempPerm256);
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm260 = (fSlow887 * fTempPerm259);
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec204[0] = (fSlow888 + (fRec204[1] - floorf((fSlow888 + fRec204[1]))));
			}
			if (iSlow342 || iSlow341 || iSlow338) {
				fTempPerm261 = ftbl0[(((int((65536.0f * (fRec204[0] + fTempPerm260))) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec206[0] = ((iSlow897)?0.0f:min(fSlow896, (fRec206[1] + 1.0f)));
				iTempPerm262 = int((fRec206[0] < fSlow893));
				fRec205[0] = ((iSlow902)?(fSlow901 * ((iTempPerm262)?((int((fRec206[0] < 0.0f)))?0.0f:((iTempPerm262)?(fSlow899 * fRec206[0]):1.0f)):((int((fRec206[0] < fSlow896)))?((fSlow898 * (fRec206[0] - fSlow893)) + 1.0f):fSlow891))):fRec205[1]);
				fRec207[0] = ((iSlow904)?0.0f:min(fSlow903, (fRec207[1] + 1.0f)));
				fTempPerm263 = ((int((fRec207[0] < 0.0f)))?fRec205[0]:((int((fRec207[0] < fSlow903)))?(fRec205[0] + (fSlow905 * (0 - (fRec207[0] * fRec205[0])))):0.0f));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec208[0] = (fSlow908 + (fRec208[1] - floorf((fSlow908 + fRec208[1]))));
				iRec210[0] = (iSlow913 * (iRec210[1] + 1));
				iTempPerm264 = int((iRec210[0] < iSlow912));
				fTempPerm265 = expf((0 - (fConst4 / ((iSlow914)?((iTempPerm264)?fSlow911:fSlow63):fSlow909))));
				fRec209[0] = ((fRec209[1] * fTempPerm265) + (((iSlow914)?((iTempPerm264)?1.5873015873015872f:fSlow915):0.0f) * (1.0f - fTempPerm265)));
				fTempPerm266 = min(1.0f, fRec209[0]);
			}
			if (iSlow338) {
				fTempPerm267 = (fSlow916 * (fTempPerm266 * ftbl0[(((int((65536.0f * (fRec208[0] + (fSlow907 * (fTempPerm263 * fTempPerm261))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow343 || iSlow339) {
				fTempPerm268 = ftbl0[(((int((65536.0f * fRec200[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow343 || iSlow339) {
				fTempPerm269 = (fTempPerm258 * fTempPerm268);
				fTempPerm270 = (fSlow866 * fTempPerm254);
			}
			if (iSlow339) {
				fTempPerm271 = (fSlow916 * (fTempPerm266 * ftbl0[(((int((65536.0f * (fRec208[0] + (fSlow20 * (fTempPerm270 + (fSlow906 * (fTempPerm263 * ftbl0[(((int((65536.0f * (fRec204[0] + (fSlow887 * fTempPerm269)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow345 || iSlow340) {
				fTempPerm272 = ftbl0[(((int((65536.0f * (fRec204[0] + fTempPerm255))) % 65536) + 65536) % 65536)];
			}
			if (iSlow340) {
				fTempPerm273 = (fSlow916 * (fTempPerm266 * ftbl0[(((int((65536.0f * (fRec208[0] + (fSlow20 * ((fSlow886 * fTempPerm259) + (fSlow906 * (fTempPerm263 * fTempPerm272))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				iRec212[0] = (iSlow900 * (iRec212[1] + 1));
				iTempPerm274 = int((iRec212[0] < iSlow920));
				fTempPerm275 = expf((0 - (fConst4 / ((iSlow902)?((iTempPerm274)?fSlow919:fSlow63):fSlow917))));
				fRec211[0] = ((fRec211[1] * fTempPerm275) + (((iSlow902)?((iTempPerm274)?1.5873015873015872f:fSlow921):0.0f) * (1.0f - fTempPerm275)));
				fTempPerm276 = min(1.0f, fRec211[0]);
			}
			if (iSlow342 || iSlow341) {
				fTempPerm277 = (fSlow922 * (fTempPerm276 * fTempPerm261));
			}
			if (iSlow341) {
				fTempPerm278 = ((fSlow916 * (fTempPerm266 * ftbl0[(((int((65536.0f * (fRec208[0] + fTempPerm260))) % 65536) + 65536) % 65536)])) + fTempPerm277);
			}
			if (iSlow337 || iSlow346 || iSlow342) {
				fTempPerm279 = (fSlow916 * (fTempPerm266 * ftbl0[(((int((65536.0f * fRec208[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow342) {
				fTempPerm280 = (fTempPerm277 + fTempPerm279);
			}
			if (iSlow337 || iSlow346 || iSlow344 || iSlow343) {
				fTempPerm281 = ftbl0[(((int((65536.0f * fRec204[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow344 || iSlow343) {
				fTempPerm282 = (fTempPerm263 * fTempPerm281);
			}
			if (iSlow343) {
				fTempPerm283 = (fSlow916 * (fTempPerm266 * ftbl0[(((int((65536.0f * (fRec208[0] + (fSlow20 * ((fTempPerm270 + (fSlow886 * fTempPerm269)) + (fSlow906 * fTempPerm282)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				iRec214[0] = (iSlow880 * (iRec214[1] + 1));
				iTempPerm284 = int((iRec214[0] < iSlow926));
				fTempPerm285 = expf((0 - (fConst4 / ((iSlow882)?((iTempPerm284)?fSlow925:fSlow63):fSlow923))));
				fRec213[0] = ((fRec213[1] * fTempPerm285) + (((iSlow882)?((iTempPerm284)?1.5873015873015872f:fSlow927):0.0f) * (1.0f - fTempPerm285)));
				fTempPerm286 = min(1.0f, fRec213[0]);
			}
			if (iSlow346 || iSlow345 || iSlow344) {
				fTempPerm287 = (fSlow928 * (fTempPerm286 * fTempPerm256));
			}
			if (iSlow344) {
				fTempPerm288 = ((fSlow916 * (fTempPerm266 * ftbl0[(((int((65536.0f * (fRec208[0] + (fSlow907 * fTempPerm282)))) % 65536) + 65536) % 65536)])) + fTempPerm287);
			}
			if (iSlow345) {
				fTempPerm289 = ((fSlow922 * (fTempPerm276 * fTempPerm272)) + (fTempPerm287 + (fSlow916 * (fTempPerm266 * ftbl0[(((int((65536.0f * (fRec208[0] + fTempPerm255))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow337 || iSlow346) {
				fTempPerm290 = (fSlow922 * (fTempPerm276 * fTempPerm281));
			}
			if (iSlow346) {
				fTempPerm291 = (fTempPerm290 + (fTempPerm279 + fTempPerm287));
			}
			if (iSlow337) {
				iRec216[0] = (iSlow860 * (iRec216[1] + 1));
				iTempPerm292 = int((iRec216[0] < iSlow932));
				fTempPerm293 = expf((0 - (fConst4 / ((iSlow862)?((iTempPerm292)?fSlow931:fSlow63):fSlow929))));
				fRec215[0] = ((fRec215[1] * fTempPerm293) + (((iSlow862)?((iTempPerm292)?1.5873015873015872f:fSlow933):0.0f) * (1.0f - fTempPerm293)));
				fTempPerm294 = (((fTempPerm279 + fTempPerm290) + (fSlow928 * (fTempPerm286 * fTempPerm268))) + (fSlow934 * (min(1.0f, fRec215[0]) * fTempPerm252)));
			}
			output0[i] = (FAUSTFLOAT)(fTempPerm294 + (fTempPerm291 + (fTempPerm289 + (fTempPerm288 + (fTempPerm283 + (fTempPerm280 + (fTempPerm278 + (fTempPerm273 + (fTempPerm271 + (fTempPerm267 + ((fTempPerm251 + (fTempPerm248 + (fTempPerm246 + (fTempPerm245 + (fTempPerm240 + (fTempPerm237 + (fTempPerm235 + (fTempPerm230 + (fTempPerm228 + (fTempPerm224 + ((fTempPerm208 + (fTempPerm205 + (fTempPerm203 + (fTempPerm202 + (fTempPerm197 + (fTempPerm194 + (fTempPerm192 + (fTempPerm187 + (fTempPerm185 + (fTempPerm181 + ((fTempPerm165 + (fTempPerm162 + (fTempPerm160 + (fTempPerm159 + (fTempPerm154 + (fTempPerm151 + (fTempPerm149 + (fTempPerm144 + (fTempPerm142 + (fTempPerm138 + ((fTempPerm122 + (fTempPerm119 + (fTempPerm117 + (fTempPerm116 + (fTempPerm111 + (fTempPerm108 + (fTempPerm106 + (fTempPerm101 + (fTempPerm99 + (fTempPerm95 + (((((((((((fTempPerm79 + fTempPerm73) + fTempPerm72) + fTempPerm71) + fTempPerm70) + fTempPerm69) + fTempPerm64) + fTempPerm59) + fTempPerm55) + fTempPerm53) + fTempPerm47) + fTempPerm30))))))))))) + fTempPerm24))))))))))) + fTempPerm18))))))))))) + fTempPerm12))))))))))) + fTempPerm6)))))))))));
			// post processing
			if (iSlow337) {
				fRec215[1] = fRec215[0];
				iRec216[1] = iRec216[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				fRec213[1] = fRec213[0];
				iRec214[1] = iRec214[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				fRec211[1] = fRec211[0];
				iRec212[1] = iRec212[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec209[1] = fRec209[0];
				iRec210[1] = iRec210[0];
				fRec208[1] = fRec208[0];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec207[1] = fRec207[0];
				fRec205[1] = fRec205[0];
				fRec206[1] = fRec206[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec204[1] = fRec204[0];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec203[1] = fRec203[0];
				fRec201[1] = fRec201[0];
				fRec202[1] = fRec202[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec200[1] = fRec200[0];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec199[1] = fRec199[0];
				fRec197[1] = fRec197[0];
				fRec198[1] = fRec198[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec196[1] = fRec196[0];
			}
			if (iSlow337) {
				fRec194[1] = fRec194[0];
				iRec195[1] = iRec195[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				fRec192[1] = fRec192[0];
				iRec193[1] = iRec193[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				fRec190[1] = fRec190[0];
				iRec191[1] = iRec191[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec188[1] = fRec188[0];
				iRec189[1] = iRec189[0];
				fRec187[1] = fRec187[0];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec186[1] = fRec186[0];
				fRec184[1] = fRec184[0];
				fRec185[1] = fRec185[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec183[1] = fRec183[0];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec182[1] = fRec182[0];
				fRec180[1] = fRec180[0];
				fRec181[1] = fRec181[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec179[1] = fRec179[0];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec178[1] = fRec178[0];
				fRec176[1] = fRec176[0];
				fRec177[1] = fRec177[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec175[1] = fRec175[0];
			}
			if (iSlow337) {
				fRec173[1] = fRec173[0];
				iRec174[1] = iRec174[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				fRec171[1] = fRec171[0];
				iRec172[1] = iRec172[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				fRec169[1] = fRec169[0];
				iRec170[1] = iRec170[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec167[1] = fRec167[0];
				iRec168[1] = iRec168[0];
				fRec166[1] = fRec166[0];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec165[1] = fRec165[0];
				fRec163[1] = fRec163[0];
				fRec164[1] = fRec164[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec162[1] = fRec162[0];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec161[1] = fRec161[0];
				fRec159[1] = fRec159[0];
				fRec160[1] = fRec160[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec158[1] = fRec158[0];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec157[1] = fRec157[0];
				fRec155[1] = fRec155[0];
				fRec156[1] = fRec156[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec154[1] = fRec154[0];
			}
			if (iSlow337) {
				fRec152[1] = fRec152[0];
				iRec153[1] = iRec153[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				fRec150[1] = fRec150[0];
				iRec151[1] = iRec151[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				fRec148[1] = fRec148[0];
				iRec149[1] = iRec149[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec146[1] = fRec146[0];
				iRec147[1] = iRec147[0];
				fRec145[1] = fRec145[0];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec144[1] = fRec144[0];
				fRec142[1] = fRec142[0];
				fRec143[1] = fRec143[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec141[1] = fRec141[0];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec140[1] = fRec140[0];
				fRec138[1] = fRec138[0];
				fRec139[1] = fRec139[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec137[1] = fRec137[0];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec136[1] = fRec136[0];
				fRec134[1] = fRec134[0];
				fRec135[1] = fRec135[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec133[1] = fRec133[0];
			}
			if (iSlow337) {
				fRec131[1] = fRec131[0];
				iRec132[1] = iRec132[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				fRec129[1] = fRec129[0];
				iRec130[1] = iRec130[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				fRec127[1] = fRec127[0];
				iRec128[1] = iRec128[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec125[1] = fRec125[0];
				iRec126[1] = iRec126[0];
				fRec124[1] = fRec124[0];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec123[1] = fRec123[0];
				fRec121[1] = fRec121[0];
				fRec122[1] = fRec122[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec120[1] = fRec120[0];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec119[1] = fRec119[0];
				fRec117[1] = fRec117[0];
				fRec118[1] = fRec118[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec116[1] = fRec116[0];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec115[1] = fRec115[0];
				fRec113[1] = fRec113[0];
				fRec114[1] = fRec114[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec112[1] = fRec112[0];
			}
			if (iSlow1) {
				fRec110[1] = fRec110[0];
				iRec111[1] = iRec111[0];
				fRec109[1] = fRec109[0];
				fRec108[1] = fRec108[0];
				fRec106[1] = fRec106[0];
				fRec107[1] = fRec107[0];
				fRec105[1] = fRec105[0];
				fRec104[1] = fRec104[0];
				fRec102[1] = fRec102[0];
				fRec103[1] = fRec103[0];
				fRec101[1] = fRec101[0];
				fRec100[1] = fRec100[0];
				fRec98[1] = fRec98[0];
				fRec99[1] = fRec99[0];
				fRec97[1] = fRec97[0];
			}
			if (iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec96[1] = fRec96[0];
				fRec94[1] = fRec94[0];
				fRec95[1] = fRec95[0];
			}
			if (iSlow344 || iSlow343 || iSlow340 || iSlow339 || iSlow338) {
				fRec93[1] = fRec93[0];
				fRec91[1] = fRec91[0];
				fRec92[1] = fRec92[0];
			}
			if (iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec90[1] = fRec90[0];
				fRec88[1] = fRec88[0];
				fRec89[1] = fRec89[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec86[1] = fRec86[0];
				iRec87[1] = iRec87[0];
				fRec85[1] = fRec85[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow342 || iSlow341) {
				fRec83[1] = fRec83[0];
				iRec84[1] = iRec84[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec82[1] = fRec82[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344) {
				fRec80[1] = fRec80[0];
				iRec81[1] = iRec81[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec79[1] = fRec79[0];
			}
			if (iSlow337) {
				fRec77[1] = fRec77[0];
				iRec78[1] = iRec78[0];
			}
			if (iSlow337 || iSlow346 || iSlow345 || iSlow344 || iSlow343 || iSlow342 || iSlow341 || iSlow340 || iSlow339 || iSlow338) {
				fRec76[1] = fRec76[0];
			}
			if (iSlow1) {
				fRec74[1] = fRec74[0];
				iRec75[1] = iRec75[0];
				fRec73[1] = fRec73[0];
				fRec72[1] = fRec72[0];
				fRec70[1] = fRec70[0];
				fRec71[1] = fRec71[0];
				fRec69[1] = fRec69[0];
				fRec68[1] = fRec68[0];
				fRec66[1] = fRec66[0];
				fRec67[1] = fRec67[0];
				fRec65[1] = fRec65[0];
				fRec64[1] = fRec64[0];
				fRec62[1] = fRec62[0];
				fRec63[1] = fRec63[0];
				fRec61[1] = fRec61[0];
				fRec59[1] = fRec59[0];
				iRec60[1] = iRec60[0];
				fRec58[1] = fRec58[0];
				fRec57[1] = fRec57[0];
				fRec55[1] = fRec55[0];
				fRec56[1] = fRec56[0];
				fRec54[1] = fRec54[0];
				fRec53[1] = fRec53[0];
				fRec51[1] = fRec51[0];
				fRec52[1] = fRec52[0];
				fRec50[1] = fRec50[0];
				fRec49[1] = fRec49[0];
				fRec47[1] = fRec47[0];
				fRec48[1] = fRec48[0];
				fRec46[1] = fRec46[0];
				fRec44[1] = fRec44[0];
				iRec45[1] = iRec45[0];
				fRec43[1] = fRec43[0];
				fRec42[1] = fRec42[0];
				fRec40[1] = fRec40[0];
				fRec41[1] = fRec41[0];
				fRec39[1] = fRec39[0];
				fRec38[1] = fRec38[0];
				fRec36[1] = fRec36[0];
				fRec37[1] = fRec37[0];
				fRec35[1] = fRec35[0];
				fRec34[1] = fRec34[0];
				fRec32[1] = fRec32[0];
				fRec33[1] = fRec33[0];
				fRec31[1] = fRec31[0];
				fRec29[1] = fRec29[0];
				iRec30[1] = iRec30[0];
				fRec28[1] = fRec28[0];
				fRec27[1] = fRec27[0];
				fRec25[1] = fRec25[0];
				fRec26[1] = fRec26[0];
				fRec24[1] = fRec24[0];
				fRec23[1] = fRec23[0];
				fRec21[1] = fRec21[0];
				fRec22[1] = fRec22[0];
				fRec20[1] = fRec20[0];
				fRec19[1] = fRec19[0];
				fRec17[1] = fRec17[0];
				fRec18[1] = fRec18[0];
				fRec16[1] = fRec16[0];
				fRec14[1] = fRec14[0];
				iRec15[1] = iRec15[0];
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


float 	faust_ottofm::ftbl0[65536];
