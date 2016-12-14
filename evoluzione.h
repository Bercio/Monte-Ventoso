//
// Created by bercio on 14/12/16.
//
#ifndef SISTEMI_COMPLESSI_EVOLUZIONE_H
#define SISTEMI_COMPLESSI_EVOLUZIONE_H

#include <random>
#include "scimmia.h"
#include <stdlib.h>
#include <iomanip>
#include <functional>
#include "Snap.h"

Parete GeneraParete(int N=1000, int x=70, int y=100, int d=3, double prob_appo=0.2, double prob_appi=0.2,int min_depth=2);
void riproduzione(std::vector<Scimmia>& generazione, double p_crosso, double p_muta);
void evoluzione(int n_passi, double p_cross, double p_muta, Parete& parete, std::vector<Scimmia>& generazione,
                std::function<double(Scimmia&, TNodeEDatNet<Point,Point>::TNodeI&, const Parete&)> fit_func);
Scimmia best_scimmia(std::vector<Scimmia>& generazione);

#endif //SISTEMI_COMPLESSI_EVOLUZIONE_H
