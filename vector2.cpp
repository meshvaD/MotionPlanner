#include "include/vector2.hpp"
#include <math.h>
#include <iostream>

double dot(vector2 a, vector2 b)
{
    return a[0] * b[0] +
        a[1] * b[1];
}

vector2 unit_vector(vector2 a)
{
    double mag = a.magnitude();
    if (mag == 0)
        return a;
    return vector2(a[0]/mag, a[1]/mag);
}

double vector2::magnitude()
{
    return pow(x[0]*x[0] + x[1]*x[1] , 0.5);
}

std::ostream& operator<<(std::ostream& os, const vector2& vec)
{
    os << "( " << vec[0] << " , " << vec[1] << " )";
}

bool vector2::operator==(const vector2& rhs) const
{
    // std::cout << "diff: " << this->x[0] - rhs[0] << " " << this->x[1] - rhs[1] << std::endl;
    if (std::fabs(this->x[0] - rhs[0]) < PRECISION && std::fabs(this->x[1] - rhs[1]) < PRECISION)
        return true;
    return false;
}

bool vector2::operator!=(const vector2& rhs) const
{
    if (std::fabs(this->x[0] - rhs[0]) < PRECISION && std::fabs(this->x[1] - rhs[1]) < PRECISION)
        return false;
    return true;
}

