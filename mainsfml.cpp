#include <iostream>
#include "evoluzione.h"
#include <Snap.h>
#include <random>
using namespace std;
int main(){
        Evoluzione e(100, 300, 0.7, 0.3);//100 passi 100 individui 0.8 pcross 0.2 pmuta
        e.change_parete(1000, 70, 100, 3, 0.2, 0.2, 3);//N=
        e.new_gen();
        int N_evoluzioni = 100;

        for (int i = 0; i < N_evoluzioni; ++i) {cout<<"evoluzione numero"<<i<<endl;
            e.evoluzione();
        }
        vector<int> v(e.best_scimmia().get_memoria());
        for (int i=0;i<e.best_scimmia().get_dna().size(); i++){cout<<e.best_scimmia().get_dna()[i]<<", ";};
        cout<<endl;
        cout<<"dna size "<<e.best_scimmia().get_dna().size()<<endl;
        cout<<"passi "<<e.best_scimmia().get_memoria().size()<<endl;
        cout<<"loop "<<e.best_scimmia().get_loop()<<endl<<endl;
        cout<<"fit " <<e.best_scimmia().get_fit()<<endl;
            e.getParete().animate(v,"titolo");
            cout<<"loop "<<e.best_scimmia().get_loop()<<endl<<endl;
}
//configurazioni: 0:niente, 1 fn, 2 pn, 3 pn fn, 4 fi, 5 fi fn, 6 fi pn,
// 7 fn pn fi, 8 pi, 9 pi fn, 10 pi pn, 11 pi pn fn, 12 pi fi, 13 pi fi fn, 14 pi fi pn, 15 pi fi pn fn
