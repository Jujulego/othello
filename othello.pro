QT += widgets

HEADERS += \
    qt/pion.h \
    qt/othellier.h \
    src/etat.h \
    src/graphe.h \
    src/ia.h \
    src/randomia.h \
    src/pion.h \
    qt/jeu.h

SOURCES += \
    qt/main.cpp \
    qt/pion.cpp \
    qt/othellier.cpp \
    src/ia.cpp \
    src/randomia.cpp \
    qt/jeu.cpp

unix:!macx: LIBS += -L$$PWD/../../lib/ -lutils

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
