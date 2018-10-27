//----------------------------------------------------------
// name: "hammond"
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
#define FAUSTCLASS faust_hammond
#endif

class faust_hammond : public dsp {
  private:
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec5[2];
		float 	fTempPerm1;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm1 = 0;
			for (int i=0; i<2; i++) iRec5[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec5[0] = (iRec5[1] + 1);
				fTempPerm1 = sinf((9.5873799242852573e-05f * float((iRec5[0] + -1))));
				output[i] = fTempPerm1;
				// post processing
				iRec5[1] = iRec5[0];
			}
		}
	};


	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	int 	iRec2[2];
	float 	fRec1[4];
	float 	fTempPerm0;
	float 	fConst8;
	FAUSTFLOAT 	fbutton0;
	float 	fVec0[2];
	float 	fRec3[2];
	FAUSTFLOAT 	fslider0;
	float 	fRec4[2];
	float 	fConst9;
	static float 	ftbl0[65536];
	float 	fConst10;
	float 	fTempPerm2;
	float 	fRec7[2];
	float 	fTempPerm3;
	float 	fTempPerm4;
	FAUSTFLOAT 	fslider1;
	float 	fConst11;
	float 	fTempPerm5;
	float 	fRec6[2];
	FAUSTFLOAT 	fslider2;
	float 	fRec8[2];
	float 	fConst12;
	float 	fTempPerm6;
	float 	fRec9[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec10[2];
	float 	fConst13;
	float 	fRec11[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec12[2];
	float 	fConst14;
	float 	fTempPerm7;
	float 	fRec13[2];
	float 	fRec0[3];
	float 	fConst15;
	float 	fTempPerm8;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	int 	iRec15[2];
	int 	iTempPerm9;
	float 	fConst16;
	float 	fTempPerm10;
	FAUSTFLOAT 	fslider8;
	float 	fRec14[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fbutton1;
	float 	fVec1[2];
	float 	fRec17[2];
	FAUSTFLOAT 	fslider10;
	float 	fTempPerm11;
	float 	fRec18[2];
	float 	fTempPerm12;
	float 	fRec19[2];
	float 	fRec20[2];
	float 	fTempPerm13;
	float 	fRec21[2];
	float 	fRec16[3];
	int 	iRec23[2];
	int 	iTempPerm14;
	float 	fTempPerm15;
	float 	fRec22[2];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fbutton2;
	float 	fVec2[2];
	float 	fRec25[2];
	FAUSTFLOAT 	fslider12;
	float 	fTempPerm16;
	float 	fRec26[2];
	float 	fTempPerm17;
	float 	fRec27[2];
	float 	fRec28[2];
	float 	fTempPerm18;
	float 	fRec29[2];
	float 	fRec24[3];
	int 	iRec31[2];
	int 	iTempPerm19;
	float 	fTempPerm20;
	float 	fRec30[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fbutton3;
	float 	fVec3[2];
	float 	fRec33[2];
	FAUSTFLOAT 	fslider14;
	float 	fTempPerm21;
	float 	fRec34[2];
	float 	fTempPerm22;
	float 	fRec35[2];
	float 	fRec36[2];
	float 	fTempPerm23;
	float 	fRec37[2];
	float 	fRec32[3];
	int 	iRec39[2];
	int 	iTempPerm24;
	float 	fTempPerm25;
	float 	fRec38[2];
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fbutton4;
	float 	fVec4[2];
	float 	fRec41[2];
	FAUSTFLOAT 	fslider16;
	float 	fTempPerm26;
	float 	fRec42[2];
	float 	fTempPerm27;
	float 	fRec43[2];
	float 	fRec44[2];
	float 	fTempPerm28;
	float 	fRec45[2];
	float 	fRec40[3];
	int 	iRec47[2];
	int 	iTempPerm29;
	float 	fTempPerm30;
	float 	fRec46[2];
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fbutton5;
	float 	fVec5[2];
	float 	fRec49[2];
	FAUSTFLOAT 	fslider18;
	float 	fTempPerm31;
	float 	fRec50[2];
	float 	fTempPerm32;
	float 	fRec51[2];
	float 	fRec52[2];
	float 	fTempPerm33;
	float 	fRec53[2];
	float 	fRec48[3];
	int 	iRec55[2];
	int 	iTempPerm34;
	float 	fTempPerm35;
	float 	fRec54[2];
	FAUSTFLOAT 	fslider19;
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
		fConst1 = tanf((5654.8667764616275f / fConst0));
		fConst2 = faustpower<2>(fConst1);
		fConst3 = (1.0f / fConst2);
		fConst4 = (2.0f * (1.0f - fConst3));
		fConst5 = (1.0f / fConst1);
		fConst6 = (((fConst5 + -1.4142135623730949f) / fConst1) + 1.0f);
		fConst7 = (1.0f / (((fConst5 + 1.4142135623730949f) / fConst1) + 1.0f));
		fTempPerm0 = 0;
		fConst8 = (0.02f * fConst0);
		fConst9 = (2.5f / fConst0);
		fConst10 = (10.0f / fConst0);
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fConst11 = (2.0f / fConst0);
		fTempPerm5 = 0;
		fConst12 = (1.3348398539999999f / fConst0);
		fTempPerm6 = 0;
		fConst13 = (0.5f / fConst0);
		fConst14 = (1.0f / fConst0);
		fTempPerm7 = 0;
		fConst15 = (0 - (2.0f / fConst2));
		fTempPerm8 = 0;
		iTempPerm9 = 0;
		fConst16 = (6.9100000000000001f / fConst0);
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		iTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		iTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		iTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		iTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		iTempPerm34 = 0;
		fTempPerm35 = 0;
	}
	virtual void instanceResetUserInterface() {
		fbutton0 = 0.0;
		fslider0 = 0.5f;
		fslider1 = 440.0f;
		fslider2 = 0.5f;
		fslider3 = 0.5f;
		fslider4 = 0.5f;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		fslider7 = 0.001f;
		fslider8 = 1.0f;
		fslider9 = 1.0f;
		fbutton1 = 0.0;
		fslider10 = 440.0f;
		fslider11 = 1.0f;
		fbutton2 = 0.0;
		fslider12 = 440.0f;
		fslider13 = 1.0f;
		fbutton3 = 0.0;
		fslider14 = 440.0f;
		fslider15 = 1.0f;
		fbutton4 = 0.0;
		fslider16 = 440.0f;
		fslider17 = 1.0f;
		fbutton5 = 0.0;
		fslider18 = 440.0f;
		fslider19 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec2[i] = 0;
		for (int i=0; i<4; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) iRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<3; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) iRec23[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<3; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) iRec31[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<3; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) iRec39[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<3; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) iRec47[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<3; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) iRec55[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
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
		ui_interface->addHorizontalSlider("drawbar1", &fslider4, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("drawbar2", &fslider3, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("drawbar3", &fslider2, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fslider7, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider6, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider5, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider8, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("leslie", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider18, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider19, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider14, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider15, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider10, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider11, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider16, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider17, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider12, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider13, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider1, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider9, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fbutton0);
		float 	fSlow1 = (0.0010000000000000009f * float(fslider0));
		float 	fSlow2 = float(fslider1);
		float 	fSlow3 = (fConst11 * fSlow2);
		float 	fSlow4 = (0.0010000000000000009f * float(fslider2));
		float 	fSlow5 = (fConst12 * fSlow2);
		float 	fSlow6 = (0.0010000000000000009f * float(fslider3));
		float 	fSlow7 = (fConst13 * fSlow2);
		float 	fSlow8 = (0.0010000000000000009f * float(fslider4));
		float 	fSlow9 = (fConst14 * fSlow2);
		float 	fSlow10 = float(fslider5);
		float 	fSlow11 = float(fslider6);
		float 	fSlow12 = float(fslider7);
		float 	fSlow13 = (6.9100000000000001f * fSlow12);
		int 	iSlow14 = int((fConst0 * fSlow12));
		int 	iSlow15 = (fSlow0 > 0.0f);
		int 	iSlow16 = int(iSlow15);
		float 	fSlow17 = float(fslider8);
		float 	fSlow18 = (float(iSlow15) * fSlow17);
		float 	fSlow19 = float(fslider9);
		float 	fSlow20 = float(fbutton1);
		float 	fSlow21 = float(fslider10);
		float 	fSlow22 = (fConst11 * fSlow21);
		float 	fSlow23 = (fConst12 * fSlow21);
		float 	fSlow24 = (fConst13 * fSlow21);
		float 	fSlow25 = (fConst14 * fSlow21);
		int 	iSlow26 = (fSlow20 > 0.0f);
		int 	iSlow27 = int(iSlow26);
		float 	fSlow28 = (float(iSlow26) * fSlow17);
		float 	fSlow29 = float(fslider11);
		float 	fSlow30 = float(fbutton2);
		float 	fSlow31 = float(fslider12);
		float 	fSlow32 = (fConst11 * fSlow31);
		float 	fSlow33 = (fConst12 * fSlow31);
		float 	fSlow34 = (fConst13 * fSlow31);
		float 	fSlow35 = (fConst14 * fSlow31);
		int 	iSlow36 = (fSlow30 > 0.0f);
		int 	iSlow37 = int(iSlow36);
		float 	fSlow38 = (float(iSlow36) * fSlow17);
		float 	fSlow39 = float(fslider13);
		float 	fSlow40 = float(fbutton3);
		float 	fSlow41 = float(fslider14);
		float 	fSlow42 = (fConst11 * fSlow41);
		float 	fSlow43 = (fConst12 * fSlow41);
		float 	fSlow44 = (fConst13 * fSlow41);
		float 	fSlow45 = (fConst14 * fSlow41);
		int 	iSlow46 = (fSlow40 > 0.0f);
		int 	iSlow47 = int(iSlow46);
		float 	fSlow48 = (float(iSlow46) * fSlow17);
		float 	fSlow49 = float(fslider15);
		float 	fSlow50 = float(fbutton4);
		float 	fSlow51 = float(fslider16);
		float 	fSlow52 = (fConst11 * fSlow51);
		float 	fSlow53 = (fConst12 * fSlow51);
		float 	fSlow54 = (fConst13 * fSlow51);
		float 	fSlow55 = (fConst14 * fSlow51);
		int 	iSlow56 = (fSlow50 > 0.0f);
		int 	iSlow57 = int(iSlow56);
		float 	fSlow58 = (float(iSlow56) * fSlow17);
		float 	fSlow59 = float(fslider17);
		float 	fSlow60 = float(fbutton5);
		float 	fSlow61 = float(fslider18);
		float 	fSlow62 = (fConst11 * fSlow61);
		float 	fSlow63 = (fConst12 * fSlow61);
		float 	fSlow64 = (fConst13 * fSlow61);
		float 	fSlow65 = (fConst14 * fSlow61);
		int 	iSlow66 = (fSlow60 > 0.0f);
		int 	iSlow67 = int(iSlow66);
		float 	fSlow68 = (float(iSlow66) * fSlow17);
		float 	fSlow69 = float(fslider19);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec2[0] = ((1103515245 * iRec2[1]) + 12345);
			fRec1[0] = (((0.52218940000000003f * fRec1[3]) + ((4.6566128752457969e-10f * float(iRec2[0])) + (2.4949560019999999f * fRec1[1]))) - (2.0172658750000001f * fRec1[2]));
			fTempPerm0 = (((0.049922034999999997f * fRec1[0]) + (0.050612698999999997f * fRec1[2])) - ((0.095993537000000004f * fRec1[1]) + (0.0044087859999999996f * fRec1[3])));
			fVec0[0] = fSlow0;
			fRec3[0] = ((int((((fSlow0 - fVec0[1]) > 0.0f) > 0)))?fConst8:max((float)0, (fRec3[1] + -1.0f)));
			fRec4[0] = (fSlow1 + (0.999f * fRec4[1]));
			fTempPerm2 = (fRec7[1] + (fConst10 * fRec4[0]));
			fRec7[0] = (fTempPerm2 - floorf(fTempPerm2));
			fTempPerm3 = (fRec4[0] * ftbl0[int((65536.0f * fRec7[0]))]);
			fTempPerm4 = ((0.02f * fTempPerm3) + 1.0f);
			fTempPerm5 = (fRec6[1] + (fSlow3 * fTempPerm4));
			fRec6[0] = (fTempPerm5 - floorf(fTempPerm5));
			fRec8[0] = (fSlow4 + (0.999f * fRec8[1]));
			fTempPerm6 = (fRec9[1] + (fSlow5 * fTempPerm4));
			fRec9[0] = (fTempPerm6 - floorf(fTempPerm6));
			fRec10[0] = (fSlow6 + (0.999f * fRec10[1]));
			fRec11[0] = (fSlow7 + (fRec11[1] - floorf((fSlow7 + fRec11[1]))));
			fRec12[0] = (fSlow8 + (0.999f * fRec12[1]));
			fTempPerm7 = (fRec13[1] + (fSlow9 * fTempPerm4));
			fRec13[0] = (fTempPerm7 - floorf(fTempPerm7));
			fRec0[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec13[0]))] + (fRec12[0] * ftbl0[int((65536.0f * fRec11[0]))])) + (fRec10[0] * ftbl0[int((65536.0f * fRec9[0]))])) + (fRec8[0] * ftbl0[int((65536.0f * fRec6[0]))])) + (fConst9 * ((fRec4[0] * fRec3[0]) * fTempPerm0)))) - (fConst7 * ((fConst6 * fRec0[2]) + (fConst4 * fRec0[1]))));
			fTempPerm8 = ((0.5f * fTempPerm3) + 1.0f);
			iRec15[0] = (iSlow15 * (iRec15[1] + 1));
			iTempPerm9 = int((iRec15[0] < iSlow14));
			fTempPerm10 = expf((0 - (fConst16 / ((iSlow16)?((iTempPerm9)?fSlow13:fSlow11):fSlow10))));
			fRec14[0] = ((fRec14[1] * fTempPerm10) + (((iSlow16)?((iTempPerm9)?1.5873015873015872f:fSlow18):0.0f) * (1.0f - fTempPerm10)));
			fVec1[0] = fSlow20;
			fRec17[0] = ((int((((fSlow20 - fVec1[1]) > 0.0f) > 0)))?fConst8:max((float)0, (fRec17[1] + -1.0f)));
			fTempPerm11 = (fRec18[1] + (fSlow22 * fTempPerm4));
			fRec18[0] = (fTempPerm11 - floorf(fTempPerm11));
			fTempPerm12 = (fRec19[1] + (fSlow23 * fTempPerm4));
			fRec19[0] = (fTempPerm12 - floorf(fTempPerm12));
			fRec20[0] = (fSlow24 + (fRec20[1] - floorf((fSlow24 + fRec20[1]))));
			fTempPerm13 = (fRec21[1] + (fSlow25 * fTempPerm4));
			fRec21[0] = (fTempPerm13 - floorf(fTempPerm13));
			fRec16[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec21[0]))] + (fRec12[0] * ftbl0[int((65536.0f * fRec20[0]))])) + (fRec10[0] * ftbl0[int((65536.0f * fRec19[0]))])) + (fRec8[0] * ftbl0[int((65536.0f * fRec18[0]))])) + (fConst9 * ((fRec4[0] * fRec17[0]) * fTempPerm0)))) - (fConst7 * ((fConst6 * fRec16[2]) + (fConst4 * fRec16[1]))));
			iRec23[0] = (iSlow26 * (iRec23[1] + 1));
			iTempPerm14 = int((iRec23[0] < iSlow14));
			fTempPerm15 = expf((0 - (fConst16 / ((iSlow27)?((iTempPerm14)?fSlow13:fSlow11):fSlow10))));
			fRec22[0] = ((fRec22[1] * fTempPerm15) + (((iSlow27)?((iTempPerm14)?1.5873015873015872f:fSlow28):0.0f) * (1.0f - fTempPerm15)));
			fVec2[0] = fSlow30;
			fRec25[0] = ((int((((fSlow30 - fVec2[1]) > 0.0f) > 0)))?fConst8:max((float)0, (fRec25[1] + -1.0f)));
			fTempPerm16 = (fRec26[1] + (fSlow32 * fTempPerm4));
			fRec26[0] = (fTempPerm16 - floorf(fTempPerm16));
			fTempPerm17 = (fRec27[1] + (fSlow33 * fTempPerm4));
			fRec27[0] = (fTempPerm17 - floorf(fTempPerm17));
			fRec28[0] = (fSlow34 + (fRec28[1] - floorf((fSlow34 + fRec28[1]))));
			fTempPerm18 = (fRec29[1] + (fSlow35 * fTempPerm4));
			fRec29[0] = (fTempPerm18 - floorf(fTempPerm18));
			fRec24[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec29[0]))] + (fRec12[0] * ftbl0[int((65536.0f * fRec28[0]))])) + (fRec10[0] * ftbl0[int((65536.0f * fRec27[0]))])) + (fRec8[0] * ftbl0[int((65536.0f * fRec26[0]))])) + (fConst9 * ((fRec4[0] * fRec25[0]) * fTempPerm0)))) - (fConst7 * ((fConst6 * fRec24[2]) + (fConst4 * fRec24[1]))));
			iRec31[0] = (iSlow36 * (iRec31[1] + 1));
			iTempPerm19 = int((iRec31[0] < iSlow14));
			fTempPerm20 = expf((0 - (fConst16 / ((iSlow37)?((iTempPerm19)?fSlow13:fSlow11):fSlow10))));
			fRec30[0] = ((fRec30[1] * fTempPerm20) + (((iSlow37)?((iTempPerm19)?1.5873015873015872f:fSlow38):0.0f) * (1.0f - fTempPerm20)));
			fVec3[0] = fSlow40;
			fRec33[0] = ((int((((fSlow40 - fVec3[1]) > 0.0f) > 0)))?fConst8:max((float)0, (fRec33[1] + -1.0f)));
			fTempPerm21 = (fRec34[1] + (fSlow42 * fTempPerm4));
			fRec34[0] = (fTempPerm21 - floorf(fTempPerm21));
			fTempPerm22 = (fRec35[1] + (fSlow43 * fTempPerm4));
			fRec35[0] = (fTempPerm22 - floorf(fTempPerm22));
			fRec36[0] = (fSlow44 + (fRec36[1] - floorf((fSlow44 + fRec36[1]))));
			fTempPerm23 = (fRec37[1] + (fSlow45 * fTempPerm4));
			fRec37[0] = (fTempPerm23 - floorf(fTempPerm23));
			fRec32[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec37[0]))] + (fRec12[0] * ftbl0[int((65536.0f * fRec36[0]))])) + (fRec10[0] * ftbl0[int((65536.0f * fRec35[0]))])) + (fRec8[0] * ftbl0[int((65536.0f * fRec34[0]))])) + (fConst9 * ((fRec4[0] * fRec33[0]) * fTempPerm0)))) - (fConst7 * ((fConst6 * fRec32[2]) + (fConst4 * fRec32[1]))));
			iRec39[0] = (iSlow46 * (iRec39[1] + 1));
			iTempPerm24 = int((iRec39[0] < iSlow14));
			fTempPerm25 = expf((0 - (fConst16 / ((iSlow47)?((iTempPerm24)?fSlow13:fSlow11):fSlow10))));
			fRec38[0] = ((fRec38[1] * fTempPerm25) + (((iSlow47)?((iTempPerm24)?1.5873015873015872f:fSlow48):0.0f) * (1.0f - fTempPerm25)));
			fVec4[0] = fSlow50;
			fRec41[0] = ((int((((fSlow50 - fVec4[1]) > 0.0f) > 0)))?fConst8:max((float)0, (fRec41[1] + -1.0f)));
			fTempPerm26 = (fRec42[1] + (fSlow52 * fTempPerm4));
			fRec42[0] = (fTempPerm26 - floorf(fTempPerm26));
			fTempPerm27 = (fRec43[1] + (fSlow53 * fTempPerm4));
			fRec43[0] = (fTempPerm27 - floorf(fTempPerm27));
			fRec44[0] = (fSlow54 + (fRec44[1] - floorf((fSlow54 + fRec44[1]))));
			fTempPerm28 = (fRec45[1] + (fSlow55 * fTempPerm4));
			fRec45[0] = (fTempPerm28 - floorf(fTempPerm28));
			fRec40[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec45[0]))] + (fRec12[0] * ftbl0[int((65536.0f * fRec44[0]))])) + (fRec10[0] * ftbl0[int((65536.0f * fRec43[0]))])) + (fRec8[0] * ftbl0[int((65536.0f * fRec42[0]))])) + (fConst9 * ((fRec4[0] * fRec41[0]) * fTempPerm0)))) - (fConst7 * ((fConst6 * fRec40[2]) + (fConst4 * fRec40[1]))));
			iRec47[0] = (iSlow56 * (iRec47[1] + 1));
			iTempPerm29 = int((iRec47[0] < iSlow14));
			fTempPerm30 = expf((0 - (fConst16 / ((iSlow57)?((iTempPerm29)?fSlow13:fSlow11):fSlow10))));
			fRec46[0] = ((fRec46[1] * fTempPerm30) + (((iSlow57)?((iTempPerm29)?1.5873015873015872f:fSlow58):0.0f) * (1.0f - fTempPerm30)));
			fVec5[0] = fSlow60;
			fRec49[0] = ((int((((fSlow60 - fVec5[1]) > 0.0f) > 0)))?fConst8:max((float)0, (fRec49[1] + -1.0f)));
			fTempPerm31 = (fRec50[1] + (fSlow62 * fTempPerm4));
			fRec50[0] = (fTempPerm31 - floorf(fTempPerm31));
			fTempPerm32 = (fRec51[1] + (fSlow63 * fTempPerm4));
			fRec51[0] = (fTempPerm32 - floorf(fTempPerm32));
			fRec52[0] = (fSlow64 + (fRec52[1] - floorf((fSlow64 + fRec52[1]))));
			fTempPerm33 = (fRec53[1] + (fSlow65 * fTempPerm4));
			fRec53[0] = (fTempPerm33 - floorf(fTempPerm33));
			fRec48[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec53[0]))] + (fRec12[0] * ftbl0[int((65536.0f * fRec52[0]))])) + (fRec10[0] * ftbl0[int((65536.0f * fRec51[0]))])) + (fRec8[0] * ftbl0[int((65536.0f * fRec50[0]))])) + (fConst9 * ((fRec4[0] * fRec49[0]) * fTempPerm0)))) - (fConst7 * ((fConst6 * fRec48[2]) + (fConst4 * fRec48[1]))));
			iRec55[0] = (iSlow66 * (iRec55[1] + 1));
			iTempPerm34 = int((iRec55[0] < iSlow14));
			fTempPerm35 = expf((0 - (fConst16 / ((iSlow67)?((iTempPerm34)?fSlow13:fSlow11):fSlow10))));
			fRec54[0] = ((fRec54[1] * fTempPerm35) + (((iSlow67)?((iTempPerm34)?1.5873015873015872f:fSlow68):0.0f) * (1.0f - fTempPerm35)));
			output0[i] = (FAUSTFLOAT)(fConst7 * ((((((fSlow69 * (min(1.0f, fRec54[0]) * (((fRec48[2] + (fRec48[0] + (2.0f * fRec48[1]))) * fTempPerm8) + (((fConst3 * fRec48[0]) + (fConst15 * fRec48[1])) + (fConst3 * fRec48[2]))))) + (fSlow59 * (min(1.0f, fRec46[0]) * ((fTempPerm8 * (fRec40[2] + (fRec40[0] + (2.0f * fRec40[1])))) + (((fConst3 * fRec40[0]) + (fConst15 * fRec40[1])) + (fConst3 * fRec40[2])))))) + (fSlow49 * (min(1.0f, fRec38[0]) * ((fTempPerm8 * (fRec32[2] + (fRec32[0] + (2.0f * fRec32[1])))) + (((fConst3 * fRec32[0]) + (fConst15 * fRec32[1])) + (fConst3 * fRec32[2])))))) + (fSlow39 * (min(1.0f, fRec30[0]) * ((fTempPerm8 * (fRec24[2] + (fRec24[0] + (2.0f * fRec24[1])))) + (((fConst3 * fRec24[0]) + (fConst15 * fRec24[1])) + (fConst3 * fRec24[2])))))) + (fSlow29 * (min(1.0f, fRec22[0]) * ((fTempPerm8 * (fRec16[2] + (fRec16[0] + (2.0f * fRec16[1])))) + (((fConst3 * fRec16[0]) + (fConst15 * fRec16[1])) + (fConst3 * fRec16[2])))))) + (fSlow19 * (min(1.0f, fRec14[0]) * ((fTempPerm8 * (fRec0[2] + (fRec0[0] + (2.0f * fRec0[1])))) + (((fConst3 * fRec0[0]) + (fConst15 * fRec0[1])) + (fConst3 * fRec0[2])))))));
			// post processing
			fRec54[1] = fRec54[0];
			iRec55[1] = iRec55[0];
			fRec48[2] = fRec48[1]; fRec48[1] = fRec48[0];
			fRec53[1] = fRec53[0];
			fRec52[1] = fRec52[0];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
			fRec49[1] = fRec49[0];
			fVec5[1] = fVec5[0];
			fRec46[1] = fRec46[0];
			iRec47[1] = iRec47[0];
			fRec40[2] = fRec40[1]; fRec40[1] = fRec40[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec41[1] = fRec41[0];
			fVec4[1] = fVec4[0];
			fRec38[1] = fRec38[0];
			iRec39[1] = iRec39[0];
			fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			fVec3[1] = fVec3[0];
			fRec30[1] = fRec30[0];
			iRec31[1] = iRec31[0];
			fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fVec2[1] = fVec2[0];
			fRec22[1] = fRec22[0];
			iRec23[1] = iRec23[0];
			fRec16[2] = fRec16[1]; fRec16[1] = fRec16[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fVec1[1] = fVec1[0];
			fRec14[1] = fRec14[0];
			iRec15[1] = iRec15[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fVec0[1] = fVec0[0];
			for (int i=3; i>0; i--) fRec1[i] = fRec1[i-1];
			iRec2[1] = iRec2[0];
		}
	}
};


float 	faust_hammond::ftbl0[65536];
