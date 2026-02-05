#include <genesis.h>
#include "sram_diag.h"
#include "bank_diag.h"

const __attribute__((externally_visible)) vu8 padding[2500000] = { 1 };

#if (ENABLE_BANK_SWITCH != 1)
#error Enable bank switching in SGDK lib
#endif

int main()
{
    (void)padding;

    CON_reset();
    CON_setConsoleSize(0, 0, 40, 28);

    SYS_disableInts();
    Z80_requestBus(TRUE);

    // test_sram();
    test_banks();

    while (1) {
        SYS_doVBlankProcess();
    }
    return 0;
}
