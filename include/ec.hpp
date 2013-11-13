#ifndef EC_H
#define EC_H

#ifndef __cplusplus__
#define __cplusplus__
#endif

/* Global External Includes */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "SDL/SDL.h"

/* Type Definitions */
typedef unsigned char       byte;       // Unsigned Byte
typedef char                sbyte;      // Signed Byte
typedef unsigned short      ushort;     // Unsigned Short
typedef unsigned int        uint;       // Unsigned Int
typedef unsigned long       ulong;      // Unsigned Long
typedef ushort              WORD;       // A 16-bit Word
typedef uint                DWORD;      // A 32-bit Word
typedef unsigned long long  QWORD;      // A 64-bit Word

/* Definitions */

#ifndef M_PI // Would be in cmath
#define M_PI        3.14159265358979323846264338327
#endif

#define PI          M_PI

#define DEFWIDTH    1024
#define DEFHEIGHT   768
#define FPS         60

#define TITLE       "ECGame"

/* Other Types */
// Tick Attributes
struct TickAtt
{
    // The current tick. Never resets, so also a measure of up-time.
    ulong tick;
    // Time (in milliseconds) since the last tick. (Roughly 1000 / FPS)
    uint last;
};

// For useful utility and helper methods
namespace utils
{
    // Converts a character string representing a hexadecimal number,
    // eg "0xfe", to an integer type of that number
    inline int hex_str_to_int(std::string str)
    {
        std::stringstream converter(str);
        int i;
        converter >> std::hex >> i;
        return i;
    }

    // Converts an integer to a string
    // (until std::to_string() gets fixed (soonish))
    inline std::string int_to_string(int i)
    {
        std::stringstream converter;
        converter << i;
        return converter.str();
    }
}

#endif
