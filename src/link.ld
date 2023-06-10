ENTRY(start)

SECTIONS {
    . = 0x00100000;

    .boot :
    {
        /* multiboot_header at beginning */
        *(.multiboot_header)
    }

    .text :
    {
        *(.text)
    }
}
