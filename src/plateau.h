#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#define TailleTab 8

#include <vector>
#include <map>
#include <memory>
#include <set>

#include "console.h"
#include "etat.h"
#include "ia.h"
#include "pion.h"

class Tableau {
    private:
        Etat m_etat;
        std::map<COULEUR,std::shared_ptr<IA>> m_ias;

    protected:
        Console* s_console = NULL;

    public:
        Tableau(std::shared_ptr<IA> ia_noir = nullptr, std::shared_ptr<IA> ia_blanc = nullptr);
        void CreationTab();
        bool Jouer(int &x, int&y);
        void AfficherTab();
        COULEUR BoucleJeu();

        // Accesseur
        std::map<COULEUR,unsigned> const scores() const;
        std::vector<std::shared_ptr<Pion>> const& get_pions() const;
};

#endif // PLATEAU_H_INCLUDED
