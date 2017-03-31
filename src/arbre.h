#ifndef ARBRE_H
#define ARBRE_H

// Dépendances
#include <memory>
#include <set>
#include <vector>

// Classe
template<class D>
class Arbre {
    public:
        // Sous-classe
        class Noeud {
            private:
                // Attributs
                D m_val;
                std::weak_ptr<Noeud> m_self;
                std::weak_ptr<Noeud> m_pere;
                std::set<std::shared_ptr<Noeud>> m_fils;

                // Constructeur
                Noeud(D val, std::shared_ptr<Noeud> pere = nullptr) : m_val(val), m_pere(pere) {
                    if (pere != nullptr) pere->add_fils(pt());
                }

                // Méthodes
                void add_fils(std::shared_ptr<Noeud> fils) {
                    m_fils.insert(fils);
                }

                void pere(std::shared_ptr<Noeud> pere) {
                    m_pere = pere;
                }

            public:
                // Méthodes statiques
                static std::shared_ptr<Noeud> creer(D val, std::shared_ptr<Noeud> pere = nullptr) {
                    return (new Noeud(val, pere))->pt();
                }

                // Accesseurs
                std::set<std::shared_ptr<Noeud>> fils() {
                    return m_fils;
                }
                std::shared_ptr<Noeud> pere() const {
                    if (m_pere.expired()) return nullptr;
                    return std::shared_ptr<Noeud>(m_pere);
                }
                D val() {
                    return m_val;
                }
                std::shared_ptr<Noeud> pt() {
                    // Déclaration
                    std::shared_ptr<Noeud> pt;

                    // Initialisation (est vrai seulement au 1er appel !)
                    if (m_self.expired()) {
                        pt = typename std::shared_ptr<Noeud>(this);
                        m_self = pt;
                    } else {
                        pt = typename std::shared_ptr<Noeud>(m_self);
                    }

                    return pt;
                }
        };

        // Alias
        using iterateur       = typename std::vector<std::weak_ptr<Noeud>>::iterator;
        using const_iterateur = typename std::vector<std::weak_ptr<Noeud>>::const_iterator;

    private:
        // Attributs
        std::shared_ptr<Noeud> m_racine;
        std::vector<std::weak_ptr<Noeud>> m_noeuds;

    public:
        // Constructeur
        Arbre(D racine) : m_racine(Noeud::creer(racine)) {
            m_noeuds.push_back(m_racine);
        }

        // Méthodes
        std::shared_ptr<Noeud> add_noeud(D val, std::shared_ptr<Noeud> pere = nullptr) {
            if (pere == nullptr) pere = m_racine;
            std::shared_ptr<Noeud> n = Noeud::creer(val, pere);
            m_noeuds.push_back(n);

            return n;
        }

        // Accesseurs
        std::shared_ptr<Noeud> racine() const {
            return m_racine;
        }
        std::vector<std::shared_ptr<Noeud>> noeuds() {
            // Déclaration
            std::vector<std::shared_ptr<Noeud>> noeuds;

            // Copie & nettoyage
            for (auto it = m_noeuds.begin(); it != m_noeuds.end(); it++) {
                if (it->expired()) {
                    m_noeuds.erase(it);
                } else {
                    noeuds.push_back(std::shared_ptr<Noeud>(*it));
                }
            }

            return noeuds;
        }
};

#endif // ARBRE_H
