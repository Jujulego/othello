// Importations
#include <limits>
#include <map>
#include <memory>
#include <iostream>
#include <string>
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
int MinMaxIA::heuristique(Etat&& etat) {
    // Initialisation
    COULEUR ennemi = (m_couleur == NOIR) ? BLANC : NOIR;
    return ((2*etat.scores[m_couleur]*etat.coups_restant(m_couleur)) - (etat.coups_restant(ennemi)*etat.scores[ennemi]));
}

std::string MinMaxIA::id() const {
	return "minmax";
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
            pv = minmax(std::move(e), prof+1, nullptr);

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

    return {val, pion};
}

Pion MinMaxIA::jouer(Etat plateau) {
    // Initialisation
    m_arbre = Noeud<PV>::creer({0, {0, 0, VIDE}});
    m_couleur = plateau.joueur;

    // Algo !!!
    PV p = minmax(std::move(plateau), 0, (m_prof > 6) ? nullptr : m_arbre);
    m_arbre->val().val = p.val;

    return p.pion;
}
