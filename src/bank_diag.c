#include <genesis.h>
#include "config.h"
#include "data.h"
#include "mapper.h"
#include "ui.h"

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

void bank_diag(void)
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

    CON_write("Done\n");
}
