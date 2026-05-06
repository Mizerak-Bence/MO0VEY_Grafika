#include "scene.h"

#include "texture.h"

#include "../lib/obj/include/draw.h"
#include "../lib/obj/include/load.h"
#include "../lib/obj/include/transform.h"

#include <GL/gl.h>

#include <math.h>
#include <stdio.h>

typedef struct SceneObstacle
{
    float center_x;
    float center_y;
    float half_width;
    float half_depth;
} SceneObstacle;

static const SceneObstacle chamber_obstacles[] = {
    {0.0f, 0.4f, 1.0f, 1.0f},
    {-2.8f, 2.2f, 0.7f, 0.5f},
    {2.8f, 2.2f, 0.7f, 0.5f}
};

static const vec3 player_spawn_position = {0.0f, -SCENE_ROOM_HALF_DEPTH + 1.25f, 0.0f};

static vec3 clamp_room_position(vec3 position, float margin, float min_z, float max_z);
static vec3 resolve_box_collision(vec3 previous, vec3 desired, float radius, SceneObstacle obstacle);
static vec3 resolve_chamber_obstacles(vec3 previous, vec3 desired, float radius);
static void draw_chamber(void);
static void draw_pedestal(vec3 position, float width, float depth, float height, float r, float g, float b);
static void draw_light_marker(const Scene* scene);
static void apply_light(const Scene* scene);
static bool load_object(SceneObject* object, const char* model_path, const char* texture_path, vec3 pos, float scale);

void init_scene(Scene* scene)
{
    scene->object_count = 0;
    scene->selected_object = 0;
    scene->elapsed = 0.0f;

    scene->light_position = (vec3){0.0f, -1.4f, 3.2f};
    scene->light_intensity = 1.1f;

    for (int i = 0; i < SCENE_MAX_OBJECTS; ++i) {
        init_model(&scene->objects[i].model);
        scene->objects[i].texture = 0;
        scene->objects[i].position = (vec3){0, 0, 0};
        scene->objects[i].rotation = (vec3){0, 0, 0};
        scene->objects[i].scale = 1.0f;
        scene->objects[i].auto_rotate = false;
    }

    if (load_object(&scene->objects[0], "assets/models/cube.obj", "assets/textures/checker.png", (vec3){0.0f, 0.4f, 0.75f}, 1.0f)) {
        scene->objects[0].auto_rotate = true;
        scene->object_count++;
    }

    if (load_object(&scene->objects[1], "assets/models/ISAAC2.obj", "assets/textures/4_ons_black_bg_1920x1080.png", player_spawn_position, 1.25f)) {
        scene->object_count++;
    }

    // Default selection: keep the first object selected for manipulation.
    scene_select_object(scene, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_NORMALIZE);

    apply_light(scene);
}

void destroy_scene(Scene* scene)
{
    for (int i = 0; i < scene->object_count; ++i) {
        free_model(&scene->objects[i].model);
        if (scene->objects[i].texture != 0) {
            glDeleteTextures(1, &scene->objects[i].texture);
            scene->objects[i].texture = 0;
        }
    }
}

void update_scene(Scene* scene, double dt)
{
    scene->elapsed += (float)dt;

    for (int i = 0; i < scene->object_count; ++i) {
        if (scene->objects[i].auto_rotate) {
            scene->objects[i].rotation.z += (float)(45.0 * dt);
            if (scene->objects[i].rotation.z >= 360.0f) {
                scene->objects[i].rotation.z -= 360.0f;
            }
        }
    }
}

void render_scene(const Scene* scene)
{
    apply_light(scene);

    draw_chamber();
    draw_light_marker(scene);

    for (int i = 0; i < scene->object_count; ++i) {
        const SceneObject* object = &scene->objects[i];

        glPushMatrix();
        glTranslatef(object->position.x, object->position.y, object->position.z);
        glRotatef(object->rotation.x, 1, 0, 0);
        glRotatef(object->rotation.y, 0, 1, 0);
        glRotatef(object->rotation.z, 0, 0, 1);
        glScalef(object->scale, object->scale, object->scale);

        if (i == 1) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }

        glBindTexture(GL_TEXTURE_2D, object->texture);
        glColor3f(1.0f, 1.0f, 1.0f);

        draw_model(&object->model);

        if (i == 1) {
            glDisable(GL_CULL_FACE);
        }

        // Selection outline
        if (i == scene->selected_object && i != 1) {
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glColor3f(1.0f, 1.0f, 0.0f);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            draw_model(&object->model);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_LIGHTING);
        }

        glPopMatrix();
    }
}

void scene_select_object(Scene* scene, int index)
{
    if (scene->object_count <= 0) {
        scene->selected_object = 0;
        return;
    }

    if (index < 0) {
        index = 0;
    }
    if (index >= scene->object_count) {
        index = scene->object_count - 1;
    }

    scene->selected_object = index;
}

void scene_move_selected(Scene* scene, vec3 delta)
{
    if (scene->object_count <= 0) {
        return;
    }

    const int index = scene->selected_object;
    SceneObject* object = &scene->objects[index];
    const vec3 target_position = vec3_add(object->position, delta);
    const float margin = (index == 1) ? 1.4f : 0.9f;
    const float min_z = (index == 0) ? 0.55f : 0.0f;
    const float max_z = (index == 0) ? 2.2f : 1.2f;

    if (index == 1) {
        object->position = scene_resolve_player_position(object->position, target_position);
        return;
    }

    object->position = clamp_room_position(target_position, margin, min_z, max_z);
}

void scene_move_light(Scene* scene, vec3 delta)
{
    scene->light_position = vec3_add(scene->light_position, delta);
    scene->light_position = clamp_room_position(scene->light_position, 0.6f, 0.8f, SCENE_ROOM_HEIGHT - 0.35f);
}

void scene_adjust_light(Scene* scene, float delta)
{
    scene->light_intensity = clampf(scene->light_intensity + delta, 0.0f, 4.0f);
}

vec3 scene_resolve_player_position(vec3 previous_position, vec3 target_position)
{
    vec3 resolved = clamp_room_position(target_position, 1.2f, 0.0f, 1.2f);

    resolved = resolve_chamber_obstacles(previous_position, resolved, 0.85f);
    resolved = clamp_room_position(resolved, 1.2f, 0.0f, 1.2f);

    return resolved;
}

static void apply_light(const Scene* scene)
{
    const float intensity = scene->light_intensity;
    const GLfloat diffuse[4] = {0.9f * intensity, 0.9f * intensity, 0.9f * intensity, 1.0f};
    const GLfloat ambient[4] = {0.15f * intensity, 0.15f * intensity, 0.15f * intensity, 1.0f};
    const GLfloat specular[4] = {0.5f * intensity, 0.5f * intensity, 0.5f * intensity, 1.0f};
    const GLfloat position[4] = {scene->light_position.x, scene->light_position.y, scene->light_position.z, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02f);
}

static vec3 clamp_room_position(vec3 position, float margin, float min_z, float max_z)
{
    position.x = clampf(position.x, -SCENE_ROOM_HALF_WIDTH + margin, SCENE_ROOM_HALF_WIDTH - margin);
    position.y = clampf(position.y, -SCENE_ROOM_HALF_DEPTH + margin, SCENE_ROOM_HALF_DEPTH - margin);
    position.z = clampf(position.z, min_z, max_z);

    return position;
}

static vec3 resolve_box_collision(vec3 previous, vec3 desired, float radius, SceneObstacle obstacle)
{
    const float limit_x = obstacle.half_width + radius;
    const float limit_y = obstacle.half_depth + radius;
    const float local_x = desired.x - obstacle.center_x;
    const float local_y = desired.y - obstacle.center_y;

    if (fabsf(local_x) >= limit_x || fabsf(local_y) >= limit_y) {
        return desired;
    }

    const float previous_local_x = previous.x - obstacle.center_x;
    const float previous_local_y = previous.y - obstacle.center_y;
    const bool crossed_x = fabsf(previous_local_x) >= limit_x;
    const bool crossed_y = fabsf(previous_local_y) >= limit_y;

    if (crossed_x && !crossed_y) {
        desired.x = obstacle.center_x + ((local_x < 0.0f) ? -limit_x : limit_x);
        return desired;
    }

    if (crossed_y && !crossed_x) {
        desired.y = obstacle.center_y + ((local_y < 0.0f) ? -limit_y : limit_y);
        return desired;
    }

    if ((limit_x - fabsf(local_x)) < (limit_y - fabsf(local_y))) {
        desired.x = obstacle.center_x + ((local_x < 0.0f) ? -limit_x : limit_x);
    }
    else {
        desired.y = obstacle.center_y + ((local_y < 0.0f) ? -limit_y : limit_y);
    }

    return desired;
}

static vec3 resolve_chamber_obstacles(vec3 previous, vec3 desired, float radius)
{
    const int obstacle_count = (int)(sizeof(chamber_obstacles) / sizeof(chamber_obstacles[0]));

    for (int i = 0; i < obstacle_count; ++i) {
        desired = resolve_box_collision(previous, desired, radius, chamber_obstacles[i]);
    }

    return desired;
}

static void draw_chamber(void)
{
    const float room_x = SCENE_ROOM_HALF_WIDTH;
    const float room_y = SCENE_ROOM_HALF_DEPTH;
    const float room_z = SCENE_ROOM_HEIGHT;
    const float door_half_width = 1.4f;
    const float door_height = 2.6f;

    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glColor3f(0.20f, 0.21f, 0.24f);
    glNormal3f(0, 0, 1);
    glVertex3f(-room_x, -room_y, 0.0f);
    glVertex3f(room_x, -room_y, 0.0f);
    glVertex3f(room_x, room_y, 0.0f);
    glVertex3f(-room_x, room_y, 0.0f);

    glColor3f(0.11f, 0.12f, 0.15f);
    glNormal3f(0, 0, -1);
    glVertex3f(-room_x, room_y, room_z);
    glVertex3f(room_x, room_y, room_z);
    glVertex3f(room_x, -room_y, room_z);
    glVertex3f(-room_x, -room_y, room_z);

    glColor3f(0.13f, 0.14f, 0.17f);
    glNormal3f(0, -1, 0);
    glVertex3f(-room_x, room_y, 0.0f);
    glVertex3f(room_x, room_y, 0.0f);
    glVertex3f(room_x, room_y, room_z);
    glVertex3f(-room_x, room_y, room_z);

    glNormal3f(1, 0, 0);
    glVertex3f(-room_x, -room_y, 0.0f);
    glVertex3f(-room_x, room_y, 0.0f);
    glVertex3f(-room_x, room_y, room_z);
    glVertex3f(-room_x, -room_y, room_z);

    glNormal3f(-1, 0, 0);
    glVertex3f(room_x, room_y, 0.0f);
    glVertex3f(room_x, -room_y, 0.0f);
    glVertex3f(room_x, -room_y, room_z);
    glVertex3f(room_x, room_y, room_z);

    glColor3f(0.10f, 0.11f, 0.14f);
    glNormal3f(0, 1, 0);
    glVertex3f(-room_x, -room_y, 0.0f);
    glVertex3f(-door_half_width, -room_y, 0.0f);
    glVertex3f(-door_half_width, -room_y, room_z);
    glVertex3f(-room_x, -room_y, room_z);

    glVertex3f(door_half_width, -room_y, 0.0f);
    glVertex3f(room_x, -room_y, 0.0f);
    glVertex3f(room_x, -room_y, room_z);
    glVertex3f(door_half_width, -room_y, room_z);

    glVertex3f(-door_half_width, -room_y, door_height);
    glVertex3f(door_half_width, -room_y, door_height);
    glVertex3f(door_half_width, -room_y, room_z);
    glVertex3f(-door_half_width, -room_y, room_z);

    glColor3f(0.16f, 0.17f, 0.21f);
    glNormal3f(0, 0, 1);
    glVertex3f(-2.9f, -2.4f, 0.02f);
    glVertex3f(2.9f, -2.4f, 0.02f);
    glVertex3f(2.9f, 2.3f, 0.02f);
    glVertex3f(-2.9f, 2.3f, 0.02f);

    glEnd();

    draw_pedestal((vec3){0.0f, 0.4f, 0.0f}, 2.0f, 2.0f, 0.25f, 0.22f, 0.23f, 0.27f);
    draw_pedestal((vec3){-2.8f, 2.2f, 0.0f}, 1.4f, 1.0f, 0.35f, 0.16f, 0.18f, 0.22f);
    draw_pedestal((vec3){2.8f, 2.2f, 0.0f}, 1.4f, 1.0f, 0.35f, 0.16f, 0.18f, 0.22f);

    glEnable(GL_TEXTURE_2D);
}

static void draw_pedestal(vec3 position, float width, float depth, float height, float r, float g, float b)
{
    const float half_width = width * 0.5f;
    const float half_depth = depth * 0.5f;

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    glBegin(GL_QUADS);

    glColor3f(r, g, b);
    glNormal3f(0, 0, 1);
    glVertex3f(-half_width, -half_depth, height);
    glVertex3f(half_width, -half_depth, height);
    glVertex3f(half_width, half_depth, height);
    glVertex3f(-half_width, half_depth, height);

    glColor3f(r * 0.82f, g * 0.82f, b * 0.82f);
    glNormal3f(0, -1, 0);
    glVertex3f(-half_width, -half_depth, 0.0f);
    glVertex3f(half_width, -half_depth, 0.0f);
    glVertex3f(half_width, -half_depth, height);
    glVertex3f(-half_width, -half_depth, height);

    glNormal3f(0, 1, 0);
    glVertex3f(half_width, half_depth, 0.0f);
    glVertex3f(-half_width, half_depth, 0.0f);
    glVertex3f(-half_width, half_depth, height);
    glVertex3f(half_width, half_depth, height);

    glNormal3f(-1, 0, 0);
    glVertex3f(-half_width, half_depth, 0.0f);
    glVertex3f(-half_width, -half_depth, 0.0f);
    glVertex3f(-half_width, -half_depth, height);
    glVertex3f(-half_width, half_depth, height);

    glNormal3f(1, 0, 0);
    glVertex3f(half_width, -half_depth, 0.0f);
    glVertex3f(half_width, half_depth, 0.0f);
    glVertex3f(half_width, half_depth, height);
    glVertex3f(half_width, -half_depth, height);

    glEnd();

    glPopMatrix();
}

static void draw_light_marker(const Scene* scene)
{
    const float marker_size = 0.22f;

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 0.86f, 0.35f);

    glPushMatrix();
    glTranslatef(scene->light_position.x, scene->light_position.y, scene->light_position.z);

    glBegin(GL_LINES);
    glVertex3f(-marker_size, 0.0f, 0.0f);
    glVertex3f(marker_size, 0.0f, 0.0f);
    glVertex3f(0.0f, -marker_size, 0.0f);
    glVertex3f(0.0f, marker_size, 0.0f);
    glVertex3f(0.0f, 0.0f, -marker_size);
    glVertex3f(0.0f, 0.0f, marker_size);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -scene->light_position.z + 0.05f);
    glEnd();

    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

static bool load_object(SceneObject* object, const char* model_path, const char* texture_path, vec3 pos, float scale)
{
    init_model(&object->model);

    if (!load_model(&object->model, model_path)) {
        printf("[ERROR] Failed to load model: %s\n", model_path);
        return false;
    }

    // the model loader uses 1-based indices; vertices[0] exists but is unused.
    scale_model(&object->model, scale, scale, scale);

    object->texture = load_texture(texture_path);
    if (object->texture == 0) {
        printf("[ERROR] Failed to load texture: %s\n", texture_path);
        free_model(&object->model);
        return false;
    }

    object->position = pos;
    object->rotation = (vec3){0, 0, 0};
    object->scale = 1.0f;

    return true;
}
