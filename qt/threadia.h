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
        COULEUR m_couleur;

        class Othellier* m_othellier;

    public:
        // Constructeur
        ThreadIA(std::shared_ptr<IA> ia = nullptr, COULEUR couleur = VIDE);
        ThreadIA(ThreadIA const& thread_ia);

        // Opérateurs
        ThreadIA& operator = (ThreadIA const& thread_ia);

        // Accesseurs
        bool ok();

    signals:
        // Signaux
        void fini(Pion const& p);

    private slots:
        // Slots
        void exec();

    public slots:
        // Slots
        void lancer(class Othellier* o);
};

#include "othellier.h"

#endif // THREADIA_H
