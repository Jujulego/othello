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
#include "menu.h"

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

    return coups;
}

std::shared_ptr<Noeud<IA::PV>> IA::arbre() const {
    return m_arbre;
}

void IA::aff_arbre(Console* s_console, std::shared_ptr<Noeud<PV>> noeud, int num_coup) {
    // Entete !
    Menu::entete();

	// Noeud père
    s_console->gotoLigCol(10, 2);
    std::cout << "Coups :";
    s_console->gotoLigCol(12, 4);
    std::cout << num_coup;
    s_console->gotoLigCol(16, 4);
    std::cout << num_coup + 1;

    for (unsigned int i = 0; i < noeud->size(); i++) {
        // On affiche chaque fils
        if (noeud->size() != 1) {
	        s_console->gotoLigCol(16, (i*3) + 9);
		    std::cout << (char) (noeud->fils(i)->val().pion.x + 'A') << (char) (noeud->fils(i)->val().pion.y + '1');
			
	        s_console->gotoLigCol(15, (i*3) + 9);
    	    std::cout << ANGLE_HDG;
        	
	        s_console->gotoLigCol(14, (i*3) + 9);
  		    if (i == 0) {
       		    std::cout << ANGLE_BD;
           		s_console->gotoLigCol(14, (i*3) + 10);
	        } else if (i == (noeud->size() -1)) {
   		        std::cout << ANGLE_BG;
       		    s_console->gotoLigCol(14, (i*3) + 7);
	        } else {
   		        std::cout << ANGLE_BDG;
       		    s_console->gotoLigCol(14, (i*3) + 7);
        	}
	    	
	        std::cout << BARRE_HORI;
    	    std::cout << BARRE_HORI;
        } else {
	        s_console->gotoLigCol(16, (i*3) + 10);
		    std::cout << (char) (noeud->fils(i)->val().pion.x + 'A') << (char) (noeud->fils(i)->val().pion.y + '1');
			
	        s_console->gotoLigCol(15, (i*3) + 10);
    	    std::cout << ANGLE_HDG;
        }
    }

    // On affiche le noeud de base
    s_console->gotoLigCol(12, noeud->size() + 9);
    std::cout << (char) (noeud->val().pion.x + 'A') << (char) (noeud->val().pion.y + '1');

    s_console->gotoLigCol(13, noeud->size() + 9);
    std::cout << BARRE_VERT;

    s_console->gotoLigCol(14, noeud->size() + 9);
    if (noeud->size() == 1) {
    	std::cout << BARRE_VERT;
    } else if (noeud->size() == 0) {
    	std::cout << BARRE_VERT;

	    s_console->gotoLigCol(15, noeud->size() + 9);
    	std::cout << ANGLE_HDG;
    } else if ((noeud->size() % 3) == 0) {
    	std::cout << INTERSECT;
    } else {
    	std::cout << ANGLE_HDG;
    }

    // On affiche les consignes de touche
    s_console->gotoLigCol(23, 0);
    std::cout << "R : remonter au dernier pere";

    s_console->gotoLigCol(24, 0);
    std::cout << "E : revenir au plateau";
    s_console->gotoLigCol(25, 0);
    std::cout << "ENTRER (sur un fils) : descendre dans la branche";

    std::cout.flush();
}

void IA::dess_plat(Console* s_console, int x, int y, Pion pion, Etat etat, int val) {
    // On applique le coup à l'othellier
    etat.appliquer_coup(pion);

    // Affichage du plateau
    s_console->gotoLigCol(y, x);
    std::cout << "  A B C D E F G H";
    for (int i = 0; i < 8; i++) {
        s_console->gotoLigCol(y + i + 1, x);
        std::cout << i + 1 << ' ';

        for (int j = 0; j < 8; j++) {
            if (etat.othellier[j][i] == VIDE) {
            	s_console->setColor(COLOR_BLACK, COLOR_GREEN);
            } else if (etat.othellier[j][i] == BLANC) {
            	s_console->setColor(COLOR_RED, COLOR_WHITE);
            } else if (etat.othellier[j][i] == NOIR) {
            	s_console->setColor(COLOR_RED, COLOR_BLACK);
            }

            if ((pion.x == j) && (pion.y == i)) {
	           	std::cout << "<>";
            } else {
	           	std::cout << "  ";
	        }
        }
        s_console->setColor();

        std::cout << i + 1;
    }

    s_console->gotoLigCol(y + 9, x);
    std::cout << "  A B C D E F G H";

    // On affiche la valeur du coup
    s_console->gotoLigCol(y + 11, x);
    std::cout << "Valeur du coup : " << val << "        ";
}

bool IA::gere_arbre(Console* s_console, std::shared_ptr<Noeud<PV>> noeud, int num_coup, Etat etat) {
    // Déclaration des variables
    unsigned x = noeud->size() + 9;
    unsigned y = 12;
    int c;
    bool cont = true;
    bool quitter = false;

    // On applique le coup à l'othellier
	if (num_coup != 0) etat.appliquer_coup(noeud->val().pion);

    // On affiche l'arbre
    aff_arbre(s_console, noeud, num_coup);

    // On dessine le plateau
    dess_plat(s_console,
    	MAX(noeud->size()*3 + 15, 30),
    	10,
    	noeud->val().pion,
    	etat,
    	noeud->val().val
    );

    // On se place sur le noeud de base
    while (cont) {
    	// Récup
	    s_console->gotoLigCol(y, x);
        c = s_console->getch();

		// Suppression des messages d'erreurs
        s_console->gotoLigCol(26, 9);
        std::cout << "                                       ";

        // Intéractions
        switch (c) {
            case 'z':
            case FL_HAUT:
                if (y == 16) {
                    y = 12;
                    x = noeud->size() + 9;
                } else if (y == 12) {
                    return quitter;
                }

                break;

            case 's':
            case FL_BAS:
                if ((y == 12) && (noeud->size())) {
                    y = 16;
                    x = 9;
                }

                break;

            case 'q':
            case FL_GAUCHE:
                if (y == 16) {
                    if (x > 9) {
                        x -= 3;
                    }
                }

                break;

            case 'd':
            case FL_DROITE:
                if (y == 16) {
                    if (x < (noeud->size() - 1)*3 + 9) {
                        x += 3;
                    }
                }

                break;

            case ENTREE:
                if (noeud->size()) {
                    if (y == 16) {
                        quitter = gere_arbre(s_console, noeud->fils((x - 9) / 3), num_coup + 1, etat);
                        if (quitter) cont = false;
                        aff_arbre(s_console, noeud, num_coup);
                    } else if (num_coup > 0) {
                    	return quitter;
                    }
                }

                break;

            case 'r':
                if (num_coup > 0) {
                    return quitter;
                } else {
                	s_console->setColor(COLOR_YELLOW);
                    s_console->gotoLigCol(27, 9);
                    std::cout << "Vous ne pouvez pas remonter plus haut !";
                	s_console->setColor();
                }

                break;

            case 'e':
                quitter = true;
                return quitter;
                break;
        }

        // On affiche le plateau
        if (y == 12) {
        	dess_plat(s_console,
        		MAX(noeud->size()*3 + 15, 30),
        		10,
        		noeud->val().pion,
        		etat,
        		noeud->val().val
        	);
        } else if (y == 16) {
        	dess_plat(s_console,
        		MAX(noeud->size()*3 + 15, 30),
        		10,
        		noeud->fils((x - 9) / 3)->val().pion,
        		etat,
        		noeud->fils((x - 9) / 3)->val().val
        	);
        }
    }

    return quitter;
}
