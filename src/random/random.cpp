#include "random.h"
#include "rng.h"
#include "whitenoise.h"
#include "meiosis.h"

Random::Random(RNG *rng):
    m_rng(rng),
    m_randSize(-1)
{}

Random::~Random()
{
    cleanUp();
}

void Random::skip(unsigned int size)
{
    for(unsigned int i = 0; i < size; i++)
    {
        if(m_randSize < 0)
        {
            m_randData = m_rng->generate();
            m_randSize = m_randData.size() - 1;
        }
        m_randSize--;
    }
}

void Random::randr(void *_container, unsigned int size)
{
    char * container = (char*)_container;
    for(unsigned int i = 0; i < size; i++)
    {
        if(m_randSize < 0)
        {
            m_randData = m_rng->generate();
            m_randSize = m_randData.size() - 1;
        }
        container[i] = m_randData[m_randSize];
        m_randSize--;
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

void Random::cleanUp()
{
    if(m_rng)
    {
        delete m_rng;
        m_rng = 0;
    }
    m_randSize = -1;
}
