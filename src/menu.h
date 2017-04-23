#ifndef __MENU
#define __MENU

// Dépendances
#include <memory>

#include "console.h"
#include "memia.h"
#include "plateau.h"

// Classe
class Menu {
	private:
		// Attributs
		std::shared_ptr<MemIA> m_memia_noire;
		std::shared_ptr<MemIA> m_memia_blanche;
		
		// Attributs statiques
		static Console s_console;
	
	public:
		// Constructeur
		Menu();
		
		// Méthode statique
		static void entete();
		
		// Méthodes
		void afficher() const;
		COULEUR choix_coul() const;
		void regles() const;
		bool charger(Tableau& tab, bool& memia_noire, bool& memia_blanche) const;
};

#endif // __MENU
