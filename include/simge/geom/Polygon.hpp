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

#ifndef SIMGE_GEOM_POLYGON_HPP_INCLUDED
#define SIMGE_GEOM_POLYGON_HPP_INCLUDED

#include <ostream>
#include <list>
#include <simge/geom/Point.hpp>
#include <simge/geom/Edge.hpp>

namespace simge { namespace geom
{

class PolygonType
{
private:
	int value_;
	
	PolygonType(int value)
	: value_(value)
	{
	}
	
public:
	static inline PolygonType LeftIsInterior()
	{
		return PolygonType(0);
	}
	
	static inline PolygonType RightIsInterior()
	{
		return PolygonType(1);
	}
	
	int value() const
	{
		return value_;
	}
};

/**
 * A polygon.
 */
template <int Dim>
class Polygon
{
public:
    typedef std::list<Point<Dim> > Vertexes;
    typedef typename Vertexes::iterator iterator;
    typedef typename Vertexes::const_iterator const_iterator;

    Polygon()
    : type_(PolygonType::LeftIsInterior())
    {
    }

    /**
     * Specify the type of polygon. If the type is LeftIsInterior,
     * then given two consecutive vertices v0, and v1
     * and when going from v0 to v1 the left hand side is the interior
     * of the polygon and the right hand side is the exterior of polygon.
     * If the type is RightInterior then the reverse of the above is correct.
     */
    Polygon(PolygonType type)
    : type_(type)
    {
    }
    
    /**
     * Get type of polygon.
     */
    PolygonType getType() const
    {
        return type_;
    }
    
    /**
     * Add a new vertex to polygon.
     */
    void addVertex(Point<Dim> const& vertex)
    {
        vertexes_.push_back(vertex);
    }
    
    //
    // Return iterators for the vertexes.
    //
    iterator begin()
    {
        return vertexes_.begin();
    }
    
    const_iterator begin() const
    {
        return vertexes_.begin();
    }
    
    iterator end()
    {
        return vertexes_.end();
    }
    
    const_iterator end() const
    {
        return vertexes_.end();
    }

    typename Vertexes::size_type size() const
    {
        return vertexes_.size();
    }
    
    /**
     * Removes all vertexes.
     */
    void clear()
    {
        vertexes_.clear();
    }
    
    inline iterator insert(iterator pos, Point<Dim> elem)
    {
        return vertexes_.insert(pos, elem);
    }
    
    iterator erase(iterator it)
    {
        return vertexes_.erase(it);
    }

    /**
     * Split the part of this polygon specified by
     * the interval [begin, end) into a new polygon.
     */
    Polygon<Dim> split(iterator begin, iterator end)
    {
    	Polygon<Dim> part(getType());
    	
    	while(begin != end)
    	{
    		part.addVertex(*begin);
    		begin = erase(begin);
    	}
    	
    	return part;
    }
    
    /**
     * Fills the given collection object with edges.
     */
    template <typename Collection>
    void getEdges(Collection& coll)
    {
        const_iterator current = begin(), end = end(), next = current;

        while(current != end)
        {  		
            ++next;
            if(next == end)
            {
                next = begin();
            }

            coll.push_back(Edge<Dim>(current, next));
            ++current;
        }
    }
    
private:
    Vertexes vertexes_;
    PolygonType type_;
};
 
template <typename Collection>
inline typename Collection::iterator cycle(Collection& coll, typename Collection::iterator it)
{
	++it;
	
	if(it == coll.end())
	{
		it = coll.begin();
	}
	
	return it;
}

template <typename Collection>
inline typename Collection::const_iterator cycle(Collection const& coll, typename Collection::const_iterator it)
{
	++it;
	
	if(it == coll.end())
	{
		it = coll.begin();
	}
	
	return it;
}

template <int Dim>
std::ostream& operator<<(std::ostream& os, Polygon<Dim> const& poly)
{
	if(poly.size() > 0)
	{		
	    typename Polygon<Dim>::const_iterator it = poly.begin(), end = poly.end();
    
    	--end;
	    for(; it != end; ++it)
    	{
        	os << *it << ", ";
	    }

      	os << *it;
	}
	
    return os;
}

} } // namespace geom/simge

#endif
