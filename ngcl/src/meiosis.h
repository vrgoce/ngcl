// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MEIOSIS_H
#define MEIOSIS_H

#include "hashgenerator.h"
#include "cell.h"

class Meiosis : public Cell
{
public:
    Meiosis(const uint256_t& motherChromosomes, const uint256_t& fatherChromosomes, const uint32_t& telomereSize = 179424673, bool imortal = false);

    /**
     * @brief generate Generate new 32 bytes hash
     * @return New random number
     */
    uint256_t generate();

private:
    uint32_t m_padding;
};

#endif // MEIOSIS_H
