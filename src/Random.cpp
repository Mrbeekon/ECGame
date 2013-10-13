#include "Random.h"

Random::Random(void)
{
    srand(time(NULL)); // Initialise C's random number generator upon initialisation. Default seed it time.
}
    
Random::Random(unsigned int seed)
{
    srand(seed);
}

int Random::Next(void)
{
    return rand() | rand() << 16; // rand() only returns a 16-bit integer (which is a bit rubbish)

    /* The reason we don't do:
     *
     * int r = rand();
     * return r | r << 16;
     *
     * is because otherwise 'r & 0xffff' would always equal to 'r >> 16 & 0xffff', which isn't very random.
     */
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
