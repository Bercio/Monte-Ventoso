#ifndef ANIMAPARETE_H
#define ANIMAPARETE_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include "parete.h"

class AnimaParete : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QVector<qreal> memoria READ memoria WRITE setMemoria NOTIFY memoriaChanged)
    Q_PROPERTY(QVector<qreal> coor READ coor WRITE setCoor NOTIFY coorChanged)
public:
    AnimaParete(QQuickPaintedItem *parent = 0);
    void setMemoria(QVector<qreal> v);
    void setCoor(QVector<qreal> v);
    QVector<qreal> memoria() const;
    QVector<qreal> coor() const;
    void paint(QPainter *painter);
signals:
    void memoriaChanged();
    void coorChanged();
private:
    QVector<qreal> m_coor;
    QVector<qreal> m_memoria;
};

#endif // ANIMAPARETE_H
