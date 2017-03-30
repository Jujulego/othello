#ifndef OTHELLIER_H
#define OTHELLIER_H

// Dépendances
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <memory>
#include <stack>
#include <vector>

#include "etat.h"
#include "pion.h"
#include "src/ia.h"

// Classe
class Othellier : public QGraphicsView {
    Q_OBJECT

    private:
        // Attributs
        int m_score_blanc = 0;
        int m_score_noir = 0;

        COULEUR m_joueur = BLANC;
        std::vector<std::vector<GPion*>> m_pions;
        std::stack<Etat> m_historique;

        std::shared_ptr<IA> m_ia;

        // Méthodes
        void exec_coup(Pion const& p);

    public:
        // Constructeur
        Othellier(std::shared_ptr<IA> ia = nullptr, QWidget* parent = nullptr);

        // Méthodes
        Etat get_etat() const;
        void set_etat(Etat const& etat);

        bool test_fin() const;
        std::vector<GPion*> test_pos(QPoint pos) const;

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
        void jouer_ia();

    public slots:
        // Slots
        void reset();
        void annuler();
};

#endif // OTHELLIER_H
