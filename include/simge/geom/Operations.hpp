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

#ifndef SIMGE_GEOM_OPERATIONS_HPP_INCLUDED
#define SIMGE_GEOM_OPERATIONS_HPP_INCLUDED

#include <simge/geom/Point.hpp>
#include <simge/geom/Vector.hpp>

namespace simge { namespace geom {

/**
 * Subtracting a point from another one yields the vector
 * for going from one point to the other.
 */
template <int Dim>
Vector<Dim> operator-(Point<Dim> const& lhs, Point<Dim> const& rhs)
{
    Vector<Dim> result;
    
    for(int i = 0; i < Dim; ++i)
    {
        result[i] = lhs[i] - rhs[i];
    }
    
    return result;
}

/**
 * Adding a vector to a point yields another vector.
 */
template <int Dim>
Point<Dim> operator+(Point<Dim> const& lhs, Vector<Dim> const& rhs)
{
    Point<Dim> result;
    
    for(int i = 0; i < Dim; ++i)
    {
        result[i] = lhs[i] + rhs[i];
    }
    
    return result;
}

template <int Dim>
Point<Dim> operator+(Vector<Dim> const& lhs, Point<Dim> const& rhs)
{
    return operator+(rhs, lhs);
}

} } // namespace geom/simge

#endif
