#include "grafica.h"
#include "../evoluzione.h"
grafica::grafica(QObject *parent) : QObject(parent), runable(false)
{
    funcs.push_back(&Scimmia::fit_func_lo);
    funcs.push_back(&Scimmia::fit_func_riri);
    evo.set_fitfunc(funcs[0]);
    evo.change_parete();
}

void grafica::set_individui(int individui){
    evo.set_individui(individui);
}
void grafica::set_passi(int passi){
    evo.set_passi(passi);
}
void grafica::set_pcross(double pcross){
    evo.set_pcross(pcross);
}
void grafica::set_pmuta(double pmuta){
    evo.set_pmuta(pmuta);
}
void grafica::change_parete(){
    evo.change_parete();
}
double grafica::show_best(){
    Scimmia sc = evo.best_scimmia();
    sc.animate();
    return sc.get_fit();
}
void grafica::start_evo(){
    running = true;
    while(running){
        evo.evoluzione();
        ++evolutions;
        fits.push_back(evo.best_scimmia().get_fit());
    }
}
void grafica::stop_evo(){
    running = false;
}
void grafica::choose_fitfunc(int i){
    evo.set_fitfunc(funcs[i]);
}

void grafica::set_runable(){
    bool _runable = evo.get_individui() && evo.get_passi()
                   && !evo.get_generazione().empty() &&
                   evo.get_parete().get_p().Nodes();
    if(runable != _runable){
        runable = _runable;
        emit is_runable();
    }

}

/*
double show_stats(){
  rapporto tra numero di evoluzioni e fit
}
*/
