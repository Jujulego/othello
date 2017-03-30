// Importations
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QPoint>

#include "pion.h"
#include "src/pion.h"

// Constructeur
GPion::GPion(QPoint pos, COULEUR couleur, QGraphicsItem* parent) : QGraphicsItem(parent), m_couleur(couleur) {
    // Préparation
    setPos(pos.x()*TAILLE_CASE, pos.y()*TAILLE_CASE);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

// Méthodes
QRectF GPion::boundingRect() const {
    return QRectF(-TAILLE_CASE/2, -TAILLE_CASE/2, TAILLE_CASE, TAILLE_CASE);
}

void GPion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Fond + bords
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(Qt::black);
    painter->setBrush(QColor("#419f2e"));
    painter->drawRect(boundingRect());

    if (m_couleur != VIDE) {
        // Dessin du rond !
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(Qt::transparent);
        painter->setBrush((m_couleur == NOIR) ? Qt::black : Qt::white);
        painter->drawEllipse(5-TAILLE_CASE/2, 5-TAILLE_CASE/2, TAILLE_CASE - 10, TAILLE_CASE - 10);
    }
}

// Accesseurs
COULEUR GPion::couleur() const {
    return m_couleur;
}

void GPion::couleur(COULEUR couleur) {
    m_couleur = couleur;
    update();
}
