#include "animaparete.h"
//TODO: load in into qml and display it; write the functions

AnimaParete::AnimaParete(QQuickPaintedItem *parent) : QQuickPaintedItem(parent) { ; }
void AnimaParete::setCoor(QVector<qreal> v) {
    if(v != m_coor){
        m_coor = v;
        emit coorChanged();
    }
}
void AnimaParete::setMemoria(QVector<qreal> v) {
    if(v != m_memoria){
        m_memoria = v;
        emit memoriaChanged();
    }
}
QVector<qreal> AnimaParete::memoria() const {return m_memoria;}
QVector<qreal> AnimaParete::coor() const {return m_coor;}
void AnimaParete::paint(QPainter* painter){;
}
