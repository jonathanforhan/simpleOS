int
kmain(void)
{
    short *fb = (short *) 0x000b8000;
    *(fb + 0) = 0x0248; // H
    *(fb + 1) = 0x0265; // e
    *(fb + 2) = 0x026c; // l
    *(fb + 3) = 0x026c; // l
    *(fb + 4) = 0x026f; // o

    return 0;
}
