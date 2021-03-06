QT += quick
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS #__cplusplus=true

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp_h/BookReader/bookreaderhandler.cpp \
    cpp_h/FsExplorer/fshandler.cpp \
    cpp_h/KTools/archiverw.cpp \
    cpp_h/KTools/ktoolsqmlinterface.cpp \
    cpp_h/KawaiFileFormat/kffstream.cpp \
    cpp_h/Parsers/parsersqmlinterface.cpp \
    cpp_h/Parsers/sites/mangakakalot.cpp \
    cpp_h/Parsers/sites/nhentaidotcom.cpp \
    cpp_h/main.cpp \
    cpp_h/KTools/HtmlAstMaker/object.cpp \
    cpp_h/KTools/HtmlAstMaker/tag.cpp \
    cpp_h/KTools/StaticVarsDeclarations.cpp \
    cpp_h/KTools/curl.cpp \
    cpp_h/KTools/fileidentifier.cpp \
    cpp_h/KTools/kawaiimageprovider.cpp \
    cpp_h/KTools/log.cpp \
    cpp_h/KTools/options.cpp \
    cpp_h/KTools/exforstring.cpp \
    cpp_h/KawaiFileFormat/KffFileTypes/kffdir.cpp \
    cpp_h/KawaiFileFormat/KffFileTypes/kfffileclass.cpp \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvarray.cpp \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvnumber.cpp \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvstring.cpp \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvtimestamp.cpp \
    cpp_h/KawaiFileFormat/kfffs.cpp \
    cpp_h/KTools/converter.cpp \
    cpp_h/KTools/file.cpp \
    cpp_h/KawaiFileFormat/kawaifileformat.cpp \
    cpp_h/KawaiFileFormat/kfffile.cpp \
    cpp_h/Parsers/handler.cpp \
    cpp_h/Parsers/parserclass.cpp \
    cpp_h/Parsers/sites/exhentai.cpp \
    cpp_h/Parsers/sites/mangadex.cpp \
    cpp_h/Parsers/sites/mangairo.cpp \
    #cpp_h/Parsers/sites/mangarockapi.cpp \
    cpp_h/Parsers/sites/nhentai.cpp \
    cpp_h/Parsers/sites/ninehentai.cpp \
    cpp_h/Parsers/sites/pixiv.cpp \
    cpp_h/Parsers/sites/twitter.cpp \
    cpp_h/Parsers/sites/vk.cpp \
    cpp_h/Parsers/sites/youtube.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cpp_h/BookReader/bookreaderhandler.h \
    cpp_h/FsExplorer/fshandler.h \
    cpp_h/KTools/HtmlAstMaker/object.h \
    cpp_h/KTools/HtmlAstMaker/tag.h \
    cpp_h/KTools/archiverw.h \
    cpp_h/KTools/curl.h \
    cpp_h/KTools/fileidentifier.h \
    cpp_h/KTools/kawaiimageprovider.h \
    cpp_h/KTools/enums.h \
    cpp_h/KTools/ktoolsqmlinterface.h \
    cpp_h/KTools/log.h \
    cpp_h/KTools/options.h \
    cpp_h/KTools/exforstring.h \
    cpp_h/KawaiFileFormat/KffFileTypes/kffdir.h \
    cpp_h/KawaiFileFormat/KffFileTypes/kfffileclass.h \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvarray.h \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvnumber.h \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvstring.h \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvtimestamp.h \
    cpp_h/KawaiFileFormat/kfffs.h \
    cpp_h/KTools/converter.h \
    cpp_h/KTools/file.h \
    cpp_h/KawaiFileFormat/kawaifileformat.h \
    cpp_h/KawaiFileFormat/kfffile.h \
    cpp_h/KawaiFileFormat/kffstream.h \
    cpp_h/Parsers/handler.h \
    cpp_h/Parsers/parserclass.h \
    cpp_h/Parsers/parsersqmlinterface.h \
    cpp_h/Parsers/sites/exhentai.h \
    cpp_h/Parsers/sites/mangadex.h \
    cpp_h/Parsers/sites/mangairo.h \
    cpp_h/Parsers/sites/mangakakalot.h \
    #cpp_h/Parsers/sites/mangarockapi.h \
    cpp_h/Parsers/sites/nhentai.h \
    cpp_h/Parsers/sites/nhentaidotcom.h \
    cpp_h/Parsers/sites/ninehentai.h \
    cpp_h/Parsers/sites/pixiv.h \
    cpp_h/Parsers/sites/twitter.h \
    cpp_h/Parsers/sites/vk.h \
    cpp_h/Parsers/sites/youtube.h

#Curl
LIBS += -L$$PWD/libs/curl-x64/lib/dll/ -llibcurl.dll
INCLUDEPATH += $$PWD/libs/curl-x64/include
DEPENDPATH += $$PWD/libs/curl-x64/include

#KArchive
LIBS += -L$$PWD/libs/karchive-5.69.0/lib/ -llibKF5Archive.dll
INCLUDEPATH += $$PWD/libs/karchive-5.69.0/include
DEPENDPATH += $$PWD/libs/karchive-5.69.0/include

QMAKE_CXXFLAGS += -O3

# defines macros for debug build
debug {DEFINES += KAWAI_DEBUG}
