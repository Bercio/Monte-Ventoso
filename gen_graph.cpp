#include "Snap.h"
#include <cstdlib>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace TSnap;
using namespace std;


struct Point : public TIntPr {
    Point() : TIntPr(){;}
    double dist(Point p){
        return sqrt(pow(Val1 - p.Val1,2) + pow(Val2-p.Val2,2));
    }
    Point(int _Val1, int _Val2) : TIntPr(_Val1, _Val2) {;}
    Point operator-(const Point& p){return Point(p.Val1 - Val1, p.Val2 - Val2);}
};

typedef TNodeEDatNet<Point, Point> TNet;
typedef TPt<TNet> PNet;
vector<Point> gen_p_distr(int N,int x, int y){
    default_random_engine gen;
    vector<Point> res;
    uniform_int_distribution<> xgen(0,x);
    uniform_int_distribution<> ygen(0,y);
    for(int i = 0; i<N; ++i){
        res.push_back(Point(xgen(gen),ygen(gen)));
    }
    return res;
}

PNet
from_points_to_graph(vector<Point> points, int d, double prob_appo, double prob_appi){
    uniform_real_distribution<> probs(0,1);
    default_random_engine gen;

    PNet gg = TNet::New();
    PNet::TObj& g = *gg;
    for(int i = 0; i < points.size(); ++i){
        if ( ! g.IsNode(i) ) g.AddNode(i,points[i]);
        for(int l = 0; l<points.size();++l){
            double dis = points[i].dist(points[l]);
            if(dis<d && l != i){
                if( ! g.IsNode(l) ) g.AddNode(l,points[l]);
                double _prob_appo = prob_appo, _prob_appi = prob_appi;
                //if l under i appo is i.l and appi is l.i; if not appi (.) surely at least <-, if neither appi nor appo l<.i;
                if(points[l].Val2<points[i].Val2){_prob_appo = prob_appi; _prob_appi = prob_appo;}
                double prob = probs(gen);
                if(prob > _prob_appo) g.AddEdge(i,l,points[l] - points[i]);
                if(prob < 1-_prob_appi) g.AddEdge(l,i, points[i] - points[l]);
            }

        }
    }
    return gg;
}

bool is_viable_subgraph(PNet& p, int min_depth=4){
    p = GetMxWcc(p);
    TIntV nodi(p->GetNodes());
    p->GetNIdV(nodi);
    int end;
    end = *max_element(nodi.BegI(), nodi.EndI(), [p](auto& n, auto& m){return p->GetNDat(m).Val2 > p->GetNDat(n).Val2; });
    int depth, size;
    GetSubTreeSz(p,end,false,true,size,depth);
    return depth > min_depth;
}

PNet generate_connected_graph(vector<Point> ret, int d, double prob_appo , double prob_appi){
    PNet graph;
    do {
         graph = from_points_to_graph(ret, d, prob_appo, prob_appi);
    } while (!is_viable_subgraph(graph));
    return graph;
}

int main(int argc, char* argv[]){
    int N(1000), x=500,y=1000, d=20;
    double prob_appo=0.1,prob_appi=0.1;
    if(argc> 1){
        N = atoi(argv[1]);
        if (argc > 2){
            d = atoi(argv[2]);
            if (argc > 3){
                prob_appo=atof(argv[3]);
                prob_appi=atof(argv[4]);
            }
        }
    }
    vector<Point> ret = gen_p_distr(N,x,y);
    PNet p = generate_connected_graph(ret,d,prob_appo,prob_appi);;
    TIntStrH Nomi;
    for(auto i = p->BegNI(); i < p->EndNI(); i++ ){
        Nomi.AddDat(i.GetId(), i.GetDat().Val2.GetStr());
    }
    DrawGViz(p, gvlDot,"gviz_net_name.png","",Nomi);


}

