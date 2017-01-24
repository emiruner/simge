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

#include <simge/util/Color.hpp>
#include <GL/glut.h>

#include <string>
#include <istream>
#include <cstdlib>
#include <cstring>

namespace
{
    static char decToHexTable[] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7', 
        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };
    
    /**
     * Assumes 0 <= d <= 15.
     */
    inline char decToHex(int d)
    {
        return decToHexTable[d];
    }

    /**
     * Assumes 0 <= num <= 65535
     */
    void writeHex4(std::ostream& out, int num)
    {
        int d1 = (num & 0xf000) >> 12;
        int d2 = (num & 0x0f00) >> 8;
        int d3 = (num & 0x00f0) >> 4;
        int d4 = (num & 0x000f);
        
        out << decToHex(d1) << decToHex(d2) << decToHex(d3) << decToHex(d4);
    }
    
    /**
     * Assumes 0 <= num <= 255
     */
    void writeHex2(std::ostream& out, int num)
    {
        int d1 = (num & 0x00f0) >> 4;
        int d2 = (num & 0x000f);
        
        out << decToHex(d1) << decToHex(d2);
    }
    
    /**
     * Assumes 0 <= num <= 15
     */
    void writeHex1(std::ostream& out, int num)
    {
        int d1 = (num & 0x000f);
        
        out << decToHex(d1);
    }
    
    /**
     * Assumes that isxdigit(ch) == true
     */
    inline int hexToDec(int ch)
    {
        switch(ch)
        {
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case '0': return 0;
        case 'a': return 10;
        case 'b': return 11;
        case 'c': return 12;
        case 'd': return 13;
        case 'e': return 14;
        case 'f': return 15;
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
        }

        return -1; // Not reached.
    }
    
    /**
     * Assumes all chars except trailing null are hex digits.
     */
    inline int hextToDec(char* buf)
    {
        int value = 0;
        int digitValue = 1 << ((strlen(buf) - 1) * 4);
        
        while(*buf != '\0')
        {
            value += hexToDec(*buf) * digitValue;
            ++buf;
            digitValue >>= 4;
        }

        return value;
    }
    
    /**
     * Parses a color in a format #rgb, #rrggbb or #rrrrggggbbbb.
     * Modifies buf temporarily.
     */
    inline simge::util::Color parseColor(char* buf, int len)
    {
        simge::util::Color color;
        const int componentLen = len / 3;
        const int shiftCount = (4 - componentLen) * 4;

        int components[3];
        
        for(int i = 0; i < 3; ++i)
        {
            char tmp = buf[componentLen * (i + 1)];
            buf[componentLen * (i + 1)] = '\0';
            components[i] = hextToDec(&buf[componentLen * i]) << shiftCount;
            buf[componentLen * (i + 1)] = tmp;
        }
        
        color.r = components[0];
        color.g = components[1];
        color.b = components[2];
        
        return color;
    }
    
} // namespace <unnamed>

namespace simge { namespace util {

std::istream& operator>>(std::istream& in, simge::util::Color& color)
{
    int ch;
    
    // Skip ws.
    while(isspace(ch = in.get()));
        
    if(ch != '#')
    {
        in.setstate(std::ios::badbit);
    }
    else
    {
        std::string buf;
        int count;
        
        in >> buf;
        count = buf.size();
        
        if(count != 3 && count != 6 && count != 12)
        {
            in.setstate(std::ios::badbit);
        }
        else
        {
            int i;
            
            for(i = 0; i < count; ++i)
            {
                if(!isxdigit(buf[i]))
                {
                    in.setstate(std::ios::badbit);
                    break;
                }
            }
            
            if(i == count)
            {
                char str[13];
                strcpy(str, buf.c_str());
                
                color = parseColor(str, count);
            }
        }
    }

    return in;
}
 
std::ostream& operator<<(std::ostream& out, simge::util::Color const& color)
{
    void (*writer)(std::ostream& out, int num);

    if(color.r < 256 && color.g < 256 && color.b < 256)
    {
        if(color.r < 16 && color.g < 16 && color.b < 16)
        {
            writer = &writeHex1;
        }
        else
        {
            writer = &writeHex2;
        }
    }
    else
    {
        writer = &writeHex4;
    }
    
    out << '#';
    writer(out, color.r);
    writer(out, color.g);
    writer(out, color.b);
    
    return out;
}

bool operator!=(simge::util::Color const& lhs, simge::util::Color const& rhs)
{
    return (lhs.r != rhs.r) || (lhs.g != rhs.g) || (lhs.b != rhs.b); 
}

void color(Color const& color)
{
    glColor3i(color.r, color.g, color.b);
}

void clearColor(Color const& color)
{
    glClearColor(color.r, color.g, color.b, 0);
}
 
} } // namespace util/simge
