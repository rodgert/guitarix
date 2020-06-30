#ifndef _REDEYE_CHUMPPRE_H_
#define _REDEYE_CHUMPPRE_H_
 
// redeyechumppre_table generated by DK/circ_table_gen.py -- do not modify manually

 // variables used
 // --sig_max  1.500000
 // --table_div  32.006667
 // --table_op  3.000000

struct tableredeyechumppre { // 1-dimensional function table
    float low;
    float high;
    float istep;
    int size;
    float data[];
};

template <int tab_size>
struct tableredeyechumppre_imp {
    float low;
    float high;
    float istep;
    int size;
    float data[tab_size];
    operator tableredeyechumppre&() const { return *(tableredeyechumppre*)this; }
};

 static tableredeyechumppre_imp<200> redeyechumppre_table __rt_data = {
	0,-0.833333,398,200, {
	0.000000000000,-0.001890319703,-0.003824468511,-0.005801811652,-0.007821732924,
	-0.009883633954,-0.011986933481,-0.014131066671,-0.016315484463,-0.018539652942,
	-0.020803052732,-0.023105178424,-0.025445538019,-0.027823652406,-0.030239054844,
	-0.032691290488,-0.035179915911,-0.037704498667,-0.040264616860,-0.042859858733,
	-0.045489822276,-0.048154114853,-0.050852352834,-0.053584161256,-0.056349173491,
	-0.059147030923,-0.061977382651,-0.064839885192,-0.067734202204,-0.070660004217,
	-0.073616968376,-0.076604778197,-0.079623123328,-0.082671699324,-0.085750207430,
	-0.088858354373,-0.091995852162,-0.095162417899,-0.098357773593,-0.101581645984,
	-0.104833766379,-0.108113870484,-0.111421698253,-0.114756993740,-0.118119504951,
	-0.121508983715,-0.124925185546,-0.128367869521,-0.131836798157,-0.135331737299,
	-0.138852456002,-0.142398726433,-0.145970323760,-0.149567026062,-0.153188614226,
	-0.156834871866,-0.160505585228,-0.164200543112,-0.167919536788,-0.171662359924,
	-0.175428808508,-0.179218680777,-0.183031777154,-0.186867900175,-0.190726854436,
	-0.194608446521,-0.198512484956,-0.202438780143,-0.206387144314,-0.210357391475,
	-0.214349337360,-0.218362799381,-0.222397596582,-0.226453549598,-0.230530480610,
	-0.234628213306,-0.238746572840,-0.242885385798,-0.247044480156,-0.251223685251,
	-0.255422831746,-0.259641751595,-0.263880278013,-0.268138245449,-0.272415489554,
	-0.276711847152,-0.281027156220,-0.285361255852,-0.289713986243,-0.294085188660,
	-0.298474705421,-0.302882379872,-0.307308056364,-0.311751580233,-0.316212797783,
	-0.320691556261,-0.325187703842,-0.329701089608,-0.334231563534,-0.338778976469,
	-0.343343180117,-0.347924027026,-0.352521370568,-0.357135064927,-0.361764965082,
	-0.366410926797,-0.371072806601,-0.375750461779,-0.380443750359,-0.385152531098,
	-0.389876663469,-0.394616007653,-0.399370424521,-0.404139775628,-0.408923923200,
	-0.413722730124,-0.418536059935,-0.423363776807,-0.428205745545,-0.433061831573,
	-0.437931900921,-0.442815820224,-0.447713456704,-0.452624678164,-0.457549352982,
	-0.462487350095,-0.467438538999,-0.472402789731,-0.477379972869,-0.482369959515,
	-0.487372621295,-0.492387830343,-0.497415459300,-0.502455381298,-0.507507469958,
	-0.512571599378,-0.517647644127,-0.522735479237,-0.527834980192,-0.532946022922,
	-0.538068483795,-0.543202239609,-0.548347167582,-0.553503145344,-0.558670050931,
	-0.563847762773,-0.569036159690,-0.574235120877,-0.579395303805,-0.584517123422,
	-0.589619335784,-0.594707488168,-0.599784552509,-0.604852406607,-0.609912345307,
	-0.614965311644,-0.620012018536,-0.625053019586,-0.630088753332,-0.635119572425,
	-0.640145763710,-0.645167562507,-0.650185163068,-0.655198726409,-0.660208386292,
	-0.665214253883,-0.670216421419,-0.675214965146,-0.680209947692,-0.685201420008,
	-0.690189422968,-0.695173988703,-0.700155141715,-0.705132899818,-0.710107274943,
	-0.715078273816,-0.720045898550,-0.725010147151,-0.729971013957,-0.734928490023,
	-0.739882563452,-0.744833219696,-0.749780441810,-0.754724210682,-0.759664505235,
	-0.764601302613,-0.769534578333,-0.774464306437,-0.779390459615,-0.784313009321,
	-0.789231925883,-0.794147178585,-0.799058735764,-0.803966564875,-0.808870632567,
	-0.813770904745,-0.818667346621,-0.823559922773,-0.828448597184,-0.833333333291
	}
};

double always_inline redeyechumppreclip(double x) {
    double f = fabs(x);
    f = f * redeyechumppre_table.istep;
    int i = static_cast<int>(f);
    if (i < 0) {
        f = redeyechumppre_table.data[0];
    } else if (i >= redeyechumppre_table.size-1) {
        f = redeyechumppre_table.data[redeyechumppre_table.size-1];
    } else {
    f -= i;
    f = redeyechumppre_table.data[i]*(1-f) + redeyechumppre_table.data[i+1]*f;
    }
    return copysign(f, x);
}
#endif // _REDEYE_CHUMPPRE_H_
