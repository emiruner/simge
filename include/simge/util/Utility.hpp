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

#ifndef SIMGE_UTIL_UTILITY_HPP_INCLUDED
#define SIMGE_UTIL_UTILITY_HPP_INCLUDED

#include <simge/geom/Operations.hpp>
#include <simge/glut/Window.hpp>
#include <simge/glut/Point.hpp>
#include <simge/geom/Polygon.hpp>
#include <simge/geom/Edge.hpp>

#include <algorithm>

namespace simge { namespace util {
    
/**
 * Draws an arrow starting from point start, int the direction dir and
 * with length length.
 */
void drawArrow(geom::Point<2> const& start, geom::Vector<2> const& dir, double len);

/**
 * Draws a cross at the given pos.
 */
void drawCross(geom::Point<2> const& pos, int size);

/**
 * Draw circle at the given position and radius.
 * This function approximates the circle by n-gons.
 * The approx parameter specify n.
 */
void drawCircle(geom::Point<2> const& center, double radius, int approx = 40);

/**
 * Draws a simple grab handle with red border and green fill.
 */
void drawGrabHandle(geom::Point<2> const& pos, double size);

/**
 * Returns true if distance between given two points is less than limit.
 */
bool closeEnough(geom::Point<2> const& orig, geom::Point<2> const& tested, double limit);

/**
 * Draws the given polyon using line loop.
 */
template <int Dim>
void drawLineLoop(geom::Polygon<Dim> const& poly)
{
    void (*vertexer)(geom::Point<2> const&) = &glut::vertex;
   
    glBegin(GL_LINE_LOOP);
    std::for_each(poly.begin(), poly.end(), vertexer);
    glEnd();
}

/**
 * Draws given line segment.
 */
template <int Dim>
void drawEdge(geom::Edge<Dim> const& ls)
{
    glBegin(GL_LINES);
    glut::vertex(ls[0]);
    glut::vertex(ls[1]);
    glEnd();
}

/**
 * Writes a string to the current window.
 */
template <typename PointType>
void drawText(void* font, PointType pos, char const* str)
{
    rasterPos(pos);
    
    while(*str != '\0')
    {
        glutBitmapCharacter(font, *str);
        pos[0] += glutBitmapWidth(font, *str);
        rasterPos(pos);
        ++str;
    }
}    

} } // namespace util/simge

#endif
