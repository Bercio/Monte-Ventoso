#ifndef ANIMAPARETE_H
#define ANIMAPARETE_H

#include <QtQuick>
#include "parete.h"

class AnimaParete : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QVector<QPoint> mem READ mem WRITE setMem NOTIFY memChanged)
    Q_PROPERTY(QVector<QLine> paths READ paths WRITE setPaths NOTIFY pathsChanged)
    Q_PROPERTY(int mem_index READ mem_index WRITE setMem_index NOTIFY mem_indexChanged)
    Q_PROPERTY(int end MEMBER m_end)
public:
    AnimaParete(QQuickPaintedItem *parent = 0);
    void setMem(QVector<QPoint> mem);
    void setPaths(QVector<QLine> v);
    void setMem_index(int index);
    QVector<QPoint> mem() const;
    QVector<QLine> paths() const;
    int mem_index() const;
    void paint(QPainter *painter);
signals:
    void memChanged();
    void pathsChanged();
    void mem_indexChanged();
private:
    QVector<QLine> m_paths;
    QVector<QPoint> m_mem;
    int m_mem_index;
    int m_end;
};
Q_DECLARE_METATYPE(QVector<QLine>);
Q_DECLARE_METATYPE(QVector<QPoint>);

#endif // ANIMAPARETE_H
