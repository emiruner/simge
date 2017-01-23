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

#include <simge/util/Utility.hpp>

namespace simge { namespace util {

using namespace glut;
using namespace geom;

void drawArrow(Point<2> const& start, Vector<2> const& dir, double len)
{
    const Point<2> end = start + dir.unit() * len;
    const Point<2> arrowBase = end + -10 * dir.unit();
    
    glBegin(GL_LINES);
    vertex(start);
    vertex(end);
    
    vertex(end);
    vertex(arrowBase + (end - start).cwNormal().unit() * 6);
    
    vertex(end);
    vertex(arrowBase + (start - end).cwNormal().unit() * 6);        
    glEnd();
}

void drawCross(Point<2> const& pos, int size)
{
    glBegin(GL_LINES);
    glVertex2d(pos[0] - size, pos[1] - size);
    glVertex2d(pos[0] + size, pos[1] + size);
    glVertex2d(pos[0] - size, pos[1] + size);
    glVertex2d(pos[0] + size, pos[1] - size);
    glEnd();
}

void drawCircle(Point<2> const& center, double radius, int approx)
{
    const double kPi2 = 6.28318530717958647688;
    const double kPi2DivApprox = kPi2 / approx;
    
    const Vector<2> shifter = center - point(0, 0);
    Point<2> last = shifter + point(radius, 0);
    
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < approx; ++i)
    {
        vertex(last);
        last = shifter + point(radius * cos(kPi2DivApprox * i),
                               radius * sin(kPi2DivApprox * i));
        vertex(last);
    }
    glEnd();
}

void drawGrabHandle(Point<2> const& pos, double size)
{
    const double x = pos[0];
    const double y = pos[1];
    
    size /= 2.0;
    
    glColor3f(0, 1, 0);
    glRectd(x - size, y + size, x + size, y - size);
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2d(x - size, y + size);
    glVertex2d(x + size, y + size);
    glVertex2d(x + size, y - size);
    glVertex2d(x - size, y - size);
    glVertex2d(x - size, y + size);
    glVertex2d(x - size, y - size);
    glVertex2d(x + size, y + size + 1);
    glVertex2d(x + size, y - size);
    glEnd();
}

bool closeEnough(Point<2> const& orig, Point<2> const& tested, double limit)
{
    return distanceBetween(orig, tested) < limit;
}    

} } // namespace simge/util
