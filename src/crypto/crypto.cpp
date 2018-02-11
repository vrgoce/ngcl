#include "crypto.h"
#include "../random/serialize.h"
#include "../random/random.h"

#define HEX_KEY_SIZE 64
#define MASTER_BUFFER_SIZE 32

class CryptoPrivate
{
public:
    CryptoPrivate(std::string key1, std::string key2, Crypto::EnrandType _type):
        rng(key1, key2),
        type(_type)
    {}

    Random rng;
    Crypto::EnrandType type;
    char masterKeyBuffer[MASTER_BUFFER_SIZE];
};

Crypto::Crypto(std::string key1, std::string key2, Crypto::EnrandType type)
{
    if(key1.size() != HEX_KEY_SIZE || key2.size() != HEX_KEY_SIZE ||
            !serialize::isHexStr(key1) || !serialize::isHexStr(key2))
        throw "Fail to create the Master Key";

    d = new CryptoPrivate(key1, key2, type);
}

Crypto::Crypto(std::string key, Crypto::EnrandType type)
{
    if(key.size() != HEX_KEY_SIZE * 2 || !serialize::isHexStr(key))
        throw "Fail to create the Master Key";

    std::string key1 = key.substr(0, HEX_KEY_SIZE);
    std::string key2 = key.substr(HEX_KEY_SIZE);
    d = new CryptoPrivate(key1, key2, type);
}

Crypto::~Crypto()
{
    cleanUp();
}

bool Crypto::next(const char *input, char *output, unsigned int size)
{
    // Split the master key into several smaller keys and use them to encrypt/decrypt the data
    int wholeKeyCicles = size / MASTER_BUFFER_SIZE;
    int keyLeftover = size % MASTER_BUFFER_SIZE;
    int currentPos = 0;
    int keyBufferSize = MASTER_BUFFER_SIZE;

    // Run through the whole size keys
    for(int i = 0; i < wholeKeyCicles; i++)
    {
        const char *tmpInput = input + currentPos;
        char *tmpOutput = output + currentPos;
        // TBD BEGIN Compute the master key
        d->rng.randr(d->masterKeyBuffer, keyBufferSize);
        // TBD END Compute the master key
        encryptDecrypt(tmpInput, d->masterKeyBuffer, keyBufferSize, tmpOutput);
        currentPos += MASTER_BUFFER_SIZE;
    }

    // Run through the leftover key
    keyBufferSize = keyLeftover;
    if(keyLeftover)
    {
        const char *tmpInput = input + currentPos;
        char *tmpOutput = output + currentPos;
        // TBD BEGIN Compute the master key
        d->rng.randr(d->masterKeyBuffer, keyBufferSize);
        // TBD END Compute the master key
        encryptDecrypt(tmpInput, d->masterKeyBuffer, keyBufferSize, tmpOutput);
    }

    return wholeKeyCicles != 0 || keyLeftover != 0;
}

void Crypto::cleanUp()
{
    delete d;
    d = 0;
}

void Crypto::encryptDecrypt(const char *input, const char *key, unsigned int size, char *output)
{
    for(unsigned int i = 0; i < size; i++)
    {
        output[i] = input[i] ^ key[i];
    }
}
