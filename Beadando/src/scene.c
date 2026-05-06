#include "scene.h"

#include "texture.h"

#include "../lib/obj/include/draw.h"
#include "../lib/obj/include/load.h"
#include "../lib/obj/include/transform.h"

#include <GL/gl.h>

#include <stdio.h>

static void draw_origin(void);
static void apply_light(const Scene* scene);
static bool load_object(SceneObject* object, const char* model_path, const char* texture_path, vec3 pos, float scale);

void init_scene(Scene* scene)
{
    scene->object_count = 0;
    scene->selected_object = 0;
    scene->elapsed = 0.0f;

    scene->light_position = (vec3){2.0f, -2.0f, 3.0f};
    scene->light_intensity = 1.0f;

    for (int i = 0; i < SCENE_MAX_OBJECTS; ++i) {
        init_model(&scene->objects[i].model);
        scene->objects[i].texture = 0;
        scene->objects[i].position = (vec3){0, 0, 0};
        scene->objects[i].rotation = (vec3){0, 0, 0};
        scene->objects[i].scale = 1.0f;
        scene->objects[i].auto_rotate = false;
    }

    if (load_object(&scene->objects[0], "assets/models/cube.obj", "assets/textures/checker.png", (vec3){0.0f, 0.0f, 0.5f}, 1.0f)) {
        scene->objects[0].auto_rotate = true;
        scene->object_count++;
    }

    if (load_object(&scene->objects[1], "assets/models/ISAAC2.obj", "assets/textures/4_ons_black_bg_1920x1080.png", (vec3){2.0f, 0.0f, 0.0f}, 1.25f)) {
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

    draw_origin();

    // Ground plane
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-10, -10, 0);
    glVertex3f(10, -10, 0);
    glVertex3f(10, 10, 0);
    glVertex3f(-10, 10, 0);
    glEnd();
    glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < scene->object_count; ++i) {
        const SceneObject* object = &scene->objects[i];

        glPushMatrix();
        glTranslatef(object->position.x, object->position.y, object->position.z);
        glRotatef(object->rotation.x, 1, 0, 0);
        glRotatef(object->rotation.y, 0, 1, 0);
        glRotatef(object->rotation.z, 0, 0, 1);
        glScalef(object->scale, object->scale, object->scale);

        glBindTexture(GL_TEXTURE_2D, object->texture);
        glColor3f(1.0f, 1.0f, 1.0f);

        draw_model(&object->model);

        // Selection outline
        if (i == scene->selected_object) {
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

    SceneObject* object = &scene->objects[scene->selected_object];
    object->position = vec3_add(object->position, delta);
}

void scene_move_light(Scene* scene, vec3 delta)
{
    scene->light_position = vec3_add(scene->light_position, delta);
}

void scene_adjust_light(Scene* scene, float delta)
{
    scene->light_intensity = clampf(scene->light_intensity + delta, 0.0f, 4.0f);
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
}

static void draw_origin(void)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();

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
