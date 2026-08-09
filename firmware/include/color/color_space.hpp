#ifndef COLOR_SPACE_HPP
#define COLOR_SPACE_HPP


#include <cmath>

#include "EmbeddedLib/math/n_vector.hpp"


namespace color_space
{


Vector<3> HSV_to_RGB(double H, double S = 1, double V = 1); 

}; // namespace color_space


#endif // COLOR_SPACE_HPP