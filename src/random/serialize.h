#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <stdint.h>
#include <cstring>
#include <string>

//Namespace for serialization integer numbers and integer lists
//Big Endian encoding for integer numbers serialization
namespace serialize
{
inline bool isLittleEndian()
{
    static int endian = 1;
    return reinterpret_cast<uint8_t*>(&endian)[0];
}

template <class Number>
void toBytes(const Number& input, uint8_t* output)
{
    int size = sizeof(Number);
    if(isLittleEndian())
    {
        for(int i = 0; i < size; i++)
        {
            output[size - 1 - i] = input >> i * 8;
        }
    }
    else
    {
        std::memcpy(output, &input, size);
    }
}

template <class Number>
void fromBytes(const uint8_t* input, Number& output)
{
    output = 0;
    int size = sizeof(Number);
    if(isLittleEndian())
    {
        for(int i = 0; i < size; i++)
        {
            output |= ((Number)input[size - 1 - i]) << i * 8;
        }
    }
    else
    {
        std::memcpy(&output, input, size);
    }
}

template <class Number, unsigned int length>
void listToBytes(const Number* input, uint8_t* output)
{
    for(unsigned int i = 0; i < length; i++)
    {
        toBytes(input[i], &output[i * sizeof(Number)]);
    }
}

template <class Number, unsigned int length>
void listFromBytes(const uint8_t* input, Number* output)
{
    for(unsigned int i = 0; i < length; i++)
    {
        fromBytes(&input[i * sizeof(Number)], output[i]);
    }
}

inline int char2int(char input)
{
    if(input >= '0' && input <= '9')
        return input - '0';
    if(input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if(input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    return 0;
}

inline void hex2bin(const char* src, char* target, int length = -1)
{
    int len = length;
    while(*src && src[1] && (length < 0 || len-- > 0))
    {
        *(target++) = char2int(*src)*16 + char2int(src[1]);
        src += 2;
    }
}

inline std::string bin2hex(const unsigned char* src, int length)
{
    std::string target;
    static const char dec2hex[16 + 1] = "0123456789abcdef";
    for(int i = 0; i < length; i++)
    {
        target += dec2hex[src[i] >> 4];
        target += dec2hex[src[i] & 15];
    }
    return target;
}

}

#endif // SERIALIZE_H
