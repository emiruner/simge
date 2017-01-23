/*
 * Copyright (c) 2006 Emir UNER
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SIMGE_GEOM_VECTOR_HPP_INCLUDED
#define SIMGE_GEOM_VECTOR_HPP_INCLUDED

#include <math.h>
#include <string.h>
#include <ostream>

namespace simge { namespace geom
{

/**
 * A vector in a Dim dimensional space.
 */
template <int Dim>
class Vector
{
public:
    Vector()
    {
    }
    
    Vector(double* components)
    {
        memcpy(components_, components, sizeof(double) * Dim);
    }
    
    template <int OtherDim>
    Vector(Vector<OtherDim> const& other)
    {
        const int min = Dim > OtherDim ? OtherDim : Dim;
        int i;
        
        for(i = 0; i < min; ++i)
        {
            components_[i] = other[i];
        }
        
        while(i < Dim)
        {
            components_[i] = 0;
            ++i;
        }
    }
    
    double operator[](int idx) const
    {
        return components_[idx];
    }
    
    double& operator[](int idx)
    {
        return components_[idx];
    }
    
    double length() const
    {
        double sum = 0;
        
        for(int i = 0; i < Dim; ++i)
        {
            sum += components_[i] * components_[i];
        }
        
        return sqrt(sum);
    }
     
    Vector<Dim> unit() const
    {
        return *this / length();
    }

    /**
     * Counter-clockwise normal.
     */
    Vector<2> ccwNormal() const
    {
        // Allows only calls on Vector<2> as this
        // operation is only meaningful for them
        struct Dummy
        {
            char dummy[static_cast<int>(Dim == 2)];
        };

        Vector<2> result;
        
        result[0] = -components_[1];
        result[1] = components_[0];
        
        return result;
    }

    /**
     * Clockwise normal.
     */
    Vector<2> cwNormal() const
    {
        return -1 * ccwNormal();
    }
    
private:
    double components_[Dim];
};

inline Vector<2> vec(double c1, double c2)
{
    Vector<2> result;
    
    result[0] = c1;
    result[1] = c2;
    
    return result;
}
    
inline Vector<3> vec(double c1, double c2, double c3)
{
    Vector<3> result;
    
    result[0] = c1;
    result[1] = c2;
    result[2] = c3;
    
    return result;
}
    
template <int Dim>
Vector<Dim> operator*(Vector<Dim> const& lhs, double rhs)
{
    Vector<Dim> result;
    
    for(int i = 0; i < Dim; ++i)
    {
        result[i] = lhs[i] * rhs;
    }
    
    return result;
}

template <int Dim>
Vector<Dim> operator*(double lhs, Vector<Dim> const& rhs)
{
    return operator*(rhs, lhs);
}

template <int Dim>
inline Vector<Dim> operator+(Vector<Dim> const& lhs, Vector<Dim> const& rhs)
{
    Vector<Dim> result;
    
    for(int i = 0; i < Dim; ++i)
    {
        result[i] = lhs[i] + rhs[i];
    }
    
    return result;
}

template <int Dim>
inline Vector<Dim> operator-(Vector<Dim> const& lhs, Vector<Dim> const& rhs)
{
    return lhs + -1 * rhs;
}

template <int Dim>
Vector<Dim> operator/(Vector<Dim> const& lhs, double rhs)
{
    Vector<Dim> result;
    
    for(int i = 0; i < Dim; ++i)
    {
        result[i] = lhs[i] / rhs;
    }
    
    return result;
}

template <int Dim>
double dot(Vector<Dim> const& lhs, Vector<Dim> const& rhs)
{
    double sum = 0;
    
    for(int i = 0; i < Dim; ++i)
    {
        sum += lhs[i] * rhs[i];
    }

    return sum;
}

inline Vector<3> cross(Vector<3> const& lhs, Vector<3> const& rhs)
{
    return vec(lhs[1] * rhs[2] - lhs[2] * rhs[1],
               lhs[2] * rhs[0] - lhs[0] * rhs[2],
               lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

/**
 * Find the angle between given vectors in radians.
 */
template <int Dim>
double angleBetween(Vector<Dim> const& lhs, Vector<Dim> const& rhs)
{
    return acos(dot(lhs.unit(), rhs.unit()));
}

template <int Dim>
std::ostream& operator<<(std::ostream& os, Vector<Dim> const& p)
{
    os << "vector:[";
    
    for(int i = 0; i < Dim - 1; ++i)
    {
        os << p[i] << ", ";
    }

    return os << p[Dim - 1] << ']';
}
 
} } // namespace geom/simge


#endif
