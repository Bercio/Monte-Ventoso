#include <vector>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

struct s {
    unsigned int b : 3;
    s(int arg) : b(arg) { }
    s():ar
};

int main(){
    int N = 100000000;
    default_random_engine gen;
    uniform_int_distribution<int> range(1,N-1);
    clock_t t, t1, t2 ,t3;
    vector<s> v(N);
    vector<s> w(N);
    vector<s> u(N);
    t1 = clock();
    int rnd = range(gen);
    auto l = copy_n(w.begin(), rnd, v.begin());
    copy(u.begin()+rnd,u.end(), l);
    t1 -= clock();
    t = clock();
    uniform_int_distribution<s> actions(0,3);
    auto acts = bind(actions,gen);
    generate(v.begin(),v.end(), [&](){ return s(acts())});
    t -= clock();

    t2 = clock();
    v[range(gen)] = acts();
    t2 -= clock();

    t3 = clock();
    vector<s> vv(v);
    t3 -= clock();
    cout << "tempo di copia di un vettore lungo " << N << ": " << ((float)t3)/CLOCKS_PER_SEC
         << "tempo di generazione random : " << ((float)t)/CLOCKS_PER_SEC << 
         "tempo di crossover :" << ((float)t1)/CLOCKS_PER_SEC << "tempo di accesso random : " <<
         ((float)t2)/CLOCKS_PER_SEC;
}


    



