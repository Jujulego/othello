#ifndef ALPHABETAIA_H
#define ALPHABETAIA_H

// Dépendances
#include <string>

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
        virtual std::string id() const override;
        virtual Pion jouer(Etat plateau) override;
};

#endif // ALPHABETAIA_H
