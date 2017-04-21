#ifndef MEMIA_H
#define MEMIA_H

// Dépendances
#include <memory>
#include <string>

#include "minmaxia.h"
#include "memarbre.h"
#include "negamaxia.h"

class MemIA : public AlphaBetaIA {
    private:
        // Attributs
        std::shared_ptr<MemArbre> m_memarbre;
        std::shared_ptr<MemArbre::Noeud> m_noeud;

        // Méthodes
        virtual MinMaxIA::PV memia(Etat&& etat, unsigned prof, int alpha, int beta, std::shared_ptr<MemArbre::Noeud> noeud);

    public:
        // Constructeur
        MemIA(std::string const& fichier, unsigned prof, COULEUR c);

        // Méthodes
        virtual Pion jouer(Etat plateau) override;
        void gagne();
        void perdu();
};

#endif // MEMIA_H
