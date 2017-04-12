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
        static Console s_console;
    public:
        Tableau();
        void CreationTab();
        void RemplisTab();
        void AffichTab();


};

#endif // PLATEAU_H_INCLUDED
