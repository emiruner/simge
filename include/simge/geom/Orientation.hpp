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

#ifndef SIMGE_GEOM_ORIENTATION_HPP_INCLUDED
#define SIMGE_GEOM_ORIENTATION_HPP_INCLUDED

#include <simge/util/Enum.hpp>
#include <ostream>

namespace simge { namespace geom
{
	
class Orientation : public util::Enum<int>
{
private:
	Orientation(int value)
	: util::Enum<int>(value)
	{
	}
	
public:
    inline static Orientation nil()
    {
        return Orientation(-1);
    }
    
	inline static Orientation Left()
	{
		return Orientation(0);
	}
	
	inline static Orientation Right()
	{
		return Orientation(1);
	}
	
	inline static Orientation Beyond()
	{
		return Orientation(2);
	}
	
	inline static Orientation Behind()
	{
		return Orientation(3);
	}
	
	inline static Orientation Between()
	{
		return Orientation(4);
	}
	
	inline static Orientation Origin()
	{
		return Orientation(5);
	}
	
	inline static Orientation Destination()
	{
		return Orientation(6);
	}	
};

} } // namespace geom/simge

#endif
