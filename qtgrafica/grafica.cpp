#include "grafica.h"
grafica::grafica(QObject* parent) : QObject(parent), m_fit(0), m_evolutions(0),evo(), animazione(0), m_runable(false),m_running(false), m_individui(100), m_pcross(0.6), m_passi(100), m_pmuta(0.2)
{
    funcs.push_back(&Scimmia::fit_func_lo);
    funcs.push_back(&Scimmia::fit_func_riri);
    evo.set_passi(m_passi);
    evo.set_individui(m_individui);
    evo.set_pcross(m_pcross);
    evo.set_pmuta(m_pmuta);
    evo.set_fitfunc(funcs[0]);
    change_parete();
    evo.new_gen();
    get_paths_parete();
    _set_runable();
}

double grafica::fit() const
    {
        return m_fit;
}
QVector<QLine> grafica::paths() const{
    return m_paths ;
}
double grafica::pcross() const
{
    return m_pcross;
}
int grafica::seed() const { return m_seed;}
void grafica::setSeed(int s){ m_seed = s;}
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
void grafica::setPaths(QVector<QLine> paths){
    if(paths == m_paths) return;
    m_paths = paths;
    emit pathsChanged(paths);
}
void grafica::setFit(double fit)
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
    setSeed(std::rand());
    evo.change_parete(m_seed);
    get_paths_parete();
}
void grafica::write(QString filename){
    QFile f(filename + ".json");
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        std::cout << "errore aprendo file per scrivere" << std::endl;
        return;
    }
    QJsonObject j;
    j["parete"] = seed();
    QVariantList q;
    for(auto& e:dna()) q.append(QVariant(e));
    j["dna"] = QJsonArray::fromVariantList(q);
    j["fit"] = fit();
    QJsonDocument d(j);
    f.write(d.toJson());
}
void grafica::read_parete(QString filename){
    QFile f(filename + ".json");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::cout << "errore aprendo file per scrivere" << std::endl;
        return;
    }
    QByteArray saveData = f.readAll();
    QJsonDocument d = QJsonDocument::fromJson(saveData);
    QJsonObject j(d.object());
    setSeed(j["parete"].toInt());
    evo.change_parete(seed());
    get_paths_parete();
}
void grafica::read_scimmia(QString filename){
    QFile f(filename + ".json");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::cout << "errore aprendo file per scrivere" << std::endl;
        return;
    }
    QByteArray saveData = f.readAll();
    QJsonObject j = QJsonDocument(QJsonDocument::fromJson(saveData)).object();
    QVariantList q = j["dna"].toArray().toVariantList();
    QVector<int> v;
    for(auto& e:q){v.append(e.toInt());}
    setDna(v);
    setFit(j["fit"].toDouble());
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
QVector<QPoint> grafica::mem() const{
    return m_mem;
}
void grafica::start_evo(){
    if(running()) return;
    setRunning(true);
    while(m_running){
        //TODO: make event processing and image drawing parallel threads;
        evo.evoluzione();
        ++m_evolutions;
        QCoreApplication::processEvents();
    }
}
void grafica::stop_evo(){
    setRunning(false);
    double fit = evo.best_scimmia().get_fit();
    setFit(fit);
}
void grafica::get_best_mem(){
    QVector<QPoint> mem;
    std::vector<int> best = evo.best_scimmia().get_memoria();
    const TPt<TNodeEDatNet<Point,Point>> p = evo.getParete().get_p();
    for(const int& i:best){
        mem.append(QPoint(p->GetNDat(i).Val1,p->GetNDat(i).Val2));
    }
     setMem(mem);
}
void grafica::setMem(QVector<QPoint> mem){
    if(m_mem == mem) return;
    m_mem=mem;
    emit memChanged(mem);
}
void grafica::setDna(QVector<int> dna){
    if(dna==m_dna) return;
    m_dna = dna;
    emit dnaChanged(dna);
}
QVector<int> grafica::dna() { return m_dna; }
void grafica::get_best_dna(){
    QVector<int> dna;
    for(int& i:evo.best_scimmia().get_dna()) dna.append(i);
    setDna(dna);
}
void grafica::get_paths_parete() {
    const TPt<TNodeEDatNet<Point,Point>> p = evo.getParete().get_p();
    QVector<QLine> res;
    for(auto orig = p->BegNI(); orig < p->EndNI(); orig++){
        for(int end = 0; end < orig.GetOutDeg(); end++){
            res.append(QLine(QPoint(orig.GetDat().Val1,orig.GetDat().Val2),QPoint(orig.GetOutNDat(end).Val1, orig.GetOutNDat(end).Val2)));
        }
    }
    setPaths(res);
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
void grafica::change_dna(const QModelIndex &top, const QModelIndex &bottom){
    QVector<int> _dna = dna();
    int inizio = bottom.row();
    int fine = top.row();
    if(inizio > fine) std::swap(inizio,fine);
    for(int i = inizio; i < fine+1; ++i) {
        _dna[i] = bottom.sibling(i,0).data().toInt();
    }
    setDna(_dna);
}

void grafica::animate(){
    std::vector<int> sci_dna = dna().toStdVector();
    Scimmia m(sci_dna) ;
    const Parete parete = evo.getParete();
    TNodeEDatNet<Point,Point>::TNodeI pos = m.traverse(parete, passi());
    setFit(evo.getFit_func()(m, pos, parete,passi()));
    QVector<QPoint> mem;
    std::vector<int> sci_mem = m.get_memoria();
    const TPt<TNodeEDatNet<Point,Point>> p = parete.get_p();
    for(const int& i:sci_mem){
        mem.append(QPoint(p->GetNDat(i).Val1,p->GetNDat(i).Val2));
    }
    setMem(mem);
}
void grafica::_set_runable(){
    bool _runable = evo.getIndividui() && evo.getPassi()
                   && !evo.getGenerazione().empty() &&
                   evo.getParete().get_p()->GetNodes();
    setRunable(_runable);
}
int grafica::evolutions() const { return m_evolutions;}
