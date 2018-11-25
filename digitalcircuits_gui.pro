QT += core gui
QT -= console
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = digitalcircuits_gui
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


HEADERS += \
    abstracts/abstractcomponent.h \
    abstracts/abstractgate.h \
    abstracts/abstractinputcomponent.h \
    abstracts/abstractiocomponent.h \
    abstracts/abstractoutputcomponent.h \
    devices/indicator.h \
    devices/signalsource.h \
    gates/gateand.h \
    gates/gateor.h \
    gates/gatexor.h \
    globals/signal.h \
    pins/input.h \
    pins/output.h \
    test/digitalcircuitstest.h \
    gates/gatenand.h \
    gates/gatenot.h \
    devices/switch.h \
    devices/pushbutton.h \
    gui/mainwindow.h

SOURCES += \
    abstracts/abstractcomponent.cpp \
    abstracts/abstractgate.cpp \
    abstracts/abstractinputcomponent.cpp \
    abstracts/abstractiocomponent.cpp \
    abstracts/abstractoutputcomponent.cpp \
    devices/indicator.cpp \
    devices/signalsource.cpp \
    gates/gateand.cpp \
    gates/gateor.cpp \
    gates/gatexor.cpp \
    globals/signal.cpp \
    pins/input.cpp \
    pins/output.cpp \
    test/digitalcircuitstest.cpp \
    gates/gatenand.cpp \
    gates/gatenot.cpp \
    devices/switch.cpp \
    devices/pushbutton.cpp \
    main_gui.cpp \
    gui/mainwindow.cpp


