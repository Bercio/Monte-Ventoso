#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "grafica.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    grafica g;
    QGuiApplication app(argc, argv);
    QQuickView view;
    view.engine()->rootContext()->setContextProperty("msgBoard", &msgBoard);
    view.setSource(QUrl::fromLocalFile("MyItem.qml"));
    view.show();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
