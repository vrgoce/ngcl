// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RNG_H
#define RNG_H

#include "bytearray.h"
#include "hashgenerator.h"

/**
 * @brief The RNG class Base class for random number generators.
 */
class RNG
{
public:
    virtual uint256_t generate() = 0;

    void feed(const char *input, unsigned int length)
    {
        if(m_hash)
        {
            m_hash->Update((const unsigned char *)input, length);
        }
    }

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

#endif // RNG_H
