// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "meiosis.h"
#include "sha3generator.h"
#include "serialize.h"

//Number of rotation cycles
static const unsigned int RotationCycles = 8;

//Prime numbers for constants
static const unsigned int Padding = 3;
static const unsigned int MinimumSubstitutions = 2;
static const unsigned int PotentialSubstitutions = 11;
static const unsigned int NumberBitsPrime = 509;
static const unsigned int TotalBytesPrime = 61;
static const unsigned int ParentBytesPrime = 31;


Meiosis::Meiosis(const uint256_t &motherChromosomes, const uint256_t &fatherChromosomes, const uint32_t &telomereSize, bool imortal):
    Cell(motherChromosomes, fatherChromosomes, telomereSize, imortal),
    m_padding(0)
{
    m_hash = new SHA3Generator();
    //throw the first number
    generate();
}

uint256_t Meiosis::generate()
{
    //Restart the process
    if(!restarting() && isNearEnd())
    {
        setRestarting(true);
        restart(generate(), generate());
        setRestarting(false);
    }

    //Generate random number
    uint256_t randomNumber, mutateNumber;
    m_hash->Update(m_motherChromosomes, m_motherChromosomes.size());
    m_hash->Update(m_fatherChromosomes, m_fatherChromosomes.size());
    m_hash->Final(randomNumber);
    m_hash->Update(m_telomereSize);
    m_hash->Final(mutateNumber);

    //Mutate the source in the generator
    uint32_t mutateSrc[RotationCycles];
    serialize::listFromBytes<uint32_t, RotationCycles>(mutateNumber, mutateSrc);

    uint32_t count = 0;
    for(unsigned int  i = 0; i < RotationCycles; i++)
    {
        flip(mutateSrc[i] % NumberBitsPrime + m_padding);
        rotate(mutateSrc[i] % TotalBytesPrime + m_padding);
        count += mutateSrc[i] % ParentBytesPrime + m_padding;
        m_padding++;
        m_padding %= Padding;
    }
    cascadeSubstitute(MinimumSubstitutions + count % PotentialSubstitutions, count % ParentBytesPrime);

    divided();

    return randomNumber;
}
