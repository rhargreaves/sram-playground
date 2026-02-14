#include "ui.h"

void print_pass(void)
{
    VDP_setTextPalette(PAL2);
    CON_write("Pass\n");
    VDP_setTextPalette(PAL0);
}

void print_fail(void)
{
    VDP_setTextPalette(PAL1);
    CON_write("Fail\n");
    VDP_setTextPalette(PAL0);
}

void print_result(bool res)
{
    if (res) {
        print_pass();
    } else {
        print_fail();
    }
}
