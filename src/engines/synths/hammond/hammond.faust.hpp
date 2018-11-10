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
		int 	iRec6[2];
		float 	fTempPerm3;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm3 = 0;
			for (int i=0; i<2; i++) iRec6[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec6[0] = (iRec6[1] + 1);
				fTempPerm3 = sinf((9.5873799242852573e-05f * float((iRec6[0] + -1))));
				output[i] = fTempPerm3;
				// post processing
				iRec6[1] = iRec6[0];
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
	FAUSTFLOAT 	fslider0;
	float 	fRec2[2];
	float 	fConst8;
	float 	fTempPerm0;
	float 	fRec1[2];
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm1;
	int 	iRec4[2];
	float 	fRec3[4];
	float 	fTempPerm2;
	float 	fConst9;
	FAUSTFLOAT 	fbutton0;
	float 	fVec0[2];
	float 	fRec5[2];
	float 	fConst10;
	static float 	ftbl0[65536];
	float 	fConst11;
	float 	fTempPerm4;
	float 	fRec8[2];
	float 	fTempPerm5;
	float 	fTempPerm6;
	FAUSTFLOAT 	fslider1;
	float 	fConst12;
	float 	fTempPerm7;
	float 	fRec7[2];
	FAUSTFLOAT 	fslider2;
	float 	fRec9[2];
	float 	fConst13;
	float 	fTempPerm8;
	float 	fRec10[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec11[2];
	float 	fConst14;
	float 	fRec12[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec13[2];
	float 	fConst15;
	float 	fTempPerm9;
	float 	fRec14[2];
	float 	fRec0[3];
	float 	fConst16;
	float 	fTempPerm10;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	int 	iRec16[2];
	int 	iTempPerm11;
	float 	fConst17;
	float 	fTempPerm12;
	FAUSTFLOAT 	fslider8;
	float 	fRec15[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fbutton1;
	float 	fVec1[2];
	float 	fRec18[2];
	FAUSTFLOAT 	fslider10;
	float 	fTempPerm13;
	float 	fRec19[2];
	float 	fTempPerm14;
	float 	fRec20[2];
	float 	fRec21[2];
	float 	fTempPerm15;
	float 	fRec22[2];
	float 	fRec17[3];
	int 	iRec24[2];
	int 	iTempPerm16;
	float 	fTempPerm17;
	float 	fRec23[2];
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fbutton2;
	float 	fVec2[2];
	float 	fRec26[2];
	FAUSTFLOAT 	fslider12;
	float 	fTempPerm18;
	float 	fRec27[2];
	float 	fTempPerm19;
	float 	fRec28[2];
	float 	fRec29[2];
	float 	fTempPerm20;
	float 	fRec30[2];
	float 	fRec25[3];
	int 	iRec32[2];
	int 	iTempPerm21;
	float 	fTempPerm22;
	float 	fRec31[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fbutton3;
	float 	fVec3[2];
	float 	fRec34[2];
	FAUSTFLOAT 	fslider14;
	float 	fTempPerm23;
	float 	fRec35[2];
	float 	fTempPerm24;
	float 	fRec36[2];
	float 	fRec37[2];
	float 	fTempPerm25;
	float 	fRec38[2];
	float 	fRec33[3];
	int 	iRec40[2];
	int 	iTempPerm26;
	float 	fTempPerm27;
	float 	fRec39[2];
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fbutton4;
	float 	fVec4[2];
	float 	fRec42[2];
	FAUSTFLOAT 	fslider16;
	float 	fTempPerm28;
	float 	fRec43[2];
	float 	fTempPerm29;
	float 	fRec44[2];
	float 	fRec45[2];
	float 	fTempPerm30;
	float 	fRec46[2];
	float 	fRec41[3];
	int 	iRec48[2];
	int 	iTempPerm31;
	float 	fTempPerm32;
	float 	fRec47[2];
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fbutton5;
	float 	fVec5[2];
	float 	fRec50[2];
	FAUSTFLOAT 	fslider18;
	float 	fTempPerm33;
	float 	fRec51[2];
	float 	fTempPerm34;
	float 	fRec52[2];
	float 	fRec53[2];
	float 	fTempPerm35;
	float 	fRec54[2];
	float 	fRec49[3];
	int 	iRec56[2];
	int 	iTempPerm36;
	float 	fTempPerm37;
	float 	fRec55[2];
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
		fConst8 = (5.0f / fConst0);
		fTempPerm0 = 0;
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fConst9 = (0.02f * fConst0);
		fConst10 = (2.5f / fConst0);
		fConst11 = (10.0f / fConst0);
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fConst12 = (2.0f / fConst0);
		fTempPerm7 = 0;
		fConst13 = (1.3348398539999999f / fConst0);
		fTempPerm8 = 0;
		fConst14 = (0.5f / fConst0);
		fConst15 = (1.0f / fConst0);
		fTempPerm9 = 0;
		fConst16 = (0 - (2.0f / fConst2));
		fTempPerm10 = 0;
		iTempPerm11 = 0;
		fConst17 = (6.9100000000000001f / fConst0);
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		iTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		iTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		iTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		iTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		iTempPerm36 = 0;
		fTempPerm37 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fbutton0 = 0.0;
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
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) iRec4[i] = 0;
		for (int i=0; i<4; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) iRec16[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<3; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) iRec24[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<3; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) iRec32[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<3; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) iRec40[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<3; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) iRec48[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<3; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) iRec56[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
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
		ui_interface->addHorizontalBargraph("phasor", &fbargraph0, 0.0f, 1.0f);
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
		float 	fSlow0 = (0.0010000000000000009f * float(fslider0));
		float 	fSlow1 = float(fbutton0);
		float 	fSlow2 = float(fslider1);
		float 	fSlow3 = (fConst12 * fSlow2);
		float 	fSlow4 = (0.0010000000000000009f * float(fslider2));
		float 	fSlow5 = (fConst13 * fSlow2);
		float 	fSlow6 = (0.0010000000000000009f * float(fslider3));
		float 	fSlow7 = (fConst14 * fSlow2);
		float 	fSlow8 = (0.0010000000000000009f * float(fslider4));
		float 	fSlow9 = (fConst15 * fSlow2);
		float 	fSlow10 = float(fslider5);
		float 	fSlow11 = float(fslider6);
		float 	fSlow12 = float(fslider7);
		float 	fSlow13 = (6.9100000000000001f * fSlow12);
		int 	iSlow14 = int((fConst0 * fSlow12));
		int 	iSlow15 = (fSlow1 > 0.0f);
		int 	iSlow16 = int(iSlow15);
		float 	fSlow17 = float(fslider8);
		float 	fSlow18 = (float(iSlow15) * fSlow17);
		float 	fSlow19 = float(fslider9);
		float 	fSlow20 = float(fbutton1);
		float 	fSlow21 = float(fslider10);
		float 	fSlow22 = (fConst12 * fSlow21);
		float 	fSlow23 = (fConst13 * fSlow21);
		float 	fSlow24 = (fConst14 * fSlow21);
		float 	fSlow25 = (fConst15 * fSlow21);
		int 	iSlow26 = (fSlow20 > 0.0f);
		int 	iSlow27 = int(iSlow26);
		float 	fSlow28 = (float(iSlow26) * fSlow17);
		float 	fSlow29 = float(fslider11);
		float 	fSlow30 = float(fbutton2);
		float 	fSlow31 = float(fslider12);
		float 	fSlow32 = (fConst12 * fSlow31);
		float 	fSlow33 = (fConst13 * fSlow31);
		float 	fSlow34 = (fConst14 * fSlow31);
		float 	fSlow35 = (fConst15 * fSlow31);
		int 	iSlow36 = (fSlow30 > 0.0f);
		int 	iSlow37 = int(iSlow36);
		float 	fSlow38 = (float(iSlow36) * fSlow17);
		float 	fSlow39 = float(fslider13);
		float 	fSlow40 = float(fbutton3);
		float 	fSlow41 = float(fslider14);
		float 	fSlow42 = (fConst12 * fSlow41);
		float 	fSlow43 = (fConst13 * fSlow41);
		float 	fSlow44 = (fConst14 * fSlow41);
		float 	fSlow45 = (fConst15 * fSlow41);
		int 	iSlow46 = (fSlow40 > 0.0f);
		int 	iSlow47 = int(iSlow46);
		float 	fSlow48 = (float(iSlow46) * fSlow17);
		float 	fSlow49 = float(fslider15);
		float 	fSlow50 = float(fbutton4);
		float 	fSlow51 = float(fslider16);
		float 	fSlow52 = (fConst12 * fSlow51);
		float 	fSlow53 = (fConst13 * fSlow51);
		float 	fSlow54 = (fConst14 * fSlow51);
		float 	fSlow55 = (fConst15 * fSlow51);
		int 	iSlow56 = (fSlow50 > 0.0f);
		int 	iSlow57 = int(iSlow56);
		float 	fSlow58 = (float(iSlow56) * fSlow17);
		float 	fSlow59 = float(fslider17);
		float 	fSlow60 = float(fbutton5);
		float 	fSlow61 = float(fslider18);
		float 	fSlow62 = (fConst12 * fSlow61);
		float 	fSlow63 = (fConst13 * fSlow61);
		float 	fSlow64 = (fConst14 * fSlow61);
		float 	fSlow65 = (fConst15 * fSlow61);
		int 	iSlow66 = (fSlow60 > 0.0f);
		int 	iSlow67 = int(iSlow66);
		float 	fSlow68 = (float(iSlow66) * fSlow17);
		float 	fSlow69 = float(fslider19);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			fRec2[0] = (fSlow0 + (0.999f * fRec2[1]));
			fTempPerm0 = (fRec1[1] + (fConst8 * fRec2[1]));
			fRec1[0] = (fTempPerm0 - floorf(fTempPerm0));
			fbargraph0 = fRec1[0];
			fTempPerm1 = fbargraph0;
			iRec4[0] = ((1103515245 * iRec4[1]) + 12345);
			fRec3[0] = (((0.52218940000000003f * fRec3[3]) + ((4.6566128752457969e-10f * float(iRec4[0])) + (2.4949560019999999f * fRec3[1]))) - (2.0172658750000001f * fRec3[2]));
			fTempPerm2 = (((0.049922034999999997f * fRec3[0]) + (0.050612698999999997f * fRec3[2])) - ((0.095993537000000004f * fRec3[1]) + (0.0044087859999999996f * fRec3[3])));
			fVec0[0] = fSlow1;
			fRec5[0] = ((int((((fSlow1 - fVec0[1]) > 0.0f) > 0)))?fConst9:max((float)0, (fRec5[1] + -1.0f)));
			fTempPerm4 = (fRec8[1] + (fConst11 * fRec2[0]));
			fRec8[0] = (fTempPerm4 - floorf(fTempPerm4));
			fTempPerm5 = (fRec2[0] * ftbl0[int((65536.0f * fRec8[0]))]);
			fTempPerm6 = ((0.02f * fTempPerm5) + 1.0f);
			fTempPerm7 = (fRec7[1] + (fSlow3 * fTempPerm6));
			fRec7[0] = (fTempPerm7 - floorf(fTempPerm7));
			fRec9[0] = (fSlow4 + (0.999f * fRec9[1]));
			fTempPerm8 = (fRec10[1] + (fSlow5 * fTempPerm6));
			fRec10[0] = (fTempPerm8 - floorf(fTempPerm8));
			fRec11[0] = (fSlow6 + (0.999f * fRec11[1]));
			fRec12[0] = (fSlow7 + (fRec12[1] - floorf((fSlow7 + fRec12[1]))));
			fRec13[0] = (fSlow8 + (0.999f * fRec13[1]));
			fTempPerm9 = (fRec14[1] + (fSlow9 * fTempPerm6));
			fRec14[0] = (fTempPerm9 - floorf(fTempPerm9));
			fRec0[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec14[0]))] + (fRec13[0] * ftbl0[int((65536.0f * fRec12[0]))])) + (fRec11[0] * ftbl0[int((65536.0f * fRec10[0]))])) + (fRec9[0] * ftbl0[int((65536.0f * fRec7[0]))])) + (fConst10 * ((fRec2[0] * fRec5[0]) * fTempPerm2)))) - (fConst7 * ((fConst6 * fRec0[2]) + (fConst4 * fRec0[1]))));
			fTempPerm10 = ((0.5f * fTempPerm5) + 1.0f);
			iRec16[0] = (iSlow15 * (iRec16[1] + 1));
			iTempPerm11 = int((iRec16[0] < iSlow14));
			fTempPerm12 = expf((0 - (fConst17 / ((iSlow16)?((iTempPerm11)?fSlow13:fSlow11):fSlow10))));
			fRec15[0] = ((fRec15[1] * fTempPerm12) + (((iSlow16)?((iTempPerm11)?1.5873015873015872f:fSlow18):0.0f) * (1.0f - fTempPerm12)));
			fVec1[0] = fSlow20;
			fRec18[0] = ((int((((fSlow20 - fVec1[1]) > 0.0f) > 0)))?fConst9:max((float)0, (fRec18[1] + -1.0f)));
			fTempPerm13 = (fRec19[1] + (fSlow22 * fTempPerm6));
			fRec19[0] = (fTempPerm13 - floorf(fTempPerm13));
			fTempPerm14 = (fRec20[1] + (fSlow23 * fTempPerm6));
			fRec20[0] = (fTempPerm14 - floorf(fTempPerm14));
			fRec21[0] = (fSlow24 + (fRec21[1] - floorf((fSlow24 + fRec21[1]))));
			fTempPerm15 = (fRec22[1] + (fSlow25 * fTempPerm6));
			fRec22[0] = (fTempPerm15 - floorf(fTempPerm15));
			fRec17[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec22[0]))] + (fRec13[0] * ftbl0[int((65536.0f * fRec21[0]))])) + (fRec11[0] * ftbl0[int((65536.0f * fRec20[0]))])) + (fRec9[0] * ftbl0[int((65536.0f * fRec19[0]))])) + (fConst10 * ((fRec2[0] * fRec18[0]) * fTempPerm2)))) - (fConst7 * ((fConst6 * fRec17[2]) + (fConst4 * fRec17[1]))));
			iRec24[0] = (iSlow26 * (iRec24[1] + 1));
			iTempPerm16 = int((iRec24[0] < iSlow14));
			fTempPerm17 = expf((0 - (fConst17 / ((iSlow27)?((iTempPerm16)?fSlow13:fSlow11):fSlow10))));
			fRec23[0] = ((fRec23[1] * fTempPerm17) + (((iSlow27)?((iTempPerm16)?1.5873015873015872f:fSlow28):0.0f) * (1.0f - fTempPerm17)));
			fVec2[0] = fSlow30;
			fRec26[0] = ((int((((fSlow30 - fVec2[1]) > 0.0f) > 0)))?fConst9:max((float)0, (fRec26[1] + -1.0f)));
			fTempPerm18 = (fRec27[1] + (fSlow32 * fTempPerm6));
			fRec27[0] = (fTempPerm18 - floorf(fTempPerm18));
			fTempPerm19 = (fRec28[1] + (fSlow33 * fTempPerm6));
			fRec28[0] = (fTempPerm19 - floorf(fTempPerm19));
			fRec29[0] = (fSlow34 + (fRec29[1] - floorf((fSlow34 + fRec29[1]))));
			fTempPerm20 = (fRec30[1] + (fSlow35 * fTempPerm6));
			fRec30[0] = (fTempPerm20 - floorf(fTempPerm20));
			fRec25[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec30[0]))] + (fRec13[0] * ftbl0[int((65536.0f * fRec29[0]))])) + (fRec11[0] * ftbl0[int((65536.0f * fRec28[0]))])) + (fRec9[0] * ftbl0[int((65536.0f * fRec27[0]))])) + (fConst10 * ((fRec2[0] * fRec26[0]) * fTempPerm2)))) - (fConst7 * ((fConst6 * fRec25[2]) + (fConst4 * fRec25[1]))));
			iRec32[0] = (iSlow36 * (iRec32[1] + 1));
			iTempPerm21 = int((iRec32[0] < iSlow14));
			fTempPerm22 = expf((0 - (fConst17 / ((iSlow37)?((iTempPerm21)?fSlow13:fSlow11):fSlow10))));
			fRec31[0] = ((fRec31[1] * fTempPerm22) + (((iSlow37)?((iTempPerm21)?1.5873015873015872f:fSlow38):0.0f) * (1.0f - fTempPerm22)));
			fVec3[0] = fSlow40;
			fRec34[0] = ((int((((fSlow40 - fVec3[1]) > 0.0f) > 0)))?fConst9:max((float)0, (fRec34[1] + -1.0f)));
			fTempPerm23 = (fRec35[1] + (fSlow42 * fTempPerm6));
			fRec35[0] = (fTempPerm23 - floorf(fTempPerm23));
			fTempPerm24 = (fRec36[1] + (fSlow43 * fTempPerm6));
			fRec36[0] = (fTempPerm24 - floorf(fTempPerm24));
			fRec37[0] = (fSlow44 + (fRec37[1] - floorf((fSlow44 + fRec37[1]))));
			fTempPerm25 = (fRec38[1] + (fSlow45 * fTempPerm6));
			fRec38[0] = (fTempPerm25 - floorf(fTempPerm25));
			fRec33[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec38[0]))] + (fRec13[0] * ftbl0[int((65536.0f * fRec37[0]))])) + (fRec11[0] * ftbl0[int((65536.0f * fRec36[0]))])) + (fRec9[0] * ftbl0[int((65536.0f * fRec35[0]))])) + (fConst10 * ((fRec2[0] * fRec34[0]) * fTempPerm2)))) - (fConst7 * ((fConst6 * fRec33[2]) + (fConst4 * fRec33[1]))));
			iRec40[0] = (iSlow46 * (iRec40[1] + 1));
			iTempPerm26 = int((iRec40[0] < iSlow14));
			fTempPerm27 = expf((0 - (fConst17 / ((iSlow47)?((iTempPerm26)?fSlow13:fSlow11):fSlow10))));
			fRec39[0] = ((fRec39[1] * fTempPerm27) + (((iSlow47)?((iTempPerm26)?1.5873015873015872f:fSlow48):0.0f) * (1.0f - fTempPerm27)));
			fVec4[0] = fSlow50;
			fRec42[0] = ((int((((fSlow50 - fVec4[1]) > 0.0f) > 0)))?fConst9:max((float)0, (fRec42[1] + -1.0f)));
			fTempPerm28 = (fRec43[1] + (fSlow52 * fTempPerm6));
			fRec43[0] = (fTempPerm28 - floorf(fTempPerm28));
			fTempPerm29 = (fRec44[1] + (fSlow53 * fTempPerm6));
			fRec44[0] = (fTempPerm29 - floorf(fTempPerm29));
			fRec45[0] = (fSlow54 + (fRec45[1] - floorf((fSlow54 + fRec45[1]))));
			fTempPerm30 = (fRec46[1] + (fSlow55 * fTempPerm6));
			fRec46[0] = (fTempPerm30 - floorf(fTempPerm30));
			fRec41[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec46[0]))] + (fRec13[0] * ftbl0[int((65536.0f * fRec45[0]))])) + (fRec11[0] * ftbl0[int((65536.0f * fRec44[0]))])) + (fRec9[0] * ftbl0[int((65536.0f * fRec43[0]))])) + (fConst10 * ((fRec2[0] * fRec42[0]) * fTempPerm2)))) - (fConst7 * ((fConst6 * fRec41[2]) + (fConst4 * fRec41[1]))));
			iRec48[0] = (iSlow56 * (iRec48[1] + 1));
			iTempPerm31 = int((iRec48[0] < iSlow14));
			fTempPerm32 = expf((0 - (fConst17 / ((iSlow57)?((iTempPerm31)?fSlow13:fSlow11):fSlow10))));
			fRec47[0] = ((fRec47[1] * fTempPerm32) + (((iSlow57)?((iTempPerm31)?1.5873015873015872f:fSlow58):0.0f) * (1.0f - fTempPerm32)));
			fVec5[0] = fSlow60;
			fRec50[0] = ((int((((fSlow60 - fVec5[1]) > 0.0f) > 0)))?fConst9:max((float)0, (fRec50[1] + -1.0f)));
			fTempPerm33 = (fRec51[1] + (fSlow62 * fTempPerm6));
			fRec51[0] = (fTempPerm33 - floorf(fTempPerm33));
			fTempPerm34 = (fRec52[1] + (fSlow63 * fTempPerm6));
			fRec52[0] = (fTempPerm34 - floorf(fTempPerm34));
			fRec53[0] = (fSlow64 + (fRec53[1] - floorf((fSlow64 + fRec53[1]))));
			fTempPerm35 = (fRec54[1] + (fSlow65 * fTempPerm6));
			fRec54[0] = (fTempPerm35 - floorf(fTempPerm35));
			fRec49[0] = ((0.5f * ((((ftbl0[int((65536.0f * fRec54[0]))] + (fRec13[0] * ftbl0[int((65536.0f * fRec53[0]))])) + (fRec11[0] * ftbl0[int((65536.0f * fRec52[0]))])) + (fRec9[0] * ftbl0[int((65536.0f * fRec51[0]))])) + (fConst10 * ((fRec2[0] * fRec50[0]) * fTempPerm2)))) - (fConst7 * ((fConst6 * fRec49[2]) + (fConst4 * fRec49[1]))));
			iRec56[0] = (iSlow66 * (iRec56[1] + 1));
			iTempPerm36 = int((iRec56[0] < iSlow14));
			fTempPerm37 = expf((0 - (fConst17 / ((iSlow67)?((iTempPerm36)?fSlow13:fSlow11):fSlow10))));
			fRec55[0] = ((fRec55[1] * fTempPerm37) + (((iSlow67)?((iTempPerm36)?1.5873015873015872f:fSlow68):0.0f) * (1.0f - fTempPerm37)));
			output0[i] = (FAUSTFLOAT)(fConst7 * ((((((fSlow69 * (min(1.0f, fRec55[0]) * (((fRec49[2] + (fRec49[0] + (2.0f * fRec49[1]))) * fTempPerm10) + (((fConst3 * fRec49[0]) + (fConst16 * fRec49[1])) + (fConst3 * fRec49[2]))))) + (fSlow59 * (min(1.0f, fRec47[0]) * ((fTempPerm10 * (fRec41[2] + (fRec41[0] + (2.0f * fRec41[1])))) + (((fConst3 * fRec41[0]) + (fConst16 * fRec41[1])) + (fConst3 * fRec41[2])))))) + (fSlow49 * (min(1.0f, fRec39[0]) * ((fTempPerm10 * (fRec33[2] + (fRec33[0] + (2.0f * fRec33[1])))) + (((fConst3 * fRec33[0]) + (fConst16 * fRec33[1])) + (fConst3 * fRec33[2])))))) + (fSlow39 * (min(1.0f, fRec31[0]) * ((fTempPerm10 * (fRec25[2] + (fRec25[0] + (2.0f * fRec25[1])))) + (((fConst3 * fRec25[0]) + (fConst16 * fRec25[1])) + (fConst3 * fRec25[2])))))) + (fSlow29 * (min(1.0f, fRec23[0]) * ((fTempPerm10 * (fRec17[2] + (fRec17[0] + (2.0f * fRec17[1])))) + (((fConst3 * fRec17[0]) + (fConst16 * fRec17[1])) + (fConst3 * fRec17[2])))))) + (fSlow19 * (min(1.0f, fRec15[0]) * ((fTempPerm10 * (fRec0[2] + (fRec0[0] + (2.0f * fRec0[1])))) + (((fConst3 * fRec0[0]) + (fConst16 * fRec0[1])) + (fConst3 * fRec0[2])))))));
			// post processing
			fRec55[1] = fRec55[0];
			iRec56[1] = iRec56[0];
			fRec49[2] = fRec49[1]; fRec49[1] = fRec49[0];
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			fRec52[1] = fRec52[0];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
			fVec5[1] = fVec5[0];
			fRec47[1] = fRec47[0];
			iRec48[1] = iRec48[0];
			fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
			fRec46[1] = fRec46[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fVec4[1] = fVec4[0];
			fRec39[1] = fRec39[0];
			iRec40[1] = iRec40[0];
			fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fVec3[1] = fVec3[0];
			fRec31[1] = fRec31[0];
			iRec32[1] = iRec32[0];
			fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fVec2[1] = fVec2[0];
			fRec23[1] = fRec23[0];
			iRec24[1] = iRec24[0];
			fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fVec1[1] = fVec1[0];
			fRec15[1] = fRec15[0];
			iRec16[1] = iRec16[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec5[1] = fRec5[0];
			fVec0[1] = fVec0[0];
			for (int i=3; i>0; i--) fRec3[i] = fRec3[i-1];
			iRec4[1] = iRec4[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
		}
	}
};


float 	faust_hammond::ftbl0[65536];
