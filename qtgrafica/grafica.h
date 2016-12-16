#ifndef GRAFICA_H
#define GRAFICA_H

#include <QObject>
#include "../evoluzione.h"

class grafica : public QObject
{
    Q_OBJECT
    Evoluzione evo;
    vector<double> fits;
    vector<std::function<double(Scimmia&,TNodeEDatNet<Point,Point>::TNodeI&, const Parete&)>>
        funcs;
    int evolutions;
    bool running;
    bool runable;
public:
    explicit grafica(QObject *parent = 0);

signals:
    bool is_runable();

public slots:
    void set_individui(int individui);

    void set_passi(int passi);

    void set_pcross(double p_cross);

    void set_pmuta(double p_muta);

    void choose_fitfunc(int i);

    void change_gen();

    void chage_parete();

    void start_evo();

    void stop_evo();

    void set_runable();

    double show_best();

    double show_stats();
};

#endif // GRAFICA_H
