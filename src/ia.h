#ifndef IA_H
#define IA_H

// Dépendances
#include <memory>
#include <set>
#include <vector>
#include <utility>

#include "etat.h"
#include "noeud.h"
#include "pion.h"
#include "console.h"
#include "Coordonnees.h"

// Classe
class IA {
    public:
        // Type
        struct PV { int val; Pion pion; };

    protected:
        // Attributs
        std::shared_ptr<Noeud<PV>> m_arbre;
        std::vector<std::vector <std::pair <Coordonnees, std::shared_ptr<Noeud<PV>>>>> m_tab; // ... le type le plus long jamais créé

    public:
        // Constructeur
        IA();

        // Destructeur
        virtual ~IA() = default;

        // Méthodes
        virtual Pion jouer(Etat plateau) = 0;
        std::set<Pion,bool(&)(Pion const&,Pion const&)> get_coups(Etat const& plateau) const;
        int charg_tab();
        void aff_arbre(Console* s_console, int x, int y);

        // Accesseurs
        std::shared_ptr<Noeud<PV>> arbre() const;
};

#endif // IA_H
