#include "parete.h"
#include <utility>
using namespace TSnap;
using namespace std;


Point::Point() : TIntPr(){;}
double Point::dist(Point p){
    return sqrt(pow(Val1 - p.Val1,2) + pow(Val2-p.Val2,2));
}
Point::Point(int _Val1, int _Val2) : TIntPr(_Val1, _Val2) {;}
Point Point::operator-(const Point& p){return Point(p.Val1 - Val1, p.Val2 - Val2);}

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

void Parete::set_end() {
        TIntV nodi(GetNodes());
        GetNIdV(nodi);
        end = *max_element(nodi.BegI(), nodi.EndI(),
               [&](auto &n, auto &m) { return this->GetNDat(m).Val2 > this->GetNDat(n).Val2; });
    }

void Parete::set_start(){
    PNGraph p = GetBfsTree(PParete, end, false, true);
    TIntV nodi(p->GetNodes());
    p->GetNIdV(nodi);
    start = *min_element(nodi.BegI(), nodi.EndI(), [&](auto& n, auto& m){
        return this->GetNDat(m).Val2 > this->GetNDat(n).Val2; });
}

bool Parete::is_viable(){
    int depth, size;
    GetSubTreeSz(PParete,end,false,true,size,depth);
    return depth > min_depth;
}
void Parete::norm_coord(){
    TIntV nodi(GetNodes());
    GetNIdV(nodi);
    int shortest = *min_element(nodi.BegI(), nodi.EndI(), [&](auto& n, auto& m){return this->GetNDat(m).Val2 > this->GetNDat(n).Val2; });
    int leftist = *min_element(nodi.BegI(), nodi.EndI(), [&](auto& n, auto& m){return this->GetNDat(m).Val1 > this->GetNDat(n).Val1; });
    int min_y = GetNDat(shortest).Val2;
    int min_x = GetNDat(leftist).Val1;
    for_each(nodi.BegI(),nodi.EndI(),[&](auto& e){
        int x = this->GetNDat(e).Val1;
        int y = this->GetNDat(e).Val2;
        this->SetNDat(e, Point(x-min_x,y-min_y));});
}
Parete::Parete(vector<Point> points, int d, double p_appi, double p_appo, int m_depth) :
        d_nodi(d), prob_appiglio(p_appi), prob_appoggio(p_appo), min_depth(m_depth){
    uniform_real_distribution<> probs(0,1);
    default_random_engine gen;

    for(int i = 0; i < points.size(); ++i){
        if ( ! IsNode(i) ) AddNode(i,points[i]);
        for(int l = 0; l<points.size();++l){
            double dis = points[i].dist(points[l]);
            if(dis<d_nodi && l != i){
                if( ! IsNode(l) ) AddNode(l,points[l]);
                double _prob_appoggio = prob_appoggio, _prob_appi = prob_appiglio;
                //if l under i appo is i.l and appi is l.i; if not appi (->) surely at least <-, if neither appi nor appo l<.i;
                if(points[l].Val2<points[i].Val2){_prob_appoggio = prob_appiglio; _prob_appi = prob_appoggio;}
                double prob = probs(gen);
                if(prob > _prob_appoggio) AddEdge(i,l,points[l] - points[i]);
                if(prob < 1-_prob_appi) AddEdge(l,i, points[i] - points[l]);
            }

        }
    }
    PParete = TPt<Parete>(this);
}
Parete::Parete(int N, int x, int y, int d, double prob_appo, double prob_appi,int min_depth) {
    vector<Point> ret = gen_p_distr(N,x,y);
    TPt<Parete> p;
    do {
        Parete g = Parete(ret, d, prob_appo, prob_appi, min_depth);
        TPt<Parete> pp(&g);
        p = GetMxWcc(pp);
    } while (!p->is_viable());
    PParete = p;
    *this = *PParete;
    set_end();
    set_start();
    norm_coord();
}
void Parete::write_schema(TStr filename){
    TIntStrH Nomi;
    for(Parete::TNodeI i = BegNI(); i < EndNI(); i++ ){
        Nomi.AddDat(i.GetId(), i.GetDat().Val2.GetStr());
    }
    DrawGViz(PParete, gvlDot,filename," ",Nomi);
}
