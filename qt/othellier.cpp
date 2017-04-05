// Importations
#include <QtMath>

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPoint>
#include <QTimer>

#include <QThread>

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
    setScene(new QGraphicsScene(this));
    connect(scene(), SIGNAL(selectionChanged()), this, SLOT(jouer()));

    // Ajout des cases
    m_pions = std::vector<std::vector<GPion*>>(8, std::vector<GPion*>(8, nullptr));
    reset();

    // Préparation Thread IA
    m_ia.moveToThread(&m_thread_ia);
    connect(this, SIGNAL(start_ia(Othellier*)), &m_ia, SLOT(lancer(Othellier*)));
    connect(&m_ia, SIGNAL(fini(Pion)), this, SLOT(exec_coup(Pion)));
    m_thread_ia.start();
}

// Méthodes
bool Othellier::test_ia() {
    return (m_joueur == BLANC) && m_ia.ok();
}

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
        if (test_fin()) {
            emit fin((m_score_noir >= m_score_blanc) ? NOIR : BLANC);
            return;
        }

        // Exec IA
        if (test_ia()) emit start_ia(this);
    }
}

Etat Othellier::get_etat() const {
    // Init
    Etat etat;
    etat.joueur = m_joueur;
    etat.scores[NOIR] = m_score_noir;
    etat.scores[BLANC] = m_score_blanc;

    // Ajout des couleurs
    etat.othellier = std::vector<std::vector<COULEUR>>(8, std::vector<COULEUR>(8, VIDE));
    COULEUR c;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            c = m_pions[i][j]->couleur();

            // Ajout matrice
            etat.othellier[i][j] = c;
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

    // Affichage !
    reset_affichage();

    // Les cases
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_pions[i][j] = new GPion(QPoint(i, j), etat.othellier[i][j]);
            scene()->addItem(m_pions[i][j]);
        }
    }
}

std::vector<GPion*> Othellier::test_pos(QPoint pos) const {
    // Initialisation
    COULEUR ennemi = (m_joueur == BLANC) ? NOIR : BLANC;
    std::vector<GPion*> pions, tmp;
    bool ok = false;

    // Recherche dans les 8 directions
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
    if (test_ia()) return;

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

void Othellier::reset() {
    // Arrêt des calculs
    m_thread_ia.quit();
    m_thread_ia.start();

    // Vidage de l'historique
    m_historique = std::stack<Etat>();

    // Joueur !
    m_joueur = NOIR;
    emit chg_joueur(m_joueur);

    // Scores
    m_score_blanc = 2;
    m_score_noir = 2;
    emit chg_scores(m_score_blanc, m_score_noir);

    // Affichage !
    reset_affichage();

    // Pions de départ
    m_pions[3][3]->couleur(BLANC);
    m_pions[4][4]->couleur(BLANC);
    m_pions[3][4]->couleur(NOIR);
    m_pions[4][3]->couleur(NOIR);
}

void Othellier::reset_affichage() {
    // Vidage de la scene
    scene()->clear();

    // Ajout des cases et des indices autour
    static std::vector<QString> lettres  = {"A", "B", "C", "D", "E", "F", "G", "H"};
    static std::vector<QString> chiffres = {"1", "2", "3", "4", "5", "6", "7", "8"};
    QGraphicsTextItem* qti;

    for (int i = 0; i < 8; i++) {
        // Les cases
        for (int j = 0; j < 8; j++) {
            m_pions[i][j] = new GPion(QPoint(i, j));
            scene()->addItem(m_pions[i][j]);
        }

        // Au dessus ...
        qti = new QGraphicsTextItem(lettres[i]);
        qti->setPos((i - 0.2)*TAILLE_CASE, -TAILLE_CASE);
        scene()->addItem(qti);

        // ... et en dessous !
        qti = new QGraphicsTextItem(lettres[i]);
        qti->setPos((i - 0.2)*TAILLE_CASE, 7.5*TAILLE_CASE);
        scene()->addItem(qti);

        // A gauche ...
        qti = new QGraphicsTextItem(chiffres[i]);
        qti->setPos(-TAILLE_CASE, (i - 0.2)*TAILLE_CASE);
        scene()->addItem(qti);

        // ... et a droite !
        qti = new QGraphicsTextItem(chiffres[i]);
        qti->setPos(7.6*TAILLE_CASE, (i - 0.2)*TAILLE_CASE);
        scene()->addItem(qti);
    }
}

void Othellier::annuler() {
    // Gradien
    if (m_historique.empty()) return;

    // Retour en arrière ! (2 fois en cas d'IA)
    if (m_ia.ok() && m_joueur != BLANC) m_historique.pop();
    set_etat(m_historique.top());
    m_historique.pop();
}

void Othellier::quitter() {
    m_thread_ia.quit();
}

// Accesseurs
int Othellier::score_blanc() const {
    return m_score_blanc;
}

int Othellier::score_noir() const {
    return m_score_noir;
}
