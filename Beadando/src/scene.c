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
#define SECOND_ROOM_CENTER_Y (SCENE_ROOM_HALF_DEPTH * 2.0f)
#define WORLD_MIN_Y (-SCENE_ROOM_HALF_DEPTH)
#define WORLD_MAX_Y (SECOND_ROOM_CENTER_Y + SCENE_ROOM_HALF_DEPTH)
#define CONNECTOR_OPEN_HALF_WIDTH (CHAMBER_DOOR_HALF_WIDTH + CHAMBER_DOOR_FRAME_WIDTH - CHAMBER_DOOR_FRAME_OVERLAP)
#define CONNECTOR_SIDE_HALF_WIDTH ((SCENE_ROOM_HALF_WIDTH - CONNECTOR_OPEN_HALF_WIDTH) * 0.5f)
#define CONNECTOR_SIDE_CENTER_X (CONNECTOR_OPEN_HALF_WIDTH + CONNECTOR_SIDE_HALF_WIDTH)
#define DOOR_USE_DISTANCE 0.95f
#define ROOM_ENTRY_OFFSET 1.25f
#define ENEMY_DRAW_SIZE 0.78f
#define ENEMY_CENTER_HEIGHT 0.90f
#define PROJECTILE_DRAW_SIZE 0.20f
#define PROJECTILE_RADIUS (PROJECTILE_DRAW_SIZE * 0.5f)
#define PROJECTILE_SPEED 9.0f
#define ENEMY_PROJECTILE_SPEED 6.5f
#define PROJECTILE_LIFETIME 1.2f
#define PROJECTILE_HIT_DISTANCE 0.62f
#define ENEMY_FIRE_INTERVAL 1.15f
#define SCENE_USE_LIGHTING 1
#define SCENE_SHOW_LIGHT_MARKER 0
#define PLAYER_COLLISION_RADIUS 0.42f
#define PLAYER_ROOM_MARGIN 0.46f

static const SceneObstacle chamber_obstacles[] = {
    {0.0f, 0.4f, 1.0f, 1.0f},
    {-2.8f, 2.2f, 0.7f, 0.5f},
    {2.8f, 2.2f, 0.7f, 0.5f},
    {-SCENE_ROOM_HALF_WIDTH + CHAMBER_PILLAR_DEPTH * 0.5f, SCENE_ROOM_HALF_DEPTH - CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f},
    {SCENE_ROOM_HALF_WIDTH - CHAMBER_PILLAR_DEPTH * 0.5f, SCENE_ROOM_HALF_DEPTH - CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f},
    {-SCENE_ROOM_HALF_WIDTH + CHAMBER_PILLAR_DEPTH * 0.5f, -SCENE_ROOM_HALF_DEPTH + CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f},
    {SCENE_ROOM_HALF_WIDTH - CHAMBER_PILLAR_DEPTH * 0.5f, -SCENE_ROOM_HALF_DEPTH + CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f},
    {0.0f, SECOND_ROOM_CENTER_Y + 0.4f, 1.2f, 1.2f},
    {-SCENE_ROOM_HALF_WIDTH + CHAMBER_PILLAR_DEPTH * 0.5f, SECOND_ROOM_CENTER_Y + SCENE_ROOM_HALF_DEPTH - CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f},
    {SCENE_ROOM_HALF_WIDTH - CHAMBER_PILLAR_DEPTH * 0.5f, SECOND_ROOM_CENTER_Y + SCENE_ROOM_HALF_DEPTH - CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f},
    {-SCENE_ROOM_HALF_WIDTH + CHAMBER_PILLAR_DEPTH * 0.5f, SECOND_ROOM_CENTER_Y - SCENE_ROOM_HALF_DEPTH + CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f},
    {SCENE_ROOM_HALF_WIDTH - CHAMBER_PILLAR_DEPTH * 0.5f, SECOND_ROOM_CENTER_Y - SCENE_ROOM_HALF_DEPTH + CHAMBER_PILLAR_WIDTH * 0.5f, CHAMBER_PILLAR_DEPTH * 0.5f, CHAMBER_PILLAR_WIDTH * 0.5f},
    {-CONNECTOR_SIDE_CENTER_X, SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f},
    {CONNECTOR_SIDE_CENTER_X, SCENE_ROOM_HALF_DEPTH, CONNECTOR_SIDE_HALF_WIDTH, CHAMBER_DOOR_FRAME_DEPTH * 0.5f}
};

static const vec3 player_spawn_position = {0.0f, -SCENE_ROOM_HALF_DEPTH + 1.25f, 0.0f};

static float get_room_center_y(int room_index);
static vec3 get_room_light_anchor(int room_index);
static int get_room_index_from_y(float y);
static vec3 clamp_room_position(vec3 position, int room_index, float margin, float min_z, float max_z);
static vec3 resolve_box_collision(vec3 previous, vec3 desired, float radius, SceneObstacle obstacle);
static vec3 resolve_chamber_obstacles(vec3 previous, vec3 desired, float radius);
static void draw_chamber(const Scene* scene);
static void draw_room(const Scene* scene, float room_center_y, bool open_south, bool open_north, bool draw_south_door, bool draw_north_door);
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
static void draw_room_enemy(const Scene* scene, int room_index);
static void draw_projectiles(const Scene* scene);
static void clear_projectiles(Scene* scene);
static int find_projectile_slot(const Scene* scene);
static bool point_hits_obstacle(vec3 position, float radius, SceneObstacle obstacle);
static bool projectile_hits_obstacle(vec3 position, float radius);
static void spawn_enemy_projectile(Scene* scene, int room_index);
static void draw_sphere(vec3 center, float radius, int slices, int stacks, float r, float g, float b);
static void draw_light_marker(const Scene* scene);
static void apply_light(const Scene* scene);
static bool load_object(SceneObject* object, const char* model_path, const char* texture_path, vec3 pos, float scale);

void init_scene(Scene* scene)
{
    scene->object_count = 0;
    scene->selected_object = -1;
    scene->current_room = 0;
    scene->chamber_floor_texture = 0;
    scene->chamber_wall_texture = 0;
    scene->pedestal_texture = 0;
    scene->door_texture = 0;
    scene->elapsed = 0.0f;

    scene->light_position = get_room_light_anchor(0);
    scene->light_intensity = 1.1f;

    for (int room_index = 0; room_index < SCENE_ROOM_COUNT; ++room_index) {
        scene->room_cleared[room_index] = true;
        scene->enemy_alive[room_index] = false;
        scene->enemy_position[room_index] = (vec3){0.0f, get_room_center_y(room_index), 0.0f};
        scene->enemy_shot_cooldown[room_index] = ENEMY_FIRE_INTERVAL;
    }

    scene->room_cleared[1] = false;
    scene->enemy_alive[1] = true;
    scene->enemy_position[1] = (vec3){0.0f, SECOND_ROOM_CENTER_Y + 0.4f, ENEMY_CENTER_HEIGHT};
    scene->enemy_shot_cooldown[1] = 0.75f;

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

    if (scene->enemy_alive[scene->current_room] && scene->object_count > 1) {
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

            if (hit_distance <= PROJECTILE_HIT_DISTANCE) {
                projectile->active = false;
                scene->enemy_alive[projectile->room_index] = false;
                scene->room_cleared[projectile->room_index] = true;
                scene->enemy_shot_cooldown[projectile->room_index] = ENEMY_FIRE_INTERVAL;
                continue;
            }
        }

        if (projectile->hostile && projectile->room_index == scene->current_room && scene->object_count > 1) {
            const vec3 player_position = scene->objects[1].position;
            const float hit_distance = sqrtf(
                (projectile->position.x - player_position.x) * (projectile->position.x - player_position.x) +
                (projectile->position.y - player_position.y) * (projectile->position.y - player_position.y));

            if (hit_distance <= PROJECTILE_HIT_DISTANCE) {
                projectile->active = false;
                continue;
            }
        }

        if (projectile_hits_obstacle(projectile->position, PROJECTILE_RADIUS)) {
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

    if (scene->current_room == 0 && distance_to_north <= DOOR_USE_DISTANCE) {
        scene->current_room = 1;
        player->position = (vec3){0.0f, get_room_center_y(1) - SCENE_ROOM_HALF_DEPTH + ROOM_ENTRY_OFFSET, 0.0f};
        scene->light_position = get_room_light_anchor(1);
        clear_projectiles(scene);
        return true;
    }

    if (scene->current_room == 1 && distance_to_south <= DOOR_USE_DISTANCE) {
        scene->current_room = 0;
        player->position = (vec3){0.0f, get_room_center_y(0) + SCENE_ROOM_HALF_DEPTH - ROOM_ENTRY_OFFSET, 0.0f};
        scene->light_position = get_room_light_anchor(0);
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

    resolved = resolve_chamber_obstacles(previous_position, resolved, PLAYER_COLLISION_RADIUS);
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

static float get_room_center_y(int room_index)
{
    return (room_index == 0) ? 0.0f : SECOND_ROOM_CENTER_Y;
}

static vec3 get_room_light_anchor(int room_index)
{
    return (vec3){0.0f, get_room_center_y(room_index), SCENE_ROOM_HEIGHT - 0.65f};
}

static int get_room_index_from_y(float y)
{
    return (y > SECOND_ROOM_CENTER_Y * 0.5f) ? 1 : 0;
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

static vec3 resolve_chamber_obstacles(vec3 previous, vec3 desired, float radius)
{
    const int obstacle_count = (int)(sizeof(chamber_obstacles) / sizeof(chamber_obstacles[0]));

    for (int i = 0; i < obstacle_count; ++i) {
        desired = resolve_box_collision(previous, desired, radius, chamber_obstacles[i]);
    }

    return desired;
}

static void draw_chamber(const Scene* scene)
{
    draw_room(scene, get_room_center_y(scene->current_room), false, false, true, true);
}

static void draw_room(const Scene* scene, float room_center_y, bool open_south, bool open_north, bool draw_south_door, bool draw_north_door)
{
    const bool second_room = room_center_y > (SCENE_ROOM_HALF_DEPTH * 0.5f);
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
    const float floor_r = second_room ? 0.78f : 0.92f;
    const float floor_g = second_room ? 0.83f : 0.88f;
    const float floor_b = second_room ? 0.90f : 0.82f;
    const float wall_r = second_room ? 0.78f : 0.88f;
    const float wall_g = second_room ? 0.82f : 0.84f;
    const float wall_b = second_room ? 0.88f : 0.80f;

    if (scene->chamber_floor_texture != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, scene->chamber_floor_texture);
        glColor3f(floor_r, floor_g, floor_b);
    }
    else {
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.20f, 0.21f, 0.24f);
    }

    draw_textured_quad_xy(0.0f, -room_x, room_x, room_min_y, room_max_y, 1.0f, floor_uv_x, floor_uv_y);

    if (scene->chamber_wall_texture != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, scene->chamber_wall_texture);
        glColor3f(wall_r, wall_g, wall_b);
    }
    else {
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.11f, 0.12f, 0.15f);
    }

    draw_textured_quad_xy(room_z, -room_x, room_x, room_min_y, room_max_y, -1.0f, 4.0f, 4.0f);

    if (open_north) {
        draw_textured_quad_xz(room_max_y, -room_x, -CONNECTOR_OPEN_HALF_WIDTH, 0.0f, room_z, -1.0f, connector_side_width * wall_u_per_world, 2.0f);
        draw_textured_quad_xz(room_max_y, CONNECTOR_OPEN_HALF_WIDTH, room_x, 0.0f, room_z, -1.0f, connector_side_width * wall_u_per_world, 2.0f);
        draw_textured_quad_xz(room_max_y, -CONNECTOR_OPEN_HALF_WIDTH, CONNECTOR_OPEN_HALF_WIDTH, CHAMBER_DOOR_LEAF_HEIGHT, room_z, -1.0f, CONNECTOR_OPEN_HALF_WIDTH * 2.0f * wall_u_per_world, connector_header_height * wall_v_per_world);
    }
    else {
        draw_textured_quad_xz(room_max_y, -room_x, room_x, 0.0f, room_z, -1.0f, 4.0f, 2.0f);
    }

    draw_textured_quad_yz(-room_x, room_min_y, room_max_y, 0.0f, room_z, 1.0f, 4.0f, 2.0f);
    draw_textured_quad_yz(room_x, room_min_y, room_max_y, 0.0f, room_z, -1.0f, 4.0f, 2.0f);

    if (open_south) {
        draw_textured_quad_xz(room_min_y, -room_x, -CONNECTOR_OPEN_HALF_WIDTH, 0.0f, room_z, 1.0f, connector_side_width * wall_u_per_world, 2.0f);
        draw_textured_quad_xz(room_min_y, CONNECTOR_OPEN_HALF_WIDTH, room_x, 0.0f, room_z, 1.0f, connector_side_width * wall_u_per_world, 2.0f);
        draw_textured_quad_xz(room_min_y, -CONNECTOR_OPEN_HALF_WIDTH, CONNECTOR_OPEN_HALF_WIDTH, CHAMBER_DOOR_LEAF_HEIGHT, room_z, 1.0f, CONNECTOR_OPEN_HALF_WIDTH * 2.0f * wall_u_per_world, connector_header_height * wall_v_per_world);
    }
    else {
        draw_textured_quad_xz(room_min_y, -room_x, room_x, 0.0f, room_z, 1.0f, 4.0f, 2.0f);
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

    draw_door_assembly((vec3){room_x - CHAMBER_DOOR_FRAME_DEPTH * 0.5f, room_center_y, 0.0f}, 90.0f, door_texture);
    draw_door_assembly((vec3){-room_x + CHAMBER_DOOR_FRAME_DEPTH * 0.5f, room_center_y, 0.0f}, -90.0f, door_texture);

    if (second_room) {
        draw_pedestal((vec3){0.0f, room_center_y + 0.4f, 0.0f}, 2.4f, 2.4f, 0.35f, pedestal_texture, 0.74f, 0.82f, 0.94f);

        draw_box(
            (vec3){0.0f, room_center_y - 1.2f, 0.14f},
            (vec3){4.2f, 1.2f, 0.28f},
            0.18f, 0.24f, 0.34f);
        draw_box(
            (vec3){-3.7f, room_center_y - 1.4f, 1.05f},
            (vec3){0.55f, 0.55f, 2.1f},
            0.20f, 0.28f, 0.42f);
        draw_box(
            (vec3){3.7f, room_center_y - 1.4f, 1.05f},
            (vec3){0.55f, 0.55f, 2.1f},
            0.20f, 0.28f, 0.42f);
        draw_box(
            (vec3){-1.8f, room_center_y + 3.2f, 0.95f},
            (vec3){0.42f, 0.42f, 1.9f},
            0.24f, 0.34f, 0.50f);
        draw_box(
            (vec3){1.8f, room_center_y + 3.2f, 0.95f},
            (vec3){0.42f, 0.42f, 1.9f},
            0.24f, 0.34f, 0.50f);
        draw_box(
            (vec3){0.0f, room_center_y, room_z - 0.18f},
            (vec3){4.8f, 0.26f, 0.18f},
            0.22f, 0.30f, 0.44f);
        draw_box(
            (vec3){0.0f, room_center_y + 2.7f, room_z - 0.18f},
            (vec3){4.8f, 0.26f, 0.18f},
            0.22f, 0.30f, 0.44f);
    }
    else {
        draw_pedestal((vec3){0.0f, room_center_y + 0.4f, 0.0f}, 2.0f, 2.0f, 0.25f, pedestal_texture, 0.92f, 0.96f, 1.0f);
        draw_pedestal((vec3){-2.8f, room_center_y + 2.2f, 0.0f}, 1.4f, 1.0f, 0.35f, pedestal_texture, 0.74f, 0.80f, 0.90f);
        draw_pedestal((vec3){2.8f, room_center_y + 2.2f, 0.0f}, 1.4f, 1.0f, 0.35f, pedestal_texture, 0.74f, 0.80f, 0.90f);
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

static void draw_room_enemy(const Scene* scene, int room_index)
{
    if (room_index < 0 || room_index >= SCENE_ROOM_COUNT || !scene->enemy_alive[room_index]) {
        return;
    }

    const vec3 enemy_position = scene->enemy_position[room_index];
    const float bob_offset = sinf(scene->elapsed * 2.6f) * 0.12f;
    const float enemy_center_z = enemy_position.z + bob_offset;

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    draw_box(
        (vec3){enemy_position.x, enemy_position.y, enemy_center_z},
        (vec3){ENEMY_DRAW_SIZE, ENEMY_DRAW_SIZE, ENEMY_DRAW_SIZE},
        0.92f, 0.20f, 0.16f);
    draw_box(
        (vec3){enemy_position.x, enemy_position.y, enemy_center_z + 0.12f},
        (vec3){ENEMY_DRAW_SIZE * 0.42f, ENEMY_DRAW_SIZE * 0.42f, ENEMY_DRAW_SIZE * 0.42f},
        1.0f, 0.84f, 0.20f);

    glEnable(GL_TEXTURE_2D);
    if (SCENE_USE_LIGHTING) {
        glEnable(GL_LIGHTING);
    }
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
    return fabsf(position.x - obstacle.center_x) <= (obstacle.half_width + radius)
        && fabsf(position.y - obstacle.center_y) <= (obstacle.half_depth + radius);
}

static bool projectile_hits_obstacle(vec3 position, float radius)
{
    const int obstacle_count = (int)(sizeof(chamber_obstacles) / sizeof(chamber_obstacles[0]));

    for (int i = 0; i < obstacle_count; ++i) {
        if (point_hits_obstacle(position, radius, chamber_obstacles[i])) {
            return true;
        }
    }

    return false;
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
