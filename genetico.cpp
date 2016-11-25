#include<iostream>
#include <set>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
#define N_INDIV 50 //individui della popolazione
#define PCROSS 0.8
#define PMUT 0.2
int N = 0b1111 + 1;
_random_engine gen;
//max situazioni; Padri non visitati,figli non visitati,padri visitat, 
//figli visitati;

struct Scimmia
{
    vector<int> dna(N);
    int stato;
    set<Node> memoria;
    int scegli_azione(){
        return dna[stato];
    }
    void set_stato(Node node){
        vector<Node> f(node.figli()), p(node.padri());
        //TODO: implement Node and Node::figli()
        stato = any_of(f.begin(),f.end(), memoria.count) +
                any_of(p.begin(),p.end(), memoria.count)*2 +
                !all_of(f.begin(),f.end(), memoria.count)*4 +
                !all_of(p.begin(),p.end(), memoria.count)*8;
    }
    Scimmia(){
        uniform_int_distribution<int> range(0,3);
        generate(dna.begin(),dna.end(),[](){return range(gen););
    }
    Scimmia(Scimmia m, Scimmia p){
        uniform_int_distribution<int> range(1,14);
        int rnd = range(gen);
        auto l = copy_n(m.dna.begin(), rnd, back_inserter(dna));
        copy(p.dna.begin()+rnd,p.dna.end(), inserter(dna,l));
    }
    Scimmia(vector<int> _dna): dna(_dna) {;
    }
}

int fit_distanza(Node stato, Graph g){
    return g.shortest_dist(stato,g.end);
}

enum Azione {a_f_noto, a_p_noto, a_f_ignoto, a_p_ignoto };

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    std::uniform_int_distribution<int> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(gen));
    return start;
}

Node move(Scimmia r, Node pos){
    vector<Node> figli_n,padri_n,figli_ig,padri_ig;
    vector<Node>::iterator fb(pos.figli.begin()), fe(pos.figli.end()), pb(pos.padri.begin()),
                           pe(pos.padri.end()), mb(r.memoria.begin()), me(r.memoria.end()),
                           fne,fie,pne,pie;

    fne = set_intersection(fb,fe,mb,me,figli_n.begin() );
    fie = set_difference(fb,fe,mb,me, figli_i.begin() );
    pne = set_intersection(pb,pe,mb,me, padri_n.begin() );
    pie = set_difference(pb,pe,mb,me, padri_i.begin() );

    switch(r.scegli_azione())
    { 
        case a_f_noto:
            (fne != figli_n.begin()) ?  return *select_randomly(figli_n.begin(),fne) : return pos;
        case a_p_noto:
            (pne != padri_n.begin()) ? return *select_randomly(padri_n.begin(),pne) : return pos;
        case a_f_noto:
            (fie != figli_i.begin()) ? return *select_randomly(figli_i.begin(),fie) : return pos;
        case a_f_noto:
            (pie != padri_i.begin()) ? return *select_randomly(padri_i.begin(),pie) : return pos;
    }
}

/*
devo fare una matrice 15x4 che definisca tutte le possibili configurazioni che il ragno si trova davanti e far corrisponere a ogni vettore una funzione.
*/
/*
funzione GUARDA: legge l'albero, ritorna un array che ha già riempito.
in ragno: c'è una funzione che riceve l'array, returna l'azione corrispondente dell'individuo-ragno;


dove scrivo che il ragno dati certi imput restituisce degli output?
