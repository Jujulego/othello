/** @file graphe.h
 *  Défini le template Graphe, avec ses Sommets et Arcs.
 *
 * Ce template peut gérer les graphes orientés, pondérés, etc ...
 * Regardez ce code à vos risques et périls !!!
 */
#ifndef __GRAPHE_GRAPHE
#define __GRAPHE_GRAPHE

// Dépendances
#include <algorithm>
#include <memory>
#include <set>
#include <string>

namespace graphe {

// Foncteur
template<typename T>
struct WeakComp {
	bool operator () (std::weak_ptr<T> const& a1, std::weak_ptr<T> const& a2) {
		return std::shared_ptr<T>(a1) < std::shared_ptr<T>(a2);
	}
};

// Classe
template<typename D>
class Graphe {
	public:
		// Foncteur de tri
		struct OrdreArretes {
			bool operator () (typename Graphe<D>::Arc::Sptr const& a1, typename Graphe<D>::Arc::Sptr const& a2) {
				return *a1 < *a2;
			}
		};
		
		// Sous classes
		class Sommet {
			public:
				// Types
				using Sptr = std::shared_ptr<Sommet>;
				using Wptr = std::weak_ptr<Sommet>;
				
				struct SommetComp {
					bool operator () (Sptr const& s1, Sptr const& s2) {
						return s1->val() < s2->val();
					}
				};
			
			private:
				// Attributs
				D m_val; /**< Valeur associée au sommet */
				
				Wptr m_self;
				std::set<typename Graphe<D>::Arc::Wptr,WeakComp<typename Graphe<D>::Arc>> m_preds;	/**< Liste des prédécesseurs du sommet */
				std::set<typename Graphe<D>::Arc::Sptr> m_succs;						/**< Liste des successeurs du sommet */
				
				// Méthodes privées
				void add_pred(typename Graphe<D>::Arc::Wptr const& a) {
					m_preds.insert(a);
				}
				
				void rem_pred(typename Graphe<D>::Arc::Wptr const& a) {
					m_preds.erase(a);
				}
			
			public:
				// Constructeurs
				Sommet(D const& val) : m_val(val) {
				}
				
				// Opérateurs
				Sptr operator & () {
					return pt();
				}
				
				// Méthodes statiques
				static Sptr creer(std::string const& val = "") {
					return (new Sommet(val))->pt();
				}
				
				// Méthodes
				unsigned degres() const {
					return degres_int() + degres_ext();
				}
				
				unsigned degres_int() const {
					return m_preds.size();
				}
				
				unsigned degres_ext() const {
					return m_succs.size();
				}
				
				bool est_voisin(Sptr const& s) {
					for (auto a : m_succs) if (a->s2() == s) return true;
					for (auto a : m_preds) if (Arc::Sptr(a)->s1() == s) return true;
					return false;
				}
				
				void add_succ(Sptr& s, int poids = 1) {
					typename Arc::Sptr a((new Arc(pt(), s, poids))->pt());
					m_succs.insert(a);
					s->add_pred(typename Arc::Wptr(a));
				}
				
				void rem_succ(Sptr& s) {
					for (auto a : m_succs) if (a->s2() == s) m_succs.erase(a);
				}
				
				void rem_succ(typename Graphe<D>::Arc::Sptr& a) {
					m_succs.erase(a);
					a->s1()->rem_pred(a);
				}
				
				// Accesseurs
				D val() const {
					return m_val;
				}
				
				void val(D const& val) {
					m_val = val;
				}
				
				Sptr pt() {
					Sptr pt;
					
					if (m_self.expired()) { // Arrive quand == nullptr => 1er appel de cette fonction
						pt = Sptr(this);
						m_self = pt;
					} else {
						pt = Sptr(m_self);
					}
					
					return pt;
				}
				
				std::set<Sptr,SommetComp> voisins() const {
					// Déclaration
					std::set<Sommet::Sptr,Sommet::SommetComp> voisins;
					
					// Copie
					for (auto a : m_succs) voisins.insert(a->s2());
					for (auto a : m_preds) voisins.insert(Arc::Sptr(a)->s1());
					
					return voisins;
				}
				
				std::set<typename Graphe<D>::Arc::Sptr> preds() const {
					// Déclaration
					std::set<typename Arc::Sptr> preds;
					
					// Copie
					for (auto a : m_preds) preds.insert(Arc::Sptr(a));
					return preds;
				}
				
				std::set<typename Graphe<D>::Arc::Sptr> succs() const {
					return m_succs;
				}
		};
		
		class Arc {
			/** Représente un arc liant 2 sommets.
			 *  Représente un arc orienté et pondéré, allant du sommet s1 au sommet s2.
			 */
			public:
				// Types
				using Sptr = std::shared_ptr<Arc>;
				using Wptr = std::weak_ptr<Arc>;
			
			private:
				// Attributs
				Wptr m_self;
				typename Sommet::Wptr m_s1;	/**< Sommet de départ */
				typename Sommet::Wptr m_s2;	/**< Sommet de fin */
				
				int m_poids;
				std::string m_nom;
			
			public:
				// Constructeur
				Arc(typename Sommet::Sptr const& s1, typename Sommet::Sptr const& s2, int poids = 1, std::string const& nom = "")
					: m_s1(s1), m_s2(s2), m_poids(poids), m_nom(nom) {
				}
				
				// Opérateurs
				Sptr operator & () {
					return pt();
				}
				
				bool operator == (Arc const& a) {
					typename Sommet::Sptr min_pt = (s1() < s2()) ? s1() : s2();
					typename Sommet::Sptr max_pt = (s1() < s2()) ? s2() : s1();
					
					typename Sommet::Sptr min_a_pt = (a.s1() < a.s2()) ? a.s1() : a.s2();
					typename Sommet::Sptr max_a_pt = (a.s1() < a.s2()) ? a.s2() : a.s1();
					
					return (min_pt == min_a_pt) && (max_pt == max_a_pt) && (m_poids == a.m_poids) && (m_nom == a.m_nom);
				}
				
				bool operator <  (Arc const& a) {
					if (m_poids == a.m_poids) {
						typename Sommet::Sptr min_pt = (s1() < s2()) ? s1() : s2();
						typename Sommet::Sptr max_pt = (s1() < s2()) ? s2() : s1();
						
						typename Sommet::Sptr min_a_pt = (a.s1() < a.s2()) ? a.s1() : a.s2();
						typename Sommet::Sptr max_a_pt = (a.s1() < a.s2()) ? a.s2() : a.s1();
						
						if (min_pt == min_a_pt) {
							if (max_pt == max_a_pt)
								return false;
							return max_pt < max_a_pt;
						}
						return min_pt < min_a_pt;
					}
					return m_poids < a.m_poids;
				}
				
				bool operator >  (Arc const& a) {
					if (m_poids == a.m_poids) {
						typename Sommet::Sptr min_pt = (s1() < s2()) ? s1() : s2();
						typename Sommet::Sptr max_pt = (s1() < s2()) ? s2() : s1();
						
						typename Sommet::Sptr min_a_pt = (a.s1() < a.s2()) ? a.s1() : a.s2();
						typename Sommet::Sptr max_a_pt = (a.s1() < a.s2()) ? a.s2() : a.s1();
						
						if (min_pt == min_a_pt) {
							if (max_pt == max_a_pt)
								return false;
							return max_pt > max_a_pt;
						}
						return min_pt > min_a_pt;
					}
					return m_poids > a.m_poids;
				}
				
				// Accesseurs
				int poids() const {
					return m_poids;
				}
				
				std::string nom() const {
					return m_nom;
				}
				
				Sptr pt() {
					Sptr pt;
					
					if (m_self.expired()) {
						pt = Sptr(this);
						m_self = pt;
					} else {
						pt = Sptr(m_self);
					}
					
					return pt;
				}
				
				typename Sommet::Sptr s1() const {
					return Sommet::Sptr(m_s1);
				}
				
				typename Sommet::Sptr s2() const {
					return Sommet::Sptr(m_s2);
				}
		};
	
	private:
		// Attributs
		std::set<typename Sommet::Sptr> m_sommets;
	
	public:
		// Types
		using iterateur = typename std::set<typename Sommet::Sptr>::iterator;
		using const_iterateur = typename std::set<typename Sommet::Sptr>::const_iterator;
		
		// Constructeur
		Graphe(unsigned ordre = 0) {
			for (unsigned i = 0; i < ordre; i++)
				add_sommet();
		}
		
		// Méthodes
		int poids() const {
			int poids = 0;
			
			for (auto a : arretes())
				poids += a->poids();
			
			return poids;
		}
		
		unsigned ordre() const {
			return m_sommets.size();
		}
		
		iterateur begin() {
			return m_sommets.begin();
		}
		
		iterateur end() {
			return m_sommets.end();
		}
		
		const_iterateur begin() const {
			return m_sommets.cbegin();
		}
		
		const_iterateur end() const {
			return m_sommets.cend();
		}
		
		typename Sommet::Sptr find_sommet(D const& val) const {
			// Parcours du graphe
			auto it = std::find_if(begin(), end(),
				[val] (typename Sommet::Sptr const& s) -> bool { return s->val() == val; }
			);
			
			// Résultat
			if (it == end()) return nullptr;
			return *it;
		}
		
		typename Sommet::Sptr add_sommet(typename Sommet::Sptr const& s) {
			auto pt = Sommet::creer(s->val());
			m_sommets.insert(pt);
			
			return pt;
		}
		
		typename Sommet::Sptr add_sommet(D const& val = D()) {
			auto pt = Sommet::creer(val);
			m_sommets.insert(pt);
			
			return pt;
		}
		
		template<typename I>
		void add_sommets(I dep, I fin) {
			for (; dep != fin; dep++) m_sommets.insert(*dep);
		}
		
		template<typename A>
		Graphe algo(typename Sommet::Sptr dep, A a = A()) {
			return a(*this, dep);
		}
		
		// Accesseurs
		typename std::set<typename Arc::Sptr,OrdreArretes> arretes() const {
			// Déclarations
			std::set<typename Arc::Sptr,OrdreArretes> arretes;
			
			// Recherche
			for (auto s : *this) {
				auto t = s->succs();
				arretes.insert(t.begin(), t.end());
			}
			
			return arretes;
		}
		
		typename std::set<typename Sommet::Sptr> sommets() const {
			return m_sommets;
		}
};

}

#endif // __GRAPHE_GRAPHE
