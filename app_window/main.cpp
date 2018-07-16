#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "item_impl/borderitem.h"
#include "base_items/basicbaritem.h"
#include "base_items/basicdockitem.h"
#include "item_impl/statusbaritem.h"
#include "item_impl/titlebaritem.h"
#include "window_impl/vnaappwindow.h"
#include "window_impl/channelwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qSetMessagePattern("%{function} %{message}");

    qmlRegisterType<ChannelWindow>("channel_window",1,0,"ChannelWindow");
    qmlRegisterType<VNAAppWindow>("vnaapp_window",1,0,"VNAAppWindow");
    qmlRegisterType<BackgroundItem>("background_item",1,0,"BackgroundItem");
    qmlRegisterType<TitleBarItem>("titlebar_item",1,0,"TitleBarItem");
    qmlRegisterType<StatusBarItem>("statusbar_item",1,0,"StatusBarItem");
    qmlRegisterType<BasicDockItem>("dock_item",1,0,"DockItem");

    app.setApplicationDisplayName("Analyzer");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
