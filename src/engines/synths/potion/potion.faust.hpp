//----------------------------------------------------------
// name: "potion"
//
// Code generated with Faust 2.13.11 (https://faust.grame.fr)
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
#define FAUSTCLASS faust_potion
#endif

class faust_potion : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fConst0;
	FAUSTFLOAT 	fbutton0;
	int 	iRec1[2];
	int 	iTempPerm0;
	float 	fConst1;
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider3;
	float 	fRec0[2];
	float 	fTempPerm2;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	float 	fTempPerm3;
	FAUSTFLOAT 	fbutton1;
	int 	iRec3[2];
	int 	iTempPerm4;
	float 	fTempPerm5;
	float 	fRec2[2];
	float 	fTempPerm6;
	FAUSTFLOAT 	fslider6;
	float 	fTempPerm7;
	FAUSTFLOAT 	fbutton2;
	int 	iRec5[2];
	int 	iTempPerm8;
	float 	fTempPerm9;
	float 	fRec4[2];
	float 	fTempPerm10;
	FAUSTFLOAT 	fslider7;
	float 	fTempPerm11;
	FAUSTFLOAT 	fbutton3;
	int 	iRec7[2];
	int 	iTempPerm12;
	float 	fTempPerm13;
	float 	fRec6[2];
	float 	fTempPerm14;
	FAUSTFLOAT 	fslider8;
	float 	fTempPerm15;
	FAUSTFLOAT 	fbutton4;
	int 	iRec9[2];
	int 	iTempPerm16;
	float 	fTempPerm17;
	float 	fRec8[2];
	float 	fTempPerm18;
	FAUSTFLOAT 	fslider9;
	float 	fTempPerm19;
	FAUSTFLOAT 	fbutton5;
	int 	iRec11[2];
	int 	iTempPerm20;
	float 	fTempPerm21;
	float 	fRec10[2];
	float 	fTempPerm22;
	FAUSTFLOAT 	fslider10;
	float 	fTempPerm23;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "potion");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "potion");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		iTempPerm0 = 0;
		fConst1 = (6.9100000000000001f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		iTempPerm4 = 0;
		fTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		iTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		iTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		iTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		iTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 0.001f;
		fbutton0 = 0.0;
		fslider3 = 1.0f;
		fslider4 = 1.0f;
		fslider5 = 1.0f;
		fbutton1 = 0.0;
		fslider6 = 1.0f;
		fbutton2 = 0.0;
		fslider7 = 1.0f;
		fbutton3 = 0.0;
		fslider8 = 1.0f;
		fbutton4 = 0.0;
		fslider9 = 1.0f;
		fbutton5 = 0.0;
		fslider10 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) iRec3[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) iRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) iRec7[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) iRec9[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) iRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
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
	virtual faust_potion* clone() {
		return new faust_potion();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("potion");
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fslider2, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider1, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider0, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider3, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("osc1/volume", &fslider5, 1.0f, 0.0f, 1.0f, 0.10000000000000001f);
		ui_interface->openVerticalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider10, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider9, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider8, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider7, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider6, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
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
		int 	iSlow5 = (float(fbutton0) > 0.0f);
		int 	iSlow6 = int(iSlow5);
		float 	fSlow7 = float(fslider3);
		float 	fSlow8 = (float(iSlow5) * fSlow7);
		float 	fSlow9 = float(fslider4);
		float 	fSlow10 = float(fslider5);
		float 	fSlow11 = (fSlow9 * fSlow10);
		int 	iSlow12 = (float(fbutton1) > 0.0f);
		int 	iSlow13 = int(iSlow12);
		float 	fSlow14 = (float(iSlow12) * fSlow7);
		float 	fSlow15 = float(fslider6);
		float 	fSlow16 = (fSlow10 * fSlow15);
		int 	iSlow17 = (float(fbutton2) > 0.0f);
		int 	iSlow18 = int(iSlow17);
		float 	fSlow19 = (float(iSlow17) * fSlow7);
		float 	fSlow20 = float(fslider7);
		float 	fSlow21 = (fSlow10 * fSlow20);
		int 	iSlow22 = (float(fbutton3) > 0.0f);
		int 	iSlow23 = int(iSlow22);
		float 	fSlow24 = (float(iSlow22) * fSlow7);
		float 	fSlow25 = float(fslider8);
		float 	fSlow26 = (fSlow10 * fSlow25);
		int 	iSlow27 = (float(fbutton4) > 0.0f);
		int 	iSlow28 = int(iSlow27);
		float 	fSlow29 = (float(iSlow27) * fSlow7);
		float 	fSlow30 = float(fslider9);
		float 	fSlow31 = (fSlow10 * fSlow30);
		int 	iSlow32 = (float(fbutton5) > 0.0f);
		int 	iSlow33 = int(iSlow32);
		float 	fSlow34 = (float(iSlow32) * fSlow7);
		float 	fSlow35 = float(fslider10);
		float 	fSlow36 = (fSlow10 * fSlow35);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec1[0] = (iSlow5 * (iRec1[1] + 1));
			iTempPerm0 = int((iRec1[0] < iSlow4));
			fTempPerm1 = expf((0 - (fConst1 / ((iSlow6)?((iTempPerm0)?fSlow3:fSlow1):fSlow0))));
			fRec0[0] = ((fRec0[1] * fTempPerm1) + (((iSlow6)?((iTempPerm0)?1.5873015873015872f:fSlow8):0.0f) * (1.0f - fTempPerm1)));
			fTempPerm2 = min(1.0f, fRec0[0]);
			if ((float(((fSlow9 * fTempPerm2) > 0.001f)) != 0.0f)) {
				fTempPerm3 = (fSlow11 * fTempPerm2);
			}
			iRec3[0] = (iSlow12 * (iRec3[1] + 1));
			iTempPerm4 = int((iRec3[0] < iSlow4));
			fTempPerm5 = expf((0 - (fConst1 / ((iSlow13)?((iTempPerm4)?fSlow3:fSlow1):fSlow0))));
			fRec2[0] = ((fRec2[1] * fTempPerm5) + (((iSlow13)?((iTempPerm4)?1.5873015873015872f:fSlow14):0.0f) * (1.0f - fTempPerm5)));
			fTempPerm6 = min(1.0f, fRec2[0]);
			if ((float(((fSlow15 * fTempPerm6) > 0.001f)) != 0.0f)) {
				fTempPerm7 = (fSlow16 * fTempPerm6);
			}
			iRec5[0] = (iSlow17 * (iRec5[1] + 1));
			iTempPerm8 = int((iRec5[0] < iSlow4));
			fTempPerm9 = expf((0 - (fConst1 / ((iSlow18)?((iTempPerm8)?fSlow3:fSlow1):fSlow0))));
			fRec4[0] = ((fRec4[1] * fTempPerm9) + (((iSlow18)?((iTempPerm8)?1.5873015873015872f:fSlow19):0.0f) * (1.0f - fTempPerm9)));
			fTempPerm10 = min(1.0f, fRec4[0]);
			if ((float(((fSlow20 * fTempPerm10) > 0.001f)) != 0.0f)) {
				fTempPerm11 = (fSlow21 * fTempPerm10);
			}
			iRec7[0] = (iSlow22 * (iRec7[1] + 1));
			iTempPerm12 = int((iRec7[0] < iSlow4));
			fTempPerm13 = expf((0 - (fConst1 / ((iSlow23)?((iTempPerm12)?fSlow3:fSlow1):fSlow0))));
			fRec6[0] = ((fRec6[1] * fTempPerm13) + (((iSlow23)?((iTempPerm12)?1.5873015873015872f:fSlow24):0.0f) * (1.0f - fTempPerm13)));
			fTempPerm14 = min(1.0f, fRec6[0]);
			if ((float(((fSlow25 * fTempPerm14) > 0.001f)) != 0.0f)) {
				fTempPerm15 = (fSlow26 * fTempPerm14);
			}
			iRec9[0] = (iSlow27 * (iRec9[1] + 1));
			iTempPerm16 = int((iRec9[0] < iSlow4));
			fTempPerm17 = expf((0 - (fConst1 / ((iSlow28)?((iTempPerm16)?fSlow3:fSlow1):fSlow0))));
			fRec8[0] = ((fRec8[1] * fTempPerm17) + (((iSlow28)?((iTempPerm16)?1.5873015873015872f:fSlow29):0.0f) * (1.0f - fTempPerm17)));
			fTempPerm18 = min(1.0f, fRec8[0]);
			if ((float(((fSlow30 * fTempPerm18) > 0.001f)) != 0.0f)) {
				fTempPerm19 = (fSlow31 * fTempPerm18);
			}
			iRec11[0] = (iSlow32 * (iRec11[1] + 1));
			iTempPerm20 = int((iRec11[0] < iSlow4));
			fTempPerm21 = expf((0 - (fConst1 / ((iSlow33)?((iTempPerm20)?fSlow3:fSlow1):fSlow0))));
			fRec10[0] = ((fRec10[1] * fTempPerm21) + (((iSlow33)?((iTempPerm20)?1.5873015873015872f:fSlow34):0.0f) * (1.0f - fTempPerm21)));
			fTempPerm22 = min(1.0f, fRec10[0]);
			if ((float(((fSlow35 * fTempPerm22) > 0.001f)) != 0.0f)) {
				fTempPerm23 = (fSlow36 * fTempPerm22);
			}
			output0[i] = (FAUSTFLOAT)(((((fTempPerm23 + fTempPerm19) + fTempPerm15) + fTempPerm11) + fTempPerm7) + fTempPerm3);
			// post processing
			fRec10[1] = fRec10[0];
			iRec11[1] = iRec11[0];
			fRec8[1] = fRec8[0];
			iRec9[1] = iRec9[0];
			fRec6[1] = fRec6[0];
			iRec7[1] = iRec7[0];
			fRec4[1] = fRec4[0];
			iRec5[1] = iRec5[0];
			fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
			fRec0[1] = fRec0[0];
			iRec1[1] = iRec1[0];
		}
	}
};


