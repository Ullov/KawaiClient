#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Parsers/apihandler.h"
#include "KTools/logging.h"
#include "KTools/optionshandler.h"
#include "KTools/kenums.h"
#include "KTools/kawaiimageprovider.h"
#include "KTools/curlclass.h"
#include "KawaiFileFormat/kfffs.h"
#include <QQmlContext>
#include <QVariant>
#include <QTextCodec>

static void registerTypesForQml()
{
    /*Kff::Fs kffFs = Kff::Fs("E:/Win7アプリ/downloads", "kffTestFile.kff");
    Kff::Stream kffStream = kffFs.create<Kff::Stream>();
    QString path = "E:/Win7アプリ/downloads/kffTestFile.kff";
    if (NativeFs::fileExist(path))
        QFile::remove(path);
    kffStream.write(NativeFs::readFile<QByteArray>("E:/Win7アプリ/downloads", "MikuDB-VOM@S28-v2.torrent"));*/


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
    Logging *logger = new Logging();
    ApiHandler *apiHandler = new ApiHandler();
    KawaiImageProvider *imgProvider = new KawaiImageProvider();

    apiHandler->logger = logger;
    apiHandler->options = options;
    QQmlApplicationEngine engine;
    apiHandler->engine = &engine;
    engine.rootContext()->setContextProperty("apiHandler", apiHandler);
    engine.rootContext()->setContextProperty("logger", logger);
    engine.rootContext()->setContextProperty("options", options);
    engine.addImageProvider("kimage", imgProvider);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

