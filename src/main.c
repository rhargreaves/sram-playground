#include <genesis.h>
#include "sram_diag.h"
#include "bank_diag.h"

static bool test_bank_mapper = true;
static bool test_sram = false;

int main()
{
    CON_reset();
    SYS_disableInts();
    Z80_requestBus(TRUE);

    if (test_bank_mapper) {
        bank_diag();
    }
    if (test_sram) {
        sram_diag();
    }

    while (1) {
        SYS_doVBlankProcess();
    }
    return 0;
}
