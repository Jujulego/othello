#ifndef IA_H
#define IA_H

// Dépendances
#include <set>

#include "pion.h"
#include "etat.h"

// Classe
class IA {
    public:
        // Destructeur
        virtual ~IA();

        // Méthodes
        virtual Pion jouer(Etat const& plateau) = 0;
        std::set<Pion,bool(&)(Pion const&,Pion const&)> get_coups(Etat const& plateau) const;
};

#endif // IA_H
