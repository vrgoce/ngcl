// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include <stdint.h>
#include "serialize.h"

/**
 * @brief The HashGenerator class Base class for hash generators.
 */
class HashGenerator
{
public:
    virtual void Update(const unsigned char *input, unsigned int length) = 0;
    void Update(const uint32_t& input)
    {
        uint8_t data[sizeof(input)];
        serialize::toBytes(input, data);
        Update(data, sizeof(input));
    }
    virtual void Restart() = 0;
    virtual void Final(char unsigned *digest) = 0;
    virtual ~HashGenerator() {}
};

#endif // NOISEGENERATOR_H
