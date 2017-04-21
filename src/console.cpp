// Importations
#include "console.h"

namespace c {
    #ifndef __gnu_linux__
    # include <conio.h>
    # include <windows.h>
    #else
    # include <fcntl.h>
    # include <unistd.h>
    # include <termios.h>

    int getch(void) {
        struct termios oldattr, newattr;
        int ch, oldf;

        // Sauvegarde de la config
        tcgetattr(STDIN_FILENO, &oldattr);

        // Modification du terminal
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

        // Vidage du buffer
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        while (getchar() != EOF) {}

        fcntl(STDIN_FILENO, F_SETFL, oldf);

        // Récupération du char
        ch = getchar();

        if (ch == 27) { // char de controle
            ch <<= 16;
            ch += getchar() << 8;
            ch += getchar();
        }

        // Rétablissement du terminal
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

        return ch;
    }

    int kbhit() {
        struct termios oldt, newt;
        int ch, oldf;

        // Sauvegarde de la config
        tcgetattr(STDIN_FILENO, &oldt);

        // Modification du terminal
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        // Préparation de stdin (rendu non bloquant)
        fflush(stdin);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        // Récupération d'un charactère (ou EOF)
        ch = getchar();

        // Rétablissement
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        // Test !
        if (ch != EOF) {
            // Renvoi du charactère
            ungetc(ch, stdin);
            return 1;
        }

        return 0;
    }
    #endif
}

using namespace c;

// Constructeur
Console::Console() {
}

// Destructeur
Console::~Console() {
}

// Méthodes
void Console::gotoLigCol(int lig, int col) { // déplacement du curseur
#ifndef __gnu_linux__
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
#else
    std::cout << "\x1b[" << lig+1 << ";" << col+1 << "H";
#endif
}

void Console::clear() {
#ifndef __gnu_linux__
    system("cls");
#else
    std::cout << "\x1b[2J";
#endif
}

int Console::getch() { // récupère le caractère du clavier
    std::cin.clear();
    int c = c::getch();

#ifndef __gnu_linux__
    if (c == 224) {
        c <<= 8;
        c += c::getch();
    }
#endif // __gnu_linux__

    return c;
}

int Console::kbhit() { // renvoi 0 ou 1
    std::cin.clear();
    return c::kbhit();
}

/*
Couleurs Windows :      Couleurs Linux :
0: noir                 0: noir
1: bleu foncé           1: rouge
2: vert                 2: vert
3: bleu-gris            3: jaune
4: marron               4: bleu
5: pourpre              5: magenta (violet)
6: kaki                 6: cyan
17: gris clair          7: blanc
8: gris
9: bleu                 9: defaut
10: vert fluo
11: turquoise
12: rouge
13: rose fluo
14: jaune fluo
15: blanc
*/
void Console::_setColor(int front, int back) {
#ifndef __gnu_linux__
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,back*16+front);
#else
    std::cout << "\x1b[" << front + 30 << ";" << back + 40 << "m";
#endif
}

void Console::setColor(Color front, Color back) {
#ifndef __gnu_linux__
    int couleurs[] = {0, 15, 12, 10, 9, 14, 11, 8, 7, 0};
#else
    int couleurs[] = {0, 7, 1, 2, 4, 3, 5, 6, 9, 9};
#endif
    _setColor(couleurs[front], couleurs[back]);
}
