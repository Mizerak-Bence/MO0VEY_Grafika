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

void ui_draw_help(int width, int height, bool visible)
{
    (void)height;

    if (!visible) {
        return;
    }

    const char* help =
        "F1: toggle help\n"
        "Esc: quit\n"
        "\n"
        "Player + camera:\n"
        "  W/A/S/D: move player\n"
        "  Mouse (hold LMB): orbit camera\n"
        "  (no up/down movement)\n"
        "\n"
        "Objects:\n"
        "  1/2: select object\n"
        "  I/J/K/L: move X/Y\n"
        "  U/O: move Z\n"
        "  R: toggle auto-rotate\n"
        "\n"
        "Light:\n"
        "  Arrows: move X/Y\n"
        "  PgUp/PgDn: move Z\n"
        "  +/-: intensity\n";

    ui_draw_text(10, 10, help);

    char hint[128];
    (void)snprintf(hint, sizeof(hint), "Viewport: %dx%d", width, height);
    ui_draw_text(10, 220, hint);
}
