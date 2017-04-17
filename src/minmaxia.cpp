// Importations
#include <limits>
#include <memory>
#include <iostream>

#include "etat.h"
#include "ia.h"
#include "pion.h"
#include "minmaxia.h"

// Macros
#define VAL_COINS 10

// Constructeur
MinMaxIA::MinMaxIA(unsigned prof) : IA(), m_prof(prof) {
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

MinMaxIA::PV MinMaxIA::minmax(Etat etat, unsigned prof, std::shared_ptr<Noeud<PV>> noeud) {
    // Feuille !
    if (prof == m_prof) return {heuristique(etat), {0, 0, VIDE}};

    // Branche
    auto coups = get_coups(etat);
    Pion pion = {0, 0, VIDE};
    int val;

    // Initialisation
    if (prof % 2) { // Max
        val = std::numeric_limits<decltype(val)>::min(); // -infini !
    } else { // Min
        val = std::numeric_limits<decltype(val)>::max(); // +infini !
    }

    // Parcours des coups
    if (coups.size() == 0) return {heuristique(etat), pion};

    for (auto c : coups) {
        // Application du coup
        Etat e(etat);
        e.appliquer_coup(c);

        // Minmax sur l'enfant
        PV pv = minmax(e, prof+1, noeud->add_fils({0, c}));

        // Résultat
        if (prof % 2) { // Max
            if (pv.val > val) {
                pion = c;
                val = pv.val;
            }
        } else { // Min
            if (pv.val < val) {
                pion = c;
                val = pv.val;
            }
        }
    }

    // Résultat
    noeud->val().val = val;

    std::cout << (char) (pion.x + 'A') << (pion.y +1) << " " << pion.couleur << " " << val << std::endl;

    return {val, pion};
}

Pion MinMaxIA::jouer(Etat plateau) {
    // Initialisation
    m_arbre = Noeud<PV>::creer({0, {0, 0, VIDE}});
    m_couleur = plateau.joueur;

    // Algo !!!
    PV p = minmax(plateau, 0, m_arbre);
    m_arbre->val().val = p.val;

    return p.pion;
}
