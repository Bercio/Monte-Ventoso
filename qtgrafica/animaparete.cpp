#include "animaparete.h"
//TODO: load in into qml and display it; write the functions

AnimaParete::AnimaParete(QQuickPaintedItem *parent) : QQuickPaintedItem(parent) { ; }

AnimaParete::paint(){
    ;
}
AnimaParete::anima(){;}
AnimaParete::setParete(Parete p){ parete = p;}
AnimaParete::setMemoria(std::vector<int> mem){ memoria = mem;}
