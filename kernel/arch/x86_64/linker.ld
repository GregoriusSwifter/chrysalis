ENTRY(_start)
SECTIONS
{
	. = 1M;
    _kernel = .;
	.text BLOCK(4K) : ALIGN(4K)
	{
        _text = .;
        *(.multiboot);
        *(.text);
        _text_end = .;
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
        _rodata = .;
        *(.rodata*);
        _rodata_end = .;
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		_data = .;
        *(.data);
        _data_end = .;
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
        _bss = .;
        *(COMMON)
        *(.bss);
        *(.bss*);
        _bss_end = .;
	}
    /DISCARD/ :
    {
        *(.gnu.version_r*);
        *(.eh_frame*);
        *(.note*);
        *(.iplt*);
        *(.igot*);
        *(.rel*);
        *(.comment);
        /* add any unwanted sections spewed out by your version of gcc and flags here */
    }
    _kernel_end = .;
}
