#include "animaparete.h"
//TODO: load in into qml and display it; write the functions


AnimaParete::AnimaParete(QQuickPaintedItem *parent) : QQuickPaintedItem(parent), m_mem_index(0) {
    ;}
void AnimaParete::setPaths(QVector<QLine> v) {
    if(v != m_paths){
        m_paths = v;
        emit pathsChanged();
    }
}
void AnimaParete::setMem(QVector<QPoint> mem) {
    m_mem = mem;
    setMem_index(0);
    setEnd(m_mem.length()-1);
    emit memChanged();
}
void AnimaParete::setEnd(int e){
    m_end = e;
    emit endChanged();
}
int AnimaParete::end() const{
    return m_end;
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
    painter->setWindow(0,0,m_end_point.x()+5,m_end_point.y()+5);
    if(!m_paths.empty()){
        painter->setRenderHint(QPainter::Antialiasing);

        for(const auto& i:m_paths){
            if(std::find(m_paths.begin(), m_paths.end(), QLine(i.p2(),i.p1())) != m_paths.end()){
                painter->setPen(Qt::black);
            }
            else if(i.dy() > 0) painter->setPen(Qt::red);
            else painter->setPen(Qt::blue);
            QPen fine = painter->pen();
            fine.setWidthF(0.02);
            painter->setPen(fine);
            painter->drawLine(i);
        }
    }
    if(!m_mem.empty()){
        QPen fine = painter->pen();
        fine.setWidthF(0.05);
        fine.setColor(Qt::darkGreen);
        painter->setPen(fine);
        painter->drawEllipse(QPointF(m_mem[m_mem_index]),0.1,0.1);
    }
}

