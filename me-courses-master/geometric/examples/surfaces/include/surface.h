#ifndef SURFACE_H
#define SURFACE_H

#include "utils.h"

#define N_ROWS 100
#define N_COLUMNS 100

/**
 * Polygon mesh approximation of a surface.
 */
typedef struct Surface
{
    vec3 vertices[N_ROWS][N_COLUMNS];
    vec3 normals[N_ROWS][N_COLUMNS];
} Surface;

/**
 * Update the surface.
 */
void update_surface(Surface* surface);

/**
 * Update the vertices of the surface.
 */
void update_surface_vertices(Surface* surface);

/**
 * Update the normals of the surface.
 */
void update_surface_normals(Surface* surface);

/**
 * Draw the surface.
 */
void draw_surface(Surface* surface);

#endif /* SURFACE_H */
