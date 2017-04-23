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
#include "macros.h"

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

    for (unsigned int i = 0; i < noeud->size(); i++) {
        // On affiche chaque fils
        s_console->gotoLigCol(8, (i*2) + 9);
        std::cout << "O";

        s_console->gotoLigCol(7, (i*2) + 9);
        std::cout << ANGLE_HDG;
        s_console->gotoLigCol(6, (i*2) + 9);
        if (i < noeud->size() / 2) {
            std::cout << ANGLE_BD;
            s_console->gotoLigCol(6, (i*2) + 10);
            std::cout << BARRE_HORI;
        }
        else if (i >= noeud->size() / 2) {
            std::cout << ANGLE_BG;
            s_console->gotoLigCol(6, (i*2) + 8);
            std::cout << BARRE_HORI;
        }
    }

    // On affiche le noeud de base
    s_console->gotoLigCol(4, noeud->size() + 9);
    std::cout << "O";
    s_console->gotoLigCol(5, noeud->size() + 9);
    std::cout << BARRE_VERT;
    s_console->gotoLigCol(6, noeud->size() + 9);
<<<<<<< HEAD
    if (noeud->size() == 1) std::cout << "\xb3";
    else std::cout << "\xc1";

    // On affiche les consignes de touche
    s_console->gotoLigCol(12, 9);
    std::cout << "R : remonter au dernier père";
    s_console->gotoLigCol(13, 9);
    std::cout << "P : revenir au plateau";
    s_console->gotoLigCol(14, 9);
    std::cout << "ENTRER (sur un fils) : descendre dans la branche";
=======
    if (noeud->size() == 1) std::cout << BARRE_VERT;
    else std::cout << ANGLE_HDG;
>>>>>>> a9b99ae91f9ebc2e2d59c2e4e8d3c24ceedaf2e9
}

bool IA::gere_arbre(Console* s_console, std::shared_ptr<Noeud<PV>> noeud, int num_coup) {
    // Déclaration des variables
    int x = noeud->size() + 9;
    int y = 4;
    int c;
    bool cont = true;
    bool quitter = false;

    // On affiche l'arbre
    aff_arbre(s_console, noeud, num_coup);

    // On se place sur le noeud de base
    s_console->gotoLigCol(y, x);

    while (cont) {
        c = s_console->getch();

        switch (c)
        {
            case 'z':
            case FL_HAUT:
                if (y == 8) {
                    y = 4;
                    x = noeud->size() + 9;
                    s_console->gotoLigCol(y, x);
                }

                break;

            case 's':
            case FL_BAS:
                if (y == 4) {
                    y = 8;
                    x = 9;
                    s_console->gotoLigCol(y, x);
                }

                break;

            case 'q':
            case FL_GAUCHE:
                if (y == 8) {
                    if (x > 9) {
                        x -= 2;
                        s_console->gotoLigCol(y, x);
                    }
                }

                break;

            case 'd':
            case FL_DROITE:
                if (y == 8) {
                    if (x < (noeud->size() - 1)*2 + 9) {
                        x += 2;
                        s_console->gotoLigCol(y, x);
                    }
                }

                break;

            case ENTREE:
                if (num_coup < 4) {
                    if (y == 8) {
                            quitter = gere_arbre(s_console, noeud->fils((x - 9) / 2), num_coup + 1);
                        if (quitter) cont = false;
                        aff_arbre(s_console, noeud, num_coup);
                        s_console->gotoLigCol(4, noeud->size() + 9);
                    }
                }
                else {
                    s_console->gotoLigCol(10, 9);
                    std::cout << "Vous etes deja en bas de l'arbre !";
                }

                break;

            case 'r':
                if (num_coup > 0) {
                    return quitter;
                }
                else {
                    s_console->gotoLigCol(10, 9);
                    std::cout << "Vous ne pouvez pas remonter plus haut !";
                }

                break;

            case 'p':
                quitter = true;
                return quitter;
                break;
        }
    }

    return quitter;
}


