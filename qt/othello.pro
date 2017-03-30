QT += widgets

HEADERS += \
    fprincipale.h \
    pion.h \
    othellier.h \
    etat.h

SOURCES += \
    fprincipale.cpp \
    main.cpp \
    pion.cpp \
    othellier.cpp

unix:!macx: LIBS += -L$$PWD/../../lib/ -lutils

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
