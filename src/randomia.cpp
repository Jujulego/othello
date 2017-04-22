// Importations
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "etat.h"
#include "ia.h"
#include "pion.h"
#include "randomia.h"

// Méthodes
std::string RandomIA::id() const {
	return "random";
}

Pion RandomIA::jouer(Etat plateau) {
    // Récupération de la liste des coups possibles
    auto coups = get_coups(plateau);

    // Tirage aléatoire !
    int r = std::rand() % coups.size();

    // Récupération du coup
    auto it = coups.begin();
    for (int i = 0; i < r; i++) it++;

    return *it;
}
