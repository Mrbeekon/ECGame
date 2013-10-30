#include "Random.hpp"

Random::Random(void)
{
    // Initialise C's random number generator upon initialisation.
    // Default xseed is time.
    srand(time(NULL));
}
    
Random::Random(uint seed)
{
    srand(seed);
}

int Random::next(void)
{
    return _get_rand_int();
}

int Random::next(uint max)
{
    return next() % (max + 1);
}

int Random::next(uint min, uint max)
{
    return next() % ((max - min) + 1) + min;
}

double Random::next_double(void)
{
    return (double)next() / RAND_MAX;
}

int Random::_get_rand_int()
{
    return rand() & 0xff | (rand() & 0xff) << 8 | (rand() & 0xff) << 16 | (rand() & 0xff) << 24;
    
    // rand() only returns a 16-bit integer (which is a bit rubbish).
    // Also, only 15 of those 16 bits are used (hence RAND_MAX = 0x7fff).

    /* The reason we don't do:
     *      int r = rand();
     *      return r & 0xff | r & 0xff << 8 | r & 0xff << 16 | r & 0xff << 24;
     * is because otherwise 'r & 0xff'
     * would always be equal to 'r >> 16 & 0xff' etc, which isn't very random.
     *
     * Therefore, whenever Random::next() is called, it's actually an
     * itteration of four randoms (may be necessary to know).
     */
}
