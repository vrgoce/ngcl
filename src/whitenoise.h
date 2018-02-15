// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef WHITENOISE_H
#define WHITENOISE_H

#include "rng.h"

namespace Noice {
//Number of waves in the pool
static const unsigned int WavesNumber = 10000;
//Multiplier for the wave function (Wave Function = (Wave Number + 1) * Wave Step)
static const unsigned int WaveStep = 3;
//Starting wave function number
static const unsigned int StartWaveNumber = 17;
//Number of waves used into the generation of the noise
static const unsigned int NoiseNumberWaves = 64;
}

/**
 * @brief The WhiteNoise class
 * White noise generator
 */
class WhiteNoise : public RNG
{
public:

    /**
     * @brief generate Generate new 32 bytes hash
     * @return New random number
     */
    uint256_t generate();

    /**
     * @brief WhiteNoise Constructor
     */
    WhiteNoise();

private:
    /**
     * @brief m_waveNumber Current wave function number
     */
    unsigned int m_waveNumber;

    /**
     * @brief m_waves List of waves
     */
    unsigned int m_waves[Noice::WavesNumber];
};

#endif // WHITENOISE_H
