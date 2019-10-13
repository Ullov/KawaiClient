QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    cpp_h/curlclass.cpp \
    cpp_h/parserclass.cpp \
    cpp_h/sites/exhentai/exhentaiapi.cpp \
    cpp_h/sites/instagram/instagramapi.cpp \
    cpp_h/sites/mangarock/mangarockapi.cpp \
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
    cpp_h/curlclass.h \
    cpp_h/parserclass.h \
    cpp_h/sites/exhentai/exhentaiapi.h \
    cpp_h/sites/instagram/instagramapi.h \
    cpp_h/sites/mangarock/mangarockapi.h \
    cpp_h/sites/nhentai/nhentaiapi.h \
    cpp_h/sites/pixiv/pixivapi.h \
    cpp_h/apihandler.h \
    cpp_h/logging.h \
    cpp_h/optionshandler.h \
    cpp_h/sites/mangadex/mangadexapi.h


LIBS += -L$$PWD/libs/curl-x64/lib/dll/ -llibcurl.dll

INCLUDEPATH += $$PWD/libs/curl-x64/include
DEPENDPATH += $$PWD/libs/curl-x64/include
