#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,4,0,0,0,1,0,0,0,
8,0,2,0,0,0,1,0,0,0,21,0,0,0,72,0,
2,0,0,0,2,0,0,0,19,0,0,0,158,0,2,0,
0,0,1,0,0,0,5,0,0,0,50,0,0,0,0,0,
1,0,0,0,0,0,0,0,72,0,2,0,0,0,1,0,
0,0,6,0,0,0,158,0,2,0,0,0,6,0,0,0,
7,0,0,2,34,0,0,0,0,0,1,0,0,0,0,0,
0,1,242,0,0,0,0,0,1,0,0,0,0,0,0,1,
18,0,2,0,0,0,3,0,0,0,13,0,0,0,222,0,
0,0,0,0,1,0,0,0,0,0,0,0,186,0,0,0,
0,0,1,0,0,0,0,0,0,2,84,0,0,0,0,0,
1,0,0,0,0,0,0,1,40,0,2,0,0,0,1,0,
0,0,18,0,0,1,168,0,2,0,0,0,1,0,0,0,
17,0,0,1,98,0,2,0,0,0,1,0,0,0,16,0,
0,1,120,0,0,0,0,0,1,0,0,0,0,0,0,1,
192,0,0,0,0,0,1,0,0,0,0,0,0,1,56,0,
0,0,0,0,1,0,0,0,0,0,0,0,116,0,0,0,
0,0,1,0,0,0,0,0,0,0,84,0,0,0,0,0,
1,0,0,0,0,0,0,0,18,0,0,0,0,0,1,0,
0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,2,0,0,7,19,0,106,0,
115,0,13,11,87,210,115,0,112,0,97,0,103,0,101,0,
108,0,111,0,97,0,100,0,101,0,114,0,46,0,106,0,
115,0,8,8,1,90,92,0,109,0,97,0,105,0,110,0,
46,0,113,0,109,0,108,0,3,0,0,120,60,0,113,0,
109,0,108,0,13,13,211,153,124,0,108,0,111,0,103,0,
87,0,105,0,110,0,100,0,111,0,119,0,46,0,113,0,
109,0,108,0,18,12,205,4,156,0,115,0,101,0,116,0,
116,0,105,0,110,0,103,0,115,0,87,0,105,0,110,0,
100,0,111,0,119,0,46,0,113,0,109,0,108,0,11,4,
83,56,195,0,81,0,109,0,108,0,73,0,110,0,99,0,
108,0,117,0,100,0,101,0,115,0,15,1,219,43,124,0,
75,0,97,0,119,0,97,0,105,0,66,0,117,0,116,0,
116,0,111,0,110,0,46,0,113,0,109,0,108,0,23,1,
167,128,220,0,75,0,97,0,119,0,97,0,105,0,72,0,
111,0,114,0,105,0,115,0,111,0,110,0,116,0,97,0,
108,0,76,0,105,0,110,0,101,0,46,0,113,0,109,0,
108,0,8,0,170,172,211,0,83,0,105,0,116,0,101,0,
84,0,97,0,98,0,115,0,5,0,87,15,6,0,80,0,
105,0,120,0,105,0,118,0,18,7,119,209,220,0,80,0,
105,0,120,0,105,0,118,0,77,0,97,0,105,0,110,0,
70,0,114,0,97,0,109,0,101,0,46,0,113,0,109,0,
108,0,8,14,236,83,249,0,69,0,120,0,104,0,101,0,
110,0,116,0,97,0,105,0,21,13,220,247,220,0,69,0,
120,0,104,0,101,0,110,0,116,0,97,0,105,0,77,0,
97,0,105,0,110,0,70,0,114,0,97,0,109,0,101,0,
46,0,113,0,109,0,108,0,9,4,216,50,155,0,77,0,
97,0,110,0,103,0,97,0,114,0,111,0,99,0,107,0,
22,8,196,173,92,0,77,0,97,0,110,0,103,0,97,0,
114,0,111,0,99,0,107,0,77,0,97,0,105,0,110,0,
70,0,114,0,97,0,109,0,101,0,46,0,113,0,109,0,
108,0,21,0,79,236,92,0,75,0,97,0,119,0,97,0,
105,0,86,0,101,0,114,0,116,0,105,0,99,0,97,0,
108,0,76,0,105,0,110,0,101,0,46,0,113,0,109,0,
108,0,22,0,41,249,156,0,75,0,97,0,119,0,97,0,
105,0,76,0,111,0,97,0,100,0,84,0,97,0,98,0,
66,0,117,0,116,0,116,0,111,0,110,0,46,0,113,0,
109,0,108,0,20,7,124,190,92,0,75,0,97,0,119,0,
97,0,105,0,68,0,111,0,119,0,110,0,108,0,111,0,
97,0,100,0,66,0,97,0,114,0,46,0,113,0,109,0,
108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _0x5f_QmlIncludes_qml_QmlIncludes_KawaiDownloadBar_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_settingsWindow_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_QmlIncludes_qml_QmlIncludes_KawaiLoadTabButton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__main_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _js_pageloader_js { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_QmlIncludes_qml_QmlIncludes_KawaiVerticalLine_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_QmlIncludes_qml_QmlIncludes_SiteTabs_Mangarock_MangarockMainFrame_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_QmlIncludes_qml_QmlIncludes_SiteTabs_Exhentai_ExhentaiMainFrame_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_QmlIncludes_qml_QmlIncludes_KawaiHorisontalLine_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_QmlIncludes_qml_QmlIncludes_SiteTabs_Pixiv_PixivMainFrame_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_QmlIncludes_qml_QmlIncludes_KawaiButton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_logWindow_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/QmlIncludes/qml/QmlIncludes/KawaiDownloadBar.qml"), &QmlCacheGeneratedCode::_0x5f_QmlIncludes_qml_QmlIncludes_KawaiDownloadBar_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/settingsWindow.qml"), &QmlCacheGeneratedCode::_qml_settingsWindow_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/QmlIncludes/qml/QmlIncludes/KawaiLoadTabButton.qml"), &QmlCacheGeneratedCode::_0x5f_QmlIncludes_qml_QmlIncludes_KawaiLoadTabButton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/main.qml"), &QmlCacheGeneratedCode::_0x5f__main_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/js/pageloader.js"), &QmlCacheGeneratedCode::_js_pageloader_js::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/QmlIncludes/qml/QmlIncludes/KawaiVerticalLine.qml"), &QmlCacheGeneratedCode::_0x5f_QmlIncludes_qml_QmlIncludes_KawaiVerticalLine_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/QmlIncludes/qml/QmlIncludes/SiteTabs/Mangarock/MangarockMainFrame.qml"), &QmlCacheGeneratedCode::_0x5f_QmlIncludes_qml_QmlIncludes_SiteTabs_Mangarock_MangarockMainFrame_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/QmlIncludes/qml/QmlIncludes/SiteTabs/Exhentai/ExhentaiMainFrame.qml"), &QmlCacheGeneratedCode::_0x5f_QmlIncludes_qml_QmlIncludes_SiteTabs_Exhentai_ExhentaiMainFrame_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/QmlIncludes/qml/QmlIncludes/KawaiHorisontalLine.qml"), &QmlCacheGeneratedCode::_0x5f_QmlIncludes_qml_QmlIncludes_KawaiHorisontalLine_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/QmlIncludes/qml/QmlIncludes/SiteTabs/Pixiv/PixivMainFrame.qml"), &QmlCacheGeneratedCode::_0x5f_QmlIncludes_qml_QmlIncludes_SiteTabs_Pixiv_PixivMainFrame_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/QmlIncludes/qml/QmlIncludes/KawaiButton.qml"), &QmlCacheGeneratedCode::_0x5f_QmlIncludes_qml_QmlIncludes_KawaiButton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/logWindow.qml"), &QmlCacheGeneratedCode::_qml_logWindow_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(qml_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    Q_CLEANUP_RESOURCE(qml_qmlcache);
    return 1;
}
