#ifndef FPRINCIPALE_H
#define FPRINCIPALE_H

// Importations
#include <QMainWindow>
#include <QLabel>

#include "othellier.h"
#include "pion.h"
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
        void btn_jouer_iaia();

        void retour_menu();

    public slots:
        // Slots
        void fin_jeu(COULEUR gagnant);
        void chg_joueur(COULEUR joueur);
        void chg_score(int blanc, int noir);
};

#endif // FPRINCIPALE_H
