#ifndef MINMAXIA_H
#define MINMAXIA_H

// Dépendances
#include <memory>

#include "arbre.h"
#include "etat.h"
#include "ia.h"
#include "minmax.h"
#include "pion.h"

// Classe
class MinMaxIA : public IA {
    private:
        // Type
        struct CE { Etat etat; Pion coup; };

        // Attributs
        unsigned m_prof;
        COULEUR m_couleur;
        AlgoMinMax<std::shared_ptr<CE>> m_algo;

    public:
        // Constructeur
        MinMaxIA(unsigned prof);

        // Méthodes
        virtual Pion jouer(Etat const& plateau) override;
};

#endif // MINMAXIA_H
