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

#ifndef SIMGE_UTIL_CONVERSION_HPP_INCLUDED
#define SIMGE_UTIL_CONVERSION_HPP_INCLUDED

namespace simge { namespace util
{
	/**
	 * Convert degree to radian.
	 * 
	 * @pre degree >= 0 and degree < 360.0
	 */
	inline double degreeToRadian(double degree)
	{
		return degree * 0.01745329251994329576;
	}
	
	/**
	 * Convert radian to degree.
	 * 
	 * @pre radian >= 0 and radian < 2*pi
	 */
	inline double radianToDegree(double radian)
	{
		return radian * 57.29577951308232087721;
	}
	
} } // namespace util/simge

#endif
