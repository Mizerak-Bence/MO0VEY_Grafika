#include "utils.h"

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double degree_to_radian(double degree)
{
    return degree * M_PI / 180.0;
}

float clampf(float value, float min_value, float max_value)
{
    if (value < min_value) {
        return min_value;
    }
    if (value > max_value) {
        return max_value;
    }
    return value;
}

vec3 vec3_add(vec3 a, vec3 b)
{
    return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3 vec3_scale(vec3 v, float s)
{
    return (vec3){v.x * s, v.y * s, v.z * s};
}
