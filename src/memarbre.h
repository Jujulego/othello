#ifndef __MEMARBRE
#define __MEMARBRE

// Imporations
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <tuple>

// Classe
class MemArbre : public std::enable_shared_from_this<MemArbre> {
	public:
		// Sous-classe
		class Noeud : public std::enable_shared_from_this<Noeud> {
			private:
				// Attributs
				int m_val, m_pos;
				std::tuple<int,int> m_coords;

				std::weak_ptr<Noeud> m_pere;
				std::set<std::shared_ptr<Noeud>> m_fils;
				std::weak_ptr<MemArbre> m_arbre;

				// Méthodes
				void add_fils(std::shared_ptr<MemArbre::Noeud> const& fils);

				friend class MemArbre;

			public:
				// Constructeurs
				Noeud(int val, std::tuple<int,int> const& coords, int pos, std::shared_ptr<MemArbre> const& arbre);
				Noeud(int val, std::tuple<int,int> const& coords, int pos, std::shared_ptr<MemArbre> const& arbre, std::shared_ptr<Noeud> const& pere);

				// Méthodes
				std::weak_ptr<Noeud> weak_from_this();

				std::ostream& afficher(std::ostream& stream) const;
				std::shared_ptr<Noeud> add_fils(int val, std::tuple<int,int> const& coords);
				void save();

				bool est_racine() const;

				// Accesseurs
                int val() const;
                void val(int val);
				int const& pos() const;
				std::tuple<int,int>& coords();
				std::shared_ptr<Noeud> pere() const;
				std::shared_ptr<MemArbre> arbre() const;
				std::set<std::shared_ptr<Noeud>> const& fils() const;
		};

	private:
		// Attributs
		std::fstream m_fichier;
		std::map<int,std::shared_ptr<Noeud>> m_noeuds;

		// Méthodes
		void save(int& pos, std::string const& data);
		void save(std::shared_ptr<MemArbre::Noeud> const& n);

	public:
		// Alias
		using iterateur = std::map<int,std::shared_ptr<Noeud>>::const_iterator;

		// Constructeur
		MemArbre(std::string const& fichier);

		// Destructeur
		~MemArbre();

		// Méthodes
		void charger();
		std::shared_ptr<Noeud> add_racine(int val, std::tuple<int,int> const& coords);
		std::set<std::shared_ptr<Noeud>> racines() const;
		iterateur begin() const;
		iterateur end() const;
};

// Opérateurs externes
std::ostream& operator << (std::ostream& stream, MemArbre::Noeud const& n);

#endif // __MEMARBRE
