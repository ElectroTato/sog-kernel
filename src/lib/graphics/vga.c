// libs
#include "../types.h"

// keep track of where our cursor is so we don't overwrite any characters
static int vga_cursor_posX = 0; // Row (80 of those)
static int vga_cursor_posY = 0; // Column (25 of those)

// video variables

// White on black by default
static int textColor = 0x0F;
// VGA Text Buffer
static uint16_t* video = (uint16_t*)0xB8000;

// scroll function
void scroll() {
    for (int i = 0; i < 24 * 80; i++) {
        video[i] = video[i + 80];
    }

    // clear last row
    for (int x = 0; x < 80; x++) {
        video[24 * 80 + x] = 0x0F20;
    }
}

// helper function to draw a single character
// TODO : Remake this to support newlines, we live in a cruel world
// Had to get some help from A.I here
void terminal_draw_char(char character)
{

    // scroll if we're over row 25
    if (vga_cursor_posY > 24) {
        scroll();
    }

    if (character == '\n') {
        vga_cursor_posX = 0;
        vga_cursor_posY++;
        return;
    }

    if (vga_cursor_posX >= 80) {
        vga_cursor_posX = 0;
        vga_cursor_posY++;
    }

    int cursorPos = vga_cursor_posY * 80 + vga_cursor_posX;

    video[cursorPos] = (textColor << 8) | character;

    vga_cursor_posX++;
}

// helper function to draw a string, no printf cuz it's too hard to code
void terminal_draw_string(char* str)
{

    // loop through every character in the array
    // ok i'll use a while *str instead of a for loop to OPTIONALLY not open a pit to hell this time
    while (*str) {
        terminal_draw_char(*str);
        str++;
    }
}

void terminal_setcolor(int color)
{
    textColor = color;
}
