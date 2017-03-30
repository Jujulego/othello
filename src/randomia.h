#ifndef RANDOMIA_H
#define RANDOMIA_H

// Dépendances
#include "etat.h"
#include "ia.h"
#include "pion.h"

// Classe
class RandomIA : public IA {
    public:
        // Méthodes
        virtual Pion jouer(Etat const& plateau) override;
};

#endif // RANDOMIA_H
