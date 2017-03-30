// Importations
#include <QtMath>

#include <QWidget>
#include <QGraphicsScene>
#include <QPoint>

#include <functional>
#include <memory>

#include "othellier.h"
#include "etat.h"
#include "pion.h"

#include "src/ia.h"

// Macros
#define ENTDIV(D, d) ((qFloor(D) - (qFloor(D) % qFloor(d))) / qFloor(d))

// Constructeur
Othellier::Othellier(std::shared_ptr<IA> ia, QWidget *parent) : QGraphicsView(parent), m_ia(ia) {
    // Préparation de la scène
    setScene(new QGraphicsScene(parent));
    connect(scene(), &QGraphicsScene::selectionChanged, this, &Othellier::jouer);

    // Ajout des cases
    m_pions = std::vector<std::vector<GPion*>>(8, std::vector<GPion*>(8, nullptr));
    reset();
}

// Méthodes
void Othellier::exec_coup(Pion const&p) {
    // Cascade !
    auto pions = test_pos(QPoint(p.x, p.y));
    int nb = pions.size();

    // Mouvement valide
    if (nb > 0) {
        // Sauvegarde dans l'historique
        m_historique.push(get_etat());

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
        m_pions[p.x][p.y]->couleur(m_joueur);
        m_joueur = (m_joueur == BLANC) ? NOIR : BLANC;
        emit chg_joueur(m_joueur);

        // Test de fin
        if (test_fin()) emit fin((m_score_noir >= m_score_blanc) ? NOIR : BLANC);

        // Exec IA
        if ((m_ia != nullptr) && (m_joueur == NOIR)) jouer_ia();
    }
}

Etat Othellier::get_etat() const {
    // Init
    Etat etat;
    etat.joueur = m_joueur;
    etat.scores[NOIR] = m_score_noir;
    etat.scores[BLANC] = m_score_blanc;

    // Ajout des couleurs
    COULEUR c;
    for (int i = 0; i < 8; i++) {
        etat.othellier.push_back(std::vector<COULEUR>());

        for (int j = 0; j < 8; j++) {
            c = m_pions[i][j]->couleur();

            // Ajout matrice
            etat.othellier[i].push_back(c);

            // Ajout aux tableaux / joueurs
            if (c == VIDE) continue;
            etat.pions[c].push_back({i, j, c});
        }
    }

    return etat;
}

void Othellier::set_etat(Etat const& etat) {
    // Mise à jour du score
    m_score_blanc = etat.scores.at(BLANC);
    m_score_noir  = etat.scores.at(NOIR);
    emit chg_scores(m_score_blanc, m_score_noir);

    // Mise à jour joueur
    m_joueur = etat.joueur;
    emit chg_joueur(m_joueur);

    // Mise à jour du plateau
    scene()->clear();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_pions[i][j] = new GPion(QPoint(i, j), etat.othellier[i][j]);
            scene()->addItem(m_pions[i][j]);
        }
    }
}

std::vector<GPion*> Othellier::test_pos(QPoint pos) const {
    COULEUR ennemi = (m_joueur == BLANC) ? NOIR : BLANC;
    std::vector<GPion*> pions, tmp;
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
    // Gardien IA
    if ((m_ia != nullptr) && (m_joueur == NOIR)) return;

    // Gardien déselection
    if (scene()->selectedItems().size() == 0) return;

    // Récupération du pion sélectionné
    GPion* pion = (GPion*) scene()->selectedItems()[0];

    // Changement de couleur !
    if (pion->couleur() == VIDE) {
        Pion p = {ENTDIV(pion->pos().x(), TAILLE_CASE), ENTDIV(pion->pos().y(), TAILLE_CASE), m_joueur};
        exec_coup(p);
    }
}

void Othellier::jouer_ia() {
    exec_coup(m_ia->jouer(get_etat()));
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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_pions[i][j] = new GPion(QPoint(i, j));
            scene()->addItem(m_pions[i][j]);
        }
    }

    // Pions de départ
    m_pions[3][3]->couleur(BLANC);
    m_pions[4][4]->couleur(BLANC);
    m_pions[3][4]->couleur(NOIR);
    m_pions[4][3]->couleur(NOIR);
}

void Othellier::annuler() {
    // Gradien
    if (m_historique.empty()) return;

    // Retour en arrière !
    set_etat(m_historique.top());
    m_historique.pop();
}

// Accesseurs
int Othellier::score_blanc() const {
    return m_score_blanc;
}

int Othellier::score_noir() const {
    return m_score_noir;
}
