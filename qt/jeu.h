#ifndef FPRINCIPALE_H
#define FPRINCIPALE_H

// Importations
#include <QMainWindow>
#include <QLabel>

#include "othellier.h"
#include "pion.h"
#include "src/memia.h"
#include "src/pion.h"

// Classe
class Jeu : public QMainWindow {
    Q_OBJECT

    private:
        // Attributes
        QWidget* m_wid_menu;
        Othellier* m_othellier;

        QAction* m_act_annuler;
        QAction* m_act_recommencer;
        QAction* m_act_quitter;

        QLabel* m_status_joueur;
        QLabel* m_status_scores;

        std::shared_ptr<MemIA> m_memia_a;
        COULEUR m_couleur_memia_a = VIDE;

        std::shared_ptr<MemIA> m_memia_b;
        COULEUR m_couleur_memia_b = VIDE;
        bool jouer_infini = false;

        // Méthodes
        void init_menu();
        void connect_othellier();

    public:
        // Constructeur
        explicit Jeu(QWidget *parent = nullptr);

    signals:

    private slots:
        // Slots
        void btn_jouer();
        void btn_jouer_iar();
        void btn_jouer_iamm();
        void btn_jouer_iaab();
        void btn_jouer_ianm();
        void btn_jouer_iami();
        void btn_jouer_iaia();

        void retour_menu();

    public slots:
        // Slots
        void fin_jeu(COULEUR gagnant);
        void chg_joueur(COULEUR joueur);
        void chg_score(int blanc, int noir);
};

#endif // FPRINCIPALE_H
