#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>

#include <sourceimages.h>
#include <imageprovider.h>
#include <mosaicview.h>
#include <maindriver.h>


int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<MoMosaicView>("MoMosaic", 1, 0, "MoMosaicView");

    // register some variables with QML engine.
    MoSourceImages sourceImages;
    engine.rootContext()->setContextProperty(
                "sourceImages", &sourceImages);
    MoImageProvider* imageProvider = new MoImageProvider(&sourceImages);
    engine.addImageProvider(QLatin1String("imageProvider"),
                            imageProvider);
    MoMainDriver mainDriver;
    mainDriver.setSourceImages(&sourceImages);
    engine.rootContext()->setContextProperty(QLatin1String("mainDriver"),
                                             &mainDriver);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    QObject* mosaicView =
            engine.rootObjects().value(0)->findChild<QObject*>(QString("mosaicView"));
    if (mosaicView) {
        QObject::connect(&mainDriver, &MoMainDriver::modelChanged,
                         static_cast<MoMosaicView*>(mosaicView),
                         &MoMosaicView::setModel);
    } else {
        qDebug() << "mosaicView not found.";
    }

    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();

    return app.exec();
}
