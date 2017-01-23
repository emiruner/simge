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

#ifndef SIMGE_UTIL_COLOR_HPP_INCLUDED
#define SIMGE_UTIL_COLOR_HPP_INCLUDED

#include <iosfwd>

namespace simge { namespace util
{

/**
 * Holds 16-bit per component. Used for file I/O.
 */    
struct Color
{
    int r;
    int g;
    int b;

    void normalize(float& fr, float& fg, float& fb) const
    {
        fr = static_cast<float>(r) / 65535;
        fg = static_cast<float>(g) / 65535;
        fb = static_cast<float>(b) / 65535;
    }
        
    Color()
    {
    }
    
    Color(int nr, int ng, int nb)
    : r(nr & 0xffff), g(ng & 0xffff), b(nb & 0xffff)
    {
    }
    
    Color(double nr, double ng, double nb)
    : r((int)(nr * 65535)), g((int)(ng * 65535)), b((int)(nb * 65535))
    {
        r &= 0xffff;
        g &= 0xffff;
        b &= 0xffff;
    }
    
    static Color white() { return Color(65535, 65535, 65535); }
    static Color black() { return Color(0, 0, 0); }
    static Color red() { return Color(65535, 0, 0); }
    static Color green() { return Color(0, 65535, 0); }
    static Color blue() { return Color(0, 0, 65535); }
};

/**
 * Calls glColor
 */
void color(Color const& color);

/**
 * Calls glClearColor
 */
void clearColor(Color const& color);

/**
 * In-equality.
 */    
bool operator!=(Color const& lhs, Color const& rhs);

/**
 * Reads a color formatted as one of #rgb, #rrggbb or #rrrrggggbbbb
 */
std::istream& operator>>(std::istream& in, Color& color);

/**
 * Writes the color in the smallest form that is possible.
 */
std::ostream& operator<<(std::ostream& out, Color const& color);

} } // namespace util/simge

#endif
