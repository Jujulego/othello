// Importations
#include <functional>
#include <iostream>
#include <set>

#include "pion.h"
#include "etat.h"
#include "ia.h"

// Fonctions
static bool cc(Pion const& c1, Pion const& c2) {
    return ((c1.x + c1.y * 10) < (c2.x + c2.y * 10));
}

// Constructeur
IA::IA() {
}

// Méthodes
std::set<Pion,bool(&)(Pion const&,Pion const&)> IA::get_coups(Etat const& plateau) const {
    // Déclaration du set
    std::set<Pion,bool(&)(Pion const&,Pion const&)> coups(cc);

    // Analyse du plateau
    COULEUR ennemi = (plateau.joueur == BLANC) ? NOIR : BLANC;

    for (Pion p : plateau.pions(plateau.joueur)) {
        // Recherche de coups possibles
        for (auto d : DIRECTIONS) {
            // Init recherche
            int i = p.x, j = p.y;
            d(i, j); // On se déplace 1 fois

            // Recherche
            bool e = false, v = false; // v => vide, e => ennemi
            for (; (i < 8) && (j < 8) && (i >= 0) && (j >= 0); d(i, j)) {
                if (plateau.othellier[i][j] == ennemi) {
                    e = true;
                } else {
                    v = (plateau.othellier[i][j] == VIDE);
                    break;
                }
            }

            // Confirmation
            if (e && v) coups.insert({i,j,plateau.joueur});
        }
    }

    //std::cout << "coups : " << coups.size() << std::endl;
    return coups;
}

std::shared_ptr<Noeud<IA::PV>> IA::arbre() const {
    return std::ref(m_arbre);
}
