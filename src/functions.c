#include "functions.h"

float rescale(uint32_t x, uint32_t x_max, uint32_t x_min, int z_max, int z_min)
{
    float out;
    out = z_min + (z_max - z_min) * (x - x_min) / (float) (x_max - x_min);
    return out
}





