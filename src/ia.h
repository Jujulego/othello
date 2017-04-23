#ifndef IA_H
#define IA_H

// Dépendances
#include <memory>
#include <set>
#include <vector>
#include <utility>
#include <string>

#include "etat.h"
#include "noeud.h"
#include "pion.h"
#include "console.h"

///Classe mère de la partie IA
// Classe
class IA {
    public:
        // Type
        struct PV { int val; Pion pion; };

    protected:
        // Attributs
        std::shared_ptr<Noeud<PV>> m_arbre;

    public:
        // Destructeur
        virtual ~IA() = default;

        // Méthodes
        /// Methode virtuel permetant de connaitre l'IA
        virtual std::string id() const = 0;

        /// Methode virtuel permettant aux différents IA de jouer en respectant les règles du jeu
        virtual Pion jouer(Etat plateau) = 0;

        /// Renvoie tous les coups possible sur le plateau donné
        std::set<Pion,bool(&)(Pion const&,Pion const&)> get_coups(Etat const& plateau) const;

        /// Affichage de l'abre et affichage des consignes pour se déplacer sur l'arbre
        void aff_arbre(Console* s_console, std::shared_ptr<Noeud<PV>> noeud, int num_coup);

        /// Permet la gestion global de l'arbre
        bool gere_arbre(Console* s_console, std::shared_ptr<Noeud<PV>> noeud, int num_coup, Etat etat);

        /// Dessine le plateau à coté de l'arbre
        void dess_plat(Console* s_console, int x, int y, Pion pion, Etat etat, int val);

        // Accesseurs
        std::shared_ptr<Noeud<PV>> arbre() const;
};

#endif // IA_H
