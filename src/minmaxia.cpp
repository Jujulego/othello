// Importations
#include <limits>
#include <map>
#include <memory>
#include <iostream>
#include <vector>

#include "etat.h"
#include "ia.h"
#include "pion.h"
#include "minmaxia.h"

// Macros
#define VAL_COINS 1

// Constructeur
MinMaxIA::MinMaxIA(unsigned prof, COULEUR c) : IA(), m_prof(prof), m_couleur(c) {
}

// Méthodes
static const std::vector<std::pair<int,int>> PIONS = {
    {0, 0},         {2, 0},                 {5, 0},         {7, 0},
                    {2, 1}, {3, 1}, {4, 1}, {5, 1},
    {0, 2}, {1, 2},         {3, 2},                 {6, 2}, {7, 2},
            {1, 3}, {2, 3},                         {6, 3},
            {1, 4},                         {5, 4}, {6, 4},
    {0, 5}, {1, 5},                 {4, 5},         {6, 5}, {7, 5},
                    {2, 6}, {3, 6}, {4, 6}, {5, 6},
    {0, 7},         {2, 7},                 {5, 7},         {7, 7}
};

int MinMaxIA::heuristique(Etat&& etat) {
    // Initialisation
    COULEUR ennemi = (m_couleur == NOIR) ? BLANC : NOIR;
    std::map<COULEUR,int> mul;
    mul[m_couleur] = +1;
    mul[ennemi]    = -1;
    mul[VIDE]      =  0;
    int m = 0;

    // Calculs !
    for (auto p : PIONS)  m += mul[etat.othellier[p.first][p.second]];
    return m * (etat.scores[m_couleur] - etat.scores[ennemi]);
}

MinMaxIA::PV MinMaxIA::minmax(Etat&& etat, unsigned prof, std::shared_ptr<Noeud<PV>> noeud) {
    // Feuille !
    if (prof == m_prof) return {heuristique(std::move(etat)), {0, 0, VIDE}};

    // Branche
    auto coups = get_coups(etat);
    Pion pion = {0, 0, VIDE};
    int val;

    // Cas sans coup
    if (coups.size() == 0) return {heuristique(std::move(etat)), pion};

    // Initialisation
    if (prof % 2) { // Min
        val = std::numeric_limits<decltype(val)>::max(); // +infini !
    } else { // Max
        val = std::numeric_limits<decltype(val)>::min(); // -infini !
    }

    // Parcours des coups
    for (auto c : coups) {
        // Application du coup
        Etat e(etat);
        e.appliquer_coup(c);

        // Minmax sur l'enfant
        PV pv;
        if (noeud)
            pv = minmax(std::move(e), prof+1, noeud->add_fils({0, c}));
        else
            pv = minmax(std::move(e), prof+1, noeud->add_fils({0, c}));

        // Résultat
        if (prof % 2) { // Min
            if (pv.val < val) {
                pion = c;
                val = pv.val;
            }
        } else { // Max
            if (pv.val > val) {
                pion = c;
                val = pv.val;
            }
        }
    }

    // Résultat
    if (noeud) noeud->val().val = val;
    std::cout << (char) (pion.x + 'A') << (pion.y +1) << " " << pion.couleur << " " << val << std::endl;

    return {val, pion};
}

Pion MinMaxIA::jouer(Etat plateau) {
    // Initialisation
    m_arbre = Noeud<PV>::creer({0, {0, 0, VIDE}});
    m_couleur = plateau.joueur;

    // Algo !!!
    PV p = minmax(std::move(plateau), 0, m_arbre);
    m_arbre->val().val = p.val;

    return p.pion;
}







