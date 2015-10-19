#include <QtGui>
#include <QQmlApplicationEngine>
#include "Plot.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Plot>("CustomGeometry", 1, 0, "Graph");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
