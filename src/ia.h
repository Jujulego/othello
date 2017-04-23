#ifndef IA_H
#define IA_H

// Dépendances
#include <memory>
#include <set>
#include <vector>
#include <utility>
#include <string>

#include "etat.h"
#include "noeud.h"
#include "pion.h"
#include "console.h"

// Classe
class IA {
    public:
        // Type
        struct PV { int val; Pion pion; };

    protected:
        // Attributs
        std::shared_ptr<Noeud<PV>> m_arbre;

    public:
        // Destructeur
        virtual ~IA() = default;

        // Méthodes
        virtual std::string id() const = 0;
        virtual Pion jouer(Etat plateau) = 0;
        std::set<Pion,bool(&)(Pion const&,Pion const&)> get_coups(Etat const& plateau) const;
        void aff_arbre(Console* s_console, std::shared_ptr<Noeud<PV>> noeud, int num_coup);
        bool gere_arbre(Console* s_console, std::shared_ptr<Noeud<PV>> noeud, int num_coup, std::vector<std::vector<COULEUR>> othellier);
        void dess_plat(Console* s_console, int x, int y, Pion pion, std::vector<std::vector<COULEUR>> othellier, int val);

        // Accesseurs
        std::shared_ptr<Noeud<PV>> arbre() const;
};

#endif // IA_H
