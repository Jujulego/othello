#ifndef IA_H
#define IA_H

// Dépendances
#include <memory>
#include <set>

#include "etat.h"
#include "noeud.h"
#include "pion.h"

// Classe
class IA {
    public:
        // Type
        struct PV { int val; Pion pion; };

    protected:
        // Attributs
        std::shared_ptr<Noeud<PV>> m_arbre;

    public:
        // Constructeur
        IA();

        // Destructeur
        virtual ~IA() = default;

        // Méthodes
        virtual Pion jouer(Etat plateau) = 0;
        std::set<Pion,bool(&)(Pion const&,Pion const&)> get_coups(Etat const& plateau) const;

        // Accesseurs
        std::shared_ptr<Noeud<PV>> arbre() const;
};

#endif // IA_H
