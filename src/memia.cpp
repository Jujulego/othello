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
MemIA::MemIA(std::string const& fichier) : MinMaxIA(1), m_memarbre(std::make_shared<MemArbre>(fichier)) {
    m_memarbre->charger();
}

// Méthodes
Pion MemIA::jouer(Etat plateau) {
    // Récupération des coups connus
    std::set<std::shared_ptr<MemArbre::Noeud>> coups_connus((m_noeud == nullptr) ? m_memarbre->racines() : m_noeud->fils());
    std::shared_ptr<MemArbre::Noeud> noeud = nullptr, np;

    // Calcul des coups possibles
    std::set<Pion,bool(&)(Pion const&,Pion const&)> coups_possibles = get_coups(plateau);
    int val = std::numeric_limits<int>::min(), v;
    Pion pion;

    std::cout << "nb : " << coups_connus.size() << std::endl;

    // Intersection
    for (Pion p : coups_possibles) {
        // Calcul du prochain etat
        Etat etat(plateau);
        etat.appliquer_coup(p);

        // Recherche d'un noeud correspondant
        np = nullptr;

        for (std::shared_ptr<MemArbre::Noeud> n : coups_connus) {
            if ((p.x == std::get<0>(n->coords())) && (p.y == std::get<1>(n->coords()))) {
                np = n;
                break;
            }
        }

        // Calcul de la valeur
        v = heuristique(std::move(etat)) * ((np == nullptr) ? 1 : np->val());
        std::cout << v << std::endl;

        if (v > val) {
            val = v;
            pion = p;
            noeud = np;
        }
    }

    // Création d'un nouveau noeud
    if (noeud == nullptr) {
        if (m_noeud == nullptr) {
            noeud = m_memarbre->add_racine(0, std::make_tuple(pion.x, pion.y));
        } else {
            noeud = m_noeud->add_fils(0, std::make_tuple(pion.x, pion.y));
        }
    }

    // Résultat !
    m_noeud = noeud;
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
