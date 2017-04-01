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
    std::map<COULEUR,unsigned> scores;

    // Représentation générale du plateau
    std::vector<std::vector<COULEUR>> othellier;

    // Méthodes
    std::vector<Pion> pions(COULEUR c) const;
    void appliquer_coup(Pion const& p);
};

#endif // ETAT_H
