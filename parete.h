//
// Created by bercio on 05/12/16.
//

#ifndef SISTEMI_COMPLESSI_GRAPH_H
#define SISTEMI_COMPLESSI_GRAPH_H
#include "Snap.h"
#include <cstdlib>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h>
struct Point : public TIntPr {
    Point();
    double dist(Point p);
    Point(int _Val1, int _Val2);
    Point operator-(const Point& p);
};
class Parete : public TNodeEDatNet<Point,Point> {
    int d_nodi;
    double prob_appiglio;
    double prob_appoggio;
    int end;
    int start;
    int min_depth;
    TPt<Parete> PParete;
    void norm_coord();
    bool is_viable();
    void set_start();
    void set_end();

public:
    Parete(std::vector<Point> ret, int d, double p_ap, double p_appi, int min_depth);
    Parete(int N, int x, int y, int d, double p_ap, double p_appi, int min_depth);
    void write_schema(TStr filename);
};
#endif //SISTEMI_COMPLESSI_GRAPH_H
