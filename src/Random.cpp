#include "Random.h"

Random::Random(void)
{
    srand(time(NULL)); // Initialise C's random number generator upon initialisation. Default seed is time.
}
    
Random::Random(uint seed)
{
    srand(seed);
}

int Random::Next(void)
{
    return _getRandInt();
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
    return (double)Next() / RAND_MAX;
}

int Random::_getRandInt()
{
    return rand() & 0xff | rand() & 0xff << 8 | rand() & 0xff << 16 | rand() & 0xff << 24;
    
    // rand() only returns a 16-bit integer (which is a bit rubbish).
    // Also, only 15 of those 16 bits are used (hence RAND_MAX = 0x7fff).

    /* The reason we don't do:
     *      int r = rand();
     *      return r & 0xff | r & 0xff << 8 | r & 0xff << 16 | r & 0xff << 24;
     * is because otherwise 'r & 0xff' would always be equal to 'r >> 16 & 0xff' etc, which isn't very random.
     *
     * Therefore, whenever Random::Next() is called, it's actually an itteration of four randoms (may be necessary to know).
     */
}