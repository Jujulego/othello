QT += widgets

HEADERS += \
    qt/pion.h \
    qt/othellier.h \
    src/etat.h \
    src/ia.h \
    src/randomia.h \
    src/pion.h \
    qt/jeu.h \
    src/macros.h \
    src/minmaxia.h \
    qt/threadia.h \
    src/alphabetaia.h \
    src/negamaxia.h \
    src/noeud.h

SOURCES += \
    qt/main.cpp \
    qt/pion.cpp \
    qt/othellier.cpp \
    src/ia.cpp \
    src/randomia.cpp \
    qt/jeu.cpp \
    src/minmaxia.cpp \
    src/etat.cpp \
    qt/threadia.cpp \
    src/alphabetaia.cpp \
    src/negamaxia.cpp

QMAKE_CXXFLAGS += -O3 -std=c++14
INCLUDEPATH += $$PWD/src
