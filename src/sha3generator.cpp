// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "sha3generator.h"
#include "serialize.h"
#include "external/hash-library/sha3.h"

SHA3Generator::SHA3Generator():
    m_sha(0)
{
    m_sha = new SHA3();
}

SHA3Generator::~SHA3Generator()
{
    delete m_sha;
    m_sha = 0;
}

void SHA3Generator::Update(const unsigned char *input, unsigned int length)
{
    m_sha->add(input, length);
}

void SHA3Generator::Restart()
{
    m_sha->reset();
}

void SHA3Generator::Final(unsigned char *digest)
{
    std::string hashStr = m_sha->getHash();
    //convert it to bytes in order to keep the original interface for SHA3
    serialize::hex2bin(hashStr.c_str(), (char *) digest);
}

