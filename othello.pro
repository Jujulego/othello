QT += widgets

HEADERS += \
    qt/pion.h \
    qt/othellier.h \
    src/etat.h \
    src/ia.h \
    src/randomia.h \
    src/pion.h \
    qt/jeu.h \
    src/minmax.h \
    src/arbre.h \
    src/macros.h \
    src/minmaxia.h

SOURCES += \
    qt/main.cpp \
    qt/pion.cpp \
    qt/othellier.cpp \
    src/ia.cpp \
    src/randomia.cpp \
    qt/jeu.cpp \
    src/minmaxia.cpp \
    src/etat.cpp

unix:!macx: LIBS += -L$$PWD/../../lib/ -lutils

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
