#pragma once
#include "stdafx.h"

class Random
{
public:
    Random(void);                   // Initialise
    Random(uint seed);              // Initialise with a seed
    int Next(void);                 // Returns the next random integer
    int Next(int max);              // Returns the next random integer, with a specified maximum
    int Next(int min, int max);     // Returns the next random integer, with a specified range
    double NextDouble(void);        // Returns the next random double
private:
    int _getRandInt();
};
