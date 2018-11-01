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
	FAUSTFLOAT 	fslider7;
	float 	fTempPerm3;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	float 	fRec5[2];
	float 	fTempPerm4;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fbutton1;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	float 	fRec7[2];
	int 	iTempPerm5;
	float 	fRec6[2];
	float 	fRec8[2];
	float 	fTempPerm6;
	FAUSTFLOAT 	fslider14;
	float 	fTempPerm7;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	float 	fRec9[2];
	float 	fTempPerm8;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fbutton2;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	float 	fRec11[2];
	int 	iTempPerm9;
	float 	fRec10[2];
	float 	fRec12[2];
	float 	fTempPerm10;
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fbutton3;
	int 	iRec15[2];
	int 	iTempPerm11;
	float 	fConst4;
	float 	fTempPerm12;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT 	fslider31;
	float 	fRec14[2];
	float 	fTempPerm13;
	FAUSTFLOAT 	fslider32;
	FAUSTFLOAT 	fslider33;
	float 	fTempPerm14;
	FAUSTFLOAT 	fslider34;
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fslider36;
	float 	fRec16[2];
	float 	fTempPerm15;
	FAUSTFLOAT 	fslider37;
	FAUSTFLOAT 	fbutton4;
	FAUSTFLOAT 	fslider38;
	FAUSTFLOAT 	fslider39;
	float 	fRec18[2];
	int 	iTempPerm16;
	float 	fRec17[2];
	float 	fRec19[2];
	FAUSTFLOAT 	fslider40;
	float 	fTempPerm17;
	FAUSTFLOAT 	fslider41;
	FAUSTFLOAT 	fslider42;
	FAUSTFLOAT 	fslider43;
	float 	fRec20[2];
	float 	fTempPerm18;
	FAUSTFLOAT 	fslider44;
	FAUSTFLOAT 	fbutton5;
	FAUSTFLOAT 	fslider45;
	FAUSTFLOAT 	fslider46;
	float 	fRec22[2];
	int 	iTempPerm19;
	float 	fRec21[2];
	float 	fRec23[2];
	float 	fTempPerm20;
	FAUSTFLOAT 	fslider47;
	float 	fTempPerm21;
	FAUSTFLOAT 	fslider48;
	FAUSTFLOAT 	fslider49;
	FAUSTFLOAT 	fslider50;
	float 	fRec24[2];
	float 	fTempPerm22;
	FAUSTFLOAT 	fslider51;
	FAUSTFLOAT 	fbutton6;
	FAUSTFLOAT 	fslider52;
	FAUSTFLOAT 	fslider53;
	float 	fRec26[2];
	int 	iTempPerm23;
	float 	fRec25[2];
	float 	fRec27[2];
	float 	fTempPerm24;
	FAUSTFLOAT 	fslider54;
	FAUSTFLOAT 	fslider55;
	FAUSTFLOAT 	fslider56;
	FAUSTFLOAT 	fslider57;
	float 	fRec28[2];
	FAUSTFLOAT 	fslider58;
	FAUSTFLOAT 	fslider59;
	FAUSTFLOAT 	fbutton7;
	int 	iRec30[2];
	int 	iTempPerm25;
	float 	fTempPerm26;
	FAUSTFLOAT 	fslider60;
	float 	fRec29[2];
	float 	fTempPerm27;
	FAUSTFLOAT 	fslider61;
	FAUSTFLOAT 	fslider62;
	float 	fTempPerm28;
	FAUSTFLOAT 	fslider63;
	FAUSTFLOAT 	fslider64;
	FAUSTFLOAT 	fslider65;
	float 	fRec31[2];
	float 	fTempPerm29;
	FAUSTFLOAT 	fslider66;
	FAUSTFLOAT 	fbutton8;
	FAUSTFLOAT 	fslider67;
	FAUSTFLOAT 	fslider68;
	float 	fRec33[2];
	int 	iTempPerm30;
	float 	fRec32[2];
	float 	fRec34[2];
	FAUSTFLOAT 	fslider69;
	float 	fTempPerm31;
	FAUSTFLOAT 	fslider70;
	FAUSTFLOAT 	fslider71;
	FAUSTFLOAT 	fslider72;
	float 	fRec35[2];
	float 	fTempPerm32;
	FAUSTFLOAT 	fslider73;
	FAUSTFLOAT 	fbutton9;
	FAUSTFLOAT 	fslider74;
	FAUSTFLOAT 	fslider75;
	float 	fRec37[2];
	int 	iTempPerm33;
	float 	fRec36[2];
	float 	fRec38[2];
	float 	fTempPerm34;
	FAUSTFLOAT 	fslider76;
	float 	fTempPerm35;
	FAUSTFLOAT 	fslider77;
	FAUSTFLOAT 	fslider78;
	FAUSTFLOAT 	fslider79;
	float 	fRec39[2];
	float 	fTempPerm36;
	FAUSTFLOAT 	fslider80;
	FAUSTFLOAT 	fbutton10;
	FAUSTFLOAT 	fslider81;
	FAUSTFLOAT 	fslider82;
	float 	fRec41[2];
	int 	iTempPerm37;
	float 	fRec40[2];
	float 	fRec42[2];
	float 	fTempPerm38;
	FAUSTFLOAT 	fslider83;
	FAUSTFLOAT 	fslider84;
	FAUSTFLOAT 	fslider85;
	FAUSTFLOAT 	fslider86;
	float 	fRec43[2];
	FAUSTFLOAT 	fslider87;
	FAUSTFLOAT 	fslider88;
	FAUSTFLOAT 	fbutton11;
	int 	iRec45[2];
	int 	iTempPerm39;
	float 	fTempPerm40;
	FAUSTFLOAT 	fslider89;
	float 	fRec44[2];
	float 	fTempPerm41;
	FAUSTFLOAT 	fslider90;
	FAUSTFLOAT 	fslider91;
	float 	fTempPerm42;
	FAUSTFLOAT 	fslider92;
	FAUSTFLOAT 	fslider93;
	FAUSTFLOAT 	fslider94;
	float 	fRec46[2];
	float 	fTempPerm43;
	FAUSTFLOAT 	fslider95;
	FAUSTFLOAT 	fbutton12;
	FAUSTFLOAT 	fslider96;
	FAUSTFLOAT 	fslider97;
	float 	fRec48[2];
	int 	iTempPerm44;
	float 	fRec47[2];
	float 	fRec49[2];
	FAUSTFLOAT 	fslider98;
	float 	fTempPerm45;
	FAUSTFLOAT 	fslider99;
	FAUSTFLOAT 	fslider100;
	FAUSTFLOAT 	fslider101;
	float 	fRec50[2];
	float 	fTempPerm46;
	FAUSTFLOAT 	fslider102;
	FAUSTFLOAT 	fbutton13;
	FAUSTFLOAT 	fslider103;
	FAUSTFLOAT 	fslider104;
	float 	fRec52[2];
	int 	iTempPerm47;
	float 	fRec51[2];
	float 	fRec53[2];
	float 	fTempPerm48;
	FAUSTFLOAT 	fslider105;
	float 	fTempPerm49;
	FAUSTFLOAT 	fslider106;
	FAUSTFLOAT 	fslider107;
	FAUSTFLOAT 	fslider108;
	float 	fRec54[2];
	float 	fTempPerm50;
	FAUSTFLOAT 	fslider109;
	FAUSTFLOAT 	fbutton14;
	FAUSTFLOAT 	fslider110;
	FAUSTFLOAT 	fslider111;
	float 	fRec56[2];
	int 	iTempPerm51;
	float 	fRec55[2];
	float 	fRec57[2];
	float 	fTempPerm52;
	FAUSTFLOAT 	fslider112;
	FAUSTFLOAT 	fslider113;
	FAUSTFLOAT 	fslider114;
	FAUSTFLOAT 	fslider115;
	float 	fRec58[2];
	FAUSTFLOAT 	fslider116;
	FAUSTFLOAT 	fslider117;
	FAUSTFLOAT 	fbutton15;
	int 	iRec60[2];
	int 	iTempPerm53;
	float 	fTempPerm54;
	FAUSTFLOAT 	fslider118;
	float 	fRec59[2];
	float 	fTempPerm55;
	FAUSTFLOAT 	fslider119;
	FAUSTFLOAT 	fslider120;
	float 	fTempPerm56;
	FAUSTFLOAT 	fslider121;
	FAUSTFLOAT 	fslider122;
	FAUSTFLOAT 	fslider123;
	float 	fRec61[2];
	float 	fTempPerm57;
	FAUSTFLOAT 	fslider124;
	FAUSTFLOAT 	fbutton16;
	FAUSTFLOAT 	fslider125;
	FAUSTFLOAT 	fslider126;
	float 	fRec63[2];
	int 	iTempPerm58;
	float 	fRec62[2];
	float 	fRec64[2];
	FAUSTFLOAT 	fslider127;
	float 	fTempPerm59;
	FAUSTFLOAT 	fslider128;
	FAUSTFLOAT 	fslider129;
	FAUSTFLOAT 	fslider130;
	float 	fRec65[2];
	float 	fTempPerm60;
	FAUSTFLOAT 	fslider131;
	FAUSTFLOAT 	fbutton17;
	FAUSTFLOAT 	fslider132;
	FAUSTFLOAT 	fslider133;
	float 	fRec67[2];
	int 	iTempPerm61;
	float 	fRec66[2];
	float 	fRec68[2];
	float 	fTempPerm62;
	FAUSTFLOAT 	fslider134;
	float 	fTempPerm63;
	FAUSTFLOAT 	fslider135;
	FAUSTFLOAT 	fslider136;
	FAUSTFLOAT 	fslider137;
	float 	fRec69[2];
	float 	fTempPerm64;
	FAUSTFLOAT 	fslider138;
	FAUSTFLOAT 	fbutton18;
	FAUSTFLOAT 	fslider139;
	FAUSTFLOAT 	fslider140;
	float 	fRec71[2];
	int 	iTempPerm65;
	float 	fRec70[2];
	float 	fRec72[2];
	float 	fTempPerm66;
	FAUSTFLOAT 	fslider141;
	FAUSTFLOAT 	fslider142;
	FAUSTFLOAT 	fslider143;
	FAUSTFLOAT 	fslider144;
	float 	fRec73[2];
	FAUSTFLOAT 	fslider145;
	FAUSTFLOAT 	fslider146;
	FAUSTFLOAT 	fbutton19;
	int 	iRec75[2];
	int 	iTempPerm67;
	float 	fTempPerm68;
	FAUSTFLOAT 	fslider147;
	float 	fRec74[2];
	float 	fTempPerm69;
	FAUSTFLOAT 	fslider148;
	FAUSTFLOAT 	fslider149;
	float 	fTempPerm70;
	FAUSTFLOAT 	fslider150;
	FAUSTFLOAT 	fslider151;
	FAUSTFLOAT 	fslider152;
	float 	fRec76[2];
	float 	fTempPerm71;
	FAUSTFLOAT 	fslider153;
	FAUSTFLOAT 	fslider154;
	FAUSTFLOAT 	fbutton20;
	int 	iRec78[2];
	int 	iTempPerm72;
	float 	fTempPerm73;
	FAUSTFLOAT 	fslider155;
	float 	fRec77[2];
	FAUSTFLOAT 	fslider156;
	FAUSTFLOAT 	fslider157;
	FAUSTFLOAT 	fslider158;
	FAUSTFLOAT 	fslider159;
	FAUSTFLOAT 	fslider160;
	float 	fRec79[2];
	float 	fTempPerm74;
	FAUSTFLOAT 	fslider161;
	FAUSTFLOAT 	fslider162;
	FAUSTFLOAT 	fbutton21;
	int 	iRec81[2];
	int 	iTempPerm75;
	float 	fTempPerm76;
	FAUSTFLOAT 	fslider163;
	float 	fRec80[2];
	float 	fTempPerm77;
	FAUSTFLOAT 	fslider164;
	FAUSTFLOAT 	fslider165;
	FAUSTFLOAT 	fslider166;
	FAUSTFLOAT 	fslider167;
	FAUSTFLOAT 	fslider168;
	float 	fRec82[2];
	float 	fTempPerm78;
	FAUSTFLOAT 	fslider169;
	FAUSTFLOAT 	fslider170;
	FAUSTFLOAT 	fbutton22;
	int 	iRec84[2];
	int 	iTempPerm79;
	float 	fTempPerm80;
	FAUSTFLOAT 	fslider171;
	float 	fRec83[2];
	float 	fTempPerm81;
	FAUSTFLOAT 	fslider172;
	FAUSTFLOAT 	fslider173;
	float 	fTempPerm82;
	FAUSTFLOAT 	fslider174;
	FAUSTFLOAT 	fslider175;
	FAUSTFLOAT 	fslider176;
	float 	fRec85[2];
	FAUSTFLOAT 	fslider177;
	FAUSTFLOAT 	fslider178;
	FAUSTFLOAT 	fbutton23;
	int 	iRec87[2];
	int 	iTempPerm83;
	float 	fTempPerm84;
	FAUSTFLOAT 	fslider179;
	float 	fRec86[2];
	float 	fTempPerm85;
	FAUSTFLOAT 	fslider180;
	FAUSTFLOAT 	fslider181;
	float 	fTempPerm86;
	float 	fTempPerm87;
	FAUSTFLOAT 	fslider182;
	FAUSTFLOAT 	fslider183;
	FAUSTFLOAT 	fslider184;
	float 	fRec89[2];
	int 	iTempPerm88;
	float 	fRec88[2];
	float 	fRec90[2];
	float 	fTempPerm89;
	float 	fTempPerm90;
	float 	fTempPerm91;
	float 	fTempPerm92;
	float 	fTempPerm93;
	float 	fTempPerm94;
	FAUSTFLOAT 	fslider185;
	FAUSTFLOAT 	fslider186;
	FAUSTFLOAT 	fslider187;
	float 	fRec92[2];
	int 	iTempPerm95;
	float 	fRec91[2];
	float 	fRec93[2];
	float 	fTempPerm96;
	float 	fTempPerm97;
	float 	fTempPerm98;
	FAUSTFLOAT 	fslider188;
	FAUSTFLOAT 	fslider189;
	FAUSTFLOAT 	fslider190;
	float 	fRec95[2];
	int 	iTempPerm99;
	float 	fRec94[2];
	float 	fRec96[2];
	float 	fTempPerm100;
	float 	fTempPerm101;
	float 	fTempPerm102;
	float 	fTempPerm103;
	float 	fTempPerm104;
	float 	fTempPerm105;
	float 	fTempPerm106;
	float 	fTempPerm107;
	float 	fTempPerm108;
	float 	fTempPerm109;
	float 	fTempPerm110;
	float 	fTempPerm111;
	float 	fTempPerm112;
	float 	fTempPerm113;
	float 	fTempPerm114;
	float 	fTempPerm115;
	FAUSTFLOAT 	fslider191;
	FAUSTFLOAT 	fslider192;
	int 	iRec98[2];
	int 	iTempPerm116;
	float 	fTempPerm117;
	FAUSTFLOAT 	fslider193;
	float 	fRec97[2];
	float 	fTempPerm118;
	FAUSTFLOAT 	fslider194;
	float 	fTempPerm119;
	float 	fTempPerm120;
	float 	fTempPerm121;
	float 	fTempPerm122;
	float 	fTempPerm123;
	float 	fTempPerm124;
	float 	fTempPerm125;
	FAUSTFLOAT 	fslider195;
	FAUSTFLOAT 	fslider196;
	int 	iRec100[2];
	int 	iTempPerm126;
	float 	fTempPerm127;
	FAUSTFLOAT 	fslider197;
	float 	fRec99[2];
	float 	fTempPerm128;
	FAUSTFLOAT 	fslider198;
	float 	fTempPerm129;
	float 	fTempPerm130;
	float 	fTempPerm131;
	float 	fTempPerm132;
	float 	fTempPerm133;
	FAUSTFLOAT 	fslider199;
	FAUSTFLOAT 	fslider200;
	int 	iRec102[2];
	int 	iTempPerm134;
	float 	fTempPerm135;
	FAUSTFLOAT 	fslider201;
	float 	fRec101[2];
	FAUSTFLOAT 	fslider202;
	float 	fTempPerm136;
	float 	fTempPerm137;
	float 	fTempPerm138;
	float 	fTempPerm139;
	float 	fTempPerm140;
	float 	fTempPerm141;
	FAUSTFLOAT 	fslider203;
	FAUSTFLOAT 	fslider204;
	int 	iRec104[2];
	int 	iTempPerm142;
	float 	fTempPerm143;
	FAUSTFLOAT 	fslider205;
	float 	fRec103[2];
	float 	fTempPerm144;
	FAUSTFLOAT 	fslider206;
	float 	fTempPerm145;
	float 	fTempPerm146;
	float 	fTempPerm147;
	float 	fTempPerm148;
	float 	fTempPerm149;
	float 	fTempPerm150;
	float 	fTempPerm151;
	FAUSTFLOAT 	fslider207;
	FAUSTFLOAT 	fslider208;
	int 	iRec106[2];
	int 	iTempPerm152;
	float 	fTempPerm153;
	FAUSTFLOAT 	fslider209;
	float 	fRec105[2];
	float 	fTempPerm154;
	FAUSTFLOAT 	fslider210;
	float 	fTempPerm155;
	float 	fTempPerm156;
	float 	fTempPerm157;
	float 	fTempPerm158;
	float 	fTempPerm159;
	FAUSTFLOAT 	fslider211;
	FAUSTFLOAT 	fslider212;
	int 	iRec108[2];
	int 	iTempPerm160;
	float 	fTempPerm161;
	FAUSTFLOAT 	fslider213;
	float 	fRec107[2];
	FAUSTFLOAT 	fslider214;
	float 	fTempPerm162;
	float 	fTempPerm163;
	float 	fTempPerm164;
	float 	fTempPerm165;
	float 	fTempPerm166;
	float 	fTempPerm167;
	FAUSTFLOAT 	fslider215;
	FAUSTFLOAT 	fslider216;
	int 	iRec110[2];
	int 	iTempPerm168;
	float 	fTempPerm169;
	FAUSTFLOAT 	fslider217;
	float 	fRec109[2];
	float 	fTempPerm170;
	FAUSTFLOAT 	fslider218;
	float 	fTempPerm171;
	float 	fTempPerm172;
	float 	fTempPerm173;
	float 	fTempPerm174;
	float 	fTempPerm175;
	float 	fTempPerm176;
	float 	fTempPerm177;
	FAUSTFLOAT 	fslider219;
	FAUSTFLOAT 	fslider220;
	int 	iRec112[2];
	int 	iTempPerm178;
	float 	fTempPerm179;
	FAUSTFLOAT 	fslider221;
	float 	fRec111[2];
	float 	fTempPerm180;
	FAUSTFLOAT 	fslider222;
	float 	fTempPerm181;
	float 	fTempPerm182;
	float 	fTempPerm183;
	float 	fTempPerm184;
	float 	fTempPerm185;
	FAUSTFLOAT 	fslider223;
	FAUSTFLOAT 	fslider224;
	int 	iRec114[2];
	int 	iTempPerm186;
	float 	fTempPerm187;
	FAUSTFLOAT 	fslider225;
	float 	fRec113[2];
	FAUSTFLOAT 	fslider226;
	float 	fTempPerm188;
	float 	fTempPerm189;
	float 	fTempPerm190;
	float 	fTempPerm191;
	float 	fTempPerm192;
	float 	fTempPerm193;
	FAUSTFLOAT 	fslider227;
	FAUSTFLOAT 	fslider228;
	int 	iRec116[2];
	int 	iTempPerm194;
	float 	fTempPerm195;
	FAUSTFLOAT 	fslider229;
	float 	fRec115[2];
	float 	fTempPerm196;
	FAUSTFLOAT 	fslider230;
	float 	fTempPerm197;
	float 	fTempPerm198;
	float 	fTempPerm199;
	float 	fTempPerm200;
	float 	fTempPerm201;
	float 	fTempPerm202;
	float 	fTempPerm203;
	FAUSTFLOAT 	fslider231;
	FAUSTFLOAT 	fslider232;
	int 	iRec118[2];
	int 	iTempPerm204;
	float 	fTempPerm205;
	FAUSTFLOAT 	fslider233;
	float 	fRec117[2];
	float 	fTempPerm206;
	FAUSTFLOAT 	fslider234;
	float 	fTempPerm207;
	float 	fTempPerm208;
	float 	fTempPerm209;
	float 	fTempPerm210;
	float 	fTempPerm211;
	FAUSTFLOAT 	fslider235;
	FAUSTFLOAT 	fslider236;
	int 	iRec120[2];
	int 	iTempPerm212;
	float 	fTempPerm213;
	FAUSTFLOAT 	fslider237;
	float 	fRec119[2];
	FAUSTFLOAT 	fslider238;
	float 	fTempPerm214;
	float 	fTempPerm215;
	float 	fTempPerm216;
	float 	fTempPerm217;
	float 	fTempPerm218;
	float 	fTempPerm219;
	FAUSTFLOAT 	fslider239;
	FAUSTFLOAT 	fslider240;
	int 	iRec122[2];
	int 	iTempPerm220;
	float 	fTempPerm221;
	FAUSTFLOAT 	fslider241;
	float 	fRec121[2];
	float 	fTempPerm222;
	FAUSTFLOAT 	fslider242;
	float 	fTempPerm223;
	float 	fTempPerm224;
	float 	fTempPerm225;
	float 	fTempPerm226;
	float 	fTempPerm227;
	float 	fTempPerm228;
	float 	fTempPerm229;
	FAUSTFLOAT 	fslider243;
	FAUSTFLOAT 	fslider244;
	int 	iRec124[2];
	int 	iTempPerm230;
	float 	fTempPerm231;
	FAUSTFLOAT 	fslider245;
	float 	fRec123[2];
	float 	fTempPerm232;
	FAUSTFLOAT 	fslider246;
	float 	fTempPerm233;
	float 	fTempPerm234;
	float 	fTempPerm235;
	float 	fTempPerm236;
	float 	fTempPerm237;
	FAUSTFLOAT 	fslider247;
	FAUSTFLOAT 	fslider248;
	int 	iRec126[2];
	int 	iTempPerm238;
	float 	fTempPerm239;
	FAUSTFLOAT 	fslider249;
	float 	fRec125[2];
	FAUSTFLOAT 	fslider250;
	float 	fTempPerm240;
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
		iTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		iTempPerm9 = 0;
		fTempPerm10 = 0;
		iTempPerm11 = 0;
		fConst4 = (6.9100000000000001f / fConst0);
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		iTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		iTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		iTempPerm23 = 0;
		fTempPerm24 = 0;
		iTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		iTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		iTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		iTempPerm37 = 0;
		fTempPerm38 = 0;
		iTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		iTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		iTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		iTempPerm51 = 0;
		fTempPerm52 = 0;
		iTempPerm53 = 0;
		fTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		iTempPerm58 = 0;
		fTempPerm59 = 0;
		fTempPerm60 = 0;
		iTempPerm61 = 0;
		fTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		iTempPerm65 = 0;
		fTempPerm66 = 0;
		iTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		fTempPerm70 = 0;
		fTempPerm71 = 0;
		iTempPerm72 = 0;
		fTempPerm73 = 0;
		fTempPerm74 = 0;
		iTempPerm75 = 0;
		fTempPerm76 = 0;
		fTempPerm77 = 0;
		fTempPerm78 = 0;
		iTempPerm79 = 0;
		fTempPerm80 = 0;
		fTempPerm81 = 0;
		fTempPerm82 = 0;
		iTempPerm83 = 0;
		fTempPerm84 = 0;
		fTempPerm85 = 0;
		fTempPerm86 = 0;
		fTempPerm87 = 0;
		iTempPerm88 = 0;
		fTempPerm89 = 0;
		fTempPerm90 = 0;
		fTempPerm91 = 0;
		fTempPerm92 = 0;
		fTempPerm93 = 0;
		fTempPerm94 = 0;
		iTempPerm95 = 0;
		fTempPerm96 = 0;
		fTempPerm97 = 0;
		fTempPerm98 = 0;
		iTempPerm99 = 0;
		fTempPerm100 = 0;
		fTempPerm101 = 0;
		fTempPerm102 = 0;
		fTempPerm103 = 0;
		fTempPerm104 = 0;
		fTempPerm105 = 0;
		fTempPerm106 = 0;
		fTempPerm107 = 0;
		fTempPerm108 = 0;
		fTempPerm109 = 0;
		fTempPerm110 = 0;
		fTempPerm111 = 0;
		fTempPerm112 = 0;
		fTempPerm113 = 0;
		fTempPerm114 = 0;
		fTempPerm115 = 0;
		iTempPerm116 = 0;
		fTempPerm117 = 0;
		fTempPerm118 = 0;
		fTempPerm119 = 0;
		fTempPerm120 = 0;
		fTempPerm121 = 0;
		fTempPerm122 = 0;
		fTempPerm123 = 0;
		fTempPerm124 = 0;
		fTempPerm125 = 0;
		iTempPerm126 = 0;
		fTempPerm127 = 0;
		fTempPerm128 = 0;
		fTempPerm129 = 0;
		fTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		fTempPerm133 = 0;
		iTempPerm134 = 0;
		fTempPerm135 = 0;
		fTempPerm136 = 0;
		fTempPerm137 = 0;
		fTempPerm138 = 0;
		fTempPerm139 = 0;
		fTempPerm140 = 0;
		fTempPerm141 = 0;
		iTempPerm142 = 0;
		fTempPerm143 = 0;
		fTempPerm144 = 0;
		fTempPerm145 = 0;
		fTempPerm146 = 0;
		fTempPerm147 = 0;
		fTempPerm148 = 0;
		fTempPerm149 = 0;
		fTempPerm150 = 0;
		fTempPerm151 = 0;
		iTempPerm152 = 0;
		fTempPerm153 = 0;
		fTempPerm154 = 0;
		fTempPerm155 = 0;
		fTempPerm156 = 0;
		fTempPerm157 = 0;
		fTempPerm158 = 0;
		fTempPerm159 = 0;
		iTempPerm160 = 0;
		fTempPerm161 = 0;
		fTempPerm162 = 0;
		fTempPerm163 = 0;
		fTempPerm164 = 0;
		fTempPerm165 = 0;
		fTempPerm166 = 0;
		fTempPerm167 = 0;
		iTempPerm168 = 0;
		fTempPerm169 = 0;
		fTempPerm170 = 0;
		fTempPerm171 = 0;
		fTempPerm172 = 0;
		fTempPerm173 = 0;
		fTempPerm174 = 0;
		fTempPerm175 = 0;
		fTempPerm176 = 0;
		fTempPerm177 = 0;
		iTempPerm178 = 0;
		fTempPerm179 = 0;
		fTempPerm180 = 0;
		fTempPerm181 = 0;
		fTempPerm182 = 0;
		fTempPerm183 = 0;
		fTempPerm184 = 0;
		fTempPerm185 = 0;
		iTempPerm186 = 0;
		fTempPerm187 = 0;
		fTempPerm188 = 0;
		fTempPerm189 = 0;
		fTempPerm190 = 0;
		fTempPerm191 = 0;
		fTempPerm192 = 0;
		fTempPerm193 = 0;
		iTempPerm194 = 0;
		fTempPerm195 = 0;
		fTempPerm196 = 0;
		fTempPerm197 = 0;
		fTempPerm198 = 0;
		fTempPerm199 = 0;
		fTempPerm200 = 0;
		fTempPerm201 = 0;
		fTempPerm202 = 0;
		fTempPerm203 = 0;
		iTempPerm204 = 0;
		fTempPerm205 = 0;
		fTempPerm206 = 0;
		fTempPerm207 = 0;
		fTempPerm208 = 0;
		fTempPerm209 = 0;
		fTempPerm210 = 0;
		fTempPerm211 = 0;
		iTempPerm212 = 0;
		fTempPerm213 = 0;
		fTempPerm214 = 0;
		fTempPerm215 = 0;
		fTempPerm216 = 0;
		fTempPerm217 = 0;
		fTempPerm218 = 0;
		fTempPerm219 = 0;
		iTempPerm220 = 0;
		fTempPerm221 = 0;
		fTempPerm222 = 0;
		fTempPerm223 = 0;
		fTempPerm224 = 0;
		fTempPerm225 = 0;
		fTempPerm226 = 0;
		fTempPerm227 = 0;
		fTempPerm228 = 0;
		fTempPerm229 = 0;
		iTempPerm230 = 0;
		fTempPerm231 = 0;
		fTempPerm232 = 0;
		fTempPerm233 = 0;
		fTempPerm234 = 0;
		fTempPerm235 = 0;
		fTempPerm236 = 0;
		fTempPerm237 = 0;
		iTempPerm238 = 0;
		fTempPerm239 = 0;
		fTempPerm240 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 1.0f;
		fslider3 = 440.0f;
		fslider4 = 0.0f;
		fbutton0 = 0.0;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		fslider7 = 0.0f;
		fslider8 = 0.0f;
		fslider9 = 1.0f;
		fslider10 = 440.0f;
		fslider11 = 0.0f;
		fbutton1 = 0.0;
		fslider12 = 0.0f;
		fslider13 = 0.0f;
		fslider14 = 0.0f;
		fslider15 = 0.0f;
		fslider16 = 1.0f;
		fslider17 = 440.0f;
		fslider18 = 0.0f;
		fbutton2 = 0.0;
		fslider19 = 0.0f;
		fslider20 = 0.0f;
		fslider21 = 0.0f;
		fslider22 = 0.0f;
		fslider23 = 1.0f;
		fslider24 = 440.0f;
		fslider25 = 0.0f;
		fslider26 = 0.0f;
		fslider27 = 0.0f;
		fslider28 = 0.0f;
		fslider29 = 0.001f;
		fbutton3 = 0.0;
		fslider30 = 1.0f;
		fslider31 = 0.0f;
		fslider32 = 0.0f;
		fslider33 = 1.0f;
		fslider34 = 0.0f;
		fslider35 = 1.0f;
		fslider36 = 440.0f;
		fslider37 = 0.0f;
		fbutton4 = 0.0;
		fslider38 = 0.0f;
		fslider39 = 0.0f;
		fslider40 = 0.0f;
		fslider41 = 0.0f;
		fslider42 = 1.0f;
		fslider43 = 440.0f;
		fslider44 = 0.0f;
		fbutton5 = 0.0;
		fslider45 = 0.0f;
		fslider46 = 0.0f;
		fslider47 = 0.0f;
		fslider48 = 0.0f;
		fslider49 = 1.0f;
		fslider50 = 440.0f;
		fslider51 = 0.0f;
		fbutton6 = 0.0;
		fslider52 = 0.0f;
		fslider53 = 0.0f;
		fslider54 = 0.0f;
		fslider55 = 0.0f;
		fslider56 = 1.0f;
		fslider57 = 440.0f;
		fslider58 = 0.0f;
		fslider59 = 0.0f;
		fbutton7 = 0.0;
		fslider60 = 0.0f;
		fslider61 = 0.0f;
		fslider62 = 1.0f;
		fslider63 = 0.0f;
		fslider64 = 1.0f;
		fslider65 = 440.0f;
		fslider66 = 0.0f;
		fbutton8 = 0.0;
		fslider67 = 0.0f;
		fslider68 = 0.0f;
		fslider69 = 0.0f;
		fslider70 = 0.0f;
		fslider71 = 1.0f;
		fslider72 = 440.0f;
		fslider73 = 0.0f;
		fbutton9 = 0.0;
		fslider74 = 0.0f;
		fslider75 = 0.0f;
		fslider76 = 0.0f;
		fslider77 = 0.0f;
		fslider78 = 1.0f;
		fslider79 = 440.0f;
		fslider80 = 0.0f;
		fbutton10 = 0.0;
		fslider81 = 0.0f;
		fslider82 = 0.0f;
		fslider83 = 0.0f;
		fslider84 = 0.0f;
		fslider85 = 1.0f;
		fslider86 = 440.0f;
		fslider87 = 0.0f;
		fslider88 = 0.0f;
		fbutton11 = 0.0;
		fslider89 = 0.0f;
		fslider90 = 0.0f;
		fslider91 = 1.0f;
		fslider92 = 0.0f;
		fslider93 = 1.0f;
		fslider94 = 440.0f;
		fslider95 = 0.0f;
		fbutton12 = 0.0;
		fslider96 = 0.0f;
		fslider97 = 0.0f;
		fslider98 = 0.0f;
		fslider99 = 0.0f;
		fslider100 = 1.0f;
		fslider101 = 440.0f;
		fslider102 = 0.0f;
		fbutton13 = 0.0;
		fslider103 = 0.0f;
		fslider104 = 0.0f;
		fslider105 = 0.0f;
		fslider106 = 0.0f;
		fslider107 = 1.0f;
		fslider108 = 440.0f;
		fslider109 = 0.0f;
		fbutton14 = 0.0;
		fslider110 = 0.0f;
		fslider111 = 0.0f;
		fslider112 = 0.0f;
		fslider113 = 0.0f;
		fslider114 = 1.0f;
		fslider115 = 440.0f;
		fslider116 = 0.0f;
		fslider117 = 0.0f;
		fbutton15 = 0.0;
		fslider118 = 0.0f;
		fslider119 = 0.0f;
		fslider120 = 1.0f;
		fslider121 = 0.0f;
		fslider122 = 1.0f;
		fslider123 = 440.0f;
		fslider124 = 0.0f;
		fbutton16 = 0.0;
		fslider125 = 0.0f;
		fslider126 = 0.0f;
		fslider127 = 0.0f;
		fslider128 = 0.0f;
		fslider129 = 1.0f;
		fslider130 = 440.0f;
		fslider131 = 0.0f;
		fbutton17 = 0.0;
		fslider132 = 0.0f;
		fslider133 = 0.0f;
		fslider134 = 0.0f;
		fslider135 = 0.0f;
		fslider136 = 1.0f;
		fslider137 = 440.0f;
		fslider138 = 0.0f;
		fbutton18 = 0.0;
		fslider139 = 0.0f;
		fslider140 = 0.0f;
		fslider141 = 0.0f;
		fslider142 = 0.0f;
		fslider143 = 1.0f;
		fslider144 = 440.0f;
		fslider145 = 0.0f;
		fslider146 = 0.0f;
		fbutton19 = 0.0;
		fslider147 = 0.0f;
		fslider148 = 0.0f;
		fslider149 = 1.0f;
		fslider150 = 0.0f;
		fslider151 = 1.0f;
		fslider152 = 440.0f;
		fslider153 = 0.0f;
		fslider154 = 0.0f;
		fbutton20 = 0.0;
		fslider155 = 0.0f;
		fslider156 = 0.0f;
		fslider157 = 1.0f;
		fslider158 = 0.0f;
		fslider159 = 1.0f;
		fslider160 = 440.0f;
		fslider161 = 0.0f;
		fslider162 = 0.0f;
		fbutton21 = 0.0;
		fslider163 = 0.0f;
		fslider164 = 0.0f;
		fslider165 = 1.0f;
		fslider166 = 0.0f;
		fslider167 = 1.0f;
		fslider168 = 440.0f;
		fslider169 = 0.0f;
		fslider170 = 0.0f;
		fbutton22 = 0.0;
		fslider171 = 0.0f;
		fslider172 = 0.0f;
		fslider173 = 1.0f;
		fslider174 = 0.0f;
		fslider175 = 1.0f;
		fslider176 = 440.0f;
		fslider177 = 0.0f;
		fslider178 = 0.0f;
		fbutton23 = 0.0;
		fslider179 = 0.0f;
		fslider180 = 0.0f;
		fslider181 = 1.0f;
		fslider182 = 0.0f;
		fslider183 = 0.0f;
		fslider184 = 0.0f;
		fslider185 = 0.0f;
		fslider186 = 0.0f;
		fslider187 = 0.0f;
		fslider188 = 0.0f;
		fslider189 = 0.0f;
		fslider190 = 0.0f;
		fslider191 = 0.0f;
		fslider192 = 0.0f;
		fslider193 = 0.0f;
		fslider194 = 1.0f;
		fslider195 = 0.0f;
		fslider196 = 0.0f;
		fslider197 = 0.0f;
		fslider198 = 1.0f;
		fslider199 = 0.0f;
		fslider200 = 0.0f;
		fslider201 = 0.0f;
		fslider202 = 1.0f;
		fslider203 = 0.0f;
		fslider204 = 0.0f;
		fslider205 = 0.0f;
		fslider206 = 1.0f;
		fslider207 = 0.0f;
		fslider208 = 0.0f;
		fslider209 = 0.0f;
		fslider210 = 1.0f;
		fslider211 = 0.0f;
		fslider212 = 0.0f;
		fslider213 = 0.0f;
		fslider214 = 1.0f;
		fslider215 = 0.0f;
		fslider216 = 0.0f;
		fslider217 = 0.0f;
		fslider218 = 1.0f;
		fslider219 = 0.0f;
		fslider220 = 0.0f;
		fslider221 = 0.0f;
		fslider222 = 1.0f;
		fslider223 = 0.0f;
		fslider224 = 0.0f;
		fslider225 = 0.0f;
		fslider226 = 1.0f;
		fslider227 = 0.0f;
		fslider228 = 0.0f;
		fslider229 = 0.0f;
		fslider230 = 1.0f;
		fslider231 = 0.0f;
		fslider232 = 0.0f;
		fslider233 = 0.0f;
		fslider234 = 1.0f;
		fslider235 = 0.0f;
		fslider236 = 0.0f;
		fslider237 = 0.0f;
		fslider238 = 1.0f;
		fslider239 = 0.0f;
		fslider240 = 0.0f;
		fslider241 = 0.0f;
		fslider242 = 1.0f;
		fslider243 = 0.0f;
		fslider244 = 0.0f;
		fslider245 = 0.0f;
		fslider246 = 1.0f;
		fslider247 = 0.0f;
		fslider248 = 0.0f;
		fslider249 = 0.0f;
		fslider250 = 1.0f;
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
		for (int i=0; i<2; i++) iRec98[i] = 0;
		for (int i=0; i<2; i++) fRec97[i] = 0;
		for (int i=0; i<2; i++) iRec100[i] = 0;
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) iRec102[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) iRec104[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) iRec106[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<2; i++) iRec108[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) iRec110[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<2; i++) iRec112[i] = 0;
		for (int i=0; i<2; i++) fRec111[i] = 0;
		for (int i=0; i<2; i++) iRec114[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) iRec116[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<2; i++) iRec118[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<2; i++) iRec120[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) iRec122[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<2; i++) iRec124[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
		for (int i=0; i<2; i++) iRec126[i] = 0;
		for (int i=0; i<2; i++) fRec125[i] = 0;
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
		ui_interface->addHorizontalSlider("Attack", &fslider29, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider27, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider26, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider30, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider178, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider177, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider179, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider174, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider176, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider180, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider175, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton23);
		ui_interface->addHorizontalSlider("velocity", &fslider181, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider170, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider169, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider171, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider166, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider168, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider186, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider187, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider185, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider172, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider167, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton22);
		ui_interface->addHorizontalSlider("velocity", &fslider173, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider162, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider161, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider163, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider158, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider160, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider189, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider190, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider188, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider164, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider159, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton21);
		ui_interface->addHorizontalSlider("velocity", &fslider165, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider154, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider153, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider155, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider150, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider152, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider183, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider184, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider182, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider156, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider151, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton20);
		ui_interface->addHorizontalSlider("velocity", &fslider157, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider117, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider116, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider118, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider113, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider115, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider119, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider114, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton15);
		ui_interface->addHorizontalSlider("velocity", &fslider120, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider204, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider203, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider205, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider106, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider108, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider110, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider111, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider109, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider112, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider107, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton14);
		ui_interface->addHorizontalSlider("velocity", &fslider206, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider208, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider207, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider209, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider99, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider101, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider103, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider104, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider102, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider105, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider100, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton13);
		ui_interface->addHorizontalSlider("velocity", &fslider210, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider212, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider211, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider213, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider92, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider94, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider96, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider97, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider95, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider98, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider93, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton12);
		ui_interface->addHorizontalSlider("velocity", &fslider214, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider59, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider58, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider60, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider55, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider57, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider61, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider56, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton7);
		ui_interface->addHorizontalSlider("velocity", &fslider62, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider228, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider227, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider229, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider48, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider50, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider52, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider53, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider51, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider54, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider49, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton6);
		ui_interface->addHorizontalSlider("velocity", &fslider230, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider232, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider231, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider233, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider41, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider43, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider45, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider46, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider44, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider47, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider42, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider234, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider236, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider235, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider237, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider34, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider36, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider38, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider39, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider37, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider40, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider35, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider238, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider146, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider145, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider147, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider142, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider144, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider148, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider143, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton19);
		ui_interface->addHorizontalSlider("velocity", &fslider149, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider192, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider191, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider193, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider135, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider137, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider139, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider140, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider138, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider141, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider136, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton18);
		ui_interface->addHorizontalSlider("velocity", &fslider194, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider196, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider195, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider197, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider128, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider130, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider132, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider133, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider131, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider134, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider129, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton17);
		ui_interface->addHorizontalSlider("velocity", &fslider198, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider200, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider199, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider201, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider121, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider123, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider125, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider126, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider124, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider127, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider122, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton16);
		ui_interface->addHorizontalSlider("velocity", &fslider202, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider88, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider87, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider89, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider84, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider86, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider90, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider85, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton11);
		ui_interface->addHorizontalSlider("velocity", &fslider91, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider216, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider215, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider217, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider77, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider79, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider81, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider82, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider80, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider83, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider78, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton10);
		ui_interface->addHorizontalSlider("velocity", &fslider218, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider220, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider219, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider221, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider70, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider72, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider74, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider75, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider73, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider76, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider71, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton9);
		ui_interface->addHorizontalSlider("velocity", &fslider222, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider224, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider223, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider225, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider63, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider65, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider67, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider68, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider66, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider69, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider64, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton8);
		ui_interface->addHorizontalSlider("velocity", &fslider226, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider28, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider25, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider31, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider22, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider24, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("outLev", &fslider32, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider23, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider33, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider240, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider239, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider241, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider15, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider17, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider19, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider20, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider18, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider21, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider16, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider242, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider244, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider243, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider245, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider8, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider10, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider12, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider13, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider11, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider14, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider9, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider246, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider248, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider247, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider249, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider1, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider3, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider5, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider6, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider7, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider2, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider250, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
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
		float 	fSlow12 = (fConst1 * ((float(fslider3) * float(fslider2)) + (25.0f * float(fslider1))));
		float 	fSlow13 = float(fslider4);
		float 	fSlow14 = float(fbutton0);
		float 	fSlow15 = (fSlow14 * fSlow13);
		float 	fSlow16 = float(fslider5);
		float 	fSlow17 = (fConst2 * fSlow16);
		float 	fSlow18 = float(fslider6);
		float 	fSlow19 = (((1.0f - fSlow13) * fSlow18) + fSlow16);
		float 	fSlow20 = (fConst2 * fSlow19);
		int 	iSlow21 = int(((fSlow14 == 0.0f) > 0));
		float 	fSlow22 = ((fSlow15 + -1.0f) / (0 - (fConst2 * (fSlow16 - fSlow19))));
		float 	fSlow23 = (fConst3 / fSlow16);
		int 	iSlow24 = (fSlow14 > 0.0f);
		float 	fSlow25 = float(iSlow24);
		int 	iSlow26 = int(iSlow24);
		float 	fSlow27 = max(0.001f, (fConst2 * (fSlow13 * fSlow18)));
		int 	iSlow28 = int((iSlow24 > 0));
		float 	fSlow29 = (1.0f / fSlow27);
		float 	fSlow30 = float(fslider7);
		float 	fSlow31 = (fConst1 * ((float(fslider10) * float(fslider9)) + (25.0f * float(fslider8))));
		float 	fSlow32 = float(fslider11);
		float 	fSlow33 = float(fbutton1);
		float 	fSlow34 = (fSlow33 * fSlow32);
		float 	fSlow35 = float(fslider12);
		float 	fSlow36 = (fConst2 * fSlow35);
		float 	fSlow37 = float(fslider13);
		float 	fSlow38 = (((1.0f - fSlow32) * fSlow37) + fSlow35);
		float 	fSlow39 = (fConst2 * fSlow38);
		int 	iSlow40 = int(((fSlow33 == 0.0f) > 0));
		float 	fSlow41 = ((fSlow34 + -1.0f) / (0 - (fConst2 * (fSlow35 - fSlow38))));
		float 	fSlow42 = (fConst3 / fSlow35);
		int 	iSlow43 = (fSlow33 > 0.0f);
		float 	fSlow44 = float(iSlow43);
		int 	iSlow45 = int(iSlow43);
		float 	fSlow46 = max(0.001f, (fConst2 * (fSlow32 * fSlow37)));
		int 	iSlow47 = int((iSlow43 > 0));
		float 	fSlow48 = (1.0f / fSlow46);
		float 	fSlow49 = float(fslider14);
		float 	fSlow50 = (fConst1 * ((float(fslider17) * float(fslider16)) + (25.0f * float(fslider15))));
		float 	fSlow51 = float(fslider18);
		float 	fSlow52 = float(fbutton2);
		float 	fSlow53 = (fSlow52 * fSlow51);
		float 	fSlow54 = float(fslider19);
		float 	fSlow55 = (fConst2 * fSlow54);
		float 	fSlow56 = float(fslider20);
		float 	fSlow57 = (((1.0f - fSlow51) * fSlow56) + fSlow54);
		float 	fSlow58 = (fConst2 * fSlow57);
		int 	iSlow59 = int(((fSlow52 == 0.0f) > 0));
		float 	fSlow60 = ((fSlow53 + -1.0f) / (0 - (fConst2 * (fSlow54 - fSlow57))));
		float 	fSlow61 = (fConst3 / fSlow54);
		int 	iSlow62 = (fSlow52 > 0.0f);
		float 	fSlow63 = float(iSlow62);
		int 	iSlow64 = int(iSlow62);
		float 	fSlow65 = max(0.001f, (fConst2 * (fSlow51 * fSlow56)));
		int 	iSlow66 = int((iSlow62 > 0));
		float 	fSlow67 = (1.0f / fSlow65);
		float 	fSlow68 = float(fslider21);
		float 	fSlow69 = (fConst1 * ((float(fslider24) * float(fslider23)) + (25.0f * float(fslider22))));
		float 	fSlow70 = float(fslider26);
		float 	fSlow71 = max((float)0, (fSlow70 + float(fslider25)));
		float 	fSlow72 = float(fslider27);
		float 	fSlow73 = float(fslider29);
		float 	fSlow74 = max((float)0, (fSlow73 + float(fslider28)));
		float 	fSlow75 = (6.9100000000000001f * fSlow74);
		int 	iSlow76 = int((fConst0 * fSlow74));
		int 	iSlow77 = (float(fbutton3) > 0.0f);
		int 	iSlow78 = int(iSlow77);
		float 	fSlow79 = float(fslider30);
		float 	fSlow80 = (float(iSlow77) * max((float)0, ((0.5f * float(fslider31)) + fSlow79)));
		float 	fSlow81 = (float(fslider33) * float(fslider32));
		float 	fSlow82 = (fConst1 * ((float(fslider36) * float(fslider35)) + (25.0f * float(fslider34))));
		float 	fSlow83 = float(fslider37);
		float 	fSlow84 = float(fbutton4);
		float 	fSlow85 = (fSlow84 * fSlow83);
		float 	fSlow86 = float(fslider38);
		float 	fSlow87 = (fConst2 * fSlow86);
		float 	fSlow88 = float(fslider39);
		float 	fSlow89 = (((1.0f - fSlow83) * fSlow88) + fSlow86);
		float 	fSlow90 = (fConst2 * fSlow89);
		int 	iSlow91 = int(((fSlow84 == 0.0f) > 0));
		float 	fSlow92 = ((fSlow85 + -1.0f) / (0 - (fConst2 * (fSlow86 - fSlow89))));
		float 	fSlow93 = (fConst3 / fSlow86);
		int 	iSlow94 = (fSlow84 > 0.0f);
		float 	fSlow95 = float(iSlow94);
		int 	iSlow96 = int(iSlow94);
		float 	fSlow97 = max(0.001f, (fConst2 * (fSlow83 * fSlow88)));
		int 	iSlow98 = int((iSlow94 > 0));
		float 	fSlow99 = (1.0f / fSlow97);
		float 	fSlow100 = float(fslider40);
		float 	fSlow101 = (fConst1 * ((float(fslider43) * float(fslider42)) + (25.0f * float(fslider41))));
		float 	fSlow102 = float(fslider44);
		float 	fSlow103 = float(fbutton5);
		float 	fSlow104 = (fSlow103 * fSlow102);
		float 	fSlow105 = float(fslider45);
		float 	fSlow106 = (fConst2 * fSlow105);
		float 	fSlow107 = float(fslider46);
		float 	fSlow108 = (((1.0f - fSlow102) * fSlow107) + fSlow105);
		float 	fSlow109 = (fConst2 * fSlow108);
		int 	iSlow110 = int(((fSlow103 == 0.0f) > 0));
		float 	fSlow111 = ((fSlow104 + -1.0f) / (0 - (fConst2 * (fSlow105 - fSlow108))));
		float 	fSlow112 = (fConst3 / fSlow105);
		int 	iSlow113 = (fSlow103 > 0.0f);
		float 	fSlow114 = float(iSlow113);
		int 	iSlow115 = int(iSlow113);
		float 	fSlow116 = max(0.001f, (fConst2 * (fSlow102 * fSlow107)));
		int 	iSlow117 = int((iSlow113 > 0));
		float 	fSlow118 = (1.0f / fSlow116);
		float 	fSlow119 = float(fslider47);
		float 	fSlow120 = (fConst1 * ((float(fslider50) * float(fslider49)) + (25.0f * float(fslider48))));
		float 	fSlow121 = float(fslider51);
		float 	fSlow122 = float(fbutton6);
		float 	fSlow123 = (fSlow122 * fSlow121);
		float 	fSlow124 = float(fslider52);
		float 	fSlow125 = (fConst2 * fSlow124);
		float 	fSlow126 = float(fslider53);
		float 	fSlow127 = (((1.0f - fSlow121) * fSlow126) + fSlow124);
		float 	fSlow128 = (fConst2 * fSlow127);
		int 	iSlow129 = int(((fSlow122 == 0.0f) > 0));
		float 	fSlow130 = ((fSlow123 + -1.0f) / (0 - (fConst2 * (fSlow124 - fSlow127))));
		float 	fSlow131 = (fConst3 / fSlow124);
		int 	iSlow132 = (fSlow122 > 0.0f);
		float 	fSlow133 = float(iSlow132);
		int 	iSlow134 = int(iSlow132);
		float 	fSlow135 = max(0.001f, (fConst2 * (fSlow121 * fSlow126)));
		int 	iSlow136 = int((iSlow132 > 0));
		float 	fSlow137 = (1.0f / fSlow135);
		float 	fSlow138 = float(fslider54);
		float 	fSlow139 = (fConst1 * ((float(fslider57) * float(fslider56)) + (25.0f * float(fslider55))));
		float 	fSlow140 = max((float)0, (fSlow70 + float(fslider58)));
		float 	fSlow141 = max((float)0, (fSlow73 + float(fslider59)));
		float 	fSlow142 = (6.9100000000000001f * fSlow141);
		int 	iSlow143 = int((fConst0 * fSlow141));
		int 	iSlow144 = (float(fbutton7) > 0.0f);
		int 	iSlow145 = int(iSlow144);
		float 	fSlow146 = (float(iSlow144) * max((float)0, ((0.5f * float(fslider60)) + fSlow79)));
		float 	fSlow147 = (float(fslider62) * float(fslider61));
		float 	fSlow148 = (fConst1 * ((float(fslider65) * float(fslider64)) + (25.0f * float(fslider63))));
		float 	fSlow149 = float(fslider66);
		float 	fSlow150 = float(fbutton8);
		float 	fSlow151 = (fSlow150 * fSlow149);
		float 	fSlow152 = float(fslider67);
		float 	fSlow153 = (fConst2 * fSlow152);
		float 	fSlow154 = float(fslider68);
		float 	fSlow155 = (((1.0f - fSlow149) * fSlow154) + fSlow152);
		float 	fSlow156 = (fConst2 * fSlow155);
		int 	iSlow157 = int(((fSlow150 == 0.0f) > 0));
		float 	fSlow158 = ((fSlow151 + -1.0f) / (0 - (fConst2 * (fSlow152 - fSlow155))));
		float 	fSlow159 = (fConst3 / fSlow152);
		int 	iSlow160 = (fSlow150 > 0.0f);
		float 	fSlow161 = float(iSlow160);
		int 	iSlow162 = int(iSlow160);
		float 	fSlow163 = max(0.001f, (fConst2 * (fSlow149 * fSlow154)));
		int 	iSlow164 = int((iSlow160 > 0));
		float 	fSlow165 = (1.0f / fSlow163);
		float 	fSlow166 = float(fslider69);
		float 	fSlow167 = (fConst1 * ((float(fslider72) * float(fslider71)) + (25.0f * float(fslider70))));
		float 	fSlow168 = float(fslider73);
		float 	fSlow169 = float(fbutton9);
		float 	fSlow170 = (fSlow169 * fSlow168);
		float 	fSlow171 = float(fslider74);
		float 	fSlow172 = (fConst2 * fSlow171);
		float 	fSlow173 = float(fslider75);
		float 	fSlow174 = (((1.0f - fSlow168) * fSlow173) + fSlow171);
		float 	fSlow175 = (fConst2 * fSlow174);
		int 	iSlow176 = int(((fSlow169 == 0.0f) > 0));
		float 	fSlow177 = ((fSlow170 + -1.0f) / (0 - (fConst2 * (fSlow171 - fSlow174))));
		float 	fSlow178 = (fConst3 / fSlow171);
		int 	iSlow179 = (fSlow169 > 0.0f);
		float 	fSlow180 = float(iSlow179);
		int 	iSlow181 = int(iSlow179);
		float 	fSlow182 = max(0.001f, (fConst2 * (fSlow168 * fSlow173)));
		int 	iSlow183 = int((iSlow179 > 0));
		float 	fSlow184 = (1.0f / fSlow182);
		float 	fSlow185 = float(fslider76);
		float 	fSlow186 = (fConst1 * ((float(fslider79) * float(fslider78)) + (25.0f * float(fslider77))));
		float 	fSlow187 = float(fslider80);
		float 	fSlow188 = float(fbutton10);
		float 	fSlow189 = (fSlow188 * fSlow187);
		float 	fSlow190 = float(fslider81);
		float 	fSlow191 = (fConst2 * fSlow190);
		float 	fSlow192 = float(fslider82);
		float 	fSlow193 = (((1.0f - fSlow187) * fSlow192) + fSlow190);
		float 	fSlow194 = (fConst2 * fSlow193);
		int 	iSlow195 = int(((fSlow188 == 0.0f) > 0));
		float 	fSlow196 = ((fSlow189 + -1.0f) / (0 - (fConst2 * (fSlow190 - fSlow193))));
		float 	fSlow197 = (fConst3 / fSlow190);
		int 	iSlow198 = (fSlow188 > 0.0f);
		float 	fSlow199 = float(iSlow198);
		int 	iSlow200 = int(iSlow198);
		float 	fSlow201 = max(0.001f, (fConst2 * (fSlow187 * fSlow192)));
		int 	iSlow202 = int((iSlow198 > 0));
		float 	fSlow203 = (1.0f / fSlow201);
		float 	fSlow204 = float(fslider83);
		float 	fSlow205 = (fConst1 * ((float(fslider86) * float(fslider85)) + (25.0f * float(fslider84))));
		float 	fSlow206 = max((float)0, (fSlow70 + float(fslider87)));
		float 	fSlow207 = max((float)0, (fSlow73 + float(fslider88)));
		float 	fSlow208 = (6.9100000000000001f * fSlow207);
		int 	iSlow209 = int((fConst0 * fSlow207));
		int 	iSlow210 = (float(fbutton11) > 0.0f);
		int 	iSlow211 = int(iSlow210);
		float 	fSlow212 = (float(iSlow210) * max((float)0, ((0.5f * float(fslider89)) + fSlow79)));
		float 	fSlow213 = (float(fslider91) * float(fslider90));
		float 	fSlow214 = (fConst1 * ((float(fslider94) * float(fslider93)) + (25.0f * float(fslider92))));
		float 	fSlow215 = float(fslider95);
		float 	fSlow216 = float(fbutton12);
		float 	fSlow217 = (fSlow216 * fSlow215);
		float 	fSlow218 = float(fslider96);
		float 	fSlow219 = (fConst2 * fSlow218);
		float 	fSlow220 = float(fslider97);
		float 	fSlow221 = (((1.0f - fSlow215) * fSlow220) + fSlow218);
		float 	fSlow222 = (fConst2 * fSlow221);
		int 	iSlow223 = int(((fSlow216 == 0.0f) > 0));
		float 	fSlow224 = ((fSlow217 + -1.0f) / (0 - (fConst2 * (fSlow218 - fSlow221))));
		float 	fSlow225 = (fConst3 / fSlow218);
		int 	iSlow226 = (fSlow216 > 0.0f);
		float 	fSlow227 = float(iSlow226);
		int 	iSlow228 = int(iSlow226);
		float 	fSlow229 = max(0.001f, (fConst2 * (fSlow215 * fSlow220)));
		int 	iSlow230 = int((iSlow226 > 0));
		float 	fSlow231 = (1.0f / fSlow229);
		float 	fSlow232 = float(fslider98);
		float 	fSlow233 = (fConst1 * ((float(fslider101) * float(fslider100)) + (25.0f * float(fslider99))));
		float 	fSlow234 = float(fslider102);
		float 	fSlow235 = float(fbutton13);
		float 	fSlow236 = (fSlow235 * fSlow234);
		float 	fSlow237 = float(fslider103);
		float 	fSlow238 = (fConst2 * fSlow237);
		float 	fSlow239 = float(fslider104);
		float 	fSlow240 = (((1.0f - fSlow234) * fSlow239) + fSlow237);
		float 	fSlow241 = (fConst2 * fSlow240);
		int 	iSlow242 = int(((fSlow235 == 0.0f) > 0));
		float 	fSlow243 = ((fSlow236 + -1.0f) / (0 - (fConst2 * (fSlow237 - fSlow240))));
		float 	fSlow244 = (fConst3 / fSlow237);
		int 	iSlow245 = (fSlow235 > 0.0f);
		float 	fSlow246 = float(iSlow245);
		int 	iSlow247 = int(iSlow245);
		float 	fSlow248 = max(0.001f, (fConst2 * (fSlow234 * fSlow239)));
		int 	iSlow249 = int((iSlow245 > 0));
		float 	fSlow250 = (1.0f / fSlow248);
		float 	fSlow251 = float(fslider105);
		float 	fSlow252 = (fConst1 * ((float(fslider108) * float(fslider107)) + (25.0f * float(fslider106))));
		float 	fSlow253 = float(fslider109);
		float 	fSlow254 = float(fbutton14);
		float 	fSlow255 = (fSlow254 * fSlow253);
		float 	fSlow256 = float(fslider110);
		float 	fSlow257 = (fConst2 * fSlow256);
		float 	fSlow258 = float(fslider111);
		float 	fSlow259 = (((1.0f - fSlow253) * fSlow258) + fSlow256);
		float 	fSlow260 = (fConst2 * fSlow259);
		int 	iSlow261 = int(((fSlow254 == 0.0f) > 0));
		float 	fSlow262 = ((fSlow255 + -1.0f) / (0 - (fConst2 * (fSlow256 - fSlow259))));
		float 	fSlow263 = (fConst3 / fSlow256);
		int 	iSlow264 = (fSlow254 > 0.0f);
		float 	fSlow265 = float(iSlow264);
		int 	iSlow266 = int(iSlow264);
		float 	fSlow267 = max(0.001f, (fConst2 * (fSlow253 * fSlow258)));
		int 	iSlow268 = int((iSlow264 > 0));
		float 	fSlow269 = (1.0f / fSlow267);
		float 	fSlow270 = float(fslider112);
		float 	fSlow271 = (fConst1 * ((float(fslider115) * float(fslider114)) + (25.0f * float(fslider113))));
		float 	fSlow272 = max((float)0, (fSlow70 + float(fslider116)));
		float 	fSlow273 = max((float)0, (fSlow73 + float(fslider117)));
		float 	fSlow274 = (6.9100000000000001f * fSlow273);
		int 	iSlow275 = int((fConst0 * fSlow273));
		int 	iSlow276 = (float(fbutton15) > 0.0f);
		int 	iSlow277 = int(iSlow276);
		float 	fSlow278 = (float(iSlow276) * max((float)0, ((0.5f * float(fslider118)) + fSlow79)));
		float 	fSlow279 = (float(fslider120) * float(fslider119));
		float 	fSlow280 = (fConst1 * ((float(fslider123) * float(fslider122)) + (25.0f * float(fslider121))));
		float 	fSlow281 = float(fslider124);
		float 	fSlow282 = float(fbutton16);
		float 	fSlow283 = (fSlow282 * fSlow281);
		float 	fSlow284 = float(fslider125);
		float 	fSlow285 = (fConst2 * fSlow284);
		float 	fSlow286 = float(fslider126);
		float 	fSlow287 = (((1.0f - fSlow281) * fSlow286) + fSlow284);
		float 	fSlow288 = (fConst2 * fSlow287);
		int 	iSlow289 = int(((fSlow282 == 0.0f) > 0));
		float 	fSlow290 = ((fSlow283 + -1.0f) / (0 - (fConst2 * (fSlow284 - fSlow287))));
		float 	fSlow291 = (fConst3 / fSlow284);
		int 	iSlow292 = (fSlow282 > 0.0f);
		float 	fSlow293 = float(iSlow292);
		int 	iSlow294 = int(iSlow292);
		float 	fSlow295 = max(0.001f, (fConst2 * (fSlow281 * fSlow286)));
		int 	iSlow296 = int((iSlow292 > 0));
		float 	fSlow297 = (1.0f / fSlow295);
		float 	fSlow298 = float(fslider127);
		float 	fSlow299 = (fConst1 * ((float(fslider130) * float(fslider129)) + (25.0f * float(fslider128))));
		float 	fSlow300 = float(fslider131);
		float 	fSlow301 = float(fbutton17);
		float 	fSlow302 = (fSlow301 * fSlow300);
		float 	fSlow303 = float(fslider132);
		float 	fSlow304 = (fConst2 * fSlow303);
		float 	fSlow305 = float(fslider133);
		float 	fSlow306 = (((1.0f - fSlow300) * fSlow305) + fSlow303);
		float 	fSlow307 = (fConst2 * fSlow306);
		int 	iSlow308 = int(((fSlow301 == 0.0f) > 0));
		float 	fSlow309 = ((fSlow302 + -1.0f) / (0 - (fConst2 * (fSlow303 - fSlow306))));
		float 	fSlow310 = (fConst3 / fSlow303);
		int 	iSlow311 = (fSlow301 > 0.0f);
		float 	fSlow312 = float(iSlow311);
		int 	iSlow313 = int(iSlow311);
		float 	fSlow314 = max(0.001f, (fConst2 * (fSlow300 * fSlow305)));
		int 	iSlow315 = int((iSlow311 > 0));
		float 	fSlow316 = (1.0f / fSlow314);
		float 	fSlow317 = float(fslider134);
		float 	fSlow318 = (fConst1 * ((float(fslider137) * float(fslider136)) + (25.0f * float(fslider135))));
		float 	fSlow319 = float(fslider138);
		float 	fSlow320 = float(fbutton18);
		float 	fSlow321 = (fSlow320 * fSlow319);
		float 	fSlow322 = float(fslider139);
		float 	fSlow323 = (fConst2 * fSlow322);
		float 	fSlow324 = float(fslider140);
		float 	fSlow325 = (((1.0f - fSlow319) * fSlow324) + fSlow322);
		float 	fSlow326 = (fConst2 * fSlow325);
		int 	iSlow327 = int(((fSlow320 == 0.0f) > 0));
		float 	fSlow328 = ((fSlow321 + -1.0f) / (0 - (fConst2 * (fSlow322 - fSlow325))));
		float 	fSlow329 = (fConst3 / fSlow322);
		int 	iSlow330 = (fSlow320 > 0.0f);
		float 	fSlow331 = float(iSlow330);
		int 	iSlow332 = int(iSlow330);
		float 	fSlow333 = max(0.001f, (fConst2 * (fSlow319 * fSlow324)));
		int 	iSlow334 = int((iSlow330 > 0));
		float 	fSlow335 = (1.0f / fSlow333);
		float 	fSlow336 = float(fslider141);
		float 	fSlow337 = (fConst1 * ((float(fslider144) * float(fslider143)) + (25.0f * float(fslider142))));
		float 	fSlow338 = max((float)0, (fSlow70 + float(fslider145)));
		float 	fSlow339 = max((float)0, (fSlow73 + float(fslider146)));
		float 	fSlow340 = (6.9100000000000001f * fSlow339);
		int 	iSlow341 = int((fConst0 * fSlow339));
		int 	iSlow342 = (float(fbutton19) > 0.0f);
		int 	iSlow343 = int(iSlow342);
		float 	fSlow344 = (float(iSlow342) * max((float)0, ((0.5f * float(fslider147)) + fSlow79)));
		float 	fSlow345 = (float(fslider149) * float(fslider148));
		float 	fSlow346 = (fConst1 * ((float(fslider152) * float(fslider151)) + (25.0f * float(fslider150))));
		float 	fSlow347 = max((float)0, (fSlow70 + float(fslider153)));
		float 	fSlow348 = max((float)0, (fSlow73 + float(fslider154)));
		float 	fSlow349 = (6.9100000000000001f * fSlow348);
		int 	iSlow350 = int((fConst0 * fSlow348));
		float 	fSlow351 = float(fbutton20);
		int 	iSlow352 = (fSlow351 > 0.0f);
		int 	iSlow353 = int(iSlow352);
		float 	fSlow354 = float(iSlow352);
		float 	fSlow355 = (fSlow354 * max((float)0, ((0.5f * float(fslider155)) + fSlow79)));
		float 	fSlow356 = float(fslider156);
		float 	fSlow357 = (float(fslider157) * fSlow356);
		float 	fSlow358 = (fConst1 * ((float(fslider160) * float(fslider159)) + (25.0f * float(fslider158))));
		float 	fSlow359 = max((float)0, (fSlow70 + float(fslider161)));
		float 	fSlow360 = max((float)0, (fSlow73 + float(fslider162)));
		float 	fSlow361 = (6.9100000000000001f * fSlow360);
		int 	iSlow362 = int((fConst0 * fSlow360));
		float 	fSlow363 = float(fbutton21);
		int 	iSlow364 = (fSlow363 > 0.0f);
		int 	iSlow365 = int(iSlow364);
		float 	fSlow366 = float(iSlow364);
		float 	fSlow367 = (fSlow366 * max((float)0, ((0.5f * float(fslider163)) + fSlow79)));
		float 	fSlow368 = float(fslider164);
		float 	fSlow369 = (float(fslider165) * fSlow368);
		float 	fSlow370 = (fConst1 * ((float(fslider168) * float(fslider167)) + (25.0f * float(fslider166))));
		float 	fSlow371 = max((float)0, (fSlow70 + float(fslider169)));
		float 	fSlow372 = max((float)0, (fSlow73 + float(fslider170)));
		float 	fSlow373 = (6.9100000000000001f * fSlow372);
		int 	iSlow374 = int((fConst0 * fSlow372));
		float 	fSlow375 = float(fbutton22);
		int 	iSlow376 = (fSlow375 > 0.0f);
		int 	iSlow377 = int(iSlow376);
		float 	fSlow378 = float(iSlow376);
		float 	fSlow379 = (fSlow378 * max((float)0, ((0.5f * float(fslider171)) + fSlow79)));
		float 	fSlow380 = float(fslider172);
		float 	fSlow381 = (float(fslider173) * fSlow380);
		float 	fSlow382 = (fConst1 * ((float(fslider176) * float(fslider175)) + (25.0f * float(fslider174))));
		float 	fSlow383 = max((float)0, (fSlow70 + float(fslider177)));
		float 	fSlow384 = max((float)0, (fSlow73 + float(fslider178)));
		float 	fSlow385 = (6.9100000000000001f * fSlow384);
		int 	iSlow386 = int((fConst0 * fSlow384));
		int 	iSlow387 = (float(fbutton23) > 0.0f);
		int 	iSlow388 = int(iSlow387);
		float 	fSlow389 = (float(iSlow387) * max((float)0, ((0.5f * float(fslider179)) + fSlow79)));
		float 	fSlow390 = (float(fslider181) * float(fslider180));
		float 	fSlow391 = float(fslider182);
		float 	fSlow392 = (fSlow351 * fSlow391);
		float 	fSlow393 = float(fslider183);
		float 	fSlow394 = (fConst2 * fSlow393);
		float 	fSlow395 = float(fslider184);
		float 	fSlow396 = (((1.0f - fSlow391) * fSlow395) + fSlow393);
		float 	fSlow397 = (fConst2 * fSlow396);
		int 	iSlow398 = int(((fSlow351 == 0.0f) > 0));
		float 	fSlow399 = ((fSlow392 + -1.0f) / (0 - (fConst2 * (fSlow393 - fSlow396))));
		float 	fSlow400 = (fConst3 / fSlow393);
		float 	fSlow401 = max(0.001f, (fConst2 * (fSlow391 * fSlow395)));
		int 	iSlow402 = int((iSlow352 > 0));
		float 	fSlow403 = (1.0f / fSlow401);
		float 	fSlow404 = float(fslider185);
		float 	fSlow405 = (fSlow375 * fSlow404);
		float 	fSlow406 = float(fslider186);
		float 	fSlow407 = (fConst2 * fSlow406);
		float 	fSlow408 = float(fslider187);
		float 	fSlow409 = (((1.0f - fSlow404) * fSlow408) + fSlow406);
		float 	fSlow410 = (fConst2 * fSlow409);
		int 	iSlow411 = int(((fSlow375 == 0.0f) > 0));
		float 	fSlow412 = ((fSlow405 + -1.0f) / (0 - (fConst2 * (fSlow406 - fSlow409))));
		float 	fSlow413 = (fConst3 / fSlow406);
		float 	fSlow414 = max(0.001f, (fConst2 * (fSlow404 * fSlow408)));
		int 	iSlow415 = int((iSlow376 > 0));
		float 	fSlow416 = (1.0f / fSlow414);
		float 	fSlow417 = float(fslider188);
		float 	fSlow418 = (fSlow363 * fSlow417);
		float 	fSlow419 = float(fslider189);
		float 	fSlow420 = (fConst2 * fSlow419);
		float 	fSlow421 = float(fslider190);
		float 	fSlow422 = (((1.0f - fSlow417) * fSlow421) + fSlow419);
		float 	fSlow423 = (fConst2 * fSlow422);
		int 	iSlow424 = int(((fSlow363 == 0.0f) > 0));
		float 	fSlow425 = ((fSlow418 + -1.0f) / (0 - (fConst2 * (fSlow419 - fSlow422))));
		float 	fSlow426 = (fConst3 / fSlow419);
		float 	fSlow427 = max(0.001f, (fConst2 * (fSlow417 * fSlow421)));
		int 	iSlow428 = int((iSlow364 > 0));
		float 	fSlow429 = (1.0f / fSlow427);
		float 	fSlow430 = max((float)0, (fSlow70 + float(fslider191)));
		float 	fSlow431 = max((float)0, (fSlow73 + float(fslider192)));
		float 	fSlow432 = (6.9100000000000001f * fSlow431);
		int 	iSlow433 = int((fConst0 * fSlow431));
		float 	fSlow434 = (fSlow331 * max((float)0, ((0.5f * float(fslider193)) + fSlow79)));
		float 	fSlow435 = (float(fslider194) * fSlow336);
		float 	fSlow436 = max((float)0, (fSlow70 + float(fslider195)));
		float 	fSlow437 = max((float)0, (fSlow73 + float(fslider196)));
		float 	fSlow438 = (6.9100000000000001f * fSlow437);
		int 	iSlow439 = int((fConst0 * fSlow437));
		float 	fSlow440 = (fSlow312 * max((float)0, ((0.5f * float(fslider197)) + fSlow79)));
		float 	fSlow441 = (float(fslider198) * fSlow317);
		float 	fSlow442 = max((float)0, (fSlow70 + float(fslider199)));
		float 	fSlow443 = max((float)0, (fSlow73 + float(fslider200)));
		float 	fSlow444 = (6.9100000000000001f * fSlow443);
		int 	iSlow445 = int((fConst0 * fSlow443));
		float 	fSlow446 = (fSlow293 * max((float)0, ((0.5f * float(fslider201)) + fSlow79)));
		float 	fSlow447 = (float(fslider202) * fSlow298);
		float 	fSlow448 = max((float)0, (fSlow70 + float(fslider203)));
		float 	fSlow449 = max((float)0, (fSlow73 + float(fslider204)));
		float 	fSlow450 = (6.9100000000000001f * fSlow449);
		int 	iSlow451 = int((fConst0 * fSlow449));
		float 	fSlow452 = (fSlow265 * max((float)0, ((0.5f * float(fslider205)) + fSlow79)));
		float 	fSlow453 = (float(fslider206) * fSlow270);
		float 	fSlow454 = max((float)0, (fSlow70 + float(fslider207)));
		float 	fSlow455 = max((float)0, (fSlow73 + float(fslider208)));
		float 	fSlow456 = (6.9100000000000001f * fSlow455);
		int 	iSlow457 = int((fConst0 * fSlow455));
		float 	fSlow458 = (fSlow246 * max((float)0, ((0.5f * float(fslider209)) + fSlow79)));
		float 	fSlow459 = (float(fslider210) * fSlow251);
		float 	fSlow460 = max((float)0, (fSlow70 + float(fslider211)));
		float 	fSlow461 = max((float)0, (fSlow73 + float(fslider212)));
		float 	fSlow462 = (6.9100000000000001f * fSlow461);
		int 	iSlow463 = int((fConst0 * fSlow461));
		float 	fSlow464 = (fSlow227 * max((float)0, ((0.5f * float(fslider213)) + fSlow79)));
		float 	fSlow465 = (float(fslider214) * fSlow232);
		float 	fSlow466 = max((float)0, (fSlow70 + float(fslider215)));
		float 	fSlow467 = max((float)0, (fSlow73 + float(fslider216)));
		float 	fSlow468 = (6.9100000000000001f * fSlow467);
		int 	iSlow469 = int((fConst0 * fSlow467));
		float 	fSlow470 = (fSlow199 * max((float)0, ((0.5f * float(fslider217)) + fSlow79)));
		float 	fSlow471 = (float(fslider218) * fSlow204);
		float 	fSlow472 = max((float)0, (fSlow70 + float(fslider219)));
		float 	fSlow473 = max((float)0, (fSlow73 + float(fslider220)));
		float 	fSlow474 = (6.9100000000000001f * fSlow473);
		int 	iSlow475 = int((fConst0 * fSlow473));
		float 	fSlow476 = (fSlow180 * max((float)0, ((0.5f * float(fslider221)) + fSlow79)));
		float 	fSlow477 = (float(fslider222) * fSlow185);
		float 	fSlow478 = max((float)0, (fSlow70 + float(fslider223)));
		float 	fSlow479 = max((float)0, (fSlow73 + float(fslider224)));
		float 	fSlow480 = (6.9100000000000001f * fSlow479);
		int 	iSlow481 = int((fConst0 * fSlow479));
		float 	fSlow482 = (fSlow161 * max((float)0, ((0.5f * float(fslider225)) + fSlow79)));
		float 	fSlow483 = (float(fslider226) * fSlow166);
		float 	fSlow484 = max((float)0, (fSlow70 + float(fslider227)));
		float 	fSlow485 = max((float)0, (fSlow73 + float(fslider228)));
		float 	fSlow486 = (6.9100000000000001f * fSlow485);
		int 	iSlow487 = int((fConst0 * fSlow485));
		float 	fSlow488 = (fSlow133 * max((float)0, ((0.5f * float(fslider229)) + fSlow79)));
		float 	fSlow489 = (float(fslider230) * fSlow138);
		float 	fSlow490 = max((float)0, (fSlow70 + float(fslider231)));
		float 	fSlow491 = max((float)0, (fSlow73 + float(fslider232)));
		float 	fSlow492 = (6.9100000000000001f * fSlow491);
		int 	iSlow493 = int((fConst0 * fSlow491));
		float 	fSlow494 = (fSlow114 * max((float)0, ((0.5f * float(fslider233)) + fSlow79)));
		float 	fSlow495 = (float(fslider234) * fSlow119);
		float 	fSlow496 = max((float)0, (fSlow70 + float(fslider235)));
		float 	fSlow497 = max((float)0, (fSlow73 + float(fslider236)));
		float 	fSlow498 = (6.9100000000000001f * fSlow497);
		int 	iSlow499 = int((fConst0 * fSlow497));
		float 	fSlow500 = (fSlow95 * max((float)0, ((0.5f * float(fslider237)) + fSlow79)));
		float 	fSlow501 = (float(fslider238) * fSlow100);
		float 	fSlow502 = max((float)0, (fSlow70 + float(fslider239)));
		float 	fSlow503 = max((float)0, (fSlow73 + float(fslider240)));
		float 	fSlow504 = (6.9100000000000001f * fSlow503);
		int 	iSlow505 = int((fConst0 * fSlow503));
		float 	fSlow506 = (fSlow63 * max((float)0, ((0.5f * float(fslider241)) + fSlow79)));
		float 	fSlow507 = (float(fslider242) * fSlow68);
		float 	fSlow508 = max((float)0, (fSlow70 + float(fslider243)));
		float 	fSlow509 = max((float)0, (fSlow73 + float(fslider244)));
		float 	fSlow510 = (6.9100000000000001f * fSlow509);
		int 	iSlow511 = int((fConst0 * fSlow509));
		float 	fSlow512 = (fSlow44 * max((float)0, ((0.5f * float(fslider245)) + fSlow79)));
		float 	fSlow513 = (float(fslider246) * fSlow49);
		float 	fSlow514 = max((float)0, (fSlow70 + float(fslider247)));
		float 	fSlow515 = max((float)0, (fSlow73 + float(fslider248)));
		float 	fSlow516 = (6.9100000000000001f * fSlow515);
		int 	iSlow517 = int((fConst0 * fSlow515));
		float 	fSlow518 = (fSlow25 * max((float)0, ((0.5f * float(fslider249)) + fSlow79)));
		float 	fSlow519 = (float(fslider250) * fSlow30);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec1[0] = (fSlow12 + (fRec1[1] - floorf((fSlow12 + fRec1[1]))));
				fTempPerm1 = ftbl0[(((int((65536.0f * fRec1[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec3[0] = ((iSlow21)?0.0f:min(fSlow20, (fRec3[1] + 1.0f)));
				iTempPerm2 = int((fRec3[0] < fSlow17));
				fRec2[0] = ((iSlow26)?(fSlow25 * ((iTempPerm2)?((int((fRec3[0] < 0.0f)))?0.0f:((iTempPerm2)?(fSlow23 * fRec3[0]):1.0f)):((int((fRec3[0] < fSlow20)))?((fSlow22 * (fRec3[0] - fSlow17)) + 1.0f):fSlow15))):fRec2[1]);
				fRec4[0] = ((iSlow28)?0.0f:min(fSlow27, (fRec4[1] + 1.0f)));
				fTempPerm3 = (fSlow30 * (((int((fRec4[0] < 0.0f)))?fRec2[0]:((int((fRec4[0] < fSlow27)))?(fRec2[0] + (fSlow29 * (0 - (fRec4[0] * fRec2[0])))):0.0f)) * fTempPerm1));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec5[0] = (fSlow31 + (fRec5[1] - floorf((fSlow31 + fRec5[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm4 = ftbl0[(((int((65536.0f * (fRec5[0] + fTempPerm3))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec7[0] = ((iSlow40)?0.0f:min(fSlow39, (fRec7[1] + 1.0f)));
				iTempPerm5 = int((fRec7[0] < fSlow36));
				fRec6[0] = ((iSlow45)?(fSlow44 * ((iTempPerm5)?((int((fRec7[0] < 0.0f)))?0.0f:((iTempPerm5)?(fSlow42 * fRec7[0]):1.0f)):((int((fRec7[0] < fSlow39)))?((fSlow41 * (fRec7[0] - fSlow36)) + 1.0f):fSlow34))):fRec6[1]);
				fRec8[0] = ((iSlow47)?0.0f:min(fSlow46, (fRec8[1] + 1.0f)));
				fTempPerm6 = ((int((fRec8[0] < 0.0f)))?fRec6[0]:((int((fRec8[0] < fSlow46)))?(fRec6[0] + (fSlow48 * (0 - (fRec8[0] * fRec6[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm7 = (fSlow49 * (fTempPerm6 * fTempPerm4));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec9[0] = (fSlow50 + (fRec9[1] - floorf((fSlow50 + fRec9[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm8 = ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm7))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec11[0] = ((iSlow59)?0.0f:min(fSlow58, (fRec11[1] + 1.0f)));
				iTempPerm9 = int((fRec11[0] < fSlow55));
				fRec10[0] = ((iSlow64)?(fSlow63 * ((iTempPerm9)?((int((fRec11[0] < 0.0f)))?0.0f:((iTempPerm9)?(fSlow61 * fRec11[0]):1.0f)):((int((fRec11[0] < fSlow58)))?((fSlow60 * (fRec11[0] - fSlow55)) + 1.0f):fSlow53))):fRec10[1]);
				fRec12[0] = ((iSlow66)?0.0f:min(fSlow65, (fRec12[1] + 1.0f)));
				fTempPerm10 = ((int((fRec12[0] < 0.0f)))?fRec10[0]:((int((fRec12[0] < fSlow65)))?(fRec10[0] + (fSlow67 * (0 - (fRec12[0] * fRec10[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec13[0] = (fSlow69 + (fRec13[1] - floorf((fSlow69 + fRec13[1]))));
				iRec15[0] = (iSlow77 * (iRec15[1] + 1));
				iTempPerm11 = int((iRec15[0] < iSlow76));
				fTempPerm12 = expf((0 - (fConst4 / ((iSlow78)?((iTempPerm11)?fSlow75:fSlow72):fSlow71))));
				fRec14[0] = ((fRec14[1] * fTempPerm12) + (((iSlow78)?((iTempPerm11)?1.5873015873015872f:fSlow80):0.0f) * (1.0f - fTempPerm12)));
				fTempPerm13 = min(1.0f, fRec14[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm14 = (fSlow81 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow68 * (fTempPerm10 * fTempPerm8))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec16[0] = (fSlow82 + (fRec16[1] - floorf((fSlow82 + fRec16[1]))));
				fTempPerm15 = ftbl0[(((int((65536.0f * fRec16[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec18[0] = ((iSlow91)?0.0f:min(fSlow90, (fRec18[1] + 1.0f)));
				iTempPerm16 = int((fRec18[0] < fSlow87));
				fRec17[0] = ((iSlow96)?(fSlow95 * ((iTempPerm16)?((int((fRec18[0] < 0.0f)))?0.0f:((iTempPerm16)?(fSlow93 * fRec18[0]):1.0f)):((int((fRec18[0] < fSlow90)))?((fSlow92 * (fRec18[0] - fSlow87)) + 1.0f):fSlow85))):fRec17[1]);
				fRec19[0] = ((iSlow98)?0.0f:min(fSlow97, (fRec19[1] + 1.0f)));
				fTempPerm17 = (fSlow100 * (((int((fRec19[0] < 0.0f)))?fRec17[0]:((int((fRec19[0] < fSlow97)))?(fRec17[0] + (fSlow99 * (0 - (fRec19[0] * fRec17[0])))):0.0f)) * fTempPerm15));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec20[0] = (fSlow101 + (fRec20[1] - floorf((fSlow101 + fRec20[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm18 = ftbl0[(((int((65536.0f * (fRec20[0] + fTempPerm17))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec22[0] = ((iSlow110)?0.0f:min(fSlow109, (fRec22[1] + 1.0f)));
				iTempPerm19 = int((fRec22[0] < fSlow106));
				fRec21[0] = ((iSlow115)?(fSlow114 * ((iTempPerm19)?((int((fRec22[0] < 0.0f)))?0.0f:((iTempPerm19)?(fSlow112 * fRec22[0]):1.0f)):((int((fRec22[0] < fSlow109)))?((fSlow111 * (fRec22[0] - fSlow106)) + 1.0f):fSlow104))):fRec21[1]);
				fRec23[0] = ((iSlow117)?0.0f:min(fSlow116, (fRec23[1] + 1.0f)));
				fTempPerm20 = ((int((fRec23[0] < 0.0f)))?fRec21[0]:((int((fRec23[0] < fSlow116)))?(fRec21[0] + (fSlow118 * (0 - (fRec23[0] * fRec21[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm21 = (fSlow119 * (fTempPerm20 * fTempPerm18));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec24[0] = (fSlow120 + (fRec24[1] - floorf((fSlow120 + fRec24[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm22 = ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm21))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec26[0] = ((iSlow129)?0.0f:min(fSlow128, (fRec26[1] + 1.0f)));
				iTempPerm23 = int((fRec26[0] < fSlow125));
				fRec25[0] = ((iSlow134)?(fSlow133 * ((iTempPerm23)?((int((fRec26[0] < 0.0f)))?0.0f:((iTempPerm23)?(fSlow131 * fRec26[0]):1.0f)):((int((fRec26[0] < fSlow128)))?((fSlow130 * (fRec26[0] - fSlow125)) + 1.0f):fSlow123))):fRec25[1]);
				fRec27[0] = ((iSlow136)?0.0f:min(fSlow135, (fRec27[1] + 1.0f)));
				fTempPerm24 = ((int((fRec27[0] < 0.0f)))?fRec25[0]:((int((fRec27[0] < fSlow135)))?(fRec25[0] + (fSlow137 * (0 - (fRec27[0] * fRec25[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec28[0] = (fSlow139 + (fRec28[1] - floorf((fSlow139 + fRec28[1]))));
				iRec30[0] = (iSlow144 * (iRec30[1] + 1));
				iTempPerm25 = int((iRec30[0] < iSlow143));
				fTempPerm26 = expf((0 - (fConst4 / ((iSlow145)?((iTempPerm25)?fSlow142:fSlow72):fSlow140))));
				fRec29[0] = ((fRec29[1] * fTempPerm26) + (((iSlow145)?((iTempPerm25)?1.5873015873015872f:fSlow146):0.0f) * (1.0f - fTempPerm26)));
				fTempPerm27 = min(1.0f, fRec29[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm28 = (fSlow147 * (fTempPerm27 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow138 * (fTempPerm24 * fTempPerm22))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec31[0] = (fSlow148 + (fRec31[1] - floorf((fSlow148 + fRec31[1]))));
				fTempPerm29 = ftbl0[(((int((65536.0f * fRec31[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec33[0] = ((iSlow157)?0.0f:min(fSlow156, (fRec33[1] + 1.0f)));
				iTempPerm30 = int((fRec33[0] < fSlow153));
				fRec32[0] = ((iSlow162)?(fSlow161 * ((iTempPerm30)?((int((fRec33[0] < 0.0f)))?0.0f:((iTempPerm30)?(fSlow159 * fRec33[0]):1.0f)):((int((fRec33[0] < fSlow156)))?((fSlow158 * (fRec33[0] - fSlow153)) + 1.0f):fSlow151))):fRec32[1]);
				fRec34[0] = ((iSlow164)?0.0f:min(fSlow163, (fRec34[1] + 1.0f)));
				fTempPerm31 = (fSlow166 * (((int((fRec34[0] < 0.0f)))?fRec32[0]:((int((fRec34[0] < fSlow163)))?(fRec32[0] + (fSlow165 * (0 - (fRec34[0] * fRec32[0])))):0.0f)) * fTempPerm29));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec35[0] = (fSlow167 + (fRec35[1] - floorf((fSlow167 + fRec35[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm32 = ftbl0[(((int((65536.0f * (fRec35[0] + fTempPerm31))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec37[0] = ((iSlow176)?0.0f:min(fSlow175, (fRec37[1] + 1.0f)));
				iTempPerm33 = int((fRec37[0] < fSlow172));
				fRec36[0] = ((iSlow181)?(fSlow180 * ((iTempPerm33)?((int((fRec37[0] < 0.0f)))?0.0f:((iTempPerm33)?(fSlow178 * fRec37[0]):1.0f)):((int((fRec37[0] < fSlow175)))?((fSlow177 * (fRec37[0] - fSlow172)) + 1.0f):fSlow170))):fRec36[1]);
				fRec38[0] = ((iSlow183)?0.0f:min(fSlow182, (fRec38[1] + 1.0f)));
				fTempPerm34 = ((int((fRec38[0] < 0.0f)))?fRec36[0]:((int((fRec38[0] < fSlow182)))?(fRec36[0] + (fSlow184 * (0 - (fRec38[0] * fRec36[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm35 = (fSlow185 * (fTempPerm34 * fTempPerm32));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec39[0] = (fSlow186 + (fRec39[1] - floorf((fSlow186 + fRec39[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm36 = ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm35))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec41[0] = ((iSlow195)?0.0f:min(fSlow194, (fRec41[1] + 1.0f)));
				iTempPerm37 = int((fRec41[0] < fSlow191));
				fRec40[0] = ((iSlow200)?(fSlow199 * ((iTempPerm37)?((int((fRec41[0] < 0.0f)))?0.0f:((iTempPerm37)?(fSlow197 * fRec41[0]):1.0f)):((int((fRec41[0] < fSlow194)))?((fSlow196 * (fRec41[0] - fSlow191)) + 1.0f):fSlow189))):fRec40[1]);
				fRec42[0] = ((iSlow202)?0.0f:min(fSlow201, (fRec42[1] + 1.0f)));
				fTempPerm38 = ((int((fRec42[0] < 0.0f)))?fRec40[0]:((int((fRec42[0] < fSlow201)))?(fRec40[0] + (fSlow203 * (0 - (fRec42[0] * fRec40[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec43[0] = (fSlow205 + (fRec43[1] - floorf((fSlow205 + fRec43[1]))));
				iRec45[0] = (iSlow210 * (iRec45[1] + 1));
				iTempPerm39 = int((iRec45[0] < iSlow209));
				fTempPerm40 = expf((0 - (fConst4 / ((iSlow211)?((iTempPerm39)?fSlow208:fSlow72):fSlow206))));
				fRec44[0] = ((fRec44[1] * fTempPerm40) + (((iSlow211)?((iTempPerm39)?1.5873015873015872f:fSlow212):0.0f) * (1.0f - fTempPerm40)));
				fTempPerm41 = min(1.0f, fRec44[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm42 = (fSlow213 * (fTempPerm41 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow204 * (fTempPerm38 * fTempPerm36))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec46[0] = (fSlow214 + (fRec46[1] - floorf((fSlow214 + fRec46[1]))));
				fTempPerm43 = ftbl0[(((int((65536.0f * fRec46[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec48[0] = ((iSlow223)?0.0f:min(fSlow222, (fRec48[1] + 1.0f)));
				iTempPerm44 = int((fRec48[0] < fSlow219));
				fRec47[0] = ((iSlow228)?(fSlow227 * ((iTempPerm44)?((int((fRec48[0] < 0.0f)))?0.0f:((iTempPerm44)?(fSlow225 * fRec48[0]):1.0f)):((int((fRec48[0] < fSlow222)))?((fSlow224 * (fRec48[0] - fSlow219)) + 1.0f):fSlow217))):fRec47[1]);
				fRec49[0] = ((iSlow230)?0.0f:min(fSlow229, (fRec49[1] + 1.0f)));
				fTempPerm45 = (fSlow232 * (((int((fRec49[0] < 0.0f)))?fRec47[0]:((int((fRec49[0] < fSlow229)))?(fRec47[0] + (fSlow231 * (0 - (fRec49[0] * fRec47[0])))):0.0f)) * fTempPerm43));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec50[0] = (fSlow233 + (fRec50[1] - floorf((fSlow233 + fRec50[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm46 = ftbl0[(((int((65536.0f * (fRec50[0] + fTempPerm45))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec52[0] = ((iSlow242)?0.0f:min(fSlow241, (fRec52[1] + 1.0f)));
				iTempPerm47 = int((fRec52[0] < fSlow238));
				fRec51[0] = ((iSlow247)?(fSlow246 * ((iTempPerm47)?((int((fRec52[0] < 0.0f)))?0.0f:((iTempPerm47)?(fSlow244 * fRec52[0]):1.0f)):((int((fRec52[0] < fSlow241)))?((fSlow243 * (fRec52[0] - fSlow238)) + 1.0f):fSlow236))):fRec51[1]);
				fRec53[0] = ((iSlow249)?0.0f:min(fSlow248, (fRec53[1] + 1.0f)));
				fTempPerm48 = ((int((fRec53[0] < 0.0f)))?fRec51[0]:((int((fRec53[0] < fSlow248)))?(fRec51[0] + (fSlow250 * (0 - (fRec53[0] * fRec51[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm49 = (fSlow251 * (fTempPerm48 * fTempPerm46));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec54[0] = (fSlow252 + (fRec54[1] - floorf((fSlow252 + fRec54[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm50 = ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm49))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec56[0] = ((iSlow261)?0.0f:min(fSlow260, (fRec56[1] + 1.0f)));
				iTempPerm51 = int((fRec56[0] < fSlow257));
				fRec55[0] = ((iSlow266)?(fSlow265 * ((iTempPerm51)?((int((fRec56[0] < 0.0f)))?0.0f:((iTempPerm51)?(fSlow263 * fRec56[0]):1.0f)):((int((fRec56[0] < fSlow260)))?((fSlow262 * (fRec56[0] - fSlow257)) + 1.0f):fSlow255))):fRec55[1]);
				fRec57[0] = ((iSlow268)?0.0f:min(fSlow267, (fRec57[1] + 1.0f)));
				fTempPerm52 = ((int((fRec57[0] < 0.0f)))?fRec55[0]:((int((fRec57[0] < fSlow267)))?(fRec55[0] + (fSlow269 * (0 - (fRec57[0] * fRec55[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec58[0] = (fSlow271 + (fRec58[1] - floorf((fSlow271 + fRec58[1]))));
				iRec60[0] = (iSlow276 * (iRec60[1] + 1));
				iTempPerm53 = int((iRec60[0] < iSlow275));
				fTempPerm54 = expf((0 - (fConst4 / ((iSlow277)?((iTempPerm53)?fSlow274:fSlow72):fSlow272))));
				fRec59[0] = ((fRec59[1] * fTempPerm54) + (((iSlow277)?((iTempPerm53)?1.5873015873015872f:fSlow278):0.0f) * (1.0f - fTempPerm54)));
				fTempPerm55 = min(1.0f, fRec59[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm56 = (fSlow279 * (fTempPerm55 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow270 * (fTempPerm52 * fTempPerm50))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec61[0] = (fSlow280 + (fRec61[1] - floorf((fSlow280 + fRec61[1]))));
				fTempPerm57 = ftbl0[(((int((65536.0f * fRec61[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec63[0] = ((iSlow289)?0.0f:min(fSlow288, (fRec63[1] + 1.0f)));
				iTempPerm58 = int((fRec63[0] < fSlow285));
				fRec62[0] = ((iSlow294)?(fSlow293 * ((iTempPerm58)?((int((fRec63[0] < 0.0f)))?0.0f:((iTempPerm58)?(fSlow291 * fRec63[0]):1.0f)):((int((fRec63[0] < fSlow288)))?((fSlow290 * (fRec63[0] - fSlow285)) + 1.0f):fSlow283))):fRec62[1]);
				fRec64[0] = ((iSlow296)?0.0f:min(fSlow295, (fRec64[1] + 1.0f)));
				fTempPerm59 = (fSlow298 * (((int((fRec64[0] < 0.0f)))?fRec62[0]:((int((fRec64[0] < fSlow295)))?(fRec62[0] + (fSlow297 * (0 - (fRec64[0] * fRec62[0])))):0.0f)) * fTempPerm57));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec65[0] = (fSlow299 + (fRec65[1] - floorf((fSlow299 + fRec65[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm60 = ftbl0[(((int((65536.0f * (fRec65[0] + fTempPerm59))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec67[0] = ((iSlow308)?0.0f:min(fSlow307, (fRec67[1] + 1.0f)));
				iTempPerm61 = int((fRec67[0] < fSlow304));
				fRec66[0] = ((iSlow313)?(fSlow312 * ((iTempPerm61)?((int((fRec67[0] < 0.0f)))?0.0f:((iTempPerm61)?(fSlow310 * fRec67[0]):1.0f)):((int((fRec67[0] < fSlow307)))?((fSlow309 * (fRec67[0] - fSlow304)) + 1.0f):fSlow302))):fRec66[1]);
				fRec68[0] = ((iSlow315)?0.0f:min(fSlow314, (fRec68[1] + 1.0f)));
				fTempPerm62 = ((int((fRec68[0] < 0.0f)))?fRec66[0]:((int((fRec68[0] < fSlow314)))?(fRec66[0] + (fSlow316 * (0 - (fRec68[0] * fRec66[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm63 = (fSlow317 * (fTempPerm62 * fTempPerm60));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec69[0] = (fSlow318 + (fRec69[1] - floorf((fSlow318 + fRec69[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm64 = ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm63))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec71[0] = ((iSlow327)?0.0f:min(fSlow326, (fRec71[1] + 1.0f)));
				iTempPerm65 = int((fRec71[0] < fSlow323));
				fRec70[0] = ((iSlow332)?(fSlow331 * ((iTempPerm65)?((int((fRec71[0] < 0.0f)))?0.0f:((iTempPerm65)?(fSlow329 * fRec71[0]):1.0f)):((int((fRec71[0] < fSlow326)))?((fSlow328 * (fRec71[0] - fSlow323)) + 1.0f):fSlow321))):fRec70[1]);
				fRec72[0] = ((iSlow334)?0.0f:min(fSlow333, (fRec72[1] + 1.0f)));
				fTempPerm66 = ((int((fRec72[0] < 0.0f)))?fRec70[0]:((int((fRec72[0] < fSlow333)))?(fRec70[0] + (fSlow335 * (0 - (fRec72[0] * fRec70[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec73[0] = (fSlow337 + (fRec73[1] - floorf((fSlow337 + fRec73[1]))));
				iRec75[0] = (iSlow342 * (iRec75[1] + 1));
				iTempPerm67 = int((iRec75[0] < iSlow341));
				fTempPerm68 = expf((0 - (fConst4 / ((iSlow343)?((iTempPerm67)?fSlow340:fSlow72):fSlow338))));
				fRec74[0] = ((fRec74[1] * fTempPerm68) + (((iSlow343)?((iTempPerm67)?1.5873015873015872f:fSlow344):0.0f) * (1.0f - fTempPerm68)));
				fTempPerm69 = min(1.0f, fRec74[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm70 = (fSlow345 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow336 * (fTempPerm66 * fTempPerm64))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec76[0] = (fSlow346 + (fRec76[1] - floorf((fSlow346 + fRec76[1]))));
				fTempPerm71 = ftbl0[(((int((65536.0f * fRec76[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11) {
				iRec78[0] = (iSlow352 * (iRec78[1] + 1));
				iTempPerm72 = int((iRec78[0] < iSlow350));
				fTempPerm73 = expf((0 - (fConst4 / ((iSlow353)?((iTempPerm72)?fSlow349:fSlow72):fSlow347))));
				fRec77[0] = ((fRec77[1] * fTempPerm73) + (((iSlow353)?((iTempPerm72)?1.5873015873015872f:fSlow355):0.0f) * (1.0f - fTempPerm73)));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec79[0] = (fSlow358 + (fRec79[1] - floorf((fSlow358 + fRec79[1]))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm74 = ftbl0[(((int((65536.0f * fRec79[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec81[0] = (iSlow364 * (iRec81[1] + 1));
				iTempPerm75 = int((iRec81[0] < iSlow362));
				fTempPerm76 = expf((0 - (fConst4 / ((iSlow365)?((iTempPerm75)?fSlow361:fSlow72):fSlow359))));
				fRec80[0] = ((fRec80[1] * fTempPerm76) + (((iSlow365)?((iTempPerm75)?1.5873015873015872f:fSlow367):0.0f) * (1.0f - fTempPerm76)));
				fTempPerm77 = min(1.0f, fRec80[0]);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec82[0] = (fSlow370 + (fRec82[1] - floorf((fSlow370 + fRec82[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm78 = ftbl0[(((int((65536.0f * fRec82[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec84[0] = (iSlow376 * (iRec84[1] + 1));
				iTempPerm79 = int((iRec84[0] < iSlow374));
				fTempPerm80 = expf((0 - (fConst4 / ((iSlow377)?((iTempPerm79)?fSlow373:fSlow72):fSlow371))));
				fRec83[0] = ((fRec83[1] * fTempPerm80) + (((iSlow377)?((iTempPerm79)?1.5873015873015872f:fSlow379):0.0f) * (1.0f - fTempPerm80)));
				fTempPerm81 = min(1.0f, fRec83[0]);
			}
			if (iSlow11 || iSlow10) {
				fTempPerm82 = (fSlow381 * (fTempPerm81 * fTempPerm78));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec85[0] = (fSlow382 + (fRec85[1] - floorf((fSlow382 + fRec85[1]))));
				iRec87[0] = (iSlow387 * (iRec87[1] + 1));
				iTempPerm83 = int((iRec87[0] < iSlow386));
				fTempPerm84 = expf((0 - (fConst4 / ((iSlow388)?((iTempPerm83)?fSlow385:fSlow72):fSlow383))));
				fRec86[0] = ((fRec86[1] * fTempPerm84) + (((iSlow388)?((iTempPerm83)?1.5873015873015872f:fSlow389):0.0f) * (1.0f - fTempPerm84)));
				fTempPerm85 = min(1.0f, fRec86[0]);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm86 = (fSlow390 * (fTempPerm85 * ftbl0[(((int((65536.0f * fRec85[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11) {
				fTempPerm87 = (((fTempPerm86 + fTempPerm82) + (fSlow369 * (fTempPerm77 * fTempPerm74))) + (fSlow357 * (min(1.0f, fRec77[0]) * fTempPerm71)));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec89[0] = ((iSlow398)?0.0f:min(fSlow397, (fRec89[1] + 1.0f)));
				iTempPerm88 = int((fRec89[0] < fSlow394));
				fRec88[0] = ((iSlow353)?(fSlow354 * ((iTempPerm88)?((int((fRec89[0] < 0.0f)))?0.0f:((iTempPerm88)?(fSlow400 * fRec89[0]):1.0f)):((int((fRec89[0] < fSlow397)))?((fSlow399 * (fRec89[0] - fSlow394)) + 1.0f):fSlow392))):fRec88[1]);
				fRec90[0] = ((iSlow402)?0.0f:min(fSlow401, (fRec90[1] + 1.0f)));
				fTempPerm89 = (fSlow356 * (((int((fRec90[0] < 0.0f)))?fRec88[0]:((int((fRec90[0] < fSlow401)))?(fRec88[0] + (fSlow403 * (0 - (fRec90[0] * fRec88[0])))):0.0f)) * fTempPerm71));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm90 = ftbl0[(((int((65536.0f * (fRec79[0] + fTempPerm89))) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm91 = (fSlow369 * (fTempPerm77 * fTempPerm90));
			}
			if (iSlow10) {
				fTempPerm92 = (fTempPerm82 + (fTempPerm86 + fTempPerm91));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm93 = ftbl0[(((int((65536.0f * (fRec82[0] + fTempPerm89))) % 65536) + 65536) % 65536)];
			}
			if (iSlow9) {
				fTempPerm94 = ((fSlow381 * (fTempPerm81 * fTempPerm93)) + (fTempPerm91 + (fSlow390 * (fTempPerm85 * ftbl0[(((int((65536.0f * (fRec85[0] + fTempPerm89))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec92[0] = ((iSlow411)?0.0f:min(fSlow410, (fRec92[1] + 1.0f)));
				iTempPerm95 = int((fRec92[0] < fSlow407));
				fRec91[0] = ((iSlow377)?(fSlow378 * ((iTempPerm95)?((int((fRec92[0] < 0.0f)))?0.0f:((iTempPerm95)?(fSlow413 * fRec92[0]):1.0f)):((int((fRec92[0] < fSlow410)))?((fSlow412 * (fRec92[0] - fSlow407)) + 1.0f):fSlow405))):fRec91[1]);
				fRec93[0] = ((iSlow415)?0.0f:min(fSlow414, (fRec93[1] + 1.0f)));
				fTempPerm96 = ((int((fRec93[0] < 0.0f)))?fRec91[0]:((int((fRec93[0] < fSlow414)))?(fRec91[0] + (fSlow416 * (0 - (fRec93[0] * fRec91[0])))):0.0f));
			}
			if (iSlow8 || iSlow7) {
				fTempPerm97 = (fSlow380 * (fTempPerm96 * fTempPerm78));
			}
			if (iSlow8) {
				fTempPerm98 = ((fSlow390 * (fTempPerm85 * ftbl0[(((int((65536.0f * (fRec85[0] + fTempPerm97))) % 65536) + 65536) % 65536)])) + fTempPerm91);
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec95[0] = ((iSlow424)?0.0f:min(fSlow423, (fRec95[1] + 1.0f)));
				iTempPerm99 = int((fRec95[0] < fSlow420));
				fRec94[0] = ((iSlow365)?(fSlow366 * ((iTempPerm99)?((int((fRec95[0] < 0.0f)))?0.0f:((iTempPerm99)?(fSlow426 * fRec95[0]):1.0f)):((int((fRec95[0] < fSlow423)))?((fSlow425 * (fRec95[0] - fSlow420)) + 1.0f):fSlow418))):fRec94[1]);
				fRec96[0] = ((iSlow428)?0.0f:min(fSlow427, (fRec96[1] + 1.0f)));
				fTempPerm100 = ((int((fRec96[0] < 0.0f)))?fRec94[0]:((int((fRec96[0] < fSlow427)))?(fRec94[0] + (fSlow429 * (0 - (fRec96[0] * fRec94[0])))):0.0f));
			}
			if (iSlow7 || iSlow3) {
				fTempPerm101 = (fSlow368 * (fTempPerm100 * fTempPerm74));
			}
			if (iSlow7) {
				fTempPerm102 = (fSlow390 * (fTempPerm85 * ftbl0[(((int((65536.0f * (fRec85[0] + ((fTempPerm89 + fTempPerm101) + fTempPerm97)))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm103 = (fSlow368 * (fTempPerm100 * fTempPerm90));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm104 = ftbl0[(((int((65536.0f * (fRec82[0] + fTempPerm103))) % 65536) + 65536) % 65536)];
			}
			if (iSlow6 || iSlow5) {
				fTempPerm105 = (fSlow381 * (fTempPerm81 * fTempPerm104));
			}
			if (iSlow6) {
				fTempPerm106 = (fTempPerm105 + fTempPerm86);
			}
			if (iSlow5) {
				fTempPerm107 = ((fSlow390 * (fTempPerm85 * ftbl0[(((int((65536.0f * (fRec85[0] + fTempPerm103))) % 65536) + 65536) % 65536)])) + fTempPerm105);
			}
			if (iSlow4) {
				fTempPerm108 = (fSlow390 * (fTempPerm85 * ftbl0[(((int((65536.0f * (fRec85[0] + (fTempPerm103 + (fSlow380 * (fTempPerm96 * fTempPerm93)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm109 = (fSlow390 * (fTempPerm85 * ftbl0[(((int((65536.0f * (fRec85[0] + (fTempPerm89 + (fSlow380 * (fTempPerm96 * ftbl0[(((int((65536.0f * (fRec82[0] + fTempPerm101))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow2 || iSlow1) {
				fTempPerm110 = (fSlow390 * (fTempPerm85 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow380 * (fTempPerm96 * fTempPerm104))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm111 = ftbl0[(((int((65536.0f * fRec65[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm112 = (fSlow317 * (fTempPerm62 * fTempPerm111));
			}
			if (iSlow3) {
				fTempPerm113 = (fSlow345 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec73[0] + (fTempPerm59 + (fSlow336 * (fTempPerm66 * ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm112))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm114 = ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm59))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm115 = (fSlow345 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec73[0] + (fTempPerm63 + (fSlow336 * (fTempPerm66 * fTempPerm114)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec98[0] = (iSlow330 * (iRec98[1] + 1));
				iTempPerm116 = int((iRec98[0] < iSlow433));
				fTempPerm117 = expf((0 - (fConst4 / ((iSlow332)?((iTempPerm116)?fSlow432:fSlow72):fSlow430))));
				fRec97[0] = ((fRec97[1] * fTempPerm117) + (((iSlow332)?((iTempPerm116)?1.5873015873015872f:fSlow434):0.0f) * (1.0f - fTempPerm117)));
				fTempPerm118 = min(1.0f, fRec97[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm119 = (fSlow435 * (fTempPerm118 * fTempPerm64));
			}
			if (iSlow5) {
				fTempPerm120 = ((fSlow345 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm63))) % 65536) + 65536) % 65536)])) + fTempPerm119);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm121 = (fSlow345 * (fTempPerm69 * ftbl0[(((int((65536.0f * fRec73[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm122 = (fTempPerm119 + fTempPerm121);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm123 = ftbl0[(((int((65536.0f * fRec69[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm124 = (fSlow336 * (fTempPerm66 * fTempPerm123));
			}
			if (iSlow7) {
				fTempPerm125 = (fSlow345 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec73[0] + ((fTempPerm59 + fTempPerm112) + fTempPerm124)))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec100[0] = (iSlow311 * (iRec100[1] + 1));
				iTempPerm126 = int((iRec100[0] < iSlow439));
				fTempPerm127 = expf((0 - (fConst4 / ((iSlow313)?((iTempPerm126)?fSlow438:fSlow72):fSlow436))));
				fRec99[0] = ((fRec99[1] * fTempPerm127) + (((iSlow313)?((iTempPerm126)?1.5873015873015872f:fSlow440):0.0f) * (1.0f - fTempPerm127)));
				fTempPerm128 = min(1.0f, fRec99[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm129 = (fSlow441 * (fTempPerm128 * fTempPerm60));
			}
			if (iSlow8) {
				fTempPerm130 = ((fSlow345 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm124))) % 65536) + 65536) % 65536)])) + fTempPerm129);
			}
			if (iSlow9) {
				fTempPerm131 = ((fSlow435 * (fTempPerm118 * fTempPerm114)) + (fTempPerm129 + (fSlow345 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm59))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm132 = (fSlow435 * (fTempPerm118 * fTempPerm123));
			}
			if (iSlow10) {
				fTempPerm133 = (fTempPerm132 + (fTempPerm121 + fTempPerm129));
			}
			if (iSlow11) {
				iRec102[0] = (iSlow292 * (iRec102[1] + 1));
				iTempPerm134 = int((iRec102[0] < iSlow445));
				fTempPerm135 = expf((0 - (fConst4 / ((iSlow294)?((iTempPerm134)?fSlow444:fSlow72):fSlow442))));
				fRec101[0] = ((fRec101[1] * fTempPerm135) + (((iSlow294)?((iTempPerm134)?1.5873015873015872f:fSlow446):0.0f) * (1.0f - fTempPerm135)));
				fTempPerm136 = (((fTempPerm121 + fTempPerm132) + (fSlow441 * (fTempPerm128 * fTempPerm111))) + (fSlow447 * (min(1.0f, fRec101[0]) * fTempPerm57)));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm137 = ftbl0[(((int((65536.0f * fRec50[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm138 = (fSlow251 * (fTempPerm48 * fTempPerm137));
			}
			if (iSlow3) {
				fTempPerm139 = (fSlow279 * (fTempPerm55 * ftbl0[(((int((65536.0f * (fRec58[0] + (fTempPerm45 + (fSlow270 * (fTempPerm52 * ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm138))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm140 = ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm45))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm141 = (fSlow279 * (fTempPerm55 * ftbl0[(((int((65536.0f * (fRec58[0] + (fTempPerm49 + (fSlow270 * (fTempPerm52 * fTempPerm140)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec104[0] = (iSlow264 * (iRec104[1] + 1));
				iTempPerm142 = int((iRec104[0] < iSlow451));
				fTempPerm143 = expf((0 - (fConst4 / ((iSlow266)?((iTempPerm142)?fSlow450:fSlow72):fSlow448))));
				fRec103[0] = ((fRec103[1] * fTempPerm143) + (((iSlow266)?((iTempPerm142)?1.5873015873015872f:fSlow452):0.0f) * (1.0f - fTempPerm143)));
				fTempPerm144 = min(1.0f, fRec103[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm145 = (fSlow453 * (fTempPerm144 * fTempPerm50));
			}
			if (iSlow5) {
				fTempPerm146 = ((fSlow279 * (fTempPerm55 * ftbl0[(((int((65536.0f * (fRec58[0] + fTempPerm49))) % 65536) + 65536) % 65536)])) + fTempPerm145);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm147 = (fSlow279 * (fTempPerm55 * ftbl0[(((int((65536.0f * fRec58[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm148 = (fTempPerm145 + fTempPerm147);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm149 = ftbl0[(((int((65536.0f * fRec54[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm150 = (fSlow270 * (fTempPerm52 * fTempPerm149));
			}
			if (iSlow7) {
				fTempPerm151 = (fSlow279 * (fTempPerm55 * ftbl0[(((int((65536.0f * (fRec58[0] + ((fTempPerm45 + fTempPerm138) + fTempPerm150)))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec106[0] = (iSlow245 * (iRec106[1] + 1));
				iTempPerm152 = int((iRec106[0] < iSlow457));
				fTempPerm153 = expf((0 - (fConst4 / ((iSlow247)?((iTempPerm152)?fSlow456:fSlow72):fSlow454))));
				fRec105[0] = ((fRec105[1] * fTempPerm153) + (((iSlow247)?((iTempPerm152)?1.5873015873015872f:fSlow458):0.0f) * (1.0f - fTempPerm153)));
				fTempPerm154 = min(1.0f, fRec105[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm155 = (fSlow459 * (fTempPerm154 * fTempPerm46));
			}
			if (iSlow8) {
				fTempPerm156 = ((fSlow279 * (fTempPerm55 * ftbl0[(((int((65536.0f * (fRec58[0] + fTempPerm150))) % 65536) + 65536) % 65536)])) + fTempPerm155);
			}
			if (iSlow9) {
				fTempPerm157 = ((fSlow453 * (fTempPerm144 * fTempPerm140)) + (fTempPerm155 + (fSlow279 * (fTempPerm55 * ftbl0[(((int((65536.0f * (fRec58[0] + fTempPerm45))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm158 = (fSlow453 * (fTempPerm144 * fTempPerm149));
			}
			if (iSlow10) {
				fTempPerm159 = (fTempPerm158 + (fTempPerm147 + fTempPerm155));
			}
			if (iSlow11) {
				iRec108[0] = (iSlow226 * (iRec108[1] + 1));
				iTempPerm160 = int((iRec108[0] < iSlow463));
				fTempPerm161 = expf((0 - (fConst4 / ((iSlow228)?((iTempPerm160)?fSlow462:fSlow72):fSlow460))));
				fRec107[0] = ((fRec107[1] * fTempPerm161) + (((iSlow228)?((iTempPerm160)?1.5873015873015872f:fSlow464):0.0f) * (1.0f - fTempPerm161)));
				fTempPerm162 = (((fTempPerm147 + fTempPerm158) + (fSlow459 * (fTempPerm154 * fTempPerm137))) + (fSlow465 * (min(1.0f, fRec107[0]) * fTempPerm43)));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm163 = ftbl0[(((int((65536.0f * fRec35[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm164 = (fSlow185 * (fTempPerm34 * fTempPerm163));
			}
			if (iSlow3) {
				fTempPerm165 = (fSlow213 * (fTempPerm41 * ftbl0[(((int((65536.0f * (fRec43[0] + (fTempPerm31 + (fSlow204 * (fTempPerm38 * ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm164))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm166 = ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm31))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm167 = (fSlow213 * (fTempPerm41 * ftbl0[(((int((65536.0f * (fRec43[0] + (fTempPerm35 + (fSlow204 * (fTempPerm38 * fTempPerm166)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec110[0] = (iSlow198 * (iRec110[1] + 1));
				iTempPerm168 = int((iRec110[0] < iSlow469));
				fTempPerm169 = expf((0 - (fConst4 / ((iSlow200)?((iTempPerm168)?fSlow468:fSlow72):fSlow466))));
				fRec109[0] = ((fRec109[1] * fTempPerm169) + (((iSlow200)?((iTempPerm168)?1.5873015873015872f:fSlow470):0.0f) * (1.0f - fTempPerm169)));
				fTempPerm170 = min(1.0f, fRec109[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm171 = (fSlow471 * (fTempPerm170 * fTempPerm36));
			}
			if (iSlow5) {
				fTempPerm172 = ((fSlow213 * (fTempPerm41 * ftbl0[(((int((65536.0f * (fRec43[0] + fTempPerm35))) % 65536) + 65536) % 65536)])) + fTempPerm171);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm173 = (fSlow213 * (fTempPerm41 * ftbl0[(((int((65536.0f * fRec43[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm174 = (fTempPerm171 + fTempPerm173);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm175 = ftbl0[(((int((65536.0f * fRec39[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm176 = (fSlow204 * (fTempPerm38 * fTempPerm175));
			}
			if (iSlow7) {
				fTempPerm177 = (fSlow213 * (fTempPerm41 * ftbl0[(((int((65536.0f * (fRec43[0] + ((fTempPerm31 + fTempPerm164) + fTempPerm176)))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec112[0] = (iSlow179 * (iRec112[1] + 1));
				iTempPerm178 = int((iRec112[0] < iSlow475));
				fTempPerm179 = expf((0 - (fConst4 / ((iSlow181)?((iTempPerm178)?fSlow474:fSlow72):fSlow472))));
				fRec111[0] = ((fRec111[1] * fTempPerm179) + (((iSlow181)?((iTempPerm178)?1.5873015873015872f:fSlow476):0.0f) * (1.0f - fTempPerm179)));
				fTempPerm180 = min(1.0f, fRec111[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm181 = (fSlow477 * (fTempPerm180 * fTempPerm32));
			}
			if (iSlow8) {
				fTempPerm182 = ((fSlow213 * (fTempPerm41 * ftbl0[(((int((65536.0f * (fRec43[0] + fTempPerm176))) % 65536) + 65536) % 65536)])) + fTempPerm181);
			}
			if (iSlow9) {
				fTempPerm183 = ((fSlow471 * (fTempPerm170 * fTempPerm166)) + (fTempPerm181 + (fSlow213 * (fTempPerm41 * ftbl0[(((int((65536.0f * (fRec43[0] + fTempPerm31))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm184 = (fSlow471 * (fTempPerm170 * fTempPerm175));
			}
			if (iSlow10) {
				fTempPerm185 = (fTempPerm184 + (fTempPerm173 + fTempPerm181));
			}
			if (iSlow11) {
				iRec114[0] = (iSlow160 * (iRec114[1] + 1));
				iTempPerm186 = int((iRec114[0] < iSlow481));
				fTempPerm187 = expf((0 - (fConst4 / ((iSlow162)?((iTempPerm186)?fSlow480:fSlow72):fSlow478))));
				fRec113[0] = ((fRec113[1] * fTempPerm187) + (((iSlow162)?((iTempPerm186)?1.5873015873015872f:fSlow482):0.0f) * (1.0f - fTempPerm187)));
				fTempPerm188 = (((fTempPerm173 + fTempPerm184) + (fSlow477 * (fTempPerm180 * fTempPerm163))) + (fSlow483 * (min(1.0f, fRec113[0]) * fTempPerm29)));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm189 = ftbl0[(((int((65536.0f * fRec20[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm190 = (fSlow119 * (fTempPerm20 * fTempPerm189));
			}
			if (iSlow3) {
				fTempPerm191 = (fSlow147 * (fTempPerm27 * ftbl0[(((int((65536.0f * (fRec28[0] + (fTempPerm17 + (fSlow138 * (fTempPerm24 * ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm190))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm192 = ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm17))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm193 = (fSlow147 * (fTempPerm27 * ftbl0[(((int((65536.0f * (fRec28[0] + (fTempPerm21 + (fSlow138 * (fTempPerm24 * fTempPerm192)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec116[0] = (iSlow132 * (iRec116[1] + 1));
				iTempPerm194 = int((iRec116[0] < iSlow487));
				fTempPerm195 = expf((0 - (fConst4 / ((iSlow134)?((iTempPerm194)?fSlow486:fSlow72):fSlow484))));
				fRec115[0] = ((fRec115[1] * fTempPerm195) + (((iSlow134)?((iTempPerm194)?1.5873015873015872f:fSlow488):0.0f) * (1.0f - fTempPerm195)));
				fTempPerm196 = min(1.0f, fRec115[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm197 = (fSlow489 * (fTempPerm196 * fTempPerm22));
			}
			if (iSlow5) {
				fTempPerm198 = ((fSlow147 * (fTempPerm27 * ftbl0[(((int((65536.0f * (fRec28[0] + fTempPerm21))) % 65536) + 65536) % 65536)])) + fTempPerm197);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm199 = (fSlow147 * (fTempPerm27 * ftbl0[(((int((65536.0f * fRec28[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm200 = (fTempPerm197 + fTempPerm199);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm201 = ftbl0[(((int((65536.0f * fRec24[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm202 = (fSlow138 * (fTempPerm24 * fTempPerm201));
			}
			if (iSlow7) {
				fTempPerm203 = (fSlow147 * (fTempPerm27 * ftbl0[(((int((65536.0f * (fRec28[0] + ((fTempPerm17 + fTempPerm190) + fTempPerm202)))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec118[0] = (iSlow113 * (iRec118[1] + 1));
				iTempPerm204 = int((iRec118[0] < iSlow493));
				fTempPerm205 = expf((0 - (fConst4 / ((iSlow115)?((iTempPerm204)?fSlow492:fSlow72):fSlow490))));
				fRec117[0] = ((fRec117[1] * fTempPerm205) + (((iSlow115)?((iTempPerm204)?1.5873015873015872f:fSlow494):0.0f) * (1.0f - fTempPerm205)));
				fTempPerm206 = min(1.0f, fRec117[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm207 = (fSlow495 * (fTempPerm206 * fTempPerm18));
			}
			if (iSlow8) {
				fTempPerm208 = ((fSlow147 * (fTempPerm27 * ftbl0[(((int((65536.0f * (fRec28[0] + fTempPerm202))) % 65536) + 65536) % 65536)])) + fTempPerm207);
			}
			if (iSlow9) {
				fTempPerm209 = ((fSlow489 * (fTempPerm196 * fTempPerm192)) + (fTempPerm207 + (fSlow147 * (fTempPerm27 * ftbl0[(((int((65536.0f * (fRec28[0] + fTempPerm17))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm210 = (fSlow489 * (fTempPerm196 * fTempPerm201));
			}
			if (iSlow10) {
				fTempPerm211 = (fTempPerm210 + (fTempPerm199 + fTempPerm207));
			}
			if (iSlow11) {
				iRec120[0] = (iSlow94 * (iRec120[1] + 1));
				iTempPerm212 = int((iRec120[0] < iSlow499));
				fTempPerm213 = expf((0 - (fConst4 / ((iSlow96)?((iTempPerm212)?fSlow498:fSlow72):fSlow496))));
				fRec119[0] = ((fRec119[1] * fTempPerm213) + (((iSlow96)?((iTempPerm212)?1.5873015873015872f:fSlow500):0.0f) * (1.0f - fTempPerm213)));
				fTempPerm214 = (((fTempPerm199 + fTempPerm210) + (fSlow495 * (fTempPerm206 * fTempPerm189))) + (fSlow501 * (min(1.0f, fRec119[0]) * fTempPerm15)));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm215 = ftbl0[(((int((65536.0f * fRec5[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm216 = (fSlow49 * (fTempPerm6 * fTempPerm215));
			}
			if (iSlow3) {
				fTempPerm217 = (fSlow81 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec13[0] + (fTempPerm3 + (fSlow68 * (fTempPerm10 * ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm216))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm218 = ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm3))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm219 = (fSlow81 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec13[0] + (fTempPerm7 + (fSlow68 * (fTempPerm10 * fTempPerm218)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec122[0] = (iSlow62 * (iRec122[1] + 1));
				iTempPerm220 = int((iRec122[0] < iSlow505));
				fTempPerm221 = expf((0 - (fConst4 / ((iSlow64)?((iTempPerm220)?fSlow504:fSlow72):fSlow502))));
				fRec121[0] = ((fRec121[1] * fTempPerm221) + (((iSlow64)?((iTempPerm220)?1.5873015873015872f:fSlow506):0.0f) * (1.0f - fTempPerm221)));
				fTempPerm222 = min(1.0f, fRec121[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm223 = (fSlow507 * (fTempPerm222 * fTempPerm8));
			}
			if (iSlow5) {
				fTempPerm224 = ((fSlow81 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm7))) % 65536) + 65536) % 65536)])) + fTempPerm223);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm225 = (fSlow81 * (fTempPerm13 * ftbl0[(((int((65536.0f * fRec13[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm226 = (fTempPerm223 + fTempPerm225);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm227 = ftbl0[(((int((65536.0f * fRec9[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm228 = (fSlow68 * (fTempPerm10 * fTempPerm227));
			}
			if (iSlow7) {
				fTempPerm229 = (fSlow81 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec13[0] + ((fTempPerm3 + fTempPerm216) + fTempPerm228)))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec124[0] = (iSlow43 * (iRec124[1] + 1));
				iTempPerm230 = int((iRec124[0] < iSlow511));
				fTempPerm231 = expf((0 - (fConst4 / ((iSlow45)?((iTempPerm230)?fSlow510:fSlow72):fSlow508))));
				fRec123[0] = ((fRec123[1] * fTempPerm231) + (((iSlow45)?((iTempPerm230)?1.5873015873015872f:fSlow512):0.0f) * (1.0f - fTempPerm231)));
				fTempPerm232 = min(1.0f, fRec123[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm233 = (fSlow513 * (fTempPerm232 * fTempPerm4));
			}
			if (iSlow8) {
				fTempPerm234 = ((fSlow81 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm228))) % 65536) + 65536) % 65536)])) + fTempPerm233);
			}
			if (iSlow9) {
				fTempPerm235 = ((fSlow507 * (fTempPerm222 * fTempPerm218)) + (fTempPerm233 + (fSlow81 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm3))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm236 = (fSlow507 * (fTempPerm222 * fTempPerm227));
			}
			if (iSlow10) {
				fTempPerm237 = (fTempPerm236 + (fTempPerm225 + fTempPerm233));
			}
			if (iSlow11) {
				iRec126[0] = (iSlow24 * (iRec126[1] + 1));
				iTempPerm238 = int((iRec126[0] < iSlow517));
				fTempPerm239 = expf((0 - (fConst4 / ((iSlow26)?((iTempPerm238)?fSlow516:fSlow72):fSlow514))));
				fRec125[0] = ((fRec125[1] * fTempPerm239) + (((iSlow26)?((iTempPerm238)?1.5873015873015872f:fSlow518):0.0f) * (1.0f - fTempPerm239)));
				fTempPerm240 = (((fTempPerm225 + fTempPerm236) + (fSlow513 * (fTempPerm232 * fTempPerm215))) + (fSlow519 * (min(1.0f, fRec125[0]) * fTempPerm1)));
			}
			output0[i] = (FAUSTFLOAT)(fTempPerm240 + (fTempPerm237 + (fTempPerm235 + (fTempPerm234 + (fTempPerm229 + (fTempPerm226 + (fTempPerm224 + (fTempPerm219 + (fTempPerm217 + (fTempPerm14 + ((fTempPerm214 + (fTempPerm211 + (fTempPerm209 + (fTempPerm208 + (fTempPerm203 + (fTempPerm200 + (fTempPerm198 + (fTempPerm193 + (fTempPerm191 + (fTempPerm28 + ((fTempPerm188 + (fTempPerm185 + (fTempPerm183 + (fTempPerm182 + (fTempPerm177 + (fTempPerm174 + (fTempPerm172 + (fTempPerm167 + (fTempPerm165 + (fTempPerm42 + ((fTempPerm162 + (fTempPerm159 + (fTempPerm157 + (fTempPerm156 + (fTempPerm151 + (fTempPerm148 + (fTempPerm146 + (fTempPerm141 + (fTempPerm139 + (fTempPerm56 + ((fTempPerm136 + (fTempPerm133 + (fTempPerm131 + (fTempPerm130 + (fTempPerm125 + (fTempPerm122 + (fTempPerm120 + (fTempPerm115 + (fTempPerm113 + (fTempPerm70 + (((((((((((fTempPerm110 + fTempPerm110) + fTempPerm109) + fTempPerm108) + fTempPerm107) + fTempPerm106) + fTempPerm102) + fTempPerm98) + fTempPerm94) + fTempPerm92) + fTempPerm87) + fTempPerm70))))))))))) + fTempPerm56))))))))))) + fTempPerm42))))))))))) + fTempPerm28))))))))))) + fTempPerm14)))))))))));
			// post processing
			if (iSlow11) {
				fRec125[1] = fRec125[0];
				iRec126[1] = iRec126[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec123[1] = fRec123[0];
				iRec124[1] = iRec124[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec121[1] = fRec121[0];
				iRec122[1] = iRec122[0];
			}
			if (iSlow11) {
				fRec119[1] = fRec119[0];
				iRec120[1] = iRec120[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec117[1] = fRec117[0];
				iRec118[1] = iRec118[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec115[1] = fRec115[0];
				iRec116[1] = iRec116[0];
			}
			if (iSlow11) {
				fRec113[1] = fRec113[0];
				iRec114[1] = iRec114[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec111[1] = fRec111[0];
				iRec112[1] = iRec112[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec109[1] = fRec109[0];
				iRec110[1] = iRec110[0];
			}
			if (iSlow11) {
				fRec107[1] = fRec107[0];
				iRec108[1] = iRec108[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec105[1] = fRec105[0];
				iRec106[1] = iRec106[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec103[1] = fRec103[0];
				iRec104[1] = iRec104[0];
			}
			if (iSlow11) {
				fRec101[1] = fRec101[0];
				iRec102[1] = iRec102[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec99[1] = fRec99[0];
				iRec100[1] = iRec100[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec97[1] = fRec97[0];
				iRec98[1] = iRec98[0];
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
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec90[1] = fRec90[0];
				fRec88[1] = fRec88[0];
				fRec89[1] = fRec89[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec86[1] = fRec86[0];
				iRec87[1] = iRec87[0];
				fRec85[1] = fRec85[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec83[1] = fRec83[0];
				iRec84[1] = iRec84[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec82[1] = fRec82[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec80[1] = fRec80[0];
				iRec81[1] = iRec81[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec79[1] = fRec79[0];
			}
			if (iSlow11) {
				fRec77[1] = fRec77[0];
				iRec78[1] = iRec78[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec76[1] = fRec76[0];
				fRec74[1] = fRec74[0];
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
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec64[1] = fRec64[0];
				fRec62[1] = fRec62[0];
				fRec63[1] = fRec63[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec61[1] = fRec61[0];
				fRec59[1] = fRec59[0];
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
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec49[1] = fRec49[0];
				fRec47[1] = fRec47[0];
				fRec48[1] = fRec48[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec46[1] = fRec46[0];
				fRec44[1] = fRec44[0];
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
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec34[1] = fRec34[0];
				fRec32[1] = fRec32[0];
				fRec33[1] = fRec33[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec31[1] = fRec31[0];
				fRec29[1] = fRec29[0];
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
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec19[1] = fRec19[0];
				fRec17[1] = fRec17[0];
				fRec18[1] = fRec18[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec16[1] = fRec16[0];
				fRec14[1] = fRec14[0];
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
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
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
