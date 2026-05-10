#ifndef APP_H
#define APP_H

#include "camera.h"
#include "scene.h"

#include <SDL2/SDL.h>

#include <GL/gl.h>

#include <stdbool.h>

#define VIEWPORT_RATIO (4.0 / 3.0)

typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;
    bool is_running;
    bool is_paused;

    int window_width;
    int window_height;

    double uptime;

    int pause_menu_selection;
    bool pause_menu_show_instructions;
    int pause_menu_instruction_scroll;

    Camera camera;
    Scene scene;

    vec3 player_speed; /* side=x, forward=y (units/sec) */
    float player_move_speed;

    bool move_forward;
    bool move_back;
    bool move_left;
    bool move_right;

    float camera_follow_distance;
    float camera_follow_height;

    float camera_follow_smoothness;
} App;

void init_app(App* app, int width, int height);
void destroy_app(App* app);

void handle_app_events(App* app);
void update_app(App* app);
void render_app(App* app);

void init_opengl(void);
void reshape(GLsizei width, GLsizei height);

#endif /* APP_H */
