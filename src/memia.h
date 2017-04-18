#ifndef MEMIA_H
#define MEMIA_H

// Dépendances
#include <memory>
#include <string>

#include "minmaxia.h"
#include "memarbre.h"

class MemIA : public MinMaxIA {
    private:
        // Attributs
        std::shared_ptr<MemArbre> m_memarbre;
        std::shared_ptr<MemArbre::Noeud> m_noeud;

    public:
        // Constructeur
        MemIA(std::string const& fichier);

        // Méthodes
        virtual Pion jouer(Etat plateau) override;
        void gagne();
        void perdu();
};

#endif // MEMIA_H
