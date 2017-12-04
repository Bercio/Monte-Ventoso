//
// Created by rita on 20/11/17.
//
#include <iostream>
#include "evoluzione.h"
#include <Snap.h>
#include <random>
using namespace std;
int main(){
Parete parete = rnd_solvable_parete(1000,70,100,3,0.2,0.2,3, rand());
vector<int> DNA {0,0,1,1,2,2,2,2,3,3,3,3,2,2,2,2,3, 0, 1, 0, 0, 2, 1, 2, 0, 3, 1, 3, 2, 3, 2, 3};
Scimmia scimmia (DNA);
scimmia.traverse(parete, 300);
vector<int> v(scimmia.get_memoria());
    cout<<scimmia.get_memoria().back() << endl;
    cout<<parete.get_endID()<<endl<<endl;
}
//configurazioni: 0:niente, 1 fn, 2 pn, 3 pn fn, 4 fi, 5 fi fn, 6 fi pn,

