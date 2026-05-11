#ifndef SCENE_H
#define SCENE_H

#include "utils.h"

#include "../lib/obj/include/model.h"

#include <GL/gl.h>

#include <stdbool.h>

#define SCENE_MAX_OBJECTS 2
#define SCENE_MAX_PROJECTILES 32
#define SCENE_ROOM_COUNT 4
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
    bool unlit;
} SceneObject;

typedef struct SceneProjectile
{
    bool active;
    bool hostile;
    int room_index;
    vec3 position;
    vec3 velocity;
    float lifetime;
} SceneProjectile;

typedef struct Scene
{
    SceneObject objects[SCENE_MAX_OBJECTS];
    SceneProjectile projectiles[SCENE_MAX_PROJECTILES];
    int object_count;
    int selected_object;
    int current_room;

    GLuint chamber_floor_texture;
    GLuint chamber_wall_texture;
    GLuint pedestal_texture;
    GLuint door_texture;
    GLuint enemy_texture;

    bool room_cleared[SCENE_ROOM_COUNT];
    bool enemy_alive[SCENE_ROOM_COUNT];
    int enemy_health[SCENE_ROOM_COUNT];
    vec3 enemy_position[SCENE_ROOM_COUNT];
    float enemy_shot_cooldown[SCENE_ROOM_COUNT];

    int player_health;
    int player_max_health;
    float player_hit_cooldown;

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
bool scene_use_nearby_door(Scene* scene);
void scene_fire_projectile(Scene* scene, float yaw_degrees);

vec3 scene_resolve_player_position(const Scene* scene, vec3 previous_position, vec3 target_position);

#endif /* SCENE_H */
