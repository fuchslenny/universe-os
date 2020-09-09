#include <kernel/drivers/graphics/vga.h>
#include <kernel/types.h>

uint32 current_cursor_location = 0;
char *vga_buffer = (char*)0xb8000;

struct color parseColor(const uint8 front_color, const uint8 back_color) {
    return (struct color) {.front=front_color, .back=back_color};
}
uint8 getColorByte(struct color *color) {
    return (color->back * 16) + color->front;
}

void setPointerToEndOfLine(int size) {
    uint32 full_line = 0;
    while (full_line < current_cursor_location) {
        full_line += LINESIZE;
    }
    current_cursor_location = (full_line - (2 * size));
}

void printc(const char c, struct color *color) {
    if (c == '\n') {
        printn();
        return;
    }
    vga_buffer[current_cursor_location++] = c;
    vga_buffer[current_cursor_location++] = getColorByte(color);
}

void prints(const char *str, struct color *color) {
    uint32 for_setter = 0;
    while (str[for_setter] != '\0') {
        uint32 a = for_setter++;
        printc(str[a], color);
    }
}

void printn() {
    uint32 i = 0;
    while (i < current_cursor_location) {
        i += LINESIZE;
    }
    current_cursor_location = i;
}

void clear_screen(struct color *color) {
    uint32 for_setter = 0;
    while (for_setter < SCREENSIZE) {
        vga_buffer[for_setter++] = ' ';
        vga_buffer[for_setter++] = getColorByte(color);
    }
}

int load_vga_driver() {
    clear_screen(&default_color);
    return 0;
}

struct color default_color = {.front=WHITE, .back=BASIC_BACKGROUND_COLOR};
struct color info_color = {.front=WHITE, .back=BASIC_BACKGROUND_COLOR};
struct color success_color = {.front=GREEN, .back=BASIC_BACKGROUND_COLOR};
struct color warning_color = {.front=YELLOW, .back=BASIC_BACKGROUND_COLOR};
struct color debug_color = {.front=YELLOW, .back=BASIC_BACKGROUND_COLOR};
struct color error_color = {.front=RED, .back=BASIC_BACKGROUND_COLOR};
struct color unknow_color = {.front=GREY, .back=BASIC_BACKGROUND_COLOR};

void kinfo(const char *str) {prints(str, &info_color);}
void ksuccess(const char *str) {prints(str, &success_color);}
void kwarning(const char *str) {prints(str, &warning_color);}
void kdebug(const char *str) {prints(str, &debug_color);}
void kerror(const char *str) {prints(str, &error_color);}
void kunknow(const char *str) {prints(str, &unknow_color);}
