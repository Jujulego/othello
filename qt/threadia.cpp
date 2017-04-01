// Importations
#include <iostream>
#include <memory>

#include "othellier.h"
#include "threadia.h"

#include "src/ia.h"

// Constructeur
ThreadIA::ThreadIA(std::shared_ptr<IA> ia) : m_ia(ia) {
}

// Slots
void ThreadIA::lancer(Othellier* o) {
    std::cout << "Yo !" << std::endl;
    emit fini(m_ia->jouer(o->get_etat()));
}

// Accesseurs
bool ThreadIA::ok() {
    return m_ia != nullptr;
}
