#ifndef NEGAMAXIA_H
#define NEGAMAXIA_H

// Dépendances
#include "alphabetaia.h"

#include <string>

// Classe
class NegaMaxIA : public AlphaBetaIA {
    protected:
        // Méthodes
        virtual MinMaxIA::PV alphabeta(Etat&& etat, unsigned prof, int alpha, int beta) override;

    public:
        // Constructeur
        NegaMaxIA(unsigned prof, COULEUR c);
        
        // Méthodes
        virtual std::string id() const override;
};

#endif // NEGAMAXIA_H
