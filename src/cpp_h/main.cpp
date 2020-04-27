#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Parsers/apihandler.h"
#include "KTools/logging.h"
#include "KTools/optionshandler.h"
#include "KTools/kenums.h"
#include "KTools/kawaiimageprovider.h"
#include "KTools/curlclass.h"
#include "KawaiFileFormat/kfffs.h"
#include "FsExplorer/fshandler.h"
#include "KTools/ktoolsqmlinterface.h"
#include <QQmlContext>
#include <QVariant>
#include <QTextCodec>

static void registerTypesForQml()
{
    qRegisterMetaType<QVector<QByteArray>>("VectorByteArray");
    KEnums::registerTypesForQml();
}

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    registerTypesForQml();
    curl_global_init(CURL_GLOBAL_ALL);

    OptionsHandler *options = new OptionsHandler();
    ApiHandler *apiHandler = new ApiHandler();
    KawaiImageProvider *imgProvider = new KawaiImageProvider();
    FsHandler *fsExplorerHandle = new FsHandler();

    apiHandler->logger = new Logging();
    apiHandler->options = options;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("apiHandler", apiHandler);
    engine.rootContext()->setContextProperty("kTools", new KToolsQmlInterface());
    engine.rootContext()->setContextProperty("fsExplorerHandle", fsExplorerHandle);
    engine.addImageProvider("kimage", imgProvider);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

