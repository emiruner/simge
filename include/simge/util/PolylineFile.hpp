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

#ifndef SIMGE_UTIL_POLYLINEFILE_HPP_INCLUDED
#define SIMGE_UTIL_POLYLINEFILE_HPP_INCLUDED

#include <istream>
#include <vector>
#include <stdexcept>

#include <simge/util/Polyline.hpp>

namespace simge { namespace util
{

inline void readPoint(std::istream& in, geom::Point<2>& p)
{
    in >> p[0] >> p[1];
}
    
inline void readPoint(std::istream& in, geom::Point<3>& p)
{
    in >> p[0] >> p[1] >> p[2];
}
    
/**
 * Interprets a polyline file.
 */
template <typename PointType>
class PolylineFile
{
public:
    /**
     * Read data from the given stream.
     */
    PolylineFile(std::istream& in)
    : in_(in)
    {
        in_ >> count_;
        if(in_.bad())
        {
            throw std::runtime_error("polyline file error while "
                                     "reading line count");
        }
    }
    
    /**
     * Get the count of polylines.
     */
    inline int getPolylineCount() const
    {
        return count_;
    }
    
    /**
     * Return the next polyline.
     * Throws std::runtime_error in case of any syntax/io error.
     */
    Polyline<PointType> getNext()
    {
        int pointCount;
        bool closed;
        Polyline<PointType> result;
        char ch;
                
        in_ >> pointCount;
        if(!in_.bad())
        {
            if(pointCount < 0)
            {
                closed = true;
                pointCount *= -1;
            }
            else
            {
                closed = false;
            }
    
            in_ >> ch;
            in_.putback(ch);
            
            if(ch == '#')
            {
                in_ >> result.color;
            }
            else
            {
                result.color = Color::black();
            }
            
            if(!in_.bad())
            {        
                int i ;
            
                for(i = 0; i < pointCount; ++i)
                {
                    PointType point;
                    
                    readPoint(in_, point);
                    
                    if(in_.fail())
                    {
                        break;
                    }
                
                    result.points.push_back(point);
                }
            
                if(i == pointCount)
                {
                    if(closed)
                    {
                        result.points.push_back(*result.points.begin());
                    }
                    
                    return result;
                }
            }
        }

        throw std::runtime_error("polyline file format not correct");
    }
    
private:
    std::istream& in_;
    int count_;
};
 
} } // namespace util/simge

#endif
