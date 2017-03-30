#ifndef PION_H
#define PION_H

// Dépendances
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QRectF>

#include "etat.h"

// Macros
#define TAILLE_CASE 50.0f

// Classe
class Pion : public QGraphicsItem {
    private:
        // Attributs
        COULEUR m_couleur;

    public:
        // Constructeur
        Pion(QPoint pos, COULEUR couleur = VIDE, QGraphicsItem* parent = nullptr);

        // Méthodes
        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        // Accesseurs
        COULEUR couleur() const;
        void couleur(COULEUR couleur);
};

#endif // PION_H
