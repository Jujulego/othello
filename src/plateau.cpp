#include <cerrno>
#include <cstring>
#include <chrono>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <thread>

#include "console.h"
#include "etat.h"
#include "macros.h"
#include "plateau.h"

// Macros
#define DROITE_PLATEAU 50

// Constructeur
Tableau::Tableau(std::shared_ptr<IA> ia_noir, std::shared_ptr<IA> ia_blanc) {
    // Init joueur
    m_ias[NOIR]  = ia_noir;
    m_ias[BLANC] = ia_blanc;

    if (m_ias[NOIR] != nullptr) m_col_ia = NOIR;
    else if (m_ias[BLANC] != nullptr) m_col_ia = BLANC;

    // Init etat
    m_etat.joueur = NOIR;     // tjs le noir qui commence
    m_etat.scores[NOIR]  = 2; // = au nb de pions du joueur
    m_etat.scores[BLANC] = 2;

    // Init plateau
    m_etat.othellier = std::vector<std::vector<COULEUR>>(TailleTab, std::vector<COULEUR>(TailleTab, VIDE));
    m_etat.othellier[3][4] = NOIR;
    m_etat.othellier[4][3] = NOIR;
    m_etat.othellier[3][3] = BLANC;
    m_etat.othellier[4][4] = BLANC;
}

Tableau::Tableau(Etat&& etat, std::shared_ptr<IA> ia_noir, std::shared_ptr<IA> ia_blanc) {
	// Init joueurs
    m_ias[NOIR]  = ia_noir;
    m_ias[BLANC] = ia_blanc;

    // Init etat
    m_etat = std::move(etat);
}

// Méthodes
void Tableau::CreationTab() {
    // Affichage du plateau
    s_console->clear();
    s_console->gotoLigCol(3, 0);
    char l;

    std::cout << "     A    B    C    D    E    F    G    H" << std::endl;
    std::cout << "   " << LIGNE_HAUT << std::endl;

    for (int i = 0; i < TailleTab; i++) {
        for (int j = 0; j < 2; j++) {
            l = ' ';

            if (j % 2) {
                l = '1' + i;
            }

            s_console->gotoLigCol(i*3+5+j, 0);
            std::cout << " " << l << " " << LIGNE_MIL1 << " " << l;

            s_console->setColor(COLOR_DEFAULT, COLOR_GREEN);
            for (int c = 0; c < 8; c++) {
            	s_console->gotoLigCol(i*3+5+j,4+5*c);
            	std::cout << "    ";
            }

            s_console->setColor();
        }

        if (i != 7) {
            s_console->gotoLigCol(i*3+7, 0);
            std::cout << "   " << LIGNE_MIL2;
        }

    }

    s_console->gotoLigCol(28, 0);
    std::cout << "   " << LIGNE_BAS << std::endl;
    std::cout << "     A    B    C    D    E    F    G    H" << std::endl;
    
    AfficherTab();
}

void Tableau::AfficherTab() {
    for (int i = 0; i < TailleTab; i++) {
        for (int j = 0; j < TailleTab; j++) {
            // Rien à faire pour le cases vides
            if (m_etat.othellier[i][j] == VIDE) {
                continue;
            }

            // Choix de la couleur
            switch (m_etat.othellier[i][j]) {
            case VIDE: // Rien à faire pour les cases vides
            	continue;

            case BLANC:
                s_console->setColor(COLOR_DEFAULT, COLOR_WHITE);
                break;

            case NOIR:
                s_console->setColor(COLOR_DEFAULT, COLOR_BLACK);
                break;
            }

            // Affichage du pion
            s_console->gotoLigCol(5+3*j,4+5*i);
            std::cout << "    ";
            s_console->gotoLigCol(6+3*j,4+5*i);
            std::cout << "    ";
            s_console->setColor();
        }
    }

	// Commandes
    int off = 0;
    s_console->gotoLigCol(5, DROITE_PLATEAU);
    std::cout << "Commandes :";

    if ((m_col_ia != VIDE) && (m_ias[m_col_ia]->arbre() != nullptr)) {
        s_console->gotoLigCol(6, DROITE_PLATEAU);
        std::cout << "A : Montrer le graphe d'etat";

        off++;
    }

    s_console->gotoLigCol(6+off, DROITE_PLATEAU);
    std::cout << "F : Sauvegarder";
    s_console->gotoLigCol(7+off, DROITE_PLATEAU);
    std::cout << "E : Quitter";

    // Message
    s_console->gotoLigCol(10, 50);
    std::cout << "Au tour de " << ((m_etat.joueur == NOIR) ? "noir ! " : "blanc !");

    s_console->gotoLigCol(15, 50);
    std::cout << "Blanc : " << m_etat.scores[BLANC] << " ";

    s_console->gotoLigCol(16, 50);
    std::cout << "Noir  : " << m_etat.scores[NOIR] << " ";
}

bool Tableau::Jouer(int &x, int&y) {
    // declaration des variables
    bool onContinue = true, quitter = false;
    int c;

    // boucle tant que on a pas appuyer sur entrer (pour entrer un pion)
    while (onContinue) {
        // Deplacement du curseur
        s_console->gotoLigCol(6+3*y,5+5*x);

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

        case 'a':
            if ((m_ias[m_col_ia]->arbre() != nullptr) && (m_ias[m_col_ia]->id() == "minmax")) {
                // On affiche l'arbre
                m_ias[m_col_ia]->gere_arbre(s_console, m_ias[m_col_ia]->arbre(), 0, m_etat.othellier);
            }
            // On réaffiche le plateau
            CreationTab();

            break;

        case 'f':
        	if (sauvegarder()) {
	            quitter = true;
    	        onContinue = false;
        	}

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
        // Message
        s_console->gotoLigCol(10, DROITE_PLATEAU);
        std::cout << "Au tour de " << ((m_etat.joueur == NOIR) ? "noir ! " : "blanc !");

        std::cout.flush();

        // Execution de l'IA
        if (m_ias[m_etat.joueur] != nullptr) {
        	// On va dormir un peu
        	//std::this_thread::sleep_for(TIMEOUT);
        	m_etat.appliquer_coup(m_ias[m_etat.joueur]->jouer(m_etat));
        } else {
            // Interaction
            continuer = Jouer(x, y); // consequences, on envoi x y
        }

        // Affichage
        AfficherTab();

        s_console->gotoLigCol(15, DROITE_PLATEAU);
        std::cout << "Blanc : " << m_etat.scores[BLANC] << " ";

        s_console->gotoLigCol(16, DROITE_PLATEAU);
        std::cout << "Noir  : " << m_etat.scores[NOIR] << " ";
        std::cout.flush(); // Force la mise à jour de l'écran

        // Test peut pas jouer !
        if (m_etat.coups_restant(m_etat.joueur) == 0) { // Le joueur ne peux pas jouer !
        	// Message
            s_console->gotoLigCol(11, DROITE_PLATEAU);
            s_console->setColor(COLOR_YELLOW);
	        std::cout << ((m_etat.joueur == NOIR) ? "Noir" : "Blanc") << " ne peux pas jouer !";
	        s_console->setColor();
	        std::cout.flush();

        	// On passe au suivant
        	m_etat.joueur = (m_etat.joueur == NOIR) ? BLANC : NOIR;

        	// Test de fin !
        	if (m_etat.coups_restant(m_etat.joueur) == 0) { // Personne ne peux jouer !
	        	m_etat.joueur = (m_etat.joueur == NOIR) ? BLANC : NOIR;
        		continuer = false;

    	    	// Message
    	    	COULEUR v = m_etat.joueur;
    	    	if (m_etat.scores[NOIR] > m_etat.scores[BLANC]) {
    	    		v = NOIR;
    	    	} else if (m_etat.scores[NOIR] < m_etat.scores[BLANC]) {
    	    		v = BLANC;
    	    	}

                s_console->gotoLigCol(12, DROITE_PLATEAU);
	        	std::cout << ((v == NOIR) ? "Noir" : "Blanc") << " a gagne !";
    		    s_console->gotoLigCol(13, DROITE_PLATEAU);
	        	std::cout << "Appuyer sur [ENTREE]";
		        std::cout.flush();

			    // Attente
			    do {} while (s_console->getch() != ENTREE);
        	}
        } else {
            s_console->gotoLigCol(11, DROITE_PLATEAU);
            std::cout << "                        ";
        }
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

bool Tableau::sauvegarder() const {
	// Déclarations
	bool annule = false;
	std::string nom;
	std::ofstream f; // au lieu de fstream => permet de créer un fichier

	int taille = 0;

	// Interactions !
	do {
		// Affichage
		s_console->gotoLigCol(21, DROITE_PLATEAU);
		std::cout << "Entrez un nom de fichier :";
		std::cout.flush();

		// Effacement du nom précédent
		if (taille != 0) {
			s_console->gotoLigCol(22, DROITE_PLATEAU);
			for (int i = 0; i < taille; i++) std::cout << " ";
		}

		// Entrée
		s_console->gotoLigCol(22, DROITE_PLATEAU);
		std::getline(std::cin, nom);

		// Effacement d'un eventuel message d'erreur
		if (taille != 0) {
			s_console->gotoLigCol(18, DROITE_PLATEAU);
			for (int i = 0; i < taille; i++) std::cout << " ";
			s_console->gotoLigCol(19, DROITE_PLATEAU);
			for (int i = 0; i < taille; i++) std::cout << " ";
			std::cout.flush();
		}

		// Annulation (chaine vide)
		if (nom == "") {
			// Message d'annulation
			s_console->gotoLigCol(24, DROITE_PLATEAU);
			s_console->setColor(COLOR_YELLOW);
			std::cout << "Annulé !" << std::endl;
			s_console->setColor();

			annule = true;
			break;
		}

		// Tentative d'ouverture
		errno = 0;
		f.clear();
		f.open(nom + ".txt", std::ios_base::out | std::ios_base::trunc); // Vide le fichier à l'ouverture

		// Cas d'erreur :
		if (f.fail()) {
			s_console->gotoLigCol(18, DROITE_PLATEAU);
			s_console->setColor(COLOR_RED);
			std::cout << "Erreur à l'ouverture de '" << nom << ".txt' :";

			s_console->gotoLigCol(19, DROITE_PLATEAU);
			std::cout << strerror(errno);

			s_console->setColor();
			std::cout.flush();

			taille = MAX(nom.size() + 32, strlen(strerror(errno)));

			continue;
		}

		// Enregistrement
		f << ((m_ias.at(NOIR ) == nullptr) ? "joueur" : m_ias.at(NOIR )->id()) << std::endl;
		f << ((m_ias.at(BLANC) == nullptr) ? "joueur" : m_ias.at(BLANC)->id()) << std::endl;
		f << m_etat.joueur << std::endl;

		for (int i = 0; i < 8; i++) {
		    for (int j = 0; j < 8; j++) {
		    	f << m_etat.othellier[i][j] << " ";
		    }
		    f << std::endl;
		}

		f.close();

        // Message de confirmation
		s_console->gotoLigCol(24, DROITE_PLATEAU);
		s_console->setColor(COLOR_GREEN);
		std::cout << "Sauvegardé !" << std::endl;
		s_console->setColor();

		break;
	} while (true);

    // Attente
	s_console->gotoLigCol(25, DROITE_PLATEAU);
   	std::cout << "Appuyer sur [ENTREE]";
    std::cout.flush();

    do {} while (s_console->getch() != ENTREE);

	// Effacage des affichages en cas d'annulation
	if (annule) {
		s_console->gotoLigCol(21, DROITE_PLATEAU);
		std::cout << "                          ";
		s_console->gotoLigCol(24, DROITE_PLATEAU);
		std::cout << "        " << std::endl;
		s_console->gotoLigCol(25, DROITE_PLATEAU);
	   	std::cout << "                    ";
	}

	return !annule;
}

std::map<COULEUR,unsigned> const Tableau::scores() const {
	return m_etat.scores;
}
