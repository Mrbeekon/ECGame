#pragma once
#ifndef RANDOM_H
#define RANDOM_H

#include "ec.hpp"

class Random
{
public:
    // Initialise
    Random(void);
    
    // Initialise with a seed
    Random(uint seed);
    
    // Returns the next random integer
    int next(void);
    
    // Returns the next random integer, with a specified maximum
    int next(uint max);
    
    // Returns the next random integer, with a specified range
    int next(uint min, uint max);
    
    // Returns the next random double
    double next_double(void);
private:    
    // Function to acquire a 32-bit random
    int _get_rand_int();
};

#endif

