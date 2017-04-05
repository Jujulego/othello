// Importations
#include <memory>
#include <iostream>
#include <set>

#include "arbre.h"
#include "etat.h"
#include "ia.h"
#include "pion.h"
#include "minmaxia.h"

// Constructeur
MinMaxIA::MinMaxIA(unsigned prof) : IA(), m_prof(prof-1),
    m_algo([this] (std::shared_ptr<CE> const& ce) -> unsigned { return ce->etat.scores.at(this->m_couleur); }) {
}

// Méthodes
Pion MinMaxIA::jouer(Etat const& plateau) {
    // Construction de l'arbre
    Arbre<std::shared_ptr<CE>> arbre(std::shared_ptr<CE>(new CE({plateau, {-1, -1, plateau.joueur}})));
    std::set<std::shared_ptr<Arbre<std::shared_ptr<CE>>::Noeud>> noeuds;
    std::set<std::shared_ptr<Arbre<std::shared_ptr<CE>>::Noeud>> peres;
    noeuds.insert(arbre.racine());

    for (unsigned i = 0; i < m_prof; i++) {
        // Copies noeuds => peres
        peres = noeuds;
        noeuds.clear();

        // Génération des fils
        std::cout << i << std::endl;
        for (auto p : peres) {
            for (auto c : get_coups(p->val()->etat)) {
                Etat e(p->val()->etat); // Copie de l'état
                e.appliquer_coup(c);

                auto n = arbre.add_noeud(std::shared_ptr<CE>(new CE({e, c})), p);
                noeuds.insert(n);

                std::cout << p << " >> " << n << std::endl;
            }

            std::cout << std::endl;
        }
    }

    // Appel de l'algo
    m_couleur = plateau.joueur;
    return m_algo.exec(arbre, (m_prof % 2) == 0)->coup;
}
