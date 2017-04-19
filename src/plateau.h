#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#define TailleTab 8
#include <vector>
#include "pion.h"
#include "console.h"
#include <memory>
#include <set>

class Tableau
{
    private:
        std::vector<std::vector<Pion>> Plateau;
    protected:
         Console* s_console = NULL;
    public:
        Tableau();
        void CreationTab();
        void Jouer();

    //Accesseur
     std::vector<std::shared_ptr<Pion>> const& get_pions() const;
};

#endif // PLATEAU_H_INCLUDED
