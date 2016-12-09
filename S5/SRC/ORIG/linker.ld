ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
TARGET(elf32-i386)

SECTIONS
{
	/* Begin @ 1 MB*/
	. = 1M;
	
	.__mbHeader : AT( ADDR(.__mbHeader) ) 
	{
      *(.__mbHeader)
    }
	
	/* multiboot header -> text */
	.text ALIGN(4K) : AT( ADDR(.text) )
	{
		*(.text)
	}

	/* Read only data 
	.rodata ALIGN(4K) : AT( ADDR(.rodata) )
	{
		*(.rodata)
	}*/

	/* Read-write data */
	.data ALIGN(4K) : AT( ADDR(.data) )
	{
		*(.data)
		*(.rodata)
	}

	/* Read, write, and stack */
	.bss ALIGN(4K) : AT( ADDR(.bss) )
	{
		/* *(COMMON)*/
		*(.bss)
		*(.bootstrap_stack)
	}

	/* Additional Here */
}