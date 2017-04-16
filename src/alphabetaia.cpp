// Importations
#include <limits>

#include "alphabetaia.h"

// Constructeur
AlphaBetaIA::AlphaBetaIA(unsigned prof) : MinMaxIA(prof) {
}

// Méthodes
MinMaxIA::PV AlphaBetaIA::alphabeta(const Etat &etat, unsigned prof, int alpha, int beta) {
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

            // AlphaBeta sur l'enfant
            PV pv = alphabeta(e, prof+1, alpha, beta);

            // Max !
            if (pv.val > val) {
                pion = c;
                val = pv.val;
            }

            // Coupure beta
            if (pv.val >= beta) return {val, pion};

            // Maj alpha
            if (pv.val > alpha) alpha = pv.val;
        }
    } else { // Min
        // Initialisation
        val = std::numeric_limits<decltype(val)>::max(); // +infini !

        // Parcours des coups
        for (auto c : coups) {
            // Application du coup
            Etat e(etat);
            e.appliquer_coup(c);

            // AlphaBeta sur l'enfant
            PV pv = alphabeta(e, prof+1, alpha, beta);

            // Min !
            if (pv.val < val) {
                pion = c;
                val = pv.val;
            }

            // Coupure alpha
            if (pv.val <= alpha) return {val, pion};

            // Maj beta
            if (pv.val < beta) beta = pv.val;
        }
    }

    return {val, pion};
}

Pion AlphaBetaIA::jouer(const Etat &plateau) {
    m_couleur = plateau.joueur;
    return alphabeta(plateau, 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()).pion;
}
