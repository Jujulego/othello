// Importations
#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>
#include <QString>

#include <iostream>
#include <ctime>

#include "jeu.h"
#include "src/pion.h"

// Macros
Q_DECLARE_METATYPE(Pion)

// Main
int main(int argc, char* argv[]) {
    // Pratique :
    std::cout << std::boolalpha;

    // Init random
    srand(time(nullptr));

    // Définition de l'application
    QApplication app(argc, argv);

    qRegisterMetaType<Pion>();

    // Traduction
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;

    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    // Execution
    Jeu f;
    f.show();

    return app.exec();
}
