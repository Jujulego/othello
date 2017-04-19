#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#define TailleTab 8

#include <vector>
#include <memory>
#include <set>

#include "etat.h"
#include "console.h"
#include "pion.h"

class Tableau {
    private:
        Etat m_etat;
//        std::vector<std::vector<Pion>> Plateau;

    protected:
        Console* s_console = NULL;

    public:
        Tableau();
        void CreationTab();
        bool Jouer(int &x, int&y);
        void AfficherTab();
        void BoucleJeu();

    //Accesseur
     std::vector<std::shared_ptr<Pion>> const& get_pions() const;
};

#endif // PLATEAU_H_INCLUDED
