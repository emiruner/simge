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

#ifndef SIMGE_GLUT_IDLEWORKER_HPP_INCLUDED
#define SIMGE_GLUT_IDLEWORKER_HPP_INCLUDED

namespace simge { namespace glut {
        
/**
 * Common base for classes that do something in the glut idle function.
 */
class IdleWorker
{
public:
    virtual void idle() = 0;

    virtual inline ~IdleWorker()
    {
    }
};

/**
 * Add an IdleWorker to list.
 */
void addIdleWorker(IdleWorker* idleWorker);

/**
 * Remove an IdleWorker from list.
 */
void removeIdleWorker(IdleWorker* idleWorker);
 
} } // namespace glut/simge

#endif
