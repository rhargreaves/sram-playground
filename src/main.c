#include "genesis.h"

const __attribute__((externally_visible)) vu8 padding[2500000] = {1};

int main() {
    (void)padding;

    CON_reset();
    CON_setConsoleSize(0, 0, 40, 28);
    CON_write("SRAM Test Program\n-----------------\n");

    SYS_disableInts();
    Z80_requestBus(TRUE);

    SRAM_enable();
    const u8 test_data = 0x42;
    CON_write("test_data = 0x%x\n", test_data);

    u8 value = SRAM_readByte(1);
    if (value == test_data) {
        CON_write("SRAM magic number set\n");
    } else {
        CON_write("SRAM magic number not set: 0x%x\n", value);
    }

    value = SRAM_readByte(1);
    if (value == test_data) {
        CON_write("SRAM magic number set\n");
    } else {
        CON_write("SRAM magic number not set: 0x%x\n", value);
    }

    SRAM_writeByte(1, test_data);
    value = SRAM_readByte(1);
    if(value == test_data) {
        CON_write("Enabled: SRAM write/read (PASS)\n");
    } else {
        CON_write("Enabled: SRAM write/read (FAIL)\n");
    }
    SRAM_disable();

    value = SRAM_readByte(2);
    if(value == test_data) {
        CON_write("Disabled: SRAM read OK (FAIL)\n");
    } else {
        CON_write("Disabled: SRAM not read (PASS)\n");
    }

    SRAM_writeByte(2, test_data);
    value = SRAM_readByte(2);
    if(value == test_data) {
        CON_write("Disabled: SRAM writen OK (FAIL)\n");
    } else {
        CON_write("Disabled: SRAM not written (PASS)\n");
    }

    while (1) {
        SYS_doVBlankProcess();
    }
    return 0;
}
