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
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	float 	fTempPerm4;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	float 	fRec5[2];
	float 	fTempPerm5;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fbutton1;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	float 	fRec7[2];
	int 	iTempPerm6;
	float 	fRec6[2];
	float 	fRec8[2];
	float 	fTempPerm7;
	float 	fTempPerm8;
	FAUSTFLOAT 	fslider15;
	float 	fTempPerm9;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	float 	fRec9[2];
	float 	fTempPerm10;
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fbutton2;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT 	fslider21;
	float 	fRec11[2];
	int 	iTempPerm11;
	float 	fRec10[2];
	float 	fRec12[2];
	float 	fTempPerm12;
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
	int 	iTempPerm13;
	float 	fConst4;
	float 	fTempPerm14;
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	float 	fRec14[2];
	float 	fTempPerm15;
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT 	fslider34;
	float 	fTempPerm16;
	FAUSTFLOAT 	fslider35;
	FAUSTFLOAT 	fslider36;
	FAUSTFLOAT 	fslider37;
	float 	fRec16[2];
	float 	fTempPerm17;
	FAUSTFLOAT 	fslider38;
	FAUSTFLOAT 	fbutton4;
	FAUSTFLOAT 	fslider39;
	FAUSTFLOAT 	fslider40;
	float 	fRec18[2];
	int 	iTempPerm18;
	float 	fRec17[2];
	float 	fRec19[2];
	float 	fTempPerm19;
	FAUSTFLOAT 	fslider41;
	float 	fTempPerm20;
	FAUSTFLOAT 	fslider42;
	FAUSTFLOAT 	fslider43;
	FAUSTFLOAT 	fslider44;
	float 	fRec20[2];
	float 	fTempPerm21;
	FAUSTFLOAT 	fslider45;
	FAUSTFLOAT 	fbutton5;
	FAUSTFLOAT 	fslider46;
	FAUSTFLOAT 	fslider47;
	float 	fRec22[2];
	int 	iTempPerm22;
	float 	fRec21[2];
	float 	fRec23[2];
	float 	fTempPerm23;
	float 	fTempPerm24;
	FAUSTFLOAT 	fslider48;
	float 	fTempPerm25;
	FAUSTFLOAT 	fslider49;
	FAUSTFLOAT 	fslider50;
	FAUSTFLOAT 	fslider51;
	float 	fRec24[2];
	float 	fTempPerm26;
	FAUSTFLOAT 	fslider52;
	FAUSTFLOAT 	fbutton6;
	FAUSTFLOAT 	fslider53;
	FAUSTFLOAT 	fslider54;
	float 	fRec26[2];
	int 	iTempPerm27;
	float 	fRec25[2];
	float 	fRec27[2];
	float 	fTempPerm28;
	FAUSTFLOAT 	fslider55;
	FAUSTFLOAT 	fslider56;
	FAUSTFLOAT 	fslider57;
	FAUSTFLOAT 	fslider58;
	float 	fRec28[2];
	FAUSTFLOAT 	fslider59;
	FAUSTFLOAT 	fslider60;
	FAUSTFLOAT 	fbutton7;
	int 	iRec30[2];
	int 	iTempPerm29;
	float 	fTempPerm30;
	FAUSTFLOAT 	fslider61;
	float 	fRec29[2];
	float 	fTempPerm31;
	FAUSTFLOAT 	fslider62;
	FAUSTFLOAT 	fslider63;
	float 	fTempPerm32;
	FAUSTFLOAT 	fslider64;
	FAUSTFLOAT 	fslider65;
	FAUSTFLOAT 	fslider66;
	float 	fRec31[2];
	float 	fTempPerm33;
	FAUSTFLOAT 	fslider67;
	FAUSTFLOAT 	fbutton8;
	FAUSTFLOAT 	fslider68;
	FAUSTFLOAT 	fslider69;
	float 	fRec33[2];
	int 	iTempPerm34;
	float 	fRec32[2];
	float 	fRec34[2];
	float 	fTempPerm35;
	FAUSTFLOAT 	fslider70;
	float 	fTempPerm36;
	FAUSTFLOAT 	fslider71;
	FAUSTFLOAT 	fslider72;
	FAUSTFLOAT 	fslider73;
	float 	fRec35[2];
	float 	fTempPerm37;
	FAUSTFLOAT 	fslider74;
	FAUSTFLOAT 	fbutton9;
	FAUSTFLOAT 	fslider75;
	FAUSTFLOAT 	fslider76;
	float 	fRec37[2];
	int 	iTempPerm38;
	float 	fRec36[2];
	float 	fRec38[2];
	float 	fTempPerm39;
	float 	fTempPerm40;
	FAUSTFLOAT 	fslider77;
	float 	fTempPerm41;
	FAUSTFLOAT 	fslider78;
	FAUSTFLOAT 	fslider79;
	FAUSTFLOAT 	fslider80;
	float 	fRec39[2];
	float 	fTempPerm42;
	FAUSTFLOAT 	fslider81;
	FAUSTFLOAT 	fbutton10;
	FAUSTFLOAT 	fslider82;
	FAUSTFLOAT 	fslider83;
	float 	fRec41[2];
	int 	iTempPerm43;
	float 	fRec40[2];
	float 	fRec42[2];
	float 	fTempPerm44;
	FAUSTFLOAT 	fslider84;
	FAUSTFLOAT 	fslider85;
	FAUSTFLOAT 	fslider86;
	FAUSTFLOAT 	fslider87;
	float 	fRec43[2];
	FAUSTFLOAT 	fslider88;
	FAUSTFLOAT 	fslider89;
	FAUSTFLOAT 	fbutton11;
	int 	iRec45[2];
	int 	iTempPerm45;
	float 	fTempPerm46;
	FAUSTFLOAT 	fslider90;
	float 	fRec44[2];
	float 	fTempPerm47;
	FAUSTFLOAT 	fslider91;
	FAUSTFLOAT 	fslider92;
	float 	fTempPerm48;
	FAUSTFLOAT 	fslider93;
	FAUSTFLOAT 	fslider94;
	FAUSTFLOAT 	fslider95;
	float 	fRec46[2];
	float 	fTempPerm49;
	FAUSTFLOAT 	fslider96;
	FAUSTFLOAT 	fbutton12;
	FAUSTFLOAT 	fslider97;
	FAUSTFLOAT 	fslider98;
	float 	fRec48[2];
	int 	iTempPerm50;
	float 	fRec47[2];
	float 	fRec49[2];
	float 	fTempPerm51;
	FAUSTFLOAT 	fslider99;
	float 	fTempPerm52;
	FAUSTFLOAT 	fslider100;
	FAUSTFLOAT 	fslider101;
	FAUSTFLOAT 	fslider102;
	float 	fRec50[2];
	float 	fTempPerm53;
	FAUSTFLOAT 	fslider103;
	FAUSTFLOAT 	fbutton13;
	FAUSTFLOAT 	fslider104;
	FAUSTFLOAT 	fslider105;
	float 	fRec52[2];
	int 	iTempPerm54;
	float 	fRec51[2];
	float 	fRec53[2];
	float 	fTempPerm55;
	float 	fTempPerm56;
	FAUSTFLOAT 	fslider106;
	float 	fTempPerm57;
	FAUSTFLOAT 	fslider107;
	FAUSTFLOAT 	fslider108;
	FAUSTFLOAT 	fslider109;
	float 	fRec54[2];
	float 	fTempPerm58;
	FAUSTFLOAT 	fslider110;
	FAUSTFLOAT 	fbutton14;
	FAUSTFLOAT 	fslider111;
	FAUSTFLOAT 	fslider112;
	float 	fRec56[2];
	int 	iTempPerm59;
	float 	fRec55[2];
	float 	fRec57[2];
	float 	fTempPerm60;
	FAUSTFLOAT 	fslider113;
	FAUSTFLOAT 	fslider114;
	FAUSTFLOAT 	fslider115;
	FAUSTFLOAT 	fslider116;
	float 	fRec58[2];
	FAUSTFLOAT 	fslider117;
	FAUSTFLOAT 	fslider118;
	FAUSTFLOAT 	fbutton15;
	int 	iRec60[2];
	int 	iTempPerm61;
	float 	fTempPerm62;
	FAUSTFLOAT 	fslider119;
	float 	fRec59[2];
	float 	fTempPerm63;
	FAUSTFLOAT 	fslider120;
	FAUSTFLOAT 	fslider121;
	float 	fTempPerm64;
	FAUSTFLOAT 	fslider122;
	FAUSTFLOAT 	fslider123;
	FAUSTFLOAT 	fslider124;
	float 	fRec61[2];
	float 	fTempPerm65;
	FAUSTFLOAT 	fslider125;
	FAUSTFLOAT 	fbutton16;
	FAUSTFLOAT 	fslider126;
	FAUSTFLOAT 	fslider127;
	float 	fRec63[2];
	int 	iTempPerm66;
	float 	fRec62[2];
	float 	fRec64[2];
	float 	fTempPerm67;
	FAUSTFLOAT 	fslider128;
	float 	fTempPerm68;
	FAUSTFLOAT 	fslider129;
	FAUSTFLOAT 	fslider130;
	FAUSTFLOAT 	fslider131;
	float 	fRec65[2];
	float 	fTempPerm69;
	FAUSTFLOAT 	fslider132;
	FAUSTFLOAT 	fbutton17;
	FAUSTFLOAT 	fslider133;
	FAUSTFLOAT 	fslider134;
	float 	fRec67[2];
	int 	iTempPerm70;
	float 	fRec66[2];
	float 	fRec68[2];
	float 	fTempPerm71;
	float 	fTempPerm72;
	FAUSTFLOAT 	fslider135;
	float 	fTempPerm73;
	FAUSTFLOAT 	fslider136;
	FAUSTFLOAT 	fslider137;
	FAUSTFLOAT 	fslider138;
	float 	fRec69[2];
	float 	fTempPerm74;
	FAUSTFLOAT 	fslider139;
	FAUSTFLOAT 	fbutton18;
	FAUSTFLOAT 	fslider140;
	FAUSTFLOAT 	fslider141;
	float 	fRec71[2];
	int 	iTempPerm75;
	float 	fRec70[2];
	float 	fRec72[2];
	float 	fTempPerm76;
	FAUSTFLOAT 	fslider142;
	FAUSTFLOAT 	fslider143;
	FAUSTFLOAT 	fslider144;
	FAUSTFLOAT 	fslider145;
	float 	fRec73[2];
	FAUSTFLOAT 	fslider146;
	FAUSTFLOAT 	fslider147;
	FAUSTFLOAT 	fbutton19;
	int 	iRec75[2];
	int 	iTempPerm77;
	float 	fTempPerm78;
	FAUSTFLOAT 	fslider148;
	float 	fRec74[2];
	float 	fTempPerm79;
	FAUSTFLOAT 	fslider149;
	FAUSTFLOAT 	fslider150;
	float 	fTempPerm80;
	FAUSTFLOAT 	fslider151;
	FAUSTFLOAT 	fslider152;
	FAUSTFLOAT 	fslider153;
	float 	fRec76[2];
	float 	fTempPerm81;
	FAUSTFLOAT 	fslider154;
	FAUSTFLOAT 	fslider155;
	FAUSTFLOAT 	fbutton20;
	int 	iRec78[2];
	int 	iTempPerm82;
	float 	fTempPerm83;
	FAUSTFLOAT 	fslider156;
	float 	fRec77[2];
	FAUSTFLOAT 	fslider157;
	FAUSTFLOAT 	fslider158;
	FAUSTFLOAT 	fslider159;
	FAUSTFLOAT 	fslider160;
	FAUSTFLOAT 	fslider161;
	float 	fRec79[2];
	float 	fTempPerm84;
	FAUSTFLOAT 	fslider162;
	FAUSTFLOAT 	fslider163;
	FAUSTFLOAT 	fbutton21;
	int 	iRec81[2];
	int 	iTempPerm85;
	float 	fTempPerm86;
	FAUSTFLOAT 	fslider164;
	float 	fRec80[2];
	float 	fTempPerm87;
	FAUSTFLOAT 	fslider165;
	FAUSTFLOAT 	fslider166;
	FAUSTFLOAT 	fslider167;
	FAUSTFLOAT 	fslider168;
	FAUSTFLOAT 	fslider169;
	float 	fRec82[2];
	float 	fTempPerm88;
	FAUSTFLOAT 	fslider170;
	FAUSTFLOAT 	fslider171;
	FAUSTFLOAT 	fbutton22;
	int 	iRec84[2];
	int 	iTempPerm89;
	float 	fTempPerm90;
	FAUSTFLOAT 	fslider172;
	float 	fRec83[2];
	float 	fTempPerm91;
	FAUSTFLOAT 	fslider173;
	FAUSTFLOAT 	fslider174;
	float 	fTempPerm92;
	FAUSTFLOAT 	fslider175;
	FAUSTFLOAT 	fslider176;
	FAUSTFLOAT 	fslider177;
	float 	fRec85[2];
	FAUSTFLOAT 	fslider178;
	FAUSTFLOAT 	fslider179;
	FAUSTFLOAT 	fbutton23;
	int 	iRec87[2];
	int 	iTempPerm93;
	float 	fTempPerm94;
	FAUSTFLOAT 	fslider180;
	float 	fRec86[2];
	float 	fTempPerm95;
	FAUSTFLOAT 	fslider181;
	FAUSTFLOAT 	fslider182;
	float 	fTempPerm96;
	float 	fTempPerm97;
	FAUSTFLOAT 	fslider183;
	FAUSTFLOAT 	fslider184;
	FAUSTFLOAT 	fslider185;
	float 	fRec89[2];
	int 	iTempPerm98;
	float 	fRec88[2];
	float 	fRec90[2];
	float 	fTempPerm99;
	float 	fTempPerm100;
	float 	fTempPerm101;
	float 	fTempPerm102;
	float 	fTempPerm103;
	float 	fTempPerm104;
	float 	fTempPerm105;
	FAUSTFLOAT 	fslider186;
	FAUSTFLOAT 	fslider187;
	FAUSTFLOAT 	fslider188;
	float 	fRec92[2];
	int 	iTempPerm106;
	float 	fRec91[2];
	float 	fRec93[2];
	float 	fTempPerm107;
	float 	fTempPerm108;
	float 	fTempPerm109;
	FAUSTFLOAT 	fslider189;
	FAUSTFLOAT 	fslider190;
	FAUSTFLOAT 	fslider191;
	float 	fRec95[2];
	int 	iTempPerm110;
	float 	fRec94[2];
	float 	fRec96[2];
	float 	fTempPerm111;
	float 	fTempPerm112;
	float 	fTempPerm113;
	float 	fTempPerm114;
	float 	fTempPerm115;
	float 	fTempPerm116;
	float 	fTempPerm117;
	float 	fTempPerm118;
	float 	fTempPerm119;
	float 	fTempPerm120;
	float 	fTempPerm121;
	float 	fTempPerm122;
	float 	fTempPerm123;
	float 	fTempPerm124;
	float 	fTempPerm125;
	float 	fTempPerm126;
	float 	fTempPerm127;
	float 	fTempPerm128;
	float 	fTempPerm129;
	FAUSTFLOAT 	fslider192;
	FAUSTFLOAT 	fslider193;
	int 	iRec98[2];
	int 	iTempPerm130;
	float 	fTempPerm131;
	FAUSTFLOAT 	fslider194;
	float 	fRec97[2];
	float 	fTempPerm132;
	FAUSTFLOAT 	fslider195;
	float 	fTempPerm133;
	float 	fTempPerm134;
	float 	fTempPerm135;
	float 	fTempPerm136;
	float 	fTempPerm137;
	float 	fTempPerm138;
	float 	fTempPerm139;
	FAUSTFLOAT 	fslider196;
	FAUSTFLOAT 	fslider197;
	int 	iRec100[2];
	int 	iTempPerm140;
	float 	fTempPerm141;
	FAUSTFLOAT 	fslider198;
	float 	fRec99[2];
	float 	fTempPerm142;
	FAUSTFLOAT 	fslider199;
	float 	fTempPerm143;
	float 	fTempPerm144;
	float 	fTempPerm145;
	float 	fTempPerm146;
	float 	fTempPerm147;
	FAUSTFLOAT 	fslider200;
	FAUSTFLOAT 	fslider201;
	int 	iRec102[2];
	int 	iTempPerm148;
	float 	fTempPerm149;
	FAUSTFLOAT 	fslider202;
	float 	fRec101[2];
	FAUSTFLOAT 	fslider203;
	float 	fTempPerm150;
	float 	fTempPerm151;
	float 	fTempPerm152;
	float 	fTempPerm153;
	float 	fTempPerm154;
	float 	fTempPerm155;
	float 	fTempPerm156;
	FAUSTFLOAT 	fslider204;
	FAUSTFLOAT 	fslider205;
	int 	iRec104[2];
	int 	iTempPerm157;
	float 	fTempPerm158;
	FAUSTFLOAT 	fslider206;
	float 	fRec103[2];
	float 	fTempPerm159;
	FAUSTFLOAT 	fslider207;
	float 	fTempPerm160;
	float 	fTempPerm161;
	float 	fTempPerm162;
	float 	fTempPerm163;
	float 	fTempPerm164;
	float 	fTempPerm165;
	float 	fTempPerm166;
	FAUSTFLOAT 	fslider208;
	FAUSTFLOAT 	fslider209;
	int 	iRec106[2];
	int 	iTempPerm167;
	float 	fTempPerm168;
	FAUSTFLOAT 	fslider210;
	float 	fRec105[2];
	float 	fTempPerm169;
	FAUSTFLOAT 	fslider211;
	float 	fTempPerm170;
	float 	fTempPerm171;
	float 	fTempPerm172;
	float 	fTempPerm173;
	float 	fTempPerm174;
	FAUSTFLOAT 	fslider212;
	FAUSTFLOAT 	fslider213;
	int 	iRec108[2];
	int 	iTempPerm175;
	float 	fTempPerm176;
	FAUSTFLOAT 	fslider214;
	float 	fRec107[2];
	FAUSTFLOAT 	fslider215;
	float 	fTempPerm177;
	float 	fTempPerm178;
	float 	fTempPerm179;
	float 	fTempPerm180;
	float 	fTempPerm181;
	float 	fTempPerm182;
	float 	fTempPerm183;
	FAUSTFLOAT 	fslider216;
	FAUSTFLOAT 	fslider217;
	int 	iRec110[2];
	int 	iTempPerm184;
	float 	fTempPerm185;
	FAUSTFLOAT 	fslider218;
	float 	fRec109[2];
	float 	fTempPerm186;
	FAUSTFLOAT 	fslider219;
	float 	fTempPerm187;
	float 	fTempPerm188;
	float 	fTempPerm189;
	float 	fTempPerm190;
	float 	fTempPerm191;
	float 	fTempPerm192;
	float 	fTempPerm193;
	FAUSTFLOAT 	fslider220;
	FAUSTFLOAT 	fslider221;
	int 	iRec112[2];
	int 	iTempPerm194;
	float 	fTempPerm195;
	FAUSTFLOAT 	fslider222;
	float 	fRec111[2];
	float 	fTempPerm196;
	FAUSTFLOAT 	fslider223;
	float 	fTempPerm197;
	float 	fTempPerm198;
	float 	fTempPerm199;
	float 	fTempPerm200;
	float 	fTempPerm201;
	FAUSTFLOAT 	fslider224;
	FAUSTFLOAT 	fslider225;
	int 	iRec114[2];
	int 	iTempPerm202;
	float 	fTempPerm203;
	FAUSTFLOAT 	fslider226;
	float 	fRec113[2];
	FAUSTFLOAT 	fslider227;
	float 	fTempPerm204;
	float 	fTempPerm205;
	float 	fTempPerm206;
	float 	fTempPerm207;
	float 	fTempPerm208;
	float 	fTempPerm209;
	float 	fTempPerm210;
	FAUSTFLOAT 	fslider228;
	FAUSTFLOAT 	fslider229;
	int 	iRec116[2];
	int 	iTempPerm211;
	float 	fTempPerm212;
	FAUSTFLOAT 	fslider230;
	float 	fRec115[2];
	float 	fTempPerm213;
	FAUSTFLOAT 	fslider231;
	float 	fTempPerm214;
	float 	fTempPerm215;
	float 	fTempPerm216;
	float 	fTempPerm217;
	float 	fTempPerm218;
	float 	fTempPerm219;
	float 	fTempPerm220;
	FAUSTFLOAT 	fslider232;
	FAUSTFLOAT 	fslider233;
	int 	iRec118[2];
	int 	iTempPerm221;
	float 	fTempPerm222;
	FAUSTFLOAT 	fslider234;
	float 	fRec117[2];
	float 	fTempPerm223;
	FAUSTFLOAT 	fslider235;
	float 	fTempPerm224;
	float 	fTempPerm225;
	float 	fTempPerm226;
	float 	fTempPerm227;
	float 	fTempPerm228;
	FAUSTFLOAT 	fslider236;
	FAUSTFLOAT 	fslider237;
	int 	iRec120[2];
	int 	iTempPerm229;
	float 	fTempPerm230;
	FAUSTFLOAT 	fslider238;
	float 	fRec119[2];
	FAUSTFLOAT 	fslider239;
	float 	fTempPerm231;
	float 	fTempPerm232;
	float 	fTempPerm233;
	float 	fTempPerm234;
	float 	fTempPerm235;
	float 	fTempPerm236;
	float 	fTempPerm237;
	FAUSTFLOAT 	fslider240;
	FAUSTFLOAT 	fslider241;
	int 	iRec122[2];
	int 	iTempPerm238;
	float 	fTempPerm239;
	FAUSTFLOAT 	fslider242;
	float 	fRec121[2];
	float 	fTempPerm240;
	FAUSTFLOAT 	fslider243;
	float 	fTempPerm241;
	float 	fTempPerm242;
	float 	fTempPerm243;
	float 	fTempPerm244;
	float 	fTempPerm245;
	float 	fTempPerm246;
	float 	fTempPerm247;
	FAUSTFLOAT 	fslider244;
	FAUSTFLOAT 	fslider245;
	int 	iRec124[2];
	int 	iTempPerm248;
	float 	fTempPerm249;
	FAUSTFLOAT 	fslider246;
	float 	fRec123[2];
	float 	fTempPerm250;
	FAUSTFLOAT 	fslider247;
	float 	fTempPerm251;
	float 	fTempPerm252;
	float 	fTempPerm253;
	float 	fTempPerm254;
	float 	fTempPerm255;
	FAUSTFLOAT 	fslider248;
	FAUSTFLOAT 	fslider249;
	int 	iRec126[2];
	int 	iTempPerm256;
	float 	fTempPerm257;
	FAUSTFLOAT 	fslider250;
	float 	fRec125[2];
	FAUSTFLOAT 	fslider251;
	float 	fTempPerm258;
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
		iTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		iTempPerm11 = 0;
		fTempPerm12 = 0;
		iTempPerm13 = 0;
		fConst4 = (6.9100000000000001f / fConst0);
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		iTempPerm18 = 0;
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
		iTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		iTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		iTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		iTempPerm43 = 0;
		fTempPerm44 = 0;
		iTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		iTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		iTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		iTempPerm59 = 0;
		fTempPerm60 = 0;
		iTempPerm61 = 0;
		fTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		iTempPerm66 = 0;
		fTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		iTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		fTempPerm73 = 0;
		fTempPerm74 = 0;
		iTempPerm75 = 0;
		fTempPerm76 = 0;
		iTempPerm77 = 0;
		fTempPerm78 = 0;
		fTempPerm79 = 0;
		fTempPerm80 = 0;
		fTempPerm81 = 0;
		iTempPerm82 = 0;
		fTempPerm83 = 0;
		fTempPerm84 = 0;
		iTempPerm85 = 0;
		fTempPerm86 = 0;
		fTempPerm87 = 0;
		fTempPerm88 = 0;
		iTempPerm89 = 0;
		fTempPerm90 = 0;
		fTempPerm91 = 0;
		fTempPerm92 = 0;
		iTempPerm93 = 0;
		fTempPerm94 = 0;
		fTempPerm95 = 0;
		fTempPerm96 = 0;
		fTempPerm97 = 0;
		iTempPerm98 = 0;
		fTempPerm99 = 0;
		fTempPerm100 = 0;
		fTempPerm101 = 0;
		fTempPerm102 = 0;
		fTempPerm103 = 0;
		fTempPerm104 = 0;
		fTempPerm105 = 0;
		iTempPerm106 = 0;
		fTempPerm107 = 0;
		fTempPerm108 = 0;
		fTempPerm109 = 0;
		iTempPerm110 = 0;
		fTempPerm111 = 0;
		fTempPerm112 = 0;
		fTempPerm113 = 0;
		fTempPerm114 = 0;
		fTempPerm115 = 0;
		fTempPerm116 = 0;
		fTempPerm117 = 0;
		fTempPerm118 = 0;
		fTempPerm119 = 0;
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
		iTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		fTempPerm133 = 0;
		fTempPerm134 = 0;
		fTempPerm135 = 0;
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
		iTempPerm148 = 0;
		fTempPerm149 = 0;
		fTempPerm150 = 0;
		fTempPerm151 = 0;
		fTempPerm152 = 0;
		fTempPerm153 = 0;
		fTempPerm154 = 0;
		fTempPerm155 = 0;
		fTempPerm156 = 0;
		iTempPerm157 = 0;
		fTempPerm158 = 0;
		fTempPerm159 = 0;
		fTempPerm160 = 0;
		fTempPerm161 = 0;
		fTempPerm162 = 0;
		fTempPerm163 = 0;
		fTempPerm164 = 0;
		fTempPerm165 = 0;
		fTempPerm166 = 0;
		iTempPerm167 = 0;
		fTempPerm168 = 0;
		fTempPerm169 = 0;
		fTempPerm170 = 0;
		fTempPerm171 = 0;
		fTempPerm172 = 0;
		fTempPerm173 = 0;
		fTempPerm174 = 0;
		iTempPerm175 = 0;
		fTempPerm176 = 0;
		fTempPerm177 = 0;
		fTempPerm178 = 0;
		fTempPerm179 = 0;
		fTempPerm180 = 0;
		fTempPerm181 = 0;
		fTempPerm182 = 0;
		fTempPerm183 = 0;
		iTempPerm184 = 0;
		fTempPerm185 = 0;
		fTempPerm186 = 0;
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
		iTempPerm202 = 0;
		fTempPerm203 = 0;
		fTempPerm204 = 0;
		fTempPerm205 = 0;
		fTempPerm206 = 0;
		fTempPerm207 = 0;
		fTempPerm208 = 0;
		fTempPerm209 = 0;
		fTempPerm210 = 0;
		iTempPerm211 = 0;
		fTempPerm212 = 0;
		fTempPerm213 = 0;
		fTempPerm214 = 0;
		fTempPerm215 = 0;
		fTempPerm216 = 0;
		fTempPerm217 = 0;
		fTempPerm218 = 0;
		fTempPerm219 = 0;
		fTempPerm220 = 0;
		iTempPerm221 = 0;
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
		iTempPerm238 = 0;
		fTempPerm239 = 0;
		fTempPerm240 = 0;
		fTempPerm241 = 0;
		fTempPerm242 = 0;
		fTempPerm243 = 0;
		fTempPerm244 = 0;
		fTempPerm245 = 0;
		fTempPerm246 = 0;
		fTempPerm247 = 0;
		iTempPerm248 = 0;
		fTempPerm249 = 0;
		fTempPerm250 = 0;
		fTempPerm251 = 0;
		fTempPerm252 = 0;
		fTempPerm253 = 0;
		fTempPerm254 = 0;
		fTempPerm255 = 0;
		iTempPerm256 = 0;
		fTempPerm257 = 0;
		fTempPerm258 = 0;
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
		fslider8 = 1.0f;
		fslider9 = 0.0f;
		fslider10 = 1.0f;
		fslider11 = 440.0f;
		fslider12 = 0.0f;
		fbutton1 = 0.0;
		fslider13 = 0.0f;
		fslider14 = 0.0f;
		fslider15 = 0.0f;
		fslider16 = 0.0f;
		fslider17 = 1.0f;
		fslider18 = 440.0f;
		fslider19 = 0.0f;
		fbutton2 = 0.0;
		fslider20 = 0.0f;
		fslider21 = 0.0f;
		fslider22 = 0.0f;
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
		fslider38 = 0.0f;
		fbutton4 = 0.0;
		fslider39 = 0.0f;
		fslider40 = 0.0f;
		fslider41 = 0.0f;
		fslider42 = 0.0f;
		fslider43 = 1.0f;
		fslider44 = 440.0f;
		fslider45 = 0.0f;
		fbutton5 = 0.0;
		fslider46 = 0.0f;
		fslider47 = 0.0f;
		fslider48 = 0.0f;
		fslider49 = 0.0f;
		fslider50 = 1.0f;
		fslider51 = 440.0f;
		fslider52 = 0.0f;
		fbutton6 = 0.0;
		fslider53 = 0.0f;
		fslider54 = 0.0f;
		fslider55 = 0.0f;
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
		fslider67 = 0.0f;
		fbutton8 = 0.0;
		fslider68 = 0.0f;
		fslider69 = 0.0f;
		fslider70 = 0.0f;
		fslider71 = 0.0f;
		fslider72 = 1.0f;
		fslider73 = 440.0f;
		fslider74 = 0.0f;
		fbutton9 = 0.0;
		fslider75 = 0.0f;
		fslider76 = 0.0f;
		fslider77 = 0.0f;
		fslider78 = 0.0f;
		fslider79 = 1.0f;
		fslider80 = 440.0f;
		fslider81 = 0.0f;
		fbutton10 = 0.0;
		fslider82 = 0.0f;
		fslider83 = 0.0f;
		fslider84 = 0.0f;
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
		fslider96 = 0.0f;
		fbutton12 = 0.0;
		fslider97 = 0.0f;
		fslider98 = 0.0f;
		fslider99 = 0.0f;
		fslider100 = 1.0f;
		fslider101 = 440.0f;
		fslider102 = 0.0f;
		fslider103 = 0.0f;
		fbutton13 = 0.0;
		fslider104 = 0.0f;
		fslider105 = 0.0f;
		fslider106 = 0.0f;
		fslider107 = 0.0f;
		fslider108 = 1.0f;
		fslider109 = 440.0f;
		fslider110 = 0.0f;
		fbutton14 = 0.0;
		fslider111 = 0.0f;
		fslider112 = 0.0f;
		fslider113 = 0.0f;
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
		fslider125 = 0.0f;
		fbutton16 = 0.0;
		fslider126 = 0.0f;
		fslider127 = 0.0f;
		fslider128 = 0.0f;
		fslider129 = 0.0f;
		fslider130 = 1.0f;
		fslider131 = 440.0f;
		fslider132 = 0.0f;
		fbutton17 = 0.0;
		fslider133 = 0.0f;
		fslider134 = 0.0f;
		fslider135 = 0.0f;
		fslider136 = 0.0f;
		fslider137 = 1.0f;
		fslider138 = 440.0f;
		fslider139 = 0.0f;
		fbutton18 = 0.0;
		fslider140 = 0.0f;
		fslider141 = 0.0f;
		fslider142 = 0.0f;
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
		fslider186 = 0.0f;
		fslider187 = 0.0f;
		fslider188 = 0.0f;
		fslider189 = 0.0f;
		fslider190 = 0.0f;
		fslider191 = 0.0f;
		fslider192 = 0.0f;
		fslider193 = 0.0f;
		fslider194 = 0.0f;
		fslider195 = 1.0f;
		fslider196 = 0.0f;
		fslider197 = 0.0f;
		fslider198 = 0.0f;
		fslider199 = 1.0f;
		fslider200 = 0.0f;
		fslider201 = 0.0f;
		fslider202 = 0.0f;
		fslider203 = 1.0f;
		fslider204 = 0.0f;
		fslider205 = 0.0f;
		fslider206 = 0.0f;
		fslider207 = 1.0f;
		fslider208 = 0.0f;
		fslider209 = 0.0f;
		fslider210 = 0.0f;
		fslider211 = 1.0f;
		fslider212 = 0.0f;
		fslider213 = 0.0f;
		fslider214 = 0.0f;
		fslider215 = 1.0f;
		fslider216 = 0.0f;
		fslider217 = 0.0f;
		fslider218 = 0.0f;
		fslider219 = 1.0f;
		fslider220 = 0.0f;
		fslider221 = 0.0f;
		fslider222 = 0.0f;
		fslider223 = 1.0f;
		fslider224 = 0.0f;
		fslider225 = 0.0f;
		fslider226 = 0.0f;
		fslider227 = 1.0f;
		fslider228 = 0.0f;
		fslider229 = 0.0f;
		fslider230 = 0.0f;
		fslider231 = 1.0f;
		fslider232 = 0.0f;
		fslider233 = 0.0f;
		fslider234 = 0.0f;
		fslider235 = 1.0f;
		fslider236 = 0.0f;
		fslider237 = 0.0f;
		fslider238 = 0.0f;
		fslider239 = 1.0f;
		fslider240 = 0.0f;
		fslider241 = 0.0f;
		fslider242 = 0.0f;
		fslider243 = 1.0f;
		fslider244 = 0.0f;
		fslider245 = 0.0f;
		fslider246 = 0.0f;
		fslider247 = 1.0f;
		fslider248 = 0.0f;
		fslider249 = 0.0f;
		fslider250 = 0.0f;
		fslider251 = 1.0f;
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
		ui_interface->addHorizontalSlider("Attack", &fslider30, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider28, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider27, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider31, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("fmAmount", &fslider8, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
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
		ui_interface->addHorizontalSlider("mAtt", &fslider187, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider188, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider186, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider173, 0.0f, 0.0f, 1.0f, 0.01f);
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
		ui_interface->addHorizontalSlider("mAtt", &fslider190, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider191, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider189, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider165, 0.0f, 0.0f, 1.0f, 0.01f);
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
		ui_interface->addHorizontalSlider("ratio", &fslider152, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton20);
		ui_interface->addHorizontalSlider("velocity", &fslider158, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
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
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider205, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider204, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider206, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider107, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider109, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider111, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider112, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider110, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider113, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider108, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton14);
		ui_interface->addHorizontalSlider("velocity", &fslider207, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider209, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider208, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider210, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider102, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider101, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider104, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider105, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider103, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider106, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider100, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton13);
		ui_interface->addHorizontalSlider("velocity", &fslider211, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider213, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider212, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider214, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider93, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider95, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider97, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider98, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider96, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider99, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider94, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton12);
		ui_interface->addHorizontalSlider("velocity", &fslider215, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
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
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider229, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider228, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider230, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider49, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider51, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider53, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider54, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider52, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider55, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider50, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton6);
		ui_interface->addHorizontalSlider("velocity", &fslider231, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider233, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider232, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider234, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider42, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider44, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider46, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider47, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider45, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider48, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider43, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider235, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider237, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider236, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider238, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider35, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider37, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider39, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider40, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider38, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider41, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider36, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider239, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
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
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider193, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider192, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider194, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider136, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider138, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider140, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider141, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider139, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider142, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider137, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton18);
		ui_interface->addHorizontalSlider("velocity", &fslider195, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider197, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider196, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider198, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider129, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider131, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider133, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider134, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider132, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider135, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider130, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton17);
		ui_interface->addHorizontalSlider("velocity", &fslider199, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider201, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider200, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider202, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider122, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider124, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider126, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider127, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider125, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider128, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider123, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton16);
		ui_interface->addHorizontalSlider("velocity", &fslider203, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
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
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider217, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider216, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider218, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider78, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider80, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider82, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider83, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider81, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider84, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider79, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton10);
		ui_interface->addHorizontalSlider("velocity", &fslider219, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider221, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider220, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider222, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider71, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider73, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider75, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider76, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider74, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider77, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider72, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton9);
		ui_interface->addHorizontalSlider("velocity", &fslider223, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider225, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider224, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider226, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider64, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider66, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider68, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider69, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider67, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider70, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider65, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton8);
		ui_interface->addHorizontalSlider("velocity", &fslider227, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->openVerticalBox("op0");
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
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider241, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider240, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider242, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider16, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider18, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider20, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider21, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider19, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider22, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider17, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider243, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider245, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider244, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider246, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider9, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider11, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider13, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider14, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider12, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider15, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider10, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider247, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider249, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider248, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider250, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider1, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("freq", &fslider3, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("mAtt", &fslider5, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider6, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider7, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider2, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider251, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
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
		float 	fSlow31 = float(fslider8);
		float 	fSlow32 = (fSlow31 * fSlow30);
		float 	fSlow33 = (fConst1 * ((float(fslider11) * float(fslider10)) + (25.0f * float(fslider9))));
		float 	fSlow34 = float(fslider12);
		float 	fSlow35 = float(fbutton1);
		float 	fSlow36 = (fSlow35 * fSlow34);
		float 	fSlow37 = float(fslider13);
		float 	fSlow38 = (fConst2 * fSlow37);
		float 	fSlow39 = float(fslider14);
		float 	fSlow40 = (((1.0f - fSlow34) * fSlow39) + fSlow37);
		float 	fSlow41 = (fConst2 * fSlow40);
		int 	iSlow42 = int(((fSlow35 == 0.0f) > 0));
		float 	fSlow43 = ((fSlow36 + -1.0f) / (0 - (fConst2 * (fSlow37 - fSlow40))));
		float 	fSlow44 = (fConst3 / fSlow37);
		int 	iSlow45 = (fSlow35 > 0.0f);
		float 	fSlow46 = float(iSlow45);
		int 	iSlow47 = int(iSlow45);
		float 	fSlow48 = max(0.001f, (fConst2 * (fSlow34 * fSlow39)));
		int 	iSlow49 = int((iSlow45 > 0));
		float 	fSlow50 = (1.0f / fSlow48);
		float 	fSlow51 = float(fslider15);
		float 	fSlow52 = (fSlow31 * fSlow51);
		float 	fSlow53 = (fConst1 * ((float(fslider18) * float(fslider17)) + (25.0f * float(fslider16))));
		float 	fSlow54 = float(fslider19);
		float 	fSlow55 = float(fbutton2);
		float 	fSlow56 = (fSlow55 * fSlow54);
		float 	fSlow57 = float(fslider20);
		float 	fSlow58 = (fConst2 * fSlow57);
		float 	fSlow59 = float(fslider21);
		float 	fSlow60 = (((1.0f - fSlow54) * fSlow59) + fSlow57);
		float 	fSlow61 = (fConst2 * fSlow60);
		int 	iSlow62 = int(((fSlow55 == 0.0f) > 0));
		float 	fSlow63 = ((fSlow56 + -1.0f) / (0 - (fConst2 * (fSlow57 - fSlow60))));
		float 	fSlow64 = (fConst3 / fSlow57);
		int 	iSlow65 = (fSlow55 > 0.0f);
		float 	fSlow66 = float(iSlow65);
		int 	iSlow67 = int(iSlow65);
		float 	fSlow68 = max(0.001f, (fConst2 * (fSlow54 * fSlow59)));
		int 	iSlow69 = int((iSlow65 > 0));
		float 	fSlow70 = (1.0f / fSlow68);
		float 	fSlow71 = float(fslider22);
		float 	fSlow72 = (fSlow31 * fSlow71);
		float 	fSlow73 = (fConst1 * ((float(fslider25) * float(fslider24)) + (25.0f * float(fslider23))));
		float 	fSlow74 = float(fslider27);
		float 	fSlow75 = max((float)0, (fSlow74 + float(fslider26)));
		float 	fSlow76 = float(fslider28);
		float 	fSlow77 = float(fslider30);
		float 	fSlow78 = max((float)0, (fSlow77 + float(fslider29)));
		float 	fSlow79 = (6.9100000000000001f * fSlow78);
		int 	iSlow80 = int((fConst0 * fSlow78));
		int 	iSlow81 = (float(fbutton3) > 0.0f);
		int 	iSlow82 = int(iSlow81);
		float 	fSlow83 = float(fslider31);
		float 	fSlow84 = (float(iSlow81) * max((float)0, ((0.5f * float(fslider32)) + fSlow83)));
		float 	fSlow85 = (float(fslider34) * float(fslider33));
		float 	fSlow86 = (fConst1 * ((float(fslider37) * float(fslider36)) + (25.0f * float(fslider35))));
		float 	fSlow87 = float(fslider38);
		float 	fSlow88 = float(fbutton4);
		float 	fSlow89 = (fSlow88 * fSlow87);
		float 	fSlow90 = float(fslider39);
		float 	fSlow91 = (fConst2 * fSlow90);
		float 	fSlow92 = float(fslider40);
		float 	fSlow93 = (((1.0f - fSlow87) * fSlow92) + fSlow90);
		float 	fSlow94 = (fConst2 * fSlow93);
		int 	iSlow95 = int(((fSlow88 == 0.0f) > 0));
		float 	fSlow96 = ((fSlow89 + -1.0f) / (0 - (fConst2 * (fSlow90 - fSlow93))));
		float 	fSlow97 = (fConst3 / fSlow90);
		int 	iSlow98 = (fSlow88 > 0.0f);
		float 	fSlow99 = float(iSlow98);
		int 	iSlow100 = int(iSlow98);
		float 	fSlow101 = max(0.001f, (fConst2 * (fSlow87 * fSlow92)));
		int 	iSlow102 = int((iSlow98 > 0));
		float 	fSlow103 = (1.0f / fSlow101);
		float 	fSlow104 = float(fslider41);
		float 	fSlow105 = (fSlow31 * fSlow104);
		float 	fSlow106 = (fConst1 * ((float(fslider44) * float(fslider43)) + (25.0f * float(fslider42))));
		float 	fSlow107 = float(fslider45);
		float 	fSlow108 = float(fbutton5);
		float 	fSlow109 = (fSlow108 * fSlow107);
		float 	fSlow110 = float(fslider46);
		float 	fSlow111 = (fConst2 * fSlow110);
		float 	fSlow112 = float(fslider47);
		float 	fSlow113 = (((1.0f - fSlow107) * fSlow112) + fSlow110);
		float 	fSlow114 = (fConst2 * fSlow113);
		int 	iSlow115 = int(((fSlow108 == 0.0f) > 0));
		float 	fSlow116 = ((fSlow109 + -1.0f) / (0 - (fConst2 * (fSlow110 - fSlow113))));
		float 	fSlow117 = (fConst3 / fSlow110);
		int 	iSlow118 = (fSlow108 > 0.0f);
		float 	fSlow119 = float(iSlow118);
		int 	iSlow120 = int(iSlow118);
		float 	fSlow121 = max(0.001f, (fConst2 * (fSlow107 * fSlow112)));
		int 	iSlow122 = int((iSlow118 > 0));
		float 	fSlow123 = (1.0f / fSlow121);
		float 	fSlow124 = float(fslider48);
		float 	fSlow125 = (fSlow31 * fSlow124);
		float 	fSlow126 = (fConst1 * ((float(fslider51) * float(fslider50)) + (25.0f * float(fslider49))));
		float 	fSlow127 = float(fslider52);
		float 	fSlow128 = float(fbutton6);
		float 	fSlow129 = (fSlow128 * fSlow127);
		float 	fSlow130 = float(fslider53);
		float 	fSlow131 = (fConst2 * fSlow130);
		float 	fSlow132 = float(fslider54);
		float 	fSlow133 = (((1.0f - fSlow127) * fSlow132) + fSlow130);
		float 	fSlow134 = (fConst2 * fSlow133);
		int 	iSlow135 = int(((fSlow128 == 0.0f) > 0));
		float 	fSlow136 = ((fSlow129 + -1.0f) / (0 - (fConst2 * (fSlow130 - fSlow133))));
		float 	fSlow137 = (fConst3 / fSlow130);
		int 	iSlow138 = (fSlow128 > 0.0f);
		float 	fSlow139 = float(iSlow138);
		int 	iSlow140 = int(iSlow138);
		float 	fSlow141 = max(0.001f, (fConst2 * (fSlow127 * fSlow132)));
		int 	iSlow142 = int((iSlow138 > 0));
		float 	fSlow143 = (1.0f / fSlow141);
		float 	fSlow144 = float(fslider55);
		float 	fSlow145 = (fSlow31 * fSlow144);
		float 	fSlow146 = (fConst1 * ((float(fslider58) * float(fslider57)) + (25.0f * float(fslider56))));
		float 	fSlow147 = max((float)0, (fSlow74 + float(fslider59)));
		float 	fSlow148 = max((float)0, (fSlow77 + float(fslider60)));
		float 	fSlow149 = (6.9100000000000001f * fSlow148);
		int 	iSlow150 = int((fConst0 * fSlow148));
		int 	iSlow151 = (float(fbutton7) > 0.0f);
		int 	iSlow152 = int(iSlow151);
		float 	fSlow153 = (float(iSlow151) * max((float)0, ((0.5f * float(fslider61)) + fSlow83)));
		float 	fSlow154 = (float(fslider63) * float(fslider62));
		float 	fSlow155 = (fConst1 * ((float(fslider66) * float(fslider65)) + (25.0f * float(fslider64))));
		float 	fSlow156 = float(fslider67);
		float 	fSlow157 = float(fbutton8);
		float 	fSlow158 = (fSlow157 * fSlow156);
		float 	fSlow159 = float(fslider68);
		float 	fSlow160 = (fConst2 * fSlow159);
		float 	fSlow161 = float(fslider69);
		float 	fSlow162 = (((1.0f - fSlow156) * fSlow161) + fSlow159);
		float 	fSlow163 = (fConst2 * fSlow162);
		int 	iSlow164 = int(((fSlow157 == 0.0f) > 0));
		float 	fSlow165 = ((fSlow158 + -1.0f) / (0 - (fConst2 * (fSlow159 - fSlow162))));
		float 	fSlow166 = (fConst3 / fSlow159);
		int 	iSlow167 = (fSlow157 > 0.0f);
		float 	fSlow168 = float(iSlow167);
		int 	iSlow169 = int(iSlow167);
		float 	fSlow170 = max(0.001f, (fConst2 * (fSlow156 * fSlow161)));
		int 	iSlow171 = int((iSlow167 > 0));
		float 	fSlow172 = (1.0f / fSlow170);
		float 	fSlow173 = float(fslider70);
		float 	fSlow174 = (fSlow31 * fSlow173);
		float 	fSlow175 = (fConst1 * ((float(fslider73) * float(fslider72)) + (25.0f * float(fslider71))));
		float 	fSlow176 = float(fslider74);
		float 	fSlow177 = float(fbutton9);
		float 	fSlow178 = (fSlow177 * fSlow176);
		float 	fSlow179 = float(fslider75);
		float 	fSlow180 = (fConst2 * fSlow179);
		float 	fSlow181 = float(fslider76);
		float 	fSlow182 = (((1.0f - fSlow176) * fSlow181) + fSlow179);
		float 	fSlow183 = (fConst2 * fSlow182);
		int 	iSlow184 = int(((fSlow177 == 0.0f) > 0));
		float 	fSlow185 = ((fSlow178 + -1.0f) / (0 - (fConst2 * (fSlow179 - fSlow182))));
		float 	fSlow186 = (fConst3 / fSlow179);
		int 	iSlow187 = (fSlow177 > 0.0f);
		float 	fSlow188 = float(iSlow187);
		int 	iSlow189 = int(iSlow187);
		float 	fSlow190 = max(0.001f, (fConst2 * (fSlow176 * fSlow181)));
		int 	iSlow191 = int((iSlow187 > 0));
		float 	fSlow192 = (1.0f / fSlow190);
		float 	fSlow193 = float(fslider77);
		float 	fSlow194 = (fSlow31 * fSlow193);
		float 	fSlow195 = (fConst1 * ((float(fslider80) * float(fslider79)) + (25.0f * float(fslider78))));
		float 	fSlow196 = float(fslider81);
		float 	fSlow197 = float(fbutton10);
		float 	fSlow198 = (fSlow197 * fSlow196);
		float 	fSlow199 = float(fslider82);
		float 	fSlow200 = (fConst2 * fSlow199);
		float 	fSlow201 = float(fslider83);
		float 	fSlow202 = (((1.0f - fSlow196) * fSlow201) + fSlow199);
		float 	fSlow203 = (fConst2 * fSlow202);
		int 	iSlow204 = int(((fSlow197 == 0.0f) > 0));
		float 	fSlow205 = ((fSlow198 + -1.0f) / (0 - (fConst2 * (fSlow199 - fSlow202))));
		float 	fSlow206 = (fConst3 / fSlow199);
		int 	iSlow207 = (fSlow197 > 0.0f);
		float 	fSlow208 = float(iSlow207);
		int 	iSlow209 = int(iSlow207);
		float 	fSlow210 = max(0.001f, (fConst2 * (fSlow196 * fSlow201)));
		int 	iSlow211 = int((iSlow207 > 0));
		float 	fSlow212 = (1.0f / fSlow210);
		float 	fSlow213 = float(fslider84);
		float 	fSlow214 = (fSlow31 * fSlow213);
		float 	fSlow215 = (fConst1 * ((float(fslider87) * float(fslider86)) + (25.0f * float(fslider85))));
		float 	fSlow216 = max((float)0, (fSlow74 + float(fslider88)));
		float 	fSlow217 = max((float)0, (fSlow77 + float(fslider89)));
		float 	fSlow218 = (6.9100000000000001f * fSlow217);
		int 	iSlow219 = int((fConst0 * fSlow217));
		int 	iSlow220 = (float(fbutton11) > 0.0f);
		int 	iSlow221 = int(iSlow220);
		float 	fSlow222 = (float(iSlow220) * max((float)0, ((0.5f * float(fslider90)) + fSlow83)));
		float 	fSlow223 = (float(fslider92) * float(fslider91));
		float 	fSlow224 = (fConst1 * ((float(fslider95) * float(fslider94)) + (25.0f * float(fslider93))));
		float 	fSlow225 = float(fslider96);
		float 	fSlow226 = float(fbutton12);
		float 	fSlow227 = (fSlow226 * fSlow225);
		float 	fSlow228 = float(fslider97);
		float 	fSlow229 = (fConst2 * fSlow228);
		float 	fSlow230 = float(fslider98);
		float 	fSlow231 = (((1.0f - fSlow225) * fSlow230) + fSlow228);
		float 	fSlow232 = (fConst2 * fSlow231);
		int 	iSlow233 = int(((fSlow226 == 0.0f) > 0));
		float 	fSlow234 = ((fSlow227 + -1.0f) / (0 - (fConst2 * (fSlow228 - fSlow231))));
		float 	fSlow235 = (fConst3 / fSlow228);
		int 	iSlow236 = (fSlow226 > 0.0f);
		float 	fSlow237 = float(iSlow236);
		int 	iSlow238 = int(iSlow236);
		float 	fSlow239 = max(0.001f, (fConst2 * (fSlow225 * fSlow230)));
		int 	iSlow240 = int((iSlow236 > 0));
		float 	fSlow241 = (1.0f / fSlow239);
		float 	fSlow242 = float(fslider99);
		float 	fSlow243 = (fSlow31 * fSlow242);
		float 	fSlow244 = (fConst1 * ((25.0f * float(fslider102)) + (float(fslider101) * float(fslider100))));
		float 	fSlow245 = float(fslider103);
		float 	fSlow246 = float(fbutton13);
		float 	fSlow247 = (fSlow246 * fSlow245);
		float 	fSlow248 = float(fslider104);
		float 	fSlow249 = (fConst2 * fSlow248);
		float 	fSlow250 = float(fslider105);
		float 	fSlow251 = (((1.0f - fSlow245) * fSlow250) + fSlow248);
		float 	fSlow252 = (fConst2 * fSlow251);
		int 	iSlow253 = int(((fSlow246 == 0.0f) > 0));
		float 	fSlow254 = ((fSlow247 + -1.0f) / (0 - (fConst2 * (fSlow248 - fSlow251))));
		float 	fSlow255 = (fConst3 / fSlow248);
		int 	iSlow256 = (fSlow246 > 0.0f);
		float 	fSlow257 = float(iSlow256);
		int 	iSlow258 = int(iSlow256);
		float 	fSlow259 = max(0.001f, (fConst2 * (fSlow245 * fSlow250)));
		int 	iSlow260 = int((iSlow256 > 0));
		float 	fSlow261 = (1.0f / fSlow259);
		float 	fSlow262 = float(fslider106);
		float 	fSlow263 = (fSlow31 * fSlow262);
		float 	fSlow264 = (fConst1 * ((float(fslider109) * float(fslider108)) + (25.0f * float(fslider107))));
		float 	fSlow265 = float(fslider110);
		float 	fSlow266 = float(fbutton14);
		float 	fSlow267 = (fSlow266 * fSlow265);
		float 	fSlow268 = float(fslider111);
		float 	fSlow269 = (fConst2 * fSlow268);
		float 	fSlow270 = float(fslider112);
		float 	fSlow271 = (((1.0f - fSlow265) * fSlow270) + fSlow268);
		float 	fSlow272 = (fConst2 * fSlow271);
		int 	iSlow273 = int(((fSlow266 == 0.0f) > 0));
		float 	fSlow274 = ((fSlow267 + -1.0f) / (0 - (fConst2 * (fSlow268 - fSlow271))));
		float 	fSlow275 = (fConst3 / fSlow268);
		int 	iSlow276 = (fSlow266 > 0.0f);
		float 	fSlow277 = float(iSlow276);
		int 	iSlow278 = int(iSlow276);
		float 	fSlow279 = max(0.001f, (fConst2 * (fSlow265 * fSlow270)));
		int 	iSlow280 = int((iSlow276 > 0));
		float 	fSlow281 = (1.0f / fSlow279);
		float 	fSlow282 = float(fslider113);
		float 	fSlow283 = (fSlow31 * fSlow282);
		float 	fSlow284 = (fConst1 * ((float(fslider116) * float(fslider115)) + (25.0f * float(fslider114))));
		float 	fSlow285 = max((float)0, (fSlow74 + float(fslider117)));
		float 	fSlow286 = max((float)0, (fSlow77 + float(fslider118)));
		float 	fSlow287 = (6.9100000000000001f * fSlow286);
		int 	iSlow288 = int((fConst0 * fSlow286));
		int 	iSlow289 = (float(fbutton15) > 0.0f);
		int 	iSlow290 = int(iSlow289);
		float 	fSlow291 = (float(iSlow289) * max((float)0, ((0.5f * float(fslider119)) + fSlow83)));
		float 	fSlow292 = (float(fslider121) * float(fslider120));
		float 	fSlow293 = (fConst1 * ((float(fslider124) * float(fslider123)) + (25.0f * float(fslider122))));
		float 	fSlow294 = float(fslider125);
		float 	fSlow295 = float(fbutton16);
		float 	fSlow296 = (fSlow295 * fSlow294);
		float 	fSlow297 = float(fslider126);
		float 	fSlow298 = (fConst2 * fSlow297);
		float 	fSlow299 = float(fslider127);
		float 	fSlow300 = (((1.0f - fSlow294) * fSlow299) + fSlow297);
		float 	fSlow301 = (fConst2 * fSlow300);
		int 	iSlow302 = int(((fSlow295 == 0.0f) > 0));
		float 	fSlow303 = ((fSlow296 + -1.0f) / (0 - (fConst2 * (fSlow297 - fSlow300))));
		float 	fSlow304 = (fConst3 / fSlow297);
		int 	iSlow305 = (fSlow295 > 0.0f);
		float 	fSlow306 = float(iSlow305);
		int 	iSlow307 = int(iSlow305);
		float 	fSlow308 = max(0.001f, (fConst2 * (fSlow294 * fSlow299)));
		int 	iSlow309 = int((iSlow305 > 0));
		float 	fSlow310 = (1.0f / fSlow308);
		float 	fSlow311 = float(fslider128);
		float 	fSlow312 = (fSlow31 * fSlow311);
		float 	fSlow313 = (fConst1 * ((float(fslider131) * float(fslider130)) + (25.0f * float(fslider129))));
		float 	fSlow314 = float(fslider132);
		float 	fSlow315 = float(fbutton17);
		float 	fSlow316 = (fSlow315 * fSlow314);
		float 	fSlow317 = float(fslider133);
		float 	fSlow318 = (fConst2 * fSlow317);
		float 	fSlow319 = float(fslider134);
		float 	fSlow320 = (((1.0f - fSlow314) * fSlow319) + fSlow317);
		float 	fSlow321 = (fConst2 * fSlow320);
		int 	iSlow322 = int(((fSlow315 == 0.0f) > 0));
		float 	fSlow323 = ((fSlow316 + -1.0f) / (0 - (fConst2 * (fSlow317 - fSlow320))));
		float 	fSlow324 = (fConst3 / fSlow317);
		int 	iSlow325 = (fSlow315 > 0.0f);
		float 	fSlow326 = float(iSlow325);
		int 	iSlow327 = int(iSlow325);
		float 	fSlow328 = max(0.001f, (fConst2 * (fSlow314 * fSlow319)));
		int 	iSlow329 = int((iSlow325 > 0));
		float 	fSlow330 = (1.0f / fSlow328);
		float 	fSlow331 = float(fslider135);
		float 	fSlow332 = (fSlow31 * fSlow331);
		float 	fSlow333 = (fConst1 * ((float(fslider138) * float(fslider137)) + (25.0f * float(fslider136))));
		float 	fSlow334 = float(fslider139);
		float 	fSlow335 = float(fbutton18);
		float 	fSlow336 = (fSlow335 * fSlow334);
		float 	fSlow337 = float(fslider140);
		float 	fSlow338 = (fConst2 * fSlow337);
		float 	fSlow339 = float(fslider141);
		float 	fSlow340 = (((1.0f - fSlow334) * fSlow339) + fSlow337);
		float 	fSlow341 = (fConst2 * fSlow340);
		int 	iSlow342 = int(((fSlow335 == 0.0f) > 0));
		float 	fSlow343 = ((fSlow336 + -1.0f) / (0 - (fConst2 * (fSlow337 - fSlow340))));
		float 	fSlow344 = (fConst3 / fSlow337);
		int 	iSlow345 = (fSlow335 > 0.0f);
		float 	fSlow346 = float(iSlow345);
		int 	iSlow347 = int(iSlow345);
		float 	fSlow348 = max(0.001f, (fConst2 * (fSlow334 * fSlow339)));
		int 	iSlow349 = int((iSlow345 > 0));
		float 	fSlow350 = (1.0f / fSlow348);
		float 	fSlow351 = float(fslider142);
		float 	fSlow352 = (fSlow31 * fSlow351);
		float 	fSlow353 = (fConst1 * ((float(fslider145) * float(fslider144)) + (25.0f * float(fslider143))));
		float 	fSlow354 = max((float)0, (fSlow74 + float(fslider146)));
		float 	fSlow355 = max((float)0, (fSlow77 + float(fslider147)));
		float 	fSlow356 = (6.9100000000000001f * fSlow355);
		int 	iSlow357 = int((fConst0 * fSlow355));
		int 	iSlow358 = (float(fbutton19) > 0.0f);
		int 	iSlow359 = int(iSlow358);
		float 	fSlow360 = (float(iSlow358) * max((float)0, ((0.5f * float(fslider148)) + fSlow83)));
		float 	fSlow361 = (float(fslider150) * float(fslider149));
		float 	fSlow362 = (fConst1 * ((float(fslider153) * float(fslider152)) + (25.0f * float(fslider151))));
		float 	fSlow363 = max((float)0, (fSlow74 + float(fslider154)));
		float 	fSlow364 = max((float)0, (fSlow77 + float(fslider155)));
		float 	fSlow365 = (6.9100000000000001f * fSlow364);
		int 	iSlow366 = int((fConst0 * fSlow364));
		float 	fSlow367 = float(fbutton20);
		int 	iSlow368 = (fSlow367 > 0.0f);
		int 	iSlow369 = int(iSlow368);
		float 	fSlow370 = float(iSlow368);
		float 	fSlow371 = (fSlow370 * max((float)0, ((0.5f * float(fslider156)) + fSlow83)));
		float 	fSlow372 = float(fslider157);
		float 	fSlow373 = (float(fslider158) * fSlow372);
		float 	fSlow374 = (fConst1 * ((float(fslider161) * float(fslider160)) + (25.0f * float(fslider159))));
		float 	fSlow375 = max((float)0, (fSlow74 + float(fslider162)));
		float 	fSlow376 = max((float)0, (fSlow77 + float(fslider163)));
		float 	fSlow377 = (6.9100000000000001f * fSlow376);
		int 	iSlow378 = int((fConst0 * fSlow376));
		float 	fSlow379 = float(fbutton21);
		int 	iSlow380 = (fSlow379 > 0.0f);
		int 	iSlow381 = int(iSlow380);
		float 	fSlow382 = float(iSlow380);
		float 	fSlow383 = (fSlow382 * max((float)0, ((0.5f * float(fslider164)) + fSlow83)));
		float 	fSlow384 = float(fslider165);
		float 	fSlow385 = (float(fslider166) * fSlow384);
		float 	fSlow386 = (fConst1 * ((float(fslider169) * float(fslider168)) + (25.0f * float(fslider167))));
		float 	fSlow387 = max((float)0, (fSlow74 + float(fslider170)));
		float 	fSlow388 = max((float)0, (fSlow77 + float(fslider171)));
		float 	fSlow389 = (6.9100000000000001f * fSlow388);
		int 	iSlow390 = int((fConst0 * fSlow388));
		float 	fSlow391 = float(fbutton22);
		int 	iSlow392 = (fSlow391 > 0.0f);
		int 	iSlow393 = int(iSlow392);
		float 	fSlow394 = float(iSlow392);
		float 	fSlow395 = (fSlow394 * max((float)0, ((0.5f * float(fslider172)) + fSlow83)));
		float 	fSlow396 = float(fslider173);
		float 	fSlow397 = (float(fslider174) * fSlow396);
		float 	fSlow398 = (fConst1 * ((float(fslider177) * float(fslider176)) + (25.0f * float(fslider175))));
		float 	fSlow399 = max((float)0, (fSlow74 + float(fslider178)));
		float 	fSlow400 = max((float)0, (fSlow77 + float(fslider179)));
		float 	fSlow401 = (6.9100000000000001f * fSlow400);
		int 	iSlow402 = int((fConst0 * fSlow400));
		int 	iSlow403 = (float(fbutton23) > 0.0f);
		int 	iSlow404 = int(iSlow403);
		float 	fSlow405 = (float(iSlow403) * max((float)0, ((0.5f * float(fslider180)) + fSlow83)));
		float 	fSlow406 = (float(fslider182) * float(fslider181));
		float 	fSlow407 = float(fslider183);
		float 	fSlow408 = (fSlow367 * fSlow407);
		float 	fSlow409 = float(fslider184);
		float 	fSlow410 = (fConst2 * fSlow409);
		float 	fSlow411 = float(fslider185);
		float 	fSlow412 = (((1.0f - fSlow407) * fSlow411) + fSlow409);
		float 	fSlow413 = (fConst2 * fSlow412);
		int 	iSlow414 = int(((fSlow367 == 0.0f) > 0));
		float 	fSlow415 = ((fSlow408 + -1.0f) / (0 - (fConst2 * (fSlow409 - fSlow412))));
		float 	fSlow416 = (fConst3 / fSlow409);
		float 	fSlow417 = max(0.001f, (fConst2 * (fSlow407 * fSlow411)));
		int 	iSlow418 = int((iSlow368 > 0));
		float 	fSlow419 = (1.0f / fSlow417);
		float 	fSlow420 = (fSlow31 * fSlow372);
		float 	fSlow421 = float(fslider186);
		float 	fSlow422 = (fSlow391 * fSlow421);
		float 	fSlow423 = float(fslider187);
		float 	fSlow424 = (fConst2 * fSlow423);
		float 	fSlow425 = float(fslider188);
		float 	fSlow426 = (((1.0f - fSlow421) * fSlow425) + fSlow423);
		float 	fSlow427 = (fConst2 * fSlow426);
		int 	iSlow428 = int(((fSlow391 == 0.0f) > 0));
		float 	fSlow429 = ((fSlow422 + -1.0f) / (0 - (fConst2 * (fSlow423 - fSlow426))));
		float 	fSlow430 = (fConst3 / fSlow423);
		float 	fSlow431 = max(0.001f, (fConst2 * (fSlow421 * fSlow425)));
		int 	iSlow432 = int((iSlow392 > 0));
		float 	fSlow433 = (1.0f / fSlow431);
		float 	fSlow434 = (fSlow31 * fSlow396);
		float 	fSlow435 = float(fslider189);
		float 	fSlow436 = (fSlow379 * fSlow435);
		float 	fSlow437 = float(fslider190);
		float 	fSlow438 = (fConst2 * fSlow437);
		float 	fSlow439 = float(fslider191);
		float 	fSlow440 = (((1.0f - fSlow435) * fSlow439) + fSlow437);
		float 	fSlow441 = (fConst2 * fSlow440);
		int 	iSlow442 = int(((fSlow379 == 0.0f) > 0));
		float 	fSlow443 = ((fSlow436 + -1.0f) / (0 - (fConst2 * (fSlow437 - fSlow440))));
		float 	fSlow444 = (fConst3 / fSlow437);
		float 	fSlow445 = max(0.001f, (fConst2 * (fSlow435 * fSlow439)));
		int 	iSlow446 = int((iSlow380 > 0));
		float 	fSlow447 = (1.0f / fSlow445);
		float 	fSlow448 = (fSlow31 * fSlow384);
		float 	fSlow449 = max((float)0, (fSlow74 + float(fslider192)));
		float 	fSlow450 = max((float)0, (fSlow77 + float(fslider193)));
		float 	fSlow451 = (6.9100000000000001f * fSlow450);
		int 	iSlow452 = int((fConst0 * fSlow450));
		float 	fSlow453 = (fSlow346 * max((float)0, ((0.5f * float(fslider194)) + fSlow83)));
		float 	fSlow454 = (float(fslider195) * fSlow351);
		float 	fSlow455 = max((float)0, (fSlow74 + float(fslider196)));
		float 	fSlow456 = max((float)0, (fSlow77 + float(fslider197)));
		float 	fSlow457 = (6.9100000000000001f * fSlow456);
		int 	iSlow458 = int((fConst0 * fSlow456));
		float 	fSlow459 = (fSlow326 * max((float)0, ((0.5f * float(fslider198)) + fSlow83)));
		float 	fSlow460 = (float(fslider199) * fSlow331);
		float 	fSlow461 = max((float)0, (fSlow74 + float(fslider200)));
		float 	fSlow462 = max((float)0, (fSlow77 + float(fslider201)));
		float 	fSlow463 = (6.9100000000000001f * fSlow462);
		int 	iSlow464 = int((fConst0 * fSlow462));
		float 	fSlow465 = (fSlow306 * max((float)0, ((0.5f * float(fslider202)) + fSlow83)));
		float 	fSlow466 = (float(fslider203) * fSlow311);
		float 	fSlow467 = max((float)0, (fSlow74 + float(fslider204)));
		float 	fSlow468 = max((float)0, (fSlow77 + float(fslider205)));
		float 	fSlow469 = (6.9100000000000001f * fSlow468);
		int 	iSlow470 = int((fConst0 * fSlow468));
		float 	fSlow471 = (fSlow277 * max((float)0, ((0.5f * float(fslider206)) + fSlow83)));
		float 	fSlow472 = (float(fslider207) * fSlow282);
		float 	fSlow473 = max((float)0, (fSlow74 + float(fslider208)));
		float 	fSlow474 = max((float)0, (fSlow77 + float(fslider209)));
		float 	fSlow475 = (6.9100000000000001f * fSlow474);
		int 	iSlow476 = int((fConst0 * fSlow474));
		float 	fSlow477 = (fSlow257 * max((float)0, ((0.5f * float(fslider210)) + fSlow83)));
		float 	fSlow478 = (float(fslider211) * fSlow262);
		float 	fSlow479 = max((float)0, (fSlow74 + float(fslider212)));
		float 	fSlow480 = max((float)0, (fSlow77 + float(fslider213)));
		float 	fSlow481 = (6.9100000000000001f * fSlow480);
		int 	iSlow482 = int((fConst0 * fSlow480));
		float 	fSlow483 = (fSlow237 * max((float)0, ((0.5f * float(fslider214)) + fSlow83)));
		float 	fSlow484 = (float(fslider215) * fSlow242);
		float 	fSlow485 = max((float)0, (fSlow74 + float(fslider216)));
		float 	fSlow486 = max((float)0, (fSlow77 + float(fslider217)));
		float 	fSlow487 = (6.9100000000000001f * fSlow486);
		int 	iSlow488 = int((fConst0 * fSlow486));
		float 	fSlow489 = (fSlow208 * max((float)0, ((0.5f * float(fslider218)) + fSlow83)));
		float 	fSlow490 = (float(fslider219) * fSlow213);
		float 	fSlow491 = max((float)0, (fSlow74 + float(fslider220)));
		float 	fSlow492 = max((float)0, (fSlow77 + float(fslider221)));
		float 	fSlow493 = (6.9100000000000001f * fSlow492);
		int 	iSlow494 = int((fConst0 * fSlow492));
		float 	fSlow495 = (fSlow188 * max((float)0, ((0.5f * float(fslider222)) + fSlow83)));
		float 	fSlow496 = (float(fslider223) * fSlow193);
		float 	fSlow497 = max((float)0, (fSlow74 + float(fslider224)));
		float 	fSlow498 = max((float)0, (fSlow77 + float(fslider225)));
		float 	fSlow499 = (6.9100000000000001f * fSlow498);
		int 	iSlow500 = int((fConst0 * fSlow498));
		float 	fSlow501 = (fSlow168 * max((float)0, ((0.5f * float(fslider226)) + fSlow83)));
		float 	fSlow502 = (float(fslider227) * fSlow173);
		float 	fSlow503 = max((float)0, (fSlow74 + float(fslider228)));
		float 	fSlow504 = max((float)0, (fSlow77 + float(fslider229)));
		float 	fSlow505 = (6.9100000000000001f * fSlow504);
		int 	iSlow506 = int((fConst0 * fSlow504));
		float 	fSlow507 = (fSlow139 * max((float)0, ((0.5f * float(fslider230)) + fSlow83)));
		float 	fSlow508 = (float(fslider231) * fSlow144);
		float 	fSlow509 = max((float)0, (fSlow74 + float(fslider232)));
		float 	fSlow510 = max((float)0, (fSlow77 + float(fslider233)));
		float 	fSlow511 = (6.9100000000000001f * fSlow510);
		int 	iSlow512 = int((fConst0 * fSlow510));
		float 	fSlow513 = (fSlow119 * max((float)0, ((0.5f * float(fslider234)) + fSlow83)));
		float 	fSlow514 = (float(fslider235) * fSlow124);
		float 	fSlow515 = max((float)0, (fSlow74 + float(fslider236)));
		float 	fSlow516 = max((float)0, (fSlow77 + float(fslider237)));
		float 	fSlow517 = (6.9100000000000001f * fSlow516);
		int 	iSlow518 = int((fConst0 * fSlow516));
		float 	fSlow519 = (fSlow99 * max((float)0, ((0.5f * float(fslider238)) + fSlow83)));
		float 	fSlow520 = (float(fslider239) * fSlow104);
		float 	fSlow521 = max((float)0, (fSlow74 + float(fslider240)));
		float 	fSlow522 = max((float)0, (fSlow77 + float(fslider241)));
		float 	fSlow523 = (6.9100000000000001f * fSlow522);
		int 	iSlow524 = int((fConst0 * fSlow522));
		float 	fSlow525 = (fSlow66 * max((float)0, ((0.5f * float(fslider242)) + fSlow83)));
		float 	fSlow526 = (float(fslider243) * fSlow71);
		float 	fSlow527 = max((float)0, (fSlow74 + float(fslider244)));
		float 	fSlow528 = max((float)0, (fSlow77 + float(fslider245)));
		float 	fSlow529 = (6.9100000000000001f * fSlow528);
		int 	iSlow530 = int((fConst0 * fSlow528));
		float 	fSlow531 = (fSlow46 * max((float)0, ((0.5f * float(fslider246)) + fSlow83)));
		float 	fSlow532 = (float(fslider247) * fSlow51);
		float 	fSlow533 = max((float)0, (fSlow74 + float(fslider248)));
		float 	fSlow534 = max((float)0, (fSlow77 + float(fslider249)));
		float 	fSlow535 = (6.9100000000000001f * fSlow534);
		int 	iSlow536 = int((fConst0 * fSlow534));
		float 	fSlow537 = (fSlow25 * max((float)0, ((0.5f * float(fslider250)) + fSlow83)));
		float 	fSlow538 = (float(fslider251) * fSlow30);
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
				fTempPerm3 = (((int((fRec4[0] < 0.0f)))?fRec2[0]:((int((fRec4[0] < fSlow27)))?(fRec2[0] + (fSlow29 * (0 - (fRec4[0] * fRec2[0])))):0.0f)) * fTempPerm1);
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm4 = (fSlow32 * fTempPerm3);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec5[0] = (fSlow33 + (fRec5[1] - floorf((fSlow33 + fRec5[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm5 = ftbl0[(((int((65536.0f * (fRec5[0] + fTempPerm4))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec7[0] = ((iSlow42)?0.0f:min(fSlow41, (fRec7[1] + 1.0f)));
				iTempPerm6 = int((fRec7[0] < fSlow38));
				fRec6[0] = ((iSlow47)?(fSlow46 * ((iTempPerm6)?((int((fRec7[0] < 0.0f)))?0.0f:((iTempPerm6)?(fSlow44 * fRec7[0]):1.0f)):((int((fRec7[0] < fSlow41)))?((fSlow43 * (fRec7[0] - fSlow38)) + 1.0f):fSlow36))):fRec6[1]);
				fRec8[0] = ((iSlow49)?0.0f:min(fSlow48, (fRec8[1] + 1.0f)));
				fTempPerm7 = ((int((fRec8[0] < 0.0f)))?fRec6[0]:((int((fRec8[0] < fSlow48)))?(fRec6[0] + (fSlow50 * (0 - (fRec8[0] * fRec6[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm8 = (fTempPerm7 * fTempPerm5);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm9 = (fSlow52 * fTempPerm8);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec9[0] = (fSlow53 + (fRec9[1] - floorf((fSlow53 + fRec9[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm10 = ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm9))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec11[0] = ((iSlow62)?0.0f:min(fSlow61, (fRec11[1] + 1.0f)));
				iTempPerm11 = int((fRec11[0] < fSlow58));
				fRec10[0] = ((iSlow67)?(fSlow66 * ((iTempPerm11)?((int((fRec11[0] < 0.0f)))?0.0f:((iTempPerm11)?(fSlow64 * fRec11[0]):1.0f)):((int((fRec11[0] < fSlow61)))?((fSlow63 * (fRec11[0] - fSlow58)) + 1.0f):fSlow56))):fRec10[1]);
				fRec12[0] = ((iSlow69)?0.0f:min(fSlow68, (fRec12[1] + 1.0f)));
				fTempPerm12 = ((int((fRec12[0] < 0.0f)))?fRec10[0]:((int((fRec12[0] < fSlow68)))?(fRec10[0] + (fSlow70 * (0 - (fRec12[0] * fRec10[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec13[0] = (fSlow73 + (fRec13[1] - floorf((fSlow73 + fRec13[1]))));
				iRec15[0] = (iSlow81 * (iRec15[1] + 1));
				iTempPerm13 = int((iRec15[0] < iSlow80));
				fTempPerm14 = expf((0 - (fConst4 / ((iSlow82)?((iTempPerm13)?fSlow79:fSlow76):fSlow75))));
				fRec14[0] = ((fRec14[1] * fTempPerm14) + (((iSlow82)?((iTempPerm13)?1.5873015873015872f:fSlow84):0.0f) * (1.0f - fTempPerm14)));
				fTempPerm15 = min(1.0f, fRec14[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm16 = (fSlow85 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow72 * (fTempPerm12 * fTempPerm10))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec16[0] = (fSlow86 + (fRec16[1] - floorf((fSlow86 + fRec16[1]))));
				fTempPerm17 = ftbl0[(((int((65536.0f * fRec16[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec18[0] = ((iSlow95)?0.0f:min(fSlow94, (fRec18[1] + 1.0f)));
				iTempPerm18 = int((fRec18[0] < fSlow91));
				fRec17[0] = ((iSlow100)?(fSlow99 * ((iTempPerm18)?((int((fRec18[0] < 0.0f)))?0.0f:((iTempPerm18)?(fSlow97 * fRec18[0]):1.0f)):((int((fRec18[0] < fSlow94)))?((fSlow96 * (fRec18[0] - fSlow91)) + 1.0f):fSlow89))):fRec17[1]);
				fRec19[0] = ((iSlow102)?0.0f:min(fSlow101, (fRec19[1] + 1.0f)));
				fTempPerm19 = (((int((fRec19[0] < 0.0f)))?fRec17[0]:((int((fRec19[0] < fSlow101)))?(fRec17[0] + (fSlow103 * (0 - (fRec19[0] * fRec17[0])))):0.0f)) * fTempPerm17);
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm20 = (fSlow105 * fTempPerm19);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec20[0] = (fSlow106 + (fRec20[1] - floorf((fSlow106 + fRec20[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm21 = ftbl0[(((int((65536.0f * (fRec20[0] + fTempPerm20))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec22[0] = ((iSlow115)?0.0f:min(fSlow114, (fRec22[1] + 1.0f)));
				iTempPerm22 = int((fRec22[0] < fSlow111));
				fRec21[0] = ((iSlow120)?(fSlow119 * ((iTempPerm22)?((int((fRec22[0] < 0.0f)))?0.0f:((iTempPerm22)?(fSlow117 * fRec22[0]):1.0f)):((int((fRec22[0] < fSlow114)))?((fSlow116 * (fRec22[0] - fSlow111)) + 1.0f):fSlow109))):fRec21[1]);
				fRec23[0] = ((iSlow122)?0.0f:min(fSlow121, (fRec23[1] + 1.0f)));
				fTempPerm23 = ((int((fRec23[0] < 0.0f)))?fRec21[0]:((int((fRec23[0] < fSlow121)))?(fRec21[0] + (fSlow123 * (0 - (fRec23[0] * fRec21[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm24 = (fTempPerm23 * fTempPerm21);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm25 = (fSlow125 * fTempPerm24);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec24[0] = (fSlow126 + (fRec24[1] - floorf((fSlow126 + fRec24[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm26 = ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm25))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec26[0] = ((iSlow135)?0.0f:min(fSlow134, (fRec26[1] + 1.0f)));
				iTempPerm27 = int((fRec26[0] < fSlow131));
				fRec25[0] = ((iSlow140)?(fSlow139 * ((iTempPerm27)?((int((fRec26[0] < 0.0f)))?0.0f:((iTempPerm27)?(fSlow137 * fRec26[0]):1.0f)):((int((fRec26[0] < fSlow134)))?((fSlow136 * (fRec26[0] - fSlow131)) + 1.0f):fSlow129))):fRec25[1]);
				fRec27[0] = ((iSlow142)?0.0f:min(fSlow141, (fRec27[1] + 1.0f)));
				fTempPerm28 = ((int((fRec27[0] < 0.0f)))?fRec25[0]:((int((fRec27[0] < fSlow141)))?(fRec25[0] + (fSlow143 * (0 - (fRec27[0] * fRec25[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec28[0] = (fSlow146 + (fRec28[1] - floorf((fSlow146 + fRec28[1]))));
				iRec30[0] = (iSlow151 * (iRec30[1] + 1));
				iTempPerm29 = int((iRec30[0] < iSlow150));
				fTempPerm30 = expf((0 - (fConst4 / ((iSlow152)?((iTempPerm29)?fSlow149:fSlow76):fSlow147))));
				fRec29[0] = ((fRec29[1] * fTempPerm30) + (((iSlow152)?((iTempPerm29)?1.5873015873015872f:fSlow153):0.0f) * (1.0f - fTempPerm30)));
				fTempPerm31 = min(1.0f, fRec29[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm32 = (fSlow154 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow145 * (fTempPerm28 * fTempPerm26))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec31[0] = (fSlow155 + (fRec31[1] - floorf((fSlow155 + fRec31[1]))));
				fTempPerm33 = ftbl0[(((int((65536.0f * fRec31[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec33[0] = ((iSlow164)?0.0f:min(fSlow163, (fRec33[1] + 1.0f)));
				iTempPerm34 = int((fRec33[0] < fSlow160));
				fRec32[0] = ((iSlow169)?(fSlow168 * ((iTempPerm34)?((int((fRec33[0] < 0.0f)))?0.0f:((iTempPerm34)?(fSlow166 * fRec33[0]):1.0f)):((int((fRec33[0] < fSlow163)))?((fSlow165 * (fRec33[0] - fSlow160)) + 1.0f):fSlow158))):fRec32[1]);
				fRec34[0] = ((iSlow171)?0.0f:min(fSlow170, (fRec34[1] + 1.0f)));
				fTempPerm35 = (((int((fRec34[0] < 0.0f)))?fRec32[0]:((int((fRec34[0] < fSlow170)))?(fRec32[0] + (fSlow172 * (0 - (fRec34[0] * fRec32[0])))):0.0f)) * fTempPerm33);
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm36 = (fSlow174 * fTempPerm35);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec35[0] = (fSlow175 + (fRec35[1] - floorf((fSlow175 + fRec35[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm37 = ftbl0[(((int((65536.0f * (fRec35[0] + fTempPerm36))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec37[0] = ((iSlow184)?0.0f:min(fSlow183, (fRec37[1] + 1.0f)));
				iTempPerm38 = int((fRec37[0] < fSlow180));
				fRec36[0] = ((iSlow189)?(fSlow188 * ((iTempPerm38)?((int((fRec37[0] < 0.0f)))?0.0f:((iTempPerm38)?(fSlow186 * fRec37[0]):1.0f)):((int((fRec37[0] < fSlow183)))?((fSlow185 * (fRec37[0] - fSlow180)) + 1.0f):fSlow178))):fRec36[1]);
				fRec38[0] = ((iSlow191)?0.0f:min(fSlow190, (fRec38[1] + 1.0f)));
				fTempPerm39 = ((int((fRec38[0] < 0.0f)))?fRec36[0]:((int((fRec38[0] < fSlow190)))?(fRec36[0] + (fSlow192 * (0 - (fRec38[0] * fRec36[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm40 = (fTempPerm39 * fTempPerm37);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm41 = (fSlow194 * fTempPerm40);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec39[0] = (fSlow195 + (fRec39[1] - floorf((fSlow195 + fRec39[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm42 = ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm41))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec41[0] = ((iSlow204)?0.0f:min(fSlow203, (fRec41[1] + 1.0f)));
				iTempPerm43 = int((fRec41[0] < fSlow200));
				fRec40[0] = ((iSlow209)?(fSlow208 * ((iTempPerm43)?((int((fRec41[0] < 0.0f)))?0.0f:((iTempPerm43)?(fSlow206 * fRec41[0]):1.0f)):((int((fRec41[0] < fSlow203)))?((fSlow205 * (fRec41[0] - fSlow200)) + 1.0f):fSlow198))):fRec40[1]);
				fRec42[0] = ((iSlow211)?0.0f:min(fSlow210, (fRec42[1] + 1.0f)));
				fTempPerm44 = ((int((fRec42[0] < 0.0f)))?fRec40[0]:((int((fRec42[0] < fSlow210)))?(fRec40[0] + (fSlow212 * (0 - (fRec42[0] * fRec40[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec43[0] = (fSlow215 + (fRec43[1] - floorf((fSlow215 + fRec43[1]))));
				iRec45[0] = (iSlow220 * (iRec45[1] + 1));
				iTempPerm45 = int((iRec45[0] < iSlow219));
				fTempPerm46 = expf((0 - (fConst4 / ((iSlow221)?((iTempPerm45)?fSlow218:fSlow76):fSlow216))));
				fRec44[0] = ((fRec44[1] * fTempPerm46) + (((iSlow221)?((iTempPerm45)?1.5873015873015872f:fSlow222):0.0f) * (1.0f - fTempPerm46)));
				fTempPerm47 = min(1.0f, fRec44[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm48 = (fSlow223 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow214 * (fTempPerm44 * fTempPerm42))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec46[0] = (fSlow224 + (fRec46[1] - floorf((fSlow224 + fRec46[1]))));
				fTempPerm49 = ftbl0[(((int((65536.0f * fRec46[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec48[0] = ((iSlow233)?0.0f:min(fSlow232, (fRec48[1] + 1.0f)));
				iTempPerm50 = int((fRec48[0] < fSlow229));
				fRec47[0] = ((iSlow238)?(fSlow237 * ((iTempPerm50)?((int((fRec48[0] < 0.0f)))?0.0f:((iTempPerm50)?(fSlow235 * fRec48[0]):1.0f)):((int((fRec48[0] < fSlow232)))?((fSlow234 * (fRec48[0] - fSlow229)) + 1.0f):fSlow227))):fRec47[1]);
				fRec49[0] = ((iSlow240)?0.0f:min(fSlow239, (fRec49[1] + 1.0f)));
				fTempPerm51 = (((int((fRec49[0] < 0.0f)))?fRec47[0]:((int((fRec49[0] < fSlow239)))?(fRec47[0] + (fSlow241 * (0 - (fRec49[0] * fRec47[0])))):0.0f)) * fTempPerm49);
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm52 = (fSlow243 * fTempPerm51);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec50[0] = (fSlow244 + (fRec50[1] - floorf((fSlow244 + fRec50[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm53 = ftbl0[(((int((65536.0f * (fRec50[0] + fTempPerm52))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec52[0] = ((iSlow253)?0.0f:min(fSlow252, (fRec52[1] + 1.0f)));
				iTempPerm54 = int((fRec52[0] < fSlow249));
				fRec51[0] = ((iSlow258)?(fSlow257 * ((iTempPerm54)?((int((fRec52[0] < 0.0f)))?0.0f:((iTempPerm54)?(fSlow255 * fRec52[0]):1.0f)):((int((fRec52[0] < fSlow252)))?((fSlow254 * (fRec52[0] - fSlow249)) + 1.0f):fSlow247))):fRec51[1]);
				fRec53[0] = ((iSlow260)?0.0f:min(fSlow259, (fRec53[1] + 1.0f)));
				fTempPerm55 = ((int((fRec53[0] < 0.0f)))?fRec51[0]:((int((fRec53[0] < fSlow259)))?(fRec51[0] + (fSlow261 * (0 - (fRec53[0] * fRec51[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm56 = (fTempPerm55 * fTempPerm53);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm57 = (fSlow263 * fTempPerm56);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec54[0] = (fSlow264 + (fRec54[1] - floorf((fSlow264 + fRec54[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm58 = ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm57))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec56[0] = ((iSlow273)?0.0f:min(fSlow272, (fRec56[1] + 1.0f)));
				iTempPerm59 = int((fRec56[0] < fSlow269));
				fRec55[0] = ((iSlow278)?(fSlow277 * ((iTempPerm59)?((int((fRec56[0] < 0.0f)))?0.0f:((iTempPerm59)?(fSlow275 * fRec56[0]):1.0f)):((int((fRec56[0] < fSlow272)))?((fSlow274 * (fRec56[0] - fSlow269)) + 1.0f):fSlow267))):fRec55[1]);
				fRec57[0] = ((iSlow280)?0.0f:min(fSlow279, (fRec57[1] + 1.0f)));
				fTempPerm60 = ((int((fRec57[0] < 0.0f)))?fRec55[0]:((int((fRec57[0] < fSlow279)))?(fRec55[0] + (fSlow281 * (0 - (fRec57[0] * fRec55[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec58[0] = (fSlow284 + (fRec58[1] - floorf((fSlow284 + fRec58[1]))));
				iRec60[0] = (iSlow289 * (iRec60[1] + 1));
				iTempPerm61 = int((iRec60[0] < iSlow288));
				fTempPerm62 = expf((0 - (fConst4 / ((iSlow290)?((iTempPerm61)?fSlow287:fSlow76):fSlow285))));
				fRec59[0] = ((fRec59[1] * fTempPerm62) + (((iSlow290)?((iTempPerm61)?1.5873015873015872f:fSlow291):0.0f) * (1.0f - fTempPerm62)));
				fTempPerm63 = min(1.0f, fRec59[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm64 = (fSlow292 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow283 * (fTempPerm60 * fTempPerm58))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec61[0] = (fSlow293 + (fRec61[1] - floorf((fSlow293 + fRec61[1]))));
				fTempPerm65 = ftbl0[(((int((65536.0f * fRec61[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec63[0] = ((iSlow302)?0.0f:min(fSlow301, (fRec63[1] + 1.0f)));
				iTempPerm66 = int((fRec63[0] < fSlow298));
				fRec62[0] = ((iSlow307)?(fSlow306 * ((iTempPerm66)?((int((fRec63[0] < 0.0f)))?0.0f:((iTempPerm66)?(fSlow304 * fRec63[0]):1.0f)):((int((fRec63[0] < fSlow301)))?((fSlow303 * (fRec63[0] - fSlow298)) + 1.0f):fSlow296))):fRec62[1]);
				fRec64[0] = ((iSlow309)?0.0f:min(fSlow308, (fRec64[1] + 1.0f)));
				fTempPerm67 = (((int((fRec64[0] < 0.0f)))?fRec62[0]:((int((fRec64[0] < fSlow308)))?(fRec62[0] + (fSlow310 * (0 - (fRec64[0] * fRec62[0])))):0.0f)) * fTempPerm65);
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm68 = (fSlow312 * fTempPerm67);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec65[0] = (fSlow313 + (fRec65[1] - floorf((fSlow313 + fRec65[1]))));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm69 = ftbl0[(((int((65536.0f * (fRec65[0] + fTempPerm68))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec67[0] = ((iSlow322)?0.0f:min(fSlow321, (fRec67[1] + 1.0f)));
				iTempPerm70 = int((fRec67[0] < fSlow318));
				fRec66[0] = ((iSlow327)?(fSlow326 * ((iTempPerm70)?((int((fRec67[0] < 0.0f)))?0.0f:((iTempPerm70)?(fSlow324 * fRec67[0]):1.0f)):((int((fRec67[0] < fSlow321)))?((fSlow323 * (fRec67[0] - fSlow318)) + 1.0f):fSlow316))):fRec66[1]);
				fRec68[0] = ((iSlow329)?0.0f:min(fSlow328, (fRec68[1] + 1.0f)));
				fTempPerm71 = ((int((fRec68[0] < 0.0f)))?fRec66[0]:((int((fRec68[0] < fSlow328)))?(fRec66[0] + (fSlow330 * (0 - (fRec68[0] * fRec66[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm72 = (fTempPerm71 * fTempPerm69);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm73 = (fSlow332 * fTempPerm72);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec69[0] = (fSlow333 + (fRec69[1] - floorf((fSlow333 + fRec69[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm74 = ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm73))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec71[0] = ((iSlow342)?0.0f:min(fSlow341, (fRec71[1] + 1.0f)));
				iTempPerm75 = int((fRec71[0] < fSlow338));
				fRec70[0] = ((iSlow347)?(fSlow346 * ((iTempPerm75)?((int((fRec71[0] < 0.0f)))?0.0f:((iTempPerm75)?(fSlow344 * fRec71[0]):1.0f)):((int((fRec71[0] < fSlow341)))?((fSlow343 * (fRec71[0] - fSlow338)) + 1.0f):fSlow336))):fRec70[1]);
				fRec72[0] = ((iSlow349)?0.0f:min(fSlow348, (fRec72[1] + 1.0f)));
				fTempPerm76 = ((int((fRec72[0] < 0.0f)))?fRec70[0]:((int((fRec72[0] < fSlow348)))?(fRec70[0] + (fSlow350 * (0 - (fRec72[0] * fRec70[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec73[0] = (fSlow353 + (fRec73[1] - floorf((fSlow353 + fRec73[1]))));
				iRec75[0] = (iSlow358 * (iRec75[1] + 1));
				iTempPerm77 = int((iRec75[0] < iSlow357));
				fTempPerm78 = expf((0 - (fConst4 / ((iSlow359)?((iTempPerm77)?fSlow356:fSlow76):fSlow354))));
				fRec74[0] = ((fRec74[1] * fTempPerm78) + (((iSlow359)?((iTempPerm77)?1.5873015873015872f:fSlow360):0.0f) * (1.0f - fTempPerm78)));
				fTempPerm79 = min(1.0f, fRec74[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm80 = (fSlow361 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow352 * (fTempPerm76 * fTempPerm74))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec76[0] = (fSlow362 + (fRec76[1] - floorf((fSlow362 + fRec76[1]))));
				fTempPerm81 = ftbl0[(((int((65536.0f * fRec76[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11) {
				iRec78[0] = (iSlow368 * (iRec78[1] + 1));
				iTempPerm82 = int((iRec78[0] < iSlow366));
				fTempPerm83 = expf((0 - (fConst4 / ((iSlow369)?((iTempPerm82)?fSlow365:fSlow76):fSlow363))));
				fRec77[0] = ((fRec77[1] * fTempPerm83) + (((iSlow369)?((iTempPerm82)?1.5873015873015872f:fSlow371):0.0f) * (1.0f - fTempPerm83)));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec79[0] = (fSlow374 + (fRec79[1] - floorf((fSlow374 + fRec79[1]))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm84 = ftbl0[(((int((65536.0f * fRec79[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec81[0] = (iSlow380 * (iRec81[1] + 1));
				iTempPerm85 = int((iRec81[0] < iSlow378));
				fTempPerm86 = expf((0 - (fConst4 / ((iSlow381)?((iTempPerm85)?fSlow377:fSlow76):fSlow375))));
				fRec80[0] = ((fRec80[1] * fTempPerm86) + (((iSlow381)?((iTempPerm85)?1.5873015873015872f:fSlow383):0.0f) * (1.0f - fTempPerm86)));
				fTempPerm87 = min(1.0f, fRec80[0]);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec82[0] = (fSlow386 + (fRec82[1] - floorf((fSlow386 + fRec82[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm88 = ftbl0[(((int((65536.0f * fRec82[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec84[0] = (iSlow392 * (iRec84[1] + 1));
				iTempPerm89 = int((iRec84[0] < iSlow390));
				fTempPerm90 = expf((0 - (fConst4 / ((iSlow393)?((iTempPerm89)?fSlow389:fSlow76):fSlow387))));
				fRec83[0] = ((fRec83[1] * fTempPerm90) + (((iSlow393)?((iTempPerm89)?1.5873015873015872f:fSlow395):0.0f) * (1.0f - fTempPerm90)));
				fTempPerm91 = min(1.0f, fRec83[0]);
			}
			if (iSlow11 || iSlow10) {
				fTempPerm92 = (fSlow397 * (fTempPerm91 * fTempPerm88));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec85[0] = (fSlow398 + (fRec85[1] - floorf((fSlow398 + fRec85[1]))));
				iRec87[0] = (iSlow403 * (iRec87[1] + 1));
				iTempPerm93 = int((iRec87[0] < iSlow402));
				fTempPerm94 = expf((0 - (fConst4 / ((iSlow404)?((iTempPerm93)?fSlow401:fSlow76):fSlow399))));
				fRec86[0] = ((fRec86[1] * fTempPerm94) + (((iSlow404)?((iTempPerm93)?1.5873015873015872f:fSlow405):0.0f) * (1.0f - fTempPerm94)));
				fTempPerm95 = min(1.0f, fRec86[0]);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm96 = (fSlow406 * (fTempPerm95 * ftbl0[(((int((65536.0f * fRec85[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11) {
				fTempPerm97 = (((fTempPerm96 + fTempPerm92) + (fSlow385 * (fTempPerm87 * fTempPerm84))) + (fSlow373 * (min(1.0f, fRec77[0]) * fTempPerm81)));
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec89[0] = ((iSlow414)?0.0f:min(fSlow413, (fRec89[1] + 1.0f)));
				iTempPerm98 = int((fRec89[0] < fSlow410));
				fRec88[0] = ((iSlow369)?(fSlow370 * ((iTempPerm98)?((int((fRec89[0] < 0.0f)))?0.0f:((iTempPerm98)?(fSlow416 * fRec89[0]):1.0f)):((int((fRec89[0] < fSlow413)))?((fSlow415 * (fRec89[0] - fSlow410)) + 1.0f):fSlow408))):fRec88[1]);
				fRec90[0] = ((iSlow418)?0.0f:min(fSlow417, (fRec90[1] + 1.0f)));
				fTempPerm99 = (((int((fRec90[0] < 0.0f)))?fRec88[0]:((int((fRec90[0] < fSlow417)))?(fRec88[0] + (fSlow419 * (0 - (fRec90[0] * fRec88[0])))):0.0f)) * fTempPerm81);
			}
			if (iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm100 = (fSlow420 * fTempPerm99);
				fTempPerm101 = ftbl0[(((int((65536.0f * (fRec79[0] + fTempPerm100))) % 65536) + 65536) % 65536)];
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm102 = (fSlow385 * (fTempPerm87 * fTempPerm101));
			}
			if (iSlow10) {
				fTempPerm103 = (fTempPerm92 + (fTempPerm96 + fTempPerm102));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm104 = ftbl0[(((int((65536.0f * (fRec82[0] + fTempPerm100))) % 65536) + 65536) % 65536)];
			}
			if (iSlow9) {
				fTempPerm105 = ((fSlow397 * (fTempPerm91 * fTempPerm104)) + (fTempPerm102 + (fSlow406 * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec85[0] + fTempPerm100))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec92[0] = ((iSlow428)?0.0f:min(fSlow427, (fRec92[1] + 1.0f)));
				iTempPerm106 = int((fRec92[0] < fSlow424));
				fRec91[0] = ((iSlow393)?(fSlow394 * ((iTempPerm106)?((int((fRec92[0] < 0.0f)))?0.0f:((iTempPerm106)?(fSlow430 * fRec92[0]):1.0f)):((int((fRec92[0] < fSlow427)))?((fSlow429 * (fRec92[0] - fSlow424)) + 1.0f):fSlow422))):fRec91[1]);
				fRec93[0] = ((iSlow432)?0.0f:min(fSlow431, (fRec93[1] + 1.0f)));
				fTempPerm107 = ((int((fRec93[0] < 0.0f)))?fRec91[0]:((int((fRec93[0] < fSlow431)))?(fRec91[0] + (fSlow433 * (0 - (fRec93[0] * fRec91[0])))):0.0f));
			}
			if (iSlow8 || iSlow7) {
				fTempPerm108 = (fTempPerm107 * fTempPerm88);
			}
			if (iSlow8) {
				fTempPerm109 = ((fSlow406 * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow434 * fTempPerm108)))) % 65536) + 65536) % 65536)])) + fTempPerm102);
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec95[0] = ((iSlow442)?0.0f:min(fSlow441, (fRec95[1] + 1.0f)));
				iTempPerm110 = int((fRec95[0] < fSlow438));
				fRec94[0] = ((iSlow381)?(fSlow382 * ((iTempPerm110)?((int((fRec95[0] < 0.0f)))?0.0f:((iTempPerm110)?(fSlow444 * fRec95[0]):1.0f)):((int((fRec95[0] < fSlow441)))?((fSlow443 * (fRec95[0] - fSlow438)) + 1.0f):fSlow436))):fRec94[1]);
				fRec96[0] = ((iSlow446)?0.0f:min(fSlow445, (fRec96[1] + 1.0f)));
				fTempPerm111 = ((int((fRec96[0] < 0.0f)))?fRec94[0]:((int((fRec96[0] < fSlow445)))?(fRec94[0] + (fSlow447 * (0 - (fRec96[0] * fRec94[0])))):0.0f));
			}
			if (iSlow7 || iSlow3) {
				fTempPerm112 = (fTempPerm111 * fTempPerm84);
				fTempPerm113 = (fSlow372 * fTempPerm99);
			}
			if (iSlow7) {
				fTempPerm114 = (fSlow406 * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow31 * ((fTempPerm113 + (fSlow384 * fTempPerm112)) + (fSlow396 * fTempPerm108)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm115 = (fTempPerm111 * fTempPerm101);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm116 = (fSlow448 * fTempPerm115);
				fTempPerm117 = ftbl0[(((int((65536.0f * (fRec82[0] + fTempPerm116))) % 65536) + 65536) % 65536)];
			}
			if (iSlow6 || iSlow5) {
				fTempPerm118 = (fSlow397 * (fTempPerm91 * fTempPerm117));
			}
			if (iSlow6) {
				fTempPerm119 = (fTempPerm118 + fTempPerm96);
			}
			if (iSlow5) {
				fTempPerm120 = ((fSlow406 * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec85[0] + fTempPerm116))) % 65536) + 65536) % 65536)])) + fTempPerm118);
			}
			if (iSlow4) {
				fTempPerm121 = (fSlow406 * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow31 * ((fSlow384 * fTempPerm115) + (fSlow396 * (fTempPerm107 * fTempPerm104))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm122 = (fSlow406 * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow31 * (fTempPerm113 + (fSlow396 * (fTempPerm107 * ftbl0[(((int((65536.0f * (fRec82[0] + (fSlow448 * fTempPerm112)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow2 || iSlow1) {
				fTempPerm123 = (fSlow406 * (fTempPerm95 * ftbl0[(((int((65536.0f * (fRec85[0] + (fSlow434 * (fTempPerm107 * fTempPerm117))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm124 = ftbl0[(((int((65536.0f * fRec65[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm125 = (fTempPerm71 * fTempPerm124);
				fTempPerm126 = (fSlow311 * fTempPerm67);
			}
			if (iSlow3) {
				fTempPerm127 = (fSlow361 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow31 * (fTempPerm126 + (fSlow351 * (fTempPerm76 * ftbl0[(((int((65536.0f * (fRec69[0] + (fSlow332 * fTempPerm125)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm128 = ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm68))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm129 = (fSlow361 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow31 * ((fSlow331 * fTempPerm72) + (fSlow351 * (fTempPerm76 * fTempPerm128))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec98[0] = (iSlow345 * (iRec98[1] + 1));
				iTempPerm130 = int((iRec98[0] < iSlow452));
				fTempPerm131 = expf((0 - (fConst4 / ((iSlow347)?((iTempPerm130)?fSlow451:fSlow76):fSlow449))));
				fRec97[0] = ((fRec97[1] * fTempPerm131) + (((iSlow347)?((iTempPerm130)?1.5873015873015872f:fSlow453):0.0f) * (1.0f - fTempPerm131)));
				fTempPerm132 = min(1.0f, fRec97[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm133 = (fSlow454 * (fTempPerm132 * fTempPerm74));
			}
			if (iSlow5) {
				fTempPerm134 = ((fSlow361 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm73))) % 65536) + 65536) % 65536)])) + fTempPerm133);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm135 = (fSlow361 * (fTempPerm79 * ftbl0[(((int((65536.0f * fRec73[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm136 = (fTempPerm133 + fTempPerm135);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm137 = ftbl0[(((int((65536.0f * fRec69[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm138 = (fTempPerm76 * fTempPerm137);
			}
			if (iSlow7) {
				fTempPerm139 = (fSlow361 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow31 * ((fTempPerm126 + (fSlow331 * fTempPerm125)) + (fSlow351 * fTempPerm138)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec100[0] = (iSlow325 * (iRec100[1] + 1));
				iTempPerm140 = int((iRec100[0] < iSlow458));
				fTempPerm141 = expf((0 - (fConst4 / ((iSlow327)?((iTempPerm140)?fSlow457:fSlow76):fSlow455))));
				fRec99[0] = ((fRec99[1] * fTempPerm141) + (((iSlow327)?((iTempPerm140)?1.5873015873015872f:fSlow459):0.0f) * (1.0f - fTempPerm141)));
				fTempPerm142 = min(1.0f, fRec99[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm143 = (fSlow460 * (fTempPerm142 * fTempPerm69));
			}
			if (iSlow8) {
				fTempPerm144 = ((fSlow361 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow352 * fTempPerm138)))) % 65536) + 65536) % 65536)])) + fTempPerm143);
			}
			if (iSlow9) {
				fTempPerm145 = ((fSlow454 * (fTempPerm132 * fTempPerm128)) + (fTempPerm143 + (fSlow361 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm68))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm146 = (fSlow454 * (fTempPerm132 * fTempPerm137));
			}
			if (iSlow10) {
				fTempPerm147 = (fTempPerm146 + (fTempPerm135 + fTempPerm143));
			}
			if (iSlow11) {
				iRec102[0] = (iSlow305 * (iRec102[1] + 1));
				iTempPerm148 = int((iRec102[0] < iSlow464));
				fTempPerm149 = expf((0 - (fConst4 / ((iSlow307)?((iTempPerm148)?fSlow463:fSlow76):fSlow461))));
				fRec101[0] = ((fRec101[1] * fTempPerm149) + (((iSlow307)?((iTempPerm148)?1.5873015873015872f:fSlow465):0.0f) * (1.0f - fTempPerm149)));
				fTempPerm150 = (((fTempPerm135 + fTempPerm146) + (fSlow460 * (fTempPerm142 * fTempPerm124))) + (fSlow466 * (min(1.0f, fRec101[0]) * fTempPerm65)));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm151 = ftbl0[(((int((65536.0f * fRec50[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm152 = (fTempPerm55 * fTempPerm151);
				fTempPerm153 = (fSlow242 * fTempPerm51);
			}
			if (iSlow3) {
				fTempPerm154 = (fSlow292 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow31 * (fTempPerm153 + (fSlow282 * (fTempPerm60 * ftbl0[(((int((65536.0f * (fRec54[0] + (fSlow263 * fTempPerm152)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm155 = ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm52))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm156 = (fSlow292 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow31 * ((fSlow262 * fTempPerm56) + (fSlow282 * (fTempPerm60 * fTempPerm155))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec104[0] = (iSlow276 * (iRec104[1] + 1));
				iTempPerm157 = int((iRec104[0] < iSlow470));
				fTempPerm158 = expf((0 - (fConst4 / ((iSlow278)?((iTempPerm157)?fSlow469:fSlow76):fSlow467))));
				fRec103[0] = ((fRec103[1] * fTempPerm158) + (((iSlow278)?((iTempPerm157)?1.5873015873015872f:fSlow471):0.0f) * (1.0f - fTempPerm158)));
				fTempPerm159 = min(1.0f, fRec103[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm160 = (fSlow472 * (fTempPerm159 * fTempPerm58));
			}
			if (iSlow5) {
				fTempPerm161 = ((fSlow292 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + fTempPerm57))) % 65536) + 65536) % 65536)])) + fTempPerm160);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm162 = (fSlow292 * (fTempPerm63 * ftbl0[(((int((65536.0f * fRec58[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm163 = (fTempPerm160 + fTempPerm162);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm164 = ftbl0[(((int((65536.0f * fRec54[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm165 = (fTempPerm60 * fTempPerm164);
			}
			if (iSlow7) {
				fTempPerm166 = (fSlow292 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow31 * ((fTempPerm153 + (fSlow262 * fTempPerm152)) + (fSlow282 * fTempPerm165)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec106[0] = (iSlow256 * (iRec106[1] + 1));
				iTempPerm167 = int((iRec106[0] < iSlow476));
				fTempPerm168 = expf((0 - (fConst4 / ((iSlow258)?((iTempPerm167)?fSlow475:fSlow76):fSlow473))));
				fRec105[0] = ((fRec105[1] * fTempPerm168) + (((iSlow258)?((iTempPerm167)?1.5873015873015872f:fSlow477):0.0f) * (1.0f - fTempPerm168)));
				fTempPerm169 = min(1.0f, fRec105[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm170 = (fSlow478 * (fTempPerm169 * fTempPerm53));
			}
			if (iSlow8) {
				fTempPerm171 = ((fSlow292 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow283 * fTempPerm165)))) % 65536) + 65536) % 65536)])) + fTempPerm170);
			}
			if (iSlow9) {
				fTempPerm172 = ((fSlow472 * (fTempPerm159 * fTempPerm155)) + (fTempPerm170 + (fSlow292 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + fTempPerm52))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm173 = (fSlow472 * (fTempPerm159 * fTempPerm164));
			}
			if (iSlow10) {
				fTempPerm174 = (fTempPerm173 + (fTempPerm162 + fTempPerm170));
			}
			if (iSlow11) {
				iRec108[0] = (iSlow236 * (iRec108[1] + 1));
				iTempPerm175 = int((iRec108[0] < iSlow482));
				fTempPerm176 = expf((0 - (fConst4 / ((iSlow238)?((iTempPerm175)?fSlow481:fSlow76):fSlow479))));
				fRec107[0] = ((fRec107[1] * fTempPerm176) + (((iSlow238)?((iTempPerm175)?1.5873015873015872f:fSlow483):0.0f) * (1.0f - fTempPerm176)));
				fTempPerm177 = (((fTempPerm162 + fTempPerm173) + (fSlow478 * (fTempPerm169 * fTempPerm151))) + (fSlow484 * (min(1.0f, fRec107[0]) * fTempPerm49)));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm178 = ftbl0[(((int((65536.0f * fRec35[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm179 = (fTempPerm39 * fTempPerm178);
				fTempPerm180 = (fSlow173 * fTempPerm35);
			}
			if (iSlow3) {
				fTempPerm181 = (fSlow223 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow31 * (fTempPerm180 + (fSlow213 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec39[0] + (fSlow194 * fTempPerm179)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm182 = ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm36))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm183 = (fSlow223 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow31 * ((fSlow193 * fTempPerm40) + (fSlow213 * (fTempPerm44 * fTempPerm182))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec110[0] = (iSlow207 * (iRec110[1] + 1));
				iTempPerm184 = int((iRec110[0] < iSlow488));
				fTempPerm185 = expf((0 - (fConst4 / ((iSlow209)?((iTempPerm184)?fSlow487:fSlow76):fSlow485))));
				fRec109[0] = ((fRec109[1] * fTempPerm185) + (((iSlow209)?((iTempPerm184)?1.5873015873015872f:fSlow489):0.0f) * (1.0f - fTempPerm185)));
				fTempPerm186 = min(1.0f, fRec109[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm187 = (fSlow490 * (fTempPerm186 * fTempPerm42));
			}
			if (iSlow5) {
				fTempPerm188 = ((fSlow223 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + fTempPerm41))) % 65536) + 65536) % 65536)])) + fTempPerm187);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm189 = (fSlow223 * (fTempPerm47 * ftbl0[(((int((65536.0f * fRec43[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm190 = (fTempPerm187 + fTempPerm189);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm191 = ftbl0[(((int((65536.0f * fRec39[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm192 = (fTempPerm44 * fTempPerm191);
			}
			if (iSlow7) {
				fTempPerm193 = (fSlow223 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow31 * ((fTempPerm180 + (fSlow193 * fTempPerm179)) + (fSlow213 * fTempPerm192)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec112[0] = (iSlow187 * (iRec112[1] + 1));
				iTempPerm194 = int((iRec112[0] < iSlow494));
				fTempPerm195 = expf((0 - (fConst4 / ((iSlow189)?((iTempPerm194)?fSlow493:fSlow76):fSlow491))));
				fRec111[0] = ((fRec111[1] * fTempPerm195) + (((iSlow189)?((iTempPerm194)?1.5873015873015872f:fSlow495):0.0f) * (1.0f - fTempPerm195)));
				fTempPerm196 = min(1.0f, fRec111[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm197 = (fSlow496 * (fTempPerm196 * fTempPerm37));
			}
			if (iSlow8) {
				fTempPerm198 = ((fSlow223 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow214 * fTempPerm192)))) % 65536) + 65536) % 65536)])) + fTempPerm197);
			}
			if (iSlow9) {
				fTempPerm199 = ((fSlow490 * (fTempPerm186 * fTempPerm182)) + (fTempPerm197 + (fSlow223 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + fTempPerm36))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm200 = (fSlow490 * (fTempPerm186 * fTempPerm191));
			}
			if (iSlow10) {
				fTempPerm201 = (fTempPerm200 + (fTempPerm189 + fTempPerm197));
			}
			if (iSlow11) {
				iRec114[0] = (iSlow167 * (iRec114[1] + 1));
				iTempPerm202 = int((iRec114[0] < iSlow500));
				fTempPerm203 = expf((0 - (fConst4 / ((iSlow169)?((iTempPerm202)?fSlow499:fSlow76):fSlow497))));
				fRec113[0] = ((fRec113[1] * fTempPerm203) + (((iSlow169)?((iTempPerm202)?1.5873015873015872f:fSlow501):0.0f) * (1.0f - fTempPerm203)));
				fTempPerm204 = (((fTempPerm189 + fTempPerm200) + (fSlow496 * (fTempPerm196 * fTempPerm178))) + (fSlow502 * (min(1.0f, fRec113[0]) * fTempPerm33)));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm205 = ftbl0[(((int((65536.0f * fRec20[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm206 = (fTempPerm23 * fTempPerm205);
				fTempPerm207 = (fSlow104 * fTempPerm19);
			}
			if (iSlow3) {
				fTempPerm208 = (fSlow154 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow31 * (fTempPerm207 + (fSlow144 * (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec24[0] + (fSlow125 * fTempPerm206)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm209 = ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm20))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm210 = (fSlow154 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow31 * ((fSlow124 * fTempPerm24) + (fSlow144 * (fTempPerm28 * fTempPerm209))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec116[0] = (iSlow138 * (iRec116[1] + 1));
				iTempPerm211 = int((iRec116[0] < iSlow506));
				fTempPerm212 = expf((0 - (fConst4 / ((iSlow140)?((iTempPerm211)?fSlow505:fSlow76):fSlow503))));
				fRec115[0] = ((fRec115[1] * fTempPerm212) + (((iSlow140)?((iTempPerm211)?1.5873015873015872f:fSlow507):0.0f) * (1.0f - fTempPerm212)));
				fTempPerm213 = min(1.0f, fRec115[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm214 = (fSlow508 * (fTempPerm213 * fTempPerm26));
			}
			if (iSlow5) {
				fTempPerm215 = ((fSlow154 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + fTempPerm25))) % 65536) + 65536) % 65536)])) + fTempPerm214);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm216 = (fSlow154 * (fTempPerm31 * ftbl0[(((int((65536.0f * fRec28[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm217 = (fTempPerm214 + fTempPerm216);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm218 = ftbl0[(((int((65536.0f * fRec24[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm219 = (fTempPerm28 * fTempPerm218);
			}
			if (iSlow7) {
				fTempPerm220 = (fSlow154 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow31 * ((fTempPerm207 + (fSlow124 * fTempPerm206)) + (fSlow144 * fTempPerm219)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec118[0] = (iSlow118 * (iRec118[1] + 1));
				iTempPerm221 = int((iRec118[0] < iSlow512));
				fTempPerm222 = expf((0 - (fConst4 / ((iSlow120)?((iTempPerm221)?fSlow511:fSlow76):fSlow509))));
				fRec117[0] = ((fRec117[1] * fTempPerm222) + (((iSlow120)?((iTempPerm221)?1.5873015873015872f:fSlow513):0.0f) * (1.0f - fTempPerm222)));
				fTempPerm223 = min(1.0f, fRec117[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm224 = (fSlow514 * (fTempPerm223 * fTempPerm21));
			}
			if (iSlow8) {
				fTempPerm225 = ((fSlow154 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow145 * fTempPerm219)))) % 65536) + 65536) % 65536)])) + fTempPerm224);
			}
			if (iSlow9) {
				fTempPerm226 = ((fSlow508 * (fTempPerm213 * fTempPerm209)) + (fTempPerm224 + (fSlow154 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + fTempPerm20))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm227 = (fSlow508 * (fTempPerm213 * fTempPerm218));
			}
			if (iSlow10) {
				fTempPerm228 = (fTempPerm227 + (fTempPerm216 + fTempPerm224));
			}
			if (iSlow11) {
				iRec120[0] = (iSlow98 * (iRec120[1] + 1));
				iTempPerm229 = int((iRec120[0] < iSlow518));
				fTempPerm230 = expf((0 - (fConst4 / ((iSlow100)?((iTempPerm229)?fSlow517:fSlow76):fSlow515))));
				fRec119[0] = ((fRec119[1] * fTempPerm230) + (((iSlow100)?((iTempPerm229)?1.5873015873015872f:fSlow519):0.0f) * (1.0f - fTempPerm230)));
				fTempPerm231 = (((fTempPerm216 + fTempPerm227) + (fSlow514 * (fTempPerm223 * fTempPerm205))) + (fSlow520 * (min(1.0f, fRec119[0]) * fTempPerm17)));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm232 = ftbl0[(((int((65536.0f * fRec5[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm233 = (fTempPerm7 * fTempPerm232);
				fTempPerm234 = (fSlow30 * fTempPerm3);
			}
			if (iSlow3) {
				fTempPerm235 = (fSlow85 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow31 * (fTempPerm234 + (fSlow71 * (fTempPerm12 * ftbl0[(((int((65536.0f * (fRec9[0] + (fSlow52 * fTempPerm233)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm236 = ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm4))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm237 = (fSlow85 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow31 * ((fSlow51 * fTempPerm8) + (fSlow71 * (fTempPerm12 * fTempPerm236))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iRec122[0] = (iSlow65 * (iRec122[1] + 1));
				iTempPerm238 = int((iRec122[0] < iSlow524));
				fTempPerm239 = expf((0 - (fConst4 / ((iSlow67)?((iTempPerm238)?fSlow523:fSlow76):fSlow521))));
				fRec121[0] = ((fRec121[1] * fTempPerm239) + (((iSlow67)?((iTempPerm238)?1.5873015873015872f:fSlow525):0.0f) * (1.0f - fTempPerm239)));
				fTempPerm240 = min(1.0f, fRec121[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm241 = (fSlow526 * (fTempPerm240 * fTempPerm10));
			}
			if (iSlow5) {
				fTempPerm242 = ((fSlow85 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm9))) % 65536) + 65536) % 65536)])) + fTempPerm241);
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm243 = (fSlow85 * (fTempPerm15 * ftbl0[(((int((65536.0f * fRec13[0])) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6) {
				fTempPerm244 = (fTempPerm241 + fTempPerm243);
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm245 = ftbl0[(((int((65536.0f * fRec9[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm246 = (fTempPerm12 * fTempPerm245);
			}
			if (iSlow7) {
				fTempPerm247 = (fSlow85 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow31 * ((fTempPerm234 + (fSlow51 * fTempPerm233)) + (fSlow71 * fTempPerm246)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iRec124[0] = (iSlow45 * (iRec124[1] + 1));
				iTempPerm248 = int((iRec124[0] < iSlow530));
				fTempPerm249 = expf((0 - (fConst4 / ((iSlow47)?((iTempPerm248)?fSlow529:fSlow76):fSlow527))));
				fRec123[0] = ((fRec123[1] * fTempPerm249) + (((iSlow47)?((iTempPerm248)?1.5873015873015872f:fSlow531):0.0f) * (1.0f - fTempPerm249)));
				fTempPerm250 = min(1.0f, fRec123[0]);
			}
			if (iSlow10 || iSlow9 || iSlow8) {
				fTempPerm251 = (fSlow532 * (fTempPerm250 * fTempPerm5));
			}
			if (iSlow8) {
				fTempPerm252 = ((fSlow85 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow72 * fTempPerm246)))) % 65536) + 65536) % 65536)])) + fTempPerm251);
			}
			if (iSlow9) {
				fTempPerm253 = ((fSlow526 * (fTempPerm240 * fTempPerm236)) + (fTempPerm251 + (fSlow85 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm4))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm254 = (fSlow526 * (fTempPerm240 * fTempPerm245));
			}
			if (iSlow10) {
				fTempPerm255 = (fTempPerm254 + (fTempPerm243 + fTempPerm251));
			}
			if (iSlow11) {
				iRec126[0] = (iSlow24 * (iRec126[1] + 1));
				iTempPerm256 = int((iRec126[0] < iSlow536));
				fTempPerm257 = expf((0 - (fConst4 / ((iSlow26)?((iTempPerm256)?fSlow535:fSlow76):fSlow533))));
				fRec125[0] = ((fRec125[1] * fTempPerm257) + (((iSlow26)?((iTempPerm256)?1.5873015873015872f:fSlow537):0.0f) * (1.0f - fTempPerm257)));
				fTempPerm258 = (((fTempPerm243 + fTempPerm254) + (fSlow532 * (fTempPerm250 * fTempPerm232))) + (fSlow538 * (min(1.0f, fRec125[0]) * fTempPerm1)));
			}
			output0[i] = (FAUSTFLOAT)(fTempPerm258 + (fTempPerm255 + (fTempPerm253 + (fTempPerm252 + (fTempPerm247 + (fTempPerm244 + (fTempPerm242 + (fTempPerm237 + (fTempPerm235 + (fTempPerm16 + ((fTempPerm231 + (fTempPerm228 + (fTempPerm226 + (fTempPerm225 + (fTempPerm220 + (fTempPerm217 + (fTempPerm215 + (fTempPerm210 + (fTempPerm208 + (fTempPerm32 + ((fTempPerm204 + (fTempPerm201 + (fTempPerm199 + (fTempPerm198 + (fTempPerm193 + (fTempPerm190 + (fTempPerm188 + (fTempPerm183 + (fTempPerm181 + (fTempPerm48 + ((fTempPerm177 + (fTempPerm174 + (fTempPerm172 + (fTempPerm171 + (fTempPerm166 + (fTempPerm163 + (fTempPerm161 + (fTempPerm156 + (fTempPerm154 + (fTempPerm64 + ((fTempPerm150 + (fTempPerm147 + (fTempPerm145 + (fTempPerm144 + (fTempPerm139 + (fTempPerm136 + (fTempPerm134 + (fTempPerm129 + (fTempPerm127 + (fTempPerm80 + (((((((((((fTempPerm123 + fTempPerm123) + fTempPerm122) + fTempPerm121) + fTempPerm120) + fTempPerm119) + fTempPerm114) + fTempPerm109) + fTempPerm105) + fTempPerm103) + fTempPerm97) + fTempPerm80))))))))))) + fTempPerm64))))))))))) + fTempPerm48))))))))))) + fTempPerm32))))))))))) + fTempPerm16)))))))))));
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
