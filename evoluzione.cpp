#include "evoluzione.h"

using namespace std;
random_device caso;
default_random_engine casuale(caso());
typedef TNodeEDatNet<Point,Point> TNet;

void Evoluzione::change_parete(int N, int x, int y, int d, double prob_appo, double prob_appi, int min_depth)
{
	parete = get_random_p(N, x, y, d, prob_appo, prob_appi, min_depth);
}

void Evoluzione::riproduzione ()
{
	vector<Scimmia> new_gen;
	vector<double> pesi;
	for (int i = 0; i < generazione.size(); ++i) pesi.push_back(generazione[i].get_fit());
	uniform_real_distribution<> dis(0,1);
	discrete_distribution<> best(pesi.begin(), pesi.end());
//inizializzo new_gen con Scimmie selezionate con cross-over, mutazione e clonazione
	for (int i=0; i<individui; i++)
	{
		double prob = dis(casuale);
		Scimmia p = generazione[best(casuale)], m = generazione[best(casuale)];
		if(prob < p_cross) p = Scimmia(p,m);
		if(prob > 1-p_muta) p.muta();
        new_gen.push_back(p);
	}
    swap(generazione,new_gen);
}

void Evoluzione::evoluzione(function<double(Scimmia&, TNet::TNodeI&, const Parete&)> fit_func) {
    riproduzione();
    #pragma omp parallel for
    for (int i =0; i < generazione.size(); ++i) {
        TNet::TNodeI pos = generazione[i].traverse(parete, passi);
        generazione[i].set_fit(fit_func(generazione[i], pos, parete));
    }
}

Scimmia Evoluzione::best_scimmia(){
	return *max_element(generazione.begin(), generazione.end(), [&](auto &e, auto &i) { return e.get_fit() < i.get_fit(); });
}

Evoluzione::Evoluzione() = default;

Evoluzione::Evoluzione(int passi, int individui, double p_cross, double p_muta) :
		passi(passi), individui(individui), p_cross(p_cross), p_muta(p_muta), generazione(individui), parete(){
	change_parete(1000,70,100,3,0.2,0.2,3);
}

void Evoluzione::new_gen(){
	generate(generazione.begin(),generazione.end(),[](){return Scimmia();});
}
void Evoluzione::set_individui(int _individui) {
    individui = _individui;
}

void Evoluzione::set_passi(int _passi) {
	passi = _passi;
}

void Evoluzione::set_pcross(double _p_cross) {
	p_cross = _p_cross;
}

void Evoluzione::set_pmuta(double _p_muta) {
	p_muta = _p_muta;
}
void Evoluzione::animate(){
    parete.animate(best_scimmia().get_memoria());
}
