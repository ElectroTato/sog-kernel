
// Libraries
#include "lib/graphics/vga.h"
#include "lib/uart/uart.h"

// Multiboot header
__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
    0x1BADB002,
    0x00000000,
    -(0x1BADB002)
};

// Kernel entry point
void kernel_main()
{
    // Print some text, I'll try out some fancy colors here!
    terminal_draw_string("=========================\n");   
    terminal_draw_string("=  Sog OS (Version Idk) =\n");    
    terminal_draw_string("=========================\n");    

    // test UART
    uart_write_char('H');

    // Halt and catch fire
    while (1) {};
}