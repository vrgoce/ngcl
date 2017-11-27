#ifndef RANDOM_H
#define RANDOM_H

#include "bytearray.h"
class RNG;

class Random
{
public:
    Random(RNG* rng);
    ~Random();
    void skip(unsigned int size);
    void randr(void *_container, unsigned int size);
    double randf();
    int randi();
    int randb(int base);
    double rand1();

private:
    Random(Random const&);
    Random& operator=(Random const&);

    void cleanUp();

    RNG* m_rng;
    uint256_t m_randData;
    int m_randSize;
};

#endif // RANDOM_H
