#include "genetico.h"
#include "gtest/gtest.h"
using namespace std;
using namespace TSnap;

class GraphTest: public testing::Test {
    int Fanout;
    int Levels;
public:
    PNGraph NGraph;
    GraphTest(){
      Fanout = 4;
      Levels = 5;
      NGraph = GenTree<PNGraph>(Fanout, Levels, true, true);
    }
};

class ScimmiaTest: public testing::Test {
    Scimmia s,p,m;
    ScimmiaTest(){
    }
};
//TEST_F(ScimmiaTest,randomDna){
 //   EXPECT_NE


TEST_F(GraphTest, figliEpadri){
    TNGraph::TNodeI n = NGraph->GetRndNI();
    vector<int> f,p;
    fill_figli_e_padri(n,f,p);
    EXPECT_EQ(p.size(),1);
    for (int i = 0; i < n.GetOutDeg(); ++i){
        if (n.GetOutNId(i) > n.GetId()){
            EXPECT_EQ(p[0], n.GetOutNId(i));
        }
        else{
            EXPECT_GT(count(f.begin(),f.end(),n.GetOutNId(i)),0);
        }
    }
}
