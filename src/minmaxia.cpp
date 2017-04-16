// Importations
#include <limits>
#include <memory>
#include <iostream>
#include <set>

#include "etat.h"
#include "ia.h"
#include "pion.h"
#include "minmaxia.h"

#define VAL_COINS 10

// Constructeur
MinMaxIA::MinMaxIA(unsigned prof) : IA(), m_prof(prof-1) {
}

// Méthodes
int MinMaxIA::heuristique(const Etat &etat) {
    COULEUR ennemi = (m_couleur == NOIR) ? BLANC : NOIR;
    return etat.scores.at(m_couleur)
        + ((etat.othellier[0][0] == m_couleur) ? VAL_COINS : 0)
        + ((etat.othellier[0][7] == m_couleur) ? VAL_COINS : 0)
        + ((etat.othellier[7][0] == m_couleur) ? VAL_COINS : 0)
        + ((etat.othellier[7][7] == m_couleur) ? VAL_COINS : 0)
        -   etat.scores.at(ennemi)
        - ((etat.othellier[0][0] == ennemi) ? VAL_COINS : 0)
        - ((etat.othellier[0][7] == ennemi) ? VAL_COINS : 0)
        - ((etat.othellier[7][0] == ennemi) ? VAL_COINS : 0)
        - ((etat.othellier[7][7] == ennemi) ? VAL_COINS : 0);
}

MinMaxIA::PV MinMaxIA::minmax(const Etat &etat, unsigned prof) {
    // Feuille !
    if (prof == m_prof) return {heuristique(etat), {0, 0, VIDE}};

    // Branche
    auto coups = get_coups(etat);
    Pion pion;
    int val;

    if (prof % 2) { // Max
        // Initialisation
        val = std::numeric_limits<decltype(val)>::min(); // -infini !

        // Parcours des coups
        for (auto c : coups) {
            // Application du coup
            Etat e(etat);
            e.appliquer_coup(c);

            // Minmax sur l'enfant
            PV pv = minmax(e, prof+1);

            // Max !
            if (pv.val > val) {
                pion = c;
                val = pv.val;
            }
        }
    } else { // Min
        // Initialisation
        val = std::numeric_limits<decltype(val)>::max(); // +infini !

        // Parcours des coups
        for (auto c : coups) {
            // Application du coup
            Etat e(etat);
            e.appliquer_coup(c);

            // Minmax sur l'enfant
            PV pv = minmax(e, prof+1);

            // Min !
            if (pv.val < val) {
                pion = c;
                val = pv.val;
            }
        }
    }

    return {val, pion};
}

Pion MinMaxIA::jouer(Etat const& plateau) {
    // Construction de l'arbre
    m_couleur = plateau.joueur;
    return minmax(plateau, 0).pion;
}
