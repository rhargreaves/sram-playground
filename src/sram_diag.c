#include "sram_diag.h"
#include "sram_ed_x7.h"
#include <genesis.h>

void test_sram(void)
{
    CON_write("SRAM Test Program\n-----------------\n");

    sram_ed_x7_enable(TRUE);
    const u8 test_data = 0x53;
    CON_write("test_data = 0x%x\n", test_data);

    u8 value = sram_ed_x7_read(1);
    if (value == test_data) {
        CON_write("SRAM magic number set\n");
    } else {
        CON_write("SRAM magic number not set: 0x%x\n", value);
    }

    value = sram_ed_x7_read(1);
    if (value == test_data) {
        CON_write("SRAM magic number set\n");
    } else {
        CON_write("SRAM magic number not set: 0x%x\n", value);
    }

    sram_ed_x7_write(1, test_data);
    value = sram_ed_x7_read(1);
    if (value == test_data) {
        CON_write("Enabled: SRAM write/read (PASS)\n");
    } else {
        CON_write("Enabled: SRAM write/read (FAIL)\n");
    }
    sram_ed_x7_disable();

    const u8 slot = 2;

    value = sram_ed_x7_read(slot);
    if (value == test_data) {
        CON_write("Disabled: SRAM read OK (FAIL)\n");
    } else {
        CON_write("Disabled: SRAM not read (PASS)\n");
    }

    sram_ed_x7_write(slot, test_data);
    value = sram_ed_x7_read(slot);
    if (value == test_data) {
        CON_write("Disabled: SRAM writen OK (FAIL)\n");
    } else {
        CON_write("Disabled: SRAM not written (PASS)\n");
    }
}
