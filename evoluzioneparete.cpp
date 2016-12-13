//SIMULARE L'EVOLUZIONE 
#include"scimmia.cpp"
#include <random>
#include "Snap.h"


using namespace std;
random_device caso;
default_random_engine casuale(caso());

const float p_cross=0.80;
const float p_muta=0.05;
const float p_clona=0.15;

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
		if(dis(casuale)<p_cross){new_gen.push_back(Scimmia(generazione[best(casuale)], generazione[best(casuale)]));}
		if(dis(casuale)>p_cross && dis(casuale)<p_cross+p_clona){new_gen.push_back(Scimmia(generazione[best(casuale)]));}
		if(dis(casuale)>p_cross+p_clona){
			Scimmia clone(generazione[best(casuale)]);
			clone.muta();
			new_gen.push_back(clone);}
	}
//inizializzo generazione[]	
	for (int i=0; i<dim; i++)
	{
		generazione[i]=new_gen[i];
	}
}
Scimmia evoluzione(bool rita, int n_ind, int n_gen, int n_passi, Parete parete){
vector<Scimmia> generazione;
for(int i = 0; i < n_ind; ++i) {
Scimmia s;
generazione.push_back(s);
}
TNodeEDatNet<Point,Point>::TNodeI pos;
for (int n=0; n<n_gen;++n){

		if(n != 0) riproduzione(generazione,n_ind);
		for (int i=0; i<n_ind; ++i)
		{
			pos=parete.get_p()->GetNI(parete.get_startID());

			generazione[i].set_memoria(pos.GetId());
			for (int j=0; j<n_passi; j++)
			{
				generazione[i].set_stato(pos);
				pos=parete.get_p()->GetNI(generazione[i].move(pos));
				
				if(pos.GetId()!=parete.get_endID())
				{
					generazione[i].set_memoria(pos.GetId());
					if(j>3 && *(generazione[i].get_memoria().end()-2)==*(generazione[i].get_memoria().end()-1)||j>6 && *(generazione[i].get_memoria().end()-2)==*(generazione[i].get_memoria().end()-4) && *(generazione[i].get_memoria().end()-1)==*(generazione[i].get_memoria().end()-3)) generazione[i].set_loop(true);	
				}
				else break;
			}
			if (rita) generazione[i].set_fit(generazione[i].fit_func_riri(pos, parete));
			else generazione[i].set_fit(generazione[i].fit_func_lo(pos, parete));
		}

	}
int piu_brava=0;
			for (int i=0; i<n_ind; i++)
			{	if (generazione[i].get_fit()>generazione[piu_brava].get_fit())
				piu_brava=i;
			}
Scimmia brava;
brava = generazione[piu_brava];
return brava;
}




int main (int argc,char*argv[])
{	
	int n_ind=atoi(argv[1]);
	int n_gen=atoi(argv[2]); 
	int n_passi=atoi(argv[3]);

	//creo la parete

	Parete parete=GeneraParete(1000, 70, 100, 3, 0.2, 0.2, 2);


	vector<Scimmia> generazione;
	for(int i = 0; i < n_ind; ++i) {
	Scimmia s;
	generazione.push_back(s);
	}

	TNodeEDatNet<Point,Point>::TNodeI pos;
	for (int n=0; n<n_gen;++n){

			if(n != 0) riproduzione(generazione,n_ind);
			for (int i=0; i<n_ind; ++i)
			{
				pos=parete.get_p()->GetNI(parete.get_startID());

				generazione[i].set_memoria(pos.GetId());
				for (int j=0; j<n_passi; j++)
				{
					generazione[i].set_stato(pos);
					pos=parete.get_p()->GetNI(generazione[i].move(pos));
				
					if(pos.GetId()!=parete.get_endID())
					{
						generazione[i].set_memoria(pos.GetId());
						if(j>3 && *(generazione[i].get_memoria().end()-2)==*(generazione[i].get_memoria().end()-1)||j>6 && *(generazione[i].get_memoria().end()-2)==*(generazione[i].get_memoria().end()-4) && *(generazione[i].get_memoria().end()-1)==*(generazione[i].get_memoria().end()-3)) generazione[i].set_loop(true);	
					}
					else break;
				}
				generazione[i].set_fit(generazione[i].fit_func_riri(pos, parete));
				
			}

		}
	int piu_brava=0;
				for (int i=0; i<n_ind; i++)
				{	if (generazione[i].get_fit()>generazione[piu_brava].get_fit())
					piu_brava=i;
				}
	Scimmia brava;
	brava = generazione[piu_brava];
	for (int i=0; i<get_dna().size; i++)cout<<generazione[piu_brava].get_dna()[i]<<" ";cout<<endl;
	parete.animate
}
