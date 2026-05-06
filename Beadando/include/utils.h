#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * GLSL-like three dimensional vector.
 */
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);

float clampf(float value, float min_value, float max_value);

vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_scale(vec3 v, float s);

#endif /* UTILS_H */
