#include "scimmia.h"
#include<iostream>
using namespace std;
using namespace TSnap;

int N = 1024;
random_device rd;
default_random_engine gen(rd());

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    std::uniform_int_distribution<int> dis(0, (int) (std::distance(start, end) - 1));
    std::advance(start, dis(gen));
    return start;
}
//genera una scimmia con dna casuale-> è un numero compreso tra 0 e 3 poichè sono 4 le azioni possibili:
//andare su padri noti, padri ignoti, figli noti, figli ignoti
Scimmia::Scimmia(): dna(N), fit(0), loop(false), stato(0), memoria({}){
    uniform_int_distribution<int> actions(0,4);
    generate(dna.begin(),dna.end(),[&](){return actions(gen);});
}

//genera una scimmia con dna derivato dal cross over: per ogni elemento del vettore dna c'è 0.5 di probabilità che venga dalla madre, 0.5 dal padre
Scimmia::Scimmia(Scimmia& m, Scimmia& p): fit(0), loop(false),stato(0), memoria({}) {
    std::bernoulli_distribution dist (0.5);
    vector<int> _dna(N);
    for (int i=0; i<N; ++i) {
        if (dist(gen)){_dna[i]=m.get_dna()[i];}
        else {_dna[i]=p.get_dna()[i];};
    }
    set_dna(_dna);

}

//scimmia con dna impostabile dall'esterno
Scimmia::Scimmia(vector<int> _dna): dna(_dna), fit(0), loop(false) {;
}

void Scimmia::set_memoria(const int& node){ memoria.push_back(node); }

void Scimmia::set_fit(double f){fit=f;}

void Scimmia::set_loop(bool l){loop=l;}

void Scimmia::set_dna(const vector<int>& _dna) { this->dna = _dna; }

vector<int> Scimmia::get_memoria()const{ return memoria;}

double Scimmia::get_fit()const { return fit;}

bool Scimmia::get_loop() const {return loop;}

vector<int> Scimmia::get_dna() const { return dna; }

int Scimmia::get_stato() const { return stato;}

int Scimmia::scegli_azione(){ return dna[stato]; }
//lo stato è la configurazione di nodi che la scimmia vede
//la scimmia può vedere solo nodi appartenenti a 4 categorie ciascuna contrassegnata dall'etichetta presente (1) o non presente (0).
// Quindi ogni stato può essere rappresentato da un numero binario tra 0 e 15.
//set stato categorizza i nodi (node) raggiungibili dalla scimmia in base a se sono piu in alto (Val2 è la y) o più in
//basso e controlla se sono presenti in memoria o meno.
void Scimmia::set_stato(const TNodeEDatNet<Point,Point>::TNodeI& node){
    int stato_precedente= get_stato()%32 ;

    bool fn=0,pn(0),fi(0),pi(0), np(0);
    for (int i = 0; i < node.GetOutDeg(); ++i){

        int fnodeEdge = node.GetOutEDat(i).Val2;
        int fnodeID = node.GetOutNId(i);
        if (find(memoria.begin(), memoria.end(), fnodeID) != memoria.end())  {
            if  (fnodeEdge < 0) pn = 1;
            else fn = 1;
        } else {
            if (fnodeEdge < 0)  pi = 1;
            else fi = 1;
        }
    if (!memoria.empty() && memoria.back()  == fnodeID) {np=1;}
    }
    stato = fn + pn*2 + fi*4 + pi*8  + stato_precedente*16; //7 fn pn fi, 8 pi, 9 pi fn, 10 pi pn, 11 pi pn fn, 12 pi fi, 13 pi fi fn, 14 pi fi pn, 15 pi fi pn fn
}

//controlla se la scimmia si alterna tra due nodi;
bool Scimmia::is_looping(const int& passi) {
           return passi > 6 &&
           *(get_memoria().end() - 2) == *(get_memoria().end() - 4) &&
           *(get_memoria().end() - 1) == *(get_memoria().end() - 3);
}

void Scimmia::muta(){
    uniform_int_distribution<int> range(0,N-1);
    uniform_int_distribution<int> actions(0,4);
    vector<int> _dna = get_dna();
    _dna[range(gen)] = actions(gen);
    set_dna(_dna);
}
//fa muovere la scimmia in base alla sua strategia (dna)  tramite la funz scegli_azione
//prima di chiamarla devo chiamare set stato altrimenti non ha senso
//riceve la posizione della scimmia assegna ogni id del nodo a una categoria e poi nello switch sposta la posizione
//in uno dei nodi a caso appartenente alla categoria scelta

int Scimmia::move(const TNodeEDatNet<Point,Point>::TNodeI& pos){

    vector<int> padri_n, padri_ig, figli_n, figli_ig;
    bool np(0);
    for(int i = 0; i<pos.GetOutDeg(); ++i){
        int outNode = pos.GetOutEDat(i).Val2;
        int IDoutNode = pos.GetOutNId(i);
        if(!memoria.empty() && memoria.back() == IDoutNode){np=1;}
        else {
            if (find(memoria.begin(),memoria.end(), IDoutNode)!= memoria.end()){
            if (outNode < 0) padri_n.push_back(IDoutNode);
                else figli_n.push_back(IDoutNode);
            }
            else if (outNode < 0) padri_ig.push_back(IDoutNode);
            else figli_ig.push_back(IDoutNode);
        }
    }
    switch(scegli_azione())
    {
        case a_f_noto:
            return !figli_n.empty() ?  *(select_randomly(figli_n.begin(),figli_n.end())) : pos.GetId();
        case a_p_noto:
            return !padri_n.empty() ?  *(select_randomly(padri_n.begin(),padri_n.end())) : pos.GetId();
        case a_f_ignoto:
            return !figli_ig.empty() ?  *(select_randomly(figli_ig.begin(),figli_ig.end())) : pos.GetId();
        case a_p_ignoto:
            return !padri_ig.empty() ?  *(select_randomly(padri_ig.begin(),padri_ig.end())) : pos.GetId();
        case a_n_precedente:
            return np ? memoria.back() : pos.GetId();

    }
}

//far muovere la scimmia per n_passi sulla parete
//dichiara la posizione e la aggiorna chiamando move. Setta anche la memoria e il loop
TNodeEDatNet<Point,Point>::TNodeI Scimmia::traverse(const Parete& parete, int n_passi) {
    TNodeEDatNet<Point,Point>::TNodeI pos = parete.get_p()->GetNI(parete.get_startID());
    for (int j = 0; j < n_passi; j++) {
        int posID = pos.GetId();
        set_stato(pos);

        set_memoria(posID);
        set_loop(is_looping(memoria.size()));
        if(posID == parete.get_endID()) break;
        pos = parete.get_p()->GetNI(move(pos));
        if(get_memoria().back() == pos.GetId()) {
            set_loop(true);
            for(int i = j+1; i < n_passi; ++i) set_memoria(posID);
            break;
        }
    }
    return pos;
}

double Scimmia::fit_func_lo(TNodeEDatNet<Point,Point>::TNodeI& n, const Parete& g, int passi){
	if(loop==false){
    	return pow(g.get_p()->GetNDat(g.get_endID()).dist(n.GetDat()),-2)*pow(memoria.size(),-1);}
	else return {0.1*pow(g.get_p()->GetNDat(g.get_endID()).dist(n.GetDat()),-1)*pow(memoria.size(),-1)};
}

double Scimmia::fit_func_riri(TNodeEDatNet<Point,Point>::TNodeI& n, const Parete& g, int passi){
	double fit;
	set<int> nodi_visitati(memoria.begin(),memoria.end());
	if(loop==false){
		fit=((double)nodi_visitati.size()-1)/pow((double)memoria.size()/passi,2);
	 	for (auto k : nodi_visitati) {fit+=g.get_p()->GetNDat(k).Val2/((double)pow(memoria.size()/passi, 2));}
	}
	else {
		fit=(0.01*((double)nodi_visitati.size()-1))/pow((double)memoria.size()/passi, 2);
		for (auto k : nodi_visitati) fit+=0.01*g.get_p()->GetNDat(k).Val2/((double)pow(memoria.size()/passi, 2));
	}
	return fit;
}
