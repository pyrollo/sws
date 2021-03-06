QT       += core gui multimedia xml svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    core/modules/coremodulesine.cpp \
    core/modules/coremoduletime.cpp \
    draw/drawnicon.cpp \
    draw/drawninput.cpp \
    draw/drawninteractive.cpp \
    draw/drawnitem.cpp \
    draw/drawnitemfactory.cpp \
    draw/drawnmodule.cpp \
    draw/drawnmodulerectangle.cpp \
    draw/drawnmoduleround.cpp \
    draw/drawnoutput.cpp \
    draw/drawnplug.cpp \
    draw/drawnresizeable.cpp \
    draw/drawnschema.cpp \
    draw/drawnschemainteraction.cpp \
    draw/drawnwire.cpp \
    draw/interactions/connectwireinteraction.cpp \
    draw/interactions/defaultinteraction.cpp \
    draw/modules/drawnmoduleconstant.cpp \
    draw/modules/drawnmoduleerror.cpp \
    draw/modules/drawnmoduleinput.cpp \
    draw/modules/drawnmoduleoutput.cpp \
    file/filedeserializer.cpp \
    file/fileserializer.cpp \
    gui/widgets/guicolorbutton.cpp \
    gui/widgets/guiinfinitedial.cpp \
    gui/widgets/guivaluelistspinbox.cpp \
    gui/guimainwindow.cpp \
    gui/guimenufile.cpp \
    gui/guimodulelibraryscene.cpp \
    gui/guimodulelibraryview.cpp \
    gui/guioutputcombobox.cpp \
    gui/guischemascene.cpp \
    gui/guischemaview.cpp \
    gui/oscilloscope/guioscilloscopedisplay.cpp \
    gui/oscilloscope/guioscilloscopedock.cpp \
    gui/oscilloscope/guioscilloscopeprobe.cpp \
    gui/oscilloscope/guioscilloscopeprobeframe.cpp \
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
    core/modules/coremodulesine.h \
    core/modules/coremoduletime.h \
    draw/drawnicon.h \
    draw/drawninput.h \
    draw/drawninteractive.h \
    draw/drawnitem.h \
    draw/drawnitemfactory.h \
    draw/drawnmodule.h \
    draw/drawnmodulerectangle.h \
    draw/drawnmoduleround.h \
    draw/drawnoutput.h \
    draw/drawnplug.h \
    draw/drawnresizeable.h \
    draw/drawnschema.h \
    draw/drawnschemainteraction.h \
    draw/drawnwire.h \
    draw/interactions/connectwireinteraction.h \
    draw/interactions/defaultinteraction.h \
    draw/modules/drawnmoduleconstant.h \
    draw/modules/drawnmoduleerror.h \
    draw/modules/drawnmoduleinput.h \
    draw/modules/drawnmoduleoutput.h \
    draw/style.h \
    file/filedeserializer.h \
    file/fileserializer.h \
    gui/widgets/guicolorbutton.h \
    gui/widgets/guiinfinitedial.h \
    gui/widgets/guivaluelistspinbox.h \
    gui/guimainwindow.h \
    gui/guimenufile.h \
    gui/guimodulelibraryscene.h \
    gui/guimodulelibraryview.h \
    gui/guioutputcombobox.h \
    gui/guischemascene.h \
    gui/guischemaview.h \
    gui/oscilloscope/guioscilloscopedisplay.h \
    gui/oscilloscope/guioscilloscopedock.h \
    gui/oscilloscope/guioscilloscopeprobe.h \
    gui/oscilloscope/guioscilloscopeprobeframe.h \
    utils/resizeablerollingbuffer.h \
    utils/rollingbuffer.h \
    value/string.h \
    value/value.h

FORMS += \
    gui/guimainwindow.ui \
    gui/oscilloscope/guioscilloscopedock.ui \
    gui/oscilloscope/guioscilloscopeprobeframe.ui

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
    draw/resources/draw.qrc \
    gui/gui.qrc
