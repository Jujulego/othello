#ifndef MINMAX_H
#define MINMAX_H

// Dépandances
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <set>

#include "arbre.h"

// Algo :
template<class D> // D est le type du graphe sur lequel on applique MinMax
class AlgoMinMax {
    private:
        // Attributs
        std::function<unsigned(D const&)> m_heuristique;

    public:
        // Constructeur
        AlgoMinMax(std::function<unsigned(D const&)> heuristique) : m_heuristique(heuristique) {
        }

        // Méthodes
        D exec(Arbre<D>& arbre, bool joueur = true) { // joueur à vrai signifie que les derniers noeuds concernent le joueur
            // Récupération des noeuds
            std::map<std::shared_ptr<typename Arbre<D>::Noeud>,std::shared_ptr<typename Arbre<D>::Noeud>> preds;
            std::map<std::shared_ptr<typename Arbre<D>::Noeud>,unsigned> noeuds;

            // Application de l'heuristique sur les feuilles (elles n'ont pas de fils !) + récup de leurs pères
            std::set<std::shared_ptr<typename Arbre<D>::Noeud>> peres;
            for (auto p : noeuds) {
                if (p.first->fils().size() == 0) {
                    noeuds[p.first] = m_heuristique(p.first->val());
                    peres.insert(p.first->pere());
                }
            }

            // MinMax !
            std::set<std::shared_ptr<typename Arbre<D>::Noeud>> feuilles;
            int i = joueur ? 0 : 1;
            unsigned val;

            while (!peres.empty()) {
                // Copie des pères
                feuilles = peres;
                peres.clear();
                i = (i + 1) % 2;

                // Parcours des noeuds
                for (auto n : peres) {
                    // Sélection de la valeur
                    if (i == 0) {
                        // i = 0 => moi => max !
                        val = 0;

                        for (auto f : n->fils()) {
                            if (noeuds[f] > val) {
                                val = noeuds[f];
                                preds[n] = f;
                            }
                        }
                    } else {
                        // i = 1 => lui => min !
                        val = std::numeric_limits<unsigned>::max();

                        for (auto f : n->fils()) {
                            if (noeuds[f] < val) {
                                val = noeuds[f];
                                preds[n] = f;
                            }
                        }
                    }

                    // Sauvegarde de la valeur
                    noeuds[n] = val;

                    // Ajout du père au prochains pères
                    peres.insert(n->pere());
                }
            }

            // Fini !
            return preds[arbre.racine()]->val();
        }
};

#endif // MINMAX_H
