#ifndef ALPHABETAIA_H
#define ALPHABETAIA_H

// Dépendances
#include "minmaxia.h"

// Classe
class AlphaBetaIA : public MinMaxIA {
    protected:
        // Méthodes
        MinMaxIA::PV alphabeta(const Etat &etat, unsigned prof, int alpha, int beta);

    public:
        // Constructeur
        AlphaBetaIA(unsigned prof);

        // Méthodes
        virtual Pion jouer(Etat const& plateau) override;
};

#endif // ALPHABETAIA_H
