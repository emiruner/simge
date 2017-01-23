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

#ifndef SIMGE_GLUT_POINT_HPP_INCLUDED
#define SIMGE_GLUT_POINT_HPP_INCLUDED

#include <GL/glut.h>
#include <simge/geom/Point.hpp>

namespace simge { namespace glut
{

//
// Calls correct glVertex* function given the point.
//

inline void vertex(geom::Point<2> const& p)
{
    glVertex2d(p[0], p[1]);
}

inline void vertex(geom::Point<3> const& p)
{
    glVertex3d(p[0], p[1], p[2]);
}

inline void rasterPos(geom::Point<2> const& p)
{
    glRasterPos2d(p[0], p[1]);
}

inline void rasterPos(geom::Point<3> const& p)
{
    glRasterPos3d(p[0], p[1], p[2]);
}

} } // namespace glut/simge

#endif
