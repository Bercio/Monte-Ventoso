//
// Created by bercio on 15/12/16.
//
#include <iostream>
#include "evoluzione.h"
using namespace std;
int main(){
    Evoluzione e(100,100,0.8,0.2);
    e.change_parete(2000,100,50,3,0.2,0.2,3);
    e.new_gen();
    int N = 1000;
    double time = clock();
    for(int i = 0; i < N; ++i) {
        e.evoluzione();
    }
    cout << "tempo impiegato per fare " << N << "evoluzioni con " << e.getIndividui() << "scimmie "
         "e una parete di " << e.getParete().get_p()->GetNodes() << " Nodi = " << (clock()-time)/CLOCKS_PER_SEC;
}

