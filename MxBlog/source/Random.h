#ifndef RANDOM_H
#define RANDOM_H

#include "includes.h"
#include "XWeb.h"

using namespace XW;

//Simple 

static inline unsigned int randomINT()
{
    unsigned int next = time(NULL) * time(NULL) / 0.6052;
    next = next * 1103215215;
    return((unsigned int) (next / 65536)*2768);

}

static inline uint64_t randomINT64()
{
    uint64_t s[2];
    s[0] = time(NULL);
    s[1] = time(NULL) * time(NULL);
    uint64_t x = s[0];
    uint64_t const y = s[1];
    s[0] = y;
    x ^= x << 23; // a
    s[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return s[1] + y;
}

static inline string UUID()
{
    char * uuid_xx = new char[39];

    sprintf(uuid_xx, "%02x-%02x-%02x-%02x-%02x%02x%02x",
            randomINT64(), randomINT(),
            ((randomINT() & 0x0fff) | 0x4000),
            ((randomINT() & 0x0fff) | 0x4000),
            (randomINT() % 0x3fff + 0x8000),
            (randomINT() % 0x3fff + 0x8000),
            ((randomINT() & 0x0fff) | 0x4000));

     string uid_str(uuid_xx);
     delete [] uuid_xx;
     return uid_str;
}



#endif /* RANDOM_H */

