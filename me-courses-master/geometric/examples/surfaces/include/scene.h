#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "surface.h"

#include <GL/gl.h>

typedef struct Scene
{
    Surface surface;
    Material material;
    double angle;
    double rotation_speed;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double elapsed_time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Draw a tesselated square.
 */
void draw_plane(int n);

#endif /* SCENE_H */
