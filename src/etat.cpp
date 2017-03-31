// Importations
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include "etat.h"
#include "pion.h"

// Structure
struct P {
    int i, j;
    COULEUR c;
    std::vector<Pion>::iterator it;
};

// Méthodes
void Etat::appliquer_coup(Pion const& p) {
    if (p.couleur != joueur) std::cout << "Aïe les couleurs ne correspondent pas !" << std::endl;

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
                tmp.push_back({i, j, othellier[i][j],
                    std::find_if(pions[ennemi].begin(), pions[ennemi].end(), [i, j] (Pion const& pe) -> bool {
                        return (pe.x == i) && (pe.y == j);
                    })
                });
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
                pt.it->couleur = joueur;
            }
        }
    }

    // Changement de joueur !
    joueur = ennemi;
}
