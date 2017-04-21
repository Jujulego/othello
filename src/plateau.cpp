#include <map>
#include <memory>

#include "etat.h"
#include "console.h"
#include "plateau.h"

#ifndef __gnu_linux__
static const std::string LIGNE_HAUT = "\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf";
static const std::string LIGNE_MIL1 = "\xb3       \xb3       \xb3       \xb3       \xb3       \xb3       \xb3       \xb3       \xb3";
static const std::string LIGNE_MIL2 = "\xc3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4";
static const std::string LIGNE_BAS  = "\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9";
#define OFFSET 1
#define ENTREE 13
#define FL_DROITE 57421
#define FL_GAUCHE 57419
#define FL_HAUT   57416
#define FL_BAS    57424
#else
static const std::string LIGNE_HAUT = "\xe2\x95\xad\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x95\xae";
static const std::string LIGNE_MIL1 = "\xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82";
static const std::string LIGNE_MIL2 = "\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xa4";
static const std::string LIGNE_BAS  = "\xe2\x95\xb0\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x95\xaf";
#define OFFSET 1
#define ENTREE 10
#define FL_DROITE 1792835
#define FL_GAUCHE 1792836
#define FL_HAUT   1792833
#define FL_BAS    1792834
#endif

Tableau::Tableau(std::shared_ptr<IA> ia_noir, std::shared_ptr<IA> ia_blanc) {
    // Init joueur
    m_ias[NOIR]  = ia_noir;
    m_ias[BLANC] = ia_blanc;

    // Init etat
    m_etat.joueur = NOIR;    // tjs le noir qui commence
    m_etat.scores[NOIR]  = 2; // = au nb de pions du joueur
    m_etat.scores[BLANC] = 2;

    // Init plateau
    m_etat.othellier = std::vector<std::vector<COULEUR>>(TailleTab, std::vector<COULEUR>(TailleTab, VIDE));
    m_etat.othellier[3][4] = NOIR;
    m_etat.othellier[4][3] = NOIR;
    m_etat.othellier[3][3] = BLANC;
    m_etat.othellier[4][4] = BLANC;
}

void Tableau::AfficherTab() {
    for (int i=0;i < TailleTab; i++) {
        for (int j=0; j < TailleTab; j++) {
            // Rien à faire pour le cases vides
            if (m_etat.othellier[i][j] == VIDE) {
                continue;
            }
            
            // Choix de la couleur
            switch (m_etat.othellier[i][j]) {
            case BLANC:
                s_console->setColor(COLOR_DEFAULT, COLOR_WHITE);
                break;

            case NOIR:
                s_console->setColor(COLOR_DEFAULT, COLOR_BLACK);
                break;
            }

            // Affichage du pion
            s_console->gotoLigCol(4+OFFSET+4*j,5+8*i);
            std::cout <<  "     ";
            s_console->gotoLigCol(5+OFFSET+4*j,4+8*i);
            std::cout << "       ";
            s_console->gotoLigCol(6+OFFSET+4*j,5+8*i);
            std::cout <<  "     ";
            s_console->setColor();
        }
    }
}

void Tableau::CreationTab() {
    // Affichage du plateau
    s_console->clear();
    s_console->gotoLigCol(3, 0);
    char l;

    std::cout << "       A       B       C       D       E       F       G       H" << std::endl;
    std::cout << "   " << LIGNE_HAUT << std::endl;

    for (int i = 0; i < TailleTab; i++) {
        for (int j = 0; j < 3; j++) {
            l = ' ';

            if (j % 2) {
                l = '1' + i;
            }

            s_console->gotoLigCol(i*4+5+j, 0);
            std::cout << " " << l << " " << LIGNE_MIL1 << " " << l;
            
            s_console->setColor(COLOR_DEFAULT, COLOR_GREEN);
            for (int c = 0; c < 8; c++) {
            	s_console->gotoLigCol(i*4+5+j, 4+8*c);
            	std::cout << "       ";
            }
            
            s_console->setColor();
        }

        if (i != 7) {
            s_console->gotoLigCol(i*4+8, 0);
            std::cout << "   " << LIGNE_MIL2;
        }

    }

    s_console->gotoLigCol(36, 0);
    std::cout << "   " << LIGNE_BAS << std::endl;
    std::cout << "       A       B       C       D       E       F       G       H" << std::endl;

    AfficherTab();
}

bool Tableau::Jouer(int &x, int&y) {
    // declaration des variables
    bool onContinue = true, quitter = false;
    int  c;

    // boucle tant que on a pas appuyer sur entrer (pour entrer un pion)
    while (onContinue) {
        // D�placement du curseur
        s_console->gotoLigCol(5+OFFSET+4*y, 7+8*x);

        c = s_console->getch();

        switch(c) {
        case 'z':
        case FL_HAUT:
            y--;
            break;

        case 'q':
        case FL_GAUCHE:
            x--;
            break;

        case 's':
        case FL_BAS:
            y++;
            break;

        case 'd':
        case FL_DROITE:
            x++;
            break;

        case 'e':
            quitter = true;
            onContinue = false;
            break;

        case ENTREE:
            if (m_etat.othellier[x][y] == VIDE) {
                // Renvoie vrai si le coup est valide et change le joueur
                onContinue = !m_etat.appliquer_coup({x, y, m_etat.joueur});
            }

            break;
        }

        // Attention au bords !
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x > 7) x = 7;
        if (y > 7) y = 7;
    }

    return !quitter;
}

COULEUR Tableau::BoucleJeu() {
    bool continuer=true;
    int x=0;
    int y=0;

    // Affichage
    CreationTab();
    
    while (continuer) {
        // Execution de l'IA
        if (m_ias[m_etat.joueur] != nullptr) {
        	m_etat.appliquer_coup(m_ias[m_etat.joueur]->jouer(m_etat));
        } else {
            // Interaction
            continuer = Jouer(x, y); // consequences, on envoi x y
        }
        
        // Test peut pas jouer !
        if (m_etat.coups_restant(m_etat.joueur) == 0) { // Le joueur ne peux pas jouer !
        	// On passe au suivant
        	m_etat.joueur = (m_etat.joueur == NOIR) ? BLANC : NOIR;
        	
        	// Test de fin !
        	if (m_etat.coups_restant(m_etat.joueur) == 0) { // Personne ne peux jouer !
	        	m_etat.joueur = (m_etat.joueur == NOIR) ? BLANC : NOIR;
        		continuer = false;
        	}
        }
        
        // Affichage
        AfficherTab();
    }
    
    s_console->gotoLigCol(40, 0);
    
    if (m_etat.scores[NOIR] > m_etat.scores[BLANC]) {
    	return NOIR;
    } else if (m_etat.scores[BLANC] > m_etat.scores[NOIR]) {
    	return BLANC;
    } else {
    	return m_etat.joueur;
    }
}

std::map<COULEUR,unsigned> const Tableau::scores() const {
	return m_etat.scores;
}
