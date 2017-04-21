#ifndef COORDONNEES_H_INCLUDED
#define COORDONNEES_H_INCLUDED

class Coordonnees
{
    private:
        // Attributs
        int m_x;
        int m_y;

    public:
        // Constructeur
        Coordonnees();
        Coordonnees(int _x, int _y);

        // Destructeur
        ~Coordonnees();

        // Getters
        int x();
        int y();

        // Setters
        void s_x(int _x);
        void s_y(int _y);
        void s_x_y(int _x, int _y);
};

#endif // COORDONNEES_H_INCLUDED
