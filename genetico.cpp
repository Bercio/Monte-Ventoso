#include<iostream>
#include <cstdlib>

using namespace std;

#define N_INDIV 50 //individui della popolazione
#define PCROSS 0.8
#define PMUT 0.2

class individuo
{
double fitpar;
int dna[15];
}
/*
devo fare una matrice 15x4 che definisca tutte le possibili configurazioni che il ragno si trova davanti e far corrisponere a ogni vettore una funzione.
*/
/*
funzione GUARDA: legge l'albero, ritorna un array che ha già riempito.
in ragno: c'è una funzione che riceve l'array, returna l'azione corrispondente dell'individuo-ragno;


dove scrivo che il ragno dati certi imput restituisce degli output?
*/

class ragno
{
void avantiv();
void avantinv();
void indietrov();
void indietronv();
}



individuo popolazione[N_INDIV];




void riempi()
{
for(int i=0, i<N_INDIV, ++i)
 {
  for (int j=0, j<15, ++j) {int caso=rand()%4;popolazione[i].dna[j]=caso;}
 }
}






double fitness();
