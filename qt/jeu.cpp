// Dépendances
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QShortcut>
#include <QStatusBar>
#include <QMessageBox>

#include <memory>

#include "jeu.h"
#include "othellier.h"
#include "pion.h"

#include "src/randomia.h"

// Constructeur
Jeu::Jeu(QWidget *parent) : QMainWindow(parent) {
    // Création de l'othellier
    m_othellier = new Othellier(std::shared_ptr<IA>(new RandomIA), this);
    setCentralWidget(m_othellier);
    setMinimumSize(TAILLE_CASE*8 + 3, TAILLE_CASE*8 + 25);
    connect(m_othellier, &Othellier::fin, this, &Jeu::fin_jeu);

    // Actions
    QAction* action_recommencer = new QAction("Recommencer", this);
    action_recommencer->setShortcuts(QKeySequence::Refresh);
    action_recommencer->setIcon(QIcon::fromTheme("view-refresh"));
    connect(action_recommencer, &QAction::triggered, m_othellier, &Othellier::reset);
    addAction(action_recommencer);

    QAction* action_annuler = new QAction("Annuler", this);
    action_annuler->setShortcuts(QKeySequence::Undo);
    action_annuler->setIcon(QIcon::fromTheme("edit-undo"));
    connect(action_annuler, &QAction::triggered, m_othellier, &Othellier::annuler);
    addAction(action_annuler);

    // Menus
    QMenu* menu_jouer = menuBar()->addMenu("&Jouer");
    menu_jouer->addAction(action_annuler);
    menu_jouer->addAction(action_recommencer);

    // Status bar
    m_status_joueur = new QLabel(this);
    m_status_joueur->setText("Au tour du joueur blanc");
    statusBar()->addWidget(m_status_joueur);
    connect(m_othellier, &Othellier::chg_joueur, this, &Jeu::chg_joueur);

    m_status_scores = new QLabel(this);
    m_status_scores->setText("Blanc : 2   Noir : 2");
    statusBar()->addPermanentWidget(m_status_scores);
    connect(m_othellier, &Othellier::chg_scores, this, &Jeu::chg_score);
}

// Slots
void Jeu::fin_jeu(COULEUR gagnant) {
    QMessageBox::information(this, "Victoire !", ((gagnant == BLANC) ? "Blanc" : "Noir") + (QString) " à gagné !!!\n" +
                         (QString) "Score final : Blanc : " + QString(std::to_string(m_othellier->score_blanc()).c_str()) +
                                              "   Noir : "  + QString(std::to_string(m_othellier->score_noir()).c_str()));
    m_othellier->reset();
}

void Jeu::chg_joueur(COULEUR joueur) {
    m_status_joueur->setText((QString) "Au tour du joueur " + ((joueur == BLANC) ? "blanc" : "noir"));
}

void Jeu::chg_score(int blanc, int noir) {
    m_status_scores->setText((QString) "Blanc : " + QString(std::to_string(blanc).c_str()) +
                                    "   Noir : "  + QString(std::to_string(noir).c_str()));
}
