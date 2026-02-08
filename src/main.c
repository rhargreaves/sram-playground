#include <genesis.h>
#include "sram_diag.h"
#include "bank_diag.h"

int main()
{
    CON_reset();
    SYS_disableInts();
    Z80_requestBus(TRUE);

    // test_sram();
    test_banks();

    while (1) {
        SYS_doVBlankProcess();
    }
    return 0;
}
