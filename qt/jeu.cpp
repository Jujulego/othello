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
#include <QTimer>
#include <QMessageBox>

#include <fstream>
#include <memory>

#include "jeu.h"
#include "othellier.h"
#include "pion.h"

#include "src/alphabetaia.h"
#include "src/memia.h"
#include "src/minmaxia.h"
#include "src/negamaxia.h"
#include "src/randomia.h"

// Macros
#define PROF_ALGO 5

// Constructeur
Jeu::Jeu(QWidget *parent) : QMainWindow(parent), m_memia_a(new MemIA("arbre_a.txt")), m_memia_b(new MemIA("arbre_b.txt")) {
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

    QPushButton* btn_jouer_iaab = new QPushButton("Joueur Vs AlphaBeta");
    connect(btn_jouer_iaab, &QPushButton::clicked, this, &Jeu::btn_jouer_iaab);
    layout_menu->addWidget(btn_jouer_iaab);

    QPushButton* btn_jouer_ianm = new QPushButton("Joueur Vs NegaMax");
    connect(btn_jouer_ianm, &QPushButton::clicked, this, &Jeu::btn_jouer_ianm);
    layout_menu->addWidget(btn_jouer_ianm);

    QPushButton* btn_jouer_iami = new QPushButton("Joueur Vs Mem");
    connect(btn_jouer_iami, &QPushButton::clicked, this, &Jeu::btn_jouer_iami);
    layout_menu->addWidget(btn_jouer_iami);

    QPushButton* btn_jouer_iaia = new QPushButton("Mem Vs Mem (infini)");
    connect(btn_jouer_iaia, &QPushButton::clicked, this, &Jeu::btn_jouer_iaia);
    layout_menu->addWidget(btn_jouer_iaia);

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
    m_status_joueur = new QLabel(this);
    m_status_joueur->setText("Au tour du joueur noir");
    statusBar()->addWidget(m_status_joueur);
}

// Slots
void Jeu::btn_jouer() {
    // Création de l'othellier
    m_othellier = new Othellier({
        {NOIR,  nullptr},
        {BLANC, nullptr}
    });
    connect_othellier();
}

void Jeu::btn_jouer_iar() {
    // Création de l'othellier
    m_othellier = new Othellier({
        {NOIR,  nullptr},
        {BLANC, std::shared_ptr<IA>(new RandomIA)}
    });
    connect_othellier();
}

void Jeu::btn_jouer_iamm() {
    // Création de l'othellier
    m_othellier = new Othellier({
        {NOIR,  nullptr},
        {BLANC, std::shared_ptr<IA>(new MinMaxIA(PROF_ALGO))}
    });
    connect_othellier();
}

void Jeu::btn_jouer_iaab() {
    // Création de l'othellier
    m_othellier = new Othellier({
        {NOIR,  nullptr},
        {BLANC, std::shared_ptr<IA>(new AlphaBetaIA(PROF_ALGO))}
    });
    connect_othellier();
}

void Jeu::btn_jouer_ianm() {
    // Création de l'othellier
    m_othellier = new Othellier({
        {NOIR,  nullptr},
        {BLANC, std::shared_ptr<IA>(new NegaMaxIA(PROF_ALGO))}
    });
    connect_othellier();
}

void Jeu::btn_jouer_iami() {
    // Création de l'othellier
    m_othellier = new Othellier({
        {NOIR,  nullptr},
        {BLANC, m_memia_a}
    });

    m_couleur_memia_a = BLANC;

    connect_othellier();
}

void Jeu::btn_jouer_iaia() {
    // Création de l'othellier
    m_othellier = new Othellier({
        {NOIR,  m_memia_a},
        {BLANC, m_memia_b}
    }, true);

    m_couleur_memia_a = NOIR;
    m_couleur_memia_b = BLANC;
    jouer_infini = true;

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
    m_othellier->quitter();
    init_menu();
    m_othellier = nullptr;

    // Vidage de la status bar
    statusBar()->removeWidget(m_status_joueur);
}

void Jeu::fin_jeu(COULEUR gagnant) {
    // MemIA A
    if (m_couleur_memia_a == gagnant) {
        m_memia_a->gagne();
    } else if (m_couleur_memia_a != VIDE) {
        m_memia_a->perdu();
    }
    m_couleur_memia_a = VIDE;

    // MemIA B
    if (m_couleur_memia_b == gagnant) {
        m_memia_b->gagne();
    } else if (m_couleur_memia_b != VIDE) {
        m_memia_b->perdu();
    }
    m_couleur_memia_b = VIDE;

    // Message
    if (!jouer_infini) {
        QMessageBox::information(this, "Victoire !", ((gagnant == BLANC) ? "Blanc" : "Noir") + (QString) " à gagné !!!\n" +
                             (QString) "Score final : Blanc : " + QString(std::to_string(m_othellier->score_blanc()).c_str()) +
                                                  "   Noir : "  + QString(std::to_string(m_othellier->score_noir()).c_str()));
    } else {
        // Log
        std::ofstream f("log.txt", std::ios_base::app | std::ios_base::out);
        f << ((gagnant == BLANC) ? "Blanc" : "Noir") << " à gagné !" << std::endl;
        f << "    Blanc : " << m_othellier->score_blanc() << std::endl;
        f << "    Noir  : " << m_othellier->score_noir() << std::endl;
        f << std::endl;

        f.close();

        // Petit temps ...
        QTimer::singleShot(1000, this, SLOT(btn_jouer_iaia()));
    }

    retour_menu();
}

void Jeu::chg_joueur(COULEUR joueur) {
    m_status_joueur->setText((QString) "Au tour du joueur " + ((joueur == BLANC) ? "blanc" : "noir"));
}

void Jeu::chg_score(int blanc, int noir) {
    m_status_scores->setText((QString) "Blanc : " + QString(std::to_string(blanc).c_str()) +
                                    "   Noir : "  + QString(std::to_string(noir).c_str()));
}
