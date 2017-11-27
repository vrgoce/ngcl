// Copyright (C) 2017 Goce Vrglevski <gocevrglevski@gmail.com>
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BYTEARRAY_H
#define BYTEARRAY_H
#include <string.h>
#include <sstream>
#include "serialize.h"

/**
 * @brief The ByteArray class Template class for array of bytes
 */
template<unsigned int T_Size>
class ByteArray
{
public:
    ByteArray()
    {
        memset(bytes, 0, T_Size);
    }
    ByteArray(const std::string& hexString)
    {
        memset(bytes, 0, T_Size);
        serialize::hex2bin(hexString.c_str(), (char*)bytes, T_Size);
    }
    unsigned int size()
    {
        return T_Size;
    }
    operator uint8_t*(){
        return bytes;
    }
    const char* c_str() const{
        return (const char*)bytes;
    }
    std::string toHex()
    {
        std::stringstream stream;
        stream << std::hex;
        for(unsigned int i = 0; i < T_Size; i++)
        {
            stream << (int)bytes[i];
        }
        return stream.str();
    }

private:
    uint8_t bytes[T_Size];
};

typedef ByteArray<32> uint256_t;

#endif // BYTEARRAY_H
