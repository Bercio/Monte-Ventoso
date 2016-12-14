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
#include "parete.h"
#include <Snap.h>

class Scimmia
{
    std::vector<int> dna;
    int stato;
    double fit;
    std::vector<int> memoria;
	bool loop;
	enum Azione {a_f_noto=0, a_p_noto, a_f_ignoto, a_p_ignoto};
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
    Scimmia clona();
    double get_fit() const;
    double fit_func_lo(TNodeEDatNet<Point,Point>::TNodeI& n,const Parete& g);
    double fit_func_riri(TNodeEDatNet<Point,Point>::TNodeI& n ,const Parete& g);
    void set_fit(double f);
	Scimmia();
	void friend swap(Scimmia& f, Scimmia& s);
    Scimmia(Scimmia& m, Scimmia& p);
    void muta(); 
    Scimmia(const Scimmia& s);
	bool is_looping(int passi);
	TNodeEDatNet<Point,Point>::TNodeI traverse(Parete parete, int n_passi);
	Scimmia operator=(Scimmia s);
    Scimmia(std::vector<int>& _dna);
    int move(TNodeEDatNet<Point,Point>::TNodeI pos);
};
#endif
