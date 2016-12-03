//SIMULARE L'EVOLUZIONE 
#include"prova.h"
#include <random>
#include "Snap.h"

using namespace std;

default_random_engine casuale;

const float p_cross=0.90;
const float p_muta=0.05;
const float p_clona=0.05;


void prima_gen(Scimmia generazione[], int dim)
{
	for(int i=0; i<dim; i++) generazione[i]=Scimmia();
}

void prolificazione (Scimmia generazione[], int dim)
{

	//riordino gli elementi dell'array generazione in base al punteggio nel fit
	
	Scimmia new_gen[dim];
	uniform_real_distribution<> dis(0,1);
	
	int min;
	for(int i=0; i<dim; i++)
	{ 
		min = i;

		for(int j=i+1; j<dim; j++)
		  if(generazione[j].fit< generazione[min].fit) min = j;
		Scimmia temp;
		temp=generazione[min];
		generazione[min]=generazione[i];
		generazione[i]=temp;
	}
	//creo l'array dei parametri di fit ordinati
	
	vector<int> pesi;
	for (int i = 0; i < dim; ++i) pesi.push_back(generazione[i].fit);
	

	discrete_distribution<> best(pesi.begin(), pesi.end());

//inizializzo new_gen con Scimmie selezionate con cross-over, mutazione e clonazione
	for (int i=0; i<dim; i++)
	{
		if(dis(casuale)<p_cross){new_gen[i]= Scimmia(generazione[best(casuale)], generazione[best(casuale)]);}
		if(dis(casuale)>p_cross && dis(casuale)<p_cross+p_clona){new_gen[i] = Scimmia(generazione[best(casuale)].dna);}
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
int n_gen=atoi(argv[1]); 
int n_ind=atoi(argv[2]);
int n_passi=50;

Scimmia generazione[n_ind];
prima_gen(generazione, n_ind);

PNGraph NGraph;
   	const int Fanout=4; //max figli
    const int Levels=5;
    NGraph = GenTree<PNGraph>(Fanout, Levels, true, true);
TNGraph::TNodeI Gianni;

for (int i=0; i<n_gen; ++i)
{
	generazione[i].fit=0;
	
	Gianni=NGraph->BegNI();
	for (int j=0; j<n_passi; ++j) Gianni=NGraph->GetNI(move(generazione[i], Gianni));
	//la scimmia fa 50 passi, Gianni è il nodo a cui arriva

	generazione[i].fit+=generazione[i].fit_distanza(Gianni.GetId(), NGraph);
	//ho calcolato la bravura delle scimmie ora posso farli prolificare
	prolificazione(generazione, n_ind);
}
for(int i=0; i<n_ind; ++i) cout<<" "<<generazione[i].fit;
}
