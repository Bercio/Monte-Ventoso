#ifndef GRAFICA_H
#define GRAFICA_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QLine>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QAbstractListModel>
#include <QVariant>
#include <exception>
#include <QCoreApplication>
#include "evoluzione.h"
#include "scimmia.h"
#include "parete.h"
#include "Snap.h"

class grafica : public QObject
{
    Q_OBJECT
    Evoluzione evo;
    std::vector<std::function<double(Scimmia&,TNodeEDatNet<Point,Point>::TNodeI&, const Parete&, int p)>>
        funcs;
    Q_PROPERTY(int evolutions READ evolutions)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(bool runable READ runable WRITE setRunable NOTIFY runableChanged)
    Q_PROPERTY(double fit READ fit WRITE setFit NOTIFY fitChanged)
    Q_PROPERTY(double pcross READ pcross WRITE setPcross NOTIFY pcrossChanged)
    Q_PROPERTY(double pmuta READ pmuta WRITE setpmuta NOTIFY pmutaChanged)
    Q_PROPERTY(int individui READ individui WRITE setindividui NOTIFY individuiChanged)
    Q_PROPERTY(int passi READ passi WRITE setpassi NOTIFY passiChanged)
    Q_PROPERTY(int f_index READ f_index WRITE setf_index NOTIFY f_indexChanged)
    Q_PROPERTY(QVector<int> dna READ dna WRITE setDna NOTIFY dnaChanged)
    Q_PROPERTY(QVector<QPoint> mem READ mem WRITE setMem NOTIFY memChanged)
    Q_PROPERTY(QVector<QLine> paths READ paths WRITE setPaths NOTIFY pathsChanged)
    Q_PROPERTY(int seed READ seed WRITE setSeed)
    bool m_runable;
    bool m_running;
    double m_fit;
    double m_pcross;

    double m_pmuta;

    int m_individui, m_seed;

    int m_passi;

    int m_f_index;

    int m_evolutions;
    QVector<int> m_dna;
    QVector<QPoint> m_mem;
    QVector<QLine> m_paths;

public:
    explicit grafica(QObject* parent=0);

    int evolutions() const;
    int seed() const;
    void setSeed(int s);
    bool running() const;
    QVector<QPoint> mem() const;
    void setMem(QVector<QPoint> mem);
    void setPaths(QVector<QLine> paths);
    bool runable() const;
    QVector<int> dna() ;
    void setDna(QVector<int>);

    double fit() const;


    double pcross() const;

    double pmuta() const;

    int individui() const;

    int passi() const;

    int f_index() const;
    QVector<QLine> paths() const;

signals:

    void dnaChanged(QVector<int> dna);
    void runningChanged(bool running);
    void memChanged(QVector<QPoint> mem);
    void runableChanged(bool runable);

    void fitChanged(double fit);

    void pcrossChanged(double pcross);

    void pmutaChanged(double pmuta);

    void individuiChanged(int individui);

    void passiChanged(int passi);

    void f_indexChanged(int f_index);
    void pathsChanged(QVector<QLine> paths);

public slots:

    void write(QString filename);
    void read_parete(QString filename);
    void read_scimmia(QString filename);
    void change_gen();
    void change_dna(const QModelIndex& top, const QModelIndex& bottom);

    void change_parete();
    void animate();
    void get_best_dna();
    void get_best_fit();

    void start_evo();

    void log_evo(QString filename);
    void stop_evo();

    void _set_runable();

    void setRunning(bool running);

    void setRunable(bool runable);

    void setFit(double fit);
    QPoint get_max_coor();

    //double show_stats();
    void setPcross(double pcross);
    void setpmuta(double pmuta);
    void setindividui(int individui);
    void setpassi(int passi);
    void setf_index(int f_index);
    void  get_best_mem();
    void get_paths_parete();
};

#endif // GRAFICA_H
