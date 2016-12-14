#include "evoluzione.h"

using namespace std;
random_device caso;
default_random_engine casuale(caso());
typedef TNodeEDatNet<Point,Point> TNet;

Parete GeneraParete(int N, int x, int y, int d, double prob_appo, double prob_appi, int min_depth)
{
	return get_random_p(N, x, y, d, prob_appo, prob_appi, min_depth);
}

void riproduzione (vector<Scimmia>& generazione, double p_cross, double p_muta)
{
	vector<Scimmia> new_gen;
	vector<double> pesi;
	for (int i = 0; i < generazione.size(); ++i) pesi.push_back(generazione[i].get_fit());
	uniform_real_distribution<> dis(0,1);
	discrete_distribution<> best(pesi.begin(), pesi.end());
//inizializzo new_gen con Scimmie selezionate con cross-over, mutazione e clonazione
	for (int i=0; i<generazione.size(); i++)
	{
		double prob = dis(casuale);
		Scimmia p = generazione[best(casuale)], m = generazione[best(casuale)];
		if(prob < p_cross) p = Scimmia(p,m);
		if(prob > 1-p_muta) p.muta();
        new_gen.push_back(p);
	}
    swap(generazione,new_gen);
}

void evoluzione(int n_passi, double p_cross, double p_muta, Parete& parete, vector<Scimmia>& generazione, function<double(Scimmia&, TNet::TNodeI&, const Parete&)> fit_func) {
    riproduzione(generazione, p_cross, p_muta);
    for (auto& i : generazione) {
        TNet::TNodeI pos = i.traverse(parete, n_passi);
        i.set_fit(fit_func(i, pos, parete));
    }
}

Scimmia best_scimmia(vector<Scimmia>& generazione){
	return *max_element(generazione.begin(), generazione.end(), [&](auto &e, auto &i) { return e.get_fit() < i.get_fit(); });
}
