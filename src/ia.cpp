// Importations
#include <functional>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

#include "pion.h"
#include "etat.h"
#include "ia.h"
#include "console.h"

// Fonctions
static bool cc(Pion const& c1, Pion const& c2) {
    return ((c1.x + c1.y * 10) < (c2.x + c2.y * 10));
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

// Charge le double vecteur
// Celui-ci nous permettra de simplifier l'affichage, et de se déplacer plus facilement dans l'arbre
// Retourne le nombre total de descendants au coup 3 (ou autre si certaines branches s'arrêtent avant le coup 3), il sera utile pour l'affichage
int IA::charg_tab() {
    // Déclaration des variables
    bool ligne_3 = false;
    bool ligne_4 = false;
    int nb_desc = 0;

    // On ajoute la première ligne, et on y stock le premier pointeur
    m_tab.push_back(std::vector<std::pair <int, std::shared_ptr<Noeud<PV>>>>(1));
    m_tab[0][0].second = m_arbre;

    // Deuxième ligne
    m_tab.push_back(std::vector<std::pair <int, std::shared_ptr<Noeud<PV>>>>(m_arbre->size()));
    for (unsigned int i = 0; i < m_arbre->size(); i++) {
        m_tab[1][i].second = m_arbre->fils(i);

        // S'il n'a pas de fils, on l'ajoute au nombre de descendants
        if (!m_tab[1][i].second->size()) nb_desc++;
    }

    // Troisième ligne
    for (unsigned int i = 0; i < m_tab[1].size(); i++) {
        for (unsigned int j = 0; j < m_tab[1][i].second->size(); j++) {
            // Si on a pas encore créé la ligne 3
            // (utile car comme ça, on ne crée pas la ligne 3 si les noeuds de la ligne 2 n'ont pas de fils)
            if (!ligne_3) {
                m_tab.push_back(std::vector<std::pair <int, std::shared_ptr<Noeud<PV>>>>(0));
                ligne_3 = true;
            }

            m_tab[2].push_back(std::make_pair(0, m_tab[1][i].second->fils(j)));

            // S'il n'a pas de fils, on l'ajoute au nombre de descendants
            if (!m_tab[2][j].second->size()) nb_desc++;
        }
    }

    // Quatrième ligne, seulement si il y en a une 3e
    if (ligne_3) {
        for (unsigned int i = 0; i < m_tab[2].size(); i++) {
            for (unsigned int j = 0; j < m_tab[2][i].second->size(); j++) {
                // Si on a pas encore créé la ligne 4
                if (!ligne_4) {
                    m_tab.push_back(std::vector<std::pair <int, std::shared_ptr<Noeud<PV>>>>(0));
                    ligne_4 = true;
                }

                m_tab[3].push_back(std::make_pair(0, m_tab[2][i].second->fils(j)));

                // On l'ajoute au nombre de descendants
                nb_desc++;
            }
        }
    }

    // On retourne le nombre de descendants
    return nb_desc;
}

// Affiche l'arbre
// s_console : console dans laquelle on affiche
// x, y : coordonnées de base de l'affichage de l'arbre (en haut à gauche de l'arbre)
void IA::aff_arbre(Console* s_console, int x, int y) {
    // Déclaration de l'arbre
    int nb_desc = 0; // nombre total de descendants
    int nb_desc_aff = 0; // nombre de descendants déjà affichés
    int moy_1 = 0; // moyenne des abscisses des noeuds du coup 1
    int moy_2 = 0; // moyenne des abscisses des noeuds du coup 2 dans une branche
    int moy_3 = 0; // moyenne des abscisses des noeuds du coup 3 dans une branche

    // On charge le tableau, et on prend le nombre de descendants
    nb_desc = charg_tab();

    // On dessine l'arbre en partant du bas :
    // Pour chaque fils du noeud de base (coup 1)
    for (unsigned int i =0; i < m_tab[0][0].second->size(); i++) {
        // On remet à 0 la moyenne au coup 2 (car nouvelle branche)
        moy_2 = 0;

        // On prend chaque fils (coup 2)
        for (unsigned int j = 0; j < m_tab[1][i].second->size(); j++) {
            // On remet à 0 la moyenne au coup 3 (car nouvelle branche)
            moy_3 = 0;

            // On prend chaque fils (coup 3)
            for (unsigned int k = 0; k < m_tab[2][j].second->size(); k++) {
                // On affiche le noeud
                m_tab[3][k].first = x + nb_desc_aff;
                s_console->gotoLigCol(m_tab[3][k].first, y + 9);
                std::cout << "\e8";
                // RAJOUTER BRANCHES

                // On incrémente le nombre de descendants affichés
                nb_desc_aff++;

                // On modifie la moyenne 3
                if (!moy_3) moy_3 = m_tab[3][k].first;
                else moy_3 = (moy_3 + m_tab[3][k].first) / 2;
            }

            // On affiche le noeud
            if (!m_tab[2][j].second->size()) { // Si le noeud n'a pas de fils
                m_tab[2][j].first = x + nb_desc_aff;
                nb_desc_aff++;
            }
            else m_tab[2][j].first = x + moy_3; // Sinon on donne comme abscisse au noeud la "moyenne", calculée à partir des abscisses de ses fils
            s_console->gotoLigCol(m_tab[2][j].first, y + 6);
            std::cout << "\e8";
            // RAJOUTER BRANCHES

            // On modifie la moyenne 2
            if (!moy_2) moy_2 = m_tab[2][j].first;
            else moy_2 = (moy_2 + m_tab[2][j].first) / 2;
        }

        // On affiche le noeud
        if (!m_tab[1][i].second->size()) { // Si le noeud n'a pas de fils
            m_tab[1][i].first = x + nb_desc_aff;
            nb_desc_aff++;
        }
        else m_tab[1][i].first = x + moy_2; // Sinon on donne comme abscisse au noeud la "moyenne", calculée à partir des abscisses de ses fils
        s_console->gotoLigCol(m_tab[1][i].first, y + 3);
        std::cout << "\e8";
        // RAJOUTER BRANCHES

        // On modifie la moyenne 1
        if (!moy_1) moy_1 = m_tab[1][i].first;
        else moy_1 = (moy_1 + m_tab[1][i].first) / 2;
    }

    // On affiche le noeud de base
    m_tab[0][0].first = x + moy_1; // On lui donne son abscisse
    s_console->gotoLigCol(m_tab[0][0].first, y); // On se place
    std::cout << "\e8";
    /*s_console->gotoLigCol(m_tab[0][0].first, y + 1); // On affiche la branche qui part en-dessous
    std::cout << "\xb3";
    s_console->gotoLigCol(m_tab[0][0].first, y + 2);
    std::cout << "\xc1"; // AFFICHAGE A MODIFIER SELON LE NOMBRE DE FILS*/
}


