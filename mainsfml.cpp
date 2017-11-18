#include <iostream>
#include "evoluzione.h"
#include <Snap.h>
#include <random>
using namespace std;
int main(){
    Evoluzione e(100,100,0.8,0.2);//100 passi 100 individui 0.8 pcross 0.2 pmuta
    e.change_parete(100,100,50,3,0.2,0.2,3);
    e.new_gen();
    int N = 100;
    for(int i = 0; i < N; ++i) {
        e.evoluzione();
    }
    vector<int> v(e.best_scimmia().get_memoria());

    e.getParete().animate(v,"titolo");
    cout<<e.best_scimmia().get_memoria().back() << endl;
}

