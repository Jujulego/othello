#ifndef MINMAX_H
#define MINMAX_H

// Dépandances
#include <functional>
#include <limits>
#include <iostream>
#include <map>
#include <memory>
#include <set>

#include "arbre.h"

// Algo :
template<class D> // D est le type de l'arbre sur lequel on applique MinMax
class AlgoMinMax {
    private:
        // Attributs
        std::function<int(D const&)> m_heuristique;

    public:
        // Constructeur
        AlgoMinMax(std::function<int(D const&)> heuristique) : m_heuristique(heuristique) {
        }

        // Méthodes
        D exec(Arbre<D>& arbre, bool joueur = true) { // joueur à vrai signifie que les derniers noeuds concernent le joueur
            // Récupération des noeuds
            std::map<std::shared_ptr<typename Arbre<D>::Noeud>,std::shared_ptr<typename Arbre<D>::Noeud>> preds;
            std::map<std::shared_ptr<typename Arbre<D>::Noeud>,int> noeuds;

            // Application de l'heuristique sur les feuilles (elles n'ont pas de fils !) + récup de leurs pères
            std::set<std::shared_ptr<typename Arbre<D>::Noeud>> peres;
            for (auto p : arbre.noeuds()) {
                if (p->fils().size() == 0) {
                    noeuds[p] = m_heuristique(p->val());
                    if (p->pere() != nullptr) peres.insert(p->pere());

                    std::cout << p << " (" << noeuds[p] << ")" << std::endl;
                }
            }

            std::cout << std::endl;

            // MinMax !
            std::set<std::shared_ptr<typename Arbre<D>::Noeud>> feuilles;
            int i = joueur ? 0 : 1, val;

            while (!peres.empty()) {
                // Copie des pères
                feuilles = peres;
                peres.clear();
                i = (i + 1) % 2;

                // Parcours des noeuds
                for (auto n : feuilles) {
                    // Sélection de la valeur
                    if (i == 0) {
                        // i = 0 => moi => max !
                        val = std::numeric_limits<int>::min();

                        for (auto f : n->fils()) {
                            if (noeuds[f] > val) {
                                val = noeuds[f];
                                preds[n] = f;
                                std::cout << "max " << n << " << " << f << " (" << noeuds[f] << ")" << std::endl;
                            }
                        }
                    } else {
                        // i = 1 => lui => min !
                        val = std::numeric_limits<int>::max();

                        for (auto f : n->fils()) {
                            if (noeuds[f] < val) {
                                val = noeuds[f];
                                preds[n] = f;
                                std::cout << "min " << n << " << " << f << " (" << noeuds[f] << ")" << std::endl;
                            }
                        }
                    }

                    // Sauvegarde de la valeur
                    noeuds[n] = val;

                    // Ajout du père au prochains pères
                    if (n->pere() != nullptr) peres.insert(n->pere());
                }
            }

            // Fini !
            std::cout << preds[arbre.racine()] << std::endl;
            return preds[arbre.racine()]->val();
        }
};

#endif // MINMAX_H
