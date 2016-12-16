//
// Created by bercio on 14/12/16.
//
#include "evoluzione.h"
using namespace std;
int main(){
    Evoluzione e(100,300,0.8,0.1);
    for(int i = 0; i < 100; ++i) {
        e.evoluzione(&Scimmia::fit_func_lo);
    }
    cout << e.best_scimmia().get_fit();
}

