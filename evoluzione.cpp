//SIMULARE L'EVOLUZIONE 

//far andare le scimmie nel grafo

#include<genetico.cpp>
#include <random>

using namespace std;

default_random_engine casuale;

const float p_cross=0.90;
const float p_muta=0.05;
const float p_clona=0.05;

const int n_gen;//numero generazioni
const int n_ind; //numero individui per generazione
const int brave=n_gen/10;

Scimmia generazione[n_ind];

void prima_gen()
{
	for(int i=0; i<n_ind; i++) generazione[i]=Scimmia();
}

void prolificazione ()
{//riordino gli elementi dell'array generazione in base al punteggio nel fit
	int min;
	Scimmia new_gen[n_ind];
	uniform_real_distribution<> dis(0,1)
	uniform_int_distribution<int> best(0, brave)

	for(i=0; i<n_ind; i++)
	{
		min = i;

		for(j=i+1; j<n_ind; j++)
		  if(generazione[j].fit_distanza < generazione[min].fit_distanza)
		    min = j;

		temp=generazione[min];
		generazione[min]=generazione[i];
		generazione[i]=temp;
	}
//inizializzo new_gen con Scimmie selezionate con cross-over, mutazione e clonazione
	for (int i=0; i<n_ind; i++)
	{
		if(dis(casuale)<p_cross){new_gen[i]= Scimmia(generazione[best(casuale)], generazione[best(casuale)]);}
		if(dis(casuale)>p_cross && dis(casuale)<p_cross+p_clona){new_gen[i] = generazione[best(casuale)];}
		if(dis(casuale)>p_cross+p_clona){new_gen[i]=generazione[best(casuale)]; new_gen[i].muta();}
	}
//inizializzo generazione[]	
	for (int i=0; i<n_ind; i++)
	{
		generazione[i]=new_gen[i];
	}
}

int main (int argc,char*argv[])
{
n_gen=argv[0]; 
n_ind=argv[1]; 

prima_gen();

PNGraph NGraph;
    const int Fanout=4; //max figli
    const int Levels=5;
    NGraph = GenTree<PNGraph>(Fanout, Levels, true, true);

for int(i=0; i<n_gen; ++i)
{prolificazione();}

}
