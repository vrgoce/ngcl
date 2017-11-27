#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "bytearray.h"
#include "hashgenerator.h"

/**
 * @brief The RNG class Base class for random number generators.
 */
class RNG
{
public:
    virtual uint256_t generate() = 0;
    virtual ~RNG()
    {
        if(m_hash)
        {
            delete m_hash;
            m_hash = 0;
        }
    }
    RNG():
        m_hash(0)
    {}

protected:
    /**
     * @brief m_hash Pointer to the hasher
     */
    HashGenerator* m_hash;
};

#endif // RANDOMGENERATOR_H
