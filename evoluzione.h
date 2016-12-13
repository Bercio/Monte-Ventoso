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

Parete GeneraParete(int, int, int, int , double, double, double, int);
void riproduzione(std::vector<Scimmia>& generazione, double p_crosso, double p_muta);
void evoluzione(int n_passi, double p_cross, double p_muta, Parete& parete, vector<Scimmia>& generazione,
                function<double(const Scimmia&, TNodeEDatNet<Point,Point>::TNodeI&, Parete&)> fit_func);
Scimmia best_scimmia(vector<Scimmia>& generazione);

#endif //SISTEMI_COMPLESSI_EVOLUZIONE_H
