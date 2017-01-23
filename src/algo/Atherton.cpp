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

#include <list>
#include <algorithm>

#include <simge/algo/Atherton.hpp>
#include <simge/geom/Edge.hpp>

using namespace simge::geom;

namespace
{
    
struct Vertex;
typedef std::list<Vertex> Vertexes;

struct Vertex
{
    Point<2> pos;
    HitType type;
    Vertexes::iterator other;

    Vertex()
    : type(HitType::Entering())
    {
    }
};

/**
 * Checks whether the given iterator points to a
 * Vertex* that is an intersection vertex.
 * Assumes that operator*() for the operator yields a Vertex*
 */
template <typename Iterator>
inline bool isInx(Iterator i)
{
    return i->type == HitType::Entering() || i->type == HitType::Exiting();
}

/**
 * Create a line segment from the given iterator and the next element
 */
inline Edge<2> segFromVertex(Vertexes& v, Vertexes::iterator i)
{
    return Edge<2>(i->pos, cycle(v, i)->pos);
}

/**
 * Finds the intersection points and stores them on two lists.
 * The other field of each new vertex shows the place on the
 * original vertex list that intersection vertex belongs.
 */
void findIntersections(Vertexes& a, Vertexes& b, Vertexes& aints, Vertexes& bints)
{
    if(a.size() < 2 || b.size() < 2)
    {
        return;
    }
    
    Point<2> inter;
    Vertexes::iterator ai, aend = a.end(), bi, bend = b.end();
        
    for(ai = a.begin(); ai != aend; ++ai)
    {
        for(bi = b.begin(); bi != bend; ++bi)
        {
            const Edge<2> aedge = segFromVertex(a, ai);
            const Edge<2> bedge = segFromVertex(b, bi);
            
            if(intersection(aedge, bedge, inter))
            {
                Vertex v1;
                Vertex v2;
                
                v1.pos = inter;
                v1.type = hitQueryRightIsInterior(aedge, bedge);
                v1.other = ai;
                
                v2.pos = inter;
                v2.type = hitQueryRightIsInterior(bedge, aedge);
                v2.other = bi;
                
                aints.push_back(v1);
                bints.push_back(v2);
            }
        }
    }
}

/**
 * Used to sort intersection points in decreasing distances
 * to a common non-intersection vertex.
 */
class CompareByDistance
{
public:
    CompareByDistance(Point<2> const& ref)
    : ref_(ref)
    {
    }
    
    int operator()(Vertex const& lhs, Vertex const& rhs)
    {
        return distanceBetween(lhs.pos, ref_) < distanceBetween(rhs.pos, ref_);
    }

private:
    Point<2> const& ref_;
};

/**
 * Place the intersection points to the original vertex lists.
 * Changes the other field of the new vertexes to point to the
 * corresponding intersection vertex at the other list.
 */
void mergeIntersection(Vertexes& vs, Vertexes& is)
{
    for(Vertexes::iterator i = vs.begin(), end = vs.end(); i != end; ++i)
    {
        Vertexes iv;
        
        for(Vertexes::iterator j = is.begin(), end = is.end(); j != end; ++j)
        {
            if(j->other == i)
            {
                iv.push_back(*j);
            }
        }

        iv.sort(CompareByDistance(i->pos));
        vs.insert(cycle(vs, i), iv.begin(), iv.end());
    }
}

/**
 * Adds intersection points to polygons.
 */
void markIntersections(Vertexes& a, Vertexes& b)
{
    Vertexes aints;
    Vertexes bints;
    
    findIntersections(a, b, aints, bints);
    mergeIntersection(a, aints);
    mergeIntersection(b, bints);

    for(Vertexes::iterator i = a.begin(), end = a.end(); i != end; ++i)
    {
        for(Vertexes::iterator j = b.begin(), end = b.end(); j != end; ++j)
        {
            if(i->pos == j->pos && isInx(i) && isInx(j))
            {
                i->other = j;
                j->other = i;
            }
        }
    }
}

/**
 * Fill the entering list with the entering intersection vertexes
 * in the orig list. Set the other field's of the vertexes in the entering
 * list to point the same vertexes to the original list.
 */
void findEntering(Vertexes& orig, Vertexes& entering)
{
    for(Vertexes::iterator i = orig.begin();i != orig.end(); ++i)
    {
        if(i->type == HitType::Entering())
        {
            Vertex v(*i);
            
            v.other = i;
            entering.push_back(v);
        }
    }
}

/**
 * Remove the vertex with the given pos from the vertex list.
 */
void removeVertex(Vertexes& v, Point<2> const& pos)
{
    for(Vertexes::iterator i = v.begin(), end = v.end(); i != v.end(); ++i)
    {
        if(i->pos == pos)
        {
            v.erase(i);
            break;
        }
    }
}

inline void removeIfEntering(Vertexes& entering, Vertex const& v)
{
    if(v.type == HitType::Entering())
    {
        removeVertex(entering, v.pos);
    }
}

Polygon<2> nextClip(Vertexes& subject, Vertexes& clip, Vertexes& entering)
{
    Polygon<2> poly(PolygonType::RightIsInterior());
    
    // Pick an entering vertex and delete it from the entering list
    Vertex v = *entering.begin();
    entering.erase(entering.begin());
    
    // Mark start
    Vertexes::iterator i, start;
    start = v.other;

    bool onSubject = true;
    poly.addVertex(start->pos);
    i = cycle(subject, start);

    while(i->pos != start->pos)
    {
        poly.addVertex(i->pos);

        if(isInx(i))
        {
            removeIfEntering(entering, onSubject ? *i : *(i->other));
            i = i->other;
            onSubject = !onSubject;
        }

        i = onSubject ? cycle(subject, i) : cycle(clip, i);
    }

    return poly;    
}

/**
 * Fill the given vertexes with poly's vertexes.
 */
void polygonToVertexes(Polygon<2> const& poly, Vertexes& vertexes)
{
    Polygon<2>::const_iterator i, end;
    
    for(i = poly.begin(), end = poly.end(); i != end; ++i)
    {
        Vertex v;
        
        v.pos = *i;
        v.type = HitType::NoHit();
        v.other = vertexes.end();
        
        vertexes.push_back(v);
    }
}
 
} // namespace <unnamed>

namespace simge { namespace algo {
        
std::vector<Polygon<2> > atherton(Polygon<2> const& subjp, Polygon<2> const& clipp)
{
    Vertexes subject, clip, entering;
    std::vector<Polygon<2> > polys;
    
    polygonToVertexes(subjp, subject);
    polygonToVertexes(clipp, clip);
    
    markIntersections(subject, clip);
    findEntering(subject, entering);
    
    while(entering.size() != 0)
    {
        polys.push_back(nextClip(subject, clip, entering));
    }

    return polys;
}

} } // namespace algo / simge
