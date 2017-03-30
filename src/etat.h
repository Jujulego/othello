/** @file etat.h
 *
 * La structure Etat ...
 * Représente l'état actuel du jeu, utile pour les sauvegardes, (un historique ?) mais surtout pour l'IA !
 *
 * Vous faites ce que vous voulez ... mais l'IA prendra cette structure en entrée !
 */

#ifndef ETAT_H
#define ETAT_H

// Dépendances
#include <map>
#include <vector>

#include "pion.h"

// Structure
struct Etat {
    // Infos joueurs
    COULEUR joueur; // qui doit jouer
    std::map<COULEUR,int> scores;
    std::map<COULEUR,std::vector<Pion>> pions;

    // Représentation générale du plateau
    std::vector<std::vector<COULEUR>> othellier;
};

#endif // ETAT_H
