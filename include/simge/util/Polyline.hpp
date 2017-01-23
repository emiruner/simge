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

#ifndef SIMGE_UTIL_POLYLINE_HPP_INCLUDED
#define SIMGE_UTIL_POLYLINE_HPP_INCLUDED

#include <simge/glut/Point.hpp>
#include <simge/util/Color.hpp>
#include <simge/glut/Window.hpp>

#include <vector>
#include <algorithm>
#include <GL/glut.h>

namespace simge { namespace util
{

/**
 * A multi-segment line.
 */
template <typename PointType>    
struct Polyline
{
    typedef std::vector<PointType> PointVec;
    
    PointVec points;
    Color color;
};

/**
 * Draw the line using OpenGL commands.
 * Does glBegin()-glEnd() calls.
 * Does not flush.
 * Assumes that current window valid.
 */
template <typename PointType>
void draw(Polyline<PointType> const& line)
{
    color(line.color);
    void (*vertexer)(PointType const& p) = &glut::vertex;
    glBegin(GL_LINE_STRIP);
    std::for_each(line.points.begin(), line.points.end(), vertexer);
    glEnd();
}

} } // namespace util/simge

#endif
