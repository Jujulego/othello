// Importations
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "alphabetaia.h"
#include "ia.h"
#include "macros.h"
#include "minmaxia.h"
#include "memia.h"
#include "menu.h"
#include "negamaxia.h"
#include "randomia.h"

// Macros
#define DECAL_MENU1 15
#define DECAL_MENU2 10
#define POS_FIN 25, 0

// Attributs statiques
Console Menu::s_console;

// Méthodes
void Menu::entete() {
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

void Menu::fichier_erreur(std::string const& fichier, std::string const& err) {
	// Affichage (EN ROUGE !!!!)
	s_console.setColor(COLOR_RED);
	s_console.gotoLigCol(17, DECAL_MENU2);
	std::cout << "Erreur lors du chargement de " << fichier << ":";
	
	s_console.gotoLigCol(18, DECAL_MENU2);
	std::cout << err;
	s_console.setColor();
	std::cout.flush();
	
	s_console.gotoLigCol(POS_FIN);
}

int Menu::init() {
	// Affichage
	entete();
	s_console.gotoLigCol(13, DECAL_MENU1);
	std::cout << "Chargement des données ... 0%";
	std::cout.flush();
	
	// Chargement des MemIA (gestion des erreurs)
	try {
		m_memia_noire = std::make_shared<MemIA>(FICHIER_NOIR, m_prof, NOIR);
	} catch (std::out_of_range const& err) {
		fichier_erreur(FICHIER_NOIR, "Le fichier est corrompu !");
		return 1;
	} catch (std::string const& err) {
		fichier_erreur(FICHIER_NOIR, err);
		return 1;
	}
	
	// Evolution pourcentage !
	s_console.gotoLigCol(13, DECAL_MENU1 + 27);
	std::cout << "50%";
	std::cout.flush();
	
	try {
		m_memia_blanche = std::make_shared<MemIA>(FICHIER_BLANC, m_prof, BLANC);
	} catch (std::out_of_range& err) {
		fichier_erreur(FICHIER_BLANC, "Le fichier est corrompu !");
		return 1;
	} catch (std::string const& err) {
		fichier_erreur(FICHIER_BLANC, err);
		return 1;
	}
	
	// Evolution pourcentage !
	s_console.gotoLigCol(13, DECAL_MENU1 + 27);
	std::cout << "Fini !";

	// Attente
	s_console.gotoLigCol(15, DECAL_MENU1);
	std::cout << "Appuyez sur [ENTREE]" << std::endl;
	std::cout.flush();
	
	do {} while (s_console.getch() != ENTREE);
	
	// Execution !
	afficher();
	
	s_console.gotoLigCol(POS_FIN);
	return 0;
}

void Menu::afficher() {
	// Déclarations
	bool quitter = false;
	int choix = 0;
	Tableau tab;
	COULEUR v;

	// Choix :
	do {
   		// Déclarations
   		bool memia_noire = false, memia_blanche = false;

		// Affichage entête
		entete();

		// Affichage des options
		s_console.gotoLigCol(10, DECAL_MENU1);
		if (choix == 0) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Joueur vs Joueur";

		s_console.gotoLigCol(11, DECAL_MENU1);
		if (choix == 1) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Joueur vs Random";

		s_console.gotoLigCol(12, DECAL_MENU1);
		if (choix == 2) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Joueur vs MinMax";

		s_console.gotoLigCol(13, DECAL_MENU1);
		if (choix == 3) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Joueur vs AlphaBeta";

		s_console.gotoLigCol(14, DECAL_MENU1);
		if (choix == 4) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Joueur vs NegaMax";

		s_console.gotoLigCol(15, DECAL_MENU1);
		if (choix == 5) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Joueur vs Memory";

		s_console.gotoLigCol(16, DECAL_MENU1);
		if (choix == 6) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Memory vs Memory";

		s_console.gotoLigCol(17, DECAL_MENU1);
		if (choix == 7) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Commandes";

		s_console.gotoLigCol(18, DECAL_MENU1);
		if (choix == 8) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Charger une sauvegarde";

		s_console.gotoLigCol(19, DECAL_MENU1);
		if (choix == 9) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else            s_console.setColor();
		std::cout << "- Parametres";

		s_console.gotoLigCol(20, DECAL_MENU1);
		if (choix == 10) s_console.setColor(COLOR_RED, COLOR_WHITE);
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
        			tab = Tableau(nullptr, std::make_shared<MinMaxIA>(m_prof, BLANC));
        		else
        			tab = Tableau(std::make_shared<MinMaxIA>(m_prof, NOIR), nullptr);

        		tab.BoucleJeu();
        		break;

        	case 3: // J vs AB
        		if (choix_coul() == NOIR)
        			tab = Tableau(nullptr, std::make_shared<AlphaBetaIA>(m_prof, BLANC));
        		else
        			tab = Tableau(std::make_shared<AlphaBetaIA>(m_prof, NOIR), nullptr);

        		tab.BoucleJeu();
        		break;

        	case 4: // J vs NM
        		if (choix_coul() == NOIR)
        			tab = Tableau(nullptr, std::make_shared<NegaMaxIA>(m_prof, BLANC));
        		else
        			tab = Tableau(std::make_shared<NegaMaxIA>(m_prof, NOIR), nullptr);

        		tab.BoucleJeu();
        		break;

        	case 5: // J vs MIA
        		if (choix_coul() == NOIR) {
        			tab = Tableau(nullptr, m_memia_blanche);
	        		v = tab.BoucleJeu();

        			// getion memias
    	    		if (v == BLANC) m_memia_blanche->gagne();
        			else m_memia_blanche->perdu();
        		} else {
        			tab = Tableau(m_memia_noire, nullptr);
	        		v = tab.BoucleJeu();

        			// getion memias
    	    		if (v == NOIR) m_memia_noire->gagne();
        			else m_memia_noire->perdu();
        		}

        		break;

        	case 6: // MIA vs MIA
        		tab = Tableau(m_memia_noire, m_memia_blanche);

        		// Gestion memia
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
        		if (charger(tab, memia_noire, memia_blanche)) {
        			// On joue !
        			v = tab.BoucleJeu();

        			// getion memias
    	    		if (memia_blanche) {
    	    			if (v == BLANC) m_memia_blanche->gagne();
        				else            m_memia_blanche->perdu();
        			}

    	    		if (memia_noire) {
	    	    		if (v == NOIR) m_memia_noire->gagne();
    	    			else           m_memia_noire->perdu();
    	    		}
        		}

        		break;

        	case 9: // Parametres
        	    params();
        	    break;
        	
        	case 10: // Quitter
        		quitter = true;
        		break;
        	}
        	break;
        }

        // Controle des bords
        if (choix < 0)  choix = 0;
        if (choix > 10) choix = 10;
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
		s_console.gotoLigCol(10, DECAL_MENU2);
		std::cout << "Quelle couleur veux-tu etre ?";

		s_console.gotoLigCol(12, DECAL_MENU1);
		if (coul == NOIR) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else              s_console.setColor();
		std::cout << "- Noir";

		s_console.gotoLigCol(13, DECAL_MENU1);
		if (coul == BLANC) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		else               s_console.setColor();
		std::cout << "- Blanc";

		s_console.gotoLigCol(15, DECAL_MENU2);
		s_console.setColor();
		std::cout << "Appuyez sur [ENTREE] pour valider !";
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
	std::cout << "Commandes :" << std::endl;
	std::cout << std::endl;
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
	std::cout << "        A           Pour parcourir l'arbre de décision de l'IA" << std::endl;
	std::cout << std::endl;
	std::cout << "Appuyez sur [ENTREE]" << std::endl;
	std::cout.flush();

	// Attente
	do {} while (s_console.getch() != ENTREE);
}

bool Menu::charger(Tableau& tab, bool& memia_noire, bool& memia_blanche) const {
	// Déclarations
	bool annule = false;
	std::ifstream f;
	std::string nom;
	int taille = 0;

	// Affichage de l'entete
	entete();

	do {
		// Demande d'un nom de fichier :
		s_console.gotoLigCol(10, DECAL_MENU2);
		std::cout << "Entrez le nom du fichier à charger :";

		// Effacage du nom précédemment entré
		if (taille != 0) {
			s_console.gotoLigCol(11, DECAL_MENU2);
			for (int i = 0; i < taille; i++) std::cout << " ";
		}
		std::cout.flush();

		s_console.gotoLigCol(11, DECAL_MENU2);
		nom = "";
		getline(std::cin, nom);

		// Effacage du message d'erreur
		if (taille != 0) {
			s_console.gotoLigCol(13, DECAL_MENU2);
			for (int i = 0; i < taille; i++) std::cout << " ";

			s_console.gotoLigCol(14, DECAL_MENU2);
			for (int i = 0; i < taille; i++) std::cout << " ";
		}
		std::cout.flush();

		taille = 0;

		// On annule !
		if (nom == "") {
			s_console.gotoLigCol(13, DECAL_MENU2);
			s_console.setColor(COLOR_YELLOW);
			std::cout << "Annulé ! ";
			s_console.setColor();
			std::cout.flush();

			annule = true;
			break;
		}

		// Tentative d'ouverture
		nom += ".txt";
		f.clear();
		errno = 0;
		f.open(nom);

		// Cas d'erreur
		if (f.fail()) {
			// Message d'erreur
			s_console.gotoLigCol(13, DECAL_MENU2);
			s_console.setColor(COLOR_RED);
			std::cout << "Erreur à l'ouverture du fichier '" + nom + "' :";

			s_console.gotoLigCol(14, DECAL_MENU2);
			std::cout << strerror(errno);
			s_console.setColor();
			std::cout.flush();

			// Calcul de la taille pour effacer
			taille = MAX(nom.size() + 36, strlen(strerror(errno)));
			continue;
		}

		// Chargement :
		std::shared_ptr<IA> ia_noire = nullptr;
		std::shared_ptr<IA> ia_blanche = nullptr;
		Etat etat;

		std::string buf;

		// Lecture des joueurs
		f >> buf;
		if (buf == "random")    ia_noire = std::make_shared<RandomIA>();
		if (buf == "minmax")    ia_noire = std::make_shared<MinMaxIA>(m_prof, NOIR);
		if (buf == "alphabeta") ia_noire = std::make_shared<AlphaBetaIA>(m_prof, NOIR);
		if (buf == "negamax")   ia_noire = std::make_shared<NegaMaxIA>(m_prof, NOIR);
		if (buf == "memory") {
			int pos = -1;
			f >> pos;

			m_memia_noire->set_noeud(pos);
			ia_noire = m_memia_noire;
			memia_noire = true;
		}

		f >> buf;
		if (buf == "random")    ia_blanche = std::make_shared<RandomIA>();
		if (buf == "minmax")    ia_blanche = std::make_shared<MinMaxIA>(m_prof, BLANC);
		if (buf == "alphabeta") ia_blanche = std::make_shared<AlphaBetaIA>(m_prof, BLANC);
		if (buf == "negamax")   ia_blanche = std::make_shared<NegaMaxIA>(m_prof, BLANC);
		if (buf == "memia") {
			int pos = -1;
			f >> pos;

			m_memia_blanche->set_noeud(pos);
			ia_blanche = m_memia_blanche;
			memia_blanche = true;
		}

		// C'est à qui de jouer ?
		f >> etat.joueur;

		// Pions !
    	etat.othellier = std::vector<std::vector<COULEUR>>(8, std::vector<COULEUR>(8, VIDE));
    	for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				f >> etat.othellier[i][j];

				switch (etat.othellier[i][j]) {
				case NOIR:
					etat.scores[NOIR]++;
					break;

				case BLANC:
					etat.scores[BLANC]++;
					break;

				case VIDE:
					break;
				}
			}
		}

		tab = Tableau(std::move(etat), ia_noire, ia_blanche);
		f.close();

		// Message de fin
		s_console.gotoLigCol(13, DECAL_MENU2);
		s_console.setColor(COLOR_GREEN);
		std::cout << "Chargé ! ";
		s_console.setColor();

		break;
	} while(true);

	// Attente finale !
	s_console.gotoLigCol(16, DECAL_MENU2);
	std::cout << "Appuyez sur [ENTREE]" << std::endl;
	std::cout.flush();
	do {} while (s_console.getch() != ENTREE);

	return !annule;
}

void Menu::params() {
	// Déclarations
	bool quitter = false;
	int pos = 0;
	
	do {
		// Entete
		entete();
		
		// Affichage
		s_console.gotoLigCol(11, 5);
		std::cout << "Profondeur de recherche des IA :";
		
		s_console.gotoLigCol(11, 38);
		if (pos == 0) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		std::cout << " - ";
		
		s_console.setColor();
		s_console.gotoLigCol(11, 42);
		std::cout << m_prof;
		
		s_console.gotoLigCol(11, 45);
		if (pos == 1) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		std::cout << " + ";
		
		s_console.setColor();
		s_console.gotoLigCol(14, DECAL_MENU2);
		if (pos == 2) s_console.setColor(COLOR_BLACK, COLOR_WHITE);
		std::cout << "- Retour";
		
		s_console.setColor();
		
		// Interactions
		switch (s_console.getch()) {
		case 'z':
		case FL_HAUT:
		    if (pos == 2) pos = 0;
			break;
		
		case 'q':
		case FL_GAUCHE:
		    if (pos == 1) pos = 0;
			break;
		
		case 's':
		case FL_BAS:
		    pos = 2;
			break;
		
		case 'd':
		case FL_DROITE:
		    if (pos == 0) pos = 1;
			break;
		
		case 'e':
		case ENTREE:
			switch (pos) {
			case 0:
				m_prof--;
				if (m_prof < 1) m_prof = 1;
				break;
			
			case 1:
				m_prof++;
				if (m_prof > 20) m_prof = 20;
				break;
			
			case 2:
				quitter = true;
				break;
			}
			
			break;
		}
	} while (!quitter);
	
	// Mise à jour des MemIA
	m_memia_noire->set_prof(m_prof);
	m_memia_blanche->set_prof(m_prof);
}
