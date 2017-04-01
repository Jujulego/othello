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
void Etat::appliquer_coup(Pion const& p) {
    // Déclarations
    COULEUR ennemi = (joueur == BLANC) ? NOIR : BLANC;
    std::vector<P> tmp;
    bool ok;

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
        if (ok) {
            // Ajout du nouveau pion
            pions[joueur].push_back(p);
            othellier[p.x][p.y] = joueur;

            // Changements de couleur
            for (P pt : tmp) {
                othellier[pt.i][pt.j] = joueur;
                pions[joueur].push_back({pt.i, pt.j, joueur});
                pions[ennemi].erase(std::find_if(pions[ennemi].begin(), pions[ennemi].end(), [pt] (Pion const& pe) -> bool {
                    return (pe.x == pt.i) && (pe.y == pt.j);
                }));
            }
        }
    }

    // Changement de joueur !
    joueur = ennemi;
}
