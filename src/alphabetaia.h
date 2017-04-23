/** @file: alphabetaia.h
 * @brief: Défini AlphaBetaIA une IA basée sur l'algorithme AlphaBeta
 *
 * Pour plus d'explication sur l'algorithme suivez ce lien :
 * https://fr.wikipedia.org/wiki/%C3%89lagage_alpha-b%C3%AAta
 */

#ifndef ALPHABETAIA_H
#define ALPHABETAIA_H

// Dépendances
#include <string>

#include "minmaxia.h"

// Classe
/** Classe de l'IA AlphaBeta
 * Hérite de MinMax pour récupérer l'heuristique et la profondeur
 */
class AlphaBetaIA : public MinMaxIA {
    protected:
        // Méthodes
        /// L'algorithme en lui-même
        virtual MinMaxIA::PV alphabeta(Etat&& etat, unsigned prof, int alpha, int beta, std::shared_ptr<Noeud<MinMaxIA::PV>> noeud);

    public:
        /// Constructeur
        AlphaBetaIA(unsigned prof, COULEUR c);

        // Méthodes
        /// Identifiant de l'IA : "alphabeta"
        virtual std::string id() const override;
        
        /// Entrée de l'IA : lance l'execution de l'algorithme
        virtual Pion jouer(Etat plateau) override;
};

#endif // ALPHABETAIA_H
