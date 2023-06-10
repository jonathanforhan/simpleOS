int
kmain(void)
{
    short *fb = (short *) 0x000b8000;
    *(fb + 0) = 0x0230 + sizeof(void *); // H

    return 0;
}
