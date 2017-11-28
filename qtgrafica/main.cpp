#include <QQuickView>
#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "grafica.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    grafica evoluzione;
    qmlRegisterType<AnimaParete>("animazione",1,0, "Animazione");
    qRegisterMetaType<QVector<QLine>>();
    qRegisterMetaType<QVector<QPoint>>();

    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("evoluzione", &evoluzione);
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}
