#include "animaparete.h"
//TODO: load in into qml and display it; write the functions


AnimaParete::AnimaParete(QQuickPaintedItem *parent) : QQuickPaintedItem(parent), m_mem_index(0) {
}
void AnimaParete::setPaths(QVector<QLine> v) {
    if(v != m_paths){
        m_paths = v;
        emit pathsChanged();
    }
}
void AnimaParete::setMem(QVector<QPoint> mem) {
    m_mem = mem;
    emit memChanged();
}
void AnimaParete::setEnd_point(QPoint end_p){
    if(end_p != m_end_point){
        m_end_point = end_p;
        emit end_pointChanged();
    }
}
void AnimaParete::setEnd(int e){
    m_end = e;
    emit endChanged();
}
int AnimaParete::end() const{
    return m_end;
}
void AnimaParete::get_end() {
    if(m_mem.empty()) setEnd(0); return;
    int r = m_mem.length()-1;
    QVector<QPoint>::reverse_iterator rend = ++m_mem.rend();
    for(QVector<QPoint>::reverse_iterator i = m_mem.rbegin(); i != rend && *i == m_mem.back(); ++i) --r;
    setEnd(r);
}
void AnimaParete::setMem_index(int ind) {
    if(ind != m_mem_index){
        m_mem_index = ind;
        emit mem_indexChanged();
    }
}
QVector<QPoint> AnimaParete::mem() const {return m_mem;}
int AnimaParete::mem_index() const {return m_mem_index;}
QPoint AnimaParete::end_point() const {return m_end_point;}
QVector<QLine> AnimaParete::paths() const {return m_paths;}
void AnimaParete::paint(QPainter* painter){
    painter->setWindow(0,0,m_end_point.x(),m_end_point.y());
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
        fine.setWidthF(0.1);
        fine.setColor(Qt::darkGreen);
        painter->setPen(fine);
        painter->drawEllipse(QPointF(m_mem[m_mem_index]),0.2,0.2);
    }
}

