#include "parete.h"

using namespace TSnap;
using namespace std;

typedef TPt<TNodeEDatNet<Point,Point>> PNet;

Point::Point() : TIntPr(){;}
double Point::dist(Point p){
    return sqrt(pow(Val1 - p.Val1,2) + pow(Val2-p.Val2,2));
}
Point::Point(int _Val1, int _Val2) : TIntPr(_Val1, _Val2) {;}
Point Point::operator-(const Point& p){return Point(p.Val1 - Val1, p.Val2 - Val2);}
bool Point::operator==(const Point& p) const {return p.Val1 == Val1 && p.Val2 == Val2;}
Point::Point(const Point &p){Val1 = p.Val1; Val2 = p.Val2;}

vector<Point> gen_p_distr(int N,int x, int y, int seed){
    default_random_engine gen(seed);
    vector<Point> res;
    uniform_int_distribution<> xgen(0,x);
    uniform_int_distribution<> ygen(0,y);
    for(int i = 0; i<N; ++i){
        res.push_back(Point(xgen(gen),ygen(gen)));
    }
    return res;
}

void Parete::set_seed(int i) {seed=i;}

int Parete::get_seed() const {return seed;}

//finds end node
void Parete::set_end() {
        TIntV nodi(p->GetNodes());
        p->GetNIdV(nodi);
        end = *max_element(nodi.BegI(), nodi.EndI(),
               [&](auto &m, auto &n) { return p->GetNDat(m).Val2 < p->GetNDat(n).Val2; });
    }

//finds start node
void Parete::set_start(){
    PNGraph g = GetBfsTree(p, end, false, true);
    TIntV nodi(g->GetNodes());
    g->GetNIdV(nodi);
    start = *min_element(nodi.BegI(), nodi.EndI(), [&](auto& n, auto& m){
        return p->GetNDat(n).Val2 < p->GetNDat(m).Val2; });
}

//checks if graph is traversable
bool Parete::is_viable(){
    int depth, size;
    GetSubTreeSz(this->get_p(),end,false,true,size,depth);
    return depth > min_depth;
}

//sets lowest hight and shortest width of vectors of parete as origin
void Parete::norm_coord(){
    TIntV nodi(p->GetNodes());
    p->GetNIdV(nodi);
    int shortest = *min_element(nodi.BegI(), nodi.EndI(), [&](auto& n, auto& m){return p->GetNDat(n).Val2 < p->GetNDat(m).Val2; });
    int leftist = *min_element(nodi.BegI(), nodi.EndI(), [&](auto& n, auto& m){return p->GetNDat(n).Val1 < p->GetNDat(m).Val1; });
    int min_y = p->GetNDat(shortest).Val2;
    int min_x = p->GetNDat(leftist).Val1;
    for_each(nodi.BegI(),nodi.EndI(),[&](auto& e){
        int x = p->GetNDat(e).Val1;
        int y = p->GetNDat(e).Val2;
        p->SetNDat(e, Point(x-min_x,y-min_y));});
}

//generates random (possibly not viable) parete. nodes are connected if at
//distance < d, and are connected from lowest to highest if highest is appiglio
//and from highest to lowest if highest is appoggio
Parete::Parete(vector<Point> points, int d, double p_appi, double p_appo, int m_depth) :
        d_nodi(d), prob_appiglio(p_appi), prob_appoggio(p_appo), min_depth(m_depth){
    uniform_real_distribution<> probs(0,1);
    default_random_engine gen(get_seed());
    p = PNet::New();
    for(int i = 0; i < points.size(); ++i){
        if ( ! p->IsNode(i) ) p->AddNode(i,points[i]);
        for(int l = 0; l<points.size();++l){
            double dis = points[i].dist(points[l]);
            if(dis<d_nodi && l != i){
                if( ! p->IsNode(l) ) p->AddNode(l,points[l]);
                //if l under i appo is i->l and appi is l->i; if not appi (->) surely at least <-, if neither appi nor appo l<.i;
                if(points[l].Val2<points[i].Val2){swap(prob_appoggio,prob_appiglio);}
                double prob = probs(gen);
                if(prob > prob_appoggio) p->AddEdge(i,l,points[i] - points[l]);
                if(prob < 1-prob_appiglio) p->AddEdge(l,i, points[l] - points[i]);
            }
        }
    }
    set_end();
    set_start();
}

void Parete::write_schema(TStr filename){
    TIntStrH Nomi;
    for(PNet::TObj::TNodeI i = p->BegNI(); i < p->EndNI(); i++ ){
        Nomi.AddDat(i.GetId(), i.GetDat().Val2.GetStr());
    }
    DrawGViz(p, gvlDot,filename," ",Nomi);
}
Parete::Parete(const Parete &pr){
    p = pr.get_p();
    d_nodi = pr.get_d();
    end = pr.get_endID();
    start = pr.get_startID();
    min_depth = pr.get_min_depth();
    prob_appiglio = pr.get_prob_appiglio();
    prob_appoggio = pr.get_prob_appoggio();
}

Parete::Parete(Parete&& pr) : p(move(pr.p)), d_nodi(pr.d_nodi), prob_appiglio(pr.prob_appiglio),
                              prob_appoggio(pr.prob_appoggio), end(pr.end), start(pr.start),
                              corr(pr.corr), min_depth(pr.min_depth) {
}

void swap(Parete& p, Parete& s){
    using std::swap;
    swap(p.p, s.p);
    swap(p.prob_appiglio,s.prob_appiglio);
    swap(p.prob_appoggio,s.prob_appoggio);
    swap(p.end,s.end);
    swap(p.start,s.start);
    swap(p.corr,s.corr);
    swap(p.min_depth,s.min_depth);
}
Parete Parete::operator=(Parete pr){
    swap(*this,pr);
    return *this;
}

Parete::Parete() = default;
int Parete::get_d()const { return d_nodi;}
int Parete::get_startID()const { return start;}
int Parete::get_endID()const { return end;}
int Parete::get_min_depth()const { return min_depth;}
double Parete::get_prob_appiglio()const { return prob_appiglio;}
double Parete::get_prob_appoggio()const { return prob_appoggio;}
const PNet &Parete::get_p()const {return p;}
bool Parete::operator ==(const Parete& pr) const {return end == pr.end && start == pr.start;}

//construct random viable parete from random distribution of N points in interval (0,0) - (x,y)
Parete rnd_solvable_parete(int N, int x, int y, int d, double prob_appo, double prob_appi,int min_depth,int s){
    random_device rd;
    vector<Point> ret = gen_p_distr(N,x,y,s);
    Parete wall;
    double time = clock();
    do {
        wall = Parete(ret,d, prob_appo,prob_appi,min_depth);
        //gets the biggest connected subgraph and checks wether it's viable; if not, repeat
        wall.p = GetMxWcc(wall.get_p());
        wall.set_end();
        if((clock()-time)/CLOCKS_PER_SEC > 10) {
            cout << "takes too long, recurse!" << endl;
            s = rd();
            return rnd_solvable_parete(N,x,y,d,prob_appo,prob_appi,min_depth,s);
        }
    } while (!wall.is_viable());
    wall.set_end();
    wall.set_start();
    wall.norm_coord();
    wall.set_seed(s);
    return wall;
}

