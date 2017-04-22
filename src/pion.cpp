// Importations
#include <istream>

#include "pion.h"

// Opérateurs externes
std::istream& operator >> (std::istream& stream, COULEUR& coul) {
	// Déclarations
	int c;
	
	// Lecture
	stream >> c;
	
	// Transformation en couleur
	switch (c) {
	case 0:
		coul = VIDE;
		break;
	
	case 1:
		coul = NOIR;
		break;
	
	case 2:
		coul = BLANC;
		break;
	}
	
	return stream;
}
