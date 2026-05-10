#ifndef UI_H
#define UI_H

#include "scene.h"

#include <stdbool.h>

void ui_begin_overlay(int width, int height);
void ui_end_overlay(void);
int ui_get_pause_instruction_max_scroll(void);
void ui_draw_pause_menu(int width, int height, bool visible, int selection, bool show_instructions, int instruction_scroll);
void ui_draw_minimap(const Scene* scene, float camera_yaw_degrees, bool visible, int width, int height);
void ui_draw_text(int x, int y, const char* text);

#endif /* UI_H */
