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

#ifndef SIMGE_GLUT_WINDOW_HPP_INCLUDED
#define SIMGE_GLUT_WINDOW_HPP_INCLUDED

#include <GL/glut.h>
#include <simge/glut/Point.hpp>

namespace simge { namespace glut {

/**
 * A GLUT window.
 * Only inside callback functions it is guaranteed that the current window
 * is the callback functions window.
 */    
class Window
{
    friend class Application;
    
public:
    /**
     * A window with given title.
     */
    Window(char const* title, unsigned int mode = GLUT_RGBA | GLUT_SINGLE);

    /**
     * Destructor glutDestroy's window.
     */
    virtual ~Window();

    /**
     * Get window width.
     */
    int getWidth() const;

    /**
     * Get window height.
     */
    int getHeight() const;

    /**
     * Changes window size.
     */
    void setSize(int width, int height);

    /**
     * Makes this window current window for OpenGL requests.
     */
    void makeCurrent();

    /**
     * Swap buffers. If in single buffer mode no effect.
     */
    void swapBuffers();
    
    /**
     * Forces a repaint as soon as possible.
     */
    void invalidate();

    /**
     * Return a reference to current window.
     */
    static Window& currentWindow();
    
protected:
    inline virtual void paintGL() {}
    inline virtual void reshapeGL(int width, int height) {}
    inline virtual void mouseGL(int button, int state, int x, int y) {}
    inline virtual void motionGL(int x, int y) {}
    inline virtual void passiveMotionGL(int x, int y) {}
    inline virtual void keyboardGL(unsigned char key, int x, int y) {}
    
private:
    static void displayCallbackDispatcher();
    static void reshapeCallbackDispatcher(int width, int height);
    static void mouseCallbackDispatcher(int button, int state, int x, int y);
    static void motionCallbackDispatcher(int x, int y);
    static void passiveMotionCallbackDispatcher(int x, int y);
    static void keyboardCallbackDispatcher(unsigned char key, int x, int y);
    
private:
    int id_;
};

} } // namespace glut/simge

#endif
