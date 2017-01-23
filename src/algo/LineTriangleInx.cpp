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

#include <simge/algo/LineTriangleInx.hpp>
#include <simge/algo/LinePlaneInx.hpp>

#include <simge/geom/Polygon.hpp>
#include <cmath>

using namespace simge::geom;

namespace
{
    const double kEpsilon = 0.0000001;
    const double kTwoPi = 6.283185307179586476925286766552;

    double angleSum(Point<3> const* p, int n, Point<3> const& q)
    {
        double sum = 0;
        
        for(int i = 0; i < n; ++i)
        {
            Vector<3> v1 = p[i] - q;
            Vector<3> v2 = p[(i + 1) % n] - q;
            
            const double denom = v1.length() * v2.length();
            
            if(denom <= kEpsilon)
            {
                return kTwoPi;
            }
            else
            {
                sum += acos((v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]) / denom);
            }
        }
        
        return sum;
    }   
}

namespace simge { namespace algo {
        
bool findLineTriangleIntersection(Point<3> const* plane, Point<3> const* line, Point<3>& inx)
{
    Point<3> planeInx;
    
    if(findLinePlaneIntersection(plane, line, planeInx))
    {
        double sum = angleSum(plane, 3, planeInx);
        
        if((sum - kTwoPi <= kEpsilon) && (sum - kTwoPi >= -kEpsilon))
        {
            inx = planeInx;
            return true;
        }
    }

    return false;
}

} } // namespace algo / simge

