QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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
    test/digitalcircuitstest.h

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
    main.cpp


