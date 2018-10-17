#ifndef HQX2_H
#define HQX2_H
#include "hqx_common.h"
#include "stdlib.h"
#include "stdint.h"



class hqx2
{
public:
    hqx2();
    static void hq2x_32( uint32_t * src, uint32_t * dest, int width, int height );
    static void hq2x_32_rb( uint32_t * src, uint32_t src_rowBytes, uint32_t * dest, uint32_t dest_rowBytes, int width, int height );
};

#endif // HQX2_H
