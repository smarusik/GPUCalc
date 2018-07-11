#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "base_windows/basicwindow.h"
#include "item_impl/borderitem.h"
#include "base_items/basicbaritem.h"
#include "item_impl/statusbaritem.h"
#include "item_impl/titlebaritem.h"
#include "window_impl/vnaappwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qSetMessagePattern("%{function} %{message}");

    qmlRegisterType<BasicWindow>("base_window",1,0,"BaseWindow");
    qmlRegisterType<VNAAppWindow>("vnaapp_window",1,0,"VNAAppWindow");
    qmlRegisterType<BackgroundItem>("background_item",1,0,"BackgroundItem");
    qmlRegisterType<BasicContentlessItem>("workarea_item",1,0,"WorkAreaItem");
    qmlRegisterType<TitleBarItem>("titlebar_item",1,0,"TitleBarItem");
    qmlRegisterType<StatusBarItem>("statusbar_item",1,0,"StatusBarItem");

    app.setApplicationDisplayName("Kill'em all");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
