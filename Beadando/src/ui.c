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

#include <stdio.h>
#include <string.h>

static void ui_draw_panel(int x, int y, int width, int height, float fill_alpha);
static void ui_draw_menu_button(int x, int y, int width, int height, const char* label, bool selected);

static const char* pause_instruction_lines[] = {
    "Jatek",
    "",
    "  W/A/S/D   mozgas",
    "  Mouse     kamera forgatas Isaac fejebol",
    "  Q         lovedek kilovese",
    "  E         ajto hasznalata, ha a szoba tiszta",
    "  Esc       pause menu / vissza",
    "  Enter     menu pont megerositese",
    "",
    "Harc",
    "",
    "  Tobb lovedek lehet egyszerre aktiv",
    "  A lovedek falnak vagy akadalyoknak utkozve eltunik",
    "  A masodik szobaban az enemy tavolrol is tamad",
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

void ui_draw_pause_menu(int width, int height, bool visible, int selection, bool show_instructions, int instruction_scroll)
{
    if (!visible) {
        return;
    }

    const int panel_width = show_instructions ? 640 : 420;
    const int panel_height = show_instructions ? 392 : 250;
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
        ui_draw_text(x + 24, y + 22, "PAUSE MENU");

        ui_draw_menu_button(x + 24, y + 66, panel_width - 48, 42, "Folytatas", selection == 0);
        ui_draw_menu_button(x + 24, y + 118, panel_width - 48, 42, "Hasznalati utasitas", selection == 1);
        ui_draw_menu_button(x + 24, y + 170, panel_width - 48, 42, "Kilepes", selection == 2);

        ui_draw_text(x + 24, y + panel_height - 34, "W/S vagy nyilak: valasztas | Enter: ok | Esc: vissza a jatekba");
    }
}
