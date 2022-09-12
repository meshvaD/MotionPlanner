#pragma once

#include <iostream>

class vector2
{
public:
    vector2() : x{0.,0.} {}
    vector2(double x, double y): x{x, y} {}

    double operator [](int i) const    {return x[i];}
    double & operator [](int i) {return x[i];}

    double magnitude();
    vector2 unit_vec();

    friend std::ostream& operator<<(std::ostream& os, const vector2& vec);
    bool operator==(const vector2& rhs) const;
    bool operator!=(const vector2& rhs) const;

    double PRECISION = 0.1;

private:
    double x[2];
};

//statics
double dot(vector2 a, vector2 b);
vector2 unit_vector(vector2 a);

inline vector2 operator*(const vector2& a, const double c)
{
    return vector2(a[0]*c, a[1]*c);
}

inline vector2 operator+(const vector2& a, const vector2& b)
{
    return vector2(a[0]+b[0], a[1]+b[1]);
}

inline vector2 operator-(const vector2& a, const vector2& b)
{
    return vector2(a[0]-b[0], a[1]-b[1]);
}

inline vector2 operator/(const vector2& a, const double c)
{
    return vector2(a[0]/c, a[1]/c);
}