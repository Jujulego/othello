#ifndef OTHELLIER_H
#define OTHELLIER_H

// Dépendances
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <stack>
#include <vector>

#include "etat.h"
#include "pion.h"

// Classe
class Othellier : public QGraphicsView {
    Q_OBJECT

    private:
        // Attributs
        int m_score_blanc = 0;
        int m_score_noir = 0;

        COULEUR m_joueur = BLANC;
        std::vector<std::vector<Pion*>> m_pions;
        std::stack<Etat> m_historique;

    public:
        // Constructeur
        Othellier(QWidget* parent = nullptr);

        // Méthodes
        Etat get_etat() const;
        bool test_fin() const;
        std::vector<Pion*> test_pos(QPoint pos) const;

        // Accesseurs
        int score_blanc() const;
        int score_noir() const;

    signals:
        // Signaux
        void fin(COULEUR gagnant);
        void chg_joueur(COULEUR joueur);
        void chg_scores(int blanc, int noir);

    private slots:
        // Slots
        void jouer();

    public slots:
        // Slots
        void reset();
};

#endif // OTHELLIER_H
