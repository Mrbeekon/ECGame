#pragma once
#include "stdafx.h"

class Random
{
public:
    Random(void);    
    Random(unsigned int seed);
    int Next(void);
    int Next(int max);
    int Next(int min, int max);
    double NextDouble(void);
};
