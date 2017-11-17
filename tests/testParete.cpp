//
// Created by bercio on 05/12/16.
//
#include "../parete.h"
#include <gtest/gtest.h>
#include <Snap.h>
#include <random>
using namespace std;
class PareteTest: public testing::Test {
public:
   Parete P;
   Parete G;
    Parete X;
    TPt<TNodeEDatNet<Point,Point>> AC;
   vector<Point> v;
    int N, x, y, d, min_depth;
    double prob_appo, prob_appi;
    PareteTest(){
        N = 100; d = 5; x = 50; y = 100; min_depth = 3; prob_appo=0.2; prob_appi= 0.3;
        default_random_engine gen;
        for (int i =0; i < 50; ++i) {
            v.push_back(Point(i / 2, i));
        }
        X = Parete(v,3,0,0, min_depth);
        G = rnd_solvable_parete(N,x,y,d,prob_appo,prob_appi,min_depth);
        P = G;
        AC = TSnap::GetMxWcc(X.get_p());
    }
};

TEST_F(PareteTest, constructtest) {
    Point a = X.get_p()->GetNDat(X.get_startID());
    Point b = X.get_p()->GetNDat(X.get_endID());
    Point aa(0,0);
    Point bb((50-1)/2,50-1);
    EXPECT_EQ(a, aa);
    EXPECT_EQ(b, bb);
    EXPECT_EQ(P, G);
    EXPECT_NE(X, G);
}
TEST_F(PareteTest, ArgsEffect){
    Parete T;
    T = rnd_solvable_parete(N,x,y,d,prob_appo,prob_appi,2);
    EXPECT_LE(G.get_p()->GetNodes(),T.get_p()->GetNodes());
    Parete M(v,10,0.1,0.3,8);
    EXPECT_GT(AC->GetNodes(), TSnap::GetMxWccSz(M.get_p()));
}
TEST_F(PareteTest, Grafica){
    Parete T;
    T = rnd_solvable_parete(300, x, y, 5, prob_appo, prob_appi, 2);
    /* T.set_window(v);
    T.draw(T.get_startID(),v);
    EXPECT_NO_FATAL_FAILURE(T.draw(T.get_startID(),w)); */
    vector<int> v;
    for(auto i = T.get_p()->BegNI(); i < T.get_p()->EndNI(); i++){
        v.push_back(i.GetId());
    }
    T.animate(v,"titolo");
}


