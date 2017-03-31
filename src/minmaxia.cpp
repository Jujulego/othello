// Importations
#include <memory>
#include <set>

#include "arbre.h"
#include "etat.h"
#include "ia.h"
#include "pion.h"
#include "minmaxia.h"

// Constructeur
MinMaxIA::MinMaxIA(unsigned prof) : IA(), m_prof(prof),
    m_algo([this] (CE const& ce) -> unsigned { return ce.etat.pions.at(this->m_couleur).size(); }) {
}

// Méthodes
Pion MinMaxIA::jouer(Etat const& plateau) {
    // Construction de l'arbre
    Arbre<CE> arbre({plateau, {-1, -1, plateau.joueur}});
    std::set<std::shared_ptr<Arbre<CE>::Noeud>> noeuds;
    std::set<std::shared_ptr<Arbre<CE>::Noeud>> peres;
    noeuds.insert(arbre.racine());

    for (unsigned i = 0; i < m_prof; i++) {
        // Copies noeuds => peres
        peres = noeuds;
        noeuds.clear();

        // Génération des fils
        for (auto p : peres) {
            for (auto c : get_coups(p->val().etat)) {
                Etat e(p->val().etat); // Copie de l'état
                e.appliquer_coup(c);
                noeuds.insert(arbre.add_noeud({e, c}, p));
            }
        }
    }

    // Appel de l'algo
    m_couleur = plateau.joueur;
    return m_algo.exec(arbre, (m_prof % 2) == 0).coup;
}
