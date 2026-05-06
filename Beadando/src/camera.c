#include "camera.h"

#include <GL/gl.h>

#include <math.h>

void init_camera(Camera* camera)
{
    camera->position = (vec3){0.0f, 0.0f, 1.6f};
    camera->rotation = (vec3){0.0f, 0.0f, 90.0f};
    camera->speed = (vec3){0.0f, 0.0f, 0.0f};
    camera->mouse_sensitivity = 0.25f;
}

void update_camera(Camera* camera, double dt)
{
    const double yaw = degree_to_radian(camera->rotation.z);
    // Right vector is yaw - 90 degrees in the XY plane (Z is up).
    const double side_yaw = degree_to_radian(camera->rotation.z - 90.0);

    camera->position.x += (float)(cos(side_yaw) * camera->speed.x * dt);
    camera->position.y += (float)(sin(side_yaw) * camera->speed.x * dt);

    camera->position.x += (float)(cos(yaw) * camera->speed.y * dt);
    camera->position.y += (float)(sin(yaw) * camera->speed.y * dt);

    camera->position.z += (float)(camera->speed.z * dt);
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-camera->rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(-camera->rotation.z, 0.0f, 0.0f, 1.0f);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += (float)(horizontal * camera->mouse_sensitivity);
    camera->rotation.x += (float)(vertical * camera->mouse_sensitivity);

    if (camera->rotation.z < 0.0f) {
        camera->rotation.z += 360.0f;
    }
    if (camera->rotation.z >= 360.0f) {
        camera->rotation.z -= 360.0f;
    }

    camera->rotation.x = clampf(camera->rotation.x, -89.0f, 89.0f);
}

void set_camera_forward_speed(Camera* camera, double speed)
{
    camera->speed.y = (float)speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = (float)speed;
}

void set_camera_up_speed(Camera* camera, double speed)
{
    camera->speed.z = (float)speed;
}
