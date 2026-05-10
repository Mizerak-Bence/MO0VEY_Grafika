#include "app.h"

#include "ui.h"

#include <SDL2/SDL_image.h>

#if defined(_WIN32)
#include <direct.h>
#define CHDIR _chdir
#else
#include <unistd.h>
#define CHDIR chdir
#endif

#include <stdio.h>

#include <math.h>

static void handle_keydown(App* app, const SDL_KeyboardEvent* key);
static void handle_keyup(App* app, const SDL_KeyboardEvent* key);
static void handle_mouse_motion(App* app, const SDL_MouseMotionEvent* motion);

static void set_mouse_capture(App* app, bool enabled);
static void try_fix_working_directory(void);
static void set_perspective_projection(double fovy_deg, double aspect, double near_plane, double far_plane);
static void update_player(App* app, double dt);
static void update_player_camera(App* app);

void init_app(App* app, int width, int height)
{
    int error_code;

    app->is_running = false;
    app->is_paused = false;
    app->window = NULL;
    app->gl_context = NULL;
    app->window_width = width;
    app->window_height = height;
    app->show_help = true;

    app->player_speed = (vec3){0.0f, 0.0f, 0.0f};
    app->player_move_speed = 2.5f;

    app->move_forward = false;
    app->move_back = false;
    app->move_left = false;
    app->move_right = false;

    app->camera_follow_distance = 0.0f;
    app->camera_follow_height = 1.45f;
    app->camera_follow_smoothness = 14.0f;

    error_code = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    try_fix_working_directory();

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    app->window = SDL_CreateWindow(
        "MO0VEY - Calibration Chamber",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window: %s\n", SDL_GetError());
        return;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context: %s\n", SDL_GetError());
        return;
    }

    set_mouse_capture(app, true);

    SDL_GL_SetSwapInterval(1);

    init_opengl();
    reshape(width, height);

    init_camera(&app->camera);
    init_scene(&app->scene);

    update_player_camera(app);

    app->uptime = (double)SDL_GetTicks() / 1000.0;
    app->is_running = true;
}

static bool file_exists(const char* path)
{
    FILE* f = fopen(path, "rb");
    if (f == NULL) {
        return false;
    }
    fclose(f);
    return true;
}

static void try_fix_working_directory(void)
{
    // If launched from the build/ directory (e.g. double-clicking build/beadando.exe),
    // the current working directory won't contain assets/. In that case, step up.
    if (file_exists("assets/README.md")) {
        return;
    }
    if (file_exists("../assets/README.md")) {
        (void)CHDIR("..");
        return;
    }
}

void init_opengl(void)
{
    glShadeModel(GL_SMOOTH);

    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_FOG);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    if (height <= 0) {
        height = 1;
    }

    ratio = (double)width / (double)height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    set_perspective_projection(60.0, (double)w / (double)h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

static void set_perspective_projection(double fovy_deg, double aspect, double near_plane, double far_plane)
{
    const double top = tan(degree_to_radian(fovy_deg) * 0.5) * near_plane;
    const double right = top * aspect;

    glFrustum(-right, right, -top, top, near_plane, far_plane);
}

void handle_app_events(App* app)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            handle_keydown(app, &event.key);
            break;
        case SDL_KEYUP:
            handle_keyup(app, &event.key);
            break;
        case SDL_MOUSEMOTION:
            handle_mouse_motion(app, &event.motion);
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                app->window_width = event.window.data1;
                app->window_height = event.window.data2;
                reshape((GLsizei)app->window_width, (GLsizei)app->window_height);
            }
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time = (double)SDL_GetTicks() / 1000.0;
    double dt = current_time - app->uptime;
    app->uptime = current_time;

    if (app->is_paused) {
        return;
    }

    update_player(app, dt);
    update_player_camera(app);
    update_scene(&app->scene, dt);
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    set_view(&app->camera);
    render_scene(&app->scene);
    glPopMatrix();

    ui_begin_overlay(app->window_width, app->window_height);
    ui_draw_pause_menu(app->window_width, app->window_height, app->is_paused);
    ui_draw_help(app->window_width, app->window_height, app->show_help);
    ui_end_overlay();

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    destroy_scene(&app->scene);

    set_mouse_capture(app, false);

    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
        app->gl_context = NULL;
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
        app->window = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}

static void handle_keydown(App* app, const SDL_KeyboardEvent* key)
{
    if (key->repeat) {
        return;
    }

    switch (key->keysym.scancode) {
    case SDL_SCANCODE_ESCAPE:
        if (app->is_paused) {
            app->is_running = false;
        }
        else {
            app->is_paused = true;
            app->move_forward = false;
            app->move_back = false;
            app->move_left = false;
            app->move_right = false;
            app->player_speed = (vec3){0.0f, 0.0f, 0.0f};
            set_mouse_capture(app, false);
        }
        break;
    case SDL_SCANCODE_RETURN:
    case SDL_SCANCODE_KP_ENTER:
        if (app->is_paused) {
            app->is_paused = false;
            set_mouse_capture(app, true);
        }
        break;
    case SDL_SCANCODE_F1:
        app->show_help = !app->show_help;
        break;
    default:
        break;
    }

    if (app->is_paused) {
        return;
    }

    switch (key->keysym.scancode) {
    // player movement
    case SDL_SCANCODE_UP:
        app->move_forward = true;
        break;
    case SDL_SCANCODE_DOWN:
        app->move_back = true;
        break;
    case SDL_SCANCODE_LEFT:
        app->move_left = true;
        break;
    case SDL_SCANCODE_RIGHT:
        app->move_right = true;
        break;
    case SDL_SCANCODE_Q:
        scene_fire_projectile(&app->scene, app->camera.rotation.z);
        break;
    case SDL_SCANCODE_E:
        if (scene_use_nearby_door(&app->scene)) {
            update_player_camera(app);
        }
        break;

    // object selection
    case SDL_SCANCODE_1:
        scene_select_object(&app->scene, 0);
        break;
    case SDL_SCANCODE_2:
        scene_select_object(&app->scene, 1);
        break;

    // object movement
    case SDL_SCANCODE_I:
        scene_move_selected(&app->scene, (vec3){0.0f, 0.15f, 0.0f});
        break;
    case SDL_SCANCODE_K:
        scene_move_selected(&app->scene, (vec3){0.0f, -0.15f, 0.0f});
        break;
    case SDL_SCANCODE_J:
        scene_move_selected(&app->scene, (vec3){-0.15f, 0.0f, 0.0f});
        break;
    case SDL_SCANCODE_L:
        scene_move_selected(&app->scene, (vec3){0.15f, 0.0f, 0.0f});
        break;
    case SDL_SCANCODE_U:
        scene_move_selected(&app->scene, (vec3){0.0f, 0.0f, 0.15f});
        break;
    case SDL_SCANCODE_O:
        scene_move_selected(&app->scene, (vec3){0.0f, 0.0f, -0.15f});
        break;

    case SDL_SCANCODE_R:
        {
            int idx = app->scene.selected_object;
            if (idx >= 0 && idx < app->scene.object_count) {
                app->scene.objects[idx].auto_rotate = !app->scene.objects[idx].auto_rotate;
            }
        }
        break;

    // light movement
    case SDL_SCANCODE_T:
        scene_move_light(&app->scene, (vec3){0.0f, 0.2f, 0.0f});
        break;
    case SDL_SCANCODE_G:
        scene_move_light(&app->scene, (vec3){0.0f, -0.2f, 0.0f});
        break;
    case SDL_SCANCODE_F:
        scene_move_light(&app->scene, (vec3){-0.2f, 0.0f, 0.0f});
        break;
    case SDL_SCANCODE_H:
        scene_move_light(&app->scene, (vec3){0.2f, 0.0f, 0.0f});
        break;
    case SDL_SCANCODE_PAGEUP:
        scene_move_light(&app->scene, (vec3){0.0f, 0.0f, 0.2f});
        break;
    case SDL_SCANCODE_PAGEDOWN:
        scene_move_light(&app->scene, (vec3){0.0f, 0.0f, -0.2f});
        break;

    // light intensity
    case SDL_SCANCODE_KP_PLUS:
    case SDL_SCANCODE_EQUALS:
        scene_adjust_light(&app->scene, 0.1f);
        break;
    case SDL_SCANCODE_KP_MINUS:
    case SDL_SCANCODE_MINUS:
        scene_adjust_light(&app->scene, -0.1f);
        break;

    default:
        break;
    }
}

static void handle_keyup(App* app, const SDL_KeyboardEvent* key)
{
    if (key->repeat) {
        return;
    }

    switch (key->keysym.scancode) {
    case SDL_SCANCODE_UP:
        app->move_forward = false;
        break;
    case SDL_SCANCODE_DOWN:
        app->move_back = false;
        break;
    case SDL_SCANCODE_LEFT:
        app->move_left = false;
        break;
    case SDL_SCANCODE_RIGHT:
        app->move_right = false;
        break;
    default:
        break;
    }
}

static void update_player(App* app, double dt)
{
    // Player is object #1 (ISAAC2) when present.
    if (app->scene.object_count <= 1) {
        return;
    }

    SceneObject* player = &app->scene.objects[1];

    float move_x = 0.0f;
    float move_y = 0.0f;
    if (app->move_right) {
        move_x += 1.0f;
    }
    if (app->move_left) {
        move_x -= 1.0f;
    }
    if (app->move_forward) {
        move_y += 1.0f;
    }
    if (app->move_back) {
        move_y -= 1.0f;
    }

    // Normalize diagonal movement so it doesn't move faster.
    const float len = sqrtf(move_x * move_x + move_y * move_y);
    if (len > 1.0f) {
        move_x /= len;
        move_y /= len;
    }

    app->player_speed.x = move_x * app->player_move_speed;
    app->player_speed.y = move_y * app->player_move_speed;

    const double yaw = degree_to_radian(app->camera.rotation.z);
    const double side_yaw = degree_to_radian(app->camera.rotation.z - 90.0);

    vec3 target_position = player->position;

    // Strafe (A/D)
    target_position.x += (float)(cos(side_yaw) * app->player_speed.x * dt);
    target_position.y += (float)(sin(side_yaw) * app->player_speed.x * dt);

    // Forward/back (W/S)
    target_position.x += (float)(cos(yaw) * app->player_speed.y * dt);
    target_position.y += (float)(sin(yaw) * app->player_speed.y * dt);

    player->position = scene_resolve_player_position(&app->scene, player->position, target_position);
}

static void update_player_camera(App* app)
{
    if (app->scene.object_count <= 0) {
        return;
    }

    const int player_index = (app->scene.object_count > 1) ? 1 : 0;
    const SceneObject* player = &app->scene.objects[player_index];

    const double yaw = degree_to_radian(app->camera.rotation.z);
    const float forward_x = (float)cos(yaw);
    const float forward_y = (float)sin(yaw);

    app->camera.position.x = player->position.x + forward_x * app->camera_follow_distance;
    app->camera.position.y = player->position.y + forward_y * app->camera_follow_distance;
    app->camera.position.z = player->position.z + app->camera_follow_height;
}

static void handle_mouse_motion(App* app, const SDL_MouseMotionEvent* motion)
{
    if (app->is_paused) {
        return;
    }

    rotate_camera(&app->camera, (double)-motion->xrel, (double)-motion->yrel);
}

static void set_mouse_capture(App* app, bool enabled)
{
    if (app->window == NULL) {
        return;
    }

    SDL_SetWindowGrab(app->window, enabled ? SDL_TRUE : SDL_FALSE);
    SDL_ShowCursor(enabled ? SDL_DISABLE : SDL_ENABLE);

    if (SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE) != 0 && enabled) {
        printf("[WARN] Unable to enable relative mouse mode: %s\n", SDL_GetError());
    }
}
