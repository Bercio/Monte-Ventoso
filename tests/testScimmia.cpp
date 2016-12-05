#include <string>
#include <gtest/gtest.h>
#include <iostream>
#include "../scimmia.h"

using namespace std;
using namespace TSnap;

class GraphTest: public testing::Test {
    int Fanout;
    int Levels;
public:
    PNGraph NGraph;
    TNGraph::TNodeI N;
    GraphTest(){
      Fanout = 4;
      Levels = 3;
      NGraph = GenTree<PNGraph>(Fanout, Levels, false, false);
    do {
        N = NGraph->GetRndNI();
    } while (N.GetOutDeg() != 5);

    }
};


//TEST_F(GraphTest,randomDna){
 //   EXPECT_NE


TEST_F(GraphTest, figliEpadri){
    vector<int> f(N.GetOutDeg()-1),p(1);
    fill_figli_e_padri(N, f.begin(),f.end(),p.begin(),p.end());
    EXPECT_EQ(f.size(),N.GetOutDeg()-1);
    ASSERT_EQ(p.size(),1);
    for (int i = 0; i < N.GetOutDeg(); ++i){
        if (N.GetOutNId(i) > N.GetId()) EXPECT_EQ(count(f.begin(),f.end(),N.GetOutNId(i)),1);
        else EXPECT_EQ(count(p.begin(),p.end(),N.GetOutNId(i)),1);
        }
}
TEST_F(GraphTest, set_state){
    vector<int> di (16, 1);
    di[12] = 3;
    Scimmia s(di);
   s.set_stato(N);
   EXPECT_EQ(s.get_stato(),12);
   ASSERT_EQ(s.get_dna().size(),16);
   EXPECT_EQ(s.scegli_azione(),3);
    s.set_memoria(N.GetId());
    ASSERT_EQ(s.get_memoria()[0], N.GetId());

}
TEST(DnaTest, mutazioni){
    vector<int> v (16, 1);
    vector<int> vv (16, 2);
    Scimmia p(v), m(vv);
    Scimmia f(m,p);
    vector<int> fdna = f.get_dna();
    (count(fdna.begin(),fdna.end(),0),0);
    f.muta();
    EXPECT_NE(fdna, f.get_dna());
    Scimmia g(f);
    EXPECT_EQ(g.get_dna(), f.get_dna());
}

TEST_F(GraphTest, scimegraf){
    vector<int> v(16,1);
    Scimmia s(v);
    s.set_stato(N);
    s.set_memoria(N.GetId());
    vector<int> f(N.GetOutDeg() - 1),P(1);
    fill_figli_e_padri(N, f.begin(),f.end(),P.begin(),P.end());
    EXPECT_EQ(N.GetId(),s.move(N));
    v[12] = 2;
    s.set_dna(v);
    int p = s.move(N);
    EXPECT_TRUE(any_of(f.begin(),f.end(), [p](int& i){return i == p;}));
    v[12] = 0;
    s.set_dna(v);
    EXPECT_EQ(N.GetId(),s.move(N));
    int padre = P[0];
    int figlio = f[0];
    s.set_memoria(P[0]);
    s.set_stato(N);
    v[0b110] = 1;
    s.set_dna(v);
    EXPECT_EQ(s.get_stato(), 0b110);
    EXPECT_EQ(padre, s.move(N));
    v[0b110] = 3;
    s.set_dna(v);
    EXPECT_EQ(N.GetId(), s.move(N));
    s.set_memoria(figlio);
    s.set_stato(N);
    EXPECT_EQ(s.get_stato(), 0b111);
    v[0b111] = 0;
    EXPECT_NE(figlio, s.move(N));
    s.set_dna(v);
    EXPECT_EQ(figlio, s.move(N));
}
TEST_F(GraphTest, fit_func){
    Scimmia s;
    s.set_memoria(0);
    TNGraph::TNodeI end =NGraph->EndNI();
    end--;
    cout << end.GetId();

    for(int i = 0; i < 20; ++i) {
        int cnode = NGraph->GetRndNId();
        s.set_fit(cnode, NGraph);
        if ( end.GetId()-4 < cnode) EXPECT_EQ(s.get_fit(),1);
        else EXPECT_LE(s.get_fit(),1);
    }
    s.set_fit(end.GetId(),NGraph);
    int endfit = s.get_fit();
    s.set_fit(20,NGraph);
    EXPECT_NE(endfit,s.get_fit()) << end.GetId();
}
