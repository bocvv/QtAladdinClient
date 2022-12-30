#include "aladdin_maker.h"
#include "aladdin_client.h"
#include "fingertip_search.h"
#include "data_listmodel.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtCharts>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    DataListModel model;
    model.init_from_redis();

    QApplication app(argc, argv);

    qmlRegisterType<AladdinMaker>("yd.qt.AladdinMaker", 1, 0, "AladdinMaker");
    qmlRegisterType<AladdinController>("yd.qt.AladdinController", 1, 0, "AladdinController");
    qmlRegisterType<FintipController>("yd.qt.FintipController", 1, 0, "FintipController");

    QQmlApplicationEngine engine;
    // const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.setOfflineStoragePath("/root/wangbw/work/aladdin_client");

    // add list model which get data from redis server
    engine.rootContext()->setContextProperty("wordModel", &model);

    engine.load(url);

    return app.exec();
}
