#ifndef GRAFICA_H
#define GRAFICA_H

#include <QObject>
#include <QCoreApplication>
#include "evoluzione.h"
#include "scimmia.h"
#include "parete.h"
#include "animaparete.h"
#include "Snap.h"

class grafica : public QObject
{
    Q_OBJECT
    Evoluzione evo;
    AnimaParete animazione;
    std::vector<double> fits;
    std::vector<std::function<double(Scimmia&,TNodeEDatNet<Point,Point>::TNodeI&, const Parete&)>>
        funcs;
    int evolutions;
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(bool runable READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(QString fit READ fit WRITE setFit NOTIFY fitChanged)
    Q_PROPERTY(double pcross READ pcross WRITE setPcross NOTIFY pcrossChanged)
    Q_PROPERTY(double pmuta READ pmuta WRITE setpmuta NOTIFY pmutaChanged)
    Q_PROPERTY(int individui READ individui WRITE setindividui NOTIFY individuiChanged)
    Q_PROPERTY(int passi READ passi WRITE setpassi NOTIFY passiChanged)
    Q_PROPERTY(int f_index READ f_index WRITE setf_index NOTIFY f_indexChanged)
    bool m_runable;
    bool m_running;
    QString m_fit;
    double m_pcross;

    double m_pmuta;

    int m_individui;

    int m_passi;

    int m_f_index;

public:
    explicit grafica(QObject* parent=0);

    bool running() const;

    bool runable() const;

    QString fit() const;


    double pcross() const;

    double pmuta() const;

    int individui() const;

    int passi() const;

    int f_index() const;

signals:

    void runningChanged(bool running);

    void runableChanged(bool runable);

    void fitChanged(QString fit);

    void pcrossChanged(double pcross);

    void pmutaChanged(double pmuta);

    void individuiChanged(int individui);

    void passiChanged(int passi);

    void f_indexChanged(int f_index);

public slots:

    void change_gen();

    void change_parete();

    void start_evo();

    void stop_evo();

    void set_runable();

    void setRunning(bool running);

    void setRunable(bool runable);

    void setFit(QString fit);

    //double show_stats();
    void setPcross(double pcross);
    void setpmuta(double pmuta);
    void setindividui(int individui);
    void setpassi(int passi);
    void setf_index(int f_index);
    QVector<qreal> get_best_memoria();
    QVector<qreal> get_coor_parete();
};

#endif // GRAFICA_H
