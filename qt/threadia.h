#ifndef THREADIA_H
#define THREADIA_H

// Dépandances
#include <QObject>

#include <memory>

#include "src/ia.h"
#include "src/pion.h"

// Classe
class ThreadIA : public QObject {
    Q_OBJECT

    private:
        // Attributs
        std::shared_ptr<IA> m_ia;

    public:
        // Constructeur
        ThreadIA(std::shared_ptr<IA> ia);

        // Accesseurs
        bool ok();

    signals:
        // Signaux
        void fini(Pion const& p);

    public slots:
        // Slots
        void lancer(class Othellier* o);
};

#include "othellier.h"

#endif // THREADIA_H
