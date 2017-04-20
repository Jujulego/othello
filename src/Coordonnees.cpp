#include "Coordonnees.h"

Coordonnees::Coordonnees()
            :m_x(0), m_y(0)
{
}

Coordonnees::Coordonnees(int _x, int _y)
            :m_x(_x), m_y(_y)
{
}

Coordonnees::~Coordonnees()
{
}

// Getters
int Coordonnees::x() {
    return m_x;
}

int Coordonnees::y() {
    return m_y;
}

// Setters
void Coordonnees::s_x(int _x) {
    m_x = _x;
}

void Coordonnees::s_y(int _y) {
    m_y = _y;
}

void Coordonnees::s_x_y(int _x, int _y) {
    m_x = _x;
    m_y = _y;
}
