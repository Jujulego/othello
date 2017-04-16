#ifndef MINMAXIA_H
#define MINMAXIA_H

// Dépendances
#include <memory>

#include "etat.h"
#include "ia.h"
#include "pion.h"

// Classe
class MinMaxIA : public IA {
    protected:
        // Type
        struct PV { int val; Pion pion; };

        // Attributs
        unsigned m_prof;
        COULEUR m_couleur;

        // Méthodes
        int heuristique(Etat const& etat);
        PV minmax(Etat const& etat, unsigned prof);

    public:
        // Constructeur
        MinMaxIA(unsigned prof);

        // Méthodes
        virtual Pion jouer(Etat const& plateau) override;
};

#endif // MINMAXIA_H
