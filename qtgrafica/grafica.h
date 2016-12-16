#ifndef GRAFICA_H
#define GRAFICA_H

#include <QObject>

class grafica : public QObject
{
    Q_OBJECT
    Evoluzione evo;
    vector<double> fits;
    int evolutions;
public:
    explicit grafica(QObject *parent = 0);

signals:


public slots:
    void set_individui(int individui);

    void set_passi(int passi);

    void set_pcross(double p_cross);

    void set_pmuta(double p_muta);

    void change_gen();

    void chage_parete();

    void start_evo();

    void stop_evo();

    double show_best();

    double show_stats();
};

#endif // GRAFICA_H
