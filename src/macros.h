#ifndef __MACROS
#define __MACROS

// Min et Max
#ifndef MIN
#define MIN(x1, x2) ((x1) < (x2) ? (x1) : (x2))
#endif

#ifndef MAX
#define MAX(x1, x2) ((x1) < (x2) ? (x2) : (x1))
#endif

// Paramètres
#define PROF_ALGO 3
#define FICHIER_NOIR  "arbre_noir.txt"
#define FICHIER_BLANC "arbre_blanc.txt"
#define TIMEOUT std::chrono::milliseconds(500) // 500ms

// Caractètres
#ifndef __gnu_linux__ // Pour Windows
// Pour le plateau
static const std::string LIGNE_HAUT = "\xda\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xc2\xc4\xc4\xc4\xc4\xbf";
static const std::string LIGNE_MIL1 = "\xb3    \xb3    \xb3    \xb3    \xb3    \xb3    \xb3    \xb3    \xb3";
static const std::string LIGNE_MIL2 = "\xc3\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xc5\xc4\xc4\xc4\xc4\xb4";
static const std::string LIGNE_BAS  = "\xc0\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xc1\xc4\xc4\xc4\xc4\xd9";

// Pour l'arbre
static const std::string BARRE_HORI = "\xc4";
static const std::string BARRE_VERT = "\xb3";
static const std::string ANGLE_BD   = "\xda";
static const std::string ANGLE_BG   = "\xbf";
static const std::string ANGLE_HDG  = "\xc1";

// Commandes
# define ENTREE  13
# define FL_DROITE 57421
# define FL_GAUCHE 57419
# define FL_HAUT   57416
# define FL_BAS    57424

#else // Pour Linux
// Pour le plateau
static const std::string LIGNE_HAUT = "\xe2\x95\xad\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xac\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x95\xae";
static const std::string LIGNE_MIL1 = "\xe2\x94\x82    \xe2\x94\x82    \xe2\x94\x82    \xe2\x94\x82    \xe2\x94\x82    \xe2\x94\x82    \xe2\x94\x82    \xe2\x94\x82    \xe2\x94\x82";
static const std::string LIGNE_MIL2 = "\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xbc\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xa4";
static const std::string LIGNE_BAS  = "\xe2\x95\xb0\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\xb4\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x95\xaf";

// Pour l'arbre
static const std::string BARRE_HORI = "\xe2\x94\x80";
static const std::string BARRE_VERT = "\xe2\x94\x82";
static const std::string ANGLE_BD   = "\xe2\x95\xad";
static const std::string ANGLE_BG   = "\xe2\x95\xae";
static const std::string ANGLE_HDG  = "\xe2\x94\xb4";

// Commandes
# define ENTREE  10
# define FL_DROITE 1792835
# define FL_GAUCHE 1792836
# define FL_HAUT   1792833
# define FL_BAS    1792834
#endif

#endif // __MACROS
