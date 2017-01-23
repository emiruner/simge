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

#include <vector>

#include <simge/geom/Edge.hpp>
#include <simge/algo/Containment.hpp>

using namespace simge::geom;

typedef std::vector<Point<2> > PointVec;

namespace simge { namespace algo {
        
bool isInsidePolygon(Polygon<2> const& poly, Point<2> const& q)
{
    const double x = q[0], y = q[1];
    const int polySides = poly.size();
    bool oddNodes = false;
    PointVec v;
    
    for(Polygon<2>::const_iterator it = poly.begin(); it != poly.end(); ++it)    
    {
        v.push_back(*it);
    }

    int j = 0;
    for(int i = 0; i < polySides; ++i)
    {
        ++j;
        
        if(j == polySides)
        {
            j = 0;
        }
        
        if(v[i][1] < y && v[j][1] >= y || v[j][1] < y && v[i][1] >= y)
        {
            if(v[i][0] + (y - v[i][1]) / (v[j][1] - v[i][1]) * (v[j][0] - v[i][0]) < x)
            {
                oddNodes = !oddNodes;
            }
        }
    }
    
    return oddNodes;
}

} } // namespace algo / simge
