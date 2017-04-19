// Importations
#include <QTimer>

#include <cassert>
#include <memory>

#include "othellier.h"
#include "threadia.h"

#include "src/ia.h"

// Constructeurs
ThreadIA::ThreadIA(std::shared_ptr<IA> ia, COULEUR couleur) : m_ia(ia), m_couleur(couleur) {
}

ThreadIA::ThreadIA(ThreadIA const& thread_ia) : ThreadIA(thread_ia.m_ia, thread_ia.m_couleur) {
}

// Opérateurs
ThreadIA& ThreadIA::operator = (ThreadIA const& thread_ia) {
    m_ia = thread_ia.m_ia;
    m_couleur = thread_ia.m_couleur;

    return *this;
}

// Slots
void ThreadIA::lancer(Othellier* o) {
    // Gardien
    if (m_couleur != o->get_joueur()) return;
    assert(ok());

    // Stockage
    m_othellier = o;

    // Timer !
    //QTimer::singleShot(500, this, SLOT(exec()));
    exec();
}

void ThreadIA::exec() {
    // Execution !
    emit fini(m_ia->jouer(m_othellier->get_etat()));
}

// Accesseurs
bool ThreadIA::ok() {
    return m_ia != nullptr;
}
