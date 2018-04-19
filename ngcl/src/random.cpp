// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "../include/random.h"
#include "rng.h"
#include "whitenoise.h"
#include "meiosis.h"
#include "serialize.h"
#include "bytearray.h"

#include <stdlib.h>

class RandomPrivate
{
public:
    RandomPrivate(std::string key1, std::string key2):
        m_rng(0),
        m_randSize(-1)
    {
        if(key1.size() > 63 && key2.size() > 63 &&
                serialize::isHexStr(key1) && serialize::isHexStr(key2))
        {
            m_rng = new Meiosis(key1, key2);
        }
        else
        {
            m_rng = new WhiteNoise();

            if(!key1.empty())
            {
                m_rng->feed(key1.c_str(), key1.length());
            }
            if(!key2.empty())
            {
                m_rng->feed(key2.c_str(), key2.length());
            }
        }
    }

    RNG* m_rng;
    byteArray32 m_randData;
    int m_randSize;
};

Random::Random(std::string key1, std::string key2):
    d(0)
{
    d = new RandomPrivate(key1, key2);
}

Random::~Random()
{
    cleanUp();
}

Random::Random(const Random &)
{

}

void Random::skip(unsigned int size)
{
    for(unsigned int i = 0; i < size; i++)
    {
        if(d->m_randSize < 0)
        {
            d->m_randData = d->m_rng->generate();
            d->m_randSize = d->m_randData.size() - 1;
        }
        d->m_randSize--;
    }
}

void Random::feed(const char *input, unsigned int length)
{
    d->m_randSize = -1;
    d->m_rng->feed(input, length);
}

void Random::randr(void *_container, unsigned int size)
{
    char * container = (char*)_container;
    for(unsigned int i = 0; i < size; i++)
    {
        if(d->m_randSize < 0)
        {
            d->m_randData = d->m_rng->generate();
            d->m_randSize = d->m_randData.size() - 1;
        }
        container[i] = d->m_randData[d->m_randSize];
        d->m_randSize--;
    }
}

double Random::randf()
{
    double ret;
    randr(&ret, sizeof(ret));
    return ret;
}

int Random::randi()
{
    int ret;
    randr(&ret, sizeof(ret));
    return ret;
}

int Random::randb(int base)
{
    if(base == 0) return 0;

    int ret = randi();
    ret %= base;
    ret = abs(ret);
    if(base < 0) ret = - ret;

    return ret;
}

double Random::rand1()
{
    int first = randi();
    int second = randi();
    first = abs(first);
    second = abs(second);
    if(first == 0 || second == 0) return 0;
    double ret =  first > second ? first / (double) second : second / (double) first;
    return 1/ret;
}

std::string Random::randHex(int size)
{
    std::string hexString;
    if(size > 0)
    {
        unsigned char * buffer = new unsigned char[size];
        randr(buffer, size);
        hexString = serialize::bin2hex(buffer, size);
    }
    return hexString;
}

bool Random::isSeedLess()
{
    return dynamic_cast<WhiteNoise*>(d->m_rng) != 0;
}

void Random::cleanUp()
{
    delete d;
    d = 0;
}
