#ifndef OTHELLIER_H
#define OTHELLIER_H

// Dépendances
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>

#include <QThread>

#include <memory>
#include <stack>
#include <vector>

#include "pion.h"
#include "threadia.h"

#include "src/etat.h"
#include "src/ia.h"
#include "src/pion.h"

// Classe
class Othellier : public QGraphicsView {
    Q_OBJECT

    private:
        // Attributs
        int m_score_blanc = 0;
        int m_score_noir = 0;

        COULEUR m_joueur = NOIR;
        std::vector<std::vector<GPion*>> m_pions;
        std::stack<Etat> m_historique;

        QTimer* m_timer_ia;
        QThread m_thread_ia;
        ThreadIA m_ia;

        // Méthodes
        bool test_ia();

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
        void start_ia(Othellier*);
        void chg_joueur(COULEUR joueur);
        void chg_scores(int blanc, int noir);

    private slots:
        // Slots
        void exec_coup(Pion const& p);
        void jouer();

    public slots:
        // Slots
        void reset();
        void reset_affichage();
        void annuler();
        void quitter();
};

#endif // OTHELLIER_H
