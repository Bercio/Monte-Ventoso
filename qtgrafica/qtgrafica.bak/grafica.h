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
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(bool runable READ runable WRITE setRunable NOTIFY runableChanged)
    Q_PROPERTY(double best_fit READ best_fit WRITE setBest_fit NOTIFY best_fitChanged)
public:
    explicit grafica(QObject *parent = 0);

    bool runable() const;

    void setRunable(const bool& b);

    bool running() const;

    void setRunning(const bool& b);

    double best_fit();

    void setBest_fit(double f);

signals:
    void runableChanged();
    void runningChanged();
    void best_fitChanged();

public slots:
    void set_individui(int individui);

    void set_passi(int passi);

    void set_pcross(double p_cross);

    void set_pmuta(double p_muta);

    void choose_fitfunc(int i);

    void newgen();

    void set_runable();

    void chage_parete();

    void start_evo();

    double show_stats();
};

#endif // GRAFICA_H
