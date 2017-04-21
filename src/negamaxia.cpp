// Importations
#include <limits>
#include <iostream>

#include "negamaxia.h"

// Constructeur
NegaMaxIA::NegaMaxIA(unsigned prof, COULEUR c) : AlphaBetaIA(prof, c) {
}

// Méthodes
MinMaxIA::PV NegaMaxIA::alphabeta(Etat&& etat, unsigned prof, int alpha, int beta) {
    // Feuille !
    if (prof == m_prof) return {heuristique(std::move(etat)), {0, 0, VIDE}};

    // Branche
    auto coups = get_coups(etat);
    Pion pion;
    int val;

    // Cas sans coup
    if (coups.size() == 0) return {heuristique(std::move(etat)), pion};

    // Initialisation
    val = std::numeric_limits<decltype(val)>::min(); // -infini !

    // Parcours des coups
    for (auto c : coups) {
        // Application du coup
        Etat e(etat);
        e.appliquer_coup(c);

        // AlphaBeta sur l'enfant
        int v = -(alphabeta(std::move(e), prof+1, -beta, -alpha).val);

        // NegaMax :
        if (v > val) {
            val = v;
            pion = c;

            if (val > alpha) {
                alpha = val;

                if (alpha >= beta) {
                    return {val, pion};
                }
            }
        }
    }

    // Résultat
    return {val, pion};
}
