//
// Created by bercio on 14/12/16.
//
#include "evoluzione.h"
using namespace std;
int main(){
    Parete p = GeneraParete();
    vector<Scimmia> gen(300);
    for(int i = 0; i < 1000; ++i) {
        evoluzione(100, 0.8, 0.1, p, gen, &Scimmia::fit_func_lo);
    }
    cout << best_scimmia(gen).get_fit();
}

