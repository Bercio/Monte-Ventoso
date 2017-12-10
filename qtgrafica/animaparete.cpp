#include "animaparete.h"
AnimaParete::AnimaParete(QQuickPaintedItem *parent) : QQuickPaintedItem(parent), m_mem_index(0) {
}
void AnimaParete::setPaths(QVector<QLine> v) {
    if(v != m_paths){
        m_paths = v;
        emit pathsChanged(v);
    }
}
void AnimaParete::setMem(QVector<QPoint> mem) {
    m_mem = mem;
    emit memChanged(mem);
}
void AnimaParete::setEnd(int e){
    m_end = e;
    emit endChanged(e);
}
int AnimaParete::end() const{
    return m_end;
}
void AnimaParete::get_end() {
    if(m_mem.empty()){
        setEnd(-1);
        return;
    }
    int r = m_mem.length();
    QVector<QPoint>::reverse_iterator rend = ++m_mem.rend();
    for(QVector<QPoint>::reverse_iterator i = m_mem.rbegin(); i != rend && *i == m_mem.back(); ++i) --r;
    setEnd(r);
}
void AnimaParete::setMem_index(int ind) {
    if(ind != m_mem_index){
        m_mem_index = ind;
        emit mem_indexChanged(ind);
    }
}
QVector<QPoint> AnimaParete::mem() const {return m_mem;}
int AnimaParete::mem_index() const {return m_mem_index;}

QVector<QLine> AnimaParete::paths() const {return m_paths;}
void AnimaParete::paint(QPainter* painter){
    painter->setWindow(QRect(m_end_point + QPoint(1,1),QPoint(-2,-2)));
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
        fine.setWidthF(0.0001);
        if(m_mem_index == m_end)  fine.setColor(Qt::darkRed);
        else  fine.setColor(Qt::darkGreen);
        painter->setPen(fine);
        QFont f = painter->font();
        f.setPointSizeF(0.4);
        painter->setFont(f);
        painter->scale(-1,-1);
        painter->drawText(QPointF(-0.6,+0.35) - QPoint(m_mem[m_mem_index]),"🐵");
    }
}
void AnimaParete::clear_mem() { m_mem.clear(); emit memChanged(m_mem);}

