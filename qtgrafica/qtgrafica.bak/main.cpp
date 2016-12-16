#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "grafica.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    grafica evoluzione;
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("evoluzione", &evoluzione);    
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    return app.exec();
}
