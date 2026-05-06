#ifndef UI_H
#define UI_H

#include <stdbool.h>

void ui_begin_overlay(int width, int height);
void ui_end_overlay(void);
void ui_draw_help(int width, int height, bool visible);
void ui_draw_text(int x, int y, const char* text);

#endif /* UI_H */
