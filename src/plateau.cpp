#include "etat.h"
#include "console.h"
#include "plateau.h"

#ifndef __gnu_linux__
static const std::string LIGNE_HAUT = "\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf";
static const std::string LIGNE_MIL1 = "\xb3       \xb3       \xb3       \xb3       \xb3       \xb3       \xb3       \xb3       \xb3";
static const std::string LIGNE_MIL2 = "\xc3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4";
static const std::string LIGNE_BAS  = "\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9";
#define OFFSET 0
#else
static const std::string LIGNE_HAUT = "\xe2\x95\xad\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x95\xae";
static const std::string LIGNE_MIL1 = "\xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82       \xe2\x94\x82";
static const std::string LIGNE_MIL2 = "\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xa4";
static const std::string LIGNE_BAS  = "\xe2\x95\xb0\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x95\xaf";
#define OFFSET 1
#endif

// Variables statiques
//Console Tableau::s_console;

Tableau::Tableau() {
    // pour mettre a la bonne taille
/*    Plateau.resize(TailleTab);
    for( int i=0; i< TailleTab; i++)
    {
        Plateau[i].resize(TailleTab);
    }

    //parcours du plateau et rendre tout vide et avec bon coordonn�s
    for ( int i=0; i<TailleTab; i++)
    {
        for(int j=0; j<TailleTab; j++)
        {
            //mise des coordonn�es
            Plateau[i][j].x=i;
            Plateau[i][j].y=j;

            //et de la couleur
            Plateau[i][j].couleur=VIDE;
        }
    }

    // mise des 4 pions au milieu
    Plateau[3][4].couleur=NOIR;
    Plateau[4][3].couleur=NOIR;
    Plateau[3][3].couleur=BLANC;
    Plateau[4][4].couleur=BLANC;*/

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
            // Les 4 coins
            s_console->setColor(COLOR_DEFAULT, COLOR_GREEN);
            s_console->gotoLigCol(4+OFFSET+4*j,4+8*i);
            std::cout << "       ";
            s_console->gotoLigCol(5+OFFSET+4*j,4+8*i);
            std::cout << "       ";
            s_console->gotoLigCol(6+OFFSET+4*j,4+8*i);
            std::cout << "       ";

            switch (m_etat.othellier[i][j]) {
            case VIDE:
                s_console->setColor(COLOR_DEFAULT, COLOR_GREEN);
                //remetcouleur � O
                break;

            case BLANC:
                s_console->setColor(COLOR_DEFAULT, COLOR_WHITE);
                break;

            case NOIR:
                s_console->setColor(COLOR_DEFAULT, COLOR_BLACK);
                break;
            }

            // Retour couleur de d�part
            s_console->gotoLigCol(4+OFFSET+4*j,5+8*i);
            std::cout << "     ";
            s_console->gotoLigCol(5+OFFSET+4*j,4+8*i);
            std::cout << "       ";
            s_console->gotoLigCol(6+OFFSET+4*j,5+8*i);
            std::cout << "     ";
            s_console->setColor(COLOR_DEFAULT, COLOR_DEFAULT);
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

            std::cout << " " << l << " " << LIGNE_MIL1 << " " << l << std::endl;
        }

        if (i != 7) {
            std::cout << "   " << LIGNE_MIL2 << std::endl;
        }

    }

    std::cout << "   " << LIGNE_BAS << std::endl;
    std::cout << "       A       B       C       D       E       F       G       H" << std::endl;

    AfficherTab();
}

bool Tableau::Jouer(int &x, int&y) {
    //declaration des variables
    bool onContinue = true, quitter = false;
    int  c;
    //int x=0,y=0;

    //boucle tant que on a pas appuyer sur entrer (pour entrer un pion)
    while (onContinue) {
        // D�placement du curseur
        s_console->gotoLigCol(5+OFFSET+4*y,7+8*x);

        c = s_console->getch();

        switch(c) {
        case 'z':
            y--;
            break;

        case 'q':
            x--;
            break;

        case 's':
            y++;
            break;

        case 'd':
            x++;
            break;

        case 'e':
            quitter = true;
            onContinue = false;
            break;

        case 13:
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

void Tableau::BoucleJeu() {
    bool continuer=true;
    int x=0;
    int y=0;

    while (continuer) {
    	// Affichage
        CreationTab();

        // Interaction
        continuer = Jouer(x, y); // consequences , on envoi x y
    }
}


