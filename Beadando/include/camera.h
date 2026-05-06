#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

/**
 * Camera as a moving point with direction.
 * Coordinate system: X/Y is ground plane, Z is up.
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation; /* pitch=x, roll=y (unused), yaw=z in degrees */
    vec3 speed;    /* side=x, forward=y, up=z (units/sec) */
    float mouse_sensitivity;
} Camera;

void init_camera(Camera* camera);
void update_camera(Camera* camera, double dt);
void set_view(const Camera* camera);
void rotate_camera(Camera* camera, double horizontal, double vertical);
void set_camera_forward_speed(Camera* camera, double speed);
void set_camera_side_speed(Camera* camera, double speed);
void set_camera_up_speed(Camera* camera, double speed);

#endif /* CAMERA_H */
