#include "color/color_space.hpp"


Vector<3> color_space::HSV_to_RGB(double H, double S, double V)
{
    double C = V * S;
    double H_p = H / 60;

    double X = C * (1 - fabs( fmod(H_p, 2) - 1 ) );

    double m = V - C;

    Vector<3> m_vec = Vector<3>({m, m, m});

    if(H_p >= 0 && H_p < 1)
        return Vector<3>({C, X, 0}).plus(m_vec);
    else if(H_p >= 1 && H_p < 2)
        return Vector<3>({X, C, 0}).plus(m_vec);
    else if(H_p >= 2 && H_p < 3)
        return Vector<3>({0, C, X}).plus(m_vec);
    else if(H_p >= 3 && H_p < 4)
        return Vector<3>({0, X, C}).plus(m_vec);
    else if(H_p >= 4 && H_p < 5)
        return Vector<3>({X, 0, C}).plus(m_vec);
    else if(H_p >= 5 && H_p < 6)
        return Vector<3>({C, 0, X}).plus(m_vec);
    else
        return Vector<3>({0, 0, 0});

} // end of "HSV_to_RGB"