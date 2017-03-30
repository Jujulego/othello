// Importations
#include <QtMath>

#include <QWidget>
#include <QGraphicsScene>
#include <QPoint>

#include <functional>

#include "othellier.h"
#include "etat.h"

// Macros
#define ENTDIV(D, d) ((qFloor(D) - (qFloor(D) % qFloor(d))) / qFloor(d))

// Constantes
static const std::vector<std::function<void(int&,int&)>> DIRECTIONS = {
    [] (int& i, int& j) {i++; j=j;}, // DROITE
    [] (int& i, int& j) {i++; j++;}, // DROITE-BAS
    [] (int& i, int& j) {i=i; j++;}, // BAS
    [] (int& i, int& j) {i--; j++;}, // GAUCHE-BAS
    [] (int& i, int& j) {i--; j=j;}, // GAUCHE
    [] (int& i, int& j) {i--; j--;}, // GAUCHE-HAUT
    [] (int& i, int& j) {i=i; j--;}, // HAUT
    [] (int& i, int& j) {i++; j--;}  // DROITE-HAUT
};

// Constructeur
Othellier::Othellier(QWidget *parent) : QGraphicsView(parent) {
    // Préparation de la scène
    setScene(new QGraphicsScene(parent));
    connect(scene(), &QGraphicsScene::selectionChanged, this, &Othellier::jouer);

    // Ajout des cases
    reset();
}

// Méthodes
Etat Othellier::get_etat() const {
    // Init
    std::vector<std::vector<COULEUR>> mat;

    // Copie !
    for (int i = 0; i < 8; i++) {
        // Ajout d'un tableau
        mat.push_back(std::vector<COULEUR>());

        // Ajout des couleurs
        for (int j = 0; j < 8; j++) {
            mat[i].push_back(m_pions[i][j]->couleur());
        }
    }

    return {m_joueur, m_score_blanc, m_score_noir, mat};
}

std::vector<Pion*> Othellier::test_pos(QPoint pos) const {
    COULEUR ennemi = (m_joueur == BLANC) ? NOIR : BLANC;
    std::vector<Pion*> pions, tmp;
    bool ok = false;

    for (std::function<void(int&,int&)> f : DIRECTIONS) {
        // Init
        tmp.clear();
        ok = false;

        // Recherche de pions à retourner
        for (int i = pos.x(), j = pos.y(); (i < 8) && (j < 8) && (i >= 0) && (j >= 0); f(i, j)) {
            // Première boucle :
            if (QPoint(i, j) == pos) continue;

            // Action :
            if (m_pions[i][j]->couleur() == ennemi) {
                // Sélection ou ...
                tmp.push_back(m_pions[i][j]);
            } else {
                // Confirmation !
                if (m_pions[i][j]->couleur() == m_joueur) ok = true;
                break;
            }
        }

        // Ajout au tableau général
        if (ok) pions.insert(pions.end(), tmp.begin(), tmp.end());
    }

    return pions;
}

bool Othellier::test_fin() const {
    // Parcours du tableau
    bool fin = true;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            // Seulement les cases vides !
            if (m_pions[x][y]->couleur() != VIDE) continue;

            // C'est pas fini !
            if (test_pos(QPoint(x, y)).size() > 0) {
                fin = false;
                break;
            }
        }

        // Fini !
        if (!fin) break;
    }

    return fin;
}

// Slots
void Othellier::jouer() {
    // Gardien déselection
    if (scene()->selectedItems().size() == 0) return;

    // Récupération du pion sélectionné
    Pion* pion = (Pion*) scene()->selectedItems()[0];

    // Changement de couleur !
    if (pion->couleur() == VIDE) {
        // Cascade !
        auto pions = test_pos(QPoint(ENTDIV(pion->pos().x(), TAILLE_CASE), ENTDIV(pion->pos().y(), TAILLE_CASE)));
        int nb = pions.size();

        // Mouvement valide
        if (nb > 0) {
            // On retourne les pions
            for (auto p : pions) p->couleur(m_joueur);

            // Maj scores
            if (m_joueur == BLANC) {
                m_score_blanc += nb + 1;
                m_score_noir  -= nb;
            } else {
                m_score_noir  += nb + 1;
                m_score_blanc -= nb;
            }
            emit chg_scores(m_score_blanc, m_score_noir);

            // Changement de joueur
            pion->couleur(m_joueur);
            m_joueur = (m_joueur == BLANC) ? NOIR : BLANC;
            emit chg_joueur(m_joueur);

            // Test de fin
            if (test_fin()) emit fin(m_joueur);
        }
    } else {
        // Test de fin
        if (test_fin()) emit fin(m_joueur);
    }
}

void Othellier::reset() {
    // Vidage de la scene
    scene()->clear();

    // Vidage de l'historique
    m_historique = std::stack<Etat>();

    // Joueur !
    m_joueur = BLANC;
    emit chg_joueur(m_joueur);

    // Scores
    m_score_blanc = 2;
    m_score_noir = 2;
    emit chg_scores(m_score_blanc, m_score_noir);

    // Ajout des cases
    m_pions = std::vector<std::vector<Pion*>>(8, std::vector<Pion*>(8, nullptr));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_pions[i][j] = new Pion(QPoint(i, j));
            scene()->addItem(m_pions[i][j]);
        }
    }

    // Pions de départ
    m_pions[3][3]->couleur(BLANC);
    m_pions[4][4]->couleur(BLANC);
    m_pions[3][4]->couleur(NOIR);
    m_pions[4][3]->couleur(NOIR);
}

// Accesseurs
int Othellier::score_blanc() const {
    return m_score_blanc;
}

int Othellier::score_noir() const {
    return m_score_noir;
}
