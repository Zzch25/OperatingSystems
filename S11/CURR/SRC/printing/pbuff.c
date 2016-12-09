#include "../sysdef/pbuff.h"

enum colors
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LGREY = 7,
	DGREY = 8,
	LBLUE = 9,
	LGREEN = 10,
	LCYAN = 11,
	LRED = 12,
	LMAGENTA = 13,
	LBROWN = 14,
	WHITE = 15,
};
 
u8int color(enum colors fg, enum colors bg)
{
	return fg | bg << 4;
}
 
u16int colorset(char in, u8int color)
{
	u16int char16 = in;
	u16int color16 = color;
	
	return char16 | color16 << 8;
}
 
static const u16int W = 80;
static const u16int H = 24;

u16int cLoc = 0;

u16int srow;
u16int scolumn;
u8int scolor;
u8int sheader;
u16int* sbuffer;
const char* header;
 
void terminal_init()
{
	srow = 1;
	scolumn = 0;
	scolor = color(RED, BLACK);
	sheader = color(BLACK, RED);
	sbuffer = (u16int*) 0xB8000;
	header = "25OS";
	
	u16int x;
	u16int s;
	u16int y;
	
	for(x = 0; x < W; x++)
		sbuffer[x] = colorset(' ', sheader);
		
	for(x = H*W; x < H*W + W; x++ )
		sbuffer[x] = colorset(' ', sheader);
		
	for(s = W/2 - strlen(header)/2, x = 0; x < strlen(header); x++, s++)
		sbuffer[s] = colorset(header[x], sheader);
	
	for (y = 1; y < H - y; y++ )
	{
		for (x = 0; x < W; x++ )
		{
			const u16int index = y * W + x;
			sbuffer[index] = colorset(' ', scolor);
		}
	}
}

static void mcursor()
{
    cLoc = srow*W + scolumn;
    outb(0x3D4, 14);                  //ready for high cursor B
    outb(0x3D5, cLoc >> 8); //send
    outb(0x3D4, 15);                  //ready for low cursor B
    outb(0x3D5, cLoc);      //send
}

void scroll()
{
	u16int pos;
	for (pos = W; pos < H*W-W; pos++) sbuffer[pos] = sbuffer[pos+W];
	for (; pos < H*W; pos++) sbuffer[pos] = ' ';
}

void kochr(char in)
{
    if(in == '\n')
	{
		if ( ++srow == H )
		{
			scroll();
			srow = H-1;
		}
		scolumn=0;
	}
	else if(in >= ' ')
	{
		sbuffer[srow*W + scolumn] = colorset(in, scolor);
		
		if ( ++scolumn == W )
		{
			scolumn = 0;
			if ( ++srow == H )
			{
				scroll();
				srow = H-1;
			}
		}
	}
	
	mcursor();
}
 
void kout(const char* in)
{
	u32int len = strlen(in);
	u32int i;
	
	for (i = 0; i < len; i++ )
		kochr(in[i]);
}


void koint(s32int in)
{
	u32int i;
	
	if(in<0)
	{	
		kochr('-');
		in*=-1;
	}
	
	for(i=1; (in/i)>=10; i*=10);
	for(; i>=1; i/=10)
		kochr('0'+(((in/i)%10)%10));
}

void kohex(s32int in)
{
	kout("0x");
		
	char* clist= "0123456789ABCDEF";
	u32int i;
	
    for (i = 28; i > 0; i -= 4)
        kochr(clist[(in >> i) & 0xF]);
    kochr(clist[in & 0xF]);
}
