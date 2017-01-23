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

#ifndef SIMGE_GLUT_PLANAR_HPP_INCLUDED
#define SIMGE_GLUT_PLANAR_HPP_INCLUDED

#include <simge/glut/Window.hpp>

namespace simge { namespace glut
{
    
/**
 * Provides a 2D area. Lower left (0, 0) upper right
 * (window width, window height).
 */
class Planar : public Window
{
public:
    /**
     * Supply creation flags.
     */
    Planar(char const* name, int mode = GLUT_RGBA | GLUT_SINGLE);

    /**
     * Converts from window coordinate system to OpenGL coordinate system.
     */
    inline geom::Point<2> windowToGl(int x, int y)
    {
        return geom::point(x, getHeight() - y);
    }
    
protected:
    void reshapeGL(int width, int height);

    /**
     * Add escape closes support.
     * If subclasses want it they must call base's keyboardGL before theirs.
     */
    void keyboardGL(unsigned char key, int x, int y);
};
 
} } // namespace glut/simge

#endif
