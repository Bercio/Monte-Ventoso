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
        N = 50; d = 10; x = 50; y = 100; min_depth = 3; prob_appo=0.2; prob_appi= 0.3;
        G = get_random_p(N,x,y,d,prob_appo,prob_appi,min_depth);
        P = G;
        default_random_engine gen;
        for (int i =0; i < 50; ++i) {
            v.push_back(Point(i / 2, i));
        }
        X = Parete(v,2,0,0, min_depth);
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
    T = get_random_p(N,x,y,d,prob_appo,prob_appi,4);
    EXPECT_LE(G.get_p()->GetNodes(),T.get_p()->GetNodes());
    Parete M(v,10,0.1,0.3,8);
    EXPECT_GT(AC->GetNodes(), TSnap::GetMxWccSz(M.get_p()));
    Parete U = get_random_p(100,x,y,d,0.6,prob_appi,min_depth);
    EXPECT_GT(U.get_p()->GetNodes(),G.get_p()->GetNodes());
    X.write_schema("X.png");
    M.write_schema("M.png");
    U.write_schema("U.png");
}
