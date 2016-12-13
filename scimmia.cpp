#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <random>
#include <algorithm>
#include <Snap.h>
#include "scimmia.h"
using namespace std;
using namespace TSnap;

int N = 0b1111 + 1;
random_device rd;
default_random_engine gen(rd());
//max situazioni; Padri non tutti visitati,figli non tutti visitati,alcuni padri visitat,
//alcuni figli visitati;

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

//QUI

void Scimmia::set_stato(TNodeEDatNet<Point,Point>::TNodeI node){
    bool fn=0,pn(0),fi(0),pi(0);
    for (int i = 0; i < node.GetOutDeg(); ++i){
        int fnode = node.GetOutEDat(i).Val2;
        if (fnode < 0) {
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

Scimmia::Scimmia(): dna(N), fit(0), loop(false), stato(0), memoria({}){
    uniform_int_distribution<int> actions(0,3);
    generate(dna.begin(),dna.end(),[&](){return actions(gen);});
    }

Scimmia::Scimmia(Scimmia& m, Scimmia& p): fit(0), loop(false),stato(0), memoria({}) {
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

Scimmia::Scimmia(const Scimmia& s): fit(0), loop(false),memoria({}), stato(0) {
    set_dna(s.get_dna());
}

double Scimmia::get_fit()const { return fit;}

Scimmia::Scimmia(vector<int>& _dna): dna(_dna), fit(0), loop(false) {;
    }

void Scimmia::set_fit(double f){fit+=f;}

double Scimmia::fit_func_lo(TNodeEDatNet<Point,Point>::TNodeI n, const Parete& g){
	if(loop==false){
    	return pow(g.get_p()->GetNDat(g.get_endID()).dist(n.GetDat()),-2)*pow(memoria.size(),-1);}
	else return {0.1*pow(g.get_p()->GetNDat(g.get_endID()).dist(n.GetDat()),-1)*pow(memoria.size(),-1)};

    }


double Scimmia::fit_func_riri(TNodeEDatNet<Point,Point>::TNodeI n, const Parete& g)
{	double fit;
	double normalizzazione=1;
	set<int> nodi_visitati(memoria.begin(),memoria.end());
	//for (int i=0; i<g.get_endID(); i++) normalizzazione+=i;
	if(loop==false){

		fit=((double)nodi_visitati.size()-1)/pow((double)memoria.size(),2);
	 	for (auto k : nodi_visitati) {fit+=g.get_p()->GetNDat(k).Val2/(normalizzazione*(double)pow(memoria.size(), 2));}
	}
	else {
		fit=(0.01*((double)nodi_visitati.size()-1))/pow((double)memoria.size(), 2);
		for (auto k : nodi_visitati) fit+=0.01*g.get_p()->GetNDat(k).Val2/(normalizzazione*(double)pow(memoria.size(), 2));
	}
	return fit;
}


void Scimmia::set_dna(const vector<int>& _dna) {
    this->dna = _dna;
}

vector<int> Scimmia::get_dna() const {
    return dna;
}
vector<int> Scimmia::get_memoria()const{ return memoria;}

int Scimmia::get_stato() const { return stato;}

void Scimmia::set_loop(bool l){loop=l;}

bool Scimmia::get_loop() const {return loop;}

void Scimmia::operator=(const Scimmia& s) { memoria=s.get_memoria(); fit=s.get_fit();
											 loop=s.get_loop(); dna=s.get_dna(); stato=s.get_stato();
}


enum Azione {a_f_noto=0, a_p_noto, a_f_ignoto, a_p_ignoto};

int Scimmia::move(TNodeEDatNet<Point,Point>::TNodeI pos){
    vector<int> padri_n, padri_ig, figli_n, figli_ig;
    for(int i = 0; i<pos.GetOutDeg(); ++i){

        int outNode = pos.GetOutEDat(i).Val2;
        int IDoutNode = pos.GetOutNId(i);
        if (outNode < 0){
            if (find(memoria.begin(),memoria.end(), IDoutNode)!= memoria.end()) padri_n.push_back(IDoutNode);
            else padri_ig.push_back(IDoutNode);
        } else if (find(memoria.begin(),memoria.end(), IDoutNode)!= memoria.end()) figli_n.push_back(IDoutNode);
        else figli_ig.push_back(IDoutNode);
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




