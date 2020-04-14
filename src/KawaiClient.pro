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
    cpp_h/KawaiFileFormat/kffstream.cpp \
    cpp_h/Parsers/sites/mangakakalotapi.cpp \
    cpp_h/main.cpp \
    cpp_h/KTools/HtmlAstMaker/htmlobject.cpp \
    cpp_h/KTools/HtmlAstMaker/htmltag.cpp \
    cpp_h/KTools/StaticVarsDeclarations.cpp \
    cpp_h/KTools/curlclass.cpp \
    cpp_h/KTools/fileidentifier.cpp \
    cpp_h/KTools/kawaiimageprovider.cpp \
    cpp_h/KTools/logging.cpp \
    cpp_h/KTools/optionshandler.cpp \
    cpp_h/KTools/stringoperations.cpp \
    cpp_h/KawaiFileFormat/KffFileTypes/kffdir.cpp \
    cpp_h/KawaiFileFormat/KffFileTypes/kfffileclass.cpp \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvarray.cpp \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvnumber.cpp \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvstring.cpp \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvtimestamp.cpp \
    cpp_h/KawaiFileFormat/kfffs.cpp \
    cpp_h/KTools/kawaiconverter.cpp \
    cpp_h/KTools/nativefs.cpp \
    cpp_h/KawaiFileFormat/kawaifileformat.cpp \
    cpp_h/KawaiFileFormat/kfffile.cpp \
    cpp_h/Parsers/apihandler.cpp \
    cpp_h/Parsers/parserclass.cpp \
    cpp_h/Parsers/sites/exhentaiapi.cpp \
    cpp_h/Parsers/sites/mangadexapi.cpp \
    cpp_h/Parsers/sites/mangairoapi.cpp \
    #cpp_h/Parsers/sites/mangarockapi.cpp \
    cpp_h/Parsers/sites/nhentaiapi.cpp \
    cpp_h/Parsers/sites/ninehentaiapi.cpp \
    cpp_h/Parsers/sites/pixivapi.cpp \
    cpp_h/Parsers/sites/twitterapi.cpp \
    cpp_h/Parsers/sites/vkapi.cpp \
    cpp_h/Parsers/sites/youtubeapi.cpp \

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
    cpp_h/KTools/HtmlAstMaker/htmlobject.h \
    cpp_h/KTools/HtmlAstMaker/htmltag.h \
    cpp_h/KTools/curlclass.h \
    cpp_h/KTools/fileidentifier.h \
    cpp_h/KTools/kawaiimageprovider.h \
    cpp_h/KTools/kenums.h \
    cpp_h/KTools/logging.h \
    cpp_h/KTools/optionshandler.h \
    cpp_h/KTools/stringoperations.h \
    cpp_h/KawaiFileFormat/KffFileTypes/kffdir.h \
    cpp_h/KawaiFileFormat/KffFileTypes/kfffileclass.h \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvarray.h \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvnumber.h \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvstring.h \
    cpp_h/KawaiFileFormat/KffValueTypes/kffvtimestamp.h \
    cpp_h/KawaiFileFormat/kfffs.h \
    cpp_h/KTools/kawaiconverter.h \
    cpp_h/KTools/nativefs.h \
    cpp_h/KawaiFileFormat/kawaifileformat.h \
    cpp_h/KawaiFileFormat/kfffile.h \
    cpp_h/KawaiFileFormat/kffstream.h \
    cpp_h/Parsers/apihandler.h \
    cpp_h/Parsers/parserclass.h \
    cpp_h/Parsers/sites/exhentaiapi.h \
    cpp_h/Parsers/sites/mangadexapi.h \
    cpp_h/Parsers/sites/mangairoapi.h \
    cpp_h/Parsers/sites/mangakakalotapi.h \
    #cpp_h/Parsers/sites/mangarockapi.h \
    cpp_h/Parsers/sites/nhentaiapi.h \
    cpp_h/Parsers/sites/ninehentaiapi.h \
    cpp_h/Parsers/sites/pixivapi.h \
    cpp_h/Parsers/sites/twitterapi.h \
    cpp_h/Parsers/sites/vkapi.h \
    cpp_h/Parsers/sites/youtubeapi.h

#curl
LIBS += -L$$PWD/libs/curl-x64/lib/dll/ -llibcurl.dll
INCLUDEPATH += $$PWD/libs/curl-x64/include
DEPENDPATH += $$PWD/libs/curl-x64/include

QMAKE_CXXFLAGS += -O3
