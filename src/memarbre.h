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
				/// Ajoute le fils donné
				void add_fils(std::shared_ptr<MemArbre::Noeud> const& fils);

				friend class MemArbre;

			public:
				// Constructeurs
				Noeud(int val, std::tuple<int,int> const& coords, int pos, std::shared_ptr<MemArbre> const& arbre);
				Noeud(int val, std::tuple<int,int> const& coords, int pos, std::shared_ptr<MemArbre> const& arbre, std::shared_ptr<Noeud> const& pere);

				// Méthodes
				/// Renvoie un weak_ptr sur this
				std::weak_ptr<Noeud> weak_from_this();

				/// Permet d'afficher le noeud
				std::ostream& afficher(std::ostream& stream) const;
				/// Crée un fils avec la valeur et la coordonnée données
				std::shared_ptr<Noeud> add_fils(int val, std::tuple<int,int> const& coords);
				/// Sauvegarde le noeud dans le fichier
				void save();

				/// Renvoie vrai si le noeud est une racine
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
		/// Sauvegarde du noeud (sérialisé dans un string)
		void save(int& pos, std::string const& data);
		/// Sauvegarde le noeud donné
		void save(std::shared_ptr<MemArbre::Noeud> const& n);

	public:
		// Alias
		using iterateur = std::map<int,std::shared_ptr<Noeud>>::const_iterator;

		// Constructeur
		MemArbre(std::string const& fichier);

		// Destructeur
		~MemArbre();

		// Méthodes
		/// Lance le chargement de l'arbre
		void charger();
		/// ajoute une racine au fichier
		std::shared_ptr<Noeud> add_racine(int val, std::tuple<int,int> const& coords);
		/// Renvoie les racines
		std::set<std::shared_ptr<Noeud>> racines() const;
		iterateur begin() const;
		iterateur end() const;
		/// Renvoie le noeud à la position donnée
		std::shared_ptr<Noeud> noeud(int pos) const;
};

// Opérateurs externes
std::ostream& operator << (std::ostream& stream, MemArbre::Noeud const& n);

#endif // __MEMARBRE
