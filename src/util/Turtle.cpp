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

#include <simge/util/Turtle.hpp>
#include <simge/util/Conversion.hpp>
#include <simge/util/Color.hpp>
#include <simge/glut/Point.hpp>

#include <cmath>

namespace simge { namespace util {

using namespace geom;
    
Turtle::Turtle()
: tail_(Color::red()), angle_(0)
{
    pos_[0] = 0;
    pos_[1] = 0;
}

Turtle::Turtle(Point<2> const& pos, Color const& color)
: tail_(color), pos_(pos)
{
}

void Turtle::setTailColor(Color const& color)
{
    tail_ = color;
}

void Turtle::moveTo(Point<2> const& pos)
{
    pos_ = pos;
}
    
void Turtle::lineTo(Point<2> const& pos)
{
    glBegin(GL_LINES);
    glut::vertex(pos_);
    glut::vertex(pos);
    glEnd();
    pos_ = pos;
}

void Turtle::moveRel(double dx, double dy)
{
    pos_[0] += dx;
    pos_[1] += dy;
}

void Turtle::lineRel(double dx, double dy)
{
    glBegin(GL_LINES);
    glut::vertex(pos_);
    pos_[0] += dx;
    pos_[1] += dy;
    glut::vertex(pos_);
    glEnd();    
}   

void Turtle::turn(double diff)
{
    angle_ += diff;

    while(angle_ > 360)
    {
        angle_ -= 360.0;
    }
    
    while(angle_ < 0)
    {
        angle_ += 360.0;
    }
}

void Turtle::turnTo(double angle)
{
    angle_ = angle;
}

void Turtle::forward(double dist, bool isVisible)
{
    double x, y;
    
    if(angle_ == 90)
    {
        x = pos_[0];
        y = pos_[1] + dist;
    }
    else
    {
        x = pos_[0] + dist * cos(degreeToRadian(angle_));
        y = pos_[1] + dist * sin(degreeToRadian(angle_));
    }
    
    if(isVisible)
    {
        lineTo(point(x, y));
    }
    else
    {
        moveTo(point(x, y));
    }
}

} } // namespace simge/util
