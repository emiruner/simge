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

#include <simge/algo/IsConvex.hpp>
#include <iostream>

using namespace simge::geom;

namespace simge { namespace algo {
        
bool isConvex(Polygon<2> const& poly)
{
    Polygon<2>::const_iterator it, end = poly.end(), next;
 
    for(it = poly.begin(); it != end; ++it)
    {
        next = it;

        ++next;
        if(next == end)
        {
            next = poly.begin();
        }
        
        const Edge<2> edge(*it, *cycle(poly, it));
        const Point<2> classifier(*cycle(poly, cycle(poly, it)));

        if(classify(edge, classifier) == Orientation::Left())
        {
            return false;
        }
    }

    return true;
}

} } // namespace algo / simge

