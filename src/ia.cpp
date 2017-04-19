// Importations
#include <functional>
#include <iostream>
#include <set>
#include <vector>

#include "pion.h"
#include "etat.h"
#include "ia.h"

// Fonctions
static bool cc(Pion const& c1, Pion const& c2) {
    return ((c1.x + c1.y * 10) < (c2.x + c2.y * 10));
}

// Constructeur
IA::IA() {
}

// Méthodes
std::set<Pion,bool(&)(Pion const&,Pion const&)> IA::get_coups(Etat const& plateau) const {
    // Déclaration du set
    std::set<Pion,bool(&)(Pion const&,Pion const&)> coups(cc);

    // Analyse du plateau
    COULEUR ennemi = (plateau.joueur == BLANC) ? NOIR : BLANC;

    for (Pion p : plateau.pions(plateau.joueur)) {
        // Recherche de coups possibles
        for (auto d : DIRECTIONS) {
            // Init recherche
            int i = p.x, j = p.y;
            d(i, j); // On se déplace 1 fois

            // Recherche
            bool e = false, v = false; // v => vide, e => ennemi
            for (; (i < 8) && (j < 8) && (i >= 0) && (j >= 0); d(i, j)) {
                if (plateau.othellier[i][j] == ennemi) {
                    e = true;
                } else {
                    v = (plateau.othellier[i][j] == VIDE);
                    break;
                }
            }

            // Confirmation
            if (e && v) coups.insert({i,j,plateau.joueur});
        }
    }

    //std::cout << "coups : " << coups.size() << std::endl;
    return coups;
}

std::shared_ptr<Noeud<IA::PV>> IA::arbre() const {
    return m_arbre;
}

// Compte le nombre de descendants au 3e coup
int IA::compt_desc() {
    // Déclaration des variables
    int nb_desc = 0;

    // Pour tous les descendants au 2e coup,
    // On ajoute le nb de fils au nb total de descendants
    for (unsigned int i = 0; i < m_arbre->size(); i++) {
        for (unsigned int j = 0; j < m_arbre->fils(i)->size(); j++) {
            nb_desc += m_arbre->fils(i)->fils(j)->size();
        }
    }

    return nb_desc;
}

void IA::charg_tab() {
    // Déclaration des variables
    bool ligne_3 = false;
    bool ligne_4 = false;

    // On ajoute la première ligne, et on y stock le premier pointeur
    m_tab.push_back(std::vector<std::shared_ptr<Noeud<PV>>>(1));
    m_tab[0][0] = m_arbre;

    // Deuxième ligne
    m_tab.push_back(std::vector<std::shared_ptr<Noeud<PV>>>(m_arbre->size()));
    for (unsigned int i = 0; i < m_arbre->size(); i++) {
        m_tab[1][i] = m_arbre->fils(i);
    }

    // Troisième ligne
    for (unsigned int i = 0; i < m_tab[1].size(); i++) {
        for (unsigned int j = 0; j < m_tab[1][i]->size(); i++) {
            // Si on a pas encore créé la ligne 3
            // (utile, car comme ça, on ne crée pas la ligne 3 si les noeuds de la ligne 2 n'ont pas de fils)
            if (!ligne_3) {
                m_tab.push_back(std::vector<std::shared_ptr<Noeud<PV>>>(0));
                ligne_3 = true;
            }

            m_tab[2].push_back(m_tab[1][i]->fils(j));
        }
    }

    // Quatrième ligne, seulement si il y en a une 3e
    if (ligne_3) {
        for (unsigned int i = 0; i < m_tab[2].size(); i++) {
            for (unsigned int j = 0; j < m_tab[2][i]->size(); i++) {
                // Si on a pas encore créé la ligne 4
                if (!ligne_4) {
                    m_tab.push_back(std::vector<std::shared_ptr<Noeud<PV>>>(0));
                    ligne_4 = true;
                }
                m_tab[3].push_back(m_tab[2][i]->fils(j));
            }
        }
    }
}


