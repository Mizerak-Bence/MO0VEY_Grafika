#ifndef SCENE_H
#define SCENE_H

#include "utils.h"

#include "../lib/obj/include/model.h"

#include <GL/gl.h>

#include <stdbool.h>

#define SCENE_MAX_OBJECTS 2
#define SCENE_ROOM_HALF_WIDTH 6.0f
#define SCENE_ROOM_HALF_DEPTH 6.0f
#define SCENE_ROOM_HEIGHT 4.5f

typedef struct SceneObject
{
    Model model;
    GLuint texture;
    vec3 position;
    vec3 rotation; /* degrees */
    float scale;
    bool auto_rotate;
} SceneObject;

typedef struct Scene
{
    SceneObject objects[SCENE_MAX_OBJECTS];
    int object_count;
    int selected_object;

    vec3 light_position;
    float light_intensity;

    float elapsed;
} Scene;

void init_scene(Scene* scene);
void destroy_scene(Scene* scene);

void update_scene(Scene* scene, double dt);
void render_scene(const Scene* scene);

void scene_select_object(Scene* scene, int index);
void scene_move_selected(Scene* scene, vec3 delta);

void scene_move_light(Scene* scene, vec3 delta);
void scene_adjust_light(Scene* scene, float delta);

vec3 scene_resolve_player_position(vec3 previous_position, vec3 target_position);

#endif /* SCENE_H */
