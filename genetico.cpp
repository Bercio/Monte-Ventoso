#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <random>
#include <algorithm>
#include <Snap.h>
#include "genetico.h"
using namespace std;
using namespace TSnap;

int N = 0b1111 + 1;
random_device rd;
default_random_engine gen(rd());
//max situazioni; Padri non tutti visitati,figli non tutti visitati,alcuni padri visitat,
//alcuni figli visitati;

void fill_figli_e_padri(TNGraph::TNodeI node, std::vector<int>::iterator fp, std::vector<int>::iterator fl,
                        std::vector<int>::iterator pp, std::vector<int>::iterator pl) {
    for (int i = 0; i < node.GetOutDeg(); ++i) {
        int id = node.GetOutNId(i);
        if (id < node.GetId()){
            *pp = id;
            ++pp;
        }
        else {
            *fp = id;
            ++fp;
        }
    }
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    std::uniform_int_distribution<int> dis(0, (int) (std::distance(start, end) - 1));
    std::advance(start, dis(gen));
    return start;
}


int Scimmia::scegli_azione(){
    return dna[stato];
    }

void Scimmia::set_memoria(int node){
    memoria.push_back(node);
    }

void Scimmia::set_stato(TNGraph::TNodeI node){
    bool fn=0,pn(0),fi(0),pi(0);
    for (int i = 0; i < node.GetOutDeg(); ++i){
        int fnode = node.GetOutNId(i);
        if (fnode < node.GetId()) {
            if (find(memoria.begin(), memoria.end(), fnode) != memoria.end()) {
                pn = 1;
            } else pi = 1;
        } else {
            if (find(memoria.begin(),memoria.end(), fnode)!= memoria.end()){
                fn = 1;
            } else fi = 1;
        }
    }
    stato = fn + pn*2 + fi*4 + pi*8;
}

Scimmia::Scimmia(): dna(N), fit(0), nodi_visitati(1), loop(false){
    uniform_int_distribution<int> actions(0,3);
    generate(dna.begin(),dna.end(),[&](){return actions(gen);});
    }

Scimmia::Scimmia(Scimmia& m, Scimmia& p): fit(0), nodi_visitati(1), loop(false) {
    vector<int> _dna(N);
    uniform_int_distribution<int> range(1,14);
    int rnd = range(gen);
    vector<int> primo = m.get_dna();
    vector<int> secondo = p.get_dna();
    auto l = copy_n(primo.begin(), rnd, _dna.begin());
    copy(secondo.begin()+rnd,secondo.end(), l );
    set_dna(_dna);
    }


void Scimmia::muta(){ 
    uniform_int_distribution<int> range(0,N-1);
    uniform_int_distribution<int> actions(0,3);
    vector<int> _dna = get_dna();
    _dna[range(gen)] = actions(gen);
    set_dna(_dna);
    }

Scimmia::Scimmia(Scimmia& s): fit(0), nodi_visitati(1), loop(false) {
    set_dna(s.get_dna());
}

double Scimmia::get_fit(){ return fit;}

Scimmia::Scimmia(vector<int>& _dna): dna(_dna), fit(0), nodi_visitati(1), loop(false) {;
    }

void Scimmia::set_fit_locale(int pos, PNGraph g){
    TNGraph::TNodeI end  = g->EndNI();
    end--;
    int endi = end.GetId();
	

	if(loop==false){	
		fit_locale=((double)nodi_visitati.size()-1)/(double)memoria.size();
	 	for (int k=0; k<nodi_visitati.size(); k++) fit_locale+=(double)nodi_visitati[k]/(double)memoria.size();
	}
	else {
		fit_locale=(((double)nodi_visitati.size()-1))/(double)memoria.size(); 
		for (int k=0; k<nodi_visitati.size(); k++) fit_locale+=0.01*(double)nodi_visitati[k]/(double)memoria.size();
	}
}

double Scimmia::get_fit_locale(){return fit_locale;}

void Scimmia::set_fit(double f){fit+=f;}

void Scimmia::set_dna(const vector<int> &dna) {
    Scimmia::dna = dna;
}

vector<int> Scimmia::get_dna() {
    return dna;
}
vector<int> Scimmia::get_memoria(){ return memoria;}

int Scimmia::get_stato(){ return stato;}

vector<int> Scimmia:: get_nodi_visitati(){return nodi_visitati;}

void Scimmia::set_nodi_visitati(int node)
{bool presente=false;
for (int i=0; i<nodi_visitati.size(); i++){if(node!=nodi_visitati[i]) continue; else {presente=true; break;}}
if(presente==false) nodi_visitati.push_back(node);
}

void Scimmia::set_loop(bool l){loop=l;}

bool Scimmia::get_loop(){return loop;}



enum Azione {a_f_noto=0, a_p_noto, a_f_ignoto, a_p_ignoto};

int Scimmia::move(TNGraph::TNodeI pos)
{
    vector<int> padri_n, padri_ig, figli_n, figli_ig;

    for(int i = 0; i<pos.GetOutDeg(); ++i){

        int outNode = pos.GetOutNId(i);
        if (outNode < pos.GetId()){
            if (find(memoria.begin(),memoria.end(), outNode)!= memoria.end()) padri_n.push_back(outNode);
            else padri_ig.push_back(outNode);
        } else if (find(memoria.begin(),memoria.end(), outNode)!= memoria.end()) figli_n.push_back(outNode);
        else figli_ig.push_back(outNode);
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
    }
}

