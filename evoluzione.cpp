#include "evoluzione.h"
using namespace std;
using namespace TSnap;
random_device caso;
default_random_engine casuale(caso());
typedef TNodeEDatNet<Point,Point> TNet;

void Evoluzione::log(int numero_evol, int evol_per_parete){
    change_parete(caso());
    for(int evolutions = 0; evolutions != numero_evol; ++evolutions){
        evoluzione();
        vector<double> av_fit;
        cout << evolutions;
        if(evolutions % 1000 == 0 && evolutions != 0){
            vector<int> dna = this->best_scimmia().get_dna();
            double fit = this->best_scimmia().get_fit();
            if(fit < 0.001){
                write(QString("L" + QString::number(evolutions)));
            } else {
                av_fit.push_back(fit);
                double ave;
                std::accumulate(av_fit.begin(), av_fit.end(),ave);
                ave /= av_fit.size();
                if(fit > ave){
                    write(QString("W" + QString::number(evolutions)));
                    change_parete(rand());
                }
                else write(QString::number(evolutions));
            }
            if(evolutions %evol_per_parete == 0 && evolutions != 0) change_parete(caso());
        }
    }
}
void Evoluzione::write(const QString& filename){
    vector<int> dna = best_scimmia().get_dna();
    double fit = best_scimmia().get_fit();
    QFile f(filename + ".json");
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        std::cout << "errore aprendo file per scrivere" << std::endl;
        return;
    }
    QJsonObject j;
    j["parete"] = parete.get_seed();
    QVariantList q;
    for(auto& e:dna) q.append(QVariant(e));
    j["dna"] = QJsonArray::fromVariantList(q);
    j["fit"] = fit;
    QJsonDocument d(j);
    f.write(d.toJson());
}
	;
void Evoluzione::change_parete(int s,int N, int x, int y, int d, double prob_appo, double prob_appi, int min_depth)
{
    parete = rnd_solvable_parete(N, x, y, d, prob_appo, prob_appi, min_depth, s);

}

void Evoluzione::riproduzione ()//inizializza generazione con la nuova generazione di scimmie selezionate in base al fit
{
	vector<Scimmia> new_gen;
	vector<double> pesi;
	for (int i = 0; i < generazione.size(); ++i) pesi.push_back(generazione[i].get_fit());
	uniform_real_distribution<> dis(0,1);
	discrete_distribution<> best(pesi.begin(), pesi.end());
//inizializzo new_gen con Scimmie selezionate con cross-over, mutazione e clonazione
        //if individui gets changed riproduzione will generate a bigger generazione than the previous one. swap works regardless.
	for (int i=0; i<individui; i++)
        {
            double prob = dis(casuale);
            Scimmia p(generazione[best(casuale)].get_dna()), m(generazione[best(casuale)].get_dna());
            if(prob < p_cross) p = Scimmia(p,m);
            if(prob > 1-p_muta) p.muta();
        new_gen.push_back(p);
    }
    swap(generazione,new_gen);
}

void Evoluzione::set_fitfunc(function<double(Scimmia&, TNet::TNodeI&, const Parete&, int passi)> _fit_func){
    fit_func = _fit_func;
}
void Evoluzione::evoluzione() {
    riproduzione();
    #pragma omp parallel for
    for (auto i = generazione.begin(); i < generazione.end(); ++i) {
        //just to be sure
        TNet::TNodeI pos = i->traverse(parete, passi);
        i->set_fit(fit_func(*i, pos, parete, passi));
    }
}

Scimmia Evoluzione::best_scimmia(){
	return *max_element(generazione.begin(), generazione.end(), [&](auto &e, auto &i) { return e.get_fit() < i.get_fit(); });
}

Evoluzione::Evoluzione() = default;

Evoluzione::Evoluzione(int passi, int individui, double p_cross, double p_muta) :
		passi(passi), individui(individui), p_cross(p_cross), p_muta(p_muta), generazione(individui), parete(), fit_func(&Scimmia::fit_func_riri){
}

void Evoluzione::new_gen(){
    vector<Scimmia> newgen(individui);
    swap(generazione,newgen);
}
void Evoluzione::set_individui(int _individui) {
    individui = _individui;
}

void Evoluzione::set_passi(int _passi) {
	passi = _passi;
}

void Evoluzione::set_pcross(double _p_cross) {
	p_cross = _p_cross;
}

void Evoluzione::set_pmuta(double _p_muta) {
	p_muta = _p_muta;
}
const Parete &Evoluzione::getParete() const {
    return parete;
}

const vector<Scimmia> &Evoluzione::getGenerazione() const {
    return generazione;
}

double Evoluzione::getP_cross() const {
    return p_cross;
}

double Evoluzione::getP_muta() const {
    return p_muta;
}

const function<double(Scimmia &, TNodeEDatNet<Point, Point>::TNodeI &, const Parete &, int passi)> &
Evoluzione::getFit_func() const {
    return fit_func;
}

int Evoluzione::getPassi() const {
    return passi;
}

int Evoluzione::getIndividui() const {
    return individui;
}


