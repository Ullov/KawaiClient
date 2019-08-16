#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cpp_h/apihandler.h"
#include "cpp_h/logging.h"
#include <QQmlContext>
#include <QVariant>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Logging *logger = new Logging();
    ApiHandler *apiHandler = new ApiHandler();
    apiHandler->logger = logger;
    QQmlApplicationEngine engine;
    apiHandler->engine = &engine;
    engine.rootContext()->setContextProperty("apiHandler", apiHandler);
    engine.rootContext()->setContextProperty("logging", logger);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
