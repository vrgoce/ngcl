// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CELL_H
#define CELL_H

#include "bytearray.h"
#include "rng.h"

/**
 * @brief The Cell class Simplified representation of cell from living organism
 */
class Cell : public RNG
{
public:
    /**
     * @brief Cell Constructor for cell
     * @param motherChromosomes Chromosomes inherited from the mother
     * @param fatherChromosomes Chromosomes inherited from the father
     * @param telomereSize Telomere size, protection mechanism for the cell,
     * it will stop dividing when they telomere become too short
     * @param imortal Is the cell immortal, if the cell is immortal will not die when the telomere become too short
     */
    Cell(const byteArray32& motherChromosomes, const byteArray32& fatherChromosomes, const uint32_t& telomereSize, bool imortal);

    /**
     * @brief divided Set that the division process is finished, the telomere will be shortened
     */
    void divided();

    /**
     * @brief isNearEnd Check if the cell is near the end of it's life.
     * @return true: near the end, false: good condition
     */
    bool isNearEnd();

    /**
     * @brief restart Restart the cell with new chromosomes sets and regrow the telomere
     * @param motherChromosomes Chromosomes inherited from the mother
     * @param fatherChromosomes Chromosomes inherited from the father
     */
    void restart(const byteArray32& motherChromosomes, const byteArray32& fatherChromosomes);

    /**
     * @brief flip Mutate one letter in the chromosomes set
     * @param bitNumber The bit that will be fliped
     * @param chromosomes Chromosomes set to be mutated
     * @return Success of the operation
     */
    static bool flip(uint32_t bitNumber, byteArray32& chromosomes);

    /**
     * @brief flip Mutate one letter in the chromosomes set
     * @param bitNumber The bit that will be fliped
     * @return Success of the operation
     */
    bool flip(uint32_t bitNumber);

    /**
     * @brief rotate Rotate byte in the the chromosomes set
     * @param byteNumber The byte that will be rotated
     * @param chromosomes Chromosomes set to be mutated
     * @return Success of the operation
     */
    static bool rotate(uint32_t byteNumber, byteArray32& chromosomes);

    /**
     * @brief rotate Rotate byte in the the chromosomes set
     * @param byteNumber The byte that will be rotated
     * @return Success of the operation
     */
    bool rotate(uint32_t byteNumber);


    /**
     * @brief substitute Substitute piece of DNA from mother to father chromosomes set
     * @param byteNumber Location of the piece
     * @param nextByte Next piece for substitution
     * @return Success of the operation
     */
    bool substitute(uint32_t byteNumber, uint32_t& nextByte);

    /**
     * @brief cascadeSubstitute Cascade substitution
     * @param numberOfSubstitutions Total number of substitutions
     * @param byteNumber Start byte in the substitution process
     * @return Success of the operation
     */
    bool cascadeSubstitute(uint32_t numberOfSubstitutions, uint32_t byteNumber);

    /**
     * @brief restarting Is the cell restarting
     * @return true: restarting, false: not restarting
     */
    bool restarting() const;

    /**
     * @brief setRestarting Set restarting attribute for the cell
     * @param restarting true: restarting, false: not restarting
     */
    void setRestarting(bool restarting);

    /**
     * @brief generate Generate new 32 bytes hash
     * @return New random number
     */
    byteArray32 generate();

protected:
    byteArray32 m_motherChromosomes;
    byteArray32 m_fatherChromosomes;
    uint32_t m_currentTelomereSize;
    uint32_t m_telomereSize;
    bool m_imortal;
    bool m_restarting;
};

#endif // CELL_H
