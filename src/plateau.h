#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#define TailleTab 8

#include <vector>
#include <map>
#include <memory>
#include <set>

#include "console.h"
#include "etat.h"
#include "ia.h"
#include "pion.h"

///Hérite de la classe console

class Tableau {
    private:
        Etat m_etat;
        std::map<COULEUR,std::shared_ptr<IA>> m_ias;
        COULEUR m_col_ia = VIDE;

    protected:
        /// Pointeur sur console initialisé à NULL
        Console* s_console = NULL;

    public:
    	// Constructeur
        Tableau(std::shared_ptr<IA> ia_noir = nullptr, std::shared_ptr<IA> ia_blanc = nullptr);
        Tableau(Etat&& etat, std::shared_ptr<IA> ia_noir, std::shared_ptr<IA> ia_blanc);

        // Méthodes
        /// Création de la structure du tableau
        void CreationTab();

        /// Permet le déplacement des pions et la pose d'un pion
        bool Jouer(int &x, int&y);

        /// Permet de choisir la couleur des cases, quand elles sont vides ou avec un pion
        void AfficherTab();

        /// Permet la permutation des joueurs, affiche le score des joueurs
        COULEUR BoucleJeu();

        /// Sauvegarde de la partie
        bool sauvegarder() const;

        // Accesseurs
        std::map<COULEUR,unsigned> const scores() const;
        std::vector<std::shared_ptr<Pion>> const& get_pions() const;
};

#endif // PLATEAU_H_INCLUDED
