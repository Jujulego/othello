#ifndef ALPHABETAIA_H
#define ALPHABETAIA_H

// Dépendances
#include "minmaxia.h"

// Classe
class AlphaBetaIA : public MinMaxIA {
    protected:
        // Méthodes
        virtual MinMaxIA::PV alphabeta(Etat&& etat, unsigned prof, int alpha, int beta);

    public:
        // Constructeur
        AlphaBetaIA(unsigned prof, COULEUR c);

        // Méthodes
        virtual Pion jouer(Etat plateau) override;
};

#endif // ALPHABETAIA_H
