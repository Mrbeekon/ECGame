#pragma once
#include <stdlib.h>
#include <time.h>

class Random
{
public:
    Random(void);    
    Random(unsigned int);
    int Next(void);
    int Next(int);
    int Next(int min, int max);
    double NextDouble(void);
};