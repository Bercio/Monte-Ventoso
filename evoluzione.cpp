#include"genetico.cpp"
#include <random>
#include "Snap.h"

using namespace std;
random_device caso;
default_random_engine casuale(caso());

const float p_cross=0.90;
const float p_muta=0.05;
const float p_clona=0.05;


void riproduzione (Scimmia generazione[], int dim)
{	
	
	Scimmia new_gen[dim];
	
	vector<double> pesi;
	for (int i = 0; i < dim; ++i) pesi.push_back(generazione[i].get_fit());
	
	uniform_real_distribution<> dis(0,1);
	discrete_distribution<> best(pesi.begin(), pesi.end());

//inizializzo new_gen con Scimmie selezionate con cross-over, mutazione e clonazione
	for (int i=0; i<dim; i++)
	{
		if(dis(casuale)<p_cross){new_gen[i]= Scimmia(generazione[best(casuale)], generazione[best(casuale)]);}
		if(dis(casuale)>p_cross && dis(casuale)<p_cross+p_clona){new_gen[i] = Scimmia(generazione[best(casuale)], generazione[best(casuale)]);}
		if(dis(casuale)>p_cross+p_clona){new_gen[i]=generazione[best(casuale)]; new_gen[i].muta();}
	}
//inizializzo generazione[]	
	for (int i=0; i<dim; i++)
	{
		generazione[i]=new_gen[i];
	}
}

int main (int argc,char*argv[])
{

	
	int n_ind=atoi(argv[1]);
	int n_gen=atoi(argv[2]); 
	int n_passi=atoi(argv[3]);

	Scimmia generazione[n_ind];

	//creo l'albero
	PNGraph NGraph;
	   	const int Fanout=2; //max figli
		const int Levels=5;
		NGraph = GenTree<PNGraph>(Fanout, Levels, false, true);
	TNGraph::TNodeI Gianni;

	for (int n=0; n<n_gen;++n)
	{	cout<<endl<<endl<<"GENERAZIONE "<<n+1<<endl<<endl;
		for (int i=0; i<n_ind; ++i)
		{	
			Gianni=NGraph->BegNI();
			for (int j=0; j<n_passi; ++j) 
			{	//faccio muovere la scimmia, se arriva in cima smette di muoversi
				
				generazione[i].set_stato(Gianni); 
				Gianni=NGraph->GetNI(generazione[i].move(Gianni));
				if(Gianni.GetId()!=NGraph->GetMxNId())
				{
					generazione[i].set_memoria(Gianni.GetId());
					generazione[i].set_nodi_visitati(Gianni.GetId());
				} else break;
			}
			//setfit
			generazione[i].set_fit_locale(Gianni.GetId(), NGraph);
			double f=generazione[i].get_fit_locale();
			generazione[i].set_fit(f);
			
			cout<<"fit: "<<generazione[i].get_fit()<<endl<<"nodo di arrivo "<<Gianni.GetId()<<endl<<"dna:  ";
			vector <int> v = generazione[i].get_dna();
			for (int j=0;j<v.size();j++){cout<<v[j]<<" ";}
			vector<int> m =generazione[i].get_memoria();
			cout<<endl<<"memoria:  ";		
			for (int k=0; k<m.size(); k++){cout<<m[k]<<" ";}
			vector<int> n=generazione[i].get_nodi_visitati();
			cout<<endl<<"nodi visitati:  ";
			for (int k=0; k<n.size(); k++){cout<<n[k]<<" ";}
			cout<<endl<<endl;
		}
		riproduzione(generazione, n_ind);
	}
cout<<NGraph->GetMxNId();
}
