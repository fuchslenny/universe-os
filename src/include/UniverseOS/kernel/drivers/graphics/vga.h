#ifndef VGA_H
#define VGA_H

#include <kernel/types.h>

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define LINESIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE
#define SCREENSIZE LINES * LINESIZE

extern uint32 current_cursor_location;
extern char *vga_buffer;

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

struct color {
    uint8 front;
    uint8 back;
};
struct color parseColor(uint8 front_color, uint8 back_color);
uint8 getColorByte(struct color *color);

int load_vga_driver();
void setPointerToEndOfLine(int size);
void clear_screen();
void printn();
void prints(const char *str, struct color *color);
void printc(const char c, struct color *color);

#define BASIC_BACKGROUND_COLOR 0 // black
extern struct color default_color;

extern struct color info_color;
extern struct color success_color;
extern struct color warning_color;
extern struct color debug_color;
extern struct color error_color;
extern struct color unknow_color;

void kinfo(const char *str);
void ksuccess(const char *str);
void kwarning(const char *str);
void kdebug(const char *str);
void kerror(const char *str);
void kunknow(const char *str);
#endif