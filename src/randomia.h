/** @file: randomia.h
 * @brief: 
 *
 */

#ifndef RANDOMIA_H
#define RANDOMIA_H

// Dépendances
#include <string>

#include "etat.h"
#include "ia.h"
#include "pion.h"

// Classe
class RandomIA : public IA {
    public:
        // Méthodes
        virtual std::string id() const override;
        virtual Pion jouer(Etat plateau) override;
};

#endif // RANDOMIA_H
