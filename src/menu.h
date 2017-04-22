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
		
		// Méthodes
		void entete() const;
		void afficher() const;
		COULEUR choix_coul() const;
		void regles() const;
};

#endif // __MENU