#include <QQuickView>
#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "grafica.h"
#include "dnamodel.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    grafica evoluzione;
    DnaModel dnas;
    QQmlApplicationEngine engine;
    qmlRegisterType<AnimaParete>("animazione",1,0, "Animazione");
    qRegisterMetaType<QVector<QLine>>();
    qRegisterMetaType<QVector<QPoint>>();
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("evoluzione", &evoluzione);
    ctx->setContextProperty("dnas",&dnas);
    QObject::connect(&evoluzione, &grafica::dnaChanged, &dnas, &DnaModel::setDna);
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}
