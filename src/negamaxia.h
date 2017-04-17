#ifndef NEGAMAXIA_H
#define NEGAMAXIA_H

// Dépendances
#include "alphabetaia.h"

// Classe
class NegaMaxIA : public AlphaBetaIA {
    protected:
        // Méthodes
        virtual MinMaxIA::PV alphabeta(Etat&& etat, unsigned prof, int alpha, int beta) override;

    public:
        // Constructeur
        NegaMaxIA(unsigned prof);
};

#endif // NEGAMAXIA_H
