// Importations
#include <iostream>
#include <limits>
#include <string>

#include "alphabetaia.h"

// Constructeur
AlphaBetaIA::AlphaBetaIA(unsigned prof, COULEUR c) : MinMaxIA(prof, c) {
}

// Méthodes
std::string AlphaBetaIA::id() const {
	return "alphabeta";
}

MinMaxIA::PV AlphaBetaIA::alphabeta(Etat&& etat, unsigned prof, int alpha, int beta, std::shared_ptr<Noeud<MinMaxIA::PV>> noeud) {
    // Feuille !
    if (prof == m_prof) {
    	int val = heuristique(std::move(etat));
    	if (noeud) noeud->val().val = val;
    	return {val, {0, 0, VIDE}};
    }

    // Branche
    auto coups = get_coups(etat);
    Pion pion;
    int val;

    // Cas sans coup
    if (coups.size() == 0) {
    	int val = heuristique(std::move(etat));
    	if (noeud) noeud->val().val = val;
    	return {val, pion};
    }

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
        PV pv;
        if (noeud)
        	pv = alphabeta(std::move(e), prof+1, alpha, beta, noeud->add_fils({0, c}));
        else
        	pv = alphabeta(std::move(e), prof+1, alpha, beta, nullptr);

        if (prof % 2) { // Min
            if (pv.val < val) {
                pion = c;
                val = pv.val;
            }

            // Coupure alpha
            if (pv.val <= alpha) break;
            if (pv.val < beta) beta = pv.val;

        } else { // Max
            if (pv.val > val) {
                pion = c;
                val = pv.val;
            }

            // Coupure beta
            if (pv.val >= beta) break;
            if (pv.val > alpha) alpha = pv.val;
        }
    }
    
    // Résultat
    if (noeud) {
    	noeud->val().val = val;
    }
    
    // Résultat
    return {val, pion};
}

Pion AlphaBetaIA::jouer(Etat plateau) {
    // Initialisation
    m_arbre = Noeud<PV>::creer({0, {0, 0, VIDE}});
    m_couleur = plateau.joueur;

    // Algo !
    MinMaxIA::PV p = alphabeta(std::move(plateau), 0,
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max(),
        (m_prof > 7) ? nullptr : m_arbre
    );
    
    if (m_prof > 7) {
    	m_arbre = nullptr;
    } else {
	    m_arbre->val().val  = p.val;
    	m_arbre->val().pion = p.pion;
    }
    
    return p.pion;
}
