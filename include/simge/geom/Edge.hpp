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

#ifndef SIMGE_GEOM_EDGE_HPP_INCLUDED
#define SIMGE_GEOM_EDGE_HPP_INCLUDED

#include <simge/geom/Operations.hpp>
#include <simge/util/Enum.hpp>
#include <simge/geom/Orientation.hpp>

namespace simge { namespace geom
{

/**
 * A line segment in a Dim dimensional space.
 */    
template <int Dim>
class Edge
{
public:
    Edge()
    {
    }
    
    Edge(Point<Dim> const& p0, Point<Dim> const& p1)
    {
        ends_[0] = p0;
        ends_[1] = p1;
    }

    Point<Dim>& operator[](int index)
    {
        return ends_[index];
    }
    
    Point<Dim> const& operator[](int index) const
    {
        return ends_[index];
    }

    double length() const
    {
        return distanceBetween(ends_[0], ends_[1]);
    }

    /**
     * Direction vector of this line segment going from 0th point to 1st point.
     */
    Vector<Dim> direction0_1() const
    {
        return (ends_[1] - ends_[0]).unit();
    }
    
    /**
     * Direction vector of this line segment going from 1st point to 0th point.
     */
    Vector<Dim> direction1_0() const
    {
        return (ends_[0] - ends_[1]).unit();
    }

    /**
     * Counterclock-wise normal of this line segments direction vector
     * when going from 0th point to 1st point.
     */
    Vector<Dim> ccwNormal0_1() const
    {
        return direction0_1().ccwNormal();
    }
    
    /**
     * Finds the point that is found at the parametric position t.
     */
    Point<Dim> point(double t)
    {
        return ends_[0] + t * (ends_[1] - ends_[0]);
    }
    
private:
    Point<Dim> ends_[2];
};

/**
 * Finds the position of the given point with respect to given edge.
 */
inline Orientation classify(Edge<2> const& edge, Point<2> const& p2)
{
	Point<2> const& p0 = edge[0];
	Point<2> const& p1 = edge[1];
	
	const Vector<2> a = p1 - p0;
	const Vector<2> b = p2 - p0;
	const double sa = a[0] * b[1] - b[0] * a[1];	
	
	if(sa > 0)
	{
		return Orientation::Left();
	}
	
	if(sa < 0)
	{
		return Orientation::Right();
	}
	
	if(a[0] * b[0] < 0 || a[1] * b[1] < 0)
	{
		return Orientation::Behind();
	}
	
	if(a.length() < b.length())
	{
		return Orientation::Beyond();
	}
	
	if(p0 == p2)
	{
		return Orientation::Origin();
	}
	
	if(p1 == p2)
	{
		return Orientation::Destination();
	}
	
	return Orientation::Between();
}
 
 /**
  * Finds the intersection point of two line segments.
  * 
  * @return true if an intersection point exists, false otherwise
  */
inline bool intersection(Edge<2> const& l0, Edge<2> const& l1, Point<2>& inter)
{
    Point<2> const& A = l0[0];
    Point<2> const& B = l0[1];
    Point<2> const& C = l1[0];
    Point<2> const& D = l1[1];
    
    const Vector<2> b = B - A;
    const Vector<2> d = D - C;
    const Vector<2> c = C - A;
    
    if(dot(b.ccwNormal(), d) != 0)
    {
        const double t = dot(d.ccwNormal(), c) / dot(d.ccwNormal(), b);
        const double u = dot(b.ccwNormal(), c) / dot(d.ccwNormal(), b);
        
        if(t >= 0 && t <= 1 && u >= 0 && u <= 1)
        {
            inter = A + t * b;
            return true;
        }
    }

    return false;
}

class HitType : public util::Enum<int>
{
private:
	HitType(int value)
	: util::Enum<int>(value)
	{
	}
	
public:
	static inline HitType NoHit()
	{
		return HitType(0);
	}
	
	static inline HitType Entering()
	{
		return HitType(1);
	}
	
	static inline HitType Exiting()
	{
		return HitType(2);
	}
};

/**
 * Checks whether line p enters or exits to the half space
 * created by line q. Assumes that while going from q0 to q1
 * the right side is interior and left side is exterior.
 */
inline HitType hitQueryRightIsInterior(Edge<2> const& p, Edge<2> const& q)
{
    Point<2> inter;
    
    if(intersection(p, q, inter))
    {
        return (dot(p[1] - p[0], (q[1] - q[0]).cwNormal()) > 0)
            ? HitType::Entering()
            : HitType::Exiting();
    }
    
    return HitType::NoHit();
}

/**
 * Checks whether line p enters or exits to the half space
 * created by line q. Assumes that while going from q0 to q1
 * the left side is interior and right side is exterior.
 */
inline HitType hitQueryLeftIsInterior(Edge<2> const& p, Edge<2> const& q)
{
    Point<2> inter;
    
    if(intersection(p, q, inter))
    {
        return (dot(p[1] - p[0], (q[1] - q[0]).ccwNormal()) > 0)
            ? HitType::Entering()
            : HitType::Exiting();
    }
    
    return HitType::NoHit();
}

/**
 * Intersection type.
 */
class IntersectionType : public util::Enum<int>
{
private:
    IntersectionType(int value)
    : util::Enum<int>(value)
    {
    }
    
public:
    static inline IntersectionType Collinear()
    {
        return IntersectionType(0);
    }
    
    static inline IntersectionType Parallel()
    {
        return IntersectionType(1);
    }
    
    static inline IntersectionType Skew()
    {
        return IntersectionType(2);
    }
    
    static inline IntersectionType SkewCross()
    {
        return IntersectionType(3);
    }
    
    static inline IntersectionType SkewNoCross()
    {
        return IntersectionType(4);
    }
};

/**
 * Finds the intersection of two line segments.
 * Returns the intersection type.
 * t will contain the parametric position of the intersection point.
 */
inline IntersectionType intersect(Edge<2> const& p, Edge<2> const& q, double& t)
{
    const Point<2> a = p[0];
    const Point<2> b = p[1];
    const Point<2> c = q[0];
    const Point<2> d = q[1];
    const Vector<2> n = vec((d - c)[1], (c - d)[0]);
    const double denom = dot(n, b - a);

    if(denom == 0.0)
    {
        Orientation aclass = classify(q, a);
        
        if(aclass == Orientation::Left() || aclass == Orientation::Right())
        {
            return IntersectionType::Parallel();
        }
        else
        {
            return IntersectionType::Collinear();
        }
    }

    const double num = dot(n, a - c);
    t = -num / denom;
    
    return IntersectionType::Skew();
}

template <int Dim>
std::ostream& operator<<(std::ostream& os, Edge<Dim> const& e)
{
    return os << "edge[" << e[0] << ", " << e[1] << ']';
}

} } // namespace geom/simge

#endif
