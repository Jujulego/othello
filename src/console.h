#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

// Dépendances
#include <iostream>

// Enumérations
enum Color {
    COLOR_BLACK = 0,
    COLOR_WHITE = 1,
    COLOR_RED = 2,
    COLOR_GREEN = 3,
    COLOR_BLUE = 4,
    COLOR_YELLOW = 5,
    COLOR_PURPLE = 6,
    COLOR_CYAN = 7,
    COLOR_DEFAULT = 8, // gris couleur de base de la console
    COLOR_DEFAULT_BACK = 9,
};

// Classe
class Console {
    private:
        // Méthodes privées
        ///Permet les modifications des couleurs
        void _setColor(int front, int back);

    public:
        // Constructeur
        Console();

        // Destructeur
        ~Console();

        // Méthodes publiques
        ///Permet le positionnement dans la console suivant les lignes et colonnes
        void gotoLigCol(int lig, int col);
        ///Nettoie la console
        void clear();
        int  kbhit();
        ///Récupere la touche du clavier
        int  getch();

        #ifndef __gnu_linux__
        void setColor(Color front=COLOR_DEFAULT, Color back=COLOR_DEFAULT_BACK);
        #else
        void setColor(Color front=COLOR_DEFAULT, Color back=COLOR_DEFAULT_BACK);
        #endif
};

#endif // CONSOLE_H_INCLUDED
