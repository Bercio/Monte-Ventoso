//
// Created by bercio on 15/12/16.
//
#include "evoluzione.h"
using namespace std;
int main(){
    Evoluzione e(100,100,0.8,0.2);
    e.change_parete(2000,100,500,3,0.2,0.2,3);
    double time = clock();
    for(int i = 0; i < 100; ++i) {
        e.evoluzione(&Scimmia::fit_func_lo);
    }
    e.animate();
}

