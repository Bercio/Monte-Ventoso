#include <iostream>
#include "evoluzione.h"
#include <Snap.h>
#include <random>
using namespace std;
int main(){
    Evoluzione e(100,100,0.7,0.3);//100 passi 100 individui 0.8 pcross 0.2 pmuta
    e.change_parete(1000,70,100,3,0.2,0.2,3);//N=
    e.new_gen();
    int N_evoluzioni = 700;
    for(int i = 0; i < N_evoluzioni; ++i) {
        e.evoluzione();
    }
    vector<int> v(e.best_scimmia().get_memoria());
    cout<<e.best_scimmia().get_memoria().back() << endl;
    cout<<e.getParete().get_endID()<<endl<<endl;
    for (int i=0;i<e.best_scimmia().get_dna().size(); i++){cout<<e.best_scimmia().get_dna()[i]<<", ";};
    cout<<endl;
    //expected: 0,0,1,1,2,2,2,2,3,3,3,3,2,2,2,2
    e.getParete().animate(v,"titolo");
}
//configurazioni: 0:niente, 1 fn, 2 pn, 3 pn fn, 4 fi, 5 fi fn, 6 fi pn,
