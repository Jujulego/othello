#ifndef __MENU
#define __MENU

// Dépendances
#include <memory>
#include <string>

#include "console.h"
#include "macros.h"
#include "memia.h"
#include "plateau.h"

///Hérite de
///Permet l'affichage des different menus en console

// Classe
class Menu {
	private:
		// Attributs
		std::shared_ptr<MemIA> m_memia_noire;
		std::shared_ptr<MemIA> m_memia_blanche;
		unsigned m_prof = PROF_ALGO;

		// Attributs statiques
		static Console s_console;

		// Méthodes
		void fichier_erreur(std::string const& fichier, std::string const& err);

	public:
		// Méthode statique

    ///Affichage de caractères
		static void entete();

		// Méthodes
    ///Permet le chargement du jeu et prevenir si une erreur à eu lieu
		int init();

    ///Affichage du menu et application des choix effectués
		void afficher();

    ///Affichage du menu pour le choix des couleurs et application des choix effectués
		COULEUR choix_coul() const;

    ///Affichage des règles du jeu
		void regles() const;

    ///Permet de charger un fichier sauvergarder sous forme de fichier texte
		bool charger(Tableau& tab, bool& memia_noire, bool& memia_blanche) const;

    ///Modifie la profondeur de l'abre dans les IAs
		void params();
};

#endif // __MENU
