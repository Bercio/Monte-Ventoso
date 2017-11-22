#ifndef ANIMAPARETE_H
#define ANIMAPARETE_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include "parete.h"

class AnimaParete : public QQuickPaintedItem
{
    Q_OBJECT
public:
    AnimaParete(QQuickPaintedItem *parent = 0);
    void paint(QPainter *painter);
    void setParete(Parete p);
    void setMemoria(std::vector<int> mem);
    void anima();
private:
    Parete parete;
    std::vector<int> memoria;


};

#endif // ANIMAPARETE_H
