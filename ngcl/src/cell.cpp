// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "cell.h"

Cell::Cell(const byteArray32 &motherChromosomes, const byteArray32 &fatherChromosomes, const uint32_t &telomereSize, bool imortal):
    m_motherChromosomes(motherChromosomes),
    m_fatherChromosomes(fatherChromosomes),
    m_currentTelomereSize(telomereSize),
    m_telomereSize(telomereSize),
    m_imortal(imortal),
    m_restarting(false)
{}

void Cell::divided()
{
    m_currentTelomereSize--;
}

bool Cell::isNearEnd()
{
    return !m_imortal && m_currentTelomereSize < 3;
}

void Cell::restart(const byteArray32 &motherChromosomes, const byteArray32 &fatherChromosomes)
{
    m_motherChromosomes = motherChromosomes;
    m_fatherChromosomes = fatherChromosomes;
    m_currentTelomereSize = m_telomereSize;
}

bool Cell::flip(uint32_t bitNumber, byteArray32 &chromosomes)
{
    uint32_t currentByte = bitNumber / 8;
    uint32_t currentBit = bitNumber % 8;
    if(currentByte < chromosomes.size())
    {
        uint8_t b = chromosomes[currentByte];
        b ^= 1 << currentBit;
        chromosomes[currentByte] = b;
        return true;
    }
    return false;
}

bool Cell::flip(uint32_t bitNumber)
{
    uint32_t chromosomesSize = m_motherChromosomes.size() * 8;
    return bitNumber < chromosomesSize ?
                flip(bitNumber, m_motherChromosomes) :
                flip(bitNumber - chromosomesSize, m_fatherChromosomes);
}

bool Cell::rotate(uint32_t byteNumber, byteArray32 &chromosomes)
{
    if(byteNumber < chromosomes.size())
    {
        uint8_t b = chromosomes[byteNumber];
        b = b % 2 << 7 | b >> 1;
        chromosomes[byteNumber] = b;
        return true;
    }
    return false;
}

bool Cell::rotate(uint32_t byteNumber)
{
    return byteNumber < m_motherChromosomes.size() ?
                rotate(byteNumber, m_motherChromosomes) :
                rotate(byteNumber - m_motherChromosomes.size(), m_fatherChromosomes);
}

bool Cell::substitute(uint32_t byteNumber, uint32_t &nextByte)
{
    if(byteNumber < m_motherChromosomes.size())
    {
        uint8_t a = m_motherChromosomes[byteNumber];
        uint32_t byteNumber2 = a % m_fatherChromosomes.size();
        uint8_t b = m_fatherChromosomes[byteNumber2];
        m_motherChromosomes[byteNumber] = b;
        m_fatherChromosomes[byteNumber2] = a;
        nextByte = b % m_motherChromosomes.size();
        return true;
    }
    return false;
}

bool Cell::cascadeSubstitute(uint32_t numberOfSubstitutions, uint32_t byteNumber)
{
    for(uint32_t i = 0; i < numberOfSubstitutions; i++)
    {
        if(!substitute(byteNumber, byteNumber)) return false;
    }
    return true;
}

bool Cell::restarting() const
{
    return m_restarting;
}

void Cell::setRestarting(bool restarting)
{
    m_restarting = restarting;
}

byteArray32 Cell::generate()
{
    // dummy implementation
    return byteArray32();
}
