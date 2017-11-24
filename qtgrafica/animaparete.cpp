#include "animaparete.h"
//TODO: load in into qml and display it; write the functions


AnimaParete::AnimaParete(QQuickPaintedItem *parent) : QQuickPaintedItem(parent), m_mem_index(0) { ; }
void AnimaParete::setPaths(QVector<QLine> v) {
    if(v != m_paths){
        m_paths = v;
        emit pathsChanged();
    }
}
void AnimaParete::setMem(QVector<QPoint> mem) {
    m_mem_index=0;
    if(v != m_mem){
        m_mem = mem;
        m_end = mem.lenght();
        emit memChanged();
    }
}
void AnimaParete::setMem_index(int ind) {
    if(ind != m_mem_index){
        m_mem_index = ind;
        emit mem_indexChanged();
    }
}
QVector<QPoint> AnimaParete::mem() const {return m_mem;}
int AnimaParete::mem_index() const {return m_mem_index;}

QVector<QLine> AnimaParete::paths() const {return m_paths;}
void AnimaParete::paint(QPainter* painter){
    if(!m_paths.empty()){
        painter->setRenderHint(QPainter::Antialiasing);
        for(auto& i:m_paths){
            if(i.dy() > 0) painter->setPen(Qt::darkBlue);
            else painter->setPen(Qt::darkRed);
            painter->drawLine(i);
        }
        painter->setPen(Qt::green);
        painter->drawText(m_mem[m_mem_index],"🐵");
    }
}
