#pragma once
#ifndef C_TYPES_H
#define C_TYPES_H

typedef unsigned char       byte;       // Unsigned Byte
typedef char                sbyte;      // Signed byte
typedef unsigned short      ushort;     // Unsigned short
typedef unsigned int        uint;       // Unsigned int
typedef unsigned long       ulong;      // Unsigned long
typedef ushort              WORD;       // A 16-bit word
typedef uint                DWORD;      // A 32-bit word
typedef unsigned long long  QWORD;      // A 64-bit word

#define PI                  3.1415926535897

// Check to see if value, v, contains flag, f
// (Use in place of boolean expression)
#define HASFLAG(v, f)       v & f == f

// [Experimental] Declare an enum member with
// a value suitable for being a flag
#define DECFLAG(f)          f = 1 << f


#endif
