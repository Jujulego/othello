#ifndef COUP_H
#define COUP_H

// Dépendances
#include <istream>
#include <vector>

// Enumération
enum COULEUR { VIDE, NOIR, BLANC };

// Opérateur externe
std::istream& operator >> (std::istream& stream, COULEUR& coul);

// Structure de Pion
struct Pion {
    // Coordonnées matrice !
    int x, y;
    COULEUR couleur;
};

// Constantes
static const std::vector<void(*)(int&,int&)> DIRECTIONS = {
    [] (int& i, int& j) {i++; j=j;}, // DROITE
    [] (int& i, int& j) {i++; j++;}, // DROITE-BAS
    [] (int& i, int& j) {i=i; j++;}, // BAS
    [] (int& i, int& j) {i--; j++;}, // GAUCHE-BAS
    [] (int& i, int& j) {i--; j=j;}, // GAUCHE
    [] (int& i, int& j) {i--; j--;}, // GAUCHE-HAUT
    [] (int& i, int& j) {i=i; j--;}, // HAUT
    [] (int& i, int& j) {i++; j--;}  // DROITE-HAUT
};

// Macros : index du tableau de directions
#define DIR_DROITE      0
#define DIR_DROITE_BAS  1
#define DIR_BAS         2
#define DIR_GAUCHE_BAS  3
#define DIR_GAUCHE      4
#define DIR_GAUCHE_HAUT 5
#define DIR_HAUT        6
#define DIR_DROITE_HAUT 7

#endif // COUP_H
