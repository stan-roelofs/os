#define VIDEO_MEMORY 0xb8000

void clear_screen()
{
    char* vga = (char*)VIDEO_MEMORY;
    for (unsigned int i = 0; i < (80 * 25 * 2); i += 2)
    {
        vga[i] = ' ';
    }
}

void print_string(const char* message)
{
    char* vga = (char*)VIDEO_MEMORY;
    unsigned int i = 0;

    while (*message != 0)
    {
        *vga++ = *message++;
        *vga++ = 0x0f;
    }
}

void main()
{
    clear_screen();
    print_string("Hello, world!");
}