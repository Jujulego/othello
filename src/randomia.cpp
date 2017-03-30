// Importations
#include <ctime>
#include <iostream>

#include "etat.h"
#include "ia.h"
#include "pion.h"
#include "randomia.h"

// Méthodes
Pion RandomIA::jouer(Etat const& plateau) {
    // Récupération de la liste des coups possibles
    auto coups = get_coups(plateau);

    // Tirage aléatoire !
    int r = rand() % coups.size();
    std::cout << r;

    // Récupération du coup
    auto it = coups.begin();
    for (int i = 0; i < r; i++) it++;

    return *it;
}
