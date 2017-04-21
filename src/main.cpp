/** @file main.cpp
 *
 * Petite note : ne jamais ajouter le dossier qt ! Y a un autre main dedans
 */

// Importations
#include <iostream>
#include <memory>

#include "plateau.h"
#include "memia.h"
#include "minmaxia.h"

#define PROF_ALGO 3

// Main
int main() {
    // Init MemIAs
<<<<<<< HEAD
    std::shared_ptr<IA> memia_noire   = std::make_shared<MinMaxIA>(PROF_ALGO, NOIR);
    std::shared_ptr<IA> memia_blanche = std::make_shared<MemIA>("arbre_blanc.txt", PROF_ALGO, BLANC);

    // Création du plateau de jeu
//    Tableau t = Tableau(nullptr, std::make_shared<MinMaxIA>(PROF_ALGO, BLANC));
    Tableau t = Tableau(memia_noire, nullptr);
    t.BoucleJeu();
=======
    std::shared_ptr<MemIA> memia_noire   = std::make_shared<MemIA>("arbre_noir.txt",  PROF_ALGO, NOIR);
    std::shared_ptr<MemIA> memia_blanche = std::make_shared<MemIA>("arbre_blanc.txt", PROF_ALGO, BLANC);
    
    // Création du plateau de jeu
//    Tableau t = Tableau(nullptr, std::make_shared<MinMaxIA>(PROF_ALGO, BLANC));
    Tableau t = Tableau(memia_noire, memia_blanche);
//    Tableau t = Tableau(nullptr, memia_blanche);
//    Tableau t = Tableau();
    COULEUR v = t.BoucleJeu();
    
    // A commenté si les MemIA ne jouent pas !
    if (v == NOIR)  { memia_noire->gagne(); memia_blanche->perdu(); }
    if (v == BLANC) { memia_blanche->gagne(); memia_noire->perdu(); }
>>>>>>> b3d12e41d1d46ca1e4f129ccf581c8b63669c5d4

	return 1; // Erreur => y a pas de code !!!
}
