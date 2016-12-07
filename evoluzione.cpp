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
		if(dis(casuale)>p_cross && dis(casuale)<p_cross+p_clona){new_gen[i] = Scimmia(generazione[best(casuale)]);}
		if(dis(casuale)>p_cross+p_clona){new_gen[i]= Scimmia(generazione[best(casuale)]); new_gen[i].muta();}
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

	PNGraph NGraph=GeneraAlbero(3, 4);

	TNGraph::TNodeI Gianni;

	for (int n=0; n<n_gen;++n)
	{	cout<<endl<<endl<<"GENERAZIONE "<<n+1<<endl<<endl;
		for (int i=0; i<n_ind; ++i)
		{	
			Gianni=NGraph->BegNI();
			for (int j=0; j<n_passi; ++j) 
			{	//faccio muovere la scimmia
				
				generazione[i].set_stato(Gianni); 
				Gianni=NGraph->GetNI(generazione[i].move(Gianni));
				//se arriva in cima smette di muoversi
				if(Gianni.GetId()!=NGraph->GetMxNId()-1)
				{ 
					vector<int> m =generazione[i].get_memoria();									
					generazione[i].set_memoria(Gianni.GetId());
					generazione[i].set_nodi_visitati(Gianni.GetId());
					if(j>3 && *(m.end()-2)==*(m.end()-1)||j>6 && *(m.end()-2)==*(m.end()-4) && *(m.end()-1)==*(m.end()-3)) generazione[i].set_loop(true);
				} 
				else break;
			}
			//setfit
			bool l=generazione[i].get_loop();
			generazione[i].set_fit_locale(Gianni.GetId(), NGraph, l);
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
			cout<<endl;
			if (generazione[i].get_loop()==true) cout<<"loop = true"<<endl<<endl; else cout<<"loop = false"<<endl;
			cout<<m.size()<<endl<<endl;
		}
		riproduzione(generazione, n_ind);
	}
cout<<"nodo in cima: "<<NGraph->GetMxNId()-1<<endl;
}
