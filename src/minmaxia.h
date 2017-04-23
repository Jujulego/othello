#ifndef MINMAXIA_H
#define MINMAXIA_H

// Dépendances
#include <memory>
#include <string>

#include "noeud.h"
#include "etat.h"
#include "ia.h"
#include "pion.h"

// Classe
/** IA basée sur l'algorithme MinMax
 * plus d'information sur ce lien :
 * https://fr.wikipedia.org/wiki/Algorithme_minimax
 */
class MinMaxIA : public IA {
    protected:
        // Attributs
        unsigned m_prof;
        COULEUR m_couleur;

        // Méthodes
        /// Fonction permettant la qualification d'un plateau de jeu
        virtual int heuristique(Etat&& etat) final;
        /// L'algorithme en lui meme
        virtual PV minmax(Etat&& etat, unsigned prof, std::shared_ptr<Noeud<PV>> noeud);

    public:
        // Constructeur
        MinMaxIA(unsigned prof, COULEUR c);

        // Méthodes
        /// Renvoie l'identifiant pour les sauvegardes
        virtual std::string id() const override;
        /// Executer l'algorithme
        virtual Pion jouer(Etat plateau) override;
};

#endif // MINMAXIA_H
