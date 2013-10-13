#include "Random.h"

Random::Random(void) /* C Random number generator initialised on constructor call */
{
    srand(time(NULL));
}
    
Random::Random(unsigned int seed)
{
    srand(seed);
}

int Random::Next(void) /* rand() only returns a 16-bit integer, which means a random 
                        * colour via rand() could only be some mix of blue and green */
{
    return rand() | rand() << 16;
}

int Random::Next(int max)
{
    return Next() % (max + 1);
}

int Random::Next(int min, int max)
{
    return Next() % ((max - min) + 1) + min;
}

double Random::NextDouble(void)
{
    return Next() / 2147483647.0;
}
