#ifndef MINMAXIA_H
#define MINMAXIA_H

// Dépendances
#include <memory>

#include "noeud.h"
#include "etat.h"
#include "ia.h"
#include "pion.h"

// Classe
class MinMaxIA : public IA {
    protected:
        // Attributs
        unsigned m_prof;
        COULEUR m_couleur;

        // Méthodes
        virtual int heuristique(Etat&& etat) final;
        virtual PV minmax(Etat&& etat, unsigned prof, std::shared_ptr<Noeud<PV>> noeud);

    public:
        // Constructeur
        MinMaxIA(unsigned prof, COULEUR c);

        // Méthodes
        virtual Pion jouer(Etat plateau) override;
};

#endif // MINMAXIA_H
