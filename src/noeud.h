#ifndef ARBRE_H
#define ARBRE_H

// Dépendances
#include <functional>
#include <memory>
#include <vector>

// Classe
template<class T>
class Noeud : public std::enable_shared_from_this<Noeud<T>> {
    private:
        // Attributs
        T m_val;
        std::weak_ptr<Noeud<T>> m_pere;
        std::vector<std::shared_ptr<Noeud<T>>> m_fils;

        // Méthodes
        std::weak_ptr<Noeud<T>> weak_from_this() {
            return std::weak_ptr<Noeud<T>>(std::enable_shared_from_this<Noeud<T>>::shared_from_this());
        }

    public:
        // Constructeur
        Noeud(T const& val, std::weak_ptr<Noeud<T>> const& pere) : m_val(val), m_pere(pere) {
        }

        // Méthodes statiques
        static std::shared_ptr<Noeud<T>> creer(T const& val) {
            return std::make_shared<Noeud<T>>(val, std::weak_ptr<Noeud<T>>());
        }

        // Opérateurs
        Noeud<T> operator [] (int i) {
            return fils(i);
        }

        // Méthodes
        std::shared_ptr<Noeud<T>> add_fils(T const& val) {
            // Création du noeud !
            std::shared_ptr<Noeud<T>> pt = std::make_shared<Noeud<T>>(val, weak_from_this());
            m_fils.push_back(pt);
            return pt; // ref sur le dernier !
        }

        std::shared_ptr<Noeud<T>> fils(int i) {
            return m_fils[i];
        }

        // Accesseurs
        std::shared_ptr<Noeud<T>> pere() {
            return m_pere;
        }

        typename std::add_lvalue_reference<T>::type val() {
            return m_val;
        }

        unsigned size() const {
            return m_fils.size();
        }
};

#endif // ARBRE_H
