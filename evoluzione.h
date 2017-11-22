//
// Created by bercio on 14/12/16.
//
#ifndef SISTEMI_COMPLESSI_EVOLUZIONE_H
#define SISTEMI_COMPLESSI_EVOLUZIONE_H

#include <random>
#include "scimmia.h"
#include <iostream>
#include <functional>

class Evoluzione {
    Parete parete;
    std::vector<Scimmia> generazione;
    double p_cross, p_muta;
    std::function<double(Scimmia &, TNodeEDatNet<Point, Point>::TNodeI &, const Parete &)> fit_func;
public:
    const Parete &getParete() const;

    const std::vector<Scimmia> &getGenerazione() const;

    double getP_cross() const;

    double getP_muta() const;

    const std::function<double(Scimmia &, TNodeEDatNet<Point, Point>::TNodeI &, const Parete &)> &getFit_func() const;

    int getPassi() const;

    int getIndividui() const;

private:
    int passi, individui;
public:
    void change_parete(int N = 1000, int x = 70, int y = 100, int d = 3, double prob_appo = 0.2, double prob_appi = 0.2,
                       int min_depth = 3);

    void riproduzione();

    void evoluzione();

    Scimmia best_scimmia();

    Evoluzione();

    void new_gen();

    Evoluzione(int passi, int individui, double p_cross, double p_muta);

    void set_individui(int _individui);

    void set_passi(int _passi);

    void set_pcross(double _p_cross);

    void set_pmuta(double _p_muta);

    void set_fitfunc(std::function<double(Scimmia &, TNodeEDatNet<Point, Point>::TNodeI &, const Parete &)> _fit_func);


};
#endif //SISTEMI_COMPLESSI_EVOLUZIONE_H
