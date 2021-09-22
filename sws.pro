QT       += core gui multimedia xml

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
    audio/audiofifobuffer.cpp \
    core/coreinput.cpp \
    core/coremachine.cpp \
    core/coremodule.cpp \
    core/coremodulefactory.cpp \
    core/coreoutput.cpp \
    core/coreplug.cpp \
    core/coreschema.cpp \
    core/modules/coremoduleadd.cpp \
    core/modules/coremoduleclip.cpp \
    core/modules/coremoduleconstant.cpp \
    core/modules/coremoduleinput.cpp \
    core/modules/coremodulemultiply.cpp \
    core/modules/coremoduleoutput.cpp \
    core/modules/coremodulesinus.cpp \
    core/modules/coremoduletime.cpp \
    draw/drawninput.cpp \
    draw/drawnitem.cpp \
    draw/drawnmodule.cpp \
    draw/drawnmodulefactory.cpp \
    draw/drawnmodulerectangle.cpp \
    draw/drawnmoduleround.cpp \
    draw/drawnoutput.cpp \
    draw/drawnplug.cpp \
    draw/drawnschema.cpp \
    draw/drawnwire.cpp \
    draw/interactions/connectwireinteraction.cpp \
    draw/interactions/defaultinteraction.cpp \
    draw/modules/drawnmoduleadd.cpp \
    draw/modules/drawnmoduleclip.cpp \
    draw/modules/drawnmoduleconstant.cpp \
    draw/modules/drawnmoduleinput.cpp \
    draw/modules/drawnmodulemultiply.cpp \
    draw/modules/drawnmoduleoutput.cpp \
    draw/modules/drawnmodulesinus.cpp \
    draw/modules/drawnmoduletime.cpp \
    file/filedeserializer.cpp \
    file/fileserializer.cpp \
    gui/guimainwindow.cpp \
    gui/guimodulelibraryscene.cpp \
    gui/guimodulelibraryview.cpp \
    gui/guioscilloscopedisplay.cpp \
    gui/guioscilloscopedock.cpp \
    gui/guioutputcombobox.cpp \
    gui/guischemascene.cpp \
    gui/guischemaview.cpp \
    gui/oscilloscopebuffer.cpp \
    main.cpp \
    value/value.cpp

HEADERS += \
    audio/audiofifobuffer.h \
    core/coreexceptions.h \
    core/coreinput.h \
    core/coremachine.h \
    core/coremodule.h \
    core/coremodulefactory.h \
    core/coreoutput.h \
    core/coreplug.h \
    core/coresamplebuffer.h \
    core/coreschema.h \
    core/modules/coremoduleadd.h \
    core/modules/coremoduleclip.h \
    core/modules/coremoduleconstant.h \
    core/modules/coremoduleinput.h \
    core/modules/coremodulemultiply.h \
    core/modules/coremoduleoutput.h \
    core/modules/coremodulesinus.h \
    core/modules/coremoduletime.h \
    draw/drawninput.h \
    draw/drawnitem.h \
    draw/drawnmodule.h \
    draw/drawnmodulefactory.h \
    draw/drawnmodulerectangle.h \
    draw/drawnmoduleround.h \
    draw/drawnoutput.h \
    draw/drawnplug.h \
    draw/drawnschema.h \
    draw/drawnschemainteraction.h \
    draw/drawnwire.h \
    draw/interactions/connectwireinteraction.h \
    draw/interactions/defaultinteraction.h \
    draw/modules/drawnmoduleadd.h \
    draw/modules/drawnmoduleclip.h \
    draw/modules/drawnmoduleconstant.h \
    draw/modules/drawnmoduleinput.h \
    draw/modules/drawnmodulemultiply.h \
    draw/modules/drawnmoduleoutput.h \
    draw/modules/drawnmodulesinus.h \
    draw/modules/drawnmoduletime.h \
    file/filedeserializer.h \
    file/fileserializer.h \
    gui/guimainwindow.h \
    gui/guimodulelibraryscene.h \
    gui/guimodulelibraryview.h \
    gui/guioscilloscopedisplay.h \
    gui/guioscilloscopedock.h \
    gui/guioutputcombobox.h \
    gui/guischemascene.h \
    gui/guischemaview.h \
    gui/guistyle.h \
    gui/oscilloscopebuffer.h \
    value/string.h \
    value/value.h

FORMS += \
    gui/guimainwindow.ui \
    gui/guioscilloscopedock.ui

TRANSLATIONS += \
    sws_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    file/core.xsd \
    file/coreandgui.xsd

RESOURCES += \
    gui/gui.qrc
