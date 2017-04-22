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
        std::vector<std::vector <std::pair <int, std::shared_ptr<Noeud<PV>>>>> m_tab; // ... le type le plus long jamais créé
        // Ce tableau permettra, pour l'affichage et le parcours de l'arbre, d'accéder plus facilement aux noeuds
        // .first (int) : abscisse du noeud dans l'arbre
        // .second (shared_ptr<Noeud<PV>>) : pointeur sur le noeud

    public:
        // Destructeur
        virtual ~IA() = default;

        // Méthodes
        virtual std::string id() const = 0;
        virtual Pion jouer(Etat plateau) = 0;
        std::set<Pion,bool(&)(Pion const&,Pion const&)> get_coups(Etat const& plateau) const;
        
        int charg_tab();
        void aff_arbre(Console* s_console, int x, int y);

        // Accesseurs
        std::shared_ptr<Noeud<PV>> arbre() const;
};

#endif // IA_H
