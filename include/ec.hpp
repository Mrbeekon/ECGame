#pragma once
#ifndef EC_H
#define EC_H

#ifndef __cplusplus__
#define __cplusplus__
#endif

/* Global External Includes */
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

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

#define PI          3.1415926535897

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

#endif
