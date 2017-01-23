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

#ifndef SIMGE_GEOM_POINT_HPP_INCLUDED
#define SIMGE_GEOM_POINT_HPP_INCLUDED

#include <math.h>
#include <string.h>
#include <ostream>

#include <simge/util/Conversion.hpp>

namespace simge { namespace geom
{

/**
 * A point in Dim-dimensional space.
 */
template <int Dim>
class Point
{
public:
    inline Point()
    {
    }
    
    inline Point(double* coords)
    {
        memcpy(coords_, coords, sizeof(double) * Dim);
    }

    template <int OtherDim>
    inline Point(Point<OtherDim> const& other)
    {
        const int min = Dim > OtherDim ? OtherDim : Dim;
        int i;
        
        for(i = 0; i < min; ++i)
        {
            coords_[i] = other[i];
        }
        
        while(i < Dim)
        {
            coords_[i] = 0;
            ++i;
        }
    }
    
    inline double operator[](int idx) const
    {
        return coords_[idx];
    }
    
    inline double& operator[](int idx)
    {
        return coords_[idx];
    }
    
private:
    double coords_[Dim];
};

/**
 * WARNING: Compares coordinates with 1e-8 precision.
 */
template <int Dim>
inline bool operator==(Point<Dim> const& lhs, Point<Dim> const& rhs)
{
    for(int i = 0; i < Dim; ++i)
    {
        double diff = lhs[i] > rhs[i] ? lhs[i] - rhs[i] : rhs[i] - lhs[i];
        
        if(diff > 0.00000001)
        {
            return false;
        }
    }
    
    return true;
}

template <int Dim>
inline bool operator!=(Point<Dim> const& lhs, Point<Dim> const& rhs)
{
    return !(lhs == rhs);
}

/**
 * Find the polar angle of the given point.
 */
inline double polarAngle(Point<2> const& p)
{
	const double x = p[0];
	const double y = p[1];
	
	if(x == 0 && y == 0)
	{
		return -1;
	}
	
	if(x == 0)
	{
		if(y > 0)
		{
			return 90;
		}
		else
		{
			return 270;
		}
	}
	
	const double angleInRadians = atan(y / x);
	double angleInDegrees = util::radianToDegree(angleInRadians);
	
	if(x > 0)
	{
		if(y < 0)
		{
			angleInDegrees += 360;
		}
	}
	else
	{
		angleInDegrees += 180;
	}
	
	return angleInDegrees;
}
	
inline Point<2> point(double x, double y)
{
    Point<2> result;
    
    result[0] = x;
    result[1] = y;
    
    return result;
}

inline Point<3> point(double x, double y, double z)
{
    Point<3> result;
    
    result[0] = x;
    result[1] = y;
    result[2] = z;
    
    return result;
}

template <int Dim>
inline Point<Dim> findMidPoint(Point<Dim> const& p1, Point<Dim> const& p2)
{
    Point<Dim> result;
    
    for(int i = 0; i < Dim; ++i)
    {
        result[i] = (p1[i] + p2[i]) / 2;
    }
    
    return result;
}

template <int Dim>
inline double distanceBetween(Point<Dim> const& p1, Point<Dim> const& p2)
{
    double sum = 0;
    
    for(int i = 0; i < Dim; ++i)
    {
        sum += (p1[i] - p2[i]) * (p1[i] - p2[i]);
    }
    
    return sqrt(sum);
}

template <int Dim>
std::ostream& operator<<(std::ostream& os, Point<Dim> const& p)
{
    os << "point[";
    
    for(int i = 0; i < Dim - 1; ++i)
    {
        os << p[i] << ", ";
    }

    return os << p[Dim - 1] << ']';
}

} } // namespace geom/simge

#endif
