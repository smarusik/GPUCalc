#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "basicwindow.h"
#include "contentlessitems.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qSetMessagePattern("%{function} %{message}");

    qmlRegisterType<BasicWindow>("vna_application_window",1,0,"VNAApplicationWindow");
    qmlRegisterType<BackgroundItem>("background_item",1,0,"BackgroundItem");
    qmlRegisterType<BaseContentlessItem>("workarea_item",1,0,"WorkAreaItem");
    qmlRegisterType<TitleBarItem>("titlebar_item",1,0,"TitleBarItem");

    app.setApplicationDisplayName("Kill'em all");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
