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
    cpp_h/KTools/htmlastmaker.cpp \
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
    cpp_h/fileidentifier.cpp \
    cpp_h/KawaiFileFormat/kawaifileformat.cpp \
    cpp_h/kawaihtmlparser.cpp \
    cpp_h/KawaiFileFormat/kfffile.cpp \
    cpp_h/sites/mangairo/mangairoapi.cpp \
    cpp_h/sites/twitter/twitterapi.cpp \
    cpp_h/sites/vk/vkapi.cpp \
    cpp_h/sites/youtube/youtubeapi.cpp \
        main.cpp \
    cpp_h/curlclass.cpp \
    cpp_h/parserclass.cpp \
    cpp_h/sites/exhentai/exhentaiapi.cpp \
    #cpp_h/sites/mangarock/mangarockapi.cpp \
    cpp_h/sites/nhentai/nhentaiapi.cpp \
    cpp_h/sites/pixiv/pixivapi.cpp \
    cpp_h/apihandler.cpp \
    cpp_h/logging.cpp \
    cpp_h/optionshandler.cpp \
    cpp_h/sites/mangadex/mangadexapi.cpp

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
    cpp_h/KTools/htmlastmaker.h \
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
    cpp_h/curlclass.h \
    cpp_h/fileidentifier.h \
    cpp_h/KawaiFileFormat/kawaifileformat.h \
    cpp_h/kawaihtmlparser.h \
    cpp_h/KawaiFileFormat/kfffile.h \
    cpp_h/parserclass.h \
    cpp_h/sites/exhentai/exhentaiapi.h \
    cpp_h/sites/mangairo/mangairoapi.h \
    #cpp_h/sites/mangarock/mangarockapi.h \
    cpp_h/sites/nhentai/nhentaiapi.h \
    cpp_h/sites/pixiv/pixivapi.h \
    cpp_h/apihandler.h \
    cpp_h/logging.h \
    cpp_h/optionshandler.h \
    cpp_h/sites/mangadex/mangadexapi.h \
    cpp_h/sites/twitter/twitterapi.h \
    cpp_h/sites/vk/vkapi.h \
    cpp_h/sites/youtube/youtubeapi.h

#curl
LIBS += -L$$PWD/libs/curl-x64/lib/dll/ -llibcurl.dll
INCLUDEPATH += $$PWD/libs/curl-x64/include
DEPENDPATH += $$PWD/libs/curl-x64/include

QMAKE_CXXFLAGS += -O3
