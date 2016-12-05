
#ifndef SCIMMIA
#define SCIMMIA
#include <iostream>
#include <cmath>
#include <set>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>
#include <Snap.h>

void fill_figli_e_padri(TNGraph::TNodeI node, std::vector<int>::iterator fp, std::vector<int>::iterator fl,
                        std::vector<int>::iterator pp, std::vector<int>::iterator pl);
class Scimmia
{
    std::vector<int> dna;
    int stato;
    double fit;
	double fit_locale;
    std::vector<int> memoria;
	std::vector<int> nodi_visitati;
	
public:

    std::vector<int> get_dna();
    void set_dna(const std::vector<int> &dna);
    int scegli_azione();
    void set_memoria(int node);
    std::vector<int> get_memoria();
    void set_stato(TNGraph::TNodeI node);
    int get_stato();
    double get_fit();
   	void set_fit(double f); 
	void set_fit_locale(int pos, PNGraph g);
	double get_fit_locale();
	std::vector<int> get_nodi_visitati();
	void set_nodi_visitati(int node);
	Scimmia();
    Scimmia(Scimmia& m, Scimmia& p);
    void muta(); 
    Scimmia(Scimmia& s);
    Scimmia(std::vector<int>& _dna);
    int move(TNGraph::TNodeI pos);
};
#endif