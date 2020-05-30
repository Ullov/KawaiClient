#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Parsers/handler.h"
#include "KTools/log.h"
#include "KTools/options.h"
#include "KTools/enums.h"
#include "KTools/kawaiimageprovider.h"
#include "KTools/curl.h"
#include "KawaiFileFormat/kfffs.h"
#include "FsExplorer/fshandler.h"
#include "KTools/ktoolsqmlinterface.h"
#include "Parsers/parsersqmlinterface.h"
#include <QQmlContext>
#include <QVariant>
#include <QTextCodec>

static void registerTypesForQml()
{
    qRegisterMetaType<QVector<QByteArray>>("VectorByteArray");
    Parsers::registerQmlTypes();
    KTools::Enums::registerTypesForQml();

    /*Kff::Fs kffFs = Kff::Fs("E:/Win7アプリ/downloads", "kffTestFile.kff");
    Kff::Stream kffStream = kffFs.create<Kff::Stream>();
    QString path = "E:/Win7アプリ/downloads/kffTestFile.kff";
    if (KTools::File::fileExist(path))
        QFile::remove(path);
    kffStream.write(KTools::File::readFile<QByteArray>("E:/Win7アプリ/downloads", "MikuDB-VOM@S28-v2.torrent"));*/
}

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    registerTypesForQml();
    curl_global_init(CURL_GLOBAL_ALL);

    KTools::Options *options = new KTools::Options();
    Parsers::Handler *apiHandler = new Parsers::Handler();
    KawaiImageProvider *imgProvider = new KawaiImageProvider();
    FsHandler *fsExplorerHandle = new FsHandler();

    /*apiHandler->logger = */new KTools::Log();
    //apiHandler->options = options;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("parsers", &ParsersQmlInterface::obj);
    engine.rootContext()->setContextProperty("kTools", &KToolsQmlInterface::obj);
    engine.rootContext()->setContextProperty("fsExplorerHandle", fsExplorerHandle);
    engine.addImageProvider("kimage", imgProvider);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

