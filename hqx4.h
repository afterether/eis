#ifndef HQX4_H
#define HQX4_H
#include "hqx_common.h"
#include "stdlib.h"
#include "stdint.h"

class hqx4
{
public:
    hqx4();
    static void hq4x_32( uint32_t * src, uint32_t * dest, int width, int height );
    static void hq4x_32_rb( uint32_t * src, uint32_t src_rowBytes, uint32_t * dest, uint32_t dest_rowBytes, int width, int height );

    static uint32_t   RGBtoYUV[16777216];
    static uint32_t   YUV1, YUV2;
};


#endif // HQX4_H
