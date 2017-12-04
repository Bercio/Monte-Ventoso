//
// Created by rita on 21/11/17.
//

#include <iostream>
#include "evoluzione.h"
#include <Snap.h>
#include <random>
#include <fstream>
#include <iomanip>
using namespace std;
int main(){
    ofstream f("dati.txt", ios::app);
    f<<setiosflags(std::ios::left);
    //f<<setw(15)<<"seed parete"<<setw(10)<<"successo"<<setw(15)<<"fitness"<<setw(15)<<"n° passi"<<setw(30)<<"DNA"<<'\n';
    for(int k=0; k<15; k++)
    {try{
        Evoluzione e(100,100,0.7,0.3);//100 passi 100 individui 0.8 pcross 0.2 pmuta
        e.change_parete(1000,70,100,3,0.2,0.2,3);//N=
        e.new_gen();
        int N_evoluzioni = 1500;

        for(int i = 0; i < N_evoluzioni; ++i) {
            e.evoluzione();
        }
        vector<int> v(e.best_scimmia().get_memoria());
        bool successo;
        if(e.best_scimmia().get_memoria().back()==e.getParete().get_endID()) {successo=1;} else {successo=0;};
        f<<setw(15)<<e.getParete().get_seed()<<setw(10)<<successo<<setw(15)<<e.best_scimmia().get_fit()<<setw(15)<<e.best_scimmia().get_memoria().size();
        for(int j=0; j<e.best_scimmia().get_dna().size(); j++){f<<e.best_scimmia().get_dna()[j]<<' ';}
        f<<'\n';}
        catch(invalid_argument a){cout<<"parete non valida";};
    }
}
//configurazioni: 0:niente, 1 fn, 2 pn, 3 pn fn, 4 fi, 5 fi fn, 6 fi pn,
// 7 fn pn fi, 8 pi, 9 pi fn, 10 pi pn, 11 pi pn fn, 12 pi fi, 13 pi fi fn, 14 pi fi pn, 15 pi fi pn fn
