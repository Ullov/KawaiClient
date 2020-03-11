#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cpp_h/apihandler.h"
#include "cpp_h/logging.h"
#include "cpp_h/optionshandler.h"
#include <QQmlContext>
#include <QVariant>
#include <QTextCodec>
//#include <QQuickWindow>

int main(int argc, char *argv[])
{
    //QQuickWindow::setSceneGraphBackend(QSGRendererInterface::VulkanRhi);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    OptionsHandler *options = new OptionsHandler();
    Logging *logger = new Logging();
    ApiHandler *apiHandler = new ApiHandler();

    apiHandler->logger = logger;
    apiHandler->options = options;
    QQmlApplicationEngine engine;
    apiHandler->engine = &engine;
    engine.rootContext()->setContextProperty("apiHandler", apiHandler);
    engine.rootContext()->setContextProperty("logger", logger);
    engine.rootContext()->setContextProperty("options", options);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
