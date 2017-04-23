// Importations
#include <limits>
#include <iostream>
#include <string>

#include "negamaxia.h"

// Constructeur
NegaMaxIA::NegaMaxIA(unsigned prof, COULEUR c) : AlphaBetaIA(prof, c) {
}

// Méthodes
std::string NegaMaxIA::id() const {
	return "negamax";
}

MinMaxIA::PV NegaMaxIA::alphabeta(Etat&& etat, unsigned prof, int alpha, int beta, std::shared_ptr<Noeud<MinMaxIA::PV>> noeud) {
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
    	return {val, {0, 0, VIDE}};
    }

    // Initialisation
    val = std::numeric_limits<decltype(val)>::min(); // -infini !

    // Parcours des coups
    for (auto c : coups) {
        // Application du coup
        Etat e(etat);
        e.appliquer_coup(c);

        // AlphaBeta sur l'enfant
        PV pv;
        if (noeud)
        	pv = alphabeta(std::move(e), prof+1, -beta, -alpha, noeud->add_fils({0, c}));
        else
        	pv = alphabeta(std::move(e), prof+1, -beta, -alpha, nullptr);
        
        int v = -pv.val;

        // NegaMax :
        if (v > val) {
            val = v;
            pion = c;

            if (val > alpha) {
                alpha = val;

                if (alpha >= beta) {
                    break;
                }
            }
        }
    }

    // Résultat
    if (noeud) {
    	noeud->val().val = val;
    }
    
    return {val, pion};
}
