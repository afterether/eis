#ifndef HQX3_H
#define HQX3_H


class hqx3
{
public:
    hqx3();
    static void hq3x_32_rb( uint32_t * sp, uint32_t srb, uint32_t * dp, uint32_t drb, int Xres, int Yres );
    static void hq3x_32( uint32_t * sp, uint32_t * dp, int Xres, int Yres );
};

#endif // HQX3_H
