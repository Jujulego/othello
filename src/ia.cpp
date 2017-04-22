// Importations
#include <functional>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

#include "pion.h"
#include "etat.h"
#include "ia.h"
#include "console.h"

// Fonctions
static bool cc(Pion const& c1, Pion const& c2) {
    return ((c1.x + c1.y * 10) < (c2.x + c2.y * 10));
}

// Méthodes
std::set<Pion,bool(&)(Pion const&,Pion const&)> IA::get_coups(Etat const& plateau) const {
    // Déclaration du set
    std::set<Pion,bool(&)(Pion const&,Pion const&)> coups(cc);

    // Analyse du plateau
    COULEUR ennemi = (plateau.joueur == BLANC) ? NOIR : BLANC;

    for (Pion p : plateau.pions(plateau.joueur)) {
        // Recherche de coups possibles
        for (auto d : DIRECTIONS) {
            // Init recherche
            int i = p.x, j = p.y;
            d(i, j); // On se déplace 1 fois

            // Recherche
            bool e = false, v = false; // v => vide, e => ennemi
            for (; (i < 8) && (j < 8) && (i >= 0) && (j >= 0); d(i, j)) {
                if (plateau.othellier[i][j] == ennemi) {
                    e = true;
                } else {
                    v = (plateau.othellier[i][j] == VIDE);
                    break;
                }
            }

            // Confirmation
            if (e && v) coups.insert({i,j,plateau.joueur});
        }
    }

    //std::cout << "coups : " << coups.size() << std::endl;
    return coups;
}

std::shared_ptr<Noeud<IA::PV>> IA::arbre() const {
    return m_arbre;
}

void IA::aff_arbre(Console* s_console, std::shared_ptr<Noeud<PV>> noeud, int num_coup) {
    // On clear la console
    s_console->clear();

    s_console->gotoLigCol(2, 2);
    std::cout << "Coups";
    s_console->gotoLigCol(4, 4);
    std::cout << num_coup;
    s_console->gotoLigCol(8, 4);
    std::cout << num_coup + 1;

    // On affiche le noeud de base
    s_console->gotoLigCol(4, noeud->size() + 9);
    std::cout << "O";
    s_console->gotoLigCol(5, noeud->size() + 9);
    std::cout << "\xb3";
    s_console->gotoLigCol(6, noeud->size() + 9);
    if (noeud->size() == 1) std::cout << "\xb3";
    else std::cout << "\xc1";

    for (unsigned int i = 0; i < noeud->size(); i++) {
        // On affiche chaque fils
        s_console->gotoLigCol(8, (i*2) + 9);
        std::cout << "O";

        s_console->gotoLigCol(7, (i*2) + 9);
        std::cout << "\xc1";
        s_console->gotoLigCol(6, (i*2) + 9);
        if (i <= noeud->size() / 2) {
            std::cout << "\xda";
            s_console->gotoLigCol(6, (i*2) + 10);
            std::cout << "\xc4";
        }
        else if (i >= noeud->size() / 2) {
            std::cout << "\xbf";
            s_console->gotoLigCol(6, (i*2) + 8);
            std::cout << "\xc4";
        }
    }
}

bool IA::gere_arbre(Console* s_console, std::shared_ptr<Noeud<PV>> noeud, int num_coup) {
    // Déclaration des variables


    // On affiche l'arbre
    aff_arbre(s_console, noeud, num_coup);


}


