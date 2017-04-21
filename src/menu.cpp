// Importations
#include <iostream>
#include <memory>

#include "alphabetaia.h"
#include "ia.h"
#include "minmaxia.h"
#include "memia.h"
#include "menu.h"
#include "negamaxia.h"
#include "randomia.h"

// Macros
#define PROF_ALGO 5

#ifndef __gnu_linux__
#define ENTREE  13
#define FL_HAUT 57416
#define FL_BAS  57424
#else
#define ENTREE  10
#define FL_HAUT 1792833
#define FL_BAS  1792834
#endif

// Attributs statiques
Console Menu::s_console;

// Constructeur
Menu::Menu() :
		m_memia_noire(std::make_shared<MemIA>("arbre_noir.txt", PROF_ALGO, NOIR)),
		m_memia_blanche(std::make_shared<MemIA>("arbre_blanc.txt", PROF_ALGO, BLANC)) {
}

// Méthodes
void Menu::afficher() const {
	// Déclarations
	bool quitter = false;
	int choix = 0;
	Tableau tab;
	COULEUR v;
	
	// Choix :
	do {
		// Affichage entête
		s_console.clear();
		s_console.gotoLigCol(2, 0);
		std::cout << "            ____       __    __             __  __     " << std::endl;
		std::cout << "           / __ \\   __/ /_  / /            / / / /     " << std::endl;
		std::cout << "          / /  \\ \\ /_  __/ / /_    ___    / / / / ___  " << std::endl;
		std::cout << "         / /   / /  / /   / __ \\  / _ \\  / / / / / _ \\ " << std::endl;
		std::cout << "         \\ \\__/ /  / /   / / / / /  __/ / / / / / // / " << std::endl;
		std::cout << "          \\____/  /_/   /_/ /_/  \\___/ /_/ /_/  \\___/  " << std::endl;
		
		// Affichage des options
		s_console.gotoLigCol(10, 15);
		if (choix == 0) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		
		std::cout << "- Joueur vs Joueur";
		
		s_console.gotoLigCol(11, 15);
		if (choix == 1) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		
		std::cout << "- Joueur vs Random";
		
		s_console.gotoLigCol(12, 15);
		if (choix == 2) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		
		std::cout << "- Joueur vs MinMax";
		
		s_console.gotoLigCol(13, 15);
		if (choix == 3) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		
		std::cout << "- Joueur vs AlphaBeta";
		
		s_console.gotoLigCol(14, 15);
		if (choix == 4) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		
		std::cout << "- Joueur vs NegaMax";
		
		s_console.gotoLigCol(15, 15);
		if (choix == 5) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		
		std::cout << "- Joueur vs Memory";
		
		s_console.gotoLigCol(16, 15);
		if (choix == 6) s_console.setColor(COLOR_RED, COLOR_WHITE);
		else            s_console.setColor(COLOR_RED);
		
		std::cout << "- Quitter";
		
		s_console.setColor();
		
		// Interactions
        int c = s_console.getch();
        
        switch (c) {
	    case 'z':
    	case FL_HAUT:
        	choix--;
        	break;
		
        case 's':
	    case FL_BAS:
    	    choix++;
        	break;
        
        case ENTREE:
        	switch (choix) {
        	case 0:
        		tab = Tableau();
        		tab.BoucleJeu();
        		
        		break;
        	
        	case 1:
        		tab = Tableau(nullptr, std::make_shared<RandomIA>());
        		tab.BoucleJeu();
        		
        		break;
        	
        	case 2:
        		tab = Tableau(nullptr, std::make_shared<MinMaxIA>(PROF_ALGO, BLANC));
        		tab.BoucleJeu();
        		
        		break;
        	
        	case 3:
        		tab = Tableau(nullptr, std::make_shared<AlphaBetaIA>(PROF_ALGO, BLANC));
        		tab.BoucleJeu();
        		
        		break;
        	
        	case 4:
        		tab = Tableau(nullptr, std::make_shared<NegaMaxIA>(PROF_ALGO, BLANC));
        		tab.BoucleJeu();
        		
        		break;
        	
        	case 5:
        		tab = Tableau(nullptr, m_memia_blanche);
        		v = tab.BoucleJeu();
        		
        		if (v == BLANC) m_memia_blanche->gagne();
        		else m_memia_blanche->perdu();
        		
        		break;
        	
        	case 6:
        		quitter = true;
        		break;
        	}
        	break;
        }
        
        // Controle des bords
        if (choix < 0) choix = 0;
        if (choix > 6) choix = 6;
	} while (!quitter);
	
	s_console.gotoLigCol(20, 0);
}
