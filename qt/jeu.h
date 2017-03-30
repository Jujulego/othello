#ifndef FPRINCIPALE_H
#define FPRINCIPALE_H

// Importations
#include <QMainWindow>
#include <QLabel>

#include "othellier.h"
#include "pion.h"
#include "src/pion.h"

// Classe
class FPrincipale : public QMainWindow {
    Q_OBJECT

    private:
        // Attributes
        Othellier* m_othellier;
        QLabel* m_status_joueur;
        QLabel* m_status_scores;

    public:
        // Constructeur
        explicit FPrincipale(QWidget *parent = nullptr);

    signals:

    public slots:
        // Slots
        void fin_jeu(COULEUR gagnant);
        void chg_joueur(COULEUR joueur);
        void chg_score(int blanc, int noir);
};

#endif // FPRINCIPALE_H
