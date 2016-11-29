#include <iostream>
#include <cmath>
#include <set>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>
#include "Snap.h"
using namespace std;
using namespace TSnap;

int N = 0b1111 + 1;

default_random_engine gen;
//max situazioni; Padri non visitati,figli non visitati,padri visitat, 
//figli visitati;

void fill_figli_e_padri(TNGraph::TNodeI node, vector<int> f, vector<int> p){
    for (int i = 0; i < node.GetOutDeg(); ++i) {
        int id = node.GetOutNId(i);
        if (id > node.GetId()) p.push_back(id);
        else f.push_back(id);
    }
}

struct Scimmia
{
    vector<int> dna;
    int stato;
    vector<int> memoria;
    int scegli_azione(){
        return dna[stato];
    }
    void set_memoria(int node){
        memoria.push_back(node);
    }
    void set_stato(TNGraph::TNodeI node){
        vector<int> f,p;
        fill_figli_e_padri(node,f,p);
        auto remember =  [&](auto& e){ 
            return find(memoria.begin(), memoria.end(), e) != memoria.end();
        };
        stato = any_of(f.begin(),f.end(), remember) +
                any_of(p.begin(),p.end(), remember)*2 +
                !all_of(f.begin(),f.end(),remember)*4 +
                !all_of(p.begin(),p.end(),remember)*8;
    }
    Scimmia(){
        dna = vector<int>(N);
        uniform_int_distribution<int> actions(0,3);
        generate(dna.begin(),dna.end(),[&](){return actions(gen);});
    }
    Scimmia(Scimmia m, Scimmia p){
        dna = vector<int>(N);
        uniform_int_distribution<int> range(1,14);
        int rnd = range(gen);
        auto l = copy_n(m.dna.begin(), rnd, dna.begin());
        copy(p.dna.begin()+rnd,p.dna.end(), l);
    }

    void muta(){ 
        uniform_int_distribution<int> range(0,N);
        uniform_int_distribution<int> actions(0,3);
        dna[range(gen)] = actions(gen);
    }

    Scimmia clona(){ return Scimmia(dna);
    }

    Scimmia(vector<int> _dna): dna(_dna) {;
    }

    int fit_distanza(int pos, PNGraph g){
        int end = g->EndNI().GetId();
        return pow((GetShortPath(g, pos,end)* memoria.size()),-2);
    }

};

enum Azione {a_f_noto, a_p_noto, a_f_ignoto, a_p_ignoto };

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    std::uniform_int_distribution<int> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(gen));
    return start;
}

int move(Scimmia r, TNGraph::TNodeI pos){
    vector<int> figli_n,padri_n,figli_ig,padri_ig;
    vector<int> figli,padri;
    fill_figli_e_padri(pos, figli,padri);
    vector<int>::iterator  fb(figli.begin()), fe(figli.end()),pb(padri.begin()),
                           pe(padri.end()), mb(r.memoria.begin()),
                           me(r.memoria.end()), fne,fie,pne,pie;

    fne = set_intersection(fb,fe,mb,me,figli_n.begin() );
    fie = set_difference(fb,fe,mb,me, figli_ig.begin() );
    pne = set_intersection(pb,pe,mb,me, padri_n.begin() );
    pie = set_difference(pb,pe,mb,me, padri_ig.begin() );

    switch(r.scegli_azione())
    { 
        case a_f_noto:
            return (fne != figli_n.begin()) ?  *select_randomly(figli_n.begin(),fne) : pos.GetId();
        case a_p_noto:
            return (pne != padri_n.begin()) ?  *select_randomly(padri_n.begin(),pne) : pos.GetId();
        case a_f_ignoto:
            return (fie != figli_ig.begin()) ?  *select_randomly(figli_ig.begin(),fie) : pos.GetId();
        case a_p_ignoto:
            return (pie != padri_ig.begin()) ?  *select_randomly(padri_ig.begin(),pie) : pos.GetId();
    }
}


