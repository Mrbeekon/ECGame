#pragma once
#ifndef EC_H
#define EC_H
#ifndef __cplusplus__
#define __cplusplus__
#endif

/* Type Definitions */
typedef unsigned char       byte;       // Unsigned Byte
typedef char                sbyte;      // Signed Byte
typedef unsigned short      ushort;     // Unsigned Short
typedef unsigned int        uint;       // Unsigned Int
typedef unsigned long       ulong;      // Unsigned Long
typedef ushort              WORD;       // A 16-bit Word
typedef uint                DWORD;      // A 32-bit Word
typedef unsigned long long  QWORD;      // A 64-bit Word

#define PI          3.1415926535897

#define DEFWIDTH    1024
#define DEFHEIGHT   768
#define FPS         60

#define TITLE       "ECGame"

// Only put global includes here.
// No headers from inludes/ should be here.
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "SDL/SDL.h"

/* Global Namespace Usings */
using namespace std;

#endif
