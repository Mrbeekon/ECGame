#pragma once
#ifndef STDAFX_H
#define STDAFX_H

typedef unsigned char       byte;       // Unsigned Byte
typedef char                sbyte;      // Signed byte
typedef unsigned short      ushort;     // Unsigned short
typedef unsigned int        uint;       // Unsigned int
typedef unsigned long       ulong;      // Unsigned long
typedef ushort              WORD;       // A 16-bit word
typedef uint                DWORD;      // A 32-bit word
typedef unsigned long long  QWORD;      // A 64-bit word

#define PI                  3.1415926535897

#define HASFLAG(v, f)       v & f == f  // Check to see if value, v, contains flag, f (Use in place of boolean expression)
#define DECFLAG(f)          f = 1 << f  // [Experimental] Declare an enum member with a value suitable for being a flag

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>

#include <SDL/SDL.h>

#include "Random.h"
#include "Colour.h"
#include "InputMan.h"
#include "Screen.h"

using namespace std;

#endif
