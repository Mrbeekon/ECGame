#pragma once
#include "stdafx.h"

class Random
{
public:
    Random(void);                   // Initialise
    Random(uint seed);              // Initialise with a seed
    int next(void);                 // Returns the next random integer
    int next(int max);              // Returns the next random integer, with a specified maximum
    int next(int min, int max);     // Returns the next random integer, with a specified range
    double next_double(void);       // Returns the next random double
private:
    int _get_rand_int();
};
