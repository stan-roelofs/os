#include "screen.h"

#include <util.h>

#include "ports.h"

int get_screen_offset(int row, int column)
{
    return 2 * (row * MAX_COLS + column);
}

int get_row_offset(int offset)
{
    return offset / (2 * MAX_COLS);
}

int get_column_offset(int offset)
{
    return (offset - (get_row_offset(offset) * 2 * MAX_COLS)) / 2;
}

int get_cursor()
{
    port_byte_out(REG_SCREEN_CTRL, 14); // 14 contains the high byte of the cursor
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15); // 15 contains the low byte of the cursor
    offset += port_byte_in(REG_SCREEN_DATA);

    return offset * 2;
}

void set_cursor(int offset)
{
    offset /= 2;

    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int handle_scrolling(int offset)
{
    if (offset >= 2 * MAX_ROWS * MAX_COLS)
    {
        int i = 0;
        for (i = 1; i < MAX_ROWS; ++i)
        {
            memory_copy((char*)(VIDEO_ADDRESS + get_screen_offset(i, 0)), (char*)(VIDEO_ADDRESS + get_screen_offset(i-1, 0)), MAX_COLS * 2);
        }

        unsigned char* last_line = (unsigned char*)(VIDEO_ADDRESS + get_screen_offset(MAX_ROWS - 1, 0));
        for (i = 0; i < MAX_COLS * 2; ++i)
        {
            last_line[i] = 0;
        }

        offset -= 2 * MAX_COLS;
    }

    return offset;
}

int print_char(char character, int row, int column, char attribute_byte)
{
    unsigned char* video_memory = (unsigned char*)VIDEO_ADDRESS;

    if (!attribute_byte)
        attribute_byte = WHITE_ON_BLACK;

    int offset;
    if (column >= 0 && row >= 0)
        offset = get_screen_offset(row, column);
    else
        offset = get_cursor();

    if (character == '\n')
    {
        row = get_row_offset(offset);
        offset = get_screen_offset(row + 1, 0);
    } else {
        video_memory[offset] = character;
        video_memory[offset+1] = attribute_byte;
        offset += 2;
    }
    
    // Scroll if necessary
    offset = handle_scrolling(offset);
    set_cursor(offset);

    return offset;
}

void print_at(char* message, int row, int column)
{
    int offset;
    if (column >= 0 && row >= 0)
    {
        offset = get_screen_offset(row, column);
    } else {
        offset = get_cursor();
        row = get_row_offset(get_cursor());
        column = get_column_offset(get_cursor());
    }

    int i = 0;
    while (message[i] != 0)
    {
        offset = print_char(message[i++], row, column, WHITE_ON_BLACK);
        row = get_row_offset(offset);
        column = get_column_offset(offset);
    }
}

void print(char* message)
{
    print_at(message, -1, -1);
}

void clear_screen()
{
    unsigned char* screen = (unsigned char*)VIDEO_ADDRESS;

    for (int i = 0; i < 2 * MAX_COLS * MAX_ROWS; i += 2)
    {
        screen[i] = ' ';
        screen[i+1] = WHITE_ON_BLACK;
    }

    set_cursor(get_screen_offset(0, 0));
}