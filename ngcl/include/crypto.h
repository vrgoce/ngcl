#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

class CryptoPrivate;

/**
 * @brief The Crypto class Implementation of encryption using random numbers
 * The Key 1 and Key 2 are used as seed for Meiosis (RNG that will be used for encryption),
 * the Meiosis will generate random stream of data called the Master Key,
 * which will be used to encrypt the data.
 * So basically, we use the RNG to create one big encryption key which will be used to encrypt/decrypt data.
 * There are infinite ways to create the Master Key, several variations will be provided.
 */
class Crypto
{
public:
    Crypto(std::string key1, std::string key2);

    Crypto(std::string key);

    ~Crypto();

    bool next(const char* input, char* output, unsigned int size);

private:
    // Disable copy constructor and equal assignment in order to prevent copying the object
    Crypto(Crypto const&);
    Crypto& operator=(Crypto const&);

    // Destroy the object
    void cleanUp();

    void encryptDecrypt(const char *input, const char* key, unsigned int size, char *output);

    // Private data for the object
    CryptoPrivate* d;
};

#endif // CRYPTO_H
