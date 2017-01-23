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

#include <simge/algo/LinePlaneInx.hpp>
#include <simge/geom/Operations.hpp>

using namespace simge::geom;

namespace
{
    Vector<3> findNormal(Point<3> const& p1, Point<3> const& p2, Point<3> const& p3)
    {
        const Vector<3> v1 = p3 - p1;
        const Vector<3> v2 = p2 - p1;
        
        return cross(v1, v2);
    }
    
} // namespace <unnamed>

namespace simge { namespace algo {
        
bool findLinePlaneIntersection(Point<3> const* plane, Point<3> const* line, Point<3>& inx)
{
    const Vector<3> normal = findNormal(plane[0], plane[1], plane[2]);
    Point<3> const& p1 = line[0];
    Point<3> const& p2 = line[1];
    
    double denom = dot(normal, p2 - p1);
    
    if(denom < 0.000001 && denom > -0.000001)
    {
        return false;
    }
    
    double u = dot(normal, plane[0] - p1) / denom;

    inx = p1 + (u * (p2 - p1));
    return true;
}

} } // namespace algo / simge

