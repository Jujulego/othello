// Importations
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include "etat.h"
#include "pion.h"

// Structure
struct P { int i, j; };

// Méthodes
std::vector<Pion> Etat::pions(COULEUR c) const {
    // Déclarations
    std::vector<Pion> pions;

    // Parcours !
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (othellier[i][j] == c) {
                pions.push_back({i, j, c});
                if (pions.size() == scores.at(c)) break;
            }
        }

        if (pions.size() == scores.at(c)) break;
    }

    return pions;
}

bool Etat::appliquer_coup(Pion const& p) {
    // Déclarations
    COULEUR ennemi = (joueur == BLANC) ? NOIR : BLANC;
    std::vector<P> tmp;
    bool ok = false, valide = false;

    // Recherches dans les 8 dirs
    for (std::function<void(int&,int&)> f : DIRECTIONS) {
        // Init
        tmp.clear();
        ok = false;

        // Recherche de pions à retourner
        for (int i = p.x, j = p.y; (i < 8) && (j < 8) && (i >= 0) && (j >= 0); f(i, j)) {
            // Première boucle :
            if ((i == p.x) && (j == p.y)) continue;

            // Action :
            if (othellier[i][j] == ennemi) {
                // Sélection ou ...
                tmp.push_back({i, j});
            } else {
                // Confirmation !
                if (othellier[i][j] == joueur) ok = true;
                break;
            }
        }

        // Application des changements
        if (ok && !tmp.empty()) {
            // Ajout du nouveau pion
            othellier[p.x][p.y] = joueur;
            valide = true;

            // Changements de couleur
            for (P pt : tmp) othellier[pt.i][pt.j] = joueur;

            // Maj scores
            scores[joueur] += tmp.size() + 1;
            scores[ennemi] -= tmp.size();
        }
    }

    // Changement de joueur !
    if (valide) joueur = ennemi;

    return valide;
}
