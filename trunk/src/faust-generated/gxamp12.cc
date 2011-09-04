namespace gxamp12 {
// generated from file '../src/faust/gxamp12.dsp'

double 	fConst0;
double 	fConst1;
double 	fConst2;
FAUSTFLOAT&	fslider0 = get_alias("amp2.stage2.gain1");
double 	fRec2[2];
double 	fConst3;
double 	fConst4;
double 	fConst5;
FAUSTFLOAT&	fslider1 = get_alias("gxdistortion.wet_dry");
double 	fRec4[2];
FAUSTFLOAT&	fslider2 = get_alias("amp2.stage1.Pregain");
double 	fRec12[2];
double 	fConst6;
double 	fConst7;
double 	fConst8;
double 	fVec0[2];
double 	fConst9;
double 	fRec13[2];
double 	fRec11[2];
double 	fConst10;
double 	fConst11;
double 	fRec10[2];
double 	fConst12;
double 	fRec9[2];
double 	fConst13;
double 	fConst14;
double 	fConst15;
double 	fVec1[2];
double 	fConst16;
double 	fRec14[2];
double 	fRec8[2];
double 	fRec7[2];
double 	fConst17;
double 	fConst18;
double 	fConst19;
double 	fVec2[2];
double 	fConst20;
double 	fRec15[2];
double 	fRec6[2];
double 	fRec5[2];
FAUSTFLOAT&	fslider3 = get_alias("gxdistortion.drive");
double 	fRec16[2];
double 	fConst21;
double 	fConst22;
double 	fConst23;
double 	fConst24;
double 	fConst25;
double 	fConst26;
double 	fConst27;
double 	fConst28;
double 	fConst29;
double 	fConst30;
double 	fConst31;
double 	fConst32;
double 	fConst33;
double 	fConst34;
double 	fConst35;
double 	fConst36;
double 	fConst37;
double 	fConst38;
double 	fConst39;
double 	fConst40;
double 	fConst41;
double 	fConst42;
double 	fConst43;
double 	fConst44;
double 	fConst45;
double 	fConst46;
double 	fConst47;
double 	fRec23[3];
double 	fVec3[2];
double 	fConst48;
double 	fRec22[2];
double 	fConst49;
double 	fConst50;
double 	fRec21[2];
double 	fRec20[3];
double 	fConst51;
double 	fRec19[3];
double 	fRec18[3];
double 	fConst52;
double 	fConst53;
double 	fConst54;
double 	fConst55;
double 	fConst56;
double 	fConst57;
double 	fConst58;
double 	fConst59;
double 	fConst60;
double 	fRec29[2];
double 	fRec28[3];
double 	fVec4[2];
double 	fConst61;
double 	fRec27[2];
double 	fRec26[3];
double 	fVec5[2];
double 	fConst62;
double 	fConst63;
double 	fRec25[2];
double 	fRec24[3];
double 	fConst64;
double 	fRec31[2];
double 	fRec30[3];
double 	fConst65;
double 	fRec34[2];
double 	fRec33[3];
double 	fConst66;
double 	fRec32[3];
double 	fVec6[2];
double 	fConst67;
double 	fRec17[2];
double 	fVec7[2];
double 	fRec3[2];
double 	fVec8[2];
double 	fConst68;
double 	fRec35[2];
double 	fRec1[2];
double 	fConst69;
double 	fRec0[2];
double 	fVec9[2];
double 	fRec38[2];
double 	fRec37[2];
double 	fRec36[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1.0 / tan((97.38937226128358 / fSamplingFreq)));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	for (int i=0; i<2; i++) fRec2[i] = 0;
	fConst3 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst4 = (1 + fConst3);
	fConst5 = (0 - ((1 - fConst3) / fConst4));
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	fConst6 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst7 = (1 + fConst6);
	fConst8 = (0 - ((1 - fConst6) / fConst7));
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst9 = (0.027 / fConst7);
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	fConst10 = (0 - fConst0);
	fConst11 = (0.05 / fConst1);
	for (int i=0; i<2; i++) fRec10[i] = 0;
	fConst12 = (1.0 / fConst4);
	for (int i=0; i<2; i++) fRec9[i] = 0;
	fConst13 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst14 = (1 + fConst13);
	fConst15 = (0 - ((1 - fConst13) / fConst14));
	for (int i=0; i<2; i++) fVec1[i] = 0;
	fConst16 = (0.015 / fConst14);
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	fConst17 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst18 = (1 + fConst17);
	fConst19 = (0 - ((1 - fConst17) / fConst18));
	for (int i=0; i<2; i++) fVec2[i] = 0;
	fConst20 = (0.0082 / fConst18);
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	fConst21 = tan((942.4777960769379 / fSamplingFreq));
	fConst22 = (1.0 / faustpower<2>(fConst21));
	fConst23 = (2 * (1 - fConst22));
	fConst24 = (1.0 / fConst21);
	fConst25 = (1 + ((fConst24 - 1.0) / fConst21));
	fConst26 = (1.0 / (1 + ((1.0 + fConst24) / fConst21)));
	fConst27 = tan((3769.9111843077517 / fSamplingFreq));
	fConst28 = (1.0 / faustpower<2>(fConst27));
	fConst29 = (2 * (1 - fConst28));
	fConst30 = (1.0 / fConst27);
	fConst31 = (1 + ((fConst30 - 1.0) / fConst27));
	fConst32 = (1.0 / (1 + ((1.0 + fConst30) / fConst27)));
	fConst33 = tan((10053.096491487338 / fSamplingFreq));
	fConst34 = (1.0 / faustpower<2>(fConst33));
	fConst35 = (2 * (1 - fConst34));
	fConst36 = (1.0 / fConst33);
	fConst37 = (1 + ((fConst36 - 1.0000000000000004) / fConst33));
	fConst38 = (1 + ((1.0000000000000004 + fConst36) / fConst33));
	fConst39 = (1.0 / fConst38);
	fConst40 = (1 + fConst36);
	fConst41 = (0 - ((1 - fConst36) / fConst40));
	fConst42 = tan((47123.8898038469 / fSamplingFreq));
	fConst43 = (2 * (1 - (1.0 / faustpower<2>(fConst42))));
	fConst44 = (1.0 / fConst42);
	fConst45 = (1 + ((fConst44 - 1.414213562373095) / fConst42));
	fConst46 = (1 + ((1.414213562373095 + fConst44) / fConst42));
	fConst47 = (1.0 / fConst46);
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	fConst48 = (1.0 / (fConst1 * fConst46));
	for (int i=0; i<2; i++) fRec22[i] = 0;
	fConst49 = (0 - fConst36);
	fConst50 = (1.0 / fConst40);
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	fConst51 = (2 * (0 - fConst34));
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	fConst52 = (1 + ((fConst24 - 1.0000000000000004) / fConst21));
	fConst53 = (1.0 / (1 + ((fConst24 + 1.0000000000000004) / fConst21)));
	fConst54 = (1 + fConst24);
	fConst55 = (0 - ((1 - fConst24) / fConst54));
	fConst56 = (1 + ((fConst30 - 1.0000000000000004) / fConst27));
	fConst57 = (1 + ((fConst30 + 1.0000000000000004) / fConst27));
	fConst58 = (1.0 / fConst57);
	fConst59 = (1 + fConst30);
	fConst60 = (0 - ((1 - fConst30) / fConst59));
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	fConst61 = (1.0 / (fConst59 * fConst38));
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	fConst62 = (0 - fConst24);
	fConst63 = (1.0 / (fConst54 * fConst57));
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	fConst64 = (2 * (0 - fConst22));
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	fConst65 = (0 - fConst30);
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	fConst66 = (2 * (0 - fConst28));
	for (int i=0; i<3; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	fConst67 = (1.5848931924611136 / fConst4);
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	fConst68 = (0.0082 / fConst4);
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	fConst69 = (0.025 / fConst1);
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * fslider0);
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (0.0010000000000000009 * (1 - (0.01 * fSlow1)));
	double 	fSlow3 = (0.0010000000000000009 * fslider2);
	double 	fSlow4 = fslider3;
	double 	fSlow5 = (1.25 * fSlow4);
	double 	fSlow6 = (1.000000000000001e-05 * fSlow1);
	double 	fSlow7 = (2 * (fSlow4 - 0.5));
	double 	fSlow8 = (1 - max(0, fSlow7));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow4));
	double 	fSlow10 = (fConst53 * pow(1e+01,(2 * fSlow4)));
	double 	fSlow11 = (fConst53 * pow(1e+01,(0.9 * fSlow4)));
	double 	fSlow12 = pow(1e+01,(1.2 * fSlow4));
	double 	fSlow13 = (1 - max(0, (0 - fSlow7)));
	for (int i=0; i<count; i++) {
		fRec2[0] = (fSlow0 + (0.999 * fRec2[1]));
		fRec4[0] = (fSlow2 + (0.999 * fRec4[1]));
		fRec12[0] = (fSlow3 + (0.999 * fRec12[1]));
		double fTemp0 = (fRec11[1] - 1.3e+02);
		fVec0[0] = fTemp0;
		fRec13[0] = ((fConst9 * (fVec0[0] + fVec0[1])) + (fConst8 * fRec13[1]));
		fRec11[0] = Ftube4(0, (fRec13[0] + ((double)input0[i] * pow(10,(0.05 * fRec12[0])))));
		fRec10[0] = ((fConst11 * ((fConst10 * fRec11[1]) + (fConst0 * fRec11[0]))) + (fConst2 * fRec10[1]));
		fRec9[0] = ((fConst12 * (fRec10[0] + fRec10[1])) + (fConst5 * fRec9[1]));
		double fTemp1 = (fRec8[1] - 1.3e+02);
		fVec1[0] = fTemp1;
		fRec14[0] = ((fConst16 * (fVec1[0] + fVec1[1])) + (fConst15 * fRec14[1]));
		fRec8[0] = Ftube4(1, (fRec14[0] + fRec9[0]));
		fRec7[0] = ((fConst11 * ((fConst10 * fRec8[1]) + (fConst0 * fRec8[0]))) + (fConst2 * fRec7[1]));
		double fTemp2 = (fRec6[1] - 1.3e+02);
		fVec2[0] = fTemp2;
		fRec15[0] = ((fConst20 * (fVec2[0] + fVec2[1])) + (fConst19 * fRec15[1]));
		fRec6[0] = Ftube4(1, (fRec15[0] + fRec7[0]));
		fRec5[0] = ((fConst11 * ((fConst10 * fRec6[1]) + (fConst0 * fRec6[0]))) + (fConst2 * fRec5[1]));
		fRec16[0] = (fSlow6 + (0.999 * fRec16[1]));
		double fTemp3 = (fConst23 * fRec18[1]);
		double fTemp4 = (fConst29 * fRec19[1]);
		fRec23[0] = ((fRec5[0] * fRec16[0]) - (fConst47 * ((fConst45 * fRec23[2]) + (fConst43 * fRec23[1]))));
		double fTemp5 = (fRec23[2] + (fRec23[0] + (2 * fRec23[1])));
		fVec3[0] = fTemp5;
		fRec22[0] = ((fConst48 * ((fConst10 * fVec3[1]) + (fConst0 * fVec3[0]))) + (fConst2 * fRec22[1]));
		fRec21[0] = ((fConst50 * ((fConst49 * fRec22[1]) + (fConst36 * fRec22[0]))) + (fConst41 * fRec21[1]));
		fRec20[0] = (fRec21[0] - (fConst39 * ((fConst37 * fRec20[2]) + (fConst35 * fRec20[1]))));
		fRec19[0] = ((fConst39 * (((fConst34 * fRec20[0]) + (fConst51 * fRec20[1])) + (fConst34 * fRec20[2]))) - (fConst32 * ((fConst31 * fRec19[2]) + fTemp4)));
		fRec18[0] = ((fRec19[2] + (fConst32 * (fTemp4 + (fConst31 * fRec19[0])))) - (fConst26 * ((fConst25 * fRec18[2]) + fTemp3)));
		double fTemp6 = max(-1, min(1, (fSlow9 * (fRec18[2] + (fConst26 * (fTemp3 + (fConst25 * fRec18[0])))))));
		fRec29[0] = ((fConst50 * (fRec22[0] + fRec22[1])) + (fConst41 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fConst39 * ((fConst37 * fRec28[2]) + (fConst35 * fRec28[1]))));
		double fTemp7 = (fRec28[2] + (fRec28[0] + (2 * fRec28[1])));
		fVec4[0] = fTemp7;
		fRec27[0] = ((fConst61 * (fVec4[0] + fVec4[1])) + (fConst60 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst58 * ((fConst56 * fRec26[2]) + (fConst29 * fRec26[1]))));
		double fTemp8 = (fRec26[2] + (fRec26[0] + (2 * fRec26[1])));
		fVec5[0] = fTemp8;
		fRec25[0] = ((fConst63 * ((fConst62 * fVec5[1]) + (fConst24 * fVec5[0]))) + (fConst55 * fRec25[1]));
		fRec24[0] = (fRec25[0] - (fConst53 * ((fConst52 * fRec24[2]) + (fConst23 * fRec24[1]))));
		double fTemp9 = max(-1, min(1, (fSlow10 * (((fConst22 * fRec24[0]) + (fConst64 * fRec24[1])) + (fConst22 * fRec24[2])))));
		fRec31[0] = ((fConst63 * (fVec5[0] + fVec5[1])) + (fConst55 * fRec31[1]));
		fRec30[0] = (fRec31[0] - (fConst53 * ((fConst52 * fRec30[2]) + (fConst23 * fRec30[1]))));
		double fTemp10 = max(-1, min(1, (fSlow11 * (fRec30[2] + (fRec30[0] + (2 * fRec30[1]))))));
		double fTemp11 = (fConst23 * fRec32[1]);
		fRec34[0] = ((fConst61 * ((fConst65 * fVec4[1]) + (fConst30 * fVec4[0]))) + (fConst60 * fRec34[1]));
		fRec33[0] = (fRec34[0] - (fConst58 * ((fConst56 * fRec33[2]) + (fConst29 * fRec33[1]))));
		fRec32[0] = ((fConst58 * (((fConst28 * fRec33[0]) + (fConst66 * fRec33[1])) + (fConst28 * fRec33[2]))) - (fConst26 * ((fConst25 * fRec32[2]) + fTemp11)));
		double fTemp12 = max(-1, min(1, (fSlow12 * (fRec32[2] + (fConst26 * (fTemp11 + (fConst25 * fRec32[0])))))));
		double fTemp13 = (((fTemp12 * (1 - (0.3333333333333333 * faustpower<2>(fTemp12)))) + ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + (0.841395141645195 * (fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9))))))) + (0.7943282347242815 * (fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6))))));
		fVec6[0] = fTemp13;
		fRec17[0] = ((fConst67 * (fVec6[0] + fVec6[1])) + (fConst5 * fRec17[1]));
		double fTemp14 = ((fSlow13 * fRec17[0]) + (fRec5[0] * ((fSlow8 * fRec16[0]) + (fRec4[0] * (1 + (fSlow5 * ((4 - (4 * fabs((fRec5[0] * fRec4[0])))) - 1)))))));
		fVec7[0] = fTemp14;
		fRec3[0] = ((fConst12 * (fVec7[0] + fVec7[1])) + (fConst5 * fRec3[1]));
		double fTemp15 = (fRec3[0] * pow(10,(0.05 * fRec2[0])));
		double fTemp16 = (fRec1[1] - 2.5e+02);
		fVec8[0] = fTemp16;
		fRec35[0] = ((fConst68 * (fVec8[0] + fVec8[1])) + (fConst5 * fRec35[1]));
		fRec1[0] = Ftube2(0, (fRec35[0] + fTemp15));
		fRec0[0] = ((fConst69 * ((fConst10 * fRec1[1]) + (fConst0 * fRec1[0]))) + (fConst2 * fRec0[1]));
		double fTemp17 = (fRec37[1] - 2.5e+02);
		fVec9[0] = fTemp17;
		fRec38[0] = ((fConst68 * (fVec9[0] + fVec9[1])) + (fConst5 * fRec38[1]));
		fRec37[0] = Ftube2(1, (fRec38[0] + fTemp15));
		fRec36[0] = ((fConst69 * ((fConst10 * fRec37[1]) + (fConst0 * fRec37[0]))) + (fConst2 * fRec36[1]));
		output0[i] = (FAUSTFLOAT)(fRec36[0] + fRec0[0]);
		// post processing
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		fVec9[1] = fVec9[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec35[1] = fRec35[0];
		fVec8[1] = fVec8[0];
		fRec3[1] = fRec3[0];
		fVec7[1] = fVec7[0];
		fRec17[1] = fRec17[0];
		fVec6[1] = fVec6[0];
		fRec32[2] = fRec32[1]; fRec32[1] = fRec32[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fVec5[1] = fVec5[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fVec4[1] = fVec4[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fVec3[1] = fVec3[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec16[1] = fRec16[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec13[1] = fRec13[0];
		fVec0[1] = fVec0[0];
		fRec12[1] = fRec12[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp2", init);
}

} // end namespace gxamp12
