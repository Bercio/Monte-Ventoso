#ifndef SCIMMIA
#define SCIMMIA
#include <iostream>
#include <cmath>
#include <set>
#include <cstdlib>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include "parete.cpp"
#include <Snap.h>

void fill_figli_e_padri(TNGraph::TNodeI node, std::vector<int>::iterator fp, std::vector<int>::iterator fl,
                        std::vector<int>::iterator pp, std::vector<int>::iterator pl);
class Scimmia
{
    std::vector<int> dna;
    int stato;
    double fit;
    std::vector<int> memoria;
	bool loop;
public:
	void set_loop(bool l);
	bool get_loop() const;
    std::vector<int> get_dna() const;
    void set_dna(const std::vector<int> &dna);
    int scegli_azione();
    void set_memoria(int node);
    std::vector<int> get_memoria() const;
    void set_stato(TNodeEDatNet<Point,Point>::TNodeI node);
    int get_stato() const;
    double get_fit() const;
    double fit_func_lo(TNodeEDatNet<Point,Point>::TNodeI ,const Parete& g);
    double fit_func_riri(TNodeEDatNet<Point,Point>::TNodeI ,const Parete& g);
    void set_fit(double f);
	Scimmia();
    Scimmia(Scimmia& m, Scimmia& p);
    void muta(); 
    Scimmia(const Scimmia& s);
	void operator=(const Scimmia& s);
    Scimmia(std::vector<int>& _dna);
    int move(TNodeEDatNet<Point,Point>::TNodeI pos);
};
#endif
