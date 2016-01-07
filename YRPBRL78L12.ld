MEMORY
{
	VEC : ORIGIN = 0x0, LENGTH = 3
	IVEC : ORIGIN = 0x4, LENGTH = 189
	OPT : ORIGIN = 0xC0, LENGTH = 5
	SEC_ID : ORIGIN = 0xC4, LENGTH = 11
	ROM : ORIGIN = 0xD8, LENGTH = 32552
	RAM : ORIGIN = 0xFF900, LENGTH = 1280
	STACK : ORIGIN = 0xFFE00, LENGTH = 3
}

SECTIONS
{
	.vec 0x0 : AT (0x0)
	{
		KEEP(*(.vec))
	} > VEC
	.vects 0x4 : AT (0x4)
	{
		KEEP(*(.vects))
	} > IVEC
	.option_bytes 0xC0 : AT (0xC0)
	{
		KEEP(*(.option_bytes))
	} > OPT
	.security_id 0xC4 : AT (0xC4)
	{
		KEEP(*(.security_id))
	} > SEC_ID
	.text 0xD8 : AT (0xD8)
	{
		*(.text)
		*(.text.*)
		etext = .;
	} > ROM
	.init : 
	{
		*(.init)
	} > ROM
	.fini : 
	{
		*(.fini)
	} > ROM
	.got : 
	{
		*(.got)
		*(.got.plt)
	} > ROM
	.rodata MAX(., 0x2000) : 
	{
		*(.rodata)
		*(.rodata.*)
		_erodata = .;
	} > ROM
	.eh_frame_hdr : 
	{
		*(.eh_frame_hdr)
	} > ROM
	.eh_frame : 
	{
		*(.eh_frame)
	} > ROM
	.jcr : 
	{
		*(.jcr)
	} > ROM
	.tors : 
	{
		__CTOR_LIST__ = .;
		___ctors = .;
		*(.ctors)
		___ctors_end = .;
		__CTOR_END__ = .;
		__DTOR_LIST__ = .;
		___dtors = .;
		*(.dtors)
		___dtors_end = .;
		__DTOR_END__ = .;
		_mdata = .;
	} > ROM
	.ram_protect 0xFF900 : AT (0xFF900)
	{
	} > RAM
	.bss : 
	{
		_bss = .;
		*(.bss)
		*(.bss.**)
		*(COMMON)
		_ebss = .;
		_end = .;
	} > RAM
	.data 0xFF980 : AT (_mdata)
	{
		_data = .;
		*(.data)
		*(.data.*)
		_edata = .;
	} > RAM
	.stack 0xFFEE0 (NOLOAD)  : AT (0xFFEE0)
	{
		_stack = .;
	}
}
