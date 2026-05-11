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
    float height;
} SceneObstacle;

typedef enum RoomLayoutKind
{
    ROOM_LAYOUT_ENTRY,
    ROOM_LAYOUT_RELIQUARY,
    ROOM_LAYOUT_FORGE,
    ROOM_LAYOUT_ARCHIVE
} RoomLayoutKind;

typedef struct RoomDefinition
{
    RoomLayoutKind layout_kind;
    const SceneObstacle* obstacles;
    int obstacle_count;
    vec3 enemy_spawn;
    vec3 floor_tint;
    vec3 wall_tint;
    vec3 ceiling_tint;
    vec3 beam_tint;
    vec3 accent_tint;
    float floor_repeat_scale;
    float wall_repeat_scale;
    float ceiling_repeat_scale;
} RoomDefinition;

#define CHAMBER_DOOR_HALF_WIDTH 1.4f
#define CHAMBER_TRIM_DEPTH 0.18f
#define CHAMBER_TRIM_HEIGHT 0.24f
#define CHAMBER_PILLAR_DEPTH 0.26f
#define CHAMBER_PILLAR_WIDTH 0.42f
#define CHAMBER_DOOR_FRAME_WIDTH 0.34f
#define CHAMBER_DOOR_FRAME_DEPTH 0.24f
#define CHAMBER_DOOR_HEADER_HEIGHT 0.40f
#define CHAMBER_DOOR_LEAF_WIDTH 2.84f
#define CHAMBER_DOOR_LEAF_DEPTH 0.08f
#define CHAMBER_DOOR_LEAF_HEIGHT 2.60f
#define CHAMBER_DOOR_FRAME_OVERLAP 0.02f
#define CHAMBER_FLOOR_TILE_WORLD_SIZE 1.0f
#define CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE 0.55f
#define CHAMBER_DOOR_TEXTURE_WORLD_SIZE 0.70f
#define ROOM_SPACING (SCENE_ROOM_HALF_DEPTH * 2.0f)
#define WORLD_MIN_Y (-SCENE_ROOM_HALF_DEPTH)
#define WORLD_MAX_Y (((SCENE_ROOM_COUNT - 1) * ROOM_SPACING) + SCENE_ROOM_HALF_DEPTH)
#define CONNECTOR_OPEN_HALF_WIDTH (CHAMBER_DOOR_HALF_WIDTH + CHAMBER_DOOR_FRAME_WIDTH - CHAMBER_DOOR_FRAME_OVERLAP)
#define CONNECTOR_SIDE_HALF_WIDTH ((SCENE_ROOM_HALF_WIDTH - CONNECTOR_OPEN_HALF_WIDTH) * 0.5f)
#define CONNECTOR_SIDE_CENTER_X (CONNECTOR_OPEN_HALF_WIDTH + CONNECTOR_SIDE_HALF_WIDTH)
#define DOOR_USE_DISTANCE 0.95f
#define ROOM_ENTRY_OFFSET 1.25f
#define ENEMY_DRAW_SIZE 0.78f
#define ENEMY_CENTER_HEIGHT 0.90f
#define ENEMY_HITBOX_RADIUS 0.46f
#define ENEMY_MOVE_SPEED 1.10f
#define ENEMY_CONTACT_DISTANCE 0.82f
#define PROJECTILE_DRAW_SIZE 0.20f
#define PROJECTILE_RADIUS (PROJECTILE_DRAW_SIZE * 0.5f)
#define PROJECTILE_SPEED 9.0f
#define ENEMY_PROJECTILE_SPEED 6.5f
#define PROJECTILE_LIFETIME 1.2f
#define PROJECTILE_HIT_DISTANCE (ENEMY_HITBOX_RADIUS + PROJECTILE_RADIUS)
#define ENEMY_MAX_HEALTH 4
#define ENEMY_FIRE_INTERVAL 1.15f
#define SCENE_USE_LIGHTING 1
#define SCENE_SHOW_LIGHT_MARKER 0
#define PLAYER_COLLISION_RADIUS 0.42f
#define PLAYER_ROOM_MARGIN 0.46f
#define PLAYER_MAX_HEALTH 8
#define PLAYER_DAMAGE_COOLDOWN 0.60f

#define ROOM_OBSTACLE_COUNT(array) ((int)(sizeof(array) / sizeof((array)[0])))

static const SceneObstacle room0_obstacles_local[] = {
    {0.0f, 0.4f, 1.0f, 1.0f, 0.25f},
    {-2.8f, 2.2f, 0.7f, 0.5f, 0.35f},
    {2.8f, 2.2f, 0.7f, 0.5f, 0.35f},
    {-SCENE_ROOM_HALF_WIDTH + CHAMBER_PILLAR_DEPTH * 0.5f, SCENE_ROOM_HALF_DEPTH - CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f, SCENE_ROOM_HEIGHT},
    {SCENE_ROOM_HALF_WIDTH - CHAMBER_PILLAR_DEPTH * 0.5f, SCENE_ROOM_HALF_DEPTH - CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f, SCENE_ROOM_HEIGHT},
    {-SCENE_ROOM_HALF_WIDTH + CHAMBER_PILLAR_DEPTH * 0.5f, -SCENE_ROOM_HALF_DEPTH + CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f, SCENE_ROOM_HEIGHT},
    {SCENE_ROOM_HALF_WIDTH - CHAMBER_PILLAR_DEPTH * 0.5f, -SCENE_ROOM_HALF_DEPTH + CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f, SCENE_ROOM_HEIGHT},
    {-CONNECTOR_SIDE_CENTER_X, SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT},
    {CONNECTOR_SIDE_CENTER_X, SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT}
};

static const SceneObstacle room1_obstacles_local[] = {
    {-SCENE_ROOM_HALF_WIDTH + CHAMBER_PILLAR_DEPTH * 0.5f, SCENE_ROOM_HALF_DEPTH - CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f, SCENE_ROOM_HEIGHT},
    {SCENE_ROOM_HALF_WIDTH - CHAMBER_PILLAR_DEPTH * 0.5f, SCENE_ROOM_HALF_DEPTH - CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f, SCENE_ROOM_HEIGHT},
    {-SCENE_ROOM_HALF_WIDTH + CHAMBER_PILLAR_DEPTH * 0.5f, -SCENE_ROOM_HALF_DEPTH + CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f, SCENE_ROOM_HEIGHT},
    {SCENE_ROOM_HALF_WIDTH - CHAMBER_PILLAR_DEPTH * 0.5f, -SCENE_ROOM_HALF_DEPTH + CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f, SCENE_ROOM_HEIGHT},
    {0.0f, -2.55f, 2.2f, 0.50f, 0.24f},
    {-2.90f, 0.0f, 0.30f, 2.70f, 1.16f},
    {1.90f, 0.80f, 0.55f, 0.55f, 2.50f},
    {-0.60f, 0.70f, 0.17f, 0.17f, 2.30f},
    {0.0f, 3.60f, 2.10f, 0.45f, 1.50f},
    {2.35f, -1.80f, 0.55f, 0.30f, 0.20f},
    {-1.55f, 2.00f, 0.45f, 0.30f, 0.20f},
    {-CONNECTOR_SIDE_CENTER_X, SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT},
    {CONNECTOR_SIDE_CENTER_X, SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT},
    {-CONNECTOR_SIDE_CENTER_X, -SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT},
    {CONNECTOR_SIDE_CENTER_X, -SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT}
};

static const SceneObstacle room2_obstacles_local[] = {
    {0.0f, 0.0f, 1.75f, 0.70f, 0.28f},
    {-3.00f, -0.60f, 0.45f, 1.75f, 1.55f},
    {2.90f, 1.15f, 0.70f, 0.55f, 1.10f},
    {-0.70f, 2.70f, 0.22f, 0.22f, 2.20f},
    {1.55f, -2.55f, 0.22f, 0.22f, 2.20f},
    {0.0f, 3.95f, 2.35f, 0.36f, 0.24f},
    {0.0f, -3.80f, 2.10f, 0.42f, 0.24f},
    {-CONNECTOR_SIDE_CENTER_X, SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT},
    {CONNECTOR_SIDE_CENTER_X, SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT},
    {-CONNECTOR_SIDE_CENTER_X, -SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT},
    {CONNECTOR_SIDE_CENTER_X, -SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT}
};

static const SceneObstacle room3_obstacles_local[] = {
    {-2.45f, -0.35f, 0.45f, 3.10f, 1.85f},
    {0.20f, 1.10f, 0.40f, 2.55f, 1.80f},
    {2.55f, -0.80f, 0.40f, 2.90f, 1.80f},
    {0.0f, 3.60f, 1.60f, 0.40f, 0.32f},
    {-1.05f, -2.75f, 0.35f, 0.35f, 1.35f},
    {1.30f, 2.65f, 0.35f, 0.35f, 1.35f},
    {-CONNECTOR_SIDE_CENTER_X, -SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT},
    {CONNECTOR_SIDE_CENTER_X, -SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f, SCENE_ROOM_HEIGHT}
};

static const RoomDefinition room_definitions[SCENE_ROOM_COUNT] = {
    {ROOM_LAYOUT_ENTRY, room0_obstacles_local, ROOM_OBSTACLE_COUNT(room0_obstacles_local), {0.0f, 0.4f, ENEMY_CENTER_HEIGHT}, {0.96f, 0.88f, 0.72f}, {0.80f, 0.78f, 0.74f}, {0.20f, 0.18f, 0.15f}, {0.56f, 0.36f, 0.14f}, {0.78f, 0.62f, 0.28f}, 0.85f, 0.90f, 0.75f},
    {ROOM_LAYOUT_RELIQUARY, room1_obstacles_local, ROOM_OBSTACLE_COUNT(room1_obstacles_local), {0.40f, -0.20f, ENEMY_CENTER_HEIGHT}, {0.62f, 0.72f, 0.86f}, {0.58f, 0.64f, 0.76f}, {0.14f, 0.18f, 0.28f}, {0.48f, 0.30f, 0.16f}, {0.46f, 0.70f, 0.92f}, 1.30f, 0.82f, 1.15f},
    {ROOM_LAYOUT_FORGE, room2_obstacles_local, ROOM_OBSTACLE_COUNT(room2_obstacles_local), {-2.10f, -1.10f, ENEMY_CENTER_HEIGHT}, {0.82f, 0.72f, 0.56f}, {0.72f, 0.66f, 0.58f}, {0.16f, 0.14f, 0.12f}, {0.58f, 0.28f, 0.10f}, {0.88f, 0.56f, 0.18f}, 0.72f, 1.28f, 0.88f},
    {ROOM_LAYOUT_ARCHIVE, room3_obstacles_local, ROOM_OBSTACLE_COUNT(room3_obstacles_local), {1.80f, -1.00f, ENEMY_CENTER_HEIGHT}, {0.78f, 0.76f, 0.68f}, {0.72f, 0.70f, 0.64f}, {0.18f, 0.16f, 0.14f}, {0.50f, 0.34f, 0.18f}, {0.74f, 0.66f, 0.32f}, 1.55f, 0.74f, 1.40f}
};

static const vec3 player_spawn_position = {0.0f, -SCENE_ROOM_HALF_DEPTH + 1.25f, 0.0f};

static const RoomDefinition* get_room_definition(int room_index);
static float get_room_center_y(int room_index);
static vec3 get_room_entry_position(int room_index, bool from_south);
static vec3 get_room_world_position(int room_index, vec3 local_position);
static SceneObstacle get_room_world_obstacle(int room_index, int obstacle_index);
static vec3 get_room_light_anchor(int room_index);
static int get_room_index_from_y(float y);
static vec3 clamp_room_position(vec3 position, int room_index, float margin, float min_z, float max_z);
static vec3 resolve_box_collision(vec3 previous, vec3 desired, float radius, SceneObstacle obstacle);
static vec3 resolve_room_movement(vec3 previous, vec3 desired, int room_index, float radius, float bottom_z, float margin, float min_z, float max_z);
static vec3 resolve_room_obstacles(vec3 previous, vec3 desired, float radius, int room_index, float bottom_z);
static vec3 move_enemy_toward_target(const Scene* scene, int room_index, vec3 enemy_position, vec3 target_position, float step_length);
static void draw_chamber(const Scene* scene);
static void draw_room(const Scene* scene, float room_center_y, bool open_south, bool open_north, bool draw_south_door, bool draw_north_door, bool draw_west_door, bool draw_east_door);
static void draw_textured_quad_xy(float z, float min_x, float max_x, float min_y, float max_y, float normal_z, float u_repeat, float v_repeat);
static void draw_textured_quad_xz(float y, float min_x, float max_x, float min_z, float max_z, float normal_y, float u_repeat, float v_repeat);
static void draw_textured_quad_yz(float x, float min_y, float max_y, float min_z, float max_z, float normal_x, float u_repeat, float v_repeat);
static void draw_box(vec3 center, vec3 size, float r, float g, float b);
static void draw_textured_box(vec3 center, vec3 size, GLuint texture, float r, float g, float b, float texture_world_size, bool unlit);
static void draw_door_assembly(vec3 center, float rotation_z, GLuint texture);
static void draw_open_door_frame(vec3 center, float rotation_z, GLuint texture);
static void draw_selection_box(const SceneObject* object);
static void get_model_bounds(const Model* model, vec3* min_corner, vec3* max_corner);
static void draw_pedestal(vec3 position, float width, float depth, float height, GLuint texture, float r, float g, float b);
static void draw_entry_room_features(const RoomDefinition* room_definition, float room_center_y, float room_z, GLuint pedestal_texture, GLuint detail_texture);
static void draw_reliquary_room_features(const RoomDefinition* room_definition, float room_center_y, float room_z, GLuint ritual_texture, GLuint relic_texture);
static void draw_forge_room_features(const RoomDefinition* room_definition, float room_center_y, float room_z, GLuint ritual_texture, GLuint detail_texture);
static void draw_archive_room_features(const RoomDefinition* room_definition, float room_center_y, float room_z, GLuint pedestal_texture, GLuint detail_texture);
static void draw_room_enemy(const Scene* scene, int room_index);
static void draw_enemy_health_bar_overlay(const Scene* scene, int room_index);
static bool project_world_to_viewport(vec3 world_position, float* screen_x, float* screen_y, float* depth);
static void draw_projectiles(const Scene* scene);
static void clear_projectiles(Scene* scene);
static int find_projectile_slot(const Scene* scene);
static bool point_hits_obstacle(vec3 position, float radius, SceneObstacle obstacle);
static bool projectile_hits_obstacle(int room_index, vec3 position, float radius);
static void spawn_enemy_projectile(Scene* scene, int room_index);
static void draw_sphere(vec3 center, float radius, int slices, int stacks, float r, float g, float b);
static void draw_light_marker(const Scene* scene);
static void apply_light(const Scene* scene);
static bool load_object(SceneObject* object, const char* model_path, const char* texture_path, vec3 pos, float scale);
static void damage_player(Scene* scene, int damage);

void init_scene(Scene* scene)
{
    scene->object_count = 0;
    scene->selected_object = -1;
    scene->current_room = 0;
    scene->chamber_floor_texture = 0;
    scene->chamber_wall_texture = 0;
    scene->pedestal_texture = 0;
    scene->door_texture = 0;
    scene->enemy_texture = 0;
    scene->player_max_health = PLAYER_MAX_HEALTH;
    scene->player_health = scene->player_max_health;
    scene->player_hit_cooldown = 0.0f;
    scene->elapsed = 0.0f;

    scene->light_position = get_room_light_anchor(0);
    scene->light_intensity = 1.1f;

    for (int room_index = 0; room_index < SCENE_ROOM_COUNT; ++room_index) {
        scene->room_cleared[room_index] = (room_index == 0);
        scene->enemy_alive[room_index] = room_index > 0;
        scene->enemy_health[room_index] = (room_index > 0) ? ENEMY_MAX_HEALTH : 0;
        scene->enemy_position[room_index] = get_room_world_position(room_index, get_room_definition(room_index)->enemy_spawn);
        scene->enemy_shot_cooldown[room_index] = (room_index > 0) ? (0.75f + 0.10f * (float)(room_index - 1)) : ENEMY_FIRE_INTERVAL;
    }

    clear_projectiles(scene);

    for (int i = 0; i < SCENE_MAX_OBJECTS; ++i) {
        init_model(&scene->objects[i].model);
        scene->objects[i].texture = 0;
        scene->objects[i].position = (vec3){0, 0, 0};
        scene->objects[i].rotation = (vec3){0, 0, 0};
        scene->objects[i].scale = 1.0f;
        scene->objects[i].auto_rotate = false;
        scene->objects[i].unlit = false;
    }

    if (load_object(&scene->objects[0], "assets/models/cube.obj", "assets/textures/relic_item.ppm", (vec3){0.0f, 0.4f, 0.75f}, 1.0f)) {
        scene->objects[0].auto_rotate = true;
        scene->objects[0].unlit = true;
        scene->object_count++;
    }

    if (load_object(&scene->objects[1], "assets/models/ISAAC2.obj", "assets/textures/4_ons_black_bg_1920x1080.png", player_spawn_position, 1.25f)) {
        scene->object_count++;
    }

    scene->chamber_floor_texture = load_texture("assets/textures/isaac_floor.ppm");
    scene->chamber_wall_texture = load_texture("assets/textures/isaac_wall.ppm");
    scene->pedestal_texture = load_texture("assets/textures/pedestal_stone.ppm");
    scene->door_texture = load_texture("assets/textures/door_panel.ppm");
    scene->enemy_texture = load_texture("assets/textures/relic_item.ppm");

    if (SCENE_USE_LIGHTING) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    }
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_COLOR_MATERIAL);
    }

    glEnable(GL_NORMALIZE);

    apply_light(scene);
}

void destroy_scene(Scene* scene)
{
    if (scene->chamber_floor_texture != 0) {
        glDeleteTextures(1, &scene->chamber_floor_texture);
        scene->chamber_floor_texture = 0;
    }

    if (scene->chamber_wall_texture != 0) {
        glDeleteTextures(1, &scene->chamber_wall_texture);
        scene->chamber_wall_texture = 0;
    }

    if (scene->pedestal_texture != 0) {
        glDeleteTextures(1, &scene->pedestal_texture);
        scene->pedestal_texture = 0;
    }

    if (scene->door_texture != 0) {
        glDeleteTextures(1, &scene->door_texture);
        scene->door_texture = 0;
    }

    if (scene->enemy_texture != 0) {
        glDeleteTextures(1, &scene->enemy_texture);
        scene->enemy_texture = 0;
    }

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

    if (scene->player_hit_cooldown > 0.0f) {
        scene->player_hit_cooldown -= (float)dt;
        if (scene->player_hit_cooldown < 0.0f) {
            scene->player_hit_cooldown = 0.0f;
        }
    }

    if (scene->enemy_alive[scene->current_room] && scene->object_count > 1 && scene->player_health > 0) {
        const vec3 player_position = scene->objects[1].position;
        vec3 enemy_position = scene->enemy_position[scene->current_room];
        const float dx = player_position.x - enemy_position.x;
        const float dy = player_position.y - enemy_position.y;
        const float distance = sqrtf(dx * dx + dy * dy);

        if (distance > ENEMY_CONTACT_DISTANCE && distance > 0.001f) {
            scene->enemy_position[scene->current_room] = move_enemy_toward_target(
                scene,
                scene->current_room,
                enemy_position,
                player_position,
                ENEMY_MOVE_SPEED * (float)dt);
        }
        else {
            damage_player(scene, 1);
        }

        scene->enemy_shot_cooldown[scene->current_room] -= (float)dt;
        if (scene->enemy_shot_cooldown[scene->current_room] <= 0.0f) {
            spawn_enemy_projectile(scene, scene->current_room);
            scene->enemy_shot_cooldown[scene->current_room] = ENEMY_FIRE_INTERVAL;
        }
    }

    for (int i = 0; i < SCENE_MAX_PROJECTILES; ++i) {
        SceneProjectile* projectile = &scene->projectiles[i];

        if (!projectile->active) {
            continue;
        }

        projectile->position.x += projectile->velocity.x * (float)dt;
        projectile->position.y += projectile->velocity.y * (float)dt;
        projectile->position.z += projectile->velocity.z * (float)dt;
        projectile->lifetime -= (float)dt;

        if (projectile->lifetime <= 0.0f) {
            projectile->active = false;
            continue;
        }

        if (!projectile->hostile && scene->enemy_alive[projectile->room_index]) {
            const vec3 enemy_position = scene->enemy_position[projectile->room_index];
            const float hit_distance = sqrtf(
                (projectile->position.x - enemy_position.x) * (projectile->position.x - enemy_position.x) +
                (projectile->position.y - enemy_position.y) * (projectile->position.y - enemy_position.y));
            const float hit_height = fabsf(projectile->position.z - enemy_position.z);

            if (hit_distance <= PROJECTILE_HIT_DISTANCE && hit_height <= ENEMY_DRAW_SIZE * 0.8f) {
                projectile->active = false;

                if (scene->enemy_health[projectile->room_index] > 0) {
                    scene->enemy_health[projectile->room_index]--;
                }

                if (scene->enemy_health[projectile->room_index] <= 0) {
                    scene->enemy_alive[projectile->room_index] = false;
                    scene->enemy_health[projectile->room_index] = 0;
                    scene->room_cleared[projectile->room_index] = true;
                    scene->enemy_shot_cooldown[projectile->room_index] = ENEMY_FIRE_INTERVAL;
                }
                continue;
            }
        }

        if (projectile->hostile && projectile->room_index == scene->current_room && scene->object_count > 1) {
            const vec3 player_position = scene->objects[1].position;
            const float hit_distance = sqrtf(
                (projectile->position.x - player_position.x) * (projectile->position.x - player_position.x) +
                (projectile->position.y - player_position.y) * (projectile->position.y - player_position.y));

            if (hit_distance <= (PLAYER_COLLISION_RADIUS + PROJECTILE_RADIUS)) {
                projectile->active = false;
                damage_player(scene, 1);
                continue;
            }
        }

        if (projectile_hits_obstacle(projectile->room_index, projectile->position, PROJECTILE_RADIUS)) {
            projectile->active = false;
            continue;
        }

        const float room_center_y = get_room_center_y(projectile->room_index);
        const bool outside_room =
            fabsf(projectile->position.x) > (SCENE_ROOM_HALF_WIDTH - PLAYER_ROOM_MARGIN * 0.5f) ||
            projectile->position.y < room_center_y - SCENE_ROOM_HALF_DEPTH + PLAYER_ROOM_MARGIN * 0.5f ||
            projectile->position.y > room_center_y + SCENE_ROOM_HALF_DEPTH - PLAYER_ROOM_MARGIN * 0.5f;

        if (outside_room) {
            projectile->active = false;
            continue;
        }
    }

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

    draw_chamber(scene);
    draw_room_enemy(scene, scene->current_room);
    draw_projectiles(scene);
    if (SCENE_SHOW_LIGHT_MARKER) {
        draw_light_marker(scene);
    }

    for (int i = 0; i < scene->object_count; ++i) {
        if (i == 1) {
            continue;
        }

        if (get_room_index_from_y(scene->objects[i].position.y) != scene->current_room) {
            continue;
        }

        const SceneObject* object = &scene->objects[i];

        glPushMatrix();
        glTranslatef(object->position.x, object->position.y, object->position.z);
        glRotatef(object->rotation.x, 1, 0, 0);
        glRotatef(object->rotation.y, 0, 1, 0);
        glRotatef(object->rotation.z, 0, 0, 1);
        glScalef(object->scale, object->scale, object->scale);

        glBindTexture(GL_TEXTURE_2D, object->texture);
        glColor3f(1.0f, 1.0f, 1.0f);

        if (object->unlit && SCENE_USE_LIGHTING) {
            glDisable(GL_LIGHTING);
        }

        draw_model(&object->model);

        if (object->unlit && SCENE_USE_LIGHTING) {
            glEnable(GL_LIGHTING);
        }

        // Selection outline
        if (i == scene->selected_object) {
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glColor3f(1.0f, 1.0f, 0.0f);
            glLineWidth(2.0f);
            draw_selection_box(object);
            glLineWidth(1.0f);
            glEnable(GL_TEXTURE_2D);
            if (SCENE_USE_LIGHTING) {
                glEnable(GL_LIGHTING);
            }
        }

        glPopMatrix();
    }

    draw_enemy_health_bar_overlay(scene, scene->current_room);
}

void scene_select_object(Scene* scene, int index)
{
    if (scene->object_count <= 0) {
        scene->selected_object = -1;
        return;
    }

    if (index < 0) {
        scene->selected_object = -1;
        return;
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
    if (index < 0 || index >= scene->object_count) {
        return;
    }

    SceneObject* object = &scene->objects[index];
    const vec3 target_position = vec3_add(object->position, delta);
    const float margin = (index == 1) ? 1.4f : 0.9f;
    const float min_z = (index == 0) ? 0.55f : 0.0f;
    const float max_z = (index == 0) ? 2.2f : 1.2f;

    if (index == 1) {
        object->position = scene_resolve_player_position(scene, object->position, target_position);
        return;
    }

    object->position = clamp_room_position(target_position, scene->current_room, margin, min_z, max_z);
}

void scene_move_light(Scene* scene, vec3 delta)
{
    scene->light_position = vec3_add(scene->light_position, delta);
    scene->light_position = clamp_room_position(scene->light_position, scene->current_room, 0.6f, 0.8f, SCENE_ROOM_HEIGHT - 0.35f);
}

void scene_adjust_light(Scene* scene, float delta)
{
    scene->light_intensity = clampf(scene->light_intensity + delta, 0.0f, 4.0f);
}

bool scene_use_nearby_door(Scene* scene)
{
    if (scene->object_count <= 1 || !scene->room_cleared[scene->current_room]) {
        return false;
    }

    SceneObject* player = &scene->objects[1];
    const float room_center_y = get_room_center_y(scene->current_room);
    const float north_door_y = room_center_y + SCENE_ROOM_HALF_DEPTH - CHAMBER_DOOR_FRAME_DEPTH * 0.5f;
    const float south_door_y = room_center_y - SCENE_ROOM_HALF_DEPTH + CHAMBER_DOOR_FRAME_DEPTH * 0.5f;
    const float distance_to_north = sqrtf(player->position.x * player->position.x + (player->position.y - north_door_y) * (player->position.y - north_door_y));
    const float distance_to_south = sqrtf(player->position.x * player->position.x + (player->position.y - south_door_y) * (player->position.y - south_door_y));

    if (scene->current_room < SCENE_ROOM_COUNT - 1 && distance_to_north <= DOOR_USE_DISTANCE) {
        scene->current_room++;
        player->position = get_room_entry_position(scene->current_room, true);
        scene->light_position = get_room_light_anchor(scene->current_room);
        clear_projectiles(scene);
        return true;
    }

    if (scene->current_room > 0 && distance_to_south <= DOOR_USE_DISTANCE) {
        scene->current_room--;
        player->position = get_room_entry_position(scene->current_room, false);
        scene->light_position = get_room_light_anchor(scene->current_room);
        clear_projectiles(scene);
        return true;
    }

    return false;
}

void scene_fire_projectile(Scene* scene, float yaw_degrees)
{
    if (scene->object_count <= 1) {
        return;
    }

    const SceneObject* player = &scene->objects[1];
    const float yaw = (float)degree_to_radian(yaw_degrees);
    const vec3 forward = {
        cosf(yaw),
        sinf(yaw),
        0.0f
    };

    const int projectile_index = find_projectile_slot(scene);
    SceneProjectile* projectile = &scene->projectiles[projectile_index];

    projectile->active = true;
    projectile->hostile = false;
    projectile->room_index = scene->current_room;
    projectile->position = (vec3){
        player->position.x + forward.x * 0.65f,
        player->position.y + forward.y * 0.65f,
        ENEMY_CENTER_HEIGHT
    };
    projectile->velocity = (vec3){
        forward.x * PROJECTILE_SPEED,
        forward.y * PROJECTILE_SPEED,
        0.0f
    };
    projectile->lifetime = PROJECTILE_LIFETIME;
}

vec3 scene_resolve_player_position(const Scene* scene, vec3 previous_position, vec3 target_position)
{
    vec3 resolved = clamp_room_position(target_position, scene->current_room, PLAYER_ROOM_MARGIN, 0.0f, 1.2f);

    resolved = resolve_room_obstacles(previous_position, resolved, PLAYER_COLLISION_RADIUS, scene->current_room, 0.0f);
    resolved = clamp_room_position(resolved, scene->current_room, PLAYER_ROOM_MARGIN, 0.0f, 1.2f);

    return resolved;
}

static void apply_light(const Scene* scene)
{
    if (!SCENE_USE_LIGHTING) {
        return;
    }

    const float intensity = scene->light_intensity;
    const GLfloat diffuse[4] = {0.72f * intensity, 0.72f * intensity, 0.72f * intensity, 1.0f};
    const GLfloat ambient[4] = {0.32f * intensity, 0.32f * intensity, 0.32f * intensity, 1.0f};
    const GLfloat specular[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    const GLfloat position[4] = {scene->light_position.x, scene->light_position.y, scene->light_position.z, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
}

static const RoomDefinition* get_room_definition(int room_index)
{
    if (room_index < 0 || room_index >= SCENE_ROOM_COUNT) {
        return &room_definitions[0];
    }

    return &room_definitions[room_index];
}

static float get_room_center_y(int room_index)
{
    return (float)room_index * ROOM_SPACING;
}

static vec3 get_room_entry_position(int room_index, bool from_south)
{
    const float room_center_y = get_room_center_y(room_index);

    return (vec3){
        0.0f,
        room_center_y + (from_south ? (-SCENE_ROOM_HALF_DEPTH + ROOM_ENTRY_OFFSET) : (SCENE_ROOM_HALF_DEPTH - ROOM_ENTRY_OFFSET)),
        0.0f
    };
}

static vec3 get_room_world_position(int room_index, vec3 local_position)
{
    local_position.y += get_room_center_y(room_index);
    return local_position;
}

static SceneObstacle get_room_world_obstacle(int room_index, int obstacle_index)
{
    const RoomDefinition* room_definition = get_room_definition(room_index);
    SceneObstacle obstacle = room_definition->obstacles[obstacle_index];

    obstacle.center_y += get_room_center_y(room_index);

    return obstacle;
}

static vec3 get_room_light_anchor(int room_index)
{
    return (vec3){0.0f, get_room_center_y(room_index), SCENE_ROOM_HEIGHT - 0.65f};
}

static int get_room_index_from_y(float y)
{
    const int room_index = (int)floorf((y + SCENE_ROOM_HALF_DEPTH) / ROOM_SPACING);

    if (room_index < 0) {
        return 0;
    }
    if (room_index >= SCENE_ROOM_COUNT) {
        return SCENE_ROOM_COUNT - 1;
    }

    return room_index;
}

static vec3 clamp_room_position(vec3 position, int room_index, float margin, float min_z, float max_z)
{
    const float room_center_y = get_room_center_y(room_index);

    position.x = clampf(position.x, -SCENE_ROOM_HALF_WIDTH + margin, SCENE_ROOM_HALF_WIDTH - margin);
    position.y = clampf(position.y, room_center_y - SCENE_ROOM_HALF_DEPTH + margin, room_center_y + SCENE_ROOM_HALF_DEPTH - margin);
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

static vec3 resolve_room_movement(vec3 previous, vec3 desired, int room_index, float radius, float bottom_z, float margin, float min_z, float max_z)
{
    desired = clamp_room_position(desired, room_index, margin, min_z, max_z);
    desired = resolve_room_obstacles(previous, desired, radius, room_index, bottom_z);
    desired = clamp_room_position(desired, room_index, margin, min_z, max_z);

    return desired;
}

static vec3 resolve_room_obstacles(vec3 previous, vec3 desired, float radius, int room_index, float bottom_z)
{
    const RoomDefinition* room_definition = get_room_definition(room_index);

    for (int i = 0; i < room_definition->obstacle_count; ++i) {
        const SceneObstacle obstacle = get_room_world_obstacle(room_index, i);

        if (bottom_z > obstacle.height) {
            continue;
        }

        desired = resolve_box_collision(previous, desired, radius, obstacle);
    }

    return desired;
}

static vec3 move_enemy_toward_target(const Scene* scene, int room_index, vec3 enemy_position, vec3 target_position, float step_length)
{
    const float dx = target_position.x - enemy_position.x;
    const float dy = target_position.y - enemy_position.y;
    const float distance = sqrtf(dx * dx + dy * dy);
    const float candidate_angles[] = {0.0f, 0.35f, -0.35f, 0.70f, -0.70f, 1.05f, -1.05f, 1.40f, -1.40f, 1.75f, -1.75f, 2.20f, -2.20f};
    const float step_scales[] = {1.0f, 0.72f, 0.44f};
    vec3 best_position = enemy_position;
    float best_score = distance;
    float best_movement = 0.0f;
    const float axis_dir_x = (fabsf(dx) > 0.001f) ? ((dx > 0.0f) ? 1.0f : -1.0f) : 0.0f;
    const float axis_dir_y = (fabsf(dy) > 0.001f) ? ((dy > 0.0f) ? 1.0f : -1.0f) : 0.0f;

    (void)scene;

    if (distance <= 0.001f || step_length <= 0.0f) {
        return enemy_position;
    }

    for (int i = 0; i < (int)(sizeof(candidate_angles) / sizeof(candidate_angles[0])); ++i) {
        const float sin_angle = sinf(candidate_angles[i]);
        const float cos_angle = cosf(candidate_angles[i]);
        const float base_dir_x = (dx / distance) * cos_angle - (dy / distance) * sin_angle;
        const float base_dir_y = (dx / distance) * sin_angle + (dy / distance) * cos_angle;

        for (int step_index = 0; step_index < (int)(sizeof(step_scales) / sizeof(step_scales[0])); ++step_index) {
            vec3 desired_position;
            vec3 resolved_position;
            float step = step_length * step_scales[step_index];
            float movement;
            float score;

            desired_position = enemy_position;
            desired_position.x += base_dir_x * step;
            desired_position.y += base_dir_y * step;
            desired_position.z = ENEMY_CENTER_HEIGHT;

            resolved_position = resolve_room_movement(
                enemy_position,
                desired_position,
                room_index,
                ENEMY_HITBOX_RADIUS,
                0.0f,
                PLAYER_ROOM_MARGIN,
                ENEMY_CENTER_HEIGHT,
                ENEMY_CENTER_HEIGHT);

            movement = sqrtf(
                (resolved_position.x - enemy_position.x) * (resolved_position.x - enemy_position.x) +
                (resolved_position.y - enemy_position.y) * (resolved_position.y - enemy_position.y));

            if (movement < step * 0.20f) {
                continue;
            }

            score = sqrtf(
                (target_position.x - resolved_position.x) * (target_position.x - resolved_position.x) +
                (target_position.y - resolved_position.y) * (target_position.y - resolved_position.y));
            score += fabsf(candidate_angles[i]) * 0.06f;
            score += (1.0f - step_scales[step_index]) * 0.18f;
            score -= movement * 0.26f;

            if (best_movement <= 0.0f || score < best_score) {
                best_position = resolved_position;
                best_score = score;
                best_movement = movement;
            }
        }
    }

    if (best_movement < step_length * 0.32f) {
        const vec3 axis_targets[] = {
            {enemy_position.x + axis_dir_x * step_length, enemy_position.y, ENEMY_CENTER_HEIGHT},
            {enemy_position.x, enemy_position.y + axis_dir_y * step_length, ENEMY_CENTER_HEIGHT},
            {enemy_position.x + axis_dir_x * step_length * 0.65f, enemy_position.y + axis_dir_y * step_length * 0.35f, ENEMY_CENTER_HEIGHT},
            {enemy_position.x + axis_dir_x * step_length * 0.35f, enemy_position.y + axis_dir_y * step_length * 0.65f, ENEMY_CENTER_HEIGHT}
        };

        for (int i = 0; i < (int)(sizeof(axis_targets) / sizeof(axis_targets[0])); ++i) {
            vec3 resolved_position = resolve_room_movement(
                enemy_position,
                axis_targets[i],
                room_index,
                ENEMY_HITBOX_RADIUS,
                0.0f,
                PLAYER_ROOM_MARGIN,
                ENEMY_CENTER_HEIGHT,
                ENEMY_CENTER_HEIGHT);
            float movement = sqrtf(
                (resolved_position.x - enemy_position.x) * (resolved_position.x - enemy_position.x) +
                (resolved_position.y - enemy_position.y) * (resolved_position.y - enemy_position.y));
            float score;

            if (movement < step_length * 0.18f) {
                continue;
            }

            score = sqrtf(
                (target_position.x - resolved_position.x) * (target_position.x - resolved_position.x) +
                (target_position.y - resolved_position.y) * (target_position.y - resolved_position.y));
            score -= movement * 0.22f;

            if (best_movement <= 0.0f || score < best_score) {
                best_position = resolved_position;
                best_score = score;
                best_movement = movement;
            }
        }
    }

    return best_position;
}

static void draw_chamber(const Scene* scene)
{
    const bool has_south_room = scene->current_room > 0;
    const bool has_north_room = scene->current_room < (SCENE_ROOM_COUNT - 1);

    draw_room(scene, get_room_center_y(scene->current_room), false, false, has_south_room, has_north_room, false, false);
}

static void draw_room(const Scene* scene, float room_center_y, bool open_south, bool open_north, bool draw_south_door, bool draw_north_door, bool draw_west_door, bool draw_east_door)
{
    const int room_index = get_room_index_from_y(room_center_y);
    const RoomDefinition* room_definition = get_room_definition(room_index);
    const bool second_room = room_definition->layout_kind == ROOM_LAYOUT_RELIQUARY;
    const float room_x = SCENE_ROOM_HALF_WIDTH;
    const float room_y = SCENE_ROOM_HALF_DEPTH;
    const float room_z = SCENE_ROOM_HEIGHT;
    const float room_min_y = room_center_y - room_y;
    const float room_max_y = room_center_y + room_y;
    const float trim_depth = CHAMBER_TRIM_DEPTH;
    const float trim_height = CHAMBER_TRIM_HEIGHT;
    const float pillar_depth = CHAMBER_PILLAR_DEPTH;
    const float pillar_width = CHAMBER_PILLAR_WIDTH;
    const float floor_uv_x = (room_x * 2.0f) / (4.0f * CHAMBER_FLOOR_TILE_WORLD_SIZE);
    const float floor_uv_y = (room_y * 2.0f) / (4.0f * CHAMBER_FLOOR_TILE_WORLD_SIZE);
    const float wall_u_per_world = 4.0f / (room_x * 2.0f);
    const float wall_v_per_world = 2.0f / room_z;
    const float connector_side_width = room_x - CONNECTOR_OPEN_HALF_WIDTH;
    const float connector_header_height = room_z - CHAMBER_DOOR_LEAF_HEIGHT;
    const GLuint pedestal_texture = (scene->pedestal_texture != 0) ? scene->pedestal_texture : scene->chamber_floor_texture;
    const GLuint door_texture = (scene->door_texture != 0) ? scene->door_texture : scene->chamber_wall_texture;
    const GLuint ceiling_texture = second_room ? door_texture : pedestal_texture;
    const GLuint wall_detail_texture = second_room ? pedestal_texture : door_texture;
    const float floor_r = room_definition->floor_tint.x;
    const float floor_g = room_definition->floor_tint.y;
    const float floor_b = room_definition->floor_tint.z;
    const float wall_r = room_definition->wall_tint.x;
    const float wall_g = room_definition->wall_tint.y;
    const float wall_b = room_definition->wall_tint.z;
    const float floor_repeat_scale = room_definition->floor_repeat_scale;
    const float wall_repeat_scale = room_definition->wall_repeat_scale;
    const float ceiling_repeat_scale = room_definition->ceiling_repeat_scale;

    if (scene->chamber_floor_texture != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, scene->chamber_floor_texture);
        glColor3f(floor_r, floor_g, floor_b);
    }
    else {
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.20f, 0.21f, 0.24f);
    }

    draw_textured_quad_xy(0.0f, -room_x, room_x, room_min_y, room_max_y, 1.0f, floor_uv_x * floor_repeat_scale, floor_uv_y * floor_repeat_scale);

    if (scene->chamber_wall_texture != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, scene->chamber_wall_texture);
        glColor3f(wall_r, wall_g, wall_b);
    }
    else {
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.11f, 0.12f, 0.15f);
    }

    draw_textured_quad_xy(room_z, -room_x, room_x, room_min_y, room_max_y, -1.0f, 4.0f * ceiling_repeat_scale, 4.0f * ceiling_repeat_scale);

    if (open_north) {
        draw_textured_quad_xz(room_max_y, -room_x, -CONNECTOR_OPEN_HALF_WIDTH, 0.0f, room_z, -1.0f, connector_side_width * wall_u_per_world * wall_repeat_scale, 2.0f * wall_repeat_scale);
        draw_textured_quad_xz(room_max_y, CONNECTOR_OPEN_HALF_WIDTH, room_x, 0.0f, room_z, -1.0f, connector_side_width * wall_u_per_world * wall_repeat_scale, 2.0f * wall_repeat_scale);
        draw_textured_quad_xz(room_max_y, -CONNECTOR_OPEN_HALF_WIDTH, CONNECTOR_OPEN_HALF_WIDTH, CHAMBER_DOOR_LEAF_HEIGHT, room_z, -1.0f, CONNECTOR_OPEN_HALF_WIDTH * 2.0f * wall_u_per_world * wall_repeat_scale, connector_header_height * wall_v_per_world * wall_repeat_scale);
    }
    else {
        draw_textured_quad_xz(room_max_y, -room_x, room_x, 0.0f, room_z, -1.0f, 4.0f * wall_repeat_scale, 2.0f * wall_repeat_scale);
    }

    draw_textured_quad_yz(-room_x, room_min_y, room_max_y, 0.0f, room_z, 1.0f, 4.0f * wall_repeat_scale, 2.0f * wall_repeat_scale);
    draw_textured_quad_yz(room_x, room_min_y, room_max_y, 0.0f, room_z, -1.0f, 4.0f * wall_repeat_scale, 2.0f * wall_repeat_scale);

    if (open_south) {
        draw_textured_quad_xz(room_min_y, -room_x, -CONNECTOR_OPEN_HALF_WIDTH, 0.0f, room_z, 1.0f, connector_side_width * wall_u_per_world * wall_repeat_scale, 2.0f * wall_repeat_scale);
        draw_textured_quad_xz(room_min_y, CONNECTOR_OPEN_HALF_WIDTH, room_x, 0.0f, room_z, 1.0f, connector_side_width * wall_u_per_world * wall_repeat_scale, 2.0f * wall_repeat_scale);
        draw_textured_quad_xz(room_min_y, -CONNECTOR_OPEN_HALF_WIDTH, CONNECTOR_OPEN_HALF_WIDTH, CHAMBER_DOOR_LEAF_HEIGHT, room_z, 1.0f, CONNECTOR_OPEN_HALF_WIDTH * 2.0f * wall_u_per_world * wall_repeat_scale, connector_header_height * wall_v_per_world * wall_repeat_scale);
    }
    else {
        draw_textured_quad_xz(room_min_y, -room_x, room_x, 0.0f, room_z, 1.0f, 4.0f * wall_repeat_scale, 2.0f * wall_repeat_scale);
    }

    glDisable(GL_TEXTURE_2D);

    if (open_north) {
        draw_box(
            (vec3){-CONNECTOR_SIDE_CENTER_X, room_max_y - trim_depth * 0.5f, trim_height * 0.5f},
            (vec3){connector_side_width, trim_depth, trim_height},
            0.26f, 0.22f, 0.18f);
        draw_box(
            (vec3){CONNECTOR_SIDE_CENTER_X, room_max_y - trim_depth * 0.5f, trim_height * 0.5f},
            (vec3){connector_side_width, trim_depth, trim_height},
            0.26f, 0.22f, 0.18f);
    }
    else {
        draw_box(
            (vec3){0.0f, room_max_y - trim_depth * 0.5f, trim_height * 0.5f},
            (vec3){room_x * 2.0f - 0.55f, trim_depth, trim_height},
            second_room ? 0.20f : 0.26f, second_room ? 0.24f : 0.22f, second_room ? 0.28f : 0.18f);
    }
    draw_box(
        (vec3){-room_x + trim_depth * 0.5f, room_center_y, trim_height * 0.5f},
        (vec3){trim_depth, room_y * 2.0f - 0.55f, trim_height},
        second_room ? 0.18f : 0.24f, second_room ? 0.22f : 0.20f, second_room ? 0.28f : 0.17f);
    draw_box(
        (vec3){room_x - trim_depth * 0.5f, room_center_y, trim_height * 0.5f},
        (vec3){trim_depth, room_y * 2.0f - 0.55f, trim_height},
        second_room ? 0.18f : 0.24f, second_room ? 0.22f : 0.20f, second_room ? 0.28f : 0.17f);

    if (open_south) {
        draw_box(
            (vec3){-CONNECTOR_SIDE_CENTER_X, room_min_y + trim_depth * 0.5f, trim_height * 0.5f},
            (vec3){connector_side_width, trim_depth, trim_height},
            0.24f, 0.20f, 0.17f);
        draw_box(
            (vec3){CONNECTOR_SIDE_CENTER_X, room_min_y + trim_depth * 0.5f, trim_height * 0.5f},
            (vec3){connector_side_width, trim_depth, trim_height},
            0.24f, 0.20f, 0.17f);
    }
    else {
        draw_box(
            (vec3){0.0f, room_min_y + trim_depth * 0.5f, trim_height * 0.5f},
            (vec3){room_x * 2.0f - 0.55f, trim_depth, trim_height},
            second_room ? 0.18f : 0.24f, second_room ? 0.22f : 0.20f, second_room ? 0.28f : 0.17f);
    }

    draw_box(
        (vec3){-room_x + pillar_depth * 0.5f, room_max_y - pillar_width * 0.5f, room_z * 0.5f},
        (vec3){pillar_depth, pillar_width, room_z},
        0.30f, 0.26f, 0.21f);
    draw_box(
        (vec3){room_x - pillar_depth * 0.5f, room_max_y - pillar_width * 0.5f, room_z * 0.5f},
        (vec3){pillar_depth, pillar_width, room_z},
        0.30f, 0.26f, 0.21f);
    draw_box(
        (vec3){-room_x + pillar_depth * 0.5f, room_min_y + pillar_width * 0.5f, room_z * 0.5f},
        (vec3){pillar_depth, pillar_width, room_z},
        0.28f, 0.24f, 0.20f);
    draw_box(
        (vec3){room_x - pillar_depth * 0.5f, room_min_y + pillar_width * 0.5f, room_z * 0.5f},
        (vec3){pillar_depth, pillar_width, room_z},
        0.28f, 0.24f, 0.20f);

    draw_box(
        (vec3){-room_x + 0.10f, room_center_y + 1.75f, 1.65f},
        (vec3){0.08f, 1.5f, 2.2f},
        0.32f, 0.27f, 0.22f);
    draw_box(
        (vec3){room_x - 0.10f, room_center_y + 1.75f, 1.65f},
        (vec3){0.08f, 1.5f, 2.2f},
        0.32f, 0.27f, 0.22f);

    if (open_south) {
        draw_open_door_frame((vec3){0.0f, room_min_y + CHAMBER_DOOR_FRAME_DEPTH * 0.5f, 0.0f}, 0.0f, door_texture);
    }
    else if (draw_south_door) {
        draw_door_assembly((vec3){0.0f, room_min_y + CHAMBER_DOOR_FRAME_DEPTH * 0.5f, 0.0f}, 0.0f, door_texture);
    }

    if (open_north) {
        draw_open_door_frame((vec3){0.0f, room_max_y - CHAMBER_DOOR_FRAME_DEPTH * 0.5f, 0.0f}, 180.0f, door_texture);
    }
    else if (draw_north_door) {
        draw_door_assembly((vec3){0.0f, room_max_y - CHAMBER_DOOR_FRAME_DEPTH * 0.5f, 0.0f}, 180.0f, door_texture);
    }

    if (draw_east_door) {
        draw_door_assembly((vec3){room_x - CHAMBER_DOOR_FRAME_DEPTH * 0.5f, room_center_y, 0.0f}, 90.0f, door_texture);
    }
    if (draw_west_door) {
        draw_door_assembly((vec3){-room_x + CHAMBER_DOOR_FRAME_DEPTH * 0.5f, room_center_y, 0.0f}, -90.0f, door_texture);
    }

    draw_textured_box(
        (vec3){0.0f, room_center_y, room_z - 0.12f},
        (vec3){room_x * 2.0f - 1.10f, room_y * 2.0f - 1.10f, 0.18f},
        ceiling_texture,
        room_definition->ceiling_tint.x,
        room_definition->ceiling_tint.y,
        room_definition->ceiling_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    if (room_definition->layout_kind == ROOM_LAYOUT_RELIQUARY) {
        draw_reliquary_room_features(room_definition, room_center_y, room_z, pedestal_texture, wall_detail_texture);
    }
    else if (room_definition->layout_kind == ROOM_LAYOUT_FORGE) {
        draw_forge_room_features(room_definition, room_center_y, room_z, pedestal_texture, wall_detail_texture);
    }
    else if (room_definition->layout_kind == ROOM_LAYOUT_ARCHIVE) {
        draw_archive_room_features(room_definition, room_center_y, room_z, pedestal_texture, wall_detail_texture);
    }
    else {
        draw_entry_room_features(room_definition, room_center_y, room_z, pedestal_texture, wall_detail_texture);
    }

    glEnable(GL_TEXTURE_2D);
}

static void draw_textured_quad_xy(float z, float min_x, float max_x, float min_y, float max_y, float normal_z, float u_repeat, float v_repeat)
{
    glBegin(GL_QUADS);

    glNormal3f(0.0f, 0.0f, normal_z);
    if (normal_z > 0.0f) {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(min_x, min_y, z);
        glTexCoord2f(u_repeat, 0.0f);
        glVertex3f(max_x, min_y, z);
        glTexCoord2f(u_repeat, v_repeat);
        glVertex3f(max_x, max_y, z);
        glTexCoord2f(0.0f, v_repeat);
        glVertex3f(min_x, max_y, z);
    }
    else {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(min_x, max_y, z);
        glTexCoord2f(u_repeat, 0.0f);
        glVertex3f(max_x, max_y, z);
        glTexCoord2f(u_repeat, v_repeat);
        glVertex3f(max_x, min_y, z);
        glTexCoord2f(0.0f, v_repeat);
        glVertex3f(min_x, min_y, z);
    }

    glEnd();
}

static void draw_textured_quad_xz(float y, float min_x, float max_x, float min_z, float max_z, float normal_y, float u_repeat, float v_repeat)
{
    glBegin(GL_QUADS);

    glNormal3f(0.0f, normal_y, 0.0f);
    if (normal_y < 0.0f) {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(min_x, y, min_z);
        glTexCoord2f(u_repeat, 0.0f);
        glVertex3f(max_x, y, min_z);
        glTexCoord2f(u_repeat, v_repeat);
        glVertex3f(max_x, y, max_z);
        glTexCoord2f(0.0f, v_repeat);
        glVertex3f(min_x, y, max_z);
    }
    else {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(max_x, y, min_z);
        glTexCoord2f(u_repeat, 0.0f);
        glVertex3f(min_x, y, min_z);
        glTexCoord2f(u_repeat, v_repeat);
        glVertex3f(min_x, y, max_z);
        glTexCoord2f(0.0f, v_repeat);
        glVertex3f(max_x, y, max_z);
    }

    glEnd();
}

static void draw_textured_quad_yz(float x, float min_y, float max_y, float min_z, float max_z, float normal_x, float u_repeat, float v_repeat)
{
    glBegin(GL_QUADS);

    glNormal3f(normal_x, 0.0f, 0.0f);
    if (normal_x > 0.0f) {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, min_y, min_z);
        glTexCoord2f(u_repeat, 0.0f);
        glVertex3f(x, max_y, min_z);
        glTexCoord2f(u_repeat, v_repeat);
        glVertex3f(x, max_y, max_z);
        glTexCoord2f(0.0f, v_repeat);
        glVertex3f(x, min_y, max_z);
    }
    else {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, max_y, min_z);
        glTexCoord2f(u_repeat, 0.0f);
        glVertex3f(x, min_y, min_z);
        glTexCoord2f(u_repeat, v_repeat);
        glVertex3f(x, min_y, max_z);
        glTexCoord2f(0.0f, v_repeat);
        glVertex3f(x, max_y, max_z);
    }

    glEnd();
}

static void draw_box(vec3 center, vec3 size, float r, float g, float b)
{
    const float half_x = size.x * 0.5f;
    const float half_y = size.y * 0.5f;
    const float half_z = size.z * 0.5f;

    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);

    glBegin(GL_QUADS);

    glColor3f(r, g, b);
    glNormal3f(0, 0, 1);
    glVertex3f(-half_x, -half_y, half_z);
    glVertex3f(half_x, -half_y, half_z);
    glVertex3f(half_x, half_y, half_z);
    glVertex3f(-half_x, half_y, half_z);

    glColor3f(r * 0.74f, g * 0.74f, b * 0.74f);
    glNormal3f(0, 0, -1);
    glVertex3f(-half_x, half_y, -half_z);
    glVertex3f(half_x, half_y, -half_z);
    glVertex3f(half_x, -half_y, -half_z);
    glVertex3f(-half_x, -half_y, -half_z);

    glColor3f(r * 0.86f, g * 0.86f, b * 0.86f);
    glNormal3f(0, -1, 0);
    glVertex3f(-half_x, -half_y, -half_z);
    glVertex3f(half_x, -half_y, -half_z);
    glVertex3f(half_x, -half_y, half_z);
    glVertex3f(-half_x, -half_y, half_z);

    glColor3f(r * 0.94f, g * 0.94f, b * 0.94f);
    glNormal3f(0, 1, 0);
    glVertex3f(half_x, half_y, -half_z);
    glVertex3f(-half_x, half_y, -half_z);
    glVertex3f(-half_x, half_y, half_z);
    glVertex3f(half_x, half_y, half_z);

    glColor3f(r * 0.80f, g * 0.80f, b * 0.80f);
    glNormal3f(-1, 0, 0);
    glVertex3f(-half_x, half_y, -half_z);
    glVertex3f(-half_x, -half_y, -half_z);
    glVertex3f(-half_x, -half_y, half_z);
    glVertex3f(-half_x, half_y, half_z);

    glColor3f(r * 0.98f, g * 0.98f, b * 0.98f);
    glNormal3f(1, 0, 0);
    glVertex3f(half_x, -half_y, -half_z);
    glVertex3f(half_x, half_y, -half_z);
    glVertex3f(half_x, half_y, half_z);
    glVertex3f(half_x, -half_y, half_z);

    glEnd();

    glPopMatrix();
}

static void draw_textured_box(vec3 center, vec3 size, GLuint texture, float r, float g, float b, float texture_world_size, bool unlit)
{
    const float half_x = size.x * 0.5f;
    const float half_y = size.y * 0.5f;
    const float half_z = size.z * 0.5f;
    const float repeat_x = fmaxf(size.x / texture_world_size, 1.0f);
    const float repeat_y = fmaxf(size.y / texture_world_size, 1.0f);
    const float repeat_z = fmaxf(size.z / texture_world_size, 1.0f);
    const bool disable_lighting = unlit && SCENE_USE_LIGHTING;
    const GLboolean texture_was_enabled = glIsEnabled(GL_TEXTURE_2D);

    if (disable_lighting) {
        glDisable(GL_LIGHTING);
    }

    if (texture == 0) {
        draw_box(center, size, r, g, b);
        if (disable_lighting) {
            glEnable(GL_LIGHTING);
        }
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);

    glBegin(GL_QUADS);

    glColor3f(r, g, b);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half_x, -half_y, half_z);
    glTexCoord2f(repeat_x, 0.0f);
    glVertex3f(half_x, -half_y, half_z);
    glTexCoord2f(repeat_x, repeat_y);
    glVertex3f(half_x, half_y, half_z);
    glTexCoord2f(0.0f, repeat_y);
    glVertex3f(-half_x, half_y, half_z);

    glColor3f(r * 0.94f, g * 0.94f, b * 0.94f);
    glNormal3f(0, 0, -1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half_x, half_y, -half_z);
    glTexCoord2f(repeat_x, 0.0f);
    glVertex3f(half_x, half_y, -half_z);
    glTexCoord2f(repeat_x, repeat_y);
    glVertex3f(half_x, -half_y, -half_z);
    glTexCoord2f(0.0f, repeat_y);
    glVertex3f(-half_x, -half_y, -half_z);

    glColor3f(r * 0.97f, g * 0.97f, b * 0.97f);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half_x, -half_y, -half_z);
    glTexCoord2f(repeat_x, 0.0f);
    glVertex3f(half_x, -half_y, -half_z);
    glTexCoord2f(repeat_x, repeat_z);
    glVertex3f(half_x, -half_y, half_z);
    glTexCoord2f(0.0f, repeat_z);
    glVertex3f(-half_x, -half_y, half_z);

    glColor3f(r * 0.99f, g * 0.99f, b * 0.99f);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(half_x, half_y, -half_z);
    glTexCoord2f(repeat_x, 0.0f);
    glVertex3f(-half_x, half_y, -half_z);
    glTexCoord2f(repeat_x, repeat_z);
    glVertex3f(-half_x, half_y, half_z);
    glTexCoord2f(0.0f, repeat_z);
    glVertex3f(half_x, half_y, half_z);

    glColor3f(r * 0.95f, g * 0.95f, b * 0.95f);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half_x, half_y, -half_z);
    glTexCoord2f(repeat_y, 0.0f);
    glVertex3f(-half_x, -half_y, -half_z);
    glTexCoord2f(repeat_y, repeat_z);
    glVertex3f(-half_x, -half_y, half_z);
    glTexCoord2f(0.0f, repeat_z);
    glVertex3f(-half_x, half_y, half_z);

    glColor3f(r, g, b);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(half_x, -half_y, -half_z);
    glTexCoord2f(repeat_y, 0.0f);
    glVertex3f(half_x, half_y, -half_z);
    glTexCoord2f(repeat_y, repeat_z);
    glVertex3f(half_x, half_y, half_z);
    glTexCoord2f(0.0f, repeat_z);
    glVertex3f(half_x, -half_y, half_z);

    glEnd();

    glPopMatrix();

    if (!texture_was_enabled) {
        glDisable(GL_TEXTURE_2D);
    }

    if (disable_lighting) {
        glEnable(GL_LIGHTING);
    }
}

static void draw_door_assembly(vec3 center, float rotation_z, GLuint texture)
{
    const float post_center_x = CHAMBER_DOOR_HALF_WIDTH + CHAMBER_DOOR_FRAME_WIDTH * 0.5f - CHAMBER_DOOR_FRAME_OVERLAP;
    const float header_center_z = CHAMBER_DOOR_LEAF_HEIGHT + CHAMBER_DOOR_HEADER_HEIGHT * 0.5f - CHAMBER_DOOR_FRAME_OVERLAP;
    const float leaf_center_y = 0.05f;
    const float accent_trim_depth = 0.03f;
    const float trim_center_y = leaf_center_y + (CHAMBER_DOOR_LEAF_DEPTH + accent_trim_depth) * 0.5f + 0.01f;

    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);
    glRotatef(rotation_z, 0, 0, 1);

    draw_textured_box(
        (vec3){-post_center_x, 0.0f, CHAMBER_DOOR_LEAF_HEIGHT * 0.5f},
        (vec3){CHAMBER_DOOR_FRAME_WIDTH, CHAMBER_DOOR_FRAME_DEPTH, CHAMBER_DOOR_LEAF_HEIGHT + 0.04f},
        texture,
        0.88f, 0.84f, 0.78f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        true);
    draw_textured_box(
        (vec3){post_center_x, 0.0f, CHAMBER_DOOR_LEAF_HEIGHT * 0.5f},
        (vec3){CHAMBER_DOOR_FRAME_WIDTH, CHAMBER_DOOR_FRAME_DEPTH, CHAMBER_DOOR_LEAF_HEIGHT + 0.04f},
        texture,
        0.88f, 0.84f, 0.78f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        true);
    draw_textured_box(
        (vec3){0.0f, 0.0f, header_center_z},
        (vec3){CHAMBER_DOOR_LEAF_WIDTH + CHAMBER_DOOR_FRAME_WIDTH * 2.0f - 0.04f, CHAMBER_DOOR_FRAME_DEPTH, CHAMBER_DOOR_HEADER_HEIGHT},
        texture,
        0.86f, 0.82f, 0.76f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        true);
    draw_textured_box(
        (vec3){0.0f, leaf_center_y, CHAMBER_DOOR_LEAF_HEIGHT * 0.5f},
        (vec3){CHAMBER_DOOR_LEAF_WIDTH, CHAMBER_DOOR_LEAF_DEPTH, CHAMBER_DOOR_LEAF_HEIGHT},
        texture,
        0.68f, 0.64f, 0.60f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        true);
    draw_textured_box(
        (vec3){0.0f, trim_center_y, CHAMBER_DOOR_LEAF_HEIGHT * 0.69f},
        (vec3){CHAMBER_DOOR_LEAF_WIDTH - 0.14f, accent_trim_depth, 0.12f},
        texture,
        0.58f, 0.54f, 0.50f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        true);
    draw_textured_box(
        (vec3){0.0f, trim_center_y, CHAMBER_DOOR_LEAF_HEIGHT * 0.35f},
        (vec3){CHAMBER_DOOR_LEAF_WIDTH - 0.14f, accent_trim_depth, 0.12f},
        texture,
        0.58f, 0.54f, 0.50f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        true);

    glPopMatrix();
}

static void draw_open_door_frame(vec3 center, float rotation_z, GLuint texture)
{
    const float post_center_x = CHAMBER_DOOR_HALF_WIDTH + CHAMBER_DOOR_FRAME_WIDTH * 0.5f - CHAMBER_DOOR_FRAME_OVERLAP;
    const float header_center_z = CHAMBER_DOOR_LEAF_HEIGHT + CHAMBER_DOOR_HEADER_HEIGHT * 0.5f - CHAMBER_DOOR_FRAME_OVERLAP;

    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);
    glRotatef(rotation_z, 0, 0, 1);

    draw_textured_box(
        (vec3){-post_center_x, 0.0f, CHAMBER_DOOR_LEAF_HEIGHT * 0.5f},
        (vec3){CHAMBER_DOOR_FRAME_WIDTH, CHAMBER_DOOR_FRAME_DEPTH, CHAMBER_DOOR_LEAF_HEIGHT + 0.04f},
        texture,
        0.88f, 0.84f, 0.78f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        true);
    draw_textured_box(
        (vec3){post_center_x, 0.0f, CHAMBER_DOOR_LEAF_HEIGHT * 0.5f},
        (vec3){CHAMBER_DOOR_FRAME_WIDTH, CHAMBER_DOOR_FRAME_DEPTH, CHAMBER_DOOR_LEAF_HEIGHT + 0.04f},
        texture,
        0.88f, 0.84f, 0.78f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        true);
    draw_textured_box(
        (vec3){0.0f, 0.0f, header_center_z},
        (vec3){CHAMBER_DOOR_LEAF_WIDTH + CHAMBER_DOOR_FRAME_WIDTH * 2.0f - 0.04f, CHAMBER_DOOR_FRAME_DEPTH, CHAMBER_DOOR_HEADER_HEIGHT},
        texture,
        0.86f, 0.82f, 0.76f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        true);

    glPopMatrix();
}

static void draw_selection_box(const SceneObject* object)
{
    vec3 min_corner;
    vec3 max_corner;
    const float padding = 0.03f;

    get_model_bounds(&object->model, &min_corner, &max_corner);

    min_corner.x -= padding;
    min_corner.y -= padding;
    min_corner.z -= padding;
    max_corner.x += padding;
    max_corner.y += padding;
    max_corner.z += padding;

    glBegin(GL_LINES);

    glVertex3f(min_corner.x, min_corner.y, min_corner.z);
    glVertex3f(max_corner.x, min_corner.y, min_corner.z);
    glVertex3f(max_corner.x, min_corner.y, min_corner.z);
    glVertex3f(max_corner.x, max_corner.y, min_corner.z);
    glVertex3f(max_corner.x, max_corner.y, min_corner.z);
    glVertex3f(min_corner.x, max_corner.y, min_corner.z);
    glVertex3f(min_corner.x, max_corner.y, min_corner.z);
    glVertex3f(min_corner.x, min_corner.y, min_corner.z);

    glVertex3f(min_corner.x, min_corner.y, max_corner.z);
    glVertex3f(max_corner.x, min_corner.y, max_corner.z);
    glVertex3f(max_corner.x, min_corner.y, max_corner.z);
    glVertex3f(max_corner.x, max_corner.y, max_corner.z);
    glVertex3f(max_corner.x, max_corner.y, max_corner.z);
    glVertex3f(min_corner.x, max_corner.y, max_corner.z);
    glVertex3f(min_corner.x, max_corner.y, max_corner.z);
    glVertex3f(min_corner.x, min_corner.y, max_corner.z);

    glVertex3f(min_corner.x, min_corner.y, min_corner.z);
    glVertex3f(min_corner.x, min_corner.y, max_corner.z);
    glVertex3f(max_corner.x, min_corner.y, min_corner.z);
    glVertex3f(max_corner.x, min_corner.y, max_corner.z);
    glVertex3f(max_corner.x, max_corner.y, min_corner.z);
    glVertex3f(max_corner.x, max_corner.y, max_corner.z);
    glVertex3f(min_corner.x, max_corner.y, min_corner.z);
    glVertex3f(min_corner.x, max_corner.y, max_corner.z);

    glEnd();
}

static void get_model_bounds(const Model* model, vec3* min_corner, vec3* max_corner)
{
    if (model->n_vertices <= 0) {
        *min_corner = (vec3){0.0f, 0.0f, 0.0f};
        *max_corner = (vec3){0.0f, 0.0f, 0.0f};
        return;
    }

    min_corner->x = (float)model->vertices[1].x;
    min_corner->y = (float)model->vertices[1].y;
    min_corner->z = (float)model->vertices[1].z;
    *max_corner = *min_corner;

    for (int i = 2; i <= model->n_vertices; ++i) {
        const float x = (float)model->vertices[i].x;
        const float y = (float)model->vertices[i].y;
        const float z = (float)model->vertices[i].z;

        if (x < min_corner->x) {
            min_corner->x = x;
        }
        if (x > max_corner->x) {
            max_corner->x = x;
        }
        if (y < min_corner->y) {
            min_corner->y = y;
        }
        if (y > max_corner->y) {
            max_corner->y = y;
        }
        if (z < min_corner->z) {
            min_corner->z = z;
        }
        if (z > max_corner->z) {
            max_corner->z = z;
        }
    }
}

static void draw_pedestal(vec3 position, float width, float depth, float height, GLuint texture, float r, float g, float b)
{
    draw_textured_box(
        (vec3){position.x, position.y, position.z + height * 0.5f},
        (vec3){width, depth, height},
        texture,
        r, g, b,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        true);
}

static void draw_entry_room_features(const RoomDefinition* room_definition, float room_center_y, float room_z, GLuint pedestal_texture, GLuint detail_texture)
{
    draw_textured_box(
        (vec3){-1.35f, room_center_y - 0.15f, 0.05f},
        (vec3){1.20f, 6.10f, 0.10f},
        detail_texture,
        0.70f, 0.54f, 0.22f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){1.75f, room_center_y + 1.85f, 0.06f},
        (vec3){2.90f, 0.90f, 0.12f},
        detail_texture,
        room_definition->accent_tint.x,
        room_definition->accent_tint.y,
        room_definition->accent_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){2.10f, room_center_y - 2.30f, 0.06f},
        (vec3){1.40f, 1.40f, 0.12f},
        detail_texture,
        0.76f, 0.64f, 0.30f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-2.35f, room_center_y + 3.70f, 0.90f},
        (vec3){1.70f, 0.30f, 1.80f},
        detail_texture,
        room_definition->beam_tint.x,
        room_definition->beam_tint.y,
        room_definition->beam_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y - 1.95f, room_z - 0.34f},
        (vec3){9.70f, 0.24f, 0.34f},
        detail_texture,
        room_definition->beam_tint.x,
        room_definition->beam_tint.y,
        room_definition->beam_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y + 1.95f, room_z - 0.34f},
        (vec3){9.70f, 0.24f, 0.34f},
        detail_texture,
        room_definition->beam_tint.x,
        room_definition->beam_tint.y,
        room_definition->beam_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y, room_z - 0.30f},
        (vec3){0.30f, 9.80f, 0.34f},
        detail_texture,
        room_definition->accent_tint.x,
        room_definition->accent_tint.y,
        room_definition->accent_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y + 5.62f, 1.48f},
        (vec3){3.20f, 0.24f, 1.60f},
        detail_texture,
        0.68f, 0.52f, 0.20f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);

    draw_pedestal((vec3){0.0f, room_center_y + 0.4f, 0.0f}, 2.0f, 2.0f, 0.25f, pedestal_texture, 0.92f, 0.96f, 1.0f);
    draw_pedestal((vec3){-2.8f, room_center_y + 2.2f, 0.0f}, 1.4f, 1.0f, 0.35f, pedestal_texture, 0.74f, 0.80f, 0.90f);
    draw_pedestal((vec3){2.8f, room_center_y + 2.2f, 0.0f}, 1.4f, 1.0f, 0.35f, pedestal_texture, 0.74f, 0.80f, 0.90f);
    draw_textured_box(
        (vec3){-2.30f, room_center_y - 2.00f, 0.48f},
        (vec3){0.48f, 0.48f, 0.96f},
        detail_texture,
        0.72f, 0.58f, 0.24f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){2.30f, room_center_y - 2.00f, 0.48f},
        (vec3){0.48f, 0.48f, 0.96f},
        detail_texture,
        0.72f, 0.58f, 0.24f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
}

static void draw_reliquary_room_features(const RoomDefinition* room_definition, float room_center_y, float room_z, GLuint ritual_texture, GLuint relic_texture)
{
    draw_textured_box(
        (vec3){1.45f, room_center_y + 0.35f, 0.05f},
        (vec3){1.10f, 7.80f, 0.10f},
        ritual_texture,
        room_definition->accent_tint.x,
        room_definition->accent_tint.y,
        room_definition->accent_tint.z,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-1.90f, room_center_y - 2.35f, 0.05f},
        (vec3){1.60f, 1.10f, 0.10f},
        ritual_texture,
        0.34f, 0.58f, 0.94f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-3.70f, room_center_y, 0.14f},
        (vec3){0.42f, 8.80f, 0.24f},
        ritual_texture,
        0.26f, 0.46f, 0.84f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y - 2.55f, 0.12f},
        (vec3){4.4f, 1.0f, 0.24f},
        ritual_texture,
        0.38f, 0.56f, 0.90f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y - 2.30f, room_z - 0.34f},
        (vec3){9.40f, 0.28f, 0.34f},
        relic_texture,
        room_definition->beam_tint.x,
        room_definition->beam_tint.y,
        room_definition->beam_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y, room_z - 0.34f},
        (vec3){9.40f, 0.28f, 0.34f},
        relic_texture,
        room_definition->beam_tint.x,
        room_definition->beam_tint.y,
        room_definition->beam_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y + 2.30f, room_z - 0.34f},
        (vec3){9.40f, 0.28f, 0.34f},
        relic_texture,
        room_definition->beam_tint.x,
        room_definition->beam_tint.y,
        room_definition->beam_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-1.85f, room_center_y - 0.85f, room_z - 0.28f},
        (vec3){0.22f, 3.10f, 0.30f},
        relic_texture,
        room_definition->accent_tint.x,
        room_definition->accent_tint.y,
        room_definition->accent_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){1.85f, room_center_y + 0.85f, room_z - 0.28f},
        (vec3){0.22f, 3.10f, 0.30f},
        relic_texture,
        room_definition->accent_tint.x,
        room_definition->accent_tint.y,
        room_definition->accent_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-2.90f, room_center_y, 0.58f},
        (vec3){0.60f, 5.40f, 1.16f},
        ritual_texture,
        0.28f, 0.42f, 0.76f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){1.90f, room_center_y + 0.80f, 1.25f},
        (vec3){1.10f, 1.10f, 2.50f},
        relic_texture,
        0.46f, 0.30f, 0.20f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-0.60f, room_center_y + 0.70f, 1.15f},
        (vec3){0.34f, 0.34f, 2.30f},
        relic_texture,
        0.64f, 0.42f, 0.20f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y + 3.60f, 0.75f},
        (vec3){4.20f, 0.90f, 1.50f},
        relic_texture,
        0.36f, 0.28f, 0.22f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){2.35f, room_center_y - 1.80f, 0.10f},
        (vec3){1.10f, 0.60f, 0.20f},
        ritual_texture,
        0.54f, 0.68f, 0.94f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-1.55f, room_center_y + 2.00f, 0.10f},
        (vec3){0.90f, 0.60f, 0.20f},
        ritual_texture,
        0.54f, 0.68f, 0.94f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y + 4.10f, room_z - 0.24f},
        (vec3){4.8f, 0.28f, 0.20f},
        relic_texture,
        0.66f, 0.44f, 0.22f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
}

static void draw_forge_room_features(const RoomDefinition* room_definition, float room_center_y, float room_z, GLuint ritual_texture, GLuint detail_texture)
{
    draw_textured_box(
        (vec3){0.0f, room_center_y - 3.80f, 0.10f},
        (vec3){4.20f, 0.84f, 0.20f},
        ritual_texture,
        0.84f, 0.56f, 0.16f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y, 0.14f},
        (vec3){3.50f, 1.40f, 0.28f},
        ritual_texture,
        0.94f, 0.46f, 0.10f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-3.00f, room_center_y - 0.60f, 0.78f},
        (vec3){0.90f, 3.50f, 1.55f},
        detail_texture,
        0.56f, 0.30f, 0.10f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){2.90f, room_center_y + 1.15f, 0.55f},
        (vec3){1.40f, 1.10f, 1.10f},
        detail_texture,
        0.68f, 0.38f, 0.12f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-0.70f, room_center_y + 2.70f, 1.10f},
        (vec3){0.44f, 0.44f, 2.20f},
        detail_texture,
        room_definition->accent_tint.x,
        room_definition->accent_tint.y,
        room_definition->accent_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){1.55f, room_center_y - 2.55f, 1.10f},
        (vec3){0.44f, 0.44f, 2.20f},
        detail_texture,
        room_definition->accent_tint.x,
        room_definition->accent_tint.y,
        room_definition->accent_tint.z,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y + 3.95f, room_z - 0.22f},
        (vec3){4.70f, 0.24f, 0.18f},
        detail_texture,
        0.52f, 0.26f, 0.12f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y - 1.10f, room_z - 0.26f},
        (vec3){9.20f, 0.22f, 0.18f},
        detail_texture,
        0.50f, 0.22f, 0.10f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y + 1.10f, room_z - 0.26f},
        (vec3){9.20f, 0.22f, 0.18f},
        detail_texture,
        0.50f, 0.22f, 0.10f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
}

static void draw_archive_room_features(const RoomDefinition* room_definition, float room_center_y, float room_z, GLuint pedestal_texture, GLuint detail_texture)
{
    (void)room_definition;

    draw_textured_box(
        (vec3){-2.45f, room_center_y - 0.35f, 0.92f},
        (vec3){0.90f, 6.20f, 1.85f},
        detail_texture,
        0.44f, 0.30f, 0.16f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.20f, room_center_y + 1.10f, 0.90f},
        (vec3){0.80f, 5.10f, 1.80f},
        detail_texture,
        0.42f, 0.28f, 0.16f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){2.55f, room_center_y - 0.80f, 0.90f},
        (vec3){0.80f, 5.80f, 1.80f},
        detail_texture,
        0.42f, 0.28f, 0.16f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y + 3.60f, 0.16f},
        (vec3){3.20f, 0.80f, 0.32f},
        pedestal_texture,
        0.70f, 0.66f, 0.54f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y - 3.40f, 0.10f},
        (vec3){3.80f, 0.55f, 0.20f},
        pedestal_texture,
        0.78f, 0.72f, 0.58f,
        CHAMBER_PEDESTAL_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){-1.05f, room_center_y - 2.75f, 0.68f},
        (vec3){0.70f, 0.70f, 1.35f},
        detail_texture,
        0.52f, 0.40f, 0.22f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){1.30f, room_center_y + 2.65f, 0.68f},
        (vec3){0.70f, 0.70f, 1.35f},
        detail_texture,
        0.52f, 0.40f, 0.22f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y - 2.70f, room_z - 0.24f},
        (vec3){9.30f, 0.18f, 0.18f},
        detail_texture,
        0.54f, 0.38f, 0.20f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y - 0.25f, room_z - 0.24f},
        (vec3){9.30f, 0.18f, 0.18f},
        detail_texture,
        0.54f, 0.38f, 0.20f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
    draw_textured_box(
        (vec3){0.0f, room_center_y + 2.20f, room_z - 0.24f},
        (vec3){9.30f, 0.18f, 0.18f},
        detail_texture,
        0.54f, 0.38f, 0.20f,
        CHAMBER_DOOR_TEXTURE_WORLD_SIZE,
        false);
}

static void draw_room_enemy(const Scene* scene, int room_index)
{
    if (room_index < 0 || room_index >= SCENE_ROOM_COUNT || !scene->enemy_alive[room_index]) {
        return;
    }

    const vec3 enemy_position = scene->enemy_position[room_index];
    const float bob_offset = sinf(scene->elapsed * 2.6f) * 0.12f;
    const float enemy_center_z = enemy_position.z + bob_offset;

    if (scene->enemy_texture != 0) {
        draw_textured_box(
            (vec3){enemy_position.x, enemy_position.y, enemy_center_z},
            (vec3){ENEMY_DRAW_SIZE, ENEMY_DRAW_SIZE, ENEMY_DRAW_SIZE},
            scene->enemy_texture,
            0.92f, 0.54f, 0.58f,
            ENEMY_DRAW_SIZE * 0.75f,
            false);
    }
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        draw_box(
            (vec3){enemy_position.x, enemy_position.y, enemy_center_z},
            (vec3){ENEMY_DRAW_SIZE, ENEMY_DRAW_SIZE, ENEMY_DRAW_SIZE},
            0.92f, 0.20f, 0.16f);
        glEnable(GL_TEXTURE_2D);
        if (SCENE_USE_LIGHTING) {
            glEnable(GL_LIGHTING);
        }
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    draw_box(
        (vec3){enemy_position.x, enemy_position.y + ENEMY_DRAW_SIZE * 0.14f, enemy_center_z + 0.10f},
        (vec3){ENEMY_DRAW_SIZE * 0.18f, ENEMY_DRAW_SIZE * 0.12f, ENEMY_DRAW_SIZE * 0.08f},
        0.06f, 0.02f, 0.02f);
    draw_box(
        (vec3){enemy_position.x, enemy_position.y - ENEMY_DRAW_SIZE * 0.14f, enemy_center_z + 0.10f},
        (vec3){ENEMY_DRAW_SIZE * 0.18f, ENEMY_DRAW_SIZE * 0.12f, ENEMY_DRAW_SIZE * 0.08f},
        0.06f, 0.02f, 0.02f);

    glEnable(GL_TEXTURE_2D);
    if (SCENE_USE_LIGHTING) {
        glEnable(GL_LIGHTING);
    }
}

static void draw_enemy_health_bar_overlay(const Scene* scene, int room_index)
{
    const vec3 enemy_position = scene->enemy_position[room_index];
    const float enemy_center_z = enemy_position.z + sinf(scene->elapsed * 2.6f) * 0.12f;
    float screen_x;
    float screen_y;
    float depth;
    GLint viewport[4];
    GLboolean depth_test_enabled;
    const int segment_count = ENEMY_MAX_HEALTH;
    const int segment_gap = 3;
    int bar_width;
    int segment_width;
    int bar_height;
    int panel_x;
    int panel_y;
    float scene_depth = 1.0f;
    GLint sample_x;
    GLint sample_y;

    if (room_index < 0 || room_index >= SCENE_ROOM_COUNT || !scene->enemy_alive[room_index]) {
        return;
    }

    if (!project_world_to_viewport((vec3){enemy_position.x, enemy_position.y, enemy_center_z + ENEMY_DRAW_SIZE * 1.18f + 0.20f}, &screen_x, &screen_y, &depth)) {
        return;
    }

    glGetIntegerv(GL_VIEWPORT, viewport);
    depth_test_enabled = glIsEnabled(GL_DEPTH_TEST);

    sample_x = (GLint)clampf(screen_x, 0.0f, (float)(viewport[2] - 1));
    sample_y = viewport[3] - 1 - (GLint)clampf(screen_y, 0.0f, (float)(viewport[3] - 1));
    glReadPixels(sample_x, sample_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &scene_depth);

    if (depth > scene_depth + 0.0025f) {
        return;
    }

    bar_width = 74;
    bar_height = 10;
    segment_width = (bar_width - segment_gap * (segment_count - 1)) / segment_count;
    panel_x = (int)(screen_x - (float)bar_width * 0.5f) - 6;
    panel_y = (int)(screen_y - 24.0f) - 6;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, viewport[2], viewport[3], 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glColor4f(0.05f, 0.02f, 0.03f, 0.92f);
    glBegin(GL_QUADS);
    glVertex2i(panel_x, panel_y);
    glVertex2i(panel_x + bar_width + 12, panel_y);
    glVertex2i(panel_x + bar_width + 12, panel_y + bar_height + 12);
    glVertex2i(panel_x, panel_y + bar_height + 12);
    glEnd();

    for (int i = 0; i < segment_count; ++i) {
        const int segment_x = panel_x + 6 + i * (segment_width + segment_gap);
        const bool active_segment = i < scene->enemy_health[room_index];

        if (active_segment) {
            glColor4f(0.92f, 0.20f, 0.14f, 1.0f);
        }
        else {
            glColor4f(0.20f, 0.06f, 0.08f, 1.0f);
        }

        glBegin(GL_QUADS);
        glVertex2i(segment_x, panel_y + 6);
        glVertex2i(segment_x + segment_width, panel_y + 6);
        glVertex2i(segment_x + segment_width, panel_y + 6 + bar_height);
        glVertex2i(segment_x, panel_y + 6 + bar_height);
        glEnd();
    }

    glColor4f(0.98f, 0.92f, 0.84f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(panel_x, panel_y);
    glVertex2i(panel_x + bar_width + 12, panel_y);
    glVertex2i(panel_x + bar_width + 12, panel_y + bar_height + 12);
    glVertex2i(panel_x, panel_y + bar_height + 12);
    glEnd();

    if (depth_test_enabled) {
        glEnable(GL_DEPTH_TEST);
    }
    glEnable(GL_TEXTURE_2D);
    if (SCENE_USE_LIGHTING) {
        glEnable(GL_LIGHTING);
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}

static bool project_world_to_viewport(vec3 world_position, float* screen_x, float* screen_y, float* depth)
{
    GLdouble modelview[16];
    GLdouble projection[16];
    GLint viewport[4];
    const GLdouble x = (GLdouble)world_position.x;
    const GLdouble y = (GLdouble)world_position.y;
    const GLdouble z = (GLdouble)world_position.z;
    GLdouble eye[4];
    GLdouble clip[4];
    GLdouble ndc_x;
    GLdouble ndc_y;
    GLdouble ndc_z;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    eye[0] = modelview[0] * x + modelview[4] * y + modelview[8] * z + modelview[12];
    eye[1] = modelview[1] * x + modelview[5] * y + modelview[9] * z + modelview[13];
    eye[2] = modelview[2] * x + modelview[6] * y + modelview[10] * z + modelview[14];
    eye[3] = modelview[3] * x + modelview[7] * y + modelview[11] * z + modelview[15];

    clip[0] = projection[0] * eye[0] + projection[4] * eye[1] + projection[8] * eye[2] + projection[12] * eye[3];
    clip[1] = projection[1] * eye[0] + projection[5] * eye[1] + projection[9] * eye[2] + projection[13] * eye[3];
    clip[2] = projection[2] * eye[0] + projection[6] * eye[1] + projection[10] * eye[2] + projection[14] * eye[3];
    clip[3] = projection[3] * eye[0] + projection[7] * eye[1] + projection[11] * eye[2] + projection[15] * eye[3];

    if (clip[3] <= 0.0001) {
        return false;
    }

    ndc_x = clip[0] / clip[3];
    ndc_y = clip[1] / clip[3];
    ndc_z = clip[2] / clip[3];

    if (fabs(ndc_x) > 1.2 || fabs(ndc_y) > 1.2 || ndc_z < -1.0 || ndc_z > 1.0) {
        return false;
    }

    *screen_x = (float)(viewport[0] + (ndc_x + 1.0) * 0.5 * viewport[2]);
    *screen_y = (float)(viewport[3] - ((ndc_y + 1.0) * 0.5 * viewport[3]));
    *depth = (float)((ndc_z + 1.0) * 0.5);

    return true;
}

static void clear_projectiles(Scene* scene)
{
    for (int i = 0; i < SCENE_MAX_PROJECTILES; ++i) {
        scene->projectiles[i].active = false;
        scene->projectiles[i].hostile = false;
        scene->projectiles[i].room_index = 0;
        scene->projectiles[i].position = (vec3){0.0f, 0.0f, 0.0f};
        scene->projectiles[i].velocity = (vec3){0.0f, 0.0f, 0.0f};
        scene->projectiles[i].lifetime = 0.0f;
    }
}

static int find_projectile_slot(const Scene* scene)
{
    int best_index = 0;
    float shortest_lifetime = scene->projectiles[0].lifetime;

    for (int i = 0; i < SCENE_MAX_PROJECTILES; ++i) {
        if (!scene->projectiles[i].active) {
            return i;
        }

        if (scene->projectiles[i].lifetime < shortest_lifetime) {
            shortest_lifetime = scene->projectiles[i].lifetime;
            best_index = i;
        }
    }

    return best_index;
}

static bool point_hits_obstacle(vec3 position, float radius, SceneObstacle obstacle)
{
    if (position.z > obstacle.height + radius) {
        return false;
    }

    return fabsf(position.x - obstacle.center_x) <= (obstacle.half_width + radius)
        && fabsf(position.y - obstacle.center_y) <= (obstacle.half_depth + radius);
}

static bool projectile_hits_obstacle(int room_index, vec3 position, float radius)
{
    const RoomDefinition* room_definition = get_room_definition(room_index);

    for (int i = 0; i < room_definition->obstacle_count; ++i) {
        if (point_hits_obstacle(position, radius, get_room_world_obstacle(room_index, i))) {
            return true;
        }
    }

    return false;
}

static void damage_player(Scene* scene, int damage)
{
    if (damage <= 0 || scene->player_health <= 0 || scene->player_hit_cooldown > 0.0f) {
        return;
    }

    scene->player_health -= damage;
    if (scene->player_health < 0) {
        scene->player_health = 0;
    }

    scene->player_hit_cooldown = PLAYER_DAMAGE_COOLDOWN;
}

static void spawn_enemy_projectile(Scene* scene, int room_index)
{
    const int projectile_index = find_projectile_slot(scene);
    SceneProjectile* projectile = &scene->projectiles[projectile_index];
    const vec3 enemy_position = scene->enemy_position[room_index];
    const vec3 player_position = scene->objects[1].position;
    vec3 direction = {
        player_position.x - enemy_position.x,
        player_position.y - enemy_position.y,
        0.0f
    };
    const float direction_length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    if (direction_length < 0.001f) {
        direction = (vec3){0.0f, -1.0f, 0.0f};
    }
    else {
        direction.x /= direction_length;
        direction.y /= direction_length;
    }

    projectile->active = true;
    projectile->hostile = true;
    projectile->room_index = room_index;
    projectile->position = (vec3){
        enemy_position.x + direction.x * 1.35f,
        enemy_position.y + direction.y * 1.35f,
        enemy_position.z
    };
    projectile->velocity = (vec3){
        direction.x * ENEMY_PROJECTILE_SPEED,
        direction.y * ENEMY_PROJECTILE_SPEED,
        0.0f
    };
    projectile->lifetime = PROJECTILE_LIFETIME;
}

static void draw_projectiles(const Scene* scene)
{
    bool drew_any = false;

    for (int i = 0; i < SCENE_MAX_PROJECTILES; ++i) {
        const SceneProjectile* projectile = &scene->projectiles[i];

        if (!projectile->active || projectile->room_index != scene->current_room) {
            continue;
        }

        if (!drew_any) {
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            drew_any = true;
        }

        draw_sphere(
            projectile->position,
            PROJECTILE_RADIUS,
            12,
            8,
            projectile->hostile ? 1.0f : 1.0f,
            projectile->hostile ? 0.32f : 0.94f,
            projectile->hostile ? 0.24f : 0.42f);
    }

    if (drew_any) {
        glEnable(GL_TEXTURE_2D);
        if (SCENE_USE_LIGHTING) {
            glEnable(GL_LIGHTING);
        }
    }
}

static void draw_sphere(vec3 center, float radius, int slices, int stacks, float r, float g, float b)
{
    const float pi = 3.14159265358979323846f;

    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);

    for (int stack = 0; stack < stacks; ++stack) {
        const float phi0 = pi * ((float)stack / (float)stacks - 0.5f);
        const float phi1 = pi * ((float)(stack + 1) / (float)stacks - 0.5f);
        const float z0 = sinf(phi0);
        const float zr0 = cosf(phi0);
        const float z1 = sinf(phi1);
        const float zr1 = cosf(phi1);

        glBegin(GL_TRIANGLE_STRIP);
        for (int slice = 0; slice <= slices; ++slice) {
            const float theta = 2.0f * pi * (float)slice / (float)slices;
            const float x = cosf(theta);
            const float y = sinf(theta);

            glVertex3f(x * zr0 * radius, y * zr0 * radius, z0 * radius);
            glVertex3f(x * zr1 * radius, y * zr1 * radius, z1 * radius);
        }
        glEnd();
    }

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
    if (SCENE_USE_LIGHTING) {
        glEnable(GL_LIGHTING);
    }
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
    object->unlit = false;

    return true;
}
