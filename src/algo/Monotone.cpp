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

#include <simge/algo/Monotone.hpp>
#include <simge/geom/Edge.hpp>
#include <simge/util/Enum.hpp>

#include <deque>

using namespace simge::geom;
using namespace simge::util;

namespace
{
    template <typename T>
    class SimpleStack
    {
    private:
        std::deque<T> q_;
        
    public:
        inline T top() const
        {
            return q_.front();
        }
        
        inline T nextToTop() const
        {
            return *(++q_.begin());
        }
        
        inline T bottom() const
        {
            return *(--q_.end());
        }
        
        inline void push(T t)
        {
            q_.push_front(t);
        }
        
        inline void pop()
        {
            q_.pop_front();
        }
        
        inline bool isEmpty()
        {
            return q_.begin() == q_.end();
        }
        
        inline void clear()
        {
            q_.clear();
        }
        
        inline int size()
        {
            return q_.size();
        }
    };

    class Chain : public Enum<int>
    {
    private:
        Chain(int value)
        : Enum<int>(value)
        {
        }
        
    public:
        inline static Chain Upper()
        {
            return Chain(0);
        }
        
        inline static Chain Lower()
        {
            return Chain(1);
        }
    };

    struct ChainIterator
    {
        
        Polygon<2> const* p;
        Polygon<2>::const_iterator it;
        Chain chain;
        
        ChainIterator(Polygon<2> const& poly, Polygon<2>::const_iterator iter, Chain ch)
        : p(&poly), it(iter), chain(ch)
        {
        }

        void prev()
        {
            if(it == p->begin())
            {
                it = p->end();
            }

            --it;
        }

        void next()
        {
            ++it;
            
            if(it == p->end())
            {
                it = p->begin();
            }
        }   

        inline ChainIterator& operator++()
        {
            if(chain == Chain::Upper())
            {
                next();
            }
            else
            {
                prev();
            }

            return *this;
        }

        inline ChainIterator& operator--()
        {
            if(chain == Chain::Upper())
            {
                prev();
            }
            else
            {
                next();
            }

            return *this;
        }

    };
    
    inline bool operator==(ChainIterator const& ti, ChainIterator const& bi)
    {
        return ti.it == bi.it;
    }

    inline bool operator!=(ChainIterator const& ti, ChainIterator const& bi)
    {
        return ti.it != bi.it;
    }

    inline bool operator<(Point<2> const& p1, Point<2> const& p2)
    {
        return p1[0] < p2[0] || (p1[0] == p2[0] && p1[1] < p2[1]);
    }
    
    Polygon<2>::const_iterator findLeftmost(Polygon<2> const& p)
    {
        Polygon<2>::const_iterator it = p.begin();
        Polygon<2>::const_iterator leftmost = p.begin();
        const Polygon<2>::const_iterator end = p.end();
        
        ++it;
        while(it != end)
        {
            Point<2> leftmostPt(*leftmost);
            Point<2> currentPt(*it);

            if(currentPt < leftmostPt)
            {
                leftmost = it;
            }
            
            ++it;
        }

        return leftmost;
    }

    template <typename T>
    inline T next(T t)
    {
        return ++t;
    }

    template <typename T>
    inline T prev(T t)
    {
        return --t;
    }

    Chain advance(ChainIterator& topIt, ChainIterator& bottomIt)
    {
        if(*next(topIt).it < *next(bottomIt).it)
        {
            ++topIt;
            return Chain::Upper();
        }
        else
        {
            ++bottomIt;
            return Chain::Lower();
        }
    }

    inline ChainIterator& current(ChainIterator& upperIt, ChainIterator& lowerIt, Chain chain)
    {
        if(chain == Chain::Upper())
        {
            return upperIt;
        }
        else
        {
            return lowerIt;
        }
    }
    
    typedef SimpleStack<ChainIterator> Stack;

    inline Edge<2> edge(Point<2> const& p0, Point<2> const& p1)
    {
        return Edge<2>(p0, p1);
    }
    
    inline Polygon<2> triangle(Point<2> const& p0, Point<2> const& p1, Point<2> const& p2)
    {
        Polygon<2> poly;
        
        poly.addVertex(p0);
        poly.addVertex(p1);
        poly.addVertex(p2);
        
        return poly;
    }
} // namespace <unnamed>

namespace simge { namespace algo {
        
std::vector<geom::Polygon<2> > triangulateMonotone(Polygon<2> const& p)
{
    std::vector<geom::Polygon<2> > triangles;
    ChainIterator upperIt(p, findLeftmost(p), Chain::Upper());
    ChainIterator lowerIt(p, findLeftmost(p), Chain::Lower());
    Chain chain(Chain::Upper());
    Stack s;
    const int size = p.size();

    chain = advance(upperIt, lowerIt);

    if(chain == Chain::Upper())
    {
        s.push(lowerIt);
        s.push(upperIt);
    }
    else
    {
        s.push(upperIt);
        s.push(lowerIt);
    }
    
    for(int i = 2; i < size; ++i)
    {
        chain = advance(upperIt, lowerIt);

        const ChainIterator cur = current(upperIt, lowerIt, chain);

        if(s.top().chain == chain)
        {
            Orientation side = chain == Chain::Upper() ? Orientation::Right() : Orientation::Left();

            while(s.size() > 1 && classify(edge(*s.nextToTop().it, *s.top().it), *cur.it) == side)
            {
                triangles.push_back(triangle(*cur.it, *s.nextToTop().it, *s.top().it));
                s.pop();
            }
            
            s.push(cur);
        }
        else
        {
            ChainIterator top = s.top();

            while(s.size() > 1)
            {
                triangles.push_back(triangle(*cur.it, *s.top().it, *s.nextToTop().it));
                s.pop();
            }

            s.pop();
            
            s.push(top);
            s.push(cur);
        }
    }
    
    return triangles;
}

} } // namespace algo / simge

