#include "parete.h"
#include <exception>
#include "ctime"
#include <utility>
#include <iostream>

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

vector<Point> gen_p_distr(int N,int x, int y){
    random_device rd;
    default_random_engine gen(1123);//rd());
    vector<Point> res;
    uniform_int_distribution<> xgen(0,x);
    uniform_int_distribution<> ygen(0,y);
    for(int i = 0; i<N; ++i){
        res.push_back(Point(xgen(gen),ygen(gen)));
    }
    return res;
}

void Parete::set_end() {
        TIntV nodi(p->GetNodes());
        p->GetNIdV(nodi);
        end = *max_element(nodi.BegI(), nodi.EndI(),
               [&](auto &m, auto &n) { return p->GetNDat(m).Val2 < p->GetNDat(n).Val2; });
    }

void Parete::set_start(){
    PNGraph g = GetBfsTree(p, end, false, true);
    TIntV nodi(g->GetNodes());
    g->GetNIdV(nodi);
    start = *min_element(nodi.BegI(), nodi.EndI(), [&](auto& n, auto& m){
        return p->GetNDat(n).Val2 < p->GetNDat(m).Val2; });
}

bool Parete::is_viable(){
    int depth, size;
    GetSubTreeSz(this->get_p(),end,false,true,size,depth);
    return depth > min_depth;
}

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
Parete::Parete(vector<Point> points, int d, double p_appi, double p_appo, int m_depth) :
        d_nodi(d), prob_appiglio(p_appi), prob_appoggio(p_appo), min_depth(m_depth){
    uniform_real_distribution<> probs(0,1);
    random_device rd;
    default_random_engine gen(12124);//rd());
    p = PNet::New();
    for(int i = 0; i < points.size(); ++i){
        if ( ! p->IsNode(i) ) p->AddNode(i,points[i]);
        for(int l = 0; l<points.size();++l){
            double dis = points[i].dist(points[l]);
            if(dis<d_nodi && l != i){
                if( ! p->IsNode(l) ) p->AddNode(l,points[l]);
                double _prob_appoggio = prob_appoggio, _prob_appi = prob_appiglio;
                //if l under i appo is i.l and appi is l.i; if not appi (->) surely at least <-, if neither appi nor appo l<.i;
                if(points[l].Val2<points[i].Val2){_prob_appoggio = prob_appiglio; _prob_appi = prob_appoggio;}
                double prob = probs(gen);
                if(prob > _prob_appoggio) p->AddEdge(i,l,points[i] - points[l]);
                if(prob < 1-_prob_appi) p->AddEdge(l,i, points[l] - points[i]);
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
void Parete::set_window(sf::RenderWindow& window, string titolo="Parete"){
    TIntV v;
    p->GetNIdV(v);
    int nmaxx = p->GetNDat(*max_element(v.BegI(), v.EndI(), [&](TInt& n, TInt& m){ return p->GetNDat(n).Val1 < p->GetNDat(m).Val1;})).Val1;
    int nmaxy = p->GetNDat(get_endID()).Val2;
    corr = 50.0/d_nodi;
    int pix_h = ceil(corr * nmaxy) + 40;
    int pix_w = ceil(corr * nmaxx) + 40;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    if (pix_w > desktop.width) {
        pix_w = desktop.width;
        corr = (desktop.width - 20)/((double)nmaxx);
    }
    if (pix_h > desktop.height) {
        pix_h = desktop.height;
        corr = (desktop.height -100)/((double)nmaxy);
    }

    sf::ContextSettings settings = window.getSettings();
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(pix_w, pix_h),titolo , sf::Style::Default, settings);
    sf::View viw = window.getView();
    viw.rotate(180);
    viw.setCenter(ceil(nmaxx*corr/2.0), ceil(nmaxy*corr/2.0));
    window.setView(viw);
}
void Parete::draw(int n, sf::RenderWindow& window){
    vector<sf::CircleShape> app;
    sf::VertexArray line(sf::Lines, 2);
    sf::CircleShape shape(2.f);
    for(auto i = p->BegNI(); i < p->EndNI(); i++) {
        bool appog=false, appigl=false;
        line[0].position = sf::Vector2f(i.GetDat().Val1*corr, i.GetDat().Val2*corr);
        line[0].color = sf::Color::Black;
        for(int j = 0; j < i.GetInDeg(); ++j){
            if(i.GetInEDat(j).Val2 > 0) appog = true;
            else appigl = true;
            line[1].position = sf::Vector2f(i.GetInNDat(j).Val1*corr, i.GetInNDat(j).Val2*corr);
            line[1].color = sf::Color::Black;
            window.draw(line);
        }
        if (appog == appigl) shape.setPointCount(6);
        else shape.setPointCount(3);
        if (appog) shape.rotate(180);
        shape.setPosition((i.GetDat().Val1*corr), (i.GetDat().Val2*corr));
        line[0] = sf::Vector2f(i.GetDat().Val1, i.GetDat().Val2);
        if (i.GetId() == end) shape.setFillColor(sf::Color::Green);
        else if (i.GetId() == n) shape.setFillColor(sf::Color::Red);
        else shape.setFillColor(sf::Color::Black);
        window.draw(shape);
    }

}
void Parete::animate(vector<int> v, string titolo){
    sf::RenderWindow window;
    this->set_window(window, titolo);
    vector<int>::iterator i = v.begin();
    bool parti = false;
    while (window.isOpen() ){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) parti = !parti;
        }
        if (i == v.end()) i = v.begin();
        if (parti) {
            window.clear(sf::Color::White);
            this->draw(*i, window);
            window.display();
            ++i;
            sleep(1);
        }
    }
}
int Parete::get_d()const { return d_nodi;}
int Parete::get_startID()const { return start;}
int Parete::get_endID()const { return end;}
int Parete::get_min_depth()const { return min_depth;}
double Parete::get_prob_appiglio()const { return prob_appiglio;}
double Parete::get_prob_appoggio()const { return prob_appoggio;}
const PNet& Parete::get_p()const {return p;}
Parete get_random_p(int N, int x, int y, int d, double prob_appo, double prob_appi,int min_depth){
    vector<Point> ret = gen_p_distr(N,x,y);
    Parete wall;
    double time = clock();
    do {
        wall = Parete(ret,d, prob_appo,prob_appi,min_depth);
        wall.p = GetMxWcc(wall.get_p());
        wall.set_end();
        if((clock()-time)/CLOCKS_PER_SEC > 20) {
            throw invalid_argument("too few numbers or too small a "
                    "distance for min_depth specified.");
        }
    } while (!wall.is_viable());
    wall.set_end();
    wall.set_start();
    wall.norm_coord();
    return wall;
}
bool Parete::operator ==(const Parete& pr) const {return end == pr.end && start == pr.start;}

