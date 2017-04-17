// Importations
#include <iostream>
#include <limits>

#include "alphabetaia.h"

// Constructeur
AlphaBetaIA::AlphaBetaIA(unsigned prof) : MinMaxIA(prof) {
}

// Méthodes
MinMaxIA::PV AlphaBetaIA::alphabeta(Etat&& etat, unsigned prof, int alpha, int beta) {
    // Feuille !
    if (prof == m_prof) return {heuristique(std::move(etat)), {0, 0, VIDE}};

    // Branche
    auto coups = get_coups(etat);
    Pion pion;
    int val;

    // Cas sans coup
    if (coups.size() == 0) return {heuristique(std::move(etat)), pion};

    // Initialisation
    if (prof % 2) { // Min
        // Initialisation
        val = std::numeric_limits<decltype(val)>::max(); // +infini !
    } else { // Max
        // Initialisation
        val = std::numeric_limits<decltype(val)>::min(); // -infini !
    }

    // Parcours des coups
    for (auto c : coups) {
        // Application du coup
        Etat e(etat);
        e.appliquer_coup(c);

        // AlphaBeta sur l'enfant
        PV pv = alphabeta(std::move(e), prof+1, alpha, beta);

        if (prof % 2) { // Min
            if (pv.val < val) {
                pion = c;
                val = pv.val;
            }

            // Coupure alpha
            if (pv.val <= alpha) return {val, pion};
            if (pv.val < beta) beta = pv.val;

        } else { // Max
            if (pv.val > val) {
                pion = c;
                val = pv.val;
            }

            // Coupure beta
            if (pv.val >= beta) return {val, pion};
            if (pv.val > alpha) alpha = pv.val;
        }
    }

    // Résultat
    std::cout << (char) (pion.x + 'A') << (pion.y +1) << " " << pion.couleur << " " << val << std::endl;
    return {val, pion};
}

Pion AlphaBetaIA::jouer(Etat plateau) {
    // Initialisation
    m_couleur = plateau.joueur;

    // Algo !
    return alphabeta(std::move(plateau), 0,
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    ).pion;
}
