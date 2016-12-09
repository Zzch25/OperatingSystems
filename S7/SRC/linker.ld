ENTRY(_start)

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

	/* Read-write data */
	.data ALIGN(4K) : AT( ADDR(.data) )
	{
		*(.data)
		*(.rodata)
	}

	/* Read, write, and stack */
	.bss ALIGN(4K) : AT( ADDR(.bss) )
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	
	end = .;
}