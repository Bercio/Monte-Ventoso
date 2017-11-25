#include "grafica.h"
grafica::grafica(QObject* parent) : QObject(parent),evolutions(0),evo(), animazione(0), m_runable(false),m_running(false), m_individui(100), m_pcross(0.6), m_passi(100), m_pmuta(0.2)
{
    funcs.push_back(&Scimmia::fit_func_lo);
    funcs.push_back(&Scimmia::fit_func_riri);
    evo.set_passi(m_passi);
    evo.set_individui(m_individui);
    evo.set_pcross(m_pcross);
    evo.set_pmuta(m_pmuta);
    evo.set_fitfunc(funcs[0]);
    evo.change_parete();

}

QString grafica::fit() const
    {
        return m_fit;
}

double grafica::pcross() const
{
    return m_pcross;
}

double grafica::pmuta() const
{
    return m_pmuta;
}
int grafica::individui() const
{
    return m_individui;
}

int grafica::passi() const
{
    return m_passi;
}

int grafica::f_index() const
{
    return m_f_index;
}

void grafica::setFit(QString fit)
{
    if (m_fit == fit) return;
    m_fit = fit;
    emit fitChanged(fit);
}

void grafica::setPcross(double pcross)
{
    if (m_pcross == pcross)
        return;

    m_pcross = pcross;
    evo.set_pcross(pcross);
    emit pcrossChanged(pcross);
}

void grafica::setpmuta(double pmuta)
{
    if (m_pmuta == pmuta)
        return;

    m_pmuta = pmuta;
    evo.set_pmuta(pmuta);
    emit pmutaChanged(pmuta);
}
void grafica::setindividui(int individui)
{
    if (m_individui == individui)
        return;

    m_individui = individui;
    evo.set_individui(individui);
    emit individuiChanged(individui);
}

void grafica::setpassi(int passi)
{
    if (m_passi == passi)
        return;

    m_passi = passi;
    evo.set_passi(passi);
    emit passiChanged(passi);
}

void grafica::setf_index(int f_index)
{
    if (m_f_index == f_index)
        return;

    m_f_index = f_index;
    evo.set_fitfunc(funcs[f_index]);
    emit f_indexChanged(f_index);
}
void grafica::change_parete(){
    evo.change_parete();
}


void grafica::setRunning(bool running){
    if (m_running == running)
        return;
    m_running = running;
    emit runningChanged(running);
}
void grafica::setRunable(bool runable){
    if (m_runable == runable)
        return;
    m_runable = runable;
    emit runableChanged(runable);
}
bool grafica::runable() const{
    return m_runable;
}
bool grafica::running() const{
    return m_running;
}

void grafica::start_evo(){
    setRunning(true);
    while(m_running){
        //TODO: make event processing and image drawing parallel threads;
        evo.evoluzione();
        ++evolutions;
        fits.push_back(evo.best_scimmia().get_fit());
        QCoreApplication::processEvents();
    }
}
void grafica::stop_evo(){
    setRunning(false);
    Scimmia best = evo.best_scimmia();
    QString fit = QString::number(best.get_fit());
    setFit(fit);
}
QVector<QPoint> grafica::get_best_mem(){
    QVector<QPoint> mem;
    std::vector<int> best = evo.best_scimmia().get_memoria();
    const TPt<TNodeEDatNet<Point,Point>> p = evo.getParete().get_p();
    for(const int& i:best){
        mem.append(QPoint(p->GetNDat(i).Val1,p->GetNDat(i).Val2));
    }
    return mem;
}
QVector<QLine> grafica::get_paths_parete() {
    const TPt<TNodeEDatNet<Point,Point>> p = evo.getParete().get_p();
    QVector<QLine> res;
    for(auto orig = p->BegNI(); orig < p->EndNI(); orig++){
        for(int end = 0; end < orig.GetOutDeg(); end++){
            res.append(QLine(QPoint(orig.GetDat().Val1,orig.GetDat().Val2),QPoint(orig.GetOutNDat(end).Val1, orig.GetOutNDat(end).Val2)));
        }
    }
    return res;
}
QPoint grafica::get_max_coor(){

    Parete parete = evo.getParete();
    const TPt<TNodeEDatNet<Point,Point>> p = parete.get_p();
    TIntV v;
    p->GetNIdV(v);
    int nmaxx = p->GetNDat(*std::max_element(v.BegI(), v.EndI(), [&](TInt& n, TInt& m){ return p->GetNDat(n).Val1 < p->GetNDat(m).Val1;})).Val1;
    int nmaxy = p->GetNDat(parete.get_endID()).Val2;
    return QPoint(nmaxx,nmaxy);
}
void grafica::change_gen(){
    evo.new_gen();
}

void grafica::set_runable(){
    bool _runable = evo.getIndividui() && evo.getPassi()
                   && !evo.getGenerazione().empty() &&
                   evo.getParete().get_p()->GetNodes();
    setRunable(_runable);
}
