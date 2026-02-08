#include <genesis.h>
#include "config.h"
#include "data.h"
#include "mapper.h"
#include "vdp.h"
#include "vdp_bg.h"

static const void* NEAR_BANKS[] = {
    data1,
    data2,
    data3,
    data4,
    data5,
    data6,
    data7,
};

static const void* FAR_BANKS[] = { data8, data9, data10 };

static void print_pass(void)
{
    VDP_setTextPalette(PAL2);
    CON_write("Pass\n");
    VDP_setTextPalette(PAL0);
}

static void print_fail(void)
{
    VDP_setTextPalette(PAL1);
    CON_write("Fail\n");
    VDP_setTextPalette(PAL0);
}

static void print_result(bool res)
{
    if (res) {
        print_pass();
    } else {
        print_fail();
    }
    // SYS_getBank(u16 regionIndex)
}

static void test_bank_at(const void* addr)
{
    CON_write("Near %06lX: ", (u32)addr);
    print_result(*((char*)addr) == 0x31);
}

static void test_bank_invalid_at(const void* addr)
{
    CON_write("Near invalid %06lX: ", (u32)addr);
    print_result(*((char*)addr) != 0x31);
}

static void test_far_bank_at(const void* addr)
{
    CON_write("Far %06lX: ", (u32)addr);
    print_result(*((char*)FAR(addr)) == 0x31);
}

void test_banks(void)
{
    CON_write("Bank Test Program\n-----------------\n");
    CON_write("ENABLE_BANK_SWITCH: %i\n", ENABLE_BANK_SWITCH);

    for (int i = 0; i < 7; i++) {
        test_bank_at(NEAR_BANKS[i]);
    }

    for (int i = 0; i < 3; i++) {
        test_bank_invalid_at(FAR_BANKS[i]);
    }

    for (int i = 0; i < 3; i++) {
        test_far_bank_at(FAR_BANKS[i]);
    }

    CON_write("Done");
}
