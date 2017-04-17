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
    emit fini(m_ia->jouer(o->get_etat()));
    std::shared_ptr<Noeud<IA::PV>> a = m_ia->arbre();

    if (a)
        std::cout << "Arbre : " << a->size() << " enfants ! val=" << a->val().val << std::endl;
}

// Accesseurs
bool ThreadIA::ok() {
    return m_ia != nullptr;
}
