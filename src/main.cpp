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
    std::shared_ptr<IA> memia_noire   = std::make_shared<MinMaxIA>(PROF_ALGO, NOIR);
    std::shared_ptr<IA> memia_blanche = std::make_shared<MemIA>("arbre_blanc.txt", PROF_ALGO, BLANC);

    // Création du plateau de jeu
//    Tableau t = Tableau(nullptr, std::make_shared<MinMaxIA>(PROF_ALGO, BLANC));
    Tableau t = Tableau(memia_noire, nullptr);
    t.BoucleJeu();

	return 1; // Erreur => y a pas de code !!!
}
