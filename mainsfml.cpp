#include <iostream>
#include "evoluzione.h"
#include <Snap.h>
#include <random>
using namespace std;
int main(){
    for(int k=0; k<1; k++)
    {
        Evoluzione e(300,100,0.7,0.3);//100 passi 100 individui 0.8 pcross 0.2 pmuta
        e.change_parete(1000,70,100,3,0.2,0.2,3);//N=
        e.new_gen();
        int N_evoluzioni = 10;

        for(int i = 0; i < N_evoluzioni; ++i) {cout<<"evoluzione "<<i<<endl;
            e.evoluzione();
            for (int i=0;i<e.best_scimmia().get_dna().size(); i++){cout<<e.best_scimmia().get_dna()[i]<<", ";};
            if(e.best_scimmia().get_memoria().size()>300){cout<<"la mem strippa"<<endl;}
        }
        vector<int> v(e.best_scimmia().get_memoria());
        cout<<k<<"° prova"<<endl;
        for (int i=0;i<e.best_scimmia().get_dna().size(); i++){cout<<e.best_scimmia().get_dna()[i]<<", ";};
        cout<<endl;
        cout<<"dna size "<<e.best_scimmia().get_dna().size();
        cout<<"passi "<<e.best_scimmia().get_memoria().size()<<endl;
        cout<<"loop "<<e.best_scimmia().get_loop()<<endl<<endl;
        cout<<"fit " <<e.best_scimmia().get_fit()<<endl;
        //expected: 0,0,1,1,2,2,2,2,3,3,3,3,2,2,2,2 dove 0 figli noti, 1 padri noti, 2 figli ignoti, padri ignoti
        //if(e.best_scimmia().get_memoria().back()!=e.getParete().get_endID()) {
            e.getParete().animate(v,"titolo");
            cout<<"loop "<<e.best_scimmia().get_loop()<<endl<<endl;
            break;
       // }
    }
}
//configurazioni: 0:niente, 1 fn, 2 pn, 3 pn fn, 4 fi, 5 fi fn, 6 fi pn,
// 7 fn pn fi, 8 pi, 9 pi fn, 10 pi pn, 11 pi pn fn, 12 pi fi, 13 pi fi fn, 14 pi fi pn, 15 pi fi pn fn
