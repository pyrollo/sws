QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/coreinput.cpp \
    core/coremachine.cpp \
    core/coremodule.cpp \
    core/coremodulefactory.cpp \
    core/coreoutput.cpp \
    core/coreplug.cpp \
    core/coreschema.cpp \
    core/modules/coremoduleadd.cpp \
    core/modules/coremoduleconstant.cpp \
    core/modules/coremoduleinput.cpp \
    core/modules/coremoduleoutput.cpp \
    core/value.cpp \
    draw/drawninput.cpp \
    draw/drawnitem.cpp \
    draw/drawnmodule.cpp \
    draw/drawnmodulefactory.cpp \
    draw/drawnmodulerectangle.cpp \
    draw/drawnoutput.cpp \
    draw/drawnplug.cpp \
    draw/drawnschema.cpp \
    draw/drawnwire.cpp \
    draw/modules/drawnmoduleadd.cpp \
    gui/guimainwindow.cpp \
    gui/guischemascene.cpp \
    gui/guischemaview.cpp \
    gui/guistyle.cpp \
    main.cpp

HEADERS += \
    core/core.h \
    core/coreexceptions.h \
    core/coreinput.h \
    core/coremachine.h \
    core/coremodule.h \
    core/coremodulefactory.h \
    core/coreoutput.h \
    core/coreplug.h \
    core/coreschema.h \
    core/modules/coremoduleadd.h \
    core/modules/coremoduleconstant.h \
    core/modules/coremoduleinput.h \
    core/modules/coremoduleoutput.h \
    core/value.h \
    draw/drawninput.h \
    draw/drawnitem.h \
    draw/drawnmodule.h \
    draw/drawnmodulefactory.h \
    draw/drawnmodulerectangle.h \
    draw/drawnoutput.h \
    draw/drawnplug.h \
    draw/drawnschema.h \
    draw/drawnwire.h \
    draw/modules/drawnmoduleadd.h \
    gui/guimainwindow.h \
    gui/guischemascene.h \
    gui/guischemaview.h \
    gui/guistyle.h

FORMS += \
    gui/guimainwindow.ui

TRANSLATIONS += \
    sws_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
