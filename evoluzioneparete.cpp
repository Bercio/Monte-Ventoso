//SIMULARE L'EVOLUZIONE 
#include"scimmia.cpp"
#include <random>
#include <stdlib.h>
#include <iomanip>
#include "Snap.h"


using namespace std;
random_device caso;
default_random_engine casuale(caso());

const float p_cross=0.80;
const float p_muta=0.19;
const float p_clona=0.01;

PNGraph GeneraAlbero(int n_figli, int livelli)
{
	PNGraph NGraph;

	NGraph = GenTree<PNGraph>(n_figli, livelli, false);
	return NGraph;
}

Parete GeneraParete(int N, int x, int y, int d, double prob_appo, double prob_appi,int min_depth)
{
	return get_random_p(N, x, y, d, prob_appo, prob_appi, min_depth);
}

void riproduzione (vector<Scimmia>& generazione, int dim)
{

	vector<Scimmia> new_gen;

	vector<double> pesi;
	for (int i = 0; i < dim; ++i) pesi.push_back(generazione[i].get_fit());

	uniform_real_distribution<> dis(0,1);
	discrete_distribution<> best(pesi.begin(), pesi.end());

//inizializzo new_gen con Scimmie selezionate con cross-over, mutazione e clonazione
	for (int i=0; i<dim; i++)
	{
		double prob = dis(casuale);
		if(prob<=p_cross){new_gen.push_back(Scimmia(generazione[best(casuale)], generazione[best(casuale)]));}
		if(prob>p_cross && prob<(p_cross+p_clona)){new_gen.push_back(generazione[best(casuale)].clona());}
		if(prob>=(p_cross+p_clona)){
			Scimmia clone = generazione[best(casuale)].clona();
			clone.muta();
			new_gen.push_back(clone);}
	}
//inizializzo generazione[]	
	for (int i=0; i<dim; i++)
	{
		generazione[i]=new_gen[i];
	}
}
Scimmia evoluzione(bool rita, int n_ind, int n_gen, int n_passi, Parete parete) {
	vector<Scimmia> generazione;
	for (int i = 0; i < n_ind; ++i) {
		Scimmia s;
		generazione.push_back(s);
	}
	TNodeEDatNet<Point, Point>::TNodeI pos;
	for (int n = 0; n < n_gen; ++n) {

		if (n != 0) riproduzione(generazione, n_ind);
		for (int i = 0; i < n_ind; ++i) {
			TNodeEDatNet<Point,Point>::TNodeI pos = generazione[i].traverse(parete, n_passi);
			if (rita) generazione[i].set_fit(generazione[i].fit_func_riri(pos, parete));
			else generazione[i].set_fit(generazione[i].fit_func_lo(pos, parete));
		}

	}

	auto best_scimmia = max_element(generazione.begin(), generazione.end(),
									[&](auto &e, auto &i) { return e.get_fit() < i.get_fit(); });
	return *best_scimmia;
}



int main (int argc,char*argv[])
{
	int n_ind=atoi(argv[1]);
	int n_gen=atoi(argv[2]);
	int n_passi=atoi(argv[3]);

	//creo la parete

	Parete parete=GeneraParete(1000, 70, 100, 3, 0.2, 0.2, 2);


	Scimmia LaMeglioRita;
	LaMeglioRita.set_dna({0,0,1,1,2,2,2,2,3,3,3,3,2,2,2,2});
	TNodeEDatNet<Point,Point>::TNodeI pos = LaMeglioRita.traverse(parete, n_passi);
    LaMeglioRita.set_fit(LaMeglioRita.fit_func_riri(pos,parete));
	vector<int> rdna = LaMeglioRita.get_dna();
	cout << "DNA di ri: ";
	for_each(rdna.begin(), rdna.end(), [&](auto& e){ cout << e << ", ";});
	cout << "; Fit di ri: " << scientific << setprecision(5) << LaMeglioRita.get_fit();
	parete.animate(LaMeglioRita.get_memoria(), "Rita");
    /*
	LaMeglioRita = evoluzione(true, n_ind, n_gen, n_passi,parete);
	Scimmia LaMeglioBercio;
	LaMeglioBercio = evoluzione(false, n_ind, n_gen, n_passi,parete);
	parete.animate(LaMeglioBercio.get_memoria(), "Lorenzo");
	cout << "\nDNA di lo: ";
	for_each(bdna.begin(), bdna.end(), [&](auto& e){ cout << e << ", ";});
	cout << "; Fit di lo: " << scientific << setprecision(5) << LaMeglioBercio.get_fit();
	cout << endl;
	*/

}
