//----------------------------------------------------------
// name: "hammond"
//
// Code generated with Faust 2.13.11 (https://faust.grame.fr)
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
#define FAUSTCLASS faust_hammond
#endif

class faust_hammond : public dsp {
  private:
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec18[2];
		float 	fTempPerm22;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm22 = 0;
			for (int i=0; i<2; i++) iRec18[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec18[0] = (iRec18[1] + 1);
				fTempPerm22 = sinf((9.5873799242852573e-05f * float((iRec18[0] + -1))));
				output[i] = fTempPerm22;
				// post processing
				iRec18[1] = iRec18[0];
			}
		}
	};


	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fConst0;
	FAUSTFLOAT 	fbutton0;
	float 	fVec0[2];
	int 	iRec1[2];
	int 	iTempPerm0;
	float 	fConst1;
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider3;
	float 	fRec0[2];
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider4;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	float 	fConst8;
	FAUSTFLOAT 	fbutton1;
	float 	fVec1[2];
	int 	iRec5[2];
	int 	iTempPerm3;
	float 	fTempPerm4;
	float 	fRec4[2];
	float 	fTempPerm5;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fbutton2;
	float 	fVec2[2];
	int 	iRec7[2];
	int 	iTempPerm6;
	float 	fTempPerm7;
	float 	fRec6[2];
	float 	fTempPerm8;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fbutton3;
	float 	fVec3[2];
	int 	iRec9[2];
	int 	iTempPerm9;
	float 	fTempPerm10;
	float 	fRec8[2];
	float 	fTempPerm11;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fbutton4;
	float 	fVec4[2];
	int 	iRec11[2];
	int 	iTempPerm12;
	float 	fTempPerm13;
	float 	fRec10[2];
	float 	fTempPerm14;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fbutton5;
	float 	fVec5[2];
	int 	iRec13[2];
	int 	iTempPerm15;
	float 	fTempPerm16;
	float 	fRec12[2];
	float 	fTempPerm17;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	float 	fRec14[2];
	float 	fConst9;
	float 	fTempPerm18;
	float 	fRec3[2];
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm19;
	int 	iRec16[2];
	float 	fRec15[4];
	float 	fTempPerm20;
	float 	fConst10;
	float 	fTempPerm21;
	float 	fRec17[2];
	static float 	ftbl0[65536];
	float 	fConst11;
	float 	fTempPerm23;
	float 	fRec20[2];
	float 	fTempPerm24;
	float 	fTempPerm25;
	FAUSTFLOAT 	fslider11;
	float 	fConst12;
	float 	fTempPerm26;
	float 	fRec19[2];
	FAUSTFLOAT 	fslider12;
	float 	fRec21[2];
	float 	fConst13;
	float 	fTempPerm27;
	float 	fRec22[2];
	FAUSTFLOAT 	fslider13;
	float 	fRec23[2];
	float 	fConst14;
	float 	fRec24[2];
	FAUSTFLOAT 	fslider14;
	float 	fRec25[2];
	float 	fConst15;
	float 	fTempPerm28;
	float 	fRec26[2];
	float 	fRec2[3];
	float 	fConst16;
	float 	fTempPerm29;
	float 	fTempPerm30;
	float 	fTempPerm31;
	float 	fRec28[2];
	FAUSTFLOAT 	fslider15;
	float 	fTempPerm32;
	float 	fRec29[2];
	float 	fTempPerm33;
	float 	fRec30[2];
	float 	fRec31[2];
	float 	fTempPerm34;
	float 	fRec32[2];
	float 	fRec27[3];
	float 	fTempPerm35;
	float 	fTempPerm36;
	float 	fRec34[2];
	FAUSTFLOAT 	fslider16;
	float 	fTempPerm37;
	float 	fRec35[2];
	float 	fTempPerm38;
	float 	fRec36[2];
	float 	fRec37[2];
	float 	fTempPerm39;
	float 	fRec38[2];
	float 	fRec33[3];
	float 	fTempPerm40;
	float 	fTempPerm41;
	float 	fRec40[2];
	FAUSTFLOAT 	fslider17;
	float 	fTempPerm42;
	float 	fRec41[2];
	float 	fTempPerm43;
	float 	fRec42[2];
	float 	fRec43[2];
	float 	fTempPerm44;
	float 	fRec44[2];
	float 	fRec39[3];
	float 	fTempPerm45;
	float 	fTempPerm46;
	float 	fRec46[2];
	FAUSTFLOAT 	fslider18;
	float 	fTempPerm47;
	float 	fRec47[2];
	float 	fTempPerm48;
	float 	fRec48[2];
	float 	fRec49[2];
	float 	fTempPerm49;
	float 	fRec50[2];
	float 	fRec45[3];
	float 	fTempPerm50;
	float 	fTempPerm51;
	float 	fRec52[2];
	FAUSTFLOAT 	fslider19;
	float 	fTempPerm52;
	float 	fRec53[2];
	float 	fTempPerm53;
	float 	fRec54[2];
	float 	fRec55[2];
	float 	fTempPerm54;
	float 	fRec56[2];
	float 	fRec51[3];
	float 	fTempPerm55;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "hammond");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "hammond");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
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
		iTempPerm0 = 0;
		fConst1 = (6.9100000000000001f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst2 = tanf((5654.8667764616275f / fConst0));
		fConst3 = faustpower<2>(fConst2);
		fConst4 = (1.0f / fConst3);
		fConst5 = (2.0f * (1.0f - fConst4));
		fConst6 = (1.0f / fConst2);
		fConst7 = (((fConst6 + -1.4142135623730949f) / fConst2) + 1.0f);
		fConst8 = (1.0f / (((fConst6 + 1.4142135623730949f) / fConst2) + 1.0f));
		iTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		iTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		iTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		iTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		iTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		fConst9 = (2.5f / fConst0);
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fConst10 = (0.02f * fConst0);
		fTempPerm21 = 0;
		fConst11 = (10.0f / fConst0);
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fConst12 = (2.0f / fConst0);
		fTempPerm26 = 0;
		fConst13 = (1.3348398539999999f / fConst0);
		fTempPerm27 = 0;
		fConst14 = (0.5f / fConst0);
		fConst15 = (1.0f / fConst0);
		fTempPerm28 = 0;
		fConst16 = (0 - (2.0f / fConst3));
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
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
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 0.001f;
		fbutton0 = 0.0;
		fslider3 = 1.0f;
		fslider4 = 1.0f;
		fbutton1 = 0.0;
		fslider5 = 1.0f;
		fbutton2 = 0.0;
		fslider6 = 1.0f;
		fbutton3 = 0.0;
		fslider7 = 1.0f;
		fbutton4 = 0.0;
		fslider8 = 1.0f;
		fbutton5 = 0.0;
		fslider9 = 1.0f;
		fslider10 = 0.5f;
		fslider11 = 440.0f;
		fslider12 = 0.5f;
		fslider13 = 0.5f;
		fslider14 = 0.5f;
		fslider15 = 440.0f;
		fslider16 = 440.0f;
		fslider17 = 440.0f;
		fslider18 = 440.0f;
		fslider19 = 440.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) iRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) iRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) iRec7[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) iRec9[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) iRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) iRec13[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) iRec16[i] = 0;
		for (int i=0; i<4; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<3; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<3; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<3; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<3; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
		for (int i=0; i<2; i++) fRec56[i] = 0;
		for (int i=0; i<3; i++) fRec51[i] = 0;
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
	virtual faust_hammond* clone() {
		return new faust_hammond();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("hammond");
		ui_interface->addHorizontalSlider("drawbar1", &fslider14, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("drawbar2", &fslider13, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("drawbar3", &fslider12, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fslider2, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider1, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider0, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider3, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("leslie", &fslider10, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalBargraph("phasor", &fbargraph0, 0.0f, 1.0f);
		ui_interface->openVerticalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider19, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider9, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider18, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider8, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider17, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider7, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider16, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider6, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider15, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider5, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider11, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider4, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = (6.9100000000000001f * fSlow2);
		int 	iSlow4 = int((fConst0 * fSlow2));
		float 	fSlow5 = float(fbutton0);
		int 	iSlow6 = (fSlow5 > 0.0f);
		int 	iSlow7 = int(iSlow6);
		float 	fSlow8 = float(fslider3);
		float 	fSlow9 = (float(iSlow6) * fSlow8);
		float 	fSlow10 = float(fslider4);
		float 	fSlow11 = float(fbutton1);
		int 	iSlow12 = (fSlow11 > 0.0f);
		int 	iSlow13 = int(iSlow12);
		float 	fSlow14 = (float(iSlow12) * fSlow8);
		float 	fSlow15 = float(fslider5);
		float 	fSlow16 = float(fbutton2);
		int 	iSlow17 = (fSlow16 > 0.0f);
		int 	iSlow18 = int(iSlow17);
		float 	fSlow19 = (float(iSlow17) * fSlow8);
		float 	fSlow20 = float(fslider6);
		float 	fSlow21 = float(fbutton3);
		int 	iSlow22 = (fSlow21 > 0.0f);
		int 	iSlow23 = int(iSlow22);
		float 	fSlow24 = (float(iSlow22) * fSlow8);
		float 	fSlow25 = float(fslider7);
		float 	fSlow26 = float(fbutton4);
		int 	iSlow27 = (fSlow26 > 0.0f);
		int 	iSlow28 = int(iSlow27);
		float 	fSlow29 = (float(iSlow27) * fSlow8);
		float 	fSlow30 = float(fslider8);
		float 	fSlow31 = float(fbutton5);
		int 	iSlow32 = (fSlow31 > 0.0f);
		int 	iSlow33 = int(iSlow32);
		float 	fSlow34 = (float(iSlow32) * fSlow8);
		float 	fSlow35 = float(fslider9);
		float 	fSlow36 = (0.0010000000000000009f * float(fslider10));
		float 	fSlow37 = float(fslider11);
		float 	fSlow38 = (fConst12 * fSlow37);
		float 	fSlow39 = (0.0010000000000000009f * float(fslider12));
		float 	fSlow40 = (fConst13 * fSlow37);
		float 	fSlow41 = (0.0010000000000000009f * float(fslider13));
		float 	fSlow42 = (fConst14 * fSlow37);
		float 	fSlow43 = (0.0010000000000000009f * float(fslider14));
		float 	fSlow44 = (fConst15 * fSlow37);
		float 	fSlow45 = (fConst8 * fSlow10);
		float 	fSlow46 = float(fslider15);
		float 	fSlow47 = (fConst12 * fSlow46);
		float 	fSlow48 = (fConst13 * fSlow46);
		float 	fSlow49 = (fConst14 * fSlow46);
		float 	fSlow50 = (fConst15 * fSlow46);
		float 	fSlow51 = (fConst8 * fSlow15);
		float 	fSlow52 = float(fslider16);
		float 	fSlow53 = (fConst12 * fSlow52);
		float 	fSlow54 = (fConst13 * fSlow52);
		float 	fSlow55 = (fConst14 * fSlow52);
		float 	fSlow56 = (fConst15 * fSlow52);
		float 	fSlow57 = (fConst8 * fSlow20);
		float 	fSlow58 = float(fslider17);
		float 	fSlow59 = (fConst12 * fSlow58);
		float 	fSlow60 = (fConst13 * fSlow58);
		float 	fSlow61 = (fConst14 * fSlow58);
		float 	fSlow62 = (fConst15 * fSlow58);
		float 	fSlow63 = (fConst8 * fSlow25);
		float 	fSlow64 = float(fslider18);
		float 	fSlow65 = (fConst12 * fSlow64);
		float 	fSlow66 = (fConst13 * fSlow64);
		float 	fSlow67 = (fConst14 * fSlow64);
		float 	fSlow68 = (fConst15 * fSlow64);
		float 	fSlow69 = (fConst8 * fSlow30);
		float 	fSlow70 = float(fslider19);
		float 	fSlow71 = (fConst12 * fSlow70);
		float 	fSlow72 = (fConst13 * fSlow70);
		float 	fSlow73 = (fConst14 * fSlow70);
		float 	fSlow74 = (fConst15 * fSlow70);
		float 	fSlow75 = (fConst8 * fSlow35);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fVec0[0] = fSlow5;
			iRec1[0] = (iSlow6 * (iRec1[1] + 1));
			iTempPerm0 = int((iRec1[0] < iSlow4));
			fTempPerm1 = expf((0 - (fConst1 / ((iSlow7)?((iTempPerm0)?fSlow3:fSlow1):fSlow0))));
			fRec0[0] = ((fRec0[1] * fTempPerm1) + (((iSlow7)?((iTempPerm0)?1.5873015873015872f:fSlow9):0.0f) * (1.0f - fTempPerm1)));
			fTempPerm2 = min(1.0f, fRec0[0]);
			fVec1[0] = fSlow11;
			iRec5[0] = (iSlow12 * (iRec5[1] + 1));
			iTempPerm3 = int((iRec5[0] < iSlow4));
			fTempPerm4 = expf((0 - (fConst1 / ((iSlow13)?((iTempPerm3)?fSlow3:fSlow1):fSlow0))));
			fRec4[0] = ((fRec4[1] * fTempPerm4) + (((iSlow13)?((iTempPerm3)?1.5873015873015872f:fSlow14):0.0f) * (1.0f - fTempPerm4)));
			fTempPerm5 = min(1.0f, fRec4[0]);
			fVec2[0] = fSlow16;
			iRec7[0] = (iSlow17 * (iRec7[1] + 1));
			iTempPerm6 = int((iRec7[0] < iSlow4));
			fTempPerm7 = expf((0 - (fConst1 / ((iSlow18)?((iTempPerm6)?fSlow3:fSlow1):fSlow0))));
			fRec6[0] = ((fRec6[1] * fTempPerm7) + (((iSlow18)?((iTempPerm6)?1.5873015873015872f:fSlow19):0.0f) * (1.0f - fTempPerm7)));
			fTempPerm8 = min(1.0f, fRec6[0]);
			fVec3[0] = fSlow21;
			iRec9[0] = (iSlow22 * (iRec9[1] + 1));
			iTempPerm9 = int((iRec9[0] < iSlow4));
			fTempPerm10 = expf((0 - (fConst1 / ((iSlow23)?((iTempPerm9)?fSlow3:fSlow1):fSlow0))));
			fRec8[0] = ((fRec8[1] * fTempPerm10) + (((iSlow23)?((iTempPerm9)?1.5873015873015872f:fSlow24):0.0f) * (1.0f - fTempPerm10)));
			fTempPerm11 = min(1.0f, fRec8[0]);
			fVec4[0] = fSlow26;
			iRec11[0] = (iSlow27 * (iRec11[1] + 1));
			iTempPerm12 = int((iRec11[0] < iSlow4));
			fTempPerm13 = expf((0 - (fConst1 / ((iSlow28)?((iTempPerm12)?fSlow3:fSlow1):fSlow0))));
			fRec10[0] = ((fRec10[1] * fTempPerm13) + (((iSlow28)?((iTempPerm12)?1.5873015873015872f:fSlow29):0.0f) * (1.0f - fTempPerm13)));
			fTempPerm14 = min(1.0f, fRec10[0]);
			fVec5[0] = fSlow31;
			iRec13[0] = (iSlow32 * (iRec13[1] + 1));
			iTempPerm15 = int((iRec13[0] < iSlow4));
			fTempPerm16 = expf((0 - (fConst1 / ((iSlow33)?((iTempPerm15)?fSlow3:fSlow1):fSlow0))));
			fRec12[0] = ((fRec12[1] * fTempPerm16) + (((iSlow33)?((iTempPerm15)?1.5873015873015872f:fSlow34):0.0f) * (1.0f - fTempPerm16)));
			fTempPerm17 = min(1.0f, fRec12[0]);
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec14[0] = (fSlow36 + (0.999f * fRec14[1]));
				fTempPerm18 = (fRec3[1] + (fConst9 * fRec14[1]));
				fRec3[0] = (fTempPerm18 - floorf(fTempPerm18));
				fbargraph0 = fRec3[0];
				fTempPerm19 = fbargraph0;
				iRec16[0] = ((1103515245 * iRec16[1]) + 12345);
				fRec15[0] = (((0.52218940000000003f * fRec15[3]) + ((4.6566128752457969e-10f * float(iRec16[0])) + (2.4949560019999999f * fRec15[1]))) - (2.0172658750000001f * fRec15[2]));
				fTempPerm20 = (((0.049922034999999997f * fRec15[0]) + (0.050612698999999997f * fRec15[2])) - ((0.095993537000000004f * fRec15[1]) + (0.0044087859999999996f * fRec15[3])));
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fTempPerm21 = (fSlow5 - fVec0[1]);
				fRec17[0] = ((int(((fTempPerm21 * float((fTempPerm21 > 0.0f))) > 0.0f)))?fConst10:max((float)0, (fRec17[1] + -1.0f)));
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fTempPerm23 = (fRec20[1] + (fConst11 * fRec14[0]));
				fRec20[0] = (fTempPerm23 - floorf(fTempPerm23));
				fTempPerm24 = (fRec14[0] * ftbl0[int((65536.0f * fRec20[0]))]);
				fTempPerm25 = ((0.02f * fTempPerm24) + 1.0f);
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fTempPerm26 = (fRec19[1] + (fSlow38 * fTempPerm25));
				fRec19[0] = (fTempPerm26 - floorf(fTempPerm26));
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec21[0] = (fSlow39 + (0.999f * fRec21[1]));
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fTempPerm27 = (fRec22[1] + (fSlow40 * fTempPerm25));
				fRec22[0] = (fTempPerm27 - floorf(fTempPerm27));
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec23[0] = (fSlow41 + (0.999f * fRec23[1]));
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec24[0] = (fSlow42 + (fRec24[1] - floorf((fSlow42 + fRec24[1]))));
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec25[0] = (fSlow43 + (0.999f * fRec25[1]));
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fTempPerm28 = (fRec26[1] + (fSlow44 * fTempPerm25));
				fRec26[0] = (fTempPerm28 - floorf(fTempPerm28));
				fRec2[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec26[0]))] + (fRec25[0] * ftbl0[int((65536.0f * fRec24[0]))])) + (fRec23[0] * ftbl0[int((65536.0f * fRec22[0]))])) + (fRec21[0] * ftbl0[int((65536.0f * fRec19[0]))])) + (fConst9 * ((fRec14[0] * fRec17[0]) * fTempPerm20)))) - (fConst8 * ((fConst7 * fRec2[2]) + (fConst5 * fRec2[1]))));
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fTempPerm29 = ((0.5f * fTempPerm24) + 1.0f);
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fTempPerm30 = (fSlow45 * (fTempPerm2 * ((fTempPerm29 * (fRec2[2] + (fRec2[0] + (2.0f * fRec2[1])))) + (((fConst4 * fRec2[0]) + (fConst16 * fRec2[1])) + (fConst4 * fRec2[2])))));
			}
			if ((float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f)) {
				fTempPerm31 = (fSlow11 - fVec1[1]);
				fRec28[0] = ((int(((fTempPerm31 * float((fTempPerm31 > 0.0f))) > 0.0f)))?fConst10:max((float)0, (fRec28[1] + -1.0f)));
				fTempPerm32 = (fRec29[1] + (fSlow47 * fTempPerm25));
				fRec29[0] = (fTempPerm32 - floorf(fTempPerm32));
				fTempPerm33 = (fRec30[1] + (fSlow48 * fTempPerm25));
				fRec30[0] = (fTempPerm33 - floorf(fTempPerm33));
				fRec31[0] = (fSlow49 + (fRec31[1] - floorf((fSlow49 + fRec31[1]))));
				fTempPerm34 = (fRec32[1] + (fSlow50 * fTempPerm25));
				fRec32[0] = (fTempPerm34 - floorf(fTempPerm34));
				fRec27[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec32[0]))] + (fRec25[0] * ftbl0[int((65536.0f * fRec31[0]))])) + (fRec23[0] * ftbl0[int((65536.0f * fRec30[0]))])) + (fRec21[0] * ftbl0[int((65536.0f * fRec29[0]))])) + (fConst9 * ((fRec14[0] * fRec28[0]) * fTempPerm20)))) - (fConst8 * ((fConst7 * fRec27[2]) + (fConst5 * fRec27[1]))));
				fTempPerm35 = (fSlow51 * (fTempPerm5 * ((fTempPerm29 * (fRec27[2] + (fRec27[0] + (2.0f * fRec27[1])))) + (((fConst4 * fRec27[0]) + (fConst16 * fRec27[1])) + (fConst4 * fRec27[2])))));
			}
			if ((float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f)) {
				fTempPerm36 = (fSlow16 - fVec2[1]);
				fRec34[0] = ((int(((fTempPerm36 * float((fTempPerm36 > 0.0f))) > 0.0f)))?fConst10:max((float)0, (fRec34[1] + -1.0f)));
				fTempPerm37 = (fRec35[1] + (fSlow53 * fTempPerm25));
				fRec35[0] = (fTempPerm37 - floorf(fTempPerm37));
				fTempPerm38 = (fRec36[1] + (fSlow54 * fTempPerm25));
				fRec36[0] = (fTempPerm38 - floorf(fTempPerm38));
				fRec37[0] = (fSlow55 + (fRec37[1] - floorf((fSlow55 + fRec37[1]))));
				fTempPerm39 = (fRec38[1] + (fSlow56 * fTempPerm25));
				fRec38[0] = (fTempPerm39 - floorf(fTempPerm39));
				fRec33[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec38[0]))] + (fRec25[0] * ftbl0[int((65536.0f * fRec37[0]))])) + (fRec23[0] * ftbl0[int((65536.0f * fRec36[0]))])) + (fRec21[0] * ftbl0[int((65536.0f * fRec35[0]))])) + (fConst9 * ((fRec14[0] * fRec34[0]) * fTempPerm20)))) - (fConst8 * ((fConst7 * fRec33[2]) + (fConst5 * fRec33[1]))));
				fTempPerm40 = (fSlow57 * (fTempPerm8 * ((fTempPerm29 * (fRec33[2] + (fRec33[0] + (2.0f * fRec33[1])))) + (((fConst4 * fRec33[0]) + (fConst16 * fRec33[1])) + (fConst4 * fRec33[2])))));
			}
			if ((float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f)) {
				fTempPerm41 = (fSlow21 - fVec3[1]);
				fRec40[0] = ((int(((fTempPerm41 * float((fTempPerm41 > 0.0f))) > 0.0f)))?fConst10:max((float)0, (fRec40[1] + -1.0f)));
				fTempPerm42 = (fRec41[1] + (fSlow59 * fTempPerm25));
				fRec41[0] = (fTempPerm42 - floorf(fTempPerm42));
				fTempPerm43 = (fRec42[1] + (fSlow60 * fTempPerm25));
				fRec42[0] = (fTempPerm43 - floorf(fTempPerm43));
				fRec43[0] = (fSlow61 + (fRec43[1] - floorf((fSlow61 + fRec43[1]))));
				fTempPerm44 = (fRec44[1] + (fSlow62 * fTempPerm25));
				fRec44[0] = (fTempPerm44 - floorf(fTempPerm44));
				fRec39[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec44[0]))] + (fRec25[0] * ftbl0[int((65536.0f * fRec43[0]))])) + (fRec23[0] * ftbl0[int((65536.0f * fRec42[0]))])) + (fRec21[0] * ftbl0[int((65536.0f * fRec41[0]))])) + (fConst9 * ((fRec14[0] * fRec40[0]) * fTempPerm20)))) - (fConst8 * ((fConst7 * fRec39[2]) + (fConst5 * fRec39[1]))));
				fTempPerm45 = (fSlow63 * (fTempPerm11 * ((fTempPerm29 * (fRec39[2] + (fRec39[0] + (2.0f * fRec39[1])))) + (((fConst4 * fRec39[0]) + (fConst16 * fRec39[1])) + (fConst4 * fRec39[2])))));
			}
			if ((float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f)) {
				fTempPerm46 = (fSlow26 - fVec4[1]);
				fRec46[0] = ((int(((fTempPerm46 * float((fTempPerm46 > 0.0f))) > 0.0f)))?fConst10:max((float)0, (fRec46[1] + -1.0f)));
				fTempPerm47 = (fRec47[1] + (fSlow65 * fTempPerm25));
				fRec47[0] = (fTempPerm47 - floorf(fTempPerm47));
				fTempPerm48 = (fRec48[1] + (fSlow66 * fTempPerm25));
				fRec48[0] = (fTempPerm48 - floorf(fTempPerm48));
				fRec49[0] = (fSlow67 + (fRec49[1] - floorf((fSlow67 + fRec49[1]))));
				fTempPerm49 = (fRec50[1] + (fSlow68 * fTempPerm25));
				fRec50[0] = (fTempPerm49 - floorf(fTempPerm49));
				fRec45[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec50[0]))] + (fRec25[0] * ftbl0[int((65536.0f * fRec49[0]))])) + (fRec23[0] * ftbl0[int((65536.0f * fRec48[0]))])) + (fRec21[0] * ftbl0[int((65536.0f * fRec47[0]))])) + (fConst9 * ((fRec14[0] * fRec46[0]) * fTempPerm20)))) - (fConst8 * ((fConst7 * fRec45[2]) + (fConst5 * fRec45[1]))));
				fTempPerm50 = (fSlow69 * (fTempPerm14 * ((fTempPerm29 * (fRec45[2] + (fRec45[0] + (2.0f * fRec45[1])))) + (((fConst4 * fRec45[0]) + (fConst16 * fRec45[1])) + (fConst4 * fRec45[2])))));
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f)) {
				fTempPerm51 = (fSlow31 - fVec5[1]);
				fRec52[0] = ((int(((fTempPerm51 * float((fTempPerm51 > 0.0f))) > 0.0f)))?fConst10:max((float)0, (fRec52[1] + -1.0f)));
				fTempPerm52 = (fRec53[1] + (fSlow71 * fTempPerm25));
				fRec53[0] = (fTempPerm52 - floorf(fTempPerm52));
				fTempPerm53 = (fRec54[1] + (fSlow72 * fTempPerm25));
				fRec54[0] = (fTempPerm53 - floorf(fTempPerm53));
				fRec55[0] = (fSlow73 + (fRec55[1] - floorf((fSlow73 + fRec55[1]))));
				fTempPerm54 = (fRec56[1] + (fSlow74 * fTempPerm25));
				fRec56[0] = (fTempPerm54 - floorf(fTempPerm54));
				fRec51[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec56[0]))] + (fRec25[0] * ftbl0[int((65536.0f * fRec55[0]))])) + (fRec23[0] * ftbl0[int((65536.0f * fRec54[0]))])) + (fRec21[0] * ftbl0[int((65536.0f * fRec53[0]))])) + (fConst9 * ((fRec14[0] * fRec52[0]) * fTempPerm20)))) - (fConst8 * ((fConst7 * fRec51[2]) + (fConst5 * fRec51[1]))));
				fTempPerm55 = (fSlow75 * (fTempPerm17 * (((fRec51[2] + (fRec51[0] + (2.0f * fRec51[1]))) * fTempPerm29) + (((fConst4 * fRec51[0]) + (fConst16 * fRec51[1])) + (fConst4 * fRec51[2])))));
			}
			output0[i] = (FAUSTFLOAT)(((((fTempPerm55 + fTempPerm50) + fTempPerm45) + fTempPerm40) + fTempPerm35) + fTempPerm30);
			// post processing
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f)) {
				fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
				fRec56[1] = fRec56[0];
				fRec55[1] = fRec55[0];
				fRec54[1] = fRec54[0];
				fRec53[1] = fRec53[0];
				fRec52[1] = fRec52[0];
			}
			if ((float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f)) {
				fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
				fRec50[1] = fRec50[0];
				fRec49[1] = fRec49[0];
				fRec48[1] = fRec48[0];
				fRec47[1] = fRec47[0];
				fRec46[1] = fRec46[0];
			}
			if ((float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f)) {
				fRec39[2] = fRec39[1]; fRec39[1] = fRec39[0];
				fRec44[1] = fRec44[0];
				fRec43[1] = fRec43[0];
				fRec42[1] = fRec42[0];
				fRec41[1] = fRec41[0];
				fRec40[1] = fRec40[0];
			}
			if ((float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f)) {
				fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
				fRec38[1] = fRec38[0];
				fRec37[1] = fRec37[0];
				fRec36[1] = fRec36[0];
				fRec35[1] = fRec35[0];
				fRec34[1] = fRec34[0];
			}
			if ((float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f)) {
				fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
				fRec32[1] = fRec32[0];
				fRec31[1] = fRec31[0];
				fRec30[1] = fRec30[0];
				fRec29[1] = fRec29[0];
				fRec28[1] = fRec28[0];
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
				fRec26[1] = fRec26[0];
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec25[1] = fRec25[0];
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec24[1] = fRec24[0];
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec23[1] = fRec23[0];
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec22[1] = fRec22[0];
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec21[1] = fRec21[0];
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec19[1] = fRec19[0];
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec20[1] = fRec20[0];
			}
			if ((float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fRec17[1] = fRec17[0];
			}
			if ((float(((fSlow35 * fTempPerm17) > 0.001f)) != 0.0f) || (float(((fSlow30 * fTempPerm14) > 0.001f)) != 0.0f) || (float(((fSlow25 * fTempPerm11) > 0.001f)) != 0.0f) || (float(((fSlow20 * fTempPerm8) > 0.001f)) != 0.0f) || (float(((fSlow15 * fTempPerm5) > 0.001f)) != 0.0f) || (float(((fSlow10 * fTempPerm2) > 0.001f)) != 0.0f)) {
				for (int i=3; i>0; i--) fRec15[i] = fRec15[i-1];
				iRec16[1] = iRec16[0];
				fRec3[1] = fRec3[0];
				fRec14[1] = fRec14[0];
			}
			fRec12[1] = fRec12[0];
			iRec13[1] = iRec13[0];
			fVec5[1] = fVec5[0];
			fRec10[1] = fRec10[0];
			iRec11[1] = iRec11[0];
			fVec4[1] = fVec4[0];
			fRec8[1] = fRec8[0];
			iRec9[1] = iRec9[0];
			fVec3[1] = fVec3[0];
			fRec6[1] = fRec6[0];
			iRec7[1] = iRec7[0];
			fVec2[1] = fVec2[0];
			fRec4[1] = fRec4[0];
			iRec5[1] = iRec5[0];
			fVec1[1] = fVec1[0];
			fRec0[1] = fRec0[0];
			iRec1[1] = iRec1[0];
			fVec0[1] = fVec0[0];
		}
	}
};


float 	faust_hammond::ftbl0[65536];
