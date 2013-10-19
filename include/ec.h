#pragma once
#ifndef EC_H
#define EC_H

typedef unsigned char       byte;       // Unsigned Byte
typedef char                sbyte;      // Signed Byte
typedef unsigned short      ushort;     // Unsigned Short
typedef unsigned int        uint;       // Unsigned Int
typedef unsigned long       ulong;      // Unsigned Long
typedef ushort              WORD;       // A 16-bit Word
typedef uint                DWORD;      // A 32-bit Word
typedef unsigned long long  QWORD;      // A 64-bit Word

#define PI                  3.1415926535897

// Only put global includes here.
// No headers from inludes/ should be here.
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include "SDL/SDL.h"

using namespace std;

#endif
