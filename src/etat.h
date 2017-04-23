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
    ///Permet de connaitre la couleur de joueur qui doit jouer
    COULEUR joueur;
    std::map<COULEUR,unsigned> scores;

    /// Représentation générale du plateau
    std::vector<std::vector<COULEUR>> othellier;

    // Méthodes
    /// Renvoi les pions de la couleur donnée
    std::vector<Pion> pions(COULEUR c) const;

    /// Permet après un coup de retourner les pions de l'adversaire
    bool appliquer_coup(Pion const& p, bool fake = false);

	/// Renvoie le nombre coups possible pour la couleur
    int coups_restant(COULEUR c);
};

#endif // ETAT_H
