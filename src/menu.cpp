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
void Menu::entete() const {
	// Affichage entête
	s_console.clear();
	s_console.gotoLigCol(2, 0);
	std::cout << "         ____       __    __             __  __     " << std::endl;
	std::cout << "        / __ \\   __/ /_  / /            / / / /     " << std::endl;
	std::cout << "       / /  \\ \\ /_  __/ / /_    ___    / / / / ___  " << std::endl;
	std::cout << "      / /   / /  / /   / __ \\  / _ \\  / / / / / _ \\ " << std::endl;
	std::cout << "      \\ \\__/ /  / /   / / / / /  __/ / / / / / // / " << std::endl;
	std::cout << "       \\____/  /_/   /_/ /_/  \\___/ /_/ /_/  \\___/  " << std::endl;
	std::cout.flush();
}

void Menu::afficher() const {
	// Déclarations
	bool quitter = false;
	int choix = 0;
	Tableau tab;
	COULEUR v;
	
	// Choix :
	do {
		// Affichage entête
		entete();
		
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
		if (choix == 6) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		
		std::cout << "- Memory vs Memory";
		
		s_console.gotoLigCol(17, 15);
		if (choix == 7) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		
		std::cout << "- Commandes";
		
		s_console.gotoLigCol(18, 15);
		if (choix == 8) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		
		std::cout << "- Charger une sauvegarde";
		
		s_console.gotoLigCol(19, 15);
		if (choix == 9) s_console.setColor(COLOR_RED, COLOR_WHITE);
		else            s_console.setColor(COLOR_RED);
		
		std::cout << "- Quitter";
		
		s_console.setColor();
		
		// Interactions
        switch (s_console.getch()) {
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
        	case 0: // J vs J
        		tab = Tableau();
        		tab.BoucleJeu();
        		
        		break;
        	
        	case 1: // J vs RIA
        		if (choix_coul() == NOIR)
        			tab = Tableau(nullptr, std::make_shared<RandomIA>());
        		else
        			tab = Tableau(std::make_shared<RandomIA>(), nullptr);
        		
        		tab.BoucleJeu();
        		break;
        	
        	case 2: // J vs MM
        		if (choix_coul() == NOIR)
        			tab = Tableau(nullptr, std::make_shared<MinMaxIA>(PROF_ALGO, BLANC));
        		else
        			tab = Tableau(std::make_shared<MinMaxIA>(PROF_ALGO, NOIR), nullptr);
        		
        		tab.BoucleJeu();
        		break;
        	
        	case 3: // J vs AB
        		if (choix_coul() == NOIR)
        			tab = Tableau(nullptr, std::make_shared<AlphaBetaIA>(PROF_ALGO, BLANC));
        		else
        			tab = Tableau(std::make_shared<AlphaBetaIA>(PROF_ALGO, NOIR), nullptr);
        		
        		tab.BoucleJeu();
        		break;
        	
        	case 4: // J vs NM
        		if (choix_coul() == NOIR)
        			tab = Tableau(nullptr, std::make_shared<NegaMaxIA>(PROF_ALGO, BLANC));
        		else
        			tab = Tableau(std::make_shared<NegaMaxIA>(PROF_ALGO, NOIR), nullptr);
        		
        		tab.BoucleJeu();
        		break;
        	
        	case 5: // J vs MIA
        		if (choix_coul() == NOIR) {
        			tab = Tableau(nullptr, m_memia_blanche);
	        		v = tab.BoucleJeu();
	        		
    	    		if (v == BLANC) m_memia_blanche->gagne();
        			else m_memia_blanche->perdu();
        		} else {
        			tab = Tableau(m_memia_noire, nullptr);
	        		v = tab.BoucleJeu();
	        		
    	    		if (v == NOIR) m_memia_noire->gagne();
        			else m_memia_noire->perdu();
        		}
        		
        		break;
        	
        	case 6: // MIA vs MIA
        		tab = Tableau(m_memia_noire, m_memia_blanche);
        		
        		if (tab.BoucleJeu() == NOIR) {
        			m_memia_noire->gagne();
        			m_memia_blanche->perdu();
        		} else {
        			m_memia_noire->perdu();
        			m_memia_blanche->gagne();
        		}
        		
        		break;
        	
        	case 7: // Commandes
        		regles();
        		break;
        	
        	case 8: // Charger
        		break;
        	
        	case 9: // Quitter
        		quitter = true;
        		break;
        	}
        	break;
        }
        
        // Controle des bords
        if (choix < 0) choix = 0;
        if (choix > 9) choix = 9;
	} while (!quitter);
	
	s_console.gotoLigCol(20, 0);
}

COULEUR Menu::choix_coul() const {
	// Déclarations
	COULEUR coul = NOIR;
	bool quitter = false;
	
	do {
		// Entete
		entete();
		
		// Affichage
		s_console.gotoLigCol(10, 10);
		std::cout << "Quelle couleur veux-tu etre ?";
		
		s_console.gotoLigCol(12, 15);
		if (coul == NOIR) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else              s_console.setColor();
		std::cout << "- Noir";
		
		s_console.gotoLigCol(13, 15);
		if (coul == BLANC) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else               s_console.setColor();
		std::cout << "- Blanc";
		
		s_console.gotoLigCol(15, 10);
		s_console.setColor();
		std::cout << "Appuyes sur [ENTREE] pour valider !";
		std::cout.flush();
		
		// Interactions
		switch (s_console.getch()) {
		case 'z':
		case FL_HAUT:
			if (coul == BLANC) coul = NOIR;
			break;
		
		case 's':
		case FL_BAS:
			if (coul == NOIR) coul = BLANC;
			break;
		
		case ENTREE:
			quitter = true;
			break;
		}
	} while (!quitter);
	
	return coul;
}

void Menu::regles() const {
	// Affichage des options
	entete();
	s_console.gotoLigCol(10, 0);
	std::cout << "    Z       ^" << std::endl;
	std::cout << "  Q S D   < v >     Pour se déplacer sur le plateau" << std::endl;
	std::cout << std::endl;
	std::cout << "             |" << std::endl;
	std::cout << " ENTREE   <--+      Pour placer un pion" << std::endl;
	std::cout << std::endl;
	std::cout << "        E           Pour quitter la partie" << std::endl;
	std::cout << std::endl;
	std::cout << "        F           Pour sauvegarder la partie" << std::endl;
	std::cout << std::endl;
	std::cout << "Appuyez sur [ENTREE]" << std::endl;
	std::cout.flush();
	
	// Attente
	do {} while (s_console.getch() != ENTREE);
}
