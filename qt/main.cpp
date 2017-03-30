// Importations
#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>
#include <QString>

#include <iostream>

#include <utils/debug.h>
#include <utils/signaux.h>

#include "fprincipale.h"

// Main
int main(int argc, char* argv[]) {
    // Initialisation signaux
    utils::init_debug();
    utils::init_signaux();

    utils::set_niveau("DEBUG");

    std::cout << std::boolalpha;

    // Définition de l'application
    QApplication app(argc, argv);

    // Traduction
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;

    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    // Execution
    FPrincipale f;
    f.show();

    return app.exec();
}
