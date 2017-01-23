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

#include <simge/glut/Window.hpp>
#include <map>

namespace
{
    typedef std::map<int, simge::glut::Window*> IdWindowMap;    
    IdWindowMap id2win;
}

namespace simge { namespace glut
{
    Window::Window(char const* title, unsigned int mode)
    {
        glutInitDisplayMode(mode);
        id_ = glutCreateWindow(title);

        glutDisplayFunc(&Window::displayCallbackDispatcher);
        glutReshapeFunc(&Window::reshapeCallbackDispatcher);
        glutMouseFunc(&Window::mouseCallbackDispatcher);
        glutMotionFunc(&Window::motionCallbackDispatcher);
        glutPassiveMotionFunc(&Window::passiveMotionCallbackDispatcher);
        glutKeyboardFunc(&Window::keyboardCallbackDispatcher);

        id2win[id_] = this;
    }
    
    Window::~Window()
    {
        id2win.erase(id2win.find(id_));
    }

    void Window::displayCallbackDispatcher()
    {
        id2win[glutGetWindow()]->paintGL();
    }

    void Window::reshapeCallbackDispatcher(int width, int height)
    {
        id2win[glutGetWindow()]->reshapeGL(width, height);
    }
    
    void Window::mouseCallbackDispatcher(int button, int state, int x, int y)
    {
        id2win[glutGetWindow()]->mouseGL(button, state, x, y);
    }
    
    void Window::motionCallbackDispatcher(int x, int y)
    {
        id2win[glutGetWindow()]->motionGL(x, y);
    }
    
    void Window::passiveMotionCallbackDispatcher(int x, int y)
    {
        id2win[glutGetWindow()]->passiveMotionGL(x, y);
    }
    
    void Window::keyboardCallbackDispatcher(unsigned char key, int x, int y)
    {
        id2win[glutGetWindow()]->keyboardGL(key, x, y);
    }

    int Window::getWidth() const
    {
        return glutGet(GLUT_WINDOW_WIDTH);
    }
    
    int Window::getHeight() const
    {
        return glutGet(GLUT_WINDOW_HEIGHT);
    }
    
    void Window::setSize(int width, int height)
    {
        glutReshapeWindow(width, height);
    }
    
    void Window::invalidate()
    {
        glutPostRedisplay();
    }

    void Window::makeCurrent()
    {
        glutSetWindow(id_);
    }

    void Window::swapBuffers()
    {
        glutSwapBuffers();
    }
    
    Window& Window::currentWindow()
    {
        return *id2win[glutGetWindow()];
    }

} } // namespace glut/simge

