// Importations
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "macros.h"
#include "minmaxia.h"
#include "memarbre.h"
#include "memia.h"

// Macros
#define VAL_MAX 2
#define VAL_MIN -2

// Constructeur
MemIA::MemIA(std::string const& fichier, unsigned prof, COULEUR c) : AlphaBetaIA(prof, c), m_memarbre(std::make_shared<MemArbre>(fichier)) {
    m_memarbre->charger();
}

// Méthodes
std::string MemIA::id() const {
	if (m_noeud == nullptr)
		return "memia -1";

	return "memia " + std::to_string(m_noeud->pos());
}

MinMaxIA::PV MemIA::memia(Etat&& etat, unsigned prof, int alpha, int beta, std::shared_ptr<MemArbre::Noeud> memnoeud, std::shared_ptr<Noeud<MinMaxIA::PV>> noeud) {
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

    // Récupération des coups connus
    std::set<std::shared_ptr<MemArbre::Noeud>> coups_connus;
    std::shared_ptr<MemArbre::Noeud> np;

    // Seulment les coups de l'IA sont enregistrés
    if ((prof % 2) == 0) {
        coups_connus = (memnoeud == nullptr) ? m_memarbre->racines() : memnoeud->fils();
    }

    // Initialisation
    if (prof % 2) {
        val = std::numeric_limits<decltype(val)>::max(); // +infini !
    } else {
        val = std::numeric_limits<decltype(val)>::min(); // -infini !
    }

    // Parcours des coups
    for (auto c : coups) {
        // Application du coup
        Etat e(etat);
        e.appliquer_coup(c);

        // Recherche d'un noeud correspondant dans la mémoire
        if ((prof % 2) == 0) {
            np = nullptr;
            for (std::shared_ptr<MemArbre::Noeud> n : coups_connus) {
                if ((c.x == std::get<0>(n->coords())) && (c.y == std::get<1>(n->coords()))) {
                    np = n;
                    break;
                }
            }
        } else {
            np = memnoeud;
        }

        // AlphaBeta sur l'enfant
        PV pv;
        int v;
        if (np != nullptr) {
    	    if (noeud)
    	        pv = memia(std::move(e), prof+1, beta, alpha, np, noeud->add_fils({0, c}));
    	    else
	            pv = memia(std::move(e), prof+1, beta, alpha, np, nullptr);
            v = pv.val;

            if (np->val() < 0) {
                v *= ((v < 0) ? -1 : 1) * np->val();
            } else {
                v *= ((v < 0) ? 1 : -1) * np->val();
            }
        } else {
	        if (noeud)
	            pv = alphabeta(std::move(e), prof+1, beta, alpha, noeud->add_fils({0, c}));
	        else
	            pv = alphabeta(std::move(e), prof+1, beta, alpha, nullptr);
            v = val;
        }

        if (prof % 2) { // Min
            if (v < val) {
                pion = c;
                val = v;
            }

            // Coupure alpha
            if (v <= alpha) break;
            if (v < beta) beta = v;

        } else { // Max
            if (v > val) {
                pion = c;
                val = v;
            }

            // Coupure beta
            if (v >= beta) break;
            if (v > alpha) alpha = v;
        }
    }

    // Résultat
    if (noeud) {
    	noeud->val().val = val;
    }
    
    return {val, pion};
}

Pion MemIA::jouer(Etat plateau) {
    // Initialisation
    m_arbre = Noeud<PV>::creer({0, {0, 0, VIDE}});
    m_couleur = plateau.joueur;

    // Algo !
    Pion pion = memia(std::move(plateau), 0,
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max(),
        m_noeud,
        (m_prof > 10) ? nullptr : m_arbre
    ).pion;
    
    if (m_prof > 10) {
    	m_arbre = nullptr;
    } else {
	    m_arbre->val().pion = pion;
	}

    // Création d'un nouveau noeud si inexistant
    std::set<std::shared_ptr<MemArbre::Noeud>> coups_connus((m_noeud == nullptr) ? m_memarbre->racines() : m_noeud->fils());
    bool existe = false;

    // Recherche du noeud correspondant
    for (std::shared_ptr<MemArbre::Noeud> n : coups_connus) {
        if ((pion.x == std::get<0>(n->coords())) && (pion.y == std::get<1>(n->coords()))) {
            m_noeud = n;
            existe = true;
            break;
        }
    }

    // Création du noeud
    if (!existe) {
        if (m_noeud == nullptr) {
            m_noeud = m_memarbre->add_racine(0, std::make_tuple(pion.x, pion.y));
        } else {
            m_noeud = m_noeud->add_fils(0, std::make_tuple(pion.x, pion.y));
        }
    }

    return pion;
}

void MemIA::gagne() {
    // Incrémentation de la valeur du noeud
    m_noeud->val(MIN(m_noeud->val() + 1, VAL_MAX));
    m_noeud->save();

    m_noeud = nullptr;
}

void MemIA::perdu() {
    // décrémentation de la valeur du noeud
    m_noeud->val(MAX(m_noeud->val() - 1, VAL_MIN));
    m_noeud->save();

    m_noeud = nullptr;
}

void MemIA::set_prof(unsigned prof) {
	m_prof = prof;
}

void MemIA::set_noeud(int pos) {
	if (pos != -1) {
		m_noeud = m_memarbre->noeud(pos);
	}
}
