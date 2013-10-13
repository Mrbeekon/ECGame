#pragma once
#include "stdafx.h"

class Random
{
public:
    Random(void);    
    Random(uint seed);
    int Next(void);
    int Next(int max);
    int Next(int min, int max);
    double NextDouble(void);
private:
    int _getRandInt();
};
