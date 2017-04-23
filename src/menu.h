#ifndef __MENU
#define __MENU

// Dépendances
#include <memory>
#include <string>

#include "console.h"
#include "macros.h"
#include "memia.h"
#include "plateau.h"

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
		static void entete();
		
		// Méthodes
		int init();
		void afficher();
		COULEUR choix_coul() const;
		void regles() const;
		bool charger(Tableau& tab, bool& memia_noire, bool& memia_blanche) const;
		void params();
};

#endif // __MENU
