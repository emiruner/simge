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

#include <simge/algo/TriangleTriangleInx.hpp>
#include <simge/algo/LineTriangleInx.hpp>

#include <simge/geom/Polygon.hpp>

using namespace simge::geom;

namespace simge { namespace algo {
        
std::vector<Point<3> > findTriangleTriangleIntersection(Point<3> const* t1, Point<3> const* t2)
{
    std::vector<Point<3> > intersection;
    
    for(int i = 0; i < 3; ++i)
    {
        Point<3> inx;
        Point<3> edge[2];
        
        edge[0] = t1[i];
        edge[1] = t1[(i + 1) % 3];
        
        if(findLineTriangleIntersection(t2, edge, inx))
        {
            intersection.push_back(inx);
        }
    }
    
    for(int i = 0; i < 3; ++i)
    {
        Point<3> inx;
        Point<3> edge[2];
        
        edge[0] = t2[i];
        edge[1] = t2[(i + 1) % 3];
        
        if(findLineTriangleIntersection(t1, edge, inx))
        {
            intersection.push_back(inx);
        }
    }
    
    return intersection;
}

} } // namespace algo / simge

