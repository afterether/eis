#ifndef HQX_H
#define HQX_H
#include <stdlib.h>
#include <stdint.h>

class hqx
{
public:
    /* RGB to YUV lookup table */
    static uint32_t RGBtoYUV[16777216];

    hqx();
    static void hqxInit(void);
};

#endif // HQX_H
