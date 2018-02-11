// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "whitenoise.h"
#include "sha3generator.h"
#include <string>

/**
 * @brief The Wave class
 * Working with waves
 */
class Wave
{
public:
    /**
     * @brief newWave Create new wave function according to the wave number
     * @param waveNumber Wave number
     * @return Wave amplitude
     */
    static unsigned int newWave(unsigned int waveNumber)
    {
        uint64_t* tmp = new uint64_t();
        std::string buffer = memToString(tmp, sizeof(*tmp)) + memToString(&tmp, sizeof(tmp));
        delete tmp;
        return generateWave(buffer.c_str(), (waveNumber + 1) * Noice::WaveStep);
    }

    /**
     * @brief waveNumber Get the wave number from the amplitude
     * @param waveAmplitude Wave amplitude
     * @return Wave Number
     */
    static unsigned int waveNumber(unsigned int waveAmplitude)
    {
        return waveAmplitude % Noice::WavesNumber;
    }

private:
    /**
     * @brief generateWave Simple method for generating wave
     * @param input Input data for creating the wave
     * @param function Number of the function that will be used for the wave
     * @return Amplitude of the generated wave
     */
    static unsigned int generateWave(const char* input, unsigned int function)
    {
        unsigned h = function;
        while (*input)
            h = h * 101 + (unsigned int)*input++;
        return h & 0x7FFFFFFF;
    }

    /**
     * @brief memToString Convert memory to string, ignore the null bytes
     * @param data Pointer to structure
     * @param size Size of the structure
     * @return String
     */
    static std::string memToString(void * data, int size)
    {
        std::string ret;
        char * buffer = new char[size];
        int pos = 0;
        char * str = (char*)data;
        for(int i = 0; i < size; i++)
        {
            char c = str[i];
            if(c)
            {
                buffer[pos++] = c;
            }
        }
        buffer[pos] = 0;
        ret = buffer;
        delete buffer;
        return ret;
    }
};

WhiteNoise::WhiteNoise():
    m_waveNumber(0)
{
    m_hash = new SHA3Generator();
    for(unsigned int waveNumber = 0; waveNumber < Noice::WavesNumber; waveNumber++)
    {
        unsigned int waveAmplitude = Wave::newWave(waveNumber);
        unsigned int newWaveNumber = Wave::waveNumber(waveAmplitude);
        m_waves[waveNumber] = Wave::newWave(newWaveNumber);
    }
    unsigned int newWave = Wave::newWave(Noice::StartWaveNumber);
    m_waveNumber = Wave::waveNumber(newWave);
    generate();
}

/**
 * @brief WhiteNoise::generate
 * When random number is generated with size of 256 bits the probability is 1/2^256 to get the number from the generator.
 * I use chain of events that gradually reduce the probability for generating the number.
 * Every event depend on the previous event, that mean reducing the probability further and further.
 * I put the chain of events into a temporary string and hash it in order to get the random number.
 * The number of events (waves) that I use is 64. The size of the pool is 10000 waves.
 * I believe the probability for generating the temporary string is much lower than 1/2^256,
 * so the number of events and the size of the pool can probably be lower too.
 * @return Random number with size 256 bits
 */
uint256_t WhiteNoise::generate()
{
    unsigned int listWaves[Noice::NoiseNumberWaves];
    for(unsigned int i = 0; i < Noice::NoiseNumberWaves; i++)
    {
        unsigned int waveAmplitude = m_waves[m_waveNumber];
        unsigned int newWaveNumber = Wave::waveNumber(waveAmplitude);
        m_waves[m_waveNumber] = Wave::newWave(newWaveNumber);
        listWaves[i] = waveAmplitude;
        m_waveNumber = newWaveNumber;
    }
    m_hash->Update((const uint8_t*)&listWaves, sizeof(unsigned int) * Noice::NoiseNumberWaves);

    uint256_t oldNoice;
    m_hash->Final(oldNoice);
    m_hash->Restart();
    m_hash->Update(oldNoice, oldNoice.size());
    return oldNoice;
}
