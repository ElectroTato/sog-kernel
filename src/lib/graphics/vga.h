// libs
#include "../types.h"

// vga.h
#ifndef VGA_H
#define VGA_H

void terminal_draw_char(char character);
void terminal_draw_string(char* str);
void terminal_setcolor(int color);

void scroll();

#endif