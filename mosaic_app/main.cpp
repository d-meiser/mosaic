#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>

#include <sourceimages.h>
#include <imageprovider.h>
#include <mosaicimageprovider.h>
#include <maindriver.h>


int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MoSourceImages mosaicImages;
    engine.rootContext()->setContextProperty(
          "mosaicImages", &mosaicImages);
    MoImageProvider* sourceImageProvider = new MoImageProvider(&mosaicImages);
    engine.addImageProvider(QLatin1String("sourceImageProvider"),
                            sourceImageProvider);

    MoMainDriver mainDriver;
    engine.rootContext()->setContextProperty(
          "mainDriver", &mainDriver);

    MoMosaicImageProvider* mosaicImageProvider = new MoMosaicImageProvider();
    mosaicImageProvider->setModel(mainDriver.mosaicModel());
    engine.addImageProvider(QLatin1String("mosaicImageProvider"),
                            mosaicImageProvider);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();

    return app.exec();
}
