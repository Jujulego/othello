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
#include <vector>

// Enumération
enum COULEUR { VIDE, NOIR, BLANC };

// Structure
struct Etat {
    // Attributs
    COULEUR joueur;

    int score_blanc;
    int score_noir;

    std::vector<std::vector<COULEUR>> othellier;
};

#endif // ETAT_H
