// Imporations
#include <cerrno>
#include <cstring>
#include <functional>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <cstdlib>

#include "memarbre.h"

// Fonctions
bool getline(std::fstream& f, std::string& buf) {
	// Gestion des erreurs
	auto mask = f.exceptions();
	f.exceptions(std::ios::goodbit);

	// Lecture
	bool ok = bool(std::getline(f, buf));

	// Remise du mask original
	f.clear();
	f.exceptions(mask);

	return ok;
}

// Constructeurs
MemArbre::Noeud::Noeud(int val, std::tuple<int,int> const& coords, int pos, std::shared_ptr<MemArbre> const& arbre)
	: m_val(val), m_pos(pos), m_coords(coords), m_arbre(arbre) {
}

MemArbre::Noeud::Noeud(int val, std::tuple<int,int> const& coords, int pos, std::shared_ptr<MemArbre> const& arbre, std::shared_ptr<MemArbre::Noeud> const& pere)
	: m_val(val), m_pos(pos), m_coords(coords), m_pere(pere), m_arbre(arbre) {
}

// Méthodes
std::weak_ptr<MemArbre::Noeud> MemArbre::Noeud::weak_from_this() {
	return std::weak_ptr<MemArbre::Noeud>(shared_from_this());
}

std::ostream& MemArbre::Noeud::afficher(std::ostream& stream) const {
	if (m_pere.expired())
        return stream << "ra " << (char) (std::get<0>(m_coords) + 'A') << (std::get<1>(m_coords) + 1) << " " << val();
    return stream << (char) (std::get<0>(pere()->coords()) + 'A') << (std::get<1>(pere()->coords()) + 1) << " " << (char) (std::get<0>(m_coords) + 'A') << (std::get<1>(m_coords) + 1) << " " << val();
}

void MemArbre::Noeud::add_fils(std::shared_ptr<MemArbre::Noeud> const& fils) {
	// Création du noeud
	m_fils.insert(fils);
}

std::shared_ptr<MemArbre::Noeud> MemArbre::Noeud::add_fils(int val, std::tuple<int,int> const& coords) {
	// Création du noeud
	auto n = std::make_shared<MemArbre::Noeud>(val, coords, -1, arbre(), shared_from_this());
	m_fils.insert(n);

	// Sauvegarde dans l'arbre
	arbre()->save(n);

	return n;
}

void MemArbre::Noeud::save() {
	// Génération de la nouvelle ligne
	std::ostringstream data(std::ostringstream::ate);

	// L'adresse du pere
	data << (m_pere.expired() ? -1 : pere()->pos());

	// Les coordonnees
	data << " " << (char) (std::get<0>(m_coords) + 'A') << (std::get<1>(m_coords) + 1) << " ";

	// La valeur
    data << m_val;

	// Envoi vers le fichier !
	arbre()->save(m_pos, data.str());
}

bool MemArbre::Noeud::est_racine() const {
	return m_pere.expired();
}

// Accesseurs
int MemArbre::Noeud::val() const {
    // Calcul !
    int val = m_val;

    if (!m_fils.empty()) {
        for (auto f : m_fils) val += f->val();
    }

    return val;
}

void MemArbre::Noeud::val(int val) {
    // Calcul !
    if (!m_fils.empty()) {
        for (auto f : m_fils) val -= f->val();
    }

    m_val = val;
}

int const& MemArbre::Noeud::pos() const {
	return std::cref(m_pos);
}

std::tuple<int,int>& MemArbre::Noeud::coords() {
	return std::ref(m_coords);
}

std::shared_ptr<MemArbre::Noeud> MemArbre::Noeud::pere() const {
	return std::shared_ptr<MemArbre::Noeud>(m_pere);
}

std::shared_ptr<MemArbre> MemArbre::Noeud::arbre() const {
	return std::shared_ptr<MemArbre>(m_arbre);
}

std::set<std::shared_ptr<MemArbre::Noeud>> const& MemArbre::Noeud::fils() const {
	return std::cref(m_fils);
}

// Constructeur
MemArbre::MemArbre(std::string const& fichier) {
	// Ouverture du fichier !
    m_fichier.open(fichier, std::ios_base::in | std::ios_base::out | std::ios_base::binary);

    while (m_fichier.fail()) {
        // Uniquement si le fichier n'existe pas
        if (errno != ENOENT) {
            std::cerr << "Impossible d'ouvrir le fichier : " << strerror(errno) << std::endl;
            std::abort();
        }

        // Création du fichier
        std::ofstream of(fichier);
        of.close();

        // 2eme tentative
        m_fichier.clear();
        m_fichier.open(fichier);
    }

    // Exception en cas d'erreur
    m_fichier.exceptions(std::ios_base::failbit | std::ios_base::badbit);
}

// Destructeur
MemArbre::~MemArbre() {
	m_fichier.close();
}

// Méthodes
void MemArbre::charger() {
	// Lecture !
	int pos = m_fichier.tellg(), pere = -1, val = 0;
	std::string coords, buf;

	while (getline(m_fichier, buf)) {
		// Analyse !
		std::istringstream s(buf);

		// Extraction des valeurs
		s >> pere;
		s >> coords;
		s >> val;

		// Création du noeud
		std::shared_ptr<MemArbre::Noeud> n;
		if (pere == -1) {
			n = std::make_shared<MemArbre::Noeud>(
				val,
				std::make_tuple((int) (coords[0] - 'A'), (int) (coords[1] - '1')),
				pos,
				shared_from_this()
			);
        } else {
			n = std::make_shared<MemArbre::Noeud>(
				val,
				std::make_tuple((int) (coords[0] - 'A'), (int) (coords[1] - '1')),
				pos,
				shared_from_this(),
                m_noeuds.at(pere)
            );
            m_noeuds.at(pere)->add_fils(n);
		}

		m_noeuds[pos] = n;

		// Position du suivant !
		pos = m_fichier.tellg();
	}
}

void MemArbre::save(int& pos, std::string const& data) {
	// Déclarations
	std::string buf;
	std::vector<std::string> lignes(1, data);

	// pos == -1 => pas de ligne à changer mais une à rajouter
	if (pos == -1) {
		m_fichier.seekg(0, m_fichier.end);
		pos = m_fichier.tellg();
	} else {
		// Lecture de la suite du fichier : après la ligne à modifier
		m_fichier.seekg(pos, m_fichier.beg);
		getline(m_fichier, buf);

		while (getline(m_fichier, buf)) lignes.push_back(buf);

		// Retour à la ligne à changer
		m_fichier.seekg(pos, m_fichier.beg);
	}

	// Modification !
	for (auto l : lignes) m_fichier << l << std::endl;
}

void MemArbre::save(std::shared_ptr<MemArbre::Noeud> const& n) {
	// Enregistrement
	n->save();
	m_noeuds[n->pos()] = n;
}

std::shared_ptr<MemArbre::Noeud> MemArbre::add_racine(int val, std::tuple<int,int> const& coords) {
	// Création du noeud
    auto n = std::make_shared<MemArbre::Noeud>(val, coords, -1, shared_from_this(), nullptr);

	// Sauvegarde dans l'arbre
    save(n);

	return n;
}

std::set<std::shared_ptr<MemArbre::Noeud>> MemArbre::racines() const {
	// Déclarations
	std::set<std::shared_ptr<MemArbre::Noeud>> racines;

	// Parcours de la liste
	for (auto p : *this) {
		if (p.second->est_racine()) racines.insert(p.second);
	}

	return racines;
}

MemArbre::iterateur MemArbre::begin() const {
	return m_noeuds.cbegin();
}

MemArbre::iterateur MemArbre::end() const {
	return m_noeuds.cend();
}

std::shared_ptr<MemArbre::Noeud> MemArbre::noeud(int pos) const {
	if (pos == -1) return nullptr;
	return m_noeuds.at(pos);
}

// Opérateurs externes
std::ostream& operator << (std::ostream& stream, MemArbre::Noeud const& n) {
	return n.afficher(stream);
}
