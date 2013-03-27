#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>


using namespace std;

int main()
{
    int n(6),m(4);
    float e(4);
    cout << "Entrez les dimensions de la matrice : " << endl;
    cout << "Nombre de ligne";
    cin >> n;
    cout << "Nombre de colonne";
    cin >> m;
    cout << "Espace entre les capteurs";
    cin >> e;

    string const out1("../net/fingertip_layout.pos");
    ofstream Fingertip(out1.c_str());

    string const out2("../net/sensor2mr.net");
    ofstream Net(out2.c_str());

    string const out3("../config/psoma_mr.conf");
    ofstream psoma_mr(out3.c_str());

    if(Fingertip && Net && psoma_mr)
    {

        Fingertip << "###############################" << endl
                << "#	PSoma - Fingertip - Layout File" << endl
                << "#" << endl
                << "# Defines the relative positions of the sensors on the fingertip" << endl
                << "###############################" << endl
                << "# Array Dimensions" << endl
                << "###############################" << endl
                << n*m << " 4" << endl
                << "# lines = one line per sensor" << endl
                << "# columns = sensor index, X pos (mm), Y pos (mm), Z pos (mm)" << endl << endl
                << "###############################" << endl
                << "#            Array            #" << endl
                << "###############################" << endl;

        Net << "###############################" << endl
                << "#	PSoma - Sensor To Mechanoreceptor - Network File" << endl
                << "#" << endl
                << "# Network file array dimensions are to be defined on the first line (lines x columns)." << endl
                << "# MC and MR index values must be 'continuous' and start at zero (though not necessarily in order)" << endl
                << "###############################" << endl
                << "# Array Dimensions" << endl
                << "###############################" << endl
                << n*m << " 4" << endl
                << "# lines = one line per sensor" << endl
                << "# columns = sensor index, mechanoreceptor index, connection weight (0..1), connection delay (ms)" << endl << endl
                << "###############################" << endl
                << "#            Array            #" << endl
                << "###############################" << endl;

        int l1(0),l2(0),im(0),jm(0);



        for(im=0;im<n;im++)
        {
            for(jm=0;jm<m;jm++)
            {
                Fingertip << "    " << l1 << "    " << jm*e << "    " << im*(-1)*e << "    " << 0 << endl;
                l1++;
                l2++;
            }
        }
        for(int i=0;i<n*m;i++)
        {
            Net << "    " << i << "    " << i << "    "
                << 1 << "    " << 0 << endl;
        }
    psoma_mr << "###############################" << endl
<<"# Sensor Parameters" << endl
<<"###############################" << endl
<<"nb_sensors	" << n*m << "	# number of sensors (ie. Merkel Cells) per mechanoreceptor" << endl
<<"rsp_amp		43	# amplitude of response signal" << endl
<<"rsp_width	1	# width of receptive field of sensors (ie. Merkel Cells) (std, mm)" << endl
<<"rsp_amp_wn	8.9	# white noise on amplitude response of the sensor" << endl
<<"rsp_width_wn	0.11	# white noise on amplitude response of the sensor (adds to std, mm)" << endl
<<"mc_layoutFile	../net/fingertip_layout.pos	# array file with fingertip sensor layout" << endl
 << endl
<<"###############################" << endl
<<"# Mechanoreceptor Parameters" << endl
<<"###############################" << endl
<<"nb_mr		" << n*m << "# number of mechanoreceptors" << endl
<<"V_rest		-70	# resting membrane potential (mV)" << endl
<<"C		0.5	# membrane capacitance (nF)" << endl
<<"g		25	# membrane passive conductance (nS)" << endl
<<"I_gain		-3e-10 	# gain factor for input current intensity" << endl
<<"V_reset		-100	# reset potential after spike (mV)" << endl
<<"t_refractory	2	# refractory period (ms)" << endl
<<"V_thresh	-50	# resting spiking threshold potential (mV)" << endl
<<"V_thresh_incr	50	# threshold increment after spiking (mV) (theshold fatigue)" << endl
<<"t_thresh	100	# time constant for threshold amplification decay (ms) (threshold fatigue)" << endl
<<"dt		1	# computation time step for LIF differential equation resolution (should normally be smaller (or equal) than global system 'time_step' parameter) (ms)" << endl;

cout << "Config crée" << endl;
    }
    else
    {
        cout << "Error" << endl;
        cout << endl;
    }
    system("pause");
    cout << system("psoma.exe") <<endl;
    system("pause");
    return 0;
}
