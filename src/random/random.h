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
     * If key1 and key2 are hex encoded and have at least 64 characters then the created RNG use the Meosis algorithm using key1 and key2 as seed.
     * Otherwise the created RNG use the White Noise algorithm which is seedless and entropy based.
     * @param key1 The first seed
     * @param key2 The second seed
     */
    Random(std::string key1 = "", std::string key2 = "");
    ~Random();

    /**
     * @brief skip Skip some sequence of bytes
     * @param size Number of bytes to skip
     */
    void skip(unsigned int size);
    void feed(const unsigned char *input, unsigned int length);

    void randr(void *_container, unsigned int size);
    double randf();
    int randi();
    int randb(int base);
    double rand1();
    std::string randHex(int size);

    bool isSeedLess();

private:
    Random(Random const&);
    Random& operator=(Random const&);

    void cleanUp();

    RandomPrivate* d;
};

#endif // RANDOM_H
