#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wmissing-braces"
#endif

#include "../third_party/stb_easy_font.h"

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include "ui.h"

#include <GL/gl.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

static void ui_draw_panel(int x, int y, int width, int height, float fill_alpha);
static void ui_draw_menu_button(int x, int y, int width, int height, const char* label, bool selected);
static void ui_draw_minimap_room(int x, int y, int size, bool current_room, bool cleared_room, bool enemy_alive);
static void ui_draw_minimap_player_marker(int center_x, int center_y, int room_size, float camera_yaw_degrees);

static const char* pause_instruction_lines[] = {
    "Jatek",
    "",
    "  W/A/S/D   mozgas",
    "  Mouse     kamera forgatas Isaac fejebol",
    "  HP csik   bal felul mutatja az eleterot",
    "  Mini-map  jobb felul mutatja a szobakat",
    "  Q         lovedek kilovese",
    "  E         ajto hasznalata, ha a szoba tiszta",
    "  Halal utan a menuben ujraindithato a jatek",
    "  Pause-bol a teljes szint ujraindithato",
    "  Esc       pause menu / vissza",
    "  Enter     menu pont megerositese",
    "",
    "Harc",
    "",
    "  Tobb lovedek lehet egyszerre aktiv",
    "  A lovedek falnak vagy akadalyoknak utkozve eltunik",
    "  A masodik szobaban az enemy kozelit es tavolrol is tamad",
    "",
    "Debug",
    "",
    "  1/2       objektum kivalasztas",
    "  I/J/K/L   mozgas X/Y",
    "  U/O       mozgas Z",
    "  R         auto-forgatas",
    "  T/F/G/H   feny mozgatasa X/Y",
    "  PgUp/PgDn feny mozgatasa Z",
    "  +/-       feny erossege"
};

#define UI_PAUSE_INSTRUCTION_VISIBLE_LINES 12

void ui_begin_overlay(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
}

void ui_end_overlay(void)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}

void ui_draw_text(int x, int y, const char* text)
{
    static char buffer[99999];

    if (text == NULL || text[0] == 0) {
        return;
    }

    const unsigned char color[4] = {255, 255, 255, 255};
    int quads = stb_easy_font_print((float)x, (float)y, (char*)text, (unsigned char*)color, buffer, (int)sizeof(buffer));

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int ui_get_pause_instruction_max_scroll(void)
{
    const int line_count = (int)(sizeof(pause_instruction_lines) / sizeof(pause_instruction_lines[0]));
    const int max_scroll = line_count - UI_PAUSE_INSTRUCTION_VISIBLE_LINES;

    return (max_scroll > 0) ? max_scroll : 0;
}

void ui_draw_player_health(const Scene* scene, bool visible, int width, int height)
{
    if (!visible || scene == NULL || scene->player_max_health <= 0) {
        return;
    }

    const int panel_x = (width > 240) ? 18 : 10;
    const int panel_y = (height > 120) ? 16 : 10;
    const int panel_width = 210;
    const int panel_height = 54;
    const int bar_x = panel_x + 18;
    const int bar_y = panel_y + 26;
    const int bar_width = 172;
    const int bar_height = 14;
    const float ratio = (scene->player_health > 0)
        ? (float)scene->player_health / (float)scene->player_max_health
        : 0.0f;
    const int fill_width = (int)(ratio * (float)bar_width);
    char health_text[48];

    snprintf(health_text, sizeof(health_text), "HP %d / %d", scene->player_health, scene->player_max_health);

    ui_draw_panel(panel_x, panel_y, panel_width, panel_height, 0.72f);

    glColor4f(0.16f, 0.04f, 0.05f, 0.96f);
    glBegin(GL_QUADS);
    glVertex2i(bar_x, bar_y);
    glVertex2i(bar_x + bar_width, bar_y);
    glVertex2i(bar_x + bar_width, bar_y + bar_height);
    glVertex2i(bar_x, bar_y + bar_height);
    glEnd();

    if (fill_width > 0) {
        glColor4f((scene->player_health > 2) ? 0.84f : 0.92f, (scene->player_health > 2) ? 0.18f : 0.08f, 0.12f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2i(bar_x, bar_y);
        glVertex2i(bar_x + fill_width, bar_y);
        glVertex2i(bar_x + fill_width, bar_y + bar_height);
        glVertex2i(bar_x, bar_y + bar_height);
        glEnd();
    }

    glColor4f(0.98f, 0.92f, 0.86f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(bar_x, bar_y);
    glVertex2i(bar_x + bar_width, bar_y);
    glVertex2i(bar_x + bar_width, bar_y + bar_height);
    glVertex2i(bar_x, bar_y + bar_height);
    glEnd();

    ui_draw_text(panel_x + 18, panel_y + 8, health_text);

    if (scene->player_health <= 0) {
        ui_draw_text(panel_x + 18, panel_y + 44, "MEGHALTAL");
    }
}

static void ui_draw_minimap_room(int x, int y, int size, bool current_room, bool cleared_room, bool enemy_alive)
{
    if (current_room) {
        glColor4f(0.92f, 0.78f, 0.34f, 0.98f);
    }
    else if (cleared_room) {
        glColor4f(0.52f, 0.54f, 0.60f, 0.92f);
    }
    else {
        glColor4f(0.28f, 0.30f, 0.34f, 0.90f);
    }

    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + size, y);
    glVertex2i(x + size, y + size);
    glVertex2i(x, y + size);
    glEnd();

    if (current_room) {
        glColor4f(1.0f, 0.98f, 0.86f, 1.0f);
    }
    else {
        glColor4f(0.18f, 0.18f, 0.20f, 1.0f);
    }

    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x + size, y);
    glVertex2i(x + size, y + size);
    glVertex2i(x, y + size);
    glEnd();

    if (enemy_alive) {
        const int marker_size = 5;
        const int marker_x = x + size - marker_size - 3;
        const int marker_y = y + 3;

        glColor4f(0.80f, 0.18f, 0.16f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2i(marker_x, marker_y);
        glVertex2i(marker_x + marker_size, marker_y);
        glVertex2i(marker_x + marker_size, marker_y + marker_size);
        glVertex2i(marker_x, marker_y + marker_size);
        glEnd();
    }
}

static void ui_draw_minimap_player_marker(int center_x, int center_y, int room_size, float camera_yaw_degrees)
{
    const float yaw = degree_to_radian(camera_yaw_degrees);
    const float dir_x = cosf(yaw);
    const float dir_y = -sinf(yaw);
    const float right_x = -dir_y;
    const float right_y = dir_x;
    const float tip_distance = (float)room_size * 0.32f;
    const float base_distance = (float)room_size * 0.10f;
    const float half_width = (float)room_size * 0.14f;
    const float tip_x = (float)center_x + dir_x * tip_distance;
    const float tip_y = (float)center_y + dir_y * tip_distance;
    const float base_center_x = (float)center_x - dir_x * base_distance;
    const float base_center_y = (float)center_y - dir_y * base_distance;

    glColor4f(0.10f, 0.10f, 0.12f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(tip_x, tip_y);
    glVertex2f(base_center_x + right_x * half_width, base_center_y + right_y * half_width);
    glVertex2f(base_center_x - right_x * half_width, base_center_y - right_y * half_width);
    glEnd();
}

void ui_draw_minimap(const Scene* scene, float camera_yaw_degrees, bool visible, int width, int height)
{
    const int room_size = 18;
    const int room_gap = 8;
    const int panel_padding = 12;
    const int panel_width = room_size + panel_padding * 2;
    const int panel_height = SCENE_ROOM_COUNT * room_size + (SCENE_ROOM_COUNT - 1) * room_gap + panel_padding * 2;
    const int panel_x = width - panel_width - 18;
    const int panel_y = 18;

    (void)height;

    if (!visible || scene == NULL) {
        return;
    }

    glColor4f(0.02f, 0.02f, 0.03f, 0.78f);
    glBegin(GL_QUADS);
    glVertex2i(panel_x, panel_y);
    glVertex2i(panel_x + panel_width, panel_y);
    glVertex2i(panel_x + panel_width, panel_y + panel_height);
    glVertex2i(panel_x, panel_y + panel_height);
    glEnd();

    glColor4f(0.10f, 0.10f, 0.12f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(panel_x, panel_y);
    glVertex2i(panel_x + panel_width, panel_y);
    glVertex2i(panel_x + panel_width, panel_y + panel_height);
    glVertex2i(panel_x, panel_y + panel_height);
    glEnd();
    glLineWidth(1.0f);

    for (int room_index = 0; room_index < SCENE_ROOM_COUNT; ++room_index) {
        const int visual_index = SCENE_ROOM_COUNT - 1 - room_index;
        const int room_x = panel_x + panel_padding;
        const int room_y = panel_y + panel_padding + visual_index * (room_size + room_gap);
        const int room_center_x = room_x + room_size / 2;
        const int room_center_y = room_y + room_size / 2;

        if (room_index < SCENE_ROOM_COUNT - 1) {
            const int connector_x = room_center_x - 3;
            const int connector_y = room_y - room_gap;

            glColor4f(0.34f, 0.36f, 0.40f, 0.92f);
            glBegin(GL_QUADS);
            glVertex2i(connector_x, connector_y);
            glVertex2i(connector_x + 6, connector_y);
            glVertex2i(connector_x + 6, connector_y + room_gap);
            glVertex2i(connector_x, connector_y + room_gap);
            glEnd();
        }

        ui_draw_minimap_room(
            room_x,
            room_y,
            room_size,
            room_index == scene->current_room,
            scene->room_cleared[room_index],
            scene->enemy_alive[room_index]);

        if (room_index == scene->current_room) {
            ui_draw_minimap_player_marker(room_center_x, room_center_y, room_size, camera_yaw_degrees);
        }
    }
}

static void ui_draw_panel(int x, int y, int width, int height, float fill_alpha)
{
    glColor4f(0.02f, 0.02f, 0.03f, fill_alpha);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();

    glColor4f(0.82f, 0.82f, 0.86f, 0.95f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();
}

static void ui_draw_menu_button(int x, int y, int width, int height, const char* label, bool selected)
{
    if (selected) {
        glColor4f(0.22f, 0.42f, 0.68f, 0.92f);
    }
    else {
        glColor4f(0.08f, 0.08f, 0.10f, 0.78f);
    }

    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();

    if (selected) {
        glColor4f(0.96f, 0.98f, 1.0f, 1.0f);
    }
    else {
        glColor4f(0.58f, 0.64f, 0.72f, 0.95f);
    }

    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();

    ui_draw_text(x + 18, y + 12, label);
}

void ui_draw_pause_menu(int width, int height, bool visible, bool game_over, int selection, bool show_instructions, int instruction_scroll)
{
    if (!visible) {
        return;
    }

    const int panel_width = show_instructions ? 640 : 420;
    const int panel_height = show_instructions ? 392 : (game_over ? 286 : 304);
    const int x = (width - panel_width) / 2;
    const int y = (height - panel_height) / 2;

    ui_draw_panel(x, y, panel_width, panel_height, 0.84f);

    if (show_instructions) {
        const int line_height = 18;
        const int text_start_y = y + 54;
        const int scroll_bar_height = panel_height - 92;
        const int scroll_bar_x = x + panel_width - 20;
        const int scroll_bar_y = y + 50;
        const int line_count = (int)(sizeof(pause_instruction_lines) / sizeof(pause_instruction_lines[0]));
        const int max_scroll = ui_get_pause_instruction_max_scroll();
        int clamped_scroll = instruction_scroll;

        if (clamped_scroll < 0) {
            clamped_scroll = 0;
        }
        if (clamped_scroll > max_scroll) {
            clamped_scroll = max_scroll;
        }

        ui_draw_text(x + 22, y + 22, "HASZNALATI UTASITAS");

        for (int i = 0; i < UI_PAUSE_INSTRUCTION_VISIBLE_LINES; ++i) {
            const int line_index = clamped_scroll + i;

            if (line_index >= line_count) {
                break;
            }

            ui_draw_text(x + 22, text_start_y + i * line_height, pause_instruction_lines[line_index]);
        }

        if (max_scroll > 0) {
            const int thumb_height = (scroll_bar_height * UI_PAUSE_INSTRUCTION_VISIBLE_LINES) / line_count;
            const int thumb_travel = scroll_bar_height - thumb_height;
            const int thumb_offset = (max_scroll > 0) ? (thumb_travel * clamped_scroll) / max_scroll : 0;
            char scroll_hint[128];

            glColor4f(0.12f, 0.12f, 0.14f, 0.92f);
            glBegin(GL_QUADS);
            glVertex2i(scroll_bar_x, scroll_bar_y);
            glVertex2i(scroll_bar_x + 8, scroll_bar_y);
            glVertex2i(scroll_bar_x + 8, scroll_bar_y + scroll_bar_height);
            glVertex2i(scroll_bar_x, scroll_bar_y + scroll_bar_height);
            glEnd();

            glColor4f(0.42f, 0.62f, 0.90f, 0.96f);
            glBegin(GL_QUADS);
            glVertex2i(scroll_bar_x, scroll_bar_y + thumb_offset);
            glVertex2i(scroll_bar_x + 8, scroll_bar_y + thumb_offset);
            glVertex2i(scroll_bar_x + 8, scroll_bar_y + thumb_offset + thumb_height);
            glVertex2i(scroll_bar_x, scroll_bar_y + thumb_offset + thumb_height);
            glEnd();

            (void)snprintf(scroll_hint, sizeof(scroll_hint), "Gorgetes: egergorgeto / W-S / PgUp-PgDn   %d/%d", clamped_scroll + 1, max_scroll + 1);
            ui_draw_text(x + 22, y + panel_height - 34, scroll_hint);
        }
        else {
            ui_draw_text(x + 22, y + panel_height - 34, "Esc / Enter: vissza");
        }
    }
    else {
        const int button_y = game_over ? (y + 92) : (y + 64);

        ui_draw_text(x + 24, y + 22, game_over ? "GAME OVER" : "PAUSE MENU");

        if (game_over) {
            ui_draw_text(x + 24, y + 52, "Az ujrainditas visszatesz a kezdo szobaba.");
            ui_draw_menu_button(x + 24, button_y, panel_width - 48, 42, "Jatekkor ujrainditasa", selection == 0);
            ui_draw_menu_button(x + 24, button_y + 52, panel_width - 48, 42, "Hasznalati utasitas", selection == 1);
            ui_draw_menu_button(x + 24, button_y + 104, panel_width - 48, 42, "Kilepes", selection == 2);
        }
        else {
            ui_draw_menu_button(x + 24, button_y, panel_width - 48, 42, "Folytatas", selection == 0);
            ui_draw_menu_button(x + 24, button_y + 52, panel_width - 48, 42, "Szint ujrainditasa", selection == 1);
            ui_draw_menu_button(x + 24, button_y + 104, panel_width - 48, 42, "Hasznalati utasitas", selection == 2);
            ui_draw_menu_button(x + 24, button_y + 156, panel_width - 48, 42, "Kilepes", selection == 3);
        }

        if (game_over) {
            ui_draw_text(x + 24, y + panel_height - 34, "W/S vagy nyilak: valasztas | Enter: ok");
        }
        else {
            ui_draw_text(x + 24, y + panel_height - 34, "W/S vagy nyilak: valasztas | Enter: ok | Esc: vissza a jatekba");
        }
    }
}
