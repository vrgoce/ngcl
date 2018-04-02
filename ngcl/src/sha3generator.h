// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SHA3GENERATOR_H
#define SHA3GENERATOR_H
#include "hashgenerator.h"

class SHA3;
/**
 * @brief The SHA3Generator class Implementation of the hash generator that use SHA 3 as hashing algorithm.
 */
class SHA3Generator: public HashGenerator
{
public:
    SHA3Generator();
    ~SHA3Generator();
    void Update(const unsigned char *input, unsigned int length);
    void Restart();
    void Final(char unsigned *digest);

private:
    SHA3* m_sha;
};

#endif // SHA3GENERATOR_H
