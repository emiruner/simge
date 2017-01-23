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

#include <simge/glut/IdleWorker.hpp>
#include <list>
#include <GL/glut.h>

namespace
{
    typedef std::list<simge::glut::IdleWorker*> IdleWorkerList;
    IdleWorkerList idleWorkers;

    void idleFunc()
    {
        IdleWorkerList::iterator it, end = idleWorkers.end();
        
        for(it = idleWorkers.begin(); it != end; ++it)
        {
            (*it)->idle();
        }
    }
}

namespace simge { namespace glut {
        
void addIdleWorker(IdleWorker* idleWorker)
{
    // Every time we add an IdleWorker we
    // reload the glutIdleFunc. It needs to be done only once
    // but calling it more than one does no harm.
    glutIdleFunc(&idleFunc);

    idleWorkers.push_back(idleWorker);
}

void removeIdleWorker(IdleWorker* idleWorker)
{
    idleWorkers.remove(idleWorker);
}

} } // namespace glut/simge

