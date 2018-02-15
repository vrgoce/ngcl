// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RANDOM_H
#define RANDOM_H

#include <string>

class RandomPrivate;

/**
 * @brief The Random class Wrapper class for generating random numbers
 */
class Random
{
public:
    /**
     * @brief Random The method create RNG object, the created object depends on the input parameters.
     * If key1 and key2 are hex encoded and have at least 64 characters then the created RNG use the Meiosis algorithm using key1 and key2 as seed.
     * Otherwise the created RNG use the White Noise algorithm which is seedless and entropy based, the data in key1 and key2 is feed into the RNG.
     * @param key1 The first key
     * @param key2 The second key
     */
    Random(std::string key1 = "", std::string key2 = "");

    /**
     * @brief Destructor
     */
    ~Random();

    /**
     * @brief isSeedLess Get the type of the RNG that is created using the constructor parameters
     * Useful to determine the used algorithm for the RNG.
     * Meiosis have seed and the generated sequence is determined by key1 and kay2.
     * White Noice is seedless and the generated sequence is always different, it is not determined by key1 and kay2.
     * @return true for seedless, false if contain seed
     */
    bool isSeedLess();

    /**
     * @brief skip Skip some sequence of bytes
     * @param size Number of bytes to skip
     */
    void skip(unsigned int size);

    /**
     * @brief feed Feed charsequence into the generator (it change the result sequence of the RING)
     * @param input Input charsequence
     * @param length Length of the sequence
     */
    void feed(const char *input, unsigned int length);

    /**
     * @brief randr Fill the container with raw form of random data
     * @param _container Some container
     * @param size Size of the container
     */
    void randr(void *_container, unsigned int size);

    /**
     * @brief randf Create random double number
     * @return Double number
     */
    double randf();

    /**
     * @brief randi Create random integer number
     * @return Integer number
     */
    int randi();

    /**
     * @brief randb Create digit from the specific base
     * @param base Digit base
     * @return Integer number netween 0 and the base
     */
    int randb(int base);

    /**
     * @brief rand1 Create double number between 0 and 1
     * @return Double number
     */
    double rand1();

    /**
     * @brief randHex Create random hex string with the specified size for the bytes
     * @param size Size for the bytes, so if the size is 5 then the hex string will have 10 characters
     * @return Random hex string
     */
    std::string randHex(int size);

private:
    // Disable copy constructor and equal assignment in order to prevent copying the object
    Random(Random const&);
    Random& operator=(Random const&);

    // Destroy the object
    void cleanUp();

    // Private data for the object
    RandomPrivate* d;
};

#endif // RANDOM_H
