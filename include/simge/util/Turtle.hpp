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

#ifndef SIMGE_UTIL_TURTLE_HPP_INCLUDED
#define SIMGE_UTIL_TURTLE_HPP_INCLUDED

#include <simge/glut/Point.hpp>
#include <simge/util/Color.hpp>

namespace simge { namespace util {

/**
 * A turtle that paints onto a window.
 */
class Turtle
{
public:
    /**
     * Positions itself at (0, 0) with a red tail.
     */
    Turtle();

    /**
     * A turtle at given position and color.
     */
    Turtle(geom::Point<2> const& pos, Color const& color);
    
    /**
     * Change tail color.
     */
    void setTailColor(Color const& color);
    
    /**
     * Jump to a location.
     */
    void moveTo(geom::Point<2> const& pos);
    
    /**
     * Line to a location.
     */
    void lineTo(geom::Point<2> const& pos);
    
    /**
     * Relative version of moveTo.
     */
    void moveRel(double dx, double dy);
    
    /**
     * Relative version of moveTo.
     */
    void lineRel(double dx, double dy);
    
    /**
     * Turn relative.
     */
    void turn(double diff);
    
    /**
     * Turn absolute.
     */
    void turnTo(double angle);
    
    /**
     * Move dist distance in current dimension.
     */
    void forward(double dist, bool isVisible = true);

    /**
     * Get current position of the turtle.
     */
    inline geom::Point<2> const& getPosition() const 
    {
        return pos_;
    }
    
private:
    Color tail_;
    double angle_;
    geom::Point<2> pos_;
};

} } // namespace glut/simge

#endif
