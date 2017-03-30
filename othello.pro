QT += widgets

HEADERS += \
    qt/fprincipale.h \
    qt/pion.h \
    qt/othellier.h \
    src/etat.h \
    src/graphe.h

SOURCES += \
    qt/fprincipale.cpp \
    qt/main.cpp \
    qt/pion.cpp \
    qt/othellier.cpp

unix:!macx: LIBS += -L$$PWD/../../lib/ -lutils

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
