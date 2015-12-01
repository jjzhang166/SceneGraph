#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qqpiprogressbar.h"
#include "qqpihyperbola.h"
#include "qqpisunpath.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<QQPIProgressBar>("QuickPaintedItemEx", 1, 0, "ProgressBarEx");
    qmlRegisterType<QQPIHyperbola>("QuickPaintedItemEx", 1, 0, "HyperbolaEx");
    qmlRegisterType<QQPISunPath>("QuickPaintedItemEx", 1, 0, "SunPath");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
