//Many thanks to OSDev and James Malloy!

#include <stddef.h>
#include <stdint.h>

#include "busopetc/descriptor_tables.h"
//#include "prereq/malloc.c" //prepare

//DEBUG
extern "C" void kill_kernel();

/* Hardware text mode color constants. */
enum vga_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};
 
uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

/*
void *operator new(size_t size)
{
    return malloc(size);
}
 
void *operator new[](size_t size)
{
    return malloc(size);
}
 
void operator delete(void *p)
{
    free(p);
}
 
void operator delete[](void *p)
{
    free(p);
}
*/ 
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint8_t terminal_header;
uint16_t* terminal_buffer;
const char* header;
 
void terminal_initialize()
{
	terminal_row = 1;
	terminal_column = 0;
	terminal_color = make_color(COLOR_RED, COLOR_BLACK);
	terminal_header = make_color(COLOR_BLACK, COLOR_RED);
	terminal_buffer = (uint16_t*) 0xB8000;
	header = "25OS";
	
	for( size_t x = 0; x < VGA_WIDTH; x++)
		terminal_buffer[x] = make_vgaentry(' ', terminal_header);
		
	for( size_t s = VGA_WIDTH/2 - strlen(header)/2, x = 0; x < strlen(header); x++, s++)
		terminal_buffer[s] = make_vgaentry(header[x], terminal_header);
	
	for ( size_t y = 1; y < VGA_HEIGHT - y; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
	
	for( size_t x = VGA_HEIGHT*VGA_WIDTH; x < VGA_HEIGHT*VGA_WIDTH + VGA_WIDTH; x++ )
		terminal_buffer[x] = make_vgaentry(' ', terminal_header);
}

void terminal_scroll()
{
	for ( size_t y = 1; y < VGA_HEIGHT - y; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			const size_t index2 = (y+1) * VGA_WIDTH + x;
			terminal_buffer[index] = terminal_buffer[index2];
		}
	}
}
 
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}
 
void terminal_putchar(char c)
{
	if(c=='\n')
	{
		if ( ++terminal_row == VGA_HEIGHT )
		{
			terminal_row--;
			terminal_scroll();
		}
		terminal_column=0;
	}
	else
	{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		
		if ( ++terminal_column == VGA_WIDTH )
		{
			terminal_column = 0;
			if ( ++terminal_row == VGA_HEIGHT )
			{
				terminal_row--;
				terminal_scroll();
			}
		}
	}
}
 
void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	
	for (size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}

extern "C"
void kernel_main()
{
	terminal_initialize();
	/* Since there is no support for newlines in terminal_putchar yet, \n will
	   produce some VGA specific character instead. This is normal. */
	terminal_writestring("25OS TERMINAL STAGE\nKERNEL LEVEL\nBUILD:PSF022\n================================================================================\n");
	terminal_writestring(":::Libraries (UNLKULP):::\n:::Interrupts Completed:::\n:::TBD:::\nVFS\nRam Disk\nMuTsk\nUser Mode");
	
	terminal_writestring("\n\nTesting Interrupts (Keyboards Coming Soon!)...");
	
	terminal_writestring("\nSetting GDT & Initializing IDT...\n\n");
	init_descriptor_tables();
	
	terminal_writestring("Clobbering...\n");
	asm volatile ("int $0x1"); //EXP crashzone
	terminal_writestring("0x1 Handled\n");
	terminal_writestring("Clobbering...\n");
	asm volatile ("int $0x25"); //EXP crashzone
	terminal_writestring("0x25 Handled\n");
}

extern "C" void __cxa_pure_virtual()
{
    terminal_writestring("ERROR: COULD NOT MAKE PVF");
}