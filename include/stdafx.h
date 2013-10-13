#pragma once

typedef unsigned char       byte;       // Unsigned Byte
typedef char                sbyte;      // Signed byte
typedef unsigned short      ushort;     // Unsigned short
typedef unsigned int        uint;       // Unsigned int
typedef unsigned long       ulong;      // Unsigned long
typedef wchar_t             wchar;      // A Unicode Character (Wide Character)
typedef ushort              WORD;       // A 16-bit word
typedef uint                DWORD;      // A 32-bit word
typedef unsigned long long  QWORD;      // A 64-bit word

#define PI                  3.1415926535897

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>

#include <SDL/SDL.h>

#include "Random.h"
#include "Colour.h"
#include "Screen.h"

using namespace std;
