TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    qqpiprogressbar.cpp \
    qqpihyperbola.cpp \
    qqpisunpath.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    qqpiprogressbar.h \
    qqpihyperbola.h \
    qqpisunpath.h
