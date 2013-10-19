#pragma once
#ifndef EC_H
#define EC_H

typedef unsigned char       byte;       // Unsigned Byte
typedef char                sbyte;      // Signed byte
typedef unsigned short      ushort;     // Unsigned short
typedef unsigned int        uint;       // Unsigned int
typedef unsigned long       ulong;      // Unsigned long
typedef ushort              WORD;       // A 16-bit word
typedef uint                DWORD;      // A 32-bit word
typedef unsigned long long  QWORD;      // A 64-bit word

#define PI                  3.1415926535897

// Only put global includes here.
// No headers from inludes/ should be here.
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include "SDL/SDL.h"

#endif
