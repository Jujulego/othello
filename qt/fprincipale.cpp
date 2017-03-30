// Dépendances
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QShortcut>
#include <QStatusBar>
#include <QMessageBox>

#include "fprincipale.h"
#include "othellier.h"
#include "pion.h"

// Constructeur
FPrincipale::FPrincipale(QWidget *parent) : QMainWindow(parent) {
    // Création de l'othellier
    m_othellier = new Othellier(this);
    setCentralWidget(m_othellier);
    setMinimumSize(TAILLE_CASE*8 + 3, TAILLE_CASE*8 + 25);
    connect(m_othellier, &Othellier::fin, this, &FPrincipale::fin_jeu);

    // Actions
    QAction* action_recommencer = new QAction("Recommencer", this);
    action_recommencer->setShortcuts(QKeySequence::Refresh);
    action_recommencer->setIcon(QIcon::fromTheme("view-refresh"));
    connect(action_recommencer, &QAction::triggered, m_othellier, &Othellier::reset);
    addAction(action_recommencer);

    // Menus
    QMenu* menu_jouer = menuBar()->addMenu("&Jouer");
    menu_jouer->addAction(action_recommencer);

    // Status bar
    m_status_joueur = new QLabel(this);
    m_status_joueur->setText("Au tour du joueur blanc");
    statusBar()->addWidget(m_status_joueur);
    connect(m_othellier, &Othellier::chg_joueur, this, &FPrincipale::chg_joueur);

    m_status_scores = new QLabel(this);
    m_status_scores->setText("Blanc : 2   Noir : 2");
    statusBar()->addPermanentWidget(m_status_scores);
    connect(m_othellier, &Othellier::chg_scores, this, &FPrincipale::chg_score);
}

// Slots
void FPrincipale::fin_jeu(COULEUR gagnant) {
    QMessageBox::information(this, "Victoire !", ((gagnant == BLANC) ? "Blanc" : "Noir") + (QString) " à gagné !!!\n" +
                         (QString) "Score final : Blanc : " + QString(std::to_string(m_othellier->score_blanc()).c_str()) +
                                              "   Noir : "  + QString(std::to_string(m_othellier->score_noir()).c_str()));
    m_othellier->reset();
}

void FPrincipale::chg_joueur(COULEUR joueur) {
    m_status_joueur->setText((QString) "Au tour du joueur " + ((joueur == BLANC) ? "blanc" : "noir"));
}

void FPrincipale::chg_score(int blanc, int noir) {
    m_status_scores->setText((QString) "Blanc : " + QString(std::to_string(blanc).c_str()) +
                                    "   Noir : "  + QString(std::to_string(noir).c_str()));
}
