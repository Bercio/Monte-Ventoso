#ifndef SCIMMIA
#define SCIMMIA
#include <cmath>
#include <string>
#include <set>
#include <cstdlib>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include "parete.h"

class Scimmia
{
    std::vector<int> dna;
    int stato;
    double fit;
    std::vector<int> memoria;
	bool loop;
	enum Azione {a_f_noto=0, a_p_noto, a_f_ignoto, a_p_ignoto, a_n_precedente};
	std::set<int> memset;
public:
	void set_loop(bool l);
	bool get_loop() const;
    std::vector<int> get_dna() const;
    void set_dna(const std::vector<int> &dna);
    int scegli_azione();
    void set_memoria(const int& node);
    std::vector<int> get_memoria() const;
    void set_stato(const TNodeEDatNet<Point,Point>::TNodeI& node);
    int get_stato() const;
    double get_fit() const;
    double fit_func_lo(TNodeEDatNet<Point,Point>::TNodeI& n,const Parete& g, int passi);
    double fit_func_riri(TNodeEDatNet<Point,Point>::TNodeI& n ,const Parete& g, int passi);
    void set_fit(double f);
	Scimmia();
    Scimmia(Scimmia& m, Scimmia& p);
    void muta(); 
	bool is_looping(const int& passi);
	TNodeEDatNet<Point,Point>::TNodeI traverse(const Parete& parete, int n_passi);
    Scimmia(std::vector<int> _dna);
    Scimmia operator=(const Scimmia& m);
    int move(const TNodeEDatNet<Point,Point>::TNodeI& pos);
};
#endif
