// Dépendances
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
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

#include "src/minmaxia.h"
#include "src/randomia.h"

// Constructeur
Jeu::Jeu(QWidget *parent) : QMainWindow(parent) {
    // Paramètres fenêtre
    setMinimumSize(TAILLE_CASE*9 + 3, TAILLE_CASE*9 + 25);

    // Création du menu
    init_menu();

    // Actions
    m_act_annuler = new QAction("Annuler", this);
    m_act_annuler->setShortcuts(QKeySequence::Undo);
    m_act_annuler->setIcon(QIcon::fromTheme("edit-undo"));
    m_act_annuler->setDisabled(true);
    addAction(m_act_annuler);

    m_act_recommencer = new QAction("Recommencer", this);
    m_act_recommencer->setShortcuts(QKeySequence::Refresh);
    m_act_recommencer->setIcon(QIcon::fromTheme("view-refresh"));
    m_act_recommencer->setDisabled(true);
    addAction(m_act_recommencer);

    m_act_quitter = new QAction("Quitter", this);
    m_act_quitter->setShortcuts(QKeySequence::Close);
    connect(m_act_quitter, &QAction::triggered, this, &Jeu::close);
    addAction(m_act_quitter);

    // Menus
    QMenu* menu_jouer = menuBar()->addMenu("&Jouer");
    menu_jouer->addAction(m_act_annuler);
    menu_jouer->addAction(m_act_recommencer);
    menu_jouer->addSeparator();
    menu_jouer->addAction(m_act_quitter);

    // Status bar
    m_status_joueur = new QLabel(this);
    m_status_scores = new QLabel(this);
    chg_score(0, 0);
    statusBar()->addPermanentWidget(m_status_scores);
}

void Jeu::init_menu() {
    // Création du menu
    m_wid_menu = new QWidget(this);
    QVBoxLayout* layout_menu = new QVBoxLayout(m_wid_menu);

    QPushButton* btn_jouer = new QPushButton("Joueur1 Vs Joueur2");
    connect(btn_jouer, &QPushButton::clicked, this, &Jeu::btn_jouer);
    layout_menu->addWidget(btn_jouer);

    QPushButton* btn_jouer_iar = new QPushButton("Joueur Vs Random");
    connect(btn_jouer_iar, &QPushButton::clicked, this, &Jeu::btn_jouer_iar);
    layout_menu->addWidget(btn_jouer_iar);

    QPushButton* btn_jouer_iamm = new QPushButton("Joueur Vs MinMax");
    connect(btn_jouer_iamm, &QPushButton::clicked, this, &Jeu::btn_jouer_iamm);
    layout_menu->addWidget(btn_jouer_iamm);

    // Ajout du menu
    m_wid_menu->setLayout(layout_menu);
    setCentralWidget(m_wid_menu);
}

void Jeu::connect_othellier() {
    // Déconnexion
    disconnect(m_act_quitter, &QAction::triggered, this, &Jeu::close);

    // Connection !
    connect(m_othellier, &Othellier::fin, this, &Jeu::fin_jeu);
    connect(m_othellier, &Othellier::chg_joueur, this, &Jeu::chg_joueur);
    connect(m_othellier, &Othellier::chg_scores, this, &Jeu::chg_score);
    connect(m_act_annuler, &QAction::triggered, m_othellier, &Othellier::annuler);
    connect(m_act_recommencer, &QAction::triggered, m_othellier, &Othellier::reset);
    connect(m_act_quitter, &QAction::triggered, this, &Jeu::retour_menu);

    // Ajout à la fenêtre
    setCentralWidget(m_othellier);
    m_wid_menu = nullptr;

    // Activation des actions
    m_act_recommencer->setEnabled(true);
    m_act_annuler->setEnabled(true);

    // Status !
    chg_score(2, 2);
    m_status_joueur->setText("Au tour du joueur blanc");
    statusBar()->addWidget(m_status_joueur);
}

// Slots
void Jeu::btn_jouer() {
    // Création de l'othellier
    m_othellier = new Othellier();
    connect_othellier();
}

void Jeu::btn_jouer_iar() {
    // Création de l'othellier
    m_othellier = new Othellier(std::shared_ptr<IA>(new RandomIA));
    connect_othellier();
}

void Jeu::btn_jouer_iamm() {
    // Création de l'othellier
    m_othellier = new Othellier(std::shared_ptr<IA>(new MinMaxIA(3)));
    connect_othellier();
}

void Jeu::retour_menu() {
    // Deconnexions !
    disconnect(m_othellier, &Othellier::fin, this, &Jeu::fin_jeu);
    disconnect(m_othellier, &Othellier::chg_joueur, this, &Jeu::chg_joueur);
    disconnect(m_othellier, &Othellier::chg_scores, this, &Jeu::chg_score);
    disconnect(m_act_annuler, &QAction::triggered, m_othellier, &Othellier::annuler);
    disconnect(m_act_recommencer, &QAction::triggered, m_othellier, &Othellier::reset);
    disconnect(m_act_quitter, &QAction::triggered, this, &Jeu::retour_menu);

    // Connection !
    connect(m_act_quitter, &QAction::triggered, this, &Jeu::close);

    // Retour au menu
    init_menu();
    m_othellier = nullptr;

    // Vidage de la status bar
    statusBar()->removeWidget(m_status_joueur);
}

void Jeu::fin_jeu(COULEUR gagnant) {
    QMessageBox::information(this, "Victoire !", ((gagnant == BLANC) ? "Blanc" : "Noir") + (QString) " à gagné !!!\n" +
                         (QString) "Score final : Blanc : " + QString(std::to_string(m_othellier->score_blanc()).c_str()) +
                                              "   Noir : "  + QString(std::to_string(m_othellier->score_noir()).c_str()));
    retour_menu();
}

void Jeu::chg_joueur(COULEUR joueur) {
    m_status_joueur->setText((QString) "Au tour du joueur " + ((joueur == BLANC) ? "blanc" : "noir"));
}

void Jeu::chg_score(int blanc, int noir) {
    m_status_scores->setText((QString) "Blanc : " + QString(std::to_string(blanc).c_str()) +
                                    "   Noir : "  + QString(std::to_string(noir).c_str()));
}
