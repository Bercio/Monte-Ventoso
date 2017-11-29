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
#include <utility>
#include <string>
//#include <SFML/Graphics.hpp>
#include <stdlib.h>

struct Point : public TIntPr {
    Point();
    double dist(Point p);
    Point(int _Val1, int _Val2);
    Point operator-(const Point& p);
    bool operator==(const Point& p) const;
    Point(const Point &p);
};
class Parete {
    TPt<TNodeEDatNet<Point,Point>> p;
    int d_nodi;
    double prob_appiglio;
    double prob_appoggio;
    int end;
    int start;
    int min_depth;
    int seed;
    void norm_coord();
    bool is_viable();
    void set_start();
    void set_end();

public:
    int get_endID()const ;
    int get_startID()const ;
    int get_min_depth()const ;
    const TPt<TNodeEDatNet<Point, Point>> & get_p()const ;
    int get_d()const ;
    double get_prob_appiglio() const;
    double get_prob_appoggio() const;
    /*
    const std::tuple<double, unsigned int, unsigned int> corr() const;
        void set_window(sf::RenderWindow &window, std::string titolo) const;
    void draw(int n, sf::RenderWindow& window) const;
    void animate(std::vector<int> v, std::string titolo) const;
   */
    Parete();
    Parete(const Parete &pr);
    bool operator==(const Parete& pr) const;
    Parete(std::vector<Point> ret, int d, double p_ap, double p_appi, int min_depth);
    friend Parete rnd_solvable_parete(int N, int x, int y, int d, double prob_appo, double prob_appi,int min_depth);
    void write_schema(TStr filename);
    void set_seed(int i);
    int get_seed() const;
};
Parete rnd_solvable_parete(int N, int x, int y, int d, double prob_appo, double prob_appi,int min_depth);
#endif //SISTEMI_COMPLESSI_GRAPH_H
