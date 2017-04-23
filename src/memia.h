#ifndef MEMIA_H
#define MEMIA_H

// Dépendances
#include <memory>
#include <string>

#include "minmaxia.h"
#include "memarbre.h"
#include "negamaxia.h"

///Hérite de la classe AlphaBetaIA
class MemIA : public AlphaBetaIA {
    private:
        // Attributs
        std::shared_ptr<MemArbre> m_memarbre;
        std::shared_ptr<MemArbre::Noeud> m_noeud;

        // Méthodes
        /// Algorithme de Memia, basé sur AlphaBeta
        virtual MinMaxIA::PV memia(Etat&& etat, unsigned prof, int alpha, int beta, std::shared_ptr<MemArbre::Noeud> memnoeud, std::shared_ptr<Noeud<MinMaxIA::PV>> noeud);

    public:
        // Constructeur
        MemIA(std::string const& fichier, unsigned prof, COULEUR c);

        // Méthodes
        virtual std::string id() const override;
        virtual Pion jouer(Etat plateau) override;

        /// Incrémentation de la valeur du noeud
        void gagne();

        /// décrémentation de la valeur du noeud
        void perdu();

		/// Modifie la profondeur de recherche
        void set_prof(unsigned prof);
        /// Modifie le noeud actuel du MemIA
        void set_noeud(int pos);
};

#endif // MEMIA_H
